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
#define IRQn_GPIO0_X                   7       /* GPIO0_X IRQ */
#define IRQn_GPIO0_Y                   8       /* GPIO0_Y IRQ */
#define IRQn_GPIO0_Z                   9       /* GPIO0_Z IRQ */
#define IRQn_MCAN0                     10      /* MCAN0 IRQ */
#define IRQn_MCAN1                     11      /* MCAN1 IRQ */
#define IRQn_MCAN2                     12      /* MCAN2 IRQ */
#define IRQn_MCAN3                     13      /* MCAN3 IRQ */
#define IRQn_MCAN4                     14      /* MCAN4 IRQ */
#define IRQn_MCAN5                     15      /* MCAN5 IRQ */
#define IRQn_MCAN6                     16      /* MCAN6 IRQ */
#define IRQn_MCAN7                     17      /* MCAN7 IRQ */
#define IRQn_PTPC                      18      /* PTPC IRQ */
#define IRQn_UART0                     27      /* UART0 IRQ */
#define IRQn_UART1                     28      /* UART1 IRQ */
#define IRQn_UART2                     29      /* UART2 IRQ */
#define IRQn_UART3                     30      /* UART3 IRQ */
#define IRQn_UART4                     31      /* UART4 IRQ */
#define IRQn_UART5                     32      /* UART5 IRQ */
#define IRQn_UART6                     33      /* UART6 IRQ */
#define IRQn_UART7                     34      /* UART7 IRQ */
#define IRQn_I2C0                      35      /* I2C0 IRQ */
#define IRQn_I2C1                      36      /* I2C1 IRQ */
#define IRQn_I2C2                      37      /* I2C2 IRQ */
#define IRQn_I2C3                      38      /* I2C3 IRQ */
#define IRQn_SPI0                      39      /* SPI0 IRQ */
#define IRQn_SPI1                      40      /* SPI1 IRQ */
#define IRQn_SPI2                      41      /* SPI2 IRQ */
#define IRQn_SPI3                      42      /* SPI3 IRQ */
#define IRQn_GPTMR0                    43      /* GPTMR0 IRQ */
#define IRQn_GPTMR1                    44      /* GPTMR1 IRQ */
#define IRQn_GPTMR2                    45      /* GPTMR2 IRQ */
#define IRQn_GPTMR3                    46      /* GPTMR3 IRQ */
#define IRQn_GPTMR4                    47      /* GPTMR4 IRQ */
#define IRQn_GPTMR5                    48      /* GPTMR5 IRQ */
#define IRQn_GPTMR6                    49      /* GPTMR6 IRQ */
#define IRQn_GPTMR7                    50      /* GPTMR7 IRQ */
#define IRQn_EWDG0                     51      /* EWDG0 IRQ */
#define IRQn_EWDG1                     52      /* EWDG1 IRQ */
#define IRQn_MBX0A                     53      /* MBX0A IRQ */
#define IRQn_MBX0B                     54      /* MBX0B IRQ */
#define IRQn_MBX1A                     55      /* MBX1A IRQ */
#define IRQn_MBX1B                     56      /* MBX1B IRQ */
#define IRQn_RNG                       57      /* RNG IRQ */
#define IRQn_HDMA                      58      /* HDMA IRQ */
#define IRQn_ADC0                      59      /* ADC0 IRQ */
#define IRQn_ADC1                      60      /* ADC1 IRQ */
#define IRQn_SDM                       61      /* SDM IRQ */
#define IRQn_OPAMP                     62      /* OPAMP IRQ */
#define IRQn_I2S0                      63      /* I2S0 IRQ */
#define IRQn_I2S1                      64      /* I2S1 IRQ */
#define IRQn_I2S2                      65      /* I2S2 IRQ */
#define IRQn_I2S3                      66      /* I2S3 IRQ */
#define IRQn_DAO                       67      /* DAO IRQ */
#define IRQn_PDM                       68      /* PDM IRQ */
#define IRQn_SMIX_DMA                  69      /* SMIX_DMA IRQ */
#define IRQn_SMIX_ASRC                 70      /* SMIX_ASRC IRQ */
#define IRQn_CAM0                      71      /* CAM0 IRQ */
#define IRQn_CAM1                      72      /* CAM1 IRQ */
#define IRQn_LCDC                      73      /* LCDC IRQ */
#define IRQn_LCDC1                     74      /* LCDC1 IRQ */
#define IRQn_PDMA                      75      /* PDMA IRQ */
#define IRQn_JPEG                      76      /* JPEG IRQ */
#define IRQn_GWCK0_FUNC                77      /* GWCK0_FUNC IRQ */
#define IRQn_GWCK0_ERR                 78      /* GWCK0_ERR IRQ */
#define IRQn_GWCK1_FUNC                79      /* GWCK1_FUNC IRQ */
#define IRQn_GWCK1_ERR                 80      /* GWCK1_ERR IRQ */
#define IRQn_MIPI_DSI0                 81      /* MIPI_DSI0 IRQ */
#define IRQn_MIPI_DSI1                 82      /* MIPI_DSI1 IRQ */
#define IRQn_MIPI_CSI0                 83      /* MIPI_CSI0 IRQ */
#define IRQn_MIPI_CSI0_AP              84      /* MIPI_CSI0_AP IRQ */
#define IRQn_MIPI_CSI0_DIAG            85      /* MIPI_CSI0_DIAG IRQ */
#define IRQn_MIPI_CSI1_AP              86      /* MIPI_CSI1_AP IRQ */
#define IRQn_MIPI_CSI1_DIAG            87      /* MIPI_CSI1_DIAG IRQ */
#define IRQn_MIPI_CSI1                 88      /* MIPI_CSI1 IRQ */
#define IRQn_LCB0                      89      /* LCB0 IRQ */
#define IRQn_LCB1                      90      /* LCB1 IRQ */
#define IRQn_GPU                       91      /* GPU IRQ */
#define IRQn_ENET0                     92      /* ENET0 IRQ */
#define IRQn_NTMR0                     93      /* NTMR0 IRQ */
#define IRQn_USB0                      94      /* USB0 IRQ */
#define IRQn_SDXC0                     95      /* SDXC0 IRQ */
#define IRQn_SDXC1                     96      /* SDXC1 IRQ */
#define IRQn_SDP                       97      /* SDP IRQ */
#define IRQn_XPI0                      98      /* XPI0 IRQ */
#define IRQn_XDMA                      99      /* XDMA IRQ */
#define IRQn_DDR                       100     /* DDR IRQ */
#define IRQn_FFA                       101     /* FFA IRQ */
#define IRQn_PSEC                      102     /* PSEC IRQ */
#define IRQn_TSNS                      103     /* TSNS IRQ */
#define IRQn_VAD                       104     /* VAD IRQ */
#define IRQn_PGPIO                     105     /* PGPIO IRQ */
#define IRQn_PWDG                      106     /* PWDG IRQ */
#define IRQn_PTMR                      107     /* PTMR IRQ */
#define IRQn_PUART                     108     /* PUART IRQ */
#define IRQn_FUSE                      109     /* FUSE IRQ */
#define IRQn_SECMON                    110     /* SECMON IRQ */
#define IRQn_RTC                       111     /* RTC IRQ */
#define IRQn_BGPIO                     112     /* BGPIO IRQ */
#define IRQn_BVIO                      113     /* BVIO IRQ */
#define IRQn_BROWNOUT                  114     /* BROWNOUT IRQ */
#define IRQn_SYSCTL                    115     /* SYSCTL IRQ */
#define IRQn_DEBUG0                    116     /* DEBUG0 IRQ */
#define IRQn_DEBUG1                    117     /* DEBUG1 IRQ */

