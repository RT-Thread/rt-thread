/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-28     qiyu     first version
 */

#ifndef DRIVERS_DRV_GPIO_H_
#define DRIVERS_DRV_GPIO_H_

#include <board.h>
#include "rtdevice.h"

#ifdef __cplusplus
extern "C" {
#endif

int rt_hw_pin_init(void);

#ifndef BSP_XINT1_PIN
#define BSP_XINT1_PIN -1
#endif
#ifndef BSP_XINT2_PIN
#define BSP_XINT2_PIN -1
#endif
#ifndef BSP_XINT3_PIN
#define BSP_XINT3_PIN -1
#endif
#ifndef BSP_XINT4_PIN
#define BSP_XINT4_PIN -1
#endif
#ifndef BSP_XINT5_PIN
#define BSP_XINT5_PIN -1
#endif

#ifdef __cplusplus
}
#endif


#endif /* DRIVERS_DRV_GPIO_H_ */
