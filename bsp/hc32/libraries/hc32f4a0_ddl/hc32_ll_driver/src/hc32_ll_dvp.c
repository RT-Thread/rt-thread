/**
 *******************************************************************************
 * @file  hc32_ll_dvp.c
 * @brief This file provides firmware functions to manage the DVP(Digital Video
 *        Processor) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-09-30       CDT             Modify typo
                                    Add function: DVP_GetCaptureState
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_dvp.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_DVP DVP
 * @brief Digital Video Processor Driver Library
 * @{
 */

#if (LL_DVP_ENABLE == DDL_ON)

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

#define IS_DVP_CROP_WIN_ROW_START_LINE(x)       ((x) <= 0x3FFFU)

#define IS_DVP_CROP_WIN_COLUMN_START_LINE(x)    ((x) <= 0x3FFFU)

#define IS_DVP_CROP_WIN_ROW_LINE_SIZE(x)        (((x) >= 0x04U) && ((x) <= 0x3FFFU))

#define IS_DVP_CROP_WIN_COLUMN_LINE_SIZE(x)     ((x) <= 0x3FFFU)
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
 * @brief  Set the fields of structure stc_dvp_init_t to default values
 * @param  [out] pstcDvpInit            Pointer to a @ref stc_dvp_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDvpInit value is NULL.
 */
