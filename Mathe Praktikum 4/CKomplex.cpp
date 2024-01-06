#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include "CKomplex.h"

CKomplex operator*(CKomplex a, double b)
{
    CKomplex result(a.re() * b, a.im() * b);
    return result;
}
CKomplex operator*(double b, CKomplex a)
{
    return operator*(a, b);
}

std::vector<CKomplex> fourier(std::vector<CKomplex> data, bool hin)
{
    int vorzeichen = 1;
    if (hin)
        vorzeichen = -1;

    std::vector<CKomplex> result;
    int N = data.size();
    result.resize(N);

    for (int n = 0; n < N; n++)
    {
        CKomplex comp(0, 0);
        for (int k = 0; k < N; k++)
        {
            comp = comp + data[k] * CKomplex(vorzeichen * 2 * M_PI * k * n / N);
        }
        comp = comp * double(1 / sqrt(N));
        result[n] = comp;
    }
    return result;
}

void test_transformation(std::string filename, int index)
{
    std::vector<CKomplex> data = werte_einlesen(filename);
    std::vector<CKomplex> data_trans = fourier(data);
    save_files(data_trans, index);
    std::vector<CKomplex> data_trans_read[5];
    open_files(index, data_trans_read);
    std::vector<CKomplex> data_retrans[5];
    for (int i = 0; i < 5; i++)
    {
        data_retrans[i] = fourier(data_trans_read[i], false);
    }
    berechne_abweichung(data, data_retrans);
}

void save_files(std::vector<CKomplex> data, int index)
{
    double epsilon[4] = {0.001, 0.01, 0.1, 1};
    werte_ausgeben("data" + std::to_string(index) + "epsilon_default", data);
    for (int j = 0; j < 4; j++)
    {
        werte_ausgeben("data" + std::to_string(index) + "epsilon" + std::to_string(epsilon[j]), data, epsilon[j]);
    };
}

void open_files(int index, std::vector<CKomplex> data_read[5])
{
    double epsilon[4] = {0.001, 0.01, 0.1, 1};
    data_read[0] = werte_einlesen("data" + std::to_string(index) + "epsilon_default");
    for (int i = 0; i < 4; i++)
    {
        data_read[i + 1] = werte_einlesen("data" + std::to_string(index) + "epsilon" + std::to_string(epsilon[i]));
    }
}

void berechne_abweichung(std::vector<CKomplex> data, std::vector<CKomplex> data_retrans[5])
{
    double deviation[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < data.size(); j++)
        {
            if ((data[j] - data_retrans[i][j]).abs() > deviation[i])
                deviation[i] = (data[j] - data_retrans[i][j]).abs();
        }
    }
    std::cout << "Maximale Abweichung Standard-Epsilon: " << deviation[0] << std::endl;
    std::cout << "Maximale Abweichung epsilon=0.001: " << deviation[1] << std::endl;
    std::cout << "Maximale Abweichung epsilon=0.01: " << deviation[2] << std::endl;
    std::cout << "Maximale Abweichung epsilon=0.1: " << deviation[3] << std::endl;
    std::cout << "Maximale Abweichung epsilon=1: " << deviation[4] << std::endl
              << std::endl;
}

void bildverarbeitung(std::string path)
{
    std::vector<CKomplex> data = werte_einlesen(path);
    std::vector<CKomplex> trans = fourier(data);
    double epsilon[5] = {10, 30, 100, 300, 1000};
    for (int i = 0; i < 5; i++)
    {
        werte_ausgeben("bild_epsilon" + std::to_string(epsilon[i]), trans, epsilon[i]);
    }
    std::vector<CKomplex> trans_filtered[5];
    for (int i = 0; i < 5; i++)
    {
        trans_filtered[i] = werte_einlesen("bild_epsilon" + std::to_string(epsilon[i]));
    }
    std::vector<CKomplex> retrans[5];
    for (int i = 0; i < 5; i++)
    {
        retrans[i] = fourier(trans_filtered[i], false);
    }
    for (int i = 0; i < 5; i++)
    {
        werte_ausgeben("bild_final_epsilon" + std::to_string(epsilon[i]) + ".txt", retrans[i]);
    }
}