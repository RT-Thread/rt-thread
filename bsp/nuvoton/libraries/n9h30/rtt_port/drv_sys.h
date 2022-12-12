#ifndef __PLAT_INTERRUPT_H__
#define __PLAT_INTERRUPT_H__

#include "rthw.h"
#include <rtconfig.h>

#if defined(BSP_USING_MMU)
    #include "mmu.h"
    #define NONCACHEABLE BIT31
#else
    #define NONCACHEABLE 0
#endif

#define sysprintf rt_kprintf

typedef enum
{
    SYS_IPRST_NA = -1,

    /* SYS_AHBIPRST, SYS_BA + 0x060 */
    CHIPRST,
    AHBIPRST_Reserved_1,
    CPURST,
    GDMARST,
    AHBIPRST_Reserved_4,
    AHBIPRST_Reserved_5,
    AHBIPRST_Reserved_6,
    AHBIPRST_Reserved_7,

    I2SRST,
    LCDRST,
    CAPRST,
    AHBIPRST_Reserved_11,
    AHBIPRST_Reserved_12,
    AHBIPRST_Reserved_13,
    AHBIPRST_Reserved_14,
    AHBIPRST_Reserved_15,

    EMAC0RST,
    EMAC1RST,
    USBHRST,
    USBDRST,
    FMIRST,
    GE2DRST,
    JPEGRST,
    CRYPTORST,

    SDIORST,
    AHBIPRST_Reserved_25,
    AHBIPRST_Reserved_26,
    AHBIPRST_Reserved_27,
    AHBIPRST_Reserved_28,
    AHBIPRST_Reserved_29,
    AHBIPRST_Reserved_30,
    AHBIPRST_Reserved_31,

    /* SYS_APBIPRST0, SYS_BA + 0x064 */
    APBIPRST0_Reserved_0,
    APBIPRST0_Reserved_1,
    APBIPRST0_Reserved_2,
    GPIORST,
    ETIMER0RST,
    ETIMER1RST,
    ETIMER2RST,
    ETIMER3RST,

    TIMER0RST,
    TIMER1RST,
    TIMER2RST,
    TIMER3RST,
    TIMER4RST,
    APBIPRST0_Reserved_13,
    APBIPRST0_Reserved_14,
    APBIPRST0_Reserved_15,

    UART0RST,
    UART1RST,
    UART2RST,
    UART3RST,
    UART4RST,
    UART5RST,
    UART6RST,
    UART7RST,

    UART8RST,
    UART9RST,
    UART10RST,
    APBIPRST0_Reserved_27,
    APBIPRST0_Reserved_28,
    APBIPRST0_Reserved_29,
    APBIPRST0_Reserved_30,
    APBIPRST0_Reserved_31,

    /* SYS_APBIPRST1, SYS_BA + 0x068 */
    I2C0RST,
    I2C1RST,
    APBIPRST1_Reserved_2,
    APBIPRST1_Reserved_3,
    SPI0RST,
    SPI1RST,
    APBIPRST1_Reserved_6,
    APBIPRST1_Reserved_7,

    CAN0RST,
    CAN1RST,
    APBIPRST1_Reserved_10,
    APBIPRST1_Reserved_11,
    SMC0RST,
    SMC1RST,
    APBIPRST1_Reserved_14,
    APBIPRST1_Reserved_15,

    APBIPRST1_Reserved_16,
    APBIPRST1_Reserved_17,
    APBIPRST1_Reserved_18,
    APBIPRST1_Reserved_19,
    APBIPRST1_Reserved_20,
    APBIPRST1_Reserved_21,
    APBIPRST1_Reserved_22,
    APBIPRST1_Reserved_23,

    ADCRST,
    APBIPRST1_Reserved_25,
    MTPCRST,
    PWMRST,
    APBIPRST1_Reserved_28,
    APBIPRST1_Reserved_29,
    APBIPRST1_Reserved_30,
    APBIPRST1_Reserved_31,

    SYS_IPRST_CNT

} E_SYS_IPRST;

