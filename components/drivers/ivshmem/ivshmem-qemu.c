/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-27     GuEe-GUI     first version
 */

#include "ivshmem.h"

struct qemu_ivshmem
{
    struct ivshmem_device parent;

    rt_bool_t is_msx;
    rt_uint32_t irq_status;
    rt_event_t irq_event;
    struct rt_spinlock rw_lock;
};

#define raw_to_qemu_ivshmem(raw) rt_container_of(raw, struct qemu_ivshmem, parent)

static rt_bool_t rw_count_fixup(struct ivshmem_device *ivdev, rt_off_t pos, rt_size_t *count)
{
    if (pos < ivdev->shmem_size)
    {
        if (pos + *count > ivdev->shmem_size)
        {
            *count = ivdev->shmem_size - pos;
        }

        return RT_TRUE;
    }
    else
    {
        *count = 0;
    }

    return RT_FALSE;
}

static rt_ssize_t qemu_ivshmem_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t count)
{
    struct ivshmem_device *ivdev = &raw_to_qemu_ivshmem(dev)->parent;

    if (rw_count_fixup(ivdev, pos, &count))
    {
        rt_memcpy(buffer, (void *)(ivdev->shmem + pos), count);
    }

    return count;
}

static rt_ssize_t qemu_ivshmem_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t count)
{
    struct ivshmem_device *ivdev = &raw_to_qemu_ivshmem(dev)->parent;

    if (rw_count_fixup(ivdev, pos, &count))
    {
        rt_memcpy((void *)(ivdev->shmem + pos), buffer, count);
    }

    return count;
}

static rt_err_t qemu_ivshmem_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct qemu_ivshmem *qemu_ivshmem = raw_to_qemu_ivshmem(dev);
    struct ivshmem_device *ivdev = &qemu_ivshmem->parent;

    if (!args && cmd != RT_DEVICE_CTRL_CLR_INT)
    {
        cmd = 0;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CONFIG:
    {
        struct ivshmem_cmd *user_cmd = args;

        if (user_cmd->is_read)
        {
            user_cmd->value = HWREG32(ivdev->reg + user_cmd->reg_off);
        }
        else
        {
            HWREG32(ivdev->reg + user_cmd->reg_off) = user_cmd->value;
        }

        break;
    }
    case RT_DEVICE_CTRL_SET_INT:
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&qemu_ivshmem->rw_lock);

        qemu_ivshmem->irq_event = args;

        rt_spin_unlock_irqrestore(&qemu_ivshmem->rw_lock, level);

        break;
    }
    case RT_DEVICE_CTRL_CLR_INT:
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&qemu_ivshmem->rw_lock);

        qemu_ivshmem->irq_event = RT_NULL;

        rt_spin_unlock_irqrestore(&qemu_ivshmem->rw_lock, level);

        break;
    }
    case RT_DEVICE_CTRL_GET_INT:
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&qemu_ivshmem->rw_lock);

        *((rt_uint32_t *)args) = qemu_ivshmem->irq_status;
        /* Only read once */
        qemu_ivshmem->irq_status = 0;

        rt_spin_unlock_irqrestore(&qemu_ivshmem->rw_lock, level);

        break;
    }
    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops qemu_ivshmem_ops =
{
    .read = qemu_ivshmem_read,
    .write = qemu_ivshmem_write,
    .control = qemu_ivshmem_control
};
#endif

static rt_err_t qemu_ivshmem_isr(struct ivshmem_device *ivdev, int irq)
{
    struct qemu_ivshmem *qemu_ivshmem = raw_to_qemu_ivshmem(ivdev);

    rt_spin_lock(&qemu_ivshmem->rw_lock);

    if (qemu_ivshmem->is_msx)
    {
        qemu_ivshmem->irq_status |= 1 << (irq - qemu_ivshmem->parent.msix_entries[0].irq);
    }
    else
    {
        qemu_ivshmem->irq_status = RT_UINT32_MAX;
    }

    if (qemu_ivshmem->irq_event)
    {
        rt_event_send(qemu_ivshmem->irq_event, qemu_ivshmem->irq_status);
    }

    rt_spin_unlock(&qemu_ivshmem->rw_lock);

    return RT_EOK;
}

static rt_err_t qemu_ivshmem_probe(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;
    const char *dev_name;
    struct rt_device *parent;
    struct qemu_ivshmem *qivdev = rt_calloc(1, sizeof(*qivdev));

    if (!qivdev)
    {
        return -RT_ENOMEM;
    }

    if ((err = ivshmem_pci_probe(pdev, &qivdev->parent)))
    {
        goto _fail;
    }

    parent = &qivdev->parent.parent;

    rt_dm_dev_set_name_auto(parent, "ivshmem");
    dev_name = rt_dm_dev_get_name(parent);

    qivdev->parent.handle_irq = qemu_ivshmem_isr;
    qivdev->irq_event = RT_NULL;
    rt_spin_lock_init(&qivdev->rw_lock);

    /* rt_event_t supports only 32 events */
    if (!ivshmem_install_msix_vectors(&qivdev->parent, 32, dev_name))
    {
        qivdev->is_msx = RT_TRUE;
    }
    else
    {
        qivdev->is_msx = RT_FALSE;
        ivshmem_install_intx_vector(&qivdev->parent, dev_name);
    }

    parent->type = RT_Device_Class_MTD;
#ifdef RT_USING_DEVICE_OPS
    parent->ops = &qemu_ivshmem_ops;
#else
    parent->read = qemu_ivshmem_read;
    parent->write = qemu_ivshmem_write;
    parent->control = qemu_ivshmem_control;
#endif

    rt_device_register(parent, dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);

    return RT_EOK;

_fail:
    rt_free(qivdev);

    return err;
}

