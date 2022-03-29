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

/* 
    Uncomment the line below according to the target device used in your application 
*/
/* #define ACM32F3XX */    /*!< ACM32F303xx */
   #define ACM32F4XX       /*!< ACM32F403xx */
/* #define ACM32FPXX */    /*!< ACM32FP400xx ACM32FP401xx */


/** @addtogroup Device_Included
  * @{
  */
#if defined(ACM32F3XX)
    #include "ACM32F3.h"
#elif defined(ACM32F4XX)
    #include "ACM32F4.h"
#elif defined(ACM32FPXX)
    #include "ACM32FP.h"
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


//#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
//#endif


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
#ifdef  ACM32F4XX
#define HAL_OPA_MODULE_ENABLED
#endif
#ifndef ACM32FPXX
#define HAL_COMP_MODULE_ENABLED
#define HAL_CAN_MODULE_ENABLED
#endif
#define HAL_LPUART_MODULE_ENABLED
#define HAL_WDT_MODULE_ENABLED 
#define HAL_FSUSB_MODULE_ENABLED
#define HAL_SYSTICK_ENABLED
#define HAL_CRC_ENABLED  
#define HAL_FAU_ENABLED  
#define HAL_AES_ENABLED  
#define HAL_HASH_SHA1_ENABLED 
#define HAL_HASH_SHA256_ENABLED 
#define HAL_HRNG_ENABLED  

#if defined(ACM32F3XX)
    #include "System_ACM32F3.h"
#elif defined(ACM32F4XX)
    #include "System_ACM32F4.h"
#elif defined(ACM32FPXX)
    #include "System_ACM32FP.h"
#else
    #error "Please select first the target device used in your application (in ACM32Fxx_HAL.h file)"
#endif

#include "System_Accelerate.h"

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

#ifdef HAL_DAC_MODULE_ENABLED
    #include "HAL_DAC.h"
#endif

#ifdef HAL_EXTI_MODULE_ENABLED
    #include "HAL_EXTI.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
    #include "HAL_I2C.h"
#endif

#ifdef HAL_I2S_MODULE_ENABLED
    #include "HAL_I2S.h"
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
    #include "HAL_EFlash.h"
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

#ifdef HAL_FSUSB_MODULE_ENABLED
    #include "HAL_FSUSB.h"
#endif

#ifdef HAL_CRC_ENABLED  
#include  "HAL_CRC.h"
#endif  

#ifdef  HAL_AES_ENABLED
#include  "HAL_AES.h"  
#endif    

#ifdef HAL_FAU_ENABLED    
#include  "HAL_FAU.h"       
#endif 

#ifdef HAL_HASH_SHA1_ENABLED 
#include "HAL_SHA1.h"  
#endif 

#ifdef HAL_HASH_SHA256_ENABLED 
#include "HAL_SHA256.h"  
#endif  

#ifdef HAL_HRNG_ENABLED     
#include "HAL_HRNG.h"    
#endif    


#endif
