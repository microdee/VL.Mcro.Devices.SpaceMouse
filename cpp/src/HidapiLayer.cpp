#include "HidapiLayer.h"
#include "OnScopeExit.h"
#include <format>

namespace NS_SM
{
    HidDeviceInfo::HidDeviceInfo(hid_device_info const& source)
        : Path(source.path)
        , VendorId(source.vendor_id)
        , ProductId(source.product_id)
        , SerialNumber(source.serial_number)
        , ReleaseNumber(source.release_number)
        , ManufacturerString(source.manufacturer_string)
        , ProductString(source.product_string)
        , UsagePage(source.usage_page)
        , Usage(source.usage)
        , InterfaceNumber(source.interface_number)
        , BusType(source.bus_type)
    {}

    bool EnumerateDevices(std::function<void(int, HidDeviceInfo const&)> callback)
    {
        auto devInfo = hid_enumerate(0, 0);
        auto firstDevInfo = devInfo;
        if (!devInfo)
        {
            return false;
        }
        ON_SCOPE_EXIT
        {
            hid_free_enumeration(firstDevInfo);
        };

        int order = 0;
        while (devInfo)
        {
            callback(order, *devInfo);
            devInfo = devInfo->next;
            order++;
        }

        return true;
    }
    
    ScopedHidDevice::ScopedHidDevice(ScopedHidDevice&& from)
        : LastError(std::move(from.LastError))
        , DeviceInfo(from.DeviceInfo)
        , Device(from.Device)
    {
		from.Device = nullptr;
    }

    ScopedHidDevice::ScopedHidDevice(HidDeviceInfo const& deviceInfo) : DeviceInfo(deviceInfo)
    {
        Device = hid_open_path(deviceInfo.Path.c_str());
        if (!Device)
        {
            LastError = "Failed to open device";
            if (auto hidError = hid_error(nullptr))
            {
                LastHidError = hidError;
            }
            return;
        }
        if (hid_set_nonblocking(Device, 1) < 0)
        {
            LastError = "Failed to set non-blocking mode";
            if (auto hidError = hid_error(Device))
            {
                LastHidError = hidError;
            }
            hid_close(Device);
            Device = nullptr;
            return;
        }
    }

    ScopedHidDevice::ScopedHidDevice()
    {
        LastError = "Empty device";
    }

    ScopedHidDevice::~ScopedHidDevice()
    {
        if (Device)
        {
            hid_close(Device);
            Device = nullptr;
        }
    }

    int ScopedHidDevice::Read(uint8_t* output, size_t length)
    {
		if (!Device)
		{
			LastError = "Attempting to read empty device";
			return -1;
		}
        int result = hid_read(Device, output, length);
        if (result < 0)
        {
            LastError = std::format("Failed to read from device: {}", DeviceInfo.Path);
            if (auto hidError = hid_error(Device))
            {
                LastHidError = hidError;
            }
        }
        return result;
    }
}