/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_PLU_H_
#define FSL_PLU_H_

#include "fsl_common.h"

/*!
 * @addtogroup plu
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_PLU_DRIVER_VERSION (MAKE_VERSION(2, 2, 1)) /*!< Version 2.2.1 */
                                                       /*! @} */

/*! @brief Index of LUT */
typedef enum _plu_lut_index
{
    kPLU_LUT_0  = 0U,  /*!< 5-input Look-up Table 0 */
    kPLU_LUT_1  = 1U,  /*!< 5-input Look-up Table 1 */
    kPLU_LUT_2  = 2U,  /*!< 5-input Look-up Table 2 */
    kPLU_LUT_3  = 3U,  /*!< 5-input Look-up Table 3 */
    kPLU_LUT_4  = 4U,  /*!< 5-input Look-up Table 4 */
    kPLU_LUT_5  = 5U,  /*!< 5-input Look-up Table 5 */
    kPLU_LUT_6  = 6U,  /*!< 5-input Look-up Table 6 */
    kPLU_LUT_7  = 7U,  /*!< 5-input Look-up Table 7 */
    kPLU_LUT_8  = 8U,  /*!< 5-input Look-up Table 8 */
    kPLU_LUT_9  = 9U,  /*!< 5-input Look-up Table 9 */
    kPLU_LUT_10 = 10U, /*!< 5-input Look-up Table 10 */
    kPLU_LUT_11 = 11U, /*!< 5-input Look-up Table 11 */
    kPLU_LUT_12 = 12U, /*!< 5-input Look-up Table 12 */
    kPLU_LUT_13 = 13U, /*!< 5-input Look-up Table 13 */
    kPLU_LUT_14 = 14U, /*!< 5-input Look-up Table 14 */
    kPLU_LUT_15 = 15U, /*!< 5-input Look-up Table 15 */
    kPLU_LUT_16 = 16U, /*!< 5-input Look-up Table 16 */
    kPLU_LUT_17 = 17U, /*!< 5-input Look-up Table 17 */
    kPLU_LUT_18 = 18U, /*!< 5-input Look-up Table 18 */
    kPLU_LUT_19 = 19U, /*!< 5-input Look-up Table 19 */
    kPLU_LUT_20 = 20U, /*!< 5-input Look-up Table 20 */
    kPLU_LUT_21 = 21U, /*!< 5-input Look-up Table 21 */
    kPLU_LUT_22 = 22U, /*!< 5-input Look-up Table 22 */
    kPLU_LUT_23 = 23U, /*!< 5-input Look-up Table 23 */
    kPLU_LUT_24 = 24U, /*!< 5-input Look-up Table 24 */
    kPLU_LUT_25 = 25U  /*!< 5-input Look-up Table 25 */
} plu_lut_index_t;

/*! @brief Inputs of LUT. 5 input present for each LUT. */
typedef enum _plu_lut_in_index
{
    kPLU_LUT_IN_0 = 0U, /*!< LUT input 0 */
    kPLU_LUT_IN_1 = 1U, /*!< LUT input 1 */
    kPLU_LUT_IN_2 = 2U, /*!< LUT input 2 */
    kPLU_LUT_IN_3 = 3U, /*!< LUT input 3 */
    kPLU_LUT_IN_4 = 4U  /*!< LUT input 4 */
} plu_lut_in_index_t;

