#pragma once

#include <rtconfig.h>

#ifdef RT_USING_SMART
#include <ioremap.h>
#else
#define rt_ioremap(a, s) (a)
#endif
