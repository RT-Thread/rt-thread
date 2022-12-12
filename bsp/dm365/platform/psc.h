/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

#ifndef __DM36X_PSC_H
#define __DM36X_PSC_H

#ifdef __cplusplus
extern "C" {
#endif


/* PSC register offsets */
#define EPCPR       0x070
#define PTCMD       0x120
#define PTSTAT      0x128
#define PDSTAT      0x200
#define PDCTL1      0x304
#define MDSTAT(n)   (0x800 + (n) * 4)
#define MDCTL(n)    (0xA00 + (n) * 4)

/* Power and Sleep Controller (PSC) Domains */
#define DAVINCI_GPSC_ARMDOMAIN      0
#define DAVINCI_GPSC_DSPDOMAIN      1


#define DAVINCI_DM365_LPSC_TPCC     0
#define DAVINCI_DM365_LPSC_TPTC0    1
#define DAVINCI_DM365_LPSC_TPTC1    2
#define DAVINCI_DM365_LPSC_TPTC2    3
#define DAVINCI_DM365_LPSC_TPTC3    4
#define DAVINCI_DM365_LPSC_TIMER3   5
#define DAVINCI_DM365_LPSC_SPI1     6
#define DAVINCI_DM365_LPSC_MMC_SD1  7
#define DAVINCI_DM365_LPSC_McBSP    8
#define DAVINCI_DM365_LPSC_USB      9
#define DAVINCI_DM365_LPSC_PWM3     10
#define DAVINCI_DM365_LPSC_SPI2     11
#define DAVINCI_DM365_LPSC_RTO      12
#define DAVINCI_DM365_LPSC_DDR_EMIF 13
#define DAVINCI_DM365_LPSC_AEMIF    14
#define DAVINCI_DM365_LPSC_MMC_SD   15
#define DAVINCI_DM365_LPSC_MMC_SD0  15
#define DAVINCI_DM365_LPSC_MEMSTICK 16
#define DAVINCI_DM365_LPSC_TIMER4   17
#define DAVINCI_DM365_LPSC_I2C      18
#define DAVINCI_DM365_LPSC_UART0    19
#define DAVINCI_DM365_LPSC_UART1    20
#define DAVINCI_DM365_LPSC_UHPI     21
#define DAVINCI_DM365_LPSC_SPI0     22
#define DAVINCI_DM365_LPSC_PWM0     23
#define DAVINCI_DM365_LPSC_PWM1     24
#define DAVINCI_DM365_LPSC_PWM2     25
#define DAVINCI_DM365_LPSC_GPIO     26
#define DAVINCI_DM365_LPSC_TIMER0   27
#define DAVINCI_DM365_LPSC_TIMER1   28
#define DAVINCI_DM365_LPSC_TIMER2   29
#define DAVINCI_DM365_LPSC_SYSTEM_SUBSYS 30
#define DAVINCI_DM365_LPSC_ARM      31
#define DAVINCI_DM365_LPSC_SCR0     33
#define DAVINCI_DM365_LPSC_SCR1     34
#define DAVINCI_DM365_LPSC_EMU      35
#define DAVINCI_DM365_LPSC_CHIPDFT  36
#define DAVINCI_DM365_LPSC_PBIST    37
#define DAVINCI_DM365_LPSC_SPI3     38
#define DAVINCI_DM365_LPSC_SPI4     39
#define DAVINCI_DM365_LPSC_CPGMAC   40
#define DAVINCI_DM365_LPSC_RTC      41
#define DAVINCI_DM365_LPSC_KEYSCAN  42
#define DAVINCI_DM365_LPSC_ADCIF    43
#define DAVINCI_DM365_LPSC_VOICE_CODEC  44
#define DAVINCI_DM365_LPSC_DAC_CLKRES   45
#define DAVINCI_DM365_LPSC_DAC_CLK  46
#define DAVINCI_DM365_LPSC_VPSSMSTR 47
#define DAVINCI_DM365_LPSC_IMCOP    50
#define DAVINCI_DM365_LPSC_KALEIDO  51

#define PSC_ENABLE     3
#define PSC_DISABLE    2
#define PSC_SYNCRESET  1
#define PSC_RESET      0

void psc_change_state(int id, int state);

#ifdef __cplusplus
}
#endif

#endif
