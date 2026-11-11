/**
  ******************************************************************************
  * @file    tae32g58xx_ll_sysctrl.c
  * @author  MCD Application Team
  * @brief   SYSCTRL LL module driver
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
#include "tae32g58xx_ll.h"


#define DBG_TAG             "SYSCTRL LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup SYSCTRL_LL SYSCTRL LL
  * @brief    SYSCTRL LL Module Driver
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Functions SYSCTRL LL Exported Functions
  * @brief    SYSCTRL LL Exported Functions
  * @{
  */

/** @defgroup SYSCTRL_LL_Exported_Functions_Group1 SYSCTRL Init and DeInit Functions
  * @brief    SYSCTRL Init and DeInit Functions
  * @{
  */

/**
  * @brief  Initializes the SYSCTRL peripheral
  * @param  Instance Specifies SYSCTRL peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_SYSCTRL_Init(SYSCTRL_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_SYSCTRL_ALL_INSTANCE(Instance));

    if (!IS_SYSCTRL_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_SYSCTRL_MspInit(Instance);

    __LL_SYSCTRL_SysRegWrite_Unlock(Instance);

    //Enable SYSCTRL PMU Monitor according to need
    __LL_SYSCTRL_VCC_LowVolDet_En(Instance);
    __LL_SYSCTRL_AVCC_LowVolDet_En(Instance);
    __LL_SYSCTRL_VDD_OverCurDet_En(Instance);
    __LL_SYSCTRL_VDD_LowVolDet_En(Instance);

    __LL_SYSCTRL_SysRegWrite_Lock(Instance);

    return LL_OK;
}

/**
  * @brief  DeInitializes the SYSCTRL peripheral
  * @param  Instance Specifies SYSCTRL peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_SYSCTRL_DeInit(SYSCTRL_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_SYSCTRL_ALL_INSTANCE(Instance));

    if (!IS_SYSCTRL_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_SYSCTRL_MspDeInit(Instance);

    __LL_SYSCTRL_SysRegWrite_Unlock(Instance);

    //Disable SYSCTRL PMU Monitor according to need
    __LL_SYSCTRL_VCC_LowVolDet_Dis(Instance);
    __LL_SYSCTRL_AVCC_LowVolDet_Dis(Instance);
    __LL_SYSCTRL_VDD_OverCurDet_Dis(Instance);
    __LL_SYSCTRL_VDD_LowVolDet_Dis(Instance);

    __LL_SYSCTRL_SysRegWrite_Lock(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the SYSCTRL MSP
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void LL_SYSCTRL_MspInit(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the SYSCTRL MSP
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
__WEAK void LL_SYSCTRL_MspDeInit(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup SYSCTRL_LL_Exported_Functions_Interrupt SYSCTRL Interrupt Handler and Callback
  * @brief    SYSCTRL Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  LL SYSCTRL IRQ Handler
  * @param  Instance Specifies SYSCTRL peripheral
  * @retval None
  */
void LL_SYSCTRL_IRQHandler(SYSCTRL_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_SYSCTRL_ALL_INSTANCE(Instance));

    if (!IS_SYSCTRL_ALL_INSTANCE(Instance)) {
        return;
    }

    //VDD OverCurrent Interrupt Handler
    if (__LL_SYSCTRL_IsVDDOverCur(Instance)) {
        LOG_D("VDD Over Current INT.\n");

        //Callback
        LL_SYSCTRL_VDDOverCurCallback(Instance);
    }

    //VDD LowVoltage Interrupt Handler
    if (__LL_SYSCTRL_IsVDDLowVol(Instance)) {
        LOG_D("VDD Low Voltage INT.\n");

        //Callback
        LL_SYSCTRL_VDDLowVolCallback(Instance);
    }

    //VCC LowVoltage Interrupt Handler
    if (__LL_SYSCTRL_IsVCCLowVol(Instance)) {
        LOG_D("VCC Low Voltage INT.\n");

        //Callback
        LL_SYSCTRL_VCCLowVolCallback(Instance);
    }

    //AVCC LowVoltage Interrupt Handler
    if (__LL_SYSCTRL_IsAVCCLowVol(Instance)) {
        LOG_D("AVCC Low Voltage INT.\n");

        //Callback
        LL_SYSCTRL_AVCCLowVolCallback(Instance);
    }
}

/**
  * @brief  SYSCTRL VDD Over Current Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void LL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VDDOverCurCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL VDD Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void LL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VDDLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL VCC Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void LL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_VCCLowVolCallback could be implemented in the user file
     */
}

/**
  * @brief  SYSCTRL AVCC Low Voltage Interrupt Callback
  * @param  Instance Specifies SYSCTRL peripheral
  * @return None
  */
__WEAK void LL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SYSCTRL_AVCCLowVolCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

