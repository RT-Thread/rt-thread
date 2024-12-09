/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rtthread.h"

#ifdef RT_CHERRYUSB_HOST

#include "usbh_core.h"

static int usb_host_init(int argc, char **argv)
{
    uint8_t busid;
    int err;

    if (argc < 2) {
        busid = 0;
    } else {
        busid = atoi(argv[1]);
    }

    err = usbh_initialize(busid, usb_hc_get_register_base(busid));
    if (err) {
        rt_kprintf("initialize usb%d@0x%x failed, err = %d\n",
                    busid, usb_hc_get_register_base(busid), err);
    } else {
        rt_kprintf("initialize usb%d@0x%x success\n",
                    busid, usb_hc_get_register_base(busid));
    }

    return err;
}

static int usb_host_deinit(int argc, char **argv)
{
    uint8_t busid;
    int err;

    if (argc < 2) {
        busid = 0;
    } else {
        busid = atoi(argv[1]);
    }

    err = usbh_deinitialize(busid);
    if (err) {
        rt_kprintf("deinitialize usb%d@0x%x failed, err = %d\n",
                    busid, usb_hc_get_register_base(busid), err);
    } else {
        rt_kprintf("deinitialize usb%d@0x%x success\n",
                    busid, usb_hc_get_register_base(busid));
    }

    return err;
}

MSH_CMD_EXPORT(usb_host_init, init usb host);
MSH_CMD_EXPORT(usb_host_deinit, deinit usb host);
#endif
