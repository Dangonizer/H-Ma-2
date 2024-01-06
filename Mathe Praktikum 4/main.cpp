#include "CKomplex.h"

#include <iostream>

int main()
{
    test_transformation("Daten_original1.txt", 1);
    test_transformation("Daten_original2.txt", 2);
    // std::vector<CKomplex> data = werte_einlesen("Aufgabe2.txt");
    // data = fourier(data, false);
    bildverarbeitung("cattrue64.txt");
    return 0;
}