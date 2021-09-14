/**
  ******************************************************************************
  * @file    tae32f53xx_ll_lvdctrl.c
  * @author  MCD Application Team
  * @brief   LVDCTRL LL Module Driver.
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


#define DBG_TAG             "LVD"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup LVDCTRL_LL LVDCTRL LL
  * @brief    LVDCTRL LL Module Driver
  * @{
  */

#ifdef LL_LVD_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup LVDCTRL_LL_Exported_Functions LVDCTRL LL Exported Functions
  * @brief    LVDCTRL LL Exported Functions
  * @{
  */

/** @defgroup LVDCTRL_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  Initializes the LVD peripheral
  * @param  Instance Specifies LVD peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_LVD_Init(LVD_TypeDef *Instance)
{
    /* Init the low level hardware eg. Clock, NVIC */
    LL_LVD_MspInit(Instance);

    //Enable LVD Module according to need
    __LL_LVDCTRL_VCC_LowVolDet_En(Instance);
    __LL_LVDCTRL_AVCC_LowVolDet_En(Instance);
    __LL_LVDCTRL_VDD_OverCurDet_En(Instance);
    __LL_LVDCTRL_VDD_LowVolDet_En(Instance);

    return LL_OK;
}

/**
  * @brief  DeInitializes the LVD peripheral
  * @param  Instance Specifies LVD peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_LVD_DeInit(LVD_TypeDef *Instance)
{
    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_LVD_MspDeInit(Instance);

    //Disable LVD Module according to need
    __LL_LVDCTRL_VCC_LowVolDet_Dis(Instance);
    __LL_LVDCTRL_AVCC_LowVolDet_Dis(Instance);
    __LL_LVDCTRL_VDD_OverCurDet_Dis(Instance);
    __LL_LVDCTRL_VDD_LowVolDet_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the LVD MSP
  * @param  Instance Specifies LVD peripheral
  * @retval None
  */
__WEAK void LL_LVD_MspInit(LVD_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_LVD_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the LVD MSP
  * @param  Instance Specifies LVD peripheral
  * @retval None
  */
__WEAK void LL_LVD_MspDeInit(LVD_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_LVD_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */


/** @defgroup LVDCTRL_LL_Exported_Functions_Interrupt LVDCTRL Interrupt Management
  * @brief    LVDCTRL Interrupt Management
  * @{
  */

/**
  * @brief  LL LVDCTRL IRQ Handler
  * @param  Instance Specifies LVD peripheral
  * @retval None
  */
void LL_LVD_CtrlIRQHandler(LVD_TypeDef *Instance)
{
    if (__LL_LVDCTRL_IsVDDOverCur(Instance)) {
        LOG_D("VDD Over Current INT.\n");
        //:TODO: add process code according to need
    }

    if (__LL_LVDCTRL_IsVDDLowVol(Instance)) {
        LOG_D("VDD Low Voltage INT.\n");
        //:TODO: add process code according to need
    }

    if (__LL_LVDCTRL_IsVCCLowVol(Instance)) {
        LOG_D("VCC Low Voltage INT.\n");
        //:TODO: add process code according to need
    }

    if (__LL_LVDCTRL_IsAVCCLowVol(Instance)) {
        LOG_D("AVCC Low Voltage INT.\n");
        //:TODO: add process code according to need
    }
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif  /* LL_LVD_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

