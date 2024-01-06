#pragma once
#include <iostream>
#include "CMyVector.h"

class CMyMatrix
{
private:
    int dim_x;
    int dim_y;
    std::vector<double> data;

public:
    CMyMatrix(int dim_x, int dim_y) : dim_x{dim_x}, dim_y{dim_y}
    {
        for (int i = 0; i < dim_x * dim_y; i++)
        {
            data.push_back(0);
        }
    };
    int get_dim_x() { return dim_x; };
    int get_dim_y() { return dim_y; };
    double get_comp(int x, int y) { return data[dim_x * y + x]; };
    void set_comp(int x, int y, double v) { data[dim_x * y + x] = v; };
    double determinant()
    {
        double d;
        d = get_comp(0, 0) * get_comp(1, 1) - get_comp(0, 1) * get_comp(1, 0);
        return d;
    };
    CMyMatrix invers()
    {
        CMyMatrix result(2, 2);
        double det = determinant();
        if (det == 0)
        {
            std::cout << "Det = 0\nKeine Inverse möglich.";
            std::exit(1);
        }
        result.set_comp(0, 0, get_comp(1, 1) / det);
        result.set_comp(1, 0, get_comp(1, 0) / det * (-1));
        result.set_comp(0, 1, get_comp(0, 1) / det * (-1));
        result.set_comp(1, 1, get_comp(0, 0) / det);
        return result;
    };
};

CMyVector operator*(CMyMatrix A, CMyVector x);
CMyMatrix jacobi(CMyVector x, CMyVector (*funktion)(CMyVector x));
CMyVector newton(CMyVector x, CMyVector (*funktion)(CMyVector x));
void print(CMyVector x, CMyVector (*funktion)(CMyVector x));
void print_final(CMyVector x, CMyVector (*funktion)(CMyVector x));
CMyVector f1(CMyVector x);
CMyVector f2(CMyVector x);