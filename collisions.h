//
// Created by Noam pnueli on 2/11/17.
//

#ifndef GRAPHICSTEST_COLLISIONS_H
#define GRAPHICSTEST_COLLISIONS_H

#include "math_2d.h"

enum CollType { AABB_c, Circle_c };

class Collider
{
public:
    CollType type;
};

typedef struct Manifold
{
	Collider *A;
	Collider *B;

	double penetration_depth;
	vector2d normal;

public:
	Manifold(double penetration_depth, vector2d normal, Collider *A, Collider *B)
			: penetration_depth(penetration_depth), normal(normal), A(A), B(B) {}
} Manifold;

class AABB : public Collider
{
public:
    vector2d min;
    vector2d max;
    vector2d pos;

    AABB() { this->type = AABB_c; }
};

class CircleCollider : public Collider
{
public:
	vector2d pos;
	float radius;

	CircleCollider() { this->type = Circle_c; }
};

Manifold collision_overlap(Collider* coll1, Collider* coll2);

#endif //GRAPHICSTEST_COLLISIONS_H
