/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __AM33XX_H__
#define __AM33XX_H__

#define REG32(x) 	(*((volatile unsigned int *)(x)))
#define REG16(x) 	(*((volatile unsigned short *)(x)))

/** Cache Line size in ARM Cortex-A8.                                         */
#define AM33XX_CACHELINE_SIZE                   (64)

/** @brief Base address of AINTC memory mapped registers                      */
#define AM33XX_AINTC_REGS                       (0x48200000)


/** @brief Base addresses of control module registers                         */
#define AM33XX_CTLM_REGS                        (0x44e10000)

/** @brief Base addresses of USB memory mapped registers                     */
#define AM33XX_USB_0_BASE                       (0x47401400)
#define AM33XX_USB_1_BASE                       (0x47401C00)
/** @brief Base addresses of SPI memory mapped registers                      */
#define AM33XX_SPI_0_REGS                       (0x48030000)
#define AM33XX_SPI_1_REGS                       (0x481A0000)

/** @brief Base addresses of GPIO memory mapped registers                     */
#define AM33XX_GPIO_0_REGS                      (0x44E07000)
#define AM33XX_GPIO_1_REGS                      (0x4804C000)
#define AM33XX_GPIO_2_REGS                      (0x481AC000)
#define AM33XX_GPIO_3_REGS                      (0x481AE000)

/** @brief Base addresses of DMTIMER memory mapped registers                  */
#define AM33XX_DMTIMER_0_REGS                   (0x44E05000)
#define AM33XX_DMTIMER_1_REGS                   (0x44E31000)
#define AM33XX_DMTIMER_2_REGS                   (0x48040000)
#define AM33XX_DMTIMER_3_REGS                   (0x48042000)
#define AM33XX_DMTIMER_4_REGS                   (0x48044000)
#define AM33XX_DMTIMER_5_REGS                   (0x48046000)
#define AM33XX_DMTIMER_6_REGS                   (0x48048000)
#define AM33XX_DMTIMER_7_REGS                   (0x4804A000)

/** @brief Base address of MMC memory mapped registers                        */
#define AM33XX_MMCHS_0_REGS                     (0x48060000)
#define AM33XX_MMCHS_1_REGS                     (0x481D8000)
#define AM33XX_MMCHS_2_REGS                     (0x47810000)

/** @brief Base address of GPMC memory mapped registers                       */
#define AM33XX_GPMC_0_REGS                      (0x50000000)

/** @brief Base address of GPMC memory mapped registers                       */
#define AM33XX_ELM_0_REGS                       (0x48080000)

/** @brief Base address of I2C memory mapped registers                        */
#define AM33XX_I2C_0_REGS                       (0x44E0B000)
#define AM33XX_I2C_1_REGS                       (0x4802A000)
#define AM33XX_I2C_2_REGS                       (0x4819C000)

/** @brief Base address of WDT memory mapped registers                        */
#define AM33XX_WDT_0_REGS                       (0x44E33000)
#define AM33XX_WDT_1_REGS                       (0x44E35000)

/** @brief Base address of WDT memory mapped registers                        */
#define AM33XX_CPSW_SS_REGS                     (0x4A100000)
#define AM33XX_CPSW_MDIO_REGS                   (0x4A101000)
#define AM33XX_CPSW_WR_REGS                     (0x4A101200)
#define AM33XX_CPSW_CPDMA_REGS                  (0x4A100800)
#define AM33XX_CPSW_ALE_REGS                    (0x4A100D00)
#define AM33XX_CPSW_STAT_REGS                   (0x4A100900)
#define AM33XX_CPSW_PORT_0_REGS                 (0x4A100100)
#define AM33XX_CPSW_PORT_1_REGS                 (0x4A100200)
#define AM33XX_CPSW_SLIVER_1_REGS               (0x4A100D80)
#define AM33XX_CPSW_PORT_2_REGS                 (0x4A100300)
#define AM33XX_CPSW_SLIVER_2_REGS               (0x4A100DC0)
#define AM33XX_CPSW_CPPI_RAM_REGS               (0x4A102000)

/** @brief Base address of McASP memory mapped registers                      */
#define AM33XX_MCASP_1_CTRL_REGS                (0x4803C000)
#define AM33XX_MCASP_1_FIFO_REGS                (AM33XX_MCASP_1_CTRL_REGS + 0x1000)
#define AM33XX_MCASP_1_DATA_REGS                (0x46400000)