#include "hpm_common.h"

#include "hpm_gpio_regs.h"
/* Address of GPIO instances */
/* FGPIO base address */
#define HPM_FGPIO_BASE (0xC0000UL)
/* FGPIO base pointer */
#define HPM_FGPIO ((GPIO_Type *) HPM_FGPIO_BASE)
/* GPIO0 base address */
#define HPM_GPIO0_BASE (0xF00D0000UL)
/* GPIO0 base pointer */
#define HPM_GPIO0 ((GPIO_Type *) HPM_GPIO0_BASE)
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

#include "hpm_crc_regs.h"
/* Address of CRC instances */
/* CRC base address */
#define HPM_CRC_BASE (0xF000C000UL)
/* CRC base pointer */
#define HPM_CRC ((CRC_Type *) HPM_CRC_BASE)

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

#include "hpm_gptmr_regs.h"
/* Address of GPTMR instances */
/* GPTMR0 base address */
#define HPM_GPTMR0_BASE (0xF0080000UL)
/* GPTMR0 base pointer */
#define HPM_GPTMR0 ((GPTMR_Type *) HPM_GPTMR0_BASE)
/* GPTMR1 base address */
#define HPM_GPTMR1_BASE (0xF0084000UL)
/* GPTMR1 base pointer */
#define HPM_GPTMR1 ((GPTMR_Type *) HPM_GPTMR1_BASE)
/* GPTMR2 base address */
#define HPM_GPTMR2_BASE (0xF0088000UL)
/* GPTMR2 base pointer */
#define HPM_GPTMR2 ((GPTMR_Type *) HPM_GPTMR2_BASE)
/* GPTMR3 base address */
#define HPM_GPTMR3_BASE (0xF008C000UL)
/* GPTMR3 base pointer */
#define HPM_GPTMR3 ((GPTMR_Type *) HPM_GPTMR3_BASE)
/* GPTMR4 base address */
#define HPM_GPTMR4_BASE (0xF0090000UL)
/* GPTMR4 base pointer */
#define HPM_GPTMR4 ((GPTMR_Type *) HPM_GPTMR4_BASE)
/* GPTMR5 base address */
#define HPM_GPTMR5_BASE (0xF0094000UL)
/* GPTMR5 base pointer */
#define HPM_GPTMR5 ((GPTMR_Type *) HPM_GPTMR5_BASE)
/* GPTMR6 base address */
#define HPM_GPTMR6_BASE (0xF0098000UL)
/* GPTMR6 base pointer */
#define HPM_GPTMR6 ((GPTMR_Type *) HPM_GPTMR6_BASE)
/* GPTMR7 base address */
#define HPM_GPTMR7_BASE (0xF009C000UL)
/* GPTMR7 base pointer */
#define HPM_GPTMR7 ((GPTMR_Type *) HPM_GPTMR7_BASE)
/* NTMR0 base address */
#define HPM_NTMR0_BASE (0xF1110000UL)
/* NTMR0 base pointer */
#define HPM_NTMR0 ((GPTMR_Type *) HPM_NTMR0_BASE)
/* PTMR base address */
#define HPM_PTMR_BASE (0xF4120000UL)
/* PTMR base pointer */
#define HPM_PTMR ((GPTMR_Type *) HPM_PTMR_BASE)

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
#define HPM_XDMA_BASE (0xF3008000UL)
/* XDMA base pointer */
#define HPM_XDMA ((DMAV2_Type *) HPM_XDMA_BASE)

