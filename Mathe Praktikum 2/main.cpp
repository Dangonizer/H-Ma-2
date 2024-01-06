#include <iostream>
#include "CMyVector.h"
#include "CMyMatrix.h"

int main()
{
    /*    CMyVector x1(4);
        x1.set_component(1, 0);
        x1.set_component(2, 1);
        x1.set_component(0, 2);
        x1.set_component(3, 3);
        jacobi(x1, f1);*/
    CMyVector x2(2);
    x2.set_component(1, 0);
    x2.set_component(1, 1);
    newton(x2, f2);
    return 0;
}