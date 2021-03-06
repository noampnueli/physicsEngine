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
protected:
    std::vector<vector2d> forces;
    std::vector<vector2d> tmp_forces;
    double mass;
    double inverse_mass;
    Collider* collider;
    std::vector<vector2d> vertices;

    double torque;
    double torque_sensitivity = 10000;
    double angular_velocity;
    double angle;

    vector2d position;
    vector2d velocity;

    double restitution = 1;

public:
    Object()
    {
        position = vector2d(0, 0);
        velocity = vector2d(0, 0);
        mass = 0;
        angle = 0;
        angular_velocity = 0;
    }

    ~Object()
    {
        delete(position, velocity, collider);
    }

    Object(double mass, vector2d position, vector2d start_velocity)
    {
        this->mass = mass;
	if(mass != 0)
		this->inverse_mass = 1 / mass;
	else
		this->inverse_mass = 0;
        this->position = position;
        this->velocity = start_velocity;
        angle = 0;
        angular_velocity = 0;
    }

    Object(double mass, vector2d position, vector2d start_velocity, double angle)
    {
        this->mass = mass;
	if(mass != 0)
		this->inverse_mass = 1 / mass;
	else
		this->inverse_mass = 0;
        this->position = position;
        this->velocity = start_velocity;
        this->angle = angle;
        angular_velocity = 0;
    }

    vector2d get_force_sum()
    {
        vector2d force_sum = vector2d(0, 0);

        for(vector2d force : forces)
        {
            force_sum = force_sum + force;
        }

        return force_sum;
    }

    // credit to Isaac Newton
    virtual void calculate(double time)
    {
	if(mass <= 0)
	{
	    update_collider();
	    return;
	}
        vector2d force_sum = vector2d(0, 0);

        for(vector2d force : forces)
        {
            force_sum = force_sum + force;
        }

        for(vector2d tmp_force : tmp_forces)
        {
            force_sum = force_sum + tmp_force;
        }

        vector2d acceleration = vector2d(0, 0);

        acceleration = force_sum / mass;

        // Apply natural rotation
        vector2d r = get_arm_vector();
        torque = r * force_sum;

        double angular_acceleration = torque / get_moment_inertia();

        angular_velocity += angular_acceleration * time;

        angle += angular_velocity * time * torque_sensitivity;

        double x = position.x + velocity.x * time + (acceleration.x * time * time) / 2;
        double y = position.y + velocity.y * time + (acceleration.y * time * time) / 2;

        //set_x(x);
        //set_y(y);

        vector2d tmp = acceleration * time;

        velocity = velocity + tmp;

	set_x(x);
	set_y(y);

        update_collider();

        tmp_forces.clear();
    }

    virtual void draw(SDL_Renderer* surface) = 0;

    virtual void update_collider() = 0;

    virtual double get_moment_inertia() = 0;

    virtual vector2d get_arm_vector() = 0;

    virtual Collider* get_collider()
    {
        return collider;
    }

    vector2d& get_position()
    {
        return position;
    }

    vector2d& get_velocity()
    {
        return velocity;
    }

    double get_restitution()
    {
	return restitution;
    }

    void set_position(vector2d& pos)
    {
        position = pos;
    }

    void set_velocity(vector2d& vel)
    {
    	velocity = vel;
    }

    void set_x(double x)
    {
        position.x = x;
    }

    void set_y(double y)
    {
        position.y = y;
    }

    void add_force(vector2d force)
    {
        forces.push_back(force);
    }

    void add_tmp_force(vector2d force)
    {
        tmp_forces.push_back(force);
    }

    double get_mass()
    {
        return mass;
    }

    double get_inverse_mass()
    {
    	return inverse_mass;
    }

    double get_angle()
    {
        return angle;
    }

    std::vector<vector2d> get_vertices()
    {
        return vertices;
    }
};

bool narrow_collision_overlap(Object* obj1, Object* obj2);


#endif //GRAPHICSTEST_OBJECT_H
