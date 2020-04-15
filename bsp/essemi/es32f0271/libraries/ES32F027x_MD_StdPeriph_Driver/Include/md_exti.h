/**
  ******************************************************************************
  * @file    md_EXTI.h
  * @brief   ES32F0271 EXTI HEAD File.
  *
  * @version V1.00.01
  * @date    22/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_EXTI_H__
#define __MD_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_exti.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (EXTI)
/** @defgroup EXTI EXTI
  * @brief EXTI micro driver
  * @{
  */


/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/* Public constants -----------------------------------------------------------*/

/** @defgroup MD_EXTI_Public_Constants EXTI Public Constants
  * @{
  */

/** @defgroup MD_EXTI_PC_Source EXTI Line Source 
  * @{
  */
#define MD_EXTI_Pin_GPIOA                 (0x00000000UL)       /*!< @brief Select GPIOA for EXTIx */
#define MD_EXTI_Pin_GPIOB                  (0x00000001UL)       /*!< @brief Select GPIOB for EXTIx */
#define MD_EXTI_Pin_GPIOC                 (0x00000002UL)       /*!< @brief Select GPIOC for EXTIx */
#define MD_EXTI_Pin_GPIOD                  (0x00000003UL)       /*!< @brief Select GPIOD for EXTIx */
 
 /**  
  * @} MD_EXTI_PC_Source 
  */

/**  
* @} MD_EXTI_Public_Constants 
*/



/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_EXTI_Public_Macros EXTI Public Macros
  * @{
  */



/** @defgroup MD_EXTI_PF_Basic_Configuration EXTI Configuration Management
  * @{
  */
/**
  * @brief  Set EXTI interrupt configuration register 1
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->ICFG1
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->ICFG1, value);
}

/**
  * @brief  Get EXTI interrupt configuration register 1
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->ICFG1));
}

/**
  * @brief  Set EXTI interrupt configuration register 2
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->ICFG2
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->ICFG2, value);
}

/**
  * @brief  Get EXTI interrupt configuration register 2
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->ICFG2));
}

/**
  * @brief  Set EXTI0 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio0(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO0_MSK, Source);
}

/**
  * @brief  Get EXTI0 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio0(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO0_MSK)>>EXTI_ICFG1_GPIO0_POSS);
}

/**
  * @brief  Set EXTI1 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio1(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO1_MSK, Source << EXTI_ICFG1_GPIO1_POSS);
}

/**
  * @brief  Get EXTI1 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO1_MSK)>>EXTI_ICFG1_GPIO1_POSS);
}

/**
  * @brief  Set EXTI2 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio2(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO2_MSK, Source << EXTI_ICFG1_GPIO2_POSS);
}

/**
  * @brief  Get EXTI2 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO2_MSK)>>EXTI_ICFG1_GPIO2_POSS);
}

/**
  * @brief  Set EXTI3 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio3(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO3_MSK, Source << EXTI_ICFG1_GPIO3_POSS);
}

/**
  * @brief  Get EXTI3 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio3(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO3_MSK)>>EXTI_ICFG1_GPIO0_POSS);
}

/**
  * @brief  Set EXTI4 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio4(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO4_MSK, Source << EXTI_ICFG1_GPIO4_POSS);
}

/**
  * @brief  Get EXTI4 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio4(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO4_MSK)>>EXTI_ICFG1_GPIO4_POSS);
}

/**
  * @brief  Set EXTI5 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio5(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO5_MSK, Source << EXTI_ICFG1_GPIO5_POSS);
}

/**
  * @brief  Get EXTI5 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio5(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO5_MSK)>>EXTI_ICFG1_GPIO5_POSS);
}

/**
  * @brief  Set EXTI6 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio6(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO6_MSK, Source << EXTI_ICFG1_GPIO6_POSS);
}

/**
  * @brief  Get EXTI6 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio6(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO6_MSK)>>EXTI_ICFG1_GPIO6_POSS);
}

/**
  * @brief  Set EXTI7 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg1_gpio7(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG1, EXTI_ICFG1_GPIO7_MSK, Source << EXTI_ICFG1_GPIO7_POSS);
}

/**
  * @brief  Get EXTI7 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg1_gpio7(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG1, EXTI_ICFG1_GPIO7_MSK)>>EXTI_ICFG1_GPIO7_POSS);
}


/**
  * @brief  Set EXTI8 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio8(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO8_MSK, Source << EXTI_ICFG2_GPIO8_POSS);
}

/**
  * @brief  Get EXTI8 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio8(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO8_MSK)>>EXTI_ICFG2_GPIO8_POSS);
}

/**
  * @brief  Set EXTI9 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio9(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO9_MSK, Source << EXTI_ICFG2_GPIO9_POSS);
}

/**
  * @brief  Get EXTI9 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio9(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO9_MSK)>>EXTI_ICFG2_GPIO9_POSS);
}

/**
  * @brief  Set EXTI10 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio10(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO10_MSK, Source << EXTI_ICFG2_GPIO10_POSS);
}

/**
  * @brief  Get EXTI10 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio10(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO10_MSK)>>EXTI_ICFG2_GPIO10_POSS);
}

/**
  * @brief  Set EXTI11 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio11(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO11_MSK, Source << EXTI_ICFG2_GPIO11_POSS);
}

/**
  * @brief  Get EXTI11 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio11(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO11_MSK)>>EXTI_ICFG2_GPIO11_POSS);
}

/**
  * @brief  Set EXTI12 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio12(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO12_MSK, Source << EXTI_ICFG2_GPIO12_POSS);
}

/**
  * @brief  Get EXTI12 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio12(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO12_MSK)>>EXTI_ICFG2_GPIO12_POSS);
}

/**
  * @brief  Set EXTI13 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio13(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO13_MSK, Source << EXTI_ICFG2_GPIO13_POSS);
}

/**
  * @brief  Get EXTI13 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio13(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO13_MSK)>>EXTI_ICFG2_GPIO13_POSS);
}

/**
  * @brief  Set EXTI14 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio14(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO14_MSK, Source << EXTI_ICFG2_GPIO14_POSS);
}

/**
  * @brief  Get EXTI14 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio14(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO14_MSK)>>EXTI_ICFG2_GPIO14_POSS);
}

/**
  * @brief  Set EXTI15 configuration
  * @param  exti EXTI Instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  * @retval None
  */
__STATIC_INLINE void md_exti_set_icfg2_gpio15(EXTI_TypeDef *exti, uint32_t Source)
{
  MODIFY_REG(exti->ICFG2, EXTI_ICFG2_GPIO15_MSK, Source << EXTI_ICFG2_GPIO15_POSS);
}

/**
  * @brief  Get EXTI15 configuration
  * @param  exti EXTI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_EXTI_Pin_GPIOA
  *         @arg @ref MD_EXTI_Pin_GPIOB
  *         @arg @ref MD_EXTI_Pin_GPIOC
  *         @arg @ref MD_EXTI_Pin_GPIOD
  */
__STATIC_INLINE uint32_t md_exti_get_icfg2_gpio15(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->ICFG2, EXTI_ICFG2_GPIO15_MSK)>>EXTI_ICFG2_GPIO15_POSS);
}  

