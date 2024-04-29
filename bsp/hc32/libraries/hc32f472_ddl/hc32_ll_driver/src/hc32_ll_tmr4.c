/**
 *******************************************************************************
 * @file  hc32_ll_tmr4.c
 * @brief This file provides firmware functions to manage the TMR4(Timer4).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Add function comments: macros group @ref TMR4_OC_Channel
                                    Modify function return value comments: TMR4_OC_GetPolarity
                                    Modify function parameter comments: TMR4_PWM_SetPolarity
                                    Modify typo
                                    Modify function: TMR4_DeInit, TMR4_OC_DeInit, TMR4_PWM_DeInit, TMR4_EVT_DeInit
                                    Modify macro-definition: IS_TMR4_OC_BUF_OBJECT
                                    Fix magic number of function:  TMR4_OC_StructInit
   2023-09-30       CDT             Rename macro-define: TMR4_INT_EVT_CMP_xx  -> TMR4_INT_SCMP_EVTx
                                    Rename macro-define: TMR4_FLAG_EVT_CMP_xx -> TMR4_FLAG_SCMP_EVTx
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
#include "hc32_ll_tmr4.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TMR4 TMR4
 * @brief TMR4 Driver Library
 * @{
 */

#if (LL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR4_Local_Macros TMR4 Local Macros
 * @{
 */

/**
 * @defgroup TMR4_Check_Parameters_Validity TMR4 Check Parameters Validity
 * @{
 */
#define IS_TMR4_UNIT(x)                     ((x) == CM_TMR4)

#define IS_TMR4_CLK_DIV(x)                                                     \
(   ((x) == TMR4_CLK_DIV1)                  ||                                 \
    ((x) == TMR4_CLK_DIV2)                  ||                                 \
    ((x) == TMR4_CLK_DIV4)                  ||                                 \
    ((x) == TMR4_CLK_DIV8)                  ||                                 \
    ((x) == TMR4_CLK_DIV16)                 ||                                 \
    ((x) == TMR4_CLK_DIV32)                 ||                                 \
    ((x) == TMR4_CLK_DIV64)                 ||                                 \
    ((x) == TMR4_CLK_DIV128)                ||                                 \
    ((x) == TMR4_CLK_DIV256)                ||                                 \
    ((x) == TMR4_CLK_DIV512)                ||                                 \
    ((x) == TMR4_CLK_DIV1024))

#define IS_TMR4_MD(x)                                                          \
(   ((x) == TMR4_MD_SAWTOOTH)               ||                                 \
    ((x) == TMR4_MD_TRIANGLE))

#define IS_TMR4_CLK_SRC(x)                                                     \
(   ((x) == TMR4_CLK_SRC_INTERNCLK)         ||                                 \
    ((x) == TMR4_CLK_SRC_EXTCLK))

#define IS_TMR4_INT_CNT_MASKTIME(x)         ((x) <= TMR4_INT_CNT_MASK15)

#define IS_TMR4_INT_CNT(x)                                                     \
(   ((x) != 0UL)                            &&                                 \
    (((x) | TMR4_INT_CNT_MASK) == TMR4_INT_CNT_MASK))

#define IS_TMR4_INT(x)                                                         \
(   ((x) != 0UL)                            &&                                 \
    (((x) | TMR4_INT_ALL) == TMR4_INT_ALL))

#define IS_TMR4_FLAG(x)                                                        \
(   ((x) != 0UL)                            &&                                 \
    (((x) | TMR4_FLAG_ALL) == TMR4_FLAG_ALL))

#define IS_TMR4_OC_HIGH_CH(x)               (((x) & 0x1UL) == 0UL)
#define IS_TMR4_OC_LOW_CH(x)                (((x) & 0x1UL) == 1UL)

#define IS_TMR4_OC_BUF_OBJECT(x)                                               \
(   (((x) | TMR4_OC_BUF_OBJECT_MASK) == TMR4_OC_BUF_OBJECT_MASK))

#define IS_TMR4_OC_BUF_COND(x)                                                 \
(   ((x) == TMR4_OC_BUF_COND_IMMED)         ||                                 \
    ((x) == TMR4_OC_BUF_COND_PEAK)          ||                                 \
    ((x) == TMR4_OC_BUF_COND_VALLEY)        ||                                 \
    ((x) == TMR4_OC_BUF_COND_PEAK_VALLEY))

#define IS_TMR4_OC_INVD_POLARITY(x)                                            \
(   ((x) == TMR4_OC_INVD_LOW)               ||                                 \
    ((x) == TMR4_OC_INVD_HIGH))

#define IS_TMR4_PWM_MD(x)                                                      \
(   ((x) == TMR4_PWM_MD_THROUGH)            ||                                 \
    ((x) == TMR4_PWM_MD_DEAD_TMR)           ||                                 \
    ((x) == TMR4_PWM_MD_DEAD_TMR_FILTER))

#define IS_TMR4_PWM_POLARITY(x)                                                \
(   ((x) == TMR4_PWM_OXH_HOLD_OXL_HOLD)     ||                                 \
    ((x) == TMR4_PWM_OXH_INVT_OXL_HOLD)     ||                                 \
    ((x) == TMR4_PWM_OXH_HOLD_OXL_INVT)     ||                                 \
    ((x) == TMR4_PWM_OXH_INVT_OXL_INVT))

#define IS_TMR4_PWM_CLK_DIV(x)              (((x) | TMR4_PWM_CLK_DIV128) == TMR4_PWM_CLK_DIV128)

#define IS_TMR4_PWM_DEADTIME_REG_IDX(x)                                        \
(   ((x) == TMR4_PWM_PDAR_IDX)              ||                                 \
    ((x) == TMR4_PWM_PDBR_IDX))

#define IS_TMR4_PWM_OE_EFFECT(x)                                               \
(   ((x) == TMR4_PWM_OE_EFFECT_IMMED)       ||                                 \
    ((x) == TMR4_PWM_OE_EFFECT_COUNT_PEAK)  ||                                 \
    ((x) == TMR4_PWM_OE_EFFECT_COUNT_VALLEY))

#define IS_TMR4_PWM_PIN_MD(x)                                                  \
(   ((x) == TMR4_PWM_PIN_OUTPUT_OS)         ||                                 \
    ((x) == TMR4_PWM_PIN_OUTPUT_NORMAL))

#define IS_TMR4_EVT_MATCH_COND(x)           (((x) | TMR4_EVT_MATCH_CNT_ALL) == TMR4_EVT_MATCH_CNT_ALL)

#define IS_TMR4_EVT_MASK_TYPE(x)                                               \
(   ((x) != 0U)                             ||                                 \
    (((x) | TMR4_EVT_MASK_TYPE_ALL) == TMR4_EVT_MASK_TYPE_ALL))

#define IS_TMR4_EVT_DELAY_OBJECT(x)                                            \
(   ((x) == TMR4_EVT_DELAY_OCCRXH)          ||                                 \
    ((x) == TMR4_EVT_DELAY_OCCRXL))

#define IS_TMR4_EVT_MD(x)                                                      \
(   ((x) == TMR4_EVT_MD_DELAY)              ||                                 \
    ((x) == TMR4_EVT_MD_CMP))

#define IS_TMR4_EVT_MASK(x)                 (((x) | TMR4_EVT_MASK15) == TMR4_EVT_MASK15)

#define IS_TMR4_EVT_BUF_COND(x)                                                \
(   ((x) == TMR4_EVT_BUF_COND_IMMED)        ||                                 \
    ((x) == TMR4_EVT_BUF_COND_PEAK)         ||                                 \
    ((x) == TMR4_EVT_BUF_COND_VALLEY)       ||                                 \
    ((x) == TMR4_EVT_BUF_COND_PEAK_VALLEY))

#define IS_TMR4_OC_CH(x)                    ((x) <= TMR4_OC_CH_WL)
#define IS_TMR4_PWM_CH(x)                   ((x) <= TMR4_PWM_CH_W)
#define IS_TMR4_PWM_PIN(x)                  ((x) <= TMR4_PWM_PIN_OWL)
#define IS_TMR4_EVT_CH(x)                   ((x) <= TMR4_EVT_CH_WL)
#define IS_TMR4_EVT_OUTPUT_EVT(x)                                              \
(   ((x) >> TMR4_SCSR_EVTOS_POS) <= (TMR4_EVT_OUTPUT_EVT5 >> TMR4_SCSR_EVTOS_POS))
#define IS_TMR4_EVT_OUTPUT_SIGNAL(x)        ((x) <= TMR4_EVT_OUTPUT_EVT5_SIGNAL)

#define IS_TMR4_PWM_ABNORMAL_PIN_STAT(x)    ((x) <= TMR4_PWM_ABNORMAL_PIN_HIGH)
/**
 * @}
 */

/**
 * @defgroup TMR4_Channel_Max TMR4 Channel Max
 * @{
 */
#define TMR4_OC_CH_MAX              (TMR4_OC_CH_WL)
#define TMR4_PWM_CH_MAX             (TMR4_PWM_CH_W)
#define TMR4_EVT_CH_MAX             (TMR4_EVT_CH_WL)
/**
 * @}
 */

/**
 * @defgroup TMR4_Flag_Interrupt_Mask TMR4 Flag and Interrupt Mask
 * @{
 */
#define TMR4_FLAG_CNT_MASK          (TMR4_FLAG_CNT_PEAK | TMR4_FLAG_CNT_VALLEY)
#define TMR4_INT_CNT_MASK           (TMR4_INT_CNT_PEAK | TMR4_INT_CNT_VALLEY)

#define TMR4_FLAG_OC_MASK           (TMR4_FLAG_OC_CMP_UH | TMR4_FLAG_OC_CMP_UL | TMR4_FLAG_OC_CMP_VH | \
                                     TMR4_FLAG_OC_CMP_VL | TMR4_FLAG_OC_CMP_WH | TMR4_FLAG_OC_CMP_WL)
#define TMR4_INT_OC_MASK            (TMR4_INT_OC_CMP_UH | TMR4_INT_OC_CMP_UL | TMR4_INT_OC_CMP_VH | \
                                     TMR4_INT_OC_CMP_VL | TMR4_INT_OC_CMP_WH | TMR4_INT_OC_CMP_WL)

#define TMR4_FLAG_RELOAD_TMR_MASK   (TMR4_FLAG_RELOAD_TMR_U | TMR4_FLAG_RELOAD_TMR_V | TMR4_FLAG_RELOAD_TMR_W)
#define TMR4_INT_RELOAD_TMR_MASK    (TMR4_INT_RELOAD_TMR_U | TMR4_INT_RELOAD_TMR_V | TMR4_INT_RELOAD_TMR_W)

