/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cordic.c
  * @author  MCD Application Team
  * @brief   CORDIC LL module driver
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


#define DBG_TAG             "CORDIC LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup CORDIC_LL CORDIC LL
  * @brief    CORDIC LL module driver
  * @{
  */

#ifdef LL_CORDIC_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup CORDIC_LL_Private_Functions CORDIC LL Private Functions
  * @brief    CORDIC_LL_Private_Functions
  * @{
  */
__STATIC_INLINE bool CORDIC_IsScaleValid(uint8_t scale, CORDIC_FuncETypeDef func);
static void CORDIC_WriteInDataIncrementPtr(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t **ppInBuff);
static void CORDIC_ReadOutDataIncrementPtr(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t **ppOutBuff);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Functions CORDIC LL Exported Functions
  * @brief    CORDIC LL Exported Functions
  * @{
  */

/** @defgroup CORDIC_LL_Exported_Functions_Group1 CORDIC Init and DeInit Functions
  * @brief    CORDIC Init and DeInit Functions
  * @{
  */

/**
  * @brief  CORDIC LL Init
  * @param  Instance Specifies CORDIC peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_CORDIC_Init(CORDIC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));

    if (!IS_CORDIC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* Init the low level hardware eg. Clock, NVIC */
    LL_CORDIC_MspInit(Instance);

    return LL_OK;
}

/**
  * @brief  CORDIC LL DeInit
  * @param  Instance Specifies CORDIC peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_CORDIC_DeInit(CORDIC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));

    if (!IS_CORDIC_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_CORDIC_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the CORDIC MSP
  * @param  Instance Specifies CORDIC peripheral
  * @return None
  */
__WEAK void LL_CORDIC_MspInit(CORDIC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CORDIC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the CORDIC MSP
  * @param  Instance Specifies CORDIC peripheral
  * @return None
  */
__WEAK void LL_CORDIC_MspDeInit(CORDIC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CORDIC_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup CORDIC_LL_Exported_Functions_Group2 CORDIC Config Functions
  * @brief    CORDIC Config Functions
  * @{
  */

/**
  * @brief  CORDIC LL Config
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch channel to Config
  * @param  user_cfg user config pointer
  * @return Status of the Config
  */
LL_StatusETypeDef LL_CORDIC_Config(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, CORDIC_UserCfgTypeDef *user_cfg)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(user_cfg != NULL);
    assert_param(CORDIC_IsScaleValid(user_cfg->scale, user_cfg->func));
    assert_param(!user_cfg->arg_num || !user_cfg->arg_width);
    assert_param(!user_cfg->res_num || !user_cfg->res_width);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || user_cfg == NULL ||
        !CORDIC_IsScaleValid(user_cfg->scale, user_cfg->func) || (user_cfg->arg_num && user_cfg->arg_width) ||
        (user_cfg->res_num && user_cfg->res_width)) {
        return LL_INVALID;
    }

    //User config
    __LL_CORDIC_InputDatWidth_Set(Instance, ch, user_cfg->arg_width);
    __LL_CORDIC_OutputDatWidth_Set(Instance, ch, user_cfg->res_width);
    __LL_CORDIC_InputDatNum_Set(Instance, ch, user_cfg->arg_num);
    __LL_CORDIC_OutputDatNum_Set(Instance, ch, user_cfg->res_num);
    __LL_CORDIC_Scale_Set(Instance, ch, user_cfg->scale);
    __LL_CORDIC_CalcFunc_Set(Instance, ch, user_cfg->func);

    return LL_OK;
}

/**
  * @brief  CORDIC LL Reset
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch channel to reset
  * @return Status of the reset
  */
LL_StatusETypeDef LL_CORDIC_Reset(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Reset CORDIC Module Register
    __LL_CORDIC_ChAllCfg_Reset(Instance, ch);

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup CORDIC_LL_Exported_Functions_Group3 CORDIC Operation Functions
  * @brief    CORDIC Operation Functions
  * @{
  */

/**
  * @brief  CORDIC Start in 16bit argument
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  arg1 Argument 1
  * @param  arg2 Argument 2
  * @retval LL_StatusETypeDef
  */
LL_StatusETypeDef LL_CORDIC_Start_16(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int16_t arg1, int16_t arg2)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Config argument to start
    __LL_CORDIC_Arg1_Set(Instance, ch, (arg2 << 16) | (arg1 & 0xffffUL));

    return LL_OK;
}

/**
  * @brief  CORDIC Start in one 32bit argument
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  arg1 Argument 1
  * @retval LL_StatusETypeDef
  */
LL_StatusETypeDef LL_CORDIC_Start_One32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t arg1)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Config argument to start
    __LL_CORDIC_Arg1_Set(Instance, ch, arg1);

    return LL_OK;
}

/**
  * @brief  CORDIC Start in two 32bit argument
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  arg1 Argument 1
  * @param  arg2 Argument 2
  * @retval LL_StatusETypeDef
  */
LL_StatusETypeDef LL_CORDIC_Start_Two32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t arg1, int32_t arg2)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Config argument to start
    __LL_CORDIC_Arg1_Set(Instance, ch, arg1);
    __LL_CORDIC_Arg2_Set(Instance, ch, arg2);

    return LL_OK;
}

