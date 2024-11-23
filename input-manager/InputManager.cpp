#include "InputManager.h"

namespace tlr
{

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::Update()
{
    _keyState = SDL_GetKeyboardState(NULL);
    _mouseState = SDL_GetMouseState(&_mouseX, &_mouseY);
    _modState = SDL_GetModState();
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ProcessEvent(event);
    }

    MouseMotion.Raise(_mouseX, _mouseY);
    NotifyKeyHoldCallbacks();
    NotifyMouseHoldCallbacks();
}

void InputManager::ProcessEvent(SDL_Event const& event)
{
    switch (event.type)
    {
    
    case SDL_KEYDOWN:
    {
        NotifyPressAndReleaseCallbacks(event.key.keysym.sym, KeyPressed);
    } break;
    
    case SDL_KEYUP:
    {
        NotifyPressAndReleaseCallbacks(event.key.keysym.sym, KeyReleased);
    } break;

    case SDL_MOUSEBUTTONDOWN:
    {
        NotifyPressAndReleaseCallbacks(event.button.button, MousePressed);
    } break;

    case SDL_MOUSEBUTTONUP:
    {
        NotifyPressAndReleaseCallbacks(event.button.button, MouseReleased);
    } break;

    }
}

template<typename T>
void InputManager::NotifyPressAndReleaseCallbacks(T const& button, DoubleMap<T>& map)
{
    auto buttonIt = map.find(button);
    if (buttonIt == map.end())
    {
        return;
    }
    
    RaiseEvents(buttonIt->second);
}

void InputManager::NotifyKeyHoldCallbacks()
{
    for (auto const& [key, modEventMap] : KeyHold)
    {
        if (_keyState[SDL_GetScancodeFromKey(key)])
        {
            RaiseEvents(modEventMap);
        }
    }
}

void InputManager::NotifyMouseHoldCallbacks()
{
    for (auto const& [button, modEventMap] : MouseHold)
    {
        if (_mouseState & SDL_BUTTON(button))
        {
            RaiseEvents(modEventMap);
        }
    }
}

void InputManager::RaiseEvents(std::unordered_map<Uint16, Event<>> const& modEventmap)
{
    for (auto const& [mod, event] : modEventmap)
    {   
        if ((_modState & (mod)) == mod)
        {
            event.Raise();
        }
    }
}

} // namespace tlr