#define TMR4_FLAG_SCMP_EVT_MASK     (TMR4_FLAG_SCMP_EVT0 | TMR4_FLAG_SCMP_EVT1 | TMR4_FLAG_SCMP_EVT2 | \
                                     TMR4_FLAG_SCMP_EVT3 | TMR4_FLAG_SCMP_EVT4 | TMR4_FLAG_SCMP_EVT5)
#define TMR4_INT_SCMP_EVT_MASK      (TMR4_INT_SCMP_EVT0 | TMR4_INT_SCMP_EVT1 | TMR4_INT_SCMP_EVT2 | \
                                     TMR4_INT_SCMP_EVT3 | TMR4_INT_SCMP_EVT4 | TMR4_INT_SCMP_EVT5)
/**
 * @}
 */

#define RCSR_REG_TYPE               uint16_t

/**
 * @defgroup TMR4_Registers_Reset_Value TMR4 Registers Reset Value
 * @{
 */
#define TMR4_CCSR_RST_VALUE         (0x0040U)
#define TMR4_SCER_RST_VALUE         (0xFF00U)
#define TMR4_SCMR_RST_VALUE         (0xFF00U)
#define TMR4_POCR_RST_VALUE         (0xFF00U)
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Buffer_Object_Mask TMR4 OC Buffer Object Mask
 * @{
 */
#define TMR4_OC_BUF_OBJECT_MASK     (TMR4_OC_BUF_CMP_VALUE | TMR4_OC_BUF_CMP_MD)
/**
 * @}
 */

/**
 * @defgroup TMR4_OCSR_Bit_Mask TMR4_OCSR Bit Mask
 * @brief Get the specified TMR4_OCSR register bis value of the specified TMR4 OC channel
 * @{
 */
#define TMR4_OCSR_OCEx_MASK(CH)     (((uint16_t)TMR4_OCSR_OCEH) << ((CH) % 2UL))
#define TMR4_OCSR_OCPx_MASK(CH)     (((uint16_t)TMR4_OCSR_OCPH) << ((CH) % 2UL))
#define TMR4_OCSR_OCIE_MASK         (TMR4_OCSR_OCIEH | TMR4_OCSR_OCIEL)
#define TMR4_OCSR_OCF_MASK          (TMR4_OCSR_OCFH | TMR4_OCSR_OCFL)
#define TMR4_OCSR_MASK(CH)                                                     \
(   ((uint16_t)(TMR4_OCSR_OCEH | TMR4_OCSR_OCPH | TMR4_OCSR_OCIEH | TMR4_OCSR_OCFH)) << (((CH) % 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCSR_Bit TMR4_OCSR Bit
 * @brief Get the specified TMR4_OCSR register bis value of the specified TMR4 OC channel
 * @{
 */
#define TMR4_OCSR_OCEx(CH, OCEx)    (((uint16_t)OCEx) << (((uint16_t)((CH) % 2UL)) + TMR4_OCSR_OCEH_POS))
#define TMR4_OCSR_OCPx(CH, OCPx)    (((uint16_t)OCPx) << ((CH) % 2UL))
#define TMR4_OCSR_OCIEx(CH, OCIEx)  (((uint16_t)OCIEx) << ((CH) % 2UL))
#define TMR4_OCSR_OCFx(CH, OCFx)    (((uint16_t)OCFx) << ((CH) % 2UL))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCER_Bit_Mask TMR4_OCER Bit Mask
 * @brief Get the specified TMR4_OCER register bis value of the specified TMR4 OC channel
 * @{
 */
#define TMR4_OCER_CxBUFEN_MASK(CH)  (((uint16_t)TMR4_OCER_CHBUFEN) << (((CH) % 2UL) << 1U))
#define TMR4_OCER_MxBUFEN_MASK(CH)  (((uint16_t)TMR4_OCER_MHBUFEN) << (((CH) % 2UL) << 1U))
#define TMR4_OCER_LMCx_MASK(CH)     (((uint16_t)TMR4_OCER_LMCH) << ((CH) % 2UL))
#define TMR4_OCER_LMMx_MASK(CH)     (((uint16_t)TMR4_OCER_LMMH) << ((CH) % 2UL))
#define TMR4_OCER_MCECx_MASK(CH)    (((uint16_t)TMR4_OCER_MCECH) << ((CH) % 2UL))
#define TMR4_OCER_MASK(CH)                                                   \
(   (((uint16_t)(TMR4_OCER_CHBUFEN | TMR4_OCER_MHBUFEN)) << (((CH) % 2UL) << 1U)) | \
    (((uint16_t)(TMR4_OCER_LMCH | TMR4_OCER_LMMH | TMR4_OCER_MCECH)) << ((CH) % 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCER_Bit TMR4_OCER Bit
 * @brief Get the specified TMR4_OCER register bis value of the specified TMR4 OC channel
 * @{
 */
#define TMR4_OCER_CxBUFEN(CH, CxBUFEN)  ((uint16_t)((uint16_t)(CxBUFEN) << ((((CH) % 2UL) << 1U) + TMR4_OCER_CHBUFEN_POS)))
#define TMR4_OCER_MxBUFEN(CH, MxBUFEN)  ((uint16_t)((uint16_t)(MxBUFEN) << ((((CH) % 2UL) << 1U) + TMR4_OCER_MHBUFEN_POS)))
#define TMR4_OCER_LMCx(CH, LMCx)        ((uint16_t)(LMCx) << ((((CH) % 2UL)) + TMR4_OCER_LMCH_POS))
#define TMR4_OCER_LMMx(CH, LMMx)        ((uint16_t)(LMMx) << ((((CH) % 2UL)) + TMR4_OCER_LMMH_POS))
#define TMR4_OCER_MCECx(CH, MCECx)      ((uint16_t)(MCECx) << ((((CH) % 2UL)) + TMR4_OCER_MCECH_POS))
/**
 * @}
 */

/**
 * @defgroup TMR4_RCSR_Bit_Mask TMR4_RCSR Bit Mask
 * @brief Get the specified TMR4_RCSR register bis value of the specified TMR4 PWM channel
 * @{
 */
#define TMR4_RCSR_RTIDx_MASK(CH)    ((RCSR_REG_TYPE)(((RCSR_REG_TYPE)TMR4_RCSR_RTIDU) << (CH)))
#define TMR4_RCSR_RTIFx_MASK(CH)    ((RCSR_REG_TYPE)(((RCSR_REG_TYPE)TMR4_RCSR_RTIFU) << ((CH) << 2U)))
#define TMR4_RCSR_RTICx_MASK(CH)    ((RCSR_REG_TYPE)(((RCSR_REG_TYPE)TMR4_RCSR_RTICU) << ((CH) << 2U)))
#define TMR4_RCSR_RTEx_MASK(CH)     ((RCSR_REG_TYPE)(((RCSR_REG_TYPE)TMR4_RCSR_RTEU) << ((CH) << 2U)))
#define TMR4_RCSR_RTSx_MASK(CH)     ((RCSR_REG_TYPE)(((RCSR_REG_TYPE)TMR4_RCSR_RTSU) << ((CH) << 2U)))
#define TMR4_RCSR_MASK(CH)          (TMR4_RCSR_RTIDx_MASK(CH) | TMR4_RCSR_RTIFx_MASK(CH) | TMR4_RCSR_RTICx_MASK(CH) | \
                                     TMR4_RCSR_RTEx_MASK(CH) | TMR4_RCSR_RTSx_MASK(CH))
/**
 * @}
 */

/**
 * @defgroup TMR4_PSCR_Bit_Mask TMR4_PSCR Bit Mask
 * @brief Get the specified TMR4_PSCR register bis value of the specified TMR4 PWM port channel
 * @{
 */
#define TMR4_PSCR_OExy_MASK(PORT)   (TMR4_PSCR_OEUH << (PORT))
#define TMR4_PSCR_OSxy_MASK(PORT)   (TMR4_PSCR_OSUH << ((PORT) << 1U))
/**
 * @}
 */

/**
 * @defgroup TMR4_PSCR_Bit TMR4_PSCR Bit
 * @brief Get the specified TMR4_PSCR register bis value of the specified TMR4 PWM port channel
 * @{
 */
#define TMR4_PSCR_OExy(PORT, OExy)  ((OExy) << (PORT))
#define TMR4_PSCR_OSxy(PORT, OSxy)  ((OSxy) << (((PORT) << 1U) + TMR4_PSCR_OSUH_POS))
/**
 * @}
 */

/**
 * @defgroup TMR4_Register TMR4 Register
 * @{
 */
#define TMR4_REG_ADDR(_REG_)        ((uint32_t)(&(_REG_)))
#define TMR4_REG16(_ADDR_)          ((__IO uint16_t *)(_ADDR_))
#define TMR4_REG32(_ADDR_)          ((__IO uint32_t *)(_ADDR_))
#define TMR4_RCSR_REG(_ADDR_)       ((__IO RCSR_REG_TYPE *)(_ADDR_))

/**
 * @defgroup TMR4_OC_Register_UVW TMR4 OC Register
 * @brief Get the specified OC register address of the specified TMR4 unit
 * @{
 */
#define _TMR4_OCCR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->OCCRUH) + ((CH) << 2U))
#define _TMR4_OCMR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->OCMRUH) + ((CH) << 2U))
#define _TMR4_OCER(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->OCERU) + (((CH) & 0x06UL) << 1U))
#define _TMR4_OCSR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->OCSRU) + (((CH) & 0x06UL) << 1U))
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Register_UVW TMR4 PWM Register
 * @brief Get the specified PWM register address of the specified TMR4 unit
 * @{
 */
#define _TMR4_RCSR(UNIT)            TMR4_RCSR_REG(TMR4_REG_ADDR((UNIT)->RCSR))
#define _TMR4_POCR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->POCRU) + ((CH) << 2U))
#define _TMR4_PFSR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->PFSRU) + ((CH) << 3U))
#define _TMR4_PDR(UNIT, CH, IDX)    TMR4_REG16(TMR4_REG_ADDR((UNIT)->PDARU) + ((CH) << 3U) + ((IDX) << 1U))
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Register_UVW TMR4 Event Register
 * @brief Get the specified event register address of the specified TMR4 unit
 * @{
 */
#define _TMR4_SCCR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->SCCRUH) + ((CH) << 2U))
#define _TMR4_SCSR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->SCSRUH) + ((CH) << 2U))
#define _TMR4_SCMR(UNIT, CH)        TMR4_REG16(TMR4_REG_ADDR((UNIT)->SCMRUH) + ((CH) << 2U))
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Register TMR4 OC Register
 * @{
 */
#define TMR4_OCCR(UNIT, CH)         _TMR4_OCCR(UNIT, CH)
#define TMR4_OCMR(UNIT, CH)         _TMR4_OCMR(UNIT, CH)
#define TMR4_OCER(UNIT, CH)         _TMR4_OCER(UNIT, CH)
#define TMR4_OCSR(UNIT, CH)         _TMR4_OCSR(UNIT, CH)
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Register TMR4 PWM Register
 * @{
 */
#define TMR4_RCSR(UNIT)             _TMR4_RCSR(UNIT)
#define TMR4_POCR(UNIT, CH)         _TMR4_POCR(UNIT, CH)
#define TMR4_PFSR(UNIT, CH)         _TMR4_PFSR(UNIT, CH)
#define TMR4_PDR(UNIT, CH, IDX)     _TMR4_PDR(UNIT, CH, IDX)
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Register TMR4 Event Register
 * @{
 */
#define TMR4_SCCR(UNIT, CH)         _TMR4_SCCR(UNIT, CH)
#define TMR4_SCSR(UNIT, CH)         _TMR4_SCSR(UNIT, CH)
#define TMR4_SCMR(UNIT, CH)         _TMR4_SCMR(UNIT, CH)
/**
 * @}
 */

#define TMR4_RMU_TIMEOUT                (100U)
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
 * @defgroup TMR4_Global_Functions TMR4 Global Functions
 * @{
 */

/**
 * @defgroup TMR4_Counter_Global_Functions TMR4 Counter Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_tmr4_init_t to default values
 * @param  [out] pstcTmr4Init           Pointer to a @ref stc_tmr4_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCntInit value is NULL.
 */
int32_t TMR4_StructInit(stc_tmr4_init_t *pstcTmr4Init)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4Init) {
        pstcTmr4Init->u16PeriodValue = 0xFFFFU;
        pstcTmr4Init->u16CountMode = TMR4_MD_SAWTOOTH;
        pstcTmr4Init->u16ClockSrc = TMR4_CLK_SRC_INTERNCLK;
        pstcTmr4Init->u16ClockDiv = TMR4_CLK_DIV1;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize TMR4 counter.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] pstcTmr4Init            Pointer to a @ref stc_tmr4_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCntInit value is NULL.
 */
int32_t TMR4_Init(CM_TMR4_TypeDef *TMR4x, const stc_tmr4_init_t *pstcTmr4Init)
{
    uint16_t u16Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4Init) {
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_CLK_SRC(pstcTmr4Init->u16ClockSrc));
        DDL_ASSERT(IS_TMR4_CLK_DIV(pstcTmr4Init->u16ClockDiv));
        DDL_ASSERT(IS_TMR4_MD(pstcTmr4Init->u16CountMode));

        /* Set TMR4_CCSR */
        u16Value = (pstcTmr4Init->u16ClockDiv | pstcTmr4Init->u16ClockSrc | \
                    pstcTmr4Init->u16CountMode | TMR4_CCSR_CLEAR | TMR4_CCSR_STOP);
        WRITE_REG16(TMR4x->CCSR, u16Value);

        /* Set TMR4_CVPR: default value */
        WRITE_REG16(TMR4x->CVPR, 0x0000U);

        /* Set TMR4 period */
        WRITE_REG16(TMR4x->CPSR, pstcTmr4Init->u16PeriodValue);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize TMR4 counter function
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval int32_t:
 *           - LL_OK:           Reset success.
 *           - LL_ERR_TIMEOUT:  Reset time out.
 * @note   Call LL_PERIPH_WE(LL_PERIPH_PWC_CLK_RMU) unlock RMU_FRSTx register first.
 */
int32_t TMR4_DeInit(CM_TMR4_TypeDef *TMR4x)
{
    int32_t i32Ret = LL_OK;
    __IO uint8_t u8TimeOut = 0U;

    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    /* Reset TMR4 */
    WRITE_REG32(bCM_RMU->FRST2_b.TMR4, 0UL);

    /* Ensure reset procedure is completed */
    while (READ_REG32(bCM_RMU->FRST2_b.TMR4) != 1UL) {
        u8TimeOut++;
        if (u8TimeOut > TMR4_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief Set TMR4 counter clock source
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Src                  TMR4 counter clock source
 *         This parameter can be one of the macros group @ref TMR4_Count_Clock_Source
 *           @arg TMR4_CLK_SRC_INTERNCLK: Uses the internal clock as counter's count clock
 *           @arg TMR4_CLK_SRC_EXTCLK:    Uses an external input clock as counter's count clock
 * @retval None
 * @note   The clock division function is valid when clock source is internal clock.
 */
void TMR4_SetClockSrc(CM_TMR4_TypeDef *TMR4x, uint16_t u16Src)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CLK_SRC(u16Src));

    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_ECKEN, u16Src);
}

/**
 * @brief  Set TMR4 counter clock division
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Div                  TMR4 clock division
 *         This parameter can be one of the macros group @ref TMR4_Count_Clock_Division
 *           @arg TMR4_CLK_DIV1:        CLK
 *           @arg TMR4_CLK_DIV2:        CLK/2
 *           @arg TMR4_CLK_DIV4:        CLK/4
 *           @arg TMR4_CLK_DIV8:        CLK/8
 *           @arg TMR4_CLK_DIV16:       CLK/16
 *           @arg TMR4_CLK_DIV32:       CLK/32
 *           @arg TMR4_CLK_DIV64:       CLK/64
 *           @arg TMR4_CLK_DIV128:      CLK/128
 *           @arg TMR4_CLK_DIV256:      CLK/256
 *           @arg TMR4_CLK_DIV512:      CLK/512
 *           @arg TMR4_CLK_DIV1024:     CLK/1024
 * @retval None
 * @note   The clock division function is valid when clock source is the internal clock.
 */
void TMR4_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint16_t u16Div)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CLK_DIV(u16Div));

    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_CKDIV, u16Div);
}

/**
 * @brief Set TMR4 counter count mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Mode                 TMR4 counter count mode
 *         This parameter can be one of the macros group @ref TMR4_Count_Mode
 *           @arg TMR4_MD_SAWTOOTH:     TMR4 count mode sawtooth wave
 *           @arg TMR4_MD_TRIANGLE:     TMR4 count mode triangular
 * @retval None
 */
void TMR4_SetCountMode(CM_TMR4_TypeDef *TMR4x, uint16_t u16Mode)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_MD(u16Mode));

    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_MODE, u16Mode);
}

/**
 * @brief  Get the period value of the TMR4 counter.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval The period value of the TMR4 counter
 */
uint16_t TMR4_GetPeriodValue(const CM_TMR4_TypeDef *TMR4x)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    return READ_REG16(TMR4x->CPSR);
}

/**
 * @brief  Set the period value of the TMR4 counter.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Value                The period value of the TMR4 counter
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_SetPeriodValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    WRITE_REG16(TMR4x->CPSR, u16Value);
}

/**
 * @brief  Get the count value of the TMR4 counter.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval The count value of the TMR4 counter
 */
uint16_t TMR4_GetCountValue(const CM_TMR4_TypeDef *TMR4x)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    return READ_REG16(TMR4x->CNTR);
}

/**
 * @brief  Set the count value of the TMR4 counter.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Value                The count value of the TMR4 counter
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_SetCountValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    WRITE_REG16(TMR4x->CNTR, u16Value);
}

/**
 * @brief  Clear TMR4 counter count value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval None
 */
void TMR4_ClearCountValue(CM_TMR4_TypeDef *TMR4x)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_CLEAR);
}

/**
 * @brief Start TMR4 counter
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval None
 */
void TMR4_Start(CM_TMR4_TypeDef *TMR4x)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    CLR_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_STOP);
}

/**
 * @brief  Stop TMR4 counter
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @retval None
 */
void TMR4_Stop(CM_TMR4_TypeDef *TMR4x)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_STOP);
}

