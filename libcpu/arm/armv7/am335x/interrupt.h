/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>
#include <stdbool.h>

// [ref]spruh73p.pdf: 6.3 ARM Cortex-A8 Interrupts
#define EMU_INT                 0
#define COMMTX_INT              1
#define COMMRX_INT              2
#define BENCH_INT               3
#define ELM_IRQ_INT             4
#define NMI_INT                 7
#define L3DEBUG_INT             9
#define L3APP_INT               10
#define PRCM_INT                11
#define EDMACOMP_INT            12
#define EDMAMPERR_INT           13
#define EDMAERR_INT             14
#define ADC_TSC_GEN_INT         16
#define USBSS_INT               17
#define USB_INT0                18
#define USB_INT1                19
#define PRU_ICSS_EVTOUT0_INT    20
#define PRU_ICSS_EVTOUT1_INT    21
#define PRU_ICSS_EVTOUT2_INT    22
#define PRU_ICSS_EVTOUT3_INT    23
#define PRU_ICSS_EVTOUT4_INT    24
#define PRU_ICSS_EVTOUT5_INT    25
#define PRU_ICSS_EVTOUT6_INT    26
#define PRU_ICSS_EVTOUT7_INT    27
#define MMCSD1_INT              28
#define MMCSD2_INT              29
#define I2C2_INT                30
#define ECAP0_INT               31
#define GPIO_INT2A              32
#define GPIO_INT2B              33
#define USBWAKEUP_INT           34
#define LCDC_INT                36
#define GFX_INT                 37
#define EPWM2_INT               39
#define CPSW_RXTHR0_INT         40
#define CPSW_RX_INT0            41
#define CPSW_TX_INT0            42
#define CPSW_MISC0_INT          43
#define UART3_INT               44
#define UART4_INT               45
#define UART5_INT               46
#define ECAP1_INT               47
#define DCAN0_INT0              52
#define DCAN0_INT1              53
#define DCAN0_PARITY            54
#define DCAN1_INT0              55
#define DCAN1_INT1              56
#define DCAN1_PARITY            57
#define EPWM0_TZINT             58
#define EPWM1_TZINT             59
#define EPWM2_TZINT             60
#define ECAP2_INT               61
#define GPIO_INT3A              62
#define GPIO_INT3B              63
#define MMCSD0_INT              64
#define MCSPI0_INT              65
#define TINT0                   66
#define TINT1_1MS               67
#define TINT2                   68
#define TINT3                   69
#define I2C0_INT                70
#define I2C1_INT                71
#define UART0_INT               72
#define UART1_INT               73
#define UART2_INT               74
#define RTC_INT                 75
#define RTC_ALARM_INT           76
#define MB_INT0                 77
#define M3_TXEV                 78
#define EQEP0_INT               79
#define MACTX_INT0              80
#define MCARX_INT0              81
#define MCATX_INT1              82
#define MCARX_INT1              83
#define EPWM0_INT               86
#define EPWM1_INT               87
#define EQEP1_INT               88
#define EQEP2_INT               89
#define DMA_INTR_PIN2           90
#define WDT1_INT                91
#define TINT4                   92
#define TINT5                   93
#define TINT6                   94
#define TINT7                   95
#define GPIO_INT0A              96
#define GPIO_INT0B              97
#define GPIO_INT1A              98
#define GPIO_INT1B              99
#define GPMC_INT                100
#define DDRERR0                 101
#define TCERR_INT0              112
#define TCERR_INT1              113
#define TCERR_INT2              114
#define ADC_TSC_PEN_INT         115
#define SMRFLX_MPU              120
#define SMRFLX_CORE             121
#define DMA_INTR_PIN0           123
#define DMA_INTR_PIN1           124
#define MCSPI1_INT              125

#ifdef __cplusplus
extern "C" {
#endif

    void rt_hw_interrupt_control(int32_t vector, int32_t priority, int32_t route);
    uint32_t rt_hw_interrupt_irq_get(void);
    void rt_hw_interrupt_irq_clr(void);
    uint32_t rt_hw_interrupt_fiq_get(void);
    void rt_hw_interrupt_fiq_clr(void);

    void rt_hw_interrupt_trigger(int32_t vector);
    void rt_hw_interrupt_clear(int32_t vector);

#ifdef __cplusplus
}
#endif

#endif
