/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SOC_H
#define HPM_SOC_H


/* List of external IRQs */
#define IRQn_GPIO0_A       1                   /* GPIO0_A IRQ */
#define IRQn_GPIO0_B       2                   /* GPIO0_B IRQ */
#define IRQn_GPIO0_C       3                   /* GPIO0_C IRQ */
#define IRQn_GPIO0_D       4                   /* GPIO0_D IRQ */
#define IRQn_GPIO0_X       5                   /* GPIO0_X IRQ */
#define IRQn_GPIO0_Y       6                   /* GPIO0_Y IRQ */
#define IRQn_GPIO0_Z       7                   /* GPIO0_Z IRQ */
#define IRQn_GPIO1_A       8                   /* GPIO1_A IRQ */
#define IRQn_GPIO1_B       9                   /* GPIO1_B IRQ */
#define IRQn_GPIO1_C       10                  /* GPIO1_C IRQ */
#define IRQn_GPIO1_D       11                  /* GPIO1_D IRQ */
#define IRQn_GPIO1_X       12                  /* GPIO1_X IRQ */
#define IRQn_GPIO1_Y       13                  /* GPIO1_Y IRQ */
#define IRQn_GPIO1_Z       14                  /* GPIO1_Z IRQ */
#define IRQn_ADC0          15                  /* ADC0 IRQ */
#define IRQn_ADC1          16                  /* ADC1 IRQ */
#define IRQn_ADC2          17                  /* ADC2 IRQ */
#define IRQn_SDFM          18                  /* SDFM IRQ */
#define IRQn_DAC0          19                  /* DAC0 IRQ */
#define IRQn_DAC1          20                  /* DAC1 IRQ */
#define IRQn_ACMP_0        21                  /* ACMP[0] IRQ */
#define IRQn_ACMP_1        22                  /* ACMP[1] IRQ */
#define IRQn_ACMP_2        23                  /* ACMP[2] IRQ */
#define IRQn_ACMP_3        24                  /* ACMP[3] IRQ */
#define IRQn_SPI0          25                  /* SPI0 IRQ */
#define IRQn_SPI1          26                  /* SPI1 IRQ */
#define IRQn_SPI2          27                  /* SPI2 IRQ */
#define IRQn_SPI3          28                  /* SPI3 IRQ */
#define IRQn_UART0         29                  /* UART0 IRQ */
#define IRQn_UART1         30                  /* UART1 IRQ */
#define IRQn_UART2         31                  /* UART2 IRQ */
#define IRQn_UART3         32                  /* UART3 IRQ */
#define IRQn_UART4         33                  /* UART4 IRQ */
#define IRQn_UART5         34                  /* UART5 IRQ */
#define IRQn_UART6         35                  /* UART6 IRQ */
#define IRQn_UART7         36                  /* UART7 IRQ */
#define IRQn_CAN0          37                  /* CAN0 IRQ */
#define IRQn_CAN1          38                  /* CAN1 IRQ */
#define IRQn_CAN2          39                  /* CAN2 IRQ */
#define IRQn_CAN3          40                  /* CAN3 IRQ */
#define IRQn_PTPC          41                  /* PTPC IRQ */
#define IRQn_WDG0          42                  /* WDG0 IRQ */
#define IRQn_WDG1          43                  /* WDG1 IRQ */
#define IRQn_TSNS          44                  /* TSNS IRQ */
#define IRQn_MBX0A         45                  /* MBX0A IRQ */
#define IRQn_MBX0B         46                  /* MBX0B IRQ */
#define IRQn_MBX1A         47                  /* MBX1A IRQ */
#define IRQn_MBX1B         48                  /* MBX1B IRQ */
#define IRQn_GPTMR0        49                  /* GPTMR0 IRQ */
#define IRQn_GPTMR1        50                  /* GPTMR1 IRQ */
#define IRQn_GPTMR2        51                  /* GPTMR2 IRQ */
#define IRQn_GPTMR3        52                  /* GPTMR3 IRQ */
#define IRQn_I2C0          53                  /* I2C0 IRQ */
#define IRQn_I2C1          54                  /* I2C1 IRQ */
#define IRQn_I2C2          55                  /* I2C2 IRQ */
#define IRQn_I2C3          56                  /* I2C3 IRQ */
#define IRQn_PWM0          57                  /* PWM0 IRQ */
#define IRQn_HALL0         58                  /* HALL0 IRQ */
#define IRQn_QEI0          59                  /* QEI0 IRQ */
#define IRQn_PWM1          60                  /* PWM1 IRQ */
#define IRQn_HALL1         61                  /* HALL1 IRQ */
#define IRQn_QEI1          62                  /* QEI1 IRQ */
#define IRQn_PWM2          63                  /* PWM2 IRQ */
#define IRQn_HALL2         64                  /* HALL2 IRQ */
#define IRQn_QEI2          65                  /* QEI2 IRQ */
#define IRQn_PWM3          66                  /* PWM3 IRQ */
#define IRQn_HALL3         67                  /* HALL3 IRQ */
#define IRQn_QEI3          68                  /* QEI3 IRQ */
#define IRQn_SDP           69                  /* SDP IRQ */
#define IRQn_XPI0          70                  /* XPI0 IRQ */
#define IRQn_XDMA          71                  /* XDMA IRQ */
#define IRQn_HDMA          72                  /* HDMA IRQ */
#define IRQn_RNG           73                  /* RNG IRQ */
#define IRQn_USB0          74                  /* USB0 IRQ */
#define IRQn_PSEC          75                  /* PSEC IRQ */
#define IRQn_PGPIO         76                  /* PGPIO IRQ */
#define IRQn_PWDG          77                  /* PWDG IRQ */
#define IRQn_PTMR          78                  /* PTMR IRQ */
#define IRQn_PUART         79                  /* PUART IRQ */
#define IRQn_FUSE          80                  /* FUSE IRQ */
#define IRQn_SECMON        81                  /* SECMON IRQ */
#define IRQn_RTC           82                  /* RTC IRQ */
#define IRQn_BUTN          83                  /* BUTN IRQ */
#define IRQn_BGPIO         84                  /* BGPIO IRQ */
#define IRQn_BVIO          85                  /* BVIO IRQ */
#define IRQn_BROWNOUT      86                  /* BROWNOUT IRQ */
#define IRQn_SYSCTL        87                  /* SYSCTL IRQ */
#define IRQn_DEBUG_0       88                  /* DEBUG[0] IRQ */
#define IRQn_DEBUG_1       89                  /* DEBUG[1] IRQ */
#define IRQn_LIN0          90                  /* LIN0 IRQ */
#define IRQn_LIN1          91                  /* LIN1 IRQ */
#define IRQn_LIN2          92                  /* LIN2 IRQ */
#define IRQn_LIN3          93                  /* LIN3 IRQ */