/**
 * @brief  Clear TMR4 flag
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Flag                 TMR4 flag
 *         This parameter can be any composed value of the macros group @ref TMR4_Flag
 * @retval None
 */
void TMR4_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32Flag)
{
    uint32_t u32ClearFlag;
    __IO uint16_t *OCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_FLAG(u32Flag));

    /* Counter flag */
    if ((u32Flag & TMR4_FLAG_CNT_MASK) > 0UL) {
        CLR_REG16_BIT(TMR4x->CCSR, (u32Flag & TMR4_FLAG_CNT_MASK));
    }

    /* Output-compare flag */
    u32ClearFlag = (u32Flag & TMR4_FLAG_OC_MASK);
    if (u32ClearFlag > 0UL) {
        /* TMR4_OCSRU */
        u32ClearFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_UH | TMR4_FLAG_OC_CMP_UL)) >> 10U);
        if (u32ClearFlag > 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_UH);
            CLR_REG16_BIT(*OCSR, u32ClearFlag);
        }

        /* TMR4_OCSRV */
        u32ClearFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_VH | TMR4_FLAG_OC_CMP_VL)) >> 12U);
        if (u32ClearFlag > 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_VH);
            CLR_REG16_BIT(*OCSR, u32ClearFlag);
        }

        /* TMR4_OCSRW */
        u32ClearFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_WH | TMR4_FLAG_OC_CMP_WL)) >> 14U);
        if (u32ClearFlag > 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_WH);
            CLR_REG16_BIT(*OCSR, u32ClearFlag);
        }
    }

    /* PWM reload timer flag */
    u32ClearFlag = ((u32Flag & TMR4_FLAG_RELOAD_TMR_MASK) << 5U);
    if (u32ClearFlag > 0UL) {
        SET_REG_BIT(TMR4x->RCSR, (RCSR_REG_TYPE)u32ClearFlag);
    }

    /* Event-compare interrupt */
    u32ClearFlag = ((u32Flag & TMR4_FLAG_SCMP_EVT_MASK) >> 24U);
    if (u32ClearFlag > 0UL) {
        CLR_REG16_BIT(TMR4x->SCFR, u32ClearFlag);
    }
}

