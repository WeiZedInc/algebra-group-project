#include "pch.h"

extern "C" int __declspec(dllexport) SampleMethod(int i)
{
    return gg(i);
}

int gg(int i)
{
    return i * 20;
}