#include "hpm_common.h"

#include "hpm_gpio_regs.h"
/* Address of GPIO instances */
/* FGPIO base address */
#define HPM_FGPIO_BASE (0xC0000UL)
/* FGPIO base pointer */
#define HPM_FGPIO ((GPIO_Type *) HPM_FGPIO_BASE)
/* GPIO0 base address */
#define HPM_GPIO0_BASE (0xF0000000UL)
/* GPIO0 base pointer */
#define HPM_GPIO0 ((GPIO_Type *) HPM_GPIO0_BASE)
/* GPIO1 base address */
#define HPM_GPIO1_BASE (0xF0004000UL)
/* GPIO1 base pointer */
#define HPM_GPIO1 ((GPIO_Type *) HPM_GPIO1_BASE)
/* PGPIO base address */
#define HPM_PGPIO_BASE (0xF40DC000UL)
/* PGPIO base pointer */
#define HPM_PGPIO ((GPIO_Type *) HPM_PGPIO_BASE)
/* BGPIO base address */
#define HPM_BGPIO_BASE (0xF5014000UL)
/* BGPIO base pointer */
#define HPM_BGPIO ((GPIO_Type *) HPM_BGPIO_BASE)

/* Address of DM instances */
/* DM base address */
#define HPM_DM_BASE (0x30000000UL)

/* Address of XBUS_SOC instances */
/* GPV_SOC base address */
#define HPM_GPV_SOC_BASE (0x30100000UL)

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

