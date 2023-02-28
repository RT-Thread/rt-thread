#include <stdint.h>
#include <csi_core.h>
#include <bl808.h>
#include <bflb_platform.h>
#include "bl808_glb.h"
#include "irq_ctx.h"

#define DUMP_ALL_REGS
#define DUMP_MCAUSE_INFO

pFunc g_irqvector[IRQn_LAST] __attribute__((aligned(16))) = { NULL };

void Interrupt_Default_Handler(void) __attribute__((weak));
void Interrupt_Default_Handler(void)
{
    /* un-handled external IRQ */
    MSG("Enter interrupt default handler\r\n");
}

void Interrupt_Handler_Register(IRQn_Type irq, pFunc interruptFun)
{
    if (irq < IRQn_LAST) {
        g_irqvector[irq] = interruptFun;
    }
}

static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs) __attribute__((noreturn));
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    MSG("\n\rUn-handled Exception on CPU %d:\n\r", GLB_Get_Core_Type());
    // clang-format off
    MSG("mstatus = 0x%16llx, FS=%d, MPP=%d, MPIE=%d\n\r", regs[REG_INT_CTX_NDX],
                                                     (regs[REG_INT_CTX_NDX] >> 13) & 0x3,
                                                     (regs[REG_INT_CTX_NDX] >> 11) & 0x3,
                                                     (regs[REG_INT_CTX_NDX] >> 7) & 1);
    MSG("mcause: %d, mtval = 0x%16llx, mepc = 0x%16llx\n\r\n\r", (cause & 0xf), val, regs[REG_EPC_NDX]);
#ifdef DUMP_MCAUSE_INFO
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
        MSG("%s\r\n\r\n", mcause_str[cause & 0xf]);
#endif

#ifdef DUMP_ALL_REGS
    MSG("ra = 0x%16llx  ", regs[REG_RA]); MSG("sp = 0x%16llx  ", regs[REG_SP]); MSG("gp = 0x%16llx  ", regs[REG_GP]);
    MSG("tp = 0x%16llx  ", regs[REG_TP]); MSG("\n\r");

    MSG("t0 = 0x%16llx  ", regs[REG_T0]); MSG("t1 = 0x%16llx  ", regs[REG_T1]); MSG("t2 = 0x%16llx  ", regs[REG_T2]);
    MSG("t3 = 0x%16llx  ", regs[REG_T3]); MSG("\n\r");
    MSG("t4 = 0x%16llx  ", regs[REG_T4]); MSG("t5 = 0x%16llx  ", regs[REG_T5]); MSG("t6 = 0x%16llx  ", regs[REG_T6]);
    MSG("\n\r");

    MSG("a0 = 0x%16llx  ", regs[REG_A0]); MSG("a1 = 0x%16llx  ", regs[REG_A1]); MSG("a2 = 0x%16llx  ", regs[REG_A2]);
    MSG("a3 = 0x%16llx  ", regs[REG_A3]); MSG("\n\r");
    MSG("a4 = 0x%16llx  ", regs[REG_A4]); MSG("a5 = 0x%16llx  ", regs[REG_A5]); MSG("a6 = 0x%16llx  ", regs[REG_A6]);
    MSG("a7 = 0x%16llx  ", regs[REG_A7]); MSG("\n\r");

    MSG("s0 = 0x%16llx  ", regs[REG_S0]); MSG("s1 = 0x%16llx  ", regs[REG_S1]); MSG("s2 = 0x%16llx  ", regs[REG_S2]);
    MSG("s3 = 0x%16llx  ", regs[REG_S3]); MSG("\n\r");
    MSG("s4 = 0x%16llx  ", regs[REG_S4]); MSG("s5 = 0x%16llx  ", regs[REG_S5]); MSG("s6 = 0x%16llx  ", regs[REG_S6]);
    MSG("s7 = 0x%16llx  ", regs[REG_S7]); MSG("\n\r");
    MSG("s8 = 0x%16llx  ", regs[REG_S8]); MSG("s9 = 0x%16llx  ", regs[REG_S9]); MSG("s10 = 0x%16llx ", regs[REG_S10]);
    MSG("s11 = 0x%16llx  ", regs[REG_S11]); MSG("\n\r");
#endif
    // clang-format on
    MSG("\n\r");

    while (1)
        ;
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

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void ATTR_TCM_SECTION CPU_Interrupt_Enable(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
    } else {
        if (csi_vic_get_prio(irq_num) == 0) {
            csi_vic_set_prio(irq_num, 1);
        }

#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_enable_sirq(irq_num);
#else
        csi_vic_enable_irq(irq_num);
#endif
    }
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void ATTR_TCM_SECTION CPU_Interrupt_Disable(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
    } else {
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_disable_sirq(irq_num);
#else
        csi_vic_disable_irq(irq_num);
#endif
    }
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void ATTR_TCM_SECTION CPU_Interrupt_Pending_Clear(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
        return;
    } else {
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_clear_pending_irq(irq_num);
#else
        csi_vic_clear_pending_irq(irq_num);
#endif
    }
}

void System_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    csi_vic_set_prio(IRQn, PreemptPriority);
}

void System_Interrupt_Init(void)
{
    for (uintptr_t irq = 0; irq < IRQn_LAST; irq++) {
        g_irqvector[irq] = Interrupt_Default_Handler;
    }
}
