/**
  ******************************************************************************
  * @file    tae32g58xx_ll_conf.h
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
#ifndef _TAE32G58XX_LL_CONF_H_
#define _TAE32G58XX_LL_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_GPIO_Flow_LED_Example
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPIO_Flow_LED_CONFIG_LL_Exported_Constants GPIO_Flow_LED CONFIG LL Exported Constants
  * @brief    GPIO_Flow_LED CONFIG LL Exported Constants
  * @{
  */

/** @defgroup GPIO_Flow_LED_CONFIG_LL_Module_Selection GPIO_Flow_LED CONFIG LL Module Selection
  * @brief    GPIO_Flow_LED CONFIG LL Module Selection
  * @note     This is the list of modules to be used in the LL driver
  * @{
  */

/* Internal Class Peripheral */
#define LL_MODULE_ENABLED           /*!< LL Module Enable       */
#define LL_CORTEX_MODULE_ENABLED    /*!< Cortex Module Enable   */
#define LL_DMA_MODULE_ENABLED       /*!< DMA Module Enable      */
#define LL_EFLASH_MODULE_ENABLED    /*!< EFLASH Module Enable   */
#define LL_TMR_MODULE_ENABLED       /*!< TMR Module Enable      */
#define LL_QEI_MODULE_ENABLED       /*!< QEI Module Enable      */
#define LL_IIR_MODULE_ENABLED       /*!< IIR Module Enable      */
#define LL_CORDIC_MODULE_ENABLED    /*!< CORDIC Module Enable   */
#define LL_IWDG_MODULE_ENABLED      /*!< IWDG Module Enable     */
#define LL_WWDG_MODULE_ENABLED      /*!< WWDG Module Enable     */

/* Interface Class Peripheral */
#define LL_GPIO_MODULE_ENABLED      /*!< GPIO Module Enable     */
#define LL_UART_MODULE_ENABLED      /*!< UART Module Enable     */
#define LL_I2C_MODULE_ENABLED       /*!< I2C Module Enable      */
#define LL_SPI_MODULE_ENABLED       /*!< SPI Module Enable      */
#define LL_CAN_MODULE_ENABLED       /*!< CAN Module Enable      */
#define LL_USB_MODULE_ENABLED       /*!< USB Module Enable      */
#define LL_XIF_MODULE_ENABLED       /*!< XIF Module Enable      */

/* Analog Class Peripheral */
#define LL_ADC_MODULE_ENABLED       /*!< ADC Module Enable      */
#define LL_DAC_MODULE_ENABLED       /*!< DAC Module Enable      */
#define LL_CMP_MODULE_ENABLED       /*!< CMP Module Enable      */
#define LL_HRPWM_MODULE_ENABLED     /*!< HRPWM Module Enable    */
#define LL_PDM_MODULE_ENABLED       /*!< PDM Module Enable      */

/**
  * @}
  */


/** @defgroup GPIO_Flow_LED_CONFIG_LL_Oscillator_Values_Adaptation GPIO_Flow_LED CONFIG LL Oscillator Values Adaptation
  * @brief    GPIO_Flow_LED CONFIG LL Oscillator Values Adaptation
  * @{
  */

/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the PLL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#define HSE_VALUE               (8000000U)

/**
  * @}
  */


/** @defgroup GPIO_Flow_LED_CONFIG_LL_System_Configuration GPIO_Flow_LED CONFIG LL System Configuration
  * @brief    GPIO_Flow_LED CONFIG LL System Configuration
  * @note     This is the LL system configuration section
  * @{
  */

#define TICK_INT_PRIORITY       (0x0FU)     /*!< tick interrupt priority, set to lowest             */
#define PREFETCH_ENABLE         (1U)        /*!< EFlash prefetch feature                            */

/**
  * @}
  */

/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"
#include "tae32g58xx_ll_rcu.h"
#include "tae32g58xx_ll_sysctrl.h"
#include "tae32g58xx_ll_usb_com.h"


/* Internal Class Peripheral */
#ifdef LL_CORTEX_MODULE_ENABLED
#include "tae32g58xx_ll_cortex.h"
#endif

#ifdef LL_DMA_MODULE_ENABLED
#include "tae32g58xx_ll_dma.h"
#endif

#ifdef LL_EFLASH_MODULE_ENABLED
#include "tae32g58xx_ll_eflash.h"
#endif

#ifdef LL_TMR_MODULE_ENABLED
#include "tae32g58xx_ll_tmr.h"
#endif

#ifdef LL_QEI_MODULE_ENABLED
#include "tae32g58xx_ll_qei.h"
#endif

#ifdef LL_IIR_MODULE_ENABLED
#include "tae32g58xx_ll_iir.h"
#endif

#ifdef LL_CORDIC_MODULE_ENABLED
#include "tae32g58xx_ll_cordic.h"
#endif

#ifdef LL_IWDG_MODULE_ENABLED
#include "tae32g58xx_ll_iwdg.h"
#endif

#ifdef LL_WWDG_MODULE_ENABLED
#include "tae32g58xx_ll_wwdg.h"
#endif


/* Interface Class Peripheral */
#ifdef LL_GPIO_MODULE_ENABLED
#include "tae32g58xx_ll_gpio.h"
#endif

#ifdef LL_UART_MODULE_ENABLED
#include "tae32g58xx_ll_uart.h"
#endif

#ifdef LL_I2C_MODULE_ENABLED
#include "tae32g58xx_ll_i2c.h"
#endif

#ifdef LL_SPI_MODULE_ENABLED
#include "tae32g58xx_ll_spi.h"
#endif

#ifdef LL_CAN_MODULE_ENABLED
#include "tae32g58xx_ll_can.h"
#endif

#ifdef LL_USB_MODULE_ENABLED
#include "tae32g58xx_ll_usb.h"
#endif

#ifdef LL_XIF_MODULE_ENABLED
#include "tae32g58xx_ll_xif.h"
#endif


/* Analog Class Peripheral */
#ifdef LL_ADC_MODULE_ENABLED
#include "tae32g58xx_ll_adc.h"
#endif

#ifdef LL_DAC_MODULE_ENABLED
#include "tae32g58xx_ll_dac.h"
#endif

#ifdef LL_CMP_MODULE_ENABLED
#include "tae32g58xx_ll_cmp.h"
#endif

#ifdef LL_HRPWM_MODULE_ENABLED
#include "tae32g58xx_ll_hrpwm.h"
#endif

#ifdef LL_PDM_MODULE_ENABLED
#include "tae32g58xx_ll_pdm.h"
#endif


/* Exported Types ------------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPIO_Flow_LED_CONFIG_LL_Exported_Macros GPIO_Flow_LED CONFIG LL Exported Macros
  * @brief    GPIO_Flow_LED CONFIG LL Exported Macros
  * @{
  */

/** @defgroup GPIO_Flow_LED_CONFIG_LL_Assert_Selection GPIO_Flow_LED CONFIG LL Assert Selection
  * @brief    GPIO_Flow_LED CONFIG LL Assert Selection
  * @{
  */

/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the LL drivers code
  */
//#define USE_FULL_ASSERT


#ifdef USE_FULL_ASSERT

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


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32G58XX_LL_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

