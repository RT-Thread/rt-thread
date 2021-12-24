/*
 * File      : mbox.h
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-29     zdzn           first version
 */

#ifndef __MBOX_H__
#define __MBOX_H__

#include <rtthread.h>
#include <stdint.h>
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

#define DEVICE_ID_SD_CARD   0
#define DEVICE_ID_USB_HCD   3
#define POWER_STATE_OFF     (0 << 0)
#define POWER_STATE_ON      (1 << 0)
#define POWER_STATE_WAIT    (1 << 1)
#define POWER_STATE_NO_DEVICE   (1 << 1)    // in response
#define MMU_ENABLE 1
#define MMU_DISABLE 0

/*
 * raspi hardware info
 */
enum {
    MBOX_TAG_HARDWARE_GET_MODEL         = 0x00010001,
    MBOX_TAG_HARDWARE_GET_REV           = 0x00010002,
    MBOX_TAG_HARDWARE_GET_MAC_ADDRESS   = 0x00010003,
    MBOX_TAG_HARDWARE_GET_SERIAL        = 0x00010004,
    MBOX_TAG_HARDWARE_GET_ARM_MEMORY    = 0x00010005,
    MBOX_TAG_HARDWARE_GET_VC_MEMORY     = 0x00010006,
    MBOX_TAG_HARDWARE_GET_CLOCKS        = 0x00010007,
};

/*
 * raspi clock
 */
enum {
    MBOX_TAG_CLOCK_GET_TURBO    = 0x00030009,
    MBOX_TAG_CLOCK_SET_TURBO    = 0x00038009,
    MBOX_TAG_CLOCK_GET_STATE    = 0x00030001,
    MBOX_TAG_CLOCK_SET_STATE    = 0x00038001,
    MBOX_TAG_CLOCK_GET_RATE     = 0x00030002,
    MBOX_TAG_CLOCK_SET_RATE     = 0x00038002,
    MBOX_TAG_CLOCK_GET_MAX_RATE = 0x00030004,
    MBOX_TAG_CLOCK_GET_MIN_RATE = 0x00030007,
};

/*
 * raspi power
 */
enum {
    MBOX_TAG_POWER_GET_STATE    = 0x00020001,
    MBOX_TAG_POWER_SET_STATE    = 0x00028001,
};

/*
 * raspi temperature
 */
enum {
    MBOX_TAG_TEMP_GET       = 0x00030006,
    MBOX_TAG_TEMP_GET_MAX   = 0x0003000A,
};

#define MBOX_ADDR 0xc00000

int mbox_call(unsigned char ch, int mmu_enable);
int bcm283x_mbox_hardware_get_model(void);
int bcm283x_mbox_hardware_get_revison(void);
int bcm283x_mbox_hardware_get_mac_address(uint8_t * mac);
int bcm283x_mbox_hardware_get_serial(rt_uint64_t* sn);
int bcm283x_mbox_hardware_get_arm_memory(rt_uint32_t * base, rt_uint32_t * size);
int bcm283x_mbox_hardware_get_vc_memory(rt_uint32_t * base, rt_uint32_t * size);
int bcm283x_mbox_clock_get_turbo(void);
int bcm283x_mbox_clock_set_turbo(int level);
int bcm283x_mbox_clock_get_state(int id);
int bcm283x_mbox_clock_set_state(int id, int state);
int bcm283x_mbox_clock_get_rate(int id);
int bcm283x_mbox_clock_set_rate(int id, int rate);
int bcm283x_mbox_clock_get_max_rate(int id);
int bcm283x_mbox_clock_get_min_rate(int id);
int bcm283x_mbox_power_get_state(int id);
int bcm283x_mbox_power_set_state(int id, int state);
int bcm283x_mbox_temp_get(void);
int bcm283x_mbox_temp_get_max(void);

#endif
