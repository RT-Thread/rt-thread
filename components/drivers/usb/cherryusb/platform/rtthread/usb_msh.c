/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rtthread.h"

#if defined(PKG_CHERRYUSB_HOST) || defined(RT_CHERRYUSB_HOST)

#include "usbh_core.h"

int usbh_init(int argc, char **argv)
{
    uint8_t busid;
    uint32_t reg_base;

    if (argc < 3) {
        USB_LOG_ERR("please input correct command: usbh_init <busid> <reg_base>\r\n");
        return -1;
    }

    busid = atoi(argv[1]);
    reg_base = strtoll(argv[2], NULL, 16);
    usbh_initialize(busid, reg_base);

    return 0;
}

int usbh_deinit(int argc, char **argv)
{
    uint8_t busid;

    if (argc < 2) {
        USB_LOG_ERR("please input correct command: usbh_deinit <busid>\r\n");
        return -1;
    }

    busid = atoi(argv[1]);
    usbh_deinitialize(busid);

    return 0;
}

MSH_CMD_EXPORT(usbh_init, init usb host);
MSH_CMD_EXPORT(usbh_deinit, deinit usb host);
MSH_CMD_EXPORT(lsusb, ls usb devices);
#endif
