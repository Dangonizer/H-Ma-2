#include <iostream>
#include "CMyVector.h"

int main()
{
    CMyVector x1(2);
    // x1.set_component(0.2, 0);
    // x1.set_component(-2.1, 1);
    // maximize(x1, function_f);
    CMyVector x2(3);
    maximize(x2, function_g, 0.1);
    return 0;
}