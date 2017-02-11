//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_BOX_H
#define GRAPHICSTEST_BOX_H


#include "object.h"

class box : object
{
public:
    const int width;
    const int height;

    box(int width, int height) : width(width), height(height) {}

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

    virtual void draw()
    {

    }
};


#endif //GRAPHICSTEST_BOX_H