#include "hpm_gpiom_regs.h"
/* Address of GPIOM instances */
/* GPIOM base address */
#define HPM_GPIOM_BASE (0xF0008000UL)
/* GPIOM base pointer */
#define HPM_GPIOM ((GPIOM_Type *) HPM_GPIOM_BASE)

#include "hpm_adc16_regs.h"
/* Address of ADC16 instances */
/* ADC0 base address */
#define HPM_ADC0_BASE (0xF0010000UL)
/* ADC0 base pointer */
#define HPM_ADC0 ((ADC16_Type *) HPM_ADC0_BASE)
/* ADC1 base address */
#define HPM_ADC1_BASE (0xF0014000UL)
/* ADC1 base pointer */
#define HPM_ADC1 ((ADC16_Type *) HPM_ADC1_BASE)
/* ADC2 base address */
#define HPM_ADC2_BASE (0xF0018000UL)
/* ADC2 base pointer */
#define HPM_ADC2 ((ADC16_Type *) HPM_ADC2_BASE)

#include "hpm_sdm_regs.h"
/* Address of SDM instances */
/* SDM base address */
#define HPM_SDM_BASE (0xF001C000UL)
/* SDM base pointer */
#define HPM_SDM ((SDM_Type *) HPM_SDM_BASE)

#include "hpm_acmp_regs.h"
/* Address of ACMP instances */
/* ACMP base address */
#define HPM_ACMP_BASE (0xF0020000UL)
/* ACMP base pointer */
#define HPM_ACMP ((ACMP_Type *) HPM_ACMP_BASE)

#include "hpm_dac_regs.h"
/* Address of DAC instances */
/* DAC0 base address */
#define HPM_DAC0_BASE (0xF0024000UL)
/* DAC0 base pointer */
#define HPM_DAC0 ((DAC_Type *) HPM_DAC0_BASE)
/* DAC1 base address */
#define HPM_DAC1_BASE (0xF0028000UL)
/* DAC1 base pointer */
#define HPM_DAC1 ((DAC_Type *) HPM_DAC1_BASE)

#include "hpm_spi_regs.h"
/* Address of SPI instances */
/* SPI0 base address */
#define HPM_SPI0_BASE (0xF0030000UL)
/* SPI0 base pointer */
#define HPM_SPI0 ((SPI_Type *) HPM_SPI0_BASE)
/* SPI1 base address */
#define HPM_SPI1_BASE (0xF0034000UL)
/* SPI1 base pointer */
#define HPM_SPI1 ((SPI_Type *) HPM_SPI1_BASE)
/* SPI2 base address */
#define HPM_SPI2_BASE (0xF0038000UL)
/* SPI2 base pointer */
#define HPM_SPI2 ((SPI_Type *) HPM_SPI2_BASE)
/* SPI3 base address */
#define HPM_SPI3_BASE (0xF003C000UL)
/* SPI3 base pointer */
#define HPM_SPI3 ((SPI_Type *) HPM_SPI3_BASE)

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
#define HPM_PUART_BASE (0xF40E4000UL)
/* PUART base pointer */
#define HPM_PUART ((UART_Type *) HPM_PUART_BASE)

#include "hpm_mcan_regs.h"
/* Address of MCAN instances */
/* MCAN0 base address */
#define HPM_MCAN0_BASE (0xF0080000UL)
/* MCAN0 base pointer */
#define HPM_MCAN0 ((MCAN_Type *) HPM_MCAN0_BASE)
/* MCAN1 base address */
#define HPM_MCAN1_BASE (0xF0084000UL)
/* MCAN1 base pointer */
#define HPM_MCAN1 ((MCAN_Type *) HPM_MCAN1_BASE)
/* MCAN2 base address */
#define HPM_MCAN2_BASE (0xF0088000UL)
/* MCAN2 base pointer */
#define HPM_MCAN2 ((MCAN_Type *) HPM_MCAN2_BASE)
/* MCAN3 base address */
#define HPM_MCAN3_BASE (0xF008C000UL)
/* MCAN3 base pointer */
#define HPM_MCAN3 ((MCAN_Type *) HPM_MCAN3_BASE)

