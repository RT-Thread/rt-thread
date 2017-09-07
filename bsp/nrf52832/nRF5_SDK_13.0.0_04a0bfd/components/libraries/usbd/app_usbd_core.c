/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#include "sdk_config.h"
#if APP_USBD_ENABLED
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_request.h"
#include "app_usbd_string_desc.h"
#include "nrf.h"
#include "nrf_atomic.h"
#include "app_util_platform.h"
#include "app_usbd.h"
#include "app_usbd_class_base.h"

/* Test if VID was configured */
#ifndef APP_USBD_VID
#error APP_USBD_VID not properly defined.
#endif

/* USBD device version creating if defined in major/minor form */
#ifndef APP_USBD_DEVICE_VER
    #if defined(APP_USBD_DEVICE_VER_MAJOR) && defined(APP_USBD_DEVICE_VER_MINOR)
        #if ((APP_USBD_DEVICE_VER_MAJOR)) > 99 || ((APP_USBD_DEVICE_VER_MINOR) > 99)
            #error Major and minor device version value have to be limited to 99.
        #endif
        #define APP_USBD_DEVICE_VER (((APP_USBD_DEVICE_VER_MAJOR)*100UL) + (APP_USBD_DEVICE_VER_MINOR))
    #else
        #error The definition of APP_USBD_DEVICE_VER or a pair APP_USBD_DEVICE_VER_MAJOR and APP_USBD_DEVICE_VER_MINOR required.
    #endif
#endif

/**
 * @internal
 * @defgroup app_usbd_core_internals USB Device high level library core module internals
 * @ingroup app_usbd_core
 *
 * Internal variables, auxiliary macros and functions of USBD high level core module.
 * @{
 */

/** @brief Make USB BCD version */
#define APP_USBD_VERSION_BCD_MAKE(major, minor) (((0x##major) << 8) | (0x##minor))

/** @brief Make USB power value */
#define APP_USBD_POWER_MAKE(ma) (((ma) + 1) / 2)

/** @brief Convert device version to BCD notation */
#define APP_USBD_BCD_DEVICE (                             \
    ((((APP_USBD_DEVICE_VER) % 10000) / 1000) * 0x1000) + \
    ((((APP_USBD_DEVICE_VER) %  1000) /  100) *  0x100) + \
    ((((APP_USBD_DEVICE_VER) %  100) /    10) *   0x10) + \
    ((((APP_USBD_DEVICE_VER) %   10) /     1) *    0x1)   \
    )

/**
 @brief Default device descriptor initializer @ref app_usbd_descriptor_device_t
* */
#define APP_USBD_CORE_DEVICE_DESCRIPTOR  {                                                                      \
   .bLength = sizeof(app_usbd_descriptor_device_t),    /* descriptor size */                                    \
   .bDescriptorType = APP_USBD_DESCRIPTOR_DEVICE,      /* descriptor type */                                    \
   .bcdUSB = APP_USBD_VERSION_BCD_MAKE(2,0),           /* USB BCD version: 2.0 */                               \
   .bDeviceClass = 0,                                  /* device class: 0 - specified by interface */           \
   .bDeviceSubClass = 0,                               /* device subclass: 0 - specified by interface */        \
   .bDeviceProtocol = 0,                               /* device protocol: 0 - specified by interface */        \
   .bMaxPacketSize0 = NRF_DRV_USBD_EPSIZE,             /* endpoint size: fixed to: NRF_DRV_USBD_EPSIZE*/        \
   .idVendor = APP_USBD_VID,                           /* Vendor ID*/                                           \
   .idProduct = APP_USBD_PID,                          /* Product ID*/                                          \
   .bcdDevice = APP_USBD_BCD_DEVICE,                   /* Device version BCD */                                 \
   .iManufacturer = APP_USBD_STRING_ID_MANUFACTURER,   /* String ID: manufacturer */                            \
   .iProduct = APP_USBD_STRING_ID_PRODUCT,             /* String ID: product */                                 \
   .iSerialNumber = APP_USBD_STRING_ID_SERIAL,         /* String ID: serial */                                  \
   .bNumConfigurations = 1,                            /* Fixed value: only one configuration supported*/       \
}


#define APP_USBD_CORE_CONFIGURATION_DESCRIPTOR {                                        \
    .bLength = sizeof(app_usbd_descriptor_configuration_t),                             \
    .bDescriptorType = APP_USBD_DESCRIPTOR_CONFIGURATION,                               \
    .wTotalLength = 0,          /*Calculated dynamically*/                              \
    .bNumInterfaces = 0,        /*Calculated dynamically*/                              \
    .bConfigurationValue = 1,   /*Value passed to set configuration*/                   \
    .iConfiguration = 0,        /*Configuration ID: fixed to 0*/                        \
    .bmAttributes = APP_USBD_DESCRIPTOR_CONFIGURATION_ATTRIBUTE_ALWAYS_SET_MASK |       \
                    APP_USBD_DESCRIPTOR_CONFIGURATION_ATTRIBUTE_SELF_POWERED_MASK,      \
    .bMaxPower = APP_USBD_POWER_MAKE(500),                                              \
}

