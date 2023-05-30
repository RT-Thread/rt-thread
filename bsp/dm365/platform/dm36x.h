/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

#ifndef __DM36X_H__
#define __DM36X_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <rtthread.h>
#include "psc.h"
#include "irqs.h"
#include "dm365_timer.h"

/**
 * @addtogroup DM36X
 */
/*@{*/

/*
 * Base register addresses
 */
#define DAVINCI_DMA_3PCC_BASE           (0x01C00000)
#define DAVINCI_DMA_3PTC0_BASE          (0x01C10000)
#define DAVINCI_DMA_3PTC1_BASE          (0x01C10400)
#define DAVINCI_I2C_BASE            (0x01C21000)
#define DAVINCI_TIMER0_BASE         (0x01C21400)
#define DAVINCI_TIMER1_BASE         (0x01C21800)
#define DAVINCI_WDOG_BASE           (0x01C21C00)
#define DAVINCI_PWM0_BASE           (0x01C22000)
#define DAVINCI_PWM1_BASE           (0x01C22400)
#define DAVINCI_PWM2_BASE           (0x01C22800)
#define DAVINCI_SYSTEM_MODULE_BASE      (0x01C40000)
#define DAVINCI_PLL_CNTRL0_BASE         (0x01C40800)
#define DAVINCI_PLL_CNTRL1_BASE         (0x01C40C00)
#define DAVINCI_PWR_SLEEP_CNTRL_BASE        (0x01C41000)
#define DAVINCI_SYSTEM_DFT_BASE         (0x01C42000)
#define DAVINCI_IEEE1394_BASE           (0x01C60000)
#define DAVINCI_USB_OTG_BASE            (0x01C64000)
#define DAVINCI_CFC_ATA_BASE            (0x01C66000)
#define DAVINCI_SPI_BASE            (0x01C66800)
#define DAVINCI_GPIO_BASE           (0x01C67000)
#define DAVINCI_UHPI_BASE           (0x01C67800)
#define DAVINCI_VPSS_REGS_BASE          (0x01C70000)
#define DAVINCI_EMAC_CNTRL_REGS_BASE        (0x01C80000)
#define DAVINCI_EMAC_WRAPPER_CNTRL_REGS_BASE    (0x01C81000)
#define DAVINCI_EMAC_WRAPPER_RAM_BASE       (0x01C82000)
#define DAVINCI_MDIO_CNTRL_REGS_BASE        (0x01C84000)
#define DAVINCI_IMCOP_BASE          (0x01CC0000)
#define DAVINCI_ASYNC_EMIF_CNTRL_BASE       (0x01E00000)
#define DAVINCI_VLYNQ_BASE          (0x01E01000)
#define DAVINCI_MCBSP_BASE          (0x01E02000)
#define DAVINCI_MMC_SD_BASE         (0x01E10000)
#define DAVINCI_MS_BASE             (0x01E20000)
#define DAVINCI_ASYNC_EMIF_DATA_CE0_BASE    (0x02000000)
#define DAVINCI_ASYNC_EMIF_DATA_CE1_BASE    (0x04000000)
#define DAVINCI_ASYNC_EMIF_DATA_CE2_BASE    (0x06000000)
#define DAVINCI_ASYNC_EMIF_DATA_CE3_BASE    (0x08000000)
#define DAVINCI_VLYNQ_REMOTE_BASE       (0x0C000000)


/*
 * We can have multiple VLYNQ IPs in our system.
 * Define 'LOW_VLYNQ_CONTROL_BASE' with the VLYNQ
 * IP having lowest base address.
 * Define 'HIGH_VLYNQ_CONTROL_BASE' with the VLYNQ
 * IP having highest base address.
 * In case of only one VLYNQ IP, define only the
 * 'LOW_VLYNQ_CONTROL_BASE'.
 */
#define LOW_VLYNQ_CONTROL_BASE          DAVINCI_VLYNQ_BASE

#define DM365_EMAC_BASE         (0x01D07000)
#define DM365_EMAC_CNTRL_OFFSET     (0x0000)
#define DM365_EMAC_CNTRL_MOD_OFFSET (0x3000)
#define DM365_EMAC_CNTRL_RAM_OFFSET (0x1000)
#define DM365_EMAC_MDIO_OFFSET      (0x4000)
#define DM365_EMAC_CNTRL_RAM_SIZE   (0x2000)


/*
 * Macro to access device power control
 */
#define DAVINCI_VDD3P3V_PWDN            (DAVINCI_SYSTEM_MODULE_BASE + 0x48)
#define DAVINCI_VSCLKDIS                (DAVINCI_SYSTEM_MODULE_BASE + 0x6c)

/*
 * System module registers
 */
#define PINMUX0     (DAVINCI_SYSTEM_MODULE_BASE + 0x00)
#define PINMUX1     (DAVINCI_SYSTEM_MODULE_BASE + 0x04)
#define PINMUX2     (DAVINCI_SYSTEM_MODULE_BASE + 0x08)
#define PINMUX3     (DAVINCI_SYSTEM_MODULE_BASE + 0x0c)
#define PINMUX4     (DAVINCI_SYSTEM_MODULE_BASE + 0x10)

