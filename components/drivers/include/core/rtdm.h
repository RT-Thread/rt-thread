/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-20     ErikChan     the first version
 */

#ifndef __RT_DM_H__
#define __RT_DM_H__

#include <rthw.h>
#include <rtdef.h>
#include <drivers/misc.h>
#include <drivers/byteorder.h>

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

#ifndef RT_USING_SMP
extern int rt_hw_cpu_id(void);
#endif

void rt_dm_secondary_cpu_init(void);

int rt_dm_set_dev_name_auto(rt_device_t dev, const char *prefix);
int rt_dm_get_dev_name_id(rt_device_t dev);

int rt_dm_set_dev_name(rt_device_t dev, const char *format, ...);
const char *rt_dm_get_dev_name(rt_device_t dev);

/* init cpu, memory, interrupt-controller, bus... */
#define INIT_CORE_EXPORT(fn)            INIT_EXPORT(fn, "1.0")
/* init pci/pcie, usb platform driver... */
#define INIT_FRAMEWORK_EXPORT(fn)       INIT_EXPORT(fn, "1.1")
/* init platform, user code... */
#define INIT_PLATFORM_EXPORT(fn)        INIT_EXPORT(fn, "1.2")
/* init sys-timer, clk, pinctrl... */
#define INIT_SUBSYS_EXPORT(fn)          INIT_EXPORT(fn, "1.3")
/* init early drivers */
#define INIT_DRIVER_EARLY_EXPORT(fn)    INIT_EXPORT(fn, "1.4")
/* init in secondary_cpu_c_start */
#define INIT_SECONDARY_CPU_EXPORT(fn)   INIT_EXPORT(fn, "7")
/* init after mount fs */
#define INIT_FS_EXPORT(fn)              INIT_EXPORT(fn, "6.0")

#endif /* __RT_DM_H__ */