/**
 * @brief Device descriptor instance.
 *
 * @note
 * Constant part of the device descriptor.
 * Values that must be calculated are updated directly in the buffer
 * just before the transmission.
 */
static const app_usbd_descriptor_device_t m_device_dsc =
    APP_USBD_CORE_DEVICE_DESCRIPTOR;

/**
 * @brief Configuration descriptor instance.
 *
 * @note
 * Constant part of the device descriptor.
 * Values that must be calculated are updated directly in the buffer
 * just before the transmission.
 */
static const app_usbd_descriptor_configuration_t m_configuration_dsc =
    APP_USBD_CORE_CONFIGURATION_DESCRIPTOR;

/* Required early declaration of event handler function */
static ret_code_t app_usbd_core_event_handler(app_usbd_class_inst_t const * const  p_inst,
                                              app_usbd_complex_evt_t const * const p_event);

/**
 * @brief Current USB device state
 *
 * This variable is updated automatically by core library.
 */
static app_usbd_state_t app_usbd_state = APP_USBD_STATE_Disabled;

/**
 * @brief Active device features
 *
 * @note Only @ref APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP is supported for device
 */
static uint8_t m_device_features_state;

/**
 * @brief Remote wake-up register/unregister
 *
 * Counter incremented when appended instance required remote wake-up functionality.
 * It should be decremented when the class is removed.
 * When this counter is not zero, remote wake-up functionality is activated inside core.
 */
static uint8_t m_rwu_counter;

/**
 * @brief Remote wake-up pending flag
 */
static nrf_atomic_flag_t m_rwu_pending;


/**
 * @brief Core class methods
 *
 * Base methods interface for core class.
 * This is quite specific class - it would be only connected into endpoint 0.
 * Not connected into instances list.
 */
static const app_usbd_class_methods_t m_core_methods = {
        .event_handler = app_usbd_core_event_handler,
        .get_descriptors = NULL,
};

/**
 * @brief Setup transfer buffer
 */
static uint8_t m_setup_transfer_buff[NRF_DRV_USBD_EPSIZE];


/**
 * @brief Handler for outgoing setup data
 *
 * @todo RK documentation
 */
static app_usbd_core_setup_data_handler_desc_t m_ep0_handler_desc;

#define APP_USBD_CORE_CLASS_INSTANCE_CONFIG ()


/*lint -u -save -e26 -e40 -e64 -e123 -e505 -e651*/

/**
 * @brief Core instance
 *
 * Create instance that would be connected into endpoints in USBD library.
 */
APP_USBD_CLASS_INST_GLOBAL_DEF(
    app_usbd_core_inst,
    app_usbd_core,
    &m_core_methods,
    APP_USBD_CORE_CLASS_CONFIGURATION,
    () );
/*lint -restore*/



/**
 * @brief Check current USBD power connection status
 *
 */
static inline bool usbd_core_power_is_detected(void)
{
    return 0 != ( (NRF_POWER->USBREGSTATUS) & POWER_USBREGSTATUS_VBUSDETECT_Msk);
}


/**
 * @brief Safely call EP0 handler
 *
 * Function calls EP0 handler only if its pointer is non-zero.
 *
 * @param status Status to send as a handler parameter.
 */
static inline ret_code_t usbd_core_ep0_handler_call_and_clear(nrf_drv_usbd_ep_status_t status)
{
    app_usbd_core_setup_data_handler_t handler = m_ep0_handler_desc.handler;
    if (NULL != handler)
    {
        m_ep0_handler_desc.handler = NULL;
        return handler(status, m_ep0_handler_desc.p_context);
    }

    return NRF_ERROR_NULL;
}

/**
 * @brief Check if EP0 handler is configured
 *
 * EP0 handler is configured is any instance that has processed SETUP command
 * expects some incoming / outgoing data.
 *
 * EP0 handler should be cleared automatically just before it is called
 * (see @ref usbd_core_ep0_handler_call_and_clear).
 * If instance requires more data - it has to setup EP0 handler once more time
 * (see @ref app_usbd_core_setup_data_handler_set).
 *
 * This function adds small layer of abstraction for checking if EP0 handler
 * is already configured.
 *
 * @retval true  EP0 handler is set
 * @retval false EP0 handler is cleared
 */
static inline bool usb_core_ep0_handler_check(void)
{
    return (NULL != m_ep0_handler_desc.handler);
}