#define DM365_ARM_INTMUX    (DAVINCI_SYSTEM_MODULE_BASE + 0x18)
#define DM365_EDMA_EVTMUX   (DAVINCI_SYSTEM_MODULE_BASE + 0x1C)
#define DAVINCI_PUPDCTL1    (DAVINCI_SYSTEM_MODULE_BASE + 0x7C)



#define ASYNC_EMIF_REVID    0x00
#define ASYNC_EMIF_AWCCR    0x04
#define ASYNC_EMIF_A1CR     0x10
#define ASYNC_EMIF_A2CR     0x14
#define ASYNC_EMIF_A3CR     0x18

/*
 * Base register addresses common across DM355 and DM365
 */
#define DM3XX_TIMER2_BASE       (0x01C20800)
#define DM3XX_REALTIME_BASE     (0x01C20C00)
#define DM3XX_PWM3_BASE         (0x01C22C00)
#define DM3XX_SPI_BASE          (0x01C66000)
#define DM3XX_SPI0_BASE         DM3XX_SPI_BASE
#define DM3XX_SPI1_BASE         (0x01C66800)
#define DM3XX_SPI2_BASE         (0x01C67800)



/*
 * DM365 base register address
 */
#define DM365_DMA_3PTC2_BASE        (0x01C10800)
#define DM365_DMA_3PTC3_BASE        (0x01C10C00)
#define DM365_TIMER3_BASE       (0x01C23800)
#define DM365_ADCIF_BASE        (0x01C23C00)
#define DM365_SPI3_BASE         (0x01C68000)
#define DM365_SPI4_BASE         (0x01C23000)
#define DM365_RTC_BASE          (0x01C69000)
#define DM365_KEYSCAN_BASE      (0x01C69400)
#define DM365_UHPI_BASE         (0x01C69800)
#define DM365_IMCOP_BASE        (0x01CA0000)
#define DM365_MMC_SD1_BASE      (0x01D00000)
#define DM365_MCBSP_BASE        (0x01D02000)
#define DM365_UART1_BASE        (0x01D06000)
#define DM365_EMAC_CNTRL_BASE       (0x01D07000)
#define DM365_EMAC_WRAP_RAM_BASE    (0x01D08000)
#define DM365_EMAC_WRAP_CNTRL_BASE  (0x01D0A000)
#define DM365_EMAC_MDIO_BASE        (0x01D0B000)
#define DM365_VOICE_CODEC_BASE      (0x01D0C000)
#define DM365_ASYNC_EMIF_CNTRL_BASE (0x01D10000)
#define DM365_MMC_SD0_BASE      (0x01D11000)
#define DM365_MS_BASE           (0x01D20000)
#define DM365_KALEIDO_BASE      (0x01E00000)

#define DAVINCI_UART0_BASE      (0x01C20000)

#define PSC_MDCTL_BASE          (0x01c41a00)
#define PSC_MDSTAT_BASE         (0x01c41800)
#define PSC_PTCMD           (0x01c41120)
#define PSC_PTSTAT          (0x01c41128)

#define DM365_EINT_ENABLE0      0x01c48018
#define DM365_EINT_ENABLE1      0x01c4801c

#define davinci_readb(a)    (*(volatile unsigned char  *)(a))
#define davinci_readw(a)    (*(volatile unsigned short *)(a))
#define davinci_readl(a)    (*(volatile unsigned int   *)(a))

#define davinci_writeb(v,a) (*(volatile unsigned char  *)(a) = (v))
#define davinci_writew(v,a) (*(volatile unsigned short *)(a) = (v))
#define davinci_writel(v,a) (*(volatile unsigned int   *)(a) = (v))

#define readb(a)    davinci_readb(a)
#define readw(a)    davinci_readw(a)
#define readl(a)    davinci_readl(a)

#define write(v,a)  davinci_writeb(v,a)
#define writew(v,a) davinci_writew(v,a)
#define writel(v,a) davinci_writel(v,a)

/* define timer register struct*/
typedef struct timer_regs_s {
    rt_uint32_t pid12;            /* 0x0 */
    rt_uint32_t emumgt_clksped;   /* 0x4 */
    rt_uint32_t gpint_en;         /* 0x8 */
    rt_uint32_t gpdir_dat;        /* 0xC */
    rt_uint32_t tim12;            /* 0x10 */
    rt_uint32_t tim34;            /* 0x14 */
    rt_uint32_t prd12;            /* 0x18 */
    rt_uint32_t prd34;            /* 0x1C */
    rt_uint32_t tcr;              /* 0x20 */
    rt_uint32_t tgcr;             /* 0x24 */
    rt_uint32_t wdtcr;            /* 0x28 */
    rt_uint32_t tlgc;             /* 0x2C */
    rt_uint32_t tlmr;             /* 0x30 */
} timer_regs_t;

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0

struct rt_hw_register
{
    rt_uint32_t cpsr;
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
};

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
