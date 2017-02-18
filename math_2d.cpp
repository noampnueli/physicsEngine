//
// Created by Noam pnueli on 2/18/17.
//

#include "math_2d.h"

using namespace std;

vector2d *rotate(vector2d *point, vector2d *pivot, double angle) {
    vector<vector<double>> tmp_m = {{cos(angle), -sin(angle), cos(angle) * pivot->x - sin(angle) * pivot->y - pivot->x},
                                    {sin(angle), cos(angle), sin(angle) * pivot->x + cos(angle) * pivot->y - pivot->y },
                                    {0         , 0         , 1                                                       }};
    matrix* mat = new matrix(tmp_m);

    point = *mat * point;

    delete(mat);

    return point;
}

vector2d *rotate(vector2d *point, double angle) {
    vector<vector<double>> tmp_m = {{cos(angle), -sin(angle)},
                                    {sin(angle), cos(angle)}};
    matrix* mat = new matrix(tmp_m);

    point = *mat * point;

    delete(mat);

    return point;
}



