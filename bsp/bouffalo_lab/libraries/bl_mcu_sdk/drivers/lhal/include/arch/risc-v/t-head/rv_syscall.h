#ifndef _RV_SYSCALL_H_
#define _RV_SYSCALL_H_

#include <stdint.h>

#define RV_SYSCALL_BACK_TO_MACHINE 0
#define RV_SYSCALL_WFI             1

#ifndef __riscv_32e

#define RV_SYSCALL(which, arg0, arg1, arg2, arg3) ({        \
    register uintptr_t a0 __asm("a0") = (uintptr_t)(arg0);  \
    register uintptr_t a1 __asm("a1") = (uintptr_t)(arg1);  \
    register uintptr_t a2 __asm("a2") = (uintptr_t)(arg2);  \
    register uintptr_t a3 __asm("a3") = (uintptr_t)(arg3);  \
    register uintptr_t a7 __asm("a7") = (uintptr_t)(which); \
    asm volatile("ecall"                                    \
                 : "+r"(a0)                                 \
                 : "r"(a1), "r"(a2), "r"(a3), "r"(a7)       \
                 : "memory");                               \
    a0;                                                     \
})

#else

#define RV_SYSCALL(which, arg0, arg1, arg2, arg3) ({        \
    register uintptr_t a0 __asm("a0") = (uintptr_t)(arg0);  \
    register uintptr_t a1 __asm("a1") = (uintptr_t)(arg1);  \
    register uintptr_t a2 __asm("a2") = (uintptr_t)(arg2);  \
    register uintptr_t a3 __asm("a3") = (uintptr_t)(arg3);  \
    register uintptr_t a5 __asm("a5") = (uintptr_t)(which); \
    asm volatile("ecall"                                    \
                 : "+r"(a0)                                 \
                 : "r"(a1), "r"(a2), "r"(a3), "r"(a5)       \
                 : "memory");                               \
    a0;                                                     \
})

#endif

static inline void rv_syscall_back_to_machine(void)
{
    RV_SYSCALL(RV_SYSCALL_BACK_TO_MACHINE, 0, 0, 0, 0);
}

#endif /* _RV_SYSCALL_H_ */
