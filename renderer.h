//
// Created by bubz on 2/11/17.
//

#ifndef GRAPHICSTEST_RENDERER_H
#define GRAPHICSTEST_RENDERER_H


#include "object.h"
#include <vector>
#include <SDL2/SDL.h>

class Renderer {
private:
    std::vector<object*> stage;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

public:
    Renderer(std::vector<object*>& stage);

    ~Renderer();

    void render();

    void add_object(object* obj);
};


#endif //GRAPHICSTEST_RENDERER_H
