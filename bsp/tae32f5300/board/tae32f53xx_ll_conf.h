/**
  ******************************************************************************
  * @file    tae32f53xx_ll_conf.h
  * @author  MCD Application Team
  * @brief   LL configuration file.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_CONF_H_
#define _TAE32F53XX_LL_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_Template
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup CONFIG_LL_Exported_Constants CONFIG LL Exported Constants
  * @brief    CONFIG LL Exported Constants
  * @{
  */

/** @defgroup CONFIG_LL_Module_Selection CONFIG LL Module Selection
  * @brief    CONFIG LL Module Selection
  * @note     This is the list of modules to be used in the LL driver
  * @{
  */

/* Internal Class Peripheral */
#define LL_MODULE_ENABLED           /*!< LL Module Enable       */
#define LL_CORTEX_MODULE_ENABLED    /*!< Cortex Module Enable   */
#define LL_FPLL_MODULE_ENABLED      /*!< FPLL Module Enable     */
#define LL_LVD_MODULE_ENABLED       /*!< LVD Module Enable      */
#define LL_DMA_MODULE_ENABLED       /*!< DMA Module Enable      */
#define LL_FLASH_MODULE_ENABLED     /*!< FLASH Module Enable    */
#define LL_DFLASH_MODULE_ENABLED    /*!< DFLASH Module Enable   */
#define LL_WWDG_MODULE_ENABLED      /*!< WWDG Module Enable     */
#define LL_IWDG_MODULE_ENABLED      /*!< IWDG Module Enable     */
#define LL_TMR_MODULE_ENABLED       /*!< TMR Module Enable      */
#define LL_IIR_MODULE_ENABLED       /*!< IIR Module Enable      */

/* Interface Class Peripheral */
#define LL_GPIO_MODULE_ENABLED      /*!< GPIO Module Enable     */
#define LL_UART_MODULE_ENABLED      /*!< UART Module Enable     */
#define LL_I2C_MODULE_ENABLED       /*!< I2C Module Enable      */
#define LL_CAN_MODULE_ENABLED       /*!< CAN Module Enable      */
#define LL_DALI_MODULE_ENABLED      /*!< DALI Module Enable     */
#define LL_USB_MODULE_ENABLED       /*!< USB Module Enable      */

/* Analog Class Peripheral */
#define LL_ADC_MODULE_ENABLED       /*!< ADC Module Enable      */
#define LL_DAC_MODULE_ENABLED       /*!< DAC Module Enable      */
#define LL_CMP_MODULE_ENABLED       /*!< CMP Module Enable      */
#define LL_ECU_MODULE_ENABLED       /*!< ECU Module Enable      */
#define LL_HRPWM_MODULE_ENABLED     /*!< HRPWM Module Enable    */

/**
  * @}
  */


/** @defgroup CONFIG_LL_Oscillator_Values_Adaptation CONFIG LL Oscillator Values Adaptation
  * @brief    CONFIG LL Oscillator Values Adaptation
  * @{
  */

/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the FPLL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE               8000000U    /*!< Value of the External oscillator in Hz */
#endif

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the FPLL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
#define HSI_VALUE               8000000U    /*!< Value of the Internal oscillator in Hz */
#endif

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  *        Defines the value of the Internal Low Speed oscillator in Hz.
  * @note  The real value may vary depending on the variations in voltage and temperature.
  */
#if !defined  (LSI_VALUE)
#define LSI_VALUE               32000U      /*!< LSI Typical Value in Hz                */
#endif

/**
  * @}
  */


/** @defgroup CONFIG_LL_System_Configuration CONFIG LL System Configuration
  * @brief    CONFIG LL System Configuration
  * @note     This is the LL system configuration section
  * @{
  */

#define TICK_INT_PRIORITY       0x07U       /*!< tick interrupt priority, set to lowest             */
#define USE_RTOS                0U          /*!< Support for RTOS (Unsupported in current version)  */
#define PREFETCH_ENABLE         1U          /*!< Flash prefetch feature                             */

/**
  * @}
  */

/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"
#include "tae32f53xx_ll_sysctrl.h"


/* Internal Class Peripheral */
#ifdef LL_CORTEX_MODULE_ENABLED
#include "tae32f53xx_ll_cortex.h"
#endif

#ifdef LL_FPLL_MODULE_ENABLED
#include "tae32f53xx_ll_fpll.h"
#endif

#ifdef LL_LVD_MODULE_ENABLED
#include "tae32f53xx_ll_lvdctrl.h"
#endif

#ifdef LL_DMA_MODULE_ENABLED
#include "tae32f53xx_ll_dma.h"
#endif

#ifdef LL_FLASH_MODULE_ENABLED
#include "tae32f53xx_ll_flash.h"
#endif

#ifdef LL_DFLASH_MODULE_ENABLED
#include "tae32f53xx_ll_dflash.h"
#endif

#ifdef LL_WWDG_MODULE_ENABLED
#include "tae32f53xx_ll_wwdg.h"
#endif

#ifdef LL_IWDG_MODULE_ENABLED
#include "tae32f53xx_ll_iwdg.h"
#endif

#ifdef LL_TMR_MODULE_ENABLED
#include "tae32f53xx_ll_tmr.h"
#endif

#ifdef LL_IIR_MODULE_ENABLED
#include "tae32f53xx_ll_iir.h"
#endif


/* Interface Class Peripheral */
#ifdef LL_GPIO_MODULE_ENABLED
#include "tae32f53xx_ll_gpio.h"
#endif

#ifdef LL_UART_MODULE_ENABLED
#include "tae32f53xx_ll_uart.h"
#endif

#ifdef LL_I2C_MODULE_ENABLED
#include "tae32f53xx_ll_i2c.h"
#endif

#ifdef LL_CAN_MODULE_ENABLED
#include "tae32f53xx_ll_can.h"
#endif

#ifdef LL_DALI_MODULE_ENABLED
#include "tae32f53xx_ll_dali.h"
#endif

#ifdef LL_USB_MODULE_ENABLED
#include "tae32f53xx_ll_usb.h"
#endif


/* Analog Class Peripheral */
#ifdef LL_ADC_MODULE_ENABLED
#include "tae32f53xx_ll_adc.h"
#endif

#ifdef LL_DAC_MODULE_ENABLED
#include "tae32f53xx_ll_dac.h"
#endif

#ifdef LL_CMP_MODULE_ENABLED
#include "tae32f53xx_ll_cmp.h"
#endif

#ifdef LL_ECU_MODULE_ENABLED
#include "tae32f53xx_ll_ecu.h"
#endif

#ifdef LL_HRPWM_MODULE_ENABLED
#include "tae32f53xx_ll_hrpwm.h"
#endif


/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup CONFIG_LL_Exported_Macros CONFIG LL Exported Macros
  * @brief    CONFIG LL Exported Macros
  * @{
  */

/** @defgroup CONFIG_LL_Assert_Selection CONFIG LL Assert Selection
  * @brief    CONFIG LL Assert Selection
  * @{
  */

/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the LL drivers code
  */
//#define USE_FULL_ASSERT


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line);

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr)      ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
#else
#define assert_param(expr)      ((void)0U)
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions ------------------------------------------------------- */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

