/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SOC_H
#define HPM_SOC_H


/* List of external IRQs */
#define IRQn_GPIO0_A                   1       /* GPIO0_A IRQ */
#define IRQn_GPIO0_B                   2       /* GPIO0_B IRQ */
#define IRQn_GPIO0_C                   3       /* GPIO0_C IRQ */
#define IRQn_GPIO0_D                   4       /* GPIO0_D IRQ */
#define IRQn_GPIO0_E                   5       /* GPIO0_E IRQ */
#define IRQn_GPIO0_F                   6       /* GPIO0_F IRQ */
#define IRQn_GPIO0_V                   7       /* GPIO0_V IRQ */
#define IRQn_GPIO0_W                   8       /* GPIO0_W IRQ */
#define IRQn_GPIO0_X                   9       /* GPIO0_X IRQ */
#define IRQn_GPIO0_Y                   10      /* GPIO0_Y IRQ */
#define IRQn_GPIO0_Z                   11      /* GPIO0_Z IRQ */
#define IRQn_GPIO1_A                   12      /* GPIO1_A IRQ */
#define IRQn_GPIO1_B                   13      /* GPIO1_B IRQ */
#define IRQn_GPIO1_C                   14      /* GPIO1_C IRQ */
#define IRQn_GPIO1_D                   15      /* GPIO1_D IRQ */
#define IRQn_GPIO1_E                   16      /* GPIO1_E IRQ */
#define IRQn_GPIO1_F                   17      /* GPIO1_F IRQ */
#define IRQn_GPIO1_V                   18      /* GPIO1_V IRQ */
#define IRQn_GPIO1_W                   19      /* GPIO1_W IRQ */
#define IRQn_GPIO1_X                   20      /* GPIO1_X IRQ */
#define IRQn_GPIO1_Y                   21      /* GPIO1_Y IRQ */
#define IRQn_GPIO1_Z                   22      /* GPIO1_Z IRQ */
#define IRQn_GPTMR0                    23      /* GPTMR0 IRQ */
#define IRQn_GPTMR1                    24      /* GPTMR1 IRQ */
#define IRQn_GPTMR2                    25      /* GPTMR2 IRQ */
#define IRQn_GPTMR3                    26      /* GPTMR3 IRQ */
#define IRQn_GPTMR4                    27      /* GPTMR4 IRQ */
#define IRQn_GPTMR5                    28      /* GPTMR5 IRQ */
#define IRQn_GPTMR6                    29      /* GPTMR6 IRQ */
#define IRQn_GPTMR7                    30      /* GPTMR7 IRQ */
#define IRQn_UART0                     31      /* UART0 IRQ */
#define IRQn_UART1                     32      /* UART1 IRQ */
#define IRQn_UART2                     33      /* UART2 IRQ */
#define IRQn_UART3                     34      /* UART3 IRQ */
#define IRQn_UART4                     35      /* UART4 IRQ */
#define IRQn_UART5                     36      /* UART5 IRQ */
#define IRQn_UART6                     37      /* UART6 IRQ */
#define IRQn_UART7                     38      /* UART7 IRQ */
#define IRQn_I2C0                      39      /* I2C0 IRQ */
#define IRQn_I2C1                      40      /* I2C1 IRQ */
#define IRQn_I2C2                      41      /* I2C2 IRQ */
#define IRQn_I2C3                      42      /* I2C3 IRQ */
#define IRQn_SPI0                      43      /* SPI0 IRQ */
#define IRQn_SPI1                      44      /* SPI1 IRQ */
#define IRQn_SPI2                      45      /* SPI2 IRQ */
#define IRQn_SPI3                      46      /* SPI3 IRQ */
#define IRQn_TSNS                      47      /* TSNS IRQ */
#define IRQn_MBX0A                     48      /* MBX0A IRQ */
#define IRQn_MBX0B                     49      /* MBX0B IRQ */
#define IRQn_MBX1A                     50      /* MBX1A IRQ */
#define IRQn_MBX1B                     51      /* MBX1B IRQ */
#define IRQn_EWDG0                     52      /* EWDG0 IRQ */
#define IRQn_EWDG1                     53      /* EWDG1 IRQ */
#define IRQn_EWDG2                     54      /* EWDG2 IRQ */
#define IRQn_EWDG3                     55      /* EWDG3 IRQ */
#define IRQn_HDMA                      56      /* HDMA IRQ */
#define IRQn_LOBS                      57      /* LOBS IRQ */
#define IRQn_ADC0                      58      /* ADC0 IRQ */
#define IRQn_ADC1                      59      /* ADC1 IRQ */
#define IRQn_ADC2                      60      /* ADC2 IRQ */
#define IRQn_ADC3                      61      /* ADC3 IRQ */
#define IRQn_ACMP0_0                   62      /* ACMP0[0] IRQ */
#define IRQn_ACMP0_1                   63      /* ACMP0[1] IRQ */
#define IRQn_ACMP1_0                   64      /* ACMP1[0] IRQ */
#define IRQn_ACMP1_1                   65      /* ACMP1[1] IRQ */
#define IRQn_ACMP2_0                   66      /* ACMP2[0] IRQ */
#define IRQn_ACMP2_1                   67      /* ACMP2[1] IRQ */
#define IRQn_ACMP3_0                   68      /* ACMP3[0] IRQ */
#define IRQn_ACMP3_1                   69      /* ACMP3[1] IRQ */
#define IRQn_I2S0                      70      /* I2S0 IRQ */
#define IRQn_I2S1                      71      /* I2S1 IRQ */
#define IRQn_DAO                       72      /* DAO IRQ */
#define IRQn_PDM                       73      /* PDM IRQ */
#define IRQn_UART8                     74      /* UART8 IRQ */
#define IRQn_UART9                     75      /* UART9 IRQ */
#define IRQn_UART10                    76      /* UART10 IRQ */
#define IRQn_UART11                    77      /* UART11 IRQ */
#define IRQn_UART12                    78      /* UART12 IRQ */
#define IRQn_UART13                    79      /* UART13 IRQ */
#define IRQn_UART14                    80      /* UART14 IRQ */
#define IRQn_UART15                    81      /* UART15 IRQ */
#define IRQn_I2C4                      82      /* I2C4 IRQ */
#define IRQn_I2C5                      83      /* I2C5 IRQ */
#define IRQn_I2C6                      84      /* I2C6 IRQ */
#define IRQn_I2C7                      85      /* I2C7 IRQ */
#define IRQn_SPI4                      86      /* SPI4 IRQ */
#define IRQn_SPI5                      87      /* SPI5 IRQ */
#define IRQn_SPI6                      88      /* SPI6 IRQ */
#define IRQn_SPI7                      89      /* SPI7 IRQ */
#define IRQn_MCAN0                     90      /* MCAN0 IRQ */
#define IRQn_MCAN1                     91      /* MCAN1 IRQ */
#define IRQn_MCAN2                     92      /* MCAN2 IRQ */
#define IRQn_MCAN3                     93      /* MCAN3 IRQ */
#define IRQn_MCAN4                     94      /* MCAN4 IRQ */
#define IRQn_MCAN5                     95      /* MCAN5 IRQ */
#define IRQn_MCAN6                     96      /* MCAN6 IRQ */
#define IRQn_MCAN7                     97      /* MCAN7 IRQ */
#define IRQn_PTPC                      98      /* PTPC IRQ */
#define IRQn_QEI0                      99      /* QEI0 IRQ */
#define IRQn_QEI1                      100     /* QEI1 IRQ */
#define IRQn_QEI2                      101     /* QEI2 IRQ */
#define IRQn_QEI3                      102     /* QEI3 IRQ */
#define IRQn_PWM0                      103     /* PWM0 IRQ */
#define IRQn_PWM1                      104     /* PWM1 IRQ */
#define IRQn_PWM2                      105     /* PWM2 IRQ */
#define IRQn_PWM3                      106     /* PWM3 IRQ */
#define IRQn_RDC0                      107     /* RDC0 IRQ */
#define IRQn_RDC1                      108     /* RDC1 IRQ */
#define IRQn_SDM0                      109     /* SDM0 IRQ */
#define IRQn_SDM1                      110     /* SDM1 IRQ */
#define IRQn_SEI_0                     111     /* SEI[0] IRQ */
#define IRQn_SEI_1                     112     /* SEI[1] IRQ */
#define IRQn_SEI_2                     113     /* SEI[2] IRQ */
#define IRQn_SEI_3                     114     /* SEI[3] IRQ */
#define IRQn_MTG0                      115     /* MTG0 IRQ */
#define IRQn_MTG1                      116     /* MTG1 IRQ */
#define IRQn_VSC0                      117     /* VSC0 IRQ */
#define IRQn_VSC1                      118     /* VSC1 IRQ */
#define IRQn_CLC0_0                    119     /* CLC0[0] IRQ */
#define IRQn_CLC0_1                    120     /* CLC0[1] IRQ */
#define IRQn_CLC1_0                    121     /* CLC1[0] IRQ */
#define IRQn_CLC1_1                    122     /* CLC1[1] IRQ */
#define IRQn_TRGMUX0                   123     /* TRGMUX0 IRQ */
#define IRQn_TRGMUX1                   124     /* TRGMUX1 IRQ */
#define IRQn_ENET0                     125     /* ENET0 IRQ */
#define IRQn_NTMR0                     126     /* NTMR0 IRQ */
#define IRQn_USB0                      127     /* USB0 IRQ */
#define IRQn_TSW_0                     128     /* TSW[0] IRQ */
#define IRQn_TSW_1                     129     /* TSW[1] IRQ */
#define IRQn_TSW_2                     130     /* TSW[2] IRQ */
#define IRQn_TSW_3                     131     /* TSW[3] IRQ */
#define IRQn_TSW_PTP_EVT               132     /* TSW_PTP_EVT IRQ */
#define IRQn_ESC                       133     /* ESC IRQ */
#define IRQn_ESC_SYNC0                 134     /* ESC_SYNC0 IRQ */
#define IRQn_ESC_SYNC1                 135     /* ESC_SYNC1 IRQ */
#define IRQn_ESC_RESET                 136     /* ESC_RESET IRQ */
#define IRQn_XPI0                      137     /* XPI0 IRQ */
#define IRQn_FEMC                      138     /* FEMC IRQ */
#define IRQn_PPI                       139     /* PPI IRQ */
#define IRQn_XDMA                      140     /* XDMA IRQ */
#define IRQn_FFA                       141     /* FFA IRQ */
#define IRQn_SDP                       142     /* SDP IRQ */
#define IRQn_RNG                       143     /* RNG IRQ */
#define IRQn_PKA                       144     /* PKA IRQ */
#define IRQn_PSEC                      145     /* PSEC IRQ */
#define IRQn_PGPIO                     146     /* PGPIO IRQ */
#define IRQn_PEWDG                     147     /* PEWDG IRQ */
#define IRQn_PTMR                      148     /* PTMR IRQ */
#define IRQn_PUART                     149     /* PUART IRQ */
#define IRQn_FUSE                      150     /* FUSE IRQ */
#define IRQn_SECMON                    151     /* SECMON IRQ */
#define IRQn_RTC                       152     /* RTC IRQ */
#define IRQn_PAD_WAKEUP                153     /* PAD_WAKEUP IRQ */
#define IRQn_BGPIO                     154     /* BGPIO IRQ */
#define IRQn_BVIO                      155     /* BVIO IRQ */
#define IRQn_BROWNOUT                  156     /* BROWNOUT IRQ */
#define IRQn_SYSCTL                    157     /* SYSCTL IRQ */
#define IRQn_CPU0                      158     /* CPU0 IRQ */
#define IRQn_CPU1                      159     /* CPU1 IRQ */
#define IRQn_DEBUG0                    160     /* DEBUG0 IRQ */
#define IRQn_DEBUG1                    161     /* DEBUG1 IRQ */

