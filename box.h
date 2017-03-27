//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_BOX_H
#define GRAPHICSTEST_BOX_H

#include "object.h"

/*
 * p1               p2
 * ________________
 * |               |
 * |               |
 * |               |
 * |               |
 * |               |
 * _________________
 * p3               p4
 *
 */
class Box : public Object
{
private:
    void update_vertices()
    {
        update_vertex_position();

        double px = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
        double py = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
        vector2d pivot = vector2d(px, py);

        rotate(vertices, pivot, 20);

    }

    void update_vertex_position()
    {
        vertices[0] = vector2d(position.x, position.y);
        vertices[1] = vector2d(vertices[0].x + width, vertices[0].y);
        vertices[2] = vector2d(vertices[0].x, vertices[0].y + height);
        vertices[3] = vector2d(vertices[1].x, vertices[1].y + height);
    }

public:
    const int width;
    const int height;

    Box(int mass, vector2d start_pos, vector2d start_vel, int width, int height) : width(width), height(height),
                                                                                   Object(mass, start_pos, start_vel)
    {
        collider = new AABB();
        vertices = std::vector<vector2d>(4);
        update_vertex_position();
    }

    Box(int mass, vector2d& start_pos, vector2d& start_vel, int width, int height, double angle) : width(width), height(height),
                                                                                     Object(mass, start_pos, start_vel, angle)
    {
        collider = new AABB();
        vertices = std::vector<vector2d>(4);
        update_vertex_position();
    }

    virtual void draw(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 43, 44, 45, SDL_ALPHA_OPAQUE);

        SDL_Point sdl_vertices[5] = {
                {(int) vertices[0].x, (int) vertices[0].y},
                {(int) vertices[1].x, (int) vertices[1].y},
                {(int) vertices[3].x, (int) vertices[3].y},
                {(int) vertices[2].x, (int) vertices[2].y},
                {(int) vertices[0].x, (int) vertices[0].y}
        };

        SDL_RenderDrawLines(renderer, sdl_vertices, 5);
    }

    virtual void update_collider()
    {
        update_vertices();

        AABB* collider_n = (AABB*) collider;
        collider_n->min = vector2d((int) get_position().x, (int) get_position().y);
        collider_n->max = vector2d(get_position().x + width, get_position().y + height);
    }

    virtual double get_moment_inertia()
    {
        return mass * (width * width * height * height) / 12;
    }

    virtual vector2d get_arm_vector()
    {
        return vector2d(width / 2, height / 2);
    }

};


#endif //GRAPHICSTEST_BOX_H
