/**
 *******************************************************************************
 * @file  hc32_ll_tmr4.h
 * @brief This file contains all the functions prototypes of the TMR4
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Update API parameter u16IntType to u32IntType
   2023-06-30       CDT             Add the macros group @ref TMR4_OC_Output_Polarity
                                    Modify typo
                                    TMR4_OC_Buffer_Object group add macro-definition: TMR4_OC_BUF_NONE
   2023-09-30       CDT             Modify API TMR4_DeInit
                                    Fix spell error about "response" that in function name
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
#ifndef __HC32_LL_TMR4_H__
#define __HC32_LL_TMR4_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_TMR4
 * @{
 */

#if (LL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR4_Global_Types TMR4 Global Types
 * @{
 */

/**
 * @brief TMR4 Counter function initialization configuration
 * @note The TMR4 division(u16ClockDiv) is valid when clock source is the internal clock.
 */
typedef struct {
    uint16_t u16ClockSrc;       /*!< TMR4 counter clock source.
                                     This parameter can be a value of @ref TMR4_Count_Clock_Source */
    uint16_t u16ClockDiv;       /*!< TMR4 counter internal clock division.
                                     This parameter can be a value of @ref TMR4_Count_Clock_Division. */
    uint16_t u16CountMode;      /*!< TMR4 counter mode.
                                     This parameter can be a value of @ref TMR4_Count_Mode */
    uint16_t u16PeriodValue;    /*!< TMR4 counter period value.
                                     This parameter can be a value of half-word */
} stc_tmr4_init_t;

/**
 * @brief The configuration of Output-Compare high channel(OUH/OVH/OWH)
 */
typedef union {
    uint16_t OCMRx;             /*!< OCMRxH(x=U/V/W) register */

    struct {                    /*!< OCMRxH(x=U/V/W) register struct field bit */
        uint16_t OCFDCH : 1;    /*!< OCMRxh b0 High channel's OCF status when high channel match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint16_t OCFPKH : 1;    /*!< OCMRxh b1 High channel's OCF status when high channel match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint16_t OCFUCH : 1;    /*!< OCMRxh b2 High channel's OCF status when high channel match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint16_t OCFZRH : 1;    /*!< OCMRxh b3 High channel's OCF status when high channel match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint16_t OPDCH  : 2;    /*!< OCMRxh b5~b4 High channel's OP output status when high channel match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint16_t OPPKH  : 2;    /*!< OCMRxh b7~b6 High channel's OP output status when high channel match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint16_t OPUCH  : 2;    /*!< OCMRxh b9~b8 High channel's OP output status when high channel match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint16_t OPZRH  : 2;    /*!< OCMRxh b11~b10 High channel's OP output status when high channel match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint16_t OPNPKH : 2;    /*!< OCMRxh b13~b12 High channel's OP output status when high channel match doesn't occur at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint16_t OPNZRH : 2;    /*!< OCMRxh b15~b14 High channel's OP output status when high channel match doesn't occur at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
    } OCMRx_f;
} un_tmr4_oc_ocmrh_t;

/**
 * @brief The configuration of Output-Compare low channel(OUL/OVL/OWL)
 */
typedef union {
    uint32_t OCMRx;             /*!< OCMRxL(x=U/V/W) register */

    struct {                    /*!< OCMRxL(x=U/V/W) register struct field bit*/
        uint32_t OCFDCL  : 1;   /*!< OCMRxl b0 Low channel's OCF status when low channel match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint32_t OCFPKL  : 1;   /*!< OCMRxl b1 Low channel's OCF status when low channel match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint32_t OCFUCL  : 1;   /*!< OCMRxl b2 Low channel's OCF status when low channel match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint32_t OCFZRL  : 1;   /*!< OCMRxl b3 Low channel's OCF status when low channel match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_OCF_State */
        uint32_t OPDCL   : 2;   /*!< OCMRxl b5~b4 Low channel's OP output status when high channel not match and low channel match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t OPPKL   : 2;   /*!< OCMRxl b7~b6 Low channel's OP output status when high channel not match and low channel match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t OPUCL   : 2;   /*!< OCMRxl b9~b8 Low channel's OP output status when high channel not match and low channel match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t OPZRL   : 2;   /*!< OCMRxl b11~b10 Low channel's OP output status when high channel not match and low channel match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t OPNPKL  : 2;   /*!< OCMRxl b13~b12 Low channel's OP output status when high channel not match and low channel not match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t OPNZRL  : 2;   /*!< OCMRxl b15~b14 Low channel's OP output status when high channel not match and low channel not match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPNDCL : 2;   /*!< OCMRxl b17~b16 Low channel's OP output status when high channel match and low channel not match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPNUCL : 2;   /*!< OCMRxl b19~b18 Low channel's OP output status when high channel match and low channel not match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPDCL  : 2;   /*!< OCMRxl b21~b20 Low channel's OP output status when high channel and low channel match occurs at the condition that counter is counting down
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPPKL  : 2;   /*!< OCMRxl b23~b22 Low channel's OP output status when high channel and low channel match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPUCL  : 2;   /*!< OCMRxl b25~b24 Low channel's OP output status when high channel and low channel match occurs at the condition that counter is counting up
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPZRL  : 2;   /*!< OCMRxl b27~b26 Low channel's OP output status when high channel and low channel match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPNPKL : 2;   /*!< OCMRxl b29~b28 Low channel's OP output status when high channel match and low channel not match occurs at the condition that counter count=Peak
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
        uint32_t EOPNZRL : 2;   /*!< OCMRxl b31~b30 Low channel's OP output status when high channel match and low channel not match occurs at the condition that counter count=0x0000
                                     This parameter can be a value of @ref TMR4_OC_Count_Match_Output_Polarity */
    } OCMRx_f;
} un_tmr4_oc_ocmrl_t;

/**
 * @brief TMR4 Output-Compare(OC) initialization configuration
 */
typedef struct {
    uint16_t u16CompareValue;           /*!< TMR4 OC compare match value.
                                             This parameter can be a value of half-word. */
    uint16_t u16OcInvalidPolarity;      /*!< Port output polarity when OC is disabled.
                                             This parameter can be a value of @ref TMR4_OC_Invalid_Output_Polarity. */
    uint16_t u16CompareModeBufCond;     /*!< Register OCMR buffer transfer condition.
                                             This parameter can be a value of @ref TMR4_OC_Buffer_Transfer_Condition. */
    uint16_t u16CompareValueBufCond;    /*!< Register OCCR buffer transfer condition.
                                             This parameter can be a value of @ref TMR4_OC_Buffer_Transfer_Condition. */
    uint16_t u16BufLinkTransObject;     /*!< Enable the specified object(OCMR/OCCR) register buffer linked transfer with the counter interrupt mask.
                                             This parameter can be a value of @ref TMR4_OC_Buffer_Object. */
} stc_tmr4_oc_init_t;

/**
 * @brief TMR4 PWM initialization configuration
 * @note The clock division(u16ClockDiv) is valid when TMR4 clock source is the internal clock.
 */
typedef struct {
    uint16_t u16Mode;                   /*!< Select PWM mode
                                             This parameter can be a value of @ref TMR4_PWM_Mode */
    uint16_t u16ClockDiv;               /*!< The internal clock division of PWM timer.
                                             This parameter can be a value of @ref TMR4_PWM_Clock_Division. */
    uint16_t u16Polarity;               /*!< TMR4 PWM polarity
                                             This parameter can be a value of @ref TMR4_PWM_Polarity */
} stc_tmr4_pwm_init_t;

/**
 * @brief TMR4 Special-Event(EVT) initialization configuration
 */
typedef struct {
    uint16_t u16Mode;                   /*!< TMR4 event mode
                                             This parameter can be a value of @ref TMR4_Event_Mode */
    uint16_t u16CompareValue;           /*!< TMR4 event compare match value.
                                             This parameter can be a value of half-word */
    uint16_t u16OutputEvent;            /*!< TMR4 event output event when match count compare condition.
                                             This parameter can be a value of @ref TMR4_Event_Output_Event */
    uint16_t u16MatchCond;              /*!< Enable the specified count compare type with counter count to generate event.
                                             This parameter can be a value of @ref TMR4_Event_Match_Condition */
} stc_tmr4_evt_init_t;

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
 * @defgroup TMR4_Counter_Macros TMR4 Counter Macros
 * @{
 */

/**
 * @defgroup TMR4_Count_Clock_Source TMR4 Count Clock Source
 * @{
 */
#define TMR4_CLK_SRC_INTERNCLK          (0U)
#define TMR4_CLK_SRC_EXTCLK             (TMR4_CCSR_ECKEN)
/**
 * @}
 */

/**
 * @defgroup TMR4_Count_Clock_Division TMR4 Count Clock Division
 * @{
 */
#define TMR4_CLK_DIV1                   (0U << TMR4_CCSR_CKDIV_POS)  /*!< CLK      */
#define TMR4_CLK_DIV2                   (1U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/2    */
#define TMR4_CLK_DIV4                   (2U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/4    */
#define TMR4_CLK_DIV8                   (3U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/8    */
#define TMR4_CLK_DIV16                  (4U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/16   */
#define TMR4_CLK_DIV32                  (5U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/32   */
#define TMR4_CLK_DIV64                  (6U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/64   */
#define TMR4_CLK_DIV128                 (7U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/128  */
#define TMR4_CLK_DIV256                 (8U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/256  */
#define TMR4_CLK_DIV512                 (9U << TMR4_CCSR_CKDIV_POS)  /*!< CLK/512  */
#define TMR4_CLK_DIV1024                (10U << TMR4_CCSR_CKDIV_POS) /*!< CLK/1024 */
/**
 * @}
 */

/**
 * @defgroup TMR4_Count_Mode TMR4 Count Mode
 * @{
 */
#define TMR4_MD_SAWTOOTH                (0U)
#define TMR4_MD_TRIANGLE                (TMR4_CCSR_MODE)
/**
 * @}
 */

/**
 * @defgroup TMR4_Flag TMR4 Flag
 * @{
 */
#define TMR4_FLAG_CNT_PEAK              ((uint32_t)TMR4_CCSR_IRQPF)     /*!< Count peak flag */
#define TMR4_FLAG_CNT_VALLEY            ((uint32_t)TMR4_CCSR_IRQZF)     /*!< Count valley flag */
#define TMR4_FLAG_RELOAD_TMR_U          (1UL << 0U)                     /*!< TMR4 PWM reload-timer flag - channel U */
#define TMR4_FLAG_RELOAD_TMR_V          (1UL << 4U)                     /*!< TMR4 PWM reload-timer flag - channel V */
#define TMR4_FLAG_RELOAD_TMR_W          (1UL << 8U)                     /*!< TMR4 PWM reload-timer flag - channel W */
#define TMR4_FLAG_OC_CMP_UH             (1UL << 16U)                    /*!< TMR4 output-compare compare flag - channel UH */
#define TMR4_FLAG_OC_CMP_UL             (1UL << 17U)                    /*!< TMR4 output-compare compare flag - channel UL */
#define TMR4_FLAG_OC_CMP_VH             (1UL << 18U)                    /*!< TMR4 output-compare compare flag - channel VH */
#define TMR4_FLAG_OC_CMP_VL             (1UL << 19U)                    /*!< TMR4 output-compare compare flag - channel VL */
#define TMR4_FLAG_OC_CMP_WH             (1UL << 20U)                    /*!< TMR4 output-compare compare flag - channel WH */
#define TMR4_FLAG_OC_CMP_WL             (1UL << 21U)                    /*!< TMR4 output-compare compare flag - channel WL */

#define TMR4_FLAG_ALL                   (TMR4_FLAG_CNT_PEAK     | TMR4_FLAG_CNT_VALLEY   | TMR4_FLAG_RELOAD_TMR_U | \
                                         TMR4_FLAG_RELOAD_TMR_V | TMR4_FLAG_RELOAD_TMR_W | TMR4_FLAG_OC_CMP_UH    | \
                                         TMR4_FLAG_OC_CMP_UL    | TMR4_FLAG_OC_CMP_VH    | TMR4_FLAG_OC_CMP_VL    | \
                                         TMR4_FLAG_OC_CMP_WH    | TMR4_FLAG_OC_CMP_WL)
/**
 * @}
 */

/**
 * @defgroup TMR4_Interrupt TMR4 Interrupt
 * @{
 */
#define TMR4_INT_CNT_PEAK               ((uint32_t)TMR4_CCSR_IRQPEN)    /*!< Count peak interrupt */
#define TMR4_INT_CNT_VALLEY             ((uint32_t)TMR4_CCSR_IRQZEN)    /*!< Count valley interrupt */
#define TMR4_INT_RELOAD_TMR_U           (1UL << 0U)                     /*!< TMR4 PWM reload-timer interrupt - channel U */
#define TMR4_INT_RELOAD_TMR_V           (1UL << 1U)                     /*!< TMR4 PWM reload-timer interrupt - channel W */
#define TMR4_INT_RELOAD_TMR_W           (1UL << 2U)                     /*!< TMR4 PWM reload-timer interrupt - channel V */
#define TMR4_INT_OC_CMP_UH              (1UL << 16U)                    /*!< TMR4 output-compare compare interrupt - channel UH */
#define TMR4_INT_OC_CMP_UL              (1UL << 17U)                    /*!< TMR4 output-compare compare interrupt - channel UL */
#define TMR4_INT_OC_CMP_VH              (1UL << 18U)                    /*!< TMR4 output-compare compare interrupt - channel VH */
#define TMR4_INT_OC_CMP_VL              (1UL << 19U)                    /*!< TMR4 output-compare compare interrupt - channel VL */
#define TMR4_INT_OC_CMP_WH              (1UL << 20U)                    /*!< TMR4 output-compare compare interrupt - channel WH */
#define TMR4_INT_OC_CMP_WL              (1UL << 21U)                    /*!< TMR4 output-compare compare interrupt - channel WL */

#define TMR4_INT_ALL                    (TMR4_INT_CNT_PEAK     | TMR4_INT_CNT_VALLEY   | TMR4_INT_RELOAD_TMR_U | \
                                         TMR4_INT_RELOAD_TMR_V | TMR4_INT_RELOAD_TMR_W | TMR4_INT_OC_CMP_UH    | \
                                         TMR4_INT_OC_CMP_UL    | TMR4_INT_OC_CMP_VH    | TMR4_INT_OC_CMP_VL    | \
                                         TMR4_INT_OC_CMP_WH    | TMR4_INT_OC_CMP_WL)
/**
 * @}
 */

/**
 * @defgroup TMR4_Count_Interrupt_Mask_Time TMR4 Count Interrupt Mask Time
 * @{
 */
#define TMR4_INT_CNT_MASK0              (0U)    /*!< Counter interrupt flag is always set(not masked) for counter count every time at "0x0000" or peak */
#define TMR4_INT_CNT_MASK1              (1U)    /*!< Counter interrupt flag is set once when counter counts 2 times at "0x0000" or peak (skipping 1 count) */
#define TMR4_INT_CNT_MASK2              (2U)    /*!< Counter interrupt flag is set once when counter counts 3 times at "0x0000" or peak (skipping 2 count) */
#define TMR4_INT_CNT_MASK3              (3U)    /*!< Counter interrupt flag is set once when counter counts 4 times at "0x0000" or peak (skipping 3 count) */
#define TMR4_INT_CNT_MASK4              (4U)    /*!< Counter interrupt flag is set once when counter counts 5 times at "0x0000" or peak (skipping 4 count) */
#define TMR4_INT_CNT_MASK5              (5U)    /*!< Counter interrupt flag is set once when counter counts 6 times at "0x0000" or peak (skipping 5 count) */
#define TMR4_INT_CNT_MASK6              (6U)    /*!< Counter interrupt flag is set once when counter counts 7 times at "0x0000" or peak (skipping 6 count) */
#define TMR4_INT_CNT_MASK7              (7U)    /*!< Counter interrupt flag is set once when counter counts 8 times at "0x0000" or peak (skipping 7 count) */
#define TMR4_INT_CNT_MASK8              (8U)    /*!< Counter interrupt flag is set once when counter counts 9 times at "0x0000" or peak (skipping 8 count) */
#define TMR4_INT_CNT_MASK9              (9U)    /*!< Counter interrupt flag is set once when counter counts 10 times at "0x0000" or peak (skipping 9 count) */
#define TMR4_INT_CNT_MASK10             (10U)   /*!< Counter interrupt flag is set once when counter counts 11 times at "0x0000" or peak (skipping 10 count) */
#define TMR4_INT_CNT_MASK11             (11U)   /*!< Counter interrupt flag is set once when counter counts 12 times at "0x0000" or peak (skipping 11 count) */
#define TMR4_INT_CNT_MASK12             (12U)   /*!< Counter interrupt flag is set once when counter counts 13 times at "0x0000" or peak (skipping 12 count) */
#define TMR4_INT_CNT_MASK13             (13U)   /*!< Counter interrupt flag is set once when counter counts 14 times at "0x0000" or peak (skipping 13 count) */
#define TMR4_INT_CNT_MASK14             (14U)   /*!< Counter interrupt flag is set once when counter counts 15 times at "0x0000" or peak (skipping 14 count) */
#define TMR4_INT_CNT_MASK15             (15U)   /*!< Counter interrupt flag is set once when counter counts 16 times at "0x0000" or peak (skipping 15 count) */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_Output_Compare_Macros TMR4 Output-Compare Macros
 * @{
 */

/**
 * @defgroup TMR4_OC_Channel TMR4 OC Channel
 * @{
 */
#define TMR4_OC_CH_UH                   (0UL)   /*!< TMR4 OC channel:UH */
#define TMR4_OC_CH_UL                   (1UL)   /*!< TMR4 OC channel:UL */
#define TMR4_OC_CH_VH                   (2UL)   /*!< TMR4 OC channel:VH */
#define TMR4_OC_CH_VL                   (3UL)   /*!< TMR4 OC channel:VL */
#define TMR4_OC_CH_WH                   (4UL)   /*!< TMR4 OC channel:WH */
#define TMR4_OC_CH_WL                   (5UL)   /*!< TMR4 OC channel:WL */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Invalid_Output_Polarity TMR4 OC Invalid Output Polarity
 * @{
 */
#define TMR4_OC_INVD_LOW                (0U)              /*!< TMR4 OC Output low level when OC is invalid */
#define TMR4_OC_INVD_HIGH               (TMR4_OCSR_OCPH)  /*!< TMR4 OC Output high level when OC is invalid */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Output_Polarity TMR4 OC Output Polarity
 * @{
 */
#define TMR4_OC_PORT_LOW                (0U)              /*!< TMR4 OC Output low level */
#define TMR4_OC_PORT_HIGH               (TMR4_OCSR_OCPH)  /*!< TMR4 OC Output high level */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Buffer_Object TMR4 OC Buffer Object
 * @{
 */
#define TMR4_OC_BUF_NONE                (0x00U) /*!< Disable the buffer function of OCCR/OCMR */
#define TMR4_OC_BUF_CMP_VALUE           (0x01U) /*!< The register OCCR buffer function */
#define TMR4_OC_BUF_CMP_MD              (0x02U) /*!< The register OCMR buffer function */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Buffer_Transfer_Condition TMR4 OC OCCR Buffer Transfer Condition
 * @{
 */
#define TMR4_OC_BUF_COND_IMMED          (0U)    /*!< Buffer transfer is made when writing to the OCCR/OCMR register. */
#define TMR4_OC_BUF_COND_VALLEY         (1U)    /*!< Buffer transfer is made when counter count valley */
#define TMR4_OC_BUF_COND_PEAK           (2U)    /*!< Buffer transfer is made when counter count peak */
#define TMR4_OC_BUF_COND_PEAK_VALLEY    (3U)    /*!< Buffer transfer is made when counter count peak or valley */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Count_Match_OCF_State TMR4 OC Count Match OCF State
 * @{
 */
#define TMR4_OC_OCF_HOLD                (0U)                /*!< Hold OCF when the TMR4 OC count match */
#define TMR4_OC_OCF_SET                 (TMR4_OCMRH_OCFDCH) /*!< Set OCF when the TMR4 OC count match */
/**
 * @}
 */

/**
 * @defgroup TMR4_OC_Count_Match_Output_Polarity TMR4 OC Count Match Output Polarity
 * @{
 */
#define TMR4_OC_HOLD                    (0U)    /*!< Hold output when the TMR4 OC count match */
#define TMR4_OC_HIGH                    (1U)    /*!< Output high when the TMR4 OC count match */
#define TMR4_OC_LOW                     (2U)    /*!< Output low when the TMR4 OC count match */
#define TMR4_OC_INVT                    (3U)    /*!< Invert output when the TMR4 OC count match */
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

/**
 * @defgroup TMR4_PWM_Channel TMR4 PWM Channel
 * @{
 */
#define TMR4_PWM_CH_U                   (0UL)   /*!< TMR4 PWM couple channel: U */
#define TMR4_PWM_CH_V                   (1UL)   /*!< TMR4 PWM couple channel: V */
#define TMR4_PWM_CH_W                   (2UL)   /*!< TMR4 PWM couple channel: W */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Pin TMR4 PWM Pin
 * @{
 */
#define TMR4_PWM_PIN_OUH                (0UL)   /*!< TMR4 PWM port: TIM4_<t>_OUH */
#define TMR4_PWM_PIN_OUL                (1UL)   /*!< TMR4 PWM port: TIM4_<t>_OUL */
#define TMR4_PWM_PIN_OVH                (2UL)   /*!< TMR4 PWM port: TIM4_<t>_OVH */
#define TMR4_PWM_PIN_OVL                (3UL)   /*!< TMR4 PWM port: TIM4_<t>_OVL */
#define TMR4_PWM_PIN_OWH                (4UL)   /*!< TMR4 PWM port: TIM4_<t>_OWH */
#define TMR4_PWM_PIN_OWL                (5UL)   /*!< TMR4 PWM port: TIM4_<t>_OWL */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Clock_Division TMR4 PWM Clock Division
 * @{
 */
#define TMR4_PWM_CLK_DIV1               (0U)                        /*!< CLK     */
#define TMR4_PWM_CLK_DIV2               (1U << TMR4_POCR_DIVCK_POS) /*!< CLK/2   */
#define TMR4_PWM_CLK_DIV4               (2U << TMR4_POCR_DIVCK_POS) /*!< CLK/8   */
#define TMR4_PWM_CLK_DIV8               (3U << TMR4_POCR_DIVCK_POS) /*!< CLK/8   */
#define TMR4_PWM_CLK_DIV16              (4U << TMR4_POCR_DIVCK_POS) /*!< CLK/16  */
#define TMR4_PWM_CLK_DIV32              (5U << TMR4_POCR_DIVCK_POS) /*!< CLK/32  */
#define TMR4_PWM_CLK_DIV64              (6U << TMR4_POCR_DIVCK_POS) /*!< CLK/64  */
#define TMR4_PWM_CLK_DIV128             (7U << TMR4_POCR_DIVCK_POS) /*!< CLK/128 */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Mode TMR4 PWM Mode
 * @{
 */
#define TMR4_PWM_MD_THROUGH             (0U)                /*!< Through mode */
#define TMR4_PWM_MD_DEAD_TMR            (TMR4_POCR_PWMMD_0) /*!< Dead timer mode */
#define TMR4_PWM_MD_DEAD_TMR_FILTER     (TMR4_POCR_PWMMD_1) /*!< Dead timer filter mode */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Polarity TMR4 PWM Polarity
 * @{
 */
#define TMR4_PWM_OXH_HOLD_OXL_HOLD      (0U)                /*!< Output PWML and PWMH signals without changing the level */
#define TMR4_PWM_OXH_INVT_OXL_INVT      (TMR4_POCR_LVLS_0)  /*!< Output both PWML and PWMH signals reversed */
#define TMR4_PWM_OXH_INVT_OXL_HOLD      (TMR4_POCR_LVLS_1)  /*!< Output the PWMH signal reversed, outputs the PWML signal without changing the level. */
#define TMR4_PWM_OXH_HOLD_OXL_INVT      (TMR4_POCR_LVLS)    /*!< Output the PWMH signal without changing the level, Outputs the PWML signal reversed. */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Dead_Time_Register_Index TMR4 PWM Dead Time Register Index
 * @{
 */
#define TMR4_PWM_PDAR_IDX               (0UL)               /*!< TMR4_PDARn(n=U/V/W) */
#define TMR4_PWM_PDBR_IDX               (1UL)               /*!< TMR4_PDBRn(n=U/V/W) */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Abnormal_Pin_Status TMR4 PWM Abnormal Pin Status
 * @{
 */
#define TMR4_PWM_ABNORMAL_PIN_NORMAL    (0UL)           /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output normal */
#define TMR4_PWM_ABNORMAL_PIN_HIZ       (1UL)           /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) to Hi-z */
#define TMR4_PWM_ABNORMAL_PIN_LOW       (2UL)           /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output low level */
#define TMR4_PWM_ABNORMAL_PIN_HIGH      (3UL)           /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output high level */
#define TMR4_PWM_ABNORMAL_PIN_HOLD      (4UL)           /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output hold */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Macros TMR4 Event Macros
 * @{
 */

/**
 * @defgroup TMR4_Event_Channel TMR4 Event Channel
 * @{
 */
#define TMR4_EVT_CH_UH                  (0UL)               /*!< TMR4 EVT channel:UH */
#define TMR4_EVT_CH_UL                  (1UL)               /*!< TMR4 EVT channel:UL */
#define TMR4_EVT_CH_VH                  (2UL)               /*!< TMR4 EVT channel:VH */
#define TMR4_EVT_CH_VL                  (3UL)               /*!< TMR4 EVT channel:VL */
#define TMR4_EVT_CH_WH                  (4UL)               /*!< TMR4 EVT channel:WH */
#define TMR4_EVT_CH_WL                  (5UL)               /*!< TMR4 EVT channel:WL */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Match_Condition TMR4 Event Match Condition
 * @{
 */
#define TMR4_EVT_MATCH_CNT_UP           (TMR4_SCSR_UEN)     /*!< Start event operation when match with SCCR&SCMR and TMR4 counter count up */
#define TMR4_EVT_MATCH_CNT_DOWN         (TMR4_SCSR_DEN)     /*!< Start event operation when match with SCCR&SCMR and TMR4 counter count down */
#define TMR4_EVT_MATCH_CNT_PEAK         (TMR4_SCSR_PEN)     /*!< Start event operation when match with SCCR&SCMR and TMR4 counter count peak */
#define TMR4_EVT_MATCH_CNT_VALLEY       (TMR4_SCSR_ZEN)     /*!< Start event operation when match with SCCR&SCMR and TMR4 counter count valley */
#define TMR4_EVT_MATCH_CNT_ALL          (TMR4_EVT_MATCH_CNT_DOWN | TMR4_EVT_MATCH_CNT_UP | \
                                         TMR4_EVT_MATCH_CNT_PEAK | TMR4_EVT_MATCH_CNT_VALLEY)
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Mask TMR4 Event Mask
 * @{
 */
#define TMR4_EVT_MASK_PEAK              (TMR4_SCMR_MPCE)    /*!< Match with the count peak interrupt mask of the counter  */
#define TMR4_EVT_MASK_VALLEY            (TMR4_SCMR_MZCE)    /*!< Match with the count valley interrupt mask  of the counter */
#define TMR4_EVT_MASK_TYPE_ALL          (TMR4_EVT_MASK_PEAK | TMR4_EVT_MASK_VALLEY)
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Buffer_Transfer_Condition TMR4 Event Buffer Transfer Condition
 * @{
 */
#define TMR4_EVT_BUF_COND_IMMED         (0U)                /*!< Register SCCR&SCMR buffer transfer when writing to the SCCR&SCMR register */
#define TMR4_EVT_BUF_COND_VALLEY        (TMR4_SCSR_BUFEN_0) /*!< Register SCCR&SCMR buffer transfer when counter count valley */
#define TMR4_EVT_BUF_COND_PEAK          (TMR4_SCSR_BUFEN_1) /*!< Register SCCR&SCMR buffer transfer when counter count peak */
#define TMR4_EVT_BUF_COND_PEAK_VALLEY   (TMR4_SCSR_BUFEN)   /*!< Register SCCR&SCMR buffer transfer when counter count peak or valley */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Mode TMR4 Event Mode
 * @{
 */
#define TMR4_EVT_MD_CMP                 (0U)                /*!< TMR4 EVT compare mode */
#define TMR4_EVT_MD_DELAY               (TMR4_SCSR_EVTMS)   /*!< TMR4 EVT delay mode */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Delay_Object TMR4 Event Delay Object
 * @{
 */
#define TMR4_EVT_DELAY_OCCRXH           (0U)                /*!< TMR4 EVT delay object: OCCRxh(x=u/v/w) */
#define TMR4_EVT_DELAY_OCCRXL           (TMR4_SCSR_EVTDS)   /*!< TMR4 EVT delay object: OCCRxl(x=u/v/w) */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Mask_Times TMR4 Event Mask Times
 * @{
 */
#define TMR4_EVT_MASK0                  (0U << TMR4_SCMR_AMC_POS)   /*!< Mask 0 time */
#define TMR4_EVT_MASK1                  (1U << TMR4_SCMR_AMC_POS)   /*!< Mask 1 times */
#define TMR4_EVT_MASK2                  (2U << TMR4_SCMR_AMC_POS)   /*!< Mask 2 times */
#define TMR4_EVT_MASK3                  (3U << TMR4_SCMR_AMC_POS)   /*!< Mask 3 times */
#define TMR4_EVT_MASK4                  (4U << TMR4_SCMR_AMC_POS)   /*!< Mask 4 times */
#define TMR4_EVT_MASK5                  (5U << TMR4_SCMR_AMC_POS)   /*!< Mask 5 times */
#define TMR4_EVT_MASK6                  (6U << TMR4_SCMR_AMC_POS)   /*!< Mask 6 times */
#define TMR4_EVT_MASK7                  (7U << TMR4_SCMR_AMC_POS)   /*!< Mask 7 times */
#define TMR4_EVT_MASK8                  (8U << TMR4_SCMR_AMC_POS)   /*!< Mask 8 times */
#define TMR4_EVT_MASK9                  (9U << TMR4_SCMR_AMC_POS)   /*!< Mask 9 times */
#define TMR4_EVT_MASK10                 (10U << TMR4_SCMR_AMC_POS)  /*!< Mask 10 times */
#define TMR4_EVT_MASK11                 (11U << TMR4_SCMR_AMC_POS)  /*!< Mask 11 times */
#define TMR4_EVT_MASK12                 (12U << TMR4_SCMR_AMC_POS)  /*!< Mask 12 times */
#define TMR4_EVT_MASK13                 (13U << TMR4_SCMR_AMC_POS)  /*!< Mask 13 times */
#define TMR4_EVT_MASK14                 (14U << TMR4_SCMR_AMC_POS)  /*!< Mask 14 times */
#define TMR4_EVT_MASK15                 (15U << TMR4_SCMR_AMC_POS)  /*!< Mask 15 times */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Output_Event TMR4 Event Output Event
 * @{
 */
#define TMR4_EVT_OUTPUT_EVT0            (0U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 0 */
#define TMR4_EVT_OUTPUT_EVT1            (1U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 1 */
#define TMR4_EVT_OUTPUT_EVT2            (2U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 2 */
#define TMR4_EVT_OUTPUT_EVT3            (3U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 3 */
#define TMR4_EVT_OUTPUT_EVT4            (4U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 4 */
#define TMR4_EVT_OUTPUT_EVT5            (5U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 event output special event 5 */
/**
 * @}
 */

/**
 * @defgroup TMR4_Event_Output_Signal TMR4 Event Output Signal
 * @{
 */
#define TMR4_EVT_OUTPUT_NONE            (0U)    /*!< Disable output event signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT0_SIGNAL     (1U)    /*!< Output the specified event 0 signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT1_SIGNAL     (2U)    /*!< Output the specified event 1 signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT2_SIGNAL     (3U)    /*!< Output the specified event 2 signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT3_SIGNAL     (4U)    /*!< Output the specified event 3 signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT4_SIGNAL     (5U)    /*!< Output the specified event 4 signal of TMR4 Special-EVT */
#define TMR4_EVT_OUTPUT_EVT5_SIGNAL     (6U)    /*!< Output the specified event 5 signal of TMR4 Special-EVT */
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
 * @addtogroup TMR4_Counter_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 counter functions */
int32_t TMR4_StructInit(stc_tmr4_init_t *pstcTmr4Init);
int32_t TMR4_Init(CM_TMR4_TypeDef *TMR4x, const stc_tmr4_init_t *pstcTmr4Init);
int32_t TMR4_DeInit(CM_TMR4_TypeDef *TMR4x);
void TMR4_SetClockSrc(CM_TMR4_TypeDef *TMR4x, uint16_t u16Src);
void TMR4_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint16_t u16Div);
void TMR4_SetCountMode(CM_TMR4_TypeDef *TMR4x, uint16_t u16Mode);
uint16_t TMR4_GetPeriodValue(const CM_TMR4_TypeDef *TMR4x);
void TMR4_SetPeriodValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value);
uint16_t TMR4_GetCountValue(const CM_TMR4_TypeDef *TMR4x);
void TMR4_SetCountValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value);
void TMR4_ClearCountValue(CM_TMR4_TypeDef *TMR4x);
void TMR4_Start(CM_TMR4_TypeDef *TMR4x);
void TMR4_Stop(CM_TMR4_TypeDef *TMR4x);
void TMR4_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32Flag);
en_flag_status_t TMR4_GetStatus(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Flag);
void TMR4_IntCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType, en_functional_state_t enNewState);
void TMR4_PeriodBufCmd(CM_TMR4_TypeDef *TMR4x, en_functional_state_t enNewState);
uint16_t TMR4_GetCountIntMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType);
void TMR4_SetCountIntMaskTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType, uint16_t u16MaskTime);
uint16_t TMR4_GetCurrentCountIntMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32IntType);
/**
 * @}
 */

/**
 * @addtogroup TMR4_Output_Compare_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 Output-Compare functions */
int32_t TMR4_OC_StructInit(stc_tmr4_oc_init_t *pstcTmr4OcInit);
int32_t TMR4_OC_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_oc_init_t *pstcTmr4OcInit);
void TMR4_OC_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
uint16_t TMR4_OC_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OC_SetCompareValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value);
void TMR4_OC_Cmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR4_OC_ExtendControlCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR4_OC_BufIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch,
                                    uint16_t u16Object, en_functional_state_t enNewState);
uint16_t TMR4_OC_GetPolarity(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OC_SetOcInvalidPolarity(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Polarity);
void TMR4_OC_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Object, uint16_t u16BufCond);
uint16_t TMR4_OC_GetHighChCompareMode(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OC_SetHighChCompareMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, un_tmr4_oc_ocmrh_t unTmr4Ocmrh);
uint32_t TMR4_OC_GetLowChCompareMode(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OC_SetLowChCompareMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, un_tmr4_oc_ocmrl_t unTmr4Ocmrl);
/**
 * @}
 */

/**
 * @addtogroup TMR4_PWM_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 PWM functions */
int32_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcTmr4PwmInit);
int32_t TMR4_PWM_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_pwm_init_t *pstcTmr4PwmInit);
void TMR4_PWM_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Div);
void TMR4_PWM_SetPolarity(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Polarity);
void TMR4_PWM_StartReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_StopReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_SetFilterCountValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value);
void TMR4_PWM_SetDeadTimeValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint32_t u32DeadTimeIndex, uint16_t u16Value);
uint16_t TMR4_PWM_GetDeadTimeValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint32_t u32DeadTimeIndex);
void TMR4_PWM_SetAbnormalPinStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32PwmPin, uint32_t u32PinStatus);

/**
 * @}
 */

/**
 * @addtogroup TMR4_Event_Global_Functions
 * @{
 */

/* Initialization and configuration TMR4 event functions */
int32_t TMR4_EVT_StructInit(stc_tmr4_evt_init_t *pstcTmr4EventInit);
int32_t TMR4_EVT_Init(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, const stc_tmr4_evt_init_t *pstcTmr4EventInit);
void TMR4_EVT_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_EVT_SetDelayObject(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Object);
void TMR4_EVT_SetMaskTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16MaskTime);
uint16_t TMR4_EVT_GetMaskTime(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_EVT_SetCompareValue(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Value);
uint16_t TMR4_EVT_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_EVT_SetOutputEvent(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Event);
void TMR4_EVT_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16BufCond);
void TMR4_EVT_BufIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR4_EVT_EventIntervalResponseCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch,
                                       uint16_t u16MaskType, en_functional_state_t enNewState);
void TMR4_EVT_MatchCondCmd(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TMR4_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
