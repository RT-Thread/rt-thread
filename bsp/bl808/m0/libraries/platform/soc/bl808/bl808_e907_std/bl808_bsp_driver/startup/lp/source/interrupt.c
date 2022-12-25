#include <stdint.h>
#include <clic.h>
#include <csi_rv32_gcc.h>
#include <bl808.h>
#include <bflb_platform.h>
#include "irq_ctx.h"
#include "bl808_common.h"

#define DUMP_ALL_REGS
#define DUMP_MCAUSE_INFO

typedef void (*pFunc)(void);
void NMI_Handler(void);

pFunc g_irqvector[IRQn_LAST] = { 0 };
pFunc g_nmivector = NMI_Handler;

extern void Default_IRQHandler(void);
extern void Default_Handler(void);
extern void Mtspend_Handler(void);

void Interrupt_Default_Handler(void) __attribute__((weak));
void Interrupt_Default_Handler(void)
{
    /* un-handled external IRQ */
#if !defined(__OS_FREERTOS__)
    MSG("Enter interrupt Default_Handler\r\n");
#endif
}

#if 0
	extern void Trap_Handler(void);
	extern void Interrupt_Handler(void);
	void Interrupt_Handler_Stub(void);

	void clic_msip_handler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void clic_mtimer_handler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void clic_mext_handler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void clic_csoft_handler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void BMX_ERR_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void BMX_TO_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void L1C_BMX_ERR_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void L1C_BMX_TO_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_BMX_ERR_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void RF_TOP_INT0_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void RF_TOP_INT1_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SDIO_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void DMA_BMX_ERR_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_GMAC_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_CDET_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_PKA_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_TRNG_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_AES_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SEC_SHA_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void DMA_ALL_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void IRTX_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void IRRX_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SF_CTRL_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void GPADC_DMA_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void EFUSE_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void SPI_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void UART0_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void UART1_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void I2C_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void PWM_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void TIMER_CH0_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void TIMER_CH1_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void TIMER_WDT_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void GPIO_INT0_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void PDS_WAKEUP_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void HBN_OUT0_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void HBN_OUT1_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void BOR_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void WIFI_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void BZ_PHY_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void BLE_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_TXRX_TIMER_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_TXRX_MISC_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_RX_TRG_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_TX_TRG_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_GEN_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void MAC_PORT_TRG_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
	void WIFI_IPC_PUBLIC_IRQHandler_Wrapper(void) __attribute__((weak, alias("Default_IRQHandler")));
#endif

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

static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs) __attribute__((noreturn));
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    MSG("\n\rUn-handled Exception on CPU %d:\n\r", GLB_Get_Core_Type());
    MSG("cause: 0x%8x, tval = 0x%8x, epc = 0x%8x\n\r", cause, val, regs[REG_EPC_NDX]);
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

// clang-format off
#ifdef DUMP_ALL_REGS
    MSG("ra = 0x%08x  ", regs[REG_RA]); MSG("sp = 0x%08x  ", regs[REG_SP]); MSG("gp = 0x%08x  ", regs[REG_GP]);
    MSG("tp = 0x%08x  ", regs[REG_TP]); MSG("\n\r");

    MSG("t0 = 0x%08x  ", regs[REG_T0]); MSG("t1 = 0x%08x  ", regs[REG_T1]); MSG("t2 = 0x%08x  ", regs[REG_T2]);
    MSG("\n\r");

    MSG("a0 = 0x%08x  ", regs[REG_A0]); MSG("a1 = 0x%08x  ", regs[REG_A1]); MSG("a2 = 0x%08x  ", regs[REG_A2]);
    MSG("a3 = 0x%08x  ", regs[REG_A3]); MSG("\n\r");
    MSG("a4 = 0x%08x  ", regs[REG_A4]); MSG("a5 = 0x%08x  ", regs[REG_A5]); MSG("\n\r");

    MSG("s0 = 0x%08x  ", regs[REG_S0]); MSG("s1 = 0x%08x  ", regs[REG_S1]); MSG("\n\r");
#endif
    // clang-format on

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

void trap_c(uint32_t *regs)
{
    uint32_t vec = 0;
    uintptr_t cause = __get_MCAUSE();
    uintptr_t tval = __get_MTVAL();

    vec = cause & 0x3FF;

    if (RV_EXCEPTION_NUM > vec) {
        exception_handlers[vec](cause, tval, regs);
    } else {
        while (1)
            ;
    }
}

void NMI_Handler(void)
{
    MSG("NMI_Handler\r\n");

    while (1)
        ;
}

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
void ATTR_TCM_SECTION CPU_Interrupt_Enable(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
    } else {
        if (irq_num >= CPU_LP_MAX_IRQ_NUM) {
            irq_num -= 32;
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
        if (irq_num >= CPU_LP_MAX_IRQ_NUM) {
            irq_num -= 32;
        }

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

void System_Interrupt_Init(void)
{
    for (uintptr_t irq = 0; irq < IRQn_LAST; irq++) {
        g_irqvector[irq] = Interrupt_Default_Handler;
    }
}