/**
  * @} MD_EXTI_PF_Basic_Configuration
  */

/** @defgroup MD_EXTI_PF_RTS EXTI Rising Edge Trigger Selection Register 
  * @{
  */

/**
  * @brief  Set rising trigger event configuration bit of line 
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->RTS
  * @retval None
  */
__STATIC_INLINE void md_exti_set_rts(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->RTS, value);
}

/**
  * @brief  Get rising trigger event configuration bit of line
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_rts(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->RTS));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO0_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO0_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 0 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO0_MSK) == (EXTI_RTS_GPIO0_MSK));
} 

/**
  * @brief  Enable rising trigger event configuration bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO1_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO1_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO1_MSK) == (EXTI_RTS_GPIO1_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO2_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO2_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 2 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO2_MSK) == (EXTI_RTS_GPIO2_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO3_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio3(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO3_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 3 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO3_MSK) == (EXTI_RTS_GPIO3_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO4_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio4(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO4_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 4 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO4_MSK) == (EXTI_RTS_GPIO4_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO5_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio5(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO5_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 5 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO5_MSK) == (EXTI_RTS_GPIO5_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO6_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio6(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO6_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO6_MSK) == (EXTI_RTS_GPIO6_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO7_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio7(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO7_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 7 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO7_MSK) == (EXTI_RTS_GPIO7_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO8_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio8(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO8_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 8 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO8_MSK) == (EXTI_RTS_GPIO8_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO9_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio9(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO9_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 9 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO9_MSK) == (EXTI_RTS_GPIO9_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO10_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio10(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO10_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 10 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO10_MSK) == (EXTI_RTS_GPIO10_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO11_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio11(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO11_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 11 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO11_MSK) == (EXTI_RTS_GPIO11_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO12_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio12(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO12_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 12 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO12_MSK) == (EXTI_RTS_GPIO12_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO13_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio13(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO13_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 13 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO13_MSK) == (EXTI_RTS_GPIO13_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO14_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO14_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 14 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO14_MSK) == (EXTI_RTS_GPIO14_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_GPIO15_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_gpio15(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_GPIO15_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 15 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_GPIO15_MSK) == (EXTI_RTS_GPIO15_MSK));
}


/**
  * @brief  Enable rising trigger event configuration bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_CMP1_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_CMP1_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 16 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_CMP1_MSK) == (EXTI_RTS_CMP1_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_CMP2_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_cmp2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_CMP2_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 17 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_CMP2_MSK) == (EXTI_RTS_CMP2_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_PVD0_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_pvd0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_PVD0_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 20 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_PVD0_MSK) == (EXTI_RTS_PVD0_MSK));
}

/**
  * @brief  Enable rising trigger event configuration bit of line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_rts_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->RTS, EXTI_RTS_WAKEUP_MSK);
}

/**
  * @brief  Disable rising trigger event configuration bit of line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_rts_wakeup(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->RTS, EXTI_RTS_WAKEUP_MSK);
}

/**
  * @brief  Check if rising trigger event configuration bit of line 21 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_rts_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->RTS, EXTI_RTS_WAKEUP_MSK) == (EXTI_RTS_WAKEUP_MSK));
}

/**
  * @} MD_EXTI_PF_RTS
  */

/** @defgroup MD_EXTI_PF_FTS EXTI Falling Edge Trigger Selection Register
  * @{
  */
 
/**
  * @brief  Set falling trigger event configuration bit of line 
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->FTS
  * @retval None
  */
__STATIC_INLINE void md_exti_set_fts(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->FTS, value);
}

