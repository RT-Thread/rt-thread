/**
  ******************************************************************************
  * @file    tae32f53xx_ll_fpll.h
  * @author  MCD Application Team
  * @brief   Header file for FPLL LL Module
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
#ifndef _TAE32F53XX_LL_FPLL_H_
#define _TAE32F53XX_LL_FPLL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup FPLL_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup FPLL_LL_Exported_Macros FPLL LL Exported Macros
  * @brief    FPLL LL Exported Macros
  * @{
  */

/**
  * @brief  FPLL Enable
  * @param  __FPLL__ Specifies FPLL peripheral
  * @return None
  */
#define __LL_FPLL_En(__FPLL__)                  SET_BIT((__FPLL__)->FCR, FPLL_EN_Msk)

/**
  * @brief  FPLL Disable
  * @param  __FPLL__ Specifies FPLL peripheral
  * @return None
  */
#define __LL_FPLL_Dis(__FPLL__)                 CLEAR_BIT((__FPLL__)->FCR, FPLL_EN_Msk)

/**
  * @brief  FPLL Start
  * @param  __FPLL__ Specifies FPLL peripheral
  * @return None
  */
#define __LL_FPLL_Start(__FPLL__)               SET_BIT((__FPLL__)->FCR, FPLL_START_Msk)


/**
  * @brief  FPLL Div Integer Set
  * @param  __FPLL__ Specifies FPLL peripheral
  * @param  integer FPLL Div Integer
  * @return None
  */
#define __LL_FPLL_DivInt_Set(__FPLL__, integer) \
        MODIFY_REG((__FPLL__)->FDR, FPLL_DIV_INT_Msk, ((integer & 0x3fffUL) << FPLL_DIV_INT_Pos))

/**
  * @brief  FPLL Div Fraction Set
  * @param  __FPLL__ Specifies FPLL peripheral
  * @param  frac FPLL Div Fraction
  * @return None
  */
#define __LL_FPLL_DivFrac_Set(__FPLL__, frac)   \
        MODIFY_REG((__FPLL__)->FDR, FPLL_DIV_FRAC_Msk, ((frac & 0xffffUL) << FPLL_DIV_FRAC_Pos))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup FPLL_LL_Exported_Functions
  * @{
  */

/** @addtogroup FPLL_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_FPLL_Init(FPLL_TypeDef *Instance);
LL_StatusETypeDef LL_FPLL_DeInit(FPLL_TypeDef *Instance);
void LL_FPLL_MspInit(FPLL_TypeDef *Instance);
void LL_FPLL_MspDeInit(FPLL_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup FPLL_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_FPLL_DivStart(FPLL_TypeDef *Instance, uint16_t integer, uint16_t frac);
/**
  * @}
  */

/**
  * @}
  */


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


#endif /* _TAE32F53XX_LL_FPLL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

