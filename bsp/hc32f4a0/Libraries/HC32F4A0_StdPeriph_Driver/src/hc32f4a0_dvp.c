/**
 *******************************************************************************
 * @file  hc32f4a0_dvp.c
 * @brief This file provides firmware functions to manage the DVP(Digital Video
 *        Processor) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-08-20       Hongjh          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_dvp.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DVP DVP
 * @brief Digital Video Processor Driver Library
 * @{
 */

#if (DDL_DVP_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DVP_Local_Macros DVP Local Macros
 * @{
 */

/**
 * @defgroup DVP_Check_Parameters_Validity DVP Check Parameters Validity
 * @{
 */

#define IS_DVP_CAPT_MD(x)                                                      \
(   ((x) == DVP_CAPT_MD_CONTINUOS_FRAME)    ||                                 \
    ((x) == DVP_CAPT_MD_SINGLE_FRAME))

#define IS_DVP_SYNC_MD(x)                                                      \
(   ((x) == DVP_SYNC_MD_HW)                 ||                                 \
    ((x) == DVP_SYNC_MD_SW))

#define IS_DVP_PIXCLK_POLARITY(x)                                              \
(   ((x) == DVP_PIXCLK_RISING)              ||                                 \
    ((x) == DVP_PIXCLK_FALLING))

#define IS_DVP_HSYNC_POLARITY(x)                                               \
(   ((x) == DVP_HSYNC_LOW)                  ||                                 \
    ((x) == DVP_HSYNC_HIGH))

#define IS_DVP_VSYNC_POLARITY(x)                                               \
(   ((x) == DVP_VSYNC_LOW)                  ||                                 \
    ((x) == DVP_VSYNC_HIGH))

#define IS_DVP_CAPT_FREQ(x)                                                    \
(   ((x) == DVP_CAPT_FREQ_ALL_FRAME)        ||                                 \
    ((x) == DVP_CAPT_FREQ_ONT_TIME_2FRAME)  ||                                 \
    ((x) == DVP_CAPT_FREQ_ONT_TIME_4FRAME))

#define IS_DVP_DATA_WIDTH(x)                                                   \
(   ((x) == DVP_DATA_WIDTH_8BIT)            ||                                 \
    ((x) == DVP_DATA_WIDTH_10BIT)           ||                                 \
    ((x) == DVP_DATA_WIDTH_12BIT)           ||                                 \
    ((x) == DVP_DATA_WIDTH_14BIT))

#define IS_DVP_FLAG(x)                                                         \
(   ((x) != 0UL)                            ||                                 \
    (((x) | DVP_FLAG_ALL) == DVP_FLAG_ALL))

#define IS_DVP_INT(x)                                                          \
(   ((x) != 0UL)                            ||                                 \
    (((x) | DVP_INT_ALL) == DVP_INT_ALL))

#define IS_DVP_CROP_WIN_X(x)                ((x) <= 0x3FFFUL)

#define IS_DVP_CROP_WIN_Y(x)                ((x) <= 0x3FFFUL)

#define IS_DVP_CROP_WIN_XSIZE(x)            ((x) <= 0x3FFFUL)

#define IS_DVP_CROP_WIN_YSIZE(x)            ((x) <= 0x3FFFUL)

#define IS_DVP_SYNC_CODE(x)                 ((x) <= 0xFFUL)

#define IS_DVP_MASK_CODE(x)                 ((x) <= 0xFFUL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup DVP_Global_Functions DVP Global Functions
 * @{
 */

/**
 * @brief  Initialize DVP function.
 * @param  [in] pstcDvpInit         Pointer to a @ref stc_dvp_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The parameter pstcDvpInit is NULL
 */
en_result_t DVP_Init(const stc_dvp_init_t *pstcDvpInit)
{
    uint32_t u32RegValue;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcDvpInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_DVP_SYNC_MD(pstcDvpInit->u32SyncMode));
        DDL_ASSERT(IS_DVP_DATA_WIDTH(pstcDvpInit->u32DataWidth));
        DDL_ASSERT(IS_DVP_CAPT_MD(pstcDvpInit->u32CaptureMode));
        DDL_ASSERT(IS_DVP_CAPT_FREQ(pstcDvpInit->u32CaptureFreq));
        DDL_ASSERT(IS_DVP_PIXCLK_POLARITY(pstcDvpInit->u32PIXCLKPolarity));
        DDL_ASSERT(IS_DVP_HSYNC_POLARITY(pstcDvpInit->u32HSYNCPolarity));
        DDL_ASSERT(IS_DVP_VSYNC_POLARITY(pstcDvpInit->u32VSYNCPolarity));

        /* De-init DVP*/
        WRITE_REG32(M4_DVP->CTR, 0UL);
        WRITE_REG32(M4_DVP->STR, 0UL);
        WRITE_REG32(M4_DVP->IER, 0UL);
        WRITE_REG32(M4_DVP->SSYNDR, 0UL);
        WRITE_REG32(M4_DVP->SSYNMR, 0xFFFFFFFFUL);
        WRITE_REG32(M4_DVP->CPSFTR, 0UL);
        WRITE_REG32(M4_DVP->CPSZER, 0UL);

        u32RegValue = (pstcDvpInit->u32SyncMode       | \
                       pstcDvpInit->u32DataWidth      | \
                       pstcDvpInit->u32CaptureMode    | \
                       pstcDvpInit->u32CaptureFreq    | \
                       pstcDvpInit->u32PIXCLKPolarity | \
                       pstcDvpInit->u32HSYNCPolarity  | \
                       pstcDvpInit->u32VSYNCPolarity);

        /* Configure DVP */
        WRITE_REG32(M4_DVP->CTR, u32RegValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize DVP function.
 * @param  None
 * @retval None
 */
void DVP_DeInit(void)
{
    WRITE_REG32(M4_DVP->CTR, 0UL);
    WRITE_REG32(M4_DVP->STR, 0UL);
    WRITE_REG32(M4_DVP->IER, 0UL);
    WRITE_REG32(M4_DVP->SSYNDR, 0UL);
    WRITE_REG32(M4_DVP->SSYNMR, 0xFFFFFFFFUL);
    WRITE_REG32(M4_DVP->CPSFTR, 0UL);
    WRITE_REG32(M4_DVP->CPSZER, 0UL);
}

/**
 * @brief  Set the fields of structure stc_dvp_init_t to default values
 * @param  [out] pstcDvpInit        Pointer to a @ref stc_dvp_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The parameter pstcDvpInit is NULL
 */
en_result_t DVP_StructInit(stc_dvp_init_t *pstcDvpInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcDvpInit)
    {
        pstcDvpInit->u32SyncMode       = DVP_SYNC_MD_HW;
        pstcDvpInit->u32DataWidth      = DVP_DATA_WIDTH_8BIT;
        pstcDvpInit->u32CaptureMode    = DVP_CAPT_MD_CONTINUOS_FRAME;
        pstcDvpInit->u32CaptureFreq    = DVP_CAPT_FREQ_ALL_FRAME;
        pstcDvpInit->u32PIXCLKPolarity = DVP_PIXCLK_FALLING;
        pstcDvpInit->u32HSYNCPolarity  = DVP_HSYNC_LOW;
        pstcDvpInit->u32VSYNCPolarity  = DVP_VSYNC_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable/disable DVP.
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable function.
 *           @arg Disable:          Disable function.
 * @retval None
 */
void DVP_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_DVP->CTR_b.DVPEN, enNewState);
}

/**
 * @brief  Enable/disable the specified DVP interrupt.
 * @param  [in] u32IntType          DVP interrupt type
 *         This parameter can be any composed value of the following values:
 *           @arg DVP_INT_FRAME_START: Frame start interrupt
 *           @arg DVP_INT_LINE_START:  Line start interrupt
 *           @arg DVP_INT_LINE_END:    Line end interrupt
 *           @arg DVP_INT_FRAME_END:   Frame end interrupt
 *           @arg DVP_INT_FIFO_OVF:    FIFO overflow error interrupt
 *           @arg DVP_INT_SYNC_ERR:    Sync error interrupt
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable function.
 *           @arg Disable:          Disable function.
 * @retval None
 */
void DVP_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_DVP_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_DVP->IER, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(M4_DVP->IER, u32IntType);
    }
}