/**
 * @brief Empty data handler
 *
 * Data handler used only to mark that there is requested data during SETUP.
 *
 * @return Always NRF_SUCCESS
 * @sa setup_empty_data_handler_desc
 */
static ret_code_t setup_data_handler_empty(nrf_drv_usbd_ep_status_t status, void * p_contex)
{
    UNUSED_PARAMETER(status);
    UNUSED_PARAMETER(p_contex);
    return NRF_SUCCESS;
}

/**
 * @brief
 *
 * @todo RK Documentation
 */
static app_usbd_core_setup_data_handler_desc_t const m_setup_data_handler_empty_desc =
{
    .handler = setup_data_handler_empty,
    .p_context = NULL
};

/**
 * @brief Structure used as a context for descriptor feeder
 *
 * Structure with all the data required to process instances to generate descriptor
 * data chunk.
 */
typedef struct
{
    app_usbd_class_inst_t const * p_cinst; //!< The class instance that is to be processed next.
    const uint8_t * p_desc;                //!< Pointer at current descriptor or NULL if finished.
                                           /**<
                                            * If we get NULL on transfer function enter it means that ZLP is required.
                                            * Or it is time to finish the transfer (depending on @c total_left).
                                            */
    size_t desc_left;                      //!< Number of bytes left in the current class descriptor to send
    size_t total_left;                     //!< Number of bytes left that was requested by the host
} app_usbd_core_descriptor_conf_feed_data_t;

/**
 * @brief Default data used by the feeder
 *
 *
 */
static app_usbd_core_descriptor_conf_feed_data_t m_descriptor_conf_feed_data;

/**
 * @brief Descriptor feeder
 *
 * Descriptor feeder is used as an callback function when descriptors are
 * transfered and buffer is ready for next data.
 * It prepares next chunk of data to be sent.
 *
 * @param p_next    See @ref nrf_drv_usbd_next_transfer_handler_t documentation.
 * @param p_context Pointer to @ref app_usbd_core_descriptor_feed_data_t data type.
 * @param ep_size   The size of the endpoint.
 *
 * @return See @ref nrf_drv_usbd_next_transfer_handler_t documentation.
 */
static bool usbd_descriptor_conf_feeder(
    nrf_drv_usbd_ep_transfer_t * p_next,
    void * p_context,
    size_t ep_size)
{
    bool continue_req = true;

    app_usbd_core_descriptor_conf_feed_data_t * p_data = p_context;
    if (NULL == p_data->p_desc)
    {
        /* ZLP */
        continue_req      = false;
        p_next->p_data.tx = NULL;
        p_next->size      = 0;
    }
    else
    {
        ASSERT(ep_size <= NRF_DRV_USBD_FEEDER_BUFFER_SIZE);
        uint8_t * p_tx_buff   = nrf_drv_usbd_feeder_buffer_get();
        size_t size = 0; /* Currently added number of bytes */
        size_t tx_size;  /* Number of bytes to send right now */

        /* Feeder function can use the USBD driver internal buffer */
        p_tx_buff = nrf_drv_usbd_feeder_buffer_get();

        tx_size = MIN(ep_size, p_data->total_left);
        while (0 != tx_size)
        {
            /* Process transfer */
            if (0 < p_data->desc_left)
            {
                size_t to_copy = MIN(tx_size, p_data->desc_left);
                memcpy(p_tx_buff+size, p_data->p_desc, to_copy);
                p_data->desc_left  -= to_copy;
                p_data->total_left -= to_copy;
                tx_size            -= to_copy;
                size               += to_copy;
                p_data->p_desc     += to_copy;
            }

            if (0 == p_data->total_left)
            {
                continue_req = false;
            }
            else if (0 == p_data->desc_left)
            {
                if (NULL == p_data->p_cinst)
                {
                    p_data->p_desc = NULL;
                    /* No more data - check if ZLP is required */
                    if (size > 0)
                    {
                        if (size < ep_size)
                        {
                            continue_req = false;
                        }
                    }
                    break;
                }
                else
                {
                    /* Prepare next descriptor */
                    p_data->p_desc =
                        p_data->p_cinst->p_class_methods->get_descriptors(
                            p_data->p_cinst,
                            &p_data->desc_left);
                    /* Get next descriptor */
                    p_data->p_cinst = app_usbd_class_next_get(p_data->p_cinst);
                }
            }
            else
            {
                /* Nothing to do */
            }
        }
        p_next->p_data.tx = p_tx_buff;
        p_next->size      = size;
    }
    return continue_req;
}

/**
 * @brief
 *
 * @todo RK Documentation
 */
static const nrf_drv_usbd_handler_desc_t usbd_descriptor_feeder_desc =
{
    .handler = { .feeder = usbd_descriptor_conf_feeder },
    .p_context = &m_descriptor_conf_feed_data
};

