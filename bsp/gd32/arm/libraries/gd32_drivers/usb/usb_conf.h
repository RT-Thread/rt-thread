/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef USB_CONF_H
#define USB_CONF_H

#include <rtconfig.h>
#include <board.h>

#if defined(BSP_USING_USB)

#if defined(SOC_SERIES_GD32H77x_H78X)
#include "gd32h77x_78x.h"
#elif defined(SOC_SERIES_GD32H75E)
#include "gd32h75e.h"
#elif (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x_H78X))
#include "gd32h7xx.h"
#endif

#if defined(BSP_USB_USING_DEVICE)
#define USE_USBHS0
#endif

#if defined(BSP_USB_USING_HOST)
#define USE_USBHS1
#endif

/* USBHS0 and USBHS1 may run different roles at the same time. Keep both
 * role-specific data models enabled when both RT-Thread options are set. */
#if defined(RT_USING_USB_DEVICE)
#define USE_DEVICE_MODE
#endif

#if defined(RT_USING_USB_HOST)
#define USE_HOST_MODE
#define USBH_USE_RTOS
#endif

/* USB FIFO size config */
#define USB_DEV_RX_FIFO_SIZE  512U
#define USB_DEV_TX0_FIFO_SIZE 128U
#define USB_DEV_TX1_FIFO_SIZE 384U
#define USB_DEV_TX2_FIFO_SIZE 0U
#define USB_DEV_TX3_FIFO_SIZE 0U
#define USB_DEV_TX4_FIFO_SIZE 0U
#define USB_DEV_TX5_FIFO_SIZE 0U
#define USB_DEV_TX6_FIFO_SIZE 0U
#define USB_DEV_TX7_FIFO_SIZE 0U

#define USB_HOST_RX_FIFO_SIZE   512U
#define USB_HOST_TX_NPFIFO_SIZE 256U
#define USB_HOST_TX_PFIFO_SIZE  256U

/* General USB Configuration */
#define USB_LOW_POWER 0U

/* if uncomment it, need jump to USB JP */
//#define VBUS_SENSING_ENABLED

//#define USB_INTERNAL_DMA_ENABLED
//#define USB_DEDICATED_EP1_ENABLED
/* End General USB Configuration */

#ifdef USE_ULPI_PHY
#define USB_EXTERNAL_ULPI_PHY_ENABLED
#endif /* USE_ULPI_PHY */

/* all variables and data structures during the transaction process should be 4-bytes aligned */
#if defined(__GNUC__)         /* GNU Compiler */
#define __ALIGN_END __attribute__((aligned(4)))
#define __ALIGN_BEGIN
#else
#define __ALIGN_END

#if defined(__CC_ARM)     /* ARM Compiler */
#define __ALIGN_BEGIN __align(4)
#elif defined(__ICCARM__) /* IAR Compiler */
#define __ALIGN_BEGIN
#elif defined(__TASKING__)/* TASKING Compiler */
#define __ALIGN_BEGIN __align(4)
#endif /* __CC_ARM */
#endif /* __GNUC__ */

/* __packed keyword used to decrease the data type alignment to 1-byte */
#if defined(__GNUC__)       /* GNU Compiler */
#ifndef __packed
#define __packed __unaligned
#endif
#elif defined(__TASKING__)    /* TASKING Compiler */
#define __packed __unaligned
#endif /* __GNUC__ */

#endif /* BSP_USING_USB */

#endif /* USB_CONF_H */
