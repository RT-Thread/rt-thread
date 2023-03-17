#include "csi_core.h"
#include "rv_hart.h"
#include <risc-v/csr.h>

#define PRV_U 0
#define PRV_S 1
#define PRV_H 2
#define PRV_M 3

#define INSERT_FIELD(val, which, fieldval) \
    (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

void __attribute__((noreturn)) rv_hart_hang(void)
{
    while (1) {
        __WFI();
    }

    __builtin_unreachable();
}

/* determine CPU extension, return non-zero support */
int rv_hart_misa_ext_chk(char ext)
{
    unsigned long misa = READ_CSR(misa);

    if (misa) {
        if ('A' <= ext && ext <= 'Z') {
            return misa & (1 << (ext - 'A'));
        }

        if ('a' <= ext && ext <= 'z') {
            return misa & (1 << (ext - 'a'));
        }

        return 0;
    }

    return 0;
}

void rv_enterSupervisor(void)
{
    __asm volatile(
        "fence\n\t"
        "csrw mepc, ra\n\t"
        "li   t0, ~(3 << 11)\n\t"
        "li   t1, 1 << 11\n\t"
        "csrr t2, mstatus\n\t"
        "and  t0, t0, t2\n\t"
        "or   t0, t0, t1\n\t"
        "csrw mstatus, t0\n\t"
        "mret\n\t"
        :
        :
        : "memory");
}

void rv_enterUser(void)
{
    __asm volatile(
        "fence\n\t"
        "csrw mepc, ra\n\t"
        "li   t0, ~(3 << 11)\n\t"
        "csrr t2, mstatus\n\t"
        "and  t0, t0, t2\n\t"
        "csrw mstatus, t0\n\t"
        "mret\n\t"
        :
        :
        : "memory");
}

void __attribute__((noreturn))
rv_hart_switch_mode_from_M(uintptr_t arg0, uintptr_t arg1,
                           uintptr_t next_addr, uintptr_t next_mode)
{
#if __riscv_xlen == 32
    unsigned long val;
#else
    unsigned long val;
#endif

    switch (next_mode) {
        case PRV_M:
            break;

        case PRV_S:
            if (!rv_hart_misa_ext_chk('S')) {
                rv_hart_hang();
            }

            break;

        case PRV_U:
            if (!rv_hart_misa_ext_chk('U')) {
                rv_hart_hang();
            }

            break;

        default:
            rv_hart_hang();
    }

    val = READ_CSR(mstatus);
    val = INSERT_FIELD(val, MSTATUS_MPPM, next_mode);
    val = INSERT_FIELD(val, MSTATUS_MPIE, 0);

    WRITE_CSR(mstatus, val);
    WRITE_CSR(mepc, next_addr);

    if (next_mode == PRV_S) {
        WRITE_CSR(stvec, next_addr);
        WRITE_CSR(sscratch, 0);
        WRITE_CSR(sie, 0);
        WRITE_CSR(satp, 0);
    } else if (next_mode == PRV_U) {
        /* un-implemented
		        WRITE_CSR(utvec, next_addr);
		        WRITE_CSR(uscratch, 0);
		        WRITE_CSR(uie, 0);
		*/
    }

    register unsigned long a0 __asm("a0") = arg0;
    register unsigned long a1 __asm("a1") = arg1;
    __asm__ __volatile__("mret"
                         :
                         : "r"(a0), "r"(a1));
    __builtin_unreachable();
}
