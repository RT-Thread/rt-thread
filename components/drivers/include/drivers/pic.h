/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#ifndef __PIC_H__
#define __PIC_H__

#include <rthw.h>

#include <bitmap.h>
#include <drivers/ofw.h>
#include <drivers/core/dm.h>

struct rt_pci_msi_desc;
struct rt_pci_msi_msg;

struct rt_pic_ops;
struct rt_pic_irq;

struct rt_pic
{
    /*
     * Other IC is not implemented with PIC but rt_device/object, we need to
     * identify with this object:
     *
     *  struct rt_ic_XYZ_device
     *  {
     *      struct rt_device parent;
     *      struct rt_pic pic;
     *      ...
     *  };
     */
    struct rt_object parent;

    rt_list_t list;

    const struct rt_pic_ops *ops;

    void *priv_data;
    void *user_data;

    int irq_start;
    rt_size_t irq_nr;
    struct rt_pic_irq *pirqs;
};

struct rt_pic_ops
{
    const char  *name;

    rt_err_t    (*irq_init)(struct rt_pic *pic);
    rt_err_t    (*irq_finit)(struct rt_pic *pic);

    void        (*irq_enable)(struct rt_pic_irq *pirq);
    void        (*irq_disable)(struct rt_pic_irq *pirq);
    void        (*irq_ack)(struct rt_pic_irq *pirq);
    void        (*irq_mask)(struct rt_pic_irq *pirq);
    void        (*irq_unmask)(struct rt_pic_irq *pirq);
    void        (*irq_eoi)(struct rt_pic_irq *pirq);

    rt_err_t    (*irq_set_priority)(struct rt_pic_irq *pirq, rt_uint32_t priority);
    rt_err_t    (*irq_set_affinity)(struct rt_pic_irq *pirq, rt_bitmap_t *affinity);
    rt_err_t    (*irq_set_triger_mode)(struct rt_pic_irq *pirq, rt_uint32_t mode);

    void        (*irq_send_ipi)(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask);

    void        (*irq_compose_msi_msg)(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg);
    void        (*irq_write_msi_msg)(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg);
    int         (*irq_alloc_msi)(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc);
    void        (*irq_free_msi)(struct rt_pic *pic, int irq);

#define RT_IRQ_STATE_PENDING    0
#define RT_IRQ_STATE_ACTIVE     1
#define RT_IRQ_STATE_MASKED     2
    rt_err_t    (*irq_set_state)(struct rt_pic *pic, int hwirq, int type, rt_bool_t state);
    rt_err_t    (*irq_get_state)(struct rt_pic *pic, int hwirq, int type, rt_bool_t *out_state);

    int         (*irq_map)(struct rt_pic *pic, int hwirq, rt_uint32_t mode);
    rt_err_t    (*irq_parse)(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq);

#define RT_PIC_F_IRQ_ROUTING    RT_BIT(0)   /* Routing ISR when cascade */
    rt_ubase_t  flags;
};

struct rt_pic_isr
{
    rt_list_t list;

#define RT_IRQ_F_NONE 0
    int flags;
    struct rt_irq_desc action;
};

#define RT_IRQ_AFFINITY_DECLARE(name)           RT_BITMAP_DECLARE(name, RT_CPUS_NR)
#define RT_IRQ_AFFINITY_SET(affinity, cpuid)    rt_bitmap_set_bit(affinity, cpuid)
#define RT_IRQ_AFFINITY_CLEAR(affinity, cpuid)  rt_bitmap_clear_bit(affinity, cpuid)

#ifdef RT_USING_PIC_STATISTICS
struct rt_pic_irq_statistics
{
    rt_ubase_t max_irq_time_ns;
    rt_ubase_t min_irq_time_ns;
    rt_ubase_t sum_irq_time_ns;
};
#endif

struct rt_pic_irq
{
    int irq;
    int hwirq;

#define RT_IRQ_MODE_NONE            0
#define RT_IRQ_MODE_EDGE_RISING     1
#define RT_IRQ_MODE_EDGE_FALLING    2
#define RT_IRQ_MODE_EDGE_BOTH       (RT_IRQ_MODE_EDGE_FALLING | RT_IRQ_MODE_EDGE_RISING)
#define RT_IRQ_MODE_LEVEL_HIGH      4
#define RT_IRQ_MODE_LEVEL_LOW       8
#define RT_IRQ_MODE_LEVEL_MASK      (RT_IRQ_MODE_LEVEL_LOW | RT_IRQ_MODE_LEVEL_HIGH)
#define RT_IRQ_MODE_MASK            0xf
    rt_uint32_t mode;

