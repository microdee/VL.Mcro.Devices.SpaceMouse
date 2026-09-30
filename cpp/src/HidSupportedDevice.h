
#pragma once

#include <cstdint>
#include <string>
#include <map>

#include "HidDeviceReading.h"

namespace NS_SM
{
    using namespace std::string_literals;

    struct HidDeviceModel
    {
        std::string Name;
        uint16_t Vid = 0;
        uint16_t Pid = 0;
    };

    struct HidDeviceFamily
    {
        HidReading Reading;
        HidDeviceFamilyRecord Record;
    };

    struct HidSupportedDevice
    {
        HidDeviceModel Model;
        HidDeviceFamily Family;
    };

    extern std::vector<HidSupportedDevice> SupportedDevices;

    struct RegisterSupportedDevice
    {
        RegisterSupportedDevice(HidSupportedDevice&& Device);
    };
}