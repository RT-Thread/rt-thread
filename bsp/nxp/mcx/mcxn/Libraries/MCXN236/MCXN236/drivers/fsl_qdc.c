/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_qdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.qdc"
#endif

#define QDC_CTRL_W1C_FLAGS (QDC_CTRL_HIRQ_MASK | QDC_CTRL_XIRQ_MASK | QDC_CTRL_DIRQ_MASK | QDC_CTRL_CMPIRQ_MASK)
#if (defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
#define QDC_CTRL2_W1C_FLAGS (QDC_CTRL2_ROIRQ_MASK | QDC_CTRL2_RUIRQ_MASK)
#else
#define QDC_CTRL2_W1C_FLAGS (QDC_CTRL2_SABIRQ_MASK | QDC_CTRL2_ROIRQ_MASK | QDC_CTRL2_RUIRQ_MASK)
#endif

#if defined(QDC_RSTS)
#define QDC_RESETS_ARRAY QDC_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for QDC module.
 *
 * @param base QDC peripheral base address
 */
static uint32_t QDC_GetInstance(QDC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to QDC bases for each instance. */
static QDC_Type *const s_qdcBases[] = QDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to QDC clocks for each instance. */
static const clock_ip_name_t s_qdcClocks[] = QDC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(QDC_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_qdcResets[] = QDC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t QDC_GetInstance(QDC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_qdcBases); instance++)
    {
        if (s_qdcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_qdcBases));

    return instance;
}

/*!
 * brief Initialization for the QDC module.
 *
 * This function is to make the initialization for the QDC module. It should be called firstly before any operation to
 * the QDC with the operations like:
 *  - Enable the clock for QDC module.
 *  - Configure the QDC's working attributes.
 *
 * param base   QDC peripheral base address.
 * param config Pointer to configuration structure. See to "qdc_config_t".
 */
