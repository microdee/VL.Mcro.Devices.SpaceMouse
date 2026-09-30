
#pragma once

#include <cstdint>
#include <span>
#include <map>

#include "Cmds.h"

namespace NS_SM::Buttons
{
    extern std::map<uint16_t, Cmd> ThDxModern;
    
    union ButtonQueue
    {
        uint16_t Array [4];
        uint64_t All;

        ButtonQueue& operator |= (ButtonQueue const& other);
        friend ButtonQueue operator | (ButtonQueue const& l, ButtonQueue const& r);

        const uint16_t* begin() const;
        const uint16_t* end() const;
        size_t size() const;

        static ButtonQueue FromBits(uint32_t buttonBits);

        array<uint16_t>^ AsManaged(array<uint16_t>^ output) const;
		ButtonQueue& Remap(std::map<uint16_t, Cmd> const& buttonMap) &;
		ButtonQueue&& Remap(std::map<uint16_t, Cmd> const& buttonMap) &&;
    };

    public ref class ButtonsManaged
    {
	public:
		static Cmd AsCmd(uint16_t button);
    };
}