/**
 * @brief  Enable/disable DVP crop.
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable function.
 *           @arg Disable:          Disable function.
 * @retval None
 */
void DVP_CropCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_DVP->CTR_b.CROPEN, enNewState);
}

/**
 * @brief  Enable/disable DVP JPEG format.
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable function.
 *           @arg Disable:          Disable function.
 * @retval None
 */
void DVP_JPEGCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_DVP->CTR_b.JPEGEN, enNewState);
}

/**
 * @brief  Enable/disable DVP capture.
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable function.
 *           @arg Disable:          Disable function.
 * @retval None
 */
void DVP_CaptrueCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_DVP->CTR_b.CAPEN, enNewState);
}

/**
 * @brief  Get DVP capture function state.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Enable:   Capture function is enabled.
 *           - Disable:  Capture function is disabled.
 */
en_functional_state_t DVP_GetCaptrueCmdState(void)
{
    return ((0UL == READ_REG32(bM4_DVP->CTR_b.CAPEN)) ? Disable : Enable);
}

/**
 * @brief  Get the specified DVP flag status.
 * @param  [in] u32Flag             DVP flag
 *         This parameter can be any composed value of the following values:
 *           @arg DVP_FLAG_FRAME_START: Frame start flag
 *           @arg DVP_FLAG_LINE_START:  Line start flag
 *           @arg DVP_FLAG_LINE_END:    Line end flag
 *           @arg DVP_FLAG_FRAME_END:   Frame end flag
 *           @arg DVP_FLAG_FIFO_OVF:    FIFO overflow error flag
 *           @arg DVP_FLAG_SYNC_ERR:    Sync error interrupt
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 */
en_flag_status_t DVP_GetStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DVP_FLAG(u32Flag));

    return ((READ_REG32_BIT(M4_DVP->STR, u32Flag) == 0UL) ? Reset : Set);
}