/**
  * @brief  CORDIC Get Result in 16bit result
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  res1 result 1 pointer
  * @param  res2 result 2 pointer
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_GetResult_16(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int16_t *res1, int16_t *res2, uint32_t timeout)
{
    uint32_t tickstart, res;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(res1 != NULL && res2 != NULL);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || res1 == NULL || res2 == NULL) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Wait transform done, check any error occurred first, because Calculation may not start and error occured
    do {
        //Check if error occurred
        if (__LL_CORDIC_IsErrtPnd(Instance, ch)) {
            __LL_CORDIC_ErrPnd_Clr(Instance, ch);
            return LL_ERROR;
        }

        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    } while (!(__LL_CORDIC_IsCpltPnd(Instance, ch)));

    //Complete Pending Clear
    __LL_CORDIC_CpltPnd_Clr(Instance, ch);

    //Get result
    res = __LL_CORDIC_Res1_Get(Instance, ch);
    *res1 = (int16_t)res;
    *res2 = (int16_t)(res >> 16);

    return LL_OK;
}

/**
  * @brief  CORDIC Get Result in one 32bit result
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  res1 result 1 pointer
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_GetResult_One32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *res1, uint32_t timeout)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(res1 != NULL);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || res1 == NULL) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Wait transform done, check any error occurred first, because Calculation may not start and error occured
    do {
        //Check if error occurred
        if (__LL_CORDIC_IsErrtPnd(Instance, ch)) {
            __LL_CORDIC_ErrPnd_Clr(Instance, ch);
            return LL_ERROR;
        }

        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    } while (!(__LL_CORDIC_IsCpltPnd(Instance, ch)));

    //Complete Pending Clear
    __LL_CORDIC_CpltPnd_Clr(Instance, ch);

    //Get result
    *res1 = __LL_CORDIC_Res1_Get(Instance, ch);

    return LL_OK;
}

/**
  * @brief  CORDIC Get Result in two 32bit result
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  res1 result 1 pointer
  * @param  res2 result 2 pointer
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_GetResult_Two32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *res1, int32_t *res2, uint32_t timeout)
{
    uint32_t tickstart;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(res1 != NULL && res2 != NULL);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || res1 == NULL || res2 == NULL) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Wait transform done, check any error occurred first, because Calculation may not start and error occured
    do {
        //Check if error occurred
        if (__LL_CORDIC_IsErrtPnd(Instance, ch)) {
            __LL_CORDIC_ErrPnd_Clr(Instance, ch);
            return LL_ERROR;
        }

        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    } while (!(__LL_CORDIC_IsCpltPnd(Instance, ch)));

    //Complete Pending Clear
    __LL_CORDIC_CpltPnd_Clr(Instance, ch);

    //Get result
    *res1 = __LL_CORDIC_Res1_Get(Instance, ch);
    *res2 = __LL_CORDIC_Res2_Get(Instance, ch);

    return LL_OK;
}

/**
  * @brief  Carry out data of CORDIC processing in polling mode with single channel
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  in_buf   Pointer to buffer in
  * @param  out_buf  Pointer to buffer out
  * @param  num_calc Number of CORDIC calculation to process
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_Calculate_SingleCh(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout)
{
    uint32_t i, tickstart;
    int32_t *p_tmp_in_buf = in_buf;
    int32_t *p_tmp_out_buf = out_buf;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(in_buf != NULL && out_buf != NULL);
    assert_param(num_calc);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || in_buf == NULL || out_buf == NULL || !num_calc) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    for (i = 0; i < num_calc; i++) {
        //Write dat into argument register
        CORDIC_WriteInDataIncrementPtr(Instance, ch, &p_tmp_in_buf);

        //Wait transform done, check any error occurred first, because Calculation may not start and error occured
        do {
            //Check if error occurred
            if (__LL_CORDIC_IsErrtPnd(Instance, ch)) {
                __LL_CORDIC_ErrPnd_Clr(Instance, ch);
                return LL_ERROR;
            }

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        } while (!(__LL_CORDIC_IsCpltPnd(Instance, ch)));

        //Complete Pending Clear
        __LL_CORDIC_CpltPnd_Clr(Instance, ch);

        //Read result
        CORDIC_ReadOutDataIncrementPtr(Instance, ch, &p_tmp_out_buf);
    }

    return LL_OK;
}

/**
  * @brief  Carry out data of CORDIC processing in polling Zero-Overhead mode with single channel
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  in_buf   Pointer to buffer in
  * @param  out_buf  Pointer to buffer out
  * @param  num_calc Number of CORDIC calculation to process
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_Calculate_SingleCh_ZO(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout)
{
    uint32_t i, tickstart;
    int32_t *p_tmp_in_buf = in_buf;
    int32_t *p_tmp_out_buf = out_buf;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(in_buf != NULL && out_buf != NULL);
    assert_param(num_calc);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || in_buf == NULL || out_buf == NULL || !num_calc) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    for (i = 0; i < num_calc; i++) {
        //Write dat into argument register
        CORDIC_WriteInDataIncrementPtr(Instance, ch, &p_tmp_in_buf);

        //Read result
        CORDIC_ReadOutDataIncrementPtr(Instance, ch, &p_tmp_out_buf);

        //Check Timeout
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    }

    return LL_OK;
}

/**
  * @brief  Carry out data of CORDIC processing in polling mode with mixed channel
  * @param  Instance Specifies CORDIC peripheral
  * @param  in_buf   Pointer to buffer in
  * @param  out_buf  Pointer to buffer out
  * @param  num_calc Number of CORDIC calculation to process
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_Calculate_MixCh(CORDIC_TypeDef *Instance,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout)
{
    uint32_t i, tickstart;
    int32_t *p_tmp_in_buf = in_buf;
    int32_t *p_tmp_out_buf = out_buf;
    CORDIC_ChannelETypeDef res_ch = CORDIC_CHANNEL_0;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(in_buf != NULL && out_buf != NULL);
    assert_param(num_calc);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || in_buf == NULL || out_buf == NULL || !num_calc) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Write dat into Channel 0 argument register first
    CORDIC_WriteInDataIncrementPtr(Instance, res_ch, &p_tmp_in_buf);

    for (i = 0; i < num_calc - 1; i++) {
        //Write dat into argument register
        CORDIC_WriteInDataIncrementPtr(Instance, res_ch == CORDIC_CHANNEL_0 ? CORDIC_CHANNEL_1 : CORDIC_CHANNEL_0, &p_tmp_in_buf);

        //Wait transform done, check any error occurred first, because Calculation may not start and error occured
        do {
            //Check if error occurred
            if (__LL_CORDIC_IsErrtPnd(Instance, res_ch)) {
                __LL_CORDIC_ErrPnd_Clr(Instance, res_ch);
                return LL_ERROR;
            }

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                return LL_TIMEOUT;
            }
        } while (!(__LL_CORDIC_IsCpltPnd(Instance, res_ch)));

        //Complete Pending Clear
        __LL_CORDIC_CpltPnd_Clr(Instance, res_ch);

        //Read result
        CORDIC_ReadOutDataIncrementPtr(Instance, res_ch, &p_tmp_out_buf);

        //Switch next result channel
        res_ch = (res_ch == CORDIC_CHANNEL_0) ? CORDIC_CHANNEL_1 : CORDIC_CHANNEL_0;
    }

    //Read result
    CORDIC_ReadOutDataIncrementPtr(Instance, res_ch, &p_tmp_out_buf);

    return LL_OK;
}

/**
  * @brief  Carry out data of CORDIC processing in Zero-Overhead mode with mixed channel
  * @param  Instance Specifies CORDIC peripheral
  * @param  in_buf   Pointer to buffer in
  * @param  out_buf  Pointer to buffer out
  * @param  num_calc Number of CORDIC calculation to process
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_CORDIC_Calculate_MixCh_ZO(CORDIC_TypeDef *Instance,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout)
{
    uint32_t i, tickstart;
    int32_t *p_tmp_in_buf = in_buf;
    int32_t *p_tmp_out_buf = out_buf;
    CORDIC_ChannelETypeDef res_ch = CORDIC_CHANNEL_0;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(in_buf != NULL && out_buf != NULL);
    assert_param(num_calc);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || in_buf == NULL || out_buf == NULL || !num_calc) {
        return LL_INVALID;
    }

    tickstart = LL_GetTick();

    //Write dat into Channel 0 argument register first
    CORDIC_WriteInDataIncrementPtr(Instance, res_ch, &p_tmp_in_buf);

    for (i = 0; i < num_calc - 1; i++) {
        //Write dat into argument register
        CORDIC_WriteInDataIncrementPtr(Instance, res_ch == CORDIC_CHANNEL_0 ? CORDIC_CHANNEL_1 : CORDIC_CHANNEL_0, &p_tmp_in_buf);

        //Read result
        CORDIC_ReadOutDataIncrementPtr(Instance, res_ch, &p_tmp_out_buf);

        //Switch next result channel
        res_ch = (res_ch == CORDIC_CHANNEL_0) ? CORDIC_CHANNEL_1 : CORDIC_CHANNEL_0;

        //Check Timeout
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            return LL_TIMEOUT;
        }
    }

    //Read result
    CORDIC_ReadOutDataIncrementPtr(Instance, res_ch, &p_tmp_out_buf);

    return LL_OK;
}


/**
  * @}
  */


