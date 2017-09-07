/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "tempmon/tempmon.h"
#include "registers/regstempmon.h"
#include "registers/regsocotp.h"
#include "registers/regspmu.h"
#include "interrupt.h"
#include "irq_numbers.h"
#include "soc_memory_map.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////////////////

//! @name Temperature calibration OTP field masks
//!{
#define BM_ROOM_COUNT (0xfff00000)  //!< Room temperature sensor count bit mask.
#define BP_ROOM_COUNT (20)          //!< Room temperature sensor count bit position.
#define BM_HOT_COUNT (0x000fff00)   //!< Hot temperature sensor count bit mask.
#define BP_HOT_COUNT (8)            //!< Hot temperature sensor count bit position.
#define BM_HOT_TEMP (0x000000ff)    //!< Hot test temperature in degrees C bit mask.
#define BP_HOT_TEMP (0)             //!< Hot test temperature in degrees C bit position.
//@}

//! @brief Room temperature in degrees C.
#define ROOM_TEMP (25.0f)

//! @brief Default temperature calibration points.
#define DEFAULT_TEMP_CAL_DATA (0x57d4df7d)

//! @brief Temperature calibration OTP register info
enum _temp_cal_otp_reg {
    kTempCalibrationOtpBank = 1,    //!< Bank 1
    kTempCalibrationOtpRow = 6      //!< Row/word 6
};

//! @brief Temperature measurement period constants.
enum _temp_period {
    kMaxMeasurementPeriod_ms = 2000, //!< 2 seconds is the maximum time between measurements.
    kMaxMeasurementTicks = 0xffff,   //!< The max measurement period in 32.768 kHz clock ticks.
    kMeasurementTicksPerSecond = 32768, //!< The temperature measurement clock rate.
    kMillisecondsPerSecond = 1000   //!< Number of milliseconds per second.
};

/*!
 * @brief Global data for the tempmon driver.
 */
typedef struct _tempmon_info {
    float roomCount; //!< Room temperature sensor count value.
    float hotCount;  //!< Hot temperature sensor count value.
    float hotTemp;  //!< The hot test temperature in degrees C.
    tempmon_alarm_callback_t alarmCallback; //!< Callback to invoke when a new measurement is ready.
    bool isAlarmEnabled; //!< True if automatic measurements are in progress.
} tempmon_info_t;

//////////////////////////////////////////////////////////////////////////////////////////
// Prototypes
//////////////////////////////////////////////////////////////////////////////////////////

inline float compute_temp(float measuredCount);
inline int compute_alarm(float alarmTemp);

static void tempmon_alarm_isr(void);

//////////////////////////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief Global data for the tempmon driver.
static tempmon_info_t s_tempmon;

//////////////////////////////////////////////////////////////////////////////////////////
// Code
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief Calculate the temperature from a measurement result.
//! @param measuredCount The resulting count value of a temp sensor measurement cycle.
//! @return The temperature in degrees C.
inline float compute_temp(float measuredCount)
{
    float a = (s_tempmon.hotTemp - ROOM_TEMP);
    float b = (s_tempmon.roomCount - s_tempmon.hotCount);
    float c = a / b;
    float d = (measuredCount - s_tempmon.hotCount);
    float e = d * c;
    float f = s_tempmon.hotTemp - e;
    return f;
//     return hotTemp - (measuredCount - hotCount) * ((hotTemp - ROOM_TEMP) / (roomCount - hotCount));
}

//! @brief Calculate an alarm value given the alarm temperature.
//! @param alarmTemp The desired alarm temperature in degrees C.
//! @return Value to use for the alarm count value for @a alarmTemp.
inline int compute_alarm(float alarmTemp)
{
    float a = (alarmTemp - s_tempmon.hotTemp);
    float b = (s_tempmon.hotTemp - ROOM_TEMP);
    float c = (s_tempmon.roomCount - s_tempmon.hotCount);
    float d = (b / c);
    return s_tempmon.hotCount + a / d;
//     return s_tempmon.hotCount + (alarmTemp - s_tempmon.hotTemp) / ((s_tempmon.hotTemp - ROOM_TEMP) / (s_tempmon.roomCount - s_tempmon.hotCount));
}

//! @brief Interrupt handler for the over-temperature alarm.
//!
//! This interrupt handler gets the current die temperature and calls the alarm callback function
//! that was previously installed with tempmon_set_alarm(). If for some reason there is no alarm
//! callback set, this routine does nothing except clear the IRQ.
static void tempmon_alarm_isr(void)
{
    if (s_tempmon.alarmCallback)
    {
        // Pass the current die temp to the alarm callback.
        float currentTemp = tempmon_get_temp();
        s_tempmon.alarmCallback(currentTemp);
    }
    
    // Clear the alarm IRQ by writing a 1.
    BF_SET(PMU_MISC1, IRQ_TEMPSENSE);
}

