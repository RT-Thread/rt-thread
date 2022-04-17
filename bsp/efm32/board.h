/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-21   onelife     Initial creation for EFM32
 * 2011-05-06   onelife     Add EFM32 development kit and SPI Flash support
 * 2011-07-12   onelife     Add prototype for SWO output enable and interrupt
 *                            context check functions
 * 2011-12-08   onelife     Add giant gecko development kit support
 * 2011-12-09   onelife     Add giant gecko support
 * 2011-12-09   onelife     Add LEUART module support
 * 2011-12-14   onelife     Add LFXO enabling routine in driver initialization function
 * 2011-12-20   onelife     Move SPI Auto-CS setting to "rtconfig.h"
 * 2012-05-15   onelife     Modified to compatible with CMSIS v3
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#if defined(EFM32G890F128)
#elif defined(EFM32G290F128)
#elif defined(EFM32G230F128)
#elif defined(EFM32GG990F1024)
#else
#error Unknown MCU type
#endif

/* Includes ------------------------------------------------------------------*/
#include <efm32.h>
#include <em_chip.h>
#include <em_cmu.h>
#include <em_rmu.h>
#include <em_emu.h>
#include <em_dma.h>
#include <em_ebi.h>
#include <em_rtc.h>
#include <em_timer.h>
#include <em_letimer.h>
#include <em_gpio.h>
#include <em_acmp.h>
#include <em_adc.h>
#include <em_usart.h>
#include <em_leuart.h>
#include <em_i2c.h>

#include <rtthread.h>

#if (defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
#include <dvk.h>
#endif

#include "drv_emu.h"

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

#define EFM32_NO_DATA               (0)
#define EFM32_NO_POINTER            (RT_NULL)
#define EFM32_NO_OFFSET             (-1)
#define EFM32_NO_DMA                (-1)

/* SECTION: SPI Flash */
#if defined(EFM32_USING_SFLASH)
#define SFLASH_CS_PORT              (gpioPortC)
#define SFLASH_CS_PIN               (8)
#endif

/* SECTION: Micro SD */
#if defined(EFM32_USING_SPISD)
 #if defined(EFM32_GXXX_DK)
 #define SD_CS_PORT                 (gpioPortC)
 #define SD_CS_PIN                  (8)
 #elif defined(EFM32GG_DK3750)
 #define SD_CS_PORT                 (gpioPortE)
 #define SD_CS_PIN                  (4)
 #endif
#endif

/* SECTION: Ethernet */
#if defined(EFM32_USING_ETHERNET)
 #if defined(EFM32_GXXX_DK)
 #define ETH_CS_PORT                (gpioPortB)
 #define ETH_CS_PIN                 (6)
 #elif defined(EFM32GG_DK3750)
 #define ETH_CS_PORT                (gpioPortD)
 #define ETH_CS_PIN                 (3)
 #endif
#endif

/* SECTION: LCD */
#if defined(EFM32_USING_LCD)
 #if defined(EFM32GG_DK3750)
 #define LCD_CS_PORT                 (gpioPortD)
 #define LCD_CS_PIN                  (3)
 #endif
#endif

/* SECTION: SYSTEM */
#define EFM32_SRAM_END              (SRAM_BASE + SRAM_SIZE)
#define EFM32_BASE_PRI_DEFAULT      (0x0UL << 5)
#define EFM32_IRQ_PRI_DEFAULT       (0x4UL << 5)

/* SECTION: CLOCK */
#define EFM32_USING_HFXO
#define EFM32_USING_LFXO
#if defined(EFM32_USING_HFXO)
 #if (defined(EFM32_G8XX_STK) || defined(EFM32_GXXX_DK))
 #define EFM32_HFXO_FREQUENCY       (32000000)
 #elif defined(EFM32GG_DK3750)
 #define EFM32_HFXO_FREQUENCY       (48000000)
 #else
 #define EFM32_HFXO_FREQUENCY       (00000000)
 #endif
#endif
#if defined(EFM32_USING_LFXO)
 #if (defined(EFM32_G8XX_STK) || defined(EFM32_GXXX_DK))
 #define EFM32_LETIMER_TOP_100HZ    (41)
 #elif defined(EFM32GG_DK3750)
 #define EFM32_LETIMER_TOP_100HZ    (41)
 #else
 #define EFM32_LETIMER_TOP_100HZ    (41)
 #endif
#endif

/* SECTION: USART */
#define USART_RX_BUFFER_SIZE        (64)
#define LEUART_RX_BUFFER_SIZE       (64)
/* Location count (start from 0) */
#if defined(_EFM32_GECKO_FAMILY)
#define EFM32_USART_LOCATION_COUNT  (3)
#define EFM32_UART_LOCATION_COUNT   (4)
#define EFM32_LEUART_LOCATION_COUNT (3)
#elif defined(_EFM32_GIANT_FAMILY)
#define EFM32_USART_LOCATION_COUNT  (6)
#define EFM32_UART_LOCATION_COUNT   (4)
#define EFM32_LEUART_LOCATION_COUNT (5)
#endif

