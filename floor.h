//
// Created by shahar on 7/22/17.
//

#ifndef PHYSICSENGINE_FLOOR_H
#define PHYSICSENGINE_FLOOR_H
#include "object.h"

class Floor : public Object
{
public:
    int y_loc = -1;

    Floor()
    {
        this->collider = new AABB();
//        this->y_loc = y;
    }

    virtual void draw(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 43, 44, 45, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, y_loc, 10000, y_loc);
    }

    virtual void update_collider()
    {
        AABB* collider_n = (AABB*) collider;
        collider_n->min = vector2d(0, this->y_loc);
        collider_n->max = vector2d(10000, this->y_loc);
    }

    virtual double get_moment_inertia()
    {}

    virtual vector2d get_arm_vector()
    {}
};
#endif //PHYSICSENGINE_FLOOR_H
