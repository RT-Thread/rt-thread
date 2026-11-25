/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __F101_USB_CONFIG_H__
#define __F101_USB_CONFIG_H__

#ifdef RT_USING_CACHE
#define CONFIG_USB_DCACHE_ENABLE
#endif

#include <cherryusb_config_template.h>

/* F101 USB0 is the four-endpoint Sunxi MUSB device controller. */
#undef CONFIG_USB_MUSB_EP_NUM
#define CONFIG_USB_MUSB_EP_NUM 4

#undef CONFIG_USB_MUSB_PIPE_NUM
#define CONFIG_USB_MUSB_PIPE_NUM 4

#define CONFIG_USB_MUSB_SUNXI

#endif /* __F101_USB_CONFIG_H__ */