#include "hpm_common.h"

#include "hpm_gpio_regs.h"
/* Address of GPIO instances */
/* FGPIO base address */
#define HPM_FGPIO_BASE (0x300000UL)
/* FGPIO base pointer */
#define HPM_FGPIO ((GPIO_Type *) HPM_FGPIO_BASE)
/* GPIO0 base address */
#define HPM_GPIO0_BASE (0xF00D0000UL)
/* GPIO0 base pointer */
#define HPM_GPIO0 ((GPIO_Type *) HPM_GPIO0_BASE)
/* GPIO1 base address */
#define HPM_GPIO1_BASE (0xF00D4000UL)
/* GPIO1 base pointer */
#define HPM_GPIO1 ((GPIO_Type *) HPM_GPIO1_BASE)
/* PGPIO base address */
#define HPM_PGPIO_BASE (0xF411C000UL)
/* PGPIO base pointer */
#define HPM_PGPIO ((GPIO_Type *) HPM_PGPIO_BASE)
/* BGPIO base address */
#define HPM_BGPIO_BASE (0xF4214000UL)
/* BGPIO base pointer */
#define HPM_BGPIO ((GPIO_Type *) HPM_BGPIO_BASE)

/* Address of DM instances */
/* DM base address */
#define HPM_DM_BASE (0x30000000UL)

