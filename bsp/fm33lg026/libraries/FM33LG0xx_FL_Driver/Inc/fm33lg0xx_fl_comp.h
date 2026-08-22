/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_comp.h
  * @author  FMSH Application Team
  * @brief   Head file of COMP FL Module
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
#ifndef __FM33LG0XX_FL_COMP_H
#define __FM33LG0XX_FL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup COMP COMP
  * @brief COMP FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup COMP_FL_ES_INIT COMP Exported Init structures
  * @{
  */

/**
  * @brief FL COMP Init Sturcture definition
  */
typedef struct
{
    /** 比较器正向输入选择 */
    uint32_t positiveInput;
    /** 比较器反向输入选择 */
    uint32_t negativeInput;
    /** 结果输出极性 */
    uint32_t polarity;
    /** 中断触发边沿选择 */
    uint32_t edge;
    /** 数字滤波器使能 */
    uint32_t digitalFilter;
    /** 数字滤波器长度 */
    uint32_t digitalFilterLen;
} FL_COMP_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup COMP_FL_Exported_Constants COMP Exported Constants
  * @{
  */

#define    COMP_CR_TRGOEN_Pos                                     (24U)
#define    COMP_CR_TRGOEN_Msk                                     (0x1U << COMP_CR_TRGOEN_Pos)
#define    COMP_CR_TRGOEN                                         COMP_CR_TRGOEN_Msk

#define    COMP_CR_DFLEN_Pos                                      (19U)
#define    COMP_CR_DFLEN_Msk                                      (0x1fU << COMP_CR_DFLEN_Pos)
#define    COMP_CR_DFLEN                                          COMP_CR_DFLEN_Msk

#define    COMP_CR_WINMODE_Pos                                    (18U)
#define    COMP_CR_WINMODE_Msk                                    (0x1U << COMP_CR_WINMODE_Pos)
#define    COMP_CR_WINMODE                                        COMP_CR_WINMODE_Msk

#define    COMP_CR_POLAR_Pos                                      (17U)
#define    COMP_CR_POLAR_Msk                                      (0x1U << COMP_CR_POLAR_Pos)
#define    COMP_CR_POLAR                                          COMP_CR_POLAR_Msk

#define    COMP_CR_DFEN_Pos                                       (16U)
#define    COMP_CR_DFEN_Msk                                       (0x1U << COMP_CR_DFEN_Pos)
#define    COMP_CR_DFEN                                           COMP_CR_DFEN_Msk

#define    COMP_CR_MODE_Pos                                       (14U)
#define    COMP_CR_MODE_Msk                                       (0x3U << COMP_CR_MODE_Pos)
#define    COMP_CR_MODE                                           COMP_CR_MODE_Msk

#define    COMP_CR_CMPO_Pos                                       (8U)
#define    COMP_CR_CMPO_Msk                                       (0x1U << COMP_CR_CMPO_Pos)
#define    COMP_CR_CMPO                                           COMP_CR_CMPO_Msk

#define    COMP_CR_VPSEL_Pos                                      (4U)
#define    COMP_CR_VPSEL_Msk                                      (0x7U << COMP_CR_VPSEL_Pos)
#define    COMP_CR_VPSEL                                          COMP_CR_VPSEL_Msk

#define    COMP_CR_VNSEL_Pos                                      (1U)
#define    COMP_CR_VNSEL_Msk                                      (0x7U << COMP_CR_VNSEL_Pos)
#define    COMP_CR_VNSEL                                          COMP_CR_VNSEL_Msk

#define    COMP_CR_CMPEN_Pos                                      (0U)
#define    COMP_CR_CMPEN_Msk                                      (0x1U << COMP_CR_CMPEN_Pos)
#define    COMP_CR_CMPEN                                          COMP_CR_CMPEN_Msk

#define    COMP_ICR_OWW_IE_Pos                                    (25U)
#define    COMP_ICR_OWW_IE_Msk                                    (0x1U << COMP_ICR_OWW_IE_Pos)
#define    COMP_ICR_OWW_IE                                        COMP_ICR_OWW_IE_Msk

#define    COMP_ICR_WIN_IE_Pos                                    (24U)
#define    COMP_ICR_WIN_IE_Msk                                    (0x1U << COMP_ICR_WIN_IE_Pos)
#define    COMP_ICR_WIN_IE                                        COMP_ICR_WIN_IE_Msk

#define    COMP_ICR_CMP3SEL_Pos                                   (18U)
#define    COMP_ICR_CMP3SEL_Msk                                   (0x3U << COMP_ICR_CMP3SEL_Pos)
#define    COMP_ICR_CMP3SEL                                       COMP_ICR_CMP3SEL_Msk

#define    COMP_ICR_CMP3IE_Pos                                    (16U)
#define    COMP_ICR_CMP3IE_Msk                                    (0x1U << COMP_ICR_CMP3IE_Pos)
#define    COMP_ICR_CMP3IE                                        COMP_ICR_CMP3IE_Msk

#define    COMP_ICR_CMP2SEL_Pos                                   (10U)
#define    COMP_ICR_CMP2SEL_Msk                                   (0x3U << COMP_ICR_CMP2SEL_Pos)
#define    COMP_ICR_CMP2SEL                                       COMP_ICR_CMP2SEL_Msk

#define    COMP_ICR_CMP2IE_Pos                                    (8U)
#define    COMP_ICR_CMP2IE_Msk                                    (0x1U << COMP_ICR_CMP2IE_Pos)
#define    COMP_ICR_CMP2IE                                        COMP_ICR_CMP2IE_Msk

#define    COMP_ICR_CMP1SEL_Pos                                   (2U)
#define    COMP_ICR_CMP1SEL_Msk                                   (0x3U << COMP_ICR_CMP1SEL_Pos)
#define    COMP_ICR_CMP1SEL                                       COMP_ICR_CMP1SEL_Msk

#define    COMP_ICR_CMP1IE_Pos                                    (0U)
#define    COMP_ICR_CMP1IE_Msk                                    (0x1U << COMP_ICR_CMP1IE_Pos)
#define    COMP_ICR_CMP1IE                                        COMP_ICR_CMP1IE_Msk

#define    COMP_ISR_OOW_IF_Pos                                    (4U)
#define    COMP_ISR_OOW_IF_Msk                                    (0x1U << COMP_ISR_OOW_IF_Pos)
#define    COMP_ISR_OOW_IF                                        COMP_ISR_OOW_IF_Msk

#define    COMP_ISR_WIN_IF_Pos                                    (3U)
#define    COMP_ISR_WIN_IF_Msk                                    (0x1U << COMP_ISR_WIN_IF_Pos)
#define    COMP_ISR_WIN_IF                                        COMP_ISR_WIN_IF_Msk

#define    COMP_ISR_CMP3IF_Pos                                    (2U)
#define    COMP_ISR_CMP3IF_Msk                                    (0x1U << COMP_ISR_CMP3IF_Pos)
#define    COMP_ISR_CMP3IF                                        COMP_ISR_CMP3IF_Msk

#define    COMP_ISR_CMP2IF_Pos                                    (1U)
#define    COMP_ISR_CMP2IF_Msk                                    (0x1U << COMP_ISR_CMP2IF_Pos)
#define    COMP_ISR_CMP2IF                                        COMP_ISR_CMP2IF_Msk

#define    COMP_ISR_CMP1IF_Pos                                    (0U)
#define    COMP_ISR_CMP1IF_Msk                                    (0x1U << COMP_ISR_CMP1IF_Pos)
#define    COMP_ISR_CMP1IF                                        COMP_ISR_CMP1IF_Msk

#define    COMP_BUFCR_BUFBYP_Pos                                  (2U)
#define    COMP_BUFCR_BUFBYP_Msk                                  (0x1U << COMP_BUFCR_BUFBYP_Pos)
#define    COMP_BUFCR_BUFBYP                                      COMP_BUFCR_BUFBYP_Msk

#define    COMP_BUFCR_BUFSEL_Pos                                  (1U)
#define    COMP_BUFCR_BUFSEL_Msk                                  (0x1U << COMP_BUFCR_BUFSEL_Pos)
#define    COMP_BUFCR_BUFSEL                                      COMP_BUFCR_BUFSEL_Msk

#define    COMP_BUFCR_BUFENB_Pos                                  (0U)
#define    COMP_BUFCR_BUFENB_Msk                                  (0x1U << COMP_BUFCR_BUFENB_Pos)
#define    COMP_BUFCR_BUFENB                                      COMP_BUFCR_BUFENB_Msk






#define    FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK                   (0x0U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_4APBCLK                   (0x3U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_5APBCLK                   (0x4U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_6APBCLK                   (0x5U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_7APBCLK                   (0x6U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_8APBCLK                   (0x7U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_9APBCLK                   (0x8U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_10APBCLK                  (0x9U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_11APBCLK                  (0xaU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_12APBCLK                  (0xbU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_13APBCLK                  (0xcU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_14APBCLK                  (0xdU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_15APBCLK                  (0xeU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_16APBCLK                  (0xfU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_17APBCLK                  (0x10U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_18APBCLK                  (0x11U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_19APBCLK                  (0x12U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_20APBCLK                  (0x13U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_21APBCLK                  (0x14U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_22APBCLK                  (0x15U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_23APBCLK                  (0x16U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_24APBCLK                  (0x17U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_25APBCLK                  (0x18U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_26APBCLK                  (0x19U << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_27APBCLK                  (0x1aU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_28APBCLK                  (0x1bU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_29APBCLK                  (0x1cU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_30APBCLK                  (0x1dU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_31APBCLK                  (0x1eU << COMP_CR_DFLEN_Pos)
#define    FL_COMP_OUTPUT_FILTER_WINDOW_32APBCLK                  (0x1fU << COMP_CR_DFLEN_Pos)


#define    FL_COMP_OUTPUT_POLARITY_NORMAL                         (0x0U << COMP_CR_POLAR_Pos)
#define    FL_COMP_OUTPUT_POLARITY_INVERT                         (0x1U << COMP_CR_POLAR_Pos)


#define    FL_COMP_POWER_MODE_LOW                                 (0x0U << COMP_CR_MODE_Pos)
#define    FL_COMP_POWER_MODE_MEDIUM                              (0x1U << COMP_CR_MODE_Pos)
#define    FL_COMP_POWER_MODE_HIGH                                (0x2U << COMP_CR_MODE_Pos)


#define    FL_COMP_OUTPUT_LOW                                     (0x0U << COMP_CR_CMPO_Pos)
#define    FL_COMP_OUTPUT_HIGH                                    (0x1U << COMP_CR_CMPO_Pos)

#define    FL_COMP_INP_SOURCE_INP1                                (0x0U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_INP2                                (0x1U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_AVREF                               (0x2U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_ULPBG_REF                           (0x3U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_VDD15                               (0x4U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_VREFP                               (0x5U << COMP_CR_VPSEL_Pos)


#define    FL_COMP_INN_SOURCE_INN1                                (0x0U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_INN2                                (0x1U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_VREF                                (0x2U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_VREF_DIV_2                          (0x3U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_VREFP                               (0x4U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_DAC                                 (0x5U << COMP_CR_VNSEL_Pos)


#define    FL_COMP_COMP3_INTERRUPT_EDGE_BOTH                      (0x0U << COMP_ICR_CMP3SEL_Pos)
#define    FL_COMP_COMP3_INTERRUPT_EDGE_RISING                    (0x1U << COMP_ICR_CMP3SEL_Pos)
#define    FL_COMP_COMP3_INTERRUPT_EDGE_FALLING                   (0x2U << COMP_ICR_CMP3SEL_Pos)


#define    FL_COMP_COMP2_INTERRUPT_EDGE_BOTH                      (0x0U << COMP_ICR_CMP2SEL_Pos)
#define    FL_COMP_COMP2_INTERRUPT_EDGE_RISING                    (0x1U << COMP_ICR_CMP2SEL_Pos)
#define    FL_COMP_COMP2_INTERRUPT_EDGE_FALLING                   (0x2U << COMP_ICR_CMP2SEL_Pos)


#define    FL_COMP_COMP1_INTERRUPT_EDGE_BOTH                      (0x0U << COMP_ICR_CMP1SEL_Pos)
#define    FL_COMP_COMP1_INTERRUPT_EDGE_RISING                    (0x1U << COMP_ICR_CMP1SEL_Pos)
#define    FL_COMP_COMP1_INTERRUPT_EDGE_FALLING                   (0x2U << COMP_ICR_CMP1SEL_Pos)

#define    FL_COMP_INTERRUPT_EDGE_BOTH                            (0x0U)
#define    FL_COMP_INTERRUPT_EDGE_RISING                          (0x1U)
#define    FL_COMP_INTERRUPT_EDGE_FALLING                         (0x2U)

#define    FL_COMP_BUFF_REFERENCE_AVREF                           (0x0U << COMP_BUFCR_BUFSEL_Pos)
#define    FL_COMP_BUFF_REFERENCE_VREF1P2                         (0x1U << COMP_BUFCR_BUFSEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup COMP_FL_Exported_Functions COMP Exported Functions
  * @{
  */

/**
  * @brief    COMPx trigger output enable
  * @rmtoll   CR    TRGOEN    FL_COMP_EnableTriggerOutput
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableTriggerOutput(COMP_Type *COMPx)
{
    SET_BIT(COMPx->CR, COMP_CR_TRGOEN_Msk);
}

/**
  * @brief    Get COMPx trigger output enable status
  * @rmtoll   CR    TRGOEN    FL_COMP_IsEnabledTriggerOutput
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledTriggerOutput(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_TRGOEN_Msk) == COMP_CR_TRGOEN_Msk);
}

/**
  * @brief    COMPx trigger output disable
  * @rmtoll   CR    TRGOEN    FL_COMP_DisableTriggerOutput
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableTriggerOutput(COMP_Type *COMPx)
{
    CLEAR_BIT(COMPx->CR, COMP_CR_TRGOEN_Msk);
}

/**
  * @brief    Set COMPx Output Digital Filter Length
  * @rmtoll   CR    DFLEN    FL_COMP_SetOutputFilterWindow
  * @param    COMPx COMP instance
  * @param    length This parameter can be one of the following values:
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_4APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_5APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_6APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_7APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_8APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_9APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_10APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_11APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_12APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_13APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_14APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_15APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_16APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_17APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_18APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_19APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_20APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_21APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_22APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_23APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_24APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_25APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_26APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_27APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_28APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_29APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_30APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_31APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_32APBCLK
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetOutputFilterWindow(COMP_Type *COMPx, uint32_t length)
{
    MODIFY_REG(COMPx->CR, COMP_CR_DFLEN_Msk, length);
}

/**
  * @brief    Get COMPx Output Digital Filter Length
  * @rmtoll   CR    DFLEN    FL_COMP_GetOutputFilterWindow
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_4APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_5APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_6APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_7APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_8APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_9APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_10APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_11APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_12APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_13APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_14APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_15APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_16APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_17APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_18APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_19APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_20APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_21APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_22APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_23APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_24APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_25APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_26APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_27APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_28APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_29APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_30APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_31APBCLK
  *           @arg @ref FL_COMP_OUTPUT_FILTER_WINDOW_32APBCLK
  */
__STATIC_INLINE uint32_t FL_COMP_GetOutputFilterWindow(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_DFLEN_Msk));
}

/**
  * @brief    COMPx Window Mode enable
  * @rmtoll   CR    WINMODE    FL_COMP_EnableWindowMode
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableWindowMode(COMP_Type *COMPx)
{
    SET_BIT(COMPx->CR, COMP_CR_WINMODE_Msk);
}

/**
  * @brief    Get COMPx Window Mode enable status
  * @rmtoll   CR    WINMODE    FL_COMP_IsEnabledWindowMode
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledWindowMode(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_WINMODE_Msk) == COMP_CR_WINMODE_Msk);
}

/**
  * @brief    COMPx Window Mode disable
  * @rmtoll   CR    WINMODE    FL_COMP_DisableWindowMode
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableWindowMode(COMP_Type *COMPx)
{
    CLEAR_BIT(COMPx->CR, COMP_CR_WINMODE_Msk);
}

/**
  * @brief    Set COMPx output polarity
  * @rmtoll   CR    POLAR    FL_COMP_SetOutputPolarity
  * @param    COMPx COMP instance
  * @param    polarity This parameter can be one of the following values:
  *           @arg @ref FL_COMP_OUTPUT_POLARITY_NORMAL
  *           @arg @ref FL_COMP_OUTPUT_POLARITY_INVERT
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetOutputPolarity(COMP_Type *COMPx, uint32_t polarity)
{
    MODIFY_REG(COMPx->CR, COMP_CR_POLAR_Msk, polarity);
}

/**
  * @brief    Get COMPx output polarity
  * @rmtoll   CR    POLAR    FL_COMP_GetOutputPolarity
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_OUTPUT_POLARITY_NORMAL
  *           @arg @ref FL_COMP_OUTPUT_POLARITY_INVERT
  */
__STATIC_INLINE uint32_t FL_COMP_GetOutputPolarity(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_POLAR_Msk));
}

