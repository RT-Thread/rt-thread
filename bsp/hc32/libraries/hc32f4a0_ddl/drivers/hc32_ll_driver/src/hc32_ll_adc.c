/**
 *******************************************************************************
 * @file  hc32_ll_adc.c
 * @brief This file provides firmware functions to manage the Analog-to-Digital
 *        Converter(ADC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             API fixed: ADC_DeInit()
   2023-06-30       CDT             Modify typo
                                    API fixed: ADC_DeInit()
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
#include "hc32_ll_adc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_ADC ADC
 * @brief Analog-to-Digital Converter Driver Library
 * @{
 */

#if (LL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Local_Macros ADC Local Macros
 * @{
 */

/**
 * @defgroup ADC_PGA_En ADC PGA Function Control
 * @{
 */
#define ADC_PGA_DISABLE                 (0x0U)
#define ADC_PGA_ENABLE                  (0xEU)
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_DR_CHSR ADC AWD DR CHSR
 * @{
 */
#define ADC_AWDx_DR(awd, reg_base)      (*(__IO uint16_t *)((uint32_t)(reg_base) + ((uint32_t)(awd) * 8U)))
#define ADC_AWDx_CHSR(awd, reg_base)    (*(__IO uint8_t *)((uint32_t)(reg_base) + ((uint32_t)(awd) * 8U)))
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Max ADC Channel Max
 * @{
 */
#define ADC1_CH_MAX                     (ADC_CH15)
#define ADC2_CH_MAX                     (ADC_CH15)
#define ADC3_CH_MAX                     (ADC_CH19)
#define ADC_REMAP_CH_MAX                (ADC_CH15)
#define ADC_REMAP_PIN_MAX               (ADC12_PIN_PC5)
#define ADC_SSTR_NUM                    (16U)
/**
 * @}
 */

/**
 * @defgroup ADC_Check_Parameters_Validity ADC check parameters validity
 * @{
 */
#define IS_ADC_1BIT_MASK(x)             (((x) != 0U) && (((x) & ((x) - 1U)) == 0U))
#define IS_ADC_BIT_MASK(x, mask)        (((x) != 0U) && (((x) | (mask)) == (mask)))

/* ADC unit check */
#define IS_ADC_UNIT(x)                                                         \
(   ((x) == CM_ADC1)                        ||                                 \
    ((x) == CM_ADC2)                        ||                                 \
    ((x) == CM_ADC3))

/* ADC sequence check */
#define IS_ADC_SEQ(x)                   (((x) == ADC_SEQ_A) || ((x) == ADC_SEQ_B))

/* ADC channel check */
#define IS_ADC_CH(adc, ch)                                                     \
(   (((adc) == CM_ADC1) && ((ch) <= ADC1_CH_MAX))   ||                         \
    (((adc) == CM_ADC2) && ((ch) <= ADC2_CH_MAX))   ||                         \
    (((adc) == CM_ADC3) && ((ch) <= ADC3_CH_MAX)))

#define IS_ADC_SCAN_MD(x)                                                      \
(   ((x) == ADC_MD_SEQA_SINGLESHOT)         ||                                 \
    ((x) == ADC_MD_SEQA_CONT)               ||                                 \
    ((x) == ADC_MD_SEQA_SEQB_SINGLESHOT)    ||                                 \
    ((x) == ADC_MD_SEQA_CONT_SEQB_SINGLESHOT))

#define IS_ADC_RESOLUTION(x)                                                   \
(   ((x) == ADC_RESOLUTION_8BIT)            ||                                 \
    ((x) == ADC_RESOLUTION_10BIT)           ||                                 \
    ((x) == ADC_RESOLUTION_12BIT))

#define IS_ADC_HARDTRIG(x)                                                     \
(   ((x) == ADC_HARDTRIG_ADTRG_PIN)         ||                                 \
    ((x) == ADC_HARDTRIG_EVT0)              ||                                 \
    ((x) == ADC_HARDTRIG_EVT1)              ||                                 \
    ((x) == ADC_HARDTRIG_EVT0_EVT1))

#define IS_ADC_DATAALIGN(x)                                                    \
(   ((x) == ADC_DATAALIGN_RIGHT)            ||                                 \
    ((x) == ADC_DATAALIGN_LEFT))

#define IS_ADC_SEQA_RESUME_MD(x)                                               \
(   ((x) == ADC_SEQA_RESUME_SCAN_CONT)      ||                                 \
    ((x) == ADC_SEQA_RESUME_SCAN_RESTART))

#define IS_ADC_SAMPLE_TIME(x)           ((x) >= 5U)

#define IS_ADC_INT(x)                   IS_ADC_BIT_MASK(x, ADC_INT_ALL)
#define IS_ADC_FLAG(x)                  IS_ADC_BIT_MASK(x, ADC_FLAG_ALL)

/* Scan-average. */
#define IS_ADC_AVG_CNT(x)               (((x) | ADC_AVG_CNT256) == ADC_AVG_CNT256)

/* Extended channel. */
#define IS_ADC_EXTCH_SRC(x)                                                    \
(   ((x) == ADC_EXTCH_EXTERN_ANALOG_PIN)    ||                                 \
    ((x) == ADC_EXTCH_INTERN_ANALOG_SRC))

/* Channel remapping. */
#define IS_ADC_REMAP_PIN(adc, pin)      (IS_ADC_UNIT(adc) && ((pin) <= ADC_REMAP_PIN_MAX))
#define IS_ADC_REMAP_CH(adc, ch)        (IS_ADC_UNIT(adc) && ((ch) <= ADC_REMAP_CH_MAX))

/* Sync mode. */
#define IS_ADC_SYNC_MD(x)                                                      \
(   ((x) == ADC_SYNC_SINGLE_DELAY_TRIG)     ||                                 \
    ((x) == ADC_SYNC_SINGLE_PARALLEL_TRIG)  ||                                 \
    ((x) == ADC_SYNC_CYCLIC_DELAY_TRIG)     ||                                 \
    ((x) == ADC_SYNC_CYCLIC_PARALLEL_TRIG))

#define IS_ADC_SYNC(x)                  (((x) == ADC_SYNC_ADC1_ADC2) || ((x) == ADC_SYNC_ADC1_ADC2_ADC3))

/* Analog watchdog. */
#define IS_ADC_AWD_MD(x)                                                       \
(   ((x) == ADC_AWD_MD_CMP_OUT)             ||                                 \
    ((x) == ADC_AWD_MD_CMP_IN))

#define IS_ADC_AWD(x)                   ((x) <= ADC_AWD1)

/* AWD flag check */
#define IS_ADC_AWD_FLAG(x)              IS_ADC_BIT_MASK(x, ADC_AWD_FLAG_ALL)

/* Two AWD units */
#define IS_ADC_AWD_COMB_MD(x)                                                  \
(   ((x) == ADC_AWD_COMB_INVD)              ||                                 \
    ((x) == ADC_AWD_COMB_OR)                ||                                 \
    ((x) == ADC_AWD_COMB_AND)               ||                                 \
    ((x) == ADC_AWD_COMB_XOR))

#define IS_ADC_AWD_INT(x)               IS_ADC_BIT_MASK(x, ADC_AWD_INT_ALL)

/* Sample hold. */
#define IS_ADC_SPLHOLD_SPLTIME(x)       ((x) >= 4U)

#define IS_ADC_SPLHOLD_UNIT(x)          ((x) == CM_ADC1)

#define IS_ADC_SH_CH(x)                 ((x) <= ADC_CH2)

/* PGA */
#define IS_ADC_PGA_GAIN(x)              ((x) <= ADC_PGA_GAIN_32)

#define IS_ADC_PGA_VSS(x)               (((x) == ADC_PGA_VSS_PGAVSS) || ((x) == ADC_PGA_VSS_AVSS))

/* PGA unit */
#define IS_ADC_PGA(adc, pga)                                                   \
(   (((adc) == CM_ADC1) && ((pga) <= ADC_PGA3))         ||                     \
    (((adc) == CM_ADC2) && ((pga) == ADC_PGA4)))

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
 * @defgroup ADC_Global_Functions ADC Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified ADC peripheral according to the specified parameters
 *         in the structure pstcAdcInit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  pstcAdcInit            Pointer to a @ref stc_adc_init_t structure that contains the
 *                                      configuration information for the specified ADC.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcAdcInit == NULL.
 */
int32_t ADC_Init(CM_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcAdcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    if (pstcAdcInit != NULL) {
        DDL_ASSERT(IS_ADC_SCAN_MD(pstcAdcInit->u16ScanMode));
        DDL_ASSERT(IS_ADC_RESOLUTION(pstcAdcInit->u16Resolution));
        DDL_ASSERT(IS_ADC_DATAALIGN(pstcAdcInit->u16DataAlign));
        /* Configures scan mode, resolution, data align. */
        WRITE_REG16(ADCx->CR0, pstcAdcInit->u16ScanMode | pstcAdcInit->u16Resolution | pstcAdcInit->u16DataAlign);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Deinitialize the specified ADC peripheral registers to their default reset values.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 */
int32_t ADC_DeInit(CM_ADC_TypeDef *ADCx)
{
    uint8_t i;
    __IO uint8_t *reg8SSTR;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    /* Stop the ADC. */
    WRITE_REG8(ADCx->STR, 0U);
    /* Set the registers to reset value. */
    WRITE_REG16(ADCx->CR0, 0x0U);
    WRITE_REG16(ADCx->CR1, 0x0U);
    WRITE_REG16(ADCx->TRGSR, 0x0U);
    WRITE_REG32(ADCx->CHSELRA, 0x0U);
    WRITE_REG32(ADCx->CHSELRB, 0x0U);
    WRITE_REG8(ADCx->ICR, 0x03U);
    WRITE_REG32(ADCx->AVCHSELR, 0x0U);

    /* SSTRx */
    reg8SSTR = (__IO uint8_t *)((uint32_t)&ADCx->SSTR0);
    for (i = 0U; i < ADC_SSTR_NUM; i++) {
        reg8SSTR[i] = 0x0BU;
    }

    /* SSTRL */
    if (ADCx == CM_ADC3) {
        WRITE_REG8(ADCx->SSTRL, 0x0BU);
    }

    /* CHMUXRx */
    WRITE_REG16(ADCx->CHMUXR0, 0x3210U);
    WRITE_REG16(ADCx->CHMUXR1, 0x7654U);
    WRITE_REG16(ADCx->CHMUXR2, 0xBA98U);
    WRITE_REG16(ADCx->CHMUXR3, 0xFEDCU);

    /* ISR clearing */
    WRITE_REG8(ADCx->ISCLRR, 0x13U);

    /* Sync mode */
    WRITE_REG16(ADCx->SYNCCR, 0x0C00U);

    /* Analog watchdog */
    WRITE_REG16(ADCx->AWDCR, 0x0U);
    WRITE_REG8(ADCx->AWDSCLRR, 0x13U);
    WRITE_REG16(ADCx->AWD0DR0, 0x0U);
    WRITE_REG16(ADCx->AWD0DR1, 0xFFFFU);
    WRITE_REG16(ADCx->AWD1DR0, 0x0U);
    WRITE_REG16(ADCx->AWD1DR1, 0xFFFFU);
    WRITE_REG8(ADCx->AWD0CHSR, 0x0U);
    WRITE_REG8(ADCx->AWD1CHSR, 0x0U);

    /* Sample hold */
    WRITE_REG16(ADCx->SHCR, 0x0U);

    /* PGA and OPA */
    if (ADCx == CM_ADC1) {
        WRITE_REG8(ADCx->PGACR1, 0x0U);
        WRITE_REG8(ADCx->PGACR2, 0x0U);
        WRITE_REG8(ADCx->PGACR3, 0x0U);
        WRITE_REG8(ADCx->PGAVSSENR, 0x0U);
    } else if (ADCx == CM_ADC2) {
        WRITE_REG8(ADCx->PGACR1, 0x0U);
        WRITE_REG8(ADCx->PGAVSSENR, 0x0U);
    } else {
        /* rsvd */
    }
    return LL_OK;
}

/**
 * @brief  Set each @ref stc_adc_init_t field to default value.
 * @param  [in]  pstcAdcInit            Pointer to a @ref stc_adc_init_t structure
 *                                      whose fields will be set to default values.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcAdcInit == NULL.
 */
int32_t ADC_StructInit(stc_adc_init_t *pstcAdcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcAdcInit != NULL) {
        pstcAdcInit->u16ScanMode   = ADC_MD_SEQA_SINGLESHOT;
        pstcAdcInit->u16Resolution = ADC_RESOLUTION_12BIT;
        pstcAdcInit->u16DataAlign  = ADC_DATAALIGN_RIGHT;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable the specified ADC channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Seq                  The sequence whose channel specified by 'u8Ch' will be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   ADC sequence A.
 *   @arg  ADC_SEQ_B:                   ADC sequence B.
 * @param  [in]  u8Ch                   The ADC channel.
 *                                      This parameter can be values of @ref ADC_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @note   Sequence A and Sequence B CAN NOT include the same channel!
 * @note   Sequence A can always started by software(by calling @ref ADC_Start()),
 *         regardless of whether the hardware trigger source is valid or not.
 * @note   Sequence B must be specified a valid hard trigger by calling functions @ref ADC_TriggerConfig()
 *         and @ref ADC_TriggerCmd().
 */
void ADC_ChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, uint8_t u8Ch, en_functional_state_t enNewState)
{
    uint32_t u32CHSELAddr;

    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));
    DDL_ASSERT(IS_ADC_SEQ(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32CHSELAddr = (uint32_t)&ADCx->CHSELRA + (u8Seq * 4UL);
    if (enNewState == ENABLE) {
        /* Enable the specified channel. */
        SET_REG32_BIT(RW_MEM32(u32CHSELAddr), 1UL << u8Ch);
    } else {
        /* Disable the specified channel. */
        CLR_REG32_BIT(RW_MEM32(u32CHSELAddr), 1UL << u8Ch);
    }
}

/**
 * @brief  Set sampling time for the specified channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   The channel to be set sampling time.
 *                                      This parameter can be values of @ref ADC_Channel
 * @param  [in]  u8SampleTime           Sampling time for the channel that specified by 'u8Ch'.
 * @retval None
 */
void ADC_SetSampleTime(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, uint8_t u8SampleTime)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_SAMPLE_TIME(u8SampleTime));

    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));
    if (u8Ch < ADC_SSTR_NUM) {
        u32Addr = (uint32_t)&ADCx->SSTR0 + u8Ch;
        WRITE_REG8(RW_MEM8(u32Addr), u8SampleTime);
    } else {
        WRITE_REG8(ADCx->SSTRL, u8SampleTime);
    }
}

/**
 * @brief  Set scan-average count.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u16AverageCount        Scan-average count.
 *                                      This parameter can be a value of @ref ADC_Average_Count
 *   @arg  ADC_AVG_CNT2:                2 consecutive average conversions.
 *   @arg  ADC_AVG_CNT4:                4 consecutive average conversions.
 *   @arg  ADC_AVG_CNT8:                8 consecutive average conversions.
 *   @arg  ADC_AVG_CNT16:               16 consecutive average conversions.
 *   @arg  ADC_AVG_CNT32:               32 consecutive average conversions.
 *   @arg  ADC_AVG_CNT64:               64 consecutive average conversions.
 *   @arg  ADC_AVG_CNT128:              128 consecutive average conversions.
 *   @arg  ADC_AVG_CNT256:              256 consecutive average conversions.
 * @retval None
 */
void ADC_ConvDataAverageConfig(CM_ADC_TypeDef *ADCx, uint16_t u16AverageCount)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AVG_CNT(u16AverageCount));
    MODIFY_REG16(ADCx->CR0, ADC_CR0_AVCNT, u16AverageCount);
}

