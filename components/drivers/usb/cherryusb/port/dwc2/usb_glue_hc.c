/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_config.h"
#include "usb_dwc2_reg.h"

/* When using [GPIO_SetFunc(USBF_VBUS_PORT, USBF_VBUS_PIN, USBF_VBUS_FUNC);], there is no need to configure GOTGCTL */

#define USB_OTG_GLB ((DWC2_GlobalTypeDef *)(reg_base))

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{

    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
    return 0;
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOVAL;
    return 0;
}

void usbd_dwc2_delay_ms(uint8_t ms)
{
    /* implement later */
}