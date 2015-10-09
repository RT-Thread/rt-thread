/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#ifndef __FSL_TSI_V2_HAL_SPECIFIC_H__
#define __FSL_TSI_V2_HAL_SPECIFIC_H__

#include <stdint.h>
#include "fsl_device_registers.h"
#include "fsl_tsi_hal.h"
#if FSL_FEATURE_SOC_TSI_COUNT

// Just for right generation of documentation
#if defined(__DOXYGEN__)
  #define  FSL_FEATURE_TSI_VERSION 1
#endif

/*!
 * @addtogroup tsi_hal
 * @{
 */


/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*!
 * @brief TSI low power scan intervals.
 *
 * These constants define the tsi low power scan intervals in a TSI instance.
 */
typedef enum _tsi_low_power_interval {
    kTsiLowPowerInterval_1ms = 0,   /*!< 1ms scan interval */
    kTsiLowPowerInterval_5ms = 1,   /*!< 5ms scan interval */
    kTsiLowPowerInterval_10ms = 2,  /*!< 10ms scan interval */
    kTsiLowPowerInterval_15ms = 3,  /*!< 15ms scan interval */
    kTsiLowPowerInterval_20ms = 4,  /*!< 20ms scan interval */
    kTsiLowPowerInterval_30ms = 5,  /*!< 30ms scan interval */
    kTsiLowPowerInterval_40ms = 6,  /*!< 40ms scan interval */
    kTsiLowPowerInterval_50ms = 7,  /*!< 50ms scan interval */
    kTsiLowPowerInterval_75ms = 8,  /*!< 75ms scan interval */
    kTsiLowPowerInterval_100ms = 9, /*!< 100ms scan interval */
    kTsiLowPowerInterval_125ms = 10, /*!< 125ms scan interval */
    kTsiLowPowerInterval_150ms = 11, /*!< 150ms scan interval */
    kTsiLowPowerInterval_200ms = 12, /*!< 200ms scan interval */
    kTsiLowPowerInterval_300ms = 13, /*!< 300ms scan interval */
    kTsiLowPowerInterval_400ms = 14, /*!< 400ms scan interval */
    kTsiLowPowerInterval_500ms = 15, /*!< 500ms scan interval */
} tsi_low_power_interval_t;

/*!
 * @brief TSI Reference oscillator charge current select.
 *
 * These constants define the tsi Reference oscillator charge current select in a TSI instance.
 */
typedef enum _tsi_reference_osc_charge_current {
    kTsiRefOscChargeCurrent_2uA = 0,        /*!< Reference oscillator charge current is 2uA */
    kTsiRefOscChargeCurrent_4uA = 1,        /*!< Reference oscillator charge current is 4uA */
    kTsiRefOscChargeCurrent_6uA = 2,        /*!< Reference oscillator charge current is 6uA */
    kTsiRefOscChargeCurrent_8uA = 3,        /*!< Reference oscillator charge current is 8uA */
    kTsiRefOscChargeCurrent_10uA = 4,       /*!< Reference oscillator charge current is 10uA */
    kTsiRefOscChargeCurrent_12uA = 5,       /*!< Reference oscillator charge current is 12uA */
    kTsiRefOscChargeCurrent_14uA = 6,       /*!< Reference oscillator charge current is 14uA */
    kTsiRefOscChargeCurrent_16uA = 7,       /*!< Reference oscillator charge current is 16uA */
    kTsiRefOscChargeCurrent_18uA = 8,       /*!< Reference oscillator charge current is 18uA */
    kTsiRefOscChargeCurrent_20uA = 9,       /*!< Reference oscillator charge current is 20uA */
    kTsiRefOscChargeCurrent_22uA = 10,      /*!< Reference oscillator charge current is 22uA */
    kTsiRefOscChargeCurrent_24uA = 11,      /*!< Reference oscillator charge current is 24uA */
    kTsiRefOscChargeCurrent_26uA = 12,      /*!< Reference oscillator charge current is 26uA */
    kTsiRefOscChargeCurrent_28uA = 13,      /*!< Reference oscillator charge current is 28uA */
    kTsiRefOscChargeCurrent_30uA = 14,      /*!< Reference oscillator charge current is 30uA */
    kTsiRefOscChargeCurrent_32uA = 15,      /*!< Reference oscillator charge current is 32uA */
} tsi_reference_osc_charge_current_t;

