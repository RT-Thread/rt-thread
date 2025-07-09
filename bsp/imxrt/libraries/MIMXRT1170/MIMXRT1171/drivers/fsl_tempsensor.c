/*
 * Copyright 2020-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_tempsensor.h"
#include "math.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tempsensor"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
static void TMPSNS_AIWriteAccess(uint32_t address, uint32_t data);
static uint32_t TMPSNS_AIReadAccess(uint32_t address);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
const static float s_Ts20   = 133.6f;
const static float s_Ts21   = -5.39f;
const static float s_Ts21_2 = 29.0521f; /*!< It means (s_Ts21* s_Ts21) */
const static float s_Ts22   = 0.002f;
static float s_Ts25c;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Initializes the TMPSNS module.
 *
 * param base TMPSNS base pointer
 * param config Pointer to configuration structure.
 */
void TMPSNS_Init(TMPSNS_Type *base, const tmpsns_config_t *config)
{
    assert(NULL != config);

    uint32_t controlVal = 0x00U;
    uint32_t temp;

    temp =
        (ANADIG_TEMPSENSOR_TEMPSNS_OTP_TRIM_VALUE_TEMPSNS_TEMP_VAL_MASK & ANADIG_TEMPSENSOR->TEMPSNS_OTP_TRIM_VALUE) >>
        10;
    s_Ts25c = (float)temp;

    /* Reset Tempsensor first. */
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    controlVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
#else
    controlVal  = base->CTRL1;
#endif /* defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE */

    controlVal |= (TMPSNS_CTRL1_PWD_MASK | TMPSNS_CTRL1_PWD_FULL_MASK);
    controlVal &= (~(TMPSNS_CTRL1_START_MASK | TMPSNS_CTRL1_FINISH_IE_MASK | TMPSNS_CTRL1_LOW_TEMP_IE_MASK |
                     TMPSNS_CTRL1_HIGH_TEMP_IE_MASK | TMPSNS_CTRL1_PANIC_TEMP_IE_MASK | TMPSNS_CTRL1_FREQ_MASK));

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), controlVal);
#else
    base->CTRL1 = controlVal;
#endif /* defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE */

    /* Set alarm temperature */
    TMPSNS_SetTempAlarm(base, config->highAlarmTemp, kTEMPMON_HighAlarmMode);
    TMPSNS_SetTempAlarm(base, config->panicAlarmTemp, kTEMPMON_PanicAlarmMode);
    TMPSNS_SetTempAlarm(base, config->lowAlarmTemp, kTEMPMON_LowAlarmMode);

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    controlVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
#else
    controlVal  = base->CTRL1;
#endif /* defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE */

    /* Enable finish interrupt status */
    controlVal |= TMPSNS_CTRL1_FINISH_IE_MASK;

    if (config->measureMode == kTEMPSENSOR_SingleMode)
    {
        controlVal |= TMPSNS_CTRL1_FREQ(0x00U);
    }
    else if (config->measureMode == kTEMPSENSOR_ContinuousMode)
    {
        controlVal |= TMPSNS_CTRL1_FREQ(config->frequency);
    }
    else
    {
        ; /* Intentional empty for MISRA C-2012 rule 15.7*/
    }

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t statusVal;

    /* Power up the temperature sensor */
    controlVal &= (~(TMPSNS_CTRL1_PWD_MASK | TMPSNS_CTRL1_PWD_FULL_MASK));

    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), controlVal);

    /* Read STATUS0 value */
    statusVal = TMPSNS_AIReadAccess((uint32_t) & (base->STATUS0));

    /* Clear interrupt status flags. */
    TMPSNS_AIWriteAccess((uint32_t) & (base->STATUS0),
                         (statusVal | TMPSNS_STATUS0_HIGH_TEMP_MASK | TMPSNS_STATUS0_LOW_TEMP_MASK |
                          TMPSNS_STATUS0_PANIC_TEMP_MASK | TMPSNS_STATUS0_FINISH_MASK));
#else
    base->CTRL1 = controlVal;

    /* Power up the temperature sensor */
    base->CTRL1 &= (~(TMPSNS_CTRL1_PWD_MASK | TMPSNS_CTRL1_PWD_FULL_MASK));

    /* Clear interrupt status flags. */
    base->STATUS0 = (TMPSNS_STATUS0_HIGH_TEMP_MASK | TMPSNS_STATUS0_LOW_TEMP_MASK | TMPSNS_STATUS0_PANIC_TEMP_MASK |
                     TMPSNS_STATUS0_FINISH_MASK);
#endif /* defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE */
}

/*!
 * brief Deinitializes the TMPSNS module.
 *
 * param base TMPSNS base pointer
 */
void TMPSNS_Deinit(TMPSNS_Type *base)
{
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), TMPSNS_CTRL1_PWD_MASK);
#else
    base->CTRL1 |= TMPSNS_CTRL1_PWD_MASK;
#endif
}

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
/*!
 * brief AI interface write access.
 *
 * param base TMPSNS base pointer
 */