/** @brief Base address of EMIF memory mapped registers                       */
#define AM33XX_EMIF_0_REGS                      (0x4C000000)

/** @brief Base addresses of RTC memory mapped registers                      */
#define AM33XX_RTC_0_REGS                       (0x44E3E000)

#define CM_PER(base)                      ((base) + 0)
#define CM_PER_L4LS_CLKSTCTRL(base)       (CM_PER(base) + 0)
#define CM_PER_UART1_CLKCTRL(base)        (CM_PER(base) + 0x6C)
#define CM_PER_UART2_CLKCTRL(base)        (CM_PER(base) + 0x70)
#define CM_PER_UART3_CLKCTRL(base)        (CM_PER(base) + 0x74)
#define CM_PER_UART4_CLKCTRL(base)        (CM_PER(base) + 0x78)
#define CM_PER_UART5_CLKCTRL(base)        (CM_PER(base) + 0x38)
#define CM_WKUP(base)                     ((base) + 0x400)
#define CM_DPLL(base)                     ((base) + 0x500)
#define CM_MPU(base)                      ((base) + 0x600)
#define CM_DEVICE(base)                   ((base) + 0x700)
#define CM_RTC(base)                      ((base) + 0x800)
#define CM_GFX(base)                      ((base) + 0x900)
#define CM_CEFUSE(base)                   ((base) + 0xA00)
#define OCP_AM33XXKET_RAM(base)           ((base) + 0xB00)
#define PRM_PER(base)                     ((base) + 0xC00)
#define PRM_PER_PWRSTST(base)             (PRM_PER(base) + 0x008)
#define PRM_PER_PWRSTCTRL(base)           (PRM_PER(base) + 0x00C)
#define PRM_WKUP(base)                    ((base) + 0xD00)
#define PRM_MPU(base)                     ((base) + 0xE00)
#define PRM_DEVICE(base)                  ((base) + 0xF00)
#define PRM_RTC(base)                     ((base) + 0x1000)
#define PRM_GFX(base)                     ((base) + 0x1100)
#define PRM_CEFUSE(base)                  ((base) + 0x1200)

/** @brief Base addresses of PRCM memory mapped registers                     */
#define AM33XX_PRCM_REGS                        (0x44E00000)
#define AM33XX_CM_PER_REGS                      CM_PER(AM33XX_PRCM_REGS)
#define AM33XX_CM_WKUP_REGS                     CM_WKUP(AM33XX_PRCM_REGS)
#define AM33XX_CM_DPLL_REGS                     CM_DPLL(AM33XX_PRCM_REGS)
#define AM33XX_CM_MPU_REGS                      CM_MPU(AM33XX_PRCM_REGS)
#define AM33XX_CM_DEVICE_REGS                   CM_DEVICE(AM33XX_PRCM_REGS)
#define AM33XX_CM_RTC_REGS                      CM_RTC(AM33XX_PRCM_REGS)
#define AM33XX_CM_GFX_REGS                      CM_GFX(AM33XX_PRCM_REGS)
#define AM33XX_CM_CEFUSE_REGS                   CM_CEFUSE(AM33XX_PRCM_REGS)
#define AM33XX_OCP_AM33XXKET_RAM_REGS           OCP_AM33XXKET_RAM(AM33XX_PRCM_REGS)
#define AM33XX_PRM_PER_REGS                     PRM_PER(AM33XX_PRCM_REGS)
#define AM33XX_PRM_WKUP_REGS                    PRM_WKUP(AM33XX_PRCM_REGS)
#define AM33XX_PRM_MPU_REGS                     PRM_MPU(AM33XX_PRCM_REGS)
#define AM33XX_PRM_DEVICE_REGS                  PRM_DEVICE(AM33XX_PRCM_REGS)
#define AM33XX_PRM_RTC_REGS                     PRM_RTC(AM33XX_PRCM_REGS)
#define AM33XX_PRM_GFX_REGS                     PRM_GFX(AM33XX_PRCM_REGS)
#define AM33XX_PRM_CEFUSE_REGS                  PRM_CEFUSE(AM33XX_PRCM_REGS)

/** @brief Base address of control module memory mapped registers             */
#define AM33XX_CONTROL_REGS                     (0x44E10000)


/** @brief Base address of Channel controller  memory mapped registers        */
#define AM33XX_EDMA30CC_0_REGS                  (0x49000000)