/*! @brief Available sources of LUT input */
typedef enum _plu_lut_input_source
{
    kPLU_LUT_IN_SRC_PLU_IN_0   = 0U,  /*!< Select PLU input 0 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_PLU_IN_1   = 1U,  /*!< Select PLU input 1 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_PLU_IN_2   = 2U,  /*!< Select PLU input 2 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_PLU_IN_3   = 3U,  /*!< Select PLU input 3 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_PLU_IN_4   = 4U,  /*!< Select PLU input 4 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_PLU_IN_5   = 5U,  /*!< Select PLU input 5 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_0  = 6U,  /*!< Select LUT output 0 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_1  = 7U,  /*!< Select LUT output 1 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_2  = 8U,  /*!< Select LUT output 2 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_3  = 9U,  /*!< Select LUT output 3 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_4  = 10U, /*!< Select LUT output 4 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_5  = 11U, /*!< Select LUT output 5 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_6  = 12U, /*!< Select LUT output 6 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_7  = 13U, /*!< Select LUT output 7 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_8  = 14U, /*!< Select LUT output 8 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_9  = 15U, /*!< Select LUT output 9 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_10 = 16U, /*!< Select LUT output 10 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_11 = 17U, /*!< Select LUT output 11 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_12 = 18U, /*!< Select LUT output 12 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_13 = 19U, /*!< Select LUT output 13 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_14 = 20U, /*!< Select LUT output 14 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_15 = 21U, /*!< Select LUT output 15 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_16 = 22U, /*!< Select LUT output 16 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_17 = 23U, /*!< Select LUT output 17 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_18 = 24U, /*!< Select LUT output 18 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_19 = 25U, /*!< Select LUT output 19 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_20 = 26U, /*!< Select LUT output 20 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_21 = 27U, /*!< Select LUT output 21 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_22 = 28U, /*!< Select LUT output 22 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_23 = 29U, /*!< Select LUT output 23 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_24 = 30U, /*!< Select LUT output 24 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_LUT_OUT_25 = 31U, /*!< Select LUT output 25 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_FLIPFLOP_0 = 32U, /*!< Select Flip-Flops state 0 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_FLIPFLOP_1 = 33U, /*!< Select Flip-Flops state 1 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_FLIPFLOP_2 = 34U, /*!< Select Flip-Flops state 2 to be connected to LUTn Input x */
    kPLU_LUT_IN_SRC_FLIPFLOP_3 = 35U  /*!< Select Flip-Flops state 3 to be connected to LUTn Input x */
} plu_lut_input_source_t;

/*! @brief PLU output multiplexer registers */
typedef enum _plu_output_index
{
    kPLU_OUTPUT_0 = 0U, /*!< PLU OUTPUT 0 */
    kPLU_OUTPUT_1 = 1U, /*!< PLU OUTPUT 1 */
    kPLU_OUTPUT_2 = 2U, /*!< PLU OUTPUT 2 */
    kPLU_OUTPUT_3 = 3U, /*!< PLU OUTPUT 3 */
    kPLU_OUTPUT_4 = 4U, /*!< PLU OUTPUT 4 */
    kPLU_OUTPUT_5 = 5U, /*!< PLU OUTPUT 5 */
    kPLU_OUTPUT_6 = 6U, /*!< PLU OUTPUT 6 */
    kPLU_OUTPUT_7 = 7U  /*!< PLU OUTPUT 7 */
} plu_output_index_t;

/*! @brief Available sources of PLU output */
typedef enum _plu_output_source
{
    kPLU_OUT_SRC_LUT_0      = 0U,  /*!< Select LUT0 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_1      = 1U,  /*!< Select LUT1 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_2      = 2U,  /*!< Select LUT2 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_3      = 3U,  /*!< Select LUT3 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_4      = 4U,  /*!< Select LUT4 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_5      = 5U,  /*!< Select LUT5 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_6      = 6U,  /*!< Select LUT6 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_7      = 7U,  /*!< Select LUT7 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_8      = 8U,  /*!< Select LUT8 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_9      = 9U,  /*!< Select LUT9 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_10     = 10U, /*!< Select LUT10 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_11     = 11U, /*!< Select LUT11 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_12     = 12U, /*!< Select LUT12 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_13     = 13U, /*!< Select LUT13 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_14     = 14U, /*!< Select LUT14 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_15     = 15U, /*!< Select LUT15 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_16     = 16U, /*!< Select LUT16 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_17     = 17U, /*!< Select LUT17 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_18     = 18U, /*!< Select LUT18 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_19     = 19U, /*!< Select LUT19 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_20     = 20U, /*!< Select LUT20 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_21     = 21U, /*!< Select LUT21 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_22     = 22U, /*!< Select LUT22 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_23     = 23U, /*!< Select LUT23 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_24     = 24U, /*!< Select LUT24 output to be connected to PLU output */
    kPLU_OUT_SRC_LUT_25     = 25U, /*!< Select LUT25 output to be connected to PLU output */
    kPLU_OUT_SRC_FLIPFLOP_0 = 26U, /*!< Select Flip-Flops state(0) to be connected to PLU output */
    kPLU_OUT_SRC_FLIPFLOP_1 = 27U, /*!< Select Flip-Flops state(1) to be connected to PLU output */
    kPLU_OUT_SRC_FLIPFLOP_2 = 28U, /*!< Select Flip-Flops state(2) to be connected to PLU output */
    kPLU_OUT_SRC_FLIPFLOP_3 = 29U  /*!< Select Flip-Flops state(3) to be connected to PLU output */
} plu_output_source_t;