static ret_code_t setup_req_get_status(app_usbd_class_inst_t const * const p_inst,
                                       app_usbd_setup_evt_t const * const p_setup_ev)
{
    size_t max_size;
    uint8_t * p_trans_buff = app_usbd_core_setup_transfer_buff_get(&max_size);
    ASSERT(sizeof(uint16_t) <= max_size);

    memset(p_trans_buff, 0, sizeof(uint16_t));
    if (m_configuration_dsc.bmAttributes &
        APP_USBD_DESCRIPTOR_CONFIGURATION_ATTRIBUTE_SELF_POWERED_MASK)
    {
        SET_BIT(p_trans_buff[0], 0);
    }
    if (IS_SET(m_device_features_state, APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP))
    {
        SET_BIT(p_trans_buff[0], 1);
    }
    return app_usbd_core_setup_rsp(&(p_setup_ev->setup), p_trans_buff, sizeof(uint16_t));
}

static ret_code_t setup_req_get_descriptor(app_usbd_class_inst_t const * const p_inst,
                                           app_usbd_setup_evt_t const * const p_setup_ev)
{
    switch (p_setup_ev->setup.wValue.hb)
    {
        case APP_USBD_DESCRIPTOR_DEVICE:
        {
            return app_usbd_core_setup_rsp(&(p_setup_ev->setup),
                                           &m_device_dsc,
                                           sizeof(m_device_dsc));
        }
        case APP_USBD_DESCRIPTOR_CONFIGURATION:
        {
            /* The size equals the size of configuration descriptor and all classes descriptors */
            const size_t size = MIN(
                sizeof(app_usbd_descriptor_configuration_t),
                p_setup_ev->setup.wLength.w);
            size_t total_length = sizeof(app_usbd_descriptor_configuration_t);
            uint8_t iface_count = 0;

            /* Iterate over all registered classes count descriptors and total size */
            app_usbd_class_inst_t const * p_class;
            for (p_class = app_usbd_class_first_get(); p_class != NULL;
                 p_class = app_usbd_class_next_get(p_class))
            {
                ASSERT(NULL != (p_class->p_class_methods));
                ASSERT(NULL != (p_class->p_class_methods->get_descriptors));
                size_t dsc_size;
                const void * dsc = p_class->p_class_methods->get_descriptors(p_class, &dsc_size);
                UNUSED_VARIABLE(dsc);
                total_length += dsc_size;
                iface_count += app_usbd_class_iface_count_get(p_class);
            }

            /* Access transmission buffer */
            size_t max_size;
            app_usbd_descriptor_configuration_t * p_trans_buff = app_usbd_core_setup_transfer_buff_get(&max_size);
            /* Copy the configuration descriptor and update the fields that require it */
            ASSERT(size <= max_size);
            memcpy(p_trans_buff, &m_configuration_dsc, size);

            p_trans_buff->bNumInterfaces = iface_count;
            p_trans_buff->wTotalLength   = total_length;
            if (m_rwu_counter)
            {
                p_trans_buff->bmAttributes |=
                    APP_USBD_DESCRIPTOR_CONFIGURATION_ATTRIBUTE_REMOTE_WAKEUP_MASK;
            }

            m_descriptor_conf_feed_data.p_cinst    = app_usbd_class_first_get();
            m_descriptor_conf_feed_data.p_desc     = (void *)p_trans_buff;
            m_descriptor_conf_feed_data.desc_left  = size;
            m_descriptor_conf_feed_data.total_left = p_setup_ev->setup.wLength.w;

            /* Start first transfer */
            ret_code_t ret;
            CRITICAL_REGION_ENTER();

            ret = app_usbd_setup_data_handled_transfer(
                NRF_DRV_USBD_EPIN0,
                &usbd_descriptor_feeder_desc);

            if (NRF_SUCCESS == ret)
            {
                ret = app_usbd_core_setup_data_handler_set(
                    NRF_DRV_USBD_EPIN0,
                    &m_setup_data_handler_empty_desc);
            }
            CRITICAL_REGION_EXIT();

            return ret;
        }
        case APP_USBD_DESCRIPTOR_STRING:
        {
            app_usbd_string_desc_idx_t id =
                    (app_usbd_string_desc_idx_t)(p_setup_ev->setup.wValue.lb);
            uint16_t langid = p_setup_ev->setup.wIndex.w;
            uint16_t const * p_string_dsc = app_usbd_string_desc_get(id, langid);
            if (p_string_dsc == NULL)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            return app_usbd_core_setup_rsp(
                &p_setup_ev->setup,
                p_string_dsc,
                app_usbd_string_desc_length(p_string_dsc));
        }
        default:
            break;
    }


    return NRF_ERROR_NOT_SUPPORTED;
}

