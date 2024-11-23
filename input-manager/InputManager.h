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
    using ModEventMap = std::unordered_map<KeyType, std::unordered_map<Uint16, Event<>>>;

    ModEventMap<SDL_Keycode> KeyPressed;
    ModEventMap<SDL_Keycode> KeyReleased;

    ModEventMap<Uint8> MousePressed;
    ModEventMap<Uint8> MouseReleased;

    void Update();

private:
    SDL_Keymod m_modState;

    InputManager() = default;
    ~InputManager() = default;

    void ProcessEvent(SDL_Event const& event);

    template<typename T>
    void NotifyCallbacks(T const& button, ModEventMap<T>& map);
};

} // namespace tlr
