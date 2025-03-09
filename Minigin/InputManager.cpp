#include <SDL.h>
#include "InputManager.h"

#include "Renderer.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>

namespace dae
{

    class InputManagerImpl
    {
    public:
        std::vector<std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>> m_keyboardCommands;
        std::vector<std::pair<unsigned int, std::unique_ptr<GameActorCommand>>> m_controllerCommands;

        XINPUT_STATE m_previousControllerState{};
        Uint8 m_previousKeyboardState[SDL_NUM_SCANCODES] = { 0 };


        int m_controllerIndex = 0;

        unsigned int m_buttonsPressedThisFrame{};
        unsigned int m_buttonsReleasedThisFrame{};

        bool ProcessInput();
        void ProcessInputKeyboard(const std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>& cmd);
        void ProcessInputController(const std::pair<unsigned int, std::unique_ptr<GameActorCommand>>& cmd);

        bool IsDownThisFrame(unsigned int button) const;
        bool IsUpThisFrame(unsigned int button) const;
        bool IsPressed(unsigned int button) const;
    };


    bool InputManagerImpl::ProcessInput()
    {
        // CONTROLLER
        //------------
        XINPUT_STATE currentState{};
        ZeroMemory(&currentState, sizeof(XINPUT_STATE));
        XInputGetState(m_controllerIndex, &currentState);

        if (IsDownThisFrame(XINPUT_GAMEPAD_A))std::cout<<"presseed"; 

        auto buttonChanges = currentState.Gamepad.wButtons ^ m_previousControllerState.Gamepad.wButtons;
        m_buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
        m_buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

        for (auto& cmd : m_controllerCommands)
        {
            ProcessInputController(cmd);
        }
        CopyMemory(&m_previousControllerState, &currentState, sizeof(XINPUT_STATE));

        // KEYBOARD
        //-----------

        for (auto& cmd : m_keyboardCommands)
        {
            ProcessInputKeyboard(cmd);
        }
        return true;
    }

    void InputManagerImpl::ProcessInputController(const std::pair<unsigned int, std::unique_ptr<GameActorCommand>>& cmd)
    {
        if (IsDownThisFrame(cmd.first))
        {
           cmd.second->m_buttonState.PressedThisFrame = true;
           cmd.second->m_buttonState.Down = true;
           cmd.second->m_buttonState.ReleasedThisFrame = false;
           cmd.second->Execute();
        }
        else if (IsUpThisFrame(cmd.first))
        {
           cmd.second->m_buttonState.ReleasedThisFrame = true;
           cmd.second->m_buttonState.PressedThisFrame = false;
           cmd.second->m_buttonState.Down = false;
           cmd.second->Execute();
        }
        else if (IsPressed(cmd.first))
        {
            cmd.second->m_buttonState.Down = true;
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->Execute();
        }
        else
        {
           cmd.second->m_buttonState.Down = false;
           cmd.second->m_buttonState.PressedThisFrame = false;
           cmd.second->m_buttonState.ReleasedThisFrame = false;
        }
    }

    void InputManagerImpl::ProcessInputKeyboard(const std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>& cmd)
    {
        SDL_Scancode key = SDL_GetScancodeFromKey(cmd.first);
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // Get current state

        bool wasDown = m_previousKeyboardState[key];  // Was key down last frame?
        bool isDown = keyboardState[key];           // Is key down this frame?

        // PRESSED THIS FRAME
        if (isDown && !wasDown)
        {
            cmd.second->m_buttonState.PressedThisFrame = true;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->m_buttonState.Down = true;
            cmd.second->Execute();
        }
        // RELEASED THIS FRAME
        else if (!isDown && wasDown)
        {
            cmd.second->m_buttonState.ReleasedThisFrame = true;
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.Down = false;
            cmd.second->Execute();
        }
        // DOWN
        else if (isDown)
        {
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->m_buttonState.Down = true;
        }
        // RELEASED
        else  
        {
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->m_buttonState.Down = false;
        }
    }



    bool InputManagerImpl::IsDownThisFrame(unsigned int button) const
    {
        return m_buttonsPressedThisFrame & button;
    }

    bool InputManagerImpl::IsUpThisFrame(unsigned int button) const
    {
        return m_buttonsReleasedThisFrame & button;
    }

    bool InputManagerImpl::IsPressed(unsigned int button) const
    {
        return m_previousControllerState.Gamepad.wButtons & button;
    }



    // INPUT MANAGER
    //--------------

    dae::InputManager::InputManager() : m_pImpl(new InputManagerImpl()) {}
    dae::InputManager::~InputManager() { delete m_pImpl; }

    void dae::InputManager::BindKeyCommand(SDL_Keycode key, std::unique_ptr<GameActorCommand> cmd)
    {
        m_pImpl->m_keyboardCommands.emplace_back(key, std::move(cmd));
    }

    void dae::InputManager::BindBtnCommand(unsigned int btn, std::unique_ptr<GameActorCommand> cmd)
    {
        m_pImpl->m_controllerCommands.emplace_back(btn, std::move(cmd));
    }

    bool InputManager::ProcessInput()
    {

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) return false;

            if (e.type == SDL_KEYDOWN)
            {
            }
        }


        return m_pImpl->ProcessInput();
    }
}
