#include "hpm_plic_regs.h"
/* Address of PLIC instances */
/* PLIC base address */
#define HPM_PLIC_BASE (0xE4000000UL)
/* PLIC base pointer */
#define HPM_PLIC ((PLIC_Type *) HPM_PLIC_BASE)

#include "hpm_mchtmr_regs.h"
/* Address of MCHTMR instances */
/* MCHTMR base address */
#define HPM_MCHTMR_BASE (0xE6000000UL)
/* MCHTMR base pointer */
#define HPM_MCHTMR ((MCHTMR_Type *) HPM_MCHTMR_BASE)

#include "hpm_plic_sw_regs.h"
/* Address of PLICSW instances */
/* PLICSW base address */
#define HPM_PLICSW_BASE (0xE6400000UL)
/* PLICSW base pointer */
#define HPM_PLICSW ((PLIC_SW_Type *) HPM_PLICSW_BASE)

#include "hpm_gptmr_regs.h"
/* Address of GPTMR instances */
/* GPTMR0 base address */
#define HPM_GPTMR0_BASE (0xF0000000UL)
/* GPTMR0 base pointer */
#define HPM_GPTMR0 ((GPTMR_Type *) HPM_GPTMR0_BASE)
/* GPTMR1 base address */
#define HPM_GPTMR1_BASE (0xF0004000UL)
/* GPTMR1 base pointer */
#define HPM_GPTMR1 ((GPTMR_Type *) HPM_GPTMR1_BASE)
/* GPTMR2 base address */
#define HPM_GPTMR2_BASE (0xF0008000UL)
/* GPTMR2 base pointer */
#define HPM_GPTMR2 ((GPTMR_Type *) HPM_GPTMR2_BASE)
/* GPTMR3 base address */
#define HPM_GPTMR3_BASE (0xF000C000UL)
/* GPTMR3 base pointer */
#define HPM_GPTMR3 ((GPTMR_Type *) HPM_GPTMR3_BASE)
/* GPTMR4 base address */
#define HPM_GPTMR4_BASE (0xF0010000UL)
/* GPTMR4 base pointer */
#define HPM_GPTMR4 ((GPTMR_Type *) HPM_GPTMR4_BASE)
/* GPTMR5 base address */
#define HPM_GPTMR5_BASE (0xF0014000UL)
/* GPTMR5 base pointer */
#define HPM_GPTMR5 ((GPTMR_Type *) HPM_GPTMR5_BASE)
/* GPTMR6 base address */
#define HPM_GPTMR6_BASE (0xF0018000UL)
/* GPTMR6 base pointer */
#define HPM_GPTMR6 ((GPTMR_Type *) HPM_GPTMR6_BASE)
/* GPTMR7 base address */
#define HPM_GPTMR7_BASE (0xF001C000UL)
/* GPTMR7 base pointer */
#define HPM_GPTMR7 ((GPTMR_Type *) HPM_GPTMR7_BASE)
/* NTMR0 base address */
#define HPM_NTMR0_BASE (0xF1410000UL)
/* NTMR0 base pointer */
#define HPM_NTMR0 ((GPTMR_Type *) HPM_NTMR0_BASE)
/* NTMR1 base address */
#define HPM_NTMR1_BASE (0xF1414000UL)
/* NTMR1 base pointer */
#define HPM_NTMR1 ((GPTMR_Type *) HPM_NTMR1_BASE)
/* PTMR base address */
#define HPM_PTMR_BASE (0xF4120000UL)
/* PTMR base pointer */
#define HPM_PTMR ((GPTMR_Type *) HPM_PTMR_BASE)

