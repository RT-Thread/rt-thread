/**
  ******************************************************************************
  * @file    hk32f0xx_hk_conf.h
  * @brief   hk32f0xx  configuration file.
  *          The file is the unique include file that the application programmer
	*          is using in the C source code.it is a patch file 
  ******************************************************************************
**/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0xx_HK_CONF_H
#define __HK32F0xx_HK_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif
 
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver with HK32F0XX 
  */
 
#include <hk32f0xx_rcc.h>
#include <hk32f0xx_usart.h>
#include <hk32f0xx_gpio.h>
#include <hk32f0xx_exti.h>
#include <hk32f0xx_syscfg.h>
#include <hk32f0xx_misc.h>
#include <hk32f0xx_i2c.h>
#include <hk32f0xx_spi.h>
// 除法开方模块，如果用到此功能，则把一下宏定义注释去掉即可
#define HAL_DIVSQRT_MODULE_ENABLED   


/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */

#ifdef HAL_DIVSQRT_MODULE_ENABLED
 #include "hk32f0xx_divsqrt.h"
#endif /* HAL_RCC_MODULE_ENABLED */
/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif
