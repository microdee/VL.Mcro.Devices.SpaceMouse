#pragma once

#include <functional>
#include <string>
#include <span>

#include "hidapi/hidapi.h"

#include "Namespace.h"

namespace NS_SM
{
    struct HidDeviceInfo
    {
        std::string  Path{};
        uint16_t     VendorId = 0;
        uint16_t     ProductId = 0;
        std::wstring SerialNumber{};
        uint16_t     ReleaseNumber = 0;
        std::wstring ManufacturerString{};
        std::wstring ProductString{};
        uint16_t     UsagePage = 0;
        uint16_t     Usage = 0;
        int          InterfaceNumber = 0;
        hid_bus_type BusType = HID_API_BUS_UNKNOWN;

        HidDeviceInfo() {}
        HidDeviceInfo(hid_device_info const& source);

        HidDeviceInfo(const HidDeviceInfo&) = default;
        HidDeviceInfo(HidDeviceInfo&&) noexcept = default;
        HidDeviceInfo& operator = (const HidDeviceInfo&) = default;
        HidDeviceInfo& operator = (HidDeviceInfo&&) noexcept = default;
    };

    bool EnumerateDevices(std::function<void(int, HidDeviceInfo const&)> callback);

    struct ScopedHidDevice
    {
        ScopedHidDevice(ScopedHidDevice&& from);
        ScopedHidDevice(ScopedHidDevice const&) = delete;
        ScopedHidDevice& operator = (ScopedHidDevice const&) = delete;

        ScopedHidDevice(HidDeviceInfo const& deviceInfo);
        ScopedHidDevice();
        ~ScopedHidDevice();

        int Read(uint8_t* output, size_t length);
        inline bool IsOpen() const { return Device != nullptr; }
        
        std::string LastError {};
		std::wstring LastHidError {};
        HidDeviceInfo DeviceInfo {};

    private:
        hid_device* Device = nullptr;
    };
}