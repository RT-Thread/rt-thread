/**
  ******************************************************************************
  * @file    partition_stm32h5xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H5xx Device Header File for Initial Setup for Secure /
  *          Non-Secure Zones for ARMCM33 based on CMSIS CORE partition_ARMCM33.h
  *          Template.
  *
  *          The file is included in system_stm32h5xx_s.c in secure application.
  *          It includes the configuration section that allows to select the
  *          STM32H5xx device partitioning file for system core secure attributes
  *          and interrupt secure and non-secure assignment.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32h5xx
  * @{
  */

#ifndef PARTITION_STM32H5XX_H
#define PARTITION_STM32H5XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Secure_configuration_section
  * @{
  */

#if defined(STM32H573xx)
  #include "partition_stm32h573xx.h"
#elif defined(STM32H563xx)
  #include "partition_stm32h563xx.h"
#elif defined(STM32H562xx)
  #include "partition_stm32h562xx.h"
#else
  #error "Please select first the target STM32H5xx device used in your application (in stm32h5xx.h file)"
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARTITION_STM32H5XX_H */
/**
  * @}
  */

/**
  * @}
  */
