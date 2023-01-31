#include <iostream>
#include "vector"
#include "tmp.h"

int SampleMethod(int i)
{
    std::vector<int> s = {1};
    return gg(s[0]);
}

int gg(int i)
{
    return i * 10;
}

int main()
{
    std::cout << SampleMethod(100) << std::endl;
}