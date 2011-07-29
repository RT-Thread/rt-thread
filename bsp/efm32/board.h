/***************************************************************************//**
 * @file 	board.h
 * @brief 	Board support of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file 
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21	onelife		Initial creation for EFM32
 * 2011-05-06	onelife		Add EFM32 development kit and SPI Flash support
 * 2011-07-12	onelife		Add prototype for SWO output enable and interrupt 
 *  context check functions 
 ******************************************************************************/
#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(EFM32G890F128)
#elif defined(EFM32G290F128)
#elif defined(EFM32G230F128)
#else
#error Unknown MCU type 
#endif

/* Includes ------------------------------------------------------------------*/
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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern volatile rt_uint32_t rt_system_status;

/* Exported macro ------------------------------------------------------------*/
#ifdef EFM32_DEBUG
#define DEBUG_EFM
#define DEBUG_EFM_USER
#define EFM32_SWO_ENABLE
#endif

#define EFM32_NO_DATA				(0)
#define EFM32_NO_POINTER			(RT_NULL)
#define EFM32_NO_OFFSET				(-1)
#define EFM32_NO_DMA				(-1)

/* SECTION: SPI Flash */
#if defined(EFM32_USING_SFLASH)
#define USART_0_AUTOCS 				(0)
#define SFLASH_CS_PORT 				(gpioPortC)
#define SFLASH_CS_PIN 				(8)
#endif

/* SECTION: Micro SD */
#if defined(EFM32_USING_SPISD)
#define USART_0_AUTOCS 				(1)
#define SD_CS_PORT 					(gpioPortC)
#define SD_CS_PIN 					(8)
#endif

/* SECTION: Ethernet */
#if defined(EFM32_USING_ETHERNET)
#define USART_2_AUTOCS 				(0)
#define ETH_CS_PORT 				(gpioPortB)
#define ETH_CS_PIN 					(6)
#endif

/* SECTION: SYSTEM */
#define EFM32_SRAM_END 				(SRAM_BASE + SRAM_SIZE)
#define EFM32_BASE_PRI_DEFAULT 		(0x0UL << 5)
#define EFM32_IRQ_PRI_DEFAULT 		(0x4UL << 5)
#if (defined(EFM32_G890_STK) || defined(EFM32_G290_DK))
#define EFM32_HFXO_FREQUENCY 		(32000000)
#else
#define EFM32_HFXO_FREQUENCY		(00000000)
#endif

/* SECTION: USART */
#define USART_RX_BUFFER_SIZE		(64)

/* SUBSECTION: UART */
#define UART_BAUDRATE				(115200)

/* SUBSECTION: SPI */
/* Max SPI clock: HFPERCLK/2 for master, HFPERCLK/8 for slave */
#define SPI_BAUDRATE				(4000000)

#ifndef USART_0_AUTOCS
#define USART_0_AUTOCS 				(0)
#endif
#ifndef USART_1_AUTOCS
#define USART_1_AUTOCS 				(0)
#endif
#ifndef USART_2_AUTOCS
#define USART_2_AUTOCS 				(0)
#endif
/* Auto Slave Select */
#define SPI_AUTOCS_ENABLE 			((USART_2_AUTOCS << 2) | \
									(USART_1_AUTOCS << 1) | \
									(USART_0_AUTOCS << 0))

/* SECTION: I2C */
#define IIC_RX_BUFFER_SIZE			(32)

/* SECTION: ADC */

#define ADC_CALI_REF				adcRef2V5
#define ADC_CALI_CH 				adcSingleInpCh5
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


/* The following defines should be consistent with those in diskio.h */
#define CTRL_SYNC						0
#define GET_SECTOR_COUNT				1
#define GET_SECTOR_SIZE					2
#define GET_BLOCK_SIZE					3
#define MMC_GET_TYPE					10
#define MMC_GET_CSD						11
#define MMC_GET_CID						12
#define MMC_GET_OCR						13
#define MMC_GET_SDSTAT					14
/* The above defines should be consistent with those in diskio.h */

/* I/O control options */
#define RT_DEVICE_CTRL_SD_SYNC 			CTRL_SYNC
#define RT_DEVICE_CTRL_SD_GET_SCOUNT 	GET_SECTOR_COUNT
#define RT_DEVICE_CTRL_SD_GET_SSIZE		GET_SECTOR_SIZE
#define RT_DEVICE_CTRL_SD_GET_BSIZE 	GET_BLOCK_SIZE
#define RT_DEVICE_CTRL_SD_GET_TYPE 		MMC_GET_TYPE
#define RT_DEVICE_CTRL_SD_GET_CSD		MMC_GET_CSD
#define RT_DEVICE_CTRL_SD_GET_CID 		MMC_GET_CID
#define RT_DEVICE_CTRL_SD_GET_OCR 		MMC_GET_OCR
#define RT_DEVICE_CTRL_SD_GET_SDSTAT	MMC_GET_SDSTAT

/*! fixme: move the following define to Rtdef.h */
#define RT_DEVICE_CTRL_USART_RBUFFER	(0xF1)		/*!< set USART rx buffer */
#define RT_DEVICE_CTRL_IIC_SETTING		(0xF2)		/*!< change IIC setting */
#define RT_DEVICE_CTRL_TIMER_PERIOD		(0xF3)		/*!< set Timer timeout period */
#define RT_DEVICE_CTRL_ADC_MODE			(0xF4)		/*!< change ADC mode */
#define RT_DEVICE_CTRL_ADC_RESULT		(0xF5)		/*!< get ADC result */
#define RT_DEVICE_CTRL_ACMP_INIT		(0xF6)		/*!< Initialize ACMP */
#define RT_DEVICE_CTRL_ACMP_OUTPUT		(0xF7)		/*!< get ACMP output */

/* Exported functions ------------------------------------------------------- */
void rt_hw_board_init(void);
void rt_hw_driver_init(void);
rt_uint32_t rt_hw_interrupt_check(void);

#endif /*__BOARD_H__ */
