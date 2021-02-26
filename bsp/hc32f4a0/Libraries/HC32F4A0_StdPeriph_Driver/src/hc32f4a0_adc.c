/**
 *******************************************************************************
 * @file  hc32f4a0_adc.c
 * @brief This file provides firmware functions to manage the Analog-to-Digital
 *        Converter(ADC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-07-02       Wuze            1. API ADC_SH_ChannelCmd() refine.
                                    2. Some other optimizations.
   2020-08-10       Wuze            ADC_SeqClrStatus(): ADC_SEQ_FLAG_NESTED can be cleared.
   2020-12-15       Wuze            ADC_ComTriggerCmd() refine.
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
#include "hc32f4a0_adc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_ADC ADC
 * @brief Analog-to-Digital Converter Driver Library
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

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
 * @defgroup ADC_Unit_Base_Address ADC Unit Base Address
 * @{
 */
#define ADC1_BASE                           (0x40040000UL)
#define ADC2_BASE                           (0x40040400UL)
#define ADC3_BASE                           (0x40040800UL)
/**
 * @}
 */

/**
 * @defgroup ADC_Configuration_Bit_Mask ADC Configuration Bit Mask
 * @{
 */
#define ADC_TRIG_SRC_MSK                    (ADC_TRGSR_TRGSELA)
#define ADC_AWD_COMB_MODE_MSK               (ADC_AWDCR_AWDCM)
#define ADC_PGA_CMD_MSK                     (ADC_PGACR1_PGACTL)
#define ADC_PGA_GAIN_MSK                    (ADC_PGACR1_PGAGAIN)
#define ADC_SYNC_CFG_MSK                    (ADC_SYNCCR_SYNCMD | ADC_SYNCCR_SYNCDLY)
#define ADC_CH_MAP_PIN_MSK                  (ADC_CHMUXR0_CH00MUX)
#define ADC_SH_CFG_MSK                      (ADC_SHCR_SHSST)
#define ADC_SH_CH_MSK                       (ADC_SHCR_SHSEL)
#define ADC_COM_TRIG_MSK                    (ADC_COM_TRIG1 | ADC_COM_TRIG2)
#define ADC_TRIG_EVENT_MSK                  (AOS_ADC_1_ITRGSELR_TRGSEL)
/**
 * @}
 */

/**
 * @defgroup ADC_PGA_Command ADC PGA Command
 * @{
 */
#define ADC_PGA_DISABLE                     (0x0U)
#define ADC_PGA_ENABLE                      (0xEU)
/**
 * @}
 */

/**
 * @defgroup ADC_Unit_Number ADC Unit Number
 * @{
 */
#define __ADC_BASE                          (ADC1_BASE)
#define __ADC_UNIT_SIZE                     (0x400UL)
#define ADC_IDX(__ADCx__)                   ((uint8_t)(((uint32_t)&(__ADCx__)->STR - __ADC_BASE) / __ADC_UNIT_SIZE))
/**
 * @}
 */

/**
 * @defgroup ADC_Register_Bit_Band ADC Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(regAddr)                  ((regAddr) - __PERIP_BASE)
#define __BIT_BAND_ADDR(regAddr, pos)       ((__REG_OFS(regAddr) << 5U) + ((uint32_t)(pos) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(regAddr, pos)              (*(__IO uint32_t *)__BIT_BAND_ADDR((regAddr), (pos)))
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_Configuration_Bit_Field_Offset ADC Sequence Configuration Bit Field Offset
 * @{
 */
#define ADC_OFS_TRGSR(__seq__)              ((uint32_t)(__seq__) * ADC_TRGSR_TRGSELB_POS)
#define ADC_OFS_AWDCR(__num__)              ((uint32_t)(__num__) * ADC_AWDCR_AWD1EN)
/**
 * @}
 */

/**
 * @defgroup ADC_Register_Configuration_Value ADC Register Configuration Value
 * @{
 */
