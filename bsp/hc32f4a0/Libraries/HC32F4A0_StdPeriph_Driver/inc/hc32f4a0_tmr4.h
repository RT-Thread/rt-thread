/**
 *******************************************************************************
 * @file  hc32f4a0_tmr4.h
 * @brief This file contains all the functions prototypes of the TMR4(Timer4) 
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-15       Hongjh          Modify macro define for TMR4 SEVT match mask.
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
#ifndef __HC32F4A0_TMR4_H__
#define __HC32F4A0_TMR4_H__

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
 * @addtogroup DDL_TMR4
 * @{
 */

#if (DDL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR4_Global_Types TMR4 Global Types
 * @{
 */

/**
 * @brief TMR4 Counter(CNT) function initialization configuration
 */
typedef struct
{
    uint16_t u16CycleVal;       /*!< TMR4 count cycle value.
                                     This parameter can be a value of half-word */

    uint16_t u16CntMode;        /*!< TMR4 count mode.
                                     This parameter can be a value of @ref TMR4_CNT_Mode */

    uint16_t u16ClkSrc;         /*!< TMR4 count clock source.
                                     This parameter can be a value of @ref TMR4_CNT_Clock_Source */

    uint16_t u16PclkDiv;        /*!< TMR4 count PCLK clock division. The PCLK division function is valid when clock source is PCLK
                                     This parameter can be a value of @ref TMR4_CNT_PCLK_Division */

    uint16_t u16ZeroIntMask;    /*!< TMR4 count zero interrupt mask times.
                                     This parameter can be a value of @ref TMR4_CNT_Interrupt_Mask_Times */

    uint16_t u16PeakIntMask;    /*!< TMR4 count peak interrupt mask times.
                                     This parameter can be a value of @ref TMR4_CNT_Interrupt_Mask_Times */

    uint16_t u16BufState;       /*!< TMR4 count buffer state.
                                    This parameter can be a value of @ref TMR4_CNT_Buffer_State */
} stc_tmr4_cnt_init_t;

/**
 * @brief The configuration of OCO high channel OCMR field (OUH/OVH/OWH)
 */
typedef struct
{
    uint16_t OCFDCH : 1;    /*!< OCMRxh b0 High channel's OCF status when high channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint16_t OCFPKH : 1;    /*!< OCMRxh b1 High channel's OCF status when high channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint16_t OCFUCH : 1;    /*!< OCMRxh b2 High channel's OCF status when high channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint16_t OCFZRH : 1;    /*!< OCMRxh b3 High channel's OCF status when high channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint16_t OPDCH  : 2;    /*!< OCMRxh b5~b4 High channel's OP output status when high channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint16_t OPPKH  : 2;    /*!< OCMRxh b7~b6 High channel's OP output status when high channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint16_t OPUCH  : 2;    /*!< OCMRxh b9~b8 High channel's OP output status when high channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint16_t OPZRH  : 2;    /*!< OCMRxh b11~b10 High channel's OP output status when high channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint16_t OPNPKH : 2;    /*!< OCMRxh b13~b12 High channel's OP output status when high channel match doesn't occur at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint16_t OPNZRH : 2;    /*!< OCMRxh b15~b14 High channel's OP output status when high channel match doesn't occur at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
} stc_tmr4_oco_ocmrh_field_t;

/**
 * @brief The configuration of OCO high channel(OUH/OVH/OWH)
 */
typedef struct
{
    union
    {
        uint16_t OCMRx;                     /*!< OCMRxH(x=U/V/W) register */

        stc_tmr4_oco_ocmrh_field_t OCMRx_f; /*!< OCMRxH(x=U/V/W) register struct field bit
                                                 This details refer @ref stc_tmr4_oco_ocmrh_field_t */
    };

    uint16_t u16ExtendMatch;                /*!< Extend the match condition
                                                 This parameter can be a value of @ref TMR4_OCO_Extend_Match_Condtion */
} stc_oco_high_ch_compare_mode_t;

/**
 * @brief The configuration of OCO low channel OCMR field (OUL/OVL/OWL)
 */
typedef struct
{
    uint32_t OCFDCL  : 1;   /*!< OCMRxl b0 Low channel's OCF status when low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint32_t OCFPKL  : 1;   /*!< OCMRxl b1 Low channel's OCF status when low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint32_t OCFUCL  : 1;   /*!< OCMRxl b2 Low channel's OCF status when low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint32_t OCFZRL  : 1;   /*!< OCMRxl b3 Low channel's OCF status when low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */

    uint32_t OPDCL   : 2;   /*!< OCMRxl b5~b4 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t OPPKL   : 2;   /*!< OCMRxl b7~b6 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t OPUCL   : 2;   /*!< OCMRxl b9~b8 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t OPZRL   : 2;   /*!< OCMRxl b11~b10 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t OPNPKL  : 2;   /*!< OCMRxl b13~b12 Low channel's OP output status when high channel not match and low channel not match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t OPNZRL  : 2;   /*!< OCMRxl b15~b14 Low channel's OP output status when high channel not match and low channel not match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPNDCL : 2;   /*!< OCMRxl b17~b16 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT is coutning down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPNUCL : 2;   /*!< OCMRxl b19~b18 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPDCL  : 2;   /*!< OCMRxl b21~b20 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPPKL  : 2;   /*!< OCMRxl b23~b22 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPUCL  : 2;   /*!< OCMRxl b25~b24 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPZRL  : 2;   /*!< OCMRxl b27~b26 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPNPKL : 2;   /*!< OCMRxl b29~b28 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */

    uint32_t EOPNZRL : 2;   /*!< OCMRxl b31~b30 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
} stc_tmr4_oco_ocmrl_field_t;

/**
 ** \brief The configuration of OCO low channel(OUL/OVL/OWL)
 */
typedef struct
{
    union
    {
        uint32_t OCMRx;                     /*!< OCMRxL(x=U/V/W) register */

        stc_tmr4_oco_ocmrl_field_t OCMRx_f; /*!< OCMRxL(x=U/V/W) register struct field bit
                                                 This details refer @ref stc_tmr4_oco_ocmrl_field_t */
    };

    uint16_t u16ExtendMatch;                /*!< Extend the match condition
                                                 This parameter can be a value of @ref TMR4_OCO_Extend_Match_Condtion */
} stc_oco_low_ch_compare_mode_t;

/**
 * @brief TMR4 Output Compare(OCO) initialization configuration
 */
typedef struct
{
    uint16_t u16CompareVal;         /*!< TMR4 OCO compare match value.
                                         This parameter can be a value of half-word */

    uint16_t u16OccrBufMode;        /*!< Buffer register function of OCCR
                                         This parameter can be a value of @ref TMR4_OCO_OCCR_Buffer_Mode */

    uint16_t u16OccrLinkTransfer;   /*!< Enable or disable the OCCR buffer linked transfer with the CNT interrupt mask counter
                                         This parameter can be a value of @ref TMR4_OCO_OCCR_Link_Transfer */

    uint16_t u16OcmrBufMode;        /*!< Buffer register function of OCMR
                                         This parameter can be a value of @ref TMR4_OCO_OCMR_Buffer_Mode */

    uint16_t u16OcmrLinkTransfer;   /*!< Enable or disable the OCMR buffer linked transfer with the CNT interrupt mask counter
                                         This parameter can be a value of @ref TMR4_OCO_OCMR_Link_Transfer */

    uint16_t u16OcoInvalidOp;       /*!< Port output polarity when OCO is invalid
                                         This parameter can be a value of @ref TMR4_OCO_Invalid_Output_Polarity */

    uint16_t u16OcoCmd;             /*!< Enable or disable OCO function
                                         This parameter can be a value of @ref TMR4_OCO_State */
} stc_tmr4_oco_init_t;

/**
 * @brief TMR4 PWM initialization configuration
 */
typedef struct
{
    uint16_t u16Mode;               /*!< Select PWM mode
                                         This parameter can be a value of @ref TMR4_PWM_Mode */

    uint16_t u16PclkDiv;            /*!< PCLK clock division of PWM timer. The PCLK division function is valid when clock source is PCLK
                                         This parameter can be a value of @ref TMR4_PWM_PCLK_Division */

    uint16_t u16TransformOcoPol;    /*!< TMR4 PWM transform OCO polarity
                                         This parameter can be a value of @ref TMR4_PWM_Transform_OCO_Polarity */

    uint32_t u32OxHPortOutMode;     /*!< TIM4_<t>_OxH port output mode
                                         This parameter can be a value of @ref TMR4_PWM_Port_Output_Mode */

    uint32_t u32EmbOxHPortState;    /*!< TIM4_<t>_OxH port state
                                         This parameter can be a value of @ref TMR4_PWM_EMB_Port_State */

    uint32_t u32OxLPortOutMode;     /*!< TIM4_<t>_OxL port output mode
                                         This parameter can be a value of @ref TMR4_PWM_Port_Output_Mode */

    uint32_t u32EmbOxLPortState;    /*!< TIM4_<t>_OxL port state
                                         This parameter can be a value of @ref TMR4_PWM_EMB_Port_State */
} stc_tmr4_pwm_init_t;

/**
 * @brief TMR4 Special-EVT initialization configuration
 */
typedef struct
{
    uint16_t u16CompareVal;         /*!< TMR4 Special-EVT compare match value.
                                         This parameter can be a value of half-word */

    uint16_t u16Mode;               /*!< Configure TMR4 Special-EVT Running mode
                                         This parameter can be a value of @ref TMR4_SEVT_Mode */

    uint16_t u16OutpuEvent;         /*!< TMR4 Special-EVT output event
                                         This parameter can be a value of @ref TMR4_SEVT_Output_Event */

    uint16_t u16BufMode;            /*!< Buffer mode
                                         This parameter can be a value of @ref TMR4_SEVT_Buffer_Mode */

    uint16_t u16LinkTransfer;       /*!< Enable or disable the buffer linked transfer with the CNT interrupt mask counter
                                         This parameter can be a value of @ref TMR4_SEVT_Link_Transfer */

    uint16_t u16UpMatchCmd;         /*!< Enable or disable trigger signal when match with SCCR&SCMR and TMR4 CNT count up
                                         This parameter can be a value of @ref TMR4_SEVT_Up_Selection */

    uint16_t u16DownMatchCmd;       /*!< Enable or disable trigger signal when match with SCCR&SCMR and TMR4 CNT count down
                                         This parameter can be a value of @ref TMR4_SEVT_Down_Selection */

    uint16_t u16PeakMatchCmd;       /*!< Enable or disable trigger signal when match with SCCR&SCMR and TMR4 CNT count peak
                                         This parameter can be a value of @ref TMR4_SEVT_Peak_Selection */

    uint16_t u16ZeroMatchCmd;       /*!< Enable or disable trigger signal when match with SCCR&SCMR and TMR4 CNT count zero
                                         This parameter can be a value of @ref TMR4_SEVT_Zero_Selection */

    uint16_t u16ZeroMatchMaskCmd;   /*!< Enable or disable perform to compare with the CNT zero interrupt mask counter
                                         This parameter can be a value of @ref TMR4_SEVT_Zero_Match_Mask_Selection */

    uint16_t u16PeakMatchMaskCmd;   /*!< Enable or disable perform to compare with the CNT peak interrupt mask counter
                                         This parameter can be a value of @ref TMR4_SEVT_Peak_Match_Mask_Selection */

    uint16_t u16MaskTimes;          /*!< Specifies start time by the value to be compared with the CNT interrupt mask counter */
} stc_tmr4_sevt_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR4_Global_Macros TMR4 Global Macros
 * @{
 */

/**
 * @defgroup TMR4_CNT_Macros TMR4 Counter Macros
 * @{
 */

/** @defgroup TMR4_CNT_PCLK_Division TMR4 Counter PCLK Clock Division
 * @{
 */
#define TMR4_CNT_PCLK_DIV1                      (0U)                    /*!< PCLK      */
#define TMR4_CNT_PCLK_DIV2                      (TMR4_CCSR_CKDIV_0)     /*!< PCLK/2    */
#define TMR4_CNT_PCLK_DIV4                      (TMR4_CCSR_CKDIV_1)     /*!< PCLK/4    */
#define TMR4_CNT_PCLK_DIV8                      (TMR4_CCSR_CKDIV_1 | \
                                                 TMR4_CCSR_CKDIV_0)     /*!< PCLK/8    */
#define TMR4_CNT_PCLK_DIV16                     (TMR4_CCSR_CKDIV_2)     /*!< PCLK/16   */
#define TMR4_CNT_PCLK_DIV32                     (TMR4_CCSR_CKDIV_2 | \
                                                 TMR4_CCSR_CKDIV_0)     /*!< PCLK/32   */
#define TMR4_CNT_PCLK_DIV64                     (TMR4_CCSR_CKDIV_2 | \
                                                 TMR4_CCSR_CKDIV_1)     /*!< PCLK/64   */
#define TMR4_CNT_PCLK_DIV128                    (TMR4_CCSR_CKDIV_2 | \
                                                 TMR4_CCSR_CKDIV_1 | \
                                                 TMR4_CCSR_CKDIV_0)     /*!< PCLK/128  */
