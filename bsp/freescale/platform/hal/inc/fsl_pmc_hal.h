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
#if !defined(__FSL_PMC_HAL_H__)
#define __FSL_PMC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_PMC_COUNT

/*! @addtogroup pmc_hal*/
/*! @{*/

/*! @file fsl_pmc_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Low-Voltage Warning Voltage Select*/
typedef enum _pmc_low_volt_warn_volt_select {
    kPmcLowVoltWarnVoltLowTrip,             /*!< Low trip point selected (VLVW = VLVW1)*/
    kPmcLowVoltWarnVoltMid1Trip,            /*!< Mid 1 trip point selected (VLVW = VLVW2)*/
    kPmcLowVoltWarnVoltMid2Trip,            /*!< Mid 2 trip point selected (VLVW = VLVW3)*/
    kPmcLowVoltWarnVoltHighTrip             /*!< High trip point selected (VLVW = VLVW4)*/
} pmc_low_volt_warn_volt_select_t;

/*! @brief Low-Voltage Detect Voltage Select*/
typedef enum _pmc_low_volt_detect_volt_select {
    kPmcLowVoltDetectVoltLowTrip,           /*!< Low trip point selected (V LVD = V LVDL )*/
    kPmcLowVoltDetectVoltHighTrip           /*!< High trip point selected (V LVD = V LVDH )*/
} pmc_low_volt_detect_volt_select_t;

#if FSL_FEATURE_PMC_HAS_BGBDS
/*! @brief Bandgap Buffer Drive Select. */
typedef enum _pmc_bandgap_buffer_drive_select {
    kPmcBandgapBufferDriveLow,              /*!< Low drive.  */
    kPmcBandgapBufferDriveHigh              /*!< High drive. */
} pmc_bandgap_buffer_drive_select_t;
#endif

/*! @brief Bandgap Buffer configuration. */
typedef struct _pmc_bandgap_buffer_config
{
    bool enable;                             /*!< Enable bandgap buffer.                   */
#if FSL_FEATURE_PMC_HAS_BGEN
    bool enableInLowPower;                   /*!< Enable bandgap buffer in low power mode. */
#endif
#if FSL_FEATURE_PMC_HAS_BGBDS
    pmc_bandgap_buffer_drive_select_t drive; /*!< Bandgap buffer drive select.             */
#endif
} pmc_bandgap_buffer_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Power Management Controller Control APIs*/
/*@{*/

/*!
 * @brief Configure the low voltage detect setting.
 *
 * This function configures the low voltage detect setting, including the trip
 * point voltage setting, enable interrupt or not, enable MCU reset or not.
 *
 * @param base  Base address for current PMC instance.
 * @param enableInt    Enable interrupt or not when low voltage detect.
 * @param enableReset  Enable MCU reset or not when low voltage detect.
 * @param voltSelect   Low voltage detect trip point voltage.
 */
static inline void PMC_HAL_LowVoltDetectConfig(PMC_Type * base,
                                               bool enableInt,
                                               bool enableReset,
                                               pmc_low_volt_detect_volt_select_t voltSelect)
{
    PMC_WR_LVDSC1(base, PMC_LVDSC1_LVDV(voltSelect) |
                        PMC_LVDSC1_LVDIE(enableInt) |
                        PMC_LVDSC1_LVDRE(enableReset));
}

/*!
 * @brief Low-Voltage Detect Acknowledge
 *
 * This function acknowledges the low voltage detection errors (write 1 to
 * clear LVDF).
 *
 * @param base  Base address for current PMC instance.
 */
static inline void PMC_HAL_SetLowVoltDetectAck(PMC_Type * base)
{
    PMC_BWR_LVDSC1_LVDACK(base, 1U);
}

/*!
 * @brief Low-Voltage Detect Flag Read
 *
 * This function  reads the current LVDF status. If it returns 1, a low
 * voltage event is detected.
 *
 * @param base  Base address for current PMC instance.
 * @return Current low voltage detect flag
 *                - true: Low-Voltage detected
 *                - false: Low-Voltage not detected
 */
static inline bool PMC_HAL_GetLowVoltDetectFlag(PMC_Type * base)
{
    return PMC_BRD_LVDSC1_LVDF(base);
}

