/*
 * Copyright  2018-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_tempmon.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tempmon"
#endif

/*! @brief TEMPMON calibration data mask. */
#define TEMPMON_HOTTEMPMASK    0xFFU
#define TEMPMON_HOTTEMPSHIFT   0x00U
#define TEMPMON_HOTCOUNTMASK   0xFFF00U
#define TEMPMON_HOTCOUNTSHIFT  0X08U
#define TEMPMON_ROOMCOUNTMASK  0xFFF00000U
#define TEMPMON_ROOMCOUNTSHIFT 0x14U

/*! @brief the room temperature. */
#define TEMPMON_ROOMTEMP 25.0f

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static int32_t s_hotTemp;    /*!< The value of TEMPMON_TEMPSENSE0[TEMP_VALUE] at room temperature .*/
static int32_t s_hotCount;   /*!< The value of TEMPMON_TEMPSENSE0[TEMP_VALUE] at the hot temperature.*/
static float s_hotT_ROOM;    /*!< The value of s_hotTemp minus room temperature(25 degrees celsius).*/
static int32_t s_roomC_hotC; /*!< The value of s_roomCount minus s_hotCount.*/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Initializes the TEMPMON module.
 *
 * param base TEMPMON base pointer
 * param config Pointer to configuration structure.
 */
void TEMPMON_Init(TEMPMON_Type *base, const tempmon_config_t *config)
{
    assert(NULL != config);

    uint32_t calibrationData;
    uint32_t tmpU32;
    int32_t roomCount;

    /* Power on the temperature sensor*/
    base->TEMPSENSE0 &= ~TEMPMON_TEMPSENSE0_POWER_DOWN_MASK;

    /* Set temperature monitor frequency */
    base->TEMPSENSE1 = TEMPMON_TEMPSENSE1_MEASURE_FREQ(config->frequency);

    /* ready to read calibration data */
    calibrationData = OCOTP->ANA1;
    tmpU32          = (calibrationData & TEMPMON_HOTTEMPMASK) >> TEMPMON_HOTTEMPSHIFT;
    s_hotTemp       = (int32_t)tmpU32;

    tmpU32     = (calibrationData & TEMPMON_HOTCOUNTMASK) >> TEMPMON_HOTCOUNTSHIFT;
    s_hotCount = (int32_t)tmpU32;

    tmpU32    = (calibrationData & TEMPMON_ROOMCOUNTMASK) >> TEMPMON_ROOMCOUNTSHIFT;
    roomCount = (int32_t)tmpU32;

    s_hotT_ROOM  = (float)s_hotTemp - TEMPMON_ROOMTEMP;
    s_roomC_hotC = roomCount - s_hotCount;

    /* Set alarm temperature */
    TEMPMON_SetTempAlarm(base, config->highAlarmTemp, kTEMPMON_HighAlarmMode);
    TEMPMON_SetTempAlarm(base, config->panicAlarmTemp, kTEMPMON_PanicAlarmMode);
    TEMPMON_SetTempAlarm(base, config->lowAlarmTemp, kTEMPMON_LowAlarmMode);
}

/*!
 * brief Deinitializes the TEMPMON module.
 *
 * param base TEMPMON base pointer
 */
void TEMPMON_Deinit(TEMPMON_Type *base)
{
    base->TEMPSENSE0 |= TEMPMON_TEMPSENSE0_POWER_DOWN_MASK;
}

/*!
 * brief Gets the default configuration structure.
 *
 * This function initializes the TEMPMON configuration structure to a default value. The default
 * values are:
 *   tempmonConfig->frequency = 0x02U;
 *   tempmonConfig->highAlarmTemp = 44U;
 *   tempmonConfig->panicAlarmTemp = 90U;
 *   tempmonConfig->lowAlarmTemp = 39U;
 *
 * param config Pointer to a configuration structure.
 */
void TEMPMON_GetDefaultConfig(tempmon_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Default measure frequency */
    config->frequency = 0x03U;
    /* Default high alarm temperature */
    config->highAlarmTemp = 40;
    /* Default panic alarm temperature */
    config->panicAlarmTemp = 90;
    /* Default low alarm temperature */
    config->lowAlarmTemp = 20;
}

/*!
 * brief Get current temperature with the fused temperature calibration data.
 *
 * param base TEMPMON base pointer
 * return current temperature with degrees Celsius.
 */
float TEMPMON_GetCurrentTemperature(TEMPMON_Type *base)
{
    /* Check arguments */
    assert(NULL != base);

    uint32_t nmeas;
    float tmeas;

    while (0U == (base->TEMPSENSE0 & TEMPMON_TEMPSENSE0_FINISHED_MASK))
    {
    }

    /* ready to read temperature code value */
    nmeas = (base->TEMPSENSE0 & TEMPMON_TEMPSENSE0_TEMP_CNT_MASK) >> TEMPMON_TEMPSENSE0_TEMP_CNT_SHIFT;

    /* Calculate temperature */
    tmeas = (float)s_hotTemp - (((float)nmeas - (float)s_hotCount) * (s_hotT_ROOM / (float)s_roomC_hotC));

    return tmeas;
}

/*!
 * brief Set the temperature count (raw sensor output) that will generate an alarm interrupt.
 *
 * param base TEMPMON base pointer
 * param tempVal The alarm temperature with degrees Celsius
 * param alarmMode The alarm mode.
 */
void TEMPMON_SetTempAlarm(TEMPMON_Type *base, int8_t tempVal, tempmon_alarm_mode alarmMode)
{
    /* Check arguments */
    assert(NULL != base);
    /* Different SOC has different qualified temperature level based on AEC-Q100 standard by default, such as Consumer(0
       to +95 degrees celsius)/Industrial(-40 to +105 degrees celsius)/Automotive(-40 to +125 degrees celsius). */
    assert(s_hotTemp >= tempVal);

    int32_t tempCodeVal;
    uint32_t tempRegVal;

    /* Calculate alarm temperature code value */
    tempCodeVal = s_hotCount + (s_hotTemp - (int32_t)tempVal) * s_roomC_hotC / (int32_t)s_hotT_ROOM;

    switch (alarmMode)
    {
        case kTEMPMON_HighAlarmMode:
            /* Clear alarm value and set a new high alarm temperature code value */
            tempRegVal = base->TEMPSENSE0;
            tempRegVal =
                (tempRegVal & ~TEMPMON_TEMPSENSE0_ALARM_VALUE_MASK) | TEMPMON_TEMPSENSE0_ALARM_VALUE(tempCodeVal);
            base->TEMPSENSE0 = tempRegVal;
            break;

        case kTEMPMON_PanicAlarmMode:
            /* Clear panic alarm value and set a new panic alarm temperature code value */
            tempRegVal = base->TEMPSENSE2;
            tempRegVal = (tempRegVal & ~TEMPMON_TEMPSENSE2_PANIC_ALARM_VALUE_MASK) |
                         TEMPMON_TEMPSENSE2_PANIC_ALARM_VALUE(tempCodeVal);
            base->TEMPSENSE2 = tempRegVal;
            break;

        case kTEMPMON_LowAlarmMode:
            /* Clear low alarm value and set a new low alarm temperature code value */
            tempRegVal = base->TEMPSENSE2;
            tempRegVal = (tempRegVal & ~TEMPMON_TEMPSENSE2_LOW_ALARM_VALUE_MASK) |
                         TEMPMON_TEMPSENSE2_LOW_ALARM_VALUE(tempCodeVal);
            base->TEMPSENSE2 = tempRegVal;
            break;

        default:
            assert(false);
            break;
    }
}
