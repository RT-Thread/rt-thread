/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     zhangyan     first version
 *
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtdevice.h>

#ifdef RT_USING_CAN

#include "fcan.h"

#ifdef __cplusplus
extern "C"
{
#endif

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif
#endif /* __DRV_CAN_H__ */
