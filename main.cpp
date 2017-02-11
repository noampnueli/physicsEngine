#include <ctime>
#include "renderer.h"
#include "box.h"

#define RUN_TIME 3
#define GRAVITY 9.807

using namespace std;

int main(int argc, char** argv)
{
    vector<Object*> stage;

    Object* box = new Box(100, new vector2d(20, 0), new vector2d(0, 0), 100, 100);
    box->add_force(new vector2d(0, 10 * GRAVITY));
    stage.push_back(box);

    Renderer* renderer = new Renderer(stage);

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

        renderer->render();
    }

    return 0;
}