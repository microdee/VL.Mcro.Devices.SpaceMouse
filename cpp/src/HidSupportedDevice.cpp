#include "HidSupportedDevice.h"

namespace NS_SM
{
    std::vector<HidSupportedDevice> SupportedDevices;
    
    RegisterSupportedDevice::RegisterSupportedDevice(HidSupportedDevice&& Device)
    {
        SupportedDevices.push_back(std::move(Device));
    }
}