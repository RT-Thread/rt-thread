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
    rt_err_t err;

    if (ep && ep->ops && hdr && func_no < ep->max_functions)
    {
        if (ep->ops->write_header)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->write_header(ep, func_no, hdr);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_set_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_err_t err = RT_EOK;

    if (ep && ep->ops && func_no < ep->max_functions && bar &&
        bar_idx < PCI_STD_NUM_BARS)
    {
        struct rt_pci_bus_resource *bus_bar = &bar->bus;

        if (bar_idx == (PCI_STD_NUM_BARS - 1) &&
            (bus_bar->flags & PCIM_BAR_MEM_TYPE_64))
        {
            err = -RT_EINVAL;
            LOG_E("%s: Set BAR[%d] can't not 64bit", ep->name, bar_idx);
        }

        if (rt_upper_32_bits(bus_bar->size) &&
            !(bus_bar->flags & PCIM_BAR_MEM_TYPE_64))
        {
            err = -RT_EINVAL;
            LOG_E("%s: Set BAR[%d] size is no support 64bit", ep->name, bar_idx);
        }

        if ((bus_bar->flags & PCIM_BAR_SPACE_IO) &&
            (bus_bar->flags & PCIM_BAR_IO_MASK))
        {
            err = -RT_EINVAL;
            LOG_E("%s: Set BAR[%d] io flags is invalid", ep->name, bar_idx);
        }

        if (!err)
        {
            if (ep->ops->set_bar)
            {
                rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
                err = ep->ops->set_bar(ep, func_no, bar, bar_idx);
                rt_mutex_release(&ep->lock);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pci_ep_clear_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions && bar &&
        bar_idx < PCI_STD_NUM_BARS)
    {
        if (ep->ops->clear_bar)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->clear_bar(ep, func_no, bar, bar_idx);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_map_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions && size)
    {
        if (ep->ops->map_addr)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->map_addr(ep, func_no, addr, pci_addr, size);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_unmap_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions)
    {
        if (ep->ops->unmap_addr)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->unmap_addr(ep, func_no, addr);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_set_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions)
    {
        if (ep->ops->set_msix)
        {
            err = -RT_EINVAL;

            for (int log2 = 0; log2 < 5; ++log2)
            {
                if (irq_nr <= (1 << log2))
                {
                    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
                    err = ep->ops->set_msi(ep, func_no, log2);
                    rt_mutex_release(&ep->lock);
                }
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

rt_err_t rt_pci_ep_get_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions && out_irq_nr)
    {
        if (ep->ops->get_msi)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->get_msi(ep, func_no, out_irq_nr);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_set_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr, int bar_idx, rt_off_t offset)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions && irq_nr < 2048 &&
        bar_idx < PCI_STD_NUM_BARS)
    {
        if (ep->ops->set_msix)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->set_msix(ep, func_no, irq_nr, bar_idx, offset);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_get_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions && out_irq_nr)
    {
        if (ep->ops->get_msix)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->get_msix(ep, func_no, out_irq_nr);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_raise_irq(struct rt_pci_ep *ep, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq)
{
    rt_err_t err;

    if (ep && ep->ops && func_no < ep->max_functions)
    {
        if (ep->ops->raise_irq)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->raise_irq(ep, func_no, type, irq);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_start(struct rt_pci_ep *ep)
{
    rt_err_t err;

    if (ep && ep->ops)
    {
        if (ep->ops->start)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->start(ep);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_stop(struct rt_pci_ep *ep)
{
    rt_err_t err;

    if (ep && ep->ops)
    {
        if (ep->ops->stop)
        {
            rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
            err = ep->ops->stop(ep);
            rt_mutex_release(&ep->lock);
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

rt_err_t rt_pci_ep_register(struct rt_pci_ep *ep)
{
    rt_ubase_t level;

    if (!ep || !ep->ops)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&ep->list);
    rt_ref_init(&ep->ref);

    rt_list_init(&ep->epf_nodes);
    rt_mutex_init(&ep->lock, ep->name, RT_IPC_FLAG_PRIO);

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

    if (rt_ref_read(&ep->ref) > 1)
    {
        err = -RT_EBUSY;
    }
    else
    {
        rt_list_remove(&ep->list);
        rt_mutex_detach(&ep->lock);
    }

    rt_spin_unlock_irqrestore(&_ep_lock, level);

    return err;
}

rt_err_t rt_pci_ep_add_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf)
{
    rt_err_t err = RT_EOK;

    if (!ep || !epf || !epf->name)
    {
        return -RT_EINVAL;
    }

    if (epf->func_no > ep->max_functions - 1)
    {
        LOG_E("%s function No(%d) > %s max function No(%d - 1)",
                epf->name, epf->func_no, ep->name, ep->max_functions);

        return -RT_EINVAL;
    }

    epf->ep = ep;
    rt_list_init(&epf->list);

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    if (!rt_bitmap_test_bit(ep->functions_map, epf->func_no))
    {
        rt_bitmap_set_bit(ep->functions_map, epf->func_no);
        rt_list_insert_before(&ep->epf_nodes, &epf->list);
    }
    else
    {
        err = -RT_EINVAL;
        LOG_E("%s function No(%d) is repeating", epf->name, epf->func_no);
    }

    rt_mutex_release(&ep->lock);

    return err;
}

rt_err_t rt_pci_ep_remove_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf)
{
    if (!ep || !epf)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);
    rt_bitmap_clear_bit(ep->functions_map, epf->func_no);
    rt_list_remove(&epf->list);
    rt_mutex_release(&ep->lock);

    return RT_EOK;
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
            rt_ref_get(&ep->ref);
            break;
        }
    }

    rt_spin_unlock_irqrestore(&_ep_lock, level);

    return ep;
}

static void pci_ep_release(struct rt_ref *ref)
{
    struct rt_pci_ep *ep = rt_container_of(ref, struct rt_pci_ep, ref);

    rt_pci_ep_unregister(ep);
}

void rt_pci_ep_put(struct rt_pci_ep *ep)
{
    if (ep)
    {
        rt_ref_put(&ep->ref, &pci_ep_release);
    }
}
