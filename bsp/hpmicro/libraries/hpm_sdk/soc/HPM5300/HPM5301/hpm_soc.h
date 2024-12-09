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
#define IRQn_GPIO0_X                   3       /* GPIO0_X IRQ */
#define IRQn_GPIO0_Y                   4       /* GPIO0_Y IRQ */
#define IRQn_GPTMR0                    5       /* GPTMR0 IRQ */
#define IRQn_GPTMR1                    6       /* GPTMR1 IRQ */
#define IRQn_UART0                     13      /* UART0 IRQ */
#define IRQn_UART1                     14      /* UART1 IRQ */
#define IRQn_UART2                     15      /* UART2 IRQ */
#define IRQn_UART3                     16      /* UART3 IRQ */
#define IRQn_I2C0                      21      /* I2C0 IRQ */
#define IRQn_I2C1                      22      /* I2C1 IRQ */
#define IRQn_I2C2                      23      /* I2C2 IRQ */
#define IRQn_I2C3                      24      /* I2C3 IRQ */
#define IRQn_SPI0                      25      /* SPI0 IRQ */
#define IRQn_SPI1                      26      /* SPI1 IRQ */
#define IRQn_SPI2                      27      /* SPI2 IRQ */
#define IRQn_SPI3                      28      /* SPI3 IRQ */
#define IRQn_TSNS                      29      /* TSNS IRQ */
#define IRQn_MBX0A                     30      /* MBX0A IRQ */
#define IRQn_MBX0B                     31      /* MBX0B IRQ */
#define IRQn_EWDG0                     32      /* EWDG0 IRQ */
#define IRQn_EWDG1                     33      /* EWDG1 IRQ */
#define IRQn_HDMA                      34      /* HDMA IRQ */
#define IRQn_USB0                      51      /* USB0 IRQ */
#define IRQn_XPI0                      52      /* XPI0 IRQ */
#define IRQn_PSEC                      54      /* PSEC IRQ */
#define IRQn_SECMON                    55      /* SECMON IRQ */
#define IRQn_FUSE                      57      /* FUSE IRQ */
#define IRQn_ADC0                      58      /* ADC0 IRQ */
#define IRQn_ACMP_0                    62      /* ACMP_0 IRQ */
#define IRQn_ACMP_1                    63      /* ACMP_1 IRQ */
#define IRQn_SYSCTL                    64      /* SYSCTL IRQ */
#define IRQn_PGPIO                     65      /* PGPIO IRQ */
#define IRQn_PTMR                      66      /* PTMR IRQ */
#define IRQn_PUART                     67      /* PUART IRQ */
#define IRQn_PEWDG                     68      /* PEWDG IRQ */
#define IRQn_BROWNOUT                  69      /* BROWNOUT IRQ */
#define IRQn_PAD_WAKEUP                70      /* PAD_WAKEUP IRQ */
#define IRQn_DEBUG0                    71      /* DEBUG0 IRQ */
#define IRQn_DEBUG1                    72      /* DEBUG1 IRQ */

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

#include "hpm_gpiom_regs.h"
/* Address of GPIOM instances */
/* GPIOM base address */
#define HPM_GPIOM_BASE (0xF00D8000UL)
/* GPIOM base pointer */
#define HPM_GPIOM ((GPIOM_Type *) HPM_GPIOM_BASE)

#include "hpm_usb_regs.h"
/* Address of USB instances */
/* USB0 base address */
#define HPM_USB0_BASE (0xF300C000UL)
/* USB0 base pointer */
#define HPM_USB0 ((USB_Type *) HPM_USB0_BASE)

/* Address of ROMC instances */
/* ROMC base address */
#define HPM_ROMC_BASE (0xF3014000UL)

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

#include "hpm_adc16_regs.h"
/* Address of ADC16 instances */
/* ADC0 base address */
#define HPM_ADC0_BASE (0xF3080000UL)
/* ADC0 base pointer */
#define HPM_ADC0 ((ADC16_Type *) HPM_ADC0_BASE)

#include "hpm_acmp_regs.h"
/* Address of ACMP instances */
/* ACMP base address */
#define HPM_ACMP_BASE (0xF30B0000UL)
/* ACMP base pointer */
#define HPM_ACMP ((ACMP_Type *) HPM_ACMP_BASE)

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

#include "hpm_pdgo_regs.h"
/* Address of PDGO instances */
/* PDGO base address */
#define HPM_PDGO_BASE (0xF4134000UL)
/* PDGO base pointer */
#define HPM_PDGO ((PDGO_Type *) HPM_PDGO_BASE)


#include "riscv/riscv_core.h"
#include "hpm_csr_regs.h"
#include "hpm_interrupt.h"
#include "hpm_misc.h"
#include "hpm_dmamux_src.h"
#include "hpm_iomux.h"
#include "hpm_pmic_iomux.h"
#endif /* HPM_SOC_H */