#define ADC_TRGSR_VAL(__seq__, __val__)     ((uint32_t)(__val__) << ADC_OFS_TRGSR(__seq__))
#define ADC_AWDCR_VAL(__num__, __val__)     ((uint32_t)(__val__) << ADC_OFS_AWDCR(__num__))
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_DR ADC AWD DR
 * @{
 */
#define ADC_AWDx_DR(__base__, __awdNum__)   (*(__IO uint32_t *)((uint32_t)(__base__) + ((uint32_t)(__awdNum__) << 3U)))
/**
 * @}
 */

/**
 * @defgroup ADC_AWD_CHSR ADC AWD CHSR
 * @{
 */
#define ADC_AWDx_CHSR(__base__, __awdNum__) (*(__IO uint32_t *)((uint32_t)(__base__) + ((uint32_t)(__awdNum__) << 3U)))
/**
 * @}
 */

/**
 * @defgroup ADC_Check_Parameters_Validity ADC check parameters validity
 * @{
 */
#define IS_ADC_UNIT(x)                                                         \
(   ((x) == M4_ADC1)                        ||                                 \
    ((x) == M4_ADC2)                        ||                                 \
    ((x) == M4_ADC3))

#define IS_ADC_SEQ(x)                                                          \
(   ((x) == ADC_SEQ_A)                      ||                                 \
    ((x) == ADC_SEQ_B))

#define IS_ADC_SCAN_MODE(x)                                                    \
(   ((x) == ADC_MODE_SA_SSHOT)              ||                                 \
    ((x) == ADC_MODE_SA_CONT)               ||                                 \
    ((x) == ADC_MODE_SA_SB_SSHOT)           ||                                 \
    ((x) == ADC_MODE_SA_CONT_SB_SSHOT))

#define IS_ADC_RESOLUTION(x)                                                   \
(   ((x) == ADC_RESOLUTION_8BIT)            ||                                 \
    ((x) == ADC_RESOLUTION_10BIT)           ||                                 \
    ((x) == ADC_RESOLUTION_12BIT))

#define IS_ADC_TRIG_SRC(x)                                                     \
(   ((x) == ADC_TRIG_SRC_ADTRG)             ||                                 \
    ((x) == ADC_TRIG_SRC_EVENT0)            ||                                 \
    ((x) == ADC_TRIG_SRC_EVENT1)            ||                                 \
    ((x) == ADC_TRIG_SRC_EVENT0_EVENT1))

#define IS_ADC_AUTO_CLEAR_CMD(x)                                               \
(   ((x) == ADC_AUTO_CLR_DISABLE)           ||                                 \
    ((x) == ADC_AUTO_CLR_ENABLE))

#define IS_ADC_DATA_ALIGN(x)                                                   \
(   ((x) == ADC_DATA_ALIGN_RIGHT)           ||                                 \
    ((x) == ADC_DATA_ALIGN_LEFT))

#define IS_ADC_SA_RESUME_POS(x)                                                \
(   ((x) == ADC_SA_RESUME_POS_INT_CH)       ||                                 \
    ((x) == ADC_SA_RESUME_POS_FIRST_CH))

#define IS_ADC_SAMPLE_TIME(x)                                                  \
(   ((x) >= 5U))

#define IS_ADC_AVG_CNT(x)                                                      \
(   ((x) == ADC_AVG_CNT_2)                  ||                                 \
    ((x) == ADC_AVG_CNT_4)                  ||                                 \
    ((x) == ADC_AVG_CNT_8)                  ||                                 \
    ((x) == ADC_AVG_CNT_16)                 ||                                 \
    ((x) == ADC_AVG_CNT_32)                 ||                                 \
    ((x) == ADC_AVG_CNT_64)                 ||                                 \
    ((x) == ADC_AVG_CNT_128)                ||                                 \
    ((x) == ADC_AVG_CNT_256))

#define IS_ADC_EXCH_SRC(x)                                                     \
(   ((x) == ADC_EXCH_SRC_ADC_PIN)           ||                                 \
    ((x) == ADC_EXCH_SRC_INTERNAL))

#define IS_AWD_UNIT(x)                                                         \
(   ((x) == ADC_AWD_0)                      ||                                 \
    ((x) == ADC_AWD_1))

#define IS_AWD_CH_NUM(x)                                                       \
(   ((x) <= ADC_CH_NUM_15))

#define IS_AWD_CMP_MODE(x)                                                     \
(   ((x) == ADC_AWD_CMP_OUT_RANGE)          ||                                 \
    ((x) == ADC_AWD_CMP_IN_RANGE))

#define IS_AWD_COMB_MODE(x)                                                    \
(   ((x) == ADC_AWD_COMB_OR)                ||                                 \
    ((x) == ADC_AWD_COMB_AND)               ||                                 \
    ((x) == ADC_AWD_COMB_XOR))

#define IS_PGA_UNIT(x)                                                         \
(   ((x) <= ADC_PGA_4))

#define IS_PGA_GAIN(x)                                                         \
(   ((x) <= ADC_PGA_GAIN_32))

#define IS_PGA_VSS(x)                                                          \
(   ((x) == ADC_PGA_VSS_PGAVSS)             ||                                 \
    ((x) == ADC_PGA_VSS_AVSS))

#define IS_ADC_SYNC_MODE(x)                                                    \
(   ((x) == ADC_SYNC_SSHOT_SEQUENTIAL)      ||                                 \
    ((x) == ADC_SYNC_SSHOT_SIMULTANEOUS)    ||                                 \
    ((x) == ADC_SYNC_CONT_SEQUENTIAL)       ||                                 \
    ((x) == ADC_SYNC_CONT_SIMULTANEOUS))

#define IS_ADC_SYNC_UNIT(x)                                                    \
(   ((x) == ADC_SYNC_ADC1_ADC2)             ||                                 \
    ((x) == ADC_SYNC_ADC1_ADC2_ADC3))

#define IS_ADC_SYNC_TRIG_DLY(x)                                                \
(   ((x) != 0U))

#define IS_ADC_REMAP_PIN_NUM(x)                                                \
(   ((x) <= ADC12_IN15))

#define IS_ADC1_DR_LENGTH(x)                                                   \
(   ((x) >= ADC1_CH_COUNT))

#define IS_ADC2_DR_LENGTH(x)                                                   \
(   ((x) >= ADC2_CH_COUNT))

#define IS_ADC3_DR_LENGTH(x)                                                   \
(   ((x) >= ADC3_CH_COUNT))

#define IS_ADC_1_BIT_MSK(x)                                                    \
(   ((x) != 0U)                             &&                                 \
    (((x) & ((x) - 1U)) == 0U))

#define IS_ADC_BIT_MSK(x, msk)                                                 \
(   ((x) != 0U)                             &&                                 \
    (((x) | (msk)) == (msk)))

/**
 * @}
 */

/**
 * @defgroup ADC_Miscellaneous_Macros ADC Miscellaneous Macros
 * @{
 */
#define ADC_UNIT_COUNT                      (3U)
#define ADC_IND_SPL_TIME_COUNT              (16U)
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
 *         in the structure stc_adc_init_t.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  pstcInit               Pointer to a stc_adc_init_t structure value that
 *                                      contains the configuration information for the ADC.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t ADC_Init(M4_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SCAN_MODE(pstcInit->u16ScanMode));
        DDL_ASSERT(IS_ADC_RESOLUTION(pstcInit->u16Resolution));
        DDL_ASSERT(IS_ADC_AUTO_CLEAR_CMD(pstcInit->u16AutoClrCmd));
        DDL_ASSERT(IS_ADC_DATA_ALIGN(pstcInit->u16DataAlign));
        DDL_ASSERT(IS_ADC_SA_RESUME_POS(pstcInit->u16SAResumePos));

        /* Configures scan convert mode, resolution, data automatically clear command
           and data alignment. */
        WRITE_REG16(ADCx->CR0,                 \
                    (pstcInit->u16ScanMode   | \
                     pstcInit->u16Resolution | \
                     pstcInit->u16AutoClrCmd | \
                     pstcInit->u16DataAlign));

        /* Configures the channel sequence A restart from. */
        WRITE_REG16(ADCx->CR1, pstcInit->u16SAResumePos);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the ADC peripheral. Reset the registers of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @retval None
 */
void ADC_DeInit(M4_ADC_TypeDef *ADCx)
{
    uint8_t i;
    uint32_t u32SSTRAddr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    /* Stop the ADC. */
    WRITE_REG8(ADCx->STR, 0U);

    /* Set the registers to reset value. */
    WRITE_REG16(ADCx->CR0, 0x0U);
    WRITE_REG16(ADCx->CR1, 0x0U);
    WRITE_REG16(ADCx->TRGSR, 0x0U);

    WRITE_REG32(ADCx->CHSELRA, 0x0U);
    WRITE_REG32(ADCx->CHSELRB, 0x0U);
    WRITE_REG32(ADCx->AVCHSELR, 0x0U);
    WRITE_REG8(ADCx->EXCHSELR, 0x0U);

    WRITE_REG16(ADCx->CHMUXR0, 0x3210U);
    WRITE_REG16(ADCx->CHMUXR1, 0x7654U);
    WRITE_REG16(ADCx->CHMUXR2, 0xBA98U);
    WRITE_REG16(ADCx->CHMUXR3, 0xFEDCU);

    WRITE_REG8(ADCx->ICR, 0x03U);
    WRITE_REG8(ADCx->ISCLRR, 0x13U);

    WRITE_REG16(ADCx->AWDCR, 0x0U);
    WRITE_REG8(ADCx->AWDSCLRR, 0x13U);

    WRITE_REG16(ADCx->AWD0DR0, 0x0U);
    WRITE_REG16(ADCx->AWD0DR1, 0xFFFFU);
    WRITE_REG16(ADCx->AWD1DR0, 0x0U);
    WRITE_REG16(ADCx->AWD1DR1, 0xFFFFU);

    WRITE_REG8(ADCx->AWD0CHSR, 0x0U);
    WRITE_REG8(ADCx->AWD1CHSR, 0x0U);

    u32SSTRAddr = (uint32_t)&ADCx->SSTR0;
    for (i=0U; i<ADC_IND_SPL_TIME_COUNT; i++)
    {
        RW_MEM8(u32SSTRAddr) = (uint8_t)0x0BU;
        u32SSTRAddr++;
    }

    if (ADCx == M4_ADC1)
    {
        WRITE_REG16(ADCx->SYNCCR, 0x0C00U);
        WRITE_REG16(ADCx->SHCR, 0x18U);
        WRITE_REG8(ADCx->PGACR1, 0x0U);
        WRITE_REG8(ADCx->PGACR2, 0x0U);
        WRITE_REG8(ADCx->PGACR3, 0x0U);
        WRITE_REG8(ADCx->PGAVSSENR, 0x0U);
    }
    else if (ADCx == M4_ADC2)
    {
        WRITE_REG8(ADCx->PGACR1, 0x0U);
        WRITE_REG8(ADCx->PGAVSSENR, 0x0U);
    }
    else if (ADCx == M4_ADC3)
    {
        WRITE_REG8(ADCx->SSTRL, 0x0BU);
    }
    else
    {
        /* rsvd */
    }
}

/**
 * @brief  Set a default value for the ADC initialization structure.
 * @param  [in]  pstcInit               Pointer to a stc_adc_init_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t ADC_StructInit(stc_adc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u16ScanMode    = ADC_MODE_SA_SSHOT;
        pstcInit->u16Resolution  = ADC_RESOLUTION_12BIT;
        pstcInit->u16AutoClrCmd  = ADC_AUTO_CLR_DISABLE;
        pstcInit->u16DataAlign   = ADC_DATA_ALIGN_RIGHT;
        pstcInit->u16SAResumePos = ADC_SA_RESUME_POS_INT_CH;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set scan convert mode for the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u16Mode                ADC san convert mode.
 *                                      This parameter can be a value of @ref ADC_Scan_Convert_Mode.
 *   @arg  ADC_MODE_SA_SSHOT:           Sequence A single shot.
 *   @arg  ADC_MODE_SA_CONT:            Sequence A continuous.
 *   @arg  ADC_MODE_SA_SB_SSHOT:        Sequence A and B both single shot.
 *   @arg  ADC_MODE_SA_CONT_SB_SSHOT:   Sequence A continuous and sequence B single shot.
 * @retval None
 */
void ADC_SetScanMode(M4_ADC_TypeDef *ADCx, uint16_t u16Mode)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SCAN_MODE(u16Mode));
    MODIFY_REG16(ADCx->CR0, ADC_CR0_MS, u16Mode);
}

