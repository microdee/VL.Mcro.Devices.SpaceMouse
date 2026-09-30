#include "HidSupportedDevice.h"

namespace NS_SM
{
    static HidDeviceFamily SpaceMouseEnterpriseFamily
    {
        .Reading = SingleReportTransRotHidReading,
        .Record = {
            .ButtonReport = ButtonQueue_Report28,
        }
    };

    static RegisterSupportedDevice SpaceMouseEnterprise(
    {
        .Model = {"Space Mouse Enterprise", 0x256f, 0xc633},
        .Family = SpaceMouseEnterpriseFamily
    });

    static RegisterSupportedDevice UniversalReceiver(
    {
        .Model = {"Universal Receiver", 0x256f, 0xc652},
        .Family = SpaceMouseEnterpriseFamily
    });
}