#if defined(FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG) && FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG

/*! @brief The enumerator of PLU Interrupt. */
enum _plu_interrupt_mask
{
    kPLU_OUTPUT_0_INTERRUPT_MASK = 1 << 0, /*!< Select PLU output 0 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_1_INTERRUPT_MASK = 1 << 1, /*!< Select PLU output 1 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_2_INTERRUPT_MASK = 1 << 2, /*!< Select PLU output 2 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_3_INTERRUPT_MASK = 1 << 3, /*!< Select PLU output 3 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_4_INTERRUPT_MASK = 1 << 4, /*!< Select PLU output 4 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_5_INTERRUPT_MASK = 1 << 5, /*!< Select PLU output 5 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_6_INTERRUPT_MASK = 1 << 6, /*!< Select PLU output 6 contribute to interrupt/wake-up generation */
    kPLU_OUTPUT_7_INTERRUPT_MASK = 1 << 7  /*!< Select PLU output 7 contribute to interrupt/wake-up generation */
};

/*! @brief Control input of the PLU, add filtering for glitch. */
typedef enum _plu_wakeint_filter_mode
{
    kPLU_WAKEINT_FILTER_MODE_BYPASS       = 0U, /*!< Select Bypass mode */
    kPLU_WAKEINT_FILTER_MODE_1_CLK_PERIOD = 1U, /*!< Filter 1 clock period */
    kPLU_WAKEINT_FILTER_MODE_2_CLK_PERIOD = 2U, /*!< Filter 2 clock period */
    kPLU_WAKEINT_FILTER_MODE_3_CLK_PERIOD = 3U  /*!< Filter 3 clock period */
} plu_wakeint_filter_mode_t;

/*! @brief Clock source for filter mode. */
typedef enum _plu_wakeint_filter_clock_source
{
    kPLU_WAKEINT_FILTER_CLK_SRC_1MHZ_LPOSC = 0U, /*!< Select the 1MHz low-power oscillator as the filter clock */
    kPLU_WAKEINT_FILTER_CLK_SRC_12MHZ_FRO  = 1U, /*!< Select the 12MHz FRO as the filer clock */
    kPLU_WAKEINT_FILTER_CLK_SRC_ALT        = 2U  /*!< Select a third clock source */
} plu_wakeint_filter_clock_source_t;

/*! @brief Wake configuration. */
typedef struct _plu_wakeint_config
{
    plu_wakeint_filter_mode_t filterMode;          /*!< Filter Mode. */
    plu_wakeint_filter_clock_source_t clockSource; /*!< The clock source for filter mode. */
} plu_wakeint_config_t;
#endif /* FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Enable the PLU clock and reset the module.
 *
 * @note This API should be called at the beginning of the application using the PLU driver.
 *
 * @param base PLU peripheral base address
 */
void PLU_Init(PLU_Type *base);

/*!
 * @brief Gate the PLU clock
 *
 * @param base PLU peripheral base address
 */
void PLU_Deinit(PLU_Type *base);

/*! @}*/

/*!
 * @name Set input/output source and Truth Table
 * @{
 */

/*!
 * @brief Set Input source of LUT.
 *
 * Note: An external clock must be applied to the PLU_CLKIN input when using FFs.
 *       For each LUT, the slot associated with the output from LUTn itself is tied low.
 *
 * @param base PLU peripheral base address.
 * @param lutIndex LUT index (see @ref plu_lut_index_t typedef enumeration).
 * @param lutInIndex LUT input index (see @ref plu_lut_in_index_t typedef enumeration).
 * @param inputSrc LUT input source (see @ref plu_lut_input_source_t typedef enumeration).
 */
static inline void PLU_SetLutInputSource(PLU_Type *base,
                                         plu_lut_index_t lutIndex,
                                         plu_lut_in_index_t lutInIndex,
                                         plu_lut_input_source_t inputSrc)
{
    PLU->LUT[lutIndex].INP_MUX[lutInIndex] = (uint32_t)inputSrc;
}

/*!
 * @brief Set Output source of PLU.
 *
 * Note: An external clock must be applied to the PLU_CLKIN input when using FFs.
 *
 * @param base PLU peripheral base address.
 * @param outputIndex PLU output index (see @ref plu_output_index_t typedef enumeration).
 * @param outputSrc PLU output source (see @ref plu_output_source_t typedef enumeration).
 */
