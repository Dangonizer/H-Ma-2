#include <cmath>
#include <iostream>
#include "CMyMatrix.h"

CMyMatrix jacobi(CMyVector x, CMyVector (*funktion)(CMyVector x))
{
    const double h = 0.0001;
    CMyMatrix result(x.get_dimension(), funktion(x).get_dimension());

    for (int i = 0; i < result.get_dim_x(); i++)
    {
        CMyVector helper = x;
        helper.set_component(helper.get_component(i) + h, i);
        CMyVector column = (funktion(helper) + (funktion(x)) * (-1)) * (1 / h);
        for (int j = 0; j < result.get_dim_y(); j++)
        {
            result.set_comp(i, j, column.get_component(j));
        }
    }
    return result;
}

CMyVector newton(CMyVector x, CMyVector (*funktion)(CMyVector x))
{
    const double l = 1e-5;
    CMyVector delta_x(x.get_dimension());
    for (int i = 0; i < 50; i++)
    {

        if (funktion(x).length() < l)
        {
            std::cout << "\nEnde wegen aureichend kleinem Funktionswert\n";
            print_final(x, funktion);
            return x;
        }
        std::cout << "\nSchritt " << i << ":\n";
        print(x, funktion);
        x = x + ((jacobi(x, funktion).invers() * funktion(x) * (-1)));
    };
    std::cout << "\nEnde wegen maximaler Anzahl der Schritte\n";
    return x;
}

void print(CMyVector x, CMyVector (*funktion)(CMyVector x))
{
    std::cout << "x = " << x.get_component(0) << "; " << x.get_component(1) << std::endl;
    std::cout << "f(x) = " << funktion(x).get_component(0) << "; " << funktion(x).get_component(1) << std::endl;
    std::cout << "f'(x) = " << jacobi(x, funktion).get_comp(0, 0) << "; " << jacobi(x, funktion).get_comp(1, 0) << "; " << jacobi(x, funktion).get_comp(0, 1) << "; " << jacobi(x, funktion).get_comp(1, 1) << std::endl;
    std::cout << "f'(x))^(-1) = " << jacobi(x, funktion).invers().get_comp(0, 0) << "; " << jacobi(x, funktion).invers().get_comp(1, 0) << "; " << jacobi(x, funktion).invers().get_comp(0, 1) << "; " << jacobi(x, funktion).invers().get_comp(1, 1) << std::endl;
    std::cout << "dx = " << (jacobi(x, funktion).invers() * funktion(x) * (-1)).get_component(0) << "; " << (jacobi(x, funktion).invers() * funktion(x) * (-1)).get_component(1) << std::endl;
    std::cout << "||f(x)|| = " << funktion(x).length() << std::endl;
}

void print_final(CMyVector x, CMyVector (*funktion)(CMyVector x))
{
    std::cout << "x = " << x.get_component(0) << "; " << x.get_component(1) << std::endl;
    std::cout << "f(x) = " << funktion(x).get_component(0) << "; " << funktion(x).get_component(1) << std::endl;
    std::cout << "||f(x)|| = " << funktion(x).length() << std::endl;
}

CMyVector operator*(CMyMatrix A, CMyVector x)
{
    CMyVector result(A.get_dim_y());
    for (int i = 0; i < A.get_dim_y(); i++)
    {
        double value = 0;
        for (int j = 0; j < A.get_dim_x(); j++)
        {
            value += A.get_comp(j, i) * x.get_component(j);
        }
        result.set_component(value, i);
    }
    return result;
};

CMyVector f1(CMyVector x)
{
    CMyVector result(3);
    result.set_component(x.get_component(0) * x.get_component(1) * exp(x.get_component(2)), 0);
    result.set_component(x.get_component(1) * x.get_component(2) * x.get_component(3), 1);
    result.set_component(x.get_component(3), 2);
    return result;
}

CMyVector f2(CMyVector x)
{
    CMyVector result(2);
    result.set_component(pow(x.get_component(0), 3) * pow(x.get_component(1), 3) - 2 * x.get_component(1), 0);
    result.set_component(x.get_component(0) - 2, 1);
    return result;
}