/**
 * @brief  Get TMR4 flag
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Flag                 TMR4 flag
 *         This parameter can be any composed value of the macros group @ref TMR4_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t TMR4_GetStatus(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Flag)
{
    uint32_t u32ReadFlag;
    uint8_t u8FlagSetCount = 0;
    __IO uint16_t *OCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_FLAG(u32Flag));

    /* Counter flag status */
    if (READ_REG16_BIT(TMR4x->CCSR, (u32Flag & TMR4_FLAG_CNT_MASK)) > 0U) {
        u8FlagSetCount++;
    }

    /* Output-compare interrupt */
    u32ReadFlag = (u32Flag & TMR4_FLAG_OC_MASK);
    if (u32ReadFlag > 0UL) {
        /* TMR4_OCSRU */
        u32ReadFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_UH | TMR4_FLAG_OC_CMP_UL)) >> 10U);
        OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_UH);
        if (READ_REG16_BIT(*OCSR, u32ReadFlag) > 0U) {
            u8FlagSetCount++;
        }

        /* TMR4_OCSRV */
        u32ReadFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_VH | TMR4_FLAG_OC_CMP_VL)) >> 12U);
        OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_VH);
        if (READ_REG16_BIT(*OCSR, u32ReadFlag) > 0U) {
            u8FlagSetCount++;
        }

        /* TMR4_OCSRW */
        u32ReadFlag = ((u32Flag & (TMR4_FLAG_OC_CMP_WH | TMR4_FLAG_OC_CMP_WL)) >> 14U);
        OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_WH);
        if (READ_REG16_BIT(*OCSR, u32ReadFlag) > 0U) {
            u8FlagSetCount++;
        }
    }

    /* PWM reload timer flag status */
    u32ReadFlag = ((u32Flag & (TMR4_FLAG_RELOAD_TMR_MASK)) << 4U);
    if (READ_REG_BIT(TMR4x->RCSR, (RCSR_REG_TYPE)u32ReadFlag) > 0U) {
        u8FlagSetCount++;
    }

    /* Event-compare interrupt */
    u32ReadFlag = ((u32Flag & TMR4_FLAG_SCMP_EVT_MASK) >> 24U);
    if (READ_REG16_BIT(TMR4x->SCFR, u32ReadFlag) > 0U) {
        u8FlagSetCount++;
    }

    return (u8FlagSetCount == 0U) ? RESET : SET;
}

/**
 * @brief  Enable or disable the specified TMR4 interrupt
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32IntType              TMR4 interrupt source
 *         This parameter can be any composed value of the macros group @ref TMR4_Interrupt
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_IntCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32Type;
    __IO uint16_t *OCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Counter interrupt */
    u32Type = (u32IntType & TMR4_INT_CNT_MASK);
    if (u32Type > 0UL) {
        (ENABLE == enNewState) ? SET_REG16_BIT(TMR4x->CCSR, u32Type) : CLR_REG16_BIT(TMR4x->CCSR, u32Type);
    }

    /* Output-compare interrupt */
    u32Type = (u32IntType & TMR4_INT_OC_MASK);
    if (u32Type > 0UL) {
        /* TMR4_OCSRU */
        u32Type = ((u32IntType & (TMR4_INT_OC_CMP_UH | TMR4_INT_OC_CMP_UL)) >> 12U);
        if (u32Type != 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_UH);
            (ENABLE == enNewState) ? SET_REG16_BIT(*OCSR, u32Type) : CLR_REG16_BIT(*OCSR, u32Type);
        }

        /* TMR4_OCSRV */
        u32Type = ((u32IntType & (TMR4_INT_OC_CMP_VH | TMR4_INT_OC_CMP_VL)) >> 14U);
        if (u32Type != 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_VH);
            (ENABLE == enNewState) ? SET_REG16_BIT(*OCSR, u32Type) : CLR_REG16_BIT(*OCSR, u32Type);
        }

        /* TMR4_OCSRW */
        u32Type = ((u32IntType & (TMR4_INT_OC_CMP_WH | TMR4_INT_OC_CMP_WL)) >> 16U);
        if (u32Type != 0UL) {
            OCSR = TMR4_OCSR(TMR4x, TMR4_OC_CH_WH);
            (ENABLE == enNewState) ? SET_REG16_BIT(*OCSR, u32Type) : CLR_REG16_BIT(*OCSR, u32Type);
        }
    }

    /* PWM reload timer interrupt */
    u32Type = (u32IntType & TMR4_INT_RELOAD_TMR_MASK);
    if (u32Type > 0UL) {
        (ENABLE == enNewState) ? CLR_REG_BIT(TMR4x->RCSR, (RCSR_REG_TYPE)u32Type) : SET_REG_BIT(TMR4x->RCSR, (RCSR_REG_TYPE)u32Type);
    }

    /* Event-compare interrupt */
    u32Type = ((u32IntType & TMR4_INT_SCMP_EVT_MASK) >> 24U);
    if (u32Type > 0UL) {
        (ENABLE == enNewState) ? SET_REG16_BIT(TMR4x->SCIR, u32Type) : CLR_REG16_BIT(TMR4x->SCIR, u32Type);
    }
}

/**
 * @brief  Enable or disable the TMR4 counter period buffer function.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_PeriodBufCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_BUFEN);
    } else {
        CLR_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_BUFEN);
    }
}

/**
 * @brief  Get TMR4 count interrupt mask times
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32IntType              TMR4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_INT_CNT_PEAK:    Count peak interrupt
 *           @arg TMR4_INT_CNT_VALLEY : Count valley interrupt
 * @retval Returned value can be one of the macros group @ref TMR4_Count_Interrupt_Mask_Time
 *           - TMR4_INT_CNT_MASK0:  Counter interrupt flag is always set(not masked) for counter count every time at "0x0000" or peak
 *           - TMR4_INT_CNT_MASK1:  Counter interrupt flag is set once when counter counts 2 times at "0x0000" or peak (skipping 1 count)
 *           - TMR4_INT_CNT_MASK2:  Counter interrupt flag is set once when counter counts 3 times at "0x0000" or peak (skipping 2 count)
 *           - TMR4_INT_CNT_MASK3:  Counter interrupt flag is set once when counter counts 4 times at "0x0000" or peak (skipping 3 count)
 *           - TMR4_INT_CNT_MASK4:  Counter interrupt flag is set once when counter counts 5 times at "0x0000" or peak (skipping 4 count)
 *           - TMR4_INT_CNT_MASK5:  Counter interrupt flag is set once when counter counts 6 times at "0x0000" or peak (skipping 5 count)
 *           - TMR4_INT_CNT_MASK6:  Counter interrupt flag is set once when counter counts 7 times at "0x0000" or peak (skipping 6 count)
 *           - TMR4_INT_CNT_MASK7:  Counter interrupt flag is set once when counter counts 8 times at "0x0000" or peak (skipping 7 count)
 *           - TMR4_INT_CNT_MASK8:  Counter interrupt flag is set once when counter counts 9 times at "0x0000" or peak (skipping 8 count)
 *           - TMR4_INT_CNT_MASK9:  Counter interrupt flag is set once when counter counts 10 times at "0x0000" or peak (skipping 9 count)
 *           - TMR4_INT_CNT_MASK10: Counter interrupt flag is set once when counter counts 11 times at "0x0000" or peak (skipping 10 count)
 *           - TMR4_INT_CNT_MASK11: Counter interrupt flag is set once when counter counts 12 times at "0x0000" or peak (skipping 11 count)
 *           - TMR4_INT_CNT_MASK12: Counter interrupt flag is set once when counter counts 13 times at "0x0000" or peak (skipping 12 count)
 *           - TMR4_INT_CNT_MASK13: Counter interrupt flag is set once when counter counts 14 times at "0x0000" or peak (skipping 13 count)
 *           - TMR4_INT_CNT_MASK14: Counter interrupt flag is set once when counter counts 15 times at "0x0000" or peak (skipping 14 count)
 *           - TMR4_INT_CNT_MASK15: Counter interrupt flag is set once when counter counts 16 times at "0x0000" or peak (skipping 15 count)
 */
uint16_t TMR4_GetCountIntMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType)
{
    uint16_t u16MaskTimes;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_INT_CNT(u32IntType));

    if (TMR4_INT_CNT_VALLEY == u32IntType) {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIM) >> TMR4_CVPR_ZIM_POS);
    } else {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIM) >> TMR4_CVPR_PIM_POS);
    }

    return u16MaskTimes;
}

/**
 * @brief  Set TMR4 counter interrupt mask times
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32IntType              TMR4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_INT_CNT_PEAK:    Count peak interrupt
 *           @arg TMR4_INT_CNT_VALLEY : Count valley interrupt
 * @param [in] u16MaskTime              TMR4 counter interrupt mask times
 *         This parameter can be one of the macros group @ref TMR4_Count_Interrupt_Mask_Time
 *           @arg TMR4_INT_CNT_MASK0:  Counter interrupt flag is always set(not masked) for counter count every time at "0x0000" or peak
 *           @arg TMR4_INT_CNT_MASK1:  Counter interrupt flag is set once when counter counts 2 times at "0x0000" or peak (skipping 1 count)
 *           @arg TMR4_INT_CNT_MASK2:  Counter interrupt flag is set once when counter counts 3 times at "0x0000" or peak (skipping 2 count)
 *           @arg TMR4_INT_CNT_MASK3:  Counter interrupt flag is set once when counter counts 4 times at "0x0000" or peak (skipping 3 count)
 *           @arg TMR4_INT_CNT_MASK4:  Counter interrupt flag is set once when counter counts 5 times at "0x0000" or peak (skipping 4 count)
 *           @arg TMR4_INT_CNT_MASK5:  Counter interrupt flag is set once when counter counts 6 times at "0x0000" or peak (skipping 5 count)
 *           @arg TMR4_INT_CNT_MASK6:  Counter interrupt flag is set once when counter counts 7 times at "0x0000" or peak (skipping 6 count)
 *           @arg TMR4_INT_CNT_MASK7:  Counter interrupt flag is set once when counter counts 8 times at "0x0000" or peak (skipping 7 count)
 *           @arg TMR4_INT_CNT_MASK8:  Counter interrupt flag is set once when counter counts 9 times at "0x0000" or peak (skipping 8 count)
 *           @arg TMR4_INT_CNT_MASK9:  Counter interrupt flag is set once when counter counts 10 times at "0x0000" or peak (skipping 9 count)
 *           @arg TMR4_INT_CNT_MASK10: Counter interrupt flag is set once when counter counts 11 times at "0x0000" or peak (skipping 10 count)
 *           @arg TMR4_INT_CNT_MASK11: Counter interrupt flag is set once when counter counts 12 times at "0x0000" or peak (skipping 11 count)
 *           @arg TMR4_INT_CNT_MASK12: Counter interrupt flag is set once when counter counts 13 times at "0x0000" or peak (skipping 12 count)
 *           @arg TMR4_INT_CNT_MASK13: Counter interrupt flag is set once when counter counts 14 times at "0x0000" or peak (skipping 13 count)
 *           @arg TMR4_INT_CNT_MASK14: Counter interrupt flag is set once when counter counts 15 times at "0x0000" or peak (skipping 14 count)
 *           @arg TMR4_INT_CNT_MASK15: Counter interrupt flag is set once when counter counts 16 times at "0x0000" or peak (skipping 15 count)
 * @retval None
 */
