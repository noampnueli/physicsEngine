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
    vector2d* velocity;

protected:
    std::vector<vector2d*> forces;
    std::vector<vector2d*> tmp_forces;
    double mass;
    Collider* collider;

public:
    Object()
    {
        position = new vector2d(0, 0);
        velocity = new vector2d(0, 0);
        mass = 0;
    }

    ~Object()
    {
        delete(position);
        delete(velocity);
        delete(collider);

        for(vector2d* force : forces)
            delete(force);
    }

    Object(double mass, vector2d* position, vector2d* start_velocity)
    {
        this->mass = mass;
        this->position = position;
        this->velocity = start_velocity;
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

        for(vector2d* temp_force : tmp_forces)
        {
            force_sum = *force_sum + *temp_force;
        }

        vector2d* acceleration = new vector2d(0, 0);

        if(mass > 0)
        {
            delete(acceleration);
            acceleration = *force_sum / mass;
        }


        // TODO: think of a more reasonable way
        if(time < 0.1)
            time *= 20;

        double x = position->x + velocity->x * time + (acceleration->x * time * time) / 2;
        double y = position->y + velocity->y * time + (acceleration->y * time * time) / 2;

        set_x(x);
        set_y(y);

        velocity = *velocity + *(*acceleration * time);

        update_collider();

        delete(force_sum);
        tmp_forces.clear();
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

    vector2d* get_velocity()
    {
        return velocity;
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

    void add_tmp_force(vector2d* force)
    {
        tmp_forces.push_back(force);
    }

    double get_mass()
    {
        return mass;
    }
};


#endif //GRAPHICSTEST_OBJECT_H
