/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-17     Supperthomas first version
 * 2025-02-25     hydevcode
 * 2026-05-09     CoreBoxer    add HID mouse example
 */
#include <rtthread.h>
#include <board.h>
#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM
/* Register the EMAC device */
static int rt_hw_mcxa366_cherryusb_cdc_init(void)
{
    extern void cdc_acm_init(uint8_t busid, uintptr_t reg_base);
    cdc_acm_init(0, USB0_BASE);
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_mcxa366_cherryusb_cdc_init);
#endif

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_HID_MOUSE
extern void hid_mouse_init(uint8_t busid, uintptr_t reg_base);
extern void hid_mouse_test(uint8_t busid);
static int rt_hw_mcxa366_cherryusb_hid_init(void)
{
    hid_mouse_init(0, USB0_BASE);
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_mcxa366_cherryusb_hid_init);
static int hid_example(int argc, char **argv)
{
    RT_UNUSED(argc);
    RT_UNUSED(argv);

    hid_mouse_test(0);
    return 0;
}
MSH_CMD_EXPORT(hid_example, USB hid example);
#endif