/* SUBSECTION: UART */
#define UART_BAUDRATE               (115200)

/* SUBSECTION: SPI */
/* Max SPI clock: HFPERCLK/2 for master, HFPERCLK/8 for slave */
#define SPI_BAUDRATE                (4000000)

/* SECTION: I2C */
#define IIC_RX_BUFFER_SIZE          (32)
#if defined(_EFM32_GECKO_FAMILY)
#define EFM32_IIC_LOCATION_COUNT    (4)
#elif defined(_EFM32_GIANT_FAMILY)
#define EFM32_IIC_LOCATION_COUNT    (7)
#endif

/* SECTION: ADC */
#define ADC_CALI_REF                (adcRef2V5)
#define ADC_CALI_CH                 (adcSingleInpCh5)
#define ADC_CONVERT_FREQUENCY       (7000000)

#if (RT_CONSOLE_DEVICE == EFM_USART0)
#define CONSOLE_DEVICE              RT_USART0_NAME
#elif (RT_CONSOLE_DEVICE == EFM_USART1)
#define CONSOLE_DEVICE              RT_USART1_NAME
#elif (RT_CONSOLE_DEVICE == EFM_USART2)
#define CONSOLE_DEVICE              RT_USART2_NAME
#elif (RT_CONSOLE_DEVICE == EFM_UART0)
#define CONSOLE_DEVICE              RT_UART0_NAME
#elif (RT_CONSOLE_DEVICE == EFM_UART1)
#define CONSOLE_DEVICE              RT_UART1_NAME
#elif (RT_CONSOLE_DEVICE == EFM_LEUART0)
#define CONSOLE_DEVICE              RT_LEUART0_NAME
#elif (RT_CONSOLE_DEVICE == EFM_LEUART1)
#define CONSOLE_DEVICE              RT_LEUART1_NAME
#else
#define CONSOLE_DEVICE              "NONE"
#endif


/* The following defines should be consistent with those in diskio.h */
#define CTRL_SYNC                       0
#define GET_SECTOR_COUNT                1
#define GET_SECTOR_SIZE                 2
#define GET_BLOCK_SIZE                  3
#define MMC_GET_TYPE                    10
#define MMC_GET_CSD                     11
#define MMC_GET_CID                     12
#define MMC_GET_OCR                     13
#define MMC_GET_SDSTAT                  14
/* The above defines should be consistent with those in diskio.h */

/* I/O control options */
#define RT_DEVICE_CTRL_SD_SYNC          CTRL_SYNC
#define RT_DEVICE_CTRL_SD_GET_SCOUNT    GET_SECTOR_COUNT
#define RT_DEVICE_CTRL_SD_GET_SSIZE     GET_SECTOR_SIZE
#define RT_DEVICE_CTRL_SD_GET_BSIZE     GET_BLOCK_SIZE
#define RT_DEVICE_CTRL_SD_GET_TYPE      MMC_GET_TYPE
#define RT_DEVICE_CTRL_SD_GET_CSD       MMC_GET_CSD
#define RT_DEVICE_CTRL_SD_GET_CID       MMC_GET_CID
#define RT_DEVICE_CTRL_SD_GET_OCR       MMC_GET_OCR
#define RT_DEVICE_CTRL_SD_GET_SDSTAT    MMC_GET_SDSTAT

/*! fixme: move the following define to Rtdef.h */
#define RT_DEVICE_CTRL_USART_RBUFFER    (0xF1)      /*!< set USART/UART rx buffer */
#define RT_DEVICE_CTRL_LEUART_RBUFFER   (0xF2)      /*!< set LEUART rx buffer */
#define RT_DEVICE_CTRL_IIC_SETTING      (0xF3)      /*!< change IIC setting */
#define RT_DEVICE_CTRL_TIMER_PERIOD     (0xF4)      /*!< set Timer timeout period */
#define RT_DEVICE_CTRL_ADC_MODE         (0xF5)      /*!< change ADC mode */
#define RT_DEVICE_CTRL_ADC_RESULT       (0xF6)      /*!< get ADC result */
#define RT_DEVICE_CTRL_ACMP_INIT        (0xF7)      /*!< Initialize ACMP */
#define RT_DEVICE_CTRL_ACMP_OUTPUT      (0xF8)      /*!< get ACMP output */

/* Exported functions ------------------------------------------------------- */
void rt_hw_board_init(void);
void rt_hw_driver_init(void);
rt_uint32_t rt_hw_interrupt_check(void);

#endif /*__BOARD_H__ */
