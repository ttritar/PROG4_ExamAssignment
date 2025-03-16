#include "Gamepad.h"

namespace dae
{
    class GamepadImpl
    {
    public:
        explicit GamepadImpl(int controllerIndex) : m_controllerIndex(controllerIndex) {}

        bool UpdateState()
        {
            XINPUT_STATE currentState{};
            ZeroMemory(&currentState, sizeof(XINPUT_STATE));

            if (XInputGetState(m_controllerIndex, &currentState) == ERROR_SUCCESS)
            {
                auto buttonChanges = currentState.Gamepad.wButtons ^ m_previousControllerState.Gamepad.wButtons;
                m_buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
                m_buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

                m_previousControllerState = currentState;
                return true; // Controller is connected
            }
            return false; // Controller not connected
        }

        bool IsDownThisFrame(unsigned int button) const { return m_buttonsPressedThisFrame & button; }
        bool IsUpThisFrame(unsigned int button) const { return m_buttonsReleasedThisFrame & button; }
        bool IsPressed(unsigned int button) const { return m_previousControllerState.Gamepad.wButtons & button; }

        int GetIndex() const
        {
            return m_controllerIndex;
        }

    private:
        int m_controllerIndex;
        XINPUT_STATE m_previousControllerState{};
        unsigned int m_buttonsPressedThisFrame{};
        unsigned int m_buttonsReleasedThisFrame{};
    };

    Gamepad::Gamepad(int controllerIndex) : m_pImpl(std::make_unique<GamepadImpl>(controllerIndex)) {}
    Gamepad::~Gamepad() = default;

    bool Gamepad::UpdateState() { return m_pImpl->UpdateState(); }
    bool Gamepad::IsDownThisFrame(unsigned int button) const { return m_pImpl->IsDownThisFrame(button); }
    bool Gamepad::IsUpThisFrame(unsigned int button) const { return m_pImpl->IsUpThisFrame(button); }
    bool Gamepad::IsPressed(unsigned int button) const { return m_pImpl->IsPressed(button); }

    int Gamepad::GetIndex() const
    {
        return m_pImpl->GetIndex();
    }
}
