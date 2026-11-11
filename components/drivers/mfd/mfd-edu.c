/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mfd.edu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#define PCI_EDU_REGS_BAR        0
#define EDU_REG_VERSION         0x00
#define EDU_REG_CARD_LIVENESS   0x04
#define EDU_REG_VALUE           0x08
#define EDU_REG_STATUS          0x20
#define     EDU_REG_STATUS_IRQ  0x80
#define EDU_REG_IRQ_STATUS      0x24
#define     EDU_REG_ISR_FACT    0x00000001
#define     EDU_REG_ISR_DMA     0x00000100
#define EDU_REG_IRQ_RAISE       0x60
#define EDU_REG_IRQ_ACK         0x64
#define EDU_REG_DMA_SRC         0x80
#define EDU_REG_DMA_DST         0x88
#define EDU_REG_DMA_SIZE        0x90
#define EDU_REG_DMA_CMD         0x98
#define   EDU_DMA_CMD_RUN       0x1
#define   EDU_DMA_CMD_TO_PCI    0x0
#define   EDU_DMA_CMD_FROM_PCI  0x2
#define   EDU_DMA_CMD_IRQ       0x4

#define EDU_FACTORIAL_ACK       0x00000001

#define EDU_DMA_ACK             0x00000100
#define EDU_DMA_FREE            (~0UL)
#define EDU_DMA_BASE            0x40000
#define EDU_DMA_SIZE            ((rt_size_t)(4096 - 1))
#define EDU_DMA_POLL_SIZE       128

struct edu_device
{
    struct rt_device parent;
    struct rt_dma_controller dma_ctrl;

    void *regs;
    rt_uint32_t ack;
    rt_bool_t dma_work;

    struct rt_mutex lock;
    struct rt_completion done;
};

#define raw_to_edu_device(raw)  rt_container_of(raw, struct edu_device, parent)
#define raw_to_edu_dma(raw)     rt_container_of(raw, struct edu_device, dma_ctrl)

rt_inline rt_uint32_t edu_readl(struct edu_device *edu, int offset)
{
    return HWREG32(edu->regs + offset);
}

rt_inline void edu_writel(struct edu_device *edu, int offset, rt_uint32_t value)
{
    HWREG32(edu->regs + offset) = value;
}

static rt_err_t edu_dma_start(struct rt_dma_chan *chan)
{
    rt_size_t len;
    rt_ubase_t dma_addr_src, dma_addr_dst;
    struct edu_device *edu = raw_to_edu_dma(chan->ctrl);

    rt_mutex_take(&edu->lock, RT_WAITING_FOREVER);

    edu->ack = EDU_DMA_ACK;
    edu->dma_work = RT_TRUE;

    len = chan->transfer.buffer_len;
    dma_addr_src = chan->transfer.src_addr;
    dma_addr_dst = chan->transfer.dst_addr;

    while ((rt_ssize_t)len > 0 && edu->dma_work)
    {
        rt_uint32_t cmd = EDU_DMA_CMD_RUN;
        rt_uint32_t blen = rt_min_t(rt_size_t, EDU_DMA_SIZE, len);

        if (blen > EDU_DMA_POLL_SIZE)
        {
            cmd |= EDU_DMA_CMD_IRQ;
        }

        edu_writel(edu, EDU_REG_DMA_SRC, dma_addr_src);
        edu_writel(edu, EDU_REG_DMA_DST, EDU_DMA_BASE);
        edu_writel(edu, EDU_REG_DMA_SIZE, blen);
        edu_writel(edu, EDU_REG_DMA_CMD, cmd | EDU_DMA_CMD_TO_PCI);

        if (cmd & EDU_DMA_CMD_IRQ)
        {
            rt_completion_wait(&edu->done, RT_WAITING_FOREVER);
        }
        else
        {
            while (edu_readl(edu, EDU_REG_DMA_CMD) & EDU_DMA_CMD_RUN)
            {
                rt_hw_cpu_relax();
            }
        }

        edu_writel(edu, EDU_REG_DMA_SRC, EDU_DMA_BASE);
        edu_writel(edu, EDU_REG_DMA_DST, dma_addr_dst);
        edu_writel(edu, EDU_REG_DMA_SIZE, blen);
        edu_writel(edu, EDU_REG_DMA_CMD, cmd | EDU_DMA_CMD_FROM_PCI);

        if (cmd & EDU_DMA_CMD_IRQ)
        {
            rt_completion_wait(&edu->done, RT_WAITING_FOREVER);
        }
        else
        {
            while (edu_readl(edu, EDU_REG_DMA_CMD) & EDU_DMA_CMD_RUN)
            {
                rt_hw_cpu_relax();
            }
        }

        len -= blen;
        dma_addr_src += blen;
        dma_addr_dst += blen;
    }

    rt_mutex_release(&edu->lock);

    rt_dma_chan_done(chan, chan->transfer.buffer_len - len);

    return RT_EOK;
}

