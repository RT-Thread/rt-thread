#include <stdint.h>
#include <clic.h>
#include <csi_rv32_gcc.h>
#include <bl808.h>
#include <bflb_platform.h>
#include "bl808_glb.h"
#include "irq_ctx.h"

typedef void (*pFunc)(void);
void NMI_Handler(void);

/*
 * g_irqvector is the real ISRs written in simple C style: no __attribute__ ((interrupt)) needed!
 * An when IRQ is in vector mode, the __Vectors is the pesudo handler entry, which redirects the CPU
 * to a single handler: Default_IRQHandler, and who will call the corresponding ISR in g_irqvector,
 * as well as context save/restore work.
 * BTW, some of the special IRQs have different solutions, such as mtime for the RTOS "tick".
 */
pFunc g_irqvector[IRQn_LAST] __attribute__((section(".noinit_data")));
pFunc g_nmivector = NMI_Handler;

extern void Default_IRQHandler(void);
extern void Default_Handler(void);
extern void Mtspend_Handler();


const pFunc __Vectors[] __attribute__((section(".init"), aligned(64))) = {
    Default_Handler, /*         */
    Default_Handler, /*         */
    Default_Handler, /*         */
#if defined(__OS_FREERTOS__)
    Mtspend_Handler, /*  3: M-mode Soft IRQ   */
#else
    Default_IRQHandler, /*  3: M-mode Soft IRQ   */
#endif
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_IRQHandler, /*  7: M-mode Timer IRQ  */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */
    Default_Handler,    /*         */

    Default_IRQHandler, //BMX_ERR_IRQHandler_Wrapper,              /* 16 +  0 */
    Default_IRQHandler, //BMX_TO_IRQHandler_Wrapper,               /* 16 +  1 */
    Default_IRQHandler, //L1C_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  2 */
    Default_IRQHandler, //L1C_BMX_TO_IRQHandler_Wrapper,           /* 16 +  3 */
    Default_IRQHandler, //SEC_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  4 */
    Default_IRQHandler, //RF_TOP_INT0_IRQHandler_Wrapper,          /* 16 +  5 */
    Default_IRQHandler, //RF_TOP_INT1_IRQHandler_Wrapper,          /* 16 +  6 */
    Default_IRQHandler, //SDIO_IRQHandler_Wrapper,                 /* 16 +  7 */
    Default_IRQHandler, //DMA_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  8 */
    Default_IRQHandler, //SEC_GMAC_IRQHandler_Wrapper,             /* 16 +  9 */
    Default_IRQHandler, //SEC_CDET_IRQHandler_Wrapper,             /* 16 + 10 */
    Default_IRQHandler, //SEC_PKA_IRQHandler_Wrapper,              /* 16 + 11 */
    Default_IRQHandler, //SEC_TRNG_IRQHandler_Wrapper,             /* 16 + 12 */
    Default_IRQHandler, //SEC_AES_IRQHandler_Wrapper,              /* 16 + 13 */
    Default_IRQHandler, //SEC_SHA_IRQHandler_Wrapper,              /* 16 + 14 */
    Default_IRQHandler, //DMA_ALL_IRQHandler_Wrapper,              /* 16 + 15 */
    Default_IRQHandler, //0,                                       /* 16 + 16 */
    Default_IRQHandler, //0,                                       /* 16 + 17 */
    Default_IRQHandler, //0,                                       /* 16 + 18 */
    Default_IRQHandler, //IRTX_IRQHandler_Wrapper,                 /* 16 + 19 */
    Default_IRQHandler, //IRRX_IRQHandler_Wrapper,                 /* 16 + 20 */
    Default_IRQHandler, //0,                                       /* 16 + 21 */
    Default_IRQHandler, //0,                                       /* 16 + 22 */
    Default_IRQHandler, //SF_CTRL_IRQHandler_Wrapper,              /* 16 + 23 */
    Default_IRQHandler, //0,                                       /* 16 + 24 */
    Default_IRQHandler, //GPADC_DMA_IRQHandler_Wrapper,            /* 16 + 25 */
    Default_IRQHandler, //EFUSE_IRQHandler_Wrapper,                /* 16 + 26 */
    Default_IRQHandler, //SPI_IRQHandler_Wrapper,                  /* 16 + 27 */
    Default_IRQHandler, //0,                                       /* 16 + 28 */
    Default_IRQHandler, //UART0_IRQHandler_Wrapper,                /* 16 + 29 */
    Default_IRQHandler, //UART1_IRQHandler_Wrapper,                /* 16 + 30 */
    Default_IRQHandler, //0,                                       /* 16 + 31 */
    Default_IRQHandler, //I2C_IRQHandler_Wrapper,                  /* 16 + 32 */
    Default_IRQHandler, //0,                                       /* 16 + 33 */
    Default_IRQHandler, //PWM_IRQHandler_Wrapper,                  /* 16 + 34 */
    Default_IRQHandler, //0,                                       /* 16 + 35 */
    Default_IRQHandler, //TIMER_CH0_IRQHandler_Wrapper,            /* 16 + 36 */
    Default_IRQHandler, //TIMER_CH1_IRQHandler_Wrapper,            /* 16 + 37 */
    Default_IRQHandler, //TIMER_WDT_IRQHandler_Wrapper,            /* 16 + 38 */
    Default_IRQHandler, //0,                                       /* 16 + 39 */
    Default_IRQHandler, //0,                                       /* 16 + 40 */
    Default_IRQHandler, //0,                                       /* 16 + 41 */
    Default_IRQHandler, //0,                                       /* 16 + 42 */
    Default_IRQHandler, //0,                                       /* 16 + 43 */
    Default_IRQHandler, //GPIO_INT0_IRQHandler_Wrapper,            /* 16 + 44 */
    Default_IRQHandler, //0,                                       /* 16 + 45 */
    Default_IRQHandler, //0,                                       /* 16 + 46 */
    Default_IRQHandler, //0,                                       /* 16 + 47 */
    Default_IRQHandler, //0,                                       /* 16 + 48 */
    Default_IRQHandler, //0,                                       /* 16 + 49 */
    Default_IRQHandler, //PDS_WAKEUP_IRQHandler_Wrapper,           /* 16 + 50 */
    Default_IRQHandler, //HBN_OUT0_IRQHandler_Wrapper,             /* 16 + 51 */
    Default_IRQHandler, //HBN_OUT1_IRQHandler_Wrapper,             /* 16 + 52 */
    Default_IRQHandler, //BOR_IRQHandler_Wrapper,                  /* 16 + 53 */
    Default_IRQHandler, //WIFI_IRQHandler_Wrapper,                 /* 16 + 54 */
    Default_IRQHandler, //BZ_PHY_IRQHandler_Wrapper,               /* 16 + 55 */
    Default_IRQHandler, //BLE_IRQHandler_Wrapper,                  /* 16 + 56 */
    Default_IRQHandler, //MAC_TXRX_TIMER_IRQHandler_Wrapper,       /* 16 + 57 */
    Default_IRQHandler, //MAC_TXRX_MISC_IRQHandler_Wrapper,        /* 16 + 58 */
    Default_IRQHandler, //MAC_RX_TRG_IRQHandler_Wrapper,           /* 16 + 59 */
    Default_IRQHandler, //MAC_TX_TRG_IRQHandler_Wrapper,           /* 16 + 60 */
    Default_IRQHandler, //MAC_GEN_IRQHandler_Wrapper,              /* 16 + 61 */
    Default_IRQHandler, //MAC_PORT_TRG_IRQHandler_Wrapper,         /* 16 + 62 */
    Default_IRQHandler, //WIFI_IPC_PUBLIC_IRQHandler_Wrapper,      /* 16 + 63 */
};

