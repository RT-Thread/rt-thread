/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

/* Mailboxes */
#define ARM_0_MAIL0             0x00
#define ARM_0_MAIL1             0x20

/*
 * Mailbox registers. We basically only support mailbox 0 & 1. We
 * deliver to the VC in mailbox 1, it delivers to us in mailbox 0. See
 * BCM2835-ARM-Peripherals.pdf section 1.3 for an explanation about
 * the placement of memory barriers.
 */
#define MAIL0_RD                (ARM_0_MAIL0 + 0x00)
#define MAIL0_POL               (ARM_0_MAIL0 + 0x10)
#define MAIL0_STA               (ARM_0_MAIL0 + 0x18)
#define MAIL0_CNF               (ARM_0_MAIL0 + 0x1C)
#define MAIL1_WRT               (ARM_0_MAIL1 + 0x00)
#define MAIL1_STA               (ARM_0_MAIL1 + 0x18)

/* Status register: FIFO state. */
#define ARM_MS_FULL             RT_BIT(31)
#define ARM_MS_EMPTY            RT_BIT(30)

/* Configuration register: Enable interrupts. */
#define ARM_MC_IHAVEDATAIRQEN   RT_BIT(0)

struct bcm2835_mbox
{
    struct rt_mbox_controller parent;

    int irq;
    void *regs;
    struct rt_spinlock lock;
};

#define raw_to_bcm2835_mbox(raw) rt_container_of(raw, struct bcm2835_mbox, parent)

rt_inline rt_uint32_t bcm2835_mbox_readl(struct bcm2835_mbox *bcm_mbox, int offset)
{
    return HWREG32(bcm_mbox->regs + offset);
}

rt_inline void bcm2835_mbox_writel(struct bcm2835_mbox *bcm_mbox, int offset,
        rt_uint32_t value)
{
    HWREG32(bcm_mbox->regs + offset) = value;
}

static rt_err_t bcm2835_mbox_request(struct rt_mbox_chan *chan)
{
    struct bcm2835_mbox *bcm_mbox = raw_to_bcm2835_mbox(chan->ctrl);

    /* Enable the interrupt on data reception */
    bcm2835_mbox_writel(bcm_mbox, MAIL0_CNF, ARM_MC_IHAVEDATAIRQEN);

    return RT_EOK;
}

static void bcm2835_mbox_release(struct rt_mbox_chan *chan)
{
    struct bcm2835_mbox *bcm_mbox = raw_to_bcm2835_mbox(chan->ctrl);

    bcm2835_mbox_writel(bcm_mbox, MAIL0_CNF, 0);
}

static rt_err_t bcm2835_mbox_send(struct rt_mbox_chan *chan, const void *data)
{
    rt_err_t err = -RT_ETIMEOUT;
    rt_int32_t timeout_us = 1000000;
    rt_uint32_t msg = *(rt_uint32_t *)data;
    struct bcm2835_mbox *bcm_mbox = raw_to_bcm2835_mbox(chan->ctrl);

    rt_spin_lock(&bcm_mbox->lock);

    /*
     * Property channel replies are polled synchronously. Mask the mailbox
     * interrupt while waiting so the ISR cannot consume the reply first and
     * leave the poll loop timing out spuriously.
     */
    rt_hw_interrupt_mask(bcm_mbox->irq);

    while (bcm2835_mbox_readl(bcm_mbox, MAIL1_STA) & ARM_MS_FULL)
    {
        rt_spin_unlock(&bcm_mbox->lock);
        rt_hw_us_delay(10);
        rt_spin_lock(&bcm_mbox->lock);
    }

    bcm2835_mbox_writel(bcm_mbox, MAIL1_WRT, msg);
    rt_hw_wmb();

    while (timeout_us > 0)
    {
        rt_uint32_t sta = bcm2835_mbox_readl(bcm_mbox, MAIL0_STA);

        if (!(sta & ARM_MS_EMPTY))
        {
            rt_uint32_t reply = bcm2835_mbox_readl(bcm_mbox, MAIL0_RD);

            rt_mbox_recv(chan, &reply);
            err = RT_EOK;
            break;
        }

        rt_hw_us_delay(10);
        timeout_us -= 10;
    }

    rt_hw_interrupt_umask(bcm_mbox->irq);
    rt_spin_unlock(&bcm_mbox->lock);

    return err;
}

static int bcm2835_mbox_ofw_parse(struct rt_mbox_controller *ctrl,
        struct rt_ofw_cell_args *args)
{
    if (args->args_count != 0)
    {
        return -RT_EINVAL;
    }

    return 0;
}

static const struct rt_mbox_controller_ops bcm2835_mbox_ops =
{
    .request = bcm2835_mbox_request,
    .release = bcm2835_mbox_release,
    .send = bcm2835_mbox_send,
    .ofw_parse = bcm2835_mbox_ofw_parse,
};

static void bcm2835_mbox_isr(int irqno, void *param)
{
    struct bcm2835_mbox *bcm_mbox = param;

    while (!(bcm2835_mbox_readl(bcm_mbox, MAIL0_STA) & ARM_MS_EMPTY))
    {
        rt_uint32_t msg = bcm2835_mbox_readl(bcm_mbox, MAIL0_RD);

        rt_mbox_recv(&bcm_mbox->parent.chans[0], &msg);
    }
}

static rt_err_t bcm2835_mbox_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_mbox *bcm_mbox = rt_calloc(1, sizeof(*bcm_mbox));

    if (!bcm_mbox)
    {
        return -RT_ENOMEM;
    }

    bcm_mbox->regs = rt_dm_dev_iomap(dev, 0);

    if (!bcm_mbox->regs)
    {
        err = -RT_EIO;

        goto _fail;
    }

    bcm_mbox->irq = rt_dm_dev_get_irq(dev, 0);

    if (bcm_mbox->irq < 0)
    {
        err = bcm_mbox->irq;

        goto _fail;
    }

    dev->user_data = bcm_mbox;

    rt_hw_interrupt_install(bcm_mbox->irq, bcm2835_mbox_isr, bcm_mbox, "bcm2835-mbox");
    rt_hw_interrupt_umask(bcm_mbox->irq);

    bcm_mbox->parent.dev = dev;
    bcm_mbox->parent.num_chans = 1;
    bcm_mbox->parent.ops = &bcm2835_mbox_ops;

    if ((err = rt_mbox_controller_register(&bcm_mbox->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (bcm_mbox->regs)
    {
        rt_iounmap(bcm_mbox->regs);
    }

    rt_free(bcm_mbox);

    return err;
}

static rt_err_t bcm2835_mbox_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_mbox *bcm_mbox = pdev->parent.user_data;

    rt_hw_interrupt_mask(bcm_mbox->irq);
    rt_pic_detach_irq(bcm_mbox->irq, bcm_mbox);

    rt_mbox_controller_unregister(&bcm_mbox->parent);

    rt_iounmap(bcm_mbox->regs);

    rt_free(bcm_mbox);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_mbox_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-mbox" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_mbox_driver =
{
    .name = "mailbox-bcm2835",
    .ids = bcm2835_mbox_ofw_ids,

    .probe = bcm2835_mbox_probe,
    .remove = bcm2835_mbox_remove,
};

static int bcm2835_mbox_drv_register(void)
{
    rt_platform_driver_register(&bcm2835_mbox_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2835_mbox_drv_register);