/** @defgroup CORDIC_LL_Exported_Functions_Interrupt CORDIC Interrupt Handler and Callback
  * @brief    CORDIC Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  CORDIC IRQ Handler
  * @param  Instance Specifies CORDIC peripheral
  * @return None
  */
void LL_CORDIC_IRQHandler(CORDIC_TypeDef *Instance)
{
    CORDIC_ChannelETypeDef ch;

    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));

    if (!IS_CORDIC_ALL_INSTANCE(Instance)) {
        return;
    }

    for (ch = CORDIC_CHANNEL_0; ch < CORDIC_CHANNEL_NUMS; ch++) {
        if (__LL_CORDIC_Cplt_Int_En(Instance, ch) && __LL_CORDIC_IsCpltPnd(Instance, ch)) {
            //Interrupt Pending Clear
            __LL_CORDIC_CpltPnd_Clr(Instance, ch);

            //Callback
            LL_CORDIC_CpltCallback(Instance, ch);
        }

        if (__LL_CORDIC_Err_Int_En(Instance, ch) && __LL_CORDIC_IsErrtPnd(Instance, ch)) {
            //Interrupt Pending Clear
            __LL_CORDIC_ErrPnd_Clr(Instance, ch);

            //Callback
            LL_CORDIC_ErrCallback(Instance, ch);
        }
    }
}

