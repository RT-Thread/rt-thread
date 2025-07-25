/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DRV_WDT_H_
#define DRV_WDT_H_

#include <drivers/dev_watchdog.h>
#include <sys/ioctl.h>

#define DEFUALT_TIMEOUT     30*1000 /* ms */
#define KD_WDT_NUM_TOPS     16
#define KD_WDT_FIX_TOP(_idx)    (1U << (16 + _idx))
#define KD_WDT_RMOD_RESET   1
#define KD_WDT_RMOD_IRQ     2

#define KD_DEVICE_CTRL_WDT_GET_TIMEOUT    _IOW('W', 1, int) /* get timeout(in seconds) */
#define KD_DEVICE_CTRL_WDT_SET_TIMEOUT    _IOW('W', 2, int) /* set timeout(in seconds) */
#define KD_DEVICE_CTRL_WDT_GET_TIMELEFT   _IOW('W', 3, int) /* get the left time before reboot(in seconds) */
#define KD_DEVICE_CTRL_WDT_KEEPALIVE      _IOW('W', 4, int) /* refresh watchdog */
#define KD_DEVICE_CTRL_WDT_START          _IOW('W', 5, int) /* start watchdog */
#define KD_DEVICE_CTRL_WDT_STOP           _IOW('W', 6, int) /* stop watchdog */

struct k230_wdt_timeout {
    rt_uint32_t top_val;
    rt_uint32_t sec;
    rt_uint32_t msec;
};

#define swap(a, b) \
    do { struct k230_wdt_timeout __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

/* wdt register map */
typedef struct _wdt
{
    /* WDT Control Register                     (0x00) */
    volatile uint32_t cr;
    /* WDT Timeout Range Register               (0x04) */
    volatile uint32_t torr;
    /* WDT Current Counter Value Register       (0x08) */
    volatile uint32_t ccvr;
    /* WDT Counter Restart Register             (0x0c) */
    volatile uint32_t crr;
    /* WDT Interrupt Status Register            (0x10) */
    volatile uint32_t stat;
    /* WDT Interrupt Clear Register             (0x14) */
    volatile uint32_t eoi;
    /* reserverd                                (0x18) */
    volatile uint32_t resv1;
    /* WDT Protection level Register            (0x1c) */
    volatile uint32_t prot_level;
    /* reserved                                 (0x20-0xe0) */
    volatile uint32_t resv4[49];
    /* WDT Component Parameters Register 5      (0xe4) */
    volatile uint32_t comp_param_5;
    /* WDT Component Parameters Register 4      (0xe8) */
    volatile uint32_t comp_param_4;
    /* WDT Component Parameters Register 3      (0xec) */
    volatile uint32_t comp_param_3;
    /* WDT Component Parameters Register 2      (0xf0) */
    volatile uint32_t comp_param_2;
    /* WDT Component Parameters Register 1      (0xf4) */
    volatile uint32_t comp_param_1;
    /* WDT Component Version Register           (0xf8) */
    volatile uint32_t comp_version;
    /* WDT Component Type Register              (0xfc) */
    volatile uint32_t comp_type;
} __attribute__((packed, aligned(4))) k230_wdt_t;


#endif /* DRV_WDT_H_ */