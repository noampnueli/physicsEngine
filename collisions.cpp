//
// Created by bubz on 2/11/17.
//

#include "collisions.h"

extern bool collision_overlap(Collider* coll1 , Collider* coll2)
{
    if(coll1->type == AABB_c && coll2->type == AABB_c)
    {
        AABB* n_coll2 = (AABB *) coll2;
        AABB* n_coll1 = (AABB *) coll1;

        double dx1 = n_coll2->min.x - n_coll1->max.x;
        double dy1 = n_coll2->min.y - n_coll1->max.y;
        double dx2 = n_coll1->min.x - n_coll2->max.x;
        double dy2 = n_coll1->min.y - n_coll2->max.y;

        if (dx1 > 0 || dy1 > 0)
            return false;

        return !(dx2 > 0 || dy2 > 0);
    }
    return false;
}