/**
 * @brief  Enable or disable the specified sequence's channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Seq                  The sequence that it's specified channels will be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  u32AdcCh               The ADC channels.
 *                                      This parameter can be values of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH15:          For M4_ADC1 and M4_ADC2.
 *   @arg  ADC_CH0 ~ ADC_CH19:          For M4_ADC3.
 * @param  [in]  pu8SplTime:            Pointer to an uint8_t type array which contains sampling time of the specified channels.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified sequence's specified channels.
 *   @arg  Disable:                     Disable the specified sequence's specified channels.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pu8SplTime == NULL.
 * @note   Sequence A and Sequence B CAN NOT include the same channel!
 * @note   ADC_CH16 ~ ADC_CH19 of ADC3 share the same sampling time.
 */
en_result_t ADC_ChannelCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, \
                           uint32_t u32AdcCh, const uint8_t pu8SplTime[], \
                           en_functional_state_t enNewState)
{
    uint8_t i = 0U;
    uint8_t j = 0U;
    uint32_t u32CHSELAddr;
    uint32_t u32SSTRAddr;
    uint32_t au32ChMsk[] = {ADC1_CH_ALL, ADC2_CH_ALL, ADC3_CH_ALL};
    en_result_t enRet = ErrorInvalidParameter;

    if (pu8SplTime != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SEQ(u8Seq));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32CHSELAddr = (uint32_t)&ADCx->CHSELRA + ((uint32_t)u8Seq * 4U);
        u32SSTRAddr  = (uint32_t)&ADCx->SSTR0;
        u32AdcCh    &= au32ChMsk[ADC_IDX(ADCx)];

        if (enNewState == Enable)
        {
            RW_MEM32(u32CHSELAddr) |= u32AdcCh;

            while (u32AdcCh != 0U)
            {
                if ((u32AdcCh & 0x1UL) != 0U)
                {
                    DDL_ASSERT(IS_ADC_SAMPLE_TIME(pu8SplTime[j]));
                    RW_MEM8(u32SSTRAddr+i) = pu8SplTime[j];
                    if (i < ADC_IND_SPL_TIME_COUNT)
                    {
                        j++;
                    }
                }
                u32AdcCh >>= 1U;
                if (i < ADC_IND_SPL_TIME_COUNT)
                {
                    i++;
                }
            }
        }
        else
        {
            RW_MEM32(u32CHSELAddr) &= (uint32_t)(~u32AdcCh);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set average count for the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u16AvgCnt              The average count to be set for the specified ADC unit.
 *                                      This parameter can be a value of @ref ADC_Average_Count
 *   @arg  ADC_AVG_CNT_2
 *   @arg  ADC_AVG_CNT_4
 *   @arg  ADC_AVG_CNT_8
 *   @arg  ADC_AVG_CNT_16
 *   @arg  ADC_AVG_CNT_32
 *   @arg  ADC_AVG_CNT_64
 *   @arg  ADC_AVG_CNT_128
 *   @arg  ADC_AVG_CNT_256
 * @retval None
 */
void ADC_AvgChannelConfig(M4_ADC_TypeDef *ADCx, uint16_t u16AvgCnt)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AVG_CNT(u16AvgCnt));
    MODIFY_REG16(ADCx->CR0, ADC_CR0_AVCNT, u16AvgCnt);
}

/**
 * @brief  Enable or disable the specified ADC unit's average channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u32AdcCh               The ADC channels.
 *                                      This parameter can be values of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH15:          For M4_ADC1 and M4_ADC2.
 *   @arg  ADC_CH0 ~ ADC_CH19:          For M4_ADC3.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified ADC unit's average channels.
 *   @arg  Disable:                     Disable the specified ADC unit's average channels.
 * @retval None
 */
void ADC_AvgChannelCmd(M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh, en_functional_state_t enNewState)
{
    uint32_t u32SACh;
    uint32_t u32SBCh;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32SACh = ADCx->CHSELRA;
    u32SBCh = ADCx->CHSELRB;
    u32AdcCh &= (u32SACh | u32SBCh);
    if (enNewState == Enable)
    {
        SET_REG32_BIT(ADCx->AVCHSELR, u32AdcCh);
    }
    else
    {
        CLEAR_REG32_BIT(ADCx->AVCHSELR, u32AdcCh);
    }
}

