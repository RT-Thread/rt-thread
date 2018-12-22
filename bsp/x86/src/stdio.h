#ifndef __STDIO_H_H
#define __STDIO_H_H

#include <rt_thread_sym.h>

typedef unsigned int size_t;

typedef int (*sprintf_fcn_t)(char *buf ,const char *format, ...);
typedef int (*snprintf_fcn_t)(char *buf, size_t size, const char *format, ...);
typedef void (*puts_fcn_t)(const char *str);
typedef void (*printf_fcn_t)(const char *fmt, ...);

#define printf ((printf_fcn_t)__abs_rt_kprintf)
#define puts ((printf_fcn_t)__abs_rt_kputs)
#define sprintf ((printf_fcn_t)__abs_rt_sprintf)
#define snprintf ((printf_fcn_t)__abs_rt_snprintf)

#endif
