//
// Created by Noam pnueli on 2/11/17.
//

#ifndef GRAPHICSTEST_COLLISIONS_H
#define GRAPHICSTEST_COLLISIONS_H

#include "math_2d.h"

enum CollType { AABB_c };

class Collider
{
public:
    CollType type;
};

class AABB : public Collider
{
public:
    vector2d min;
    vector2d max;

    AABB() { this->type = AABB_c; }
};

extern bool collision_overlap(Collider* coll1 , Collider* coll2);

#endif //GRAPHICSTEST_COLLISIONS_H
