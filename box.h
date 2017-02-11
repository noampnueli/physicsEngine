//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_BOX_H
#define GRAPHICSTEST_BOX_H

#include "object.h"

class Box : public Object
{
private:
    AABB collider;

public:
    const int width;
    const int height;

    Box(int mass, vector2d* start_pos, vector2d* start_vel, int width, int height) : width(width), height(height),
                                                                                   Object(mass, start_pos, start_vel)
    {
        collider.min = vector2d(0, 0);
        collider.max = vector2d(width, height);
    }

    virtual void draw(SDL_Surface* surface)
    {
        SDL_Rect rect = {(int) get_position().x, (int) get_position().y, width, height};
        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x2b, 0x2c, 0x2d));
    }
};


#endif //GRAPHICSTEST_BOX_H
