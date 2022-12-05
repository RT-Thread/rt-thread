/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_CMP_H_
#define __FSL_CMP_H_

#include "fsl_common.h"

/*!
 * @addtogroup cmp_1
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.2.1. */
#define FSL_CMP_DRIVER_VERSION (MAKE_VERSION(2U, 2U, 1U))
/*@}*/

/*! @brief CMP input mux for positive and negative sides. */
enum _cmp_input_mux
{
    kCMP_InputVREF = 0U, /*!< Cmp input from VREF. */
    kCMP_Input1    = 1U, /*!< Cmp input source 1. */
    kCMP_Input2    = 2U, /*!< Cmp input source 2. */
    kCMP_Input3    = 3U, /*!< Cmp input source 3. */
    kCMP_Input4    = 4U, /*!< Cmp input source 4. */
    kCMP_Input5    = 5U, /*!< Cmp input source 5. */
};

/*! @brief CMP interrupt type. */
enum _cmp_interrupt_type
{
    kCMP_EdgeDisable       = 0U, /*!< Disable edge interupt. */
    kCMP_EdgeRising        = 2U, /*!< Interrupt on falling edge. */
    kCMP_EdgeFalling       = 4U, /*!< Interrupt on rising edge. */
    kCMP_EdgeRisingFalling = 6U, /*!< Interrupt on both rising and falling edges. */

    kCMP_LevelDisable = 1U, /*!< Disable level interupt. */
    kCMP_LevelHigh    = 3U, /*!< Interrupt on high level. */
    kCMP_LevelLow     = 5U, /*!< Interrupt on low level. */
};

/*! @brief CMP Voltage Reference source. */
typedef enum _cmp_vref_source
{
    KCMP_VREFSourceVDDA         = 1U, /*!< Select VDDA as VREF. */
    KCMP_VREFSourceInternalVREF = 0U, /*!< Select internal VREF as VREF. */
} cmp_vref_source_t;

typedef struct _cmp_vref_config
{
    cmp_vref_source_t vrefSource; /*!< Reference voltage source. */
    uint8_t vrefValue; /*!< Reference voltage step. Available range is 0-31. Per step equals to VREFINPUT/31. */
} cmp_vref_config_t;

/*! @brief CMP Filter sample mode. */
typedef enum _cmp_filtercgf_samplemode
{
    kCMP_FilterSampleMode0 = 0U, /*!< Bypass mode. Filtering is disabled. */
    kCMP_FilterSampleMode1 = 1U, /*!< Filter 1 clock period. */
    kCMP_FilterSampleMode2 = 2U, /*!< Filter 2 clock period. */
    kCMP_FilterSampleMode3 = 3U  /*!< Filter 3 clock period. */
} cmp_filtercgf_samplemode_t;

/*! @brief CMP Filter clock divider. */
typedef enum _cmp_filtercgf_clkdiv
{
    kCMP_FilterClockDivide1  = 0U, /*!< Filter clock period duration equals 1 analog comparator clock period. */
    kCMP_FilterClockDivide2  = 1U, /*!< Filter clock period duration equals 2 analog comparator clock period. */
    kCMP_FilterClockDivide4  = 2U, /*!< Filter clock period duration equals 4 analog comparator clock period. */
    kCMP_FilterClockDivide8  = 3U, /*!< Filter clock period duration equals 8 analog comparator clock period. */
    kCMP_FilterClockDivide16 = 4U, /*!< Filter clock period duration equals 16 analog comparator clock period. */
    kCMP_FilterClockDivide32 = 5U, /*!< Filter clock period duration equals 32 analog comparator clock period. */
    kCMP_FilterClockDivide64 = 6U  /*!< Filter clock period duration equals 64 analog comparator clock period. */
} cmp_filtercgf_clkdiv_t;

/*! @brief CMP configuration structure. */
typedef struct _cmp_config
{
    bool enableHysteresis;                     /*!< Enable hysteresis. */
    bool enableLowPower;                       /*!< Enable low power mode. */
    cmp_filtercgf_clkdiv_t filterClockDivider; /* Filter clock divider. Filter clock equals the Analog Comparator clock
                                                  divided by 2^FILTERCGF_CLKDIV. */
    cmp_filtercgf_samplemode_t
        filterSampleMode; /* Filter sample mode. Control the filtering of the Analog Comparator output. */
} cmp_config_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief CMP initialization.
 *
 * This function enables the CMP module and do necessary settings.
 *
 * @param config Pointer to the configuration structure.
 */
void CMP_Init(const cmp_config_t *config);

/*!
 * @brief CMP deinitialization.
 *
 * This function gates the clock for CMP module.
 */
void CMP_Deinit(void);

/*!
 * @brief Initializes the CMP user configuration structure.
 *
 * This function initializes the user configuration structure to these default values.
 * @code
 *   config->enableHysteresis    = true;
 *   config->enableLowPower      = true;
 *   config->filterClockDivider  = kCMP_FilterClockDivide1;
 *   config->filterSampleMode    = kCMP_FilterSampleMode0;
 * @endcode
 * @param config Pointer to the configuration structure.
 */