void TMR4_SetCountIntMaskTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType, uint16_t u16MaskTime)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_INT_CNT(u32IntType));
    DDL_ASSERT(IS_TMR4_INT_CNT_MASKTIME(u16MaskTime));

    if (TMR4_INT_CNT_VALLEY == (u32IntType & TMR4_INT_CNT_VALLEY)) {
        MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_ZIM, (u16MaskTime << TMR4_CVPR_ZIM_POS));
    }

    if (TMR4_INT_CNT_PEAK == (u32IntType & TMR4_INT_CNT_PEAK)) {
        MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_PIM, (u16MaskTime << TMR4_CVPR_PIM_POS));
    }
}

/**
 * @brief  Get TMR4 counter current interrupt mask times
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32IntType              TMR4 interrupt source
 *         This parameter can be one of the macros group @ref TMR4_Interrupt
 *           @arg TMR4_INT_CNT_PEAK:    Count peak interrupt
 *           @arg TMR4_INT_CNT_VALLEY : Count valley interrupt
 * @retval Returned value can be one of the macros group @ref TMR4_Count_Interrupt_Mask_Time
 *           - TMR4_INT_CNT_MASK0:   Counter interrupt flag is always set(not masked) for every counter count at "0x0000" or peak
 *           - TMR4_INT_CNT_MASK1:   Counter interrupt flag is set once for 2 every counter counts at "0x0000" or peak (skipping 1 count)
 *           - TMR4_INT_CNT_MASK2:   Counter interrupt flag is set once for 3 every counter counts at "0x0000" or peak (skipping 2 count)
 *           - TMR4_INT_CNT_MASK3:   Counter interrupt flag is set once for 4 every counter counts at "0x0000" or peak (skipping 3 count)
 *           - TMR4_INT_CNT_MASK4:   Counter interrupt flag is set once for 5 every counter counts at "0x0000" or peak (skipping 4 count)
 *           - TMR4_INT_CNT_MASK5:   Counter interrupt flag is set once for 6 every counter counts at "0x0000" or peak (skipping 5 count)
 *           - TMR4_INT_CNT_MASK6:   Counter interrupt flag is set once for 7 every counter counts at "0x0000" or peak (skipping 6 count)
 *           - TMR4_INT_CNT_MASK7:   Counter interrupt flag is set once for 8 every counter counts at "0x0000" or peak (skipping 7 count)
 *           - TMR4_INT_CNT_MASK8:   Counter interrupt flag is set once for 9 every counter counts at "0x0000" or peak (skipping 8 count)
 *           - TMR4_INT_CNT_MASK9:   Counter interrupt flag is set once for 10 every counter counts at "0x0000" or peak (skipping 9 count)
 *           - TMR4_INT_CNT_MASK10:  Counter interrupt flag is set once for 11 every counter counts at "0x0000" or peak (skipping 10 count)
 *           - TMR4_INT_CNT_MASK11:  Counter interrupt flag is set once for 12 every counter counts at "0x0000" or peak (skipping 11 count)
 *           - TMR4_INT_CNT_MASK12:  Counter interrupt flag is set once for 13 every counter counts at "0x0000" or peak (skipping 12 count)
 *           - TMR4_INT_CNT_MASK13:  Counter interrupt flag is set once for 14 every counter counts at "0x0000" or peak (skipping 13 count)
 *           - TMR4_INT_CNT_MASK14:  Counter interrupt flag is set once for 15 every counter counts at "0x0000" or peak (skipping 14 count)
 *           - TMR4_INT_CNT_MASK15:  Counter interrupt flag is set once for 16 every counter counts at "0x0000" or peak (skipping 15 count)
 */
uint16_t TMR4_GetCurrentCountIntMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType)
{
    uint16_t u16MaskTimes;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_INT_CNT(u32IntType));

    if (TMR4_INT_CNT_VALLEY == u32IntType) {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIC) >> TMR4_CVPR_ZIC_POS);
    } else {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIC) >> TMR4_CVPR_PIC_POS);
    }

    return u16MaskTimes;
}

/**
 * @brief  Enable or disable port output TMR4 counter direction signal
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_PortOutputCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    } else {
        CLR_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    }
}

/**
 * @brief  Enable or disable hardware start of the TMR4 count.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_HWStartCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_HST);
    } else {
        CLR_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_HST);
    }
}

/**
 * @}
 */

/**
 * @defgroup TMR4_Output_Compare_Global_Functions TMR4 Output-Compare Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_tmr4_oc_init_t to default values
 * @param  [out] pstcTmr4OcInit         Pointer to a @ref stc_tmr4_oc_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4OcInit value is NULL.
 */
int32_t TMR4_OC_StructInit(stc_tmr4_oc_init_t *pstcTmr4OcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4OcInit) {
        pstcTmr4OcInit->u16CompareValue = 0U;
        pstcTmr4OcInit->u16OcInvalidPolarity = TMR4_OC_INVD_LOW;
        pstcTmr4OcInit->u16CompareModeBufCond = TMR4_OC_BUF_COND_IMMED;
        pstcTmr4OcInit->u16CompareValueBufCond = TMR4_OC_BUF_COND_IMMED;
        pstcTmr4OcInit->u16BufLinkTransObject = TMR4_OC_BUF_NONE;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize TMR4 OC
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] pstcTmr4OcInit          Pointer to a @ref stc_tmr4_oc_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4OcInit value is NULL.
 */
int32_t TMR4_OC_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_oc_init_t *pstcTmr4OcInit)
{
    uint16_t u16Value;
    __IO uint16_t *OCER;
    __IO uint16_t *OCSR;
    __IO uint16_t *OCCR;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4OcInit) {
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_OC_INVD_POLARITY(pstcTmr4OcInit->u16OcInvalidPolarity));
        DDL_ASSERT(IS_TMR4_OC_BUF_COND(pstcTmr4OcInit->u16CompareModeBufCond));
        DDL_ASSERT(IS_TMR4_OC_BUF_COND(pstcTmr4OcInit->u16CompareValueBufCond));
        DDL_ASSERT(IS_TMR4_OC_BUF_OBJECT(pstcTmr4OcInit->u16BufLinkTransObject));

        /* Get pointer of current channel OC register address */
        OCSR = TMR4_OCSR(TMR4x, u32Ch);
        OCER = TMR4_OCER(TMR4x, u32Ch);
        OCCR = TMR4_OCCR(TMR4x, u32Ch);

        /* Set output polarity when OC is disabled. */
        MODIFY_REG16(*OCSR, TMR4_OCSR_MASK(u32Ch), TMR4_OCSR_OCPx(u32Ch, pstcTmr4OcInit->u16OcInvalidPolarity));

        /* Set OCMR&&OCCR buffer function */
        u16Value = (TMR4_OCER_MxBUFEN(u32Ch, pstcTmr4OcInit->u16CompareModeBufCond) | \
                    TMR4_OCER_CxBUFEN(u32Ch, pstcTmr4OcInit->u16CompareValueBufCond));
        if (TMR4_OC_BUF_CMP_VALUE == (pstcTmr4OcInit->u16BufLinkTransObject & TMR4_OC_BUF_CMP_VALUE)) {
            u16Value |= TMR4_OCER_LMCx_MASK(u32Ch);
        }

        if (TMR4_OC_BUF_CMP_MD == (pstcTmr4OcInit->u16BufLinkTransObject & TMR4_OC_BUF_CMP_MD)) {
            u16Value |= TMR4_OCER_LMMx_MASK(u32Ch);
        }

        MODIFY_REG16(*OCER, TMR4_OCER_MASK(u32Ch), u16Value);

        /* Set OC compare value */
        WRITE_REG16(*OCCR, pstcTmr4OcInit->u16CompareValue);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-initialize TMR4 OC
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @retval None
 */
void TMR4_OC_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *OCER;
    __IO uint16_t *OCSR;
    __IO uint16_t *OCCR;
    __IO uint16_t *OCMRxH;
    __IO uint32_t *OCMRxL;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCSR = TMR4_OCSR(TMR4x, u32Ch);
    OCER = TMR4_OCER(TMR4x, u32Ch);
    OCCR = TMR4_OCCR(TMR4x, u32Ch);

    /* Clear bits: port output valid && OP level && interrupt */
    CLR_REG16_BIT(*OCSR, TMR4_OCSR_MASK(u32Ch));

    /* Clear bits: OCMR&&OCCR buffer */
    CLR_REG16_BIT(*OCER, TMR4_OCER_MASK(u32Ch));

    /* Set OC compare match value */
    WRITE_REG16(*OCCR, 0x0000U);

    /* Set OCMR value */
    if ((u32Ch & 0x01UL) == 0UL) {
        OCMRxH = TMR4_OCMR(TMR4x, u32Ch);
        WRITE_REG16(*OCMRxH, 0x0000U);
    } else {
        OCMRxL = (__IO uint32_t *)((uint32_t)TMR4_OCMR(TMR4x, u32Ch));
        WRITE_REG32(*OCMRxL, 0x00000000UL);
    }
}

/**
 * @brief  Get TMR4 OC OCCR compare value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @retval The compare value of the TMR4 OC OCCR register
 */
uint16_t TMR4_OC_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *OCCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCCR = TMR4_OCCR(TMR4x, u32Ch);

    return READ_REG16(*OCCR);
}

/**
 * @brief  Set TMR4 OC compare value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] u16Value                The compare value of the TMR4 OC OCCR register
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_OC_SetCompareValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint16_t *OCCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCCR = TMR4_OCCR(TMR4x, u32Ch);

    WRITE_REG16(*OCCR, u16Value);
}

/**
 * @brief  Enable or disable the TMR4 OC of the specified channel.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_OC_Cmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    __IO uint16_t *OCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OC register address */
    OCSR = TMR4_OCSR(TMR4x, u32Ch);

    /* Set OCSR port output compare */
    MODIFY_REG16(*OCSR, TMR4_OCSR_OCEx_MASK(u32Ch), TMR4_OCSR_OCEx(u32Ch, enNewState));
}

/**
 * @brief  Extend the matching conditions of TMR4 OC channel
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_OC_ExtendControlCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    __IO uint16_t *OCER;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OC register address */
    OCER = TMR4_OCER(TMR4x, u32Ch);

    /* Set OCER register: Extend match function */
    MODIFY_REG16(*OCER, TMR4_OCER_MCECx_MASK(u32Ch), TMR4_OCER_MCECx(u32Ch, enNewState));
}

/**
 * @brief  Set TMR4 OC OCCR/OCMR buffer interval response function
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] u16Object               TMR4 OC register buffer: OCCR/OCMR
 *         This parameter can be any composed value of the macros group @ref TMR4_OC_Buffer_Object
 *           @arg TMR4_OC_BUF_CMP_VALUE: The register OCCR buffer function
 *           @arg TMR4_OC_BUF_CMP_MD:    The register OCMR buffer function
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 *           @arg ENABLE:               Enable the OCMR/OCMR register buffer function.
 *           @arg DISABLE:              Disable the OCMR/OCMR register buffer function.
 * @retval None
 */
