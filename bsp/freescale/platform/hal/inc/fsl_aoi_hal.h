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
#if !defined(__FSL_AOI_HAL_H__)
#define __FSL_AOI_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_AOI_COUNT

/*!
 * @addtogroup aoi_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief AOI status return codes.
 */
typedef enum _aoi_status
{
    kStatus_AOI_Success         = 0U, /*!< Success. */
    kStatus_AOI_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_AOI_Failed          = 2U /*!< Execution failed. */
} aoi_status_t;

/*
 * @brief AOI input configurations.
 *
 * The selection item represents the Boolean evaluations.
*/
typedef enum _aoi_input_config
{
    kAoiConfigLogicZero       = 0x0U, /*!< Forces the input to logical zero. */
    kAoiConfigInputSignal     = 0x1U, /*!< Passes the input signal. */
    kAoiConfigInvInputSignal  = 0x2U, /*!< Inverts the input signal. */
    kAoiConfigLogicOne        = 0x3U  /*!< Forces the input to logical one. */
} aoi_input_config_t;

/*!
 * @brief Defines the product term numbers.
 */
typedef enum _aoi_product_term
{
    kAoiTerm0 = 0x0U, /*!< Product term 0 */
    kAoiTerm1 = 0x1U, /*!< Product term 1 */
    kAoiTerm2 = 0x2U, /*!< Product term 2 */
    kAoiTerm3 = 0x3U  /*!< Product term 3 */
} aoi_product_term_t;

/*!
 * @brief AOI input signal indexes.
 */
typedef enum _aoi_input_signal_index
{
    kAoiInputA = 0x0U, /*!< Input configuration A */
    kAoiInputB = 0x1U, /*!< Input configuration B */
    kAoiInputC = 0x2U, /*!< Input configuration C */
    kAoiInputD = 0x3U  /*!< Input configuration D */
} aoi_input_signal_index_t;

/*!
 * @brief AOI event indexes, where an event is the collection of the four product
 *        terms (0, 1, 2, and 3) and the four signal inputs (A, B, C, and D).
 */
typedef enum _aoi_event_index
{
    kAoiEvent0 = 0x0U, /*!< Event 0 index */
    kAoiEvent1 = 0x1U, /*!< Event 1 index */
    kAoiEvent2 = 0x2U, /*!< Event 2 index */
    kAoiEvent3 = 0x3U  /*!< Event 3 index */
} aoi_event_index_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the AOI module to the reset state.
 *
 * This function initializes the module to the reset state. This state is defined in the chip Reference
 * Manual, which is the power on reset value.
 *
 * @param base Register base address for AOI module.
 */
void AOI_HAL_Init(AOI_Type* base);

/*!
* @brief Resets the configuration registers of a specific AOI event.
 *
 * This function resets all product term inputs of a selected event to the reset values.
 * This state is defined in the chip Reference Manual, which is the power on reset value.
 *
 * @param base Register base address for AOI module.
 * @param event Event of AOI to be reset of type aoi_event_index_t.
*/
void AOI_HAL_Reset(AOI_Type* base, aoi_event_index_t event);

/*!
 * @brief Defines the Boolean evaluation associated with the selected input in the selected product
 *        term of the desired event.
 *
 * This function defines the Boolean evaluation associated with the selected input in the selected
 * product term of the desired event.
 *
 * @param base Register base address for AOI module.
 * @param event Number of the event which will be set of type aoi_event_index_t.
 * @param productTerm The term which will be set of type aoi_product_term_t.
 * @param input The input which will be set of type aoi_input_signal_index_t.
 * @param config Selected input configuration of type aoi_input_config_t.
 */
void AOI_HAL_SetSignalLogicUnit(AOI_Type* base,
                                aoi_event_index_t event,
                                aoi_product_term_t productTerm,
                                aoi_input_signal_index_t input,
                                aoi_input_config_t config);

/*!
 * @brief Gets the Boolean evaluation associated with the selected input in the selected product
 *        term of the desired event.
 *
 * This function returns the Boolean evaluation associated with the selected input in the selected
 * product term of the desired event.
 *
 * @param base Register base address for AOI module.
 * @param event Number of the event which will be set of type aoi_event_index_t.
 * @param productTerm The product term which will be set of type aoi_product_term_t.
 * @param input The input which will be set of type aoi_input_signal_index_t.
 * @return Selected input configuration of type aoi_input_config_t.
 */
aoi_input_config_t AOI_HAL_GetSignalLogicUnit(AOI_Type* base,
                                              aoi_event_index_t event,
                                              aoi_product_term_t productTerm,
                                              aoi_input_signal_index_t input);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_FEATURE_SOC_AOI_COUNT */
#endif /* __FSL_AOI_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