/**
  * @brief    COMPx DigitalFilter enable
  * @rmtoll   CR    DFEN    FL_COMP_EnableOutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableOutputFilter(COMP_Type *COMPx)
{
    SET_BIT(COMPx->CR, COMP_CR_DFEN_Msk);
}

/**
  * @brief    Get COMPx  DigitalFilter enable status
  * @rmtoll   CR    DFEN    FL_COMP_IsEnabledOutputFilter
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledOutputFilter(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_DFEN_Msk) == COMP_CR_DFEN_Msk);
}

/**
  * @brief    COMPx  DigitalFilter disable
  * @rmtoll   CR    DFEN    FL_COMP_DisableOutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableOutputFilter(COMP_Type *COMPx)
{
    CLEAR_BIT(COMPx->CR, COMP_CR_DFEN_Msk);
}

/**
  * @brief    Set COMPx Power mode
  * @rmtoll   CR    MODE    FL_COMP_SetPowerMode
  * @param    COMPx COMP instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_COMP_POWER_MODE_LOW
  *           @arg @ref FL_COMP_POWER_MODE_MEDIUM
  *           @arg @ref FL_COMP_POWER_MODE_HIGH
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetPowerMode(COMP_Type *COMPx, uint32_t mode)
{
    MODIFY_REG(COMPx->CR, COMP_CR_MODE_Msk, mode);
}

/**
  * @brief    Get COMPx Power mode
  * @rmtoll   CR    MODE    FL_COMP_GetPowerMode
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_POWER_MODE_LOW
  *           @arg @ref FL_COMP_POWER_MODE_MEDIUM
  *           @arg @ref FL_COMP_POWER_MODE_HIGH
  */