void QDC_Init(QDC_Type *base, const qdc_config_t *config)
{
    assert(NULL != config);

    uint16_t tmp16;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_qdcClocks[QDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(QDC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_qdcResets[QDC_GetInstance(base)]);
#endif

    /* QDC_CTRL. */
    tmp16 = base->CTRL & (uint16_t)(~(QDC_CTRL_W1C_FLAGS | QDC_CTRL_HIP_MASK | QDC_CTRL_HNE_MASK | QDC_CTRL_REV_MASK |
                                      QDC_CTRL_PH1_MASK | QDC_CTRL_XIP_MASK | QDC_CTRL_XNE_MASK | QDC_CTRL_WDE_MASK));
    /* For HOME trigger. */
    if (kQDC_HOMETriggerDisabled != config->HOMETriggerMode)
    {
        tmp16 |= QDC_CTRL_HIP_MASK;
        if (kQDC_HOMETriggerOnFallingEdge == config->HOMETriggerMode)
        {
            tmp16 |= QDC_CTRL_HNE_MASK;
        }
    }
    /* For encoder work mode. */
    if (config->enableReverseDirection)
    {
        tmp16 |= QDC_CTRL_REV_MASK;
    }
    if (kQDC_DecoderWorkAsSignalPhaseCountMode == config->decoderWorkMode)
    {
        tmp16 |= QDC_CTRL_PH1_MASK;
    }
    /* For INDEX trigger. */
    if (kQDC_INDEXTriggerDisabled != config->INDEXTriggerMode)
    {
        tmp16 |= QDC_CTRL_XIP_MASK;
        if (kQDC_INDEXTriggerOnFallingEdge == config->INDEXTriggerMode)
        {
            tmp16 |= QDC_CTRL_XNE_MASK;
        }
    }
    /* Watchdog. */
    if (config->enableWatchdog)
    {
        tmp16 |= QDC_CTRL_WDE_MASK;
        base->WTR = config->watchdogTimeoutValue; /* WDOG can be only available when the feature is enabled. */
    }
    base->CTRL = tmp16;

    /* QDC_FILT. */
    base->FILT = QDC_FILT_FILT_CNT(config->filterCount) | QDC_FILT_FILT_PER(config->filterSamplePeriod)
#if (defined(FSL_FEATURE_QDC_HAS_FILT_PRSC) && FSL_FEATURE_QDC_HAS_FILT_PRSC)
                 | QDC_FILT_FILT_PRSC(config->filterPrescaler)
#endif
        ;

    /* QDC_CTRL2. */
    tmp16 = base->CTRL2 & (uint16_t)(~(QDC_CTRL2_W1C_FLAGS | QDC_CTRL2_OUTCTL_MASK | QDC_CTRL2_REVMOD_MASK |
                                       QDC_CTRL2_MOD_MASK | QDC_CTRL2_UPDPOS_MASK | QDC_CTRL2_UPDHLD_MASK));
    if (kQDC_POSMATCHOnReadingAnyPositionCounter == config->positionMatchMode)
    {
        tmp16 |= QDC_CTRL2_OUTCTL_MASK;
    }
    if (kQDC_RevolutionCountOnRollOverModulus == config->revolutionCountCondition)
    {
        tmp16 |= QDC_CTRL2_REVMOD_MASK;
    }
    if (config->enableModuloCountMode)
    {
        tmp16 |= QDC_CTRL2_MOD_MASK;
        /* Set modulus value. */
        base->UMOD = (uint16_t)(config->positionModulusValue >> 16U); /* Upper 16 bits. */
        base->LMOD = (uint16_t)(config->positionModulusValue);        /* Lower 16 bits. */
    }
    if (config->enableTRIGGERClearPositionCounter)
    {
        tmp16 |= QDC_CTRL2_UPDPOS_MASK;
    }
    if (config->enableTRIGGERClearHoldPositionCounter)
    {
        tmp16 |= QDC_CTRL2_UPDHLD_MASK;
    }
    base->CTRL2 = tmp16;

#if (defined(FSL_FEATURE_QDC_HAS_CTRL3) && FSL_FEATURE_QDC_HAS_CTRL3)
    /* QDC_CTRL3. */
    tmp16 = base->CTRL3 & (uint16_t)(~(QDC_CTRL3_PMEN_MASK | QDC_CTRL3_PRSC_MASK));
    if (config->enablePeriodMeasurementFunction)
    {
        tmp16 |= QDC_CTRL3_PMEN_MASK;
        /* Set prescaler value. */
        tmp16 |= ((uint16_t)config->prescalerValue << QDC_CTRL3_PRSC_SHIFT);
    }
    base->CTRL3 = tmp16;
#endif

    /* QDC_UCOMP & QDC_LCOMP. */
    base->UCOMP = (uint16_t)(config->positionCompareValue >> 16U); /* Upper 16 bits. */
    base->LCOMP = (uint16_t)(config->positionCompareValue);        /* Lower 16 bits. */

    /* QDC_UINIT & QDC_LINIT. */
    base->UINIT = (uint16_t)(config->positionInitialValue >> 16U); /* Upper 16 bits. */
    base->LINIT = (uint16_t)(config->positionInitialValue);        /* Lower 16 bits. */
}

/*!
 * brief De-initialization for the QDC module.
 *
 * This function is to make the de-initialization for the QDC module. It could be called when QDC is no longer used with
 * the operations like:
 *  - Disable the clock for QDC module.
 *
 * param base QDC peripheral base address.
 */
void QDC_Deinit(QDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_qdcClocks[QDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get an available pre-defined settings for QDC's configuration.
 *
 * This function initializes the QDC configuration structure with an available settings, the default value are:
 * code
 *   config->enableReverseDirection                = false;
 *   config->decoderWorkMode                       = kQDC_DecoderWorkAsNormalMode;
 *   config->HOMETriggerMode                       = kQDC_HOMETriggerDisabled;
 *   config->INDEXTriggerMode                      = kQDC_INDEXTriggerDisabled;
 *   config->enableTRIGGERClearPositionCounter     = false;
 *   config->enableTRIGGERClearHoldPositionCounter = false;
 *   config->enableWatchdog                        = false;
 *   config->watchdogTimeoutValue                  = 0U;
 *   config->filterCount                           = 0U;
 *   config->filterSamplePeriod                    = 0U;
 *   config->positionMatchMode                     = kQDC_POSMATCHOnPositionCounterEqualToComapreValue;
 *   config->positionCompareValue                  = 0xFFFFFFFFU;
 *   config->revolutionCountCondition              = kQDC_RevolutionCountOnINDEXPulse;
 *   config->enableModuloCountMode                 = false;
 *   config->positionModulusValue                  = 0U;
 *   config->positionInitialValue                  = 0U;
 *   config->prescalerValue                        = kQDC_ClockDiv1;
 *   config->enablePeriodMeasurementFunction       = true;
 * endcode
 * param config Pointer to a variable of configuration structure. See to "qdc_config_t".
 */
void QDC_GetDefaultConfig(qdc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableReverseDirection                = false;
    config->decoderWorkMode                       = kQDC_DecoderWorkAsNormalMode;
    config->HOMETriggerMode                       = kQDC_HOMETriggerDisabled;
    config->INDEXTriggerMode                      = kQDC_INDEXTriggerDisabled;
    config->enableTRIGGERClearPositionCounter     = false;
    config->enableTRIGGERClearHoldPositionCounter = false;
    config->enableWatchdog                        = false;
    config->watchdogTimeoutValue                  = 0U;
    config->filterCount                           = 0U;
    config->filterSamplePeriod                    = 0U;
    config->positionMatchMode                     = kQDC_POSMATCHOnPositionCounterEqualToComapreValue;
    config->positionCompareValue                  = 0xFFFFFFFFU;
    config->revolutionCountCondition              = kQDC_RevolutionCountOnINDEXPulse;
    config->enableModuloCountMode                 = false;
    config->positionModulusValue                  = 0U;
    config->positionInitialValue                  = 0U;
#if (defined(FSL_FEATURE_QDC_HAS_CTRL3) && FSL_FEATURE_QDC_HAS_CTRL3)
    config->prescalerValue                  = kQDC_ClockDiv1;
    config->enablePeriodMeasurementFunction = true;
#endif

#if (defined(FSL_FEATURE_QDC_HAS_FILT_PRSC) && FSL_FEATURE_QDC_HAS_FILT_PRSC)
    config->filterPrescaler = kQDC_FilterPrescalerDiv1;
#endif
}

/*!
 * brief Load the initial position value to position counter.
 *
 * This function is to transfer the initial position value (UINIT and LINIT) contents to position counter (UPOS and
 * LPOS), so that to provide the consistent operation the position counter registers.
 *
 * param base QDC peripheral base address.
 */
void QDC_DoSoftwareLoadInitialPositionValue(QDC_Type *base)
{
    uint16_t tmp16 = base->CTRL & (uint16_t)(~QDC_CTRL_W1C_FLAGS);

    tmp16 |= QDC_CTRL_SWIP_MASK; /* Write 1 to trigger the command for loading initial position value. */
    base->CTRL = tmp16;
}

/*!
 * brief Enable and configure the self test function.
 *
 * This function is to enable and configuration the self test function. It controls and sets the frequency of a
 * quadrature signal generator. It provides a quadrature test signal to the inputs of the quadrature decoder module.
 * It is a factory test feature; however, it may be useful to customers' software development and testing.
 *
 * param base   QDC peripheral base address.
 * param config Pointer to configuration structure. See to "qdc_self_test_config_t". Pass "NULL" to disable.
 */
void QDC_SetSelfTestConfig(QDC_Type *base, const qdc_self_test_config_t *config)
{
    uint16_t tmp16 = 0U;

    if (NULL == config) /* Pass "NULL" to disable the feature. */
    {
        tmp16 = 0U;
    }
    else
    {
        tmp16 = QDC_TST_TEN_MASK | QDC_TST_TCE_MASK | QDC_TST_TEST_PERIOD(config->signalPeriod) |
                QDC_TST_TEST_COUNT(config->signalCount);
        if (kQDC_SelfTestDirectionNegative == config->signalDirection)
        {
            tmp16 |= QDC_TST_QDN_MASK;
        }
    }

    base->TST = tmp16;
}

/*!
 * brief Enable watchdog for QDC module.
 *
 * param base QDC peripheral base address
 * param enable Enables or disables the watchdog
 */
void QDC_EnableWatchdog(QDC_Type *base, bool enable)
{
    uint16_t tmp16 = base->CTRL & (uint16_t)(~(QDC_CTRL_W1C_FLAGS | QDC_CTRL_WDE_MASK));

    if (enable)
    {
        tmp16 |= QDC_CTRL_WDE_MASK;
    }
    base->CTRL = tmp16;
}

/*!
 * brief  Get the status flags.
 *
 * param  base QDC peripheral base address.
 *
 * return      Mask value of status flags. For available mask, see to "_qdc_status_flags".
 */
uint32_t QDC_GetStatusFlags(QDC_Type *base)
{
    uint32_t ret32 = 0U;

    /* QDC_CTRL. */
    if (0U != (QDC_CTRL_HIRQ_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_HOMETransitionFlag;
    }
    if (0U != (QDC_CTRL_XIRQ_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_INDEXPulseFlag;
    }
    if (0U != (QDC_CTRL_DIRQ_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_WatchdogTimeoutFlag;
    }
    if (0U != (QDC_CTRL_CMPIRQ_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_PositionCompareFlag;
    }

    /* QDC_CTRL2. */
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    if (0U != (QDC_CTRL2_SABIRQ_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_SimultBothPhaseChangeFlag;
    }
#endif
    if (0U != (QDC_CTRL2_ROIRQ_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_PositionRollOverFlag;
    }
    if (0U != (QDC_CTRL2_RUIRQ_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_PositionRollUnderFlag;
    }
    if (0U != (QDC_CTRL2_DIR_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_LastCountDirectionFlag;
    }

    return ret32;
}

/*!
 * brief Clear the status flags.
 *
 * param base QDC peripheral base address.
 * param mask Mask value of status flags to be cleared. For available mask, see to "_qdc_status_flags".
 */
void QDC_ClearStatusFlags(QDC_Type *base, uint32_t mask)
{
    uint32_t tmp16 = 0U;

    /* QDC_CTRL. */
    if (0U != ((uint32_t)kQDC_HOMETransitionFlag & mask))
    {
        tmp16 |= QDC_CTRL_HIRQ_MASK;
    }
    if (0U != ((uint32_t)kQDC_INDEXPulseFlag & mask))
    {
        tmp16 |= QDC_CTRL_XIRQ_MASK;
    }
    if (0U != ((uint32_t)kQDC_WatchdogTimeoutFlag & mask))
    {
        tmp16 |= QDC_CTRL_DIRQ_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionCompareFlag & mask))
    {
        tmp16 |= QDC_CTRL_CMPIRQ_MASK;
    }
    if (0U != tmp16)
    {
        base->CTRL = (uint16_t)(((uint32_t)base->CTRL & (~QDC_CTRL_W1C_FLAGS)) | tmp16);
    }

    /* QDC_CTRL2. */
    tmp16 = 0U;
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    if (0U != ((uint32_t)kQDC_SimultBothPhaseChangeFlag & mask))
    {
        tmp16 |= QDC_CTRL2_SABIRQ_MASK;
    }
#endif
    if (0U != ((uint32_t)kQDC_PositionRollOverFlag & mask))
    {
        tmp16 |= QDC_CTRL2_ROIRQ_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionRollUnderFlag & mask))
    {
        tmp16 |= QDC_CTRL2_RUIRQ_MASK;
    }
    if (0U != tmp16)
    {
        base->CTRL2 = (uint16_t)(((uint32_t)base->CTRL2 & (~QDC_CTRL2_W1C_FLAGS)) | tmp16);
    }
}

/*!
 * brief Enable the interrupts.
 *
 * param base QDC peripheral base address.
 * param mask Mask value of interrupts to be enabled. For available mask, see to "_qdc_interrupt_enable".
 */
void QDC_EnableInterrupts(QDC_Type *base, uint32_t mask)
{
    uint32_t tmp16 = 0U;

    /* QDC_CTRL. */
    if (0U != ((uint32_t)kQDC_HOMETransitionInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_HIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_INDEXPulseInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_XIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_WatchdogTimeoutInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_DIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionCompareInerruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_CMPIE_MASK;
    }
    if (tmp16 != 0U)
    {
        base->CTRL = (uint16_t)(((uint32_t)base->CTRL & (~QDC_CTRL_W1C_FLAGS)) | tmp16);
    }
    /* QDC_CTRL2. */
    tmp16 = 0U;
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    if (0U != ((uint32_t)kQDC_SimultBothPhaseChangeInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_SABIE_MASK;
    }
#endif
    if (0U != ((uint32_t)kQDC_PositionRollOverInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_ROIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionRollUnderInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_RUIE_MASK;
    }
    if (tmp16 != 0U)
    {
        base->CTRL2 = (uint16_t)(((uint32_t)base->CTRL2 & (~QDC_CTRL2_W1C_FLAGS)) | tmp16);
    }
}

/*!
 * brief Disable the interrupts.
 *
 * param base QDC peripheral base address.
 * param mask Mask value of interrupts to be disabled. For available mask, see to "_qdc_interrupt_enable".
 */
void QDC_DisableInterrupts(QDC_Type *base, uint32_t mask)
{
    uint16_t tmp16 = 0U;

    /* QDC_CTRL. */
    if (0U != ((uint32_t)kQDC_HOMETransitionInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_HIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_INDEXPulseInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_XIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_WatchdogTimeoutInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_DIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionCompareInerruptEnable & mask))
    {
        tmp16 |= QDC_CTRL_CMPIE_MASK;
    }
    if (0U != tmp16)
    {
        base->CTRL = (uint16_t)(base->CTRL & (uint16_t)(~QDC_CTRL_W1C_FLAGS)) & (uint16_t)(~tmp16);
    }
    /* QDC_CTRL2. */
    tmp16 = 0U;
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    if (0U != ((uint32_t)kQDC_SimultBothPhaseChangeInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_SABIE_MASK;
    }
#endif
    if (0U != ((uint32_t)kQDC_PositionRollOverInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_ROIE_MASK;
    }
    if (0U != ((uint32_t)kQDC_PositionRollUnderInterruptEnable & mask))
    {
        tmp16 |= QDC_CTRL2_RUIE_MASK;
    }
    if (tmp16 != 0U)
    {
        base->CTRL2 = (uint16_t)(base->CTRL2 & (uint16_t)(~QDC_CTRL2_W1C_FLAGS)) & (uint16_t)(~tmp16);
    }
}

/*!
 * brief  Get the enabled interrupts' flags.
 *
 * param  base QDC peripheral base address.
 *
 * return      Mask value of enabled interrupts.
 */
uint32_t QDC_GetEnabledInterrupts(QDC_Type *base)
{
    uint32_t ret32 = 0U;

    /* QDC_CTRL. */
    if (0U != (QDC_CTRL_HIE_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_HOMETransitionInterruptEnable;
    }
    if (0U != (QDC_CTRL_XIE_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_INDEXPulseInterruptEnable;
    }
    if (0U != (QDC_CTRL_DIE_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_WatchdogTimeoutInterruptEnable;
    }
    if (0U != (QDC_CTRL_CMPIE_MASK & base->CTRL))
    {
        ret32 |= (uint32_t)kQDC_PositionCompareInerruptEnable;
    }
    /* QDC_CTRL2. */
#if !(defined(FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT) && FSL_FEATURE_QDC_HAS_NO_CTRL2_SAB_INT)
    if (0U != (QDC_CTRL2_SABIE_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_SimultBothPhaseChangeInterruptEnable;
    }
#endif
    if (0U != (QDC_CTRL2_ROIE_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_PositionRollOverInterruptEnable;
    }
    if (0U != (QDC_CTRL2_RUIE_MASK & base->CTRL2))
    {
        ret32 |= (uint32_t)kQDC_PositionRollUnderInterruptEnable;
    }
    return ret32;
}

/*!
 * brief Set initial position value for QDC module.
 *
 * param base QDC peripheral base address
 * param value Positive initial value
 */
void QDC_SetInitialPositionValue(QDC_Type *base, uint32_t value)
{
    base->UINIT = (uint16_t)(value >> 16U); /* Set upper 16 bits. */
    base->LINIT = (uint16_t)(value);        /* Set lower 16 bits. */
}

/*!
 * brief  Get the current position counter's value.
 *
 * param  base QDC peripheral base address.
 *
 * return     Current position counter's value.
 */
uint32_t QDC_GetPositionValue(QDC_Type *base)
{
    uint32_t ret32;

    ret32 = base->UPOS; /* Get upper 16 bits and make a snapshot. */
    ret32 <<= 16U;
    ret32 |= base->LPOSH; /* Get lower 16 bits from hold register. */

    return ret32;
}

/*!
 * brief  Get the hold position counter's value.
 *
 * When any of the counter registers is read, the contents of each counter register is written to the corresponding hold
 * register. Taking a snapshot of the counters' values provides a consistent view of a system position and a velocity to
 * be attained.
 *
 * param  base QDC peripheral base address.
 *
 * return      Hold position counter's value.
 */
uint32_t QDC_GetHoldPositionValue(QDC_Type *base)
{
    uint32_t ret32;

    ret32 = base->UPOSH; /* Get upper 16 bits and make a snapshot. */
    ret32 <<= 16U;
    ret32 |= base->LPOSH; /* Get lower 16 bits from hold register. */

    return ret32;
}
