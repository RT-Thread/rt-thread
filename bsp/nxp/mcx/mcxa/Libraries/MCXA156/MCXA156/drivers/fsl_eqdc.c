/*
 * Copyright 2022, 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_eqdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.eqdc"
#endif

#if defined(EQDC_RSTS)
#define EQDC_RESETS_ARRAY EQDC_RSTS
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for EQDC module.
 *
 * @param base EQDC peripheral base address
 */
static uint32_t EQDC_GetInstance(EQDC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to EQDC bases for each instance. */
static EQDC_Type *const s_eqdcBases[] = EQDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to EQDC clocks for each instance. */
#if defined(QDC_CLOCKS)
static const clock_ip_name_t s_eqdcClocks[] = QDC_CLOCKS;
#elif defined(ENC_CLOCKS)
static const clock_ip_name_t s_eqdcClocks[] = ENC_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(EQDC_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_eqdcResets[] = EQDC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EQDC_GetInstance(EQDC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_eqdcBases); instance++)
    {
        if (s_eqdcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_eqdcBases));

    return instance;
}

/*
 * Initializes the EQDC module.
 *
 * This function initializes the EQDC by enabling the IP bus clock (optional).
 *
 * param base   EQDC peripheral base address.
 * param psConfig Pointer to configuration structure.
 */
