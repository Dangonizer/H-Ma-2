#include <iostream>
#include "CMyVector.h"
#include "C_DGLSolver.h"

int main()
{

    CMyVector start(2);
    start.set_component(0, 0);
    start.set_component(1, 1);
    C_DGLSolver system(dgl1);
    CMyVector result = system.euler(0, 2, 100, start);
    std::cout << "Ende Euler bei y: " << result.get_component(0) << "; " << result.get_component(1) << std::endl;
    result = system.heun(0, 2, 100, start);
    std::cout << "Ende Heun bei y: " << result.get_component(0) << "; " << result.get_component(1) << std::endl;
    deviation();
    return 0;
}