
#pragma once

#include <cstdint>
#include <string>
#include <map>

#include "Buttons.h"

namespace NS_SM
{
    enum ButtonMode
    {
        ButtonBits_Report3,
        ButtonQueue_Report28
    };

    struct HidDeviceFamilyRecord
    {
        int AxisResolution = 350;
        ButtonMode ButtonReport = ButtonBits_Report3;
        std::map<uint16_t, Buttons::Cmd> ButtonMap = Buttons::ThDxModern;
    };
}