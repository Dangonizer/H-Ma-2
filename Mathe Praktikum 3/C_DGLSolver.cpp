#include "C_DGLSolver.h"
#include <iostream>

CMyVector dgl1(CMyVector y, double x)
{
    CMyVector result(2);
    result.set_component(2 * y.get_component(1) - x * y.get_component(0), 0);
    result.set_component(y.get_component(0) * y.get_component(1) - 2 * x * x * x, 1);
    return result;
}

double dgl2(CMyVector y, double x)
{
    return 2 * x * y.get_component(1) * y.get_component(2) + 2 * y.get_component(0) * y.get_component(0) * y.get_component(1);
}

void deviation()
{
    CMyVector start(3);
    start.set_component(1, 0);
    start.set_component(-1, 1);
    start.set_component(2, 2);
    C_DGLSolver dgl(dgl2);
    std::cout << "Euler 10 steps: " << 0.5 - dgl.euler(1, 2, 10, start).get_component(0) << std::endl;
    std::cout << "Euler 100 steps: " << 0.5 - dgl.euler(1, 2, 100, start).get_component(0) << std::endl;
    std::cout << "Euler 1000 steps: " << 0.5 - dgl.euler(1, 2, 1000, start).get_component(0) << std::endl;
    std::cout << "Euler 10000 steps: " << 0.5 - dgl.euler(1, 2, 10000, start).get_component(0) << std::endl;

    std::cout << "Heun 10 steps: " << 0.5 - dgl.heun(1, 2, 10, start).get_component(0) << std::endl;
    std::cout << "Heun 100 steps: " << 0.5 - dgl.heun(1, 2, 100, start).get_component(0) << std::endl;
    std::cout << "Heun 1000 steps: " << 0.5 - dgl.heun(1, 2, 1000, start).get_component(0) << std::endl;
    std::cout << "Heun 10000 steps: " << 0.5 - dgl.heun(1, 2, 10000, start).get_component(0) << std::endl;
}