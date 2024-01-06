#pragma once
#include "CMyVector.h"
class C_DGLSolver
{
private:
    CMyVector (*f_DGL_System)(CMyVector y, double x);
    double (*f_DGL_nterOrdnung)(CMyVector y, double x);
    bool issystem;

    CMyVector ableitungen(CMyVector y, double x)
    {
        if (issystem)
            return f_DGL_System(y, x);
        else
        {
            CMyVector result(y.get_dimension());
            for (int i = 0; i < y.get_dimension() - 1; i++)
            {
                result.set_component(y.get_component(i + 1), i);
            }
            result.set_component(f_DGL_nterOrdnung(y, x), y.get_dimension() - 1);
            return result;
        }
    }

public:
    C_DGLSolver(CMyVector (*f_)(CMyVector y, double x)) : f_DGL_System{f_}, issystem{true} {};
    C_DGLSolver(double (*f_)(CMyVector y, double x)) : f_DGL_nterOrdnung{f_}, issystem{false} {};

    CMyVector euler(double x_start, double x_end, int steps, CMyVector y_start)
    {
        double h = (x_end - x_start) / steps;
        double x = x_start;
        CMyVector result = y_start;
        for (int i = 0; i < steps; i++)
        {
            result = result + (ableitungen(result, x) * h);
            x += h;
        }
        return result;
    }

    CMyVector heun(double x_start, double x_end, int steps, CMyVector y_start)
    {
        double h = (x_end - x_start) / steps;
        double x = x_start;
        double x_test;
        CMyVector result = y_start;
        CMyVector test(y_start.get_dimension());
        for (int i = 0; i < steps; i++)
        {
            test = result + (ableitungen(result, x) * h);
            x_test = x + h;

            result = result + ((ableitungen(result, x) + ableitungen(test, x_test)) * 0.5 * h);
            x += h;
        }
        return result;
    }
};

CMyVector dgl1(CMyVector y, double x);
double dgl2(CMyVector y, double x);
void deviation();