#include "hpm_uart_regs.h"
/* Address of UART instances */
/* UART0 base address */
#define HPM_UART0_BASE (0xF0040000UL)
/* UART0 base pointer */
#define HPM_UART0 ((UART_Type *) HPM_UART0_BASE)
/* UART1 base address */
#define HPM_UART1_BASE (0xF0044000UL)
/* UART1 base pointer */
#define HPM_UART1 ((UART_Type *) HPM_UART1_BASE)
/* UART2 base address */
#define HPM_UART2_BASE (0xF0048000UL)
/* UART2 base pointer */
#define HPM_UART2 ((UART_Type *) HPM_UART2_BASE)
/* UART3 base address */
#define HPM_UART3_BASE (0xF004C000UL)
/* UART3 base pointer */
#define HPM_UART3 ((UART_Type *) HPM_UART3_BASE)
/* UART4 base address */
#define HPM_UART4_BASE (0xF0050000UL)
/* UART4 base pointer */
#define HPM_UART4 ((UART_Type *) HPM_UART4_BASE)
/* UART5 base address */
#define HPM_UART5_BASE (0xF0054000UL)
/* UART5 base pointer */
#define HPM_UART5 ((UART_Type *) HPM_UART5_BASE)
/* UART6 base address */
#define HPM_UART6_BASE (0xF0058000UL)
/* UART6 base pointer */
#define HPM_UART6 ((UART_Type *) HPM_UART6_BASE)
/* UART7 base address */
#define HPM_UART7_BASE (0xF005C000UL)
/* UART7 base pointer */
#define HPM_UART7 ((UART_Type *) HPM_UART7_BASE)
/* UART8 base address */
#define HPM_UART8_BASE (0xF0180000UL)
/* UART8 base pointer */
#define HPM_UART8 ((UART_Type *) HPM_UART8_BASE)
/* UART9 base address */
#define HPM_UART9_BASE (0xF0184000UL)
/* UART9 base pointer */
#define HPM_UART9 ((UART_Type *) HPM_UART9_BASE)
/* UART10 base address */
#define HPM_UART10_BASE (0xF0188000UL)
/* UART10 base pointer */
#define HPM_UART10 ((UART_Type *) HPM_UART10_BASE)
/* UART11 base address */
#define HPM_UART11_BASE (0xF018C000UL)
/* UART11 base pointer */
#define HPM_UART11 ((UART_Type *) HPM_UART11_BASE)
/* UART12 base address */
#define HPM_UART12_BASE (0xF0190000UL)
/* UART12 base pointer */
#define HPM_UART12 ((UART_Type *) HPM_UART12_BASE)
/* UART13 base address */
#define HPM_UART13_BASE (0xF0194000UL)
/* UART13 base pointer */
#define HPM_UART13 ((UART_Type *) HPM_UART13_BASE)
/* UART14 base address */
#define HPM_UART14_BASE (0xF0198000UL)
/* UART14 base pointer */
#define HPM_UART14 ((UART_Type *) HPM_UART14_BASE)
/* UART15 base address */
#define HPM_UART15_BASE (0xF019C000UL)
/* UART15 base pointer */
#define HPM_UART15 ((UART_Type *) HPM_UART15_BASE)
/* PUART base address */
#define HPM_PUART_BASE (0xF4124000UL)
/* PUART base pointer */
#define HPM_PUART ((UART_Type *) HPM_PUART_BASE)

#include "hpm_i2c_regs.h"
/* Address of I2C instances */
/* I2C0 base address */
#define HPM_I2C0_BASE (0xF0060000UL)
/* I2C0 base pointer */
#define HPM_I2C0 ((I2C_Type *) HPM_I2C0_BASE)
/* I2C1 base address */
#define HPM_I2C1_BASE (0xF0064000UL)
/* I2C1 base pointer */
#define HPM_I2C1 ((I2C_Type *) HPM_I2C1_BASE)
/* I2C2 base address */
#define HPM_I2C2_BASE (0xF0068000UL)
/* I2C2 base pointer */
#define HPM_I2C2 ((I2C_Type *) HPM_I2C2_BASE)
/* I2C3 base address */
#define HPM_I2C3_BASE (0xF006C000UL)
/* I2C3 base pointer */
#define HPM_I2C3 ((I2C_Type *) HPM_I2C3_BASE)
/* I2C4 base address */
#define HPM_I2C4_BASE (0xF01A0000UL)
/* I2C4 base pointer */
#define HPM_I2C4 ((I2C_Type *) HPM_I2C4_BASE)
/* I2C5 base address */
#define HPM_I2C5_BASE (0xF01A4000UL)
/* I2C5 base pointer */
#define HPM_I2C5 ((I2C_Type *) HPM_I2C5_BASE)
/* I2C6 base address */
#define HPM_I2C6_BASE (0xF01A8000UL)
/* I2C6 base pointer */
#define HPM_I2C6 ((I2C_Type *) HPM_I2C6_BASE)
/* I2C7 base address */
#define HPM_I2C7_BASE (0xF01AC000UL)
/* I2C7 base pointer */
#define HPM_I2C7 ((I2C_Type *) HPM_I2C7_BASE)

#include "hpm_spi_regs.h"
/* Address of SPI instances */
/* SPI0 base address */
#define HPM_SPI0_BASE (0xF0070000UL)
/* SPI0 base pointer */
#define HPM_SPI0 ((SPI_Type *) HPM_SPI0_BASE)
/* SPI1 base address */
#define HPM_SPI1_BASE (0xF0074000UL)
/* SPI1 base pointer */
#define HPM_SPI1 ((SPI_Type *) HPM_SPI1_BASE)
/* SPI2 base address */
#define HPM_SPI2_BASE (0xF0078000UL)
/* SPI2 base pointer */
#define HPM_SPI2 ((SPI_Type *) HPM_SPI2_BASE)
/* SPI3 base address */
#define HPM_SPI3_BASE (0xF007C000UL)
/* SPI3 base pointer */
#define HPM_SPI3 ((SPI_Type *) HPM_SPI3_BASE)
/* SPI4 base address */
#define HPM_SPI4_BASE (0xF01B0000UL)
/* SPI4 base pointer */
#define HPM_SPI4 ((SPI_Type *) HPM_SPI4_BASE)
/* SPI5 base address */
#define HPM_SPI5_BASE (0xF01B4000UL)
/* SPI5 base pointer */
#define HPM_SPI5 ((SPI_Type *) HPM_SPI5_BASE)
/* SPI6 base address */
#define HPM_SPI6_BASE (0xF01B8000UL)
/* SPI6 base pointer */
#define HPM_SPI6 ((SPI_Type *) HPM_SPI6_BASE)
/* SPI7 base address */
#define HPM_SPI7_BASE (0xF01BC000UL)
/* SPI7 base pointer */
#define HPM_SPI7 ((SPI_Type *) HPM_SPI7_BASE)

#include "hpm_crc_regs.h"
/* Address of CRC instances */
/* CRC base address */
#define HPM_CRC_BASE (0xF0080000UL)
/* CRC base pointer */
#define HPM_CRC ((CRC_Type *) HPM_CRC_BASE)

#include "hpm_tsns_regs.h"
/* Address of TSNS instances */
/* TSNS base address */
#define HPM_TSNS_BASE (0xF0090000UL)
/* TSNS base pointer */
#define HPM_TSNS ((TSNS_Type *) HPM_TSNS_BASE)