/**
  \brief       the default IRQ handler.
  \param[in]   cause Number of IRQ.
  \return      no return.
*/
void Interrupt_Default_Handler(uintptr_t cause) __attribute__((weak));
void Interrupt_Default_Handler(uintptr_t cause)
{
    /* un-handled external IRQ */
    MSG("Enter interrupt default handler %x\r\n", cause);
}

/**
  \brief       the default Trap handler.
  \param[in]   cause Number of Trap.
  \param[in]   val from mtval reg.
  \param[in]   regs CPU context of the Trap.
  \return      no return.
*/
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs);
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    uint32_t mepc_val;

    /* 0x80000000-0x90000000 is protected by PMP for CPU Prefetching */
    if(val>=0x80000000&&val<0x90000000){
        uint32_t tmp_cause=cause&0xf;
        if(tmp_cause==0x01||tmp_cause==0x05){
            /*Instruction access fault or Load access fault*/
            mepc_val=BL_RD_WORD(regs[REG_EPC_NDX]);
            if((mepc_val&0x03)==0x03){
                regs[REG_EPC_NDX] += 4;
            }else{
                regs[REG_EPC_NDX] += 2;
            }
            return 0;
        }
    }

    MSG("\n\rUn-handled Exception on CPU %d:\n\r", GLB_Get_Core_Type());

    MSG("cause: 0x%8x, tval = 0x%8x, epc = 0x%8x\n\r", cause, val, regs[REG_EPC_NDX]);
#ifndef CONFIG_ERR_NOT_DUMP_MCAUSE_INFO
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

