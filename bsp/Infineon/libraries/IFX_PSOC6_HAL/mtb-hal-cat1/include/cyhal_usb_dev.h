/***************************************************************************//**
* \file cyhal_usb_dev.h
*
* \brief
* Provides a high level interface for interacting with the Infineon USB Device.
* This interface abstracts out the chip specific details.
* If any chip specific functionality is necessary, or performance is critical
* the low level functions can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_usb_dev USB Device
* \ingroup group_hal
* \{
* High level interface for interacting with the USB Device.
*
* This block supports one control endpoint (EP0) and one or more data endpoints.
* See the device datasheet for the number of data endpoints supported.
*
* Four transfer types are supported (see \ref cyhal_usb_dev_ep_type_t):
* * Bulk
* * Interrupt
* * Isochronous
* * Control
*
* \section section_usb_dev_features Features
* * Complies with USB specification 2.0
* * Supports full-speed peripheral device operation with a signaling bit rate of 12 Mbps.
* * Configurable D+ AND D- pins  using \ref cyhal_gpio_t
* * Configurable Interrupt and Callback assignment on USB events like SOF, Bus Reset, EP0 Setup and EP0 transaction.
* * Configurable USB device address.
* * Configurable USB Endpoints (except for Endpoint 0)
*
* \section section_usb_dev_quickstart Quick Start
* \ref cyhal_usb_dev_init can be used for initialization of USB by providing the USBDP and USBDM pins.
* See \ref subsection_usb_dev_snippet_1 for the initialization code snippet.
*
* \section section_usb_dev_snippets Code snippets
*
* \subsection subsection_usb_dev_snippet_1 Snippet 1: USB Device Initialization
* The following section initializes the USB Device and assigns the USBDM and USBDP pins using
* \ref cyhal_usb_dev_init. The clock parameter <b>clk</b> is optional and need not be provided (NULL),
* to generate and use an available clock resource with a default frequency. The device can be made
* physically visible to the USB Host by using \ref cyhal_usb_dev_connect
*
* \snippet hal_usb_dev.c snippet_cyhal_usb_dev_init
*
*
* \subsection subsection_usb_dev_snippet_2 Snippet 2: Handling USB Event Completion
* USB events (see \ref cyhal_usb_dev_event_t) like Bus Reset, EP0 transaction, EP0 Setup can be mapped to an interrupt and assigned
* a callback function. The callback function needs to be first registered using
* \ref cyhal_usb_dev_register_event_callback. Use different callback functions to handle events individually.
*
* \snippet hal_usb_dev.c snippet_cyhal_usb_dev_event
*
*
* \subsection subsection_usb_dev_snippet_3 Snippet 3: Custom USB Interrupt Handler
* The following section illustrates how to set up the IRQ interrupt handler for USB device. Inside the handler
* \ref cyhal_usb_dev_process_irq has been used to process the interrupts.
*
* \snippet hal_usb_dev.c snippet_cyhal_usb_dev_irq
*
*
* \subsection subsection_usb_dev_snippet_4 Snippet 4: Adding an Endpoint and Handling its Interrupts
* The following section shows how to add endpoint to the USB device and configure the endpoint using
* \ref cyhal_usb_dev_endpoint_add. The interrupts associated with the endpoints are handled by a
* callback function registered using \ref cyhal_usb_dev_register_endpoint_callback.
* The endpoint can also be configured using <a href="https://www.cypress.com/ModusToolboxUSBConfig">ModusToolboxâ„¢ USB Configurator</a>
*
* \snippet hal_usb_dev.c snippet_cyhal_usb_dev_endpoint
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_usbdev USB Device HAL Results
 *  USB Device specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The usb error */
#define CYHAL_USB_DEV_RSLT_ERR                          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_USB, 0))
/** The driver configuration is not supported by the HAL */
#define CYHAL_USB_DEV_RSLT_ERR_BAD_DRV_CFG              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_USB, 1))
/** The configuration of USB clock failed */
#define CYHAL_USB_DEV_RSLT_ERR_CLK_CFG                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_USB, 2))

/**
 * \}
 */

/**
 * \addtogroup group_hal_usb_dev_endpoint Endpoint
 * \{
 * APIs relating to endpoint management
 */

/** Returns true if endpoint direction is IN */
#define CYHAL_USB_DEV_IS_IN_EP(endpoint)        (0U != (0x80U & (uint32_t) (endpoint)))

/** Returns endpoint number (type uint32_t) */
#define CYHAL_USB_DEV_GET_EP_NUM(endpoint)      ((uint32_t) (endpoint) & 0x0FU)

/** Returns endpoint index (type uint32_t) */
#define CYHAL_USB_DEV_GET_EP_IDX(endpoint)      (CYHAL_USB_DEV_GET_EP_NUM(endpoint) - 1U)