#include "hpm_mbx_regs.h"
/* Address of MBX instances */
/* MBX0A base address */
#define HPM_MBX0A_BASE (0xF00A0000UL)
/* MBX0A base pointer */
#define HPM_MBX0A ((MBX_Type *) HPM_MBX0A_BASE)
/* MBX0B base address */
#define HPM_MBX0B_BASE (0xF00A4000UL)
/* MBX0B base pointer */
#define HPM_MBX0B ((MBX_Type *) HPM_MBX0B_BASE)
/* MBX1A base address */
#define HPM_MBX1A_BASE (0xF00A8000UL)
/* MBX1A base pointer */
#define HPM_MBX1A ((MBX_Type *) HPM_MBX1A_BASE)
/* MBX1B base address */
#define HPM_MBX1B_BASE (0xF00AC000UL)
/* MBX1B base pointer */
#define HPM_MBX1B ((MBX_Type *) HPM_MBX1B_BASE)

#include "hpm_ewdg_regs.h"
/* Address of EWDG instances */
/* EWDG0 base address */
#define HPM_EWDG0_BASE (0xF00B0000UL)
/* EWDG0 base pointer */
#define HPM_EWDG0 ((EWDG_Type *) HPM_EWDG0_BASE)
/* EWDG1 base address */
#define HPM_EWDG1_BASE (0xF00B4000UL)
/* EWDG1 base pointer */
#define HPM_EWDG1 ((EWDG_Type *) HPM_EWDG1_BASE)
/* EWDG2 base address */
#define HPM_EWDG2_BASE (0xF00B8000UL)
/* EWDG2 base pointer */
#define HPM_EWDG2 ((EWDG_Type *) HPM_EWDG2_BASE)
/* EWDG3 base address */
#define HPM_EWDG3_BASE (0xF00BC000UL)
/* EWDG3 base pointer */
#define HPM_EWDG3 ((EWDG_Type *) HPM_EWDG3_BASE)
/* PEWDG base address */
#define HPM_PEWDG_BASE (0xF4128000UL)
/* PEWDG base pointer */
#define HPM_PEWDG ((EWDG_Type *) HPM_PEWDG_BASE)

#include "hpm_dmamux_regs.h"
/* Address of DMAMUX instances */
/* DMAMUX base address */
#define HPM_DMAMUX_BASE (0xF00C4000UL)
/* DMAMUX base pointer */
#define HPM_DMAMUX ((DMAMUX_Type *) HPM_DMAMUX_BASE)

#include "hpm_dmav2_regs.h"
/* Address of DMAV2 instances */
/* HDMA base address */
#define HPM_HDMA_BASE (0xF00C8000UL)
/* HDMA base pointer */
#define HPM_HDMA ((DMAV2_Type *) HPM_HDMA_BASE)
/* XDMA base address */
#define HPM_XDMA_BASE (0xF3100000UL)
/* XDMA base pointer */
#define HPM_XDMA ((DMAV2_Type *) HPM_XDMA_BASE)

#include "hpm_ppi_regs.h"
/* Address of PPI instances */
/* PPI base address */
#define HPM_PPI_BASE (0xF00CC000UL)
/* PPI base pointer */
#define HPM_PPI ((PPI_Type *) HPM_PPI_BASE)

#include "hpm_gpiom_regs.h"
/* Address of GPIOM instances */
/* GPIOM base address */
#define HPM_GPIOM_BASE (0xF00D8000UL)
/* GPIOM base pointer */
#define HPM_GPIOM ((GPIOM_Type *) HPM_GPIOM_BASE)

#include "hpm_lobs_regs.h"
/* Address of LOBS instances */
/* LOBS base address */
#define HPM_LOBS_BASE (0xF00DC000UL)
/* LOBS base pointer */
#define HPM_LOBS ((LOBS_Type *) HPM_LOBS_BASE)

#include "hpm_adc16_regs.h"
/* Address of ADC16 instances */
/* ADC0 base address */
#define HPM_ADC0_BASE (0xF0100000UL)
/* ADC0 base pointer */
#define HPM_ADC0 ((ADC16_Type *) HPM_ADC0_BASE)
/* ADC1 base address */
#define HPM_ADC1_BASE (0xF0104000UL)
/* ADC1 base pointer */
#define HPM_ADC1 ((ADC16_Type *) HPM_ADC1_BASE)
/* ADC2 base address */
#define HPM_ADC2_BASE (0xF0108000UL)
/* ADC2 base pointer */
#define HPM_ADC2 ((ADC16_Type *) HPM_ADC2_BASE)
/* ADC3 base address */
#define HPM_ADC3_BASE (0xF010C000UL)
/* ADC3 base pointer */
#define HPM_ADC3 ((ADC16_Type *) HPM_ADC3_BASE)

#include "hpm_acmp_regs.h"
/* Address of ACMP instances */
/* ACMP0 base address */
#define HPM_ACMP0_BASE (0xF0130000UL)
/* ACMP0 base pointer */
#define HPM_ACMP0 ((ACMP_Type *) HPM_ACMP0_BASE)
/* ACMP1 base address */
#define HPM_ACMP1_BASE (0xF0134000UL)
/* ACMP1 base pointer */
#define HPM_ACMP1 ((ACMP_Type *) HPM_ACMP1_BASE)
/* ACMP2 base address */
#define HPM_ACMP2_BASE (0xF0138000UL)
/* ACMP2 base pointer */
#define HPM_ACMP2 ((ACMP_Type *) HPM_ACMP2_BASE)
/* ACMP3 base address */
#define HPM_ACMP3_BASE (0xF013C000UL)
/* ACMP3 base pointer */
#define HPM_ACMP3 ((ACMP_Type *) HPM_ACMP3_BASE)

#include "hpm_i2s_regs.h"
/* Address of I2S instances */
/* I2S0 base address */
#define HPM_I2S0_BASE (0xF0140000UL)
/* I2S0 base pointer */
#define HPM_I2S0 ((I2S_Type *) HPM_I2S0_BASE)
/* I2S1 base address */
#define HPM_I2S1_BASE (0xF0144000UL)
/* I2S1 base pointer */
#define HPM_I2S1 ((I2S_Type *) HPM_I2S1_BASE)

#include "hpm_dao_regs.h"
/* Address of DAO instances */
/* DAO base address */
#define HPM_DAO_BASE (0xF0150000UL)
/* DAO base pointer */
#define HPM_DAO ((DAO_Type *) HPM_DAO_BASE)

