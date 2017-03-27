//
// Created by Noam pnueli on 2/18/17.
//

#include "math_2d.h"

using namespace std;

void rotate(std::vector<vector2d>& vertices, double angle)
{
    vector2d pivot = vector2d(0, 0);
    rotate(vertices, pivot, angle);
}
void rotate(std::vector<vector2d>& vertices, vector2d& pivot, double angle)
{
    for(int i = 0; i < vertices.size(); i++)
        vertices[i] = rotate(vertices[i], pivot, angle);
}
vector2d rotate(vector2d& point, double angle)
{
    vector2d pivot = vector2d(0, 0);
    return rotate(point, pivot, angle);
}
vector2d rotate(vector2d& point, vector2d& pivot, double angle)
{
    // Change to radians
    angle = angle * (180 / PI);

    // T(-pivot) * R(angle) * T(pivot)
    mpoints tmp_m = {{cos(angle), -sin(angle), cos(angle) * pivot.x - sin(angle) * pivot.y - pivot.x},
                     {sin(angle), cos(angle) , sin(angle) * pivot.x + cos(angle) * pivot.y - pivot.y},
                     {0         , 0          , 1                                                    }};
    matrix mat = matrix(tmp_m);

    vector3d tmp_vec = vector3d(point.x, point.y, 1);

    vector3d product = mat * tmp_vec;

    // Normalizing returned vector

    return vector2d(product.x / product.z, product.y / product.z);
}


