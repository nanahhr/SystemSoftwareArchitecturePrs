#include <iostream>
using namespace std;

void module2_computation(int n)
{
    cout << "Thread 2: Starting...\n";
    unsigned long long fact = 1;
    for (int i = 1; i <= n; ++i)
    {
        fact *= i;
    }
    cout << "Thread 2: Factorial of " << n << " = " << fact << "\n";
}