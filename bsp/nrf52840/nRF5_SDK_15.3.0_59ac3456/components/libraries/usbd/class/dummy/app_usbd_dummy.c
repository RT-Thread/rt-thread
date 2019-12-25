/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(APP_USBD_DUMMY)

#include <string.h>
#include <ctype.h>
#include "app_usbd.h"
#include "app_usbd_dummy.h"
#include "app_usbd_string_desc.h"
#include "nrf_gpio.h"

/**
 * @defgroup app_usbd_dummy_internal USBD Dummy internals
 * @{
 * @ingroup app_usbd_dummy
 * @internal
 */

#define NRF_LOG_MODULE_NAME usbd_dummy

#if APP_USBD_DUMMY_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       APP_USBD_DUMMY_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  APP_USBD_DUMMY_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR APP_USBD_DUMMY_CONFIG_DEBUG_COLOR
#else //APP_USBD_DUMMY_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //APP_USBD_DUMMY_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/** @brief @ref app_usbd_class_methods_t::event_handler */
static ret_code_t dummy_class_event_handler(app_usbd_class_inst_t const *  p_inst,
                                            app_usbd_complex_evt_t const * p_event)
{
    if((p_event->app_evt.type  == APP_USBD_EVT_INST_APPEND) || 
       (p_event->app_evt.type  == APP_USBD_EVT_INST_REMOVE))
    {
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
}

/** @brief @ref app_usbd_class_methods_t::feed_descriptors */
static bool dummy_class_feed_descriptors(app_usbd_class_descriptor_ctx_t * p_ctx,
                                         app_usbd_class_inst_t const     * p_inst,
                                         uint8_t                         * p_buff,
                                         size_t                            max_size)
{
    static app_usbd_class_iface_conf_t const * p_cur_iface = 0;
    p_cur_iface = app_usbd_class_iface_get(p_inst, 0);

    APP_USBD_CLASS_DESCRIPTOR_BEGIN(p_ctx, p_buff, max_size)

    /* INTERFACE DESCRIPTOR */
    APP_USBD_CLASS_DESCRIPTOR_WRITE(sizeof(app_usbd_descriptor_iface_t)); // bLength
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DESCRIPTOR_INTERFACE); // bDescriptorType
    APP_USBD_CLASS_DESCRIPTOR_WRITE(app_usbd_class_iface_number_get(p_cur_iface)); // bInterfaceNumber
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // bAlternateSetting
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0); // bNumEndpoints
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DUMMY_CLASS); // bInterfaceClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DUMMY_SUBCLASS); // bInterfaceSubClass
    APP_USBD_CLASS_DESCRIPTOR_WRITE(APP_USBD_DUMMY_PROTOCOL); // bInterfaceProtocol
    APP_USBD_CLASS_DESCRIPTOR_WRITE(0x00); // iInterface

    APP_USBD_CLASS_DESCRIPTOR_END();
}

const app_usbd_class_methods_t app_usbd_dummy_class_methods = {
    .event_handler    = dummy_class_event_handler,
    .feed_descriptors = dummy_class_feed_descriptors,
};


#endif //NRF_MODULE_ENABLED(APP_USBD_DUMMY)
