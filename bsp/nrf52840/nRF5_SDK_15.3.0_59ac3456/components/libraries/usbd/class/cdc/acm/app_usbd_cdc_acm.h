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
#ifndef APP_USBD_CDC_ACM_H__
#define APP_USBD_CDC_ACM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "nrf_drv_usbd.h"
#include "app_usbd_class_base.h"
#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_descriptor.h"

#include "app_usbd_cdc_desc.h"
#include "app_usbd_cdc_types.h"
#include "app_usbd_cdc_acm_internal.h"

/**
 * @defgroup app_usbd_cdc_acm USB CDC ACM class
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 Module with types, definitions and API used by CDC ACM class.
 *
 * @details References:
 * - "Universal Serial Bus Class Definitions for Communications Devices"
 *      Revision 1.2, November 3, 2010
 * - "Universal Serial Bus Communications Class Subclass Specification for PSTN Devices"
 *      Revision 1.2, February 9, 2007
 *
 * @{
 */

#ifdef DOXYGEN
/**
 * @brief CDC ACM class instance type.
 *
 * @ref APP_USBD_CLASS_TYPEDEF
 */
typedef struct { } app_usbd_cdc_acm_t;
#else
/*lint -save -e10 -e26 -e123 -e505 */
APP_USBD_CLASS_TYPEDEF(app_usbd_cdc_acm,            \
            APP_USBD_CDC_ACM_CONFIG(0, 0, 0, 0, 0), \
            APP_USBD_CDC_ACM_INSTANCE_SPECIFIC_DEC, \
            APP_USBD_CDC_ACM_DATA_SPECIFIC_DEC      \
);
/*lint -restore*/
#endif


/*lint -save -e407 */

/**
 * @brief Events passed to user event handler.
 *
 * @note Example prototype of user event handler:
 *
 * @code
   void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                              app_usbd_cdc_acm_user_event_t   event);
 * @endcode
 */
typedef enum app_usbd_cdc_acm_user_event_e {
    APP_USBD_CDC_ACM_USER_EVT_RX_DONE,     /**< User event RX_DONE.    */
    APP_USBD_CDC_ACM_USER_EVT_TX_DONE,     /**< User event TX_DONE.    */

    APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN,   /**< User event PORT_OPEN.  */
    APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE,  /**< User event PORT_CLOSE. */
} app_usbd_cdc_acm_user_event_t;

/*lint -restore*/

/**
 * @brief Default CDC ACM descriptors.
 *
 * @param comm_interface COMM interface number.
 * @param comm_epin      COMM interface IN endpoint.
 * @param data_interface DATA interface number.
 * @param data_epin      DATA interface IN endpoint.
 * @param data_epout     DATA interface OUT endpoint.
 */
#define APP_USBD_CDC_ACM_DEFAULT_DESC(comm_interface,                       \
                                      comm_epin,                            \
                                      data_interface,                       \
                                      data_epin,                            \
                                      data_epout)                           \
    APP_USBD_CDC_IAD_DSC(comm_interface,                                    \
                         APP_USBD_CDC_SUBCLASS_ACM,                         \
                         APP_USBD_CDC_COMM_PROTOCOL_AT_V250)                \
    APP_USBD_CDC_COMM_INTERFACE_DSC(comm_interface,                         \
                                    APP_USBD_CDC_SUBCLASS_ACM,              \
                                    APP_USBD_CDC_COMM_PROTOCOL_AT_V250)     \
        APP_USBD_CDC_HEADER_DSC(0x0110)                                     \
        APP_USBD_CDC_CALL_MGMT_DSC(0x03, data_interface)                    \
        APP_USBD_CDC_ACM_DSC(0x02)                                          \
        APP_USBD_CDC_UNION_DSC(comm_interface, data_interface)              \
        APP_USBD_CDC_COM_EP_DSC(comm_epin, NRF_DRV_USBD_EPSIZE)             \
    APP_USBD_CDC_DATA_INTERFACE_DSC(data_interface, 0, 0)                   \
        APP_USBD_CDC_DATA_EP_DSC(data_epin, data_epout, NRF_DRV_USBD_EPSIZE)

