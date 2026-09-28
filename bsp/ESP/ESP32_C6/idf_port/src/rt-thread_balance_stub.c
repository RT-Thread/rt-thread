#include <math.h>
#include "rtconfig.h"

static int _real_out_of_range(double x)
{
    return x != x || x >= 9223372036854775808.0 || x <= -9223372036854775808.0;
}

double ceil(double x)
{
    long long n;

    if (_real_out_of_range(x))
    {
        return x;
    }
    n = (long long)x;
    if (x > 0 && (double)n != x)
    {
        n++;
    }
    return (double)n;
}

double floor(double x)
{
    long long n;

    if (_real_out_of_range(x))
    {
        return x;
    }
    n = (long long)x;
    if (x < 0 && (double)n != x)
    {
        n--;
    }
    return (double)n;
}


void _end(void)
{
    return;
}


void _edata(void)
{
    return;
}


#ifndef BSP_USING_BLE // 由于BLE组件使用了VFS组件，而VFS组件提供了这些函数导致了冲突
void opendir(void)
{
    return;
}


void readdir(void)
{
    return;
}


void closedir(void)
{
    return;
}


void select(void)
{
    return;
}

#endif /* BSP_USING_BLE */