/** @brief Base address of DCAN module memory mapped registers                */
#define AM33XX_DCAN_0_REGS                      (0x481CC000)
#define AM33XX_DCAN_1_REGS                      (0x481D0000)

/******************************************************************************\
*  Parameterizable Configuration:- These are fed directly from the RTL
*  parameters for the given AM33XX
\******************************************************************************/
#define TPCC_MUX(n)                             0xF90 + ((n) * 4)


#define AM33XX_LCDC_0_REGS                     0x4830E000

#define AM33XX_ADC_TSC_0_REGS                  0x44E0D000

/** @brief Base addresses of PWMSS memory mapped registers.                   */

#define AM33XX_PWMSS0_REGS                     (0x48300000)
#define AM33XX_PWMSS1_REGS                     (0x48302000)
#define AM33XX_PWMSS2_REGS                     (0x48304000)

#define AM33XX_ECAP_REGS                       (0x00000100)
#define AM33XX_EQEP_REGS                       (0x00000180)
#define AM33XX_EPWM_REGS                       (0x00000200)

#define AM33XX_ECAP_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_ECAP_REGS)
#define AM33XX_ECAP_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_ECAP_REGS)
#define AM33XX_ECAP_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_ECAP_REGS)

#define AM33XX_EQEP_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_EQEP_REGS)
#define AM33XX_EQEP_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_EQEP_REGS)
#define AM33XX_EQEP_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_EQEP_REGS)

#define AM33XX_EPWM_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_EPWM_REGS)
#define AM33XX_EPWM_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_EPWM_REGS)
#define AM33XX_EPWM_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_EPWM_REGS)

#define AM33XX_EPWM_MODULE_FREQ                 100

/* PRCM registers */
#define CM_PER_L4LS_CLKSTCTRL_REG(base)    REG32((base) + 0x0)
#define CM_PER_UART1_CLKCTRL_REG(base)     REG32(CM_PER_UART1_CLKCTRL(base))
#define CM_PER_UART2_CLKCTRL_REG(base)     REG32(CM_PER_UART2_CLKCTRL(base))
#define CM_PER_UART3_CLKCTRL_REG(base)     REG32(CM_PER_UART3_CLKCTRL(base))
#define CM_PER_UART4_CLKCTRL_REG(base)     REG32(CM_PER_UART4_CLKCTRL(base))
#define CM_PER_UART5_CLKCTRL_REG(base)     REG32(CM_PER_UART5_CLKCTRL(base))

#define CM_PER_TIMER7_CLKCTRL(base)        REG32((base) + 0x7C)
#define CM_PER_TIMER2_CLKCTRL(base)        REG32((base) + 0x80)

#define PRM_PER_PWRSTST_REG(base)          REG32(PRM_PER_PWRSTST(base))
#define PRM_PER_PWRSTCTRL_REG(base)        REG32(PRM_PER_PWRSTCTRL(base))

#define CM_DPLL_CLKSEL_TIMER7_CLK(base)    REG32(CM_DPLL(base) + 0x4)
#define CM_DPLL_CLKSEL_TIMER2_CLK(base)    REG32(CM_DPLL(base) + 0x8)

/* timer registers */
#define DMTIMER_TIDR(base)   		REG32(base + 0x0)
#define DMTIMER_TIOCP_CFG(base)   	REG32(base + 0x10)
#define DMTIMER_IRQ_EOI(base)   	REG32(base + 0x20)
#define DMTIMER_IRQSTATUS_RAW(base)	REG32(base + 0x24)
#define DMTIMER_IRQSTATUS(base)   	REG32(base + 0x28)
#define DMTIMER_IRQENABLE_SET(base)	REG32(base + 0x2C)
#define DMTIMER_IRQENABLE_CLR(base)	REG32(base + 0x30)
#define DMTIMER_IRQWAKEEN(base)   	REG32(base + 0x34)
#define DMTIMER_TCLR(base)   		REG32(base + 0x38)
#define DMTIMER_TCRR(base)   		REG32(base + 0x3C)
#define DMTIMER_TLDR(base)   		REG32(base + 0x40)
#define DMTIMER_TTGR(base)   		REG32(base + 0x44)
#define DMTIMER_TWPS(base)   		REG32(base + 0x48)
#define DMTIMER_TMAR(base)   		REG32(base + 0x4C)
#define DMTIMER_TCAR(base, n)		REG32(base + 0x50 + (((n) - 1) * 8))
#define DMTIMER_TSICR(base)   		REG32(base + 0x54)