/**
 * @brief  Enable or disable conversion data average calculation channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   The ADC channel.
 *                                      This parameter can be values of @ref ADC_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_ConvDataAverageChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG32_BIT(ADCx->AVCHSELR, 1UL << u8Ch);
    } else {
        CLR_REG32_BIT(ADCx->AVCHSELR, 1UL << u8Ch);
    }
}

/**
 * @brief  Specifies the analog input source of extended channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8ExtChSrc             The analog input source of extended channel.
 *                                      This parameter can be a value of @ref ADC_Ext_Ch_Analog_Src
 * @retval None
 */
void ADC_SetExtChSrc(CM_ADC_TypeDef *ADCx, uint8_t u8ExtChSrc)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_EXTCH_SRC(u8ExtChSrc));
    WRITE_REG8(ADCx->EXCHSELR, u8ExtChSrc);
}

/**
 * @brief  Specifies the hard trigger for the specified ADC sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADCx or CM_ADC
 * @param  [in]  u8Seq                  The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  u16TriggerSel          Hard trigger selection. This parameter can be a value of @ref ADC_Hard_Trigger_Sel
 *   @arg  ADC_HARDTRIG_ADTRG_PIN:      Selects the following edge of pin ADTRG as the trigger of ADC sequence.
 *   @arg  ADC_HARDTRIG_EVT0:           Selects an internal event as the trigger of ADC sequence.
                                        This event is specified by register ADCx_TRGSEL0(x=(null), 1, 2, 3).
 *   @arg  ADC_HARDTRIG_EVT1:           Selects an internal event as the trigger of ADC sequence.
                                        This event is specified by register ADCx_TRGSEL1(x=(null), 1, 2, 3).
 *   @arg  ADC_HARDTRIG_EVT0_EVT1:      Selects two internal events as the trigger of ADC sequence.
                                        The two events are specified by register ADCx_TRGSEL0 and register ADCx_TRGSEL1.
 * @retval None
 * @note   ADC must be stopped while calling this function.
 * @note   The trigger source CANNOT be an event that generated by the sequence itself.
 */
