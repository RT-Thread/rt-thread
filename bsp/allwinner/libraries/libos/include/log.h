#ifndef LIBOS_LOG_H__
#define LIBOS_LOG_H__

#include <rtthread.h>

#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define pr_err(fmt, ...)           LOG_E(fmt, ##__VA_ARGS__)
#define pr_warn(fmt, ...)          LOG_W(fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...)          LOG_I(fmt, ##__VA_ARGS__)
#define pr_debug(fmt, ...)         LOG_D(fmt, ##__VA_ARGS__)

#define __wrn(...) rt_kprintf(__VA_ARGS__)
#define __inf(...) rt_kprintf(__VA_ARGS__)
#define __err(...) rt_kprintf(__VA_ARGS__)
#define __msg(...) rt_kprintf(__VA_ARGS__)

#ifndef printk
#define printk  rt_kprintf
#endif

#include "typedef.h"

#endif