/**
  * @brief  Get falling trigger event configuration bit of line
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_fts(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->FTS));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO0_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO0_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 0 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO0_MSK) == (EXTI_FTS_GPIO0_MSK));
} 

/**
  * @brief  Enable falling trigger event configuration bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO1_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO1_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO1_MSK) == (EXTI_FTS_GPIO1_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO2_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO2_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 2 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO2_MSK) == (EXTI_FTS_GPIO2_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO3_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio3(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO3_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 3 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO3_MSK) == (EXTI_FTS_GPIO3_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO4_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio4(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO4_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 4 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO4_MSK) == (EXTI_FTS_GPIO4_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO5_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio5(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO5_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 5 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO5_MSK) == (EXTI_FTS_GPIO5_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO6_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio6(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO6_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 6 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO6_MSK) == (EXTI_FTS_GPIO6_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO7_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio7(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO7_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 7 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO7_MSK) == (EXTI_FTS_GPIO7_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO8_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio8(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO8_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 8 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO8_MSK) == (EXTI_FTS_GPIO8_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO9_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio9(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO9_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 9 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO9_MSK) == (EXTI_FTS_GPIO9_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO10_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio10(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO10_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 10 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO10_MSK) == (EXTI_FTS_GPIO10_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO11_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio11(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO11_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 11 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO11_MSK) == (EXTI_FTS_GPIO11_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO12_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio12(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO12_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 12 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO12_MSK) == (EXTI_FTS_GPIO12_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO13_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio13(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO13_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 13 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO13_MSK) == (EXTI_FTS_GPIO13_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO14_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO14_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 14 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO14_MSK) == (EXTI_FTS_GPIO14_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_GPIO15_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_gpio15(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO15_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 15 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_GPIO15_MSK) == (EXTI_FTS_GPIO15_MSK));
}



/**
  * @brief  Enable falling trigger event configuration bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_CMP1_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_CMP1_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 16 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_CMP1_MSK) == (EXTI_FTS_CMP1_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_CMP2_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 18
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_cmp2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_CMP2_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 18 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_CMP2_MSK) == (EXTI_RTS_CMP2_MSK));
}


/**
  * @brief  Enable falling trigger event configuration bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_PVD0_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_pvd0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_PVD0_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 17 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_PVD0_MSK) == (EXTI_FTS_PVD0_MSK));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_fts_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->FTS, EXTI_FTS_WAKEUP_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_fts_wakeup(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_WAKEUP_MSK);
}

/**
  * @brief  Check if falling trigger event configuration bit of line 21 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_fts_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->FTS, EXTI_FTS_WAKEUP_MSK) == (EXTI_FTS_WAKEUP_MSK));
}



/**
  * @} MD_EXTI_PF_FTS
  */

/** @defgroup MD_EXTI_PF_SWI EXTI Software Interrupt Event register
  * @{
  */
  
/**
  * @brief  Set software interrupt on line
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->SWI
  * @retval None
  */
__STATIC_INLINE void md_exti_set_swi(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->SWI, value);
}

/**
  * @brief  Get software interrupt on line
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_swi(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->SWI));
}

/**
  * @brief  Enable falling trigger event configuration bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO0_MSK);
}

/**
  * @brief  Disable software interrupt on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO0_MSK);
}

/**
  * @brief  Check if software interrupt on line 0 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO0_MSK) == (EXTI_SWI_GPIO0_MSK));
} 

/**
  * @brief  Enable software interrupt on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO1_MSK);
}

/**
  * @brief  Disable software interrupt on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO1_MSK);
}

/**
  * @brief  Check if software interrupt on line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO1_MSK) == (EXTI_SWI_GPIO1_MSK));
}

/**
  * @brief  Enable software interrupt on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO2_MSK);
}

/**
  * @brief  Disable software interrupt on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO2_MSK);
}

/**
  * @brief  Check if software interrupt on line 2 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO2_MSK) == (EXTI_SWI_GPIO2_MSK));
}

/**
  * @brief  Enable software interrupt on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO3_MSK);
}

/**
  * @brief  Disable software interrupt on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio3(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO3_MSK);
}

/**
  * @brief  Check if software interrupt on line 3 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO3_MSK) == (EXTI_SWI_GPIO3_MSK));
}

/**
  * @brief  Enable software interrupt on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO4_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio4(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO4_MSK);
}

/**
  * @brief  Check if software interrupt on line 4 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO4_MSK) == (EXTI_SWI_GPIO4_MSK));
}

/**
  * @brief  Enable software interrupt on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO5_MSK);
}

/**
  * @brief  Disable software interrupt on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio5(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO5_MSK);
}

/**
  * @brief  Check if software interrupt on line 5 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO5_MSK) == (EXTI_SWI_GPIO5_MSK));
}

/**
  * @brief  Enable software interrupt on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO6_MSK);
}

/**
  * @brief  Disable software interrupt on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio6(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO6_MSK);
}

/**
  * @brief  Check if software interrupt on line 6 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO6_MSK) == (EXTI_SWI_GPIO6_MSK));
}

/**
  * @brief  Enable software interrupt on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO7_MSK);
}

/**
  * @brief  Disable software interrupt on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio7(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO7_MSK);
}

/**
  * @brief  Check if software interrupt on line 7 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO7_MSK) == (EXTI_SWI_GPIO7_MSK));
}

/**
  * @brief  Enable software interrupt on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO8_MSK);
}

/**
  * @brief  Disable software interrupt on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio8(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO8_MSK);
}

/**
  * @brief  Check if software interrupt on line 8 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO8_MSK) == (EXTI_SWI_GPIO8_MSK));
}

/**
  * @brief  Enable software interrupt on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO9_MSK);
}

/**
  * @brief  Disable software interrupt on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio9(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO9_MSK);
}

/**
  * @brief  Check if software interrupt on line 9 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO9_MSK) == (EXTI_SWI_GPIO9_MSK));
}

/**
  * @brief  Enable software interrupt on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO10_MSK);
}

/**
  * @brief  Disable software interrupt on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio10(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO10_MSK);
}

/**
  * @brief  Check if software interrupt on line 10 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO10_MSK) == (EXTI_SWI_GPIO10_MSK));
}

/**
  * @brief  Enable software interrupt on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO11_MSK);
}

/**
  * @brief  Disable falling trigger event configuration bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio11(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->FTS, EXTI_FTS_GPIO11_MSK);
}

/**
  * @brief  Check if software interrupt on line 11 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO11_MSK) == (EXTI_SWI_GPIO11_MSK));
}

/**
  * @brief  Enable software interrupt on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO12_MSK);
}

/**
  * @brief  Disable software interrupt on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio12(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO12_MSK);
}

/**
  * @brief  Check if software interrupt on line 12 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO12_MSK) == (EXTI_SWI_GPIO12_MSK));
}

/**
  * @brief  Enable software interrupt on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO13_MSK);
}

/**
  * @brief  Disable software interrupt on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio13(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO13_MSK);
}

/**
  * @brief  Check if software interrupt on line 13 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO13_MSK) == (EXTI_SWI_GPIO13_MSK));
}

/**
  * @brief  Enable software interrupt on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO14_MSK);
}

/**
  * @brief  Disable software interrupt on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO14_MSK);
}

/**
  * @brief  Check if software interrupt on line 14 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO14_MSK) == (EXTI_SWI_GPIO14_MSK));
}

/**
  * @brief  Enable software interrupt on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_GPIO15_MSK);
}

/**
  * @brief  Disable software interrupt on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_gpio15(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_GPIO15_MSK);
}

/**
  * @brief  Check if software interrupt on line is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_GPIO15_MSK) == (EXTI_SWI_GPIO15_MSK));
}

/**
  * @brief  Enable software interrupt on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_CMP1_MSK);
}

/**
  * @brief  Disable software interrupt on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_CMP1_MSK);
}

/**
  * @brief  Check if software interrupt on line 16 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_CMP1_MSK) == (EXTI_SWI_CMP1_MSK));
}

/**
  * @brief  Enable software interrupt on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_CMP2_MSK);
}

/**
  * @brief  Disable software interrupt on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_cmp2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_CMP2_MSK);
}

/**
  * @brief  Check if software interrupt on line 17 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_CMP2_MSK) == (EXTI_SWI_CMP2_MSK));
}


/**
  * @brief  Enable software interrupt on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_PVD0_MSK);
}

/**
  * @brief  Disable software interrupt on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_pvd0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_PVD0_MSK);
}

/**
  * @brief  Check if software interrupt on line 20 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_PVD0_MSK) == (EXTI_SWI_PVD0_MSK));
}

/**
  * @brief  Enable software interrupt on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_swi_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->SWI, EXTI_SWI_WAKEUP_MSK);
}

/**
  * @brief  Disable software interrupt on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_swi_wakeup(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->SWI, EXTI_SWI_WAKEUP_MSK);
}

/**
  * @brief  Check if software interrupt on line 21 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_swi_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->SWI, EXTI_SWI_WAKEUP_MSK) == (EXTI_SWI_WAKEUP_MSK));
}

/**
  * @} MD_EXTI_PF_SWI
  */


