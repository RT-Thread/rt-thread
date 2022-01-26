/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */

#ifndef __DM36X_IRQS_H__
#define __DM36X_IRQS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Base address */
#define DAVINCI_ARM_INTC_BASE 0x01C48000

#define DAVINCI_N_AINTC_IRQ 64

/* Interrupt lines */
#define IRQ_VDINT0       0
#define IRQ_VDINT1       1
#define IRQ_VDINT2       2
#define IRQ_HISTINT      3
#define IRQ_H3AINT       4
#define IRQ_PRVUINT      5
#define IRQ_RSZINT       6
#define IRQ_VFOCINT      7
#define IRQ_VENCINT      8
#define IRQ_ASQINT       9
#define IRQ_IMXINT       10
#define IRQ_VLCDINT      11
#define IRQ_USBINT       12
#define IRQ_EMACINT      13

#define IRQ_CCINT0       16
#define IRQ_CCERRINT     17
#define IRQ_TCERRINT0    18
#define IRQ_TCERRINT     19
#define IRQ_PSCIN        20

#define IRQ_IDE          22
#define IRQ_HPIINT       23
#define IRQ_MBXINT       24
#define IRQ_MBRINT       25
#define IRQ_MMCINT       26
#define IRQ_SDIOINT      27
#define IRQ_MSINT        28
#define IRQ_DDRINT       29
#define IRQ_AEMIFINT     30
#define IRQ_VLQINT       31
#define IRQ_TINT0_TINT12 32
#define IRQ_TINT0_TINT34 33
#define IRQ_TINT1_TINT12 34
#define IRQ_TINT1_TINT34 35
#define IRQ_PWMINT0      36
#define IRQ_PWMINT1      37
#define IRQ_PWMINT2      38
#define IRQ_I2C          39
#define IRQ_UARTINT0     40
#define IRQ_UARTINT1     41
#define IRQ_UARTINT2     42
#define IRQ_SPINT0       43
#define IRQ_SPINT1       44

#define IRQ_DSP2ARM0     46
#define IRQ_DSP2ARM1     47
#define IRQ_GPIO0        48
#define IRQ_GPIO1        49
#define IRQ_GPIO2        50
#define IRQ_GPIO3        51
#define IRQ_GPIO4        52
#define IRQ_GPIO5        53
#define IRQ_GPIO6        54
#define IRQ_GPIO7        55
#define IRQ_GPIOBNK0     56
#define IRQ_GPIOBNK1     57
#define IRQ_GPIOBNK2     58
#define IRQ_GPIOBNK3     59
#define IRQ_GPIOBNK4     60
#define IRQ_COMMTX       61
#define IRQ_COMMRX       62
#define IRQ_EMUINT       63

/*
 * Base Interrupts common across DM355 and DM365
 */
