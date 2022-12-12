/*
  ******************************************************************************
  * @file    ACM32Fxx_HAL.h
  * @version V1.0.0
  * @date    2020
  * @brief   HAL Config header file.
  ******************************************************************************
*/
#ifndef __ACM32FXX_HAL_H__
#define __ACM32FXX_HAL_H__
#ifdef __GNUC__
#define  __weak __attribute__((weak))
#endif
/*
    Uncomment the line below according to the target device used in your application
*/
   #define ACM32F0X0       /*!< ACM32F0x0xx */
/* #define ACM32FP0X */    /*!< ACM32FP0xxx */

/** @addtogroup Device_Included
  * @{
  */
#if defined(ACM32F0X0)
    #include "ACM32F0x0.h"
#elif defined(ACM32FP0X)
    #include "ACM32FP0X.h"
#else
    #error "Please select first the target device used in your application (in ACM32Fxx_HAL.h file)"
#endif
/**
  * @}
  */


/*
 * @brief  HAL Status structures definition
 */
typedef enum
{
    HAL_OK       = 0x00U,
    HAL_ERROR    = 0x01U,
    HAL_BUSY     = 0x02U,
    HAL_TIMEOUT  = 0x03U
}HAL_StatusTypeDef;

/* USE FULL ASSERT */
#define USE_FULL_ASSERT    (1)

#define HAL_DMA_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_DAC_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_I2S_MODULE_ENABLED
#define HAL_IWDT_MODULE_ENABLED
#define HAL_RTC_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_TIMER_MODULE_ENABLED
#define HAL_EFLASH_MODULE_ENABLED
#define HAL_OPA_MODULE_ENABLED
#define HAL_COMP_MODULE_ENABLED
#define HAL_CAN_MODULE_ENABLED
#define HAL_LPUART_MODULE_ENABLED
#define HAL_WDT_MODULE_ENABLED
#define HAL_FSUSB_MODULE_ENABLED
#define HAL_LCD_MODULE_ENABLED
//#define HAL_SYSTICK_ENABLED
#define HAL_CRC_ENABLED
#define HAL_TKEY_MODULE_ENABLED
#define HAL_AES_ENABLED
#define HAL_HRNG_ENABLED
#define HAL_DIV_ENABLED

#include "System_ACM32F0x0.h"

#ifdef HAL_DMA_MODULE_ENABLED
    #include "HAL_DMA.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
    #include "HAL_GPIO.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
    #include "HAL_UART.h"
    #include "HAL_UART_EX.h"
#endif

#ifdef HAL_ADC_MODULE_ENABLED
    #include "HAL_ADC.h"
#endif

#ifdef HAL_EXTI_MODULE_ENABLED
    #include "HAL_EXTI.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
    #include "HAL_I2C.h"
#endif


#ifdef HAL_RTC_MODULE_ENABLED
    #include "HAL_RTC.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
    #include "HAL_SPI.h"
#endif

#ifdef HAL_IWDT_MODULE_ENABLED
    #include "HAL_IWDT.h"
#endif

#ifdef HAL_EFLASH_MODULE_ENABLED
    #include "HAL_EFLASH.h"
    #include "HAL_EFlash_EX.h"
#endif

#ifdef HAL_OPA_MODULE_ENABLED
    #include "HAL_OPA.h"
#endif

#ifdef HAL_COMP_MODULE_ENABLED
    #include "HAL_COMP.h"
#endif

#ifdef HAL_CAN_MODULE_ENABLED
    #include "HAL_CAN.h"
#endif

#ifdef HAL_LPUART_MODULE_ENABLED
    #include "HAL_LPUART.h"
#endif

#ifdef HAL_WDT_MODULE_ENABLED
    #include "HAL_WDT.h"
#endif

#ifdef HAL_TIMER_MODULE_ENABLED
    #include "HAL_TIMER.h"
    #include "HAL_TIMER_EX.h"
#endif
#ifdef HAL_LCD_MODULE_ENABLED
    #include "HAL_LCD.h"
#endif


#ifdef HAL_TKEY_MODULE_ENABLED
    #include "HAL_TKEY.h"
#endif
#ifdef HAL_CRC_ENABLED
#include  "HAL_CRC.h"
#endif

#ifdef  HAL_AES_ENABLED
#include  "HAL_AES.h"
#endif

#ifdef HAL_HRNG_ENABLED
#include "HAL_HRNG.h"
#endif

#ifdef HAL_DIV_ENABLED
#include "HAL_DIV.h"
#endif


#endif
