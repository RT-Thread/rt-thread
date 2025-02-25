/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-17     Supperthomas first version
 * 2025-02-25     hydevcode
 */
#include <rtthread.h>
#include <board.h>

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM
/* Register the EMAC device */
static int rt_hw_stm32_cherryusb_cdc_init(void)
{
    extern void cdc_acm_init(uint8_t busid, uintptr_t reg_base);
    cdc_acm_init(0, 0x400A4000u);
    return 0;
}

INIT_COMPONENT_EXPORT(rt_hw_stm32_cherryusb_cdc_init);
static int cherry_usb_cdc_send(int argc, char *argv[])
{
    char str[100];
    if (argc == 2)
    {
        rt_strncpy(str, argv[1], 100);
        rt_kprintf("%s",str);
        extern void cdc_acm_data_send(char *format, ...);
        cdc_acm_data_send("%s\r\n",str);
    }
}
MSH_CMD_EXPORT(cherry_usb_cdc_send, send the cdc data for test)
#endif

