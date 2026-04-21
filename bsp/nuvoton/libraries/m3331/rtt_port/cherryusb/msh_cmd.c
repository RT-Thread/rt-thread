/* Includes ------------------------------------------------------------------*/
#include "rtthread.h"
#include "NuMicro.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.unknown"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 

#if defined(PKG_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM)
void cdc_acm_init(uint8_t busid, uint32_t reg_base);

int rt_cdc_acm_init(void)
{
    cdc_acm_init(0, USBD_BASE);
    return 0;
}

INIT_APP_EXPORT(rt_cdc_acm_init);
MSH_CMD_EXPORT(rt_cdc_acm_init, start rt_cdc_acm_init);
#endif

#if defined(PKG_CHERRYUSB_DEVICE_TEMPLATE_HID_MOUSE)
void hid_mouse_init(uint8_t busid, uint32_t reg_base);
void hid_mouse_test(uint8_t busid);

int rt_hid_mouse_init(void)
{
    hid_mouse_init(0, HSUSBD_BASE);
    return 0;
}

int rt_hid_mouse_test(void)
{
    hid_mouse_test(0);
    return 0;
}

MSH_CMD_EXPORT(rt_hid_mouse_init, start hid_mouse_test);
MSH_CMD_EXPORT(rt_hid_mouse_test, start hid_mouse_test);
#endif

#if defined(PKG_CHERRYUSB_DEVICE_TEMPLATE_HID_KEYBOARD)
void hid_keyboard_init(uint8_t busid, uint32_t reg_base);
void hid_keyboard_test(uint8_t busid);

int rt_hid_keyboard_test(void)
{
    hid_keyboard_init(0, HSUSBD_BASE);
    hid_keyboard_test(0);
    return 0;
}

MSH_CMD_EXPORT(rt_hid_keyboard_test, start hid_keyboard_test);
#endif

#if defined(PKG_CHERRYUSB_DEVICE_TEMPLATE_MSC)
void msc_ram_init(uint8_t busid, uint32_t reg_base);

int rt_msc_ram_test(void)
{
    msc_ram_init(0, HSUSBD_BASE);
    return 0;
}

INIT_APP_EXPORT(rt_msc_ram_test);
MSH_CMD_EXPORT(rt_msc_ram_test, start msc_ram_init);
#endif