int32_t DVP_StructInit(stc_dvp_init_t *pstcDvpInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDvpInit) {
        pstcDvpInit->u32SyncMode       = DVP_SYNC_MD_HW;
        pstcDvpInit->u32DataWidth      = DVP_DATA_WIDTH_8BIT;
        pstcDvpInit->u32CaptureMode    = DVP_CAPT_MD_CONTINUOS_FRAME;
        pstcDvpInit->u32CaptureFreq    = DVP_CAPT_FREQ_ALL_FRAME;
        pstcDvpInit->u32PIXCLKPolarity = DVP_PIXCLK_FALLING;
        pstcDvpInit->u32HSYNCPolarity  = DVP_HSYNC_LOW;
        pstcDvpInit->u32VSYNCPolarity  = DVP_VSYNC_LOW;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize DVP function.
 * @param  [in] pstcDvpInit             Pointer to a @ref stc_dvp_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDvpInit value is NULL.
 */
int32_t DVP_Init(const stc_dvp_init_t *pstcDvpInit)
{
    uint32_t u32Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDvpInit) {
        DDL_ASSERT(IS_DVP_SYNC_MD(pstcDvpInit->u32SyncMode));
        DDL_ASSERT(IS_DVP_DATA_WIDTH(pstcDvpInit->u32DataWidth));
        DDL_ASSERT(IS_DVP_CAPT_MD(pstcDvpInit->u32CaptureMode));
        DDL_ASSERT(IS_DVP_CAPT_FREQ(pstcDvpInit->u32CaptureFreq));
        DDL_ASSERT(IS_DVP_PIXCLK_POLARITY(pstcDvpInit->u32PIXCLKPolarity));
        DDL_ASSERT(IS_DVP_HSYNC_POLARITY(pstcDvpInit->u32HSYNCPolarity));
        DDL_ASSERT(IS_DVP_VSYNC_POLARITY(pstcDvpInit->u32VSYNCPolarity));

        /* Configure DVP */
        u32Value = (pstcDvpInit->u32SyncMode    | pstcDvpInit->u32DataWidth      | pstcDvpInit->u32CaptureMode   | \
                    pstcDvpInit->u32CaptureFreq | pstcDvpInit->u32PIXCLKPolarity | pstcDvpInit->u32HSYNCPolarity | \
                    pstcDvpInit->u32VSYNCPolarity);
        WRITE_REG32(CM_DVP->CTR, u32Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize DVP function.
 * @param  None
 * @retval None
 */
void DVP_DeInit(void)
{
    WRITE_REG32(CM_DVP->CTR, 0UL);
    WRITE_REG32(CM_DVP->STR, 0UL);
    WRITE_REG32(CM_DVP->IER, 0UL);
    WRITE_REG32(CM_DVP->SSYNDR, 0UL);
    WRITE_REG32(CM_DVP->SSYNMR, 0xFFFFFFFFUL);
    WRITE_REG32(CM_DVP->CPSFTR, 0UL);
    WRITE_REG32(CM_DVP->CPSZER, 0UL);
}

/**
 * @brief  Enable/disable DVP.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DVP_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_DVP->CTR, DVP_CTR_DVPEN);
    } else {
        CLR_REG32_BIT(CM_DVP->CTR, DVP_CTR_DVPEN);
    }
}

/**
 * @brief  Enable/disable the specified DVP interrupt.
 * @param  [in] u32IntType              DVP interrupt type
 *         This parameter can be any composed value of the macros group @ref DVP_Interrupt
 *           @arg DVP_INT_FRAME_START:  Frame start interrupt
 *           @arg DVP_INT_LINE_START:   Line start interrupt
 *           @arg DVP_INT_LINE_END:     Line end interrupt
 *           @arg DVP_INT_FRAME_END:    Frame end interrupt
 *           @arg DVP_INT_FIFO_OVF:     FIFO overflow error interrupt
 *           @arg DVP_INT_SYNC_ERR:     Sync error interrupt
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DVP_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DVP_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_DVP->IER, u32IntType);
    } else {
        CLR_REG32_BIT(CM_DVP->IER, u32IntType);
    }
}

/**
 * @brief  Enable/disable DVP crop.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DVP_CropCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_DVP->CTR_b.CROPEN, enNewState);
}

/**
 * @brief  Enable/disable DVP JPEG format.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DVP_JPEGCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_DVP->CTR, DVP_CTR_JPEGEN);
    } else {
        CLR_REG32_BIT(CM_DVP->CTR, DVP_CTR_JPEGEN);
    }
}

/**
 * @brief  Enable/disable DVP capture.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DVP_CaptureCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_DVP->CTR, DVP_CTR_CAPEN);
    } else {
        CLR_REG32_BIT(CM_DVP->CTR, DVP_CTR_CAPEN);
    }
}

/**
 * @brief  Get DVP capture status.
 * @param  None
 * @retval An @ref en_functional_state_t enumeration value.
 *           - ENABLE: DVP capture started
 *           - DISABLE: DVP capture stopped
 */
en_functional_state_t DVP_GetCaptureState(void)
{
    return (READ_REG32_BIT(CM_DVP->CTR, DVP_CTR_CAPEN) > 0UL) ? ENABLE : DISABLE;
}

/**
 * @brief  Get the specified DVP flag status.
 * @param  [in] u32Flag                 DVP flag
 *         This parameter can be any composed value of the macros group @ref DVP_Flag
 *           @arg DVP_FLAG_FRAME_START: Frame start flag
 *           @arg DVP_FLAG_LINE_START:  Line start flag
 *           @arg DVP_FLAG_LINE_END:    Line end flag
 *           @arg DVP_FLAG_FRAME_END:   Frame end flag
 *           @arg DVP_FLAG_FIFO_OVF:    FIFO overflow error flag
 *           @arg DVP_FLAG_SYNC_ERR:    Sync error interrupt
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t DVP_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_DVP_FLAG(u32Flag));

    return ((READ_REG32_BIT(CM_DVP->STR, u32Flag) == 0UL) ? RESET : SET);
}

/**
 * @brief  Clear the specified DVP flag status.
 * @param  [in] u32Flag                 DVP flag
 *         This parameter can be any composed value of the macros group @ref DVP_Flag
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
    DDL_ASSERT(IS_DVP_FLAG(u32Flag));

    CLR_REG32_BIT(CM_DVP->STR, u32Flag);
}

/**
 * @brief  Set DVP software sync code.
 * @param  [in] pstcSyncCode            Pointer to a @ref stc_dvp_sw_sync_code_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The parameter pstcSyncCode value is NULL.
 */
int32_t DVP_SetSWSyncCode(const stc_dvp_sw_sync_code_t *pstcSyncCode)
{
    uint32_t u32Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSyncCode) {
        /* Set sync code. */
        u32Value = (((uint32_t)pstcSyncCode->u8FrameStartSyncCode << DVP_SSYNDR_FSDAT_POS) | \
                    ((uint32_t)pstcSyncCode->u8LineStartSyncCode << DVP_SSYNDR_LSDAT_POS)  | \
                    ((uint32_t)pstcSyncCode->u8LineEndSyncCode << DVP_SSYNDR_LEDAT_POS)    | \
                    ((uint32_t)pstcSyncCode->u8FrameEndSyncCode << DVP_SSYNDR_FEDAT_POS));
        WRITE_REG32(CM_DVP->SSYNDR, u32Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set DVP software sync mask code.
 * @param  [in] pstcMaskCode            Pointer to a @ref stc_dvp_sw_mask_code_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The parameter pstcMaskCode value is NULL.
 */
int32_t DVP_SetSWMaskCode(const stc_dvp_sw_mask_code_t *pstcMaskCode)
{
    uint32_t u32Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcMaskCode) {
        /* Set sync code. */
        u32Value = (((uint32_t)pstcMaskCode->u8FrameStartMaskCode << DVP_SSYNMR_FSMSK_POS) | \
                    ((uint32_t)pstcMaskCode->u8LineStartMaskCode << DVP_SSYNMR_LSMSK_POS)  | \
                    ((uint32_t)pstcMaskCode->u8LineEndMaskCode << DVP_SSYNMR_LEMSK_POS)    | \
                    ((uint32_t)pstcMaskCode->u8FrameEndMaskCode << DVP_SSYNMR_FEMSK_POS));
        WRITE_REG32(CM_DVP->SSYNMR, u32Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set DVP software sync mask code.
 * @param  [in] pstcConfig              Pointer to a @ref stc_dvp_crop_window_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The parameter pstcConfig value is NULL.
 */
int32_t DVP_CropWindowConfig(const stc_dvp_crop_window_config_t *pstcConfig)
{
    uint32_t u32Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcConfig) {
        DDL_ASSERT(IS_DVP_CROP_WIN_ROW_START_LINE(pstcConfig->u16RowStartLine));
        DDL_ASSERT(IS_DVP_CROP_WIN_COLUMN_START_LINE(pstcConfig->u16ColumnStartLine));
        DDL_ASSERT(IS_DVP_CROP_WIN_ROW_LINE_SIZE(pstcConfig->u16RowLineSize));
        DDL_ASSERT(IS_DVP_CROP_WIN_COLUMN_LINE_SIZE(pstcConfig->u16ColumnLineSize));

        /* Configure crop window */
        u32Value = ((uint32_t)pstcConfig->u16RowStartLine | \
                    ((uint32_t)pstcConfig->u16ColumnStartLine << DVP_CPSFTR_CSHIFT_POS));
        WRITE_REG32(CM_DVP->CPSFTR, u32Value);

        u32Value = ((uint32_t)pstcConfig->u16RowLineSize | \
                    ((uint32_t)pstcConfig->u16ColumnLineSize << DVP_CPSZER_CSIZE_POS));
        WRITE_REG32(CM_DVP->CPSZER, u32Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_DVP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