__STATIC_INLINE uint32_t FL_COMP_GetPowerMode(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_MODE_Msk));
}

/**
  * @brief    Get comparator output channel
  * @rmtoll   CR    CMPO    FL_COMP_GetOutput
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_OUTPUT_LOW
  *           @arg @ref FL_COMP_OUTPUT_HIGH
  */
__STATIC_INLINE uint32_t FL_COMP_GetOutput(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_CMPO_Msk));
}

/**
  * @brief    Set COMPx positive input
  * @rmtoll   CR    VPSEL    FL_COMP_SetINPSource
  * @param    COMPx COMP instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_COMP_INP_SOURCE_INP1
  *           @arg @ref FL_COMP_INP_SOURCE_INP2
  *           @arg @ref FL_COMP_INP_SOURCE_AVREF
  *           @arg @ref FL_COMP_INP_SOURCE_ULPBG_AREF
  *           @arg @ref FL_COMP_INP_SOURCE_VDD15
  *           @arg @ref FL_COMP_INP_SOURCE_VREFP
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetINPSource(COMP_Type *COMPx, uint32_t source)
{
    MODIFY_REG(COMPx->CR, COMP_CR_VPSEL_Msk, source);
}

/**
  * @brief    Get COMPx positive input status
  * @rmtoll   CR    VPSEL    FL_COMP_GetINPSource
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_INP_SOURCE_INP1
  *           @arg @ref FL_COMP_INP_SOURCE_INP2
  *           @arg @ref FL_COMP_INP_SOURCE_AVREF
  *           @arg @ref FL_COMP_INP_SOURCE_ULPBG_AREF
  *           @arg @ref FL_COMP_INP_SOURCE_VDD15
  *           @arg @ref FL_COMP_INP_SOURCE_VREFP
  */
