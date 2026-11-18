/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2021 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2021 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Board configuration for the GD32H77D OV7670 port.
 */
#ifndef __CAM_BOARDCONFIG_H__
#define __CAM_BOARDCONFIG_H__

#define OMV_XCLK_FREQUENCY      (24000000U)
#define OMV_CAM_BUS_NAME        "hwi2c2"

#define OMV_ENABLE_OV7670       (1)
#define OMV_OV7670_VERSION      (70)
#define OMV_OV7670_CLKRC        (0x00)

#define ISC_I2C_ID              (2U)
#define ISC_I2C_SPEED           (0U)

#endif /* __CAM_BOARDCONFIG_H__ */