/**
 * @brief  Clear the specified DVP flag status.
 * @param  [in] u32Flag             DVP flag
 *         This parameter can be any composed value of the following values:
 *           @arg DVP_FLAG_FRAME_START: Frame start flag
 *           @arg DVP_FLAG_LINE_START:  Line start flag
 *           @arg DVP_FLAG_LINE_END:    Line end flag
 *           @arg DVP_FLAG_FRAME_END:   Frame end flag
 *           @arg DVP_FLAG_FIFO_OVF:    FIFO overflow error flag
 *           @arg DVP_FLAG_SYNC_ERR:    Sync error interrupt
 * @retval None
 */
void DVP_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DVP_FLAG(u32Flag));

    CLEAR_REG32_BIT(M4_DVP->STR, u32Flag);
}

/**
 * @brief  Set DVP software sync code.
 * @param  [in] pstcSyncCode        Pointer to a @ref stc_dvp_sw_sync_code_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The parameter pstcSyncCode is NULL
 */
en_result_t DVP_SetSWSyncCode(const stc_dvp_sw_sync_code_t *pstcSyncCode)
{
    uint32_t u32RegValue;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcSyncCode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_DVP_SYNC_CODE(pstcSyncCode->u32FrameStartSyncCode));
        DDL_ASSERT(IS_DVP_SYNC_CODE(pstcSyncCode->u32LineStartSyncCode));
        DDL_ASSERT(IS_DVP_SYNC_CODE(pstcSyncCode->u32LineEndSyncCode));
        DDL_ASSERT(IS_DVP_SYNC_CODE(pstcSyncCode->u32FrameEndSyncCode));

        /* Set sync code. */
        u32RegValue = ((pstcSyncCode->u32FrameStartSyncCode << DVP_SSYNDR_FSDAT_POS) | \
                       (pstcSyncCode->u32LineStartSyncCode << DVP_SSYNDR_LSDAT_POS)  | \
                       (pstcSyncCode->u32LineEndSyncCode << DVP_SSYNDR_LEDAT_POS)    | \
                       (pstcSyncCode->u32FrameEndSyncCode << DVP_SSYNDR_FEDAT_POS));
        WRITE_REG32(M4_DVP->SSYNDR, u32RegValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set DVP software sync mask code.
 * @param  [in] pstcMaskCode        Pointer to a @ref stc_dvp_sw_mask_code_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The parameter pstcMaskCode is NULL
 */
en_result_t DVP_SetSWMaskCode(const stc_dvp_sw_mask_code_t *pstcMaskCode)
{
    uint32_t u32RegValue;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcMaskCode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_DVP_MASK_CODE(pstcMaskCode->u32FrameStartMaskCode));
        DDL_ASSERT(IS_DVP_MASK_CODE(pstcMaskCode->u32LineStartMaskCode));
        DDL_ASSERT(IS_DVP_MASK_CODE(pstcMaskCode->u32LineEndMaskCode));
        DDL_ASSERT(IS_DVP_MASK_CODE(pstcMaskCode->u32FrameEndMaskCode));

        /* Set sync code. */
        u32RegValue = ((pstcMaskCode->u32FrameStartMaskCode << DVP_SSYNMR_FSMSK_POS) | \
                       (pstcMaskCode->u32LineStartMaskCode << DVP_SSYNMR_LSMSK_POS)  | \
                       (pstcMaskCode->u32LineEndMaskCode << DVP_SSYNMR_LEMSK_POS)    | \
                       (pstcMaskCode->u32FrameEndMaskCode << DVP_SSYNMR_FEMSK_POS));
        WRITE_REG32(M4_DVP->SSYNMR, u32RegValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set DVP software sync mask code.
 * @param  [in] pstcConfig          Pointer to a @ref stc_dvp_crop_window_config_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The parameter pstcConfig is NULL
 */
en_result_t DVP_CropWindowConfig(const stc_dvp_crop_window_config_t *pstcConfig)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcConfig)
    {
        /* Check parameters */
        DDL_ASSERT(IS_DVP_CROP_WIN_X(pstcConfig->u32X));
        DDL_ASSERT(IS_DVP_CROP_WIN_Y(pstcConfig->u32Y));
        DDL_ASSERT(IS_DVP_CROP_WIN_XSIZE(pstcConfig->u32XSize));
        DDL_ASSERT(IS_DVP_CROP_WIN_YSIZE(pstcConfig->u32YSize));

        /* Configure crop window */
        WRITE_REG32(M4_DVP->CPSFTR, (pstcConfig->u32X | (pstcConfig->u32Y << DVP_CPSFTR_CSHIFT_POS)));
        WRITE_REG32(M4_DVP->CPSZER, (pstcConfig->u32XSize | (pstcConfig->u32YSize << DVP_CPSZER_CSIZE_POS)));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_DVP_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
