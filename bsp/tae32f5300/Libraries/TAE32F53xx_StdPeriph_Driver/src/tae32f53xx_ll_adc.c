/**
  ******************************************************************************
  * @file    tae32f53xx_ll_adc.c
  * @author  MCD Application Team
  * @brief   ADC LL module driver.
  *
  ******************************************************************************
  @verbatim
  * ==============================================================================
  *                    ##### ADC peripheral features #####
  * ==============================================================================
  * [..]
  * (+) Interrupt generation at the end of regular conversion and in case of
  *     analog watchdog or overrun events.
  *
  * (+) Single and continuous conversion modes.
  *
  * (+) Scan mode for conversion of several channels sequentially.
  *
  * (+) Data alignment with in-built data coherency.
  *
  * (+) Programmable sampling time (channel wise)
  *
  * (+) External trigger (timer or EXTI) with configurable polarity
  *
  * (+) DMA request generation for transfer of conversions data of regular group.
  *
  * (+) Configurable delay between conversions in Dual interleaved mode.
  *
  * (+) ADC channels selectable single/differential input.
  *
  * (+) ADC calibration shared on 4 group offset & gain compensation instances.
  *
  * (+) ADC conversion of regular group.
  *
  * (+) ADC supply requirements: 1.62 V to 3.6 V.
  *
  * (+) ADC single input range: 0 to Vref. Vref is 3V
  *
  * (+) ADC Differential input range: from Vref- (connected to IN-) to Vref+ (connected to
  *     IN+ or to an external voltage reference).
  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"
#include "string.h"
#include "stdlib.h"


#define DBG_TAG             "ADC LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup ADC_LL ADC LL
  * @brief    ADC LL module driver
  * @{
  */