// clang-format off
#ifndef CONFIG_ERR_NOT_DUMP_ALL_REGS
    MSG("ra = 0x%08x  ", regs[REG_RA]); MSG("sp = 0x%08x  ", regs[REG_SP]); MSG("gp = 0x%08x  ", regs[REG_GP]);
    MSG("tp = 0x%08x  ", regs[REG_TP]); MSG("\n\r");

    MSG("t0 = 0x%08x  ", regs[REG_T0]); MSG("t1 = 0x%08x  ", regs[REG_T1]); MSG("t2 = 0x%08x  ", regs[REG_T2]);
    MSG("t3 = 0x%08x  ", regs[REG_T3]); MSG("\n\r");
    MSG("t4 = 0x%08x  ", regs[REG_T4]); MSG("t5 = 0x%08x  ", regs[REG_T5]); MSG("t6 = 0x%08x  ", regs[REG_T6]);
    MSG("\n\r");

    MSG("a0 = 0x%08x  ", regs[REG_A0]); MSG("a1 = 0x%08x  ", regs[REG_A1]); MSG("a2 = 0x%08x  ", regs[REG_A2]);
    MSG("a3 = 0x%08x  ", regs[REG_A3]); MSG("\n\r");
    MSG("a4 = 0x%08x  ", regs[REG_A4]); MSG("a5 = 0x%08x  ", regs[REG_A5]); MSG("a6 = 0x%08x  ", regs[REG_A6]);
    MSG("a7 = 0x%08x  ", regs[REG_A7]); MSG("\n\r");

    MSG("s0 = 0x%08x  ", regs[REG_S0]); MSG("s1 = 0x%08x  ", regs[REG_S1]); MSG("s2 = 0x%08x  ", regs[REG_S2]);
    MSG("s3 = 0x%08x  ", regs[REG_S3]); MSG("\n\r");
    MSG("s4 = 0x%08x  ", regs[REG_S4]); MSG("s5 = 0x%08x  ", regs[REG_S5]); MSG("s6 = 0x%08x  ", regs[REG_S6]);
    MSG("s7 = 0x%08x  ", regs[REG_S7]); MSG("\n\r");
    MSG("s8 = 0x%08x  ", regs[REG_S8]); MSG("s9 = 0x%08x  ", regs[REG_S9]); MSG("s10 = 0x%08x ", regs[REG_S10]);
    MSG("s11 = 0x%08x  ", regs[REG_S11]); MSG("\n\r");
#endif
    // clang-format on

    while (1)
        ;
}

/**
  \brief       the trap handler for ecall from M-mode.
  \param[in]   cause Number of Trap.
  \param[in]   val from mtval reg.
  \param[in]   regs CPU context of the Trap.
  \return      no return.
*/
static uintptr_t exception_handler_ECALL_M(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    regs[REG_EPC_NDX] += 4;
    __asm volatile("nop" ::
                       : "memory");

    /* indicated ecall from Machine-Mode */
    regs[REG_A0] = 1;
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

/**
  \brief       install handler to Trap handler.
  \param[in]   vec Number of Trap.
  \param[in]   handler the handler for Trap.
  \return      the previous handler.
*/
exception_handler exception_handler_install(uintptr_t vec, exception_handler handler)
{
    exception_handler previous = NULL;

    if (RV_EXCEPTION_NUM > vec) {
        previous = exception_handlers[vec];
        exception_handlers[vec] = handler;
    }

    return previous;
}

/**
  \brief       C handler for CPU Traps.
  \param[in]   regs is the CPU context.
  \return      None.
*/
void trap_c(uintptr_t *regs)
{
    uint32_t vec = 0;
    uintptr_t cause = __get_MCAUSE();
    uintptr_t tval = __get_MTVAL();

    //riscv_savefpu(regs);

    vec = cause & 0x3FF;

    if (RV_EXCEPTION_NUM > vec) {
        exception_handlers[vec](cause, tval, (uintptr_t *)regs);
    } else {
        while (1)
            ;
    }

    //riscv_restorefpu(regs);
}

/**
  \brief       set all ISRs in g_irqvector to the default one.
  \return      None.
*/
void System_Interrupt_Init(void)
{
    for (uintptr_t irq = 0; irq < IRQn_LAST; irq++) {
        g_irqvector[irq] = (pFunc)Interrupt_Default_Handler;
    }
}

/**
  \brief       install ISR to g_irqvector.
  \param[in]   irq Number of IRQ.
  \param[in]   interruptFun the ISR for irq.
  \return      None.
*/
void Interrupt_Handler_Register(IRQn_Type irq, pFunc interruptFun)
{
    if (irq < IRQn_LAST) {
        g_irqvector[irq] = interruptFun;
    }
}

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Enable(uint32_t irq_num)
{
    if (irq_num < IRQn_LAST)
        csi_vic_enable_irq(irq_num);
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Disable(uint32_t irq_num)
{
    if (irq_num < IRQn_LAST)
        csi_vic_disable_irq(irq_num);
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void CPU_Interrupt_Pending_Clear(uint32_t irq_num)
{
    if (irq_num < IRQn_LAST)
        csi_vic_clear_pending_irq(irq_num);
}