#include "hpm_pdm_regs.h"
/* Address of PDM instances */
/* PDM base address */
#define HPM_PDM_BASE (0xF0154000UL)
/* PDM base pointer */
#define HPM_PDM ((PDM_Type *) HPM_PDM_BASE)

#include "hpm_mcan_regs.h"
/* Address of MCAN instances */
/* MCAN0 base address */
#define HPM_MCAN0_BASE (0xF0300000UL)
/* MCAN0 base pointer */
#define HPM_MCAN0 ((MCAN_Type *) HPM_MCAN0_BASE)
/* MCAN1 base address */
#define HPM_MCAN1_BASE (0xF0304000UL)
/* MCAN1 base pointer */
#define HPM_MCAN1 ((MCAN_Type *) HPM_MCAN1_BASE)
/* MCAN2 base address */
#define HPM_MCAN2_BASE (0xF0308000UL)
/* MCAN2 base pointer */
#define HPM_MCAN2 ((MCAN_Type *) HPM_MCAN2_BASE)
/* MCAN3 base address */
#define HPM_MCAN3_BASE (0xF030C000UL)
/* MCAN3 base pointer */
#define HPM_MCAN3 ((MCAN_Type *) HPM_MCAN3_BASE)
/* MCAN4 base address */
#define HPM_MCAN4_BASE (0xF0310000UL)
/* MCAN4 base pointer */
#define HPM_MCAN4 ((MCAN_Type *) HPM_MCAN4_BASE)
/* MCAN5 base address */
#define HPM_MCAN5_BASE (0xF0314000UL)
/* MCAN5 base pointer */
#define HPM_MCAN5 ((MCAN_Type *) HPM_MCAN5_BASE)
/* MCAN6 base address */
#define HPM_MCAN6_BASE (0xF0318000UL)
/* MCAN6 base pointer */
#define HPM_MCAN6 ((MCAN_Type *) HPM_MCAN6_BASE)
/* MCAN7 base address */
#define HPM_MCAN7_BASE (0xF031C000UL)
/* MCAN7 base pointer */
#define HPM_MCAN7 ((MCAN_Type *) HPM_MCAN7_BASE)

#include "hpm_ptpc_regs.h"
/* Address of PTPC instances */
/* PTPC base address */
#define HPM_PTPC_BASE (0xF037C000UL)
/* PTPC base pointer */
#define HPM_PTPC ((PTPC_Type *) HPM_PTPC_BASE)

#include "hpm_qeiv2_regs.h"
/* Address of QEIV2 instances */
/* QEI0 base address */
#define HPM_QEI0_BASE (0xF0400000UL)
/* QEI0 base pointer */
#define HPM_QEI0 ((QEIV2_Type *) HPM_QEI0_BASE)
/* QEI1 base address */
#define HPM_QEI1_BASE (0xF0404000UL)
/* QEI1 base pointer */
#define HPM_QEI1 ((QEIV2_Type *) HPM_QEI1_BASE)
/* QEI2 base address */
#define HPM_QEI2_BASE (0xF0408000UL)
/* QEI2 base pointer */
#define HPM_QEI2 ((QEIV2_Type *) HPM_QEI2_BASE)
/* QEI3 base address */
#define HPM_QEI3_BASE (0xF040C000UL)
/* QEI3 base pointer */
#define HPM_QEI3 ((QEIV2_Type *) HPM_QEI3_BASE)

#include "hpm_qeov2_regs.h"
/* Address of QEOV2 instances */
/* QEO0 base address */
#define HPM_QEO0_BASE (0xF0410000UL)
/* QEO0 base pointer */
#define HPM_QEO0 ((QEOV2_Type *) HPM_QEO0_BASE)
/* QEO1 base address */
#define HPM_QEO1_BASE (0xF0414000UL)
/* QEO1 base pointer */
#define HPM_QEO1 ((QEOV2_Type *) HPM_QEO1_BASE)
/* QEO2 base address */
#define HPM_QEO2_BASE (0xF0418000UL)
/* QEO2 base pointer */
#define HPM_QEO2 ((QEOV2_Type *) HPM_QEO2_BASE)
/* QEO3 base address */
#define HPM_QEO3_BASE (0xF041C000UL)
/* QEO3 base pointer */
#define HPM_QEO3 ((QEOV2_Type *) HPM_QEO3_BASE)

#include "hpm_pwmv2_regs.h"
/* Address of PWMV2 instances */
/* PWM0 base address */
#define HPM_PWM0_BASE (0xF0420000UL)
/* PWM0 base pointer */
#define HPM_PWM0 ((PWMV2_Type *) HPM_PWM0_BASE)
/* PWM1 base address */
#define HPM_PWM1_BASE (0xF0424000UL)
/* PWM1 base pointer */
#define HPM_PWM1 ((PWMV2_Type *) HPM_PWM1_BASE)
/* PWM2 base address */
#define HPM_PWM2_BASE (0xF0428000UL)
/* PWM2 base pointer */
#define HPM_PWM2 ((PWMV2_Type *) HPM_PWM2_BASE)
/* PWM3 base address */
#define HPM_PWM3_BASE (0xF042C000UL)
/* PWM3 base pointer */
#define HPM_PWM3 ((PWMV2_Type *) HPM_PWM3_BASE)

#include "hpm_rdc_regs.h"
/* Address of RDC instances */
/* RDC0 base address */
#define HPM_RDC0_BASE (0xF0440000UL)
/* RDC0 base pointer */
#define HPM_RDC0 ((RDC_Type *) HPM_RDC0_BASE)
/* RDC1 base address */
#define HPM_RDC1_BASE (0xF0444000UL)
/* RDC1 base pointer */
#define HPM_RDC1 ((RDC_Type *) HPM_RDC1_BASE)

#include "hpm_sdm_regs.h"
/* Address of SDM instances */
/* SDM0 base address */
#define HPM_SDM0_BASE (0xF0450000UL)
/* SDM0 base pointer */
#define HPM_SDM0 ((SDM_Type *) HPM_SDM0_BASE)
/* SDM1 base address */
#define HPM_SDM1_BASE (0xF0454000UL)
/* SDM1 base pointer */
#define HPM_SDM1 ((SDM_Type *) HPM_SDM1_BASE)