#ifdef LL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Variables ADC LL Private Variables
  * @brief    ADC LL Private Variables
  * @{
  */

/**
  * @brief ADC Calibration temp offset param
  */
volatile static int16_t   temp_offset = 0;

/**
  * @brief ADC Calibration temp gain param
  */
volatile static uint16_t  temp_gain = 0;

/**
  * @brief ADC Calibration Data struct param
  */
volatile ADC_CalibrationDataTypeDef pCoef = {0};

/**
  * @brief ADC Calibration Data static param
  */
static const uint32_t Calib_check_data[3] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

/**
  * @brief ADC Calibration read data array
  */
static uint32_t Calib_read_data[3] = {0};
/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADC_LL_Private_Functions ADC LL Private Functions
  * @brief    ADC LL Private Functions
  * @{
  */
static void LL_ADC_ReadCoef(void);
static void LL_ADC_OverSamp_Mode(ADC_TypeDef *Instance, int16_t offset);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC LL Exported Functions
  * @brief    ADC LL Exported Functions
  * @{
  */

/** @defgroup ADC_LL_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Initialize some features of ADC instance.
  * @note   These parameters have an impact on ADC scope: ADC instance.
  *         Affects both group regular and group injected
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Instance .
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  * @param  Instance ADC instance
  * @param  ADC_InitStruct Pointer to a @ref ADC_REG_InitTypeDef structure
  * @retval An LL_StatusETypeDef enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
LL_StatusETypeDef LL_ADC_Init(ADC_TypeDef *Instance, ADC_InitTypeDef *ADC_InitStruct)
{
    LL_StatusETypeDef status = LL_OK;
    /*hardware level Initialize*/
    LL_ADC_MspInit(Instance);
    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_SYNCHRONIZATION(ADC_InitStruct->Synchronization));
    assert_param(IS_ADC_ANOLOGSET(ADC_InitStruct->AnologCfg));
    assert_param(IS_ADC_OVR_DATA_BEHAVIOR(ADC_InitStruct->Overrun));

    /*Check whether the SOC has been calibrated*/
    LL_ADC_ReadCoef();

    /* Note: Hardware constraint (refer to description of this function):         */
    /*       ADC instance must be disabled.                                       */
    if (__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) {
        /* Configuration of ADC hierarchical scope:                               */
        /*  - ADC instance                                                        */
        /*  - Set ADC Synchronization                                             */
        MODIFY_REG(Instance->CR1, ADC_CR1_SYNCEN, ADC_InitStruct->Synchronization);

        //WRITE_REG(Instance->CR2, ADC_InitStruct->AnologCfg);
        /*only ADC0 valid paramter*/
        //WRITE_REG(ADC0->CR2, ADC_InitStruct->AnologCfg);

        if (Instance == ADC0) {
            WRITE_REG(Instance->CR2, ADC_InitStruct->AnologCfg);
        } else if (Instance == ADC1) {
            /*only ADC0 valid paramter*/
            WRITE_REG(Instance->CR2, ADC_InitStruct->AnologCfg);
            WRITE_REG(ADC0->CR2, ADC_InitStruct->AnologCfg);
        }

        while (!(Instance->ISR & BIT(8)));

        /* Configuration of Oversampler:                                      */
        /*  - Oversampling Ratio                                              */
        /*  - Right bit shift                                                 */
        /*  - Triggered mode                                                  */
        /*  - Oversampling mode (continued/resumed)                           */

        if (ADC_InitStruct->RegOversampMode && !(ADC_InitStruct->InjOversampMode)) {
            SET_BIT(Instance->CR1, ADC_CR1_ROVSE);
        } else if (ADC_InitStruct->InjOversampMode && !(ADC_InitStruct->RegOversampMode)) {
            SET_BIT(Instance->CR1, ADC_CR1_JOVSE);
        } else {
            SET_BIT(Instance->CR1, ADC_CR1_ROVSE | ADC_CR1_JOVSE);
        }

        assert_param(IS_ADC_OVERSAMPMODE_SET(ADC_InitStruct->OverSampling.OverSampResetMode));
        assert_param(IS_ADC_TRIGOVERSAMP(ADC_InitStruct->OverSampling.TrigOverSamp));
        assert_param(IS_ADC_OVERSAMPSHIFT(ADC_InitStruct->OverSampling.OverSampShiftBit));
        assert_param(IS_ADC_OVERSAMPRATIO(ADC_InitStruct->OverSampling.OverSampRatio));

        MODIFY_REG(Instance->CR1,
                   ADC_CR1_ROVSM
                   | ADC_CR1_TROVS
                   | ADC_CR1_OVSS
                   | ADC_CR1_OVSR
                   | ADC_CR1_OVRMOD
                   ,
                   ADC_InitStruct->OverSampling.OverSampResetMode
                   | ADC_InitStruct->OverSampling.TrigOverSamp
                   | ADC_InitStruct->OverSampling.OverSampShiftBit
                   | ADC_InitStruct->OverSampling.OverSampRatio
                   | ADC_InitStruct->Overrun
                  );
        /*Normal interrupt config*/
        WRITE_REG(Instance->IER, ADC_InitStruct->NormInterrupt);

    } else {
        /* Initialization error: ADC instance is not disabled. */
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  De-initialize registers of the selected ADC instance
  *         to their default reset values.
  * @note   To reset all ADC instances quickly (perform a hard reset),
  * @note   If this functions returns error status, it means that ADC instance
  *         is in an unknown state.
  *         In this case, perform a hard reset using high level
  *         clock source RCC ADC reset.
  * @param  Instance ADC instance
  * @retval An LL_StatusETypeDef enumeration value:
  *          - SUCCESS: ADC registers are de-initialized
  *          - ERROR: ADC registers are not de-initialized
  */
LL_StatusETypeDef LL_ADC_DeInit(ADC_TypeDef *Instance)
{
    LL_StatusETypeDef status = LL_OK;

    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    /* Disable ADC instance if not already disabled.                          */
    /* Set ADC group regular trigger source to SW start to ensure to not      */
    /* have an external trigger event occurring during the conversion stop    */
    /* ADC disable process.                                                   */
    __LL_ADC_REG_SetTriggerSource(Instance, ADC_REG_TRIG_SOFTWARE);

    /* Stop potential ADC conversion on going on ADC group regular.           */
    if (__LL_ADC_REG_IsConversionOngoing(Instance) != 0UL) {
        if (__LL_ADC_REG_IsStopConversionOngoing(Instance) == 0UL) {
            __LL_ADC_REG_StopConversion(Instance);
        }
    }

    /* Set ADC group injected trigger source to SW start to ensure to not     */
    /* have an external trigger event occurring during the conversion stop    */
    /* ADC disable process.                                                   */
    __LL_ADC_INJ_SetTriggerSource(Instance, ADC_INJ_TRIG_SOFTWARE);

    /* Stop potential ADC conversion on going on ADC group injected.          */
    if (__LL_ADC_INJ_IsConversionOngoing(Instance) != 0UL) {
        if (__LL_ADC_INJ_IsStopConversionOngoing(Instance) == 0UL) {
            __LL_ADC_INJ_StopConversion(Instance);
        }
    }

    /* Check whether ADC state is compliant with expected state */
    if (READ_BIT(Instance->CR0, (ADC_CR0_JADSTP | ADC_CR0_ADSTP | ADC_CR0_JADSTART | ADC_CR0_ADSTART)) == 0UL) {
        /* ========== Reset ADC registers ========== */
        /* Reset register IER */
        CLEAR_BIT(Instance->IER,
                  (ADC_IER_ADRDYIE
                   | ADC_IER_EOCIE
                   | ADC_IER_EOSIE
                   | ADC_IER_OVRIE
                   | ADC_IER_EOSMPIE
                   | ADC_IER_JEOCIE
                   | ADC_IER_JEOSIE
                   | ADC_IER_AWD0IE
                   | ADC_IER_AWD1IE
                   | ADC_IER_AWD2IE
                  )
                 );

        /* Reset register ISR */
        SET_BIT(Instance->ISR,
                (ADC_ISR_ADRDY
                 | ADC_ISR_EOC
                 | ADC_ISR_EOS
                 | ADC_ISR_OVR
                 | ADC_ISR_EOSMP
                 | ADC_ISR_JEOC
                 | ADC_ISR_JEOS
                 | ADC_ISR_AWD0
                 | ADC_ISR_AWD1
                 | ADC_ISR_AWD2
                )
               );
        /* Reset register SIER */
        CLEAR_BIT(Instance->SIER, (ADC_SIER_CHANNEL));
        /* Reset register SISR */
        SET_BIT(Instance->SISR, (ADC_SISR_CHANNEL));

        /* Reset register HIER */
        CLEAR_BIT(Instance->HIER, (ADC_HIER_CHANNEL));
        /* Reset register SISR */
        SET_BIT(Instance->HISR, (ADC_HISR_CHANNEL));

        /* Reset register SIER */
        CLEAR_BIT(Instance->FIER, (ADC_FIER_CHANNEL));
        /* Reset register SISR */
        SET_BIT(Instance->FISR, (ADC_FISR_CHANNEL));

        /* Reset register CR1 */
        CLEAR_BIT(Instance->CR1,
                  (ADC_CR1_SYNCEN    | ADC_CR1_JAUTO  | ADC_CR1_JDISCEN
                   | ADC_CR1_DISCNUM | ADC_CR1_DISCEN | ADC_CR1_CONT
                   | ADC_CR1_OVRMOD  | ADC_CR1_ROVSM  | ADC_CR1_TROVS
                   | ADC_CR1_OVSS    | ADC_CR1_OVSR   | ADC_CR1_JOVSE
                   | ADC_CR1_ROVSE)
                 );

        /* Reset register CR2 */
        CLEAR_BIT(Instance->CR2,
                  (ADC_CR2_ISEL  | ADC_CR2_TBOMOD | ADC_CR2_TBIMOD
                   | ADC_CR2_TB_EN | ADC_CR2_CH_EN | ADC_CR2_FADC_EN
                   | ADC_CR2_REF_EN | ADC_CR2_BIAS_EN)
                 );

        /* Reset register DIFSEL */
        CLEAR_BIT(Instance->DIFSEL, (ADC_DIFSEL_DIFSEL));

        /* Reset register SMPR0 */
        CLEAR_BIT(Instance->SMPR0,
                  (ADC_SMPR0_SMP7 | ADC_SMPR0_SMP6 | ADC_SMPR0_SMP5
                   | ADC_SMPR0_SMP4 | ADC_SMPR0_SMP3 | ADC_SMPR0_SMP2
                   | ADC_SMPR0_SMP1 | ADC_SMPR0_SMP0)
                 );

        /* Reset register SMPR1 */
        CLEAR_BIT(Instance->SMPR1, (ADC_SMPR1_SMP11 | ADC_SMPR1_SMP10 | ADC_SMPR1_SMP9 | ADC_SMPR1_SMP8));

        /* Reset register CALR0 */
        CLEAR_BIT(Instance->SMPR0,
                  (ADC_CALR0_CAL7 | ADC_CALR0_CAL6 | ADC_CALR0_CAL5
                   | ADC_CALR0_CAL4 | ADC_CALR0_CAL3 | ADC_CALR0_CAL2
                   | ADC_CALR0_CAL1 | ADC_CALR0_CAL0)
                 );

        /* Reset register CALR1 */
        CLEAR_BIT(Instance->SMPR1, (ADC_CALR1_CAL11 | ADC_CALR1_CAL10 | ADC_CALR1_CAL9 | ADC_CALR1_CAL8));

        /* Reset register AWD0CR TR0 */
        CLEAR_BIT(Instance->AWDCR[0], ADC_AWD0CR_AWD0FILT | ADC_AWD0CR_AWD0CH);
        CLEAR_BIT(Instance->TR[0], ADC_TR0_HT0 | ADC_TR0_LT0);

        /* Reset register AWD1CR TR1 */
        CLEAR_BIT(Instance->AWDCR[1], ADC_AWD1CR_AWD1FILT | ADC_AWD1CR_AWD1CH);
        CLEAR_BIT(Instance->TR[1], ADC_TR1_HT1 | ADC_TR1_LT1);

        /* Reset register AWD2CR TR2 */
        CLEAR_BIT(Instance->AWDCR[2], ADC_AWD2CR_AWD2FILT | ADC_AWD2CR_AWD2CH);
        CLEAR_BIT(Instance->TR[2], ADC_TR2_HT2 | ADC_TR2_LT2);

        /* Reset register SQR0*/
        CLEAR_BIT(Instance->SQR0,
                  (ADC_SQR0_SQ8 | ADC_SQR0_SQ7 | ADC_SQR0_SQ6
                   | ADC_SQR0_SQ5 | ADC_SQR0_SQ4 | ADC_SQR0_SQ3
                   | ADC_SQR0_SQ2 | ADC_SQR0_SQ1)
                 );

        /* Reset register SQR1 */
        CLEAR_BIT(Instance->SQR1,
                  (ADC_SQR1_SQ16 | ADC_SQR1_SQ15 | ADC_SQR1_SQ14
                   | ADC_SQR1_SQ13 | ADC_SQR1_SQ12 | ADC_SQR1_SQ11
                   | ADC_SQR1_SQ10 | ADC_SQR1_SQ9)
                 );

        /* Reset register LR */
        CLEAR_BIT(Instance->LR, (ADC_LR_LEN | ADC_LR_EXTEN | ADC_LR_EXTSEL));

        /* Reset register JSQR */
        CLEAR_BIT(Instance->JSQR, ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3 | ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1);

        /* Reset register JLR */
        CLEAR_BIT(Instance->JLR, (ADC_JLR_JLEN | ADC_JLR_JEXTSEL | ADC_JLR_JEXTEN));

        /* Reset register DR */
        /* Note: bits in access mode read only, no direct reset applicable */

        /* Reset register OFR0 */
        CLEAR_BIT(Instance->OFR[0], ADC_OFR0_OFFSET);
        /* Reset register OFR1 */
        CLEAR_BIT(Instance->OFR[1], ADC_OFR1_OFFSET);
        /* Reset register OFR2 */
        CLEAR_BIT(Instance->OFR[2], ADC_OFR2_OFFSET);
        /* Reset register OFR3 */
        CLEAR_BIT(Instance->OFR[3], ADC_OFR3_OFFSET);

        /* Reset register GCR0 */
        CLEAR_BIT(Instance->GCR[0], ADC_GCR0_GAIN);
        /* Reset register GCR1 */
        CLEAR_BIT(Instance->GCR[1], ADC_GCR1_GAIN);
        /* Reset register GCR2 */
        CLEAR_BIT(Instance->GCR[2], ADC_GCR2_GAIN);
        /* Reset register GCR3 */
        CLEAR_BIT(Instance->GCR[3], ADC_GCR3_GAIN);

        /* Reset register DOFR0 */
        CLEAR_BIT(Instance->DOFR[0], ADC_DOFR0_OFFSET);
        /* Reset register DOFR1 */
        CLEAR_BIT(Instance->DOFR[1], ADC_DOFR1_OFFSET);
        /* Reset register DOFR2 */
        CLEAR_BIT(Instance->DOFR[2], ADC_DOFR2_OFFSET);
        /* Reset register DOFR3 */
        CLEAR_BIT(Instance->DOFR[3], ADC_DOFR3_OFFSET);

        /* Reset register DGCR0 */
        CLEAR_BIT(Instance->DGCR[0], ADC_DGCR0_GAIN);
        /* Reset register DGCR1 */
        CLEAR_BIT(Instance->DGCR[1], ADC_DGCR1_GAIN);
        /* Reset register DGCR2 */
        CLEAR_BIT(Instance->DGCR[2], ADC_DGCR2_GAIN);
        /* Reset register DGCR3 */
        CLEAR_BIT(Instance->DGCR[3], ADC_DGCR3_GAIN);

        /* Reset registers JDR1, JDR2, JDR3, JDR4 */
        /* Note: bits in access mode read only, no direct reset applicable */

        /* Reset register ECR0 */
        CLEAR_BIT(Instance->ECR[0], ADC_ECR0_ADSRC | ADC_ECR0_PSRCU | ADC_ECR0_PSRCD
                  | ADC_ECR0_AWD2SEL | ADC_ECR0_AWD1SEL | ADC_ECR0_AWD0SEL);

        /* Reset register ECR1 */
        CLEAR_BIT(Instance->ECR[1], ADC_ECR1_ADSRC | ADC_ECR1_PSRCU | ADC_ECR1_PSRCD
                  | ADC_ECR1_AWD2SEL | ADC_ECR1_AWD1SEL | ADC_ECR1_AWD0SEL);

        /* Reset register ECR2 */
        CLEAR_BIT(Instance->ECR[2], ADC_ECR2_ADSRC | ADC_ECR2_PSRCU | ADC_ECR2_PSRCD
                  | ADC_ECR2_AWD2SEL | ADC_ECR2_AWD1SEL | ADC_ECR2_AWD0SEL);

        /* Reset register ECR3 */
        CLEAR_BIT(Instance->ECR[3], ADC_ECR3_ADSRC | ADC_ECR3_PSRCU | ADC_ECR3_PSRCD
                  | ADC_ECR3_AWD2SEL | ADC_ECR3_AWD1SEL | ADC_ECR3_AWD0SEL);

        /* Reset register DMA_CR */
        for (uint8_t i = 0; i < 12; i++) {
            CLEAR_BIT(Instance->DMA_CR[i].TCR, ADC_DMA_TCR_CIRC | ADC_DMA_TCR_STP | ADC_DMA_TCR_START);
            CLEAR_BIT(Instance->DMA_CR[i].TAR, ADC_DMA_TAR_ADDR);
            CLEAR_BIT(Instance->DMA_CR[i].TLR, ADC_DMA_TLR_LENG);
        }

    } else {
        /* ADC instance is in an unknown state */
        /* Need to performing a hard reset of ADC instance, using high level      */
        /* clock source RCC ADC reset.                                            */
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Initialize some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @param  Instance ADC instance
  * @param  ADC_REG_InitStruct Pointer to a @ref ADC_REG_InitTypeDef structure
  * @retval An StatusETypeDef enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
LL_StatusETypeDef LL_ADC_REG_Init(ADC_TypeDef *Instance, ADC_REG_InitTypeDef *ADC_REG_InitStruct)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_CHANNEL(ADC_REG_InitStruct->Channel));
    assert_param(IS_ADC_REG_TRIG_SOURCE(ADC_REG_InitStruct->TriggerSource));
    assert_param(IS_ADC_REG_SEQ_LENGTH(ADC_REG_InitStruct->SequencerLength));
    assert_param(IS_ADC_REG_SEQ_POS(ADC_REG_InitStruct->SequencerPos));

    if (ADC_REG_InitStruct->SequencerLength != ADC_REG_SEQ_LENGTH_1) {
        assert_param(IS_ADC_REG_SEQ_DISCONT(ADC_REG_InitStruct->SequencerDiscont));
    }

    if (ADC_REG_InitStruct->Channel == ADC_CHANNEL_TEMPSENSOR) {
        /*Enable temperature sensor detection*/
        __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
        __LL_SYSCTRL_ADCBuf_En(SYSCTRL);
        __LL_SYSCTRL_Reg_Lock(SYSCTRL);
    }

    assert_param(IS_ADC_REG_CONTINUOUS_MODE(ADC_REG_InitStruct->ContinuousMode));
    assert_param(IS_ADC_REG_DIFFERSEL(ADC_REG_InitStruct->DifferSel));
    assert_param(IS_ADC_REG_SAMPTIMCLK(ADC_REG_InitStruct->SampTimClk));

    if (__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) {
        /* Configuration of ADC hierarchical scope:                               */
        /*  - ADC group regular                                                   */
        /*    - Set ADC group regular trigger source                              */
        /*    - Set ADC group regular sequencer length                            */
        /*    - Set ADC group regular sequencer discontinuous mode                */
        /*    - Set ADC group regular continuous mode                             */
        /*    - Set ADC group regular overrun behavior                            */
        /* Note: ADC trigger edge is set to value 0x0 by                          */
        /*       setting of trigger source to SW start.                           */
        /* Set ADC group regular sequencer length */
        if (ADC_REG_InitStruct->SequencerLength == ADC_REG_SEQ_LENGTH_1) {
            MODIFY_REG(Instance->LR,
                       ADC_LR_EXTSEL
                       | ADC_LR_EXTEN
                       | ADC_LR_LEN
                       ,
                       ADC_REG_InitStruct->TriggerSource
                       | ADC_REG_InitStruct->SequencerLength
                      );
            MODIFY_REG(Instance->SQR0,
                       ADC_SQR0_SQ1,
                       ADC_REG_InitStruct->Channel
                      );
        } else {
            MODIFY_REG(Instance->LR,
                       ADC_LR_EXTSEL
                       | ADC_LR_EXTEN
                       | ADC_LR_LEN
                       ,
                       ADC_REG_InitStruct->TriggerSource
                       | ADC_REG_InitStruct->SequencerLength
                      );

            if (ADC_REG_InitStruct->SequencerPos > 7) {
                MODIFY_REG(Instance->SQR1,
                           (ADC_SQR1_SQ9 << ((ADC_REG_InitStruct->SequencerPos - 8U) << 2U)),
                           (ADC_REG_InitStruct->Channel << ((ADC_REG_InitStruct->SequencerPos - 8U) << 2U))
                          );
            } else {
                MODIFY_REG(Instance->SQR0,
                           ADC_SQR0_SQ1 << (ADC_REG_InitStruct->SequencerPos << 2U),
                           (ADC_REG_InitStruct->Channel << (ADC_REG_InitStruct->SequencerPos << 2U))
                          );
            }
        }

        /*Continuous mode and discontinuous mode cannot be set to 1 at the same time*/
        CLEAR_BIT(Instance->CR1, ADC_CR1_CONT | ADC_CR1_DISCEN);

        if (ADC_REG_InitStruct->ContinuousMode == ADC_REG_CONV_CONTINUOUS) {
            SET_BIT(Instance->CR1, ADC_CR1_CONT);
        } else {
            MODIFY_REG(Instance->CR1,
                       ADC_CR1_DISCEN
                       | ADC_CR1_DISCNUM
                       | ADC_CR1_CONT
                       ,
                       ADC_REG_InitStruct->SequencerDiscont
                       | ADC_REG_InitStruct->ContinuousMode
                      );
        }

        /*Sampling time and calibration parameter set selection*/
        if (ADC_REG_InitStruct->Channel > 7) {
            MODIFY_REG(Instance->SMPR1,
                       ADC_SMPR1_SMP8 << ((ADC_REG_InitStruct->Channel - 8U) << 2U),
                       ADC_REG_InitStruct->SampTimClk << ((ADC_REG_InitStruct->Channel - 8U) << 2U)
                      );
        } else {
            MODIFY_REG(Instance->SMPR0,
                       ADC_SMPR0_SMP0 << (ADC_REG_InitStruct->Channel << 2U),
                       ADC_REG_InitStruct->SampTimClk << (ADC_REG_InitStruct->Channel << 2U)
                      );
        }

        /*configure the channel sample interrupt*/
        if (ADC_REG_InitStruct->SampInterrupt == ENABLE) {
            __LL_ADC_ENABLE_IT_DONE(Instance, ADC_REG_InitStruct->Channel);
        } else {
            __LL_ADC_DISABLE_IT_DONE(Instance, ADC_REG_InitStruct->Channel);
        }

        /*Differential single-end Offset/Gain setting*/
        SET_BIT(Instance->DIFSEL, (ADC_DIFSEL_DIFSEL & (ADC_REG_InitStruct->DifferSel << ADC_REG_InitStruct->Channel)));
    } else {
        /* Initialization error: ADC instance is not disabled. */
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Initialize some features of ADC group injected.
  * @note   These parameters have an impact on ADC scope: ADC group injected.
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  * @note   After using this function, other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group injected sequencer:
  *            map channel on the selected sequencer rank.
  *            Refer to function @ref LL_ADC_INJ_SetSequencerRanks().
  * @param  Instance ADC instance
  * @param  ADC_INJ_InitStruct Pointer to a @ref ADC_INJ_InitTypeDef structure
  * @retval An LL_StatusETypeDef enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
LL_StatusETypeDef LL_ADC_INJ_Init(ADC_TypeDef *Instance, ADC_INJ_InitTypeDef *ADC_INJ_InitStruct)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_CHANNEL(ADC_INJ_InitStruct->Channel));
    assert_param(IS_ADC_INJ_JSEQ_POS(ADC_INJ_InitStruct->SequencerPos));
    assert_param(IS_ADC_INJ_TRIG_SOURCE(ADC_INJ_InitStruct->TriggerSource));
    assert_param(IS_ADC_INJ_SEQ_SCAN_LENGTH(ADC_INJ_InitStruct->SequencerLength));
    assert_param(IS_ADC_INJ_SEQ_SCAN_DISCONT_MODE(ADC_INJ_InitStruct->SequencerDiscont));
    assert_param(IS_ADC_INJ_TRIG_AUTO(ADC_INJ_InitStruct->TrigAuto));

    /* Note: Hardware constraint (refer to description of this function):         */
    /*       ADC instance must be disabled.                                       */
    if (__LL_ADC_INJ_IsConversionOngoing(Instance) == 0UL) {
        if (ADC_INJ_InitStruct->Channel == ADC_CHANNEL_TEMPSENSOR) {
            /*Enable temperature sensor detection*/
            __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);
            __LL_SYSCTRL_ADCBuf_En(SYSCTRL);
            __LL_SYSCTRL_Reg_Lock(SYSCTRL);
        }

        /* Configuration of ADC hierarchical scope:                               */
        /*  - ADC group injected                                                  */
        /*    - Set ADC group injected trigger source                             */
        /*    - Set ADC group injected sequencer length                           */
        /*    - Set ADC group injected sequencer discontinuous mode               */
        /*    - Set ADC group injected conversion trigger: independent or         */
        /*      from ADC group regular (injected auto )                           */
        MODIFY_REG(Instance->CR1,
                   ADC_CR1_JDISCEN
                   | ADC_CR1_JAUTO
                   ,
                   ADC_INJ_InitStruct->SequencerDiscont
                   | ADC_INJ_InitStruct->TrigAuto
                  );

        MODIFY_REG(Instance->JLR,
                   ADC_JLR_JEXTSEL
                   | ADC_JLR_JEXTEN
                   | ADC_JLR_JLEN
                   ,
                   ADC_INJ_InitStruct->TriggerSource
                   | ADC_INJ_InitStruct->SequencerLength
                  );
        /*JSQR sequence position*/
        MODIFY_REG(Instance->JSQR, (ADC_JSQR_JSQ1 << ADC_INJ_InitStruct->SequencerPos),
                   ADC_INJ_InitStruct->Channel << ADC_INJ_InitStruct->SequencerPos);
    } else {
        /* Initialization error: ADC instance is not disabled. */
        status = LL_ERROR;
    }


    return status;
}

/**
  * @brief  Initializes the ADC MSP.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_MspInit(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the ADC MSP
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_MspDeInit(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */

/** @defgroup ADC_LL_Exported_Functions_Group2 ADC Config Functions
  * @brief    ADC Config Functions
  *
  @verbatim
  ===============================================================================
             ##### Peripheral Control functions #####
  ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the adc to ecu paramter
      (+) Configure the analog watchdog
      (+) Configure the DMA Transfer
      (+) Configure the calibration paramter
      (+) Configure the oversamping
  @endverbatim
  *
  * @{
  */


/**
  * @brief  Initialize some features of ADC and ECU linkage related register.
  * @note   These parameters have an impact on ADC scope: ADC to ECU register ECR0~3.
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  * @param  Instance ADC instance
  * @param  ADC_ECU_Config Pointer to a @ref ADC_ECU_Config structure
  * @retval An LL_StatusETypeDef enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
LL_StatusETypeDef LL_ADC_ECU_Config(ADC_TypeDef *Instance, ADC_ECUConfTypeDef *ADC_ECU_Config)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_ECU_GROUPSEL(ADC_ECU_Config->GroupSel));
    assert_param(IS_ADC_CHANNEL(ADC_ECU_Config->AddrDataSel));
    assert_param(IS_ADC_CHANNEL(ADC_ECU_Config->AWD0SourceSel));
    assert_param(IS_ADC_CHANNEL(ADC_ECU_Config->AWD1SourceSel));
    assert_param(IS_ADC_CHANNEL(ADC_ECU_Config->AWD2SourceSel));
    assert_param(IS_ADC_REG_AWD_SEL(ADC_ECU_Config->PingPongUpZero));
    assert_param(IS_ADC_REG_AWD_SEL(ADC_ECU_Config->PingPongDownZero));

    /* Note: Hardware constraint (refer to description of this function):         */
    /*       ADC instance must be disabled.                                       */
    if (__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) {
        /* Configuration of ADC hierarchical scope:                               */
        /*  - ADC to ECU control paramter                                         */
        /*    - Set ADC address data flag                                         */
        /*    - Set ADC ping pong up zero anolog watchdog                         */
        /*    - Set ADC ping pong down zero anolog watchdog                       */
        /*    - Set ADC anolog watchdog x detected channel                        */
        MODIFY_REG(Instance->ECR[ADC_ECU_Config->GroupSel],
                   ADC_ECR0_ADSRC
                   | ADC_ECR0_PSRCU
                   | ADC_ECR0_PSRCD
                   | ADC_ECR0_AWD2SEL
                   | ADC_ECR0_AWD1SEL
                   | ADC_ECR0_AWD0SEL
                   ,
                   (ADC_ECU_Config->AddrDataSel << 16U)
                   | (ADC_ECU_Config->PingPongUpZero << 14U)
                   | (ADC_ECU_Config->PingPongDownZero << 12U)
                   | (ADC_ECU_Config->AWD2SourceSel << 8U)
                   | (ADC_ECU_Config->AWD1SourceSel << 4U)
                   | ADC_ECU_Config->AWD0SourceSel
                  );
    } else {
        /* Initialization error: ADC instance is not disabled. */
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Configure the analog watchdog.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the selected analog watchdog, successive
  *         calls to this function can be used to reconfigure some parameters
  *         of structure "ADC_AnalogWDGCfgTypeDef" on the fly, without resetting
  *         the ADC.
  *         The same watchdog can monitor multiple channels simultaneously.
  * @param  Instance ADC instance
  * @param  AnalogWDGConfig Structure of ADC analog watchdog configuration
  * @retval LL status
  */
LL_StatusETypeDef LL_ADC_AnalogWDGConfig(ADC_TypeDef *Instance, ADC_AnalogWDGCfgTypeDef *AnalogWDGConfig)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_REG_AWD_SEL(AnalogWDGConfig->WatchdogNumber));
    assert_param(IS_ADC_AWD_CHANNEL(AnalogWDGConfig->Channel));
    assert_param(IS_ADC_REG_AWD_FILTER(AnalogWDGConfig->Filtering));

    /*  - Analog watchdog channels  */
    if ((__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) && (__LL_ADC_INJ_IsConversionOngoing(Instance) == 0UL)) {
        /* Configuration of analog watchdog:*/
        /* Set the filtering \ channel configuration */
        MODIFY_REG(Instance->AWDCR[AnalogWDGConfig->WatchdogNumber],
                   ADC_AWD0CR_AWD0CH | ADC_AWD0CR_AWD0FILT,
                   (AnalogWDGConfig->Channel)
                   | (AnalogWDGConfig->Filtering)
                  );
        /* Set the watchdog high and low threshold */
        MODIFY_REG(Instance->TR[AnalogWDGConfig->WatchdogNumber],
                   ADC_TR0_HT0 | ADC_TR0_LT0,
                   (AnalogWDGConfig->LowThreshold & ADC_TR0_LT0)
                   | ((AnalogWDGConfig->HighThreshold & ADC_TR0_LT0) << ADC_TR0_HT0_Pos)
                  );
    } else {
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Configure the DMA transfer.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the selected channel,
  *         Only one channel can be configured at a time.
  *         You cannot use the same address for different channels.
  * @param  Instance ADC instance
  * @param  DMATransferConfig Structure of ADC DMA transfer configuration
  * @retval LL status
  */
LL_StatusETypeDef LL_ADC_DMATransferConfig(ADC_TypeDef *Instance, ADC_DMATransferCfgTypeDef *DMATransferConfig)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_CHANNEL(DMATransferConfig->Channel));
    assert_param(IS_ADC_REG_DMA_TRANSFER(DMATransferConfig->TransferMode));

    /*  - DMA Transfer channels   */
    if ((__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) && (__LL_ADC_INJ_IsConversionOngoing(Instance) == 0UL)) {
        MODIFY_REG(Instance->DMA_CR[DMATransferConfig->Channel].TAR,
                   ADC_DMA_TAR_ADDR,
                   (DMATransferConfig->Address)
                  );
        MODIFY_REG(Instance->DMA_CR[DMATransferConfig->Channel].TLR,
                   ADC_DMA_TLR_LENG,
                   (DMATransferConfig->Length)
                  );
        MODIFY_REG(Instance->DMA_CR[DMATransferConfig->Channel].TCR,
                   ADC_DMA_TCR_START | ADC_DMA_TCR_CIRC,
                   (DMATransferConfig->TransferMode)
                  );

        if (DMATransferConfig->HalfInterrupt == ENABLE) {
            __LL_ADC_ENABLE_IT_HALF(Instance, DMATransferConfig->Channel);
        } else {
            __LL_ADC_DISABLE_IT_HALF(Instance, DMATransferConfig->Channel);
        }

        if (DMATransferConfig->FullInterrupt == ENABLE) {
            __LL_ADC_ENABLE_IT_FULL(Instance, DMATransferConfig->Channel);
        } else {
            __LL_ADC_DISABLE_IT_FULL(Instance, DMATransferConfig->Channel);
        }

    } else {
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Configure the calibration parameters.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the selected channel,
  *         A total of four sets of calibration parameters can be selected for 12 channels.
  * @param  Instance ADC instance
  * @param  CalibrationConfig Structure of ADC DMA transfer configuration
  * @retval LL status
  */
LL_StatusETypeDef LL_ADC_CalibrationConfig(ADC_TypeDef *Instance, ADC_CalibrationTypeDef *CalibrationConfig)
{
    LL_StatusETypeDef status = LL_OK;

    temp_offset = 0;
    temp_gain = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_INSTANCE(Instance));
    assert_param(IS_ADC_CHANNEL(CalibrationConfig->Channel));
    assert_param(IS_LL_ADC_CALCOEFSEL(CalibrationConfig->CalibrationGroup));

    /* Determine if the ADC is started */
    if ((__LL_ADC_REG_IsConversionOngoing(Instance) == 0UL) && (__LL_ADC_INJ_IsConversionOngoing(Instance) == 0UL)) {

        __LL_ADC_SetCalGroup(Instance, CalibrationConfig->Channel, CalibrationConfig->CalibrationGroup);

        /*Determines whether the selected channel is single-ended or differential*/
        if (__LL_ADC_GetChannelSingleDiff(Instance, CalibrationConfig->Channel)) {

            temp_offset = (int16_t)(pCoef.DiffOffset + (((int32_t)CalibrationConfig->Offset << 13) / pCoef.DiffGain));
            temp_gain = (uint16_t)((uint32_t)(CalibrationConfig->Gain * pCoef.DiffGain) >> 13);

            LL_ADC_OverSamp_Mode(Instance, temp_offset);

            MODIFY_REG(Instance->DOFR[CalibrationConfig->CalibrationGroup],
                       ADC_DOFR0_OFFSET,
                       (temp_offset)
                      );
            MODIFY_REG(Instance->DGCR[CalibrationConfig->CalibrationGroup],
                       ADC_DGCR0_GAIN,
                       (temp_gain)
                      );
        } else {

            temp_offset = (int16_t)(pCoef.SingleOffset + (((int32_t)CalibrationConfig->Offset << 13) / pCoef.SingleGain));
            temp_gain = (uint16_t)((uint32_t)(CalibrationConfig->Gain * pCoef.SingleGain) >> 13);

            LL_ADC_OverSamp_Mode(Instance, temp_offset);

            MODIFY_REG(Instance->OFR[CalibrationConfig->CalibrationGroup],
                       ADC_OFR0_OFFSET,
                       (temp_offset)
                      );
            MODIFY_REG(Instance->GCR[CalibrationConfig->CalibrationGroup],
                       ADC_GCR0_GAIN,
                       (temp_gain)
                      );
        }

    } else {
        status = LL_ERROR;
    }

    return status;
}

/**
  * @brief  Convert to actual degrees Celsius
  * @note Temperature = (Vout - 1.34) / 0.005
  * @retval LL status
  */
float LL_ADC_TemperatureCovert(uint16_t voltage_data)
{
    float  voltage_realvalue = 0;
    float  temper_realvalue = 0;

    voltage_realvalue = (3.0 * voltage_data * 1000) / 8192.0;

    temper_realvalue = (voltage_realvalue - 1340) / 5;

    return temper_realvalue;

}

/**
  * @}
  */


/** @defgroup ADC_LL_Exported_Functions_Interrupt Interrupt handler and call back
  * @brief    Interrupt handler and call back
  * @{
  */

/**
  * @brief  ADC Ready detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_AdRdyCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_AdRdyCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC EoSmp detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_EosmpCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_EoSmpCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Anolog WatchDog 2 detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_AnologWD2Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_AnologWD2Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC Anolog WatchDog 1 detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_AnologWD1Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_AnologWD1Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC Anolog WatchDog 0 detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_AnologWD0Callback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_AnologWD0Callback could be implemented in the user file
     */
}

/**
  * @brief  ADC OverRun detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_OverRunCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_OverRunCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC injected end of sequencer detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_JeosCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_JeosCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC regular end of sequencer detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_EosCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_EosCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC injected end of conversion detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_JeocCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_JeocCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC regualr end of conversion detection callback.
  * @param  Instance ADC instance
  * @return None
  */
__WEAK void LL_ADC_EocCallback(ADC_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_EocCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC Sample done detection callback.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
__WEAK void LL_ADC_SampCallback(ADC_TypeDef *Instance, uint8_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_SampCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC DMA Half detection callback.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
__WEAK void LL_ADC_HalfCallback(ADC_TypeDef *Instance, uint8_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_HalfCallback could be implemented in the user file
     */
}

/**
  * @brief  ADC DMA Full detection callback.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
__WEAK void LL_ADC_FullCallback(ADC_TypeDef *Instance, uint8_t Channel)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ADC_FullCallback could be implemented in the user file
     */
}
/**
  * @brief  This function handles ADC Normal interrupts requests.
  * @param  Instance ADC instance
  * @return None
  */
void LL_ADC_NORM_IRQHandler(ADC_TypeDef *Instance)
{
    if ((__LL_ADC_GET_IT_ADRDY(Instance)) && (__LL_ADC_GET_FLAG_ADRDY(Instance))) {
        __LL_ADC_CLEAR_FLAG_ADRDY(Instance);

        /*Handle something*/
        LL_ADC_AdRdyCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_EOSMP(Instance)) && (__LL_ADC_GET_FLAG_EOSMP(Instance))) {
        __LL_ADC_CLEAR_FLAG_EOSMP(Instance);

        /*Handle something*/
        LL_ADC_EosmpCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_AWD2(Instance)) && (__LL_ADC_GET_FLAG_AWD2(Instance))) {
        __LL_ADC_CLEAR_FLAG_AWD2(Instance);

        /*Handle something*/
        LL_ADC_AnologWD2Callback(Instance);
    }

    if ((__LL_ADC_GET_IT_AWD1(Instance)) && (__LL_ADC_GET_FLAG_AWD1(Instance))) {
        __LL_ADC_CLEAR_FLAG_AWD1(Instance);

        /*Handle something*/
        LL_ADC_AnologWD1Callback(Instance);
    }

    if ((__LL_ADC_GET_IT_AWD0(Instance)) && (__LL_ADC_GET_FLAG_AWD0(Instance))) {
        __LL_ADC_CLEAR_FLAG_AWD0(Instance);

        /*Handle something*/
        LL_ADC_AnologWD0Callback(Instance);
    }

    if ((__LL_ADC_GET_IT_OVR(Instance)) && (__LL_ADC_GET_FLAG_OVR(Instance))) {
        __LL_ADC_CLEAR_FLAG_OVR(Instance);

        /*Handle something*/
        LL_ADC_OverRunCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_JEOS(Instance)) && (__LL_ADC_GET_FLAG_JEOS(Instance))) {
        __LL_ADC_CLEAR_FLAG_JEOS(Instance);

        /*Handle something*/
        LL_ADC_JeosCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_JEOC(Instance)) && (__LL_ADC_GET_FLAG_JEOC(Instance))) {
        __LL_ADC_CLEAR_FLAG_JEOC(Instance);

        /*Handle something*/
        LL_ADC_JeocCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_EOS(Instance)) && (__LL_ADC_GET_FLAG_EOS(Instance))) {
        __LL_ADC_CLEAR_FLAG_EOS(Instance);

        /*Handle something*/
        LL_ADC_EosCallback(Instance);
    }

    if ((__LL_ADC_GET_IT_EOC(Instance)) && (__LL_ADC_GET_FLAG_EOC(Instance))) {
        __LL_ADC_CLEAR_FLAG_EOC(Instance);

        /*Handle something*/
        LL_ADC_EocCallback(Instance);
    }

}

