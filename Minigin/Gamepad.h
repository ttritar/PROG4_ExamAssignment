#pragma once
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#include <Xinput.h>
#include <memory>

namespace dae
{
    class GamepadImpl;

    class Gamepad
    {
    public:
        explicit Gamepad(int controllerIndex);
        ~Gamepad();

        bool UpdateState(); // Update the gamepad state
        bool IsDownThisFrame(unsigned int button) const;
        bool IsUpThisFrame(unsigned int button) const;
        bool IsPressed(unsigned int button) const;

        int GetIndex() const;

    private:
        std::unique_ptr<GamepadImpl> m_pImpl;
    };
}

