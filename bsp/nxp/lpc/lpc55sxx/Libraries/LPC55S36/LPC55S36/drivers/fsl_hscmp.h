/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_HSCMP_H_
#define _FSL_HSCMP_H_

#include "fsl_common.h"

/*!
 * @addtogroup hscmp
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief HSCMP driver version 2.0.3. */
#define FSL_HSCMP_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))
/*@}*/

/*!
 * @brief HSCMP status falgs mask.
 */
enum _hscmp_status_flags
{
    kHSCMP_OutputRisingEventFlag  = HSCMP_CSR_CFR_MASK,  /*!< Rising-edge on the comparison output has occurred. */
    kHSCMP_OutputFallingEventFlag = HSCMP_CSR_CFF_MASK,  /*!< Falling-edge on the comparison output has occurred. */
    kHSCMP_OutputAssertEventFlag  = HSCMP_CSR_COUT_MASK, /*!< Return the current value of the analog comparator output.
                                                              The flag does not support W1C. */
};

/*!
 * @brief HSCMP interrupt enable/disable mask.
 */
enum _hscmp_interrupt_enable
{
    kHSCMP_OutputRisingInterruptEnable  = HSCMP_IER_CFR_IE_MASK, /*!< Comparator interrupt enable rising. */
    kHSCMP_OutputFallingInterruptEnable = HSCMP_IER_CFF_IE_MASK, /*!< Comparator interrupt enable falling. */
};
/*!
 * @brief HSCMP hysteresis mode. See chip data sheet to get the actual hystersis
 *        value with each level
 */
typedef enum _hscmp_hysteresis_mode
{
    kHSCMP_HysteresisLevel0 = 0U, /*!< The hard block output has level 0 hysteresis internally. */
    kHSCMP_HysteresisLevel1 = 1U, /*!< The hard block output has level 1 hysteresis internally. */
    kHSCMP_HysteresisLevel2 = 2U, /*!< The hard block output has level 2 hysteresis internally. */
    kHSCMP_HysteresisLevel3 = 3U, /*!< The hard block output has level 3 hysteresis internally. */
} hscmp_hysteresis_mode_t;

/*!
 * @brief HSCMP nano mode.
 */
typedef enum _hscmp_power_mode
{
    kHSCMP_LowSpeedPowerMode  = 0U, /*!< Low speed comparison mode is selected. */
    kHSCMP_HighSpeedPowerMode = 1U, /*!< High speed comparison mode is selected. */
    kHSCMP_NanoPowerMode      = 2U, /*!< Nano power comparator is enabled. */
} hscmp_power_mode_t;

/*!
 * @brief Internal DAC reference voltage source.
 */
typedef enum _hscmp_dac_reference_voltage_source
{
    kHSCMP_VrefSourceVin1 = 0U, /*!< vrefh_int is selected as resistor ladder network supply reference Vin. */
    kHSCMP_VrefSourceVin2 = 1U, /*!< vrefh_ext is selected as resistor ladder network supply reference Vin. */
} hscmp_dac_reference_voltage_source_t;

/*!
 * @brief Configure the filter.
 */
typedef struct _hscmp_filter_config
{
    bool enableSample;          /*!< Decide whether to use the external SAMPLE as a sampling clock input. */
    uint8_t filterSampleCount;  /*!< Filter Sample Count. Available range is 1-7; 0 disables the filter. */
    uint8_t filterSamplePeriod; /*!< Filter Sample Period. The divider to the bus clock. Available range is 0-255. The
                                sampling clock must be at least 4 times slower than the system clock to the comparator.
                                So if enableSample is "false", filterSamplePeriod should be set greater than 4.*/
} hscmp_filter_config_t;

/*!
 * @brief configure the internal DAC.
 */
typedef struct _hscmp_dac_config
{
    bool enableLowPowerMode;                                     /*!< Decide whether to enable DAC low power mode. */
    hscmp_dac_reference_voltage_source_t referenceVoltageSource; /*!< Internal DAC supply voltage reference source. */
    uint8_t DACValue; /*!< Value for the DAC Output Voltage. Available range is 0-63.*/
} hscmp_dac_config_t;

/*!
 * @brief Configures the comparator.
 */
typedef struct _hscmp_config
{
    bool enableStopMode;      /*!< Decide whether to enable the comparator when in STOP modes. */
    bool enableOutputPin;     /*!< Decide whether to enable the comparator is available in selected pin. */
    bool useUnfilteredOutput; /*!< Decide whether to use unfiltered output. */
    bool enableInvertOutput;  /*!< Decide whether to inverts the comparator output. */
    hscmp_hysteresis_mode_t hysteresisMode; /*!< HSCMP hysteresis mode. */
    hscmp_power_mode_t powerMode;           /*!< HSCMP power mode. */
} hscmp_config_t;
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initialize the HSCMP
 *
 * This function initializes the HSCMP module. The operations included are:
 * - Enabling the clock for HSCMP module.
 * - Configuring the comparator.
 * - Enabling the HSCMP module.
 * Note: For some devices, multiple HSCMP instance share the same clock gate. In this case, to enable the clock for
 * any instance enables all the HSCMPs. Check the chip reference manual for the clock assignment of the HSCMP.
 *
 * @param base HSCMP peripheral base address.
 * @param config Pointer to "hscmp_config_t" structure.
 */
void HSCMP_Init(HSCMP_Type *base, const hscmp_config_t *config);