__STATIC_INLINE uint32_t FL_COMP_GetINPSource(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_VPSEL_Msk));
}

/**
  * @brief    Set COMPx negative input
  * @rmtoll   CR    VNSEL    FL_COMP_SetINNSource
  * @param    COMPx COMP instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_COMP_INN_SOURCE_INN1
  *           @arg @ref FL_COMP_INN_SOURCE_INN2
  *           @arg @ref FL_COMP_INN_SOURCE_VREF
  *           @arg @ref FL_COMP_INN_SOURCE_VREF_DIV_2
  *           @arg @ref FL_COMP_INN_SOURCE_VREFP
  *           @arg @ref FL_COMP_INN_SOURCE_DAC
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetINNSource(COMP_Type *COMPx, uint32_t source)
{
    MODIFY_REG(COMPx->CR, COMP_CR_VNSEL_Msk, source);
}

/**
  * @brief    Get COMPx negative input status
  * @rmtoll   CR    VNSEL    FL_COMP_GetINNSource
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_INN_SOURCE_INN1
  *           @arg @ref FL_COMP_INN_SOURCE_INN2
  *           @arg @ref FL_COMP_INN_SOURCE_VREF
  *           @arg @ref FL_COMP_INN_SOURCE_VREF_DIV_2
  *           @arg @ref FL_COMP_INN_SOURCE_VREFP
  *           @arg @ref FL_COMP_INN_SOURCE_DAC
  */
