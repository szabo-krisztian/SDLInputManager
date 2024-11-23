#include "demo_app.h"

#include <iostream>
#include <cassert>

namespace tlr
{

DemoApp::DemoApp(int windowWidth, int windowHeight) : WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight), m_inputManager(InputManager::GetInstance())
{
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && "sdl could not initialize!");

    m_window = SDL_CreateWindow(
        "SDL2 Window",
        WINDOW_WIDTH / 2,
        WINDOW_HEIGHT / 2,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    assert(m_window != nullptr && "window could not be created!");
}

DemoApp::~DemoApp()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void k()
{
    std::cout <<"Hello" << std::endl;
}

void DemoApp::Quit()
{
    m_running = false;
}

void DemoApp::Sayhi()
{
    std::cout <<"Hello from obj" << std::endl;
}

void DemoApp::Run()
{
    m_inputManager.KeyPressed[SDLK_a][KMOD_LALT | KMOD_LCTRL].RegisterCallback(k);
    
    m_inputManager.MousePressed[SDL_BUTTON_LEFT][KMOD_LALT].RegisterCallback(this, Sayhi);
    
    m_inputManager.KeyPressed[SDLK_ESCAPE][KMOD_NONE].RegisterCallback(this, Quit);
    

    while (m_running) {
        m_inputManager.Update();
    }
}

} // namespace tlr
