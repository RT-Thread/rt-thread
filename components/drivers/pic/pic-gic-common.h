/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#ifndef __PIC_GIC_COMMON_H__
#define __PIC_GIC_COMMON_H__

#include <rtdef.h>

#ifdef RT_PCI_MSI
#include <drivers/pci_msi.h>
#endif
#include <drivers/ofw.h>

#define GIC_SGI_NR  16

#define GICD_INT_DEF_PRI        0xa0U
#define GICD_INT_DEF_PRI_X4     \
(                               \
    (GICD_INT_DEF_PRI << 24) |  \
    (GICD_INT_DEF_PRI << 16) |  \
    (GICD_INT_DEF_PRI << 8) |   \
    GICD_INT_DEF_PRI            \
)

struct gic_quirk
{
    const char *desc;
    const char *compatible;
    rt_err_t (*init)(void *data);

    rt_uint32_t iidr;
    rt_uint32_t iidr_mask;
};

void gic_common_init_quirk_ofw(const struct rt_ofw_node *ic_np, const struct gic_quirk *quirks, void *data);
void gic_common_init_quirk_hw(rt_uint32_t iidr, const struct gic_quirk *quirks, void *data);

void gic_common_sgi_config(void *base, void *data, int irq_base);
rt_err_t gic_common_configure_irq(void *base, int irq, rt_uint32_t mode, void (*sync_access)(void *), void *data);
void gic_common_dist_config(void *base, int max_irqs, void (*sync_access)(void *), void *data);
void gic_common_cpu_config(void *base, int nr, void (*sync_access)(void *), void *data);

void gic_fill_ppi_affinity(rt_bitmap_t *affinity);

#ifdef RT_PIC_ARM_GIC_V2M
rt_err_t gicv2m_ofw_probe(struct rt_ofw_node *ic_np, const struct rt_ofw_node_id *id);
#endif
#ifdef RT_PIC_ARM_GIC_V3_ITS
rt_err_t gicv3_its_ofw_probe(struct rt_ofw_node *ic_np, const struct rt_ofw_node_id *id);
#endif

#endif /* __PIC_GIC_COMMON_H__ */
