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
    bool m_running = true;
    InputManager& m_inputManager;
    SDL_Window* m_window = nullptr;
};

} // namespace tlr
