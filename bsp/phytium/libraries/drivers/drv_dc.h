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
#include "fdcdp.h"

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
struct phytium_dc_bus
{
    struct rt_device parent;
    FDcDp  dc_handle;/* data */
    const char *name;
    rt_uint32_t fdc_id;
};
#ifdef __cplusplus
}
#endif

#endif /* __DRV_DC_H__ */