static void TMPSNS_AIWriteAccess(uint32_t address, uint32_t data)
{
    /* AI bridge setting: AIRWB and ADDR
       Write: 0x00
       Address: offset from base address
     */
    ANADIG_MISC->VDDLPSR_AI_CTRL = (0x00UL << 16) | (address & 0xFFFFU);
    /* Write data into related register through AI bridge */
    ANADIG_MISC->VDDLPSR_AI_WDATA = data;
    /* AI toggle */
    ANADIG_TEMPSENSOR->TEMPSENSOR ^= ANADIG_TEMPSENSOR_TEMPSENSOR_TEMPSNS_AI_TOGGLE_MASK;
}

/*!
 * brief AI interface read access.
 *
 * param base TMPSNS base pointer
 */
static uint32_t TMPSNS_AIReadAccess(uint32_t address)
{
    uint32_t ret;

    /* AI bridge setting: AIRWB and ADDR
       Read: 0x01
       Address: offset from base address
     */
    ANADIG_MISC->VDDLPSR_AI_CTRL = (0x01UL << 16) | (address & 0xFFFFU);
    /* AI toggle */
    ANADIG_TEMPSENSOR->TEMPSENSOR ^= ANADIG_TEMPSENSOR_TEMPSENSOR_TEMPSNS_AI_TOGGLE_MASK;
    /* Read data from related register through AI bridge */
    ret = ANADIG_MISC->VDDLPSR_AI_RDATA_TMPSNS;

    return ret;
}
#endif /* FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE */

/*!
 * brief Gets the default configuration structure.
 *
 * This function initializes the TMPSNS configuration structure to a default value. The default
 * values are:
 *   tempmonConfig->frequency = 0x00U;
 *   tempmonConfig->highAlarmTemp = 25U;
 *   tempmonConfig->panicAlarmTemp = 80U;
 *   tempmonConfig->lowAlarmTemp = 20U;
 *
 * param config Pointer to a configuration structure.
 */
void TMPSNS_GetDefaultConfig(tmpsns_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Default measurement mode */
    config->measureMode = kTEMPSENSOR_SingleMode;
    /* Default measure frequency */
    config->frequency = 0x00U;
    /* Default high alarm temperature */
    config->highAlarmTemp = 25;
    /* Default panic alarm temperature */
    config->panicAlarmTemp = 80;
    /* Default low alarm temperature */
    config->lowAlarmTemp = 5;
}

/*!
 * @brief start the temperature measurement process.
 *
 * @param base TMPSNS base pointer.
 */
void TMPSNS_StartMeasure(TMPSNS_Type *base)
{
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t controlVal;
    /* Read CTRL1 value*/
    controlVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
    /* Start measurement */
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), controlVal | TMPSNS_CTRL1_SET_START_MASK);
#else
    base->CTRL1 |= TMPSNS_CTRL1_SET_START_MASK;
#endif
}

/*!
 * @brief stop the measurement process.
 *
 * @param base TMPSNS base pointer
 */
void TMPSNS_StopMeasure(TMPSNS_Type *base)
{
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t controlVal;
    /* Read CTRL1 value*/
    controlVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
    /* Start measurement */
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), controlVal & (~TMPSNS_CTRL1_SET_START_MASK));
#else
    base->CTRL1 &= ~TMPSNS_CTRL1_SET_START_MASK;
#endif
}

/*!
 * brief Get current temperature with the fused temperature calibration data.
 *
 * param base TMPSNS base pointer
 * return current temperature with degrees Celsius.
 */
float TMPSNS_GetCurrentTemperature(TMPSNS_Type *base)
{
    uint32_t measureTempVal;
    float actualTempVal;

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    /* Waiting for measurement finished */
    while (0U == (TMPSNS_AIReadAccess((uint32_t) & (base->STATUS0)) & TMPSNS_STATUS0_FINISH_MASK))
    {
    }
    /* Ready to read measured temperature value */
    measureTempVal = (TMPSNS_AIReadAccess((uint32_t) & (base->STATUS0)) & TMPSNS_STATUS0_TEMP_VAL_MASK) >>
                     TMPSNS_STATUS0_TEMP_VAL_SHIFT;
#else
    /* Waiting for measurement finished */
    while (0U == (base->STATUS0 & TMPSNS_STATUS0_FINISH_MASK))
    {
    }
    /* Ready to read measured temperature value */
    measureTempVal = (base->STATUS0 & TMPSNS_STATUS0_TEMP_VAL_MASK) >> TMPSNS_STATUS0_TEMP_VAL_SHIFT;
#endif

    /* Calculate actual temperature */
    actualTempVal =
        (-s_Ts21 - sqrtf(s_Ts21_2 - 4.0f * s_Ts22 * (s_Ts20 + s_Ts25c - (float)measureTempVal))) / (2.0f * s_Ts22);

#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t statusVal;
    /* Read STATUS0 value */
    statusVal = TMPSNS_AIReadAccess((uint32_t) & (base->STATUS0));
    /* Clear the FINISH flag */
    TMPSNS_AIWriteAccess((uint32_t) & (base->STATUS0), statusVal | TMPSNS_STATUS0_FINISH_MASK);
#else
    /* Clear the FINISH flag */
    base->STATUS0 |= TMPSNS_STATUS0_FINISH_MASK;
#endif

    return actualTempVal;
}