__STATIC_INLINE uint32_t FL_COMP_GetINNSource(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_VNSEL_Msk));
}

/**
  * @brief    COMPx enable
  * @rmtoll   CR    CMPEN    FL_COMP_Enable
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_Enable(COMP_Type *COMPx)
{
    SET_BIT(COMPx->CR, COMP_CR_CMPEN_Msk);
}

/**
  * @brief    Get COMPx enable status
  * @rmtoll   CR    CMPEN    FL_COMP_IsEnabled
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabled(COMP_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->CR, COMP_CR_CMPEN_Msk) == COMP_CR_CMPEN_Msk);
}

/**
  * @brief    COMPx disable
  * @rmtoll   CR    CMPEN    FL_COMP_Disable
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_Disable(COMP_Type *COMPx)
{
    CLEAR_BIT(COMPx->CR, COMP_CR_CMPEN_Msk);
}

/**
  * @brief    Comparator Out Of Window interrupt enable
  * @rmtoll   ICR    OWW_IE    FL_COMP_EnableIT_OutOfWindow
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableIT_OutOfWindow(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_OWW_IE_Msk);
}

/**
  * @brief    Get Comparator Out Of Window interrupt enable status
  * @rmtoll   ICR    OWW_IE    FL_COMP_IsEnabledIT_OutOfWindow
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledIT_OutOfWindow(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_OWW_IE_Msk) == COMP_ICR_OWW_IE_Msk);
}

/**
  * @brief    Comparator Out Of Window interrupt disable
  * @rmtoll   ICR    OWW_IE    FL_COMP_DisableIT_OutOfWindow
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableIT_OutOfWindow(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_OWW_IE_Msk);
}

/**
  * @brief    Comparator Across Window interrupt enable
  * @rmtoll   ICR    WIN_IE    FL_COMP_EnableIT_AcrossWindowThreshold
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableIT_AcrossWindowThreshold(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_WIN_IE_Msk);
}

/**
  * @brief    Get comparator  Across Window interrupt enable status
  * @rmtoll   ICR    WIN_IE    FL_COMP_IsEnabledIT_AcrossWindowThreshold
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledIT_AcrossWindowThreshold(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_WIN_IE_Msk) == COMP_ICR_WIN_IE_Msk);
}

/**
  * @brief    Comparator  Across Window interrupt disable
  * @rmtoll   ICR    WIN_IE    FL_COMP_DisableIT_AcrossWindowThreshold
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableIT_AcrossWindowThreshold(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_WIN_IE_Msk);
}

/**
  * @brief    Set comparator3 interrupt edge
  * @rmtoll   ICR    CMP3SEL    FL_COMP_SetComparator3InterruptEdge
  * @param    COMPx COMP instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetComparator3InterruptEdge(COMP_COMMON_Type *COMPx, uint32_t edge)
{
    MODIFY_REG(COMPx->ICR, COMP_ICR_CMP3SEL_Msk, edge);
}

/**
  * @brief    Get comparator3 interrupt edge
  * @rmtoll   ICR    CMP3SEL    FL_COMP_GetComparator3InterruptEdge
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP3_INTERRUPT_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_COMP_GetComparator3InterruptEdge(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP3SEL_Msk));
}

/**
  * @brief    Comparator3 interrupt enable
  * @rmtoll   ICR    CMP3IE    FL_COMP_EnableIT_Comparator3
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableIT_Comparator3(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_CMP3IE_Msk);
}

/**
  * @brief    Get comparator3 interrupt enable status
  * @rmtoll   ICR    CMP3IE    FL_COMP_IsEnabledIT_Comparator3
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledIT_Comparator3(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP3IE_Msk) == COMP_ICR_CMP3IE_Msk);
}

/**
  * @brief    Comparator3 interrupt disable
  * @rmtoll   ICR    CMP3IE    FL_COMP_DisableIT_Comparator3
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableIT_Comparator3(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_CMP3IE_Msk);
}

/**
  * @brief    Set comparator2 interrupt edge
  * @rmtoll   ICR    CMP2SEL    FL_COMP_SetComparator2InterruptEdge
  * @param    COMPx COMP instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetComparator2InterruptEdge(COMP_COMMON_Type *COMPx, uint32_t edge)
{
    MODIFY_REG(COMPx->ICR, COMP_ICR_CMP2SEL_Msk, edge);
}

/**
  * @brief    Get comparator2 interrupt edge
  * @rmtoll   ICR    CMP2SEL    FL_COMP_GetComparator2InterruptEdge
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP2_INTERRUPT_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_COMP_GetComparator2InterruptEdge(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP2SEL_Msk));
}

/**
  * @brief    Comparator2 interrupt enable
  * @rmtoll   ICR    CMP2IE    FL_COMP_EnableIT_Comparator2
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableIT_Comparator2(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_CMP2IE_Msk);
}

/**
  * @brief    Get comparator2 interrupt enable status
  * @rmtoll   ICR    CMP2IE    FL_COMP_IsEnabledIT_Comparator2
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledIT_Comparator2(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP2IE_Msk) == COMP_ICR_CMP2IE_Msk);
}

/**
  * @brief    Comparator2 interrupt disable
  * @rmtoll   ICR    CMP2IE    FL_COMP_DisableIT_Comparator2
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableIT_Comparator2(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_CMP2IE_Msk);
}

/**
  * @brief    Set comparator1 interrupt edge
  * @rmtoll   ICR    CMP1SEL    FL_COMP_SetComparator1InterruptEdge
  * @param    COMPx COMP instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetComparator1InterruptEdge(COMP_COMMON_Type *COMPx, uint32_t edge)
{
    MODIFY_REG(COMPx->ICR, COMP_ICR_CMP1SEL_Msk, edge);
}

/**
  * @brief    Get comparator1 interrupt edge
  * @rmtoll   ICR    CMP1SEL    FL_COMP_GetComparator1InterruptEdge
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_BOTH
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_RISING
  *           @arg @ref FL_COMP_COMP1_INTERRUPT_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_COMP_GetComparator1InterruptEdge(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP1SEL_Msk));
}

/**
  * @brief    Comparator1 interrupt enable
  * @rmtoll   ICR    CMP1IE    FL_COMP_EnableIT_Comparator1
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableIT_Comparator1(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_CMP1IE_Msk);
}

/**
  * @brief    Get comparator1 interrupt enable status
  * @rmtoll   ICR    CMP1IE    FL_COMP_IsEnabledIT_Comparator1
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledIT_Comparator1(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_CMP1IE_Msk) == COMP_ICR_CMP1IE_Msk);
}

/**
  * @brief    Comparator1 interrupt disable
  * @rmtoll   ICR    CMP1IE    FL_COMP_DisableIT_Comparator1
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableIT_Comparator1(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_CMP1IE_Msk);
}

/**
  * @brief    Get outof window interrupt flag
  * @rmtoll   ISR    OOW_IF    FL_COMP_IsActiveFlag_OutOfWindow
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsActiveFlag_OutOfWindow(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ISR, COMP_ISR_OOW_IF_Msk) == (COMP_ISR_OOW_IF_Msk));
}

/**
  * @brief    Clear outof window interrupt flag
  * @rmtoll   ISR    OOW_IF    FL_COMP_ClearFlag_OutOfWindow
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_ClearFlag_OutOfWindow(COMP_COMMON_Type *COMPx)
{
    WRITE_REG(COMPx->ISR, COMP_ISR_OOW_IF_Msk);
}

/**
  * @brief    Get across window interrupt flag
  * @rmtoll   ISR    WIN_IF    FL_COMP_IsActiveFlag_AcrossWindowThreshold
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsActiveFlag_AcrossWindowThreshold(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ISR, COMP_ISR_WIN_IF_Msk) == (COMP_ISR_WIN_IF_Msk));
}

/**
  * @brief    Clear across window interrupt flag
  * @rmtoll   ISR    WIN_IF    FL_COMP_ClearFlag_AcrossWindowThreshold
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_ClearFlag_AcrossWindowThreshold(COMP_COMMON_Type *COMPx)
{
    WRITE_REG(COMPx->ISR, COMP_ISR_WIN_IF_Msk);
}

/**
  * @brief    Get comparator3 interrupt flag
  * @rmtoll   ISR    CMP3IF    FL_COMP_IsActiveFlag_Comparator3
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsActiveFlag_Comparator3(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ISR, COMP_ISR_CMP3IF_Msk) == (COMP_ISR_CMP3IF_Msk));
}

/**
  * @brief    Clear comparator3 interrupt flag
  * @rmtoll   ISR    CMP3IF    FL_COMP_ClearFlag_Comparator3
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_ClearFlag_Comparator3(COMP_COMMON_Type *COMPx)
{
    WRITE_REG(COMPx->ISR, COMP_ISR_CMP3IF_Msk);
}

/**
  * @brief    Get comparator2 interrupt flag
  * @rmtoll   ISR    CMP2IF    FL_COMP_IsActiveFlag_Comparator2
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsActiveFlag_Comparator2(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ISR, COMP_ISR_CMP2IF_Msk) == (COMP_ISR_CMP2IF_Msk));
}

/**
  * @brief    Clear comparator2 interrupt flag
  * @rmtoll   ISR    CMP2IF    FL_COMP_ClearFlag_Comparator2
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_ClearFlag_Comparator2(COMP_COMMON_Type *COMPx)
{
    WRITE_REG(COMPx->ISR, COMP_ISR_CMP2IF_Msk);
}

/**
  * @brief    Get comparator1 interrupt flag
  * @rmtoll   ISR    CMP1IF    FL_COMP_IsActiveFlag_Comparator1
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsActiveFlag_Comparator1(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ISR, COMP_ISR_CMP1IF_Msk) == (COMP_ISR_CMP1IF_Msk));
}

/**
  * @brief    Clear comparator1 interrupt flag
  * @rmtoll   ISR    CMP1IF    FL_COMP_ClearFlag_Comparator1
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_ClearFlag_Comparator1(COMP_COMMON_Type *COMPx)
{
    WRITE_REG(COMPx->ISR, COMP_ISR_CMP1IF_Msk);
}

/**
  * @brief    COMPx bypass buffer enable
  * @rmtoll   BUFCR    BUFBYP    FL_COMP_EnableBufferBypass
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableBufferBypass(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->BUFCR, COMP_BUFCR_BUFBYP_Msk);
}

/**
  * @brief    Get COMPx bypass buffer enable status
  * @rmtoll   BUFCR    BUFBYP    FL_COMP_IsEnabledBufferBypass
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledBufferBypass(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->BUFCR, COMP_BUFCR_BUFBYP_Msk) == COMP_BUFCR_BUFBYP_Msk);
}

/**
  * @brief    COMPx bypass buffer disable
  * @rmtoll   BUFCR    BUFBYP    FL_COMP_DisableBufferBypass
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableBufferBypass(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->BUFCR, COMP_BUFCR_BUFBYP_Msk);
}

/**
  * @brief    Set COMPx buffer select
  * @rmtoll   BUFCR    BUFSEL    FL_COMP_SetBufferReference
  * @param    COMPx COMP instance
  * @param    select This parameter can be one of the following values:
  *           @arg @ref FL_COMP_BUFF_REFERENCE_VREF1P2
  *           @arg @ref FL_COMP_BUFF_REFERENCE_AVREF
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_SetBufferReference(COMP_COMMON_Type *COMPx, uint32_t select)
{
    MODIFY_REG(COMPx->BUFCR, COMP_BUFCR_BUFSEL_Msk, select);
}

/**
  * @brief    Get COMPx buffer select
  * @rmtoll   BUFCR    BUFSEL    FL_COMP_GetBufferReference
  * @param    COMPx COMP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_COMP_BUFF_REFERENCE_VREF1P2
  *           @arg @ref FL_COMP_BUFF_REFERENCE_AVREF
  */
