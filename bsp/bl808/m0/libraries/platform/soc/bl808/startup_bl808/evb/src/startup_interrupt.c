
#include <stdint.h>
#include <clic.h>
#include <csi_rv32_gcc.h>
#ifdef BL808
#include "bl808.h"
#elif defined(BL606P)
#include "bl606p.h"
#else
#error "Use CHIP BL808/BL606P for this module"
#endif


#define MSG(...)

typedef void( *pFunc )( void );
void NMI_Handler(void);

pFunc g_irqvector[IRQn_LAST]={0};
pFunc g_nmivector=NMI_Handler;

extern void Default_IRQHandler(void);
extern void Default_Handler(void);
extern void IRQ_Handler(void);

const pFunc __Vectors[] __attribute__ ((section(".init"),aligned(64))) = {
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,            /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */
    IRQ_Handler,                         /*         */

    IRQ_Handler,//BMX_ERR_IRQHandler_Wrapper,              /* 16 +  0 */
    IRQ_Handler,//BMX_TO_IRQHandler_Wrapper,               /* 16 +  1 */
    IRQ_Handler,//L1C_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  2 */
    IRQ_Handler,//L1C_BMX_TO_IRQHandler_Wrapper,           /* 16 +  3 */
    IRQ_Handler,//SEC_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  4 */
    IRQ_Handler,//RF_TOP_INT0_IRQHandler_Wrapper,          /* 16 +  5 */
    IRQ_Handler,//RF_TOP_INT1_IRQHandler_Wrapper,          /* 16 +  6 */
    IRQ_Handler,//SDIO_IRQHandler_Wrapper,                 /* 16 +  7 */
    IRQ_Handler,//DMA_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  8 */
    IRQ_Handler,//SEC_GMAC_IRQHandler_Wrapper,             /* 16 +  9 */
    IRQ_Handler,//SEC_CDET_IRQHandler_Wrapper,             /* 16 + 10 */
    IRQ_Handler,//SEC_PKA_IRQHandler_Wrapper,              /* 16 + 11 */
    IRQ_Handler,//SEC_TRNG_IRQHandler_Wrapper,             /* 16 + 12 */
    IRQ_Handler,//SEC_AES_IRQHandler_Wrapper,              /* 16 + 13 */
    IRQ_Handler,//SEC_SHA_IRQHandler_Wrapper,              /* 16 + 14 */
    IRQ_Handler,//DMA_ALL_IRQHandler_Wrapper,              /* 16 + 15 */
    IRQ_Handler,//0,                                       /* 16 + 16 */
    IRQ_Handler,//0,                                       /* 16 + 17 */
    IRQ_Handler,//0,                                       /* 16 + 18 */
    IRQ_Handler,//IRTX_IRQHandler_Wrapper,                 /* 16 + 19 */
    IRQ_Handler,//IRRX_IRQHandler_Wrapper,                 /* 16 + 20 */
    IRQ_Handler,//0,                                       /* 16 + 21 */
    IRQ_Handler,//0,                                       /* 16 + 22 */
    IRQ_Handler,//SF_CTRL_IRQHandler_Wrapper,              /* 16 + 23 */
    IRQ_Handler,//0,                                       /* 16 + 24 */
    IRQ_Handler,//GPADC_DMA_IRQHandler_Wrapper,            /* 16 + 25 */
    IRQ_Handler,//EFUSE_IRQHandler_Wrapper,                /* 16 + 26 */
    IRQ_Handler,//SPI_IRQHandler_Wrapper,                  /* 16 + 27 */
    IRQ_Handler,//0,                                       /* 16 + 28 */
    IRQ_Handler,//UART0_IRQHandler_Wrapper,                /* 16 + 29 */
    IRQ_Handler,//UART1_IRQHandler_Wrapper,                /* 16 + 30 */
    IRQ_Handler,//0,                                       /* 16 + 31 */
    IRQ_Handler,//I2C_IRQHandler_Wrapper,                  /* 16 + 32 */
    IRQ_Handler,//0,                                       /* 16 + 33 */
    IRQ_Handler,//PWM_IRQHandler_Wrapper,                  /* 16 + 34 */
    IRQ_Handler,//0,                                       /* 16 + 35 */
    IRQ_Handler,//TIMER_CH0_IRQHandler_Wrapper,            /* 16 + 36 */
    IRQ_Handler,//TIMER_CH1_IRQHandler_Wrapper,            /* 16 + 37 */
    IRQ_Handler,//TIMER_WDT_IRQHandler_Wrapper,            /* 16 + 38 */
    IRQ_Handler,//0,                                       /* 16 + 39 */
    IRQ_Handler,//0,                                       /* 16 + 40 */
    IRQ_Handler,//0,                                       /* 16 + 41 */
    IRQ_Handler,//0,                                       /* 16 + 42 */
    IRQ_Handler,//0,                                       /* 16 + 43 */
    IRQ_Handler,//GPIO_INT0_IRQHandler_Wrapper,            /* 16 + 44 */
    IRQ_Handler,//0,                                       /* 16 + 45 */
    IRQ_Handler,//0,                                       /* 16 + 46 */
    IRQ_Handler,//0,                                       /* 16 + 47 */
    IRQ_Handler,//0,                                       /* 16 + 48 */
    IRQ_Handler,//0,                                       /* 16 + 49 */
    IRQ_Handler,//PDS_WAKEUP_IRQHandler_Wrapper,           /* 16 + 50 */
    IRQ_Handler,//HBN_OUT0_IRQHandler_Wrapper,             /* 16 + 51 */
    IRQ_Handler,//HBN_OUT1_IRQHandler_Wrapper,             /* 16 + 52 */
    IRQ_Handler,//BOR_IRQHandler_Wrapper,                  /* 16 + 53 */
    IRQ_Handler,//WIFI_IRQHandler_Wrapper,                 /* 16 + 54 */
    IRQ_Handler,//BZ_PHY_IRQHandler_Wrapper,               /* 16 + 55 */
    IRQ_Handler,//BLE_IRQHandler_Wrapper,                  /* 16 + 56 */
    IRQ_Handler,//MAC_TXRX_TIMER_IRQHandler_Wrapper,       /* 16 + 57 */
    IRQ_Handler,//MAC_TXRX_MISC_IRQHandler_Wrapper,        /* 16 + 58 */
    IRQ_Handler,//MAC_RX_TRG_IRQHandler_Wrapper,           /* 16 + 59 */
    IRQ_Handler,//MAC_TX_TRG_IRQHandler_Wrapper,           /* 16 + 60 */
    IRQ_Handler,//MAC_GEN_IRQHandler_Wrapper,              /* 16 + 61 */
    IRQ_Handler,//MAC_PORT_TRG_IRQHandler_Wrapper,         /* 16 + 62 */
    IRQ_Handler,//WIFI_IPC_PUBLIC_IRQHandler_Wrapper,      /* 16 + 63 */
};