#include "hpm_wdg_regs.h"
/* Address of WDOG instances */
/* WDG0 base address */
#define HPM_WDG0_BASE (0xF0090000UL)
/* WDG0 base pointer */
#define HPM_WDG0 ((WDG_Type *) HPM_WDG0_BASE)
/* WDG1 base address */
#define HPM_WDG1_BASE (0xF0094000UL)
/* WDG1 base pointer */
#define HPM_WDG1 ((WDG_Type *) HPM_WDG1_BASE)
/* PWDG base address */
#define HPM_PWDG_BASE (0xF40E8000UL)
/* PWDG base pointer */
#define HPM_PWDG ((WDG_Type *) HPM_PWDG_BASE)

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

#include "hpm_ptpc_regs.h"
/* Address of PTPC instances */
/* PTPC base address */
#define HPM_PTPC_BASE (0xF00B0000UL)
/* PTPC base pointer */
#define HPM_PTPC ((PTPC_Type *) HPM_PTPC_BASE)

#include "hpm_crc_regs.h"
/* Address of CRC instances */
/* CRC base address */
#define HPM_CRC_BASE (0xF00B8000UL)
/* CRC base pointer */
#define HPM_CRC ((CRC_Type *) HPM_CRC_BASE)

#include "hpm_dmamux_regs.h"
/* Address of DMAMUX instances */
/* DMAMUX base address */
#define HPM_DMAMUX_BASE (0xF00C0000UL)
/* DMAMUX base pointer */
#define HPM_DMAMUX ((DMAMUX_Type *) HPM_DMAMUX_BASE)

#include "hpm_dma_regs.h"
/* Address of DMA instances */
/* HDMA base address */
#define HPM_HDMA_BASE (0xF00C4000UL)
/* HDMA base pointer */
#define HPM_HDMA ((DMA_Type *) HPM_HDMA_BASE)
/* XDMA base address */
#define HPM_XDMA_BASE (0xF3048000UL)
/* XDMA base pointer */
#define HPM_XDMA ((DMA_Type *) HPM_XDMA_BASE)

#include "hpm_rng_regs.h"
/* Address of RNG instances */
/* RNG base address */
#define HPM_RNG_BASE (0xF00C8000UL)
/* RNG base pointer */
#define HPM_RNG ((RNG_Type *) HPM_RNG_BASE)

#include "hpm_keym_regs.h"
/* Address of KEYM instances */
/* KEYM base address */
#define HPM_KEYM_BASE (0xF00CC000UL)
/* KEYM base pointer */
#define HPM_KEYM ((KEYM_Type *) HPM_KEYM_BASE)

#include "hpm_pwm_regs.h"
/* Address of PWM instances */
/* PWM0 base address */
#define HPM_PWM0_BASE (0xF0200000UL)
/* PWM0 base pointer */
#define HPM_PWM0 ((PWM_Type *) HPM_PWM0_BASE)
/* PWM1 base address */
#define HPM_PWM1_BASE (0xF0210000UL)
/* PWM1 base pointer */
#define HPM_PWM1 ((PWM_Type *) HPM_PWM1_BASE)
/* PWM2 base address */
#define HPM_PWM2_BASE (0xF0220000UL)
/* PWM2 base pointer */
#define HPM_PWM2 ((PWM_Type *) HPM_PWM2_BASE)
/* PWM3 base address */
#define HPM_PWM3_BASE (0xF0230000UL)
/* PWM3 base pointer */
#define HPM_PWM3 ((PWM_Type *) HPM_PWM3_BASE)

#include "hpm_hall_regs.h"
/* Address of HALL instances */
/* HALL0 base address */
#define HPM_HALL0_BASE (0xF0204000UL)
/* HALL0 base pointer */
#define HPM_HALL0 ((HALL_Type *) HPM_HALL0_BASE)
/* HALL1 base address */
#define HPM_HALL1_BASE (0xF0214000UL)
/* HALL1 base pointer */
#define HPM_HALL1 ((HALL_Type *) HPM_HALL1_BASE)
/* HALL2 base address */
#define HPM_HALL2_BASE (0xF0224000UL)
/* HALL2 base pointer */
#define HPM_HALL2 ((HALL_Type *) HPM_HALL2_BASE)
/* HALL3 base address */
#define HPM_HALL3_BASE (0xF0234000UL)
/* HALL3 base pointer */
#define HPM_HALL3 ((HALL_Type *) HPM_HALL3_BASE)

