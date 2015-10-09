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
#ifndef __FSL_AOI_DRIVER_H__
#define __FSL_AOI_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_aoi_hal.h"

#if FSL_FEATURE_SOC_AOI_COUNT

/*!
 * @addtogroup aoi_driver
 * @{
 */

/*! @brief Table of base addresses for AOI instances. */
extern AOI_Type* const g_aoiBase[];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief AOI product term configuration structure  */
typedef struct AoiProductTermConfig
{
    aoi_input_config_t PTAC;  /*!< PTx_AC configuration.  */
    aoi_input_config_t PTBC;  /*!< PTx_BC configuration.  */
    aoi_input_config_t PTCC;  /*!< PTx_CC configuration.  */
    aoi_input_config_t PTDC;  /*!< PTx_DC configuration.  */
} aoi_product_term_config_t;

/*!
 * @brief AOI event configuration structure
 *
 * Defines structure AoiEventConfig and use the AOI_DRV_ConfigEventLogic() function to make
 * whole event configuration.
 */
typedef struct AoiEventConfig
{
    aoi_input_config_t PT1DC; /*!< PT1_DC configuration.  */
    aoi_input_config_t PT1CC; /*!< PT1_CC configuration.  */
    aoi_input_config_t PT1BC; /*!< PT1_BC configuration.  */
    aoi_input_config_t PT1AC; /*!< PT1_AC configuration.  */
    aoi_input_config_t PT0DC; /*!< PT0_DC configuration.  */
    aoi_input_config_t PT0CC; /*!< PT0_CC configuration.  */
    aoi_input_config_t PT0BC; /*!< PT0_BC configuration.  */
    aoi_input_config_t PT0AC; /*!< PT0_AC configuration.  */
    aoi_input_config_t PT3DC; /*!< PT3_DC configuration.  */
    aoi_input_config_t PT3CC; /*!< PT3_CC configuration.  */
    aoi_input_config_t PT3BC; /*!< PT3_BC configuration.  */
    aoi_input_config_t PT3AC; /*!< PT3_AC configuration.  */
    aoi_input_config_t PT2DC; /*!< PT2_DC configuration.  */
    aoi_input_config_t PT2CC; /*!< PT2_CC configuration.  */
    aoi_input_config_t PT2BC; /*!< PT2_BC configuration.  */
    aoi_input_config_t PT2AC; /*!< PT2_AC configuration.  */
} aoi_event_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes AOI module.
 *
 * This function initializes AOI module. It configures all the AOI module inputs
 * of all events to the reset state (kAoiLogicZero).
 *
 * This is an example to initialize the AOI module:
   @code
    status = AOI_DRV_Init();
    switch (status)
    {
        //...
    }
   @endcode
 *
 * @param   instance The instance number of the AOI peripheral
 * @return kStatus_AOI_Success indicating successful initialization
 */
aoi_status_t AOI_DRV_Init(uint32_t instance);

/*!
 * @brief De-initializes the AOI module.
 *
 * This function clears all configurations and shuts down the AOI module clock to reduce the power
 * consumption.
 *
 * @param   instance The instance number of the AOI peripheral
 * @return kStatus_AOI_Success indicating successful de-initialization
 */
aoi_status_t AOI_DRV_Deinit(uint32_t instance);

/*!
 * @brief Configures an AOI event.
 *
 * This function configures an AOI event according
 * to the aoiEventConfig structure. This function configures all  inputs (A, B, C, and D)
 * of all  product terms (0, 1, 2, and 3) of a desired event.
 * This is an example to set up the AOI Event structure:
 *
   @code

    aoi_event_config_t aoiEventConfig;

    aoiEventConfig.PT0AC =  kAoiConfigInputSignal;
    aoiEventConfig.PT0BC =  kAoiConfigLogicZero;
    aoiEventConfig.PT0CC =  kAoiConfigLogicZero;
    aoiEventConfig.PT0DC =  kAoiConfigLogicZero;

    aoiEventConfig.PT1AC =  kAoiConfigInvInputSignal;
    aoiEventConfig.PT1BC =  kAoiConfigLogicZero;
    aoiEventConfig.PT1CC =  kAoiConfigLogicZero;
    aoiEventConfig.PT1DC =  kAoiConfigInputSignal;

    aoiEventConfig.PT2AC =  kAoiConfigInputSignal;
    aoiEventConfig.PT2BC =  kAoiConfigInputSignal;
    aoiEventConfig.PT2CC =  kAoiConfigInputSignal;
    aoiEventConfig.PT2DC =  kAoiConfigLogicOne;

    aoiEventConfig.PT3AC =  kAoiConfigLogicOne;
    aoiEventConfig.PT3BC =  kAoiConfigLogicOne;
    aoiEventConfig.PT3CC =  kAoiConfigLogicOne;
    aoiEventConfig.PT3DC =  kAoiConfigLogicOne;

    aoi_status_t status;
    // In the function call below, the value of "2" indicates event #2 is being used.
    status = AOI_DRV_ConfigEventLogic(0, 2, &aoiEventConfig);
    switch (status)
    {
        //...
    }
   @endcode
 *
 * @param   instance The instance number of the AOI peripheral
 * @param   event Event which will be configured of type aoi_event_index_t.
 * @param   eventConfigPtr Pointer to type aoi_event_config_t structure. The user is responsible to
 * fill out the members of this structure and pass the pointer to this function.
 * @return  An error code or kStatus_AOI_Success.
 */
aoi_status_t AOI_DRV_ConfigEventLogic(uint32_t instance,
                                      aoi_event_index_t event,
                                      const aoi_event_config_t * eventConfigPtr);

/*!
 * @brief Configures an AOI module product term in a specific event.
 *
 * This function configures an AOI module product terms for a specific event. The user has
 * to select the event and the product term which is configured and fill the
 * AoiProductTermConfig configuration structure.
 *
 * Example:
   @code

    aoi_product_term_config_t productTermConfigStruct;
    aoi_status_t status;

    productTermConfigStruct.PTAC = kAoiConfigLogicZero;
    productTermConfigStruct.PTBC = kAoiConfigInputSignal;
    productTermConfigStruct.PTCC = kAoiConfigInvInputSignal;
    productTermConfigStruct.PTDC = kAoiConfigLogicOne;

    // Configure product term 1 of event 3
    status = AOI_DRV_ConfigProductTermLogic(0, 3, kAoiTerm1, &productTermConfigStruct);
    switch (status)
    {
        //...
    }
   @endcode
 *
 * @param   instance The instance number of the AOI peripheral
 * @param   event Event which will be configured of type aoi_event_index_t.
 * @param   productTerm Product term which will be configured of type aoi_product_term_t.
 * @param   productTermConfigPtr Pointer to type aoi_product_term_config_t structure.
 * The user is responsible to fill out the members of this structure and pass the pointer
 * to this function.
 * @return  An error code or kStatus_AOI_Success.
 */
aoi_status_t AOI_DRV_ConfigProductTermLogic(uint32_t instance,
                                            aoi_event_index_t event,
                                            aoi_product_term_t productTerm,
                                            const aoi_product_term_config_t * productTermConfigPtr);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_FEATURE_SOC_AOI_COUNT */
#endif /* __FSL_AOI_DRIVER_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/

