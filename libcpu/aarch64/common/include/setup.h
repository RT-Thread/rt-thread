/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     GuEe-GUI     first version
 */

#ifndef __SETUP_H__
#define __SETUP_H__

#include <rtdef.h>
#include <mm_aspace.h>
#ifdef RT_USING_OFW
#include <drivers/ofw_fdt.h>
#endif

void rt_hw_common_setup(void);

#endif /* __SETUP_H__ */
