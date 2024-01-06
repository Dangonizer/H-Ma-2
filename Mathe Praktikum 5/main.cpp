#include <iostream>
#include "CZufall.h"
#include "CLotto.h"
#include <time.h>

int main()
{
    CZufall test;
    test.initialisiere(2);
    test.test(3, 7, 10000);
    test.initialisiere(2);
    test.test(3, 7, 10000);
    // Selbe ergebnisse da selbe rng seed

    test.initialisiere(4);
    test.test(3, 7, 10000);
    test.initialisiere(5);
    test.test(3, 7, 10000);
    // Unterschiedliche ergebnisse mit anderer seed

    test.initialisiere(time(nullptr));
    test.test(3, 7, 10000);
    // std::cin.ignore();
    test.initialisiere(time(nullptr));
    test.test(3, 7, 10000);
    // unterschiedliche ergebnisse wenn mehr als eine sekunde zwischen den initialisierungen liegt

    test.test_falsch(3, 7, 10000);

    CLotto testziehung(6, 40, 2);
    testziehung.set_zettel({11, 16, 19, 22, 29, 40});
    std::cout << "Richtige Zahlen: " << testziehung.ergebnis() << std::endl;

    std::cout << "Wahrscheinlichkeit für 2 Richtige: " << montecarlo(2, 6, 40, 1000000, 1) << std::endl;

    return 0;
}