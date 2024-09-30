/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_DC_H
#define USB_DC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief init device controller registers.
 * @return On success will return 0, and others indicate fail.
 */
int usb_dc_init(uint8_t busid);

/**
 * @brief deinit device controller registers.
 * @return On success will return 0, and others indicate fail.
 */
int usb_dc_deinit(uint8_t busid);

/**
 * @brief Set USB device address
 *
 * @param[in] addr Device address
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_set_address(uint8_t busid, const uint8_t addr);

/**
 * @brief Set remote wakeup feature
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_set_remote_wakeup(uint8_t busid);

/**
 * @brief Get USB device speed
 *
 * @param[in] busid bus index
 *
 * @return port speed, USB_SPEED_LOW or USB_SPEED_FULL or USB_SPEED_HIGH
 */
uint8_t usbd_get_port_speed(uint8_t busid);

/**
 * @brief configure and enable endpoint.
 *
 * @param [in]  ep_cfg Endpoint config.
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep);

/**
 * @brief Disable the selected endpoint
 *
 * @param[in] ep Endpoint address
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_ep_close(uint8_t busid, const uint8_t ep);

/**
 * @brief Set stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address
 *
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_ep_set_stall(uint8_t busid, const uint8_t ep);

/**
 * @brief Clear stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep);

/**
 * @brief Check if the selected endpoint is stalled
 *
 * @param[in]  ep       Endpoint address
 *
 * @param[out] stalled  Endpoint stall status
 *
 * @return On success will return 0, and others indicate fail.
 */
int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled);

/**
 * @brief Setup in ep transfer setting and start transfer.
 *
 * This function is asynchronous.
 * This function is similar to uart with tx dma.
 *
 * This function is called to write data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is transmitted
 * out.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to write
 * @param[in]  data_len  Length of the data requested to write. This may
 *                       be zero for a zero length status packet.
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len);

/**
 * @brief Setup out ep transfer setting and start transfer.
 *
 * This function is asynchronous.
 * This function is similar to uart with rx dma.
 *
 * This function is called to read data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is received
 * in.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to read
 * @param[in]  data_len  Max length of the data requested to read.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len);

/* usb dcd irq callback */

/**
 * @brief Usb connect irq callback.
 */
void usbd_event_connect_handler(uint8_t busid);

/**
 * @brief Usb disconnect irq callback.
 */
void usbd_event_disconnect_handler(uint8_t busid);

/**
 * @brief Usb resume irq callback.
 */
void usbd_event_resume_handler(uint8_t busid);

/**
 * @brief Usb suspend irq callback.
 */
void usbd_event_suspend_handler(uint8_t busid);

/**
 * @brief Usb reset irq callback.
 */
void usbd_event_reset_handler(uint8_t busid);

/**
 * @brief Usb setup packet recv irq callback.
 * @param[in]  psetup  setup packet.
 */
void usbd_event_ep0_setup_complete_handler(uint8_t busid, uint8_t *psetup);

/**
 * @brief In ep transfer complete irq callback.
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  nbytes    How many nbytes have transferred.
 */
void usbd_event_ep_in_complete_handler(uint8_t busid, uint8_t ep, uint32_t nbytes);

/**
 * @brief Out ep transfer complete irq callback.
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  nbytes    How many nbytes have transferred.
 */
void usbd_event_ep_out_complete_handler(uint8_t busid, uint8_t ep, uint32_t nbytes);

#ifdef CONFIG_USBDEV_TEST_MODE
/**
 * @brief Usb execute test mode
 * @param[in]  busid     device busid
 * @param[in]  test_mode usb test mode
 */
void usbd_execute_test_mode(uint8_t busid, uint8_t test_mode);
#endif

#ifdef __cplusplus
}
#endif

#endif /* USB_DC_H */
