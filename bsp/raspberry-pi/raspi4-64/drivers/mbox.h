/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-09-10     bigmagic       first version
 */

#ifndef __MBOX_H__
#define __MBOX_H__

#include <rtthread.h>

//https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
//https://github.com/hermanhermitage/videocoreiv

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

#define MMIO_BASE       0xFE000000
#define VIDEOCORE_MBOX  (MMIO_BASE+0x0000B880)
extern size_t videocore_mbox;
#define MBOX_READ       ((volatile unsigned int*)(videocore_mbox+0x0))
#define MBOX_POLL       ((volatile unsigned int*)(videocore_mbox+0x10))
#define MBOX_SENDER     ((volatile unsigned int*)(videocore_mbox+0x14))
#define MBOX_STATUS     ((volatile unsigned int*)(videocore_mbox+0x18))
#define MBOX_CONFIG     ((volatile unsigned int*)(videocore_mbox+0x1C))
#define MBOX_WRITE      ((volatile unsigned int*)(videocore_mbox+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

#define DEVICE_ID_SD_CARD        (0)
#define DEVICE_ID_USB_HCD        (3)
#define POWER_STATE_OFF          (0 << 0)
#define POWER_STATE_ON           (1 << 0)
#define POWER_STATE_WAIT         (1 << 1)
#define POWER_STATE_NO_DEVICE    (1 << 1)    // in response
#define MMU_ENABLE               (1)
#define MMU_DISABLE              (0)

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

/*
 * raspi Memory
 */
enum {
    MBOX_TAG_ALLOCATE_MEMORY = 0x0003000C, // Memory: Allocates Contiguous Memory On The GPU (Response: Handle)
    MBOX_TAG_LOCK_MEMORY     = 0x0003000D, // Memory: Unlock Buffer (Response: Status)
    MBOX_TAG_UNLOCK_MEMORY   = 0x0003000E, // Memory: Unlock Buffer (Response: Status)
    MBOX_TAG_RELEASE_MEMORY  = 0x0003000F, // Memory: Free The Memory Buffer (Response: Status)
    MBOX_TAG_EXECUTE_CODE    = 0x00030010, // Memory: Calls The Function At Given (Bus) Address And With Arguments Given
};

/*
 * raspi GPU
 */
enum {
    MBOX_TAG_EXECUTE_QPU = 0x00030011, // QPU: Calls The QPU Function At Given (Bus) Address And With Arguments Given (Response: Number Of QPUs, Control, No Flush, Timeout In ms)
    MBOX_TAG_ENABLE_QPU  = 0x00030012, // QPU: Enables The QPU (Response: Enable State)
};

/*
 * raspi HDMI
 */
#define MBOX_TAG_GET_EDID_BLOCK        0x00030020 // HDMI: Read Specificed EDID Block From Attached HDMI/DVI Device (Response: Block Number, Status, EDID Block (128 Bytes))

/*
 * raspi NOTIFY
 */
#define MBOX_TAG_NOTIFY_REBOOT         0x00030048
#define MBOX_TAG_NOTIFY_XHCI_RESET     0x00030058

/*
* touch
*/
#define MBOX_TAG_GET_TOUCHBUF          (0x0004000F)

#define MBOX_ADDR 0x08000000
extern size_t mbox_addr;

#define    RES_CLK_ID           (0x000000000)
#define    EMMC_CLK_ID          (0x000000001)
#define    UART_CLK_ID          (0x000000002)
#define    ARM_CLK_ID           (0x000000003)
#define    CORE_CLK_ID          (0x000000004)
#define    V3D_CLK_ID           (0x000000005)
#define    H264_CLK_ID          (0x000000006)
#define    ISP_CLK_ID           (0x000000007)
#define    SDRAM_CLK_ID         (0x000000008)
#define    PIXEL_CLK_ID         (0x000000009)
#define    PWM_CLK_ID           (0x00000000a)

int mbox_call(unsigned char ch, int mmu_enable);
int bcm271x_mbox_get_touch(void);
int bcm271x_notify_reboot(void);
int bcm271x_notify_xhci_reset(void);
int bcm271x_gpu_enable(void);
int bcm271x_mbox_hardware_get_model(void);
int bcm271x_mbox_hardware_get_revison(void);
int bcm271x_mbox_hardware_get_mac_address(uint8_t * mac);
int bcm271x_mbox_hardware_get_serial(rt_uint64_t* sn);
int bcm271x_mbox_hardware_get_arm_memory(rt_uint32_t * base, rt_uint32_t * size);
int bcm271x_mbox_hardware_get_vc_memory(rt_uint32_t * base, rt_uint32_t * size);
int bcm271x_mbox_clock_get_turbo(void);
int bcm271x_mbox_clock_set_turbo(int level);
int bcm271x_mbox_clock_get_state(int id);
int bcm271x_mbox_clock_set_state(int id, int state);
int bcm271x_mbox_clock_get_rate(int id);
int bcm271x_mbox_clock_set_rate(int id, int rate);
int bcm271x_mbox_clock_get_max_rate(int id);
int bcm271x_mbox_clock_get_min_rate(int id);
int bcm271x_mbox_power_get_state(int id);
int bcm271x_mbox_power_set_state(int id, int state);
int bcm271x_mbox_temp_get(void);
int bcm271x_mbox_temp_get_max(void);

#endif