/*!
 * @brief TSI Reference oscillator charge current select limits.
 *
 * These constants define the limits of the TSI Reference oscillator charge current select in a TSI instance.
 */
typedef struct _tsi_reference_osc_charge_current_limits
{
  tsi_reference_osc_charge_current_t    upper;  /*!< Reference oscillator charge current upper limit */
  tsi_reference_osc_charge_current_t    lower;  /*!< Reference oscillator charge current lower limit */
}tsi_reference_osc_charge_current_limits_t;

/*!
 * @brief TSI External oscillator charge current select.
 *
 * These constants define the tsi External oscillator charge current select in a TSI instance.
 */
typedef enum _tsi_external_osc_charge_current {
    kTsiExtOscChargeCurrent_2uA = 0,        /*!< External oscillator charge current is 2uA */
    kTsiExtOscChargeCurrent_4uA = 1,        /*!< External oscillator charge current is 4uA */
    kTsiExtOscChargeCurrent_6uA = 2,        /*!< External oscillator charge current is 6uA */
    kTsiExtOscChargeCurrent_8uA = 3,        /*!< External oscillator charge current is 8uA */
    kTsiExtOscChargeCurrent_10uA = 4,       /*!< External oscillator charge current is 10uA */
    kTsiExtOscChargeCurrent_12uA = 5,       /*!< External oscillator charge current is 12uA */
    kTsiExtOscChargeCurrent_14uA = 6,       /*!< External oscillator charge current is 14uA */
    kTsiExtOscChargeCurrent_16uA = 7,       /*!< External oscillator charge current is 16uA */
    kTsiExtOscChargeCurrent_18uA = 8,       /*!< External oscillator charge current is 18uA */
    kTsiExtOscChargeCurrent_20uA = 9,       /*!< External oscillator charge current is 20uA */
    kTsiExtOscChargeCurrent_22uA = 10,      /*!< External oscillator charge current is 22uA */
    kTsiExtOscChargeCurrent_24uA = 11,      /*!< External oscillator charge current is 24uA */
    kTsiExtOscChargeCurrent_26uA = 12,      /*!< External oscillator charge current is 26uA */
    kTsiExtOscChargeCurrent_28uA = 13,      /*!< External oscillator charge current is 28uA */
    kTsiExtOscChargeCurrent_30uA = 14,      /*!< External oscillator charge current is 30uA */
    kTsiExtOscChargeCurrent_32uA = 15,      /*!< External oscillator charge current is 32uA */
} tsi_external_osc_charge_current_t;

/*!
 * @brief TSI External oscillator charge current select limits.
 *
 * These constants define the limits of the TSI External oscillator charge current select in a TSI instance.
 */
typedef struct _tsi_external_osc_charge_current_limits
{
  tsi_external_osc_charge_current_t    upper;  /*!< External oscillator charge current upper limit */
  tsi_external_osc_charge_current_t    lower;  /*!< External oscillator charge current lower limit */
}tsi_external_osc_charge_current_limits_t;

/*!
 * @brief TSI Internal capacitance trim value.
 *
 * These constants define the tsi Internal capacitance trim value in a TSI instance.
 */
typedef enum _tsi_internal_cap_trim {
    kTsiIntCapTrim_0_5pF = 0,        /*!< 0.5 pF internal reference capacitance */
    kTsiIntCapTrim_0_6pF = 1,        /*!< 0.6 pF internal reference capacitance */
    kTsiIntCapTrim_0_7pF = 2,        /*!< 0.7 pF internal reference capacitance */
    kTsiIntCapTrim_0_8pF = 3,        /*!< 0.8 pF internal reference capacitance */
    kTsiIntCapTrim_0_9pF = 4,        /*!< 0.9 pF internal reference capacitance */
    kTsiIntCapTrim_1_0pF = 5,        /*!< 1.0 pF internal reference capacitance */
    kTsiIntCapTrim_1_1pF = 6,        /*!< 1.1 pF internal reference capacitance */
    kTsiIntCapTrim_1_2pF = 7,        /*!< 1.2 pF internal reference capacitance */
} tsi_internal_cap_trim_t;

/*!
 * @brief TSI Delta voltage applied to analog oscillators.
 *
 * These constants define the tsi Delta voltage applied to analog oscillators in a TSI instance.
 */