void TMR4_OC_BufIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch,
                                    uint16_t u16Object, en_functional_state_t enNewState)
{
    __IO uint16_t *OCER;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OC_BUF_OBJECT(u16Object));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OC register address */
    OCER = TMR4_OCER(TMR4x, u32Ch);

    if (TMR4_OC_BUF_CMP_VALUE == (u16Object & TMR4_OC_BUF_CMP_VALUE)) {
        /* Set OCER register: OCCR link transfer function */
        MODIFY_REG16(*OCER, TMR4_OCER_LMCx_MASK(u32Ch), TMR4_OCER_LMCx(u32Ch, enNewState));
    }

    if (TMR4_OC_BUF_CMP_MD == (u16Object & TMR4_OC_BUF_CMP_MD)) {
        /* Set OCER register: OCMR link transfer function */
        MODIFY_REG16(*OCER, TMR4_OCER_LMMx_MASK(u32Ch), TMR4_OCER_LMMx(u32Ch, enNewState));
    }
}

/**
 * @brief  Get TMR4 OC output current polarity
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @retval Returned value can be one of the macros group @ref TMR4_OC_Output_Polarity
 *           - TMR4_OC_PORT_LOW:        TMR4 OC output low level
 *           - TMR4_OC_PORT_HIGH:       TMR4 OC output high level
 */
uint16_t TMR4_OC_GetPolarity(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *OCSR;
    uint16_t u16Polarity;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCSR = TMR4_OCSR(TMR4x, u32Ch);

    /* Get OCSR register: OC output polarity */
    u16Polarity = READ_REG16_BIT(*OCSR, TMR4_OCSR_OCPx_MASK(u32Ch));
    return (u16Polarity >> (u32Ch % 2UL));
}

/**
 * @brief  Set TMR4 OC invalid output polarity
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] u16Polarity             TMR4 OC invalid output polarity.
 *         This parameter can be one of the macros group @ref TMR4_OC_Invalid_Output_Polarity
 *           @arg TMR4_OC_INVD_LOW:     TMR4 OC output low level when OC is invalid
 *           @arg TMR4_OC_INVD_HIGH:    TMR4 OC output high level when OC is invalid
 * @retval None
 */
void TMR4_OC_SetOcInvalidPolarity(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Polarity)
{
    __IO uint16_t *OCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OC_INVD_POLARITY(u16Polarity));

    /* Get pointer of current channel OC register address */
    OCSR = TMR4_OCSR(TMR4x, u32Ch);

    /* Set OCSR register: OC invalid output polarity */
    MODIFY_REG16(*OCSR, TMR4_OCSR_OCPx_MASK(u32Ch), TMR4_OCSR_OCPx(u32Ch, u16Polarity));
}

/**
 * @brief  Set TMR4 OC OCCR/OCMR buffer transfer condition
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] u16Object               TMR4 OC register buffer type: OCCR/OCMR
 *         This parameter can be any composed value of the macros group @ref TMR4_OC_Buffer_Object
 *           @arg TMR4_OC_BUF_CMP_VALUE: The register OCCR buffer function
 *           @arg TMR4_OC_BUF_CMP_MD:    The register OCMR buffer function
 * @param  [in] u16BufCond              TMR4 OC OCCR/OCMR buffer transfer condition
 *         This parameter can be one of the macros group @ref TMR4_OC_Buffer_Transfer_Condition
 *           @arg TMR4_OC_BUF_COND_IMMED:   Buffer transfer is made when writing to the OCCR/OCMR register.
 *           @arg TMR4_OC_BUF_COND_VALLEY:  Buffer transfer is made when counter count valley.
 *           @arg TMR4_OC_BUF_COND_PEAK:    Buffer transfer is made when counter count peak.
 *           @arg TMR4_OC_BUF_COND_PEAK_VALLEY: Buffer transfer is made when counter count peak or valley.
 * @retval None
 */
void TMR4_OC_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Object, uint16_t u16BufCond)
{
    __IO uint16_t *OCER;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OC_BUF_OBJECT(u16Object));
    DDL_ASSERT(IS_TMR4_OC_BUF_COND(u16BufCond));

    /* Get pointer of current channel OC register address */
    OCER = TMR4_OCER(TMR4x, u32Ch);

    if (TMR4_OC_BUF_CMP_VALUE == (u16Object & TMR4_OC_BUF_CMP_VALUE)) {
        /* Set OCER register: OCCR buffer mode */
        MODIFY_REG16(*OCER, TMR4_OCER_CxBUFEN_MASK(u32Ch), TMR4_OCER_CxBUFEN(u32Ch, u16BufCond));
    }

    if (TMR4_OC_BUF_CMP_MD == (u16Object & TMR4_OC_BUF_CMP_MD)) {
        /* Set OCER register: OCMR buffer mode */
        MODIFY_REG16(*OCER, TMR4_OCER_MxBUFEN_MASK(u32Ch), TMR4_OCER_MxBUFEN(u32Ch, u16BufCond));
    }
}

/**
 * @brief  Get the TMR4 OC high channel mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel.
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @retval The TMR4 OC high channel mode
 * @note   The function only can get high channel mode:TMR4_OC_CH_xH(x = U/V/W)
 */
uint16_t TMR4_OC_GetHighChCompareMode(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *OCMRxH;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_HIGH_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCMRxH = TMR4_OCMR(TMR4x, u32Ch);
    return READ_REG16(*OCMRxH);
}

/**
 * @brief  Set the TMR4 OC high channel mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel.
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] unTmr4Ocmrh             The TMR4 OC high channel mode @ref un_tmr4_oc_ocmrh_t
 * @retval None
 * @note   The function only can set high channel mode:TMR4_OC_CH_xH(x = U/V/W)
 */
void TMR4_OC_SetHighChCompareMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, un_tmr4_oc_ocmrh_t unTmr4Ocmrh)
{
    __IO uint16_t *OCMRxH;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_HIGH_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCMRxH = TMR4_OCMR(TMR4x, u32Ch);
    WRITE_REG16(*OCMRxH, unTmr4Ocmrh.OCMRx);
}

/**
 * @brief  Get the TMR4 OC low channel mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel.
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @retval The TMR4 OC low channel mode
 * @note   The function only can get low channel mode:TMR4_OC_CH_xL(x = U/V/W)
 */
uint32_t TMR4_OC_GetLowChCompareMode(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint32_t *OCMRxL;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_LOW_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCMRxL = (__IO uint32_t *)((uint32_t)TMR4_OCMR(TMR4x, u32Ch));
    return READ_REG32(*OCMRxL);
}

/**
 * @brief  Set the TMR4 OC low channel mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 OC channel.
 *         This parameter can be one of the macros group @ref TMR4_OC_Channel
 * @param  [in] unTmr4Ocmrl             The TMR4 OC low channel mode @ref un_tmr4_oc_ocmrl_t
 * @retval None
 * @note   The function only can set low channel mode:TMR4_OC_CH_xL(x = U/V/W)
 */
void TMR4_OC_SetLowChCompareMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, un_tmr4_oc_ocmrl_t unTmr4Ocmrl)
{
    __IO uint32_t *OCMRxL;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OC_LOW_CH(u32Ch));

    /* Get pointer of current channel OC register address */
    OCMRxL = (__IO uint32_t *)((uint32_t)TMR4_OCMR(TMR4x, u32Ch));
    WRITE_REG32(*OCMRxL, unTmr4Ocmrl.OCMRx);
}

/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Global_Functions TMR4 PWM Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_tmr4_pwm_init_t to default values
 * @param  [out] pstcTmr4PwmInit        Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4PwmInit value is NULL.
 */
int32_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcTmr4PwmInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4PwmInit) {
        pstcTmr4PwmInit->u16Mode = TMR4_PWM_MD_THROUGH;
        pstcTmr4PwmInit->u16ClockDiv = TMR4_PWM_CLK_DIV1;
        pstcTmr4PwmInit->u16Polarity = TMR4_PWM_OXH_HOLD_OXL_HOLD;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize TMR4 PWM
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] pstcTmr4PwmInit         Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4PwmInit value is NULL.
 */
int32_t TMR4_PWM_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_pwm_init_t *pstcTmr4PwmInit)
{
    uint16_t POCRValue;
    __IO uint16_t *POCR;
    RCSR_REG_TYPE RCSRValue;
    __IO RCSR_REG_TYPE *RCSR;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4PwmInit) {
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_PWM_MD(pstcTmr4PwmInit->u16Mode));
        DDL_ASSERT(IS_TMR4_PWM_CLK_DIV(pstcTmr4PwmInit->u16ClockDiv));
        DDL_ASSERT(IS_TMR4_PWM_POLARITY(pstcTmr4PwmInit->u16Polarity));

        /* Get pointer of current channel PWM register address */
        POCR = TMR4_POCR(TMR4x, u32Ch);
        RCSR = TMR4_RCSR(TMR4x);

        /* Set POCR register */
        POCRValue = (pstcTmr4PwmInit->u16Mode | pstcTmr4PwmInit->u16ClockDiv | pstcTmr4PwmInit->u16Polarity);
        WRITE_REG16(*POCR, POCRValue);

        /* Set RCSR register */
        RCSRValue = (TMR4_RCSR_RTSx_MASK(u32Ch) | TMR4_RCSR_RTIDx_MASK(u32Ch) | TMR4_RCSR_RTICx_MASK(u32Ch));
        MODIFY_REG(*RCSR, TMR4_RCSR_MASK(u32Ch), RCSRValue);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-initialize TMR4 PWM
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @retval None
 */
void TMR4_PWM_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *POCR;
    __IO RCSR_REG_TYPE *RCSR;
    RCSR_REG_TYPE RCSRValue;
    __IO uint16_t *PDAR;
    __IO uint16_t *PDBR;
    __IO uint16_t *PFSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    POCR = TMR4_POCR(TMR4x, u32Ch);
    RCSR = TMR4_RCSR(TMR4x);
    PDAR = TMR4_PDR(TMR4x, u32Ch, TMR4_PWM_PDAR_IDX);
    PDBR = TMR4_PDR(TMR4x, u32Ch, TMR4_PWM_PDBR_IDX);
    PFSR = TMR4_PFSR(TMR4x, u32Ch);

    /* Set POCR register to reset value */
    WRITE_REG16(*POCR, TMR4_POCR_RST_VALUE);

    /* Set RCSR register */
    RCSRValue = (TMR4_RCSR_RTSx_MASK(u32Ch) | TMR4_RCSR_RTICx_MASK(u32Ch));
    MODIFY_REG(*RCSR, TMR4_RCSR_MASK(u32Ch), RCSRValue);

    /* Set PDAR/PDBR register to reset value */
    WRITE_REG16(*PDAR, 0U);
    WRITE_REG16(*PDBR, 0U);

    /* Set POCR register to reset value */
    WRITE_REG16(*PFSR, 0U);

    /* Set abnormal pin status to reset value */
    TMR4_PWM_SetAbnormalPinStatus(TMR4x, ((u32Ch << 1) + 0UL), TMR4_PWM_ABNORMAL_PIN_HIZ);
    TMR4_PWM_SetAbnormalPinStatus(TMR4x, ((u32Ch << 1) + 1UL), TMR4_PWM_ABNORMAL_PIN_HIZ);

    /* Set port output mode to reset value */
    TMR4_PWM_SetPortOutputMode(TMR4x, ((u32Ch << 1) + 0UL), TMR4_PWM_PIN_OUTPUT_OS);
    TMR4_PWM_SetPortOutputMode(TMR4x, ((u32Ch << 1) + 1UL), TMR4_PWM_PIN_OUTPUT_OS);
}