static ret_code_t setup_req_get_configuration(app_usbd_class_inst_t const * const p_inst,
                                             app_usbd_setup_evt_t const * const   p_setup_ev)
{
    size_t max_size;
    uint8_t * p_trans_buff = app_usbd_core_setup_transfer_buff_get(&max_size);
    if (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Configured)
    {
        p_trans_buff[0] = 1;
    }
    else if (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Addressed)
    {
        p_trans_buff[0] = 0;
    }
    else
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    return app_usbd_core_setup_rsp(&p_setup_ev->setup, p_trans_buff, sizeof(p_trans_buff[0]));
}

/**
 * @brief Internal SETUP standard IN request handler
 * @param[in] p_inst        Instance of the class
 * @param[in] p_setup_ev    Setup request
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_std_in(app_usbd_class_inst_t const * const p_inst,
                                   app_usbd_setup_evt_t const * const  p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_GET_STATUS:
        {
            return setup_req_get_status(p_inst, p_setup_ev);
        }
        case APP_USBD_SETUP_STDREQ_GET_DESCRIPTOR:
        {
            return setup_req_get_descriptor(p_inst, p_setup_ev);
        }
        case APP_USBD_SETUP_STDREQ_GET_CONFIGURATION:
        {
            return setup_req_get_configuration(p_inst, p_setup_ev);
        }
        default:
            /*Not supported*/
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}


static ret_code_t setup_req_std_set_configuration(app_usbd_class_inst_t const * const p_inst,
                                                  app_usbd_setup_evt_t const * const  p_setup_ev)
{
    if (!((app_usbd_state == APP_USBD_STATE_Configured) ||
          (app_usbd_state == APP_USBD_STATE_Addressed)))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    app_usbd_state_t new_state = app_usbd_state;

    if (p_setup_ev->setup.wValue.lb == 0)
    {
        new_state = APP_USBD_STATE_Addressed;
    }
    else if (p_setup_ev->setup.wValue.lb == 1)
    {
        new_state = APP_USBD_STATE_Configured;
        /*Clear all bulk/interrupt endpoint status and set toggle to DATA0*/

        app_usbd_class_inst_t const * p_inst_it = app_usbd_class_first_get();
        while (p_inst_it != NULL)
        {
            uint8_t iface_count = app_usbd_class_iface_count_get(p_inst_it);
            for (uint8_t i = 0; i < iface_count; ++i)
            {
                app_usbd_class_iface_conf_t const * p_iface;
                p_iface = app_usbd_class_iface_get(p_inst_it, i);
                uint8_t ep_count = app_usbd_class_iface_ep_count_get(p_iface);

                for (uint8_t j = 0; j < ep_count; ++j)
                {
                    /*Clear stall for every endpoint*/
                    app_usbd_class_ep_conf_t const * p_ep = app_usbd_class_iface_ep_get(p_iface, j);


                    if (nrf_usbd_dtoggle_get(p_ep->address) != NRF_USBD_DTOGGLE_DATA0)
                    {
                        nrf_usbd_dtoggle_set(p_ep->address, NRF_USBD_DTOGGLE_DATA0);
                    }

                    if (NRF_USBD_EPISO_CHECK(p_ep->address) == 0)
                    {
                        nrf_drv_usbd_ep_stall_clear(p_ep->address);
                    }

                }
            }
            p_inst_it = p_inst_it->p_data->p_next;
        }

    }
    else
    {
        /*In this driver only one configuration is supported.*/
        return NRF_ERROR_INVALID_PARAM;
    }



    if (app_usbd_state != new_state)
    {
        app_usbd_state = new_state;
        /** @todo RK A way to notify class that state was changed */
    }

    return NRF_SUCCESS;
}

/**
 * @brief Internal SETUP standard OUT request handler
 * @param[in] p_inst        Instance of the class
 * @param[in] p_setup_ev    Setup request
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_req_std_out(app_usbd_class_inst_t const * const p_inst,
                                    app_usbd_setup_evt_t const * const p_setup_ev)
{
    switch (p_setup_ev->setup.bmRequest)
    {
        case APP_USBD_SETUP_STDREQ_SET_ADDRESS:
        {
            if ((app_usbd_state != APP_USBD_STATE_Default)   &&
                (app_usbd_state != APP_USBD_STATE_Addressed) &&
                (app_usbd_state != APP_USBD_STATE_Configured))
            {
                return NRF_ERROR_INVALID_STATE;
            }

            app_usbd_state = APP_USBD_STATE_Addressed;
            return NRF_SUCCESS;
        }
        case APP_USBD_SETUP_STDREQ_SET_FEATURE:
        {
            if (p_setup_ev->setup.wValue.w != APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            SET_BIT(m_device_features_state, APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP);
            return NRF_SUCCESS;
        }
        case APP_USBD_SETUP_STDREQ_CLEAR_FEATURE:
        {
            if (p_setup_ev->setup.wValue.w != APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP)
            {
                return NRF_ERROR_NOT_SUPPORTED;
            }

            CLR_BIT(m_device_features_state, APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP);
            return NRF_SUCCESS;
        }
        case APP_USBD_SETUP_STDREQ_SET_CONFIGURATION:
        {
            return setup_req_std_set_configuration(p_inst, p_setup_ev);
        }
        case APP_USBD_SETUP_STDREQ_SET_DESCRIPTOR:
        {
            /*Not supported yet.*/
            break;
        }
        default:
            /*Not supported*/
            break;
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Internal SETUP event handler
 * @param[in] p_inst        Instance of the class
 * @param[in] p_setup_ev    Setup request
 * @return Standard error code
 * @retval NRF_SUCCESS if request handled correctly
 * @retval NRF_ERROR_NOT_SUPPORTED if request is not supported
 */
