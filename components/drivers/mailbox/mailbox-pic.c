/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mailbox.pic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * RT-Thread PIC Mailbox device driver
 *
 * The mailbox device(s) may be instantiated in one of three equivalent way:
 *
 * Device Tree node, eg.:
 *
 *      interrupt-controller@0 {
 *          interrupt-controller;
 *          #interrupt-cells = <1>;
 *      };
 *
 *      pic_mailbox@10000 {
 *          compatible = "rt-thread,pic-mailbox";
 *          reg = <0x10000 0x100>;
 *          position = <0>;
 *          interrupts = <34>;
 *          peer-interrupts = <35>;
 *          uid = <0>;
 *          #mbox-cells = <1>;
 *      };
 */

#define MAILBOX_IMASK       0x00
#define MAILBOX_ISTATE      0x04
#define MAILBOX_MSG(n)      (0x08 + (n) * 4)

struct pic_mbox
{
    struct rt_mbox_controller parent;

    void *regs;
    void *peer_regs;

    int position;
    int chans_nr;
    int irq;
    int peer_hwirq;
    struct rt_pic *pic;

    struct rt_spinlock lock;
};

#define raw_to_pic_mbox(raw) rt_container_of(raw, struct pic_mbox, parent)

static rt_err_t pic_mbox_request(struct rt_mbox_chan *chan)
{
    int index = chan - chan->ctrl->chans;
    struct pic_mbox *pic_mbox = raw_to_pic_mbox(chan->ctrl);

    HWREG32(pic_mbox->regs + MAILBOX_IMASK) &= ~RT_BIT(index);

    return RT_EOK;
}

static void pic_mbox_release(struct rt_mbox_chan *chan)
{
    int index = chan - chan->ctrl->chans;
    struct pic_mbox *pic_mbox = raw_to_pic_mbox(chan->ctrl);

    HWREG32(pic_mbox->regs + MAILBOX_IMASK) |= RT_BIT(index);
}

static rt_err_t pic_mbox_send(struct rt_mbox_chan *chan, const void *data)
{
    rt_ubase_t level;
    int index = chan - chan->ctrl->chans;
    struct pic_mbox *pic_mbox = raw_to_pic_mbox(chan->ctrl);

    while (HWREG32(pic_mbox->peer_regs + MAILBOX_ISTATE) & RT_BIT(index))
    {
        rt_thread_yield();
    }

    level = rt_spin_lock_irqsave(&pic_mbox->lock);

    HWREG32(pic_mbox->regs + MAILBOX_MSG(index)) = *(rt_uint32_t *)data;
    HWREG32(pic_mbox->peer_regs + MAILBOX_ISTATE) |= RT_BIT(index);
    rt_hw_wmb();

    rt_pic_irq_set_state_raw(pic_mbox->pic, pic_mbox->peer_hwirq,
            RT_IRQ_STATE_PENDING, RT_TRUE);

    rt_spin_unlock_irqrestore(&pic_mbox->lock, level);

    return RT_EOK;
}

static const struct rt_mbox_controller_ops pic_mbox_ops =
{
    .request = pic_mbox_request,
    .release = pic_mbox_release,
    .send = pic_mbox_send,
};

static void pic_mbox_isr(int irqno, void *param)
{
    rt_uint32_t isr;
    struct pic_mbox *pic_mbox = param;

    isr = HWREG32(pic_mbox->regs + MAILBOX_ISTATE);

    for (int idx = 0; idx < 32; ++idx)
    {
        rt_uint32_t msg;

        if (!(RT_BIT(idx) & isr))
        {
            continue;
        }

        rt_hw_rmb();
        msg = HWREG32(pic_mbox->peer_regs + MAILBOX_MSG(idx));

        rt_mbox_recv(&pic_mbox->parent.chans[idx], &msg);
    }

    HWREG32(pic_mbox->regs + MAILBOX_ISTATE) &= ~isr;
}

static void pic_mbox_free_resource(struct pic_mbox *pic_mbox)
{
    if (pic_mbox->regs && pic_mbox->peer_regs)
    {
        if (pic_mbox->peer_regs > pic_mbox->regs)
        {
            rt_iounmap(pic_mbox->regs);
        }
        else
        {
            rt_iounmap(pic_mbox->peer_regs);
        }
    }

    rt_free(pic_mbox);
}

static rt_err_t pic_mbox_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t size;
    rt_uint32_t value;
    char dev_name[RT_NAME_MAX];
    struct rt_ofw_node *pic_np;
    struct rt_device *dev = &pdev->parent;
    struct pic_mbox *pic_mbox = rt_calloc(1, sizeof(*pic_mbox));

    if (!pic_mbox)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_dm_dev_get_address(dev, 0, RT_NULL, &size)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "position", &value)))
    {
        goto _fail;
    }

    if (!value)
    {
        pic_mbox->regs = rt_dm_dev_iomap(dev, 0);

        if (!pic_mbox->regs)
        {
            goto _fail;
        }

        pic_mbox->peer_regs = pic_mbox->regs + size / 2;
    }
    else
    {
        pic_mbox->peer_regs = rt_dm_dev_iomap(dev, 0);

        if (!pic_mbox->peer_regs)
        {
            goto _fail;
        }

        pic_mbox->regs = pic_mbox->peer_regs + size / 2;
    }

    pic_mbox->irq = rt_dm_dev_get_irq(dev, 0);

    if (pic_mbox->irq < 0)
    {
        err = pic_mbox->irq;

        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "peer-interrupts", &value)))
    {
        goto _fail;
    }
    pic_mbox->peer_hwirq = value;

    if ((err = rt_dm_dev_prop_read_u32(dev, "uid", &value)))
    {
        goto _fail;
    }

    if (!(pic_np = rt_ofw_find_irq_parent(dev->ofw_node, RT_NULL)))
    {
        goto _fail;
    }
    pic_mbox->pic = rt_ofw_data(pic_np);
    rt_ofw_node_put(pic_np);

    rt_spin_lock_init(&pic_mbox->lock);

    pic_mbox->parent.dev = dev;
    pic_mbox->parent.num_chans = 32;
    pic_mbox->parent.ops = &pic_mbox_ops;

    if ((err = rt_mbox_controller_register(&pic_mbox->parent)))
    {
        goto _fail;
    }

    rt_snprintf(dev_name, sizeof(dev_name), "pic-mbox%d", value);
    rt_hw_interrupt_install(pic_mbox->irq, pic_mbox_isr, pic_mbox, dev_name);
    rt_hw_interrupt_umask(pic_mbox->irq);

    return RT_EOK;

_fail:
    pic_mbox_free_resource(pic_mbox);

    return err;
}

static rt_err_t pic_mbox_remove(struct rt_platform_device *pdev)
{
    struct pic_mbox *pic_mbox = pdev->parent.user_data;

    rt_pic_detach_irq(pic_mbox->irq, pic_mbox);

    rt_mbox_controller_unregister(&pic_mbox->parent);

    pic_mbox_free_resource(pic_mbox);

    return RT_EOK;
}

static const struct rt_ofw_node_id pic_mbox_ofw_ids[] =
{
    { .compatible = "rt-thread,pic-mailbox" },
    { /* sentinel */ }
};

static struct rt_platform_driver pic_mbox_driver =
{
    .name = "mailbox-pic",
    .ids = pic_mbox_ofw_ids,

    .probe = pic_mbox_probe,
    .remove = pic_mbox_remove,
};
RT_PLATFORM_DRIVER_EXPORT(pic_mbox_driver);