/**
 * @brief  Set analog input source for the specified ADC unit's extend channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8ExChSrc              The analog input source for the extend channel.
 *                                      This parameter can be a value of @ref ADC_Extend_Channel_Source
 *   @arg  ADC_EXCH_SRC_ADC_PIN:        The analog input source of extend channel is ADC analog input pin,
 *                                      ADC12_IN15 of ADC1/ADC2 and ADC3_IN15 of ADC3.
 *   @arg  ADC_EXCH_SRC_INTERNAL:       The analog input source of extend channels is internal reference voltage or
 *                                      the partial voltage of VBAT.
 * @retval None
 */
void ADC_SetExChannelSrc(M4_ADC_TypeDef *ADCx, uint8_t u8ExChSrc)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_EXCH_SRC(u8ExChSrc));
    WRITE_REG8(ADCx->EXCHSELR, u8ExChSrc);
}

/**
 * @brief  Set a default value for the trigger source configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_adc_trig_cfg_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t ADC_TrigSrcStructInit(stc_adc_trig_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u16TrigSrc = ADC_TRIG_SRC_ADTRG;
        pstcCfg->enEvent0   = EVT_MAX;
        pstcCfg->enEvent1   = EVT_MAX;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures the trigger source for the specified sequence of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Seq                  The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  pstcCfg                Pointer to a stc_adc_trig_cfg_t structure that contains
 *                                      the configuration information of the trigger source.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 * @note   ADC must be stopped while calling this function.
 * @note   The trigger source CANNOT be an event that generated by the sequence itself.
 */
en_result_t ADC_TrigSrcConfig(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, const stc_adc_trig_cfg_t *pstcCfg)
{
    uint32_t u32AdcIdx;
    uint32_t u32ITRGSELRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SEQ(u8Seq));
        DDL_ASSERT(IS_ADC_TRIG_SRC(pstcCfg->u16TrigSrc));

        u32AdcIdx = ADC_IDX(ADCx);
        u32ITRGSELRAddr = (uint32_t)&M4_AOS->ADC_1_ITRGSELR0 + u32AdcIdx * 8U;
        if ((pstcCfg->u16TrigSrc & ADC_TRIG_SRC_EVENT0) != 0U)
        {
            MODIFY_REG32(RW_MEM32(u32ITRGSELRAddr), ADC_TRIG_EVENT_MSK, pstcCfg->enEvent0);
        }

        if ((pstcCfg->u16TrigSrc & ADC_TRIG_SRC_EVENT1) != 0U)
        {
            u32ITRGSELRAddr += 4U;
            MODIFY_REG32(RW_MEM32(u32ITRGSELRAddr), ADC_TRIG_EVENT_MSK, pstcCfg->enEvent1);
        }

        MODIFY_REG16(ADCx->TRGSR, \
                     ADC_TRGSR_VAL(u8Seq, ADC_TRIG_SRC_MSK), \
                     ADC_TRGSR_VAL(u8Seq, pstcCfg->u16TrigSrc));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the trigger source of the specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Seq                  The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable the trigger source of the specified sequence.
 *   @arg  Disable:                     Disable the trigger source of the specified sequence.
 * @retval None
 * @note   ADC must be stopped while calling this function.
 */
void ADC_TrigSrcCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint8_t au8CmdPos[] = {ADC_TRGSR_TRGENA_POS, ADC_TRGSR_TRGENB_POS};

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&ADCx->TRGSR;
    BIT_BAND(u32Addr, au8CmdPos[u8Seq]) = (uint32_t)enNewState;
}

/**
 * @brief  Enable or disable common trigger event to start ADC.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u16TrigSrc             ADC trigger source type.
 *                                      This parameter can be a value of @ref ADC_Trigger_Source_Type except ADC_TRIG_SRC_ADTRG.
 *   @arg  ADC_TRIG_SRC_EVENT0:         The trigger source is a internal event from other peripheral. \
 *                                      Only one event can be configured to trigger ADC.
 *   @arg  ADC_TRIG_SRC_EVENT1:         The trigger source is a internal event from other peripheral. \
 *                                      Only one event can be configured to trigger ADC.
 *   @arg  ADC_TRIG_SRC_EVENT0_EVENT1:  The trigger source are two internal events from other peripheral(s). \
 *                                      Two events can be configured to trigger ADC and one of which can trigger the ADC.
 * @param  [in]  u32ComTrig             Common trigger event enable bit mask.
 *                                      This parameter can be a value of @ref ADC_Common_Trigger_Sel
 *   @arg  ADC_COM_TRIG1:               Common trigger 1.
 *   @arg  ADC_COM_TRIG2:               Common trigger 2.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified common trigger.
 *   @arg Disable:                      Disable the specified common trigger.
 * @retval None
 */
void ADC_ComTriggerCmd(M4_ADC_TypeDef *ADCx, uint16_t u16TrigSrc, \
                       uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    uint32_t u32AdcIdx;
    uint32_t u32ITRGSELRAddr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_BIT_MSK(u32ComTrig, ADC_COM_TRIG_MSK));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32AdcIdx = ADC_IDX(ADCx);
    u32ITRGSELRAddr = (uint32_t)&M4_AOS->ADC_1_ITRGSELR0 + u32AdcIdx * 8U;

    if ((u16TrigSrc & ADC_TRIG_SRC_EVENT0) != 0U)
    {
        if (enNewState == Enable)
        {
            SET_REG32_BIT(RW_MEM32(u32ITRGSELRAddr), u32ComTrig);
        }
        else
        {
            CLEAR_REG32_BIT(RW_MEM32(u32ITRGSELRAddr), u32ComTrig);
        }
    }

    if ((u16TrigSrc & ADC_TRIG_SRC_EVENT1) != 0U)
    {
        u32ITRGSELRAddr += 4UL;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(RW_MEM32(u32ITRGSELRAddr), u32ComTrig);
        }
        else
        {
            CLEAR_REG32_BIT(RW_MEM32(u32ITRGSELRAddr), u32ComTrig);
        }
    }
}

/**
 * @brief  Enable or disable the interrupt of the specified ADC unit's specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Seq                  The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable the interrupt of the specified sequence.
 *   @arg  Disable:                     Disable the interrupt of the specified sequence.
 * @retval None
 */
void ADC_SeqIntCmd(M4_ADC_TypeDef *ADCx, uint8_t u8Seq, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&ADCx->ICR;
    BIT_BAND(u32Addr, u8Seq) = (uint32_t)enNewState;
}

/**
 * @brief  Get the status flag of the specified ADC unit's specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Flag                 Status flag type.
 *                                      This parameter can be valueS of @ref ADC_Sequence_Status_Flag
 *   @arg  ADC_SEQ_FLAG_EOCA:           Status flag of the end of conversion of sequence A.
 *   @arg  ADC_SEQ_FLAG_EOCB:           Status flag of the end of conversion of sequence B.
 *   @arg  ADC_SEQ_FLAG_NESTED:         Status flag of sequence A was interrupted by sequence B.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified flags is set.
 *   @arg  Reset:                       The specified flags are not set.
 */