/**
  * @brief  CORDIC Complete Interrupt Callback
  * @param  Instance Specifies CORDIC peripheral
  * @return None
  */
__WEAK void LL_CORDIC_CpltCallback(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(ch);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CORDIC_CpltCallback could be implemented in the user file
     */
}

/**
  * @brief  CORDIC Error Interrupt Callback
  * @param  Instance Specifies CORDIC peripheral
  * @return None
  */
__WEAK void LL_CORDIC_ErrCallback(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(ch);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_CORDIC_ErrCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup CORDIC_LL_Private_Functions
  * @{
  */

/**
  * @brief  Judge is Scale valid or not
  * @param  scale Scale
  * @param  func Calculate Function
  * @retval false Scale is Invalid
  * @retval true  Scale is Valid
  */
__STATIC_INLINE bool CORDIC_IsScaleValid(uint8_t scale, CORDIC_FuncETypeDef func)
{
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) { 
        //Assert param
        assert_param(scale <= CORDIC_SCALE_MAX_VD);

        if (scale > CORDIC_SCALE_MAX_VD) {
            return false;
        }

        if (func <= CORDIC_FUNC_MODULUS) {
            if (!scale) {
                return true;
            }
        } else if (func == CORDIC_FUNC_ARCTAN) {
            if (scale <= 7) {
                return true;
            }
        } else if (func == CORDIC_FUNC_SQRT) {
            return true;
        }      
    } else {
        //Assert param
        assert_param(scale <= CORDIC_SCALE_MAX);

        if (scale > CORDIC_SCALE_MAX) {
            return false;
        }

        if (func <= CORDIC_FUNC_MODULUS) {
            if (!scale) {
                return true;
            }
        } else if (func == CORDIC_FUNC_ARCTAN) {
            return true;
        }  else if (func <= CORDIC_FUNC_ARCTANH) {
            if (scale == 1) {
                return true;
            }
        } else if (func == CORDIC_FUNC_LOGN) {
            if (scale >= 1 && scale <= 4) {
                return true;
            }
        } else if (func == CORDIC_FUNC_SQRT) {
            if (scale <= 2) {
                return true;
            }
        }      
    }


    return false;
}

/**
  * @brief  Write input data for CORDIC processing, and increment input buffer pointer
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  ppInBuff Pointer to pointer to input buffer
  * @retval none
  */
static void CORDIC_WriteInDataIncrementPtr(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t **ppInBuff)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(ppInBuff != NULL && *ppInBuff != NULL);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || ppInBuff == NULL || *ppInBuff == NULL) {
        return;
    }

    //First write of input data in the Write Data register
    __LL_CORDIC_Arg1_Set(Instance, ch, (uint32_t) **ppInBuff);

    //Increment input data pointer
    (*ppInBuff)++;

    //Check if second write of input data is expected
    if (__LL_CORDIC_InputDatNum_Get(Instance, ch)) {
        //Second write of input data in the Write Data register
        __LL_CORDIC_Arg2_Set(Instance, ch, (uint32_t) **ppInBuff);

        //Increment input data pointer
        (*ppInBuff)++;
    }
}

