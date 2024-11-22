/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <drivers/pci_msi.h>

#define DBG_TAG "pci.msi.irq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_spinlock msi_irq_map_lock = {};
static RT_BITMAP_DECLARE(msi_irq_map, MAX_HANDLERS) = {};

rt_err_t rt_pci_msi_setup_irqs(struct rt_pci_device *pdev, int nvec, int type)
{
    int irq, index = 0, irq_nr = 0;
    rt_err_t err = RT_EOK;
    struct rt_pic_irq *pirq;
    struct rt_pic *msi_pic;
    struct rt_pci_msi_desc *desc;

    if (!pdev)
    {
        return -RT_EINVAL;
    }

    msi_pic = pdev->msi_pic;

    if (type == PCIY_MSI)
    {
        int last_irq = -1, irq_idx;
        rt_size_t irq_nr;

        desc = rt_pci_msi_first_desc(pdev);
        irq_nr = 1 << desc->msi.cap.multi_msg_use;

        rt_hw_spin_lock(&msi_irq_map_lock.lock);

    _retry:
        for (int i = 0; i < irq_nr; ++i)
        {
            if ((irq = msi_pic->ops->irq_alloc_msi(msi_pic, desc)) < 0)
            {
                err = irq;

                LOG_E("Setup %s[%d] IRQ error = %s", "MSI", i, rt_strerror(err));

                break;
            }

            if (last_irq >= 0 && last_irq + 1 != irq)
            {
                for (int idx = 0; idx < i; ++i, --last_irq)
                {
                    rt_bitmap_set_bit(msi_irq_map, last_irq);
                }

                last_irq = irq;
                goto _retry;
            }

            last_irq = irq;
        }

        if (!err)
        {
            /* Get the first irq */
            desc->irq = irq - (irq_nr - 1);
        }

        rt_bitmap_for_each_set_bit(msi_irq_map, irq_idx, MAX_HANDLERS)
        {
            msi_pic->ops->irq_free_msi(msi_pic, irq_idx);

            /* Free bit so the next user doesn't need to bzero */
            rt_bitmap_clear_bit(msi_irq_map, irq_idx);
        }

        rt_hw_spin_unlock(&msi_irq_map_lock.lock);

        if (!err)
        {
            for (int idx = 0; idx < nvec; ++idx)
            {
                pirq = rt_pic_find_pirq(msi_pic, irq + idx);
                pirq->msi_desc = desc;

                msi_pic->ops->irq_compose_msi_msg(pirq, &desc->msg);

                rt_pci_msi_write_msg(desc, &desc->msg);
            }
        }
    }
    else if (type == PCIY_MSIX)
    {
        rt_pci_msi_for_each_desc(pdev, desc)
        {
            if ((irq = msi_pic->ops->irq_alloc_msi(msi_pic, desc)) < 0)
            {
                err = irq;

                LOG_E("Setup %s[%d] IRQ error = %s", "MSI-X",
                        desc->msix.index, rt_strerror(err));

                break;
            }

            desc->irq = irq;
            pirq = rt_pic_find_pirq(msi_pic, irq);
            pirq->msi_desc = desc;

            msi_pic->ops->irq_compose_msi_msg(pirq, &desc->msg);

            rt_pci_msi_write_msg(desc, &desc->msg);

            ++irq_nr;
        }

        if (err)
        {
            rt_pci_msi_for_each_desc(pdev, desc)
            {
                if (index >= irq_nr)
                {
                    break;
                }

                msi_pic->ops->irq_free_msi(msi_pic, desc->irq);

                ++index;
            }
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}