    rt_uint32_t priority;
    RT_IRQ_AFFINITY_DECLARE(affinity);

    rt_list_t list;
    rt_list_t children_nodes;

    struct rt_pci_msi_desc *msi_desc;

    struct rt_pic_isr isr;

    struct rt_spinlock rw_lock;

    struct rt_pic *pic;
    struct rt_pic_irq *parent;
#ifdef RT_USING_PIC_STATISTICS
    struct rt_pic_irq_statistics stat;
#endif
};

void rt_pic_default_name(struct rt_pic *pic);
struct rt_pic *rt_pic_dynamic_cast(void *ptr);

rt_err_t rt_pic_linear_irq(struct rt_pic *pic, rt_size_t irq_nr);
rt_err_t rt_pic_cancel_irq(struct rt_pic *pic);

int rt_pic_config_ipi(struct rt_pic *pic, int ipi_index, int hwirq);
int rt_pic_config_irq(struct rt_pic *pic, int irq_index, int hwirq);

rt_inline struct rt_pic_irq *rt_pic_find_irq(struct rt_pic *pic, int irq_index)
{
    /* This is a quickly interface */
    RT_ASSERT(pic != RT_NULL);
    RT_ASSERT(pic->pirqs != RT_NULL);
    RT_ASSERT(irq_index < pic->irq_nr);

    return &pic->pirqs[irq_index];
}

struct rt_pic_irq *rt_pic_find_ipi(struct rt_pic *pic, int ipi_index);
struct rt_pic_irq *rt_pic_find_pirq(struct rt_pic *pic, int irq);

rt_err_t rt_pic_cascade(struct rt_pic_irq *pirq, int parent_irq);
rt_err_t rt_pic_uncascade(struct rt_pic_irq *pirq);

rt_err_t rt_pic_attach_irq(int irq, rt_isr_handler_t handler, void *uid, const char *name, int flags);
rt_err_t rt_pic_detach_irq(int irq, void *uid);

rt_err_t rt_pic_add_traps(rt_bool_t (*handler)(void *), void *data);
rt_err_t rt_pic_do_traps(void);
rt_err_t rt_pic_handle_isr(struct rt_pic_irq *pirq);

/* User-implemented extensions */
rt_err_t rt_pic_user_extends(struct rt_pic *pic);

rt_err_t rt_pic_irq_init(void);
rt_err_t rt_pic_irq_finit(void);
void rt_pic_irq_enable(int irq);
void rt_pic_irq_disable(int irq);
void rt_pic_irq_ack(int irq);
void rt_pic_irq_mask(int irq);
void rt_pic_irq_unmask(int irq);
void rt_pic_irq_eoi(int irq);
rt_err_t rt_pic_irq_set_priority(int irq, rt_uint32_t priority);
rt_uint32_t rt_pic_irq_get_priority(int irq);
rt_err_t rt_pic_irq_set_affinity(int irq, rt_bitmap_t *affinity);
rt_err_t rt_pic_irq_get_affinity(int irq, rt_bitmap_t *out_affinity);
rt_err_t rt_pic_irq_set_triger_mode(int irq, rt_uint32_t mode);
rt_uint32_t rt_pic_irq_get_triger_mode(int irq);
void rt_pic_irq_send_ipi(int irq, rt_bitmap_t *cpumask);

rt_err_t rt_pic_irq_set_state_raw(struct rt_pic *pic, int hwirq, int type, rt_bool_t state);
rt_err_t rt_pic_irq_get_state_raw(struct rt_pic *pic, int hwirq, int type, rt_bool_t *out_state);
rt_err_t rt_pic_irq_set_state(int irq, int type, rt_bool_t state);
rt_err_t rt_pic_irq_get_state(int irq, int type, rt_bool_t *out_state);

void rt_pic_irq_parent_enable(struct rt_pic_irq *pirq);
void rt_pic_irq_parent_disable(struct rt_pic_irq *pirq);
void rt_pic_irq_parent_ack(struct rt_pic_irq *pirq);
void rt_pic_irq_parent_mask(struct rt_pic_irq *pirq);
void rt_pic_irq_parent_unmask(struct rt_pic_irq *pirq);
void rt_pic_irq_parent_eoi(struct rt_pic_irq *pirq);
rt_err_t rt_pic_irq_parent_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority);
rt_err_t rt_pic_irq_parent_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity);
rt_err_t rt_pic_irq_parent_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode);

#define RT_PIC_OFW_DECLARE(name, ids, handler)   RT_OFW_STUB_EXPORT(name, ids, pic, handler)

rt_err_t rt_pic_init(void);

#endif /* __PIC_H__ */
