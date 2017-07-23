//
// Created by Noam pnueli on 2/11/17.
//

#include "collisions.h"
#include <algorithm>

// TODO: support more collision types
Manifold collision_overlap(Collider* coll1 , Collider* coll2)
{
    if(coll1->type == AABB_c && coll2->type == AABB_c)
    {
        AABB* n_coll2 = (AABB *) coll2;
        AABB* n_coll1 = (AABB *) coll1;

        double dx1 = n_coll2->min.x - n_coll1->max.x;
        double dy1 = n_coll2->min.y - n_coll1->max.y;
        double dx2 = n_coll1->min.x - n_coll2->max.x;
        double dy2 = n_coll1->min.y - n_coll2->max.y;

        if(dx1 > 0 || dy1 > 0)
            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);

        if(dx2 > 0 || dy2 > 0)
            return Manifold(-1, vector2d(0, 0), nullptr, nullptr);

        // TODO: Fill with actual values
        return Manifold(0, vector2d(0, 0), nullptr, nullptr);
    }
    else if(coll1->type == Circle_c && coll2->type == Circle_c)
    {
        CircleCollider* n_coll1 = (CircleCollider *) coll1;
	    CircleCollider* n_coll2 = (CircleCollider *) coll2;

        vector2d delta = n_coll2->pos - n_coll1->pos;
        float radii_sum = n_coll1->radius + n_coll2->radius;
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
	   n_coll2 = (AABB *)coll1;
	   n_coll1 = (CircleCollider *)coll2;
	}

	vector2d delta_pos = n_coll2->pos - n_coll1->pos;
	vector2d closest = delta_pos;

	double extent_x = (n_coll2->max.x - n_coll2->min.x) / 2;
	double extent_y = (n_coll2->max.y - n_coll2->min.y) / 2;

	closest.x = std::clamp(-extent_x, extent_x, closest.x);
	closest.y = std::clamp(-extent_y, extent_y, closest.y);
	
	bool inside = false;

	if(delta_pos == closest)
	{
	    inside = true;
	}

	vector2d normal = delta_pos - closest;
	double len = normal.get_squared_length();
	double radius = n_coll1->radius;

	if(len > radius * radius && !inside)
	    return Manifold(-1, vector2d(0, 0), nullptr, nullptr);

	len = std::sqrt(len);

	if(inside)
	{
	    return Manifold(radius - len, normal * -1, n_coll1, n_coll2);
	}
	
	return Manifold(radius - len, normal, n_coll1, n_coll2);
    }
    return Manifold(-1, vector2d(0, 0), nullptr, nullptr);
}