static rt_err_t edu_dma_stop(struct rt_dma_chan *chan)
{
    struct edu_device *edu = raw_to_edu_dma(chan->ctrl);

    edu->dma_work = RT_FALSE;

    return RT_EOK;
}

static rt_err_t edu_dma_config(struct rt_dma_chan *chan,
        struct rt_dma_slave_config *conf)
{
    return RT_EOK;
}

static rt_err_t edu_dma_prep_memcpy(struct rt_dma_chan *chan,
        rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    return RT_EOK;
}

const static struct rt_dma_controller_ops edu_dma_ops =
{
    .start = edu_dma_start,
    .stop = edu_dma_stop,
    .config = edu_dma_config,
    .prep_memcpy = edu_dma_prep_memcpy,
};

static rt_ssize_t edu_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint32_t number;
    struct edu_device *edu = raw_to_edu_device(dev);

    rt_mutex_take(&edu->lock, RT_WAITING_FOREVER);

    number = edu_readl(edu, EDU_REG_VALUE);

    rt_mutex_release(&edu->lock);

    rt_memcpy(buffer, &number, rt_min(sizeof(number), size));

    return rt_min(sizeof(number), size);
}

static rt_ssize_t edu_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_uint32_t number = 0;
    struct edu_device *edu = raw_to_edu_device(dev);

    rt_memcpy(&number, buffer, rt_min(sizeof(number), size));

    rt_mutex_take(&edu->lock, RT_WAITING_FOREVER);

    edu->ack = EDU_FACTORIAL_ACK;
    edu_writel(edu, EDU_REG_STATUS, EDU_REG_STATUS_IRQ);
    edu_writel(edu, EDU_REG_VALUE, number);

    rt_completion_wait(&edu->done, RT_WAITING_FOREVER);

    rt_mutex_release(&edu->lock);

    return rt_min(sizeof(number), size);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops edu_ops =
{
    .read = edu_read,
    .write = edu_write,
};
#endif

static void edu_isr(int irqno, void *param)
{
    struct edu_device *edu = param;

    if (edu_readl(edu, EDU_REG_IRQ_STATUS) & (EDU_REG_ISR_FACT | EDU_REG_ISR_DMA))
    {
        edu_writel(edu, EDU_REG_IRQ_ACK, edu->ack);
        rt_completion_done(&edu->done);
    }
}

static rt_err_t edu_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct edu_device *edu = rt_calloc(1, sizeof(*edu));

    if (!edu)
    {
        return -RT_ENOMEM;
    }

    edu->regs = rt_pci_iomap(pdev, PCI_EDU_REGS_BAR);

    if (!edu->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    edu->dma_ctrl.dev = &pdev->parent;
    edu->dma_ctrl.ops = &edu_dma_ops;
    rt_dma_controller_add_direction(&edu->dma_ctrl, RT_DMA_MEM_TO_MEM);
    /* Config in QEMU option: -device edu,dma_mask=0xffffffff */
    rt_dma_controller_set_addr_mask(&edu->dma_ctrl, RT_DMA_ADDR_MASK(32));

    if ((err = rt_dma_controller_register(&edu->dma_ctrl)))
    {
        goto _fail;
    }

    edu->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    edu->parent.ops = &edu_ops;
#else
    edu->parent.read = edu_read;
    edu->parent.write = edu_write;
#endif

    if ((err = rt_device_register(&edu->parent, "edu", RT_DEVICE_FLAG_RDWR)))
    {
        goto _free_dma;
    }

    pdev->parent.user_data = edu;

    rt_mutex_init(&edu->lock, "edu", RT_IPC_FLAG_PRIO);
    rt_completion_init(&edu->done);

    rt_hw_interrupt_install(pdev->irq, edu_isr, edu, "edu");
    rt_pci_irq_unmask(pdev);

    LOG_D("EDU PCI device v%d.%d", edu_readl(edu, EDU_REG_VERSION) >> 16,
            (edu_readl(edu, EDU_REG_VERSION) >> 8) & 0xff);

    return RT_EOK;

_free_dma:
    rt_dma_controller_unregister(&edu->dma_ctrl);

_fail:
    if (edu->regs)
    {
        rt_iounmap(edu->regs);
    }

    rt_free(edu);

    return err;
}

static rt_err_t edu_remove(struct rt_pci_device *pdev)
{
    struct edu_device *edu = pdev->parent.user_data;

    /* INTx is shared, don't mask all */
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_mask(pdev);

    rt_dma_controller_unregister(&edu->dma_ctrl);
    rt_device_unregister(&edu->parent);

    rt_mutex_detach(&edu->lock);

    rt_iounmap(edu->regs);
    rt_free(edu);

    return RT_EOK;
}

static const struct rt_pci_device_id edu_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_QEMU, 0x11e8), },
    { /* sentinel */ }
};

static struct rt_pci_driver edu_driver =
{
    .name = "edu",

    .ids = edu_ids,
    .probe = edu_probe,
    .remove = edu_remove,
};
RT_PCI_DRIVER_EXPORT(edu_driver);
