//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_BOX_H
#define GRAPHICSTEST_BOX_H


#include "object.h"

class Box : public object
{
public:
    const int width;
    const int height;

    Box(int mass, vector2f* start_pos, vector2f* start_vel, int width, int height) : width(width), height(height),
                                                                                   object(mass, start_pos, start_vel)
    { }

    virtual void calculate(double time)
    {
        vector2f* force_sum = new vector2f(0, 0);

        for(vector2f* force : forces)
        {
            force_sum = *force_sum + *force;
        }

        vector2f* acceleration = *force_sum / mass;

        double x = get_position().x + get_velocity().x * time + (acceleration->x * time * time) / 2;
        double y = get_position().y + get_velocity().y * time + (acceleration->y * time * time) / 2;

        set_x(x);
        set_y(y);
    }

    virtual void draw(SDL_Surface* surface)
    {
        SDL_Rect rect = {(int) get_position().x, (int) get_position().y, width, height};
        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
    }
};


#endif //GRAPHICSTEST_BOX_H
