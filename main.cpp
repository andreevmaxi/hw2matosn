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

    FILE* f = fopen("input.txt", "r");
    fscanf(f, "%c %llu %llu", &operation, &n, &k);

    f = fopen("output.txt", "w");
    switch (operation)
    {
        case 'C':
            CALL("Number of combinations of k in n: ");
            fprintf(f, "%llu", combinations(n, k));
            break;
        case 'A':
            CALL("Number of allocations of k in n: ");
            fprintf(f, "%llu", allocation(n, k));
            break;
        default:
            fprintf(f, "error");
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
    unsigned long long* FactorialOfKArray = (unsigned long long*)calloc(k, sizeof(unsigned long long));

    int i = 0; // index integer of FactorArray

    for (unsigned long long CounterFactorial = n; CounterFactorial > tmp; --CounterFactorial)
    {
        *(FactorArray + i) = CounterFactorial;
        ++i;
    }

    *(FactorialOfKArray) = 1;

    for (int j = 1; j < k; ++j)
    {
        *(FactorialOfKArray + j) = j + 1;
    }

    for (i = 0; i < (n - tmp); ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            unsigned long long tmp = *(FactorialOfKArray + j);

            while(*(FactorialOfKArray + j) != 1 && tmp > 1)
            {
                if(*(FactorialOfKArray + j) % tmp == 0 && *(FactorArray + i) % tmp == 0)
                {
                    *(FactorArray + i)       /= tmp; // doing ans/k! or ans/(n - k)! if k > (n - k)
                    *(FactorialOfKArray + j) /= tmp;
                }

                --tmp;
            }
        }

        answer *= (*(FactorArray + i)); // doing n!/(n - k)! or n!/k! if k > (n - k)
    }

    free(FactorArray);
    free(FactorialOfKArray);

    return answer;
}