/**
  * @brief  Read output data of CORDIC processing, and increment output buffer pointer
  * @param  Instance Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  ppOutBuff Pointer to pointer to output buffer
  * @retval none
  */
static void CORDIC_ReadOutDataIncrementPtr(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t **ppOutBuff)
{
    //Assert param
    assert_param(IS_CORDIC_ALL_INSTANCE(Instance));
    assert_param(__LL_CORDIC_IsChannelValid(ch));
    assert_param(ppOutBuff != NULL && *ppOutBuff != NULL);

    if (!IS_CORDIC_ALL_INSTANCE(Instance) || !__LL_CORDIC_IsChannelValid(ch) || ppOutBuff == NULL || *ppOutBuff == NULL) {
        return;
    }

    //First read of output data from the Read Data register
    **ppOutBuff = __LL_CORDIC_Res1_Get(Instance, ch);

    //Increment output data pointer
    (*ppOutBuff)++;

    //Check if second read of output data is expected
    if (__LL_CORDIC_OutputDatNum_Get(Instance, ch)) {
        //Second read of output data from the Read Data register
        **ppOutBuff = __LL_CORDIC_Res2_Get(Instance, ch);

        //Increment output data pointer
        (*ppOutBuff)++;
    }
}

/**
  * @}
  */


#endif  /* LL_CORDIC_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