#include "hpm_gpiom_regs.h"
/* Address of GPIOM instances */
/* GPIOM base address */
#define HPM_GPIOM_BASE (0xF00D8000UL)
/* GPIOM base pointer */
#define HPM_GPIOM ((GPIOM_Type *) HPM_GPIOM_BASE)

#include "hpm_adc16_regs.h"
/* Address of ADC16 instances */
/* ADC0 base address */
#define HPM_ADC0_BASE (0xF00E0000UL)
/* ADC0 base pointer */
#define HPM_ADC0 ((ADC16_Type *) HPM_ADC0_BASE)

#include "hpm_i2s_regs.h"
/* Address of I2S instances */
/* I2S0 base address */
#define HPM_I2S0_BASE (0xF0200000UL)
/* I2S0 base pointer */
#define HPM_I2S0 ((I2S_Type *) HPM_I2S0_BASE)
/* I2S1 base address */
#define HPM_I2S1_BASE (0xF0204000UL)
/* I2S1 base pointer */
#define HPM_I2S1 ((I2S_Type *) HPM_I2S1_BASE)
/* I2S2 base address */
#define HPM_I2S2_BASE (0xF0208000UL)
/* I2S2 base pointer */
#define HPM_I2S2 ((I2S_Type *) HPM_I2S2_BASE)
/* I2S3 base address */
#define HPM_I2S3_BASE (0xF020C000UL)
/* I2S3 base pointer */
#define HPM_I2S3 ((I2S_Type *) HPM_I2S3_BASE)

