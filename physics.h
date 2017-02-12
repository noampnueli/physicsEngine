//
// Created by Noam pnueli on 2/11/17.
//

#ifndef PHYSICSENGINE_PHYSICS_H
#define PHYSICSENGINE_PHYSICS_H

#include "renderer.h"
#include "constraints.h"

#define RUN_TIME 3
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
        double start_point = 0;
        double last = 0;

        while(start_point < RUN_TIME)
        {
            clock_t now = clock();

            start_point += now / CLOCKS_PER_SEC;

            double dt = (now - last) / CLOCKS_PER_SEC;

            for(Object* obj : stage)
            {
                obj->calculate(dt);
            }

            calculate_collisions();

            renderer->render();

            last = now;
        }
    }

    // TODO: use a more efficient algorithm - O(n^2) for now :(
    void calculate_collisions()
    {
        for(int i = 0; i < stage.size(); i++)
        {
            for(int k = 0; k < stage.size(); k++)
            {
                if(i != k)
                {
                    if(collision_overlap(stage[i]->get_collider(), stage[k]->get_collider()))
                    {
                        // Collide!
                        std::cout << "We have a collision!" << std::endl;
                        Object* this_obj = stage[i];
                        Object* other = stage[k];
                    }
                }
            }
        }
    }
};

#endif //PHYSICSENGINE_PHYSICS_H
