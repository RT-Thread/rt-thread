/**
  ******************************************************************************
  * @file    tae32g58xx_ll_iir.c
  * @author  MCD Application Team
  * @brief   IIR LL module driver
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


#define DBG_TAG             "IIR LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup IIR_LL IIR LL
  * @brief    IIR LL module driver
  * @{
  */

#ifdef LL_IIR_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Functions IIR LL Exported Functions
  * @brief    IIR LL Exported Functions
  * @{
  */

/** @defgroup IIR_LL_Exported_Functions_Group1 IIR Init and DeInit Functions
  * @brief    IIR Init and DeInit Functions
  * @{
  */

/**
  * @brief  IIR LL Init
  * @param  Instance Specifies IIR peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_IIR_Init(IIR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    if (!IS_IIR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_IIR_MspInit(Instance);

    //IIR Enable
    __LL_IIR_En(Instance);

    return LL_OK;
}

/**
  * @brief  IIR LL DeInit
  * @param  Instance Specifies IIR peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_IIR_DeInit(IIR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    if (!IS_IIR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //IIR Disable
    __LL_IIR_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_IIR_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the IIR MSP
  * @param  Instance Specifies IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_MspInit(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the IIR MSP
  * @param  Instance Specifies IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_MspDeInit(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Group2 IIR Config Functions
  * @brief    IIR Config Functions
  * @{
  */

/**
  * @brief  IIR LL Config
  * @param  Instance Specifies IIR peripheral
  * @param  user_cfg user config pointer
  * @return Status of the Config
  */
LL_StatusETypeDef LL_IIR_Config(IIR_TypeDef *Instance, IIR_UserCfgTypeDef *user_cfg)
{
    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));
    assert_param(user_cfg != NULL);

    if (!IS_IIR_ALL_INSTANCE(Instance) || user_cfg == NULL) {
        return LL_INVALID;
    }

    if (IS_IIRy_ALL_INSTANCE(Instance) && user_cfg->order > IIR_ORDER_2) {
        LOG_E("IIRy max order is 2, while now config is [%d]!!!\n", user_cfg->order + 1);
        return LL_INVALID;
    }

    __LL_IIR_Order_Set(Instance, user_cfg->order);

    //Scale Config
    __LL_IIR_FbScale_Set(Instance, user_cfg->fb_scale);
    __LL_IIR_OutputScale_Set(Instance, user_cfg->out_scale);

    //Coef Config
    __LL_IIR_B0Coef_Set(Instance, user_cfg->coef.Bx[0]);
    __LL_IIR_B1Coef_Set(Instance, user_cfg->coef.Bx[1]);
    __LL_IIR_B2Coef_Set(Instance, user_cfg->coef.Bx[2]);
    __LL_IIR_B3Coef_Set(Instance, user_cfg->coef.Bx[3]);
    __LL_IIR_B4Coef_Set(Instance, user_cfg->coef.Bx[4]);

    __LL_IIR_A1Coef_Set(Instance, user_cfg->coef.Ax[0]);
    __LL_IIR_A2Coef_Set(Instance, user_cfg->coef.Ax[1]);
    __LL_IIR_A3Coef_Set(Instance, user_cfg->coef.Ax[2]);
    __LL_IIR_A4Coef_Set(Instance, user_cfg->coef.Ax[3]);

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_IIR_HighOrderOutputScale_Set(Instance, user_cfg->hi_out_scale);
        __LL_IIR_HighOrderFbScale_Set(Instance, user_cfg->hi_fb_scale);
        __LL_IIR_B5Coef_Set(Instance, user_cfg->coef.Bx[5]);
    }

    return LL_OK;
}

/**
  * @brief  IIR LL Reset
  * @param  Instance Specifies IIR peripheral
  * @return Status of the reset
  */