static inline void PLU_SetOutputSource(PLU_Type *base, plu_output_index_t outputIndex, plu_output_source_t outputSrc)
{
    base->OUTPUT_MUX[outputIndex] = (uint32_t)outputSrc;
}

/*!
 * @brief Set Truth Table of LUT.
 *
 * @param base PLU peripheral base address.
 * @param lutIndex LUT index (see @ref plu_lut_index_t typedef enumeration).
 * @param truthTable Truth Table value.
 */
static inline void PLU_SetLutTruthTable(PLU_Type *base, plu_lut_index_t lutIndex, uint32_t truthTable)
{
    base->LUT_TRUTH[lutIndex] = truthTable;
}

/*! @}*/

/*!
 * @name Read current Output State
 * @{
 */

/*!
 * @brief Read the current state of the 8 designated PLU Outputs.
 *
 * Note: The PLU bus clock must be re-enabled prior to reading the Outpus Register if PLU bus clock is
 *       shut-off.
 *
 * @param base PLU peripheral base address.
 * @return Current PLU output state value.
 */
static inline uint32_t PLU_ReadOutputState(PLU_Type *base)
{
    return (base->OUTPUTS & PLU_OUTPUTS_OUTPUT_STATE_MASK);
}

/*! @}*/

#if defined(FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG) && FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG
/*!
 * @name Wake-up/Interrupt Control
 * @{
 */

/*!
 * @brief Gets an available pre-defined settings for wakeup/interrupt control.
 *
 * This function initializes the initial configuration structure with an available settings. The default values are:
 * @code
 *   config->filterMode = kPLU_WAKEINT_FILTER_MODE_BYPASS;
 *   config->clockSource = kPLU_WAKEINT_FILTER_CLK_SRC_1MHZ_LPOSC;
 * @endcode
 * @param config Pointer to configuration structure.
 */
void PLU_GetDefaultWakeIntConfig(plu_wakeint_config_t *config);

/*!
 * @brief Enable PLU outputs wakeup/interrupt request.
 *
 * This function enables Any of the eight selected PLU outputs to contribute to an asynchronous wake-up or an interrupt
 * request.
 *
 * Note: If a PLU_CLKIN is provided, the raw wake-up/interrupt request will be set on the rising-edge of the PLU_CLKIN
 * whenever the raw request signal is high. This registered signal will be glitch-free and just use the default wakeint
 * config by PLU_GetDefaultWakeIntConfig(). If not, have to specify the filter mode and clock source to eliminate the
 * glitches caused by long and widely disparate delays through the network of LUTs making up the PLU. This way may
 * increase power consumption in low-power operating modes and inject delay before the wake-up/interrupt request is
 * generated.
 *
 * @param base PLU peripheral base address.
 * @param interruptMask PLU interrupt mask (see @ref _plu_interrupt_mask enumeration).
 * @param config Pointer to configuration structure (see @ref plu_wakeint_config_t typedef enumeration)
 */
void PLU_EnableWakeIntRequest(PLU_Type *base, uint32_t interruptMask, const plu_wakeint_config_t *config);

/*!
 * @brief Latch an interrupt
 *
 * This function latches the interrupt and then it can be cleared with PLU_ClearLatchedInterrupt().
 *
 * Note: This mode is not compatible with use of the glitch filter. If this bit is set, the FILTER MODE should be set
 * to kPLU_WAKEINT_FILTER_MODE_BYPASS (Bypass Mode) and PLU_CLKIN should be provided. If this bit is set, the
 * wake-up/interrupt request will be set on the rising-edge of PLU_CLKIN whenever the raw wake-up/interrupt signal is
 * high. The request must be cleared by software.
 *
 * @param base PLU peripheral base address.
 */
static inline void PLU_LatchInterrupt(PLU_Type *base)
{
    base->WAKEINT_CTRL |= PLU_WAKEINT_CTRL_LATCH_ENABLE_MASK;
}

/*!
 * @brief Clear the latched interrupt
 *
 * This function clears the wake-up/interrupt request flag latched by PLU_LatchInterrupt()
 *
 * Note: It is not necessary for the PLU bus clock to be enabled in order to write-to or read-back this bit.
 *
 * @param base PLU peripheral base address.
 */
void PLU_ClearLatchedInterrupt(PLU_Type *base);

/*! @}*/
#endif /* FSL_FEATURE_PLU_HAS_WAKEINT_CTRL_REG */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_PLU_H_ */