/**
 * @brief  Set TMR4 PWM clock division
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] u16Div                  TMR4 PWM internal clock division
 *         This parameter can be one of the macros group @ref TMR4_PWM_Clock_Division
 *           @arg TMR4_PWM_CLK_DIV1:    CLK
 *           @arg TMR4_PWM_CLK_DIV2:    CLK/2
 *           @arg TMR4_PWM_CLK_DIV4:    CLK/4
 *           @arg TMR4_PWM_CLK_DIV8:    CLK/8
 *           @arg TMR4_PWM_CLK_DIV16:   CLK/16
 *           @arg TMR4_PWM_CLK_DIV32:   CLK/32
 *           @arg TMR4_PWM_CLK_DIV64:   CLK/64
 *           @arg TMR4_PWM_CLK_DIV128:  CLK/128
 * @retval None
 */
void TMR4_PWM_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Div)
{
    __IO uint16_t *POCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_CLK_DIV(u16Div));

    /* Get pointer of current channel PWM register address */
    POCR = TMR4_POCR(TMR4x, u32Ch);

    MODIFY_REG16(*POCR, TMR4_POCR_DIVCK, u16Div);
}

/**
 * @brief  Set TMR4 PWM output polarity.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] u16Polarity             TMR4 PWM output polarity
 *         This parameter can be one of the macros group @ref TMR4_PWM_Polarity
 *           @arg TMR4_PWM_OXH_HOLD_OXL_HOLD: Output PWML and PWMH signals without changing the level
 *           @arg TMR4_PWM_OXH_INVT_OXL_INVT: Output both PWML and PWMH signals reversed
 *           @arg TMR4_PWM_OXH_INVT_OXL_HOLD: Output the PWMH signal reversed, outputs the PWML signal without changing the level
 *           @arg TMR4_PWM_OXH_HOLD_OXL_INVT: Output the PWMH signal without changing the level, Outputs the PWML signal reversed
 * @retval None
 */
void TMR4_PWM_SetPolarity(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Polarity)
{
    __IO uint16_t *POCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_POLARITY(u16Polarity));

    /* Get pointer of current channel PWM register address */
    POCR = TMR4_POCR(TMR4x, u32Ch);

    MODIFY_REG16(*POCR, TMR4_POCR_LVLS, u16Polarity);
}

/**
 * @brief  Start TMR4 PWM reload-timer
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @retval None
 */
void TMR4_PWM_StartReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    SET_REG_BIT(TMR4x->RCSR, TMR4_RCSR_RTEx_MASK(u32Ch));
}

/**
 * @brief  Stop TMR4 PWM reload-timer
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @retval None
 */
void TMR4_PWM_StopReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    SET_REG_BIT(TMR4x->RCSR, TMR4_RCSR_RTSx_MASK(u32Ch));
}

/**
 * @brief  Set TMR4 PWM filter count value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] u16Value                TMR4 PWM filter count value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetFilterCountValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint16_t *PFSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    PFSR = TMR4_PFSR(TMR4x, u32Ch);

    WRITE_REG16(*PFSR, u16Value);
}

/**
 * @brief  Set TMR4 PWM dead time count
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] u32DeadTimeIndex        TMR4 PWM dead time register index
 *         This parameter can be one of the macros group @ref TMR4_PWM_Dead_Time_Register_Index
 *           @arg TMR4_PWM_PDAR_IDX:    TMR4_PDARn
 *           @arg TMR4_PWM_PDBR_IDX:    TMR4_PDBRn
 * @param  [in] u16Value                TMR4 PWM dead time register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetDeadTimeValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint32_t u32DeadTimeIndex, uint16_t u16Value)
{
    __IO uint16_t *PDR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_DEADTIME_REG_IDX(u32DeadTimeIndex));

    /* Get pointer of current channel PWM register address */
    PDR = TMR4_PDR(TMR4x, u32Ch, u32DeadTimeIndex);

    WRITE_REG16(*PDR, u16Value);
}

/**
 * @brief  Get TMR4 PWM dead time count
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 PWM channel
 *         This parameter can be one of the macros group @ref TMR4_PWM_Channel
 * @param  [in] u32DeadTimeIndex        TMR4 PWM dead time register index
 *         This parameter can be one of the macros group @ref TMR4_PWM_Dead_Time_Register_Index
 *           @arg TMR4_PWM_PDAR_IDX:    TMR4_PDARn
 *           @arg TMR4_PWM_PDBR_IDX:    TMR4_PDBRn
 * @retval TMR4 PWM dead time register value
 */
uint16_t TMR4_PWM_GetDeadTimeValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint32_t u32DeadTimeIndex)
{
    __I uint16_t *PDR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_DEADTIME_REG_IDX(u32DeadTimeIndex));

    /* Get pointer of current channel PWM register address */
    PDR = TMR4_PDR(TMR4x, u32Ch, u32DeadTimeIndex);

    return READ_REG16(*PDR);
}

/**
 * @brief Set TMR4 PWM register TMR4_PSCR.OE bit effect time
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Time                 Effect time
 *         This parameter can be one of the macros group @ref TMR4_PWM_OE_Bit_Effect_Time
 *           @arg TMR4_PWM_OE_EFFECT_IMMED:        TMR4 PWM register TMR4_PSCR.OE bit immediate effect
 *           @arg TMR4_PWM_OE_EFFECT_COUNT_PEAK:   TMR4 PWM register TMR4_PSCR.OE bit effect when TMR4 counter count peak
 *           @arg TMR4_PWM_OE_EFFECT_COUNT_VALLEY: TMR4 PWM register TMR4_PSCR.OE bit effect when TMR4 counter count valley
 * @retval None
 */
void TMR4_PWM_SetOEEffectTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32Time)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_OE_EFFECT(u32Time));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_ODT, u32Time);
}

/**
 * @brief Enable or disable the TMR4 PWM main output by hardware after clear EMB event.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 *           @arg ENABLE:               The TMR4_PSCR.MOE bit automatically set to 1 by hardware to restore the PWM normal output.
 *           @arg DISABLE:              The TMR4_PSCR.MOE bit can only be set to 1 by software to restore the PWM normal output.
 * @retval None
 */
void TMR4_PWM_EmbHWMainOutputCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_AOE);
    } else {
        CLR_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_AOE);
    }
}

/**
 * @brief Enable or disable the TMR4 PWM main output function.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_PWM_MainOutputCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    } else {
        CLR_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    }
}

/**
 * @brief  Set TMR4 PWM port output mode
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32PwmPin               TMR4 PWM pin
 *         This parameter can be one of the macros group @ref TMR4_PWM_Pin
 * @param  [in] u32Mode                 The PWM port output mode
 *         This parameter can be one of the macros group @ref TMR4_PWM_Pin_Output_Mode
 *           @arg TMR4_PWM_PIN_OUTPUT_OS:     TIM4_<t>_Oxy(x=U/V/W,y=H/L) output polarity by specified OSxy
 *           @arg TMR4_PWM_PIN_OUTPUT_NORMAL: TIM4_<t>_Oxy(x=U/V/W,y=H/L) output normal PWM
 * @retval None
 */
void TMR4_PWM_SetPortOutputMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32PwmPin, uint32_t u32Mode)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_PIN(u32PwmPin));
    DDL_ASSERT(IS_TMR4_PWM_PIN_MD(u32Mode));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_OExy_MASK(u32PwmPin), TMR4_PSCR_OExy(u32PwmPin, u32Mode));
}

/**
 * @brief Set TMR4 PWM pin status when below conditions occur:1.EMB 2.MOE=0 3.MOE=1&OExy=0
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32PwmPin               TMR4 PWM pin
 *         This parameter can be one of the macros group @ref TMR4_PWM_Pin
 * @param  [in] u32PinStatus            TMR4 PWM pin status
 *         This parameter can be one of the macros group @ref TMR4_PWM_Abnormal_Pin_Status.
 * @retval None
 */
void TMR4_PWM_SetAbnormalPinStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32PwmPin, uint32_t u32PinStatus)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_ABNORMAL_PIN_STAT(u32PinStatus));
    DDL_ASSERT(IS_TMR4_PWM_PIN(u32PwmPin));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_OSxy_MASK(u32PwmPin), TMR4_PSCR_OSxy(u32PwmPin, u32PinStatus));
}

/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Global_Functions TMR4 Event Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_tmr4_evt_init_t to default values
 * @param  [in] pstcTmr4EventInit       Pointer to a @ref stc_tmr4_evt_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4EventInit value is NULL.
 */
int32_t TMR4_EVT_StructInit(stc_tmr4_evt_init_t *pstcTmr4EventInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4EventInit) {
        pstcTmr4EventInit->u16Mode = TMR4_EVT_MD_CMP;
        pstcTmr4EventInit->u16CompareValue = 0U;
        pstcTmr4EventInit->u16OutputEvent = TMR4_EVT_OUTPUT_EVT0;
        pstcTmr4EventInit->u16MatchCond = 0U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize TMR4 event
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] pstcTmr4EventInit       Pointer to a @ref stc_tmr4_evt_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTmr4EventInit value is NULL.
 */
