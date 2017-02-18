//
// Created by Noam pnueli on 2/18/17.
//

#include "math_2d.h"

using namespace std;

vector2d* rotate(vector2d *point, vector2d *pivot, double angle)
{
    // T(-pivot) * R(angle) * T(pivot)
    mpoints tmp_m = {{cos(angle), -sin(angle), cos(angle) * pivot->x - sin(angle) * pivot->y - pivot->x},
                     {sin(angle), cos(angle), sin(angle) * pivot->x + cos(angle) * pivot->y - pivot->y },
                     {0         , 0         , 1                                                       }};
    matrix* mat = new matrix(tmp_m);

    // Hacky way to convert 3D vector to 2D vector; Will fix in the future
    mpoints tmp_v = {{point->x},
                     {point->y},
                     {1}};
    matrix* tmp_vec = new matrix(tmp_v);

    tmp_vec = *mat * tmp_vec;

    delete(point);

    // Normalizing returned vector
    double w = tmp_vec->get_points()[0][2];
    point = new vector2d(tmp_vec->get_points()[0][0] / w, tmp_vec->get_points()[0][1] / w);

    delete(mat, tmp_vec);

    return point;
}

vector2d* rotate(vector2d *point, double angle)
{
    mpoints tmp_m = {{cos(angle), -sin(angle)},
                     {sin(angle), cos(angle)}};
    matrix* mat = new matrix(tmp_m);

    point = *mat * point;

    delete(mat);

    return point;
}



