#pragma once

#include <SDL2/SDL.h>
#include "../input-manager/InputManager.h"

namespace tlr
{

class DemoApp
{
public:
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    
    DemoApp(int windowWidth, int windowHeight);
    ~DemoApp();

    void Run();
    void Quit();

    void Sayhi();
    
private:
    bool _running = true;
    InputManager& _inputManager;
    SDL_Window* _window = nullptr;
};

} // namespace tlr
