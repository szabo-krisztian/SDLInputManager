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
    m_modState = SDL_GetModState();

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
        NotifyCallbacks(event.key.keysym.sym, KeyPressed);
    } break;
    
    case SDL_KEYUP:
    {
        NotifyCallbacks(event.key.keysym.sym, KeyReleased);
    } break;

    case SDL_MOUSEBUTTONDOWN:
    {
        NotifyCallbacks(event.button.button, MousePressed);
    } break;

    case SDL_MOUSEBUTTONUP:
    {
        NotifyCallbacks(event.button.button, MouseReleased);
    } break;

    }
}

template<typename T>
void InputManager::NotifyCallbacks(T const& button, ModEventMap<T>& map)
{
    auto buttonIt = map.find(button);
    if (buttonIt == map.end())
    {
        return;
    }
    
    for (auto const& modEventPair : buttonIt->second)
    {
        if ((m_modState & (modEventPair.first)) == modEventPair.first)
        {
            modEventPair.second.Raise();
        }
    }
}


} // namespace tlr