static ret_code_t setup_device_event_handler(app_usbd_class_inst_t const * const p_inst,
                                             app_usbd_setup_evt_t const * const  p_setup_ev)
{
    ASSERT(p_inst != NULL);
    ASSERT(p_setup_ev != NULL);

    if (app_usbd_setup_req_dir(p_setup_ev->setup.bmRequestType) == APP_USBD_SETUP_REQDIR_IN)
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_in(p_inst, p_setup_ev);
            default:
                break;
        }
    }
    else /*APP_USBD_SETUP_REQDIR_OUT*/
    {
        switch (app_usbd_setup_req_typ(p_setup_ev->setup.bmRequestType))
        {
            case APP_USBD_SETUP_REQTYPE_STD:
                return setup_req_std_out(p_inst, p_setup_ev);
            default:
                break;
        }
    }

    return NRF_ERROR_NOT_SUPPORTED;
}

/**
 * @brief Process SETUP command
 *
 * Auxiliary function for SETUP command processing
 */
static inline ret_code_t app_usbd_core_setup_req_handler(app_usbd_class_inst_t const * const p_inst,
                                                         nrf_drv_usbd_evt_t const * const p_event)
{
    app_usbd_setup_evt_t setup_ev;
    ret_code_t ret = NRF_ERROR_INTERNAL;         /* Final result of request processing function */

    /* This handler have to be cleared when SETUP is entered */
    // ASSERT(!usb_core_ep0_handler_check());

    setup_ev.type = APP_USBD_EVT_DRV_SETUP;
    nrf_drv_usbd_setup_get((nrf_drv_usbd_setup_t *)&(setup_ev.setup));

    switch (app_usbd_setup_req_rec(setup_ev.setup.bmRequestType))
    {
        case APP_USBD_SETUP_REQREC_DEVICE:
        {
            /* Endpoint 0 has core instance (that process device requests) connected */
            ret = setup_device_event_handler(p_inst, &setup_ev);

            app_usbd_setup_reqtype_t req_type =
                    app_usbd_setup_req_typ(setup_ev.setup.bmRequestType);
            if (ret == NRF_ERROR_NOT_SUPPORTED &&
                req_type == APP_USBD_SETUP_REQTYPE_VENDOR)
            {
                ret = app_usbd_all_until_served_call((app_usbd_complex_evt_t const *)&setup_ev);
            }

            break;
        }
        case APP_USBD_SETUP_REQREC_INTERFACE:
        {
            uint8_t iface_number = setup_ev.setup.wIndex.lb;
            ret = app_usbd_iface_call(iface_number, (app_usbd_complex_evt_t const *)&setup_ev);
            if (ret == NRF_SUCCESS || ret != NRF_ERROR_NOT_SUPPORTED)
            {
                break;
            }

            ret = app_usbd_interface_std_req_handle(&setup_ev);
            break;
        }
        case APP_USBD_SETUP_REQREC_ENDPOINT:
        {
            nrf_drv_usbd_ep_t ep = (nrf_drv_usbd_ep_t)setup_ev.setup.wIndex.lb;

            if ((ep == NRF_DRV_USBD_EPOUT0) || (ep == NRF_DRV_USBD_EPIN0))
            {
                ret = app_usbd_endpoint_std_req_handle(&setup_ev);
                break;
            }

            ret = app_usbd_ep_call(ep, (app_usbd_complex_evt_t const *)&setup_ev);
            if (ret == NRF_SUCCESS || ret != NRF_ERROR_NOT_SUPPORTED)
            {
                break;
            }

            ret = app_usbd_endpoint_std_req_handle(&setup_ev);
            break;
        }
        case APP_USBD_SETUP_REQREC_OTHER:
        {
            /* Try to process via every instance */
            ret = app_usbd_all_until_served_call((app_usbd_complex_evt_t *)&setup_ev);
            break;
        }
        default:
            break;
    }

    /* Processing result */
    if (ret == NRF_SUCCESS)
    {
        if (usb_core_ep0_handler_check())
        {
            /* Request processed successfully and requires SETUP data */
            nrf_drv_usbd_setup_data_clear();
        }
        else
        {
            /* Request processed successfully */
            nrf_drv_usbd_setup_clear();
        }
    }
    else
    {
        /* Request finished with error */
        nrf_drv_usbd_setup_stall();
    }
    return ret;
}

