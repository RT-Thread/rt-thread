/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_RTC_HAL_H__)
#define __FSL_RTC_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*!
 * @addtogroup rtc_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Error codes for RTC driver. */
typedef enum _rtc_status
{
    kStatusRtcSuccess = 0x00U,        /*!< RTC success status.*/
    kStatusRtcFail    = 0x01U         /*!< RTC error status.*/
} rtc_status_t;

/*!
 * @brief Structure is used to hold the time in a simple "date" format.
 */
typedef struct RtcDatetime
{
   uint16_t year;    /*!< Range from 1970 to 2099.*/
   uint16_t month;   /*!< Range from 1 to 12.*/
   uint16_t day;     /*!< Range from 1 to 31 (depending on month).*/
   uint16_t hour;    /*!< Range from 0 to 23.*/
   uint16_t minute;  /*!< Range from 0 to 59.*/
   uint8_t second;   /*!< Range from 0 to 59.*/
} rtc_datetime_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name RTC HAL API Functions
 * @{
 */

/*!
 * @brief  Clears all interrupts.
 *
 * This function initiates a soft-reset of the RTC module if the time invalid flag is set.
 *
 * @param  base The RTC base address pointer.
 */
void RTC_HAL_Init(RTC_Type *base);

/*!
 * @brief  Converts seconds to date time format data structure.
 *
 * @param  seconds holds the date and time information in seconds
 * @param  datetime holds the converted information from seconds in date and time format
 */
void RTC_HAL_ConvertSecsToDatetime(const uint32_t * seconds, rtc_datetime_t * datetime);

/*!
 * @brief  Checks whether the date time structure elements have the information that is within the range.
 *
 * @param  datetime holds the date and time information that needs to be converted to seconds
 *
 * @return returns true if the datetime argument has the right format, false otherwise
 */
bool RTC_HAL_IsDatetimeCorrectFormat(const rtc_datetime_t * datetime);

/*!
 * @brief  Converts the date time format data structure to seconds.
 *
 * @param  datetime holds the date and time information that needs to be converted to seconds
 * @param  seconds holds the converted date and time in seconds
 */
void RTC_HAL_ConvertDatetimeToSecs(const rtc_datetime_t * datetime, uint32_t * seconds);

/*!
 * @brief  Sets the RTC date and time according to a given time structure.
 *
 * The function converts the data from the time structure to seconds and writes the seconds
 * value to the RTC register. The RTC counter is started after setting the time.
 *
 * @param  base The RTC base address pointer
 * @param  datetime [in] Pointer to structure where the date and time
 *         details to set are stored.
 */
void RTC_HAL_SetDatetime(RTC_Type *base, const rtc_datetime_t * datetime);

/*!
 * @brief  Sets the RTC date and time according to the given time provided in seconds.
 *
 * The RTC counter is started after setting the time.
 *
 * @param  base The RTC base address pointer
 * @param  seconds [in] Time in seconds
 */
void RTC_HAL_SetDatetimeInsecs(RTC_Type *base, const uint32_t seconds);

/*!
 * @brief  Gets the RTC time and stores it in the given time structure.
 *
 * The function reads the value in seconds from the RTC register. It then converts to the
 * time structure which provides the time in date, hour, minutes, and seconds.
 *
 * @param  base The RTC base address pointer
 * @param  datetime [out] pointer to a structure where the date and time details are
 *         stored.
 */
void RTC_HAL_GetDatetime(RTC_Type *base, rtc_datetime_t * datetime);

/*!
 * @brief  Gets the RTC time and returns it in seconds.
 *
 * @param  base The RTC base address pointer
 * @param  seconds [out] pointer to variable where the RTC time is stored in seconds
 */
void RTC_HAL_GetDatetimeInSecs(RTC_Type *base, uint32_t * seconds);

/*!
 * @brief  Reads the value of the time alarm.
 *
 * @param  base The RTC base address pointer
 * @param  date [out] pointer to a variable where the alarm date and time
 *         details are stored.
 */
void RTC_HAL_GetAlarm(RTC_Type *base, rtc_datetime_t * date);

/*!
 * @brief  Sets the RTC alarm time and enables the alarm interrupt.
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * @param  base The RTC base address pointer.
 * @param  date [in] pointer to structure where the alarm date and time
 *         details will be stored at.
 * @return  true: success in setting the RTC alarm
 *          false: error in setting the RTC alarm.
 */
bool RTC_HAL_SetAlarm(RTC_Type *base, const rtc_datetime_t * date);

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*-------------------------------------------------------------------------------------------*/
/* RTC Monotonic Counter*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the values of the Monotonic Counter High and Monotonic Counter Low and returns
 *         them as a single value.
 *
 * @param  base The RTC base address pointer
 * @param  counter [out] pointer to variable where the value is  stored.
 */
void RTC_HAL_GetMonotonicCounter(RTC_Type *base, uint64_t * counter);

/*!
 * @brief  Writes values Monotonic Counter High and Monotonic Counter Low by decomposing
 *         the given single value.
 *
 * @param  base The RTC base address pointer
 * @param  counter [in] pointer to variable where the value is stored.
 */
void RTC_HAL_SetMonotonicCounter(RTC_Type *base, const uint64_t * counter);

/*!
 * @brief  Increments the Monotonic Counter by one.
 *
 * Increments the Monotonic Counter (registers RTC_MCLR and RTC_MCHR accordingly) by setting
 * the monotonic counter enable (MER[MCE]) and then writing to the RTC_MCLR register. A write to the
 * monotonic counter low that causes it to overflow also increments the monotonic counter high.
 *
 * @param  base The RTC base address pointer
 *
 * @return  true: success
 *          false: error occurred, either time invalid or monotonic overflow flag was found
 */
bool RTC_HAL_IncrementMonotonicCounter(RTC_Type *base);
#endif
/*! @}*/

/*!
 * @name RTC register access functions
 * @{
 */

/*!
 * @brief  Reads the value of the time seconds counter.
 *
 * The time counter reads as zero if either the SR[TOF] or the SR[TIF] is set.
 *
 * @param  base The RTC base address pointer.
 *
 * @return contents of the seconds register.
 */
static inline uint32_t RTC_HAL_GetSecsReg(RTC_Type *base)
{
    return RTC_RD_TSR(base);
}

/*!
 * @brief  Writes to the time seconds counter.
 *
 * When the time counter is enabled, the TSR is read only and increments
 * once every second provided the SR[TOF] or SR[TIF] is not set. When the time counter
 * is disabled, the TSR can be read or written. Writing to the TSR when the
 * time counter is disabled clears the SR[TOF] and/or the SR[TIF]. Writing
 * to the TSR register with zero is supported, but not recommended, since the TSR
 * reads as zero when either the SR[TIF] or the SR[TOF] is set (indicating the time is
 * invalid).
 *
 * @param  base The RTC base address pointer.
 * @param  seconds [in] seconds value.
 *
 */
static inline void RTC_HAL_SetSecsReg(RTC_Type *base, const uint32_t seconds)
{
    RTC_WR_TPR_TPR(base, (uint32_t)0x00000000U);
    RTC_WR_TSR(base, seconds);
}

/*!
 * @brief  Sets the time alarm and clears the time alarm flag.
 *
 * When the time counter is enabled, the SR[TAF] is set whenever the TAR[TAR]
 * equals the TSR[TSR] and the TSR[TSR] increments. Writing to the TAR
 * clears the SR[TAF].
 *
 * @param  base The RTC base address pointer.
 * @param  seconds [in] alarm value in seconds.
 */
static inline void RTC_HAL_SetAlarmReg(RTC_Type *base, const uint32_t seconds)
{
    RTC_WR_TAR(base, seconds);
}

/*!
 * @brief  Gets the time alarm register contents.
 *
 * @param  base The RTC base address pointer
 *
 * @return  contents of the alarm register.
 */
static inline uint32_t RTC_HAL_GetAlarmReg(RTC_Type *base)
{
    return RTC_RD_TAR(base);
}


/*!
 * @brief  Reads the value of the time prescaler.
 *
 * The time counter reads as zero when either the SR[TOF] or the SR[TIF] is set.
 *
 * @param  base The RTC base address pointer
 *
 * @return  contents of the time prescaler register.
 */
static inline uint16_t RTC_HAL_GetPrescaler(RTC_Type *base)
{
    return RTC_RD_TPR_TPR(base);
}

/*!
 * @brief  Sets the time prescaler.
 *
 * When the time counter is enabled, the TPR is read only and increments
 * every 32.768 kHz clock cycle. When the time counter is disabled, the TPR
 * can be read or written. The TSR[TSR] increments when bit 14 of the TPR
 * transitions from a logic one to a logic zero.
 *
 * @param  base The RTC base address pointer
 * @param  prescale Prescaler value
 */
static inline void RTC_HAL_SetPrescaler(RTC_Type *base, const uint16_t prescale)
{
    RTC_WR_TPR_TPR(base, prescale);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Time Compensation*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the time compensation register contents.
 *
 * @param  base The RTC base address pointer
 *
 * @return time compensation register contents.
 */
static inline uint32_t RTC_HAL_GetCompensationReg(RTC_Type *base)
{
    return RTC_RD_TCR(base);
}

/*!
 * @brief  Writes the value to the RTC TCR register.
 *
 * @param  base The RTC base address pointer
 * @param  compValue value to be written to the compensation register.
 */
static inline void RTC_HAL_SetCompensationReg(RTC_Type *base, const uint32_t compValue)
{
    RTC_WR_TCR(base, compValue);
}

/*!
 * @brief  Reads the current value of the compensation interval counter, which is the field CIC in the RTC TCR register.
 *
 * @param  base The RTC base address pointer.
 *
 * @return  compensation interval value.
 */
static inline uint8_t RTC_HAL_GetCompensationIntervalCounter(RTC_Type *base)
{
    return RTC_RD_TCR_CIC(base);
}

/*!
 * @brief  Reads the current value used by the compensation logic for the present second interval.
 *
 * @param  base The RTC base address pointer
 *
 * @return  time compensation value
 */
static inline uint8_t RTC_HAL_GetTimeCompensationValue(RTC_Type *base)
{
    return RTC_RD_TCR_TCV(base);
}

/*!
 * @brief  Reads the compensation interval register.

 * The value is the configured compensation interval in seconds from 1 to 256 to control
 * how frequently the time compensation register  should adjust the
 * number of 32.768 kHz cycles in each second. The value is one
 * less than the number of seconds (for example, zero means a
 * configuration for a compensation interval of one second).
 *
 * @param  base The RTC base address pointer.
 *
 * @return compensation interval in seconds.
 */
static inline uint8_t RTC_HAL_GetCompensationIntervalRegister(RTC_Type *base)
{
    return RTC_RD_TCR_CIR(base);
}

/*!
 * @brief  Writes the compensation interval.
 *
 * This configures the compensation interval in seconds from 1 to 256 to control
 * how frequently the TCR should adjust the number of 32.768 kHz
 * cycles in each second. The value written should be one less than
 * the number of seconds (for example, write zero to configure for
 * a compensation interval of one second). This register is double
 * buffered and writes do not take affect until the end of the
 * current compensation interval.
 *
 * @param  base The RTC base address pointer.
 * @param  value the compensation interval value.
 */
static inline void RTC_HAL_SetCompensationIntervalRegister(RTC_Type *base, const uint8_t value)
{
    RTC_WR_TCR_CIR(base, value);
}

/*!
 * @brief  Reads the time compensation value which is the configured number
 *         of 32.768 kHz clock cycles in each second.
 *
 * @param  base The RTC base address pointer
 *
 * @return  time compensation value.
 */
static inline uint8_t RTC_HAL_GetTimeCompensationRegister(RTC_Type *base)
{
    return RTC_RD_TCR_TCR(base);
}

/*!
 * @brief  Writes to the field Time Compensation Register (TCR) of the RTC Time Compensation Register (RTC_TCR).
 *
 * Configures the number of 32.768 kHz clock cycles in each second. This register is double
 * buffered and writes do not take affect until the end of the
 * current compensation interval.
 *
 * @param  base The RTC base address pointer
 * @param  compValue value of the time compensation.
 */
static inline void RTC_HAL_SetTimeCompensationRegister(RTC_Type *base, const uint8_t compValue)
{
    RTC_WR_TCR_TCR(base, compValue);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Control*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Enables/disables the oscillator configuration for the 2pF load.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables load
 *         -false: disables load.
 */
static inline void RTC_HAL_SetOsc2pfLoadCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_SC2P(base, enable);
}

/*!
 * @brief  Reads the oscillator 2pF load configure bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 2pF additional load enabled.
 *         false: 2pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc2pfLoad(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_SC2P(base);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 4pF load.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables load.
 *         -false: disables load
 */
static inline void RTC_HAL_SetOsc4pfLoadCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_SC4P(base, enable);
}

/*!
 * @brief  Reads the oscillator 4pF load configuration bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 4pF additional load enabled.
 *         false: 4pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc4pfLoad(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_SC4P(base);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 8pF load.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables load.
 *         -false: disables load.
 */
static inline void RTC_HAL_SetOsc8pfLoadCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_SC8P(base, enable);
}

