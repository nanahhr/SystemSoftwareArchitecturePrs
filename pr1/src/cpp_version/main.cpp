#include <iostream>
#include <thread>
using namespace std;

void module1_computation(long add_num);
void module2_computation(int n);

int main()
{
    long add_num = 5;
    int fact_num = 12;

    cout << "Main: Starting threads (C++ style, no headers)...\n";

    thread t1(module1_computation, add_num);
    thread t2(module2_computation, fact_num);

    t1.join();
    t2.join();

    cout << "Main: All done!\n";

    return 0;
}