/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_config.h"
#include "stdint.h"
#include "usb_dwc2_reg.h"

/* you can find this config in function: usb_global_init, file:at32fxxx_usb.c, for example:
 *
 *  usbx->gccfg_bit.pwrdown = TRUE;
 *  usbx->gccfg_bit.avalidsesen = TRUE;
 *  usbx->gccfg_bit.bvalidsesen = TRUE;
 * 
*/

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#ifdef CONFIG_USB_HS
    return ((1 << 16) | (1 << 21));
#else
    // AT32F415
#if defined(AT32F415RCT7) || defined(AT32F415RCT7_7) || defined(AT32F415CCT7) ||   \
    defined(AT32F415CCU7) || defined(AT32F415KCU7_4) || defined(AT32F415RBT7) ||   \
    defined(AT32F415RBT7_7) || defined(AT32F415CBT7) || defined(AT32F415CBU7) ||   \
    defined(AT32F415KBU7_4) || defined(AT32F415R8T7) || defined(AT32F415R8T7_7) || \
    defined(AT32F415C8T7) || defined(AT32F415K8U7_4)
    return ((1 << 16) | (1 << 18) | (1 << 19) | (1 << 21));
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#ifdef CONFIG_USB_HS
    return ((1 << 16) | (1 << 21));
#else
    // AT32F415
#if defined(AT32F415RCT7) || defined(AT32F415RCT7_7) || defined(AT32F415CCT7) ||   \
    defined(AT32F415CCU7) || defined(AT32F415KCU7_4) || defined(AT32F415RBT7) ||   \
    defined(AT32F415RBT7_7) || defined(AT32F415CBT7) || defined(AT32F415CBU7) ||   \
    defined(AT32F415KBU7_4) || defined(AT32F415R8T7) || defined(AT32F415R8T7_7) || \
    defined(AT32F415C8T7) || defined(AT32F415K8U7_4)
    return ((1 << 16) | (1 << 18) | (1 << 19) | (1 << 21));
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}