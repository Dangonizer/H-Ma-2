#pragma once
#include <vector>
#include "CZufall.h"

class CLotto
{
private:
    int k;
    int n;
    int s;
    std::vector<int> zettel;

public:
    CLotto(int k, int n, int s) : k{k}, n{n}
    {
        if (s < 0)
            srand(time(NULL));
        else
            srand(s);
    }

    void set_zettel(std::vector<int> z)
    {
        zettel = z;
        return;
    }

    std::vector<int> ziehung()
    {
        std::vector<int> result;
        result.resize(k);
        CZufall random;
        // random.initialisiere(s);
        for (int i = 0; i < k; i++)
        {
            int value = random.wert(1, n);
            bool duplicate = false;
            for (int j = 0; j < k; j++)
            {
                if (result[j] == value)
                    duplicate = true;
            }
            if (duplicate == true)
            {
                i--;
                continue;
            }
            result[i] = value;
        }
        return result;
    }

    int ergebnis()
    {
        int count = 0;
        std::vector<int> result = ziehung();
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (zettel[i] == result[j])
                    count++;
            }
        }
        return count;
    }
};

double montecarlo(int r, int k, int n, int N, int typ);