/** @defgroup MD_EXTI_PF_ADTE EXTI ADC Trigger Enable Register
  * @{
  */
/**
  * @brief  Set ADC trigger enable on line 
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->ADTE
  * @retval None
  */
__STATIC_INLINE void md_exti_set_adte(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->ADTE, value);
}

/**
  * @brief  Get ADC trigger enable on line
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_get_adte(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->ADTE));
}

/**
  * @brief  Enable ADC trigger on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO0_MSK);
}

/**
  * @brief  Disable ADC trigger on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO0_MSK);
}

/**
  * @brief  Check if ADC trigger on line 0 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO0_MSK) == (EXTI_ADTE_GPIO0_MSK));
} 

/**
  * @brief  Enable ADC trigger on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO1_MSK);
}

/**
  * @brief  Disable ADC trigger on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO1_MSK);
}

/**
  * @brief  Check if ADC trigger on line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO1_MSK) == (EXTI_ADTE_GPIO1_MSK));
}

/**
  * @brief  Enable ADC trigger on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO2_MSK);
}

/**
  * @brief  Disable ADC trigger on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO2_MSK);
}

/**
  * @brief  Check if ADC trigger on line 2 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO2_MSK) == (EXTI_ADTE_GPIO2_MSK));
}

/**
  * @brief  Enable ADC trigger on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO3_MSK);
}

/**
  * @brief  Disable ADC trigger on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio3(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO3_MSK);
}

/**
  * @brief  Check if ADC trigger on line 3 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO3_MSK) == (EXTI_ADTE_GPIO3_MSK));
}

/**
  * @brief  Enable ADC trigger on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO4_MSK);
}

/**
  * @brief  Disable ADC trigger on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio4(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO4_MSK);
}

/**
  * @brief  Check if ADC trigger on line 4 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO4_MSK) == (EXTI_ADTE_GPIO4_MSK));
}

/**
  * @brief  Enable ADC trigger on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO5_MSK);
}

/**
  * @brief  Disable ADC trigger on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio5(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO5_MSK);
}

/**
  * @brief  Check if ADC trigger on line 5 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO5_MSK) == (EXTI_ADTE_GPIO5_MSK));
}

/**
  * @brief  Enable ADC trigger on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO6_MSK);
}

/**
  * @brief  Disable ADC trigger on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio6(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO6_MSK);
}

/**
  * @brief  Check if ADC trigger on line 6 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO6_MSK) == (EXTI_ADTE_GPIO6_MSK));
}

/**
  * @brief  Enable ADC trigger on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO7_MSK);
}

/**
  * @brief  Disable ADC trigger on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio7(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO7_MSK);
}

/**
  * @brief  Check if ADC trigger on line 7 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO7_MSK) == (EXTI_ADTE_GPIO7_MSK));
}

/**
  * @brief  Enable ADC trigger on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO8_MSK);
}

/**
  * @brief  Disable ADC trigger on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio8(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO8_MSK);
}

/**
  * @brief  Check if ADC trigger on line 8 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO8_MSK) == (EXTI_ADTE_GPIO8_MSK));
}

/**
  * @brief  Enable ADC trigger on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO9_MSK);
}

/**
  * @brief  Disable ADC trigger on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio9(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO9_MSK);
}

/**
  * @brief  Check if ADC trigger on line 9 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO9_MSK) == (EXTI_ADTE_GPIO9_MSK));
}

/**
  * @brief  Enable ADC trigger on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO10_MSK);
}

/**
  * @brief  Disable ADC trigger on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio10(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO10_MSK);
}

/**
  * @brief  Check if ADC trigger on line 10 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO10_MSK) == (EXTI_ADTE_GPIO10_MSK));
}

/**
  * @brief  Enable ADC trigger on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO11_MSK);
}

/**
  * @brief  Disable ADC trigger on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio11(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO11_MSK);
}

/**
  * @brief  Check if ADC trigger on line 11 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO11_MSK) == (EXTI_ADTE_GPIO11_MSK));
}

/**
  * @brief  Enable ADC trigger on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO12_MSK);
}

/**
  * @brief  Disable ADC trigger on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio12(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO12_MSK);
}

/**
  * @brief  Check if ADC trigger on line 12 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO12_MSK) == (EXTI_ADTE_GPIO12_MSK));
}

/**
  * @brief  Enable ADC trigger on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO13_MSK);
}

/**
  * @brief  Disable ADC trigger on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio13(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO13_MSK);
}

/**
  * @brief  Check if ADC trigger on line 13 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO13_MSK) == (EXTI_ADTE_GPIO13_MSK));
}

/**
  * @brief  Enable ADC trigger on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO14_MSK);
}

/**
  * @brief  Disable ADC trigger on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO14_MSK);
}

/**
  * @brief  Check if ADC trigger on line 14 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO14_MSK) == (EXTI_ADTE_GPIO14_MSK));
}

/**
  * @brief  Enable ADC trigger on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_GPIO15_MSK);
}

/**
  * @brief  Disable ADC trigger on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_gpio15(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_GPIO15_MSK);
}

/**
  * @brief  Check if ADC trigger on line is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_GPIO15_MSK) == (EXTI_ADTE_GPIO15_MSK));
}

/**
  * @brief  Enable ADC trigger on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_CMP1_MSK);
}

/**
  * @brief  Disable ADC trigger on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_CMP1_MSK);
}

/**
  * @brief  Check if ADC trigger on line 16 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_CMP1_MSK) == (EXTI_ADTE_CMP1_MSK));
}

/**
  * @brief  Enable ADC trigger on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_CMP2_MSK);
}

/**
  * @brief  Disable ADC trigger on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_cmp2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_CMP2_MSK);
}

/**
  * @brief  Check if ADC trigger on line 17 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_CMP2_MSK) == (EXTI_ADTE_CMP2_MSK));
}

/**
  * @brief  Enable ADC trigger on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_PVD0_MSK);
}

/**
  * @brief  Disable ADC trigger on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_pvd0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_PVD0_MSK);
}

/**
  * @brief  Check if ADC trigger on line 20 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_PVD0_MSK) == (EXTI_ADTE_PVD0_MSK));
}

/**
  * @brief  Enable ADC trigger on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_adte_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ADTE, EXTI_ADTE_WAKEUP_MSK);
}

/**
  * @brief  Disable ADC trigger on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_adte_wakeup(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->ADTE, EXTI_ADTE_WAKEUP_MSK);
}

/**
  * @brief  Check if ADC trigger on line 21 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_adte_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->ADTE, EXTI_ADTE_WAKEUP_MSK) == (EXTI_ADTE_WAKEUP_MSK));
}


/**
  * @} MD_EXTI_PF_ADTE
  */

