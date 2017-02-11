//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_OBJECT_H
#define GRAPHICSTEST_OBJECT_H


#include "collisions.h"
#include <vector>
#include <SDL2/SDL.h>

class Object
{
private:
    vector2d* position;
    vector2d* start_velocity;

protected:
    std::vector<vector2d*> forces;
    double mass;

public:
    Object()
    {
        position = new vector2d(0, 0);
        start_velocity = new vector2d(0, 0);
        mass = 0;
    }

    ~Object()
    {
        delete(position);
        delete(start_velocity);
//        delete(forces);
    }

    Object(double mass, vector2d* position, vector2d* start_velocity)
    {
        this->mass = mass;
        this->position = position;
        this->start_velocity = start_velocity;
    }

    virtual void calculate(double time) = 0;

    virtual void draw(SDL_Surface* surface) = 0;

    const vector2d& get_position()
    {
        return *position;
    }

    const vector2d& get_velocity()
    {
        return *start_velocity;
    }

    void set_position(vector2d& pos)
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

    void add_force(vector2d* force)
    {
        forces.push_back(force);
    }

    double get_mass()
    {
        return mass;
    }
};


#endif //GRAPHICSTEST_OBJECT_H
