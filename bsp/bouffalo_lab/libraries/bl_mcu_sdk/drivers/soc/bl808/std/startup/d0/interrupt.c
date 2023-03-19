#include "bflb_core.h"
#include <csi_core.h>
#include "irq_ctx.h"
#include "bl808_glb.h"

extern void riscv_savefpu(const uintptr_t *regs);
extern void riscv_restorefpu(const uintptr_t *regs);

#define RV_EXCEPTION_NUM (16)
typedef uintptr_t (*exception_handler)(uintptr_t cause, uintptr_t val, uintptr_t *regs);

typedef void (*pFunc)(void);

struct bflb_irq_info_s g_irqvector[CONFIG_IRQ_NUM] __attribute__((aligned(16)));

static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs) __attribute__((noreturn));
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    printf("\n\rUn-handled Exception on CPU %d:\n\r", GLB_Get_Core_Type());
    // clang-format off
    printf("mstatus = 0x%16llx, FS=%d, MPP=%d, MPIE=%d\n\r", regs[REG_INT_CTX_NDX],
                                                     (regs[REG_INT_CTX_NDX] >> 13) & 0x3,
                                                     (regs[REG_INT_CTX_NDX] >> 11) & 0x3,
                                                     (regs[REG_INT_CTX_NDX] >> 7) & 1);
    printf("mcause: %d, mtval = 0x%16llx, mepc = 0x%16llx\n\r\n\r", (cause & 0xf), val, regs[REG_EPC_NDX]);

const char *mcause_str[] = {
    "Instruction address misaligned",
    "Instruction access fault",
    "Illegal instruction",
    "Breakpoint",
    "Load address misaligned",
    "Load access fault",
    "Store/AMO address misaligned",
    "Store/AMO access fault",
    "Environment call from U-mode",
    "Environment call from S-mode",
    "RSVD",
    "Environment call from M-mode",
    "Instruction page fault",
    "Load page fault",
    "RSVD",
    "Store/AMO page fault"
};
    if ((cause & 0xf))
        printf("%s\r\n\r\n", mcause_str[cause & 0xf]);

#ifdef CONFIG_TRAP_DUMP_ALL_REGS
    printf("ra = 0x%16llx  ", regs[REG_RA]); printf("sp = 0x%16llx  ", regs[REG_SP]); printf("gp = 0x%16llx  ", regs[REG_GP]);
    printf("tp = 0x%16llx  ", regs[REG_TP]); printf("\n\r");

    printf("t0 = 0x%16llx  ", regs[REG_T0]); printf("t1 = 0x%16llx  ", regs[REG_T1]); printf("t2 = 0x%16llx  ", regs[REG_T2]);
    printf("t3 = 0x%16llx  ", regs[REG_T3]); printf("\n\r");
    printf("t4 = 0x%16llx  ", regs[REG_T4]); printf("t5 = 0x%16llx  ", regs[REG_T5]); printf("t6 = 0x%16llx  ", regs[REG_T6]);
    printf("\n\r");

    printf("a0 = 0x%16llx  ", regs[REG_A0]); printf("a1 = 0x%16llx  ", regs[REG_A1]); printf("a2 = 0x%16llx  ", regs[REG_A2]);
    printf("a3 = 0x%16llx  ", regs[REG_A3]); printf("\n\r");
    printf("a4 = 0x%16llx  ", regs[REG_A4]); printf("a5 = 0x%16llx  ", regs[REG_A5]); printf("a6 = 0x%16llx  ", regs[REG_A6]);
    printf("a7 = 0x%16llx  ", regs[REG_A7]); printf("\n\r");

    printf("s0 = 0x%16llx  ", regs[REG_S0]); printf("s1 = 0x%16llx  ", regs[REG_S1]); printf("s2 = 0x%16llx  ", regs[REG_S2]);
    printf("s3 = 0x%16llx  ", regs[REG_S3]); printf("\n\r");
    printf("s4 = 0x%16llx  ", regs[REG_S4]); printf("s5 = 0x%16llx  ", regs[REG_S5]); printf("s6 = 0x%16llx  ", regs[REG_S6]);
    printf("s7 = 0x%16llx  ", regs[REG_S7]); printf("\n\r");
    printf("s8 = 0x%16llx  ", regs[REG_S8]); printf("s9 = 0x%16llx  ", regs[REG_S9]); printf("s10 = 0x%16llx ", regs[REG_S10]);
    printf("s11 = 0x%16llx  ", regs[REG_S11]); printf("\n\r");
#endif
    // clang-format on
    printf("\n\r");

    while (1) {
    }
}

static uintptr_t exception_handler_ECALL_M(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    regs[REG_EPC_NDX] += 4;
    __asm volatile("nop" ::
                       : "memory");

    return 0;
}

static exception_handler exception_handlers[RV_EXCEPTION_NUM] = {
    exception_handler_default, /*  0: Instruction Address Misaligned */
    exception_handler_default, /*  1: Instruction Access Fault */
    exception_handler_default, /*  2: Illegal Instruction */
    exception_handler_default, /*  3: Breakpoint */
    exception_handler_default, /*  4: Load Address Misaligned */
    exception_handler_default, /*  5: Load Access Fault */
    exception_handler_default, /*  6: Store/AMO Address Misaligned */
    exception_handler_default, /*  7: Store/AMO Access Fault */
    exception_handler_default, /*  8: Environment Call from U-mode */
    exception_handler_default, /*  9: Environment Call from S-mode */
    exception_handler_default, /* 10: Environment Call from H-mode */
    exception_handler_ECALL_M, /* 11: Environment Call from M-mode */
    exception_handler_default, /* 12: Instruction Page Fault */
    exception_handler_default, /* 13: Load Page Fault */
    exception_handler_default, /* 14: Reserved */
    exception_handler_default, /* 15: Store/AMO Page Fault */
};

exception_handler exception_handler_install(uintptr_t vec, exception_handler handler)
{
    exception_handler previous = NULL;

    if (RV_EXCEPTION_NUM > vec) {
        previous = exception_handlers[vec];
        exception_handlers[vec] = handler;
    }

    return previous;
}

uintptr_t *trap_c(uintptr_t cause, uintptr_t *regs)
{
    uint32_t vec = 0;
    uintptr_t tval = __get_MTVAL();

    riscv_savefpu(regs);

    vec = cause & 0x3FF;

    if (RV_EXCEPTION_NUM > vec) {
        exception_handlers[vec](cause, tval, regs);
    } else {
        while (1)
            ;
    }

    riscv_restorefpu(regs);

    return regs;
}

void interrupt_entry(uint64_t irq_num)
{
    irq_callback handler;
    void *arg;
    // volatile uint32_t irq_num;

    //irq_num = PLIC->PLIC_H0_MCLAIM & 0x3ff;

    if (irq_num < CONFIG_IRQ_NUM) {
        handler = g_irqvector[irq_num].handler;
        arg = g_irqvector[irq_num].arg;
        if (handler) {
            handler(irq_num, arg);
        } else {
        }
    } else {
    }
}