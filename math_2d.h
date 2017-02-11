//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_MATH_2D_H
#define GRAPHICSTEST_MATH_2D_H


class vector2f
{
public:
    double x;
    double y;

    vector2f() { }

    vector2f(double _x, double _y)
    {
        x = _x;
        y = _y;
    }

    vector2f* operator+ (vector2f& vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        return this;
    }

    vector2f* operator- (vector2f& vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;
        return this;
    }

    vector2f* operator/ (double scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return this;
    }
};


#endif //GRAPHICSTEST_MATH_2D_H