/**
 * @brief Event handler for core module
 *
 * The event handler that would process all events directed to device.
 *
 */
static ret_code_t app_usbd_core_event_handler(app_usbd_class_inst_t const * const p_inst,
                                              app_usbd_complex_evt_t const * const p_event)
{
    ret_code_t ret = NRF_ERROR_NOT_SUPPORTED;
    switch(p_event->type)
    {
        case APP_USBD_EVT_DRV_RESET:
        {
            app_usbd_state = APP_USBD_STATE_Default;
            break;
        }
        case APP_USBD_EVT_DRV_SUSPEND:
        {
            ASSERT(app_usbd_state >= APP_USBD_STATE_Unattached);
            app_usbd_state |= APP_USBD_STATE_SuspendedMask;
            ret = NRF_SUCCESS;
            break;
        }
        case APP_USBD_EVT_DRV_RESUME:
        {
            if (nrf_atomic_flag_clear_fetch(&m_rwu_pending) != 0)
            {
                nrf_usbd_task_trigger(NRF_USBD_TASK_NODRIVEDPDM);
            }

            ASSERT(APP_USB_STATE_BASE(app_usbd_state) >= APP_USBD_STATE_Unattached);
            app_usbd_state &= (app_usbd_state_t)(~APP_USBD_STATE_SuspendedMask);
            ret = NRF_SUCCESS;
            break;
        }
        case APP_USBD_EVT_DRV_SETUP:
        {
            ret = app_usbd_core_setup_req_handler(p_inst, &(p_event->drv_evt));
            break;
        }
        case APP_USBD_EVT_INST_APPEND:
        {
            ASSERT(app_usbd_state == APP_USBD_STATE_Disabled);
            app_usbd_state = APP_USBD_STATE_Unattached;
            ret = NRF_SUCCESS;
            break;
        }
        case APP_USBD_EVT_INST_REMOVE:
        {
            ASSERT(app_usbd_state == APP_USBD_STATE_Unattached);
            app_usbd_state = APP_USBD_STATE_Disabled;
            ret = NRF_SUCCESS;
            break;
        }
        case APP_USBD_EVT_START:
        {
            app_usbd_state = APP_USBD_STATE_Powered;
            if (usbd_core_power_is_detected())
            {
                app_usbd_state = APP_USBD_STATE_Default;
            }
            ret = NRF_SUCCESS;
            break;
        }
        case APP_USBD_EVT_STOP:
        {
            ASSERT(APP_USB_STATE_BASE(app_usbd_state) > APP_USBD_STATE_Powered);
            if (app_usbd_state & APP_USBD_STATE_SuspendedMask)
            {
                app_usbd_state = APP_USBD_STATE_SuspendedPowered;
            }
            else
            {
                app_usbd_state = APP_USBD_STATE_Powered;
            }
            ret = NRF_SUCCESS;
            break;
        }
        /* Data transfer on endpoint 0 */
        case APP_USBD_EVT_DRV_EPTRANSFER:
        {
            /* This EPTRANSFER event has to be called only for EP0 */
            ASSERT((p_event->drv_evt.data.eptransfer.ep == NRF_DRV_USBD_EPOUT0) ||
                   (p_event->drv_evt.data.eptransfer.ep == NRF_DRV_USBD_EPIN0));
            ret = usbd_core_ep0_handler_call_and_clear(p_event->drv_evt.data.eptransfer.status);
            /* Processing result */
            if(ret == NRF_SUCCESS)
            {
                if(usb_core_ep0_handler_check())
                {
                    /* Request processed successfully and requires SETUP data */
                    nrf_drv_usbd_setup_data_clear();
                }
                else
                {
                    /* Request processed successfully */
                    /* Clear setup only for a write transfer - for a read transfer,
                     * it is cleared inside the driver */
                    if(p_event->drv_evt.data.eptransfer.ep == NRF_DRV_USBD_EPOUT0)
                    {
                        nrf_drv_usbd_setup_clear();
                    }
                }
            }
            else
            {
                /* Request finished with error */
                nrf_drv_usbd_setup_stall();
            }
            break;
        }
        default:
            break;
    }

    return ret;
}