/** USB Device Endpoints types */
typedef enum
{
    CYHAL_USB_DEV_EP_TYPE_CTRL = 0,
    CYHAL_USB_DEV_EP_TYPE_ISO  = 1,
    CYHAL_USB_DEV_EP_TYPE_BULK = 2,
    CYHAL_USB_DEV_EP_TYPE_INT  = 3
} cyhal_usb_dev_ep_type_t;

/** \} group_hal_usb_dev_endpoint */


/**
 * \addtogroup group_hal_usb_dev_common Common
 * \{
 */

/** Service Callback Events */
typedef enum
{
    CYHAL_USB_DEV_EVENT_BUS_RESET,  /**< Callback hooked to bus reset interrupt */
    CYHAL_USB_DEV_EVENT_EP0_SETUP,  /**< Callback hooked to endpoint 0 SETUP packet interrupt */
    CYHAL_USB_DEV_EVENT_EP0_IN,     /**< Callback hooked to endpoint 0 IN packet interrupt */
    CYHAL_USB_DEV_EVENT_EP0_OUT,    /**< Callback hooked to endpoint 0 OUT packet interrupt */
} cyhal_usb_dev_event_t;


/**
 * USB endpoint address (consists from endpoint number and direction)
 */
typedef uint8_t cyhal_usb_dev_ep_t;

/**
 * Callback handler for USB Device interrupt
 */
typedef void (*cyhal_usb_dev_irq_callback_t)(void);

/**
 * Callback handler for the transfer completion event for data endpoints (not applicable for endpoint 0)
 */
typedef void (* cyhal_usb_dev_endpoint_callback_t)(cyhal_usb_dev_ep_t endpoint);

/** Callback handler for the events for USB Device */
typedef void (*cyhal_usb_dev_event_callback_t)(void);

/** Callback handler for the events for USB Device */
typedef void (*cyhal_usb_dev_sof_callback_t)(uint32_t frame_number);


/**
 * Initialize the USB instance.
 *
 * @param[out] obj    Pointer to a USB object. The caller must allocate the
 *  memory for this object but the init function will initialize its contents.
 * @param[in] dp      The D+ pin to initialize
 * @param[in] dm      The D- pin to initialize
 * @param[in] clk     The clock to use can be shared, if not provided a new clock will be allocated
 *
 * @return The status of the initialization request
 */
 cy_rslt_t cyhal_usb_dev_init(cyhal_usb_dev_t *obj, cyhal_gpio_t dp, cyhal_gpio_t dm, const cyhal_clock_t *clk);

/**
 * Power down the USB instance
 *
 * Disable interrupts and stop sending events.
 *
 * @param[in,out] obj The USB device object
 */
 void cyhal_usb_dev_free(cyhal_usb_dev_t *obj);

/**
 * Make the USB device visible to the USB host
 *
 * Enable either the D+ or D- pull-up so the host can detect
 * the presence of this device.
 *
 * @param[in,out] obj The USB device object
 */
 void cyhal_usb_dev_connect(cyhal_usb_dev_t *obj);

/**
 * Detach the USB device
 *
 * Disable the D+ and D- pull-up and stop responding to
 * USB traffic.
 *
 * @param[in,out] obj The USB device object
 */
 void cyhal_usb_dev_disconnect(cyhal_usb_dev_t *obj);

 /**
  * Suspend the USB phy. This allows the device to enter deepsleep.
  * Any data left any USB EP buffers will be lost, when device go into deepsleep.
  * Call \ref cyhal_usb_dev_resume to resume USB from deepsleep.
  *
  * @param[in] obj The usb device object
  */
 void cyhal_usb_dev_suspend(cyhal_usb_dev_t *obj);

/**
 * Resume the USB phy from a suspended state. \see cyhal_usb_dev_suspend
 *
 * @param[in] obj The usb device object
 */
 void cyhal_usb_dev_resume(cyhal_usb_dev_t *obj);

/**
 * Set this device to the configured state
 *
 * Enable added endpoints if they are not enabled
 * already.
 *
 * @param[in,out] obj The USB device object
 */
 void cyhal_usb_dev_set_configured(cyhal_usb_dev_t *obj);

/**
 * Leave the configured state
 *
 * This is a notification to the USBPhy indicating that the device
 * is leaving the configured state. The USBPhy can disable all
 * endpoints other than endpoint 0.
 *
 * @param[in,out] obj The USB device object
 */
 void cyhal_usb_dev_set_unconfigured(cyhal_usb_dev_t *obj);