en_flag_status_t ADC_SeqGetStatus(const M4_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    en_flag_status_t enRet = Reset;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    if (READ_REG8_BIT(ADCx->ISR, (u8Flag & (uint8_t)ADC_SEQ_FLAG_ALL)) != 0U)
    {
        enRet = Set;
    }

    return enRet;
}

/**
 * @brief  Clear the status flag of the specified ADC unit's specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Flag                 Status flag type.
 *                                      This parameter can be values of @ref ADC_Sequence_Status_Flag
 *   @arg  ADC_SEQ_FLAG_EOCA:           Status flag of the end of conversion of sequence A.
 *   @arg  ADC_SEQ_FLAG_EOCB:           Status flag of the end of conversion of sequence B.
 *   @arg  ADC_SEQ_FLAG_NESTED:         Status flag of sequence A was interrupted by sequence B.
 * @retval None
 */
void ADC_SeqClrStatus(M4_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    SET_REG8_BIT(ADCx->ISCLRR, (u8Flag & (uint8_t)ADC_SEQ_FLAG_ALL));
}

/**
 * @brief  Configures analog watchdog(AWD).
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8AWDx                 AWD unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 *   @arg  ADC_AWD_0:                   AWD unit 0 of the specified ADC.
 *   @arg  ADC_AWD_1:                   AWD unit 1 of the specified ADC.
 * @param  [in]  pstcCfg                Pointer to a stc_adc_awd_cfg_t structure value that
 *                                      contains the configuration information for the AWD.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t ADC_AWD_Config(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, const stc_adc_awd_cfg_t *pstcCfg)
{
    uint32_t u32AwdCr;
    uint32_t u32AwdDr0;
    uint32_t u32AwdDr1;
    uint32_t u32AwdChsr;
    uint32_t u32Pos;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_AWD_UNIT(u8AWDx));
        DDL_ASSERT(IS_AWD_CH_NUM(pstcCfg->u8ChNum));
        DDL_ASSERT(IS_AWD_CMP_MODE(pstcCfg->u16CmpMode));

        u32Pos     = ((uint32_t)u8AWDx << 2U) + ADC_AWDCR_AWD0MD_POS;
        u32AwdCr   = (uint32_t)&ADCx->AWDCR;
        u32AwdDr0  = (uint32_t)&ADCx->AWD0DR0;
        u32AwdDr1  = (uint32_t)&ADCx->AWD0DR1;
        u32AwdChsr = (uint32_t)&ADCx->AWD0CHSR;

        BIT_BAND(u32AwdCr, u32Pos) = (uint32_t)pstcCfg->u16CmpMode;
        ADC_AWDx_DR(u32AwdDr0, u8AWDx) = pstcCfg->u16LowerLimit;
        ADC_AWDx_DR(u32AwdDr1, u8AWDx) = pstcCfg->u16UpperLimit;
        ADC_AWDx_CHSR(u32AwdChsr, u8AWDx) = pstcCfg->u8ChNum;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable combination mode of analog watchdog(AWD).
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u16CombMode            Combination mode of analog watchdog.
 *                                      This parameter can be a value of @ref ADC_AWD_Combination_Mode
 *   @arg  ADC_AWD_COMB_OR:             The status of AWD0 is set or the status of AWD1 is set, the status of combination mode is set.
 *   @arg  ADC_AWD_COMB_AND:            The status of AWD0 is set and the status of AWD1 is set, the status of combination mode is set.
 *   @arg  ADC_AWD_COMB_XOR:            Only one of the status of AWD0 and AWD1 is set, the status of combination mode is set.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the combination mode of specified ADC unit's AWD.
 *   @arg  Disable:                     Disable the combination mode of specified ADC unit's AWD.
 * @retval None
 */
void ADC_AWD_CombModeCmd(M4_ADC_TypeDef *ADCx, uint16_t u16CombMode, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_AWD_COMB_MODE(u16CombMode));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CLEAR_REG16_BIT(ADCx->AWDCR, ADC_AWD_COMB_MODE_MSK);
    if (enNewState == Enable)
    {
        SET_REG16_BIT(ADCx->AWDCR, u16CombMode);
    }
}

/**
 * @brief  Enable or disable the specified analog watchdog(AWD).
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8AWDx                 AWD unit that is going to be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 *   @arg  ADC_AWD_0:                   AWD unit 0 of the specified ADC.
 *   @arg  ADC_AWD_1:                   AWD unit 1 of the specified ADC.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified AWD.
 *   @arg  Disable:                     Disable the specified AWD.
 * @retval None
 */
