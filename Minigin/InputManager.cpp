#include <SDL.h>
#include "InputManager.h"

#include "Renderer.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "Gamepad.h"

namespace dae
{
    class InputManagerImpl
    {
    public:
        std::vector<std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>> m_keyboardCommands;
        std::vector<std::tuple<unsigned int, unsigned int, std::unique_ptr<GameActorCommand>>> m_controllerCommands;

        std::vector<std::unique_ptr<Gamepad>> m_gamepads;  // Vector of Gamepad instances

        //Uint8 m_previousKeyboardState[SDL_NUM_SCANCODES] = { 0 };

        const Uint8* currentKeyboardState = nullptr;
        Uint8 previousKeyboardState[SDL_NUM_SCANCODES] = { 0 };

        bool ProcessInput();
        void ProcessInputKeyboard(const std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>& cmd);
        void ProcessInputController(const std::tuple<unsigned int, unsigned int, std::unique_ptr<GameActorCommand>>& cmd);

        bool IsDownThisFrame(unsigned int button) const;
        bool IsUpThisFrame(unsigned int button) const;
        bool IsPressed(unsigned int button) const;
    };

    bool InputManagerImpl::ProcessInput()
    {
        SDL_PumpEvents();
        currentKeyboardState = SDL_GetKeyboardState(nullptr);

        // KEYBOARD
        //-----------
        for (auto& cmd : m_keyboardCommands)
        {
            ProcessInputKeyboard(cmd);
        }

        // CONTROLLERS
        //------------
        for (auto& cmd : m_controllerCommands)
        {
            ProcessInputController(cmd);
        }

        // Update Gamepad states
        for (auto& gamepad : m_gamepads)
        {
            gamepad->UpdateState();
        }


        memcpy(previousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);

        return true;
    }

    void InputManagerImpl::ProcessInputController(const std::tuple<unsigned int, unsigned int, std::unique_ptr<GameActorCommand>>& cmd)
    {
        int controllerIndex = std::get<0>(cmd);
        unsigned int button = std::get<1>(cmd);
        auto& gamepad = m_gamepads[controllerIndex]; // Get the gamepad instance for this controller index

        // Check if the button is pressed or released
        if (gamepad->IsDownThisFrame(button))
        {
            std::get<2>(cmd)->m_buttonState.PressedThisFrame = true;
            std::get<2>(cmd)->m_buttonState.Down = true;
            std::get<2>(cmd)->m_buttonState.ReleasedThisFrame = false;
            std::get<2>(cmd)->Execute();
        }
        else if (gamepad->IsUpThisFrame(button))
        {
            std::get<2>(cmd)->m_buttonState.ReleasedThisFrame = true;
            std::get<2>(cmd)->m_buttonState.PressedThisFrame = false;
            std::get<2>(cmd)->m_buttonState.Down = false;
            std::get<2>(cmd)->Execute();
        }
        else if (gamepad->IsPressed(button))
        {
            std::get<2>(cmd)->m_buttonState.Down = true;
            std::get<2>(cmd)->m_buttonState.PressedThisFrame = false;
            std::get<2>(cmd)->m_buttonState.ReleasedThisFrame = false;
            std::get<2>(cmd)->Execute();
        }
        else
        {
            std::get<2>(cmd)->m_buttonState.Down = false;
            std::get<2>(cmd)->m_buttonState.PressedThisFrame = false;
            std::get<2>(cmd)->m_buttonState.ReleasedThisFrame = false;
        }
    }


    void InputManagerImpl::ProcessInputKeyboard(const std::pair<SDL_Keycode, std::unique_ptr<GameActorCommand>>& cmd)
    {
        SDL_Scancode key = SDL_GetScancodeFromKey(cmd.first);
        //const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // Get current state
        //
        //bool wasDown = m_previousKeyboardState[key];  // Was key down last frame?
        //bool isDown = keyboardState[key];           // Is key down this frame?

       

        // PRESSED THIS FRAME
        if (/*isDown && !wasDown*/currentKeyboardState[key] && !previousKeyboardState[key])
        {
            cmd.second->m_buttonState.PressedThisFrame = true;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->m_buttonState.Down = true;
            cmd.second->Execute();
        }
        // RELEASED THIS FRAME
        else if (/*!isDown && wasDown*/!currentKeyboardState[key] && previousKeyboardState[key])
        {
            cmd.second->m_buttonState.ReleasedThisFrame = true;
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.Down = false;
            cmd.second->Execute();
        }
        // DOWN
        else if (/*isDown*/currentKeyboardState[key])
        {
            cmd.second->m_buttonState.PressedThisFrame = false;
            cmd.second->m_buttonState.ReleasedThisFrame = false;
            cmd.second->m_buttonState.Down = true;
            cmd.second->Execute();
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
        for (const auto& gamepad : m_gamepads)
        {
            if (gamepad->IsDownThisFrame(button))
            {
                return true;
            }
        }
        return false;
    }

    bool InputManagerImpl::IsUpThisFrame(unsigned int button) const
    {
        for (const auto& gamepad : m_gamepads)
        {
            if (gamepad->IsUpThisFrame(button))
            {
                return true;
            }
        }
        return false;
    }

    bool InputManagerImpl::IsPressed(unsigned int button) const
    {
        for (const auto& gamepad : m_gamepads)
        {
            if (gamepad->IsPressed(button))
            {
                return true;
            }
        }
        return false;
    }




    // INPUT MANAGER
    //--------------

    dae::InputManager::InputManager() : m_pImpl(new InputManagerImpl()) {}
    dae::InputManager::~InputManager() { delete m_pImpl; }


    void dae::InputManager::BindKeyCommand(SDL_Keycode key, std::unique_ptr<GameActorCommand> cmd)
    {
        m_pImpl->m_keyboardCommands.emplace_back(key, std::move(cmd));
    }
    void dae::InputManager::BindBtnCommand(unsigned int controllerIndex, unsigned int btn, std::unique_ptr<GameActorCommand> cmd)
    {
        // Make sure that the Gamepad instance exists for the given controller index
        if (controllerIndex >= m_pImpl->m_gamepads.size())
        {
            m_pImpl->m_gamepads.resize(controllerIndex + 1);  // Resize to accommodate the controller index
        }
        m_pImpl->m_gamepads[controllerIndex] = std::make_unique<Gamepad>(controllerIndex);

        // Now bind the command as before, but use the controller index
        m_pImpl->m_controllerCommands.emplace_back(controllerIndex, btn, std::move(cmd));
    }


    void dae::InputManager::UnbindKeyCommand(SDL_Keycode key, const GameActorCommand* command)
    {
        m_pImpl->m_keyboardCommands.erase(
            std::remove_if( m_pImpl->m_keyboardCommands.begin(), 
                            m_pImpl->m_keyboardCommands.end(),
                            [key, command](const auto& pair) { return pair.first == key && pair.second.get() == command; } ),
            m_pImpl->m_keyboardCommands.end()
        );
    }

    void dae::InputManager::UnbindBtnCommand(unsigned int controllerIndex, unsigned int btn, const GameActorCommand* command)
    {
        auto& controllerCommands = m_pImpl->m_controllerCommands;

        controllerCommands.erase(
            std::remove_if(controllerCommands.begin(), controllerCommands.end(),
                [controllerIndex, btn, command](const auto& pair) {
                    return std::get<0>(pair) == controllerIndex &&
                        std::get<1>(pair) == btn &&
                        std::get<2>(pair).get() == command;
                }),
            controllerCommands.end());
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
















