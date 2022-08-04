/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_comp.h
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
#ifndef __FM33LC0XX_FL_COMP_H
#define __FM33LC0XX_FL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
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
    uint32_t digitalFilterLen;  /* 此芯片不可设 */

} FL_COMP_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup COMP_FL_Exported_Constants COMP Exported Constants
  * @{
  */

#define    COMP_CR_CMPO_Pos                                       (8U)
#define    COMP_CR_CMPO_Msk                                       (0x1U << COMP_CR_CMPO_Pos)
#define    COMP_CR_CMPO                                           COMP_CR_CMPO_Msk

#define    COMP_CR_POLAR_Pos                                      (5U)
#define    COMP_CR_POLAR_Msk                                      (0x1U << COMP_CR_POLAR_Pos)
#define    COMP_CR_POLAR                                          COMP_CR_POLAR_Msk

#define    COMP_CR_VPSEL_Pos                                      (3U)
#define    COMP_CR_VPSEL_Msk                                      (0x3U << COMP_CR_VPSEL_Pos)
#define    COMP_CR_VPSEL                                          COMP_CR_VPSEL_Msk

#define    COMP_CR_VNSEL_Pos                                      (1U)
#define    COMP_CR_VNSEL_Msk                                      (0x3U << COMP_CR_VNSEL_Pos)
#define    COMP_CR_VNSEL                                          COMP_CR_VNSEL_Msk

#define    COMP_CR_CMPEN_Pos                                      (0U)
#define    COMP_CR_CMPEN_Msk                                      (0x1U << COMP_CR_CMPEN_Pos)
#define    COMP_CR_CMPEN                                          COMP_CR_CMPEN_Msk

#define    COMP_ICR_COMP2DF_Pos                                   (9U)
#define    COMP_ICR_COMP2DF_Msk                                   (0x1U << COMP_ICR_COMP2DF_Pos)
#define    COMP_ICR_COMP2DF                                       COMP_ICR_COMP2DF_Msk

#define    COMP_ICR_COMP1DF_Pos                                   (8U)
#define    COMP_ICR_COMP1DF_Msk                                   (0x1U << COMP_ICR_COMP1DF_Pos)
#define    COMP_ICR_COMP1DF                                       COMP_ICR_COMP1DF_Msk

#define    COMP_ICR_CMP2SEL_Pos                                   (4U)
#define    COMP_ICR_CMP2SEL_Msk                                   (0x3U << COMP_ICR_CMP2SEL_Pos)
#define    COMP_ICR_CMP2SEL                                       COMP_ICR_CMP2SEL_Msk

#define    COMP_ICR_CMP1SEL_Pos                                   (2U)
#define    COMP_ICR_CMP1SEL_Msk                                   (0x3U << COMP_ICR_CMP1SEL_Pos)
#define    COMP_ICR_CMP1SEL                                       COMP_ICR_CMP1SEL_Msk

#define    COMP_ICR_CMP2IE_Pos                                    (1U)
#define    COMP_ICR_CMP2IE_Msk                                    (0x1U << COMP_ICR_CMP2IE_Pos)
#define    COMP_ICR_CMP2IE                                        COMP_ICR_CMP2IE_Msk

#define    COMP_ICR_CMP1IE_Pos                                    (0U)
#define    COMP_ICR_CMP1IE_Msk                                    (0x1U << COMP_ICR_CMP1IE_Pos)
#define    COMP_ICR_CMP1IE                                        COMP_ICR_CMP1IE_Msk

#define    COMP_ISR_CMP2IF_Pos                                    (1U)
#define    COMP_ISR_CMP2IF_Msk                                    (0x1U << COMP_ISR_CMP2IF_Pos)
#define    COMP_ISR_CMP2IF                                        COMP_ISR_CMP2IF_Msk

#define    COMP_ISR_CMP1IF_Pos                                    (0U)
#define    COMP_ISR_CMP1IF_Msk                                    (0x1U << COMP_ISR_CMP1IF_Pos)
#define    COMP_ISR_CMP1IF                                        COMP_ISR_CMP1IF_Msk



#define    FL_COMP_INTERRUPT_EDGE_BOTH                            0x0U
#define    FL_COMP_INTERRUPT_EDGE_RISING                          0x1U
#define    FL_COMP_INTERRUPT_EDGE_FALLING                         0x2U



#define    FL_COMP_OUTPUT_LOW                                     (0x0U << COMP_CR_CMPO_Pos)
#define    FL_COMP_OUTPUT_HIGH                                    (0x1U << COMP_CR_CMPO_Pos)

#define    FL_COMP_OUTPUT_POLARITY_NORMAL                         (0x0U << COMP_CR_POLAR_Pos)
#define    FL_COMP_OUTPUT_POLARITY_INVERT                         (0x1U << COMP_CR_POLAR_Pos)


#define    FL_COMP_INP_SOURCE_INP1                                (0x0U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_INP2                                (0x1U << COMP_CR_VPSEL_Pos)
#define    FL_COMP_INP_SOURCE_INP3                                (0x2U << COMP_CR_VPSEL_Pos)


#define    FL_COMP_INN_SOURCE_INN1                                (0x0U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_INN2                                (0x1U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_VREF                                (0x2U << COMP_CR_VNSEL_Pos)
#define    FL_COMP_INN_SOURCE_VREF_DIV_2                          (0x3U << COMP_CR_VNSEL_Pos)


#define    FL_COMP_COMP2_INTERRUPT_EDGE_BOTH                      (0x0U << COMP_ICR_CMP2SEL_Pos)
#define    FL_COMP_COMP2_INTERRUPT_EDGE_RISING                    (0x1U << COMP_ICR_CMP2SEL_Pos)
#define    FL_COMP_COMP2_INTERRUPT_EDGE_FALLING                   (0x2U << COMP_ICR_CMP2SEL_Pos)


#define    FL_COMP_COMP1_INTERRUPT_EDGE_BOTH                      (0x0U << COMP_ICR_CMP1SEL_Pos)
#define    FL_COMP_COMP1_INTERRUPT_EDGE_RISING                    (0x1U << COMP_ICR_CMP1SEL_Pos)
#define    FL_COMP_COMP1_INTERRUPT_EDGE_FALLING                   (0x2U << COMP_ICR_CMP1SEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup COMP_FL_Exported_Functions COMP Exported Functions
  * @{
  */

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
  * @brief    Set COMPx positive input
  * @rmtoll   CR    VPSEL    FL_COMP_SetINPSource
  * @param    COMPx COMP instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_COMP_INP_SOURCE_INP1
  *           @arg @ref FL_COMP_INP_SOURCE_INP2
  *           @arg @ref FL_COMP_INP_SOURCE_INP3
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
  *           @arg @ref FL_COMP_INP_SOURCE_INP3
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
  * @brief    Comparator2  DigitalFilter enable
  * @rmtoll   ICR    COMP2DF    FL_COMP_EnableComparator2OutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableComparator2OutputFilter(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_COMP2DF_Msk);
}

/**
  * @brief    Get comparator2 DigitalFilter enable status
  * @rmtoll   ICR    COMP2DF    FL_COMP_IsEnabledComparator2OutputFilter
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledComparator2OutputFilter(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_COMP2DF_Msk) == COMP_ICR_COMP2DF_Msk);
}

/**
  * @brief    Comparator2 DigitalFilter disable
  * @rmtoll   ICR    COMP2DF    FL_COMP_DisableComparator2OutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableComparator2OutputFilter(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_COMP2DF_Msk);
}

/**
  * @brief    Comparator1 DigitalFilter enable
  * @rmtoll   ICR    COMP1DF    FL_COMP_EnableComparator1OutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_EnableComparator1OutputFilter(COMP_COMMON_Type *COMPx)
{
    SET_BIT(COMPx->ICR, COMP_ICR_COMP1DF_Msk);
}

/**
  * @brief    Get comparator1   DigitalFilter enable status
  * @rmtoll   ICR    COMP1DF    FL_COMP_IsEnabledComparator1OutputFilter
  * @param    COMPx COMP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_COMP_IsEnabledComparator1OutputFilter(COMP_COMMON_Type *COMPx)
{
    return (uint32_t)(READ_BIT(COMPx->ICR, COMP_ICR_COMP1DF_Msk) == COMP_ICR_COMP1DF_Msk);
}

/**
  * @brief    Comparator1   DigitalFilter disable
  * @rmtoll   ICR    COMP1DF    FL_COMP_DisableComparator1OutputFilter
  * @param    COMPx COMP instance
  * @retval   None
  */
__STATIC_INLINE void FL_COMP_DisableComparator1OutputFilter(COMP_COMMON_Type *COMPx)
{
    CLEAR_BIT(COMPx->ICR, COMP_ICR_COMP1DF_Msk);
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

#endif /* __FM33LC0XX_FL_COMP_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-22*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