/** @defgroup MD_EXTI_PF_INTERRUNPT_MANAGEMENT EXTI Interrupt Management
  * @{
  */

/** @defgroup MD_EXTI_PF_IER EXTI Interrupt Enable Register
  * @{
  */


/**
  * @brief  Set interrupt enable on line 
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->IER
  * @retval None
  */
__STATIC_INLINE void md_spi_set_exti_ier(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->IER, value);
}

/**
  * @brief  Enable interrupt on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO0_MSK);
}

/**
  * @brief  Enable interrupt on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO1_MSK);
}

/**
  * @brief  Enable interrupt on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO2_MSK);
}

/**
  * @brief  Enable interrupt on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO3_MSK);
}

/**
  * @brief  Enable interrupt on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO4_MSK);
}

/**
  * @brief  Enable interrupt on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO5_MSK);
}

/**
  * @brief  Enable interrupt on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO6_MSK);
}

/**
  * @brief  Enable interrupt on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO7_MSK);
}

/**
  * @brief  Enable interrupt on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO8_MSK);
}

/**
  * @brief  Enable interrupt on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO9_MSK);
}

/**
  * @brief  Enable interrupt on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO10_MSK);
}

/**
  * @brief  Enable interrupt on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO11_MSK);
}

/**
  * @brief  Enable interrupt on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO12_MSK);
}

/**
  * @brief  Enable interrupt on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO13_MSK);
}

/**
  * @brief  Enable interrupt on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO14_MSK);
}

/**
  * @brief  Enable interrupt on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_GPIO15_MSK);
}


/**
  * @brief  Enable interrupt on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_CMP1_MSK);
}

/**
  * @brief  Enable interrupt on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_CMP2_MSK);
}

/**
  * @brief  Enable interrupt on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_PVD0_MSK);
}

/**
  * @brief  Enable interrupt on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_ier_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IER, EXTI_IER_WAKEUP_MSK);
}

/** 
  * @} MD_EXTI_PF_IER
  */

/** @defgroup MD_EXTI_PF_IDR EXTI Interrupt Disable Register
  * @{
  */