/**
  * @brief  This function handles ADC Sample interrupts requests.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
void LL_ADC_SAMP_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel)
{
    if ((__LL_ADC_GET_IT_DONE(Instance, Channel)) && (__LL_ADC_GET_FLAG_DONE(Instance, Channel))) {
        __LL_ADC_CLEAR_FLAG_DONE(Instance, Channel);

        /*Handle something*/
        LL_ADC_SampCallback(Instance, Channel);
    }
}

/**
  * @brief  This function handles ADC Dma Half interrupts requests.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
void LL_ADC_HALF_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel)
{
    if ((__LL_ADC_GET_IT_HALF(Instance, Channel)) && (__LL_ADC_GET_FLAG_HALF(Instance, Channel))) {
        __LL_ADC_CLEAR_FLAG_HALF(Instance, Channel);

        /*Handle something*/
        LL_ADC_HalfCallback(Instance, Channel);
    }
}

/**
  * @brief  This function handles ADC Dma Full interrupts requests.
  * @param  Instance ADC instance
  * @param  Channel  0~11
  * @return None
  */
void LL_ADC_FULL_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel)
{
    if ((__LL_ADC_GET_IT_FULL(Instance, Channel)) && (__LL_ADC_GET_FLAG_FULL(Instance, Channel))) {
        __LL_ADC_CLEAR_FLAG_FULL(Instance, Channel);

        /*Handle something*/
        LL_ADC_FullCallback(Instance, Channel);
    }
}
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup ADC_LL_Private_Functions
  * @{
  */

/**
  * @brief  Read ADC single-ended self-calibration data
  * @note   No external calls
  * @return None
  */
static void LL_ADC_ReadCoef(void)
{
    Calib_read_data[0] = SYSCTRL->SINGLE;
    Calib_read_data[1] = SYSCTRL->DIFFER;
    Calib_read_data[2] = SYSCTRL->SINGLE_BUFF;

    /* Determinate whether the SoC has been calibrated. If it has not been calibrated,
       the standard register is written into the user configuration data;
       if the calibration criterion reads the calibration data*/
    if (memcmp(&Calib_check_data, &Calib_read_data, sizeof(Calib_read_data)) == 0) {
        /* CALB_SE*/
        pCoef.SingleGain       = 8192;
        /* CALA_SE*/
        pCoef.SingleOffset     = 0;
        /* CALB_DF*/
        pCoef.DiffGain         = 8192;
        /* CALA_DF*/
        pCoef.DiffOffset       = 0;
        /* CALB_WB*/
        pCoef.SingleBuffGain   = 8192;
        /* CALA_WB*/
        pCoef.SingleBuffOffset = 0;
    } else {
        /* CALB_SE*/
        pCoef.SingleGain       = (uint16_t)Calib_read_data[0];
        /* CALA_SE*/
        pCoef.SingleOffset     = (int16_t)(Calib_read_data[0] >> 16);
        /* CALB_DF*/
        pCoef.DiffGain         = (uint16_t)Calib_read_data[1];
        /* CALA_DF*/
        pCoef.DiffOffset       = (int16_t)(Calib_read_data[1] >> 16);
        /* CALB_WB*/
        pCoef.SingleBuffGain   = (uint16_t)Calib_read_data[2];
        /* CALA_WB*/
        pCoef.SingleBuffOffset = (int16_t)(Calib_read_data[2] >> 16);
    }

}

/**
  * @brief  The calibration coefficient varies with the change of oversampling
  * @note   No external calls
  * @param  Instance ADC instance
  * @param  offset ADC offset
  * @return None
  */
static void LL_ADC_OverSamp_Mode(ADC_TypeDef *Instance, int16_t offset)
{
    int8_t temp_mode = 0;

    temp_mode = (__LL_ADC_GetOverSamplingShift(Instance) >> ADC_CR1_OVSS_Pos) - \
                (__LL_ADC_GetOverSamplingRatio(Instance) >> ADC_CR1_OVSR_Pos);

    if ((temp_mode - 1) >= 0) {
        temp_offset = offset >> (temp_mode - 1);
    } else {
        temp_offset = offset << (abs(temp_mode) + 1);
    }
}

/**
  * @}
  */


#endif /* LL_ADC_MODULE_ENABLE */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

