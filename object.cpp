//
// Created by Noam pnueli on 2/17/17.
//

#include "object.h"


bool narrow_collision_overlap(Object *obj1, Object *obj2) {
    std::vector<vector2d_c*> points1 = obj1->get_points();
    std::vector<vector2d_c*> points2 = obj2->get_points();

    for(int i = 0; i < obj1->get_points().size() - 1; i++)
    {
        vector2d* edge = *points1[i + 1] - *points1[i];
        vector2d* perp = edge->get_perpendicular();

        if(*(*points2[i % points2.size()] - *points1[i]) * *perp < 0)
            return true;

        delete(edge);
    }
    return false;
}


