/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rtthread.h"

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_MSC

#include "usbd_core.h"

void msc_ram_init(uint8_t busid, uintptr_t reg_base);

static int usb_device_init(int argc, char **argv)
{
    uint8_t busid = 0;
    msc_ram_init(busid, usb_dc_get_register_base(busid));
    return 0;
}

static int usb_device_deinit(int argc, char **argv)
{
    uint8_t busid = 0;
    return usbd_deinitialize(busid);
}

MSH_CMD_EXPORT(usb_device_init, init usb device as msc);
MSH_CMD_EXPORT(usb_device_deinit, deinit usb device as msc);
#endif
