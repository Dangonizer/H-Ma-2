#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

class CZufall
{
public:
    int wert(int a, int b)
    {
        return (rand() % (b - a + 1)) + a;
    }

    void initialisiere(int s)
    {
        srand(s);
    }

    void test(int a, int b, int N)
    {
        std::vector<int> counter;
        counter.resize(b - a + 1);
        for (int i = 0; i < N; i++)
        {
            counter[wert(a, b) - a] += 1;
        }
        for (int i = 0; i < b - a + 1; i++)
        {
            std::cout << i + a << ": " << counter[i] << std::endl;
        }
        std::cout << std::endl;
    }

    void test_falsch(int a, int b, int N)
    {
        std::vector<int> counter;
        counter.resize(b - a + 1);
        for (int i = 0; i < N; i++)
        {
            initialisiere(time(NULL));
            counter[wert(a, b) - a] += 1;
        }
        for (int i = 0; i < b - a + 1; i++)
        {
            std::cout << i + a << ": " << counter[i] << std::endl;
        }
        std::cout << std::endl;
    }
};