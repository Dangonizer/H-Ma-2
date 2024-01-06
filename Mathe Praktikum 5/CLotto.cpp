#include "CLotto.h"

double montecarlo(int r, int k, int n, int N, int typ)
{
    CLotto Lotto(k, n, -1);
    double count = 0;
    if (typ == 0)
    {
        Lotto.set_zettel(Lotto.ziehung());
        for (int i = 0; i < N; i++)
        {
            if (Lotto.ergebnis() == r)
            {
                count += 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            Lotto.set_zettel(Lotto.ziehung());
            if (Lotto.ergebnis() == r)
            {
                count += 1;
            }
        }
    }
    return count / N;
}