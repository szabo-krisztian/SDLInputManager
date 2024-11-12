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
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ProcessEvent(event);
    }
}

void InputManager::ProcessEvent(SDL_Event const& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
    {
        auto const& key = event.key.keysym.sym;
        auto keycodeIt = KeyPressed.find(key);
        
        if (keycodeIt == KeyPressed.end()) break;
        
        SDL_Keymod modState = SDL_GetModState();
        for (auto const& pair : KeyPressed[key])
        {
            if ((modState & (pair.first)) == pair.first) KeyPressed[key][pair.first].Raise();
        }

    } break;

    }
}

} // namespace tlr