/*!
 * @brief De-initializes the HSCMP module.
 *
 * This function de-initializes the HSCMP module. The operations included are:
 * - Disabling the HSCMP module.
 * - Disabling the clock for HSCMP module.
 *
 * This function disables the clock for the HSCMP.
 * Note: For some devices, multiple HSCMP instance shares the same clock gate. In this case, before disabling the
 * clock for the HSCMP, ensure that all the HSCMP instances are not used.
 *
 * @param base HSCMP peripheral base address.
 */
void HSCMP_Deinit(HSCMP_Type *base);

/*!
 * @brief Gets an available pre-defined settings for the comparator's configuration.
 *
 * This function initializes the comparator configuration structure to these default values:
 * @code
 *   config->enableStopMode      = false;
 *   config->enableOutputPin     = false;
 *   config->useUnfilteredOutput = false;
 *   config->enableInvertOutput  = false;
 *   config->hysteresisMode      = kHSCMP_HysteresisLevel0;
 *   config->powerMode           = kHSCMP_LowSpeedPowerMode;
 * @endcode
 * @param config Pointer to "hscmp_config_t" structure.
 */
void HSCMP_GetDefaultConfig(hscmp_config_t *config);

/*!
 * @brief Enable/Disable HSCMP module.
 *
 * @param base HSCMP peripheral base address.
 * @param enable "true" means enable the module, and "false" means disable the module.
 */
static inline void HSCMP_Enable(HSCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR0 |= HSCMP_CCR0_CMP_EN_MASK;
    }
    else
    {
        base->CCR0 &= ~HSCMP_CCR0_CMP_EN_MASK;
    }
}

/*!
 * @brief Select the input channels for HSCMP. This function determines which input
 *        is selected for the negative and positive mux.
 *
 * @param base HSCMP peripheral base address.
 * @param positiveChannel Positive side input channel number. Available range is 0-7.
 * @param negativeChannel Negative side input channel number. Available range is 0-7.
 */
void HSCMP_SetInputChannels(HSCMP_Type *base, uint32_t positiveChannel, uint32_t negativeChannel);

/*!
 * @brief Enables/disables the DMA request for rising/falling events.
 *        Normally, the HSCMP generates a CPU interrupt if there is a rising/falling event. When
 *        DMA support is enabled and the rising/falling interrupt is enabled , the rising/falling
 *        event forces a DMA transfer request rather than a CPU interrupt instead.
 *
 * @param base HSCMP peripheral base address.
 * @param enable "true" means enable DMA support, and "false" means disable DMA support.
 */
static inline void HSCMP_EnableDMA(HSCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR1 |= HSCMP_CCR1_DMA_EN_MASK;
    }
    else
    {
        base->CCR1 &= ~HSCMP_CCR1_DMA_EN_MASK;
    }
}

/*!
 * @brief Enable/Disable window mode.When any windowed mode is active, COUTA is clocked by
 *        the bus clock whenever WINDOW = 1. The last latched value is held when WINDOW = 0.
 *        The optionally inverted comparator output COUT_RAW is sampled on every bus clock
 *        when WINDOW=1 to generate COUTA.
 *
 * @param base HSCMP peripheral base address.
 * @param enable "true" means enable window mode, and "false" means disable window mode.
 */
static inline void HSCMP_EnableWindowMode(HSCMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CCR1 |= HSCMP_CCR1_WINDOW_EN_MASK;
    }
    else
    {
        base->CCR1 &= ~HSCMP_CCR1_WINDOW_EN_MASK;
    }
}

/*!
 * @brief Configures the filter.
 *
 * @param base HSCMP peripheral base address.
 * @param config Pointer to "hscmp_filter_config_t" structure.
 */
void HSCMP_SetFilterConfig(HSCMP_Type *base, const hscmp_filter_config_t *config);

/*!
 * @brief Configure the internal DAC module.
 *
 * @param base HSCMP peripheral base address.
 * @param config Pointer to "hscmp_dac_config_t" structure. If config is "NULL", disable internal DAC.
 */
void HSCMP_SetDACConfig(HSCMP_Type *base, const hscmp_dac_config_t *config);

/*!
 * @brief Enable the interrupts.
 *
 * @param base HSCMP peripheral base address.
 * @param mask Mask value for interrupts. See "_hscmp_interrupt_enable".
 */
static inline void HSCMP_EnableInterrupts(HSCMP_Type *base, uint32_t mask)
{
    base->IER |= mask;
}

/*!
 * @brief Disable the interrupts.
 *
 * @param base HSCMP peripheral base address.
 * @param mask Mask value for interrupts. See "_hscmp_interrupt_enable".
 */
static inline void HSCMP_DisableInterrupts(HSCMP_Type *base, uint32_t mask)
{
    base->IER &= ~mask;
}

/*!
 * @brief Get the HSCMP status flags.
 *
 * @param base HSCMP peripheral base address.
 *
 * @return Mask value for the asserted flags. See "_hscmp_status_flags".
 */
static inline uint32_t HSCMP_GetStatusFlags(HSCMP_Type *base)
{
    return base->CSR;
}

/*!
 * @brief Clear the HSCMP status flags
 *
 * @param base HSCMP peripheral base address.
 * @param mask Mask value for the flags. See "_hscmp_status_flags".
 */
static inline void HSCMP_ClearStatusFlags(HSCMP_Type *base, uint32_t mask)
{
    base->CSR = mask;
}

/*@}*/

/*@}*/

#endif /* _FSL_HSCMP_H_ */