/*!
 * @brief  Reads the oscillator 8pF load configuration bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 8pF additional load enabled.
 *         false: 8pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc8pfLoad(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_SC8P(base);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 16pF load.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables load.
 *         -false: disables load.
 */
static inline void RTC_HAL_SetOsc16pfLoadCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_SC16P(base, enable);
}

/*!
 * @brief  Reads the oscillator 16pF load configuration bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 16pF additional load enabled.
 *         false: 16pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc16pfLoad(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_SC16P(base);
}

/*!
 * @brief  Enables/disables the 32 kHz clock output to other peripherals.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables clock out.
 *         -false: disables clock out.
 */
static inline void RTC_HAL_SetClockOutCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_CLKO(base, !enable);
}

/*!
 * @brief  Reads the RTC_CR CLKO bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 32 kHz clock is not output to other peripherals.
 *         false: 32 kHz clock is output to other peripherals.
 */
static inline bool RTC_HAL_GetClockOutCmd(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_CLKO(base);
}

/*!
 * @brief  Enables/disables the oscillator.
 *
 * After enabling, waits for the oscillator startup time before enabling the
 * time counter to allow the 32.768 kHz clock time to stabilize.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables oscillator.
 *         -false: disables oscillator.
 */
static inline void RTC_HAL_SetOscillatorCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_CR_OSCE(base, enable);
}

