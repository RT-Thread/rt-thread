/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2013-11-15     bright       fix SRAM size for heap management
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32l0xx.h>

/* board configuration */
// <o> SDCard Driver <1=>SDIO sdcard <0=>SPI MMC card
// 	<i>Default: 1
#define STM32_USE_SDIO			0

/* whether use board external SRAM memory */
// <e>Use external SRAM memory on the board
// 	<i>Enable External SRAM memory
#define STM32_EXT_SRAM          0
//	<o>Begin Address of External SRAM
//		<i>Default: 0x68000000
#define STM32_EXT_SRAM_BEGIN    0x68000000 /* the begining address of external SRAM */
//	<o>End Address of External SRAM
//		<i>Default: 0x68080000
#define STM32_EXT_SRAM_END      0x68080000 /* the end address of external SRAM */
// </e>

// <o> Internal SRAM memory size[Kbytes] <8-64>
//	<i>Default: 64
#define STM32_SRAM_SIZE         20
#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)

void rt_hw_board_init(void);

/* SD Card init function */
void rt_hw_msd_init(void);

#define PRINT_RCC_FREQ_INFO
#define UFQFPN32

#ifdef RT_USING_PIN
extern inline void stm32_pin_write_early(rt_base_t pin, rt_base_t value);
extern inline int stm32_pin_read_early(rt_base_t pin);
extern void stm32_pin_mode_early(rt_base_t pin, rt_base_t mode);
#endif /*RT_USING_PIN*/

#define RT_USING_UART1
#define UART1_GPIO_TX			19
#define UART1_GPIO_RX			20
#define UART1_GPIO_AF			GPIO_AF4_USART1

#define RT_USING_SPI1
#define SPI1PINNSS   8
#define SPI1PINSCK   11
#define SPI1PINMOSI  12
#define SPI1PINMISO  13

#define RT_USING_SI4438
#define SI4438_SDN   7

#endif
