/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     zyh          the first version
 */

/*
 * This file defines the USB charger type and state that are needed for
 * USB device APIs.
 */

#ifndef __UAPI_USB_CHARGER_H__
#define __UAPI_USB_CHARGER_H__

/*
 * USB charger type:
 * SDP (Standard Downstream Port)
 * DCP (Dedicated Charging Port)
 * CDP (Charging Downstream Port)
 * ACA (Accessory Charger Adapters)
 */
enum usb_charger_type {
    UNKNOWN_TYPE = 0,
    SDP_TYPE     = 1,
    DCP_TYPE     = 2,
    CDP_TYPE     = 3,
    ACA_TYPE     = 4,
};

/* USB charger state */
enum usb_charger_state {
    USB_CHARGER_DEFAULT = 0,
    USB_CHARGER_PRESENT = 1,
    USB_CHARGER_ABSENT  = 2,
};

#endif /* __UAPI_USB_CHARGER_H__ */
