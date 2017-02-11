//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_BOX_H
#define GRAPHICSTEST_BOX_H

#include "object.h"

class Box : public Object
{
public:
    const int width;
    const int height;

    Box(int mass, vector2d* start_pos, vector2d* start_vel, int width, int height) : width(width), height(height),
                                                                                   Object(mass, start_pos, start_vel)
    {
        collider = new AABB();
    }

    virtual void draw(SDL_Surface* surface)
    {
        SDL_Rect rect = {(int) get_position().x, (int) get_position().y, width, height};
        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x2b, 0x2c, 0x2d));
    }

    virtual void update_collider()
    {
        AABB* collider_n = (AABB*) collider;
        collider_n->min = vector2d((int) get_position().x, (int) get_position().y);
        collider_n->max = vector2d((int) get_position().x + width , (int) get_position().y + height);
    }
};


#endif //GRAPHICSTEST_BOX_H
