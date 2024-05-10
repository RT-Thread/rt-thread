#ifndef ASM_VDSO_SYS_H
#define ASM_VDSO_SYS_H

#include <time.h>
#include <unistd.h>

#include <syscall.h>
#include "vdso_config.h"
#include "vdso_datapage.h"

#define __always_unused                 __attribute__((__unused__))
#define __maybe_unused                  __attribute__((__unused__))

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

extern VdsoDataPage _vdso_data[CS_BASES] __attribute__((visibility("hidden")));
static inline const VdsoDataPage *__arch_get_vdso_data(void)
{
	return _vdso_data;
}

#endif