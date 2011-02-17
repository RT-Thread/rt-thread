/******************************************************************//**
 * @file 		drv_dma.h
 * @brief 	USART driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21	onelife		Initial creation for EFM32
 *********************************************************************/
#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(EFM32G890F128)
#define EFM32_G890_STK
#elif defined(EFM32G290F128)
#define EFM32_G290_DK
#else
#error Unknown MCU type 
#endif

/* Includes -------------------------------------------------------------------*/
#include <efm32.h>
#include <efm32_chip.h>
#include <efm32_cmu.h>
#include <efm32_rmu.h>
#include <efm32_dma.h>
#include <efm32_timer.h>
#include <efm32_gpio.h>
#include <efm32_rtc.h>
#include <efm32_usart.h>
#include <efm32_i2c.h>

#include <rtthread.h>

/* Exported types -------------------------------------------------------------*/
/* Exported constants ---------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------*/
extern rt_uint32_t rt_system_status;

/* Exported macro -------------------------------------------------------------*/
#define DEBUG_EFM
#define DEBUG_EFM_USER

#define EFM32_NO_DATA			(0)
#define EFM32_NO_OFFSET			(-1)
#define EFM32_NO_POINTER		(RT_NULL)


#define HFXO_FREQUENCY 			(32000000)
#define UART_PERCLK_FREQUENCY	HFXO_FREQUENCY
#define UART_BAUDRATE			(115200)
#define SERIAL_RX_BUFFER_SIZE	(64)

#define IIC_RX_BUFFER_SIZE		(32)



#define EFM32_SRAM_END 			(RAM_MEM_BASE + SRAM_SIZE)

#define EFM32_BASE_PRI_DEFAULT 	(0x0UL << 5)
#define EFM32_IRQ_PRI_DEFAULT 	(0x4UL << 5)


#if (RT_CONSOLE_DEVICE == 0x0UL)
#define CONSOLE_DEVICE 			RT_USART0_NAME
#elif (RT_CONSOLE_DEVICE == 0x1UL)
#define CONSOLE_DEVICE 			RT_USART1_NAME
#elif (RT_CONSOLE_DEVICE == 0x2UL)
#define CONSOLE_DEVICE 			RT_USART2_NAME
#else
#define CONSOLE_DEVICE 			"no"
#endif

#define RT_DEVICE_CTRL_USART    (0x04)		/*!< USART control */
#define RT_DEVICE_CTRL_IIC	    (0x08)		/*!< IIC control */
#define RT_DEVICE_CTRL_TIMER    (0x10)		/*!< Timer control */

/* Exported functions --------------------------------------------------------- */
void rt_hw_board_init(void);
void rt_hw_driver_init(void);

#endif /*__BOARD_H__ */