/**
 * Configure start of frame interrupt enablement.
 *
 * @param[in,out] obj The USB device object
 * @param[in] enable  True to turn on interrupt and start calling sof callback on every frame,
 *                    False to turn off interrupt and stop calling sof callback.
 */
 void cyhal_usb_dev_sof_enable(cyhal_usb_dev_t *obj, bool enable);

/**
 * Set the USBPhy's address
 *
 * @param[in,out] obj The USB device object
 * @param[in] address This device's USB address
 */
 void cyhal_usb_dev_set_address(cyhal_usb_dev_t *obj, uint8_t address);

/** \} group_hal_usb_dev_common */

/**
 * \addtogroup group_hal_usb_dev_ep0 EP0
 * \{
 * APIs relating specifically to management of endpoint zero
 */

/**
 * Get wMaxPacketSize of endpoint 0.
 * The endpoint 0 has dedicated buffer.
 *
 * @param[in,out] obj       The USB device object
 *
 * @return The size allocated for endpoint 0
 */
uint32_t cyhal_usb_dev_ep0_get_max_packet(cyhal_usb_dev_t *obj);

/**
 * Read the contents of the SETUP packet
 *
 * @param[in,out] obj The USB device object
 * @param[in] buffer  Buffer to fill with data
 * @param[in] size    Size of buffer passed in
 */
 void cyhal_usb_dev_ep0_setup_read_result(cyhal_usb_dev_t *obj, uint8_t *buffer, uint32_t size);

/**
 * Start receiving a packet of up to wMaxPacketSize on endpoint 0
 *
 * @param[in,out] obj The USB device object
 * @param[in] buffer  Buffer to fill with the data read
 * @param[in] size    Size of buffer
 */
 void cyhal_usb_dev_ep0_read(cyhal_usb_dev_t *obj, uint8_t *buffer, uint32_t size);

/**
 * Read the contents of a received packet
 *
 * @param[in,out] obj  The USB device object
 *
 * @return Actual number of bytes that was read
 */
 uint32_t cyhal_usb_dev_ep0_read_result(cyhal_usb_dev_t *obj);

/**
 * Write a packet on endpoint 0
 *
 * @param[in,out] obj The USB device object
 * @param[in] buffer  Buffer fill with data to send
 * @param[in] size    Size of data to send
 *
 * @return The number of bytes that were written.
 */
 uint32_t cyhal_usb_dev_ep0_write(cyhal_usb_dev_t *obj, uint8_t *buffer, uint32_t size);

/**
 * Protocol stall on endpoint 0.
 * Stall all IN and OUT packets on endpoint 0 until a SETUP packet is received.
 *
 * @param[in,out] obj The USB device object
 *
 * @note The stall is cleared automatically when a setup packet is received
 */
 void cyhal_usb_dev_ep0_stall(cyhal_usb_dev_t *obj);

/** \} group_hal_usb_dev_ep0 */

/**
 * \addtogroup group_hal_usb_dev_endpoint
 * \{
 */

/**
 * Configure an endpoint.
 *
 * @param[in,out] obj    The USB device object
 * @param[in] alloc      True to allocates buffer for the endpoint, false to skip allocation
 * @param[in] enable     True to enable endpoint operation, false to skip enablement
 * @param[in] endpoint   Endpoint to configure and enable
 * @param[in] max_packet The maximum packet size that can be sent or received
 * @param[in] type       The type of endpoint (does not care when enable parameter is false)
 *
 * @return The status of the endpoint add request
 *
 * @note
 * - This function cannot be used to configure endpoint 0. That must be done
 *   with cyhal_usb_dev_ep0_get_max_packet.
 * - After endpoint was enabled it must be removed with cyhal_usb_dev_endpoint_remove
 *   and then enabled again.
 */
cy_rslt_t cyhal_usb_dev_endpoint_add(cyhal_usb_dev_t *obj, bool alloc, bool enable ,cyhal_usb_dev_ep_t endpoint, uint32_t max_packet, cyhal_usb_dev_ep_type_t type);

/**
 * Disable an endpoint
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to disable
 *
 * @return The status of the endpoint remove request
 */
 cy_rslt_t cyhal_usb_dev_endpoint_remove(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint);

/**
 * Perform a functional stall on the given endpoint
 *
 * Set the HALT feature for this endpoint so that all further
 * communication is aborted.
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to stall
 *
 * @return The status of the endpoint stall request
 */
 cy_rslt_t cyhal_usb_dev_endpoint_stall(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint);

/**
 * Unstall the endpoint
 *
 * Clear the HALT feature on this endpoint so communication can
 * resume.
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to stall
 *
 * @return The status of the endpoint unstall request
 */
 cy_rslt_t cyhal_usb_dev_endpoint_unstall(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint);

