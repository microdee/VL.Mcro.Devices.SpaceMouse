#include "Cmds.h"

namespace NS_SM::Buttons
{
    uint16_t FromCmd(Cmd input)
    {
        return static_cast<uint16_t>(input);
    }
    Cmd AsCmd(uint16_t input)
    {
        return static_cast<Cmd>(input);
    }

    uint16_t CmdUtils::FromCmd(Cmd input)
    {
        return static_cast<uint16_t>(input);
    }
    Cmd CmdUtils::AsCmd(uint16_t input)
    {
        return static_cast<Cmd>(input);
    }
}