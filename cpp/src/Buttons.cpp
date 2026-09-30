#include "Buttons.h"
#include <algorithm>

namespace NS_SM::Buttons
{
    ButtonQueue& ButtonQueue::operator |= (ButtonQueue const& other)
    {
        ButtonQueue selfCopy = *this;
        
        All = 0;
        int i = 0;
        for (uint16_t button : selfCopy)
        {
            if (i > 3) break;
            Array[i] = button;
            ++i;
        }
        for (uint16_t button : other)
        {
            if ([&]
            {
                for (int ii = 0; ii < 4; ++ii)
                {
                    if (Array[ii] == button) return true;
                }
                return false;
            }()) continue;
			
            if (i > 3) break;
            Array[i] = button;
            ++i;
        }
        return *this;
    }

    ButtonQueue operator | (ButtonQueue const& l, ButtonQueue const& r)
    {
        ButtonQueue output(l);
        output |= r;
        return output;
    }

    const uint16_t* ButtonQueue::begin() const
    {
        return &Array[0];
    }

    const uint16_t* ButtonQueue::end() const
    {
        for (int i = 0; i < 4; ++i)
        {
            if (Array[i] == 0) return &Array[i];
        }
        return &Array[3] + 1;
    }
    
    size_t ButtonQueue::size() const
    {
        for (int i = 0; i < 4; ++i)
        {
            if (Array[i] == 0) return i;
        }
        return 4;
    }

    array<uint16_t>^ ButtonQueue::AsManaged(array<uint16_t>^ output) const
    {
        for (int i = 0; i < std::min(4, output->Length); ++i)
        {
            output[i] = Array[i];
        }
        return output;
    }

    ButtonQueue& ButtonQueue::Remap(std::map<uint16_t, Cmd> const& buttonMap) &
    {
        for (int i = 0; i < size(); ++i)
        {
            uint16_t button = Array[i];
            Array[i] = buttonMap.contains(button - 1)
                ? static_cast<uint16_t>(buttonMap.at(button - 1)) + 1
                : static_cast<uint16_t>(Cmd::Noop) + 1
            ;
        }
        return *this;
    }

    ButtonQueue&& ButtonQueue::Remap(std::map<uint16_t, Cmd> const& buttonMap) &&
    {
        return std::move((*this).Remap(buttonMap));
    }

    ButtonQueue ButtonQueue::FromBits(uint32_t buttonBits)
    {
        ButtonQueue result = {.All = 0};
        size_t current = 0;
        for (int i = 0; i < 32; ++i)
        {
            if (buttonBits & 1 << i)
            {
                result.Array[current++] = i + 1;
                if (current > 3) break;
            }
        }
        return result;
    }

    std::map<uint16_t, Cmd> ThDxModern
    {
        {   0, Cmd::MenuOptions    },
        {   1, Cmd::ViewFit        },
        {   2, Cmd::ViewTop        },
        {   3, Cmd::ViewLeft       },
        {   4, Cmd::ViewRight      },
        {   5, Cmd::ViewFront      },
        {   6, Cmd::ViewBottom     },
        {   7, Cmd::ViewBack       },
        {   8, Cmd::ViewRollCW     },
        {   9, Cmd::ViewRollCCW    },
        {  10, Cmd::ViewIso1       },
        {  11, Cmd::ViewIso2       },
        {  12, Cmd::KeyF1          },
        {  13, Cmd::KeyF2          },
        {  14, Cmd::KeyF3          },
        {  15, Cmd::KeyF4          },
        {  16, Cmd::KeyF5          },
        {  17, Cmd::KeyF6          },
        {  18, Cmd::KeyF7          },
        {  19, Cmd::KeyF8          },
        {  20, Cmd::KeyF9          },
        {  21, Cmd::KeyF10         },
        {  22, Cmd::KeyEsc         },
        {  23, Cmd::KeyAlt         },
        {  24, Cmd::KeyShift       },
        {  25, Cmd::KeyCtrl        },
        {  26, Cmd::FilterRotate   },
        {  27, Cmd::FilterPanzoom  },
        {  28, Cmd::FilterDominant },
        {  29, Cmd::ScalePlus      },
        {  30, Cmd::ScaleMinus     },

        // Only available on button queue input (report 28)
        {  35, Cmd::KeyEnter       },
        {  36, Cmd::KeyDelete      },
        {  76, Cmd::KeyF11         },
        {  77, Cmd::KeyF12         },
        { 102, Cmd::View1          },
        { 103, Cmd::View2          },
        { 104, Cmd::View3          },
        { 174, Cmd::KeyTab         },
        { 175, Cmd::KeySpace       },
    };

    Cmd ButtonsManaged::AsCmd(uint16_t button)
    {
        return static_cast<Cmd>(button - 1);
    }
}