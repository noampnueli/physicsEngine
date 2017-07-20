#ifndef GRAPHICSTEST_CIRCLE_H
#define GRAPHICSTEST_CIRCLE_H

#include "object.h"

class Circle : public Object
{
public:
	float radius;

	Circle(int mass, vector2d start_pos, vector2d start_vel, float radius) : radius(radius), Object(mass, start_pos, start_vel)
	{
		this->collider = new CircleCollider();
		//this->collider->radius = radius;
	}

	virtual void draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 43, 44, 45, SDL_ALPHA_OPAQUE);

		SDL_Point points[360];

		for(int i = 0; i < 360; i++)
		{
			float rad = (PI / 180) * i;
			points[i] = {this->position.x + radius * cos(rad), this->position.y + radius * sin(rad) };
		}

		SDL_RenderDrawPoints(renderer, points, 360);
	}

	virtual void update_collider()
	{
		CircleCollider *collider_n = (CircleCollider *)collider;
		collider_n->pos = this->position;
	}

	virtual double get_moment_inertia()
	{
		// TODO: Do
	}

	virtual vector2d get_arm_vector()
	{
		// TODO: Do
	}
};

#endif