void ADC_TriggerConfig(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, uint16_t u16TriggerSel)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u8Seq));
    DDL_ASSERT(IS_ADC_HARDTRIG(u16TriggerSel));

    u8Seq *= ADC_TRGSR_TRGSELB_POS;
    MODIFY_REG16(ADCx->TRGSR, (uint32_t)ADC_TRGSR_TRGSELA << u8Seq, (uint32_t)u16TriggerSel << u8Seq);
}

/**
 * @brief  Enable or disable the hard trigger of the specified ADC sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADCx or CM_ADC
 * @param  [in]  u8Seq                  The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   ADC must be stopped while calling this function.
 */
void ADC_TriggerCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&ADCx->TRGSR;
    /* Enable bit position: u8Seq * sequence_offset + enable_bit_base. */
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, (uint32_t)u8Seq * ADC_TRGSR_TRGSELB_POS + ADC_TRGSR_TRGENA_POS), enNewState);
}

/**
 * @brief  Enable or disable ADC interrupts.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8IntType              ADC interrupt.
 *                                      This parameter can be values of @ref ADC_Int_Type
 *   @arg  ADC_INT_EOCA:                Interrupt of the end of conversion of sequence A.
 *   @arg  ADC_INT_EOCB:                Interrupt of the end of conversion of sequence B.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_IntCmd(CM_ADC_TypeDef *ADCx, uint8_t u8IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_INT(u8IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG8_BIT(ADCx->ICR, u8IntType);
    } else {
        CLR_REG8_BIT(ADCx->ICR, u8IntType);
    }
}

/**
 * @brief  Start sequence A conversion.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @retval None
 */