int32_t TMR4_EVT_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_evt_init_t *pstcTmr4EventInit)
{
    uint16_t u16Value;
    __IO uint16_t *SCCR;
    __IO uint16_t *SCSR;
    __IO uint16_t *SCMR;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTmr4EventInit) {
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_EVT_MD(pstcTmr4EventInit->u16Mode));
        DDL_ASSERT(IS_TMR4_EVT_OUTPUT_EVT(pstcTmr4EventInit->u16OutputEvent));
        DDL_ASSERT(IS_TMR4_EVT_MATCH_COND(pstcTmr4EventInit->u16MatchCond));

        /* Get actual address of register list of current channel */
        SCCR = TMR4_SCCR(TMR4x, u32Ch);
        SCSR = TMR4_SCSR(TMR4x, u32Ch);
        SCMR = TMR4_SCMR(TMR4x, u32Ch);

        /* Set SCSR register */
        u16Value = (pstcTmr4EventInit->u16Mode | pstcTmr4EventInit->u16OutputEvent | pstcTmr4EventInit->u16MatchCond);
        WRITE_REG16(*SCSR, u16Value);

        /* Set SCMR register */
        WRITE_REG16(*SCMR, 0xFF00U);

        /* Set SCCR register: compare value */
        WRITE_REG16(*SCCR, pstcTmr4EventInit->u16CompareValue);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-initialize TMR4 PWM
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @retval None
 */
void TMR4_EVT_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *SCCR;
    __IO uint16_t *SCSR;
    __IO uint16_t *SCMR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    SCCR = TMR4_SCCR(TMR4x, u32Ch);
    SCSR = TMR4_SCSR(TMR4x, u32Ch);
    SCMR = TMR4_SCMR(TMR4x, u32Ch);

    /* Configure default parameter */
    WRITE_REG16(*SCCR, 0x0U);
    WRITE_REG16(*SCSR, 0x0000U);
    WRITE_REG16(*SCMR, TMR4_SCMR_RST_VALUE);
}

/**
 * @brief  Set TMR4 event delay object
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16Object               TMR4 event delay object
 *         This parameter can be one of the macros group @ref TMR4_Event_Delay_Object
 *           @arg TMR4_EVT_DELAY_OCCRXH: TMR4 event delay object - OCCRxh
 *           @arg TMR4_EVT_DELAY_OCCRXL: TMR4 event delay object - OCCRxl
 * @retval None
 */
void TMR4_EVT_SetDelayObject(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Object)
{
    __IO uint16_t *SCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_DELAY_OBJECT(u16Object));

    /* Get actual address of register list of current channel */
    SCSR = TMR4_SCSR(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*SCSR, TMR4_SCSR_EVTDS, u16Object);
}

/**
 * @brief  Set TMR4 event trigger event.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16MaskTime             Mask times
 *         This parameter can be one of the macros group @ref TMR4_Event_Mask_Times
 *           @arg TMR4_EVT_MASK0:       Mask 0 times
 *           @arg TMR4_EVT_MASK1:       Mask 1 times
 *           @arg TMR4_EVT_MASK2:       Mask 2 times
 *           @arg TMR4_EVT_MASK3:       Mask 3 times
 *           @arg TMR4_EVT_MASK4:       Mask 4 times
 *           @arg TMR4_EVT_MASK5:       Mask 5 times
 *           @arg TMR4_EVT_MASK6:       Mask 6 times
 *           @arg TMR4_EVT_MASK7:       Mask 7 times
 *           @arg TMR4_EVT_MASK8:       Mask 8 times
 *           @arg TMR4_EVT_MASK9:       Mask 9 times
 *           @arg TMR4_EVT_MASK10:      Mask 10 times
 *           @arg TMR4_EVT_MASK11:      Mask 11 times
 *           @arg TMR4_EVT_MASK12:      Mask 12 times
 *           @arg TMR4_EVT_MASK13:      Mask 13 times
 *           @arg TMR4_EVT_MASK14:      Mask 14 times
 *           @arg TMR4_EVT_MASK15:      Mask 15 times
 * @retval None
 */
void TMR4_EVT_SetMaskTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16MaskTime)
{
    __IO uint16_t *SCMR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_MASK(u16MaskTime));

    /* Get actual address of register list of current channel */
    SCMR = TMR4_SCMR(TMR4x, u32Ch);

    /* Set SCMR register */
    MODIFY_REG16(*SCMR, TMR4_SCMR_AMC, u16MaskTime);
}

/**
 * @brief  Get TMR4 event SCCR register value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @retval Returned value can be one of the macros group @ref TMR4_Event_Mask_Times
 *           - TMR4_EVT_MASK0:          Mask 0 times
 *           - TMR4_EVT_MASK1:          Mask 1 times
 *           - TMR4_EVT_MASK2:          Mask 2 times
 *           - TMR4_EVT_MASK3:          Mask 3 times
 *           - TMR4_EVT_MASK4:          Mask 4 times
 *           - TMR4_EVT_MASK5:          Mask 5 times
 *           - TMR4_EVT_MASK6:          Mask 6 times
 *           - TMR4_EVT_MASK7:          Mask 7 times
 *           - TMR4_EVT_MASK8:          Mask 8 times
 *           - TMR4_EVT_MASK9:          Mask 9 times
 *           - TMR4_EVT_MASK10:         Mask 10 times
 *           - TMR4_EVT_MASK11:         Mask 11 times
 *           - TMR4_EVT_MASK12:         Mask 12 times
 *           - TMR4_EVT_MASK13:         Mask 13 times
 *           - TMR4_EVT_MASK14:         Mask 14 times
 *           - TMR4_EVT_MASK15:         Mask 15 times
 */
uint16_t TMR4_EVT_GetMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *SCMR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    SCMR = TMR4_SCMR(TMR4x, u32Ch);

    return READ_REG16_BIT(*SCMR, TMR4_SCMR_AMC);
}

/**
 * @brief  Set TMR4 event compare value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16Value                SCCR register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_EVT_SetCompareValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint16_t *SCCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    SCCR = TMR4_SCCR(TMR4x, u32Ch);

    /* Set SCCR register */
    WRITE_REG16(*SCCR, u16Value);
}

/**
 * @brief  Get TMR4 event compare value
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @retval SCCR register value
 */
uint16_t TMR4_EVT_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *SCCR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    SCCR = TMR4_SCCR(TMR4x, u32Ch);

    return READ_REG16(*SCCR);
}

/**
 * @brief  Set TMR4 output event
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16Event                TMR4 event output event
 *         This parameter can be one of the macros group @ref TMR4_Event_Output_Event
 * @retval None
 */
void TMR4_EVT_SetOutputEvent(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Event)
{
    __IO uint16_t *SCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_OUTPUT_EVT(u16Event));

    /* Get actual address of register list of current channel */
    SCSR = TMR4_SCSR(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*SCSR, TMR4_SCSR_EVTOS, u16Event);
}

/**
 * @brief  Set the SCCR&SCMR buffer transfer condition
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16BufCond              The buffer transfer condition
 *         This parameter can be one of the macros group @ref TMR4_Event_Buffer_Transfer_Condition
 *           @arg TMR4_EVT_BUF_COND_IMMED:       Register SCCR&SCMR buffer transfer when writing to the SCCR&SCMR register
 *           @arg TMR4_EVT_BUF_COND_VALLEY:      Register SCCR&SCMR buffer transfer when counter count valley
 *           @arg TMR4_EVT_BUF_COND_PEAK:        Register SCCR&SCMR buffer transfer when counter count peak
 *           @arg TMR4_EVT_BUF_COND_PEAK_VALLEY: Register SCCR&SCMR buffer transfer when counter count peak or valley
 * @retval None
 */
void TMR4_EVT_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16BufCond)
{
    __IO uint16_t *SCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_BUF_COND(u16BufCond));

    /* Get actual address of register list of current channel */
    SCSR = TMR4_SCSR(TMR4x, u32Ch);

    MODIFY_REG16(*SCSR, TMR4_SCSR_BUFEN, u16BufCond);
}

/**
 * @brief  Enable or disable the buffer interval response function of TMR4 event.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_EVT_BufIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    __IO uint16_t *SCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get actual address of register list of current channel */
    SCSR = TMR4_SCSR(TMR4x, u32Ch);

    if (ENABLE == enNewState) {
        SET_REG16_BIT(*SCSR, TMR4_SCSR_LMC);
    } else {
        CLR_REG16_BIT(*SCSR, TMR4_SCSR_LMC);
    }
}

/**
 * @brief  Enable or disable the specified interval response of TMR4 event.
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16MaskType             The specified mask compare type of TMR4 event
 *         This parameter can be any composed value of the macros group @ref TMR4_Event_Mask
 *           @arg TMR4_EVT_MASK_VALLEY: Compare with the counter valley interrupt mask counter
 *           @arg TMR4_EVT_MASK_PEAK:   Compare with the counter peak interrupt mask counter
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_EVT_EventIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch,
                                       uint16_t u16MaskType, en_functional_state_t enNewState)
{
    __IO uint16_t *SCMR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_MASK_TYPE(u16MaskType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get actual address of register list of current channel */
    SCMR = TMR4_SCMR(TMR4x, u32Ch);

    if (ENABLE == enNewState) {
        SET_REG16_BIT(*SCMR, u16MaskType);
    } else {
        CLR_REG16_BIT(*SCMR, u16MaskType);
    }
}

/**
 * @brief  Enable or disable the specified count compare type of TMR4 event
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u32Ch                   TMR4 event channel
 *         This parameter can be one of the macros group @ref TMR4_Event_Channel
 * @param  [in] u16Cond                 The specified count compare type of TMR4 event
 *         This parameter can be any composed value of the macros group @ref TMR4_Event_Match_Condition
 *           @arg TMR4_EVT_MATCH_CNT_UP:     Start event operate when match with SCCR&SCMR and TMR4 counter count up
 *           @arg TMR4_EVT_MATCH_CNT_DOWN:   Start event operate when match with SCCR&SCMR and TMR4 counter count down
 *           @arg TMR4_EVT_MATCH_CNT_VALLEY: Start event operate when match with SCCR&SCMR and TMR4 counter count valley
 *           @arg TMR4_EVT_MATCH_CNT_PEAK:   Start event operate when match with SCCR&SCMR and TMR4 counter count peak
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR4_EVT_MatchCondCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState)
{
    __IO uint16_t *SCSR;

    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_EVT_MATCH_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get actual address of register list of current channel */
    SCSR = TMR4_SCSR(TMR4x, u32Ch);

    if (ENABLE == enNewState) {
        SET_REG16_BIT(*SCSR, u16Cond);
    } else {
        CLR_REG16_BIT(*SCSR, u16Cond);
    }
}

/**
 * @brief  Set TMR4 event signal output to port
 * @param  [in] TMR4x                   Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4 or CM_TMR4_x: TMR4 unit instance register base
 * @param  [in] u16Signal               TMR4 event signal selection
 *         This parameter can be one of the macros group @ref TMR4_Event_Output_Signal
 * @retval None
 */
void TMR4_EVT_SetOutputEventSignal(CM_TMR4_TypeDef *TMR4x, uint16_t u16Signal)
{
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_EVT_OUTPUT_SIGNAL(u16Signal));

    MODIFY_REG16(TMR4x->SCER, TMR4_SCER_EVTRS, u16Signal);
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* LL_TMR4_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
