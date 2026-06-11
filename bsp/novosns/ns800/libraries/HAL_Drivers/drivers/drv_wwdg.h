/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-05-13     Jeffery Yuan      first version
 */

#ifndef DRV_WWDG_H__
#define DRV_WWDG_H__

#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WWDG_DEVICE_NAME    "wwdg"

int rt_hw_wwdg_init(void);

#ifdef __cplusplus
}
#endif

#endif /* DRV_WWDG_H__ */

