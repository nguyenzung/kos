#ifndef MATH
#define MATH

namespace std
{

template <class T>
T abs(T value)
{
    return value >= 0 ? value : -value; 
}

template <class T>
T max(T a, T b)
{
    return a > b ? a : b;
}

template <class T>
T min(T a, T b)
{
    return a < b ? a : b;
}

}

#endif