void ADC_Start(CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    WRITE_REG8(ADCx->STR, ADC_STR_STRT);
}

/**
 * @brief  Stop ADC conversion, both sequence A and sequence B.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @retval None
 */
void ADC_Stop(CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    WRITE_REG8(ADCx->STR, 0U);
}

/**
 * @brief  Get the ADC value of the specified channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   The ADC channel.
 *                                      This parameter can be values of @ref ADC_Channel
 * @retval An uint16_t type value of ADC value.
 */
uint16_t ADC_GetValue(const CM_ADC_TypeDef *ADCx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));

    return RW_MEM16((uint32_t)&ADCx->DR0 + u8Ch * 2UL);
}

/**
 * @brief  Get the ADC resolution.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @retval An uint16_t type value of ADC resolution.
 */
uint16_t ADC_GetResolution(const CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    return (READ_REG16_BIT(ADCx->CR0, ADC_CR0_ACCSEL));
}

/**
 * @brief  Get the status of the specified ADC flag.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Flag                 ADC status flag.
 *                                      This parameter can be a value of @ref ADC_Status_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ADC_GetStatus(const CM_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_FLAG(u8Flag));

    if (READ_REG8_BIT(ADCx->ISR, u8Flag) != 0U) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified ADC flag.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Flag                 ADC status flag.
 *                                      This parameter can be valueS of @ref ADC_Status_Flag
 * @retval None
 */
