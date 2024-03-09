#ifndef TIME_H
#define TIME_H

#include <iostream>

using namespace std;

class Time{
public:
    Time(int sec = 0, int min = 0, int hour = 0);

    Time operator+(const Time &other) const;
    Time operator-(const Time &other) const;
    Time operator*(int &C) const;
    friend ostream &operator<<(ostream &str, Time&rhs);
    friend istream &operator>>(istream &str, Time &rhs);
    operator int();

private:
    int sec_, min_, hour_;
};


#endif // TIME_H
