//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_OBJECT_H
#define GRAPHICSTEST_OBJECT_H


#include "math_2d.h"
#include <vector>
#include <SDL2/SDL.h>

class object
{
private:
    vector2f* position;
    vector2f* curr_velocity;

protected:
    std::vector<vector2f*> forces;
    double mass;

public:
    object()
    {
        position = new vector2f(0, 0);
        curr_velocity = new vector2f(0, 0);
        mass = 0;
    }

    ~object()
    {
        delete(position);
        delete(curr_velocity);
//        delete(forces);
    }

    object(double mass, vector2f* position, vector2f* start_velocity)
    {
        this->mass = mass;
        this->position = position;
        this->curr_velocity = start_velocity;
    }

    virtual void calculate(double time) = 0;

    virtual void draw(SDL_Surface* surface) = 0;

    const vector2f& get_position()
    {
        return *position;
    }

    const vector2f& get_velocity()
    {
        return *curr_velocity;
    }

    void set_position(vector2f& pos)
    {
        *position = pos;
    }

    void set_x(double x)
    {
        position->x = x;
    }

    void set_y(double y)
    {
        position->y = y;
    }

    void add_force(vector2f* force)
    {
        forces.push_back(force);
    }
};


#endif //GRAPHICSTEST_OBJECT_H