void ADC_ClearStatus(CM_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_FLAG(u8Flag));

    WRITE_REG8(ADCx->ISCLRR, u8Flag);
}

/**
 * @brief  Remap the correspondence between ADC channel and analog input pins.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   This parameter can be values of @ref ADC_Channel
 * @param  [in]  u8AdcPin               This parameter can be a value of @ref ADC_Remap_Pin
 * @retval None
 */
void ADC_ChRemap(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, uint8_t u8AdcPin)
{
    uint8_t u8FieldOfs;
    uint8_t u8RegIdx;
    __IO uint16_t *regCHMUXR;

    DDL_ASSERT(IS_ADC_REMAP_CH(ADCx, u8Ch));
    DDL_ASSERT(IS_ADC_REMAP_PIN(ADCx, u8AdcPin));

    regCHMUXR  = (__IO uint16_t *)((uint32_t)&ADCx->CHMUXR0);
    u8RegIdx   = u8Ch / 4U;
    u8FieldOfs = (u8Ch % 4U) * 4U;
    MODIFY_REG16(regCHMUXR[u8RegIdx], ((uint32_t)ADC_CHMUXR0_CH00MUX << u8FieldOfs), ((uint32_t)u8AdcPin << u8FieldOfs));
}

/**
 * @brief  Get the ADC pin corresponding to the specified ADC channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   ADC channel.
 *                                      This parameter can be one of the following values of @ref ADC_Channel
 * @retval An uint8_t type value of ADC pin. @ref ADC_Remap_Pin
 */
uint8_t ADC_GetChPin(const CM_ADC_TypeDef *ADCx, uint8_t u8Ch)
{
    uint8_t u8RetPin;
    uint8_t u8FieldOfs;
    uint8_t u8RegIdx;
    __IO uint16_t *regCHMUXR;

    DDL_ASSERT(IS_ADC_REMAP_CH(ADCx, u8Ch));

    regCHMUXR  = (__IO uint16_t *)((uint32_t)&ADCx->CHMUXR0);
    u8RegIdx   = u8Ch / 4U;
    u8FieldOfs = (u8Ch % 4U) * 4U;
    u8RetPin   = ((uint8_t)(regCHMUXR[u8RegIdx] >> u8FieldOfs)) & 0xFU;

    return u8RetPin;
}

/**
 * @brief  Reset channel-pin mapping.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @retval None
 */
void ADC_ResetChMapping(CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    WRITE_REG16(ADCx->CHMUXR0, 0x3210U);
    WRITE_REG16(ADCx->CHMUXR1, 0x7654U);
    WRITE_REG16(ADCx->CHMUXR2, 0xBA98U);
    WRITE_REG16(ADCx->CHMUXR3, 0xFEDCU);
}

/**
 * @brief  Configures synchronous mode.
 * @param  [in]  u16SyncUnit            Specify the ADC units which work synchronously.
 *                                      This parameter can be a value of @ref ADC_Sync_Unit
 * @param  [in]  u16SyncMode            Synchronous mode.
 *                                      This parameter can be a value of @ref ADC_Sync_Mode
 *   @arg  ADC_SYNC_SINGLE_DELAY_TRIG:  Single shot delayed trigger mode.
 *                                      When the trigger condition occurs, ADC1 starts first, then ADC2, last ADC3(if has).
 *                                      All ADCs scan once.
 *   @arg  ADC_SYNC_SINGLE_PARALLEL_TRIG: Single shot parallel trigger mode.
 *                                        When the trigger condition occurs, all ADCs start at the same time.
 *                                        All ADCs scan once.
 *   @arg  ADC_SYNC_CYCLIC_DELAY_TRIG:  Cyclic delayed trigger mode.
 *                                      When the trigger condition occurs, ADC1 starts first, then ADC2, last ADC3(if has).
 *                                      All ADCs scan cyclicly(keep scanning till you stop them).
 *   @arg  ADC_SYNC_CYCLIC_PARALLEL_TRIG: Single shot parallel trigger mode.
 *                                        When the trigger condition occurs, all ADCs start at the same time.
 *                                        All ADCs scan cyclicly(keep scanning till you stop them).
 * @param  [in]  u8TriggerDelay         Trigger delay time(ADCLK cycle), range is [1, 255].
 * @retval None
 */
