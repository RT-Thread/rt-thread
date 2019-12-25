/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#ifndef APP_USBD_CORE_H__
#define APP_USBD_CORE_H__

#include <stdint.h>

#include "sdk_common.h"
#include "nrf_drv_usbd.h"
#include "app_usbd_types.h"
#include "app_usbd_class_base.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup app_usbd_core USB Device high level library core module
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 Core module that manages current USB state and process device requests.
 * @{
 */

/**
 * @brief Core interface configuration.
 *
 * Core instance would have 2 endpoints (IN0 and OUT0).
 * The interface number does not matter because it is not used.
 */
#define APP_USBD_CORE_CLASS_CONFIGURATION ((0, NRF_DRV_USBD_EPOUT0, NRF_DRV_USBD_EPIN0))

/**
 * @brief USB Device state.
 *
 * Possible USB Device states according to specification.
 */
typedef enum
{
    APP_USBD_STATE_Disabled  , /**< The whole USBD library is disabled */
    APP_USBD_STATE_Unattached, /**< Device is currently not connected to the host */
    APP_USBD_STATE_Powered   , /**< Device is connected to the host but has not been enumerated */
    APP_USBD_STATE_Default   , /**< USB Reset condition detected, waiting for the address */
    APP_USBD_STATE_Addressed , /**< Device has been addressed but has not been configured */
    APP_USBD_STATE_Configured, /**< Device is addressed and configured */
}app_usbd_state_t;

/**
 * @brief EP0 handler function pointer.
 *
 * Type of the variable that would hold the pointer to the handler for
 * endpoint 0 messages processing.
 *
 * @param p_contex Context variable configured with the transmission request.
 */
typedef ret_code_t (*app_usbd_core_setup_data_handler_t)(nrf_drv_usbd_ep_status_t status,
                                                         void * p_context);

/**
 * @brief Variable type used to register EP0 transfer handler.
 *
 * EP0 messages are processed by core instance.
 * Another class can register itself to receive messages from EP0 when requesting
 * for Setup data transfer.
 */
typedef struct
{
    app_usbd_core_setup_data_handler_t   handler;   //!< Event handler to be called when transmission is ready
    void                               * p_context; //!< Context pointer to be send to every called event.
} app_usbd_core_setup_data_handler_desc_t;

/*lint -save -e10 -e26 -e93 -e123 -e505 */
/**
 * @brief Declare Core instance type.
 *
 * USBD core instance type definition.
 */
APP_USBD_CLASS_TYPEDEF(app_usbd_core,
        APP_USBD_CORE_CLASS_CONFIGURATION,
        APP_USBD_CLASS_INSTANCE_SPECIFIC_DEC_NONE,
        APP_USBD_CLASS_DATA_SPECIFIC_DEC_NONE);
/*lint -restore*/

/**
 * @brief Access to core instance.
 *
 * Function that returns pointer to the USBD core instance.
 *
 * @return pointer to the core instance.
 */
static inline app_usbd_class_inst_t const * app_usbd_core_instance_access(void)
{
    extern const APP_USBD_CLASS_INSTANCE_TYPE(app_usbd_core) app_usbd_core_inst;
    return (app_usbd_class_inst_t const *)&app_usbd_core_inst;
}

/**
 * @brief Enable endpoint 0
 *
 * Function enables endpoint OUT0 and IN0.
 * This makes the USB respond to SETUP transfers.
 */
void app_usbd_core_ep0_enable(void);

/**
 * @brief Disable endpoint 0
 *
 * Function disables endpoint OUT0 and IN0.
 * This makes the USB ignore SETUP transfers.
 */
void app_usbd_core_ep0_disable(void);

/**
 * @brief Default simple response to setup command.
 *
 * This function generates default simple response.
 * It sends ZLP when required and on takes care on allowing status stage when
 * transfer is finished.
 *
 * @param p_setup Pointer to original setup message.
 * @param p_data  Pointer to the response. This has to be globaly aviable data.
 * @param size    Total size of the answer - The function takes care about
 *                limiting the size of transfered data to the size required
 *                by setup command.
 */
ret_code_t app_usbd_core_setup_rsp(app_usbd_setup_t const * p_setup,
                                   void const *             p_data,
                                   size_t                   size);

/**
 * @brief Configure the handler for the nearest setup data endpoint transfer.
 *
 * This function would be called on incomming setup data.
 * The correct place to set the handler for a data is when SETUP command
 * was received.
 *
 * @param ep             Endpoint number (only IN0 and OUT0 are supported).
 * @param p_handler_desc Descriptor of the handler to be called.
 *
 * @retval NRF_SUCCESS            Successfully configured.
 * @retval NRF_ERROR_INVALID_ADDR Last received setup direction does not match
 *                                configured endpoint.
 */
ret_code_t app_usbd_core_setup_data_handler_set(
    nrf_drv_usbd_ep_t ep,
    app_usbd_core_setup_data_handler_desc_t const * const p_handler_desc);

/**
 * @brief Set up a data transfer buffer.
 *
 * Returns special internal buffer that can be used in setup transfer.
 * @return Internal buffer pointer.
 */
void * app_usbd_core_setup_transfer_buff_get(size_t * p_size);


/**@brief Return internal USBD core state.
 *
 * @return Check @ref app_usbd_state_t to find possible USBD core states.
 */
app_usbd_state_t app_usbd_core_state_get(void);


/**
 * @brief Check current feature state.
 *
 * Function checks the state of the selected feature that was configured by the host.
 *
 * @param feature Feature to check. @ref app_usbd_setup_stdfeature_t
 *                Only features related to the device should be checked by this function.
 *
 * @retval true  Selected feature is set.
 * @retval false Selected feature is cleared.
 */
bool app_usbd_core_feature_state_get(app_usbd_setup_stdfeature_t feature);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_CORE_H__ */