void ADC_AWD_Cmd(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint32_t u32Pos;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_AWD_UNIT(u8AWDx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Pos  = ((uint32_t)u8AWDx << 2U) + ADC_AWDCR_AWD0EN_POS;
    u32Addr = (uint32_t)&ADCx->AWDCR;
    BIT_BAND(u32Addr, u32Pos) = (uint32_t)enNewState;
}

/**
 * @brief  Enable or disable the specified analog watchdog's interrupt.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8AWDx                 AWD unit.
 *                                      This parameter can be a value of @ref ADC_AWD_Unit
 *   @arg  ADC_AWD_0:                   AWD unit 0 of the specified ADC.
 *   @arg  ADC_AWD_1:                   AWD unit 1 of the specified ADC.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified AWD's interrupt.
 *   @arg  Disable:                     Disable the specified AWD's interrupt.
 * @retval None
 */
void ADC_AWD_IntCmd(M4_ADC_TypeDef *ADCx, uint8_t u8AWDx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint32_t u32Pos;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_AWD_UNIT(u8AWDx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Pos  = ((uint32_t)u8AWDx << 2U) + ADC_AWDCR_AWD0IEN_POS;
    u32Addr = (uint32_t)&ADCx->AWDCR;
    BIT_BAND(u32Addr, u32Pos) = (uint32_t)enNewState;
}

/**
 * @brief  Get the analog watchdog's flag status of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Flag                 AWD status flag type.
 *                                      This parameter can be values of @ref ADC_AWD_Status_Flag
 *   @arg  ADC_AWD_FLAG_AWD0:           Flag of AWD0.
 *   @arg  ADC_AWD_FLAG_AWD1:           Flag of AWD1.
 *   @arg  ADC_AWD_FLAG_COMB:           Flag of combination mode.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified flags is set.
 *   @arg  Reset:                       The specified flags are not set.
 */
en_flag_status_t ADC_AWD_GetStatus(const M4_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    en_flag_status_t enRet = Reset;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    if (READ_REG8_BIT(ADCx->AWDSR, (u8Flag & (uint8_t)ADC_AWD_FLAG_ALL)) != 0U)
    {
        enRet = Set;
    }

    return enRet;
}

/**
 * @brief  Clear the analog watchdog's flag status of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8Flag                 AWD status flag type.
 *                                      This parameter can be values of @ref ADC_AWD_Status_Flag
 *   @arg  ADC_AWD_FLAG_AWD0:           Flag of AWD0.
 *   @arg  ADC_AWD_FLAG_AWD1:           Flag of AWD1.
 *   @arg  ADC_AWD_FLAG_COMB:           Flag of combination mode.
 * @retval None
 */
void ADC_AWD_ClrStatus(M4_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    u8Flag &= (uint8_t)ADC_AWD_FLAG_ALL;
    SET_REG8_BIT(ADCx->AWDSCLRR, u8Flag);
}

/**
 * @brief  Configures the specified programmable gain amplifier(PGA).
 * @param  [in]  u8PGAx                 The PGA unit that is going to be configured.
 *                                      This parameter can be a value of @ref ADC_PGA_Unit
 *   @arg  ADC_PGA_1:                   PGA1, belongs to ADC1. Input pin is ADC123_IN0.
 *   @arg  ADC_PGA_2:                   PGA2, belongs to ADC1. Input pin is ADC123_IN1.
 *   @arg  ADC_PGA_3:                   PGA3, belongs to ADC1. Input pin is ADC123_IN2.
 *   @arg  ADC_PGA_4:                   PGA4, belongs to ADC2. Input pin is ADC12_IN7.
 * @param  [in]  u8GainFactor           Gain factor for the specified PGA.
 *                                      This parameter can be a value of @ref ADC_PGA_Gain_Factor
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
 *   @arg  ADC_PGA_VSS_PGAVSS:          Use pin PGA123_VSS as the reference GND of PGA1, PGA2 and PGA3.
 *   @arg  ADC_PGA_VSS_AVSS:            Use AVSS as the reference GND of PGA1, PGA2 and PGA3.
 * @retval None
 */
void ADC_PGA_Config(uint8_t u8PGAx, uint8_t u8GainFactor, uint8_t u8PgaVss)
{
    uint32_t u32Addr;
    uint32_t u32PGACRAddr;
    M4_ADC_TypeDef *ADCx;
    uint32_t au32AdcBase[] = {ADC1_BASE, ADC1_BASE, ADC1_BASE, ADC2_BASE};

    DDL_ASSERT(IS_PGA_GAIN(u8GainFactor));
    DDL_ASSERT(IS_PGA_VSS(u8PgaVss));
    DDL_ASSERT(IS_PGA_UNIT(u8PGAx));

    ADCx    = (M4_ADC_TypeDef *)au32AdcBase[u8PGAx];
    u8PGAx %= 3U;
    u32PGACRAddr = (uint32_t)&ADCx->PGACR1 + u8PGAx;
    MODIFY_REG8(RW_MEM8(u32PGACRAddr), ADC_PGA_GAIN_MSK, u8GainFactor);
    u32Addr = (uint32_t)&ADCx->PGAVSSENR;
    BIT_BAND(u32Addr, u8PGAx) = (uint32_t)u8PgaVss;
}

/**
 * @brief  Enable the specified programmable gain amplifier(PGA).
 * @param  [in]  u8PGAx                 The PGA unit which is going to be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_PGA_Unit
 *   @arg  ADC_PGA_1:                   PGA1, belongs to ADC1. Input pin is ADC123_IN0.
 *   @arg  ADC_PGA_2:                   PGA2, belongs to ADC1. Input pin is ADC123_IN1.
 *   @arg  ADC_PGA_3:                   PGA3, belongs to ADC1. Input pin is ADC123_IN2.
 *   @arg  ADC_PGA_4:                   PGA4, belongs to ADC2. Input pin is ADC12_IN7.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified PGA.
 *   @arg  Disable:                     Disable the specified PGA.
 * @retval None
 */
void ADC_PGA_Cmd(uint8_t u8PGAx, en_functional_state_t enNewState)
{
    uint32_t u32PGACRAddr;
    M4_ADC_TypeDef *ADCx;
    uint32_t au32AdcBase[] = {ADC1_BASE, ADC1_BASE, ADC1_BASE, ADC2_BASE};
    uint8_t au8Cmd[] = {ADC_PGA_DISABLE, ADC_PGA_ENABLE};

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PGA_UNIT(u8PGAx));

    ADCx    = (M4_ADC_TypeDef *)au32AdcBase[u8PGAx];
    u8PGAx %= 3U;
    u32PGACRAddr = (uint32_t)&ADCx->PGACR1 + u8PGAx;
    MODIFY_REG8(RW_MEM8(u32PGACRAddr), ADC_PGA_CMD_MSK, au8Cmd[(uint8_t)enNewState]);
}

/**
 * @brief  Configures synchronous mode.
 * @param  [in]  u16SyncUnit            Specify the ADC units which work synchronously.
 *                                      This parameter can be a value of @ref ADC_Synchronous_Unit
 *   @arg  ADC_SYNC_ADC1_ADC2:          ADC1 and ADC2 work synchronously.
 *   @arg  ADC_SYNC_ADC1_ADC2_ADC3:     ADC1, ADC2 and ADC3 work synchronously.
 * @param  [in]  u16SyncMode            Synchronous mode.
 *                                      This parameter can be a value of @ref ADC_Synchronous_Mode
 *   @arg  ADC_SYNC_SSHOT_SEQUENTIAL:   Single shot trigger, sequentially trigger. \
 *                                      When the trigger condition occurs, ADC1 starts before ADC2, \
 *                                      and ADC1 and ADC2 only perform one sample conversion.
 *   @arg  ADC_SYNC_SSHOT_SIMULTANEOUS: Single shot trigger, simultaneously trigger. \
 *                                      When the trigger condition occurs, ADC1 and ADC2 start at the same time, \
 *                                      and ADC1 and ADC2 only perform one sample conversion.
 *   @arg  ADC_SYNC_CONT_SEQUENTIAL:    Continuously trigger, sequentially trigger. \
 *                                      When the trigger condition occurs, ADC1 starts before ADC2, \
 *                                      and ADC1 and ADC2 will continue to sample conversion until stopped by software.
 *   @arg  ADC_SYNC_CONT_SIMULTANEOUS:  Continuously trigger, simultaneously trigger. \
 *                                      When the trigger condition occurs, ADC1 and ADC2 start at the same time, \
 *                                      and ADC1 and ADC2 will continue to sample conversion until stopped by software.
 * @param  [in]  u8TrigDelay            Trigger delay time(PCLK2 cycle), range is [1, 255].
 * @retval None
 */
void ADC_SYNC_Config(uint16_t u16SyncUnit, uint16_t u16SyncMode, uint8_t u8TrigDelay)
{
    DDL_ASSERT(IS_ADC_SYNC_UNIT(u16SyncUnit));
    DDL_ASSERT(IS_ADC_SYNC_MODE(u16SyncMode));
    DDL_ASSERT(IS_ADC_SYNC_TRIG_DLY(u8TrigDelay));

    u16SyncMode |= ((uint16_t)((uint32_t)u8TrigDelay << ADC_SYNCCR_SYNCDLY_POS)) | u16SyncUnit;
    MODIFY_REG16(M4_ADC1->SYNCCR, ADC_SYNC_CFG_MSK, u16SyncMode);
}

/**
 * @brief  Enable or disable synchronous mode.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable synchronous mode.
 *   @arg  Disable:                     Disable synchronous mode.
 * @retval None
 */
void ADC_SYNC_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bM4_ADC1->SYNCCR_b.SYNCEN, enNewState);
}