typedef enum _tsi_osc_delta_voltage {
    kTsiOscDeltaVoltage_100mV = 0,        /*!< 100 mV delta voltage is applied */
    kTsiOscDeltaVoltage_150mV = 1,        /*!< 150 mV delta voltage is applied */
    kTsiOscDeltaVoltage_200mV = 2,        /*!< 200 mV delta voltage is applied */
    kTsiOscDeltaVoltage_250mV = 3,        /*!< 250 mV delta voltage is applied */
    kTsiOscDeltaVoltage_300mV = 4,        /*!< 300 mV delta voltage is applied */
    kTsiOscDeltaVoltage_400mV = 5,        /*!< 400 mV delta voltage is applied */
    kTsiOscDeltaVoltage_500mV = 6,        /*!< 500 mV delta voltage is applied */
    kTsiOscDeltaVoltage_600mV = 7,        /*!< 600 mV delta voltage is applied */
} tsi_osc_delta_voltage_t;

/*!
 * @brief TSI Active mode clock divider.
 *
 * These constants define the active mode clock divider in a TSI instance.
 */
typedef enum _tsi_active_mode_clock_divider {
    kTsiActiveClkDiv_1div = 0,          /*!< Active mode clock divider is set to 1 */
    kTsiActiveClkDiv_2048div = 1,       /*!< Active mode clock divider is set to 2048 */
} tsi_active_mode_clock_divider_t;

/*!
 * @brief TSI Active mode clock source.
 *
 * These constants define the active mode clock source in a TSI instance.
 */
typedef enum _tsi_active_mode_clock_source {
    kTsiActiveClkSource_BusClock = 0,      /*!< Active mode clock source is set to Bus Clock */
    kTsiActiveClkSource_MCGIRCLK = 1,      /*!< Active mode clock source is set to MCG Internal reference clock */
    kTsiActiveClkSource_OSCERCLK = 2,      /*!< Active mode clock source is set to System oscillator output */
} tsi_active_mode_clock_source_t;

/*!
 * @brief TSI active mode prescaler.
 *
 * These constants define the tsi active mode prescaler in a TSI instance.
 */
typedef enum _tsi_active_mode_prescaler {
    kTsiActiveModePrescaler_1div = 0,          /*!< Input clock source divided by 1 */
    kTsiActiveModePrescaler_2div = 1,          /*!< Input clock source divided by 2 */
    kTsiActiveModePrescaler_4div = 2,          /*!< Input clock source divided by 4 */
    kTsiActiveModePrescaler_8div = 3,          /*!< Input clock source divided by 8 */
    kTsiActiveModePrescaler_16div = 4,         /*!< Input clock source divided by 16 */
    kTsiActiveModePrescaler_32div = 5,         /*!< Input clock source divided by 32 */
    kTsiActiveModePrescaler_64div = 6,         /*!< Input clock source divided by 64 */
    kTsiActiveModePrescaler_128div = 7,        /*!< Input clock source divided by 128 */
} tsi_active_mode_prescaler_t;

/*!
* @brief TSI active mode prescaler limits.
*
* These constants define the limits of the TSI active mode prescaler in a TSI instance.
*/
typedef struct _tsi_active_mode_prescaler_limits {
  tsi_active_mode_prescaler_t upper;        /*!< Input clock source prescaler upper limit */
  tsi_active_mode_prescaler_t lower;        /*!< Input clock source prescaler lower limit */
}tsi_active_mode_prescaler_limits_t;

/*!
* @brief TSI operation mode limits
*
* These constants is used to specify the valid range of settings for the recalibration process of TSI parameters
*/
typedef struct _tsi_parameter_limits {
  tsi_n_consecutive_scans_limits_t              consNumberOfScan;       /*!< number of consecutive scan limits */
  tsi_reference_osc_charge_current_limits_t     refOscChargeCurrent;    /*!< Reference oscillator charge current limits */
  tsi_external_osc_charge_current_limits_t      extOscChargeCurrent;    /*!< External oscillator charge current limits */
  tsi_active_mode_prescaler_limits_t            activeModePrescaler;    /*!< Input clock source prescaler limits */
}tsi_parameter_limits_t;


#if (FSL_FEATURE_TSI_VERSION == 1)
/*!
 * @brief TSI configuration structure.
 *
 * This structure contains the settings for the most common TSI configurations including
 * the TSI module charge currents, number of scans, thresholds, trimming etc.
 */
