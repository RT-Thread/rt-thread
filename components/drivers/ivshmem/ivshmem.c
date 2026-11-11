/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-27     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.ivshmem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include "ivshmem.h"

static void ivshmem_isr(int irqno, void *param)
{
    rt_uint32_t status;
    struct ivshmem_device *ivdev = param;

    status = HWREG32(ivdev->reg + IVSHMEM_INTR_STATUS);

    if ((status && status != 0xffffffff) || ivdev->nvectors)
    {
        if (ivdev->handle_irq)
        {
            ivdev->handle_irq(ivdev, ivdev->nvectors ? irqno : status);
        }
        else
        {
            LOG_E("IVSHMEM<%p> have a irq = %d, by no have irq handers", ivdev, irqno);
        }
    }
}

rt_err_t ivshmem_install_msix_vectors(struct ivshmem_device *ivdev, int nvectors, const char *name)
{
    rt_err_t err = RT_EOK;
    char irq_name[RT_NAME_MAX];

    if (!ivdev || !name)
    {
        return -RT_EINVAL;
    }

    if (ivdev->nvectors != 0)
    {
        LOG_E("IVSHMEM<%p> '%s' have already install msix", ivdev, name);

        return -RT_ERROR;
    }

    if (!ivdev->handle_irq)
    {
        LOG_E("IVSHMEM<%p> '%s' no have irq handers", ivdev, name);

        return -RT_EINVAL;
    }

    ivdev->msix_entries = rt_malloc(nvectors * sizeof(*ivdev->msix_entries));

    if (!ivdev->msix_entries)
    {
        return -RT_ENOMEM;
    }

    ivdev->nvectors = nvectors;

    rt_pci_msix_entry_index_linear(ivdev->msix_entries, nvectors);

    if ((err = rt_pci_msix_enable(ivdev->pdev, ivdev->msix_entries, ivdev->nvectors)))
    {
        rt_free(ivdev->msix_entries);
        ivdev->msix_entries = RT_NULL;
        ivdev->nvectors = 0;

        return err;
    }

    for (int i = 0; i < nvectors; i++)
    {
        int irq = ivdev->msix_entries[i].irq;

        rt_snprintf(irq_name, RT_NAME_MAX, "%s%d", name, irq);

        rt_hw_interrupt_install(irq, ivshmem_isr, ivdev, irq_name);
        rt_hw_interrupt_umask(irq);
    }

    return err;
}

rt_err_t ivshmem_install_intx_vector(struct ivshmem_device *ivdev, const char *name)
{
    rt_err_t err = RT_EOK;

    if (!ivdev || !name)
    {
        return -RT_EINVAL;
    }

    if (ivdev->nvectors != 0)
    {
        LOG_E("IVSHMEM<%p> '%s' have already install msix", ivdev, name);

        return -RT_ERROR;
    }

    if (!ivdev->handle_irq)
    {
        LOG_E("IVSHMEM<%p> '%s' no have irq handers", ivdev, name);

        return -RT_EINVAL;
    }

    ivdev->nvectors = 0;
    ivdev->msix_entries = RT_NULL;

    rt_hw_interrupt_install(ivdev->irq, ivshmem_isr, ivdev, name);
    rt_pci_irq_unmask(ivdev->pdev);

    return err;
}

static void ivshmem_free_resource(struct ivshmem_device *ivdev)
{
    if (ivdev->pdev)
    {
        ivdev->pdev->sysdata = RT_NULL;
    }

    if (ivdev->reg)
    {
        rt_iounmap(ivdev->reg);
    }

    if (ivdev->shmem)
    {
        rt_iounmap(ivdev->shmem);
    }
}

rt_err_t ivshmem_pci_probe(struct rt_pci_device *pdev, struct ivshmem_device *ivdev)
{
    rt_err_t err = RT_EOK;

    if (!ivdev || !pdev || pdev->irq < 0)
    {
        return -RT_EINVAL;
    }

    rt_memset(ivdev, 0, sizeof(*ivdev));

    ivdev->pdev = pdev;
    ivdev->irq = pdev->irq;

    pdev->sysdata = ivdev;

    ivdev->reg = rt_pci_iomap(pdev, IVSHMEM_REG_BAR);

    if (!ivdev->reg)
    {
        err = -RT_EIO;
        goto _fail;
    }

    /* Set all masks to on */
    HWREG32(ivdev->reg + IVSHMEM_INTR_MASK) = 0xffffffff;

    ivdev->shmem_size = pdev->resource[IVSHMEM_SHARE_MEM_BAR].size;
    ivdev->shmem = (void *)pdev->resource[IVSHMEM_SHARE_MEM_BAR].base;

    if (!ivdev->shmem_size)
    {
        rt_pci_read_config_u32(pdev, PCI_CFG_SHARE_MEM_ADDR_LO, (rt_uint32_t *)&ivdev->shmem);
        rt_pci_read_config_u32(pdev, PCI_CFG_SHARE_MEM_ADDR_HI, (rt_uint32_t *)&ivdev->shmem + 1);
        rt_pci_read_config_u32(pdev, PCI_CFG_SHARE_MEM_SIZE_LO, (rt_uint32_t *)&ivdev->shmem_size);
        rt_pci_read_config_u32(pdev, PCI_CFG_SHARE_MEM_SIZE_HI, (rt_uint32_t *)&ivdev->shmem_size + 1);
    }

    ivdev->shmem = rt_ioremap(ivdev->shmem, ivdev->shmem_size);

    if (!ivdev->shmem)
    {
        err = -RT_ERROR;
        goto _fail;
    }

    return RT_EOK;

_fail:
    ivshmem_free_resource(ivdev);

    return err;
}

struct ivshmem_device *ivshmem_pci_remove(struct rt_pci_device *pdev)
{
    struct ivshmem_device *ivdev = RT_NULL;

    if (!pdev || !pdev->sysdata)
    {
        return ivdev;
    }

    ivdev = pdev->sysdata;

    if (ivdev->msix_entries)
    {
        for (int i = 0; i < ivdev->nvectors; ++i)
        {
            int irq = ivdev->msix_entries[i].irq;

            rt_hw_interrupt_umask(irq);
            rt_pic_detach_irq(irq, ivdev);
        }
    }

    rt_hw_interrupt_umask(ivdev->irq);
    rt_pic_detach_irq(ivdev->irq, ivdev);

    if (ivdev->nvectors)
    {
        rt_pci_msix_disable(ivdev->pdev);
        rt_free(ivdev->msix_entries);
    }
    else
    {
        rt_pci_irq_unmask(ivdev->pdev);
    }

    ivshmem_free_resource(ivdev);

    return ivdev;
}
