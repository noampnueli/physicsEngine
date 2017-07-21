//
// Created by Noam pnueli on 2/11/17.
//

#ifndef PHYSICSENGINE_PHYSICS_H
#define PHYSICSENGINE_PHYSICS_H

#include "renderer.h"
#include "constraints.h"

#define RUN_TIME 10
#define GRAVITY 9.807
#define TIME_INTERVAL 0.01

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
            obj->add_force(vector2d(0, obj->get_mass() * GRAVITY));
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
    }

    void run()
    {
        double start_point = 0;
        double last = 0;

        while(start_point < RUN_TIME)
        {
            clock_t now = clock();
	    start_point += now / CLOCKS_PER_SEC;

            for(Object* obj : stage)
            {
                obj->calculate(TIME_INTERVAL);
            }

            calculate_collisions();

            renderer->render();
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
                    collide(stage[i], stage[k]);
                }
            }
        }
    }

    void collide(Object* obj1, Object* obj2)
    {
        Manifold m = collision_overlap(obj1->get_collider(), obj2->get_collider());
        if(m.penetration_depth != -1)
        {
            // std::cout << "We have a potential collision!" << std::endl;

            //if(narrow_collision_overlap(obj1, obj2))
            //{
            std::cout << "We have a collision!" << std::endl;
            //}
        }
    }
};

#endif //PHYSICSENGINE_PHYSICS_H
