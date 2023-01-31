#ifdef CS_COMPILE

#include "pch.h"

int extern "C" __delclspec(dllexport) sayHello(int i)
{
    return gg(i);
}

#endif

inline int gg(int i)
{
    return i * 10;
}