void CMP_GetDefaultConfig(cmp_config_t *config);

/* @} */

/*!
 * @name Compare Interface
 * @{
 */

/*
 * @brief Set the input channels for the comparator.
 *
 * @param positiveChannel Positive side input channel number. See "_cmp_input_mux".
 * @param negativeChannel Negative side input channel number. See "_cmp_input_mux".
 */
static inline void CMP_SetInputChannels(uint8_t positiveChannel, uint8_t negativeChannel)
{
    PMC->COMP &= ~(PMC_COMP_PMUX_MASK | PMC_COMP_NMUX_MASK);
    PMC->COMP |= (PMC_COMP_PMUX(positiveChannel) | PMC_COMP_NMUX(negativeChannel));
}

/*!
 * @brief Configures the VREFINPUT.
 *
 * @param config Pointer to the configuration structure.
 */
void CMP_SetVREF(const cmp_vref_config_t *config);

/*!
 * @brief Get CMP compare output.
 *
 * @return The output result. true: voltage on positive side is greater than negative side.
 *                            false: voltage on positive side is lower than negative side.
 */
static inline bool CMP_GetOutput(void)
{
    return SYSCON_COMP_INT_STATUS_VAL_MASK == (SYSCON->COMP_INT_STATUS & SYSCON_COMP_INT_STATUS_VAL_MASK);
}

/* @} */

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief CMP enable interrupt.
 *
 * @param type CMP interrupt type. See "_cmp_interrupt_type".
 */
static inline void CMP_EnableInterrupt(uint32_t type)
{
    SYSCON->COMP_INT_CTRL |= (SYSCON_COMP_INT_CTRL_INT_CTRL(type) | SYSCON_COMP_INT_CTRL_INT_ENABLE_MASK);
}

/*!
 * @brief CMP disable interrupt.
 *
 */
static inline void CMP_DisableInterrupt(void)
{
    SYSCON->COMP_INT_CTRL &= ~SYSCON_COMP_INT_CTRL_INT_ENABLE_MASK;
}

/*!
 * @brief CMP clear interrupt.
 *
 */
static inline void CMP_ClearInterrupt(void)
{
    SYSCON->COMP_INT_CTRL |= SYSCON_COMP_INT_CTRL_INT_CLEAR_MASK;
}

/*!
 * @brief Select which Analog comparator output (filtered or un-filtered) is used for interrupt detection.
 *
 * @param enable false: Select Analog Comparator raw output (unfiltered) as input for interrupt detection.
 *               true: Select Analog Comparator filtered output as input for interrupt detection.
 *
 * @note: When CMP is configured as the wakeup source in power down mode, this function must use the raw output as the
 *        interupt source, that is, call this function and set parameter enable to false.
 */
static inline void CMP_EnableFilteredInterruptSource(bool enable)
{
    if (enable)
    {
        SYSCON->COMP_INT_CTRL &= ~SYSCON_COMP_INT_CTRL_INT_SOURCE_MASK;
    }
    else
    {
        SYSCON->COMP_INT_CTRL |= SYSCON_COMP_INT_CTRL_INT_SOURCE_MASK;
    }
}
/* @} */

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Get CMP interrupt status before interupt enable.
 *
 * @return Interrupt status. true: interrupt pending,
 *                           false: no interrupt pending.
 */
static inline bool CMP_GetPreviousInterruptStatus(void)
{
    return SYSCON_COMP_INT_STATUS_STATUS_MASK == (SYSCON->COMP_INT_STATUS & SYSCON_COMP_INT_STATUS_STATUS_MASK);
}

/*!
 * @brief Get CMP interrupt status after interupt enable.
 *
 * @return Interrupt status. true: interrupt pending,
 *                           false: no interrupt pending.
 */
static inline bool CMP_GetInterruptStatus(void)
{
    return SYSCON_COMP_INT_STATUS_INT_STATUS_MASK == (SYSCON->COMP_INT_STATUS & SYSCON_COMP_INT_STATUS_INT_STATUS_MASK);
}
/* @} */

/*!
 * @name Filter Interface
 * @{
 */

/*!
 * @brief CMP Filter Sample Config.
 *
 * This function allows the users to configure the sampling mode and clock divider of the CMP Filter.
 *
 * @param filterSampleMode   CMP Select filter sample mode
 * @param filterClockDivider CMP Set fileter clock divider
 */
static inline void CMP_FilterSampleConfig(cmp_filtercgf_samplemode_t filterSampleMode,
                                          cmp_filtercgf_clkdiv_t filterClockDivider)
{
    uint32_t comp = PMC->COMP;

    comp &= ~(PMC_COMP_FILTERCGF_CLKDIV_MASK | PMC_COMP_FILTERCGF_SAMPLEMODE_MASK);
    comp |= (((uint32_t)filterClockDivider << PMC_COMP_FILTERCGF_CLKDIV_SHIFT) |
             ((uint32_t)filterSampleMode << PMC_COMP_FILTERCGF_SAMPLEMODE_SHIFT));

    PMC->COMP = comp;
}
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */
#endif /* __FSL_CMP_H_ */
