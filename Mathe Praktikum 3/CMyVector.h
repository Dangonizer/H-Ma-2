#pragma once
#include <vector>
#include <cmath>
class CMyVector
{
private:
    std::vector<double> x;
    int d;

public:
    CMyVector(int dim) : d{dim}
    {
        x.reserve(d);
        for (int i = 0; i < d; i++)
        {
            x.push_back(0);
        }
    };
    int get_dimension() { return d; };
    double get_component(int pos) { return x[pos]; };
    void set_component(double v, int pos) { x[pos] = v; };

    double length()
    {
        double l = 0;
        for (int i = 0; i < d; i++)
        {
            l += pow(x[i], 2);
        }
        return sqrt(l);
    };

    CMyVector operator+(CMyVector b)
    {
        CMyVector result(this->d);
        for (int i = 0; i < this->d; i++)
        {
            result.x[i] = this->x[i] + b.x[i];
        }
        return result;
    };
    /*    CMyVector operator*(double lambda)
        {
            CMyVector result(this->d);
            for (int i = 0; i < this->d; i++)
            {
                result.x[i] = this->x[i] * lambda;
            }
            return result;
        };*/
};

CMyVector operator*(CMyVector a, double lambda);
CMyVector operator*(double lambda, CMyVector a);

CMyVector gradient(CMyVector x, double (*function)(CMyVector x));
CMyVector maximize(CMyVector x, double (*function)(CMyVector x), double lambda = 1.0);
void print_default(CMyVector x, double (*function)(CMyVector x), double lambda);
void print_new(CMyVector x, double (*function)(CMyVector x));
void print_test(CMyVector x, double (*function)(CMyVector x));
double function_f(CMyVector x);
double function_g(CMyVector x);