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
    Collider* collider;

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
        delete(collider);

        for(vector2d* force : forces)
            delete(force);
//        delete(forces);
    }

    Object(double mass, vector2d* position, vector2d* start_velocity)
    {
        this->mass = mass;
        this->position = position;
        this->start_velocity = start_velocity;
    }

    vector2d* get_force_sum()
    {
        vector2d* force_sum = new vector2d(0, 0);

        for(vector2d* force : forces)
        {
            force_sum = *force_sum + *force;
        }

        return force_sum;
    }

    // credit to Isaac Newton
    virtual void calculate(double time)
    {
        vector2d* force_sum = new vector2d(0, 0);

        for(vector2d* force : forces)
        {
            force_sum = *force_sum + *force;
        }

        vector2d* acceleration = new vector2d(0, 0);

        if(mass > 0)
        {
            delete(acceleration);
            acceleration = *force_sum / mass;
        }

        double x = get_position()->x + get_velocity().x * time + (acceleration->x * time * time) / 2;
        double y = get_position()->y + get_velocity().y * time + (acceleration->y * time * time) / 2;

        set_x(x);
        set_y(y);

        update_collider();

        delete(force_sum);
    }

    virtual void draw(SDL_Surface* surface) = 0;

    virtual void update_collider() = 0;

    virtual Collider* get_collider()
    {
        return collider;
    }

    vector2d* get_position()
    {
        return position;
    }

    const vector2d& get_velocity()
    {
        return *start_velocity;
    }

    void set_position(vector2d* pos)
    {
        position = pos;
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
