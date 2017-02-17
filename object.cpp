//
// Created by Noam pnueli on 2/17/17.
//

#include "object.h"


bool narrow_collision_overlap(Object *obj1, Object *obj2) {
    std::vector<vector2d_c*> vertices1 = obj1->get_vertices();
    std::vector<vector2d_c*> vertices2 = obj2->get_vertices();

    for(int i = 0; i < obj1->get_vertices().size() - 1; i++)
    {
        vector2d* edge = *vertices1[i + 1] - *vertices1[i];
        vector2d* perp = edge->get_perpendicular();

        if(*(*vertices2[i % vertices2.size()] - *vertices1[i]) * *perp < 0)
            return true;

        delete(edge);
    }
    return false;
}


