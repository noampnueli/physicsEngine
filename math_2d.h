//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_MATH_2D_H
#define GRAPHICSTEST_MATH_2D_H

#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double>> mpoints;

class vector2d
{
public:
    double x;
    double y;

    vector2d() { x = 0; y = 0;}

    vector2d(double x, double y)
    {
        this->x = x;
        this->y = y;
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

    vector2d* get_perpendicular()
    {
        return new vector2d(y, -x);
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

    virtual vector2d_c* operator- (vector2d& vec)
    {
        return new vector2d_c(this->x - vec.x, this->y - vec.y);
    }
};

class matrix
{
private:
    mpoints points;
//    double points[];
    int rows;
    int colons;

public:
    matrix(mpoints points)
    {
        this->points = points;
        this->rows = (int) points.size();
        this->colons = (int) points[0].size();
    }

    matrix(int rows, int colons)
    {
//        points = std::vector<std::vector<double>>((unsigned long) colons, std::vector<double>((unsigned long) rows, 0.0));
        points = mpoints((unsigned long) colons);
        for(int i = 0; i < colons; i++)
        {
            points[i] = std::vector<double>((unsigned long) rows);
            for(int j = 0; j < rows; j++)
                points[i][j] = 0;
        }

        this->rows = rows;
        this->colons = colons;
    }

    matrix* operator* (matrix* mat)
    {
        if(mat->rows > this->rows)
            throw "Invalid matrix multiplication";

        matrix* tmp = new matrix(this->rows, this->colons);

        double sum = 0;

        for(int a = 0; a < rows; a++)
        {
            for(int b = 0; b < colons; b++)
            {
                for(int c = 0; c < colons; c++)
                    sum += this->points[a][c] * mat->points[b][c];
                tmp->points[b][a] = sum;
                sum = 0;
            }
        }
        return tmp;
    }

    vector2d* operator*(vector2d* vec)
    {
        if(this->colons != 2)
            throw "Invalid matrix multiplication";
        vec->x = vec->x * points[0][0] + vec->y * points[0][1];
        vec->y = vec->x * points[1][0] + vec->y * points[1][1];

        return vec;
    }

    const mpoints& get_points()
    {
        return points;
    }

    void print()
    {
        for(int row = 0; row < rows; row++)
        {
            for(int colon = 0; colon < colons; colon++)
            {
                std::cout << "|" << this->points[row][colon];
            }
            std::cout << "|\n";
        }
    }
};

vector2d* rotate(vector2d* point, vector2d* pivot, double angle);

vector2d* rotate(vector2d* point, double angle);


#endif //GRAPHICSTEST_MATH_2D_H
