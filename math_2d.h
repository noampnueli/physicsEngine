//
// Created by Noam pnueli on 10/02/2017.
//

#ifndef GRAPHICSTEST_MATH_2D_H
#define GRAPHICSTEST_MATH_2D_H

#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.141592654

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

    virtual vector2d operator+ (vector2d& vec)
    {
        return vector2d(this->x + vec.x, this->y + vec.y);
    }

    virtual vector2d operator- (vector2d& vec)
    {
        return vector2d(this->x - vec.x, this->y - vec.y);
    }

    vector2d operator/ (double scalar)
    {
        return vector2d(this->x / scalar, this->y / scalar);
    }

    vector2d operator* (double scalar)
    {
        return vector2d(this->x * scalar, this->y * scalar);
    }

    double operator* (vector2d& vec)
    {
        return x * vec.x + y * vec.y;
    }

    vector2d get_perpendicular()
    {
        return vector2d(y, -x);
    }

    vector2d get_unit_vector()
    {
        double magnitude = get_length();
        return vector2d(x / magnitude, y / magnitude);
    }

    double get_squared_length()
    {
	    return x*x + y*y;
    }

    double get_length()
    {
        return (double) std::sqrt(x*x + y*y);
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

class vector3d
{
public:
    double x;
    double y;
    double z;

    vector3d() { x = 0; y = 0; z =0;}

    vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

    virtual vector3d operator+ (vector3d& vec)
    {
        return vector3d(this->x + vec.x, this->y + vec.y, this->z + vec.z);
    }

    virtual vector3d operator- (vector3d& vec)
    {
        return vector3d(this->x - vec.x, this->y - vec.y, this->z - vec.z);
    }

    vector3d operator/ (double scalar)
    {
        return vector3d(this->x / scalar, this->y / scalar, this->z / scalar);
    }

    vector3d operator* (double scalar)
    {
        return vector3d(this->x * scalar, this->y * scalar, this->z * scalar);
    }

    double operator* (vector3d& vec)
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    void zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    void print()
    {
        std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
    }

};

class matrix3d
{
private:
    vector3d col1;
    vector3d col2;
    vector3d col3;

public:
    matrix3d(mpoints points)
    {
        if(points.size() != 3 || points[0].size() != 3)
            throw "Invalid 3D matrix";
    }
};

class matrix
{
private:
    mpoints points;
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
        points = mpoints((unsigned long) rows);
        for(int i = 0; i < colons; i++)
        {
            points[i] = std::vector<double>((unsigned long) colons);
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

    vector2d operator*(vector2d& vec)
    {
        if(this->rows != 2)
            throw "Invalid matrix multiplication";

        return vector2d(vec.x * points[0][0] + vec.y * points[0][1], vec.x * points[1][0] + vec.y * points[1][1]);
    }

    vector3d operator*(vector3d& vec)
    {
        if(this->rows != 3)
            throw "Invalid matrix multiplication";
        vector3d tmp_vec = vector3d(0, 0 ,0);

        tmp_vec.x = points[0][0] * vec.x + points[0][1] * vec.y + points[0][2] * vec.z;
        tmp_vec.y = points[1][0] * vec.x + points[1][1] * vec.y + points[1][2] * vec.z;
        tmp_vec.z = points[2][0] * vec.x + points[2][1] * vec.y + points[2][2] * vec.z;

        return tmp_vec;
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

vector2d rotate(vector2d& point, vector2d& pivot, double angle);

vector2d rotate(vector2d& point, double angle);

void rotate(std::vector<vector2d>& vertices, double angle);

void rotate(std::vector<vector2d>& vertices, vector2d& pivot, double angle);


#endif //GRAPHICSTEST_MATH_2D_H
