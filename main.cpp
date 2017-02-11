#include <iostream>
#include <ctime>
#include "renderer.h"
#include "box.h"

#define RUN_TIME 5

using namespace std;

int main(int argc, char** argv)
{
    vector<object*> stage;

    object* box = new Box(1, new vector2f(5, 0), new vector2f(0, 0), 100, 100);
    box->add_force(new vector2f(0, 2));
    stage.push_back(box);

    Renderer* renderer = new Renderer(stage);

    std::time_t start_point = std::time(nullptr);
    double dt = 0;

    while(dt < RUN_TIME)
    {
        std::time_t now = std::time(nullptr);
        dt = now - start_point;

        for(object* obj : stage)
        {
            obj->calculate(dt);
        }

        renderer->render();
    }

    return 0;
}