typedef struct TsiConfig {
    tsi_electrode_osc_prescaler_t ps;       /*!< Prescaler */
    tsi_external_osc_charge_current_t extchrg;  /*!< Electrode charge current */
    tsi_reference_osc_charge_current_t refchrg;  /*!< Reference charge current */
    tsi_n_consecutive_scans_t nscn;     /*!< Number of scans. */
    uint8_t lpclks;   /*!< Low power clock. */
    tsi_active_mode_clock_source_t amclks;   /*!< Active mode clock source. */
    tsi_active_mode_clock_divider_t amclkdiv; /*!< Active mode prescaler. */
    tsi_active_mode_prescaler_t ampsc;    /*!< Active mode prescaler. */
    tsi_low_power_interval_t lpscnitv; /*!< Low power scan interval. */
    tsi_osc_delta_voltage_t delvol;   /*!< Delta voltage. */
    tsi_internal_cap_trim_t captrm;   /*!< Internal capacitence trimmer. */
    uint16_t thresh;   /*!< High threshold. */
    uint16_t thresl;   /*!< Low threshold. */
}tsi_config_t;

#elif (FSL_FEATURE_TSI_VERSION == 2)
/*!
 * @brief TSI configuration structure.
 *
 * This structure contains the settings for the most common TSI configurations including
 * the TSI module charge currents, number of scans, thresholds, trimming etc.
 */
typedef struct TsiConfig {
    tsi_electrode_osc_prescaler_t ps;       /*!< Prescaler */
    tsi_external_osc_charge_current_t extchrg;  /*!< Electrode charge current */
    tsi_reference_osc_charge_current_t refchrg;  /*!< Reference charge current */
    tsi_n_consecutive_scans_t nscn;     /*!< Number of scans. */
    uint8_t lpclks;   /*!< Low power clock. */
    tsi_active_mode_clock_source_t amclks;   /*!< Active mode clock source. */
    tsi_active_mode_prescaler_t ampsc;    /*!< Active mode prescaler. */
    tsi_low_power_interval_t lpscnitv; /*!< Low power scan interval. */
    uint16_t thresh;   /*!< High threshold. */
    uint16_t thresl;   /*!< Low threshold. */
}tsi_config_t;

#else
#error TSI version not supported.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
* @brief Enable Touch Sensing Input Module.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableModule(TSI_Type * base)
{
    TSI_BWR_GENCS_TSIEN(base, 1);
}

/*!
* @brief Disable Touch Sensing Input Module.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableModule(TSI_Type * base)
{
    TSI_BWR_GENCS_TSIEN(base, 0);
}

/*!
* @brief    Enable TSI module in stop mode.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableStop(TSI_Type * base)
{
    TSI_BWR_GENCS_STPE(base, 1);
}

/*!
* @brief Disable TSI module in stop mode.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableStop(TSI_Type * base)
{
    TSI_BWR_GENCS_STPE(base, 0);
}

/*!
* @brief Enable out of range interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableOutOfRangeInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_ESOR(base, 0);
}

/*!
* @brief Enable end of scan interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableEndOfScanInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_ESOR(base, 1);
}
  
/*!
* @brief Enable periodical (hardware) trigger scan.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnablePeriodicalScan(TSI_Type * base)
{
    TSI_BWR_GENCS_STM(base, 1);
}
  
/*!
* @brief Enable software trigger scan.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableSoftwareTriggerScan(TSI_Type * base)
{
    TSI_BWR_GENCS_STM(base, 0);
}

/*!
* @brief Enable error interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableErrorInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_ERIE(base, 1);
}

/*!
* @brief Disable error interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableErrorInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_ERIE(base, 0);
}

/*!
* @brief Clear out of range flag.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearOutOfRangeFlag(TSI_Type * base)
{
    TSI_BWR_GENCS_OUTRGF(base, 1);
}

/*!
* @brief Clear end of scan flag.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearEndOfScanFlag(TSI_Type * base)
{
    TSI_BWR_GENCS_EOSF(base, 1);
}

/*!
* @brief Enable TSI module interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_TSIIE(base, 1);
}

/*!
* @brief Disable TSI interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableInterrupt(TSI_Type * base)
{
    TSI_BWR_GENCS_TSIIE(base, 0);
}

/*!
* @brief Get interrupt enable flag.
*
* @param    base TSI module base address.
* @return   State of enable interrupt flag.
*/
static inline uint32_t TSI_HAL_IsInterruptEnabled(TSI_Type * base)
{
    return TSI_BRD_GENCS_TSIIE(base);
}

