#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "input-manager/InputManager.h"

bool running = true;

void Close()
{
    running = false;
}

void hello()
{
    std::cout << "ASDF";
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Hello SDL", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    tlr::InputManager &manager = tlr::InputManager::GetInstance();
    
    manager.KeyPressed[SDLK_a][KMOD_NONE].RegisterCallback(hello);
    manager.KeyPressed[SDLK_ESCAPE][KMOD_NONE].RegisterCallback(Close);
    manager.KeyPressed[SDLK_b][KMOD_LALT | KMOD_LCTRL].RegisterCallback(hello);

    while (running)
    {
        manager.Update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}