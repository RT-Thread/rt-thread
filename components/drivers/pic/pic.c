/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "rtdm.pic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pic.h>
#ifdef RT_USING_PIC_STATISTICS
#include <ktime.h>
#endif

struct irq_traps
{
    rt_list_t list;

    void *data;
    rt_bool_t (*handler)(void *);
};

static int _ipi_hash[] =
{
#ifdef RT_USING_SMP
    [RT_SCHEDULE_IPI] = RT_SCHEDULE_IPI,
    [RT_STOP_IPI] = RT_STOP_IPI,
    [RT_SMP_CALL_IPI] = RT_SMP_CALL_IPI,
#endif
};

/* reserved ipi */
static int _pirq_hash_idx = RT_ARRAY_SIZE(_ipi_hash);
static struct rt_pic_irq _pirq_hash[MAX_HANDLERS] =
{
    [0 ... MAX_HANDLERS - 1] =
    {
        .irq = -1,
        .hwirq = -1,
        .mode = RT_IRQ_MODE_NONE,
        .priority = RT_UINT32_MAX,
        .rw_lock = { },
    }
};

static struct rt_spinlock _pic_lock = { };
static rt_size_t _pic_name_max = sizeof("PIC");
static rt_list_t _pic_nodes = RT_LIST_OBJECT_INIT(_pic_nodes);
static rt_list_t _traps_nodes = RT_LIST_OBJECT_INIT(_traps_nodes);

static struct rt_pic_irq *irq2pirq(int irq)
{
    struct rt_pic_irq *pirq = RT_NULL;

    if ((irq >= 0) && (irq < MAX_HANDLERS))
    {
        pirq = &_pirq_hash[irq];

        if (pirq->irq < 0)
        {
            pirq = RT_NULL;
        }
    }

    if (!pirq)
    {
        LOG_E("irq = %d is invalid", irq);
    }

    return pirq;
}

static void append_pic(struct rt_pic *pic)
{
    int pic_name_len = rt_strlen(pic->ops->name);

    rt_list_insert_before(&_pic_nodes, &pic->list);

    if (pic_name_len > _pic_name_max)
    {
        _pic_name_max = pic_name_len;
    }
}

void rt_pic_default_name(struct rt_pic *pic)
{
    if (pic)
    {
    #if RT_NAME_MAX > 0
        rt_strncpy(pic->parent.name, "PIC", RT_NAME_MAX - 1);
        pic->parent.name[RT_NAME_MAX - 1] = '\0';
    #else
        pic->parent.name = "PIC";
    #endif
    }
}

struct rt_pic *rt_pic_dynamic_cast(void *ptr)
{
    struct rt_pic *pic = RT_NULL, *tmp = RT_NULL;

    if (ptr)
    {
        struct rt_object *obj = ptr;

        if (obj->type == RT_Object_Class_Unknown)
        {
            tmp = (void *)obj;
        }
        else if (obj->type == RT_Object_Class_Device)
        {
            tmp = (void *)obj + sizeof(struct rt_device);
        }
        else
        {
            tmp = (void *)obj + sizeof(struct rt_object);
        }

        if (tmp && !rt_strcmp(tmp->parent.name, "PIC"))
        {
            pic = tmp;
        }
    }

    return pic;
}

