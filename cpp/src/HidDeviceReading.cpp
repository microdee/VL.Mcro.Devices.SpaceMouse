#include "HidDeviceReading.h"
#include "SmOutput.h"
#include "Buttons.h"

namespace NS_SM
{
    struct TransRotReport
    {
        int16_t TransX;
        int16_t TransY;
        int16_t TransZ;
        int16_t RotX;
        int16_t RotY;
        int16_t RotZ;
    };

    void SetButtons(Buttons::ButtonQueue buttons, HidReadCallbackParams const& params)
    {
        params.HighLevelOutput.SetButtons(buttons.Remap(params.Family.ButtonMap));
    }

    void SetButtonBits(uint32_t buttonBits, HidReadCallbackParams const& params)
    {
        SetButtons(Buttons::ButtonQueue::FromBits(buttonBits), params);
    }

    HidReading SingleReportTransRotHidReading
    {
        .Params = { 13, 4 },
        .Read = [](HidReadCallbackParams const& params)
        {
            int report = 0;
            for (int i = 0; i < params.ReadingParams.ReportCount; i++)
            {
                const uint8_t reportID = params.Output[report];

                if (reportID == 1)
                {
                    TransRotReport tr = *reinterpret_cast<TransRotReport*>(&params.Output[report + 1]);

                    if (!CheckAxes(params, tr.TransX, tr.TransY, tr.TransZ, tr.RotX, tr.RotY, tr.RotZ))
                        continue;

                    float fx = static_cast<float>(tr.TransX) / params.Family.AxisResolution;
                    float fy = static_cast<float>(tr.TransY) / params.Family.AxisResolution;
                    float fz = static_cast<float>(tr.TransZ) / params.Family.AxisResolution;
                    float rfx = static_cast<float>(tr.RotX) / params.Family.AxisResolution;
                    float rfy = static_cast<float>(tr.RotY) / params.Family.AxisResolution;
                    float rfz = static_cast<float>(tr.RotZ) / params.Family.AxisResolution;

                    params.HighLevelOutput.SetTranslation(fx, fy, fz);
                    params.HighLevelOutput.SetRotation(rfx, rfy, rfz);
                }
                else if (reportID == 3 && params.Family.ButtonReport == ButtonBits_Report3)
                {
                    uint32_t buttonBits = *reinterpret_cast<uint32_t*>(&params.Output[report + 1]);
                    SetButtonBits(buttonBits, params);
                }
                else if (reportID == 28 && params.Family.ButtonReport == ButtonQueue_Report28)
                {
                    SetButtons({.All = *reinterpret_cast<uint64_t*>(&params.Output[report + 1])}, params);
                }
                report += params.ReadingParams.ReportSize;
            }
        }
    };

    HidReading SeparateReportTransRotHidReading
    {
        .Params = { 7, 3 },
        .Read = [](HidReadCallbackParams const& params)
        {
            int report = 0;
            for (int i = 0; i < params.ReadingParams.ReportCount; i++)
            {
                const uint8_t reportID = params.Output[report];

                if (reportID == 1 || reportID == 2)
                {
                    int16_t xx = *reinterpret_cast<int16_t*>(&params.Output[report + 1]);
                    int16_t yy = *reinterpret_cast<int16_t*>(&params.Output[report + 3]);
                    int16_t zz = *reinterpret_cast<int16_t*>(&params.Output[report + 5]);

                    if (!CheckAxes(params, xx, yy, zz)) continue;

                    float fx = static_cast<float>(xx) / params.Family.AxisResolution;
                    float fy = static_cast<float>(yy) / params.Family.AxisResolution;
                    float fz = static_cast<float>(zz) / params.Family.AxisResolution;

                    if (reportID == 1) params.HighLevelOutput.SetTranslation(fx, fy, fz);
                    if (reportID == 2) params.HighLevelOutput.SetRotation(fx, fy, fz);
                }
                else if (reportID == 3)
                {
                    uint32_t buttonBits = *reinterpret_cast<uint32_t*>(&params.Output[report + 1]);
                    SetButtonBits(buttonBits, params);
                }
                report += params.ReadingParams.ReportSize;
            }
        }
    };
}