static rt_err_t qemu_ivshmem_remove(struct rt_pci_device *pdev)
{
    struct ivshmem_device *ivdev = ivshmem_pci_remove(pdev);
    struct qemu_ivshmem *qivdev = raw_to_qemu_ivshmem(ivdev);

    rt_device_unregister(&qivdev->parent.parent);
    rt_free(qivdev);

    return RT_EOK;
}

static const struct rt_pci_device_id qemu_ivshmem_pci_ids[] =
{
    {
        RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT_QUMRANET, 0x1110),
        .class = PCIC_MEMORY << 16,
        .class_mask = 0xff << 16,
    },
    { /* sentinel */ }
};

static struct rt_pci_driver qemu_ivshmem_driver =
{
    .name = "ivshmem-qemu",

    .ids = qemu_ivshmem_pci_ids,
    .probe = qemu_ivshmem_probe,
    .remove = qemu_ivshmem_remove,
};
RT_PCI_DRIVER_EXPORT(qemu_ivshmem_driver);

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
#include <stdlib.h>

static int ivshmem_qemu(int argc, char**argv)
{
    rt_err_t err = -RT_EINVAL, res;
    const char *dev_name, *opt;
    struct ivshmem_cmd cmd;
    struct rt_device *ivdev;

    if (argc < 3)
    {
        goto _help;
    }

    dev_name = argv[1];
    ivdev = rt_device_find(dev_name);

    if (!ivdev)
    {
        rt_kprintf("dev '%s' not found\n", dev_name);
        goto _help;
    }

    if (rt_device_open(ivdev, 0))
    {
        rt_kprintf("dev '%s' open fail\n", dev_name);
        goto _help;
    }

    err = RT_EOK;
    opt = argv[2];

    if (!rt_strcmp(opt, "info"))
    {
        cmd.is_read = RT_TRUE;
        cmd.reg_off = IVSHMEM_IV_POSITION;

        res = rt_device_control(ivdev, RT_DEVICE_CTRL_CONFIG, &cmd);

        if (!res)
        {
            rt_kprintf("%s ivposition = %d\n", dev_name, cmd.value);
        }

        goto _end;
    }

    if (!rt_strcmp(opt, "set-int") && argc == 5)
    {
        cmd.is_read = RT_FALSE;
        cmd.reg_off = IVSHMEM_DOORBELL;
        cmd.value = ivshmem_doorbell(atol(argv[3]), atol(argv[4]));

        res = rt_device_control(ivdev, RT_DEVICE_CTRL_CONFIG, &cmd);

        if (!res)
        {
            rt_kprintf("%s set doorbell OK\n", dev_name);
        }

        goto _end;
    }

    if (!rt_strcmp(opt, "get-int"))
    {
        rt_event_t ev = rt_event_create("ivshmem", RT_IPC_FLAG_PRIO);

        if (!ev)
        {
            rt_kprintf("create event fail\n");
        }

        res = rt_device_control(ivdev, RT_DEVICE_CTRL_SET_INT, ev);

        if (!res)
        {
            rt_uint32_t irq_status;

            if (!rt_event_recv(ev, RT_UINT32_MAX, RT_EVENT_FLAG_OR, RT_WAITING_FOREVER, &irq_status))
            {
                rt_kprintf("irq status = 0x%x\n", irq_status);
            }

            rt_device_control(ivdev, RT_DEVICE_CTRL_CLR_INT, RT_NULL);
        }

        rt_event_delete(ev);

        goto _end;
    }

    if (!rt_strcmp(opt, "write") && argc == 5)
    {
        rt_device_write(ivdev, atol(argv[3]), argv[4], rt_strlen(argv[4]));

        goto _end;
    }

    if (!rt_strcmp(opt, "read") && argc == 5)
    {
        long pos = atol(argv[3]);
        long size = atol(argv[4]);

        while (size --> 0)
        {
            rt_uint8_t value;
            rt_device_read(ivdev, pos, &value, 1);

            rt_kprintf("[%2d] = %02x (%c)\n", pos, value, value);

            ++pos;
        }

        goto _end;
    }

    err = -RT_EINVAL;

_help:
    if (err)
    {
        const char *cmd_prefix = "\t " RT_STRINGIFY(__FUNCTION__) " <dev> ";

        rt_kputs("Usage:\n");
        rt_kprintf("%s%s\n", cmd_prefix, "info");
        rt_kprintf("%s%s <peer-id> <vector-index>\n", cmd_prefix, "set-int");
        rt_kprintf("%s%s\n", cmd_prefix, "get-int");
        rt_kprintf("%s%s <pos> <value>\n", cmd_prefix, "write");
        rt_kprintf("%s%s <pos> <size>\n", cmd_prefix, "read");
    }

_end:
    return err;
}
MSH_CMD_EXPORT(ivshmem_qemu, ivshmem qemu device command);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
