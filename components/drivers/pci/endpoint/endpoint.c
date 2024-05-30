/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#include <drivers/pci_endpoint.h>

#define DBG_TAG "pci.ep"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_list_t _ep_nodes = RT_LIST_OBJECT_INIT(_ep_nodes);
static struct rt_spinlock _ep_lock = { 0 };

rt_err_t rt_pci_ep_write_header(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_header *hdr)
{
    if (ep && ep->ops && hdr)
    {
        if (ep->ops->write_header)
        {
            return ep->ops->write_header(ep, func_no, hdr);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_set_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_bus_resource *bar, int bar_idx)
{
    if (ep && ep->ops && bar && bar_idx < PCI_STD_NUM_BARS &&
        (bar->flags == PCI_BUS_REGION_F_NONE ||
        bar->flags == PCI_BUS_REGION_F_MEM ||
        bar->flags == PCI_BUS_REGION_F_IO ||
        bar->flags == PCI_BUS_REGION_F_PREFETCH))
    {
        if (ep->ops->set_bar)
        {
            return ep->ops->set_bar(ep, func_no, bar, bar_idx);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_clear_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        int bar_idx)
{
    if (ep && ep->ops && bar_idx < PCI_STD_NUM_BARS)
    {
        if (ep->ops->clear_bar)
        {
            return ep->ops->clear_bar(ep, func_no, bar_idx);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}


rt_err_t rt_pci_ep_map_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size)
{
    if (ep && ep->ops && size)
    {
        if (ep->ops->map_addr)
        {
            return ep->ops->map_addr(ep, func_no, addr, pci_addr, size);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_unmap_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr)
{
    if (ep && ep->ops)
    {
        if (ep->ops->unmap_addr)
        {
            return ep->ops->unmap_addr(ep, func_no, addr);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_set_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr)
{
    if (ep && ep->ops)
    {
        if (ep->ops->set_msix)
        {
            for (int log2 = 0; log2 < 5; ++log2)
            {
                if (irq_nr <= (1 << log2))
                {
                    return ep->ops->set_msix(ep, func_no, log2);
                }
            }

            return -RT_EINVAL;
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_get_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    if (ep && ep->ops && out_irq_nr)
    {
        if (ep->ops->get_msi)
        {
            return ep->ops->get_msi(ep, func_no, out_irq_nr);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_set_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr)
{
    if (ep && ep->ops && irq_nr < 2048)
    {
        if (ep->ops->set_msix)
        {
            return ep->ops->set_msix(ep, func_no, irq_nr);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_get_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    if (ep && ep->ops && out_irq_nr)
    {
        if (ep->ops->get_msix)
        {
            return ep->ops->get_msix(ep, func_no, out_irq_nr);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_raise_irq(struct rt_pci_ep *ep, rt_uint8_t func_no,
        enum rt_pci_ep_pin pin, unsigned irq)
{
    if (ep && ep->ops)
    {
        if (ep->ops->raise_irq)
        {
            return ep->ops->raise_irq(ep, func_no, pin, irq);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_start(struct rt_pci_ep *ep)
{
    if (ep && ep->ops)
    {
        if (ep->ops->start)
        {
            return ep->ops->start(ep);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_stop(struct rt_pci_ep *ep)
{
    if (ep && ep->ops)
    {
        if (ep->ops->stop)
        {
            return ep->ops->stop(ep);
        }

        return -RT_ENOSYS;
    }

    return -RT_EINVAL;
}

rt_err_t rt_pci_ep_register(struct rt_pci_ep *ep)
{
    rt_ubase_t level;

    if (!ep || !ep->ops)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&ep->list);
    ref_init(&ep->ref);

    level = rt_spin_lock_irqsave(&_ep_lock);
    rt_list_insert_before(&_ep_nodes, &ep->list);
    rt_spin_unlock_irqrestore(&_ep_lock, level);

    return RT_EOK;
}

rt_err_t rt_pci_ep_unregister(struct rt_pci_ep *ep)
{
    rt_ubase_t level;
    rt_err_t err = RT_EOK;

    if (!ep)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&_ep_lock);

    if (ref_read(&ep->ref) > 1)
    {
        err = -RT_EBUSY;
    }
    else
    {
        rt_list_remove(&ep->list);
    }

    rt_spin_unlock_irqrestore(&_ep_lock, level);

    return err;
}

struct rt_pci_ep *rt_pci_ep_get(const char *name)
{
    rt_ubase_t level;
    struct rt_pci_ep *ep = RT_NULL, *ep_tmp;

    level = rt_spin_lock_irqsave(&_ep_lock);

    rt_list_for_each_entry(ep_tmp, &_ep_nodes, list)
    {
        if (!name || !rt_strcmp(ep_tmp->name, name))
        {
            ep = ep_tmp;
            ref_get(&ep->ref);
            break;
        }
    }

    rt_spin_unlock_irqrestore(&_ep_lock, level);

    return ep;
}

static void pci_ep_release(struct ref *ref)
{
    struct rt_pci_ep *ep = rt_container_of(ref, struct rt_pci_ep, ref);

    rt_pci_ep_unregister(ep);
}

void rt_pci_ep_put(struct rt_pci_ep *ep)
{
    if (ep)
    {
        ref_put(&ep->ref, &pci_ep_release);
    }
}
