/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_vao.h
  * @author  FMSH Application Team
  * @brief   Head file of VAO FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LG0XX_FL_VAO_H
#define __FM33LG0XX_FL_VAO_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup VAO VAO
  * @brief VAO FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup VAO_FL_ES_INIT VAO Exported Init structures
  * @{
  */

/**
  * @brief FL VAO Init Sturcture definition
  */

/**
* @brief FL VAO Init Sturcture definition
*/
typedef struct
{
    /*! PH15输入使能 */
    uint32_t input;
    /*! PH15上拉使能 */
    uint32_t pullup;
    /*! PH15开漏输出使能 */
    uint32_t opendrainOutput;
    /*! PH15功能选择 */
    uint32_t mode;

} FL_VAO_IO_InitTypeDef;
typedef struct
{
    /*! 驱动能力配置 */
    uint32_t driveMode;
    /*! 工作电流大小*/
    uint32_t workingCurrentMode;

} FL_VAO_XTLF_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup VAO_FL_Exported_Constants VAO Exported Constants
  * @{
  */

#define    VAO_RSTCR_VBAT_RST_Pos                                 (0U)
#define    VAO_RSTCR_VBAT_RST_Msk                                 (0x1U << VAO_RSTCR_VBAT_RST_Pos)
#define    VAO_RSTCR_VBAT_RST                                     VAO_RSTCR_VBAT_RST_Msk

#define    VAO_XTLFCR_XTLFEN_Pos                                  (0U)
#define    VAO_XTLFCR_XTLFEN_Msk                                  (0xfU << VAO_XTLFCR_XTLFEN_Pos)
#define    VAO_XTLFCR_XTLFEN                                      VAO_XTLFCR_XTLFEN_Msk

#define    VAO_XTLFPR_DRVCFG_Pos                                  (4U)
#define    VAO_XTLFPR_DRVCFG_Msk                                  (0x7U << VAO_XTLFPR_DRVCFG_Pos)
#define    VAO_XTLFPR_DRVCFG                                      VAO_XTLFPR_DRVCFG_Msk

#define    VAO_XTLFPR_XTLFIPW_Pos                                 (0U)
#define    VAO_XTLFPR_XTLFIPW_Msk                                 (0xfU << VAO_XTLFPR_XTLFIPW_Pos)
#define    VAO_XTLFPR_XTLFIPW                                     VAO_XTLFPR_XTLFIPW_Msk

#define    VAO_FDIER_LFDET_IE_Pos                                 (0U)
#define    VAO_FDIER_LFDET_IE_Msk                                 (0x1U << VAO_FDIER_LFDET_IE_Pos)
#define    VAO_FDIER_LFDET_IE                                     VAO_FDIER_LFDET_IE_Msk

#define    VAO_FDISR_LFDETO_Pos                                   (1U)
#define    VAO_FDISR_LFDETO_Msk                                   (0x1U << VAO_FDISR_LFDETO_Pos)
#define    VAO_FDISR_LFDETO                                       VAO_FDISR_LFDETO_Msk

#define    VAO_FDISR_LFDETIF_Pos                                  (0U)
#define    VAO_FDISR_LFDETIF_Msk                                  (0x1U << VAO_FDISR_LFDETIF_Pos)
#define    VAO_FDISR_LFDETIF                                      VAO_FDISR_LFDETIF_Msk

#define    VAO_INEN_PHINEN_Pos                                    (15U)
#define    VAO_INEN_PHINEN_Msk                                    (0x1U << VAO_INEN_PHINEN_Pos)
#define    VAO_INEN_PHINEN                                        VAO_INEN_PHINEN_Msk

#define    VAO_PUEN_PHPUEN_Pos                                    (15U)
#define    VAO_PUEN_PHPUEN_Msk                                    (0x1U << VAO_PUEN_PHPUEN_Pos)
#define    VAO_PUEN_PHPUEN                                        VAO_PUEN_PHPUEN_Msk

#define    VAO_ODEN_PHODEN_Pos                                    (15U)
#define    VAO_ODEN_PHODEN_Msk                                    (0x1U << VAO_ODEN_PHODEN_Pos)
#define    VAO_ODEN_PHODEN                                        VAO_ODEN_PHODEN_Msk

#define    VAO_FCR_PH15FCR_Pos                                    (30U)
#define    VAO_FCR_PH15FCR_Msk                                    (0x3U << VAO_FCR_PH15FCR_Pos)
#define    VAO_FCR_PH15FCR                                        VAO_FCR_PH15FCR_Msk

#define    VAO_DOR_PHDO_Pos                                       (15U)
#define    VAO_DOR_PHDO_Msk                                       (0x1U << VAO_DOR_PHDO_Pos)
#define    VAO_DOR_PHDO                                           VAO_DOR_PHDO_Msk

#define    VAO_DIR_PHDIN_Pos                                      (15U)
#define    VAO_DIR_PHDIN_Msk                                      (0x1U << VAO_DIR_PHDIN_Pos)
#define    VAO_DIR_PHDIN                                          VAO_DIR_PHDIN_Msk

#define    VAO_VILR_PHVIL15_Pos                                   (15U)
#define    VAO_VILR_PHVIL15_Msk                                   (0x1U << VAO_VILR_PHVIL15_Pos)
#define    VAO_VILR_PHVIL15                                       VAO_VILR_PHVIL15_Msk






#define    FL_VAO_XTLF_ENABLE                                     (0x5U << VAO_XTLFCR_XTLFEN_Pos)
#define    FL_VAO_XTLF_DISABLE                                    (0xaU << VAO_XTLFCR_XTLFEN_Pos)

#define    FL_VAO_XTLF_DRIVE_LEVEL_NONE                           (0x0U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_1                              (0x1U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_2                              (0x2U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_3                              (0x3U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_4                              (0x4U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_5                              (0x5U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_6                              (0x6U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_DRIVE_LEVEL_7                              (0x7U << VAO_XTLFPR_DRVCFG_Pos)

#define    FL_VAO_XTLF_OUTPUT_LEVEL_NONE                          (0x0U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_1                             (0x1U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_2                             (0x2U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_3                             (0x3U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_4                             (0x4U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_5                             (0x5U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_6                             (0x6U << VAO_XTLFPR_DRVCFG_Pos)
#define    FL_VAO_XTLF_OUTPUT_LEVEL_7                             (0x7U << VAO_XTLFPR_DRVCFG_Pos)

#define    FL_VAO_XTLF_WORK_CURRENT_850NA                         (0x0U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_800NA                         (0x1U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_750NA                         (0x2U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_700NA                         (0x3U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_650NA                         (0x4U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_600NA                         (0x5U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_550NA                         (0x6U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_500NA                         (0x7U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_450NA                         (0x8U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_400NA                         (0x9U << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_350NA                         (0xaU << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_300NA                         (0xbU << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_250NA                         (0xcU << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_200NA                         (0xdU << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_150NA                         (0xeU << VAO_XTLFPR_XTLFIPW_Pos)
#define    FL_VAO_XTLF_WORK_CURRENT_100NA                         (0xfU << VAO_XTLFPR_XTLFIPW_Pos)


#define    FL_VAO_PH15_MODE_INPUT                                 (0x0U << VAO_FCR_PH15FCR_Pos)
#define    FL_VAO_PH15_MODE_OUTPUT                                (0x1U << VAO_FCR_PH15FCR_Pos)
#define    FL_VAO_PH15_MODE_RTCOUT                                (0x2U << VAO_FCR_PH15FCR_Pos)


#define    FL_VAO_PH15_THRESHOLD_NORMAL                           (0x0U << VAO_VILR_PHVIL15_Pos)
#define    FL_VAO_PH15_THRESHOLD_LOW                              (0x1U << VAO_VILR_PHVIL15_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup VAO_FL_Exported_Functions VAO Exported Functions
  * @{
  */

/**
  * @brief    VBAT电源域寄存器复位使能
  * @rmtoll   RSTCR    VBAT_RST    FL_VAO_EnableReset
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_EnableReset(VAO_Type *VAOx)
{
    SET_BIT(VAOx->RSTCR, VAO_RSTCR_VBAT_RST_Msk);
}

/**
  * @brief    获取VBAT电源域寄存器复位控制状态
  * @rmtoll   RSTCR    VBAT_RST    FL_VAO_IsEnabledReset
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_IsEnabledReset(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->RSTCR, VAO_RSTCR_VBAT_RST_Msk) == VAO_RSTCR_VBAT_RST_Msk);
}

/**
  * @brief    VBAT电源域寄存器复位撤销
  * @rmtoll   RSTCR    VBAT_RST    FL_VAO_DisableReset
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_DisableReset(VAO_Type *VAOx)
{
    CLEAR_BIT(VAOx->RSTCR, VAO_RSTCR_VBAT_RST_Msk);
}

/**
  * @brief    使能XTLF
  * @rmtoll   XTLFCR    XTLFEN    FL_VAO_XTLF_Enable
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_XTLF_Enable(VAO_Type *VAOx)
{
    WRITE_REG(VAOx->XTLFCR, FL_VAO_XTLF_ENABLE);
}

/**
  * @brief    获取XTLF状态
  * @rmtoll   XTLFCR    XTLFEN    FL_VAO_XTLF_IsEnabled
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_XTLF_IsEnabled(VAO_Type *VAOx)
{
    return (uint32_t)(READ_REG(VAOx->XTLFCR));
}

/**
  * @brief    禁止XTLF
  * @rmtoll   XTLFCR    XTLFEN    FL_VAO_XTLF_Disable
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_XTLF_Disable(VAO_Type *VAOx)
{
    WRITE_REG(VAOx->XTLFCR, FL_VAO_XTLF_DISABLE);
}

/**
  * @brief    设置输出级驱动等级
  * @rmtoll   XTLFPR    DRVCFG    FL_VAO_XTLF_SetDriveLevel
  * @param    VAOx VAO instance
  * @param    level This parameter can be one of the following values:
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_NONE
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_1
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_2
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_3
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_4
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_5
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_6
  *           @arg @ref FL_VAO_XTLF_DRIVE_LEVEL_7
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_XTLF_SetDriveLevel(VAO_Type *VAOx, uint32_t level)
{
    MODIFY_REG(VAOx->XTLFPR, VAO_XTLFPR_DRVCFG_Msk, level);
}

/**
  * @brief    Get output drive  Level
  * @rmtoll   XTLFPR    DRVCFG    FL_VAO_XTLF_GetDriveLevel
  * @param    VAOx VAO instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_NONE
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_1
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_2
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_3
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_4
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_5
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_6
  *           @arg @ref FL_VAO_XTLF_OUTPUT_LEVEL_7
  */
__STATIC_INLINE uint32_t FL_VAO_XTLF_GetDriveLevel(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->XTLFPR, VAO_XTLFPR_DRVCFG_Msk));
}

/**
  * @brief    Set XTLF working current
  * @rmtoll   XTLFPR    XTLFIPW    FL_VAO_XTLF_SetWorkCurrent
  * @param    VAOx VAO instance
  * @param    current This parameter can be one of the following values:
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_850NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_800NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_750NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_700NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_650NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_600NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_550NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_500NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_450NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_400NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_350NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_300NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_250NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_200NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_150NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_100NA
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_XTLF_SetWorkCurrent(VAO_Type *VAOx, uint32_t current)
{
    MODIFY_REG(VAOx->XTLFPR, VAO_XTLFPR_XTLFIPW_Msk, current);
}

/**
  * @brief    Get XTLF working current
  * @rmtoll   XTLFPR    XTLFIPW    FL_VAO_XTLF_GetWorkCurrent
  * @param    VAOx VAO instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_850NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_800NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_750NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_700NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_650NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_600NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_550NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_500NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_450NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_400NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_350NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_300NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_250NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_200NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_150NA
  *           @arg @ref FL_VAO_XTLF_WORK_CURRENT_100NA
  */
__STATIC_INLINE uint32_t FL_VAO_XTLF_GetWorkCurrent(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->XTLFPR, VAO_XTLFPR_XTLFIPW_Msk));
}

