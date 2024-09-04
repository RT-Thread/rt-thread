/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/04/23     sakumisu    first version
 */
#include <rtthread.h>
#include <board.h>

/* low level init here, this has implemented in cherryusb */

/* low level deinit here, this has implemented in cherryusb */

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_MSC
int cherryusb_devinit(void)
{
    extern void msc_ram_init(uint8_t busid, uintptr_t reg_base);

    board_init_usb_pins();

    msc_ram_init(0, HPM_USB0_BASE);
    return 0;
}
INIT_COMPONENT_EXPORT(cherryusb_devinit);
#endif

#ifdef RT_CHERRYUSB_HOST
#include "usbh_core.h"

int cherryusb_hostinit(void)
{
    board_init_usb_pins();

    usbh_initialize(0, HPM_USB0_BASE);
    return 0;
}
INIT_COMPONENT_EXPORT(cherryusb_hostinit);
#endif