rt_err_t rt_pic_linear_irq(struct rt_pic *pic, rt_size_t irq_nr)
{
    rt_err_t err = RT_EOK;

    if (pic && pic->ops && pic->ops->name)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&_pic_lock);

        if (_pirq_hash_idx + irq_nr <= RT_ARRAY_SIZE(_pirq_hash))
        {
            rt_list_init(&pic->list);

            rt_pic_default_name(pic);
            pic->parent.type = RT_Object_Class_Unknown;

            pic->irq_start = _pirq_hash_idx;
            pic->irq_nr = irq_nr;
            pic->pirqs = &_pirq_hash[_pirq_hash_idx];

            _pirq_hash_idx += irq_nr;

            append_pic(pic);

            LOG_D("%s alloc irqs ranges [%d, %d]", pic->ops->name,
                    pic->irq_start, pic->irq_start + pic->irq_nr);
        }
        else
        {
            LOG_E("%s alloc %d irqs is overflow", pic->ops->name, irq_nr);

            err = -RT_EEMPTY;
        }

        rt_spin_unlock_irqrestore(&_pic_lock, level);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pic_cancel_irq(struct rt_pic *pic)
{
    rt_err_t err = RT_EOK;

    if (pic && pic->pirqs)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&_pic_lock);

        /*
         * This is only to make system runtime safely,
         * we don't recommend PICs to unregister.
         */
        rt_list_remove(&pic->list);

        rt_spin_unlock_irqrestore(&_pic_lock, level);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static void config_pirq(struct rt_pic *pic, struct rt_pic_irq *pirq, int irq, int hwirq)
{
    rt_ubase_t level = rt_spin_lock_irqsave(&pirq->rw_lock);

    if (pirq->irq < 0)
    {
        rt_list_init(&pirq->list);
        rt_list_init(&pirq->children_nodes);
        rt_list_init(&pirq->isr.list);
    }
    else if (pirq->pic != pic)
    {
        RT_ASSERT(rt_list_isempty(&pirq->list) == RT_TRUE);
        RT_ASSERT(rt_list_isempty(&pirq->children_nodes) == RT_TRUE);
        RT_ASSERT(rt_list_isempty(&pirq->isr.list) == RT_TRUE);
    }

    pirq->irq = irq;
    pirq->hwirq = hwirq;

    pirq->pic = pic;

    rt_spin_unlock_irqrestore(&pirq->rw_lock, level);
}

int rt_pic_config_ipi(struct rt_pic *pic, int ipi_index, int hwirq)
{
    int ipi = ipi_index;
    struct rt_pic_irq *pirq;

    if (pic && ipi < RT_ARRAY_SIZE(_ipi_hash) && hwirq >= 0 && pic->ops->irq_send_ipi)
    {
        pirq = &_pirq_hash[ipi];
        config_pirq(pic, pirq, ipi, hwirq);

        for (int cpuid = 0; cpuid < RT_CPUS_NR; ++cpuid)
        {
            RT_IRQ_AFFINITY_SET(pirq->affinity, cpuid);
        }

        LOG_D("%s config %s %d to hwirq %d", pic->ops->name, "ipi", ipi, hwirq);
    }
    else
    {
        ipi = -RT_EINVAL;
    }

    return ipi;
}

int rt_pic_config_irq(struct rt_pic *pic, int irq_index, int hwirq)
{
    int irq;

    if (pic && hwirq >= 0)
    {
        irq = pic->irq_start + irq_index;

        if (irq >= 0 && irq < MAX_HANDLERS)
        {
            config_pirq(pic, &_pirq_hash[irq], irq, hwirq);

            LOG_D("%s config %s %d to hwirq %d", pic->ops->name, "irq", irq, hwirq);
        }
        else
        {
            irq = -RT_ERROR;
        }
    }
    else
    {
        irq = -RT_EINVAL;
    }

    return irq;
}

struct rt_pic_irq *rt_pic_find_ipi(struct rt_pic *pic, int ipi_index)
{
    struct rt_pic_irq *pirq = &_pirq_hash[ipi_index];

    RT_ASSERT(ipi_index < RT_ARRAY_SIZE(_ipi_hash));
    RT_ASSERT(pirq->pic == pic);

    return pirq;
}

struct rt_pic_irq *rt_pic_find_pirq(struct rt_pic *pic, int irq)
{
    if (pic && irq >= pic->irq_start && irq <= pic->irq_start + pic->irq_nr)
    {
        return &pic->pirqs[irq - pic->irq_start];
    }

    return RT_NULL;
}

