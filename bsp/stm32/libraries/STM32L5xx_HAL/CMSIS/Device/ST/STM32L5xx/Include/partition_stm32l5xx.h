/**
  ******************************************************************************
  * @file    partition_stm32l5xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32L5xx Device Header File for Initial Setup for
  *          Secure / Non-Secure Zones based on CMSIS CORE V5.3.1
  *
  *          The file is included in system_stm32l5xx_s.c in secure application.
  *          It includes the configuration section that allows to select the
  *          STM32L5xx device partitioning file for system core secure attributes
  *          and interrupt secure and non-secure assignment.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Apache License, Version 2.0,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/Apache-2.0
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l5xx
  * @{
  */

#ifndef PARTITION_STM32L5XX_H
#define PARTITION_STM32L5XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Secure_configuration_section
  * @{
  */

#if defined(STM32L552xx)
  #include "partition_stm32l552xx.h"
#elif defined(STM32L562xx)
  #include "partition_stm32l562xx.h"
#else
  #error "Please select first the target STM32L5xx device used in your application (in stm32l5xx.h file)"
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARTITION_STM32L5XX_H */
/**
  * @}
  */

/**
  * @}
  */




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