#include "hpm_plb_regs.h"
/* Address of PLB instances */
/* PLB base address */
#define HPM_PLB_BASE (0xF0460000UL)
/* PLB base pointer */
#define HPM_PLB ((PLB_Type *) HPM_PLB_BASE)

#include "hpm_synt_regs.h"
/* Address of SYNT instances */
/* SYNT base address */
#define HPM_SYNT_BASE (0xF0464000UL)
/* SYNT base pointer */
#define HPM_SYNT ((SYNT_Type *) HPM_SYNT_BASE)

#include "hpm_sei_regs.h"
/* Address of SEI instances */
/* SEI base address */
#define HPM_SEI_BASE (0xF0470000UL)
/* SEI base pointer */
#define HPM_SEI ((SEI_Type *) HPM_SEI_BASE)

#include "hpm_trgm_regs.h"
/* Address of TRGM instances */
/* TRGM0 base address */
#define HPM_TRGM0_BASE (0xF047C000UL)
/* TRGM0 base pointer */
#define HPM_TRGM0 ((TRGM_Type *) HPM_TRGM0_BASE)

#include "hpm_mtg_regs.h"
/* Address of MTG instances */
/* MTG0 base address */
#define HPM_MTG0_BASE (0xF0490000UL)
/* MTG0 base pointer */
#define HPM_MTG0 ((MTG_Type *) HPM_MTG0_BASE)
/* MTG1 base address */
#define HPM_MTG1_BASE (0xF0494000UL)
/* MTG1 base pointer */
#define HPM_MTG1 ((MTG_Type *) HPM_MTG1_BASE)

#include "hpm_vsc_regs.h"
/* Address of VSC instances */
/* VSC0 base address */
#define HPM_VSC0_BASE (0xF04A0000UL)
/* VSC0 base pointer */
#define HPM_VSC0 ((VSC_Type *) HPM_VSC0_BASE)
/* VSC1 base address */
#define HPM_VSC1_BASE (0xF04A4000UL)
/* VSC1 base pointer */
#define HPM_VSC1 ((VSC_Type *) HPM_VSC1_BASE)

#include "hpm_clc_regs.h"
/* Address of CLC instances */
/* CLC0 base address */
#define HPM_CLC0_BASE (0xF04B0000UL)
/* CLC0 base pointer */
#define HPM_CLC0 ((CLC_Type *) HPM_CLC0_BASE)
/* CLC1 base address */
#define HPM_CLC1_BASE (0xF04B4000UL)
/* CLC1 base pointer */
#define HPM_CLC1 ((CLC_Type *) HPM_CLC1_BASE)

#include "hpm_enet_regs.h"
/* Address of ENET instances */
/* ENET0 base address */
#define HPM_ENET0_BASE (0xF1400000UL)
/* ENET0 base pointer */
#define HPM_ENET0 ((ENET_Type *) HPM_ENET0_BASE)
/* ENET1 base address */
#define HPM_ENET1_BASE (0xF1404000UL)
/* ENET1 base pointer */
#define HPM_ENET1 ((ENET_Type *) HPM_ENET1_BASE)

#include "hpm_usb_regs.h"
/* Address of USB instances */
/* USB0 base address */
#define HPM_USB0_BASE (0xF1420000UL)
/* USB0 base pointer */
#define HPM_USB0 ((USB_Type *) HPM_USB0_BASE)

#include "hpm_tsw_regs.h"
/* Address of TSW instances */
/* TSW base address */
#define HPM_TSW_BASE (0xF1600000UL)
/* TSW base pointer */
#define HPM_TSW ((TSW_Type *) HPM_TSW_BASE)

#include "hpm_esc_regs.h"
/* Address of ESC instances */
/* ESC base address */
#define HPM_ESC_BASE (0xF1700000UL)
/* ESC base pointer */
#define HPM_ESC ((ESC_Type *) HPM_ESC_BASE)

#include "hpm_femc_regs.h"
/* Address of FEMC instances */
/* FEMC base address */
#define HPM_FEMC_BASE (0xF300C000UL)
/* FEMC base pointer */
#define HPM_FEMC ((FEMC_Type *) HPM_FEMC_BASE)

/* Address of ROMC instances */
/* ROMC base address */
#define HPM_ROMC_BASE (0xF3104000UL)

#include "hpm_ffa_regs.h"
/* Address of FFA instances */
/* FFA base address */
#define HPM_FFA_BASE (0xF3108000UL)
/* FFA base pointer */
#define HPM_FFA ((FFA_Type *) HPM_FFA_BASE)

#include "hpm_sdp_regs.h"
/* Address of SDP instances */
/* SDP base address */
#define HPM_SDP_BASE (0xF3140000UL)
/* SDP base pointer */
#define HPM_SDP ((SDP_Type *) HPM_SDP_BASE)

#include "hpm_psec_regs.h"
/* Address of PSEC instances */
/* PSEC base address */
#define HPM_PSEC_BASE (0xF3144000UL)
/* PSEC base pointer */
#define HPM_PSEC ((PSEC_Type *) HPM_PSEC_BASE)

#include "hpm_pmon_regs.h"
/* Address of PMON instances */
/* PMON base address */
#define HPM_PMON_BASE (0xF3148000UL)
/* PMON base pointer */
#define HPM_PMON ((PMON_Type *) HPM_PMON_BASE)

#include "hpm_rng_regs.h"
/* Address of RNG instances */
/* RNG base address */
#define HPM_RNG_BASE (0xF314C000UL)
/* RNG base pointer */
#define HPM_RNG ((RNG_Type *) HPM_RNG_BASE)

#include "hpm_keym_regs.h"
/* Address of KEYM instances */
/* KEYM base address */
#define HPM_KEYM_BASE (0xF3154000UL)
/* KEYM base pointer */
#define HPM_KEYM ((KEYM_Type *) HPM_KEYM_BASE)

#include "hpm_otp_regs.h"
/* Address of OTP instances */
/* OTP base address */
#define HPM_OTP_BASE (0xF3158000UL)
/* OTP base pointer */
#define HPM_OTP ((OTP_Type *) HPM_OTP_BASE)

