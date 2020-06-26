/*
 * File      : mbox.h
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-29     zdzn           first version
 */

#ifndef __MBOX_H__
#define __MBOX_H__

/* a properly aligned buffer */
extern volatile unsigned int* mbox;

#define MBOX_REQUEST    0

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_SETPOWER       0x28001
#define MBOX_TAG_SETCLKRATE     0x38002
#define MBOX_GET_MAC_ADDRESS    0x10003
#define MBOX_GET_CLOCK_RATE        0x30002
#define MBOX_SET_CLOCK_RATE        0x38002
#define MBOX_TAG_LAST           0

#define MMIO_BASE       0x3F000000
#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
#define MBOX_READ       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile unsigned int*)(VIDEOCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile unsigned int*)(VIDEOCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile unsigned int*)(VIDEOCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

#define DEVICE_ID_SD_CARD    0
#define DEVICE_ID_USB_HCD    3
#define POWER_STATE_OFF        (0 << 0)
#define POWER_STATE_ON        (1 << 0)
#define POWER_STATE_WAIT    (1 << 1)
#define POWER_STATE_NO_DEVICE    (1 << 1)    // in response
#define MMU_ENABLE 1
#define MMU_DISABLE 0

#define MBOX_ADDR 0xc00000

int mbox_call(unsigned char ch, int mmu_enable);
#endif
