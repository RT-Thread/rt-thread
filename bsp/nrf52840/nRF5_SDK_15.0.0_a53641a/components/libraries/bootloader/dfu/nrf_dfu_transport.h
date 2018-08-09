/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/**@file
 *
 * @defgroup sdk_nrf_dfu_transport DFU transport
 * @{
 * @ingroup  nrf_dfu
 * @brief Generic Device Firmware Update (DFU) transport interface.
 *
 * @details The DFU transport module defines a generic interface that must
 *          be implemented for each transport layer.
 */

#ifndef NRF_DFU_TRANSPORT_H__
#define NRF_DFU_TRANSPORT_H__

#include <stdint.h>
#include "nrf_section.h"
#include "nrf_dfu_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Forward declaration of nrf_dfu_transport_t */
typedef struct nrf_dfu_transport_s nrf_dfu_transport_t;

/** @brief  Function type for initializing a DFU transport.
 *
 * @details This function initializes a DFU transport. The implementation
 *          of the function must initialize DFU mode and stay in service
 *          until either the device is reset or the DFU operation is finalized.
 *          When the DFU transport receives requests, it should call @ref nrf_dfu_req_handler_on_req for handling the requests.
 *
 * @param observer          Function for receiving DFU transport notifications.
 *
 * @retval  NRF_SUCCESS     If initialization was successful for the transport. Any other return code indicates that the DFU transport could not be initialized.
 */
typedef uint32_t (*nrf_dfu_init_fn_t)(nrf_dfu_observer_t observer);


/** @brief  Function type for closing down a DFU transport.
 *
 * @details This function closes down a DFU transport in a gentle way.
 *
 * @param[in] p_exception    If exception matches current transport closing should be omitted.
 *
 * @retval    NRF_SUCCESS    If closing was successful for the transport. Any other return code indicates that the DFU transport could not be closed closed down.
 */
typedef uint32_t (*nrf_dfu_close_fn_t)(nrf_dfu_transport_t const * p_exception);



/** @brief DFU transport registration.
 *
 * @details     Every DFU transport must provide a registration of the initialization function.
 */
struct nrf_dfu_transport_s
{
    nrf_dfu_init_fn_t              init_func;          /**< Registration of the init function to run to initialize a DFU transport. */
    nrf_dfu_close_fn_t             close_func;         /**< Registration of the close function to close down a DFU transport. */
};


/** @brief Function for initializing all the registered DFU transports.
 *
 * @retval  NRF_SUCCESS     If all DFU transport were initialized successfully.
 *                          Any other error code indicates that at least one DFU
 *                          transport could not be initialized.
 */
uint32_t nrf_dfu_transports_init(nrf_dfu_observer_t observer);

/** @brief Function for closing down all (with optional exception) the registered DFU transports.
 *
 * @param[in] p_exception   Transport which should not be closed. NULL if all transports should be closed.
 * @retval    NRF_SUCCESS   If all DFU transport were closed down successfully.
 *                          Any other error code indicates that at least one DFU
 *                          transport could not be closed down.
 */
uint32_t nrf_dfu_transports_close(nrf_dfu_transport_t const * p_exception);


/** @brief  Macro for registering a DFU transport by using section variables.
 *
 * @details     This macro places a variable in a section named "dfu_trans", which
 *              is initialized by @ref nrf_dfu_transports_init.
 */
#define DFU_TRANSPORT_REGISTER(trans_var) NRF_SECTION_ITEM_REGISTER(dfu_trans, trans_var)


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_TRANSPORT_H__

/** @} */