typedef enum
{
    SYS_IPCLK_NA = -1,

    /* CLK_HCLKEN, CLK_BA + 0x010 */
    CPUCKEN,
    HCLKCKEN,
    HCLK1CKEN,
    HCLK3CKEN,
    HCLK4CKEN,
    PCLKCKEN,
    HCLKEN_Reserved_6,
    TICCKEN,

    SRAMCKEN,
    EBICKEN,
    DDRCKEN,
    HCLKEN_Reserved_11,
    GDMACKEN,
    HCLKEN_Reserved_13,
    HCLKEN_Reserved_14,
    CKOCKEN,

    EMAC0CKEN,
    EMAC1CKEN,
    USBHCKEN,
    USBDCKEN,
    FMICKEN,
    NANDCKEN,
    EMMCCKEN,
    CRYPTOCKEN,

    I2SCKEN,
    LCDCKEN,
    CAPCKEN,
    SENSORCKEN,
    GE2DCKEN,
    JPEGCKEN,
    SDHCKEN,
    HCLKEN_Reserved_31,

    CLK_HCLKEN_END,

    /* CLK_BA+0x014 */

    /* CLK_PCLKEN0 CLK_BA+0x018 */
    CLK_PCLKEN0_BEGIN = CLK_HCLKEN_END + 32,

    WDTCKEN = CLK_PCLKEN0_BEGIN,
    WWDTCKEN,
    RTCCKEN,
    GPIOCKEN,
    ETIMER0CKEN,
    ETIMER1CKEN,
    ETIMER2CKEN,
    ETIMER3CKEN,

    TIMER0CKEN,
    TIMER1CKEN,
    TIMER2CKEN,
    TIMER3CKEN,
    TIMER4CKEN,
    PCLKEN0_Reserved_14,
    PCLKEN0_Reserved_15,
    PCLKEN0_Reserved_16,

    UART0CKEN,
    UART1CKEN,
    UART2CKEN,
    UART3CKEN,
    UART4CKEN,
    UART5CKEN,
    UART6CKEN,
    UART7CKEN,

    UART8CKEN,
    UART9CKEN,
    UART10CKEN,
    PCLKEN0_Reserved_27,
    PCLKEN0_Reserved_28,
    PCLKEN0_Reserved_29,
    PCLKEN0_Reserved_30,
    PCLKEN0_Reserved_31,

    /* CLK_PCLKEN1, CLK_BA + 0x01C */
    I2C0CKEN,
    I2C1CKEN,
    PCLKEN1_Reserved_2,
    PCLKEN1_Reserved_3,
    SPI0CKEN,
    SPI1CKEN,
    PCLKEN1_Reserved_6,
    PCLKEN1_Reserved_7,

    CAN0CKEN,
    CAN1CKEN,
    PCLKEN1_Reserved_10,
    PCLKEN1_Reserved_11,
    SMC0CKEN,
    SMC1CKEN,
    PCLKEN1_Reserved_14,
    PCLKEN1_Reserved_15,

    PCLKEN1_Reserved_16,
    PCLKEN1_Reserved_17,
    PCLKEN1_Reserved_18,
    PCLKEN1_Reserved_19,
    PCLKEN1_Reserved_20,
    PCLKEN1_Reserved_21,
    PCLKEN1_Reserved_22,
    PCLKEN1_Reserved_23,

    ADCCKEN,
    PCLKEN1_Reserved_25,
    MTPCCKEN,
    PWMCKEN,
    PCLKEN1_Reserved_28,
    PCLKEN1_Reserved_29,
    PCLKEN1_Reserved_30,
    PCLKEN1_Reserved_31,

    SYS_IPCLK_CNT

} E_SYS_IPCLK;

typedef enum
{
    USB0_ID_DEVICE,
    USB0_ID_HOST,
    USB0_ID_CNT
} E_SYS_USB0_ID;

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_set_priority(int vector, int priority);
void rt_hw_interrupt_set_type(int vector, int type);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name);

void rt_hw_systick_init(void);
void nu_clock_base_init(void);

void nu_systick_udelay(uint32_t delay_us);
void nu_sys_ip_reset(E_SYS_IPRST eIPRstIdx);
void nu_sys_ipclk_enable(E_SYS_IPCLK eIPClkIdx);
void nu_sys_ipclk_disable(E_SYS_IPCLK eIPClkIdx);
E_SYS_USB0_ID nu_sys_usb0_role(void);

#endif
