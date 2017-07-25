//
// Created by Noam pnueli on 2/11/17.
//

#include "collisions.h"
using namespace std;

double clamp(double lower, double upper, double n)
{
    return max(lower, min(n, upper));
//    if(n < min)
//        return min;
//    else if(n > max)
//	    return max;
//
//    return n;
}

// TODO: support more collision types
Manifold collision_overlap(Collider* coll1 , Collider* coll2)
{
    if(coll1->type == AABB_c && coll2->type == AABB_c)
    {
        AABB* abox = (AABB *) coll1;
        AABB* bbox = (AABB *) coll2;

        vector2d n = bbox->pos - abox->pos;

        double a_extent = (abox->max.x - abox->min.x) / 2;
        double b_extent = (bbox->max.x - bbox->min.x) / 2;

        double x_overlap = a_extent + b_extent - std::abs(n.x);

        if(x_overlap > 0)
        {
            a_extent = (abox->max.y - abox->min.y) / 2;
            b_extent = (bbox->max.y - bbox->min.y) / 2;

            double y_overlap = a_extent + b_extent - std::abs(n.y);

            if(y_overlap > 0)
            {
                if(x_overlap > y_overlap)
                {
                    if(n.x < 0)
                        return Manifold(x_overlap, vector2d(-1, 0), abox, bbox);
                    else
                        return Manifold(x_overlap, vector2d(0, 0), abox, bbox);

                }
            }
            else
            {
                if(n.y < 0)
                    return Manifold(y_overlap, vector2d(0, -1), abox, bbox);
                else
                    return Manifold(y_overlap, vector2d(0, 1), abox, bbox);

            }
        }

//        double dx1 = n_coll2->min.x - n_coll1->max.x;
//        double dy1 = n_coll2->min.y - n_coll1->max.y;
//        double dx2 = n_coll1->min.x - n_coll2->max.x;
//        double dy2 = n_coll1->min.y - n_coll2->max.y;
//
//        if(dx1 > 0 || dy1 > 0)
//            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);
//
//        if(dx2 > 0 || dy2 > 0)
//            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);
//
//        // TODO: Fill with actual values
//        return Manifold(0, vector2d(0, 0), nullptr, nullptr);
    }
    else if(coll1->type == Circle_c && coll2->type == Circle_c)
    {
        CircleCollider* n_coll1 = (CircleCollider *) coll1;
	    CircleCollider* n_coll2 = (CircleCollider *) coll2;

        vector2d delta = n_coll2->pos - n_coll1->pos;
        double radii_sum = n_coll1->radius + n_coll2->radius;
        radii_sum *= radii_sum;

        if(delta.get_squared_length() >= radii_sum)
            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);

        double distance = delta.get_length();

        if(distance != 0)
        {
            double penetration = radii_sum - distance;
            vector2d t = delta.get_unit_vector();

            return Manifold(penetration, t / distance, n_coll1, n_coll2);
        }

        return Manifold(n_coll1->radius, vector2d(1, 0), n_coll1, n_coll2);
    }
    else if((coll1->type == AABB_c && coll2->type == Circle_c) || (coll2->type == AABB_c && coll1->type == Circle_c))
    {

        CircleCollider *n_coll1;
        AABB *n_coll2;

        if(coll1->type == Circle_c)
        {
            n_coll1 = (CircleCollider *)coll1;
            n_coll2 = (AABB *)coll2;
        }
        else
        {
            n_coll1 = (CircleCollider *)coll2;
            n_coll2 = (AABB *)coll1;
        }

        vector2d delta_pos = n_coll1->pos - n_coll2->pos;
        vector2d closest = delta_pos;

        double extent_x = (n_coll2->max.x - n_coll2->min.x) / 2;
        double extent_y = (n_coll2->max.y - n_coll2->min.y) / 2;

        closest.x = clamp(-extent_x, extent_x, closest.x);
        closest.y = clamp(-extent_y, extent_y, closest.y);

        bool inside = false;

        if(delta_pos == closest)
        {
            inside = true;

            if(abs(delta_pos.x) > abs(delta_pos.y))
            {
                if(closest.x > 0)
                    closest.x = extent_x;
                else
                    closest.x = -extent_x;
            }
            else
            {
                if(closest.y > 0)
                    closest.y = extent_y;
                else
                    closest.y = -extent_y;
            }
        }

        vector2d normal = (delta_pos - closest);
        double len = normal.get_squared_length();
        double radius = n_coll1->radius;

        if(len > (radius * radius) && !inside)
        {
            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);
        }
//        normal.print();

        len = std::sqrt(len);

//        vector2d distraction = normal.get_unit_vector() * radius;
//        normal = normal - distraction;

        if(inside)
        {
            printf("ehhhhh");
            return Manifold(radius - len, normal.get_unit_vector() * -1, n_coll1, n_coll2);
        }

        return Manifold(radius - len, normal.get_unit_vector(), n_coll1, n_coll2);
    }
    return Manifold(-1, vector2d(0, 0), nullptr, nullptr);
}