#include "hpm_dao_regs.h"
/* Address of DAO instances */
/* DAO base address */
#define HPM_DAO_BASE (0xF0210000UL)
/* DAO base pointer */
#define HPM_DAO ((DAO_Type *) HPM_DAO_BASE)

#include "hpm_pdm_regs.h"
/* Address of PDM instances */
/* PDM base address */
#define HPM_PDM_BASE (0xF0214000UL)
/* PDM base pointer */
#define HPM_PDM ((PDM_Type *) HPM_PDM_BASE)

#include "hpm_smix_regs.h"
/* Address of SMIX instances */
/* SMIX base address */
#define HPM_SMIX_BASE (0xF0218000UL)
/* SMIX base pointer */
#define HPM_SMIX ((SMIX_Type *) HPM_SMIX_BASE)

#include "hpm_mcan_regs.h"
/* Address of MCAN instances */
/* MCAN0 base address */
#define HPM_MCAN0_BASE (0xF0280000UL)
/* MCAN0 base pointer */
#define HPM_MCAN0 ((MCAN_Type *) HPM_MCAN0_BASE)
/* MCAN1 base address */
#define HPM_MCAN1_BASE (0xF0284000UL)
/* MCAN1 base pointer */
#define HPM_MCAN1 ((MCAN_Type *) HPM_MCAN1_BASE)
/* MCAN2 base address */
#define HPM_MCAN2_BASE (0xF0288000UL)
/* MCAN2 base pointer */
#define HPM_MCAN2 ((MCAN_Type *) HPM_MCAN2_BASE)
/* MCAN3 base address */
#define HPM_MCAN3_BASE (0xF028C000UL)
/* MCAN3 base pointer */
#define HPM_MCAN3 ((MCAN_Type *) HPM_MCAN3_BASE)
/* MCAN4 base address */
#define HPM_MCAN4_BASE (0xF0290000UL)
/* MCAN4 base pointer */
#define HPM_MCAN4 ((MCAN_Type *) HPM_MCAN4_BASE)
/* MCAN5 base address */
#define HPM_MCAN5_BASE (0xF0294000UL)
/* MCAN5 base pointer */
#define HPM_MCAN5 ((MCAN_Type *) HPM_MCAN5_BASE)
/* MCAN6 base address */
#define HPM_MCAN6_BASE (0xF0298000UL)
/* MCAN6 base pointer */
#define HPM_MCAN6 ((MCAN_Type *) HPM_MCAN6_BASE)
/* MCAN7 base address */
#define HPM_MCAN7_BASE (0xF029C000UL)
/* MCAN7 base pointer */
#define HPM_MCAN7 ((MCAN_Type *) HPM_MCAN7_BASE)

#include "hpm_ptpc_regs.h"
/* Address of PTPC instances */
/* PTPC base address */
#define HPM_PTPC_BASE (0xF02FC000UL)
/* PTPC base pointer */
#define HPM_PTPC ((PTPC_Type *) HPM_PTPC_BASE)

#include "hpm_lcdc_regs.h"
/* Address of LCDC instances */
/* LCDC base address */
#define HPM_LCDC_BASE (0xF1000000UL)
/* LCDC base pointer */
#define HPM_LCDC ((LCDC_Type *) HPM_LCDC_BASE)
/* LCDC1 base address */
#define HPM_LCDC1_BASE (0xF1004000UL)
/* LCDC1 base pointer */
#define HPM_LCDC1 ((LCDC_Type *) HPM_LCDC1_BASE)