/**
 * @brief Global definition of app_usbd_cdc_acm_t class instance.
 *
 * @param instance_name             Name of global instance.
 * @param user_ev_handler           User event handler (optional).
 * @param comm_ifc                  Interface number of cdc_acm control.
 * @param data_ifc                  Interface number of cdc_acm DATA.
 * @param comm_ein                  COMM subclass IN endpoint.
 * @param data_ein                  DATA subclass IN endpoint.
 * @param data_eout                 DATA subclass OUT endpoint.
 * @param cdc_protocol              CDC protocol @ref app_usbd_cdc_comm_protocol_t
 *
 * @note This macro is just simplified version of @ref APP_USBD_CDC_ACM_GLOBAL_DEF_INTERNAL.
 *
 */
#define APP_USBD_CDC_ACM_GLOBAL_DEF(instance_name,                              \
                                    user_ev_handler,                            \
                                    comm_ifc,                                   \
                                    data_ifc,                                   \
                                    comm_ein,                                   \
                                    data_ein,                                   \
                                    data_eout,                                  \
                                    cdc_protocol)                               \
    APP_USBD_CDC_ACM_GLOBAL_DEF_INTERNAL(instance_name,                         \
                                         user_ev_handler,                       \
                                         comm_ifc,                              \
                                         data_ifc,                              \
                                         comm_ein,                              \
                                         data_ein,                              \
                                         data_eout,                             \
                                         cdc_protocol)                          \

/**
 * @brief Helper function to get class instance from CDC ACM class.
 *
 * @param[in] p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 *
 * @return Base class instance.
 */
static inline app_usbd_class_inst_t const *
app_usbd_cdc_acm_class_inst_get(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    return &p_cdc_acm->base;
}

/**
 * @brief Helper function to get cdc_acm specific request from cdc_acm class.
 *
 * @param[in] p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 *
 * @return CDC ACM class specific request.
 */
static inline app_usbd_cdc_acm_req_t *
app_usbd_cdc_acm_class_request_get(app_usbd_cdc_acm_t const * p_cdc_acm)
{
    return &p_cdc_acm->specific.p_data->ctx.request;
}

/**
 * @brief Helper function to get cdc_acm from base class instance.
 *
 * @param[in] p_inst Base class instance.
 *
 * @return CDC ACM class handle.
 */
static inline app_usbd_cdc_acm_t const *
app_usbd_cdc_acm_class_get(app_usbd_class_inst_t const * p_inst)
{
    return (app_usbd_cdc_acm_t const *)p_inst;
}


/**
 * @brief Writes data to CDC ACM serial port.
 *
 * This is asynchronous call. User should wait for @ref APP_USBD_CDC_ACM_USER_EVT_TX_DONE event
 * to be sure that all data has been sent and input buffer could be accessed again.
 *
 * @param[in] p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 * @param[in] p_buf     Input buffer.
 * @param[in] length    Input buffer length.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_cdc_acm_write(app_usbd_cdc_acm_t const * p_cdc_acm,
                                  const void *               p_buf,
                                  size_t                     length);

/**
 * @brief Returns the amount of data that was read.
 *
 * This function should be used on @ref APP_USBD_CDC_ACM_USER_EVT_RX_DONE event to get
 * information how many bytes have been transfered into user buffer.
 *
 * @param[in] p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 *
 * @return Amount of data transfered.
 */
size_t app_usbd_cdc_acm_rx_size(app_usbd_cdc_acm_t const * p_cdc_acm);

/**
 * @brief Returns the amount of data that was stored into internal buffer
 *
 * This function should be used on @ref APP_USBD_CDC_ACM_USER_EVT_RX_DONE event to get
 * information how many bytes are waiting in internal buffer.
 *
 * @param[in] p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 *
 * @return Amount of data waiting.
 */
size_t app_usbd_cdc_acm_bytes_stored(app_usbd_cdc_acm_t const * p_cdc_acm);

/**
 * @brief Reads data from CDC ACM serial port.
 *
 * This function uses internal buffer and double buffering for continuous transmission.
 *
 * If there is enough data in internal buffer to fill user buffer, NRF_SUCCESS is
 * returned and data is immediately available in the user buffer.
 *
 * If not, up to two user buffers can be scheduled, function returns NRF_ERROR_IO_PENDING
 * when first buffer is filled and @ref APP_USBD_CDC_ACM_USER_EVT_RX_DONE event is generated.
 *
 * @sa app_usbd_cdc_acm_read_any
 * @sa app_usbd_cdc_acm_rx_size
 *
 * @param[in]  p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 * @param[out] p_buf     Output buffer.
 * @param[in]  length    Number of bytes to read.
 *
 * @retval NRF_SUCCESS          Data is stored into user buffer.
 * @retval NRF_ERROR_IO_PENDING Awaiting transmission, when data is stored into user buffer,
 *                              @ref APP_USBD_CDC_ACM_USER_EVT_RX_DONE event will be raised.
 * @retval NRF_ERROR_BUSY       There are already 2 buffers queued for transfers.
 * @retval other                Standard error code.
 */