/*!
* @brief Start measurement (trigger the new measurement).
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_StartSoftwareTrigger(TSI_Type * base)
{
    TSI_SET_GENCS(base, TSI_GENCS_SWTS(1));
}

/*!
* @brief Get overrun flag.
*
* @param    base TSI module base address.
* @return   State of over run flag.
*/
static inline uint32_t TSI_HAL_IsOverrun(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_OVRF(base);
}

/*!
* @brief Clear over run flag
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearOverrunFlag(TSI_Type * base)
{
    TSI_BWR_GENCS_OVRF(base, 1);
}

/*!
* @brief Get external electrode error flag.
*
* @param    base TSI module base address.
* @return   Stae of external electrode error flag
*/
static inline uint32_t TSI_HAL_GetExternalElectrodeErrorFlag(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_EXTERF(base);
}

/*!
* @brief Clear external electrode error flag
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearExternalElectrodeErrorFlag(TSI_Type * base)
{
    TSI_BWR_GENCS_EXTERF(base, 1);
}

/*!
* @brief Set prescaler.
*
* @param    base    TSI module base address.
* @param    prescaler   Prescaler value.
* @return   None.
*/
static inline void TSI_HAL_SetPrescaler(TSI_Type * base, tsi_electrode_osc_prescaler_t prescaler)
{
    TSI_BWR_GENCS_PS(base, prescaler);
}

/*!
* @brief Set number of scans (NSCN).
*
* @param    base    TSI module base address.
* @param    number      Number of scans.
* @return   None.
*/
static inline void TSI_HAL_SetNumberOfScans(TSI_Type * base, tsi_n_consecutive_scans_t number)
{
    TSI_BWR_GENCS_NSCN(base, number);
}

/*!
* @brief Set low power scan interval.
*
* @param    base    TSI module base address.
* @param    interval    Interval for low power scan.
* @return   None.
*/
static inline void TSI_HAL_SetLowPowerScanInterval(TSI_Type * base, tsi_low_power_interval_t interval)
{
    TSI_BWR_GENCS_LPSCNITV(base, interval);
}

/*!
* @brief Get low power scan interval.
*
* @param   base    TSI module base address.
* @return  Interval for low power scan.
*/
static inline tsi_low_power_interval_t TSI_HAL_GetLowPowerScanInterval(TSI_Type * base)
{
    return (tsi_low_power_interval_t)TSI_BRD_GENCS_LPSCNITV(base);
}

/*!
* @brief Set low power clock.
*
* @param   base TSI module base address.
* @param clock Low power clock selection.
*/
static inline void TSI_HAL_SetLowPowerClock(TSI_Type * base, uint32_t clock)
{
    TSI_BWR_GENCS_LPCLKS(base, clock);
}

/*!
* @brief Get low power clock.
*
* @param    base    TSI module base address.
* @return   Low power clock selection.
*/
static inline uint32_t TSI_HAL_GetLowPowerClock(TSI_Type * base)
{
    return TSI_BRD_GENCS_LPCLKS(base);
}

/*!
* @brief Set the reference oscilator charge current.
*
* @param    base    TSI module base address.
* @param    current     The charge current.
* @return   None.
*/
static inline void TSI_HAL_SetReferenceChargeCurrent(TSI_Type * base, tsi_reference_osc_charge_current_t current)
{
    TSI_BWR_SCANC_REFCHRG(base, current);
}

/*!
* @brief Get the reference oscilator charge current.
*
* @param    base    TSI module base address.
* @return   The charge current.
*/
static inline tsi_reference_osc_charge_current_t TSI_HAL_GetReferenceChargeCurrent(TSI_Type * base)
{
    return (tsi_reference_osc_charge_current_t)TSI_BRD_SCANC_REFCHRG(base);
}

#if (FSL_FEATURE_TSI_VERSION == 1)
/*!
* @brief Set internal capacitance trim.
*
* @param    base    TSI module base address.
* @param    trim        Trim value.
* @return   None.
*/
static inline void TSI_HAL_SetInternalCapacitanceTrim(TSI_Type * base, tsi_internal_cap_trim_t trim)
{
    TSI_BWR_SCANC_CAPTRM(base, trim);
}

