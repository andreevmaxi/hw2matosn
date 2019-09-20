#include <cstdio>
#include <cassert>
#include <cstdlib>

#ifdef _VORONEZH
    #define CALL printf
#else
    #define CALL if(0) printf
#endif

unsigned long long   allocation(unsigned long long n, unsigned long long k);

unsigned long long combinations(unsigned long long n, unsigned long long k);

int main()
{
    char operation = {};
    unsigned long long n,k;
    CALL("Hello, zemlyak, enter your operation and two integers, used in this operation\n");
    scanf("%c %llu %llu", &operation, &n, &k);

    assert(n != 0);
    assert(k != 0);

    switch (operation)
    {
        case 'C':
            CALL("Number of combinations of k in n: ");
            printf("%llu", combinations(n, k));
            break;
        case 'A':
            CALL("Number of allocations of k in n: ");
            printf("%llu", allocation(n, k));
            break;
        default:
            printf("error");
    }
    CALL("\nThank you for reading this code!");

    return 0;
}


unsigned long long allocation(unsigned long long n, unsigned long long k)
{
    assert(n > k);
    unsigned long long answer = 1;
    unsigned long long tmp = n - k;

    for (unsigned long long CounterFactorial = n; CounterFactorial > tmp; --CounterFactorial)
    {
        answer *= CounterFactorial;
    }

    return answer;
}

unsigned long long combinations(unsigned long long n, unsigned long long k)
{
    unsigned long long answer = 1;
    unsigned long long tmp = 0;
    unsigned long long DivideTmp = 2;

    if(k < (n - k))  //swaps k and (n - k) to use it in n!/k!*(n - k)!
    {
        tmp = (n - k);
    } else
    {
        tmp = k;
        k = (n - k);
    }

    unsigned long long* FactorArray = (unsigned long long*)calloc((n - tmp), sizeof(unsigned long long));
    unsigned long long* FactorialOfKArray = (unsigned long long*)calloc(k - 1, sizeof(unsigned long long));

    int i = 0; // index integer of FactorArray

    for (unsigned long long CounterFactorial = n; CounterFactorial > tmp; --CounterFactorial)
    {
        *(FactorArray + i) = CounterFactorial;
        CALL("FactorArray: %llu %d\n", *(FactorArray + i), i);
        ++i;
    }

    for (int j = 0; j < k - 1; ++j)
    {
        *(FactorialOfKArray + j) = j + 2;
        CALL("FactorialOfKArray: %llu %d\n", *(FactorialOfKArray + j), j);
    }

    CALL("\n");

    for (i = 0; i < (n - tmp); ++i)
    {
        for (int j = 0; j < k - 1; ++j)
        {
            if(*(FactorialOfKArray + j) != 0 && *(FactorArray + i) % *(FactorialOfKArray + j) == 0)
            {
                CALL("%llu %llu\n", *(FactorArray + i), *(FactorialOfKArray + j));
                *(FactorArray + i) /= *(FactorialOfKArray + j); // doing ans/k! or ans/(n - k)! if k > (n - k)
                *(FactorialOfKArray + j) = 0;
            }
        }

        answer *= (*(FactorArray + i)); // doing n!/(n - k)! or n!/k! if k > (n - k)
    }

    free(FactorArray);
    free(FactorialOfKArray);

    return answer;
}
