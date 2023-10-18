/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     XYZboom      fix usb_conf.h not found in nuclei-sdk after 0.3.8
 */
#ifndef __USB_CONF_H__
#define __USB_CONF_H__

#include <stddef.h>
#include "gd32vf103.h"

#define USE_USB_FS

#ifdef USE_USB_FS
#define USB_FS_CORE
#endif

#ifdef USE_USB_HS
#define USB_HS_CORE
#endif

#ifdef USB_FS_CORE
#define RX_FIFO_FS_SIZE                         128
#define TX0_FIFO_FS_SIZE                        64
#define TX1_FIFO_FS_SIZE                        128
#define TX2_FIFO_FS_SIZE                        0
#define TX3_FIFO_FS_SIZE                        0
#define USB_RX_FIFO_FS_SIZE                     128
#define USB_HTX_NPFIFO_FS_SIZE                  96
#define USB_HTX_PFIFO_FS_SIZE                   96
#endif /* USB_FS_CORE */

#ifdef USB_HS_CORE
#define RX_FIFO_HS_SIZE                          512
#define TX0_FIFO_HS_SIZE                         128
#define TX1_FIFO_HS_SIZE                         372
#define TX2_FIFO_HS_SIZE                         0
#define TX3_FIFO_HS_SIZE                         0
#define TX4_FIFO_HS_SIZE                         0
#define TX5_FIFO_HS_SIZE                         0

#ifdef USE_ULPI_PHY
#define USB_OTG_ULPI_PHY_ENABLED
#endif

#ifdef USE_EMBEDDED_PHY
#define USB_OTG_EMBEDDED_PHY_ENABLED
#endif

#define USB_OTG_HS_INTERNAL_DMA_ENABLED
#define USB_OTG_HS_DEDICATED_EP1_ENABLED
#endif /* USB_HS_CORE */

#ifndef USB_SOF_OUTPUT
#define USB_SOF_OUTPUT                                     0
#endif

#ifndef USB_LOW_POWER
#define USB_LOW_POWER                                      0
#endif

#ifndef USE_HOST_MODE
#define  USE_DEVICE_MODE
#endif

#ifndef USB_FS_CORE
#ifndef USB_HS_CORE
#error "USB_HS_CORE or USB_FS_CORE should be defined"
#endif
#endif

#ifndef USE_DEVICE_MODE
#ifndef USE_HOST_MODE
#error "USE_DEVICE_MODE or USE_HOST_MODE should be defined"
#endif
#endif

#ifndef USE_USB_HS
#ifndef USE_USB_FS
#error "USE_USB_HS or USE_USB_FS should be defined"
#endif
#endif

/****************** C Compilers dependant keywords ****************************/
/* In HS mode and when the DMA is used, all variables and data structures dealing
   with the DMA during the transaction process should be 4-bytes aligned */
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined   (__GNUC__)            /* GNU Compiler */
#define __ALIGN_END __attribute__ ((aligned(4)))
#define __ALIGN_BEGIN
#endif                              /* __GNUC__ */
#else
#define __ALIGN_BEGIN
#define __ALIGN_END
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

#endif /* __USB_CONF_H__ */