void EQDC_Init(EQDC_Type *base, const eqdc_config_t *psConfig)
{
    assert(NULL != psConfig);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_eqdcClocks[EQDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(EQDC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_eqdcResets[EQDC_GetInstance(base)]);
#endif

    /* Initialize Double-set registers */
    EQDC_ClearBufferedRegisterLoadUpdateMode(base);
    EQDC_ClearEqdcLdok(base);
    
    /* Counter value. */
    EQDC_SetPositionCounterValue(base, psConfig->positionCounterValue);

    /* Initial value. */
    EQDC_SetInitialPositionValue(base, psConfig->positionInitialValue);

    /* Modulus value. */
    EQDC_SetPositionModulusValue(base, psConfig->positionModulusValue);

    /* Compare value. */
    EQDC_SetPositionCompare0Value(base, psConfig->positionCompareValue[0]);
    EQDC_SetPositionCompare1Value(base, psConfig->positionCompareValue[1]);
    EQDC_SetPositionCompare2Value(base, psConfig->positionCompareValue[2]);
    EQDC_SetPositionCompare3Value(base, psConfig->positionCompareValue[3]);

    EQDC_SetEqdcLdok(base);
    while (EQDC_GetEqdcLdok(base) != 0U)
    {
    }

    /* Watchdog. */
    EQDC_SetWatchdogTimeout(base, psConfig->watchdogTimeoutValue);

    /* Clear EQDC_REV */
    base->REV = 0U;

    /* EQDC_IMR. */
    base->IMR = EQDC_IMR_FPHA(psConfig->filterPhaseA) | EQDC_IMR_FPHB(psConfig->filterPhaseB) |
                EQDC_IMR_FIND_PRE(psConfig->filterIndPre) | EQDC_IMR_FHOM_ENA(psConfig->filterHomEna);

    /* EQDC_FILT. */
    base->FILT = EQDC_FILT_PRSC(psConfig->prescaler) | /* Prescaler used by LASTEDGE and POSDPER. */
                 EQDC_FILT_FILT_CS(psConfig->filterClockSourceselection) |
                 EQDC_FILT_FILT_CNT(psConfig->filterSampleCount) | EQDC_FILT_FILT_PER(psConfig->filterSamplePeriod);

    /* EQDC_CTRL. */
    base->CTRL = EQDC_CTRL_W1C_FLAGS |                                /* W1C flags. */
                 (uint16_t)psConfig->homeEnableInitPosCounterMode |  /* HOME Enable trigger. */
                 (uint16_t)psConfig->indexPresetInitPosCounterMode | /* INDEX Preset trigger. */
                 EQDC_CTRL_REV(psConfig->enableReverseDirection) |   /* Reverse direction. */
                 EQDC_CTRL_WDE(psConfig->enableWatchdog) |           /* Enable watchdog. */
                 EQDC_CTRL_DMAEN(psConfig->enableDma);               /* Enable Dma. */

    /* Set mode of count. */
    EQDC_SetCountMode(base, psConfig->countMode); /* eqdcoder count mode. */

    /* EQDC_CTRL2. */
    base->CTRL2 =
        EQDC_CTRL2_ONCE(psConfig->countOnce) |
        EQDC_CTRL2_INITPOS(psConfig->enableTriggerInitPositionCounter) | /* TRIGGER initializes position counter. */
#if (defined(FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD) && FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD)
        EQDC_CTRL2_EMIP(psConfig->enableIndexInitPositionCounter)|       /* Index Event Edge Mark initializes position counter */
#endif /* FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD */
        EQDC_CTRL2_PMEN(psConfig->enablePeriodMeasurement) |             /* Enable period measurement. */
        EQDC_CTRL2_OUTCTL(psConfig->outputPulseMode) |                   /* Output pulse. */
        EQDC_CTRL2_REVMOD(psConfig->revolutionCountCondition) |          /* Revolution count condition. */
        EQDC_CTRL2_LDMOD(psConfig->bufferedRegisterLoadMode) | /* Buffered register load (Update) mode select. */
        EQDC_CTRL2_UPDPOS(psConfig->enableTriggerClearPositionRegisters) | /* TRIGGER clears position register. */
        EQDC_CTRL2_UPDHLD(psConfig->enableTriggerHoldPositionRegisters);   /* TRIGGER loads position registers. */

    /* Set mode of operation. */
    EQDC_SetOperateMode(base, psConfig->operateMode); /* eqdcoder work mode. */

    /* Enable interrupts. */
    EQDC_EnableInterrupts(base, psConfig->enabledInterruptsMask);
}

/*
 * De-initializes the EQDC module.
 *
 * This function deinitializes the EQDC by:
 * 1. Disables the IP bus clock (optional).
 *
 * param base EQDC peripheral base address.
 */
void EQDC_Deinit(EQDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_eqdcClocks[EQDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * Gets an available pre-defined configuration.
 *
 * The default value are:
 *    psConfig->enableReverseDirection              = false;
 *    psConfig->countOnce                           = false;
 *    psConfig->operateMode                         = kEQDC_QuadratureDecodeOperationMode;
 *    psConfig->countMode                           = kEQDC_QuadratureX4;
 *    psConfig->homeEnableInitPosCounterMode        = kEQDC_HomeInitPosCounterDisabled;
 *    psConfig->indexPresetInitPosCounterMode       = kEQDC_IndexInitPosCounterDisabled;
 *    psConfig->enableIndexInitPositionCounter      = false;
 *    psConfig->enableDma                           = false;
 *    psConfig->bufferedRegisterLoadMode            = false;
 *    psConfig->enableTriggerInitPositionCounter    = false;
 *    psConfig->enableTriggerClearPositionRegisters = false;
 *    psConfig->enableTriggerHoldPositionRegisters  = false;
 *    psConfig->enableWatchdog                      = false;
 *    psConfig->watchdogTimeoutValue                = 0xFFFFU;
 *    psConfig->filterPhaseA                        = 0U;
 *    psConfig->filterPhaseB                        = 0U;
 *    psConfig->filterIndPre                        = 0U;
 *    psConfig->filterHomEna                        = 0U;
 *    psConfig->filterClockSourceselection          = false;
 *    psConfig->filterSampleCount                   = kEQDC_Filter3Samples;
 *    psConfig->filterSamplePeriod                  = 0U;
 *    psConfig->outputPulseMode                     = kEQDC_OutputPulseOnCounterEqualCompare;
 *    psConfig->positionCompareValue[0]  	    = 0xFFFFFFFFU;
 *    psConfig->positionCompareValue[1]             = 0xFFFFFFFFU;
 *    psConfig->positionCompareValue[2]             = 0xFFFFFFFFU;
 *    psConfig->positionCompareValue[3]             = 0xFFFFFFFFU;
 *    psConfig->revolutionCountCondition            = kEQDC_RevolutionCountOnIndexPulse;
 *    psConfig->positionModulusValue                = 0U;
 *    psConfig->positionInitialValue                = 0U;
 *    psConfig->positionCounterValue                = 0U;
 *    psConfig->enablePeriodMeasurement             = false;
 *    psConfig->prescaler                           = kEQDC_Prescaler1;
 *    psConfig->enabledInterruptsMask               = 0U;
 *
 * param psConfig Pointer to configuration structure.
 */
void EQDC_GetDefaultConfig(eqdc_config_t *psConfig)
{
    assert(NULL != psConfig);

    psConfig->enableReverseDirection              = false;
    psConfig->countOnce                           = false;
    psConfig->operateMode                         = kEQDC_QuadratureDecodeOperationMode; /*!< Decode Mode. */
    psConfig->countMode                           = kEQDC_QuadratureX4;
    psConfig->homeEnableInitPosCounterMode        = kEQDC_HomeInitPosCounterDisabled;
    psConfig->indexPresetInitPosCounterMode       = kEQDC_IndexInitPosCounterDisabled;
#if (defined(FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD) && FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD)
    psConfig->enableIndexInitPositionCounter      = false;
#endif /* FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD */
    psConfig->enableDma                           = false;
    psConfig->bufferedRegisterLoadMode            = false;
    psConfig->enableTriggerInitPositionCounter    = false;
    psConfig->enableTriggerClearPositionRegisters = false;
    psConfig->enableTriggerHoldPositionRegisters  = false;
    psConfig->enableWatchdog                      = false;
    psConfig->watchdogTimeoutValue                = 0xFFFFU;
    psConfig->filterPhaseA                        = 0U;
    psConfig->filterPhaseB                        = 0U;
    psConfig->filterIndPre                        = 0U;
    psConfig->filterHomEna                        = 0U;
    psConfig->filterClockSourceselection          = false;
    psConfig->filterSampleCount                   = kEQDC_Filter3Samples;
    psConfig->filterSamplePeriod                  = 0U;
    psConfig->outputPulseMode                     = kEQDC_OutputPulseOnCounterEqualCompare;
    psConfig->positionCompareValue[0]             = 0xFFFFFFFFU;
    psConfig->positionCompareValue[1]             = 0xFFFFFFFFU;
    psConfig->positionCompareValue[2]             = 0xFFFFFFFFU;
    psConfig->positionCompareValue[3]             = 0xFFFFFFFFU;
    psConfig->revolutionCountCondition            = kEQDC_RevolutionCountOnIndexPulse;
    psConfig->positionModulusValue                = 0U;
    psConfig->positionInitialValue                = 0U;
    psConfig->positionCounterValue                = 0U;
    psConfig->enablePeriodMeasurement             = false;
    psConfig->prescaler                           = kEQDC_Prescaler1;
    psConfig->enabledInterruptsMask               = 0U;
}

/*
 * Initializes the mode of operation.
 *
 * The Quadrature Decoder operates in following 4 operation modes:
 *   1.Quadrature Decode(QDC) Operation Mode (CTRL[PH1] = 0,CTRL2[OPMODE] = 0)
 *   2.Quadrature Count(QCT) Operation Mode (CTRL[PH1] = 0,CTRL2[OPMODE] = 1)
 *   3.Single Phase Decode(PH1DC) Operation Mode (CTRL[PH1] = 1,CTRL2[OPMODE] = 0)
 *   4.Single Phase Count(PH1CT) Operation Mode (CTRL[PH1] = 1,CTRL2[OPMODE] = 1)
 *
 * param base   EQDC peripheral base address.
 * param psConfig Pointer to configuration structure.
 */
void EQDC_SetOperateMode(EQDC_Type *base, eqdc_operate_mode_t operateMode)
{
    switch (operateMode)
    {
        case kEQDC_QuadratureDecodeOperationMode:
            base->CTRL &= ~EQDC_CTRL_PH1_MASK;
            base->CTRL2 &= ~EQDC_CTRL2_OPMODE_MASK;
            break;

        case kEQDC_QuadratureCountOperationMode:
            base->CTRL &= ~EQDC_CTRL_PH1_MASK;
            base->CTRL2 |= EQDC_CTRL2_OPMODE_MASK;
            break;

        case kEQDC_SinglePhaseDecodeOperationMode:
            base->CTRL |= EQDC_CTRL_PH1_MASK;
            base->CTRL2 &= ~EQDC_CTRL2_OPMODE_MASK;
            break;

        case kEQDC_SinglePhaseCountOperationMode:
            base->CTRL |= EQDC_CTRL_PH1_MASK;
            base->CTRL2 |= EQDC_CTRL2_OPMODE_MASK;
            break;

        default:
            assert(false);
            break;
    }
}