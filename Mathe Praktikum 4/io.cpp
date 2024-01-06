#include <fstream>
#include <vector>
#include "CKomplex.h"
using namespace std;

vector<CKomplex> werte_einlesen(const std::string dateiname)
{
    int i, N, idx;
    double re, im;
    vector<CKomplex> werte;
    // File oeffnen
    ifstream fp;
    fp.open(dateiname);
    // Dimension einlesen
    fp >> N;
    // Werte-Vektor anlegen
    werte.resize(N);
    CKomplex null(0, 0);
    for (i = 0; i < N; i++)
        werte[i] = null;
    // Eintraege einlesen und im Werte-Vektor ablegen
    while (!fp.eof())
    {
        fp >> idx >> re >> im;
        CKomplex a(re, im);
        werte[idx] = a;
    }
    // File schliessen
    fp.close();

    return werte;
}

void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon)
{
    int i;
    int N = werte.size();
    // File oeffnen
    ofstream fp;
    fp.open(dateiname);
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    fp.precision(10);
    for (i = 0; i < N; i++)
        if (werte[i].abs() > epsilon)
            fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
    // File schliessen
    fp.close();
}