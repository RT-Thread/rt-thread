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
#ifndef __FSL_TSI_V4_HAL_SPECIFIC_H__
#define __FSL_TSI_V4_HAL_SPECIFIC_H__

#include <stdint.h>
#include "fsl_device_registers.h"
#include "fsl_tsi_hal.h"
#if FSL_FEATURE_SOC_TSI_COUNT

/*!
 * @addtogroup tsi_hal
 * @{
 */


/*! @file*/

extern uint32_t tsi_hal_gencs/*[TSI_INSTANCE_COUNT]*/;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief TSI analog mode select.
 *
 * Set up TSI analog modes in a TSI instance.
 */
typedef enum _tsi_analog_mode_select {
    kTsiAnalogModeSel_Capacitive = 0,     /*!< Active TSI capacitive sensing mode */
    kTsiAnalogModeSel_NoiseNoFreqLim = 4, /*!< TSI works in single threshold noise detection mode and the freq. limitation
is disabled */
    kTsiAnalogModeSel_NoiseFreqLim = 8,   /*!< TSI analog works in single threshold noise detection mode and the freq. limitation
is enabled */
    kTsiAnalogModeSel_AutoNoise = 12,     /*!/ Active TSI analog in automatic noise detection mode */
} tsi_analog_mode_select_t;

/*!
 * @brief TSI Reference oscillator charge and discharge current select.
 *
 * These constants define the tsi Reference oscillator charge current select in a TSI (REFCHRG) instance.
 */
