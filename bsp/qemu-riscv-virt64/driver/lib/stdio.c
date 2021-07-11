#include <rthw.h>
#include <rtconfig.h>

#ifdef USING_RV64_LINUX_GNU_TOOLCHAIN

int vsprintf(char *out, const char *fmt, va_list ap) {
  rt_vsprintf(out, fmt, ap);
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(out, fmt, args);
  return 0;
}


#endif