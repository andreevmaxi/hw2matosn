#include <cstdio>
#include <cassert>

unsigned long long allocation(unsigned long long n, unsigned long long k);

unsigned long long combinations(unsigned int n, unsigned int k);

int main()
{
    char operation = {};
    unsigned long long n,k;
    scanf("%c %d %d", &operation, &n, &k);

    assert(n != 0);
    assert(k != 0);

    switch (operation)
    {
        case 'Ñ':
            printf("%d", combinations(n, k));
            break;
        case 'A':
            printf("%d", allocation(n, k));
            break;
        default:
            printf("error");
    }

    return 0;
}


unsigned long long allocation(unsigned long long n, unsigned long long k)
{
    assert(n > k);
    unsigned long long answer = 1;
    unsigned long long tmp = n - k;
    printf("%d", tmp);

    for (unsigned long long CounterFactorial = n; CounterFactorial > tmp; --CounterFactorial)
    {
        printf("%d %d %d\n", CounterFactorial, (CounterFactorial > tmp), tmp);
        answer *= CounterFactorial;
    }

    return answer;
}

unsigned long long combinations(unsigned int n, unsigned int k)
{
    long long answer = 1;
    int tmp = 0;

    if(k < (n - k))
    {
        tmp = (n - k);
    } else
    {
        tmp = k;
        k = (n - k);
    }

    for (int CounterFactorial = 0; CounterFactorial < tmp; ++CounterFactorial)
    {
        answer *= (n - CounterFactorial);
    }
    for (int i = 2; i < k; ++i)
    {
        answer /= i;
    }

    return answer;
}
