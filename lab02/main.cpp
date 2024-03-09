#include <iostream>
#include "Time.h"

using namespace std;

int main()
{
    Time t1(200);
    cout << t1 << endl;
    Time t2;
    cin >> t2;

    Time t3  = t2 - t1;
    int t3s = t3;
    cout << t3s << endl;
    return 0;
}