typedef enum _tsi_reference_osc_charge_current {
    kTsiRefOscChargeCurrent_500nA = 0, /*!< Reference oscillator charge current is 500nA */
    kTsiRefOscChargeCurrent_1uA = 1,   /*!< Reference oscillator charge current is 1uA */
    kTsiRefOscChargeCurrent_2uA = 2,   /*!< Reference oscillator charge current is 2uA */
    kTsiRefOscChargeCurrent_4uA = 3,   /*!< Reference oscillator charge current is 4uA */
    kTsiRefOscChargeCurrent_8uA = 4,   /*!< Reference oscillator charge current is 8uA */
    kTsiRefOscChargeCurrent_16uA = 5,  /*!< Reference oscillator charge current is 16uA */
    kTsiRefOscChargeCurrent_32uA = 6,  /*!< Reference oscillator charge current is 32uA */
    kTsiRefOscChargeCurrent_64uA = 7,  /*!< Reference oscillator charge current is 64uA */
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
 * @brief TSI oscilator's voltage rails.
 *
 * These bits indicate the oscillator's voltage rails.
 */
typedef enum _tsi_oscilator_voltage_rails {
    kTsiOscVolRails_Dv_103 = 0,        /*!< DV = 1.03 V; VP = 1.33 V; Vm = 0.30 V */
    kTsiOscVolRails_Dv_073 = 1,        /*!< DV = 0.73 V; VP = 1.18 V; Vm = 0.45 V */
    kTsiOscVolRails_Dv_043 = 2,        /*!< DV = 0.43 V; VP = 1.03 V; Vm = 0.60 V */
    kTsiOscVolRails_Dv_029 = 3,        /*!< DV = 0.29 V; VP = 0.95 V; Vm = 0.67 V */
} tsi_oscilator_voltage_rails_t;

/*!
 * @brief TSI External oscillator charge and discharge current select.
 *
 * These bits indicate the electrode oscillator charge and discharge current value
 * in TSI (EXTCHRG) instance.
 */
typedef enum _tsi_external_osc_charge_current {
    kTsiExtOscChargeCurrent_500nA = 0,  /*!< External oscillator charge current is 500nA */
    kTsiExtOscChargeCurrent_1uA = 1,    /*!< External oscillator charge current is 1uA */
    kTsiExtOscChargeCurrent_2uA = 2,    /*!< External oscillator charge current is 2uA */
    kTsiExtOscChargeCurrent_4uA = 3,    /*!< External oscillator charge current is 4uA */
    kTsiExtOscChargeCurrent_8uA = 4,    /*!< External oscillator charge current is 8uA */
    kTsiExtOscChargeCurrent_16uA = 5,   /*!< External oscillator charge current is 16uA */
    kTsiExtOscChargeCurrent_32uA = 6,   /*!< External oscillator charge current is 32uA */
    kTsiExtOscChargeCurrent_64uA = 7,   /*!< External oscillator charge current is 64uA */
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
 * @brief TSI channel number.
 *
 * These bits specify current channel to be measured.
 */
typedef enum _tsi_channel_number {
    kTsiChannelNumber_0 = 0,       /*!< Channel Number 0 */
    kTsiChannelNumber_1 = 1,       /*!< Channel Number 1 */
    kTsiChannelNumber_2 = 2,       /*!< Channel Number 2 */
    kTsiChannelNumber_3 = 3,       /*!< Channel Number 3 */
    kTsiChannelNumber_4 = 4,       /*!< Channel Number 4 */
    kTsiChannelNumber_5 = 5,       /*!< Channel Number 5 */
    kTsiChannelNumber_6 = 6,       /*!< Channel Number 6 */
    kTsiChannelNumber_7 = 7,       /*!< Channel Number 7 */
    kTsiChannelNumber_8 = 8,       /*!< Channel Number 8 */
    kTsiChannelNumber_9 = 9,       /*!< Channel Number 9 */
    kTsiChannelNumber_10 = 10,     /*!< Channel Number 10 */
    kTsiChannelNumber_11 = 11,     /*!< Channel Number 11 */
    kTsiChannelNumber_12 = 12,     /*!< Channel Number 12 */
    kTsiChannelNumber_13 = 13,     /*!< Channel Number 13 */
    kTsiChannelNumber_14 = 14,     /*!< Channel Number 14 */
    kTsiChannelNumber_15 = 15,     /*!< Channel Number 15 */
} tsi_channel_number_t;

/*!
 * @brief TSI configuration structure.
 *
 * This structure contains the settings for the most common TSI configurations including
 * the TSI module charge currents, number of scans, thresholds, and so on.
 */
typedef struct TsiConfig {
    tsi_electrode_osc_prescaler_t ps;       /*!< Prescaler */
    tsi_external_osc_charge_current_t extchrg;  /*!< Electrode charge current */
    tsi_reference_osc_charge_current_t refchrg;  /*!< Reference charge current */
    tsi_n_consecutive_scans_t nscn;     /*!< Number of scans. */
    tsi_analog_mode_select_t mode;      /*!< TSI mode of operation. */
    tsi_oscilator_voltage_rails_t dvolt;       /*!< Oscillator's voltage rails. */
    uint16_t thresh;   /*!< High threshold. */
    uint16_t thresl;   /*!< Low threshold. */
}tsi_config_t;

/*!
* @brief TSI operation mode limits
*
* These constants is used to specify the valid range of settings for the recalibration process of TSI parameters
*/
typedef struct _tsi_parameter_limits {
  tsi_n_consecutive_scans_limits_t              consNumberOfScan;       /*!< number of consecutive scan limits */
  tsi_reference_osc_charge_current_limits_t     refOscChargeCurrent;    /*!< Reference oscillator charge current limits */
  tsi_external_osc_charge_current_limits_t      extOscChargeCurrent;    /*!< External oscillator charge current limits */
}tsi_parameter_limits_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!
* @brief Enables an out-of-range interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableOutOfRangeInterrupt(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_ESOR_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);    
}

/*!
* @brief Enables the end of the scan interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableEndOfScanInterrupt(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_ESOR_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Enables the Touch Sensing Input Module.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableModule(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_TSIEN_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Disables the Touch Sensing Input Module.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableModule(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_TSIEN_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Enables the TSI module interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableInterrupt(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_TSIIEN_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Disables the TSI interrupt.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableInterrupt(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_TSIIEN_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the interrupt enable flag.
*
* @param    base TSI module base address.
* @return   State of enable interrupt flag.
*/
static inline uint32_t TSI_HAL_IsInterruptEnabled(TSI_Type * base)
{
    return TSI_BRD_GENCS_TSIIEN(base);
}

/*!
* @brief Gets the TSI STOP enable.
*
* @param    base    TSI module base address.
* @return   Number of scans.
*/
static inline uint32_t TSI_HAL_GetEnableStop(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_STPE(base);
}

/*!
* @brief Sets the TSI STOP enable. This enables TSI module function in low power modes.
*
* @param    base    TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableStop(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_STPE_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Sets the TSI STOP disable. The TSI is disabled in low power modes.
*
* @param    base    TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DisableStop(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_STPE_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Enables the periodical (hardware) trigger scan.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableHardwareTriggerScan(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_STM_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Enables the periodical (hardware) trigger scan.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_EnableSoftwareTriggerScan(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_STM_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Swaps the current sources (CURSW) of electrode oscillator and reference
* oscillator.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_CurrentSourcePairSwapped(TSI_Type * base)
{
    tsi_hal_gencs |= TSI_GENCS_CURSW_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Does not swap the current sources (CURSW) of electrode oscillator and reference
* oscillator.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_CurrentSourcePairNotSwapped(TSI_Type * base)
{
    tsi_hal_gencs &= ~TSI_GENCS_CURSW_MASK;
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the current source pair swapped status.
*
* @param    base TSI module base address.
* @return   Current source pair swapped status.
*/
static inline uint32_t TSI_HAL_GetCurrentSourcePairSwapped(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_GENCS_CURSW(base);
}

/*!
* @brief Clears an out-of-range flag.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearOutOfRangeFlag(TSI_Type * base)
{    
    TSI_WR_GENCS(base, (tsi_hal_gencs | TSI_GENCS_OUTRGF_MASK));
}


/*!
* @brief Clears the end of scan flag.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_ClearEndOfScanFlag(TSI_Type * base)
{
    TSI_WR_GENCS(base, (tsi_hal_gencs | TSI_GENCS_EOSF_MASK));
}

/*!
* @brief Sets the prescaler.
*
* @param    base    TSI module base address.
* @param    prescaler   Prescaler value.
* @return   None.
*/
static inline void TSI_HAL_SetPrescaler(TSI_Type * base, tsi_electrode_osc_prescaler_t prescaler)
{
    tsi_hal_gencs &= ~TSI_GENCS_PS_MASK;
    tsi_hal_gencs |= TSI_GENCS_PS(prescaler);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Sets the number of scans (NSCN).
*
* @param    base    TSI module base address.
* @param    number      Number of scans.
* @return   None.
*/
static inline void TSI_HAL_SetNumberOfScans(TSI_Type * base, tsi_n_consecutive_scans_t number)
{
    tsi_hal_gencs &= ~TSI_GENCS_NSCN_MASK;
    tsi_hal_gencs |= TSI_GENCS_NSCN(number);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Sets the the measured channel number.
*
* @param    base    TSI module base address.
* @param    channel     Channel number 0 ... 15.
* @return   None.
*/
static inline void TSI_HAL_SetMeasuredChannelNumber(TSI_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_TSI_CHANNEL_COUNT);  
    TSI_BWR_DATA_TSICH(base, channel);
}

/*!
* @brief Gets the measured channel number.
*
* @param    base    TSI module base address.
* @return   uint32_t    Channel number 0 ... 15.
*/
static inline uint32_t TSI_HAL_GetMeasuredChannelNumber(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_DATA_TSICH(base);
}

/*!
* @brief DMA transfer enable.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DmaTransferEnable(TSI_Type * base)
{
    TSI_BWR_DATA_DMAEN(base, 1);
}

/*!
* @brief DMA transfer disable - does not generate DMA transfer request.
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_DmaTransferDisable(TSI_Type * base)
{
    TSI_BWR_DATA_DMAEN(base, 0);
}

/*!
* @brief Gets the DMA transfer enable flag.
*
* @param    base TSI module base address.
* @return   State of enable module flag.
*/
static inline uint32_t TSI_HAL_IsDmaTransferEnable(TSI_Type * base)
{
    return TSI_BRD_DATA_DMAEN(base);
}

/*!
* @brief Starts measurement (trigger the new measurement).
*
* @param    base TSI module base address.
* @return   None.
*/
static inline void TSI_HAL_StartSoftwareTrigger(TSI_Type * base)
{
    TSI_SET_DATA(base, TSI_DATA_SWTS(1));
}

/*!
* @brief Gets the conversion counter value.
*
* @param    base TSI module base address.
* @return   Accumulated scan counter value ticked by the reference clock.
*/
static inline uint32_t TSI_HAL_GetCounter(TSI_Type * base)
{
    return (uint32_t)TSI_BRD_DATA_TSICNT(base);
}

/*!
* @brief Sets the TSI wake-up channel low threshold.
*
* @param    base        TSI module base address.
* @param    low_threshold   Low counter threshold.
* @return   None.
*/
static inline void TSI_HAL_SetLowThreshold(TSI_Type * base, uint32_t low_threshold)
{
    assert(low_threshold < 65535U);
    TSI_BWR_TSHD_THRESL(base, low_threshold);
}

/*!
* @brief Sets the TSI wake-up channel high threshold.
*
* @param    base        TSI module base address.
* @param    high_threshold  High counter threshold.
* @return   None.
*/
static inline void TSI_HAL_SetHighThreshold(TSI_Type * base, uint32_t high_threshold)
{
    assert(high_threshold < 65535U);  
    TSI_BWR_TSHD_THRESH(base, high_threshold);
}

/*!
* @brief Sets the analog mode of the TSI module.
*
* @param    base    TSI module base address.
* @param    mode   Mode value.
* @return   None.
*/
static inline void TSI_HAL_SetMode(TSI_Type * base, tsi_analog_mode_select_t mode)
{
    tsi_hal_gencs &= ~TSI_GENCS_MODE_MASK;
    tsi_hal_gencs |= TSI_GENCS_MODE(mode);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the analog mode of the TSI module.
*
* @param    base    TSI module base address.
* @return   tsi_analog_mode_select_t   Mode value.
*/
static inline tsi_analog_mode_select_t TSI_HAL_GetMode(TSI_Type * base)
{
    return (tsi_analog_mode_select_t)((tsi_hal_gencs & TSI_GENCS_MODE_MASK) >> TSI_GENCS_MODE_SHIFT);
}

/*!
* @brief Gets the analog mode of the TSI module.
*
* @param    base    TSI module base address.
* @return   tsi_analog_mode_select_t   Mode value.
*/
static inline uint32_t TSI_HAL_GetNoiseResult(TSI_Type * base)
{
    uint32_t gencs = TSI_RD_GENCS(base);
    
    return (gencs & TSI_GENCS_MODE_MASK) >> TSI_GENCS_MODE_SHIFT;
}

/*!
* @brief Sets the reference oscillator charge current.
*
* @param    base    TSI module base address.
* @param    current     The charge current.
* @return   None.
*/
static inline void TSI_HAL_SetReferenceChargeCurrent(TSI_Type * base, tsi_reference_osc_charge_current_t current)
{
    tsi_hal_gencs &= ~TSI_GENCS_REFCHRG_MASK;
    tsi_hal_gencs |= TSI_GENCS_REFCHRG(current);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the reference oscillator charge current.
*
* @param    base    TSI module base address.
* @return   tsi_reference_osc_charge_current_t The charge current.
*/
static inline tsi_reference_osc_charge_current_t TSI_HAL_GetReferenceChargeCurrent(TSI_Type * base)
{
    return (tsi_reference_osc_charge_current_t)TSI_GENCS_REFCHRG(tsi_hal_gencs);
}

/*!
* @brief Sets the oscillator's voltage rails.
*
* @param    base    TSI module base address.
* @param    dvolt     The voltage rails.
* @return   None.
*/
static inline void TSI_HAL_SetOscilatorVoltageRails(TSI_Type * base, tsi_oscilator_voltage_rails_t dvolt)
{
    tsi_hal_gencs &= ~TSI_GENCS_DVOLT_MASK;
    tsi_hal_gencs |= TSI_GENCS_DVOLT(dvolt);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the oscillator's voltage rails.
*
* @param    base    TSI module base address.
* @return   dvolt     The voltage rails..
*/
static inline tsi_oscilator_voltage_rails_t TSI_HAL_GetOscilatorVoltageRails(TSI_Type * base)
{
    return (tsi_oscilator_voltage_rails_t)TSI_BRD_GENCS_DVOLT(base);
}

/*!
* @brief Sets the external electrode charge current.
*
* @param    base    TSI module base address.
* @param    current     Electrode current.
* @return   None.
*/
static inline void TSI_HAL_SetElectrodeChargeCurrent(TSI_Type * base, tsi_external_osc_charge_current_t current)
{
    tsi_hal_gencs &= ~TSI_GENCS_EXTCHRG_MASK;
    tsi_hal_gencs |= TSI_GENCS_EXTCHRG(current);
    TSI_WR_GENCS(base, tsi_hal_gencs);
}

/*!
* @brief Gets the electrode charge current.
*
* @param   base    TSI module base address.
* @return  Charge current.
*/
static inline tsi_external_osc_charge_current_t TSI_HAL_GetElectrodeChargeCurrent(TSI_Type * base)
{
    return (tsi_external_osc_charge_current_t)TSI_BRD_GENCS_EXTCHRG(base);
}

#ifdef __cplusplus
}
#endif

#endif

/*! @}*/

#endif /* __FSL_TSI_V4_HAL_H_SPECIFIC__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

