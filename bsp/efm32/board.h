/******************************************************************//**
 * @file 		drv_dma.h
 * @brief 	USART driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
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
 * 2011-05-06	onelife		Add EFM32 development kit and SPI Flash support
 *********************************************************************/
#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(EFM32G890F128)
#elif defined(EFM32G290F128)
#elif defined(EFM32G230F128)
#else
#error Unknown MCU type 
#endif

/* Includes -------------------------------------------------------------------*/
#include <efm32.h>
#include <efm32_chip.h>
#include <efm32_cmu.h>
#include <efm32_rmu.h>
#include <efm32_dma.h>
#include <efm32_rtc.h>
#include <efm32_timer.h>
#include <efm32_gpio.h>
#include <efm32_acmp.h>
#include <efm32_adc.h>
#include <efm32_usart.h>
#include <efm32_i2c.h>

#include <rtthread.h>

#if defined(EFM32_G290_DK)
#include <dvk.h>
#endif

/* Exported types -------------------------------------------------------------*/
/* Exported constants ---------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------*/
extern rt_uint32_t rt_system_status;

/* Exported macro -------------------------------------------------------------*/
#define DEBUG_EFM
#define DEBUG_EFM_USER

#define EFM32_SFLASH_DEBUG

#define EFM32_NO_DATA				(0)
#define EFM32_NO_OFFSET				(-1)
#define EFM32_NO_POINTER			(RT_NULL)

#define EFM32_SRAM_END 				(RAM_MEM_BASE + SRAM_SIZE)

#define EFM32_BASE_PRI_DEFAULT 		(0x0UL << 5)
#define EFM32_IRQ_PRI_DEFAULT 		(0x4UL << 5)

#if (defined(EFM32_G890_STK) || defined(EFM32_G290_DK))
#define EFM32_HFXO_FREQUENCY 		(32000000)
#else
#define EFM32_HFXO_FREQUENCY		(00000000)
#endif

#define UART_BAUDRATE				(115200)
#define USART_RX_BUFFER_SIZE		(64)

/* Max SPI clock: HFPERCLK/2 for master, HFPERCLK/8 for slave */
#define SPI_BAUDRATE				(4000000)

/* Slave select PIN setting for unit 2, 1 and 0 */
#define SPI_AUTOCS_ENABLE 			((0 << 2) | (0 << 1) | (1 << 0))

#define IIC_RX_BUFFER_SIZE			(32)

#define ADC_INIT_REF				adcRef2V5
#define ADC_INIT_CH 				adcSingleInpCh5
#define ADC_CONVERT_FREQUENCY 		(7000000)

#if (RT_CONSOLE_DEVICE == 0x0UL)
#define CONSOLE_DEVICE 				RT_USART0_NAME
#elif (RT_CONSOLE_DEVICE == 0x1UL)
#define CONSOLE_DEVICE 				RT_USART1_NAME
#elif (RT_CONSOLE_DEVICE == 0x2UL)
#define CONSOLE_DEVICE 				RT_USART2_NAME
#else
#define CONSOLE_DEVICE 				"no"
#endif

#if defined(EFM32_G290_DK)
#define EFM32_USING_SFLASH
#endif
#define SFLASH_USING_DEVICE_NAME 	RT_USART0_NAME

/*! fixme: move the following define to Rtdef.h */
#define RT_DEVICE_CTRL_USART_RBUFFER	(0xF1)		/*!< set USART rx buffer */
#define RT_DEVICE_CTRL_IIC_SETTING		(0xF2)		/*!< change IIC setting */
#define RT_DEVICE_CTRL_TIMER_PERIOD		(0xF3)		/*!< set Timer timeout period */
#define RT_DEVICE_CTRL_ADC_MODE			(0xF4)		/*!< change ADC mode */
#define RT_DEVICE_CTRL_ADC_RESULT		(0xF5)		/*!< get ADC result */
#define RT_DEVICE_CTRL_ACMP_INIT		(0xF6)		/*!< Initialize ACMP */
#define RT_DEVICE_CTRL_ACMP_OUTPUT		(0xF7)		/*!< get ACMP output */

/* Exported functions --------------------------------------------------------- */
void rt_hw_board_init(void);
void rt_hw_driver_init(void);

#endif /*__BOARD_H__ */
