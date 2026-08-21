/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-27     yeml           the first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"
#include <rtdevice.h>
#include <rtthread.h>

#ifdef SOC_SERIES_TAE32G58xx
#include "tae32g58xx_ll_can.h"
#include "config/g58xx/can_config.h"
#endif

/* tae32 can device */
struct tae32_can
{
    struct rt_can_device rt_can;     /* inherit from can device */

    char *name;
    CAN_TypeDef *Instance;
    CAN_UserCfgTypeDef config;
    
    rt_int8_t intOpenCnt;
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */
