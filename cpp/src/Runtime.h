#pragma once

#include <chrono>
#include <thread>
#include <map>
#include <thread>
#include <shared_mutex>

#include "gcroot.h"

#include "HidSupportedDevice.h"
#include "HidapiLayer.h"
#include "SmOutput.h"
#include "OnScopeExit.h"

namespace NS_SM
{
    using namespace System;
    using namespace System::Reactive;
    using namespace VL::Core;

    struct SmDeviceInstance
    {
        HidSupportedDevice DeviceModel;
        ScopedHidDevice Device;

        SmDeviceInstance(HidSupportedDevice const& model, HidDeviceInfo const& info);
    };

    ref class AppExitObserver : public System::IObserver<Unit>
    {
    public:
        virtual void OnNext(Unit);
        virtual void OnError(Exception^) {}
        virtual void OnCompleted();
    };
    
    struct SmGlobals
    {
        bool NeedsStart = true;

        std::unordered_map<uint32_t, SmDeviceInstance> Instances;
        std::shared_mutex Access;
        std::chrono::time_point<std::chrono::high_resolution_clock> LastCheck;

        gcroot<SmOutputManaged^> ManagedOutput;
        std::jthread AsyncMainLoop;
    };

    void DiscoverDevices();
    void RuntimeLoop();
    void RuntimeMainloop(std::stop_token stopToken);
    
    public ref class SmRuntime
    {
    public:
        static SmOutputManaged^ SpaceMouseMainLoop();
    };
}