#include "hpm_cam_regs.h"
/* Address of CAM instances */
/* CAM0 base address */
#define HPM_CAM0_BASE (0xF1008000UL)
/* CAM0 base pointer */
#define HPM_CAM0 ((CAM_Type *) HPM_CAM0_BASE)
/* CAM1 base address */
#define HPM_CAM1_BASE (0xF100C000UL)
/* CAM1 base pointer */
#define HPM_CAM1 ((CAM_Type *) HPM_CAM1_BASE)

#include "hpm_pdma_regs.h"
/* Address of PDMA instances */
/* PDMA base address */
#define HPM_PDMA_BASE (0xF1010000UL)
/* PDMA base pointer */
#define HPM_PDMA ((PDMA_Type *) HPM_PDMA_BASE)

#include "hpm_jpeg_regs.h"
/* Address of JPEG instances */
/* JPEG base address */
#define HPM_JPEG_BASE (0xF1014000UL)
/* JPEG base pointer */
#define HPM_JPEG ((JPEG_Type *) HPM_JPEG_BASE)

#include "hpm_gwc_regs.h"
/* Address of GWC instances */
/* GWC0 base address */
#define HPM_GWC0_BASE (0xF1018000UL)
/* GWC0 base pointer */
#define HPM_GWC0 ((GWC_Type *) HPM_GWC0_BASE)
/* GWC1 base address */
#define HPM_GWC1_BASE (0xF101C000UL)
/* GWC1 base pointer */
#define HPM_GWC1 ((GWC_Type *) HPM_GWC1_BASE)

#include "hpm_mipi_dsi_regs.h"
/* Address of MIPI_DSI instances */
/* MIPI_DSI0 base address */
#define HPM_MIPI_DSI0_BASE (0xF1020000UL)
/* MIPI_DSI0 base pointer */
#define HPM_MIPI_DSI0 ((MIPI_DSI_Type *) HPM_MIPI_DSI0_BASE)
/* MIPI_DSI1 base address */
#define HPM_MIPI_DSI1_BASE (0xF1024000UL)
/* MIPI_DSI1 base pointer */
#define HPM_MIPI_DSI1 ((MIPI_DSI_Type *) HPM_MIPI_DSI1_BASE)

#include "hpm_mipi_csi_regs.h"
/* Address of MIPI_CSI instances */
/* MIPI_CSI0 base address */
#define HPM_MIPI_CSI0_BASE (0xF1028000UL)
/* MIPI_CSI0 base pointer */
#define HPM_MIPI_CSI0 ((MIPI_CSI_Type *) HPM_MIPI_CSI0_BASE)
/* MIPI_CSI1 base address */
#define HPM_MIPI_CSI1_BASE (0xF102C000UL)
/* MIPI_CSI1 base pointer */
#define HPM_MIPI_CSI1 ((MIPI_CSI_Type *) HPM_MIPI_CSI1_BASE)

#include "hpm_lvb_regs.h"
/* Address of LVB instances */
/* LVB base address */
#define HPM_LVB_BASE (0xF1030000UL)
/* LVB base pointer */
#define HPM_LVB ((LVB_Type *) HPM_LVB_BASE)

#include "hpm_pixelmux_regs.h"
/* Address of PIXELMUX instances */
/* PIXEL_MUX base address */
#define HPM_PIXEL_MUX_BASE (0xF1034000UL)
/* PIXEL_MUX base pointer */
#define HPM_PIXEL_MUX ((PIXELMUX_Type *) HPM_PIXEL_MUX_BASE)

#include "hpm_lcb_regs.h"
/* Address of LCB instances */
/* LCB base address */
#define HPM_LCB_BASE (0xF1038000UL)
/* LCB base pointer */
#define HPM_LCB ((LCB_Type *) HPM_LCB_BASE)