void trap_c(uint32_t *regs)
{
    int i;
    uint32_t vec = 0;

    vec = __get_MCAUSE() & 0x3FF;

    MSG("CPU Exception: NO.%d", vec);
    MSG("\n");

    for (i = 0; i < 31; i++) {
        MSG("x%d: %08x\t", i + 1, regs[i]);

        if ((i % 4) == 3) {
            MSG("\n");
        }
    }

    MSG("\n");
    MSG("mepc   : %08x\n", regs[31]);
    MSG("mstatus: %08x\n", regs[32]);

    //if (trap_c_callback) {
    //    trap_c_callback();
    //}

    while (1);
}

void NMI_Handler(void)
{

    MSG("NMI_Handler\r\n");

    while (1);
}

void Interrupt_Handler_Register(IRQn_Type irq,pFunc interruptFun)
{
    if(irq<IRQn_LAST){
        g_irqvector[irq]=interruptFun;
    }
}

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Enable(uint32_t irq_num)
{
#ifdef CONFIG_SYSTEM_SECURE
    csi_vic_enable_sirq(irq_num);
#else
    csi_vic_enable_irq(irq_num);
#endif
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Disable(uint32_t irq_num)
{
#ifdef CONFIG_SYSTEM_SECURE
    csi_vic_disable_sirq(irq_num);
#else
    csi_vic_disable_irq(irq_num);
#endif
}