rt_err_t rt_pic_cascade(struct rt_pic_irq *pirq, int parent_irq)
{
    rt_err_t err = RT_EOK;

    if (pirq && !pirq->parent && parent_irq >= 0)
    {
        struct rt_pic_irq *parent;

        rt_spin_lock(&pirq->rw_lock);

        parent = irq2pirq(parent_irq);

        if (parent)
        {
            pirq->parent = parent;
            pirq->priority = parent->priority;
            rt_memcpy(&pirq->affinity, &parent->affinity, sizeof(pirq->affinity));
        }

        rt_spin_unlock(&pirq->rw_lock);

        if (parent && pirq->pic->ops->flags & RT_PIC_F_IRQ_ROUTING)
        {
            rt_spin_lock(&parent->rw_lock);

            rt_list_insert_before(&parent->children_nodes, &pirq->list);

            rt_spin_unlock(&parent->rw_lock);
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pic_uncascade(struct rt_pic_irq *pirq)
{
    rt_err_t err = RT_EOK;

    if (pirq && pirq->parent)
    {
        struct rt_pic_irq *parent;

        rt_spin_lock(&pirq->rw_lock);

        parent = pirq->parent;
        pirq->parent = RT_NULL;

        rt_spin_unlock(&pirq->rw_lock);

        if (parent && pirq->pic->ops->flags & RT_PIC_F_IRQ_ROUTING)
        {
            rt_spin_lock(&parent->rw_lock);

            rt_list_remove(&pirq->list);

            rt_spin_unlock(&parent->rw_lock);
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pic_attach_irq(int irq, rt_isr_handler_t handler, void *uid, const char *name, int flags)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq;

    if (handler && name && (pirq = irq2pirq(irq)))
    {
        struct rt_pic_isr *isr = RT_NULL;
        rt_ubase_t level = rt_spin_lock_irqsave(&pirq->rw_lock);

        err = RT_EOK;

        if (!pirq->isr.action.handler)
        {
            /* first attach */
            isr = &pirq->isr;
            rt_list_init(&isr->list);
        }
        else
        {
            rt_spin_unlock_irqrestore(&pirq->rw_lock, level);

            if ((isr = rt_malloc(sizeof(*isr))))
            {
                rt_list_init(&isr->list);

                level = rt_spin_lock_irqsave(&pirq->rw_lock);

                rt_list_insert_after(&pirq->isr.list, &isr->list);
            }
            else
            {
                LOG_E("No memory to save '%s' isr", name);
                err = -RT_ERROR;
            }
        }

        if (!err)
        {
            isr->flags = flags;
            isr->action.handler = handler;
            isr->action.param = uid;
        #ifdef RT_USING_INTERRUPT_INFO
            isr->action.counter = 0;
            rt_strncpy(isr->action.name, name, RT_NAME_MAX - 1);
            isr->action.name[RT_NAME_MAX - 1] = '\0';
        #ifdef RT_USING_SMP
            rt_memset(isr->action.cpu_counter, 0, sizeof(isr->action.cpu_counter));
        #endif
        #endif

            rt_spin_unlock_irqrestore(&pirq->rw_lock, level);
        }
    }

    return err;
}

rt_err_t rt_pic_detach_irq(int irq, void *uid)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    if (pirq)
    {
        rt_bool_t will_free = RT_FALSE;
        struct rt_pic_isr *isr = RT_NULL;
        rt_ubase_t level = rt_spin_lock_irqsave(&pirq->rw_lock);

        isr = &pirq->isr;

        if (isr->action.param == uid)
        {
            if (rt_list_isempty(&isr->list))
            {
                isr->action.handler = RT_NULL;
                isr->action.param = RT_NULL;
            }
            else
            {
                struct rt_pic_isr *next_isr = rt_list_first_entry(&isr->list, struct rt_pic_isr, list);

                rt_list_remove(&next_isr->list);

                isr->action.handler = next_isr->action.handler;
                isr->action.param = next_isr->action.param;
            #ifdef RT_USING_INTERRUPT_INFO
                isr->action.counter = next_isr->action.counter;
                rt_strncpy(isr->action.name, next_isr->action.name, RT_NAME_MAX);
            #ifdef RT_USING_SMP
                rt_memcpy(isr->action.cpu_counter, next_isr->action.cpu_counter, sizeof(next_isr->action.cpu_counter));
            #endif
            #endif

                isr = next_isr;
                will_free = RT_TRUE;
            }

            err = RT_EOK;
        }
        else
        {
            rt_list_for_each_entry(isr, &pirq->isr.list, list)
            {
                if (isr->action.param == uid)
                {
                    err = RT_EOK;

                    will_free = RT_TRUE;
                    rt_list_remove(&isr->list);
                    break;
                }
            }
        }

        rt_spin_unlock_irqrestore(&pirq->rw_lock, level);

        if (will_free)
        {
            rt_free(isr);
        }
    }

    return err;
}

rt_err_t rt_pic_add_traps(rt_bool_t (*handler)(void *), void *data)
{
    rt_err_t err = -RT_EINVAL;

    if (handler)
    {
        struct irq_traps *traps = rt_malloc(sizeof(*traps));

        if (traps)
        {
            rt_ubase_t level = rt_hw_interrupt_disable();

            rt_list_init(&traps->list);

            traps->data = data;
            traps->handler = handler;

            rt_list_insert_before(&_traps_nodes, &traps->list);
            err = RT_EOK;

            rt_hw_interrupt_enable(level);
        }
        else
        {
            LOG_E("No memory to save '%p' handler", handler);
            err = -RT_ENOMEM;
        }
    }

    return err;
}

rt_err_t rt_pic_do_traps(void)
{
    rt_err_t err = -RT_ERROR;
    struct irq_traps *traps;

    rt_interrupt_enter();

    rt_list_for_each_entry(traps, &_traps_nodes, list)
    {
        if (traps->handler(traps->data))
        {
            err = RT_EOK;

            break;
        }
    }

    rt_interrupt_leave();

    return err;
}

rt_err_t rt_pic_handle_isr(struct rt_pic_irq *pirq)
{
    rt_err_t err = -RT_EEMPTY;
    rt_list_t *handler_nodes;
    struct rt_irq_desc *action;
#ifdef RT_USING_PIC_STATISTICS
    struct timespec ts;
    rt_ubase_t irq_time_ns;
    rt_ubase_t current_irq_begin;
#endif

    RT_ASSERT(pirq != RT_NULL);
    RT_ASSERT(pirq->pic != RT_NULL);

#ifdef RT_USING_PIC_STATISTICS
    rt_ktime_boottime_get_ns(&ts);
    current_irq_begin = ts.tv_sec * (1000UL * 1000 * 1000) + ts.tv_nsec;
#endif

    handler_nodes = &pirq->isr.list;
    action = &pirq->isr.action;

    if (!rt_list_isempty(&pirq->children_nodes))
    {
        struct rt_pic_irq *child;

        rt_list_for_each_entry(child, &pirq->children_nodes, list)
        {
            if (child->pic->ops->irq_ack)
            {
                child->pic->ops->irq_ack(child);
            }

            err = rt_pic_handle_isr(child);

            if (child->pic->ops->irq_eoi)
            {
                child->pic->ops->irq_eoi(child);
            }
        }
    }

    if (action->handler)
    {
        action->handler(pirq->irq, action->param);
    #ifdef RT_USING_INTERRUPT_INFO
        action->counter++;
    #ifdef RT_USING_SMP
        action->cpu_counter[rt_hw_cpu_id()]++;
    #endif
    #endif

        if (!rt_list_isempty(handler_nodes))
        {
            struct rt_pic_isr *isr;

            rt_list_for_each_entry(isr, handler_nodes, list)
            {
                action = &isr->action;

                RT_ASSERT(action->handler != RT_NULL);

                action->handler(pirq->irq, action->param);
            #ifdef RT_USING_INTERRUPT_INFO
                action->counter++;
            #ifdef RT_USING_SMP
                action->cpu_counter[rt_hw_cpu_id()]++;
            #endif
            #endif
            }
        }

        err = RT_EOK;
    }

#ifdef RT_USING_PIC_STATISTICS
    rt_ktime_boottime_get_ns(&ts);
    irq_time_ns = ts.tv_sec * (1000UL * 1000 * 1000) + ts.tv_nsec - current_irq_begin;
    pirq->stat.sum_irq_time_ns += irq_time_ns;
    if (irq_time_ns < pirq->stat.min_irq_time_ns || pirq->stat.min_irq_time_ns == 0)
    {
        pirq->stat.min_irq_time_ns = irq_time_ns;
    }
    if (irq_time_ns > pirq->stat.max_irq_time_ns)
    {
        pirq->stat.max_irq_time_ns = irq_time_ns;
    }
#endif

    return err;
}

rt_weak rt_err_t rt_pic_user_extends(struct rt_pic *pic)
{
    return -RT_ENOSYS;
}

rt_err_t rt_pic_irq_init(void)
{
    rt_err_t err = RT_EOK;
    struct rt_pic *pic;

    rt_list_for_each_entry(pic, &_pic_nodes, list)
    {
        if (pic->ops->irq_init)
        {
            err = pic->ops->irq_init(pic);

            if (err)
            {
                LOG_E("PIC = %s init fail", pic->ops->name);
                break;
            }
        }
    }

    return err;
}

rt_err_t rt_pic_irq_finit(void)
{
    rt_err_t err = RT_EOK;
    struct rt_pic *pic;

    rt_list_for_each_entry(pic, &_pic_nodes, list)
    {
        if (pic->ops->irq_finit)
        {
            err = pic->ops->irq_finit(pic);

            if (err)
            {
                LOG_E("PIC = %s finit fail", pic->ops->name);
                break;
            }
        }
    }

    return err;
}

void rt_pic_irq_enable(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_enable)
    {
        pirq->pic->ops->irq_enable(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

void rt_pic_irq_disable(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_disable)
    {
        pirq->pic->ops->irq_disable(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

void rt_pic_irq_ack(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_ack)
    {
        pirq->pic->ops->irq_ack(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

void rt_pic_irq_mask(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_mask)
    {
        pirq->pic->ops->irq_mask(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

void rt_pic_irq_unmask(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_unmask)
    {
        pirq->pic->ops->irq_unmask(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

void rt_pic_irq_eoi(int irq)
{
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);

    if (pirq->pic->ops->irq_eoi)
    {
        pirq->pic->ops->irq_eoi(pirq);
    }

    rt_hw_spin_unlock(&pirq->rw_lock.lock);
}

rt_err_t rt_pic_irq_set_priority(int irq, rt_uint32_t priority)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    if (pirq)
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        if (pirq->pic->ops->irq_set_priority)
        {
            err = pirq->pic->ops->irq_set_priority(pirq, priority);

            if (!err)
            {
                pirq->priority = priority;
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return err;
}

rt_uint32_t rt_pic_irq_get_priority(int irq)
{
    rt_uint32_t priority = RT_UINT32_MAX;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    if (pirq)
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        priority = pirq->priority;

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return priority;
}

rt_err_t rt_pic_irq_set_affinity(int irq, rt_bitmap_t *affinity)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq;

    if (affinity && (pirq = irq2pirq(irq)))
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        if (pirq->pic->ops->irq_set_affinity)
        {
            err = pirq->pic->ops->irq_set_affinity(pirq, affinity);

            if (!err)
            {
                rt_memcpy(pirq->affinity, affinity, sizeof(pirq->affinity));
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return err;
}

rt_err_t rt_pic_irq_get_affinity(int irq, rt_bitmap_t *out_affinity)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq;

    if (out_affinity && (pirq = irq2pirq(irq)))
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        rt_memcpy(out_affinity, pirq->affinity, sizeof(pirq->affinity));
        err = RT_EOK;

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return err;
}

rt_err_t rt_pic_irq_set_triger_mode(int irq, rt_uint32_t mode)
{
    rt_err_t err = -RT_EINVAL;
    struct rt_pic_irq *pirq;

    if ((~mode & RT_IRQ_MODE_MASK) && (pirq = irq2pirq(irq)))
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        if (pirq->pic->ops->irq_set_triger_mode)
        {
            err = pirq->pic->ops->irq_set_triger_mode(pirq, mode);

            if (!err)
            {
                pirq->mode = mode;
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return err;
}

rt_uint32_t rt_pic_irq_get_triger_mode(int irq)
{
    rt_uint32_t mode = RT_UINT32_MAX;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    if (pirq)
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        mode = pirq->mode;

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }

    return mode;
}

void rt_pic_irq_send_ipi(int irq, rt_bitmap_t *cpumask)
{
    struct rt_pic_irq *pirq;

    if (cpumask && (pirq = irq2pirq(irq)))
    {
        rt_hw_spin_lock(&pirq->rw_lock.lock);

        if (pirq->pic->ops->irq_send_ipi)
        {
            pirq->pic->ops->irq_send_ipi(pirq, cpumask);
        }

        rt_hw_spin_unlock(&pirq->rw_lock.lock);
    }
}

rt_err_t rt_pic_irq_set_state_raw(struct rt_pic *pic, int hwirq, int type, rt_bool_t state)
{
    rt_err_t err;

    if (pic && hwirq >= 0)
    {
        if (pic->ops->irq_set_state)
        {
            err = pic->ops->irq_set_state(pic, hwirq, type, state);
        }
        else
        {
            err = -RT_ENOSYS;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pic_irq_get_state_raw(struct rt_pic *pic, int hwirq, int type, rt_bool_t *out_state)
{
    rt_err_t err;

    if (pic && hwirq >= 0)
    {
        if (pic->ops->irq_get_state)
        {
            rt_bool_t state;

            if (!(err = pic->ops->irq_get_state(pic, hwirq, type, &state)) && out_state)
            {
                *out_state = state;
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pic_irq_set_state(int irq, int type, rt_bool_t state)
{
    rt_err_t err;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);
    err = rt_pic_irq_set_state_raw(pirq->pic, pirq->hwirq, type, state);
    rt_hw_spin_unlock(&pirq->rw_lock.lock);

    return err;
}

rt_err_t rt_pic_irq_get_state(int irq, int type, rt_bool_t *out_state)
{
    rt_err_t err;
    struct rt_pic_irq *pirq = irq2pirq(irq);

    RT_ASSERT(pirq != RT_NULL);

    rt_hw_spin_lock(&pirq->rw_lock.lock);
    err = rt_pic_irq_get_state_raw(pirq->pic, pirq->hwirq, type, out_state);
    rt_hw_spin_unlock(&pirq->rw_lock.lock);

    return err;
}

void rt_pic_irq_parent_enable(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_enable)
    {
        pirq->pic->ops->irq_enable(pirq);
    }
}

void rt_pic_irq_parent_disable(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_disable)
    {
        pirq->pic->ops->irq_disable(pirq);
    }
}

void rt_pic_irq_parent_ack(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_ack)
    {
        pirq->pic->ops->irq_ack(pirq);
    }
}

void rt_pic_irq_parent_mask(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_mask)
    {
        pirq->pic->ops->irq_mask(pirq);
    }
}

void rt_pic_irq_parent_unmask(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_unmask)
    {
        pirq->pic->ops->irq_unmask(pirq);
    }
}

void rt_pic_irq_parent_eoi(struct rt_pic_irq *pirq)
{
    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_eoi)
    {
        pirq->pic->ops->irq_eoi(pirq);
    }
}

rt_err_t rt_pic_irq_parent_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    rt_err_t err = -RT_ENOSYS;

    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_set_priority)
    {
        if (!(err = pirq->pic->ops->irq_set_priority(pirq, priority)))
        {
            pirq->priority = priority;
        }
    }

    return err;
}

rt_err_t rt_pic_irq_parent_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    rt_err_t err = -RT_ENOSYS;

    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_set_affinity)
    {
        if (!(err = pirq->pic->ops->irq_set_affinity(pirq, affinity)))
        {
            rt_memcpy(pirq->affinity, affinity, sizeof(pirq->affinity));
        }
    }

    return err;
}

rt_err_t rt_pic_irq_parent_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    rt_err_t err = -RT_ENOSYS;

    RT_ASSERT(pirq != RT_NULL);
    pirq = pirq->parent;

    if (pirq->pic->ops->irq_set_triger_mode)
    {
        if (!(err = pirq->pic->ops->irq_set_triger_mode(pirq, mode)))
        {
            pirq->mode = mode;
        }
    }

    return err;
}

#ifdef RT_USING_OFW
RT_OFW_STUB_RANGE_EXPORT(pic, _pic_ofw_start, _pic_ofw_end);

static rt_err_t ofw_pic_init(void)
{
    struct rt_ofw_node *ic_np;

    rt_ofw_foreach_node_by_prop(ic_np, "interrupt-controller")
    {
        rt_ofw_stub_probe_range(ic_np, &_pic_ofw_start, &_pic_ofw_end);
    }

    return RT_EOK;
}
#else
static rt_err_t ofw_pic_init(void)
{
    return RT_EOK;
}
#endif /* !RT_USING_OFW */

rt_err_t rt_pic_init(void)
{
    rt_err_t err;

    LOG_D("init start");

    err = ofw_pic_init();

    LOG_D("init end");

    return err;
}

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
static int list_irq(int argc, char**argv)
{
    rt_size_t irq_nr = 0;
    rt_bool_t dump_all = RT_FALSE;
    const char *const irq_modes[] =
    {
        [RT_IRQ_MODE_NONE] = "None",
        [RT_IRQ_MODE_EDGE_RISING] = "Edge-Rising",
        [RT_IRQ_MODE_EDGE_FALLING] = "Edge-Falling",
        [RT_IRQ_MODE_EDGE_BOTH] = "Edge-Both",
        [RT_IRQ_MODE_LEVEL_HIGH] = "Level-High",
        [RT_IRQ_MODE_LEVEL_LOW] = "Level-Low",
    };
    static char info[RT_CONSOLEBUF_SIZE];
#ifdef RT_USING_SMP
    static char cpumask[RT_CPUS_NR + 1] = { [RT_CPUS_NR] = '\0' };
#endif

    if (argc > 1)
    {
        if (!rt_strcmp(argv[1], "all"))
        {
            dump_all = RT_TRUE;
        }
    }

    rt_kprintf("%-*.s %-*.s %s %-*.s %-*.s %-*.s %-*.sUsers%-*.s",
            6, "IRQ",
            6, "HW-IRQ",
            "MSI",
            _pic_name_max, "PIC",
            12, "Mode",
        #ifdef RT_USING_SMP
            RT_CPUS_NR, "CPUs",
        #else
            0, 0,
        #endif
        #ifdef RT_USING_INTERRUPT_INFO
            11, "Count",
            5, ""
        #else
            0, 0,
            10, "-Number"
        #endif
            );

#if defined(RT_USING_SMP) && defined(RT_USING_INTERRUPT_INFO)
    for (int i = 0; i < RT_CPUS_NR; i++)
    {
        rt_kprintf(" cpu%2d     ", i);
    }
#endif

#ifdef RT_USING_PIC_STATISTICS
    rt_kprintf(" max/ns      avg/ns      min/ns");
#endif

    rt_kputs("\n");

    for (int i = 0; i < RT_ARRAY_SIZE(_pirq_hash); ++i)
    {
        struct rt_pic_irq *pirq = &_pirq_hash[i];

        if (!pirq->pic || !(dump_all || pirq->isr.action.handler))
        {
            continue;
        }

        rt_snprintf(info, sizeof(info), "%-6d %-6d %c   %-*.s %-*.s ",
                pirq->irq,
                pirq->hwirq,
                pirq->msi_desc ? 'Y' : 'N',
                _pic_name_max, pirq->pic->ops->name,
                12, irq_modes[pirq->mode]);

    #ifdef RT_USING_SMP
        for (int group = 0, id = 0; group < RT_ARRAY_SIZE(pirq->affinity); ++group)
        {
            rt_bitmap_t mask = pirq->affinity[group];

            for (int idx = 0; id < RT_CPUS_NR && idx < RT_BITMAP_BIT_LEN(1); ++idx, ++id)
            {
                cpumask[RT_ARRAY_SIZE(cpumask) - id - 2] = '0' + ((mask >> idx) & 1);
            }
        }
    #endif /* RT_USING_SMP */

        rt_kputs(info);
    #ifdef RT_USING_SMP
        rt_kputs(cpumask);
    #endif

    #ifdef RT_USING_INTERRUPT_INFO
        rt_kprintf(" %-10d ", pirq->isr.action.counter);
        rt_kprintf("%-*.s", 10, pirq->isr.action.name);
    #ifdef RT_USING_SMP
        for (int cpuid = 0; cpuid < RT_CPUS_NR; cpuid++)
        {
            rt_kprintf(" %-10d", pirq->isr.action.cpu_counter[cpuid]);
        }
    #endif
    #ifdef RT_USING_PIC_STATISTICS
        rt_kprintf(" %-10d  %-10d  %-10d", pirq->stat.max_irq_time_ns, pirq->stat.sum_irq_time_ns/pirq->isr.action.counter, pirq->stat.min_irq_time_ns);
    #endif
        rt_kputs("\n");

        if (!rt_list_isempty(&pirq->isr.list))
        {
            struct rt_pic_isr *repeat_isr;

            rt_list_for_each_entry(repeat_isr, &pirq->isr.list, list)
            {
                rt_kputs(info);
            #ifdef RT_USING_SMP
                rt_kputs(cpumask);
            #endif
                rt_kprintf("%-10d ", repeat_isr->action.counter);
                rt_kprintf("%-*.s", 10, repeat_isr->action.name);
            #ifdef RT_USING_SMP
                for (int cpuid = 0; cpuid < RT_CPUS_NR; cpuid++)
                {
                    rt_kprintf(" %-10d", repeat_isr->action.cpu_counter[cpuid]);
                }
            #endif
            #ifdef RT_USING_PIC_STATISTICS
                rt_kprintf(" ---         ---         ---");
            #endif
                rt_kputs("\n");
            }
        }
    #else
        rt_kprintf(" %d\n", rt_list_len(&pirq->isr.list));
    #endif

        ++irq_nr;
    }

    rt_kprintf("%d IRQs found\n", irq_nr);

    return 0;
}
MSH_CMD_EXPORT(list_irq, dump using or args = all of irq information);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
