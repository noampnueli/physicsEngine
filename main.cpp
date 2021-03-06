#include "box.h"
#include "circle.h"
#include "physics.h"
#include "floor.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<Object*> stage;

    Box* box1 = new Box(0, vector2d(100, 500), vector2d(0, 0), 200, 200);
//    Box* box2 = new Box(50, vector2d(100, 200), vector2d(0, -10), 100, 100);
    Circle* circle1 = new Circle(10, vector2d(200, 200), vector2d(0, 0), 50);
//    Circle* circle2 = new Circle(70, vector2d(200, 0), vector2d(0, 0), 50);
    //Floor* floor = new Floor();
    //floor->y_loc = 500;
    stage.push_back(box1);
//    stage.push_back(box2);
    stage.push_back(circle1);
//    stage.push_back(circle2);
//    stage.push_back(floor);
    //stage.push_back(circle3);

    Physics physics = Physics(stage);
    physics.run();

    return 0;
}
