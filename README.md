# SDLInputManager

## Overview

The InputManager is a lightweight, event-subscribe-based input handling library built using SDL. The core idea is to provide a flexible way to register and unregister callbacks for input events, allowing raw functions and member methods to be used. While the project currently uses SDL for event management, the idea can be easily extended to other environments.

```cpp

void SayHi()
{
    std::cout << "Hi" << std::endl;
}

class A
{
public:
    void DoSomething() { ++x; }
    
private:
    int x = 0;
};

auto& manager = tlr::InputManager::GetInstance();

// Key press: 'a' with left alt + left ctrl
manager.KeyPressed[SDLK_a][KMOD_LALT | KMOD_LCTRL].RegisterCallback(SayHi);

// Unregister
manager.KeyPressed[SDLK_a][KMOD_LALT | KMOD_LCTRL].UnegisterCallback(SayHi);

// Mouse button press: 'left' with left alt
A a;
manager.MousePressed[SDL_BUTTON_LEFT][KMOD_LALT].RegisterCallback(&a, &A::DoSomething);

// Unregister
manager.MousePressed[SDL_BUTTON_LEFT][KMOD_LALT].UnregisterCallback(&a, &A::DoSomething);

/*
    Updating InputManager inside the render loop:
    while (running) { manager.Update(); }
*/

```
