#include "demo_app.h"

#include <iostream>
#include <cassert>

namespace tlr
{

DemoApp::DemoApp(int windowWidth, int windowHeight) : WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight), _inputManager(InputManager::GetInstance())
{
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && "sdl could not initialize!");

    _window = SDL_CreateWindow(
        "SDL2 Window",
        WINDOW_WIDTH / 2,
        WINDOW_HEIGHT / 2,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    assert(_window != nullptr && "window could not be created!");
}

DemoApp::~DemoApp()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void DemoApp::Quit()
{
    _running = false;
}

void DemoApp::SayHi()
{
    std::cout <<"Hi" << std::endl;
}

void Mouse(int x, int y)
{
    std::cout << "x: " << x << ", " << "y: " << y << std::endl;
}

void DemoApp::Run()
{
    /*
    _inputManager.KeyPressed[SDLK_a][KMOD_NONE].RegisterCallback(this, SayHi);
    _inputManager.KeyReleased[SDLK_b][KMOD_NONE].RegisterCallback(this, SayHi);
    
    _inputManager.MousePressed[SDL_BUTTON_LEFT][KMOD_LALT].RegisterCallback(this, SayHi);
    _inputManager.MouseReleased[SDL_BUTTON_LEFT][KMOD_LALT].RegisterCallback(this, SayHi);

    _inputManager.KeyHold[SDLK_u][KMOD_LALT].RegisterCallback(this, SayHi);
    _inputManager.MouseHold[SDL_BUTTON_LEFT][KMOD_LALT].RegisterCallback(this, SayHi);

    _inputManager.MouseMotion.RegisterCallback(Mouse);
    */

    _inputManager.KeyPressed[SDLK_ESCAPE][KMOD_NONE].RegisterCallback(this, Quit);
    
    while (_running)
    {
        _inputManager.Update();
    }
}

} // namespace tlr