LL_StatusETypeDef LL_IIR_Reset(IIR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    if (!IS_IIR_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    __LL_IIR_SoftReset(Instance);
    __LL_IIR_Order_Set(Instance, IIR_ORDER_2);

    //Scale Reset
    __LL_IIR_FbScale_Set(Instance, IIR_SCALE_2_POWER_0);
    __LL_IIR_OutputScale_Set(Instance, IIR_SCALE_2_POWER_0);

    //Coef Reset
    __LL_IIR_B0Coef_Set(Instance, 0);
    __LL_IIR_B1Coef_Set(Instance, 0);
    __LL_IIR_B2Coef_Set(Instance, 0);
    __LL_IIR_B3Coef_Set(Instance, 0);
    __LL_IIR_B4Coef_Set(Instance, 0);

    __LL_IIR_A1Coef_Set(Instance, 0);
    __LL_IIR_A2Coef_Set(Instance, 0);
    __LL_IIR_A3Coef_Set(Instance, 0);
    __LL_IIR_A4Coef_Set(Instance, 0);

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_IIR_HighOrderOutputScale_Set(Instance, IIR_SCALE_2_POWER_0);
        __LL_IIR_HighOrderFbScale_Set(Instance, IIR_SCALE_2_POWER_0);
        __LL_IIR_B5Coef_Set(Instance, 0);
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Group3 IIR Operation Functions
  * @brief    IIR Operation Functions
  * @{
  */

/**
  * @brief  IIR Calc Once
  * @param  Instance Specifies IIR peripheral
  * @param  dat_in Input data
  * @param  grp Special Coef Group
  * @param  dat_out Output data pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_IIR_Calc_Once(IIR_TypeDef *Instance, int16_t dat_in, int16_t *dat_out, uint32_t timeout)
{
    uint32_t tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));
    assert_param(dat_out != NULL);

    if (!IS_IIR_ALL_INSTANCE(Instance) || dat_out == NULL) {
        return LL_INVALID;
    }

    // Input Data Write
    __LL_IIR_InputDat_Write(Instance, dat_in);

    //Wait for Busy, check any error occurred first, because Calculation may not start and error occured
    do {
        //Check if error occurred
        if (__LL_IIR_IsErrIntPnd(Instance)) {
            __LL_IIR_ErrIntPnd_Clr(Instance);
            return LL_ERROR;
        }

        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    } while (__LL_IIR_IsBusy(Instance));

    //Read Output Data
    *dat_out = __LL_IIR_OutputDat_Read(Instance);

    return LL_OK;
}

/**
  * @brief  IIR Calc Multi
  * @param  Instance Specifies IIR peripheral
  * @param  dat_in Input data pointer
  * @param  dat_nums Input/Output data numbers in int16_t unit
  * @param  grp Special Coef Group
  * @param  dat_out Output data pointer
  * @param  timeout timeout duration
  * @return Success Calculate Counter
  */
uint32_t LL_IIR_Calc_Multi(IIR_TypeDef *Instance, const int16_t *dat_in, uint32_t dat_nums, int16_t *dat_out, uint32_t timeout)
{
    uint32_t i, tickstart = LL_GetTick();

    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));
    assert_param(dat_in != NULL);
    assert_param(dat_out != NULL);

    if (!IS_IIR_ALL_INSTANCE(Instance) || dat_in == NULL || dat_out == NULL) {
        return 0;
    }

    for (i = 0; i < dat_nums; i++) {
        //Input Data Write
        __LL_IIR_InputDat_Write(Instance, *dat_in++);

        //Wait for Busy, check any error occurred first, because Calculation may not start and error occured
        do {
            //Check if error occurred
            if (__LL_IIR_IsErrIntPnd(Instance)) {
                __LL_IIR_ErrIntPnd_Clr(Instance);
                return i;
            }

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return i;
            }
        } while (__LL_IIR_IsBusy(Instance));

        //Read Output Data
        *dat_out++ = __LL_IIR_OutputDat_Read(Instance);
    }

    return i;
}

/**
  * @}
  */


/** @defgroup IIR_LL_Exported_Functions_Interrupt IIR Interrupt Handler and Callback
  * @brief    IIR Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  LL IIR IRQ Handler
  * @param  Instance Specifies IIR peripheral
  * @retval None
  */
void LL_IIR_IRQHandler(IIR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_IIR_ALL_INSTANCE(Instance));

    if (!IS_IIR_ALL_INSTANCE(Instance)) {
        return;
    }

    //Error Interrupt Handler
    if (__LL_IIR_IsErrIntEn(Instance) && __LL_IIR_IsErrIntPnd(Instance)) {
        //Clear Interrupt Pending
        __LL_IIR_ErrIntPnd_Clr(Instance);

        //Callback
        LL_IIR_ErrCallback(Instance);
    }
}

/**
  * @brief  IIR Error Interrupt Callback
  * @param  Instance Specifies IIR peripheral
  * @return None
  */
__WEAK void LL_IIR_ErrCallback(IIR_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_IIR_ErrCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif  /* LL_IIR_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

