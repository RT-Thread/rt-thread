/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     first version
 */

#include <rtdef.h>
#include <drivers/byteorder.h>

#define DBG_TAG "pci.procfs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "procfs.h"
#ifdef RT_USING_LWP
#include <lwp_user_mm.h>
#endif

static struct rt_bus *pci_bus;
static struct proc_dentry *pci_proc_dentry;

rt_inline void copy_to_user(void *to, void *from, size_t size)
{
#ifdef RT_USING_LWP
    if (!lwp_put_to_user(to, from, size))
#endif
    {
        rt_memcpy(to, from, size);
    }
}

rt_inline void copy_from_user(void *to, const void *from, size_t size)
{
#ifdef RT_USING_LWP
    if (!lwp_get_from_user(to, (void *)from, size))
#endif
    {
        rt_memcpy(to, (void *)from, size);
    }
}

static void pci_pm_runtime_get(struct rt_pci_device *pdev, rt_ubase_t *out_flags)
{
    *out_flags = pdev->pm_enabled;

    if (!pdev->pm_enabled)
    {
        rt_pci_pme_active(pdev, RT_TRUE);
    }
}

static void pci_pm_runtime_put(struct rt_pci_device *pdev, rt_ubase_t *flags)
{
    if (!*flags)
    {
        rt_pci_pme_active(pdev, RT_FALSE);
    }
}

static ssize_t pci_read(struct dfs_file *file, void *buf, size_t count, off_t *ppos)
{
    off_t pos = *ppos;
    size_t res = count;
    rt_ubase_t pm_flags;
    struct proc_dentry *dentry = file->vnode->data;
    struct rt_pci_device *pdev = dentry->data;

    pci_pm_runtime_get(pdev, &pm_flags);

    if ((pos & 1) && count)
    {
        rt_uint8_t val;

        rt_pci_read_config_u8(pdev, pos, &val);
        copy_to_user(buf, &val, sizeof(val));

        ++buf;
        ++pos;
        --count;
    }

    if ((pos & 3) && count > 2)
    {
        rt_uint16_t val;

        rt_pci_read_config_u16(pdev, pos, &val);

        val = rt_cpu_to_le16(val);
        copy_to_user(buf, &val, sizeof(val));

        buf += 2;
        pos += 2;
        count -= 2;
    }

    while (count >= 4)
    {
        rt_uint32_t val;

        rt_pci_read_config_u32(pdev, pos, &val);

        val = rt_cpu_to_le32(val);
        copy_to_user(buf, &val, sizeof(val));

        buf += 4;
        pos += 4;
        count -= 4;
    }

    if (count >= 2)
    {
        rt_uint16_t val;

        rt_pci_read_config_u16(pdev, pos, &val);

        val = rt_cpu_to_le16(val);
        copy_to_user(buf, &val, sizeof(val));

        buf += 2;
        pos += 2;
        count -= 2;
    }

    if (count)
    {
        rt_uint8_t val;

        rt_pci_read_config_u8(pdev, pos, &val);
        copy_to_user(buf, &val, sizeof(val));

        ++pos;
    }

    pci_pm_runtime_put(pdev, &pm_flags);

    *ppos = pos;

    return res;
}

static ssize_t pci_write(struct dfs_file *file, const void *buf, size_t count, off_t *ppos)
{
    off_t pos = *ppos;
    size_t res = count;
    rt_ubase_t pm_flags;
    struct proc_dentry *dentry = file->vnode->data;
    struct rt_pci_device *pdev = dentry->data;

    pci_pm_runtime_get(pdev, &pm_flags);

    if ((pos & 1) && count)
    {
        rt_uint8_t val;

        copy_from_user(&val, buf, sizeof(val));
        rt_pci_write_config_u8(pdev, pos, val);

        ++buf;
        ++pos;
        --count;
    }

    if ((pos & 3) && count > 2)
    {
        rt_le16_t val;

        copy_from_user(&val, buf, sizeof(val));
        rt_pci_write_config_u16(pdev, pos, rt_le16_to_cpu(val));

        buf += 2;
        pos += 2;
        count -= 2;
    }

    while (count >= 4)
    {
        rt_le32_t val;

        copy_from_user(&val, buf, sizeof(val));
        rt_pci_write_config_u32(pdev, pos, rt_le32_to_cpu(val));

        buf += 4;
        pos += 4;
        count -= 4;
    }

    if (count >= 2)
    {
        rt_le16_t val;

        copy_from_user(&val, buf, sizeof(val));
        rt_pci_write_config_u16(pdev, pos, rt_le16_to_cpu(val));

        buf += 2;
        pos += 2;
        count -= 2;
    }

    if (count)
    {
        rt_uint8_t val;

        copy_from_user(&val, buf, sizeof(val));
        rt_pci_write_config_u8(pdev, pos, val);

        ++pos;
    }

    pci_pm_runtime_put(pdev, &pm_flags);

    *ppos = pos;

    return res;
}

