#pragma once

#include <rtconfig.h>

#ifdef ARCH_MM_MMU
#include <ioremap.h>
#else
#define rt_ioremap(a, s) (a)
#define rt_iounmap(a)
#endif