#define TMR4_CNT_PCLK_DIV256                    (TMR4_CCSR_CKDIV_3)     /*!< PCLK/256  */
#define TMR4_CNT_PCLK_DIV512                    (TMR4_CCSR_CKDIV_3 | \
                                                 TMR4_CCSR_CKDIV_0)     /*!< PCLK/512  */
#define TMR4_CNT_PCLK_DIV1024                   (TMR4_CCSR_CKDIV_3 | \
                                                 TMR4_CCSR_CKDIV_1)     /*!< PCLK/1024 */
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Mode TMR4 Counter Mode
 * @{
 */
#define TMR4_CNT_MODE_SAWTOOTH_WAVE             (0U)
#define TMR4_CNT_MODE_TRIANGLE_WAVE             (TMR4_CCSR_MODE)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Flag TMR4 Counter Flag
 * @{
 */
#define TMR4_CNT_FLAG_PEAK                      (TMR4_CCSR_IRQPF)
#define TMR4_CNT_FLAG_ZERO                      (TMR4_CCSR_IRQZF)
#define TMR4_CNT_FLAG_MASK                      (TMR4_CCSR_IRQPF | TMR4_CCSR_IRQZF)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Interrupt TMR4 Counter Interrupt
 * @{
 */
#define TMR4_CNT_INT_PEAK                       (TMR4_CCSR_IRQPEN)
#define TMR4_CNT_INT_ZERO                       (TMR4_CCSR_IRQZEN)
#define TMR4_CNT_INT_MASK                       (TMR4_CCSR_IRQPEN | TMR4_CCSR_IRQZEN)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Buffer_State TMR4 CNT Buffer State
 * @{
 */
#define TMR4_CNT_BUFFER_DISABLE                 (0U)                /*!< Disable TMR4 counter buffer function */
#define TMR4_CNT_BUFFER_ENABLE                  (TMR4_CCSR_BUFEN)   /*!< Enable TMR4 counter buffer function */
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Clock_Source TMR4 Count Clock Source
 * @{
 */
#define TMR4_CNT_PCLK                           (0U)
#define TMR4_CNT_EXTCLK                         (TMR4_CCSR_ECKEN)
/**
 * @}
 */

/** @defgroup TMR4_CNT_Interrupt_Mask_Times TMR4 Counter Interrupt Mask Times
 * @{
 */
#define TMR4_CNT_INT_MASK_0                     (0U)    /*!< Counter interrupt flag is always set(not masked) for every counter count at "0x0000" */
#define TMR4_CNT_INT_MASK_1                     (1U)    /*!< Counter interrupt flag is set once for 2 for every counter counts at "0x0000" (skiping 1 count) */
#define TMR4_CNT_INT_MASK_2                     (2U)    /*!< Counter interrupt flag is set once for 3 for every counter counts at "0x0000" (skiping 2 count) */
#define TMR4_CNT_INT_MASK_3                     (3U)    /*!< Counter interrupt flag is set once for 4 for every counter counts at "0x0000" (skiping 3 count) */
#define TMR4_CNT_INT_MASK_4                     (4U)    /*!< Counter interrupt flag is set once for 5 for every counter counts at "0x0000" (skiping 4 count) */
#define TMR4_CNT_INT_MASK_5                     (5U)    /*!< Counter interrupt flag is set once for 6 for every counter counts at "0x0000" (skiping 5 count) */
#define TMR4_CNT_INT_MASK_6                     (6U)    /*!< Counter interrupt flag is set once for 7 for every counter counts at "0x0000" (skiping 6 count) */
#define TMR4_CNT_INT_MASK_7                     (7U)    /*!< Counter interrupt flag is set once for 8 for every counter counts at "0x0000" (skiping 7 count) */
#define TMR4_CNT_INT_MASK_8                     (8U)    /*!< Counter interrupt flag is set once for 9 for every counter counts at "0x0000" (skiping 8 count) */
#define TMR4_CNT_INT_MASK_9                     (9U)    /*!< Counter interrupt flag is set once for 10 for every counter counts at "0x0000" (skiping 9 count) */
#define TMR4_CNT_INT_MASK_10                    (10U)   /*!< Counter interrupt flag is set once for 11 for every counter counts at "0x0000" (skiping 10 count) */
#define TMR4_CNT_INT_MASK_11                    (11U)   /*!< Counter interrupt flag is set once for 12 for every counter counts at "0x0000" (skiping 11 count) */
#define TMR4_CNT_INT_MASK_12                    (12U)   /*!< Counter interrupt flag is set once for 13 for every counter counts at "0x0000" (skiping 12 count) */
#define TMR4_CNT_INT_MASK_13                    (13U)   /*!< Counter interrupt flag is set once for 14 for every counter counts at "0x0000" (skiping 13 count) */
#define TMR4_CNT_INT_MASK_14                    (14U)   /*!< Counter interrupt flag is set once for 15 for every counter counts at "0x0000" (skiping 14 count) */
#define TMR4_CNT_INT_MASK_15                    (15U)   /*!< Counter interrupt flag is set once for 16 for every counter counts at "0x0000" (skiping 15 count) */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Macros TMR4 Output Compare Macros
 * @{
 */

/** @defgroup TMR4_OCO_Channel TMR4 OCO Channel
 * @{
 */
#define TMR4_OCO_UH                             (0UL)   /*!< TMR4 OCO channel:UH */
#define TMR4_OCO_UL                             (1UL)   /*!< TMR4 OCO channel:UL */
#define TMR4_OCO_VH                             (2UL)   /*!< TMR4 OCO channel:VH */
#define TMR4_OCO_VL                             (3UL)   /*!< TMR4 OCO channel:VL */
#define TMR4_OCO_WH                             (4UL)   /*!< TMR4 OCO channel:WH */
#define TMR4_OCO_WL                             (5UL)   /*!< TMR4 OCO channel:WL */
/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_State TMR4 OCO State
 * @{
 */
#define TMR4_OCO_DISABLE                        (0U)                /*!< Disable TMR4 OCO output */
#define TMR4_OCO_ENABLE                         (TMR4_OCSR_OCEH)    /*!< Enable TMR4 OCO output */
/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Invalid_Output_Polarity TMR4 OCO Invalid Output Polarity
 * @{
 */
#define TMR4_OCO_INVAILD_OP_LOW                 (0U)                /*!< TMR4 OCO Output low level when OCO is invalid */
#define TMR4_OCO_INVAILD_OP_HIGH                (TMR4_OCSR_OCPH)    /*!< TMR4 OCO Output high level when OCO is invalid */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Extend_Match_Condtion TMR4 OCO Extend Match Condtion
 * @{
 */
#define TMR4_OCO_EXTEND_MATCH_DISABLE           (0U)                /*!< Disable TMR4 OCO extend match function */
#define TMR4_OCO_EXTEND_MATCH_ENABLE            (TMR4_OCER_MCECH)   /*!< Enable TMR4 OCO extend match function */
/**
 * @}
 */

/** @defgroup TMR4_OCO_OCCR_Link_Transfer TMR4 OCO OCCR Link Transfer
 * @{
 */
#define TMR4_OCO_OCCR_LINK_TRANSFER_DISABLE     (0U)                /*!< Disable the register OCCR buffer link transfer function */
#define TMR4_OCO_OCCR_LINK_TRANSFER_ENABLE      (TMR4_OCER_LMCH)    /*!< Register OCCR buffer transfer when the value is both 0 and CPSR and ZIC/PIC is 0 */
/**
 * @}
 */

/** @defgroup TMR4_OCO_OCCR_Buffer_Mode TMR4 OCO OCCR Buffer Mode
 * @{
 */
#define TMR4_OCO_OCCR_BUF_DISABLE               (0U)                    /*!< Disable the register OCCR buffer function */
#define TMR4_OCO_OCCR_BUF_CNT_ZERO              (TMR4_OCER_CHBUFEN_0)   /*!< Register OCCR buffer transfer when counter value is 0x0000 */
#define TMR4_OCO_OCCR_BUF_CNT_PEAK              (TMR4_OCER_CHBUFEN_1)   /*!< Register OCCR buffer transfer when counter value is CPSR */
#define TMR4_OCO_OCCR_BUF_CNT_ZERO_OR_PEAK      (TMR4_OCER_CHBUFEN)     /*!< Register OCCR buffer transfer when the value is both 0 and CPSR */
/**
 * @}
 */

/** @defgroup TMR4_OCO_OCMR_Link_Transfer TMR4 OCO OCMR Link Transfer
 * @{
 */
#define TMR4_OCO_OCMR_LINK_TRANSFER_DISABLE     (0x0000U)           /*!< Disable the register OCMR buffer link transfer function */
#define TMR4_OCO_OCMR_LINK_TRANSFER_ENABLE      (TMR4_OCER_LMMH)    /*!< Register OCMR buffer transfer when the value is both 0 and CPSR and ZIC/PIC is 0 */
/**
 * @}
 */

/** @defgroup TMR4_OCO_OCMR_Buffer_Mode TMR4 OCO OCMR Buffer Mode
 * @{
 */
#define TMR4_OCO_OCMR_BUF_DISABLE               (0U)                    /*!< Disable the register OCCR buffer function */
#define TMR4_OCO_OCMR_BUF_CNT_ZERO              (TMR4_OCER_MHBUFEN_0)   /*!< Register OCMR buffer transfer when counter value is 0x0000 */
#define TMR4_OCO_OCMR_BUF_CNT_PEAK              (TMR4_OCER_MHBUFEN_1)   /*!< Register OCMR buffer transfer when counter value is CPSR */
#define TMR4_OCO_OCMR_BUF_CNT_ZERO_OR_PEAK      (TMR4_OCER_MHBUFEN)     /*!< Register OCMR buffer transfer when the value is both 0 and CPSR */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Cnt_Match_OCF_State TMR4 OCO Cnt Match OCF State
 * @{
 */
#define TMR4_OCO_OCF_HOLD                       (0U)                /*!< Hold OCF */
#define TMR4_OCO_OCF_SET                        (TMR4_OCMRH_OCFDCH) /*!< Set OCF */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Cnt_Match_Output_Polarity TMR4 OCO Cnt Match Output Polarity
 * @{
 */
#define TMR4_OCO_OP_HOLD                        (0U)    /*!< Hold output when the TMR4 OCO count match */
#define TMR4_OCO_OP_HIGH                        (1U)    /*!< Output high when the TMR4 OCO count match */
#define TMR4_OCO_OP_LOW                         (2U)    /*!< Output low when the TMR4 OCO count match */
#define TMR4_OCO_OP_INVERT                      (3U)    /*!< Invert output when the TMR4 OCO count match */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Macros TMR4 PWM Macros
 * @{
 */

/** @defgroup TMR4_PWM_Channel TMR4 PWM Channel
 * @{
 */
#define TMR4_PWM_U                              (0UL)   /*!< TMR4 PWM couple channel: U */
#define TMR4_PWM_V                              (1UL)   /*!< TMR4 PWM couple channel: V */
#define TMR4_PWM_W                              (2UL)   /*!< TMR4 PWM couple channel: W */
/**
 * @}
 */

/** @defgroup TMR4_PWM_Port TMR4 PWM Port
 * @{
 */
#define TMR4_PWM_PORT_OUH                       (0UL)   /*!< TMR4 PWM port: TIM4_<t>_OUH */
#define TMR4_PWM_PORT_OUL                       (1UL)   /*!< TMR4 PWM port: TIM4_<t>_OUL */
#define TMR4_PWM_PORT_OVH                       (2UL)   /*!< TMR4 PWM port: TIM4_<t>_OVH */
#define TMR4_PWM_PORT_OVL                       (3UL)   /*!< TMR4 PWM port: TIM4_<t>_OVL */
#define TMR4_PWM_PORT_OWH                       (4UL)   /*!< TMR4 PWM port: TIM4_<t>_OWH */
#define TMR4_PWM_PORT_OWL                       (5UL)   /*!< TMR4 PWM port: TIM4_<t>_OWL */
/**
 * @}
 */

/** @defgroup TMR4_PWM_PCLK_Division TMR4 PWM PCLK Clock Division
 * @{
 */
#define TMR4_PWM_PCLK_DIV1                      (0U)                    /*!< PCLK     */
#define TMR4_PWM_PCLK_DIV2                      (TMR4_POCR_DIVCK_0)     /*!< PCLK/2   */
#define TMR4_PWM_PCLK_DIV4                      (TMR4_POCR_DIVCK_1)     /*!< PCLK/4   */
#define TMR4_PWM_PCLK_DIV8                      (TMR4_POCR_DIVCK_1 | \
                                                 TMR4_POCR_DIVCK_0)     /*!< PCLK/8   */
#define TMR4_PWM_PCLK_DIV16                     (TMR4_POCR_DIVCK_2)     /*!< PCLK/16  */
#define TMR4_PWM_PCLK_DIV32                     (TMR4_POCR_DIVCK_2 | \
                                                 TMR4_POCR_DIVCK_0)     /*!< PCLK/32  */
#define TMR4_PWM_PCLK_DIV64                     (TMR4_POCR_DIVCK_2 | \
                                                 TMR4_POCR_DIVCK_1)     /*!< PCLK/64  */
#define TMR4_PWM_PCLK_DIV128                    (TMR4_POCR_DIVCK_2 | \
                                                 TMR4_POCR_DIVCK_1 | \
                                                 TMR4_POCR_DIVCK_0)     /*!< PCLK/128 */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Mode TMR4 PWM Mode
 * @{
 */
#define TMR4_PWM_THROUGH_MODE                   (0U)                /*!< Through mode */
#define TMR4_PWM_DEAD_TIMER_MODE                (TMR4_POCR_PWMMD_0) /*!< Dead timer mode */
#define TMR4_PWM_DEAD_TIMER_FILTER_MODE         (TMR4_POCR_PWMMD_1) /*!< Dead timer filter mode */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Transform_OCO_Polarity TMR4 PWM Transform OCO Polarity
 * @{
 */
#define TMR4_PWM_OP_OXH_HOLD_OXL_HOLD           (0U)                /*!< Output PWML and PWMH signals without changing the level */
#define TMR4_PWM_OP_OXH_INVERT_OXL_INVERT       (TMR4_POCR_LVLS_0)  /*!< Output both PWML and PWMH signals reversed */
#define TMR4_PWM_OP_OXH_INVERT_OXL_HOLD         (TMR4_POCR_LVLS_1)  /*!< Output the PWMH signal reversed, outputs the PWML signal without changing the level. */
#define TMR4_PWM_OP_OXH_HOLD_OXL_INVERT         (TMR4_POCR_LVLS)    /*!< Output the PWMH signal without changing the level, Outputs the PWML signal reversed. */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Port_Output_Mode TMR4 PWM Port Mode
 * @{
 */
#define TMR4_PWM_PORT_OUTPUT_OSxy               (0UL)               /*!< TIM4_<t>_Oxy output polarity by specified OSxy */
#define TMR4_PWM_PORT_OUTPUT_NORMAL             (TMR4_PSCR_OEUH)    /*!< TIM4_<t>_Oxy output normal PWM */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_EMB_Port_State TMR4 PWM EMB Port State
 * @{
 */
#define TMR4_PWM_EMB_PORT_OUTPUT_NORMAL         (0UL)               /*!< TIM4_<t>_Oxy output normal */
#define TMR4_PWM_EMB_PORT_OUTPUT_HIZ            (TMR4_PSCR_OSUH_0)  /*!< TIM4_<t>_Oxy output Hi-z */
#define TMR4_PWM_EMB_PORT_OUTPUT_LOW            (TMR4_PSCR_OSUH_1)  /*!< TIM4_<t>_Oxy output low level */
#define TMR4_PWM_EMB_PORT_OUTPUT_HIGH           (TMR4_PSCR_OSUH)    /*!< TIM4_<t>_Oxy output high level */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Port_Enable_Bit_Effective_Time TMR4 PWM Port Enable Bit Effective Time
 * @{
 */
#define TMR4_PWM_PORT_ENBIT_EFFECT_IMMEDIATE    (0UL)               /*!< TMR4 PWM Port Enable Bit Effective Time: immediate */
#define TMR4_PWM_PORT_ENBIT_EFFECT_CNTUVF       (TMR4_PSCR_ODT_1)   /*!< TMR4 PWM Port Enable Bit Effective Time: TMR4 counter underflow */
#define TMR4_PWM_PORT_ENBIT_EFFECT_CNTOVF       (TMR4_PSCR_ODT)     /*!< TMR4 PWM Port Enable Bit Effective Time: TMR4 counter overflow */
 /**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Macros TMR4 Special Event Macros
 * @{
 */

/** @defgroup TMR4_SEVT_Channel TMR4 SEVT Channel
 * @{
 */
#define TMR4_SEVT_UH                            (0UL)   /*!< TMR4 SEVT channel:UH */
#define TMR4_SEVT_UL                            (1UL)   /*!< TMR4 SEVT channel:UL */
#define TMR4_SEVT_VH                            (2UL)   /*!< TMR4 SEVT channel:VH */
#define TMR4_SEVT_VL                            (3UL)   /*!< TMR4 SEVT channel:VL */
#define TMR4_SEVT_WH                            (4UL)   /*!< TMR4 SEVT channel:WH */
#define TMR4_SEVT_WL                            (5UL)   /*!< TMR4 SEVT channel:WL */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Link_Transfer TMR4 SEVT Link Transfer
 * @{
 */
#define TMR4_SEVT_LINK_TRANSFER_DISABLE         (0U)            /*!< Disable the SEVT Link Transfer function */
#define TMR4_SEVT_LINK_TRANSFER_ENABLE          (TMR4_SCSR_LMC) /*!< Enable the SEVT Link Transfer function */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Down_Selection TMR4 SEVT Down Selection
 * @{
 */
#define TMR4_SEVT_DOWN_DISABLE                  (0U)            /*!< Disable trigger signal when match with SCCR&SCMR and TMR4 CNT count zero */
#define TMR4_SEVT_DOWN_ENABLE                   (TMR4_SCSR_DEN) /*!< Enable trigger signal when match with SCCR&SCMR and TMR4 CNT count down */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Up_Selection TMR4 SEVT Up Selection
 * @{
 */
#define TMR4_SEVT_UP_DISABLE                    (0U)            /*!< Disable trigger signal when match with SCCR&SCMR and TMR4 CNT count up */
#define TMR4_SEVT_UP_ENABLE                     (TMR4_SCSR_UEN) /*!< Enable trigger signal when match with SCCR&SCMR and TMR4 CNT count up */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Peak_Selection TMR4 SEVT Peak Selection
 * @{
 */
#define TMR4_SEVT_PEAK_DISABLE                  (0U)            /*!< Disable trigger signal when match with SCCR&SCMR and TMR4 CNT count peak */
#define TMR4_SEVT_PEAK_ENABLE                   (TMR4_SCSR_PEN) /*!< Enable trigger signal when match with SCCR&SCMR and TMR4 CNT count peak */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Zero_Selection TMR4 SEVT Zero Selection
 * @{
 */
#define TMR4_SEVT_ZERO_DISABLE                  (0U)            /*!< Disable trigger signal when match with SCCR&SCMR and TMR4 CNT count zero */
#define TMR4_SEVT_ZERO_ENABLE                   (TMR4_SCSR_ZEN) /*!< Enable trigger signal when match with SCCR&SCMR and TMR4 CNT count zero */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Zero_Match_Mask_Selection TMR4 SEVT Zero Match Mask Selection
 * @{
 */
#define TMR4_SEVT_ZERO_MATCH_MASK_DISABLE       (0U)             /*!< Disable perform to compare with the CNT zero interrupt mask counter */
#define TMR4_SEVT_ZERO_MATCH_MASK_ENABLE        (TMR4_SCMR_MZCE) /*!< Enable perform to compare with the CNT zero interrupt mask counter */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Peak_Match_Mask_Selection TMR4 SEVT Peak Match Mask Selection
 * @{
 */
#define TMR4_SEVT_PEAK_MATCH_MASK_DISABLE       (0U)             /*!< Disable perform to compare with the CNT peak interrupt mask counter */
#define TMR4_SEVT_PEAK_MATCH_MASK_ENABLE        (TMR4_SCMR_MPCE) /*!< Enable perform to compare with the CNT peak interrupt mask counter */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Buffer_Mode TMR4 SEVT Buffer Mode
 * @{
 */
#define TMR4_SEVT_BUF_DISABLE                   (0U)                /*!< Disable the register SCCR&SCMR buffer function */
#define TMR4_SEVT_BUF_CNT_ZERO                  (TMR4_SCSR_BUFEN_0) /*!< Register SCCR&SCMR buffer transfer when counter value is 0x0000 */
#define TMR4_SEVT_BUF_CNT_PEAK                  (TMR4_SCSR_BUFEN_1) /*!< Register SCCR&SCMR buffer transfer when counter value is CPSR */
#define TMR4_SEVT_BUF_CNT_ZERO_OR_PEAK          (TMR4_SCSR_BUFEN)   /*!< Register SCCR&SCMR buffer transfer when the value is both 0 and CPSR */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Output_Event TMR4 SEVT Output Event
 * @{
 */
#define TMR4_SEVT_OUTPUT_EVENT0                 (0U)                    /*!< TMR4 SEVT output special event 0 */
#define TMR4_SEVT_OUTPUT_EVENT1                 (TMR4_SCSR_EVTOS_0)     /*!< TMR4 SEVT output special event 1 */
#define TMR4_SEVT_OUTPUT_EVENT2                 (TMR4_SCSR_EVTOS_1)     /*!< TMR4 SEVT output special event 2 */
#define TMR4_SEVT_OUTPUT_EVENT3                 (TMR4_SCSR_EVTOS_1 | \
                                                 TMR4_SCSR_EVTOS_0)     /*!< TMR4 SEVT output special event 3 */
#define TMR4_SEVT_OUTPUT_EVENT4                 (TMR4_SCSR_EVTOS_2)     /*!< TMR4 SEVT output special event 4 */
#define TMR4_SEVT_OUTPUT_EVENT5                 (TMR4_SCSR_EVTOS_2 | \
                                                 TMR4_SCSR_EVTOS_0)     /*!< TMR4 SEVT output special event 5 */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Mode TMR4 SEVT Mode
 * @{
 */
#define TMR4_SEVT_MODE_COMPARE_TRIGGER          (0U)
#define TMR4_SEVT_MODE_DELAY_TRIGGER            (TMR4_SCSR_EVTMS)
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Delay_Object TMR4 SEVT Delay Object
 * @{
 */
#define TMR4_SEVT_DELAY_OCCRXH                  (0U)                /*!< TMR4 SEVT delay object: OCCRxh */
#define TMR4_SEVT_DELAY_OCCRXL                  (TMR4_SCSR_EVTDS)   /*!< TMR4 SEVT delay object: OCCRxl */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Mask_Times TMR4 SEVT Mask Times
 * @{
 */
#define TMR4_SEVT_MASK_0                        (0U)    /*!< Mask 0 time */
#define TMR4_SEVT_MASK_1                        (1U)    /*!< Mask 1 times */
#define TMR4_SEVT_MASK_2                        (2U)    /*!< Mask 2 times */
#define TMR4_SEVT_MASK_3                        (3U)    /*!< Mask 3 times */
#define TMR4_SEVT_MASK_4                        (4U)    /*!< Mask 4 times */
#define TMR4_SEVT_MASK_5                        (5U)    /*!< Mask 5 times */
#define TMR4_SEVT_MASK_6                        (6U)    /*!< Mask 6 times */
#define TMR4_SEVT_MASK_7                        (7U)    /*!< Mask 7 times */
#define TMR4_SEVT_MASK_8                        (8U)    /*!< Mask 8 times */
#define TMR4_SEVT_MASK_9                        (9U)    /*!< Mask 9 times */
#define TMR4_SEVT_MASK_10                       (10U)   /*!< Mask 10 times */
#define TMR4_SEVT_MASK_11                       (11U)   /*!< Mask 11 times */
#define TMR4_SEVT_MASK_12                       (12U)   /*!< Mask 12 times */
#define TMR4_SEVT_MASK_13                       (13U)   /*!< Mask 13 times */
#define TMR4_SEVT_MASK_14                       (14U)   /*!< Mask 14 times */
#define TMR4_SEVT_MASK_15                       (15U)   /*!< Mask 15 times */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Port_Output_Event_Signal TMR4 SEVT Port Output Event Signal
 * @{
 */
#define TMR4_SEVT_PORT_OUTPUT_NONE              (0U)                    /*!< Disable output event signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT0_SIGNAL     (TMR4_SCER_EVTRS_0 )    /*!< Output the specified event 0 signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT1_SIGNAL     (TMR4_SCER_EVTRS_1)     /*!< Output the specified event 1 signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT2_SIGNAL     (TMR4_SCER_EVTRS_1 | \
                                                 TMR4_SCER_EVTRS_0)     /*!< Output the specified event 2 signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT3_SIGNAL     (TMR4_SCER_EVTRS_2)     /*!< Output the specified event 3 signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT4_SIGNAL     (TMR4_SCER_EVTRS_2 | \
                                                 TMR4_SCER_EVTRS_0)     /*!< Output the specified event 4 signal of TMR4 Special-EVT */
#define TMR4_SEVT_PORT_OUTPUT_EVENT5_SIGNAL     (TMR4_SCER_EVTRS_2 | \
                                                 TMR4_SCER_EVTRS_1)     /*!< Output the specified event 5 signal of TMR4 Special-EVT */
/**
 * @}
 */

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
 * @addtogroup TMR4_Global_Functions
 * @{
 */

/**
 * @addtogroup TMR4_CNT_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 counter functions */
en_result_t TMR4_CNT_Init(M4_TMR4_TypeDef *TMR4x,
                                const stc_tmr4_cnt_init_t *pstcInit);
en_result_t TMR4_CNT_StructInit(stc_tmr4_cnt_init_t *pstcInit);
void TMR4_CNT_DeInit(M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetClock(M4_TMR4_TypeDef *TMR4x, uint16_t u16ClkSrc);
uint16_t TMR4_CNT_GetClock(const M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetPclkDiv(M4_TMR4_TypeDef *TMR4x, uint16_t u16Div);
uint16_t TMR4_CNT_GetPclkDiv(const M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetMode(M4_TMR4_TypeDef *TMR4x, uint16_t u16Mode);
uint16_t TMR4_CNT_GetMode(const M4_TMR4_TypeDef *TMR4x);
en_flag_status_t TMR4_CNT_GetStatus(const M4_TMR4_TypeDef *TMR4x, uint16_t u16Flag);
void TMR4_CNT_ClearStatus(M4_TMR4_TypeDef *TMR4x, uint16_t u16Flag);
void TMR4_CNT_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint16_t u16IntSource,
                            en_functional_state_t enNewState);
void TMR4_CNT_Start(M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_Stop(M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetCycleVal(M4_TMR4_TypeDef *TMR4x, uint16_t u16CycleVal);
uint16_t TMR4_CNT_GetCycleVal(const M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_ClearCountVal(M4_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetCountVal(M4_TMR4_TypeDef *TMR4x, uint16_t u16CountVal);
uint16_t TMR4_CNT_GetCountVal(const M4_TMR4_TypeDef *TMR4x);
en_result_t TMR4_CNT_SetIntMaskTimes(M4_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntSource,
                                        uint16_t u16MaskTimes);
en_result_t TMR4_CNT_GetIntMaskTimes(const M4_TMR4_TypeDef *TMR4x,
                                            uint16_t u16IntSource,
                                            uint16_t *pu16MaskTimes);
en_result_t TMR4_CNT_GetIntMaskCurrentTimes(const M4_TMR4_TypeDef *TMR4x,
                                                    uint16_t u16IntSource,
                                                    uint16_t *pu16MaskTimes);
void TMR4_CNT_PortOutputDirSigCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState);
/**
 * @}
 */

/**
 * @addtogroup TMR4_OCO_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 OCO functions */
en_result_t TMR4_OCO_Init(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_tmr4_oco_init_t *pstcInit);
en_result_t TMR4_OCO_StructInit(stc_tmr4_oco_init_t *pstcInit);
void TMR4_OCO_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OCO_SetOccrBufMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16OccrBufMode);
uint16_t TMR4_OCO_GetOccrBufMode(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch);
void TMR4_OCO_SetOccrLinkTransfer(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16TransferState);
void TMR4_OCO_SetOcmrBufMode(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OcmrBufMode);
uint16_t TMR4_OCO_GetOcmrBufMode(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch);
void TMR4_OCO_SetOcmrLinkTransfer(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16TransferState);
void TMR4_OCO_SetExtMatchCond(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16ExtMatch);
en_result_t TMR4_OCO_SetHighChCompareMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_high_ch_compare_mode_t *pstcMode);
en_result_t TMR4_OCO_SetLowChCompareMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_low_ch_compare_mode_t *pstcMode);
void TMR4_OCO_SetOutputCompare(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OcoCmd);
void TMR4_OCO_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            en_functional_state_t enNewState);
en_flag_status_t TMR4_OCO_GetStatus(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
void TMR4_OCO_ClearStatus(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OCO_SetOcoInvalidOp(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OutputPolarity);
uint16_t TMR4_OCO_GetOutputPolarity(const M4_TMR4_TypeDef *TMR4x,
                                                uint32_t u32Ch);
void TMR4_OCO_SetCompareVal(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16CompareVal);
uint16_t TMR4_OCO_GetCompareVal(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
/**
 * @}
 */

/**
 * @addtogroup TMR4_PWM_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 PWM functions */
en_result_t TMR4_PWM_Init(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_tmr4_pwm_init_t *pstcInit);
en_result_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcInit);
void TMR4_PWM_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_SetPclkDiv(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Div);
uint16_t TMR4_PWM_GetPclkDiv(const M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_SetOcoPolarityTransform(M4_TMR4_TypeDef *TMR4x,
                                                uint32_t u32Ch,
                                                uint16_t u16OcoPolTransform);
uint16_t TMR4_PWM_GetOcoPolarityTransform(const M4_TMR4_TypeDef *TMR4x,
                                                    uint32_t u32Ch);
void TMR4_PWM_StartReloadTimer(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_StopReloadTimer(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            en_functional_state_t enNewState);
en_flag_status_t TMR4_PWM_GetStatus(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
void TMR4_PWM_ClearStatus(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch);
void TMR4_PWM_SetDeadRegionValue(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16PDAR,
                                            uint16_t u16PDBR);
void TMR4_PWM_GetDeadRegionValue(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t *pu16PDAR,
                                            uint16_t *pu16PDBR);
void TMR4_PWM_SetFilterCountValue(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16Count);
void TMR4_PWM_AutoOutputCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState);
void TMR4_PWM_MasterOutputCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState);
void TMR4_PWM_PortOutputMode(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32PwmPort,
                                    uint32_t u32Mode);
void TMR4_PWM_SetPortEnBitEffectTime(M4_TMR4_TypeDef *TMR4x,
                                                    uint32_t u32EffectTime);
uint32_t TMR4_PWM_GetPortEnBitEffectTime(const M4_TMR4_TypeDef *TMR4x);
void TMR4_PWM_EmbPwmPortOutputState(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32PwmPort,
                                            uint32_t u32State);
/**
 * @}
 */

/**
 * @addtogroup TMR4_SEVT_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 SEVT functions */
en_result_t TMR4_SEVT_Init(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    const stc_tmr4_sevt_init_t *pstcInit);
en_result_t TMR4_SEVT_StructInit(stc_tmr4_sevt_init_t *pstcInit);
void TMR4_SEVT_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_SEVT_SetOutpuEvent(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16Event);
uint16_t TMR4_SEVT_GetOutpuEvent(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_SEVT_SetDelayObject(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16DelayObject);
uint16_t TMR4_SEVT_GetDelayObject(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch);
void TMR4_SEVT_SetCompareVal(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16CompareVal);
uint16_t TMR4_SEVT_GetCompareVal(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
void TMR4_SEVT_SetMaskTimes(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16MaskTimes);
uint16_t TMR4_SEVT_GetMaskTimes(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
void TMR4_SEVT_SetPortOutputEventSig(M4_TMR4_TypeDef *TMR4x,
                                            uint16_t u16EvtSignal);
uint16_t TMR4_SEVT_GetPortOutputEventSig(const M4_TMR4_TypeDef *TMR4x);
/**
 * @}
 */

/**
 * @}
 */

#endif /* DDL_TMR4_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR4_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