/**
  * @brief  Disable interrupt on line
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->IDR
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->IDR, value);
}


/**
  * @brief  Disable interrupt on line 0 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO0_MSK);
}

/**
  * @brief  Disable interrupt on line 1 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO1_MSK);
}

/**
  * @brief  Disable interrupt on line 2 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO2_MSK);
}

/**
  * @brief  Disable interrupt on line 3 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO3_MSK);
}

/**
  * @brief  Disable interrupt on line 4 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO4_MSK);
}

/**
  * @brief  Disable interrupt on line 5 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO5_MSK);
}

/**
  * @brief  Disable interrupt on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO6_MSK);
}

/**
  * @brief  Disable interrupt on line 7 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO7_MSK);
}

/**
  * @brief  Disable interrupt on line 8 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO8_MSK);
}

/**
  * @brief  Disable interrupt on line 9 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO9_MSK);
}

/**
  * @brief  Disable interrupt on line 10 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO10_MSK);
}

/**
  * @brief  Disable interrupt on line 11 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO11_MSK);
}

/**
  * @brief  Disable interrupt on line 12 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO12_MSK);
}

/**
  * @brief  Disable interrupt on line 13 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO13_MSK);
}

/**
  * @brief  Disable interrupt on line 14 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->IDR, EXTI_IDR_GPIO14_MSK);
}

/**
  * @brief  Disable interrupt on line 15 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_GPIO15_MSK);
}

/**
  * @brief  Disable interrupt on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->IDR, EXTI_IDR_CMP1_MSK);
}

/**
  * @brief  Disable interrupt on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_CMP2_MSK);
}

/**
  * @brief  Disable interrupt on line 20 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_PVD0_MSK);
}

/**
  * @brief  Disable interrupt on line 21 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_idr_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->IDR, EXTI_IDR_WAKEUP_MSK);
}


/** 
  * @} MD_EXTI_PF_IDR
  */

/** @defgroup MD_EXTI_PF_ICR EXTI Interrupt Clear Register
  * @{
  */

/**
  * @brief  Interrupt Clear on line
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->ICR
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->ICR, value);
}

/**
  * @brief  Interrupt Clear on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO0_MSK);
}

/**
  * @brief  Interrupt Clear on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO1_MSK);
}

/**
  * @brief  Interrupt Clear on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO2_MSK);
}

/**
  * @brief  Interrupt Clear on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO3_MSK);
}

/**
  * @brief  Interrupt Clear on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO4_MSK);
}

/**
  * @brief  Interrupt Clear on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO5_MSK);
}

/**
  * @brief  Interrupt Clear on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO6_MSK);
}

/**
  * @brief  Interrupt Clear on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO7_MSK);
}

/**
  * @brief  Interrupt Clear on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO8_MSK);
}

/**
  * @brief  Interrupt Clear on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO9_MSK);
}

/**
  * @brief  Interrupt Clear on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO10_MSK);
}

/**
  * @brief  Interrupt Clear on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO11_MSK);
}

/**
  * @brief  Interrupt Clear on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO12_MSK);
}

/**
  * @brief  Interrupt Clear on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO13_MSK);
}

/**
  * @brief  Interrupt Clear on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO14_MSK);
}

/**
  * @brief  Interrupt Clear on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_GPIO15_MSK);
}


/**
  * @brief  Interrupt Clear on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_CMP1_MSK);
}

/**
  * @brief  Interrupt Clear on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_CMP2_MSK);
}


/**
  * @brief  Interrupt Clear on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_PVD0_MSK);
}

/**
  * @brief  Interrupt Clear on line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_clear_icr_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->ICR, EXTI_ICR_WAKEUP_MSK);
}

/** 
  * @} MD_EXTI_PF_ICR
  */

/** @defgroup MD_EXTI_PF_IVS EXTI Interrupt Valid Status Register
  * @{
  */

/**
  * @brief  Interrupt Valid Status on line
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->IVS
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs(EXTI_TypeDef *exti, uint32_t value)
{
  return (READ_REG(exti->IVS));
}

/**
  * @brief  Interrupt Valid Status on line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO0_MSK) == EXTI_IVS_GPIO0_POS);
}

/**
  * @brief  Interrupt Valid Status on line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO1_MSK) == EXTI_IVS_GPIO1_POS);
}

/**
  * @brief  Interrupt Valid Status on line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO2_MSK) == EXTI_IVS_GPIO2_POS);
}

/**
  * @brief  Interrupt Valid Status on line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO3_MSK) == EXTI_IVS_GPIO3_POS);
}

/**
  * @brief  Interrupt Valid Status on line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO4_MSK) == EXTI_IVS_GPIO4_POS);
}

/**
  * @brief  Interrupt Valid Status on line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO5_MSK)>>EXTI_IVS_GPIO5_POS);
}

/**
  * @brief  Interrupt Valid Status on line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO6_MSK) == EXTI_IVS_GPIO6_POS);
}

/**
  * @brief  Interrupt Valid Status on line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO7_MSK) == EXTI_IVS_GPIO7_POS);
}

/**
  * @brief  Interrupt Valid Status on line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO8_MSK) == EXTI_IVS_GPIO8_POS);
}

/**
  * @brief  Interrupt Valid Status on line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO9_MSK) == EXTI_IVS_GPIO9_POS);
}

/**
  * @brief  Interrupt Valid Status on line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO10_MSK) == EXTI_IVS_GPIO10_POS);
}

/**
  * @brief  Interrupt Valid Status on line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO11_MSK) == EXTI_IVS_GPIO11_POS);
}

/**
  * @brief  Interrupt Valid Status on line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO12_MSK) == EXTI_IVS_GPIO12_POS);
}

/**
  * @brief  Interrupt Valid Status on line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO13_MSK) == EXTI_IVS_GPIO13_POS);
}

/**
  * @brief  Interrupt Valid Status on line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO14_MSK) == EXTI_IVS_GPIO14_POS);
}

/**
  * @brief  Interrupt Valid Status on line 15
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_GPIO15_MSK) == EXTI_IVS_GPIO15_POS);
}

/**
  * @brief  Interrupt Valid Status on line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_CMP1_MSK) == EXTI_IVS_CMP1_POS);
}

/**
  * @brief  Interrupt Valid Status on line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_CMP2_MSK) == EXTI_IVS_CMP2_POS);
}


/**
  * @brief  Interrupt Valid Status on line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_enable_ivs_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_PVD0_MSK) == EXTI_IVS_PVD0_POS);
}

/**
  * @brief  Interrupt Valid Status on line 21
  * @param  exti EXTI Instance
  * @retval None
  */