#define IRQ_DM3XX_VPSSINT0  0
#define IRQ_DM3XX_VPSSINT1  1
#define IRQ_DM3XX_VPSSINT2  2
#define IRQ_DM3XX_VPSSINT3  3
#define IRQ_DM3XX_VPSSINT4  4
#define IRQ_DM3XX_VPSSINT5  5
#define IRQ_DM3XX_VPSSINT6  6
#define IRQ_DM3XX_VPSSINT7  7
#define IRQ_DM3XX_VPSSINT8  8
#define IRQ_DM3XX_IMCOPINT  11
#define IRQ_DM3XX_RTOINT    13
#define IRQ_DM3XX_TINT4     13
#define IRQ_DM3XX_TINT2_TINT12  13
#define IRQ_DM3XX_TINT5     14
#define IRQ_DM3XX_TINT2_TINT34  14
#define IRQ_DM3XX_TINT6     15
#define IRQ_DM3XX_TINT3_TINT12  15
#define IRQ_DM3XX_SPINT1_0  17
#define IRQ_DM3XX_SPINT1_1  18
#define IRQ_DM3XX_SPINT2_0  19
#define IRQ_DM3XX_SPINT2_1  21
#define IRQ_DM3XX_TINT7     22
#define IRQ_DM3XX_TINT3_TINT34  22
#define IRQ_DM3XX_SDIOINT0  23
#define IRQ_DM3XX_MMCINT0   26
#define IRQ_DM3XX_MSINT     26
#define IRQ_DM3XX_MMCINT1   27
#define IRQ_DM3XX_PWMINT3   28
#define IRQ_DM3XX_SDIOINT1  31
#define IRQ_DM3XX_SPINT0_0  42
#define IRQ_DM3XX_SPINT0_1  43
#define IRQ_DM3XX_GPIO0     44
#define IRQ_DM3XX_GPIO1     45
#define IRQ_DM3XX_GPIO2     46
#define IRQ_DM3XX_GPIO3     47
#define IRQ_DM3XX_GPIO4     48
#define IRQ_DM3XX_GPIO5     49
#define IRQ_DM3XX_GPIO6     50
#define IRQ_DM3XX_GPIO7     51
#define IRQ_DM3XX_GPIO8     52
#define IRQ_DM3XX_GPIO9     53

/* DaVinci DM365-specific Interrupts */
#define IRQ_DM365_INSFINT   7
#define IRQ_DM365_IMXINT1   8
#define IRQ_DM365_IMXINT0   10
#define IRQ_DM365_KLD_ARMINT    10
#define IRQ_DM365_CCERRINT  17
#define IRQ_DM365_TCERRINT0 18
#define IRQ_DM365_SPINT2_0  19
#define IRQ_DM365_PSCINT    20
#define IRQ_DM365_TVINT     20
#define IRQ_DM365_SPINT4_0  21
#define IRQ_DM365_MBXINT    24
#define IRQ_DM365_VCINT     24
#define IRQ_DM365_MBRINT    25
#define IRQ_DM365_TINT9     28
#define IRQ_DM365_TINT4_TINT34  28
#define IRQ_DM365_DDRINT    29
#define IRQ_DM365_RTCINT    29
#define IRQ_DM365_AEMIFINT  30
#define IRQ_DM365_HPIINT    30
#define IRQ_DM365_TINT0     32
#define IRQ_DM365_TINT0_TINT12  32
#define IRQ_DM365_TINT1     33
#define IRQ_DM365_TINT0_TINT34  33
#define IRQ_DM365_TINT2     34
#define IRQ_DM365_TINT1_TINT12  34
#define IRQ_DM365_TINT3     35
#define IRQ_DM365_TINT1_TINT34  35
#define IRQ_DM365_PWMINT2   38
#define IRQ_DM365_TINT8     38
#define IRQ_DM365_TINT4_TINT12  38
#define IRQ_DM365_IICINT    39
#define IRQ_DM365_SPINT3_0  43
#define IRQ_DM365_EMAC_RXTHRESH 52
#define IRQ_DM365_EMAC_RXPULSE  53
#define IRQ_DM365_GPIO10    54
#define IRQ_DM365_EMAC_TXPULSE  54
#define IRQ_DM365_GPIO11    55
#define IRQ_DM365_EMAC_MISCPULSE 55
#define IRQ_DM365_GPIO12    56
#define IRQ_DM365_PWRGIO0   56
#define IRQ_DM365_GPIO13    57
#define IRQ_DM365_PWRGIO1   57
#define IRQ_DM365_GPIO14    58
#define IRQ_DM365_PWRGIO2   58
#define IRQ_DM365_GPIO15    59
#define IRQ_DM365_ADCINT    59
#define IRQ_DM365_KEYINT    60
#define IRQ_DM365_COMMTX    61
#define IRQ_DM365_TCERRINT2 61
#define IRQ_DM365_COMMRX    62
#define IRQ_DM365_TCERRINT3 62


#ifdef __cplusplus
}
#endif

#endif
