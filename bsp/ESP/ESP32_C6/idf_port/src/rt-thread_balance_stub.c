#include <math.h>
#include "rtconfig.h"
double ceil(double i)
{
    i=i;
    return i;
}

double floor (double i)
{
    i = i;
    return i;
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
