#include "HidSupportedDevice.h"

namespace NS_SM
{
    static RegisterSupportedDevice SpaceMousePro(
    {
        .Model = {"Space Mouse Pro", 0x046d, 0xc62b},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceMouseProWL(
    {
        .Model = {"Space Mouse Pro Wireless (Receiver)", 0x256f, 0xc632},
        .Family =
        {
            .Reading = SingleReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceMouseProUSB(
    {
        .Model = {"Space Mouse Pro Wireless (USB cable)", 0x256f, 0xc631},
        .Family =
        {
            .Reading = SingleReportTransRotHidReading
        }
    });
}