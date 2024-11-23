#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>

#include "Event.h"

namespace tlr
{

class InputManager
{
public:
    static InputManager& GetInstance();

    template<typename KeyType>
    using DoubleMap = std::unordered_map<KeyType, std::unordered_map<Uint16, Event<>>>;

    Event<int, int> MouseMotion;

    DoubleMap<SDL_Keycode> KeyPressed;
    DoubleMap<SDL_Keycode> KeyReleased;
    DoubleMap<SDL_Keycode> KeyHold;

    DoubleMap<Uint8> MousePressed;
    DoubleMap<Uint8> MouseReleased;
    DoubleMap<Uint8> MouseHold;
    
    void Update();

private:
    Uint8 const* _keyState;
    int _mouseX, _mouseY;
    Uint32 _mouseState;
    SDL_Keymod _modState;

    InputManager() = default;
    ~InputManager() = default;

    void ProcessEvent(SDL_Event const& event);
    
    template<typename T>
    void NotifyPressAndReleaseCallbacks(T const& button, DoubleMap<T>& map);
    
    void NotifyKeyHoldCallbacks();
    
    void NotifyMouseHoldCallbacks();
    
    void RaiseEvents(std::unordered_map<Uint16, Event<>> const& modEventmap);
};

} // namespace tlr
