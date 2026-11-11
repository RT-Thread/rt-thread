/**
  ******************************************************************************
  * @file    tae32f53xx_ll_fpll.c
  * @author  MCD Application Team
  * @brief   FPLL LL Module Driver
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

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "FPLL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup FPLL_LL FPLL LL
  * @brief    FPLL LL Module Driver
  * @{
  */

#ifdef LL_FPLL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup FPLL_LL_Exported_Functions FPLL LL Exported Functions
  * @brief    FPLL LL Exported Functions
  * @{
  */

/** @defgroup FPLL_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  Initializes the FPLL peripheral
  * @param  Instance Specifies FPLL peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_FPLL_Init(FPLL_TypeDef *Instance)
{
    /* Init the low level hardware eg. Clock, NVIC */
    LL_FPLL_MspInit(Instance);

    return LL_OK;
}

/**
  * @brief  DeInitializes the FPLL peripheral
  * @param  Instance Specifies FPLL peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_FPLL_DeInit(FPLL_TypeDef *Instance)
{
    /* Init the low level hardware eg. Clock, NVIC */
    LL_FPLL_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the FPLL MSP
  * @param  Instance Specifies FPLL peripheral
  * @retval None
  */
__WEAK void LL_FPLL_MspInit(FPLL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_FPLL_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the FPLL MSP
  * @param  Instance Specifies FPLL peripheral
  * @retval None
  */
__WEAK void LL_FPLL_MspDeInit(FPLL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_FPLL_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */


/** @defgroup FPLL_LL_Exported_Functions_Group2 FPLL Config Fucntions
  * @brief    FPLL Config Fucntions
  * @{
  */

/**
  * @brief  FPLL LL Start
  * @param  Instance Specifies FPLL peripheral
  * @param  integer  FPLL Div integer
  * @param  frac     FPLL Div Fraction
  * @return FPLL Start Result
  */
LL_StatusETypeDef LL_FPLL_DivStart(FPLL_TypeDef *Instance, uint16_t integer, uint16_t frac)
{
    if (Instance == NULL) {
        LOG_E("FPLL Div config params error!\n");
        return LL_ERROR;
    }

    __LL_FPLL_DivInt_Set(Instance, integer);
    __LL_FPLL_DivFrac_Set(Instance, frac);
    __LL_FPLL_En(Instance);
    __LL_FPLL_Start(Instance);

    return LL_OK;
}
/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif  /* LL_FPLL_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