#include "hpm_qei_regs.h"
/* Address of QEI instances */
/* QEI0 base address */
#define HPM_QEI0_BASE (0xF0208000UL)
/* QEI0 base pointer */
#define HPM_QEI0 ((QEI_Type *) HPM_QEI0_BASE)
/* QEI1 base address */
#define HPM_QEI1_BASE (0xF0218000UL)
/* QEI1 base pointer */
#define HPM_QEI1 ((QEI_Type *) HPM_QEI1_BASE)
/* QEI2 base address */
#define HPM_QEI2_BASE (0xF0228000UL)
/* QEI2 base pointer */
#define HPM_QEI2 ((QEI_Type *) HPM_QEI2_BASE)
/* QEI3 base address */
#define HPM_QEI3_BASE (0xF0238000UL)
/* QEI3 base pointer */
#define HPM_QEI3 ((QEI_Type *) HPM_QEI3_BASE)

#include "hpm_trgm_regs.h"
/* Address of TRGM instances */
/* TRGM0 base address */
#define HPM_TRGM0_BASE (0xF020C000UL)
/* TRGM0 base pointer */
#define HPM_TRGM0 ((TRGM_Type *) HPM_TRGM0_BASE)
/* TRGM1 base address */
#define HPM_TRGM1_BASE (0xF021C000UL)
/* TRGM1 base pointer */
#define HPM_TRGM1 ((TRGM_Type *) HPM_TRGM1_BASE)
/* TRGM2 base address */
#define HPM_TRGM2_BASE (0xF022C000UL)
/* TRGM2 base pointer */
#define HPM_TRGM2 ((TRGM_Type *) HPM_TRGM2_BASE)
/* TRGM3 base address */
#define HPM_TRGM3_BASE (0xF023C000UL)
/* TRGM3 base pointer */
#define HPM_TRGM3 ((TRGM_Type *) HPM_TRGM3_BASE)

#include "hpm_pla_regs.h"
/* Address of PLA instances */
/* PLA0 base address */
#define HPM_PLA0_BASE (0xF020E000UL)
/* PLA0 base pointer */
#define HPM_PLA0 ((PLA_Type *) HPM_PLA0_BASE)
/* PLA1 base address */
#define HPM_PLA1_BASE (0xF021E000UL)
/* PLA1 base pointer */
#define HPM_PLA1 ((PLA_Type *) HPM_PLA1_BASE)

#include "hpm_synt_regs.h"
/* Address of SYNT instances */
/* SYNT base address */
#define HPM_SYNT_BASE (0xF0240000UL)
/* SYNT base pointer */
#define HPM_SYNT ((SYNT_Type *) HPM_SYNT_BASE)

/* Address of PLA_X2 instances */
/* PLA_X2 base address */
#define HPM_PLA_X2_BASE (0xF024E000UL)

#include "hpm_usb_regs.h"
/* Address of USB instances */
/* USB0 base address */
#define HPM_USB0_BASE (0xF2020000UL)
/* USB0 base pointer */
#define HPM_USB0 ((USB_Type *) HPM_USB0_BASE)

#include "hpm_gptmr_regs.h"
/* Address of TMR instances */
/* GPTMR0 base address */
#define HPM_GPTMR0_BASE (0xF3000000UL)
/* GPTMR0 base pointer */
#define HPM_GPTMR0 ((GPTMR_Type *) HPM_GPTMR0_BASE)
/* GPTMR1 base address */
#define HPM_GPTMR1_BASE (0xF3004000UL)
/* GPTMR1 base pointer */
#define HPM_GPTMR1 ((GPTMR_Type *) HPM_GPTMR1_BASE)
/* GPTMR2 base address */
#define HPM_GPTMR2_BASE (0xF3008000UL)
/* GPTMR2 base pointer */
#define HPM_GPTMR2 ((GPTMR_Type *) HPM_GPTMR2_BASE)
/* GPTMR3 base address */
#define HPM_GPTMR3_BASE (0xF300C000UL)
/* GPTMR3 base pointer */
#define HPM_GPTMR3 ((GPTMR_Type *) HPM_GPTMR3_BASE)
/* PTMR base address */
#define HPM_PTMR_BASE (0xF40E0000UL)
/* PTMR base pointer */
#define HPM_PTMR ((GPTMR_Type *) HPM_PTMR_BASE)

