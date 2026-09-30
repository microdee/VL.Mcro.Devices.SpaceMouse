#pragma once

#include <functional>

#include "Namespace.h"
#include "HidDeviceFamilyRecord.h"

namespace NS_SM
{
    class SmOutput;
    class ScopedHidDevice;

    struct HidReadingParams
    {
        size_t ReportSize = 0;
        size_t ReportCount = 0;
    };

    struct HidReadCallbackParams
    {
        SmOutput& HighLevelOutput;
        uint8_t* Output;
        size_t OutputLength;
        HidReadingParams const& ReadingParams;
        HidDeviceFamilyRecord const& Family;
    };

    template <typename... Axes>
    bool CheckAxes(HidReadCallbackParams const& params, Axes... axes)
    {
        return ((axes <= params.Family.AxisResolution) && ...)
            && ((-axes <= params.Family.AxisResolution) && ...);
    }

    using HidReadCallback = std::function<void(HidReadCallbackParams const&)>;

    struct HidReading
    {
        HidReadingParams Params;
        HidReadCallback Read;
    };

    extern HidReading SingleReportTransRotHidReading;
    extern HidReading SeparateReportTransRotHidReading;
}