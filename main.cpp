#include "box.h"
#include "physics.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<Object*> stage;

    Object* box = new Box(10, new vector2d(20, 0), new vector2d(0, 0), 100, 100);
    Object* box2 = new Box(50, new vector2d(200, 50), new vector2d(0, 0), 120, 100);
    stage.push_back(box);
    stage.push_back(box2);

    Physics physics = Physics(stage);
    physics.run();

    return 0;
}