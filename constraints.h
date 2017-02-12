//
// Created by bubz on 2/12/17.
//

#ifndef PHYSICSENGINE_CONSTRAINTS_H
#define PHYSICSENGINE_CONSTRAINTS_H

#include "math_2d.h"

class ZeroConstraint
{
public:
    static double calculate_lagrange_multiplier(vector2d* ext_forces, vector2d* position, double mass, vector2d* velocity)
    {
        vector2d* neg_forces = *ext_forces * -1;
        double dot1 = *neg_forces * *position;
        double dot2 = *(*velocity * mass) * *velocity;
        double dot3 = *position * *position;

        return (dot1 - dot2) / dot3;
    }

    static vector2d* get_constraint_force(double lagrange_multiplier, vector2d* position)
    {
        return *position * lagrange_multiplier;
    }
};

#endif //PHYSICSENGINE_CONSTRAINTS_H
