#include <cmath>
#include <iostream>
#include "CMyVector.h"

CMyVector gradient(CMyVector x, double (*function)(CMyVector x))
{
    CMyVector result(x.get_dimension());
    CMyVector helper = x;
    double comp;
    const double h = pow(10, -8);
    for (int i = 0; i < x.get_dimension(); i++)
    {
        helper.set_component(x.get_component(i) + h, i);
        comp = (function(helper) - function(x)) / h;
        helper = x;
        result.set_component(comp, i);
    }
    return result;
};

CMyVector maximize(CMyVector x, double (*function)(CMyVector x), double lambda)
{
    const double l = pow(10, -5);
    CMyVector x_neu(x.get_dimension());
    CMyVector x_test(x.get_dimension());
    for (int i = 0; i < 25; i++)
    {

        if (gradient(x, function).length() < l)
        {
            std::cout << "\nEnde wegen aureichend kleinem Gradientenbetrag\n";
            print_default(x, function, lambda);
            return x;
        }
        std::cout << "\nSchritt " << i << ":\n";
        print_default(x, function, lambda);

        x_neu = x + (gradient(x, function) * lambda);

        print_new(x_neu, function);

        if (function(x_neu) <= function(x))
        {
            while (function(x_neu) <= function(x))
            {
                lambda = lambda / 2;
                std::cout << "\nhalbiere Schrittweite: lambda = " << lambda;
                x_neu = x + (gradient(x, function) * lambda);
                print_new(x_neu, function);
            }
            x = x_neu;
        }
        else
        {
            x_test = x + (gradient(x, function) * 2 * lambda);
            std::cout << "\nTeste mit doppelter Schrittweite: lambda = " << lambda * 2;
            print_test(x_test, function);
            if (function(x_test) > function(x_neu))
            {
                std::cout << "Verdoppele Schrittweite\n";
                x = x_test;
                lambda = lambda * 2;
            }
            else
            {
                std::cout << "Behalte Schrittweite\n";
                x = x_neu;
            }
        }
    };
    std::cout << "\nEnde wegen maximaler Anzahl der Schritte\n";
    print_default(x, function, lambda);
    return x;
};

void print_default(CMyVector x, double (*function)(CMyVector x), double lambda)
{
    std::cout << "x = ( ";
    for (int i = 0; i < x.get_dimension(); i++)
    {
        std::cout << x.get_component(i) << "; ";
    }
    std::cout << ")\nlambda = " << lambda << "\nf(x) = " << function(x) << "\ngrad f(x) = ( ";
    for (int i = 0; i < x.get_dimension(); i++)
    {
        std::cout << gradient(x, function).get_component(i) << "; ";
    }
    std::cout << ")\n||grad f(x)|| = " << gradient(x, function).length() << std::endl;
};

void print_new(CMyVector x, double (*function)(CMyVector x))
{
    std::cout << "\nx_neu = ( ";
    for (int i = 0; i < x.get_dimension(); i++)
    {
        std::cout << x.get_component(i) << "; ";
    }
    std::cout << ")\nf(x_neu) = " << function(x) << std::endl;
}

void print_test(CMyVector x, double (*function)(CMyVector x))
{
    std::cout << "\nx_test = ( ";
    for (int i = 0; i < x.get_dimension(); i++)
    {
        std::cout << x.get_component(i) << "; ";
    }
    std::cout << ")\nf(x_test) = " << function(x) << std::endl;
}

double function_f(CMyVector x)
{
    double result;
    result = sin(x.get_component(0) * x.get_component(1)) + sin(x.get_component(0)) + cos(x.get_component(1));
    return result;
};

double function_g(CMyVector x)
{
    double result;
    result = -(2 * pow(x.get_component(0), 2) - 2 * x.get_component(0) * x.get_component(1) + pow(x.get_component(1), 2) + pow(x.get_component(2), 2) - 2 * x.get_component(0) - 4 * x.get_component(2));
    return result;
};