/*!
 * brief Set the temperature count (raw sensor output) that will generate an alarm interrupt.
 *
 * param base TMPSNS base pointer
 * param tempVal The alarm temperature with degrees Celsius
 * param alarmMode The alarm mode.
 */
void TMPSNS_SetTempAlarm(TMPSNS_Type *base, int32_t tempVal, tmpsns_alarm_mode_t alarmMode)
{
    float temp;
    int32_t tempCodeVal;
    uint32_t tempRegVal;

    /* Calculate alarm temperature code value */;
    temp        = (-2.0f * s_Ts22 * (float)tempVal - s_Ts21) * (-2.0f * s_Ts22 * (float)tempVal - s_Ts21);
    temp        = (temp - (s_Ts21_2 - 4.0f * s_Ts22 * (s_Ts20 + s_Ts25c))) / (4.0f * s_Ts22);
    tempCodeVal = (int32_t)temp;

    switch (alarmMode)
    {
        case kTEMPMON_HighAlarmMode:
            /* Clear alarm value and set a new high alarm temperature code value */
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
            tempRegVal = TMPSNS_AIReadAccess((uint32_t) & (base->RANGE0));
            tempRegVal = (tempRegVal & ~TMPSNS_RANGE0_HIGH_TEMP_VAL_MASK) | TMPSNS_RANGE0_HIGH_TEMP_VAL(tempCodeVal);
            TMPSNS_AIWriteAccess((uint32_t) & (base->RANGE0), tempRegVal);
#else
            tempRegVal = (base->RANGE0 & ~TMPSNS_RANGE0_HIGH_TEMP_VAL_MASK) | TMPSNS_RANGE0_HIGH_TEMP_VAL(tempCodeVal);
            base->RANGE0 = tempRegVal;
#endif
            /* Enable high temperature interrupt */
            TMPSNS_EnableInterrupt(base, kTEMPSENSOR_HighTempInterruptStatusEnable);
            break;

        case kTEMPMON_PanicAlarmMode:
            /* Clear panic alarm value and set a new panic alarm temperature code value */
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
            tempRegVal = TMPSNS_AIReadAccess((uint32_t) & (base->RANGE1));
            tempRegVal = (tempRegVal & ~TMPSNS_RANGE1_PANIC_TEMP_VAL_MASK) | TMPSNS_RANGE1_PANIC_TEMP_VAL(tempCodeVal);
            TMPSNS_AIWriteAccess((uint32_t) & (base->RANGE1), tempRegVal);
#else
            tempRegVal =
                (base->RANGE1 & ~TMPSNS_RANGE1_PANIC_TEMP_VAL_MASK) | TMPSNS_RANGE1_PANIC_TEMP_VAL(tempCodeVal);
            base->RANGE1 = tempRegVal;
#endif
            /* Enable panic temperature interrupt */
            TMPSNS_EnableInterrupt(base, kTEMPSENSOR_PanicTempInterruptStatusEnable);
            break;

        case kTEMPMON_LowAlarmMode:
            /* Clear low alarm value and set a new low alarm temperature code value */
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
            tempRegVal = TMPSNS_AIReadAccess((uint32_t) & (base->RANGE0));
            tempRegVal = (tempRegVal & ~TMPSNS_RANGE0_LOW_TEMP_VAL_MASK) | TMPSNS_RANGE0_LOW_TEMP_VAL(tempCodeVal);
            TMPSNS_AIWriteAccess((uint32_t) & (base->RANGE0_SET), tempRegVal);
#else
            tempRegVal   = (base->RANGE0 & ~TMPSNS_RANGE0_LOW_TEMP_VAL_MASK) | TMPSNS_RANGE0_LOW_TEMP_VAL(tempCodeVal);
            base->RANGE0 = tempRegVal;
#endif
            /* Enable low temperature interrupt */
            TMPSNS_EnableInterrupt(base, kTEMPSENSOR_LowTempInterruptStatusEnable);
            break;

        default:
            assert(false);
            break;
    }
}

/*!
 * brief Enable interrupt status.
 *
 * param base TMPSNS base pointer
 * param mask The interrupts to enable from tmpsns_interrupt_status_enable_t.
 */
void TMPSNS_EnableInterrupt(TMPSNS_Type *base, uint32_t mask)
{
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t tempRegVal;
    tempRegVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), tempRegVal | mask);
#else
    base->CTRL1 |= mask;
#endif
}

/*!
 * brief Disable interrupt status.
 *
 * param base TMPSNS base pointer
 * param mask The interrupts to disable from tmpsns_interrupt_status_enable_t.
 */
void TMPSNS_DisableInterrupt(TMPSNS_Type *base, uint32_t mask)
{
#if defined(FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE) && FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE
    uint32_t tempRegVal;
    tempRegVal = TMPSNS_AIReadAccess((uint32_t) & (base->CTRL1));
    TMPSNS_AIWriteAccess((uint32_t) & (base->CTRL1), tempRegVal & (~mask));
#else
    base->CTRL1 &= ~mask;
#endif
}
