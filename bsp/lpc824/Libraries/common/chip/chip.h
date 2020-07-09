/*
 * @brief LPC8xx basic chip inclusion file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CHIP_H_
#define __CHIP_H_

#include "lpc_types.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CORE_M0PLUS
#error CORE_M0PLUS is not defined for the LPC8xx architecture
#error CORE_M0PLUS should be defined as part of your compiler define list
#endif

#ifndef CHIP_LPC8XX
#error The LPC8XX Chip include path is used for this build, but
#error CHIP_LPC8XX is not defined!
#endif

/** @defgroup PERIPH_8XX_BASE CHIP: LPC8xx Peripheral addresses and register set declarations
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/* Base addresses */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_ROM_BASE          (0x1FFF0000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_AHB_BASE          (0x50000000UL)

/* APB0 peripherals */
#define LPC_WWDT_BASE         (0x40000000UL)
#define LPC_MRT_BASE          (0x40004000UL)
#define LPC_WKT_BASE          (0x40008000UL)
#define LPC_SWM_BASE          (0x4000C000UL)
#define LPC_ADC_BASE          (0x4001C000UL)  /* Available only on LPC82x */
#define LPC_PMU_BASE          (0x40020000UL)
#define LPC_CMP_BASE          (0x40024000UL)
#define LPC_DMATIRGMUX_BASE   (0x40028000UL)  /* Available only on LPC82x */
#define LPC_INMUX_BASE        (0x4002C000UL)  /* Available only on LPC82x */

#define LPC_FMC_BASE          (0x40040000UL)
#define LPC_IOCON_BASE        (0x40044000UL)
#define LPC_SYSCTL_BASE       (0x40048000UL)
#define LPC_I2C0_BASE         (0x40050000UL)
#define LPC_I2C1_BASE         (0x40054000UL)  /* Available only on LPC82x */
#define LPC_SPI0_BASE         (0x40058000UL)
#define LPC_SPI1_BASE         (0x4005C000UL)
#define LPC_USART0_BASE       (0x40064000UL)
#define LPC_USART1_BASE       (0x40068000UL)
#define LPC_USART2_BASE       (0x4006C000UL)
#define LPC_I2C2_BASE         (0x40070000UL)  /* Available only on LPC82x */
#define LPC_I2C3_BASE         (0x40074000UL)  /* Available only on LPC82x */

/* AHB peripherals */
#define LPC_CRC_BASE          (0x50000000UL)
#define LPC_SCT_BASE          (0x50004000UL)
#define LPC_DMA_BASE          (0x50008000UL)  /* Available only on LPC82x */

#define LPC_GPIO_PORT_BASE    (0xA0000000UL)
#define LPC_PIN_INT_BASE      (0xA0004000UL)

#define LPC_WWDT            ((LPC_WWDT_T     *) LPC_WWDT_BASE)
#define LPC_SPI0            ((LPC_SPI_T      *) LPC_SPI0_BASE)
#define LPC_SPI1            ((LPC_SPI_T      *) LPC_SPI1_BASE)
#define LPC_USART0          ((LPC_USART_T    *) LPC_USART0_BASE)
#define LPC_USART1          ((LPC_USART_T    *) LPC_USART1_BASE)
#define LPC_USART2          ((LPC_USART_T    *) LPC_USART2_BASE)
#define LPC_WKT             ((LPC_WKT_T         *) LPC_WKT_BASE)
#define LPC_PMU             ((LPC_PMU_T         *) LPC_PMU_BASE)
#define LPC_CRC             ((LPC_CRC_T         *) LPC_CRC_BASE)
#define LPC_SCT             ((LPC_SCT_T         *) LPC_SCT_BASE)
#define LPC_GPIO_PORT       ((LPC_GPIO_T        *) LPC_GPIO_PORT_BASE)
#define LPC_PININT          ((LPC_PININT_T     *) LPC_PIN_INT_BASE)
#define LPC_IOCON           ((LPC_IOCON_T       *) LPC_IOCON_BASE)
#define LPC_SWM             ((LPC_SWM_T         *) LPC_SWM_BASE)
#define LPC_SYSCTL          ((LPC_SYSCTL_T      *) LPC_SYSCTL_BASE)
#define LPC_CMP             ((LPC_CMP_T         *) LPC_CMP_BASE)
#define LPC_FMC             ((LPC_FMC_T         *) LPC_FMC_BASE)
#define LPC_MRT             ((LPC_MRT_T         *) LPC_MRT_BASE)
#define LPC_I2C0            ((LPC_I2C_T         *) LPC_I2C0_BASE)

#ifdef CHIP_LPC82X
/* Peripherals available only on LPC82x */
#define LPC_ADC             ((LPC_ADC_T         *) LPC_ADC_BASE)
#define LPC_I2C1            ((LPC_I2C_T         *) LPC_I2C1_BASE)
#define LPC_I2C2            ((LPC_I2C_T         *) LPC_I2C2_BASE)
#define LPC_I2C3            ((LPC_I2C_T         *) LPC_I2C3_BASE)
#define LPC_DMA             ((LPC_DMA_T         *) LPC_DMA_BASE)
#define LPC_DMATRIGMUX      ((LPC_DMATRIGMUX_T  *) LPC_DMATIRGMUX_BASE)
#define LPC_INMUX           ((LPC_INMUX_T       *) LPC_INMUX_BASE)
#endif

/* Base address Alias list */
#define LPC_I2C_BASE         LPC_I2C0_BASE
#define LPC_I2C              LPC_I2C0
#define LPC_SYSCON           LPC_SYSCTL

/* IRQ Handler alias list */
#ifdef CHIP_LPC82X
#define I2C_IRQHandler       I2C0_IRQHandler
#define PININT0_IRQHandler   PIN_INT0_IRQHandler
#define PININT1_IRQHandler   PIN_INT1_IRQHandler
#define PININT2_IRQHandler   PIN_INT2_IRQHandler
#define PININT3_IRQHandler   PIN_INT3_IRQHandler
#define PININT4_IRQHandler   PIN_INT4_IRQHandler
#define PININT5_IRQHandler   PIN_INT5_IRQHandler
#define PININT6_IRQHandler   PIN_INT6_IRQHandler
#define PININT7_IRQHandler   PIN_INT7_IRQHandler
#endif

/**
 * @}
 */

/** @ingroup CHIP_8XX_DRIVER_OPTIONS
 * @{
 */

/**
 * @brief	System oscillator rate
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the external oscillator for the board. If using the
 * internal oscillator, this rate can be 0.
 */
extern const uint32_t OscRateIn;

/**
 * @brief	Clock rate on the CLKIN pin
 * This value is defined externally to the chip layer and contains
 * the value in Hz for the CLKIN pin for the board. If this pin isn't used,
 * this rate can be 0.
 */
extern const uint32_t ExtRateIn;

/**
 * @}
 */

/* Include order is important! */
#include "syscon_8xx.h"
#include "clock_8xx.h"
#include "fmc_8xx.h"
#include "ioswm_8xx.h"

#ifndef _CHIP_COMMON_
#include "../../peri_driver/peri_driver.h"
#endif

/** @defgroup SUPPORT_8XX_FUNC CHIP: LPC8xx support functions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief	Current system clock rate, mainly used for sysTick
 */
extern uint32_t SystemCoreClock;

/**
 * @brief	Update system core clock rate, should be called if the
 *			system has a clock rate change
 * @return	None
 */
void SystemCoreClockUpdate(void);

/**
 * @brief	Set up and initialize hardware prior to call to main()
 * @return	None
 * @note	Chip_SystemInit() is called prior to the application and sets up
 * system clocking prior to the application starting.
 */
void Chip_SystemInit(void);

/**
 * @brief	Clock and PLL initialization based on the external oscillator
 * @return	None
 * @note	This function assumes an external crystal oscillator
 * frequency of 12MHz.
 */
void Chip_SetupXtalClocking(void);

/**
 * @brief	Clock and PLL initialization based on the internal oscillator
 * @return	None
 */
void Chip_SetupIrcClocking(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_H_ */