/*!
* @brief Get internal capacitance trim.
*
* @param    base    TSI module base address.
* @return   Trim value.
*/
static inline tsi_internal_cap_trim_t TSI_HAL_GetInternalCapacitanceTrim(TSI_Type * base)
{
    return (tsi_internal_cap_trim_t)TSI_BRD_SCANC_CAPTRM(base);
}

#endif

/*!
* @brief Set electrode charge current.
*
* @param    base    TSI module base address.
* @param    current     Electrode current.
* @return   None.
*/
static inline void TSI_HAL_SetElectrodeChargeCurrent(TSI_Type * base, tsi_external_osc_charge_current_t current)
{
    TSI_BWR_SCANC_EXTCHRG(base, current);
}

/*!
* @brief Get electrode charge current.
*
* @param   base    TSI module base address.
* @return  Charge current.
*/
static inline tsi_external_osc_charge_current_t TSI_HAL_GetElectrodeChargeCurrent(TSI_Type * base)
{
    return (tsi_external_osc_charge_current_t)TSI_BRD_SCANC_EXTCHRG(base);
}

#if (FSL_FEATURE_TSI_VERSION == 1)
/*!
* @brief Set delta voltage.
*
* @param    base    TSI module base address.
* @param    voltage     delta voltage.
* @return   None.
*/
static inline void TSI_HAL_SetDeltaVoltage(TSI_Type * base, uint32_t voltage)
{
    TSI_BWR_SCANC_DELVOL(base, voltage);
}

/*!
* @brief Get delta voltage.
*
* @param    base    TSI module base address.
* @return   Delta voltage.
*/
static inline uint32_t TSI_HAL_GetDeltaVoltage(TSI_Type * base)
{
    return TSI_BRD_SCANC_DELVOL(base);
}

#endif

/*!
* @brief Set scan modulo value.
*
* @param    base    TSI module base address.
* @param    modulo      Scan modulo value.
* @return   None.
*/
static inline void TSI_HAL_SetScanModulo(TSI_Type * base, uint32_t modulo)
{
    TSI_BWR_SCANC_SMOD(base, modulo);
}

/*!
* @brief Get scan modulo value.
*
* @param    base    TSI module base address.
* @return   Scan modulo value.
*/
static inline uint32_t TSI_HAL_GetScanModulo(TSI_Type * base)
{
    return TSI_BRD_SCANC_SMOD(base);
}

#if (FSL_FEATURE_TSI_VERSION == 1)
/*!
* @brief Set active mode clock divider.
*
* @param    base    TSI module base address.
* @param    divider     A value for divider.
* @return   None.
*/
static inline void TSI_HAL_SetActiveModeClockDivider(TSI_Type * base, uint32_t divider)
{
    TSI_BWR_SCANC_AMCLKDIV(base, divider);
}

/*!
* @brief Get active mode clock divider.
*
* @param    base    TSI module base address.
* @return   A value for divider.
*/
static inline uint32_t TSI_HAL_GetActiveModeClockDivider(TSI_Type * base)
{
    return TSI_BRD_SCANC_AMCLKDIV(base);
}
#endif

/*!
* @brief Set active mode source.
*
* @param    base    TSI module base address.
* @param    source      Active mode clock source (LPOSCCLK, MCGIRCLK, OSCERCLK).
* @return   None.
*/
static inline void TSI_HAL_SetActiveModeSource(TSI_Type * base, uint32_t source)
{
    TSI_BWR_SCANC_AMCLKS(base, source);
}

/*!
* @brief Get active mode source.
*
* @param    base    TSI module base address.
* @return   Source value.
*/
static inline uint32_t TSI_HAL_GetActiveModeSource(TSI_Type * base)
{
    return TSI_BRD_SCANC_AMCLKS(base);
}

/*!
* @brief Set active mode prescaler.
*
* @param    base    TSI module base address.
* @param    prescaler   Prescaler's value.
* @return   None.
*/
static inline void TSI_HAL_SetActiveModePrescaler(TSI_Type * base, tsi_active_mode_prescaler_t prescaler)
{
    TSI_BWR_SCANC_AMPSC(base, prescaler);
}

/*!
* @brief Get active mode prescaler.
*
* @param    base    TSI module base address.
* @return   Prescaler's value.
*/
static inline uint32_t TSI_HAL_GetActiveModePrescaler(TSI_Type * base)
{
    return TSI_BRD_SCANC_AMPSC(base);
}