/**
  * @brief    XTLF  detect interrupt enable
  * @rmtoll   FDIER    LFDET_IE    FL_VAO_EnableIT_XTLFFail
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_EnableIT_XTLFFail(VAO_Type *VAOx)
{
    SET_BIT(VAOx->FDIER, VAO_FDIER_LFDET_IE_Msk);
}

/**
  * @brief    Get XTLF detect interrupt enable status
  * @rmtoll   FDIER    LFDET_IE    FL_VAO_IsEnabledIT_XTLFFail
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_IsEnabledIT_XTLFFail(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->FDIER, VAO_FDIER_LFDET_IE_Msk) == VAO_FDIER_LFDET_IE_Msk);
}

/**
  * @brief    XTLF  detect interrupt disable
  * @rmtoll   FDIER    LFDET_IE    FL_VAO_DisableIT_XTLFFail
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_DisableIT_XTLFFail(VAO_Type *VAOx)
{
    CLEAR_BIT(VAOx->FDIER, VAO_FDIER_LFDET_IE_Msk);
}

/**
  * @brief    Get XTLF  detect output
  * @rmtoll   FDISR    LFDETO    FL_VAO_GetXTLFFailOutput
  * @param    VAOx VAO instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_VAO_GetXTLFFailOutput(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->FDISR, VAO_FDISR_LFDETO_Msk) >> VAO_FDISR_LFDETO_Pos);
}

/**
  * @brief    Get XTLF  detect interrupt flag
  * @rmtoll   FDISR    LFDETIF    FL_VAO_IsActiveFlag_XTLFFail
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_IsActiveFlag_XTLFFail(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->FDISR, VAO_FDISR_LFDETIF_Msk) == (VAO_FDISR_LFDETIF_Msk));
}

/**
  * @brief    Clear XTLF  detect interrupt flag
  * @rmtoll   FDISR    LFDETIF    FL_VAO_ClearFlag_XTLFFail
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_ClearFlag_XTLFFail(VAO_Type *VAOx)
{
    WRITE_REG(VAOx->FDISR, VAO_FDISR_LFDETIF_Msk);
}

/**
  * @brief    PH15 input enable
  * @rmtoll   INEN    PHINEN    FL_VAO_GPIO_EnablePH15Input
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_EnablePH15Input(VAO_Type *VAOx)
{
    SET_BIT(VAOx->INEN, VAO_INEN_PHINEN_Msk);
}

/**
  * @brief    Get PH15 input enable status
  * @rmtoll   INEN    PHINEN    FL_VAO_GPIO_IsEnabledPH15Input
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_IsEnabledPH15Input(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->INEN, VAO_INEN_PHINEN_Msk) == VAO_INEN_PHINEN_Msk);
}

/**
  * @brief    PH15 input disable
  * @rmtoll   INEN    PHINEN    FL_VAO_GPIO_DisablePH15Input
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_DisablePH15Input(VAO_Type *VAOx)
{
    CLEAR_BIT(VAOx->INEN, VAO_INEN_PHINEN_Msk);
}

/**
  * @brief    PH15 pullup enable
  * @rmtoll   PUEN    PHPUEN    FL_VAO_GPIO_EnablePH15Pullup
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_EnablePH15Pullup(VAO_Type *VAOx)
{
    SET_BIT(VAOx->PUEN, VAO_PUEN_PHPUEN_Msk);
}

/**
  * @brief    Get PH15 pullup enable status
  * @rmtoll   PUEN    PHPUEN    FL_VAO_GPIO_IsEnabledPH15Pullup
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_IsEnabledPH15Pullup(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->PUEN, VAO_PUEN_PHPUEN_Msk) == VAO_PUEN_PHPUEN_Msk);
}

/**
  * @brief    PH15 pullup disable
  * @rmtoll   PUEN    PHPUEN    FL_VAO_GPIO_DisablePH15Pullup
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_DisablePH15Pullup(VAO_Type *VAOx)
{
    CLEAR_BIT(VAOx->PUEN, VAO_PUEN_PHPUEN_Msk);
}

/**
  * @brief    PH15 pullup enable
  * @rmtoll   ODEN    PHODEN    FL_VAO_GPIO_EnablePH15OpenDrain
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_EnablePH15OpenDrain(VAO_Type *VAOx)
{
    SET_BIT(VAOx->ODEN, VAO_ODEN_PHODEN_Msk);
}

/**
  * @brief    Get PH15 pullup enable status
  * @rmtoll   ODEN    PHODEN    FL_VAO_GPIO_IsEnabledPH15OpenDrain
  * @param    VAOx VAO instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_IsEnabledPH15OpenDrain(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->ODEN, VAO_ODEN_PHODEN_Msk) == VAO_ODEN_PHODEN_Msk);
}

/**
  * @brief    PH15 pullup disable
  * @rmtoll   ODEN    PHODEN    FL_VAO_GPIO_DisablePH15OpenDrain
  * @param    VAOx VAO instance
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_DisablePH15OpenDrain(VAO_Type *VAOx)
{
    CLEAR_BIT(VAOx->ODEN, VAO_ODEN_PHODEN_Msk);
}

/**
  * @brief    Set PH15 mode
  * @rmtoll   FCR    PH15FCR    FL_VAO_GPIO_SetPH15Mode
  * @param    VAOx VAO instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_VAO_PH15_MODE_INPUT
  *           @arg @ref FL_VAO_PH15_MODE_OUTPUT
  *           @arg @ref FL_VAO_PH15_MODE_RTCOUT
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_SetPH15Mode(VAO_Type *VAOx, uint32_t mode)
{
    MODIFY_REG(VAOx->FCR, VAO_FCR_PH15FCR_Msk, mode);
}

/**
  * @brief    Get PH15 mode
  * @rmtoll   FCR    PH15FCR    FL_VAO_GPIO_GetPH15Mode
  * @param    VAOx VAO instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VAO_PH15_MODE_INPUT
  *           @arg @ref FL_VAO_PH15_MODE_OUTPUT
  *           @arg @ref FL_VAO_PH15_MODE_RTCOUT
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_GetPH15Mode(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->FCR, VAO_FCR_PH15FCR_Msk));
}

/**
  * @brief    Set PH15 output data register
  * @rmtoll   DOR    PHDO    FL_VAO_GPIO_WritePH15Output
  * @param    VAOx VAO instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_WritePH15Output(VAO_Type *VAOx, uint32_t data)
{
    MODIFY_REG(VAOx->DOR, (0x1U << 15U), (data << 15U));
}

/**
  * @brief    Get PH15 output data
  * @rmtoll   DOR    PHDO    FL_VAO_GPIO_ReadPH15Output
  * @param    VAOx VAO instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_ReadPH15Output(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->DOR, (0x1U << 15U)) >> 15U);
}

/**
  * @brief    Get PH15 input data
  * @rmtoll   DIR    PHDIN    FL_VAO_GPIO_ReadPH15Input
  * @param    VAOx VAO instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_ReadPH15Input(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->DIR, (0x1U << 15U)) >> 15U);
}

/**
  * @brief    Set PH15 input low threshold value
  * @rmtoll   VILR    PHVIL15    FL_VAO_GPIO_SetPH15Threshold
  * @param    VAOx VAO instance
  * @param    value This parameter can be one of the following values:
  *           @arg @ref FL_VAO_PH15_THRESHOLD_NORMAL
  *           @arg @ref FL_VAO_PH15_THRESHOLD_LOW
  * @retval   None
  */
