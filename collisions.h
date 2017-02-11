//
// Created by bubz on 2/11/17.
//

#ifndef GRAPHICSTEST_COLLISIONS_H
#define GRAPHICSTEST_COLLISIONS_H

#include "math_2d.h"

struct AABB
{
    vector2d min;
    vector2d max;
};

bool AABB_overlap(AABB* coll1, AABB* coll2)
{
    double dx1 = coll2->min.x - coll1->max.x;
    double dy1 = coll2->min.y - coll1->max.y;
    double dx2 = coll1->min.x - coll2->max.x;
    double dy2 = coll1->min.y - coll2->max.y;

    if(dx1 > 0 || dy1 > 0)
        return false;

    return !(dx2 > 0 || dy2 > 0);

}

#endif //GRAPHICSTEST_COLLISIONS_H
