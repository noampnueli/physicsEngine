//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_MATH_2D_H
#define GRAPHICSTEST_MATH_2D_H

#include <iostream>

class vector2d
{
public:
    double x;
    double y;

    vector2d() { }

    vector2d(double _x, double _y)
    {
        x = _x;
        y = _y;
    }

    vector2d* operator+ (vector2d& vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        return this;
    }

    vector2d* operator- (vector2d& vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;
        return this;
    }

    vector2d* operator/ (double scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return this;
    }

    void print()
    {
        std::cout << "X: " << x << " Y: " << y << std::endl;
    }
};


#endif //GRAPHICSTEST_MATH_2D_H