/*!
* @brief Set low power channel. Only one channel can wake up MCU.
*
* @param    base    TSI module base address.
* @param    channel     Channel number.
* @return   None.
*/
static inline void TSI_HAL_SetLowPowerChannel(TSI_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);  
    TSI_BWR_PEN_LPSP(base, channel);
}

/*!
 * @brief Get low power channel. Only one channel can wake up MCU.
 *
 * @param   base TSI module base address.
 * @return Channel number.
 */
static inline uint32_t TSI_HAL_GetLowPowerChannel(TSI_Type * base)
{
    return TSI_BRD_PEN_LPSP(base);
}

/*!
* @brief Enable channel.
*
* @param    base    TSI module base address.
* @param    channel     Channel to be enabled.
* @return   None.
*/
static inline void TSI_HAL_EnableChannel(TSI_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);  
    TSI_SET_PEN(base, (1U << channel));
}

/*!
* @brief Enable channels. The function enables channels by mask. It can set all
*          at once.
*
* @param    base        TSI module base address.
* @param    channelsMask    Channels mask to be enabled.
* @return   None.
*/
static inline void TSI_HAL_EnableChannels(TSI_Type * base, uint32_t channelsMask)
{
    TSI_SET_PEN(base, (uint16_t)channelsMask);
}

/*!
* @brief Disable channel.
*
* @param    base    TSI module base address.
* @param    channel     Channel to be disabled.
* @return   None.
*/
static inline void TSI_HAL_DisableChannel(TSI_Type * base, uint32_t channel)
{
    TSI_CLR_PEN(base, (1U << channel));
}

/*!
* @brief Disable channels. The function disables channels by mask. It can set all
*          at once.
*
* @param    base        TSI module base address.
* @param    channelsMask    Channels mask to be disabled.
* @return   None.
*/
static inline void TSI_HAL_DisableChannels(TSI_Type * base, uint32_t channelsMask)
{
    TSI_CLR_PEN(base, channelsMask);
}

/*!
 * @brief Returns if channel is enabled.
 *
 * @param   base    TSI module base address.
 * @param   channel     Channel to be checked.
 *
 * @return True - if channel is enabled, false - otherwise.
 */
static inline uint32_t TSI_HAL_GetEnabledChannel(TSI_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);  
    return (TSI_RD_PEN(base) & (1U << channel));
}

/*!
* @brief Returns mask of enabled channels.
*
* @param    base    TSI module base address.
* @return   Channels mask that are enabled.
*/
static inline uint32_t TSI_HAL_GetEnabledChannels(TSI_Type * base)
{
    return (uint32_t)TSI_RD_PEN(base);
}

/*!
* @brief Set the Wake up channel counter.
*
* @param    base    TSI module base address.
* @return   Wake up counter value.
*/
static inline uint16_t TSI_HAL_GetWakeUpChannelCounter(TSI_Type * base)
{
  return TSI_BRD_WUCNTR_WUCNT(base);
}

/*!
* @brief Get tsi counter on actual channel.
*
* @param    base    TSI module base address.
* @param    channel     Index of TSI channel.
*
* @return   The counter value.
*/
static inline uint32_t TSI_HAL_GetCounter(TSI_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);  
    uint16_t *counter =  (uint16_t *)((uint32_t)(&(TSI_CNTR1_REG(base))) + (channel * 2U));
    return (uint32_t)(*counter);
}

/*!
* @brief Set low threshold.
*
* @param    base        TSI module base address.
* @param    low_threshold   Low counter threshold.
* @return   None.
*/
static inline void TSI_HAL_SetLowThreshold(TSI_Type * base, uint32_t low_threshold)
{
    TSI_BWR_THRESHOLD_LTHH(base, low_threshold);
}

/*!
* @brief Set high threshold.
*
* @param    base        TSI module base address.
* @param    high_threshold  High counter threshold.
* @return   None.
*/
static inline void TSI_HAL_SetHighThreshold(TSI_Type * base, uint32_t high_threshold)
{
    TSI_BWR_THRESHOLD_HTHH(base, high_threshold);
}

#ifdef __cplusplus
}
#endif


/*! @}*/

#endif
#endif /* __FSL_TSI_V2_HAL_SPECIFIC_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