#define EMU_INT               0
#define COMMTX_INT            1
#define COMMRX_INT            2
#define BENCH_INT             3
#define ELM_IRQ_INT           4
#define NMI_INT               7
#define L3DEBUG_INT           9
#define L3APP_INT             10
#define PRCM_INT              11
#define EDMACOMP_INT          12
#define EDMAMPERR_INT         13
#define EDMAERR_INT           14
#define ADC_TSC_GEN_INT       16
#define USBSS_INT             17
#define USB_INT0              18
#define USB_INT1              19
#define PRU_ICSS_EVTOUT0_INT  20
#define PRU_ICSS_EVTOUT1_INT  21
#define PRU_ICSS_EVTOUT2_INT  22
#define PRU_ICSS_EVTOUT3_INT  23
#define PRU_ICSS_EVTOUT4_INT  24
#define PRU_ICSS_EVTOUT5_INT  25
#define PRU_ICSS_EVTOUT6_INT  26
#define PRU_ICSS_EVTOUT7_INT  27
#define MMCSD1_INT            28
#define MMCSD2_INT            29
#define I2C2_INT              30
#define ECAP0_INT             31
#define GPIO_INT2A            32
#define GPIO_INT2B            33
#define USBWAKEUP_INT         34
#define LCDC_INT              36
#define GFX_INT               37
#define EPWM2_INT             39
#define CPSW_RXTHR0_INT       40
#define CPSW_RX_INT0          41
#define CPSW_TX_INT0          42
#define CPSW_MISC0_INT        43
#define UART3_INT             44
#define UART4_INT             45
#define UART5_INT             46
#define ECAP1_INT             47
#define DCAN0_INT0            52
#define DCAN0_INT1            53
#define DCAN0_PARITY          54
#define DCAN1_INT0            55
#define DCAN1_INT1            56
#define DCAN1_PARITY          57
#define EPWM0_TZINT           58
#define EPWM1_TZINT           59
#define EPWM2_TZINT           60
#define ECAP2_INT             61
#define GPIO_INT3A            62
#define GPIO_INT3B            63
#define MMCSD0_INT            64
#define MCSPI0_INT            65
#define TINT0                 66
#define TINT1_1MS             67
#define TINT2                 68
#define TINT3                 69
#define I2C0_INT              70
#define I2C1_INT              71
#define UART0_INT             72
#define UART1_INT             73
#define UART2_INT             74
#define RTC_INT               75
#define RTC_ALARM_INT         76
#define MB_INT0               77
#define M3_TXEV               78
#define EQEP0_INT             79
#define MACTX_INT0            80
#define MCARX_INT0            81
#define MCATX_INT1            82
#define MCARX_INT1            83
#define EPWM0_INT             86
#define EPWM1_INT             87
#define EQEP1_INT             88
#define EQEP2_INT             89
#define DMA_INTR_PIN2         90
#define WDT1_INT              91
#define TINT4                 92
#define TINT5                 93
#define TINT6                 94
#define TINT7                 95
#define GPIO_INT0A            96
#define GPIO_INT0B            97
#define GPIO_INT1A            98
#define GPIO_INT1B            99
#define GPMC_INT              100
#define DDRERR0               101
#define TCERR_INT0            112
#define TCERR_INT1            113
#define TCERR_INT2            114
#define ADC_TSC_PEN_INT       115
#define SMRFLX_MPU            120
#define SMRFLX_CORE           121
#define DMA_INTR_PIN0         123
#define DMA_INTR_PIN1         124
#define MCSPI1_INT            125

struct rt_hw_register
{
	unsigned long r0;
	unsigned long r1;
	unsigned long r2;
	unsigned long r3;
	unsigned long r4;
	unsigned long r5;
	unsigned long r6;
	unsigned long r7;
	unsigned long r8;
	unsigned long r9;
	unsigned long r10;
	unsigned long fp;
	unsigned long ip;
	unsigned long sp;
	unsigned long lr;
	unsigned long pc;
	unsigned long cpsr;
	unsigned long ORIG_r0;
};

#define USERMODE	0x10
#define FIQMODE		0x11
#define IRQMODE		0x12
#define SVCMODE		0x13
#define ABORTMODE	0x17
#define UNDEFMODE	0x1b
#define MODEMASK	0x1f
#define NOINT		0xc0

#endif
