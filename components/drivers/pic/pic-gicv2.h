/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2023-02-01     GuEe-GUI     move macros to header
 */

#ifndef __PIC_GICV2_H__
#define __PIC_GICV2_H__

#include <rtdef.h>

#include <drivers/pic.h>

#define GIC_DIST_CTRL               0x000
#define GIC_DIST_TYPE               0x004
#define GIC_DIST_IIDR               0x008
#define GIC_DIST_IGROUP             0x080
#define GIC_DIST_ENABLE_SET         0x100
#define GIC_DIST_ENABLE_CLEAR       0x180
#define GIC_DIST_PENDING_SET        0x200
#define GIC_DIST_PENDING_CLEAR      0x280
#define GIC_DIST_ACTIVE_SET         0x300
#define GIC_DIST_ACTIVE_CLEAR       0x380
#define GIC_DIST_PRI                0x400
#define GIC_DIST_TARGET             0x800
#define GIC_DIST_CONFIG             0xc00
#define GIC_DIST_SOFTINT            0xf00
#define GIC_DIST_SGI_PENDING_CLEAR  0xf10
#define GIC_DIST_SGI_PENDING_SET    0xf20
#define GIC_DIST_ICPIDR2            0xfe8

#define GICD_ENABLE                 0x1
#define GICD_DISABLE                0x0
#define GICD_INT_ACTLOW_LVLTRIG     0x0
#define GICD_INT_EN_CLR_X32         0xffffffff
#define GICD_INT_EN_SET_SGI         0x0000ffff
#define GICD_INT_EN_CLR_PPI         0xffff0000

#define GICD_GROUP0                 0
#define GICD_GROUP1                 (~GICD_GROUP0)

#define GIC_CPU_CTRL                0x00
#define GIC_CPU_PRIMASK             0x04
#define GIC_CPU_BINPOINT            0x08
#define GIC_CPU_INTACK              0x0c
#define GIC_CPU_EOI                 0x10
#define GIC_CPU_RUNNINGPRI          0x14
#define GIC_CPU_HIGHPRI             0x18
#define GIC_CPU_ALIAS_BINPOINT      0x1c
#define GIC_CPU_ACTIVEPRIO          0xd0
#define GIC_CPU_IIDR                0xfc
#define GIC_CPU_DIR                 0x1000

#define GICC_ENABLE                 0x1
#define GICC_INT_PRI_THRESHOLD      0xf0        /* priority levels 16 */
#define GIC_CPU_CTRL_ENABLE_GRP0    (1 << 0)
#define GIC_CPU_CTRL_ENABLE_GRP1    (1 << 1)
#define GIC_CPU_CTRL_EOI_MODE_NS    (1 << 9)

struct gicv2
{
    struct rt_pic parent;

    int version;
    int max_irq;

    void *dist_base;
    rt_size_t dist_size;
    void *cpu_base;
    rt_size_t cpu_size;

    void *hyp_base;
    rt_size_t hyp_size;
    void *vcpu_base;
    rt_size_t vcpu_size;
};

#endif /* __IRQ_GICV2_H__ */