__STATIC_INLINE uint32_t FL_COMP_GetBufferReference(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->BUFCR, COMP_BUFCR_BUFSEL_Msk));
}

/**
  * @brief    COMPx close buffer enable
  * @rmtoll   BUFCR    BUFENB    FL_COMP_EnableBuffer
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableBuffer(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->BUFCR, COMP_BUFCR_BUFENB_Msk);
}

/**
  * @brief    Get COMPx close buffer enable status
  * @rmtoll   BUFCR    BUFENB    FL_COMP_IsEnabledBuffer
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledBuffer(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->BUFCR, COMP_BUFCR_BUFENB_Msk) == COMP_BUFCR_BUFENB_Msk);
}

/**
  * @brief    COMPx close buffer disable
  * @rmtoll   BUFCR    BUFENB    FL_COMP_DisableBuffer
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableBuffer(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->BUFCR, COMP_BUFCR_BUFENB_Msk);
}

/**
  * @}
  */

/** @defgroup COMP_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_COMP_DeInit(COMP_Type *COMPx);
void FL_COMP_StructInit(FL_COMP_InitTypeDef *initStruct);
FL_ErrorStatus FL_COMP_Init(COMP_Type *COMPx, FL_COMP_InitTypeDef *initStruct);

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

#endif /* __FM33LG0XX_FL_COMP_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
