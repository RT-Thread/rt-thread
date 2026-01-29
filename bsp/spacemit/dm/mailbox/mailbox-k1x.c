/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mailbox.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SPACEMIT_NUM_CHANNELS   4
#define SPACEMIT_TX_ACK_OFFSET  4

#define MBOX_REG_IPC_DW         0x00
#define MBOX_REG_IPC_WDR        0x04
#define MBOX_REG_ISRW           0x08
#define MBOX_REG_ICR            0x0C
#define MBOX_REG_IIR            0x10
#define MBOX_REG_RDR            0x14

struct spacemit_mailbox
{
    struct rt_mbox_controller parent;

    int irq;
    void *regs;
    struct rt_reset_control *rstc;

    struct rt_mbox_chan chans[];
};

#define raw_to_spacemit_mailbox(raw) rt_container_of(raw, struct spacemit_mailbox, parent)

static rt_err_t spacemit_mailbox_request(struct rt_mbox_chan *chan)
{
    return RT_EOK;
}

static void spacemit_mailbox_release(struct rt_mbox_chan *chan)
{
    struct spacemit_mailbox *sp_mbox = raw_to_spacemit_mailbox(chan->ctrl);

    HWREG32(sp_mbox->regs + MBOX_REG_ICR) = RT_BIT(chan - sp_mbox->chans);
}

static rt_err_t spacemit_mailbox_send(struct rt_mbox_chan *chan, const void *data)
{
    struct spacemit_mailbox *sp_mbox = raw_to_spacemit_mailbox(chan->ctrl);

    HWREG32(sp_mbox->regs + MBOX_REG_ISRW) = RT_BIT(chan - sp_mbox->chans);

    return RT_EOK;
}

static rt_bool_t spacemit_mailbox_peek(struct rt_mbox_chan *chan)
{
    struct spacemit_mailbox *sp_mbox = raw_to_spacemit_mailbox(chan->ctrl);

    return !!(HWREG32(sp_mbox->regs + MBOX_REG_RDR) & RT_BIT(chan - sp_mbox->chans));
}

static const struct rt_mbox_controller_ops spacemit_mailbox_ops =
{
    .request = spacemit_mailbox_request,
    .release = spacemit_mailbox_release,
    .send = spacemit_mailbox_send,
    .peek = spacemit_mailbox_peek,
};

static void spacemit_mailbox_isr(int irqno, void *param)
{
    rt_uint32_t status, msg = 0;
    struct rt_mbox_chan *chan;
    struct spacemit_mailbox *sp_mbox = param;

    HWREG32(sp_mbox->regs + MBOX_REG_IIR) = 0;

    status = HWREG32(sp_mbox->regs + MBOX_REG_IIR);

    if (!(status & 0xff))
    {
        return;
    }

    for (int i = SPACEMIT_TX_ACK_OFFSET; i < SPACEMIT_NUM_CHANNELS + SPACEMIT_TX_ACK_OFFSET; ++i)
    {
        chan = &sp_mbox->chans[i - SPACEMIT_TX_ACK_OFFSET];

        if (!(status & RT_BIT(i)))
        {
            continue;
        }

        /* Clear the irq pending */
        HWREG32(sp_mbox->regs + MBOX_REG_ICR) = 1 << i;

        rt_mbox_send_done(chan, 0);
    }

    for (int i = 0; i < SPACEMIT_NUM_CHANNELS; ++i)
    {
        chan = &sp_mbox->chans[i];

        if (!(status & RT_BIT(i)))
        {
            continue;
        }

        rt_mbox_recv(chan, &msg);

        /* Clear the irq pending */
        HWREG32(sp_mbox->regs + MBOX_REG_ICR) = RT_BIT(i);

        /* Then send an ack */
        HWREG32(sp_mbox->regs + MBOX_REG_ISRW) = RT_BIT(i + SPACEMIT_TX_ACK_OFFSET);
    }
}

static void spacemit_mailbox_free_resource(struct spacemit_mailbox *sp_mbox)
{
    if (sp_mbox->regs)
    {
        rt_iounmap(sp_mbox->regs);
    }

    if (!rt_is_err_or_null(sp_mbox->rstc))
    {
        rt_reset_control_put(sp_mbox->rstc);
    }

    rt_free(sp_mbox);
}

static rt_err_t spacemit_mailbox_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_mailbox *sp_mbox = rt_calloc(1, sizeof(*sp_mbox) +
            SPACEMIT_NUM_CHANNELS * sizeof(struct rt_mbox_chan));

    if (!sp_mbox)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < SPACEMIT_NUM_CHANNELS; ++i)
    {
        sp_mbox->chans[i].priv = sp_mbox;
    }

    sp_mbox->regs = rt_dm_dev_iomap(dev, 0);

    if (!sp_mbox->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    sp_mbox->rstc = rt_reset_control_get_by_name(dev, "core_reset");

    if (rt_is_err(sp_mbox->rstc))
    {
        err = rt_ptr_err(sp_mbox->rstc);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(sp_mbox->rstc)))
    {
        goto _fail;
    }

    sp_mbox->irq = rt_dm_dev_get_irq(dev, 0);

    if (sp_mbox->irq < 0)
    {
        err = sp_mbox->irq;
        goto _fail;
    }

    rt_hw_interrupt_install(sp_mbox->irq, spacemit_mailbox_isr, sp_mbox, "sp_mbox");
    rt_hw_interrupt_umask(sp_mbox->irq);

    dev->user_data = sp_mbox;

    sp_mbox->parent.dev = dev;
    sp_mbox->parent.num_chans = SPACEMIT_NUM_CHANNELS;
    sp_mbox->parent.ops = &spacemit_mailbox_ops;

    if ((err = rt_mbox_controller_register(&sp_mbox->parent)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(sp_mbox->irq);
    rt_pic_detach_irq(sp_mbox->irq, sp_mbox);

_fail:
    spacemit_mailbox_free_resource(sp_mbox);

    return err;
}

static rt_err_t spacemit_mailbox_remove(struct rt_platform_device *pdev)
{
    struct spacemit_mailbox *sp_mbox = pdev->parent.user_data;

    rt_hw_interrupt_mask(sp_mbox->irq);
    rt_pic_detach_irq(sp_mbox->irq, sp_mbox);

    rt_mbox_controller_unregister(&sp_mbox->parent);

    spacemit_mailbox_free_resource(sp_mbox);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_mailbox_ofw_ids[] =
{
    { .compatible = "spacemit,k1-x-mailbox", },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_mailbox_driver =
{
    .name = "mailbox-spacemit",
    .ids = spacemit_mailbox_ofw_ids,

    .probe = spacemit_mailbox_probe,
    .remove = spacemit_mailbox_remove,
};

static int spacemit_mailbox_drv_register(void)
{
    rt_platform_driver_register(&spacemit_mailbox_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_mailbox_drv_register);