#include "hpm_i2c_regs.h"
/* Address of I2C instances */
/* I2C0 base address */
#define HPM_I2C0_BASE (0xF3020000UL)
/* I2C0 base pointer */
#define HPM_I2C0 ((I2C_Type *) HPM_I2C0_BASE)
/* I2C1 base address */
#define HPM_I2C1_BASE (0xF3024000UL)
/* I2C1 base pointer */
#define HPM_I2C1 ((I2C_Type *) HPM_I2C1_BASE)
/* I2C2 base address */
#define HPM_I2C2_BASE (0xF3028000UL)
/* I2C2 base pointer */
#define HPM_I2C2 ((I2C_Type *) HPM_I2C2_BASE)
/* I2C3 base address */
#define HPM_I2C3_BASE (0xF302C000UL)
/* I2C3 base pointer */
#define HPM_I2C3 ((I2C_Type *) HPM_I2C3_BASE)

#include "hpm_lin_regs.h"
/* Address of LIN instances */
/* LIN0 base address */
#define HPM_LIN0_BASE (0xF3030000UL)
/* LIN0 base pointer */
#define HPM_LIN0 ((LIN_Type *) HPM_LIN0_BASE)
/* LIN1 base address */
#define HPM_LIN1_BASE (0xF3034000UL)
/* LIN1 base pointer */
#define HPM_LIN1 ((LIN_Type *) HPM_LIN1_BASE)
/* LIN2 base address */
#define HPM_LIN2_BASE (0xF3038000UL)
/* LIN2 base pointer */
#define HPM_LIN2 ((LIN_Type *) HPM_LIN2_BASE)
/* LIN3 base address */
#define HPM_LIN3_BASE (0xF303C000UL)
/* LIN3 base pointer */
#define HPM_LIN3 ((LIN_Type *) HPM_LIN3_BASE)

#include "hpm_sdp_regs.h"
/* Address of SDP instances */
/* SDP base address */
#define HPM_SDP_BASE (0xF304C000UL)
/* SDP base pointer */
#define HPM_SDP ((SDP_Type *) HPM_SDP_BASE)

/* Address of ROMC instances */
/* ROMC base address */
#define HPM_ROMC_BASE (0xF3054000UL)

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
#define HPM_PIOC_BASE (0xF40D8000UL)
/* PIOC base pointer */
#define HPM_PIOC ((IOC_Type *) HPM_PIOC_BASE)
/* BIOC base address */
#define HPM_BIOC_BASE (0xF5010000UL)
/* BIOC base pointer */
#define HPM_BIOC ((IOC_Type *) HPM_BIOC_BASE)

#include "hpm_otp_regs.h"
/* Address of OTP instances */
/* OTPSHW base address */
#define HPM_OTPSHW_BASE (0xF4080000UL)
/* OTPSHW base pointer */
#define HPM_OTPSHW ((OTP_Type *) HPM_OTPSHW_BASE)
/* OTP base address */
#define HPM_OTP_BASE (0xF40C8000UL)
/* OTP base pointer */
#define HPM_OTP ((OTP_Type *) HPM_OTP_BASE)

#include "hpm_ppor_regs.h"
/* Address of PPOR instances */
/* PPOR base address */
#define HPM_PPOR_BASE (0xF40C0000UL)
/* PPOR base pointer */
#define HPM_PPOR ((PPOR_Type *) HPM_PPOR_BASE)

#include "hpm_pcfg_regs.h"
/* Address of PCFG instances */
/* PCFG base address */
#define HPM_PCFG_BASE (0xF40C4000UL)
/* PCFG base pointer */
#define HPM_PCFG ((PCFG_Type *) HPM_PCFG_BASE)

