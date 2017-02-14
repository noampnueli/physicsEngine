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

    vector2d() { x = 0; y = 0;}

    vector2d(double _x, double _y)
    {
        x = _x;
        y = _y;
    }

    virtual vector2d* operator+ (vector2d& vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        return this;
    }

    virtual vector2d* operator- (vector2d& vec)
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

    vector2d* operator* (double scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return this;
    }

    double operator* (vector2d& vec)
    {
        return x * vec.x + y * vec.y;
    }

    void zero()
    {
        x = 0;
        y = 0;
    }

    void print()
    {
        std::cout << "X: " << x << " Y: " << y << std::endl;
    }
};

/*
 * A vector that returns a new vector rather than modifying the vector
 */
class vector2d_c : public vector2d
{
public:
    vector2d_c(double _x, double _y) : vector2d(_x, _y) { }

    virtual vector2d_c* operator+ (vector2d& vec)
    {
        return new vector2d_c(this->x + vec.x, this->y + vec.y);
    }
};


#endif //GRAPHICSTEST_MATH_2D_H
