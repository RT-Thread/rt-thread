/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_config.h"
#include "stdint.h"
#include "usb_dwc2_reg.h"

#if CONFIG_USBDEV_EP_NUM != 4 && CONFIG_USBDEV_EP_NUM != 6
#error "gd32 only has 4 endpoints for pa11/pa12 and 6 endpoints for pb14/pb15"
#endif

/* you can find this config in function:usb_core_init, file:drv_usb_core.c, for example:
 *
 *  usb_regs->gr->GCCFG |= GCCFG_PWRON | GCCFG_VBUSACEN | GCCFG_VBUSBCEN;
 *
*/

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#ifdef CONFIG_USB_HS
    return 0;
#else
    return ((1 << 16) | (1 << 18) | (1 << 19) | (1 << 21));
#endif
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#ifdef CONFIG_USB_HS
    return 0;
#else
    return ((1 << 16) | (1 << 18) | (1 << 19) | (1 << 21));
#endif
}

extern uint32_t SystemCoreClock;

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}