/*!
 * @brief  Reads the RTC_CR OSCE bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: 32.768 kHz oscillator is enabled
 *         false: 32.768 kHz oscillator is disabled.
 */
static inline bool RTC_HAL_IsOscillatorEnabled(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_OSCE(base);
}

/*!
 * @brief  Performs a software reset on the RTC module.
 *
 * This resets all RTC registers except for the SWR bit and the RTC_WAR and RTC_RAR
 * registers. The SWR bit is cleared after VBAT POR and by software
 * explicitly clearing it.
 * Note that  access control features (RTC_WAR and RTC_RAR registers)
 * are not available in all MCUs.
 *
 * @param  base The RTC base address pointer
 */
static inline void RTC_HAL_SoftwareReset(RTC_Type *base)
{
    RTC_BWR_CR_SWR(base, 1u);
}

/*!
 * @brief  Clears the software reset flag.
 *
 * @param  base The RTC base address pointer
 */
static inline void RTC_HAL_SoftwareResetFlagClear(RTC_Type *base)
{
    RTC_BWR_CR_SWR(base, 0u);
}

/*!
 * @brief  Reads the RTC_CR SWR bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: SWR is set.
 *         false: SWR is cleared.
 */
static inline bool RTC_HAL_ReadSoftwareResetStatus(RTC_Type *base)
{
    return (bool)RTC_BRD_CR_SWR(base);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Status*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the time counter status (enabled/disabled).
 *
 * @param  base The RTC base address pointer
 *
 * @return  -true: time counter is enabled, time seconds register and time
 *                prescaler register are not writeable, but increment.
 *          -false: time counter is disabled, time seconds register and
 *                 time prescaler register are writeable, but do not increment.
 */
static inline bool RTC_HAL_IsCounterEnabled(RTC_Type *base)
{
    return (bool)RTC_BRD_SR_TCE(base);
}

/*!
 * @brief  Changes the time counter status.
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: enables the time counter
 *         -false: disables the time counter.
 */
static inline void RTC_HAL_EnableCounter(RTC_Type *base, bool enable)
{
    RTC_BWR_SR_TCE(base, enable);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*!
 * @brief  Reads the value of the Monotonic Overflow Flag (MOF).
 *
 * This flag is set when the monotonic counter is enabled and the monotonic
 * counter high overflows. The monotonic counter does not increment and
 * reads as zero when this bit is set. This bit is cleared by writing the monotonic
 * counter high register when the monotonic counter is disabled.
 *
 * @param  base The RTC base address pointer.
 *
 * @return  -true: monotonic counter overflow has occurred and monotonic
 *                counter is read as zero.
 *          -false: No monotonic counter overflow has occurred.
 */
static inline bool RTC_HAL_IsMonotonicCounterOverflow(RTC_Type *base)
{
    return (bool)RTC_BRD_SR_MOF(base);
}
#endif

/*!
 * @brief  Checks whether the configured time alarm has occurred.
 *
 * Reads time alarm flag (TAF). This flag is set when the time
 * alarm register (TAR) equals the time seconds register (TSR) and
 * the TSR increments. This flag is cleared by writing the TAR register.
 *
 * @param  base The RTC base address pointer.
 *
 * @return  -true: time alarm has occurred.
 *          -false: no time alarm occurred.
 */
static inline bool RTC_HAL_HasAlarmOccured(RTC_Type *base)
{
    return (bool)RTC_BRD_SR_TAF(base);
}

/*!
 * @brief  Checks whether the time has been marked as invalid.
 *
 * Reads the value of RTC Status Register (RTC_SR), field Time
 * Invalid Flag (TIF). This flag is set on VBAT POR or software
 * reset. The TSR and TPR do not increment and read as zero when
 * this bit is set. This flag is cleared by writing the TSR
 * register when the time counter is disabled.
 *
 * @param  base The RTC base address pointer.
 *
 * @return  -true: time is INVALID and time counter is zero.
 *          -false: time is valid.
 */
static inline bool RTC_HAL_IsTimeInvalid(RTC_Type *base)
{
    return (bool)RTC_BRD_SR_TIF(base);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Interrupt Enable*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Checks whether the Time Seconds Interrupt is enabled/disabled.
 *
 * Reads the value of field Time Seconds Interrupt Enable (TSIE)of the RTC Interrupt Enable Register (RTC_IER).
 * The seconds interrupt is an edge-sensitive
 * interrupt with a dedicated interrupt vector. It is generated once a second
 * and requires no software overhead (there is no corresponding status flag to
 * clear).
 *
 * @param  base The RTC base address pointer
 *
 * @return  -true: Seconds interrupt is enabled.
 *          -false: Seconds interrupt is disabled.
 */
static inline bool RTC_HAL_IsSecsIntEnabled(RTC_Type *base)
{
    return (bool)RTC_BRD_IER_TSIE(base);
}

/*!
 * @brief  Enables/disables the Time Seconds Interrupt.
 *
 * Writes to the field Time Seconds
 * Interrupt Enable (TSIE) of the RTC Interrupt Enable Register (RTC_IER).
 * Note: The seconds interrupt is an edge-sensitive interrupt with a
 * dedicated interrupt vector. It is generated once a second and
 * requires no software overhead (there is no corresponding status
 * flag to clear).
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: Seconds interrupt is enabled.
 *         -false: Seconds interrupt is disabled.
 */
static inline void RTC_HAL_SetSecsIntCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_IER_TSIE(base, (uint32_t) enable);
}

/*!
 * @brief  Checks whether the Time Alarm Interrupt is enabled/disabled.
 *
 * Reads the field Time Alarm Interrupt Enable (TAIE) value of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  base The RTC base address pointer
 *
 * @return  true: Time alarm flag does generate an interrupt.
 *          false: Time alarm flag does not generate an interrupt.
 */
static inline bool RTC_HAL_ReadAlarmInt(RTC_Type *base)
{
    return (bool)RTC_BRD_IER_TAIE(base);
}

/*!
 * @brief  Enables/disables the Time Alarm Interrupt.
 *
 * Writes to the field Time Alarm
 * Interrupt Enable (TAIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: Time alarm flag does generate an interrupt.
 *         -false: Time alarm flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetAlarmIntCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_IER_TAIE(base, (uint32_t) enable);
}

/*!
 * @brief  Enables/disables the Time Overflow Interrupt.
 *
 * Writes to the field Time Overflow Interrupt Enable (TOIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: Time overflow flag does generate an interrupt.
 *         -false: Time overflow flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetTimeOverflowIntCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_IER_TOIE(base, (uint32_t) enable);
}

/*!
 * @brief  Enables/disables the Time Invalid Interrupt.
 *
 * Writes to the field Time Invalid
 * Interrupt Enable (TIIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  base The RTC base address pointer
 * @param  enable can be true or false
 *         -true: Time invalid flag does generate an interrupt.
 *         -false: Time invalid flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetTimeInvalidIntCmd(RTC_Type *base, bool enable)
{
    RTC_BWR_IER_TIIE(base, (uint32_t) enable);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*-------------------------------------------------------------------------------------------*/
/* RTC Monotonic Enable*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the Monotonic Counter Enable bit.
 *
 * @param  base The RTC base address pointer
 *
 * @return true: This means writing to the monotonic counter increments the counter by one and
 *               the value written is ignored.
 *         false: This means writing to the monotonic counter loads the counter with the
 *                value written.
 */
static inline bool RTC_HAL_ReadMonotonicEnable(RTC_Type *base)
{
    /* Reads value of the RTC_MER register, field Monotonic Counter Enable (MCE). */
    return (bool)RTC_BRD_MER_MCE(base);
}

/*!
 * @brief  Changes the state of Monotonic Counter Enable bit.
 *
 * @param  base The RTC base address pointer
 * @param  enable value to be written to the MER[MCE] bit
 *         true: Set the bit to 1 which means writing to the monotonic counter will increment
 *               the counter by one and the value written will be ignored.
 *         false: Set the bit to 0 which means writing to the monotonic counter loads the counter
 *                with the value written.
 */
static inline void RTC_HAL_SetMonotonicEnableCmd(RTC_Type *base, bool enable)
{
    /* Writes to the RTC_MER registers Monotonic Counter Enable (MCE) bit.*/
    RTC_BWR_MER_MCE(base, (uint32_t)enable);
}

/*!
 * @brief  Reads the values of the Monotonic Counter Low register.
 *
 * @param  base The RTC base address pointer
 *
 * @return  Monotonic Counter Low value.
 */
static inline uint32_t RTC_HAL_GetMonotonicCounterLow(RTC_Type *base)
{
    return RTC_RD_MCLR(base);
}

/*!
 * @brief  Reads the values of the Monotonic Counter High register.
 *
 * @param  base The RTC base address pointer
 *
 * @return  Monotonic Counter High value.
 */
static inline uint32_t RTC_HAL_GetMonotonicCounterHigh(RTC_Type *base)
{
    return RTC_RD_MCHR(base);
}

/*!
 * @brief  Writes values of the Monotonic Counter Low register.
 *
 * @param  base The RTC base address pointer
 * @param  counter [in] Monotonic Counter Low value to be stored.
 */
static inline void RTC_HAL_SetMonotonicCounterLow(RTC_Type *base, const uint32_t counter)
{
    /* enable writing to the counter*/
    RTC_BWR_MER_MCE(base, 0U);
    RTC_WR_MCLR(base, counter);
}

/*!
 * @brief  Writes values of the Monotonic Counter High register.
 *
 * @param  base The RTC base address pointer
 * @param  counter [in] Monotonic Counter High value to be stored.
 */
static inline void RTC_HAL_SetMonotonicCounterHigh(RTC_Type *base, const uint32_t counter)
{
    /* enable writing to the counter*/
    RTC_BWR_MER_MCE(base, 0U);
    RTC_WR_MCHR(base, counter);
}

#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */

/*! @}*/

#if defined(__cplusplus)
}
#endif


/*! @}*/

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

#endif /* __FSL_RTC_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

