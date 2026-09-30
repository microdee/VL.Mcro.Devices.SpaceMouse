
#pragma once

#include "Buttons.h"

namespace NS_SM
{
    using namespace System;
    using namespace System::Collections;
    using namespace Stride::Core::Mathematics;

    class SmOutput
    {
    public:
        float Translation[3] {0, 0, 0};
        float Rotation[3] {0, 0, 0};
        Buttons::ButtonQueue ButtonQueue;

        void GetManagedButtons(array<uint16_t>^ target) const;

        void SetTranslation(float x, float y, float z);
        void SetRotation(float x, float y, float z);
        void SetButtons(Buttons::ButtonQueue const& input);
        void Reset();

        bool TranslationResetting = false;
        bool RotationResetting = false;
        bool ButtonsResetting = false;
    };

    public ref class SmOutputManaged
    {
    public:
        SmOutputManaged();
        ~SmOutputManaged();

        property Vector3 Translation
        {
            Vector3 get();
        }

        property Vector3 Rotation
        {
            Vector3 get();
        }

		property array<uint16_t>^ Buttons
        {
            array<uint16_t>^ get();
        }

		property int ButtonCount
        {
            int get();
        }

        SmOutput* Native = nullptr;

    private:
        Vector3 _translation;
        Vector3 _rotation;
        array<uint16_t>^ _buttons = nullptr;

    };
}