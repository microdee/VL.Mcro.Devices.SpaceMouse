#include "HidSupportedDevice.h"

namespace NS_SM
{
    static RegisterSupportedDevice SpaceMouseEnterprise(
    {
        .Model = {"Space Pilot Pro", 0x046d, 0xc629},
        .Family = 
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });
}