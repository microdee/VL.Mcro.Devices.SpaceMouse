#include "HidSupportedDevice.h"

namespace NS_SM
{
    static RegisterSupportedDevice SpaceMouseCompact(
    {
        .Model = {"Space Mouse Compact", 0x256f, 0xc635},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });
    
    static RegisterSupportedDevice SpaceMouseWL(
    {
        .Model = {"Space Mouse Wireless (Receiver)", 0x256f, 0xc62e},
        .Family =
        {
            .Reading = SingleReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceMouseUSB(
    {
        .Model = {"Space Mouse Wireless (USB cable)", 0x256f, 0xc62e},
        .Family =
        {
            .Reading = SingleReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceNavigator(
    {
        .Model = {"Space Navigator", 0x046d, 0xc626},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceNavigatorNotebook(
    {
        .Model = {"Space Navigator for Notebooks", 0x046d, 0xc628},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });

    static RegisterSupportedDevice SpaceTraveler(
    {
        .Model = {"Space Traveler", 0x046d, 0xc623},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading
        }
    });
}