#include "hpm_gpu_regs.h"
/* Address of GPU instances */
/* GPU base address */
#define HPM_GPU_BASE (0xF1080000UL)
/* GPU base pointer */
#define HPM_GPU ((GPU_Type *) HPM_GPU_BASE)

#include "hpm_enet_regs.h"
/* Address of ENET instances */
/* ENET0 base address */
#define HPM_ENET0_BASE (0xF1100000UL)
/* ENET0 base pointer */
#define HPM_ENET0 ((ENET_Type *) HPM_ENET0_BASE)

#include "hpm_usb_regs.h"
/* Address of USB instances */
/* USB0 base address */
#define HPM_USB0_BASE (0xF1120000UL)
/* USB0 base pointer */
#define HPM_USB0 ((USB_Type *) HPM_USB0_BASE)

#include "hpm_sdxc_regs.h"
/* Address of SDXC instances */
/* SDXC0 base address */
#define HPM_SDXC0_BASE (0xF1130000UL)
/* SDXC0 base pointer */
#define HPM_SDXC0 ((SDXC_Type *) HPM_SDXC0_BASE)
/* SDXC1 base address */
#define HPM_SDXC1_BASE (0xF1134000UL)
/* SDXC1 base pointer */
#define HPM_SDXC1 ((SDXC_Type *) HPM_SDXC1_BASE)

#include "hpm_ddrctl_regs.h"
/* Address of DDRCTL instances */
/* DDRCTL base address */
#define HPM_DDRCTL_BASE (0xF3010000UL)
/* DDRCTL base pointer */
#define HPM_DDRCTL ((DDRCTL_Type *) HPM_DDRCTL_BASE)

/* Address of ROMC instances */
/* ROMC base address */
#define HPM_ROMC_BASE (0xF3014000UL)

#include "hpm_ffa_regs.h"
/* Address of FFA instances */
/* FFA base address */
#define HPM_FFA_BASE (0xF3018000UL)
/* FFA base pointer */
#define HPM_FFA ((FFA_Type *) HPM_FFA_BASE)

#include "hpm_sdp_regs.h"
/* Address of SDP instances */
/* SDP base address */
#define HPM_SDP_BASE (0xF3040000UL)
/* SDP base pointer */
#define HPM_SDP ((SDP_Type *) HPM_SDP_BASE)

#include "hpm_sec_regs.h"
/* Address of SEC instances */
/* SEC base address */
#define HPM_SEC_BASE (0xF3044000UL)
/* SEC base pointer */
#define HPM_SEC ((SEC_Type *) HPM_SEC_BASE)

#include "hpm_mon_regs.h"
/* Address of MON instances */
/* MON base address */
#define HPM_MON_BASE (0xF3048000UL)
/* MON base pointer */
#define HPM_MON ((MON_Type *) HPM_MON_BASE)

#include "hpm_rng_regs.h"
/* Address of RNG instances */
/* RNG base address */
#define HPM_RNG_BASE (0xF304C000UL)
/* RNG base pointer */
#define HPM_RNG ((RNG_Type *) HPM_RNG_BASE)

#include "hpm_otp_regs.h"
/* Address of OTP instances */
/* OTP base address */
#define HPM_OTP_BASE (0xF3050000UL)
/* OTP base pointer */
#define HPM_OTP ((OTP_Type *) HPM_OTP_BASE)

#include "hpm_keym_regs.h"
/* Address of KEYM instances */
/* KEYM base address */
#define HPM_KEYM_BASE (0xF3054000UL)
/* KEYM base pointer */
#define HPM_KEYM ((KEYM_Type *) HPM_KEYM_BASE)

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

#include "hpm_pgpr_regs.h"
/* Address of PGPR instances */
/* PGPR0 base address */
#define HPM_PGPR0_BASE (0xF4110000UL)
/* PGPR0 base pointer */
#define HPM_PGPR0 ((PGPR_Type *) HPM_PGPR0_BASE)
/* PGPR1 base address */
#define HPM_PGPR1_BASE (0xF4114000UL)
/* PGPR1 base pointer */
#define HPM_PGPR1 ((PGPR_Type *) HPM_PGPR1_BASE)

