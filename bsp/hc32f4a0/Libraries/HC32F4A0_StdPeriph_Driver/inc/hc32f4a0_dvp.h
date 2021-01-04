/**
 *******************************************************************************
 * @file  hc32f4a0_dvp.h
 * @brief This file contains all the functions prototypes of the DVP(Digital
 *        Video Processor) driver library.
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
#ifndef __HC32F4A0_DVP_H__
#define __HC32F4A0_DVP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_DVP
 * @{
 */

#if (DDL_DVP_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DVP_Global_Types DVP Global Types
 * @{
 */

/**
 * @brief  DVP Initialization Structure definition
 */
typedef struct
{
    uint32_t u32SyncMode;           /*!< The DVP sync mode.
                                         This parameter can be a value of @ref DVP_Sync_Mode. */
    uint32_t u32DataWidth;          /*!< The DVP data interface width.
                                         This parameter can be a value of @ref DVP_Data_Width. */
    uint32_t u32CaptureMode;        /*!< The DVP capture mode.
                                         This parameter can be a value of @ref DVP_Capture_Mode. */
    uint32_t u32CaptureFreq;        /*!< The DVP capture frequence.
                                         This parameter can be a value of @ref DVP_Capture_Frequence. */
    uint32_t u32PIXCLKPolarity;     /*!< The DVP_PIXCLK Polarity.
                                         This parameter can be a value of @ref DVP_PIXCLK_Polarity. */
    uint32_t u32HSYNCPolarity;      /*!< The DVP_HSYNC Polarity.
                                         This parameter can be a value of @ref DVP_HSYNC_Polarity. */
    uint32_t u32VSYNCPolarity;      /*!< The DVP_VSYNC Polarity.
                                         This parameter can be a value of @ref DVP_VSYNC_Polarity. */
} stc_dvp_init_t;

/**
 * @brief  DVP Crop Window Configure definition
 */
typedef struct
{
    uint32_t u32X;                  /*!< The DVP window X offset
                                         This parameter can be a value between 0x00 and 0x3FFF */
    uint32_t u32Y;                  /*!< The DVP window Y offset
                                         This parameter can be a value between 0x00 and 0x3FFF */
    uint32_t u32XSize;              /*!< The DVP window pixel per line
                                         This parameter can be a value between 0x00 and 0x3FFF */
    uint32_t u32YSize;              /*!< The DVP window line number.
                                         This parameter can be a value between 0x00 and 0x3FFF */
} stc_dvp_crop_window_config_t;

/**
 * @brief  DVP Software Sync Code definition
 */
typedef struct
{
    uint32_t u32FrameStartSyncCode; /*!< The sync code of the frame start delimiter.
                                         This parameter can be a value between 0x00 and 0xFF */
    uint32_t u32LineStartSyncCode;  /*!< The sync code of the line start delimiter.
                                         This parameter can be a value between 0x00 and 0xFF */
    uint32_t u32LineEndSyncCode;    /*!< The sync code of the line end delimiter.
                                         This parameter can be a value between 0x00 and 0xFF */
    uint32_t u32FrameEndSyncCode;   /*!< The sync code of the frame end delimiter.
                                         This parameter can be a value between 0x00 and 0xFF */
} stc_dvp_sw_sync_code_t;

/**
 * @brief  DVP Software Mask Code definition
 */
typedef struct
{
    uint32_t u32FrameStartMaskCode; /*!< The mask code of the frame start delimiter.
                                         This parameter can be a value between between 0x00 and 0xFF */
    uint32_t u32LineStartMaskCode;  /*!< The mask code of the line start delimiter.
                                         This parameter can be a value between between 0x00 and 0xFF */
    uint32_t u32LineEndMaskCode;    /*!< The mask code of the line end delimiter.
                                         This parameter can be a value between between 0x00 and 0xFF */
    uint32_t u32FrameEndMaskCode;   /*!< The mask code of the frame end delimiter.
                                         This parameter can be a value between between 0x00 and 0xFF */
} stc_dvp_sw_mask_code_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DVP_Global_Macros DVP Global Macros
 * @{
 */

/** @defgroup DVP_Capture_Mode DVP Capture Mode
 * @{
 */
#define DVP_CAPT_MD_CONTINUOS_FRAME         (0UL)
#define DVP_CAPT_MD_SINGLE_FRAME            (DVP_CTR_CAPMD)
/**
 * @}
 */

/** @defgroup DVP_Sync_Mode DVP Sync Mode
 * @{
 */
#define DVP_SYNC_MD_HW                      (0UL)               /*!< Hardware sync */
#define DVP_SYNC_MD_SW                      (DVP_CTR_SWSYNC)    /*!< Software sync */
/**
 * @}
 */

/** @defgroup DVP_PIXCLK_Polarity DVP PIXCLK Polarity
 * @{
 */
#define DVP_PIXCLK_FALLING                  (0UL)               /*!< DVP_PIXCLK active on Falling edge */
#define DVP_PIXCLK_RISING                   (DVP_CTR_PIXCKSEL)  /*!< DVP_PIXCLK active on Rising edge */
/**
 * @}
 */

/** @defgroup DVP_HSYNC_Polarity DVP HSYNC Polarity
 * @{
 */
#define DVP_HSYNC_LOW                       (0UL)               /*!< DVP_HSYNC active Low */
#define DVP_HSYNC_HIGH                      (DVP_CTR_HSYNCSEL)  /*!< DVP_HSYNC active High */
/**
 * @}
 */

/** @defgroup DVP_VSYNC_Polarity DVP VSYNC Polarity
 * @{
 */
#define DVP_VSYNC_LOW                       (0UL)               /*!< DVP_VSYNC active Low */
#define DVP_VSYNC_HIGH                      (DVP_CTR_VSYNCSEL)  /*!< DVP_VSYNC active High */
/**
 * @}
 */

/**
 * @defgroup DVP_Capture_Frequence DVP Capture Frequence
 * @{
 */
#define DVP_CAPT_FREQ_ALL_FRAME             (0UL)               /*!< All frames are captured */
#define DVP_CAPT_FREQ_ONT_TIME_2FRAME       (DVP_CTR_CAPFRC_0)  /*!< One frame per 2 frames captured */
#define DVP_CAPT_FREQ_ONT_TIME_4FRAME       (DVP_CTR_CAPFRC_1)  /*!< One frame per 4 frames captured */
/**
 * @}
 */

/**
 * @defgroup DVP_Data_Width DVP Data Width
 * @{
 */
#define DVP_DATA_WIDTH_8BIT                 (0UL)               /*!< DVP captures 8-bit data on every DVP_PIXCLK clock */
#define DVP_DATA_WIDTH_10BIT                (DVP_CTR_BITSEL_0)  /*!< DVP captures 10-bit data on every DVP_PIXCLK clock */
#define DVP_DATA_WIDTH_12BIT                (DVP_CTR_BITSEL_1)  /*!< DVP captures 12-bit data on every DVP_PIXCLK clock */
#define DVP_DATA_WIDTH_14BIT                (DVP_CTR_BITSEL)    /*!< DVP captures 14-bit data on every DVP_PIXCLK clock */
/**
 * @}
 */

/**
 * @defgroup DVP_Flag DVP Flag
 * @{
 */
#define DVP_FLAG_FRAME_START                (DVP_STR_FSF)     /*!< Frame start flag */
#define DVP_FLAG_LINE_START                 (DVP_STR_LSF)     /*!< Line start flag */
#define DVP_FLAG_LINE_END                   (DVP_STR_LEF)     /*!< Line end flag */
#define DVP_FLAG_FRAME_END                  (DVP_STR_FEF)     /*!< Frame end flag */
#define DVP_FLAG_FIFO_OVF                   (DVP_STR_FIFOERF) /*!< FIFO overflow error flag */
#define DVP_FLAG_SYNC_ERR                   (DVP_STR_SQUERF)  /*!< Sync error flag */
#define DVP_FLAG_ALL                        (DVP_FLAG_SYNC_ERR   |             \
                                             DVP_FLAG_FIFO_OVF   |             \
                                             DVP_FLAG_LINE_END   |             \
                                             DVP_FLAG_LINE_START |             \
                                             DVP_FLAG_FRAME_END  |             \
                                             DVP_FLAG_FRAME_START)
/**
 * @}
 */

/**
 * @defgroup DVP_Interrupt DVP Interrupt
 * @{
 */
#define DVP_INT_FRAME_START                 (DVP_IER_FSIEN)     /*!< Frame start interrupt */
#define DVP_INT_LINE_START                  (DVP_IER_LSIEN)     /*!< Line start interrupt */
#define DVP_INT_LINE_END                    (DVP_IER_LEIEN)     /*!< Line end interrupt */
#define DVP_INT_FRAME_END                   (DVP_IER_FEIEN)     /*!< Frame end interrupt */
#define DVP_INT_FIFO_OVF                    (DVP_IER_FIFOERIEN) /*!< FIFO overflow error interrupt */
#define DVP_INT_SYNC_ERR                    (DVP_IER_SQUERIEN)  /*!< Sync error interrupt */
#define DVP_INT_ALL                         (DVP_INT_SYNC_ERR   |              \
                                             DVP_INT_FIFO_OVF   |              \
                                             DVP_INT_LINE_END   |              \
                                             DVP_INT_LINE_START |              \
                                             DVP_INT_FRAME_END  |              \
                                             DVP_INT_FRAME_START)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DVP_Global_Functions
 * @{
 */
en_result_t DVP_Init(const stc_dvp_init_t *pstcDvpInit);
void DVP_DeInit(void);
en_result_t DVP_StructInit(stc_dvp_init_t *pstcDvpInit);
void DVP_Cmd(en_functional_state_t enNewState);
void DVP_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState);
void DVP_CropCmd(en_functional_state_t enNewState);
void DVP_JPEGCmd(en_functional_state_t enNewState);
void DVP_CaptrueCmd(en_functional_state_t enNewState);
en_functional_state_t DVP_GetCaptrueCmdState(void);
en_flag_status_t DVP_GetStatus(uint32_t u32Flag);
void DVP_ClearStatus(uint32_t u32Flag);
en_result_t DVP_SetSWSyncCode(const stc_dvp_sw_sync_code_t *pstcSyncCode);
en_result_t DVP_SetSWMaskCode(const stc_dvp_sw_mask_code_t *pstcMaskCode);
en_result_t DVP_CropWindowConfig(const stc_dvp_crop_window_config_t *pstcConfig);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DVP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
