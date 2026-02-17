#include <iostream>
using namespace std;
void module1_computation(long add_num)
{
    cout << "Thread 1: Starting...\n";
    long sum = 0;
    for (long i = 0; i < 1000000000; ++i)
    {
        sum += add_num;
    }
    cout << "Thread 1: Done. Sum = " << sum << "\n";
}