__STATIC_INLINE uint32_t md_exti_is_enable_ivs_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->IVS, EXTI_IVS_WAKEUP_MSK) == EXTI_IVS_WAKEUP_POS);
}


/** 
  * @} MD_EXTI_PF_IVS
  */

/** @defgroup MD_EXTI_PF_IFM EXTI Interrupt Flag Masked Status Register
  * @{
  */

/**
  * @brief  Check if Interrupt Flag Masked Status on line is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->IFM));
}


/**
  * @brief  Check if Interrupt Flag Masked Status on line 0 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio0(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO0_MSK) == EXTI_IFM_GPIO0_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 1 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO1_MSK) == EXTI_IFM_GPIO1_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 2 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO2_MSK) == EXTI_IFM_GPIO2_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 3 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio3(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO3_MSK) == EXTI_IFM_GPIO3_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 4 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio4(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO4_MSK) == EXTI_IFM_GPIO4_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 5 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio5(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO5_MSK) == EXTI_IFM_GPIO5_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 6 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio6(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO6_MSK) == EXTI_IFM_GPIO6_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 7 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio7(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO7_MSK) == EXTI_IFM_GPIO7_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 8 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio8(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO8_MSK) == EXTI_IFM_GPIO8_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 9 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio9(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO9_MSK) == EXTI_IFM_GPIO9_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 10 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio10(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO10_MSK) == EXTI_IFM_GPIO10_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 11 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio11(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO11_MSK) == EXTI_IFM_GPIO11_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 12 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio12(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO12_MSK) == EXTI_IFM_GPIO12_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 13 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio13(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO13_MSK) == EXTI_IFM_GPIO13_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 14 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio14(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO14_MSK) == EXTI_IFM_GPIO14_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 15 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_gpio15(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_GPIO15_MSK) == EXTI_IFM_GPIO15_POS);
}


/**
  * @brief  Check if Interrupt Flag Masked Status on line 16 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_cmp1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_CMP1_MSK) == EXTI_IFM_CMP1_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 17 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_cmp2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_CMP2_MSK) == EXTI_IFM_CMP2_POS);
}


/**
  * @brief  Check if Interrupt Flag Masked Status on line 20 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_pvd0(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_PVD0_MSK) == EXTI_IFM_PVD0_POS);
}

/**
  * @brief  Check if Interrupt Flag Masked Status on line 21 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_ifm_WAKEUP(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->IFM, EXTI_IFM_WAKEUP_MSK) == EXTI_IFM_WAKEUP_POS);
}

/** 
  * @} MD_EXTI_PF_IFM
  */

/** @defgroup MD_EXTI_PF_RIF EXTI Raw Interrupt Flag Status Register
  * @{
  */


/**
  * @brief  Check if Raw interrupt flag Status on line is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->RIF));
}


/**
  * @brief  Check if Raw interrupt flag Status on line 0 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio0(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO0_MSK) == EXTI_RIF_GPIO0_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 1 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO1_MSK) == EXTI_RIF_GPIO1_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 2 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO2_MSK) == EXTI_RIF_GPIO2_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 3 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio3(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO3_MSK) == EXTI_RIF_GPIO3_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 4 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio4(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO4_MSK) == EXTI_RIF_GPIO4_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 5 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio5(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO5_MSK) == EXTI_RIF_GPIO5_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 6 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio6(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO6_MSK) == EXTI_RIF_GPIO6_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 7 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio7(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO7_MSK) == EXTI_RIF_GPIO7_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 8 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio8(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO8_MSK) == EXTI_RIF_GPIO8_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 9 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio9(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO9_MSK) == EXTI_RIF_GPIO9_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 10 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio10(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO10_MSK) == EXTI_RIF_GPIO10_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 11 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio11(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO11_MSK) == EXTI_RIF_GPIO11_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 12 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio12(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO12_MSK) == EXTI_RIF_GPIO12_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 13 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio13(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO13_MSK) == EXTI_RIF_GPIO13_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 14 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio14(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO14_MSK) == EXTI_RIF_GPIO14_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 15 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_gpio15(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_GPIO15_MSK) == EXTI_RIF_GPIO15_POS);
}


/**
  * @brief  Check if Raw interrupt flag Status on line 16 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_cmp1(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_CMP1_MSK) == EXTI_RIF_CMP1_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 17 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_cmp2(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_CMP2_MSK) == EXTI_RIF_CMP2_POS);
}


/**
  * @brief  Check if Raw interrupt flag Status on line 20 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_pvd0(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_PVD0_MSK) == EXTI_RIF_PVD0_POS);
}

/**
  * @brief  Check if Raw interrupt flag Status on line 21 is actived
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_exti_is_active_flag_rif_WAKEUP(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_BIT(exti->RIF, EXTI_RIF_WAKEUP_MSK) == EXTI_RIF_WAKEUP_POS);
}


/**
  * @} MD_EXTI_PF_RIF
  */




/**
  * @} MD_EXTI_PF_INTERRUNPT_MANAGEMENT
  */






/** @defgroup MD_EXTI_PF_DEBOUNCE_SETTING EXTI Debounce Management
  * @{
  */
/**
  * @brief  Set debounce enable bit of line 
  * @param  exti EXTI Instance 
  * @param  value The value write in EXTI->DB
  * @retval None
  */
__STATIC_INLINE void md_spi_set_exti_db(EXTI_TypeDef *exti, uint32_t value)
{
  WRITE_REG(exti->DB, value);
}

