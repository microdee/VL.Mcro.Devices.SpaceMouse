#include "HidSupportedDevice.h"

namespace NS_SM
{
    // Source of info: https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/intern/ghost/intern/GHOST_NDOFManager.cpp#L101

    static RegisterSupportedDevice SpaceExplorer(
    {
        .Model = {"Space Explorer", 0x046d, 0xc627},
        .Family =
        {
            .Reading = SeparateReportTransRotHidReading,
            .Record = {
                .ButtonMap =
                {
                    {  0, Buttons::Cmd::KeyF1        },
                    {  1, Buttons::Cmd::KeyF2        },
                    {  2, Buttons::Cmd::ViewTop      },
                    {  3, Buttons::Cmd::ViewLeft     },
                    {  4, Buttons::Cmd::ViewRight    },
                    {  5, Buttons::Cmd::ViewFront    },
                    {  6, Buttons::Cmd::KeyEsc       },
                    {  7, Buttons::Cmd::KeyAlt       },
                    {  8, Buttons::Cmd::KeyShift     },
                    {  9, Buttons::Cmd::KeyCtrl      },
                    { 10, Buttons::Cmd::ViewFit      },
                    { 11, Buttons::Cmd::MenuOptions  },
                    { 12, Buttons::Cmd::ScalePlus    },
                    { 13, Buttons::Cmd::ScaleMinus   },
                    { 14, Buttons::Cmd::FilterRotate },
                }
            }
        }
    });
}