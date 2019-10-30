/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-07     Tanek        first implementation
 */

#ifndef  __DRV_WAKEUP_H__
#define  __DRV_WAKEUP_H__

extern void bsp_register_wakeup(void (*hook)(void));

#endif /* __DRV_WAKEUP_H__ */

