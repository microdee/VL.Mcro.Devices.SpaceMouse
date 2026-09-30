#include "Runtime.h"

namespace NS_SM
{
    using namespace VL::Core;

    using namespace std::chrono_literals;

    SmDeviceInstance::SmDeviceInstance(HidSupportedDevice const& model, HidDeviceInfo const& info)
        : DeviceModel(model)
        , Device(info)
    {}

    static SmGlobals Globals;

    static void DiscoverDevices()
    {
        using namespace std::chrono_literals;

        std::jthread asyncEnumerate([]
        {
            // TODO: handle device removal
            EnumerateDevices([](int order, HidDeviceInfo const& info)
            {
                for (auto const& model : SupportedDevices)
                {
                    uint32_t combinedId = model.Model.Vid | (model.Model.Pid << 16);
                    bool deviceAlreadyOpened = [&]
                    {
                        std::shared_lock lock(Globals.Access);
                        return Globals.Instances.contains(combinedId);
                    }();
                    if (!deviceAlreadyOpened && model.Model.Vid == info.VendorId && model.Model.Pid == info.ProductId)
                    {
                        std::lock_guard lock(Globals.Access);
                        Globals.Instances.emplace(combinedId, SmDeviceInstance(model, info));
                    }
                }
            });
        });
        asyncEnumerate.detach();
    }

    static void RuntimeLoop()
    {
        auto now = std::chrono::high_resolution_clock::now();
        if (now - Globals.LastCheck > 1600ms)
        {
            DiscoverDevices();
            Globals.LastCheck = now;
        }

        std::shared_lock lock(Globals.Access);
		Globals.ManagedOutput->Native->Reset();

        for (auto& [key, instance] : Globals.Instances)
        {
            for (int ctr = 0; ctr < 2048; ++ctr)
            {
                auto [reportSize, reportCount] = instance.DeviceModel.Family.Reading.Params;
                std::vector<uint8_t> buffer(reportSize * reportCount, '\0');

                int readResult = instance.Device.Read(buffer.data(), reportSize * reportCount);
                if (readResult < 0)
                {
                    break;
                }
                if (readResult > 0)
                {
                    instance.DeviceModel.Family.Reading.Read(HidReadCallbackParams{
                        .HighLevelOutput = *Globals.ManagedOutput->Native,
                        .Output = buffer.data(),
                        .OutputLength = reportSize * reportCount,
                        .ReadingParams = instance.DeviceModel.Family.Reading.Params,
                        .Family = instance.DeviceModel.Family.Record
                    });
                }
                else break;
            }
        }
    }

    void RuntimeMainloop(std::stop_token stopToken)
    {
        hid_init();
        Globals.LastCheck = std::chrono::high_resolution_clock::now();
        DiscoverDevices();

        while (!stopToken.stop_requested())
        {
            RuntimeLoop();
            std::this_thread::sleep_for(5ms);
        }
        hid_exit();
    }

    SmOutputManaged^ SmRuntime::SpaceMouseMainLoop()
    {
        if (Globals.NeedsStart)
        {
            Globals.NeedsStart = false;
            Globals.ManagedOutput = gcnew SmOutputManaged();
            Globals.AsyncMainLoop = std::jthread(RuntimeMainloop);
            AppHost::CurrentOrGlobal->OnExit->Subscribe(gcnew AppExitObserver());
        }
        return Globals.ManagedOutput;
    }

    void AppExitObserver::OnNext(Unit)
    {
        OnCompleted();
    }

    void AppExitObserver::OnCompleted()
    {
        if (!Globals.NeedsStart && Globals.AsyncMainLoop.joinable())
        {
            Globals.AsyncMainLoop.request_stop();
        }
    }
}