ret_code_t app_usbd_cdc_acm_read(app_usbd_cdc_acm_t const * p_cdc_acm,
                                 void *                     p_buf,
                                 size_t                     length);

/**
 * @brief Read any data from CDC ACM port up to given buffer size
 *
 * This function is very similar to the @ref app_usbd_cdc_acm_read but it returns
 * data as quick as any data is available, even if the given buffer was not totally full.
 *
 * @note This function cannot use double buffering.
 * @note To check the number of bytes really read use @ref app_usbd_cdc_acm_rx_size
 * function.
 *
 * @sa app_usbd_cdc_acm_read
 * @sa app_usbd_cdc_acm_rx_size
 *
 * @param p_cdc_acm CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 * @param[out] p_buf     Output buffer.
 * @param[in]  length    Maximum number of bytes to read.
 *
 * @retval NRF_SUCCESS          Data is stored into user buffer.
 * @retval NRF_ERROR_IO_PENDING Awaiting transmission, when data is stored into user buffer,
 *                              @ref APP_USBD_CDC_ACM_USER_EVT_RX_DONE event will be raised.
 * @retval NRF_ERROR_BUSY       There is already buffer set for a transfer.
 * @retval other                Standard error code.
 */
ret_code_t app_usbd_cdc_acm_read_any(app_usbd_cdc_acm_t const * p_cdc_acm,
                                     void *                     p_buf,
                                     size_t                     length);

/**
 * @brief Serial state notifications.
 * */
typedef enum {
    APP_USBD_CDC_ACM_SERIAL_STATE_DCD     = (1u << 0), /**< Notification bit DCD.    */
    APP_USBD_CDC_ACM_SERIAL_STATE_DSR     = (1u << 1), /**< Notification bit DSR.    */
    APP_USBD_CDC_ACM_SERIAL_STATE_BREAK   = (1u << 2), /**< Notification bit BREAK.  */
    APP_USBD_CDC_ACM_SERIAL_STATE_RING    = (1u << 3), /**< Notification bit RING.   */
    APP_USBD_CDC_ACM_SERIAL_STATE_FRAMING = (1u << 4), /**< Notification bit FRAMING.*/
    APP_USBD_CDC_ACM_SERIAL_STATE_PARITY  = (1u << 5), /**< Notification bit PARITY. */
    APP_USBD_CDC_ACM_SERIAL_STATE_OVERRUN = (1u << 6), /**< Notification bit OVERRUN.*/
} app_usbd_cdc_acm_serial_state_t;

/**
 * @brief Serial line state.
 */
typedef enum {
    APP_USBD_CDC_ACM_LINE_STATE_DTR = (1u << 0),  /**< Line state bit DTR.*/
    APP_USBD_CDC_ACM_LINE_STATE_RTS = (1u << 1),  /**< Line state bit RTS.*/
} app_usbd_cdc_acm_line_state_t;

/**
 * @brief Serial state notification via IN interrupt endpoint.
 *
 * @param[in] p_cdc_acm     CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 * @param[in] serial_state  Serial state notification type.
 * @param[in] value         Serial state value.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_cdc_acm_serial_state_notify(app_usbd_cdc_acm_t const *      p_cdc_acm,
                                                app_usbd_cdc_acm_serial_state_t serial_state,
                                                bool                            value);

/**
 * @brief Control line value get.
 *
 * @param[in]  p_cdc_acm   CDC ACM class instance (defined by @ref APP_USBD_CDC_ACM_GLOBAL_DEF).
 * @param[in]  line_state  Line control value type.
 * @param[out] value       Line control value.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_cdc_acm_line_state_get(app_usbd_cdc_acm_t const *    p_cdc_acm,
                                           app_usbd_cdc_acm_line_state_t line_state,
                                           uint32_t *                    value);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_CDC_ACM_H__ */