#include "hpm_vad_regs.h"
/* Address of VAD instances */
/* VAD base address */
#define HPM_VAD_BASE (0xF412C000UL)
/* VAD base pointer */
#define HPM_VAD ((VAD_Type *) HPM_VAD_BASE)

#include "hpm_mipi_dsi_phy_regs.h"
/* Address of MIPI_DSI_PHY instances */
/* MIPI_DSI_PHY0 base address */
#define HPM_MIPI_DSI_PHY0_BASE (0xF4140000UL)
/* MIPI_DSI_PHY0 base pointer */
#define HPM_MIPI_DSI_PHY0 ((MIPI_DSI_PHY_Type *) HPM_MIPI_DSI_PHY0_BASE)
/* MIPI_DSI_PHY1 base address */
#define HPM_MIPI_DSI_PHY1_BASE (0xF4144000UL)
/* MIPI_DSI_PHY1 base pointer */
#define HPM_MIPI_DSI_PHY1 ((MIPI_DSI_PHY_Type *) HPM_MIPI_DSI_PHY1_BASE)

#include "hpm_mipi_csi_phy_regs.h"
/* Address of MIPI_CSI_PHY instances */
/* MIPI_CSI_PHY0 base address */
#define HPM_MIPI_CSI_PHY0_BASE (0xF4148000UL)
/* MIPI_CSI_PHY0 base pointer */
#define HPM_MIPI_CSI_PHY0 ((MIPI_CSI_PHY_Type *) HPM_MIPI_CSI_PHY0_BASE)
/* MIPI_CSI_PHY1 base address */
#define HPM_MIPI_CSI_PHY1_BASE (0xF414C000UL)
/* MIPI_CSI_PHY1 base pointer */
#define HPM_MIPI_CSI_PHY1 ((MIPI_CSI_PHY_Type *) HPM_MIPI_CSI_PHY1_BASE)

#include "hpm_ddrphy_regs.h"
/* Address of DDRPHY instances */
/* DDRPHY base address */
#define HPM_DDRPHY_BASE (0xF4150000UL)
/* DDRPHY base pointer */
#define HPM_DDRPHY ((DDRPHY_Type *) HPM_DDRPHY_BASE)

#include "hpm_tsns_regs.h"
/* Address of TSNS instances */
/* TSNS base address */
#define HPM_TSNS_BASE (0xF4154000UL)
/* TSNS base pointer */
#define HPM_TSNS ((TSNS_Type *) HPM_TSNS_BASE)

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

#include "hpm_butn_regs.h"
/* Address of BUTN instances */
/* BUTN base address */
#define HPM_BUTN_BASE (0xF420C000UL)
/* BUTN base pointer */
#define HPM_BUTN ((BUTN_Type *) HPM_BUTN_BASE)

#include "hpm_bgpr_regs.h"
/* Address of BGPR instances */
/* BGPR base address */
#define HPM_BGPR_BASE (0xF4218000UL)
/* BGPR base pointer */
#define HPM_BGPR ((BGPR_Type *) HPM_BGPR_BASE)

#include "hpm_rtc_regs.h"
/* Address of RTC instances */
/* RTCSHW base address */
#define HPM_RTCSHW_BASE (0xF421C000UL)
/* RTCSHW base pointer */
#define HPM_RTCSHW ((RTC_Type *) HPM_RTCSHW_BASE)
/* RTC base address */
#define HPM_RTC_BASE (0xF4244000UL)
/* RTC base pointer */
#define HPM_RTC ((RTC_Type *) HPM_RTC_BASE)

#include "hpm_bsec_regs.h"
/* Address of BSEC instances */
/* BSEC base address */
#define HPM_BSEC_BASE (0xF4240000UL)
/* BSEC base pointer */
#define HPM_BSEC ((BSEC_Type *) HPM_BSEC_BASE)

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
#include "hpm_iomux.h"
#include "hpm_pmic_iomux.h"
#include "hpm_batt_iomux.h"
#endif /* HPM_SOC_H */
