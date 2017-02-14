//
// Created by Noam pnueli on 2/11/17.
//

#include "renderer.h"

Renderer::Renderer(std::vector<Object*>& stage)
{
    this->stage = stage;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Let the physics begin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << SDL_GetError();
    else
    {
        screen_surface = SDL_GetWindowSurface(window);

        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
//        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

//        SDL_UpdateWindowSurface(window);
    }
}


Renderer::~Renderer()
{

    SDL_DestroyWindow(window);

    SDL_Quit();
}


void Renderer::render() {

//    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for(Object* obj : stage)
    {
        obj->draw(this->renderer);
    }

    SDL_RenderPresent(renderer);
//    SDL_UpdateWindowSurface(window);
}


void Renderer::add_object(Object* obj)
{
    stage.push_back(obj);
}