/**
 * @brief  Configures sample-hold. Specifies the sample time of sample-hold.
 * @param  [in]  u8SplTime              Sample time(ADCLK cycles) for sample-hold. \
 *                                      It should be more than 0.4 microseconds.
 * @retval None
 */
void ADC_SH_Config(uint8_t u8SplTime)
{
    MODIFY_REG16(M4_ADC1->SHCR, ADC_SH_CFG_MSK, u8SplTime);
}

/**
 * @brief  Enable or disable sample-hold channels.
 * @param  [in]  u32AdcCh               ADC channels.
 *                                      This parameter be values of the following that from @ref ADC_Channel
 *   @arg  ADC_CH0:                     Channel 0 of ADC1.
 *   @arg  ADC_CH1:                     Channel 1 of ADC1.
 *   @arg  ADC_CH2:                     Channel 2 of ADC1.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified sample-hold channels.
 *   @arg  Disable:                     Disable the specified sample-hold channels.
 * @retval None
 */
void ADC_SH_ChannelCmd(uint32_t u32AdcCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_BIT_MSK(u32AdcCh, ADC_CH0|ADC_CH1|ADC_CH2));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32AdcCh <<= ADC_SHCR_SHSEL_POS;
    if (enNewState == Enable)
    {
        SET_REG16_BIT(M4_ADC1->SHCR, u32AdcCh);
    }
    else
    {
        CLEAR_REG16_BIT(M4_ADC1->SHCR, u32AdcCh);
    }
}

/**
 * @brief  Remap the correspondence between ADC channels and analog input pins.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u32AdcCh               This parameter be values of the following that from @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH15           For all of ADC units.
 * @param  [in]  u8AdcPinNum            This parameter be a value of @ref ADC_Pin_Number
 *   @arg  ADC123_xxx:                  Pin number belongs to all of ADC units.
 *   @arg  ADC12_xxx:                   Pin number belongs to ADC1 and ADC2.
 *   @arg  ADC3_xxx:                    Pin number belongs to ADC3.
 * @note   The pin number is from 0 to 15 can be remaped.
 * @retval None
 */
void ADC_ChannelRemap(M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh, uint8_t u8AdcPinNum)
{
    uint8_t u8FieldOfs;
    uint32_t u32RegIdx;
    uint32_t u32CHMUXRAddr;
    uint32_t u32ChNum = 0U;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_REMAP_PIN_NUM(u8AdcPinNum));
    DDL_ASSERT(IS_ADC_BIT_MSK(u32AdcCh, ADC_CH_REMAP_ALL));

    u32CHMUXRAddr = (uint32_t)&ADCx->CHMUXR0;
    while (u32AdcCh != 0U)
    {
        if ((u32AdcCh & 0x1UL) != 0U)
        {
            u32RegIdx  = u32ChNum / 4U;
            u8FieldOfs = (uint8_t)((u32ChNum % 4U) << 2U);
            MODIFY_REG16(RW_MEM16(u32CHMUXRAddr + u32RegIdx * 2U), \
                         ((uint32_t)ADC_CH_MAP_PIN_MSK << u8FieldOfs), \
                         ((uint32_t)u8AdcPinNum << u8FieldOfs));
        }

        u32AdcCh >>= 1U;
        u32ChNum++;
    }
}

/**
 * @brief  Get the number of the analog input pin corresponding to the specified ADC unit's channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u32AdcCh               ADC channel.
 *                                      This parameter can be one of the following values of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH15
 * @retval An uint8_t type value of ADC pin number that corresponding to the specified channel number.
 *         This parameter can be one of the following values of @ref ADC_Pin_Number
 *   @arg  ADC123_xxx:                  Pin number belongs to all of ADC units.
 *   @arg  ADC12_xxx:                   Pin number belongs to ADC1 and ADC2.
 *   @arg  ADC3_xxx:                    Pin number belongs to ADC3.
 */
uint8_t ADC_GetChannelPinNum(const M4_ADC_TypeDef *ADCx, uint32_t u32AdcCh)
{
    uint32_t u32RegIdx;
    uint32_t u32CHMUXRAddr;
    uint32_t u32ChNum = 0U;
    uint8_t u8RetPinNum;
    uint8_t u8FieldOfs;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_BIT_MSK(u32AdcCh, ADC_CH_REMAP_ALL));
    DDL_ASSERT(IS_ADC_1_BIT_MSK(u32AdcCh));

    while ((u32AdcCh & (1UL << u32ChNum)) == 0U)
    {
        u32ChNum++;
    }

    u32RegIdx     = u32ChNum / 4U;
    u8FieldOfs    = (uint8_t)((u32ChNum % 4U) << 2U);
    u32CHMUXRAddr = (uint32_t)&ADCx->CHMUXR0 + (u32RegIdx * 2U);
    u8RetPinNum   = (uint8_t)((RW_MEM16(u32CHMUXRAddr) >> u8FieldOfs) & 0xFU);

    return u8RetPinNum;
}

/**
 * @brief  Basic usage of ADC sampling. Get the ADC values of the pins
 *         corresponding to the channels enabled in sequence A.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [out]  pu16AdcVal            Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      The location of the value store depends on the parameter u8Length.
 *                                      u8Length >= ADCx_CH_COUNT, all of the ADC data registers will be read:
 *                                      pu16AdcVal[0] = value of Channel 0,
 *                                      pu16AdcVal[1] = value of Channel 1,
 *                                      pu16AdcVal[2] = value of Channel 2,
 *                                                  ...
 *                                      u8Length < ADCx_CH_COUNT(ADC1_CH_COUNT or ADC2_CH_COUNT),
 *                                      only the value of the enabled channels will be read:
 *                                      pu16AdcVal[0] = value of the 1st enabled channel,
 *                                      pu16AdcVal[1] = value of the 2nd enabled channel,
 *                                      pu16AdcVal[2] = value of the 3rd enabled channel,
 * @param  [in]  u8Length               The length of the ADC value to be got.
 * @param  [in]  u32Timeout             Timeout value(millisecond).
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -pu16AdcVal == NULL.
 *                                     -u8Length == 0.
 *                                     -u32Timeout == 0.
 *                                     -The base address of 'pu16AdcVal' is not 2-byte aligned.
 */
