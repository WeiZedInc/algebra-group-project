#include "pch.h"

extern "C" int __declspec(dllexport) SampleMethod(int i)
{
    return i * 10;
}
