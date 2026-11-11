/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_PL2303_H
#define USBH_PL2303_H

#include "usb_cdc.h"

#define PL2303_VENDOR_WRITE_REQUEST  0x01
#define PL2303_VENDOR_WRITE_NREQUEST 0x80
#define PL2303_VENDOR_READ_REQUEST   0x01
#define PL2303_VENDOR_READ_NREQUEST  0x81

#define PL2303_FLOWCTRL_MASK 0xf0

#define PL2303_READ_TYPE_HX_STATUS 0x8080

#define PL2303_HXN_RESET_REG             0x07
#define PL2303_HXN_RESET_UPSTREAM_PIPE   0x02
#define PL2303_HXN_RESET_DOWNSTREAM_PIPE 0x01

#define PL2303_HXN_FLOWCTRL_REG      0x0a
#define PL2303_HXN_FLOWCTRL_MASK     0x1c
#define PL2303_HXN_FLOWCTRL_NONE     0x1c
#define PL2303_HXN_FLOWCTRL_RTS_CTS  0x18
#define PL2303_HXN_FLOWCTRL_XON_XOFF 0x0c

#define PL2303_QUIRK_UART_STATE_IDX0  BIT(0)
#define PL2303_QUIRK_LEGACY           BIT(1)
#define PL2303_QUIRK_ENDPOINT_HACK    BIT(2)
#define PL2303_QUIRK_NO_BREAK_GETLINE BIT(3)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBH_PL2303_H */