ret_code_t app_usbd_core_setup_rsp(app_usbd_setup_t const * p_setup,
                                   void const *             p_data,
                                   size_t                   size)
{
    size_t req_size = p_setup->wLength.w;
    size_t tx_size = MIN(req_size, size);
    bool zlp_required = (size < req_size) &&
                        (0 == (size % nrf_drv_usbd_ep_max_packet_size_get(NRF_DRV_USBD_EPIN0)));

    NRF_DRV_USBD_TRANSFER_IN_FLAGS(
        transfer,
        p_data,
        tx_size,
        zlp_required ? NRF_DRV_USBD_TRANSFER_ZLP_FLAG : 0);

    ret_code_t ret;
    CRITICAL_REGION_ENTER();
    ret = app_usbd_core_setup_data_transfer(NRF_DRV_USBD_EPIN0,
                                            &transfer);
    if (NRF_SUCCESS == ret)
    {
        ret = app_usbd_core_setup_data_handler_set(NRF_DRV_USBD_EPIN0,
                                                   &m_setup_data_handler_empty_desc);
    }
    CRITICAL_REGION_EXIT();

    return ret;
}

ret_code_t app_usbd_core_setup_data_handler_set(
        nrf_drv_usbd_ep_t ep,
        app_usbd_core_setup_data_handler_desc_t const * const p_handler_desc)
{
    if (nrf_drv_usbd_last_setup_dir_get() != ep)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    m_ep0_handler_desc = *p_handler_desc;
    return NRF_SUCCESS;
}

ret_code_t app_usbd_core_ep_transfer(
    nrf_drv_usbd_ep_t                                  ep,
    nrf_drv_usbd_transfer_t              const * const p_transfer)
{
    if (APP_USB_STATE_BASE(app_usbd_state) != APP_USBD_STATE_Configured)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_transfer(ep, p_transfer);
}

ret_code_t app_usbd_core_setup_data_transfer(
    nrf_drv_usbd_ep_t                                  ep,
    nrf_drv_usbd_transfer_t              const * const p_transfer)
{
    ASSERT(0 == NRF_USBD_EP_NR_GET(ep));

    if (!((APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Configured) ||
          (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Addressed ) ||
          (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Default   ) ))
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_transfer(ep, p_transfer);
}

ret_code_t app_usbd_ep_handled_transfer(
    nrf_drv_usbd_ep_t                         ep,
    nrf_drv_usbd_handler_desc_t const * const p_handler)
{
    if (APP_USB_STATE_BASE(app_usbd_state) != APP_USBD_STATE_Configured)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_handled_transfer(ep, p_handler);
}

ret_code_t app_usbd_setup_data_handled_transfer(
    nrf_drv_usbd_ep_t                         ep,
    nrf_drv_usbd_handler_desc_t const * const p_handler)
{
    ASSERT(0 == NRF_USBD_EP_NR_GET(ep));

    if (!((APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Configured) ||
          (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Addressed ) ||
          (APP_USB_STATE_BASE(app_usbd_state) == APP_USBD_STATE_Default   ) ))
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return nrf_drv_usbd_ep_handled_transfer(ep, p_handler);
}

void * app_usbd_core_setup_transfer_buff_get(size_t * p_size)
{
    if (p_size != NULL)
        *p_size = sizeof(m_setup_transfer_buff);

    return m_setup_transfer_buff;
}

app_usbd_state_t app_usbd_core_state_get(void)
{
    return app_usbd_state;
}

void app_usbd_core_class_rwu_register(app_usbd_class_inst_t const * const p_inst)
{
    ASSERT(p_inst != NULL);
    ++m_rwu_counter;
    /*Overflow check*/
    ASSERT(m_rwu_counter != 0);
}

void app_usbd_core_class_rwu_unregister(app_usbd_class_inst_t const * const p_inst)
{
    ASSERT(p_inst != NULL);
    /* Usage validation. If counter is 0 unregister is not possible.*/
    ASSERT(m_rwu_counter != 0);
    --m_rwu_counter;
}

void app_usbd_core_class_rwu_pend(void)
{
    if (m_rwu_counter == 0)
    {
        /* No class registered on remote wake-up */
        return;
    }

    if (IS_SET(m_device_features_state, APP_USBD_SETUP_STDFEATURE_DEVICE_REMOTE_WAKEUP) == 0)
    {
        /* Feature remote wake-up hasn't been set by host*/
        return;
    }

    if (nrf_atomic_flag_set_fetch(&m_rwu_pending) != 0)
    {
        /* Remote wake-up pending */
        return;
    }

    nrf_usbd_dpdmvalue_set(NRF_USBD_DPDMVALUE_RESUME);
    nrf_usbd_task_trigger(NRF_USBD_TASK_DRIVEDPDM);
}

/** @} */
#endif // APP_USBD_ENABLED