void ADC_SyncModeConfig(uint16_t u16SyncUnit, uint16_t u16SyncMode, uint8_t u8TriggerDelay)
{
    DDL_ASSERT(IS_ADC_SYNC(u16SyncUnit));
    DDL_ASSERT(IS_ADC_SYNC_MD(u16SyncMode));

    u16SyncMode |= ((uint16_t)((uint32_t)u8TriggerDelay << ADC_SYNCCR_SYNCDLY_POS)) | u16SyncUnit;
    MODIFY_REG16(CM_ADC1->SYNCCR, ADC_SYNCCR_SYNCMD | ADC_SYNCCR_SYNCDLY, u16SyncMode);
}

/**
 * @brief  Enable or disable synchronous mode.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_SyncModeCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_ADC1->SYNCCR_b.SYNCEN, enNewState);
}

/**
 * @brief  Configures analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @param  [in]  u8Ch                   The channel that to be used as an analog watchdog channel.
 *                                      This parameter can be a value of @ref ADC_Channel
 * @param  [in]  pstcAwd                Pointer to a @ref stc_adc_awd_config_t structure value that
 *                                      contains the configuration information of the AWD.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcAwd == NULL.
 */
int32_t ADC_AWD_Config(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint8_t u8Ch, const stc_adc_awd_config_t *pstcAwd)
{
    uint32_t u32AwdDr0;
    uint32_t u32AwdDr1;
    uint32_t u32AwdChsr;
    uint32_t u32Addr;
    uint8_t u8Pos;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));

    if (pstcAwd != NULL) {
        DDL_ASSERT(IS_ADC_AWD_MD(pstcAwd->u16WatchdogMode));

        u8Pos      = (u8AwdUnit * 4U) + ADC_AWDCR_AWD0MD_POS;
        u32Addr    = (uint32_t)&ADCx->AWDCR;
        u32AwdDr0  = (uint32_t)&ADCx->AWD0DR0;
        u32AwdDr1  = (uint32_t)&ADCx->AWD0DR1;
        u32AwdChsr = (uint32_t)&ADCx->AWD0CHSR;

        WRITE_REG32(PERIPH_BIT_BAND(u32Addr, u8Pos), pstcAwd->u16WatchdogMode);
        WRITE_REG16(ADC_AWDx_DR(u8AwdUnit, u32AwdDr0), pstcAwd->u16LowThreshold);
        WRITE_REG16(ADC_AWDx_DR(u8AwdUnit, u32AwdDr1), pstcAwd->u16HighThreshold);
        WRITE_REG8(ADC_AWDx_CHSR(u8AwdUnit, u32AwdChsr), u8Ch);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Specifies combination mode of analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u16CombMode            Combination mode of analog watchdog.
 *                                      This parameter can be a value of @ref ADC_AWD_Comb_Mode
 *   @arg  ADC_AWD_COMB_INVD            Combination mode is invalid.
 *   @arg  ADC_AWD_COMB_OR:             The status of AWD0 is set or the status of AWD1 is set, the status of combination mode is set.
 *   @arg  ADC_AWD_COMB_AND:            The status of AWD0 is set and the status of AWD1 is set, the status of combination mode is set.
 *   @arg  ADC_AWD_COMB_XOR:            Only one of the status of AWD0 and AWD1 is set, the status of combination mode is set.
 * @retval None
 */
void ADC_AWD_SetCombMode(CM_ADC_TypeDef *ADCx, uint16_t u16CombMode)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD_COMB_MD(u16CombMode));
    MODIFY_REG16(ADCx->AWDCR, ADC_AWDCR_AWDCM, u16CombMode);
}

/**
 * @brief  Specifies the compare mode of analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @param  [in]  u16WatchdogMode        Analog watchdog compare mode.
 *                                      This parameter can be a value of @ref ADC_AWD_Mode
 *   @arg  ADC_AWD_MD_CMP_OUT:          ADCValue > HighThreshold or ADCValue < LowThreshold
 *   @arg  ADC_AWD_MD_CMP_IN:           LowThreshold < ADCValue < HighThreshold
 * @retval None
 */
void ADC_AWD_SetMode(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint16_t u16WatchdogMode)
{
    uint8_t u8Pos;
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));
    DDL_ASSERT(IS_ADC_AWD_MD(u16WatchdogMode));

    u8Pos   = (u8AwdUnit * 4U) + ADC_AWDCR_AWD0MD_POS;
    u32Addr = (uint32_t)&ADCx->AWDCR;
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, u8Pos), u16WatchdogMode);
}

/**
 * @brief  Get the compare mode of analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @retval Analog watchdog compare mode. A value of @ref ADC_AWD_Mode
 *         - ADC_AWD_MD_CMP_OUT:        ADCValue > HighThreshold or ADCValue < LowThreshold
 *         - ADC_AWD_MD_CMP_IN:         LowThreshold < ADCValue < HighThreshold
 */