/**
 * Return the endpoint stall state
 *
 * @param[in,out] obj    The USB device object
 * @param[in] endpoint   Endpoint to check stall state
 *
 * @return True if endpoint stalled, false otherwise.
 */
 bool cyhal_usb_dev_endpoint_is_stalled(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint);

/**
 * Start a read on the given endpoint
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to start the read on
 * @param[in] data     Buffer to fill with data
 * @param[in] size     Size of the read buffer. This must be at least
 *                     the max packet size for this endpoint.
 *
 * @return The status of start a read operation
 */
 cy_rslt_t cyhal_usb_dev_endpoint_read(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint, uint8_t *data, uint32_t size);

/**
 * Finish a read on the given endpoint
 *
 * @param[in,out] obj   The USB device object
 * @param[in] endpoint  Endpoint to check
 * @param[out] act_size Actual number of bytes that was read
 *
 * @return The status of a finish read
 */
 cy_rslt_t cyhal_usb_dev_endpoint_read_result(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint, uint32_t *act_size);

/**
 * Start a write on the given endpoint
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to write to
 * @param[in] data     Buffer to write
 * @param[in] size     Size of data to write
 *
 * @return The status of a write request
 */
 cy_rslt_t cyhal_usb_dev_endpoint_write(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint, uint8_t const *data, uint32_t size);

/**
 * Abort the current transfer if it has not yet been sent
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to abort the transfer on. It is implementation defined
 * if this function has an effect on receive endpoints.
 *
 * @return The status of an abort request
 *
 * @note
 * For the ISOC endpoints in pending state this function does not wait for
 * bus activity completion because these endpoints do not have handshake and are
 * always accessible to the Host. Therefore it is safe to call this function for
 * ISOC endpoint when the Host will not access them during abort.
 */
 cy_rslt_t cyhal_usb_dev_endpoint_abort(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint);

/** \} group_hal_usb_dev_endpoint */

/**
 * \addtogroup group_hal_usb_dev_common Common
 * \{
 */

 /** Register a USB Device callback handler
 *
 * This function will be called when the USB interrupt is triggered. This interrupt can be
 * enabled or disabled using \ref cyhal_usb_dev_irq_enable.
 *
 * @param[in,out] obj The USB device object
 * @param[in] callback The event handler function which will be invoked when the event fires
 *
 * @return The status of the register_irq_callback request
 */
cy_rslt_t cyhal_usb_dev_register_irq_callback(cyhal_usb_dev_t *obj, cyhal_usb_dev_irq_callback_t callback);

/**
 * Configure USB Device event enablement.
 *
 * When the interrupt is enabled and triggered, the function specified by \ref cyhal_usb_dev_register_irq_callback will be called.
 *
 * @param[in,out] obj The usb device object
 * @param[in] enable  True to turn on events, False to turn off
 */
void cyhal_usb_dev_irq_enable(cyhal_usb_dev_t *obj, bool enable);

/**
 *  Default USB Device interrupt handler.
 *
 * @param[in,out] obj The USB device object
 */
void cyhal_usb_dev_process_irq(cyhal_usb_dev_t *obj);

/**
 * The USB Device endpoint complete callback handler registration
 *
 * @param[in,out] obj  The USB device object
 * @param[in] endpoint Endpoint to registers handler
 * @param[in] callback  The callback handler which will be invoked when the endpoint comp
 *
 * \ingroup group_hal_usb_dev_endpoint
 */
void cyhal_usb_dev_register_endpoint_callback(cyhal_usb_dev_t *obj, cyhal_usb_dev_ep_t endpoint, cyhal_usb_dev_endpoint_callback_t callback);

/**
 * The USB Device event complete callback handler registration. The events are defined by x type.
 *
 * @param[in,out] obj The USB device object
 * @param[in] event   The event that triggers the callback, see \ref cyhal_usb_dev_event_t
 * @param[in] callback The callback handler which will be invoked when the interrupt fires
 */
void cyhal_usb_dev_register_event_callback(cyhal_usb_dev_t *obj, cyhal_usb_dev_event_t event, cyhal_usb_dev_event_callback_t callback);

/**
 * The USB Device start of frame (SOF) complete callback handler registration.
 *
 * @param[in,out] obj The USB device object
 * @param[in] callback The callback handler which will be invoked when the interrupt fires
 */
void cyhal_usb_dev_register_sof_callback( cyhal_usb_dev_t *obj, cyhal_usb_dev_sof_callback_t callback);

/** \} group_hal_usb_dev_common */

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_USB_DEV_IMPL_HEADER
#include CYHAL_USB_DEV_IMPL_HEADER
#endif /* CYHAL_USB_DEV_IMPL_HEADER */

/** \} group_hal_usb_dev */
