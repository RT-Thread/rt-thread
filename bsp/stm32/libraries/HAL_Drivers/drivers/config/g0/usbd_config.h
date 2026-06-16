/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-10     Luxianfan    add FS USB support
 */
#ifndef __USBD_CONFIG_H__
#define __USBD_CONFIG_H__

#include <rtconfig.h>

#ifdef BSP_USBD_TYPE_HS
#else
#define USBD_IRQ_TYPE    USB_UCPD1_2_IRQn
#define USBD_IRQ_HANDLER USB_UCPD1_2_IRQHandler
#define USBD_INSTANCE    USB_DRD_FS
#endif

#ifdef BSP_USBD_SPEED_HS
#else
#define USBD_PCD_SPEED PCD_SPEED_FULL
#endif

#ifdef BSP_USBD_PHY_ULPI
#else
#define USBD_PCD_PHY_MODULE PCD_PHY_EMBEDDED
#endif

#endif