int tempmon_init(void)
{
    // Read the calibration point data from OTP.
    uint32_t calibrationData = HW_OCOTP_ANA1_RD();
    
    // If the OTP fields are blank, use a default set of calibration points.
    if (calibrationData == 0)
    {
        calibrationData = DEFAULT_TEMP_CAL_DATA;
    }
    
    // Extract calibration points from the OTP data.
    s_tempmon.roomCount = (calibrationData & BM_ROOM_COUNT) >> BP_ROOM_COUNT;
    s_tempmon.hotCount = (calibrationData & BM_HOT_COUNT) >> BP_HOT_COUNT;
    s_tempmon.hotTemp = (calibrationData & BM_HOT_TEMP) >> BP_HOT_TEMP;
    
    // Fill in other global info fields.
    s_tempmon.alarmCallback = NULL;
    s_tempmon.isAlarmEnabled = false;
    
    return 0;
}

float tempmon_get_temp(void)
{
    // If automatic measurements are not enabled, wake up the temp sensor and take a measurement.
    if (!s_tempmon.isAlarmEnabled)
    {
        // Wake up the temp monitor.
        BF_CLR(TEMPMON_TEMPSENSE0, POWER_DOWN);
    
        // Clear the measure frequency so we only get single measurements.
        BF_CLR(TEMPMON_TEMPSENSE1, MEASURE_FREQ);
    
        // Start a measurement cycle.
        BF_SET(TEMPMON_TEMPSENSE0, MEASURE_TEMP);
    }
    
    // Wait until the measurement is ready.
    while (!HW_TEMPMON_TEMPSENSE0.B.FINISHED);
    
    // Read the measured temperature.
    int measuredCount = HW_TEMPMON_TEMPSENSE0.B.TEMP_CNT;
    
    // Power down the temp monitor, unless alarms are enabled.
    if (!s_tempmon.isAlarmEnabled)
    {
        BF_SET(TEMPMON_TEMPSENSE0, POWER_DOWN);
    }
    
    // Return the computed temperature.
    return compute_temp(measuredCount);
}

void tempmon_set_alarm(uint32_t period, float alarmTemp, tempmon_alarm_callback_t alarmCallback)
{
    // Save alarm info.
    s_tempmon.alarmCallback = alarmCallback;
    s_tempmon.isAlarmEnabled = true;
    
    // Wake up the temp monitor.
    BF_CLR(TEMPMON_TEMPSENSE0, POWER_DOWN);
    
    // Set the measurement frequency.
    int ticks;
    if (period >= kMaxMeasurementPeriod_ms)
    {
        ticks = kMaxMeasurementTicks;
    }
    else
    {
        // Convert milliseconds to 32.768 kHz clock ticks.
        ticks = period * kMeasurementTicksPerSecond / kMillisecondsPerSecond;
    }
    
    BF_WR(TEMPMON_TEMPSENSE1, MEASURE_FREQ, ticks);
    
    // Calculate and fill in the alarm value.
    int alarmValue = compute_alarm(alarmTemp);
    BF_WR(TEMPMON_TEMPSENSE0, ALARM_VALUE, alarmValue);
    
    // Clear the alarm IRQ by writing a 1.
    BF_SET(PMU_MISC1, IRQ_TEMPSENSE);
    
    // Enable the alarm interrupt.
    register_interrupt_routine(IMX_INT_TEMPERATURE, tempmon_alarm_isr);
    enable_interrupt(IMX_INT_TEMPERATURE, CPU_0, 1);
    
    // Start automatic measurements.
    BF_SET(TEMPMON_TEMPSENSE0, MEASURE_TEMP);
}

void tempmon_disable_alarm(void)
{
    // Turn off the alarm interrupt.
    disable_interrupt(IMX_INT_TEMPERATURE, CPU_0);
    
    // Stop automatic measurements.
    BF_CLR(TEMPMON_TEMPSENSE0, MEASURE_TEMP);
    BF_CLR(TEMPMON_TEMPSENSE1, MEASURE_FREQ);
    
    // Power down the temp monitor.
    BF_SET(TEMPMON_TEMPSENSE0, POWER_DOWN);

    // Clear auto measurement info.
    s_tempmon.alarmCallback = NULL;
    s_tempmon.isAlarmEnabled = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////////////////
