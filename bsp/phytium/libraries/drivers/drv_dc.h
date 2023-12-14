/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date          Author           Notes
 * 2023-11-7     wangzongqiang     first version
 *
 */

#ifndef __DRV_DC_H__
#define __DRV_DC_H__
#include <rtdevice.h>


#ifdef __cplusplus
extern "C"
{
#endif


#define FB_XSIZE        1024
#define FB_YSIZE        768
#define DISPLAY_COLOR_DEPTH     32
#define DISPLAY_REFRESH_RATE_60 60
#define DISPLAY_REFRESH_RATE_59 59
#define DISPLAY_REFRESH_RATE_40 40
#define DISPLAY_REFRESH_RATE_30 30


int rt_hw_dc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DC_H__ */