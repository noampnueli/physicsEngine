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
    vector2d* point1;
    vector2d* point2;
    vector2d* point3;
    vector2d* point4;

    void update_points()
    {
        delete(point1, point2, point3, point4);

        // initializing transform vectors
        vector2d transform1 = vector2d((double) (width * cos(get_angle())), (double) (width * sin(get_angle())));
        vector2d transform2 = vector2d((double) (-height * sin(get_angle())), (double) (height * cos(get_angle())));

        point1 = new vector2d_c(get_position()->x, get_position()->y);
        point2 = *point1 + transform1;
        point3 = *point1 + transform2;
        point4 = *point2 + transform2;
    }

public:
    const int width;
    const int height;

    Box(int mass, vector2d* start_pos, vector2d* start_vel, int width, int height) : width(width), height(height),
                                                                                   Object(mass, start_pos, start_vel)
    {
        collider = new AABB();
    }

    Box(int mass, vector2d* start_pos, vector2d* start_vel, int width, int height, double angle) : width(width), height(height),
                                                                                     Object(mass, start_pos, start_vel, angle)
    {
        collider = new AABB();
    }

    virtual void draw(SDL_Renderer* renderer)
    {
//        SDL_Rect rect = {(int) get_position()->x, (int) get_position()->y, width, height};
//        SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x2b, 0x2c, 0x2d));

        SDL_SetRenderDrawColor(renderer, 43, 44, 45, SDL_ALPHA_OPAQUE);

        SDL_Point points[5] = {
                {(int) point1->x, (int) point1->y},
                {(int) point2->x, (int) point2->y},
                {(int) point4->x, (int) point4->y},
                {(int) point3->x, (int) point3->y},
                {(int) point1->x, (int) point1->y}
        };

        SDL_RenderDrawLines(renderer, points, 5);
    }

    virtual void update_collider()
    {
        update_points();

        AABB* collider_n = (AABB*) collider;
        collider_n->min = vector2d((int) get_position()->x, (int) get_position()->y);
        collider_n->max = vector2d(point4->x, point4->y);
    }
};


#endif //GRAPHICSTEST_BOX_H