static off_t pci_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    struct proc_dentry *dentry = file->vnode->data;
    struct rt_pci_device *pdev = dentry->data;

    switch (wherece)
    {
    case SEEK_SET:
        break;

    case SEEK_CUR:
        offset += file->fpos;
        break;

    case SEEK_END:
        offset += pdev->cfg_size;
        break;

    default:
        return -EINVAL;
    }

    if (offset <= (off_t)pdev->cfg_size)
    {
        return offset;
    }

    return -EIO;
}

static const struct dfs_file_ops pci_fops =
{
    .read = pci_read,
    .write = pci_write,
    .lseek = pci_lseek,
};

void pci_procfs_attach(struct rt_pci_device *pdev)
{
    const char *name;
    struct proc_dentry *dentry;

    if (!pci_proc_dentry)
    {
        return;
    }

    name = rt_dm_dev_get_name(&pdev->parent);
    dentry = proc_create_data(name, 0644, pci_proc_dentry, &pci_fops, pdev);

    if (!dentry)
    {
        LOG_E("Create %s file fail", name);
        return;
    }
    proc_release(dentry);
}

void pci_procfs_detach(struct rt_pci_device *pdev)
{
    if (!pci_proc_dentry)
    {
        return;
    }

    proc_remove_dentry(rt_dm_dev_get_name(&pdev->parent), pci_proc_dentry);
}

static int pci_single_show(struct dfs_seq_file *seq, void *data)
{
    struct rt_device *dev;
    struct rt_pci_driver *pdrv;
    struct rt_pci_device *pdev;

    rt_hw_spin_lock(&pci_bus->dev_lock.lock);

    rt_list_for_each_entry(dev, &pci_bus->dev_list, node)
    {
        pdev = rt_container_of(dev, struct rt_pci_device, parent);

        dfs_seq_printf(seq, "%02x%02x\t%04x%04x\t%x",
                pdev->bus->number,
                pdev->devfn,
                pdev->vendor,
                pdev->device,
                pdev->irq);

        /* BAR, ROM base */
        for (int bar = 0; bar < RT_PCI_BAR_NR_MAX; ++bar)
        {
            dfs_seq_printf(seq, "\t%16llx", (rt_uint64_t)pdev->resource[bar].base);
        }
        dfs_seq_printf(seq, "\t%16llx", (rt_uint64_t)pdev->rom.base);

        /* BAR, ROM size */
        for (int bar = 0; bar < RT_PCI_BAR_NR_MAX; ++bar)
        {
            dfs_seq_printf(seq, "\t%16llx", (rt_uint64_t)pdev->resource[bar].size);
        }
        dfs_seq_printf(seq, "\t%16llx", (rt_uint64_t)pdev->rom.size);

        dfs_seq_puts(seq, "\t");

        /* Driver Name */
        if (dev->drv)
        {
            pdrv = rt_container_of(dev->drv, struct rt_pci_driver, parent);

            dfs_seq_puts(seq, pdrv->name);
        }

        /* End of a seq */
        dfs_seq_puts(seq, "\n");
    }

    rt_hw_spin_unlock(&pci_bus->dev_lock.lock);

    return 0;
}

static int pci_procfs_init(void)
{
    struct proc_dentry *dentry;

    pci_bus = rt_bus_find_by_name("pci");

    RT_ASSERT(pci_bus != RT_NULL);

    pci_proc_dentry = proc_mkdir("pci", RT_NULL);

    if (!pci_proc_dentry)
    {
        LOG_E("Create pci entry fail");
        return (int)-RT_ERROR;
    }
    proc_release(pci_proc_dentry);

    dentry = proc_create_single_data("devices", 0644, pci_proc_dentry, &pci_single_show, NULL);

    if (!dentry)
    {
        proc_remove(pci_proc_dentry);
        pci_proc_dentry = RT_NULL;

        LOG_E("Create pci devices fail");
        return (int)-RT_ERROR;
    }
    proc_release(dentry);

    return 0;
}
INIT_PREV_EXPORT(pci_procfs_init);
