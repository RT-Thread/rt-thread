/**
  ******************************************************************************
  * @file    ft32f0xx_conf.h
  * @author  FMD-AE
  * @version V1.0.0
  * @date    2021-8-2
  * @brief   Library configuration file.
  ******************************************************************************
*/

#ifndef __FT32F030XX_CONF_H
#define __FT32F030XX_CONF_H

#ifdef _RTE_
#include "RTE_Components.h"             /* Component selection */
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef  RTE_DEVICE_ADC
#include "ft32f0xx_adc.h"
#endif  /*RTE_DEVICE_ADC*/

#ifdef   RTE_DEVICE_COMP
#include "ft32f0xx_comp.h"
#endif  /*RTE_DEVICE_COMP*/

#ifdef   RTE_DEVICE_CRC
#include "ft32f0xx_crc.h"
#endif  /*RTE_DEVICE_CRC*/

#ifdef   RTE_DEVICE_CRS
#include "ft32f0xx_crs.h"
#endif  /*RTE_DEVICE_CRS*/

#ifdef   RTE_DEVICE_DAC
#include "ft32f0xx_dac.h"
#endif  /*RTE_DEVICE_DAC*/

#ifdef   RTE_DEVICE_DMA
#include "ft32f0xx_dma.h"
#endif  /*RTE_DEVICE_DMA*/

#ifdef   RTE_DEVICE_DBGMCU
#include "ft32f0xx_debug.h"
#endif  /*RTE_DEVICE_DBGMCU*/

#ifdef   RTE_DEVICE_EXTI
#include "ft32f0xx_exti.h"
#endif  /*RTE_DEVICE_EXTI*/

#ifdef   RTE_DEVICE_FLASH
#include "ft32f0xx_flash.h"
#endif  /*RTE_DEVICE_FLASH*/

#ifdef   RTE_DEVICE_GPIO
#include "ft32f0xx_gpio.h"
#endif  /*RTE_DEVICE_GPIO*/

#ifdef   RTE_DEVICE_I2C
#include "ft32f0xx_i2c.h"
#endif  /*RTE_DEVICE_I2C*/

#ifdef   RTE_DEVICE_IWDG
#include "ft32f0xx_iwdg.h"
#endif  /*RTE_DEVICE_IWDG*/

#ifdef   RTE_DEVICE_MISC
#include "ft32f0xx_misc.h"
#endif  /*RTE_DEVICE_MISC*/

#ifdef   RTE_DEVICE_OPA
#include "ft32f0xx_opa.h"
#endif  /*RTE_DEVICE_OPA*/

#ifdef   RTE_DEVICE_PWR
#include "ft32f0xx_pwr.h"
#endif  /*RTE_DEVICE_PWR*/

#ifdef   RTE_DEVICE_RCC
#include "ft32f0xx_rcc.h"
#endif  /*RTE_DEVICE_RCC*/

#ifdef   RTE_DEVICE_RTC
#include "ft32f0xx_rtc.h"
#endif  /*RTE_DEVICE_RTC*/

#ifdef   RTE_DEVICE_SPI
#include "ft32f0xx_spi.h"
#endif  /*RTE_DEVICE_SPI*/

#ifdef   RTE_DEVICE_SYSCFG
#include "ft32f0xx_syscfg.h"
#endif  /*RTE_DEVICE_SYSCFG*/

#ifdef   RTE_DEVICE_TIM
#include "ft32f0xx_tim.h"
#endif  /*RTE_DEVICE_TIM*/

#ifdef   RTE_DEVICE_USART
#include "ft32f0xx_usart.h"
#endif  /*RTE_DEVICE_USART*/

#ifdef   RTE_DEVICE_WWDG
#include "ft32f0xx_wwdg.h"
#endif  /*RTE_DEVICE_WWDG*/



#include "stdio.h"

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

#endif /* __FT32F030X8_CONF_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