/**
  * @brief  Get debounce enable bit of line
  * @param  exti EXTI Instance 
  * @retval None
  */
__STATIC_INLINE uint32_t md_spi_get_exti_db(EXTI_TypeDef *exti)
{
  return (uint32_t)(READ_REG(exti->DB));
}

/**
  * @brief  Enable debounce enable bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO0_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 0
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO0_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 0 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO0_MSK) == (EXTI_DB_GPIO0_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO1_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 1 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO1_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 1 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO1_MSK) == (EXTI_DB_GPIO1_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO2_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 2
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO2_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 2 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO2_MSK) == (EXTI_DB_GPIO2_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 3
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio3(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO3_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 3 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio3(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO3_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 3 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio3(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO3_MSK) == (EXTI_DB_GPIO3_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 4
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio4(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO4_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 4 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio4(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO4_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 4 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio4(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO4_MSK) == (EXTI_DB_GPIO4_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 5
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio5(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO5_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 5 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio5(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO5_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 5 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio5(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO5_MSK) == (EXTI_DB_GPIO5_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 6
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio6(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO6_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 6 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio6(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO6_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 6 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio6(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO6_MSK) == (EXTI_DB_GPIO6_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 7
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio7(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO7_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 7 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio7(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO7_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 7 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio7(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO7_MSK) == (EXTI_DB_GPIO7_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 8
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio8(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO8_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 8 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio8(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO1_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 8 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio8(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO8_MSK) == (EXTI_DB_GPIO8_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 9
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio9(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO9_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 9 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio9(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO9_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 9 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio9(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO9_MSK) == (EXTI_DB_GPIO9_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 10
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio10(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO10_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 10 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio10(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO10_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 10 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio10(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO10_MSK) == (EXTI_DB_GPIO10_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 11
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio11(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO11_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 11 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio11(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO11_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 11 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio11(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO11_MSK) == (EXTI_DB_GPIO11_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio12(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO12_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 12
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio12(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO12_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 12 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio12(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO12_MSK) == (EXTI_DB_GPIO12_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 13
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio13(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO13_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 13 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio13(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO13_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 13 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio13(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO13_MSK) == (EXTI_DB_GPIO13_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio14(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO14_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 14
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio14(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO14_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 14 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio14(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO14_MSK) == (EXTI_DB_GPIO14_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 1
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_gpio15(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_GPIO15_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 15 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_gpio15(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_GPIO15_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 15 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_gpio15(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_GPIO15_MSK) == (EXTI_DB_GPIO15_MSK));
} 


/**
  * @brief  Enable debounce enable bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_cmp1(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_CMP1_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 16
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_cmp1(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_CMP1_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 16 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_cmp1(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_CMP1_MSK) == (EXTI_DB_CMP1_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_cmp2(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_CMP2_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 17
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_cmp2(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_CMP2_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 17 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_cmp2(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_CMP2_MSK) == (EXTI_DB_CMP2_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 20
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_pvd0(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_PVD0_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 20 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_pvd0(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_PVD0_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 20 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_pvd0(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_PVD0_MSK) == (EXTI_DB_PVD0_MSK));
} 

/**
  * @brief  Enable debounce enable bit of line 21
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_enable_db_wakeup(EXTI_TypeDef *exti)
{
  SET_BIT(exti->DB, EXTI_DB_WAKEUP_MSK);
}

/**
  * @brief  Disable debounce enable bit of line 21 
  * @param  exti EXTI Instance
  * @retval None
  */
__STATIC_INLINE void md_exti_disable_db_wakeup(EXTI_TypeDef *exti)
{
  CLEAR_BIT(exti->DB, EXTI_DB_WAKEUP_MSK);
}

/**
  * @brief  Check if debounce enable bit of line 21 is enabled
  * @param  exti EXTI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_exti_is_enable_db_wakeup(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DB, EXTI_DB_WAKEUP_MSK) == (EXTI_DB_WAKEUP_MSK));
} 

/**
  * @brief  Set Debounce counter  
  * @param  exti EXTI Port
  * @param  dbcnt This bit can be one of following valus:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_exti_set_dbcon_dbcnt(EXTI_TypeDef *exti, uint32_t dbcnt)
{
  MODIFY_REG(exti->DBCON, EXTI_DBCON_DBCNT_MSK, (dbcnt<<EXTI_DBCON_DBCNT_POSS));
}

/**
  * @brief  Return Debounce counter  
  * @retval 0~7
  */
__STATIC_INLINE uint32_t md_exti_get_dbcon_dbcnt(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DBCON, EXTI_DBCON_DBCNT_MSK)>>EXTI_DBCON_DBCNT_POSS);
}

/**
  * @brief  Set Debounce prescale  
  * @param  exti EXTI Port
  * @param  prescale This bit can be one of following valus:
  *         @arg Max Value 255
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_exti_set_dbcon_dbpre(EXTI_TypeDef *exti, uint32_t prescale)
{
  MODIFY_REG(exti->DBCON, EXTI_DBCON_DBPRE_MSK, (prescale<<EXTI_DBCON_DBPRE_POSS));
}

/**
  * @brief  Get Debounce prescale  
  * @retval 0~255
  */
__STATIC_INLINE uint32_t md_exti_get_dbcon_dbpre(EXTI_TypeDef *exti)
{
  return (READ_BIT(exti->DBCON, EXTI_DBCON_DBPRE_MSK)>>EXTI_DBCON_DBPRE_POSS);
}


/**
  * @} MD_EXTI_PF_DEBOUNCE_SETTING
  */






/**
  * @} MD_EXTI_Public_Macros
  */




/* Public functions -----------------------------------------------------------*/



/**
  * @} EXTI
  */

#endif



/**
  * @} Micro_Driver
  */

#endif

#ifdef __cplusplus
}
#endif


/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