uint16_t ADC_AWD_GetMode(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit)
{
    uint16_t u16RetMode;

    uint8_t u8Pos;
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));

    u8Pos   = (u8AwdUnit * 4U) + ADC_AWDCR_AWD0MD_POS;
    u32Addr = (uint32_t)&ADCx->AWDCR;
    u16RetMode = (uint16_t)PERIPH_BIT_BAND(u32Addr, u8Pos);

    return u16RetMode;
}

/**
 * @brief  Specifies the low threshold and high threshold of analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @param  [in]  u16LowThreshold        Low threshold of analog watchdog.
 * @param  [in]  u16HighThreshold       High threshold of analog watchdog.
 * @retval None
 */
void ADC_AWD_SetThreshold(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint16_t u16LowThreshold, uint16_t u16HighThreshold)
{
    uint32_t u32AwdDr0;
    uint32_t u32AwdDr1;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));

    u32AwdDr0 = (uint32_t)&ADCx->AWD0DR0;
    u32AwdDr1 = (uint32_t)&ADCx->AWD0DR1;
    WRITE_REG16(ADC_AWDx_DR(u8AwdUnit, u32AwdDr0), u16LowThreshold);
    WRITE_REG16(ADC_AWDx_DR(u8AwdUnit, u32AwdDr1), u16HighThreshold);
}

/**
 * @brief  Select the specified ADC channel as an analog watchdog channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @param  [in]  u8Ch                   The channel that to be used as an analog watchdog channel.
 *                                      This parameter can be a value of @ref ADC_Channel
 * @retval None
 */
void ADC_AWD_SelectCh(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, uint8_t u8Ch)
{
    uint32_t u32AwdChsr;
    DDL_ASSERT(IS_ADC_CH(ADCx, u8Ch));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));

    u32AwdChsr = (uint32_t)&ADCx->AWD0CHSR;
    WRITE_REG8(ADC_AWDx_CHSR(u8AwdUnit, u32AwdChsr), u8Ch);
}

/**
 * @brief  Enable or disable the specified analog watchdog.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8AwdUnit              AWD unit that is going to be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_AWD_Cmd(CM_ADC_TypeDef *ADCx, uint8_t u8AwdUnit, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD(u8AwdUnit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&ADCx->AWDCR;
    /* Enable bit position: u8AwdUnit * 4 */
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, (u8AwdUnit * 4UL)), enNewState);
}

/**
 * @brief  Enable or disable the specified analog watchdog interrupts.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u16IntType             Interrupt of AWD.
 *                                      This parameter can be a value of @ref ADC_AWD_Int_Type
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_AWD_IntCmd(CM_ADC_TypeDef *ADCx, uint16_t u16IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD_INT(u16IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(ADCx->AWDCR, u16IntType);
    } else {
        CLR_REG16_BIT(ADCx->AWDCR, u16IntType);
    }
}

/**
 * @brief  Get the status of the specified analog watchdog flag.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u32Flag                AWD status flag.
 *                                      This parameter can be values of @ref ADC_AWD_Status_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t ADC_AWD_GetStatus(const CM_ADC_TypeDef *ADCx, uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD_FLAG(u32Flag));
    if (READ_REG8_BIT(ADCx->AWDSR, u32Flag) != 0U) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified analog watchdog flag.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u32Flag                AWD status flag.
 *                                      This parameter can be values of @ref ADC_AWD_Status_Flag
 * @retval None
 */
void ADC_AWD_ClearStatus(CM_ADC_TypeDef *ADCx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AWD_FLAG(u32Flag));
    WRITE_REG8(ADCx->AWDSCLRR, u32Flag);
}

/**
 * @brief  Specifies sampling time of sample-hold.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8SampleTime           Sampling time of sample hold.
 * @retval None
 */
void ADC_SH_SetSampleTime(CM_ADC_TypeDef *ADCx, uint8_t u8SampleTime)
{
    DDL_ASSERT(IS_ADC_SPLHOLD_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SPLHOLD_SPLTIME(u8SampleTime));
    MODIFY_REG16(ADCx->SHCR, ADC_SHCR_SHSST, u8SampleTime);
}