en_result_t ADC_PollingSA(M4_ADC_TypeDef *ADCx, uint16_t pu16AdcVal[], uint8_t u8Length, uint32_t u32Timeout)
{
    uint32_t u32Ch;
    uint32_t u32TimeCnt;
    uint8_t au8DrLen[ADC_UNIT_COUNT] = {ADC1_CH_COUNT, ADC2_CH_COUNT, ADC3_CH_COUNT};
    en_result_t enRet = ErrorInvalidParameter;

    if ((pu16AdcVal != NULL) && \
        (u8Length != 0U) && (u32Timeout != 0U) && \
        IS_ADDRESS_ALIGN_HALFWORD(&pu16AdcVal[0U]))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));

        u32TimeCnt = u32Timeout * (HCLK_VALUE / 10U / 1000U);
        enRet = ErrorTimeout;
        /* Start ADC.*/
        WRITE_REG8(ADCx->STR, ADC_STR_STRT);
        while (u32TimeCnt-- != 0U)
        {
            if (READ_REG8_BIT(ADCx->ISR, ADC_SEQ_FLAG_EOCA) != 0U)
            {
                if (u8Length < au8DrLen[ADC_IDX(ADCx)])
                {
                    u32Ch = ADCx->CHSELRA;
                    (void)ADC_GetChannelData(ADCx, u32Ch, pu16AdcVal, u8Length);
                }
                else
                {
                    (void)ADC_GetAllData(ADCx, pu16AdcVal, u8Length);
                }
                /* Clear EOC flag. */
                SET_REG8_BIT(ADCx->ISCLRR, ADC_ISCLRR_CLREOCAF);
                enRet = Ok;
                break;
            }
        }
        if (enRet != Ok)
        {
            /* Stop ADC if timeout. */
            WRITE_REG8(ADCx->STR, 0U);
        }
    }

    return enRet;
}

/**
 * @brief  Start the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @retval None
 */
void ADC_Start(M4_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    WRITE_REG8(ADCx->STR, ADC_STR_STRT);
}

/**
 * @brief  Stop the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @retval None
 */
void ADC_Stop(M4_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    WRITE_REG8(ADCx->STR, 0U);
}

/**
 * @brief  Get all of the channels' value of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [out]  pu16AdcVal            Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      pu16AdcVal[0] = value of Channel 0,
 *                                      pu16AdcVal[1] = value of Channel 1,
 *                                      pu16AdcVal[2] = value of Channel 2,
 * @param  [in]  u8Length               The length of the ADC value to be got.
 *                                      It CAN NOT be less than the number of channels of the ADC unit.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -pu16AdcVal == NULL.
 *                                     -The base address of 'pu16AdcVal' is not 2-byte aligned.
 */
en_result_t ADC_GetAllData(const M4_ADC_TypeDef *ADCx, uint16_t pu16AdcVal[], uint8_t u8Length)
{
    uint8_t u8AdcIdx;
    uint32_t i;
    uint32_t u32DRAddr;
    uint8_t au8DrLen[ADC_UNIT_COUNT] = {ADC1_CH_COUNT, ADC2_CH_COUNT, ADC3_CH_COUNT};
    en_result_t enRet = ErrorInvalidParameter;

    if ((pu16AdcVal != NULL) && IS_ADDRESS_ALIGN_HALFWORD(&pu16AdcVal[0U]))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));

        u8AdcIdx = ADC_IDX(ADCx);
        DDL_ASSERT(u8Length >= au8DrLen[u8AdcIdx]);

        if (u8Length > au8DrLen[u8AdcIdx])
        {
            u8Length = au8DrLen[u8AdcIdx];
        }
        u32DRAddr = (uint32_t)&ADCx->DR0;
        for (i=0U; i<u8Length; i++)
        {
            pu16AdcVal[i] = RW_MEM16(u32DRAddr);
            u32DRAddr += 2U;
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get specified channels' value of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in] u32TargetCh             The channels which's ADC values will be read.
 *                                      This parameter can be a value of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH15:          For M4_ADC1 and M4_ADC2.
 *   @arg  ADC_CH0 ~ ADC_CH19:          For M4_ADC3.
 * @param  [out]  pu16AdcVal            Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      pu16AdcVal[0] = value of the 1st enabled channel,
 *                                      pu16AdcVal[1] = value of the 2nd enabled channel,
 *                                      pu16AdcVal[2] = value of the 3rd enabled channel,
 * @param  [in]  u8Length               The length of the ADC value to be got.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -u32TargetCh = 0.
 *                                     -pu16AdcVal == NULL.
 *                                     -u8Length == 0.
 *                                     -The base address of 'pu16AdcVal' is not 2-byte aligned.
 */
en_result_t ADC_GetChannelData(const M4_ADC_TypeDef *ADCx, uint32_t u32TargetCh, \
                               uint16_t pu16AdcVal[], uint8_t u8Length)
{
    uint8_t  j = 0U;
    uint32_t i = 0U;
    uint32_t u32DRAddr;
    uint32_t au32ChAllMsk[] = {ADC1_CH_ALL, ADC2_CH_ALL, ADC3_CH_ALL};
    en_result_t enRet = ErrorInvalidParameter;

    if ((u32TargetCh != 0U) && (pu16AdcVal != NULL) &&
        IS_ADDRESS_ALIGN_HALFWORD(&pu16AdcVal[0U]) && (u8Length != 0U))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        u32TargetCh &= au32ChAllMsk[ADC_IDX(ADCx)];
        u32DRAddr    = (uint32_t)&ADCx->DR0;
        while ((u32TargetCh != 0U) && (u8Length != 0U))
        {
            if ((u32TargetCh & 0x1UL) != 0U)
            {
                pu16AdcVal[j++] = RW_MEM16(u32DRAddr + i * 2U);
                u8Length--;
            }
            u32TargetCh >>= 1U;
            i++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get a specified channel's value of the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8ChNum                The index number of ADC channel.
 *                                      The following parameters that from @ref ADC_Channel_Number can be used:
 *   @arg  ADC_CH_NUM_0 ~ ADC_CH_NUM_15: For ADC1 and ADC2.
 *   @arg  ADC_CH_NUM_0 ~ ADC_CH_NUM_19: For ADC3.
 * @retval An uint16_t type value between 0 ~ 4095.
 */
uint16_t ADC_GetValue(const M4_ADC_TypeDef *ADCx, uint8_t u8ChNum)
{
    uint32_t u32DRAddr;
#ifdef __DEBUG
    uint8_t au8DrLen[ADC_UNIT_COUNT] = {ADC1_CH_COUNT, ADC2_CH_COUNT, ADC3_CH_COUNT};
    DDL_ASSERT(u8ChNum < au8DrLen[ADC_IDX(ADCx)]);
#endif
    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    u32DRAddr = (uint32_t)&ADCx->DR0 + ((uint32_t)u8ChNum * 2U);
    return RW_MEM16(u32DRAddr);
}

/**
 * @}
 */

#endif /* DDL_ADC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
