//
// Created by Noam pnueli on 2/11/17.
//

#ifndef PHYSICSENGINE_PHYSICS_H
#define PHYSICSENGINE_PHYSICS_H

#include "renderer.h"

#define RUN_TIME 1
#define GRAVITY 9.807

class Physics
{
private:
    std::vector<Object*> stage;
    Renderer* renderer;
public:
    Physics(std::vector<Object*> stage) : stage(stage), renderer(new Renderer(stage))
    {
        for(Object* obj : stage)
        {
            obj->add_force(new vector2d(0, obj->get_mass() * GRAVITY));
        }
    }

    ~Physics()
    {
        for(Object* obj : stage)
            delete(obj);
        delete(renderer);
    }

    void add_object(Object* object)
    {
        stage.push_back(object);
        renderer->add_object(object);
    }

    void run()
    {
        clock_t start_point = clock();
        double dt = 0;

        while(dt < RUN_TIME)
        {
            clock_t now = clock();

            dt = double(now - start_point) / CLOCKS_PER_SEC;

            for(Object* obj : stage)
            {
                obj->calculate(dt);
            }

            calculate_collisions();

            renderer->render();
        }
    }

    //TODO: use a more efficient algorithm - O(n^2) for now :(
    void calculate_collisions()
    {
        for(int i = 0; i < stage.size(); i++)
        {
            for(int k = 0; k < stage.size(); k++)
            {
                if(i != k)
                {
                    if (collision_overlap(stage[i]->get_collider(), stage[k]->get_collider())) {
                        // Collide!
                        std::cout << "We have a collision!" << std::endl;
                        Object* this_obj = stage[i];
                        Object* other = stage[k];
                    }
                }
            }
        }
    }

    double calculate_lagrange_multiplier(vector2d* ext_forces, vector2d* position, double mass, vector2d* velocity)
    {
        vector2d* neg_forces = *ext_forces * -1;
        double dot1 = *neg_forces * *position;
        double dot2 = *(*velocity * mass) * *velocity;
        double dot3 = *position * *position;

        return (dot1 - dot2) / dot3;
    }

    vector2d* get_constraint_force(double lagrange_multiplier, vector2d* position)
    {
        return *position * lagrange_multiplier;
    }
};

#endif //PHYSICSENGINE_PHYSICS_H