/**
 * @brief  Enable or disable sample-hold channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8Ch                   Sample hold channel.
 *                                      This parameter can be ADC_CH0, ADC_CH1 and ADC_CH2 of @ref ADC_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_SH_ChCmd(CM_ADC_TypeDef *ADCx, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_SPLHOLD_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SH_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(ADCx->SHCR, (1UL << u8Ch) << ADC_SHCR_SHSEL_POS);
    } else {
        CLR_REG16_BIT(ADCx->SHCR, (1UL << u8Ch) << ADC_SHCR_SHSEL_POS);
    }
}

/**
 * @brief  Configures the specified programmable gain amplifier.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8PgaUnit              The PGA unit.
 *                                      This parameter can be a value of @ref ADC_PGA_Unit
 * @param  [in]  u8Gain                 Gain of the specified PGA.
 *                                      This parameter can be a value of @ref ADC_PGA_Gain
 *   @arg  ADC_PGA_GAIN_2:              PGA gain factor is 2.
 *   @arg  ADC_PGA_GAIN_2P133:          PGA gain factor is 2.133.
 *   @arg  ADC_PGA_GAIN_2P286:          PGA gain factor is 2.286.
 *   @arg  ADC_PGA_GAIN_2P667:          PGA gain factor is 2.667.
 *   @arg  ADC_PGA_GAIN_2P909:          PGA gain factor is 2.909.
 *   @arg  ADC_PGA_GAIN_3P2:            PGA gain factor is 3.2.
 *   @arg  ADC_PGA_GAIN_3P556:          PGA gain factor is 2.556.
 *   @arg  ADC_PGA_GAIN_4:              PGA gain factor is 4.
 *   @arg  ADC_PGA_GAIN_4P571:          PGA gain factor is 4.571.
 *   @arg  ADC_PGA_GAIN_5P333:          PGA gain factor is 5.333.
 *   @arg  ADC_PGA_GAIN_6P4:            PGA gain factor is 6.4.
 *   @arg  ADC_PGA_GAIN_8:              PGA gain factor is 8.
 *   @arg  ADC_PGA_GAIN_10P667:         PGA gain factor is 10.667.
 *   @arg  ADC_PGA_GAIN_16:             PGA gain factor is 16.
 *   @arg  ADC_PGA_GAIN_32:             PGA gain factor is 32.
 * @param  [in]  u8PgaVss               VSS for the specified PGA.
 *                                      This parameter can be a value of @ref ADC_PGA_VSS
 *   @arg  ADC_PGA_VSS_PGAVSS:          Use pin PGAx_VSS as the reference GND of PGAx
 *   @arg  ADC_PGA_VSS_AVSS:            Use AVSS as the reference GND of PGAx.
 * @retval None
 */
void ADC_PGA_Config(CM_ADC_TypeDef *ADCx, uint8_t u8PgaUnit, uint8_t u8Gain, uint8_t u8PgaVss)
{
    uint32_t u32Addr;
    uint32_t u32PGACRAddr;
    DDL_ASSERT(IS_ADC_PGA(ADCx, u8PgaUnit));
    DDL_ASSERT(IS_ADC_PGA_GAIN(u8Gain));
    DDL_ASSERT(IS_ADC_PGA_VSS(u8PgaVss));

    if (ADCx == CM_ADC2) {
        u8PgaUnit = 0U;
    }
    u32PGACRAddr = (uint32_t)&ADCx->PGACR1 + u8PgaUnit;
    MODIFY_REG8(RW_MEM8(u32PGACRAddr), ADC_PGACR_PGAGAIN, u8Gain << ADC_PGACR_PGAGAIN_POS);
    u32Addr = (uint32_t)&ADCx->PGAVSSENR;
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, u8PgaUnit), u8PgaVss);
}

/**
 * @brief  Enable the specified programmable gain amplifier.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u8PgaUnit              The PGA unit.
 *                                      This parameter can be a value of @ref ADC_PGA_Unit
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_PGA_Cmd(CM_ADC_TypeDef *ADCx, uint8_t u8PgaUnit, en_functional_state_t enNewState)
{
    const uint8_t au8Cmd[] = {ADC_PGA_DISABLE, ADC_PGA_ENABLE};
    uint32_t u32PGACRAddr;

    DDL_ASSERT(IS_ADC_PGA(ADCx, u8PgaUnit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ADCx == CM_ADC2) {
        u8PgaUnit = 0U;
    }
    u32PGACRAddr = (uint32_t)&ADCx->PGACR1 + u8PgaUnit;
    MODIFY_REG8(RW_MEM8(u32PGACRAddr), ADC_PGACR_PGACTL, au8Cmd[(uint8_t)enNewState]);
}

/**
 * @brief  Enable or disable automatically clear data register.
 *         The automatic clearing function is mainly used to detect whether the data register is updated.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void ADC_DataRegAutoClearCmd(CM_ADC_TypeDef *ADCx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(ADCx->CR0, ADC_CR0_CLREN);
    } else {
        CLR_REG16_BIT(ADCx->CR0, ADC_CR0_CLREN);
    }
}

/**
 * @brief  Sequence A restart channel selection.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC or CM_ADCx:           ADC instance register base.
 * @param  [in]  u16SeqAResumeMode      Sequence A resume mode.
 *                                      This parameter can be a value of @ref ADC_SeqA_Resume_Mode
 *   @arg  ADC_SEQA_RESUME_SCAN_CONT:   Scanning will continue from the interrupted channel.
 *   @arg  ADC_SEQA_RESUME_SCAN_RESTART: Scanning will start from the first channel.
 * @retval None
 */
void ADC_SetSeqAResumeMode(CM_ADC_TypeDef *ADCx, uint16_t u16SeqAResumeMode)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQA_RESUME_MD(u16SeqAResumeMode));
    WRITE_REG16(ADCx->CR1, u16SeqAResumeMode);
}

/**
 * @}
 */

#endif /* LL_ADC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
