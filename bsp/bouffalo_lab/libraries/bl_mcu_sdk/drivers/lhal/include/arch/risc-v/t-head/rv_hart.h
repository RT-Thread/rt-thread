#ifndef _RV_HART_H_
#define _RV_HART_H_

#include <stdint.h>

void __attribute__((noreturn)) rv_hart_hang(void);
int rv_hart_misa_ext_chk(char ext);

void rv_enterSupervisor(void) __attribute__((naked, noinline));
void rv_enterUser(void) __attribute__((naked, noinline));

void __attribute__((noreturn))
rv_hart_switch_mode_from_M(uintptr_t arg0, uintptr_t arg1,
                           uintptr_t next_addr, uintptr_t next_mode);

#endif