#include "hpm_psec_regs.h"
/* Address of PSEC instances */
/* PSEC base address */
#define HPM_PSEC_BASE (0xF40CC000UL)
/* PSEC base pointer */
#define HPM_PSEC ((PSEC_Type *) HPM_PSEC_BASE)

#include "hpm_pmon_regs.h"
/* Address of PMON instances */
/* PMON base address */
#define HPM_PMON_BASE (0xF40D0000UL)
/* PMON base pointer */
#define HPM_PMON ((PMON_Type *) HPM_PMON_BASE)

#include "hpm_pgpr_regs.h"
/* Address of PGPR instances */
/* PGPR base address */
#define HPM_PGPR_BASE (0xF40D4000UL)
/* PGPR base pointer */
#define HPM_PGPR ((PGPR_Type *) HPM_PGPR_BASE)

#include "hpm_pllctlv2_regs.h"
/* Address of PLLCTLV2 instances */
/* PLLCTLV2 base address */
#define HPM_PLLCTLV2_BASE (0xF4100000UL)
/* PLLCTLV2 base pointer */
#define HPM_PLLCTLV2 ((PLLCTLV2_Type *) HPM_PLLCTLV2_BASE)

#include "hpm_tsns_regs.h"
/* Address of TSNS instances */
/* TSNS base address */
#define HPM_TSNS_BASE (0xF4104000UL)
/* TSNS base pointer */
#define HPM_TSNS ((TSNS_Type *) HPM_TSNS_BASE)

/* Address of BACC instances */
/* BACC base address */
#define HPM_BACC_BASE (0xF5000000UL)

#include "hpm_bpor_regs.h"
/* Address of BPOR instances */
/* BPOR base address */
#define HPM_BPOR_BASE (0xF5004000UL)
/* BPOR base pointer */
#define HPM_BPOR ((BPOR_Type *) HPM_BPOR_BASE)

#include "hpm_bcfg_regs.h"
/* Address of BCFG instances */
/* BCFG base address */
#define HPM_BCFG_BASE (0xF5008000UL)
/* BCFG base pointer */
#define HPM_BCFG ((BCFG_Type *) HPM_BCFG_BASE)

#include "hpm_butn_regs.h"
/* Address of BUTN instances */
/* BUTN base address */
#define HPM_BUTN_BASE (0xF500C000UL)
/* BUTN base pointer */
#define HPM_BUTN ((BUTN_Type *) HPM_BUTN_BASE)

#include "hpm_bgpr_regs.h"
/* Address of BGPR instances */
/* BGPR base address */
#define HPM_BGPR_BASE (0xF5018000UL)
/* BGPR base pointer */
#define HPM_BGPR ((BGPR_Type *) HPM_BGPR_BASE)

#include "hpm_bsec_regs.h"
/* Address of BSEC instances */
/* BSEC base address */
#define HPM_BSEC_BASE (0xF5040000UL)
/* BSEC base pointer */
#define HPM_BSEC ((BSEC_Type *) HPM_BSEC_BASE)

#include "hpm_rtc_regs.h"
/* Address of RTC instances */
/* RTC base address */
#define HPM_RTC_BASE (0xF5044000UL)
/* RTC base pointer */
#define HPM_RTC ((RTC_Type *) HPM_RTC_BASE)

#include "hpm_bkey_regs.h"
/* Address of BKEY instances */
/* BKEY base address */
#define HPM_BKEY_BASE (0xF5048000UL)
/* BKEY base pointer */
#define HPM_BKEY ((BKEY_Type *) HPM_BKEY_BASE)

#include "hpm_bmon_regs.h"
/* Address of BMON instances */
/* BMON base address */
#define HPM_BMON_BASE (0xF504C000UL)
/* BMON base pointer */
#define HPM_BMON ((BMON_Type *) HPM_BMON_BASE)

#include "hpm_tamp_regs.h"
/* Address of TAMP instances */
/* TAMP base address */
#define HPM_TAMP_BASE (0xF5050000UL)
/* TAMP base pointer */
#define HPM_TAMP ((TAMP_Type *) HPM_TAMP_BASE)

#include "hpm_mono_regs.h"
/* Address of MONO instances */
/* MONO base address */
#define HPM_MONO_BASE (0xF5054000UL)
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