/*!
 * @brief Configure the low voltage warning setting.
 *
 * This function configures the low voltage warning setting, including the trip
 * point voltage setting and enable interrupt or not.
 *
 * @param base  Base address for current PMC instance.
 * @param enableInt    Enable interrupt or not when low voltage detect.
 * @param voltSelect   Low voltage detect trip point voltage.
 */
static inline void PMC_HAL_LowVoltWarnConfig(PMC_Type * base,
                                             bool enableInt,
                                             pmc_low_volt_warn_volt_select_t voltSelect)
{
    PMC_WR_LVDSC2(base, PMC_LVDSC2_LVWV(voltSelect) |
                        PMC_LVDSC2_LVWIE(enableInt));
}

/*!
 * @brief Low-Voltage Warning Acknowledge
 * 
 * This function acknowledges the low voltage warning errors (write 1 to
 * clear LVWF).
 *
 * @param base  Base address for current PMC instance.
 */
static inline void PMC_HAL_SetLowVoltWarnAck(PMC_Type * base)
{
    PMC_BWR_LVDSC2_LVWACK(base, 1U);
}

/*!
 * @brief Low-Voltage Warning Flag Read
 *
 * This function polls the current LVWF status. When 1 is returned, it 
 * indicates a low-voltage warning event. LVWF is set when V Supply transitions
 * below the trip point or after reset and V Supply is already below the V LVW.
 *
 * @param base  Base address for current PMC instance.
 * @return Current LVWF status
 *                  - true: Low-Voltage Warning Flag is set.
 *                  - false: the  Low-Voltage Warning does not happen.
 */
static inline bool PMC_HAL_GetLowVoltWarnFlag(PMC_Type * base)
{
    return PMC_BRD_LVDSC2_LVWF(base);
}

/*!
 * @brief Configures the PMC bandgap.
 *
 * This function configures the PMC bandgap, including the drive select and
 * behavior in low power mode.
 *
 * @param base  Base address for current PMC instance.
 * @param config Pointer to the configuration.
 */
static inline void PMC_HAL_BandgapBufferConfig(PMC_Type * base,
                                               pmc_bandgap_buffer_config_t *config)
{
    PMC_WR_REGSC(base, PMC_REGSC_BGBE(config->enable)
#if FSL_FEATURE_PMC_HAS_BGEN
                     | PMC_REGSC_BGEN(config->enableInLowPower)
#endif
#if FSL_FEATURE_PMC_HAS_BGBDS
                     | PMC_REGSC_BGBDS(config->drive)
#endif
                     );
}

/*!
 * @brief Gets the acknowledge isolation value.
 *
 * This function  reads the Acknowledge Isolation setting that indicates 
 * whether certain peripherals and the I/O pads are in a latched state as 
 * a result of having been in the VLLS mode. 
 *
 * @param base  Base address for current PMC instance.
 * @return ACK isolation
 *               0 - Peripherals and I/O pads are in a normal run state.
 *               1 - Certain peripherals and I/O pads are in an isolated and
 *                   latched state.
 */
static inline uint8_t PMC_HAL_GetAckIsolation(PMC_Type * base)
{
    return PMC_BRD_REGSC_ACKISO(base);
}

/*!
 * @brief Clears an acknowledge isolation.
 *
 * This function  clears the ACK Isolation flag. Writing one to this setting
 * when it is set releases the I/O pads and certain peripherals to their normal
 * run mode state.
 *
 * @param base  Base address for current PMC instance.
 */
static inline void PMC_HAL_ClearAckIsolation(PMC_Type * base)
{
    PMC_BWR_REGSC_ACKISO(base, 1U);
}

/*!
 * @brief Gets the Regulator regulation status.
 *
 * This function  returns the regulator to a run regulation status. It provides
 * the current status of the internal voltage regulator.
 *
 * @param base  Base address for current PMC instance.
 * @return Regulation status
 *               0 - Regulator is in a stop regulation or in transition to/from the regulation.
 *               1 - Regulator is in a run regulation.
 *
 */
static inline uint8_t PMC_HAL_GetRegulatorStatus(PMC_Type * base)
{
    return PMC_BRD_REGSC_REGONS(base);
}

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_PMC_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