#include "hpm_sysctl_regs.h"
/* Address of SYSCTL instances */
/* SYSCTL base address */
#define HPM_SYSCTL_BASE (0xF4000000UL)
/* SYSCTL base pointer */
#define HPM_SYSCTL ((SYSCTL_Type *) HPM_SYSCTL_BASE)

#include "hpm_ioc_regs.h"
/* Address of IOC instances */
/* IOC base address */
#define HPM_IOC_BASE (0xF4040000UL)
/* IOC base pointer */
#define HPM_IOC ((IOC_Type *) HPM_IOC_BASE)
/* PIOC base address */
#define HPM_PIOC_BASE (0xF4118000UL)
/* PIOC base pointer */
#define HPM_PIOC ((IOC_Type *) HPM_PIOC_BASE)
/* BIOC base address */
#define HPM_BIOC_BASE (0xF4210000UL)
/* BIOC base pointer */
#define HPM_BIOC ((IOC_Type *) HPM_BIOC_BASE)

#include "hpm_pllctlv2_regs.h"
/* Address of PLLCTLV2 instances */
/* PLLCTLV2 base address */
#define HPM_PLLCTLV2_BASE (0xF40C0000UL)
/* PLLCTLV2 base pointer */
#define HPM_PLLCTLV2 ((PLLCTLV2_Type *) HPM_PLLCTLV2_BASE)

#include "hpm_ppor_regs.h"
/* Address of PPOR instances */
/* PPOR base address */
#define HPM_PPOR_BASE (0xF4100000UL)
/* PPOR base pointer */
#define HPM_PPOR ((PPOR_Type *) HPM_PPOR_BASE)

#include "hpm_pcfg_regs.h"
/* Address of PCFG instances */
/* PCFG base address */
#define HPM_PCFG_BASE (0xF4104000UL)
/* PCFG base pointer */
#define HPM_PCFG ((PCFG_Type *) HPM_PCFG_BASE)

#include "hpm_pdgo_regs.h"
/* Address of PDGO instances */
/* PDGO base address */
#define HPM_PDGO_BASE (0xF4134000UL)
/* PDGO base pointer */
#define HPM_PDGO ((PDGO_Type *) HPM_PDGO_BASE)

#include "hpm_pgpr_regs.h"
/* Address of PGPR instances */
/* PGPR0 base address */
#define HPM_PGPR0_BASE (0xF4138000UL)
/* PGPR0 base pointer */
#define HPM_PGPR0 ((PGPR_Type *) HPM_PGPR0_BASE)
/* PGPR1 base address */
#define HPM_PGPR1_BASE (0xF413C000UL)
/* PGPR1 base pointer */
#define HPM_PGPR1 ((PGPR_Type *) HPM_PGPR1_BASE)

#include "hpm_bacc_regs.h"
/* Address of BACC instances */
/* BACC base address */
#define HPM_BACC_BASE (0xF4200000UL)
/* BACC base pointer */
#define HPM_BACC ((BACC_Type *) HPM_BACC_BASE)

#include "hpm_bpor_regs.h"
/* Address of BPOR instances */
/* BPOR base address */
#define HPM_BPOR_BASE (0xF4204000UL)
/* BPOR base pointer */
#define HPM_BPOR ((BPOR_Type *) HPM_BPOR_BASE)

#include "hpm_bcfg_regs.h"
/* Address of BCFG instances */
/* BCFG base address */
#define HPM_BCFG_BASE (0xF4208000UL)
/* BCFG base pointer */
#define HPM_BCFG ((BCFG_Type *) HPM_BCFG_BASE)

#include "hpm_bgpr_regs.h"
/* Address of BGPR instances */
/* BGPR0 base address */
#define HPM_BGPR0_BASE (0xF4218000UL)
/* BGPR0 base pointer */
#define HPM_BGPR0 ((BGPR_Type *) HPM_BGPR0_BASE)
/* BGPR1 base address */
#define HPM_BGPR1_BASE (0xF4220000UL)
/* BGPR1 base pointer */
#define HPM_BGPR1 ((BGPR_Type *) HPM_BGPR1_BASE)

#include "hpm_bsec_regs.h"
/* Address of BSEC instances */
/* BSEC base address */
#define HPM_BSEC_BASE (0xF4240000UL)
/* BSEC base pointer */
#define HPM_BSEC ((BSEC_Type *) HPM_BSEC_BASE)

#include "hpm_rtc_regs.h"
/* Address of RTC instances */
/* RTC base address */
#define HPM_RTC_BASE (0xF4244000UL)
/* RTC base pointer */
#define HPM_RTC ((RTC_Type *) HPM_RTC_BASE)

#include "hpm_bkey_regs.h"
/* Address of BKEY instances */
/* BKEY base address */
#define HPM_BKEY_BASE (0xF4248000UL)
/* BKEY base pointer */
#define HPM_BKEY ((BKEY_Type *) HPM_BKEY_BASE)

#include "hpm_bmon_regs.h"
/* Address of BMON instances */
/* BMON base address */
#define HPM_BMON_BASE (0xF424C000UL)
/* BMON base pointer */
#define HPM_BMON ((BMON_Type *) HPM_BMON_BASE)

#include "hpm_tamp_regs.h"
/* Address of TAMP instances */
/* TAMP base address */
#define HPM_TAMP_BASE (0xF4250000UL)
/* TAMP base pointer */
#define HPM_TAMP ((TAMP_Type *) HPM_TAMP_BASE)

#include "hpm_mono_regs.h"
/* Address of MONO instances */
/* MONO base address */
#define HPM_MONO_BASE (0xF4254000UL)
/* MONO base pointer */
#define HPM_MONO ((MONO_Type *) HPM_MONO_BASE)


#include "riscv/riscv_core.h"
#include "hpm_csr_regs.h"
#include "hpm_interrupt.h"
#include "hpm_misc.h"
#include "hpm_dmamux_src.h"
#include "hpm_trgmmux_src.h"
#include "hpm_iomux.h"
#include "hpm_pmic_iomux.h"
#include "hpm_batt_iomux.h"
#endif /* HPM_SOC_H */
