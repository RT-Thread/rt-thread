/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __RPISENSE_H__
#define __RPISENSE_H__

#include <sys/ioctl.h>

#define SENSEFB_FBIO_IOC_MAGIC  0xf1

#define SENSEFB_FBIOGET_GAMMA   _IO(SENSEFB_FBIO_IOC_MAGIC, 0)
#define SENSEFB_FBIOSET_GAMMA   _IO(SENSEFB_FBIO_IOC_MAGIC, 1)
#define SENSEFB_FBIORESET_GAMMA _IO(SENSEFB_FBIO_IOC_MAGIC, 2)

/*
 * Register values.
 */
#define RPISENSE_FB     0x00
#define RPISENSE_WAI    0xf0
#define RPISENSE_VER    0xf1
#define RPISENSE_KEYS   0xf2
#define RPISENSE_EE_WP  0xf3

#define RPISENSE_ID     's'

struct rpisense
{
    struct rt_i2c_client *i2c_client;

    struct rt_platform_device joystick_dev;
    struct rt_platform_device framebuffer_dev;
};

rt_int32_t rpisense_reg_read(struct rpisense *rpisense, int reg);
rt_ssize_t rpisense_block_write(struct rpisense *rpisense, const char *buf, int count);

#endif /* __RPISENSE_H__ */