__STATIC_INLINE void FL_VAO_GPIO_SetPH15Threshold(VAO_Type *VAOx, uint32_t value)
{
    MODIFY_REG(VAOx->VILR, VAO_VILR_PHVIL15_Msk, value);
}

/**
  * @brief    Get PH15 input low threshold value
  * @rmtoll   VILR    PHVIL15    FL_VAO_GPIO_GetPH15Threshold
  * @param    VAOx VAO instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VAO_PH15_THRESHOLD_NORMAL
  *           @arg @ref FL_VAO_PH15_THRESHOLD_LOW
  */
__STATIC_INLINE uint32_t FL_VAO_GPIO_GetPH15Threshold(VAO_Type *VAOx)
{
    return (uint32_t)(READ_BIT(VAOx->VILR, VAO_VILR_PHVIL15_Msk));
}

/**
  * @}
  */

/** @defgroup VAO_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
//#warning "PLEASE ANNOUCE THE INIT AND DEINIT FUNCTIONS HERE!!!"
FL_ErrorStatus FL_VAO_DeInit(VAO_Type *VAOx);
FL_ErrorStatus FL_VAO_IO_Init(VAO_Type *VAOx, FL_VAO_IO_InitTypeDef *VAO_InitStruct);
FL_ErrorStatus FL_VAO_XTLF_Init(VAO_Type *VAOx, FL_VAO_XTLF_InitTypeDef *VAO_XTLF_InitStruct);
void FL_VAO_IO_StructInit(FL_VAO_IO_InitTypeDef *VAO_InitStruct);
void FL_VAO_XTLF_StructInit(FL_VAO_XTLF_InitTypeDef *VAO_XTLF_InitStruct);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LG0XX_FL_VAO_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
