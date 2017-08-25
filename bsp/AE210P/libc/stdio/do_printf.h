#ifndef __DO_PRINTF_H__
#define __DO_PRINTF_H__

#include <stdarg.h> /* va_list, va_arg() */
typedef int (*fnptr_t)(unsigned c, void **helper);
int do_printf(const char *fmt, va_list args, fnptr_t fn, void *ptr);

#endif /* __DO_PRINTF_H__ */
