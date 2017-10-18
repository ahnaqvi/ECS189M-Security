#include "windows.h"
#include <stdio.h>

DWORD WINAPI thread_function(void* data)
{
    float number = 1.5;
    while(true)
    {
        number*=number;
    }
    return 0;
}

void main()
{
    while (true)
    {
        CreateThread(NULL, 0, &thread_function, NULL, 0, NULL);
    }
}