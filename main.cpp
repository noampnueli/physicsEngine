#include "box.h"
#include "physics.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<Object*> stage;

    Box* box1 = new Box(10, vector2d(400, 0), vector2d(0, 0), 100, 100);
    Box* box2 = new Box(50, vector2d(350, 200), vector2d(0, -10), 100, 100);
    stage.push_back(box1);
    stage.push_back(box2);

    Physics physics = Physics(stage);
    physics.run();

    return 0;
}