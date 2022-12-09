/*
 * ===========================================================================================
 *
 *       Filename:  sunxi_usb_common.h
 *
 *    Description:  USB HAL definition.
 * ===========================================================================================
 */
#ifndef SUNXI_HAL_UDC_H
#define SUNXI_HAL_UDC_H

#include <stdint.h>
#include "ch9.h"

typedef enum {
    UDC_EVENT_RX_STANDARD_REQUEST = 1,
    UDC_EVENT_RX_CLASS_REQUEST = 2,
    UDC_EVENT_RX_DATA = 3,
    UDC_EVENT_TX_COMPLETE = 4,
} udc_callback_event_t;

typedef enum {
    UDC_ERRNO_SUCCESS = 0,
    UDC_ERRNO_CMD_NOT_SUPPORTED = -1,
    UDC_ERRNO_CMD_INVALID = -2,
    UDC_ERRNO_BUF_NULL = -3,
    UDC_ERRNO_BUF_FULL = -4,
    UDC_ERRNO_EP_INVALID = -5,
    UDC_ERRNO_RX_NOT_READY = -6,
    UDC_ERRNO_TX_BUSY = -7,
} udc_errno_t;

typedef udc_errno_t (*udc_callback_t)(uint8_t ep_addr, udc_callback_event_t event,
                void *data, uint32_t len);

int32_t hal_udc_init(void);
int32_t hal_udc_deinit(void);
int32_t hal_udc_enter_test_mode(uint32_t test_mode);
void hal_udc_device_desc_init(struct usb_device_descriptor *device_desc);
void hal_udc_config_desc_init(void *config_desc, uint32_t len);
void hal_udc_string_desc_init(const void *string_desc);
void hal_udc_register_callback(udc_callback_t user_callback);
int32_t hal_udc_ep_read(uint8_t ep_addr, void *buf, uint32_t len);
int32_t hal_udc_ep_write(uint8_t ep_addr, void *buf , uint32_t len);
void hal_udc_ep_enable(uint8_t ep_addr, uint16_t maxpacket, uint32_t ts_type);
void hal_udc_ep_disable(uint8_t ep_addr);
void hal_udc_ep_set_buf(uint8_t ep_addr, void *buf, uint32_t len);
ssize_t ed_test(const char *buf, size_t count);
ssize_t hal_udc_driverlevel_adjust(int driverlevel);
#endif
