/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-17     Supperthomas first version
 */
#include "board.h"
#include "rtthread.h"
#include "drv_config.h"

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM
/* Register the EMAC device */
static int rt_hw_stm32_cherryusb_cdc_init(void)
{
    extern void cdc_acm_init(uint8_t busid, uintptr_t reg_base);
    cdc_acm_init(0, USB_OTG_FS_PERIPH_BASE);

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_stm32_cherryusb_cdc_init);
static int cherry_usb_cdc_send(int argc, char **argv)
{
    extern void cdc_acm_data_send_with_dtr_test(uint8_t busid);
    cdc_acm_data_send_with_dtr_test(0);
    return 0;
}
MSH_CMD_EXPORT(cherry_usb_cdc_send, send the cdc data for test)
#endif

