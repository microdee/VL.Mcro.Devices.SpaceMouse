#include "SmOutput.h"

namespace NS_SM
{
    void SmOutput::GetManagedButtons(array<uint16_t>^ target) const
    {
        ButtonQueue.AsManaged(target);
    }

    float AbsMax(float a, float b)
    {
        float sign = std::abs(a) > std::abs(b) ? (a < 0 ? -1 : 1) : (b < 0 ? -1 : 1);
        return std::max(std::abs(a), std::abs(b)) * sign;
    }

    void SmOutput::SetTranslation(float x, float y, float z)
    {
        if (TranslationResetting)
        {
            Translation[0] = x;
            Translation[1] = y;
            Translation[2] = z;
            TranslationResetting = false;
        }
        else
        {
            Translation[0] += AbsMax(Translation[0], x);
            Translation[1] += AbsMax(Translation[1], y);
            Translation[2] += AbsMax(Translation[2], z);
        }
    }

    void SmOutput::SetRotation(float x, float y, float z)
    {
        if (RotationResetting)
        {
            Rotation[0] = x;
            Rotation[1] = y;
            Rotation[2] = z;
            RotationResetting = false;
        }
        else
        {
            Rotation[0] += AbsMax(Rotation[0], x);
            Rotation[1] += AbsMax(Rotation[1], y);
            Rotation[2] += AbsMax(Rotation[2], z);
        }
    }

    void SmOutput::SetButtons(Buttons::ButtonQueue const &input)
    {
        if (ButtonsResetting)
        {
            ButtonQueue = input;
            ButtonsResetting = false;
        }
        else
        {
            ButtonQueue |= input;
        }
    }

    void SmOutput::Reset()
    {
        TranslationResetting = RotationResetting = ButtonsResetting = true;
    }

    SmOutputManaged::SmOutputManaged()
    {
        Native = new SmOutput();
    }

    SmOutputManaged::~SmOutputManaged()
    {
        if (Native) delete Native;
        Native = nullptr;
    }

    Vector3 SmOutputManaged::Translation::get()
    {
        _translation.X = Native->Translation[0];
        _translation.Y = Native->Translation[1];
        _translation.Z = Native->Translation[2];
        return _translation;
    }

    Vector3 SmOutputManaged::Rotation::get()
    {
        _rotation.X = Native->Rotation[0];
        _rotation.Y = Native->Rotation[1];
        _rotation.Z = Native->Rotation[2];
        return _rotation;
    }

    array<uint16_t>^ SmOutputManaged::Buttons::get()
    {
        if (!_buttons)
        {
            _buttons = gcnew array<uint16_t>(4);
		}
		Native->GetManagedButtons(_buttons);
		return _buttons;
    }

    int SmOutputManaged::ButtonCount::get()
    {
        return Native->ButtonQueue.size();
    }
}