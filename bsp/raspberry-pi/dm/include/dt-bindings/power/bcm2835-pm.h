/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_POWER_BCM2835_PM_H__
#define __DT_BINDINGS_POWER_BCM2835_PM_H__

#define BCM2835_POWER_DOMAIN_GRAFX              0
#define BCM2835_POWER_DOMAIN_GRAFX_V3D          1
#define BCM2835_POWER_DOMAIN_IMAGE              2
#define BCM2835_POWER_DOMAIN_IMAGE_PERI         3
#define BCM2835_POWER_DOMAIN_IMAGE_ISP          4
#define BCM2835_POWER_DOMAIN_IMAGE_H264         5
#define BCM2835_POWER_DOMAIN_USB                6
#define BCM2835_POWER_DOMAIN_DSI0               7
#define BCM2835_POWER_DOMAIN_DSI1               8
#define BCM2835_POWER_DOMAIN_CAM0               9
#define BCM2835_POWER_DOMAIN_CAM1               10
#define BCM2835_POWER_DOMAIN_CCP2TX             11
#define BCM2835_POWER_DOMAIN_HDMI               12

#define BCM2835_POWER_DOMAIN_COUNT              13

#define BCM2835_RESET_V3D                       0
#define BCM2835_RESET_ISP                       1
#define BCM2835_RESET_H264                      2

#define BCM2835_RESET_COUNT                     3

#endif /* __DT_BINDINGS_POWER_BCM2835_PM_H__ */
