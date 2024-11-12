#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>

#include "Event.h"

namespace tlr
{

class InputManager
{
public:
    template<typename KeyType>
    using EventMap = std::unordered_map<KeyType, Event<>>;

    template<typename KeyType>
    using ModEventMap = std::unordered_map<KeyType, std::unordered_map<Uint16, Event<>>>;

    ModEventMap<SDL_Keycode> KeyPressed;
    ModEventMap<SDL_Keycode> KeyReleased;

    ModEventMap<Uint8> MousePressed;
    ModEventMap<Uint8> MouseReleased;

    void Update()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
            {
                auto key = event.key.keysym.sym;
                KeyPressed[key][KMOD_NONE].Raise();

                SDL_Keymod modState = SDL_GetModState();
                for (auto const& pair : KeyPressed[key])
                {
                    if (modState & pair.first) KeyPressed[key][pair.first].Raise();
                }

            } break;
            }
        }
    }
};

} // namespace tlr
