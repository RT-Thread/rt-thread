/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "audio.pcm.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "spacemit-audio.h"

static rt_list_t pcm_nodes = RT_LIST_OBJECT_INIT(pcm_nodes);
static RT_DEFINE_SPINLOCK(pcm_nodes_lock);

struct spacemit_pcm *spacemit_pcm_find(struct rt_ofw_node *np)
{
    struct spacemit_pcm *pcm;

    rt_spin_lock(&pcm_nodes_lock);
    rt_list_for_each_entry(pcm, &pcm_nodes, list)
    {
        if (pcm->np == np)
        {
            rt_spin_unlock(&pcm_nodes_lock);
            return pcm;
        }
    }
    rt_spin_unlock(&pcm_nodes_lock);

    return RT_NULL;
}

static void spacemit_pcm_free(struct spacemit_pcm *pcm)
{
    if (!pcm)
    {
        return;
    }

    if (!rt_is_err_or_null(pcm->rx))
    {
        rt_dma_chan_release(pcm->rx);
    }
    if (!rt_is_err_or_null(pcm->tx))
    {
        rt_dma_chan_release(pcm->tx);
    }
    if (pcm->hdmi_buffer)
    {
        rt_iounmap(pcm->hdmi_buffer);
    }

    rt_free(pcm);
}

static rt_err_t spacemit_pcm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address, size;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_pcm *pcm = rt_calloc(1, sizeof(*pcm));

    if (!pcm)
    {
        return -RT_ENOMEM;
    }

    pcm->dev = dev;
    pcm->np = dev->ofw_node;
    pcm->is_hdmi = rt_ofw_node_is_compatible(dev->ofw_node,
            "spacemit,spacemit-snd-dma-hdmi");

    if (pcm->is_hdmi)
    {
        pcm->hdmi_buffer = rt_dm_dev_iomap(dev, 0);
        if (!pcm->hdmi_buffer ||
            rt_dm_dev_get_address(dev, 0, &address, &size))
        {
            err = -RT_EIO;
            goto _fail;
        }

        pcm->hdmi_dma = (rt_ubase_t)address;
        pcm->hdmi_size = (rt_size_t)size;
        rt_memset(pcm->hdmi_buffer, 0, pcm->hdmi_size);
        rt_hw_wmb();
    }

    pcm->tx = rt_dma_chan_request(dev, "tx");
    if (rt_is_err_or_null(pcm->tx))
    {
        err = pcm->tx ? rt_ptr_err(pcm->tx) : -RT_ENOSYS;
        goto _fail;
    }

    if (!pcm->is_hdmi)
    {
        pcm->rx = rt_dma_chan_request(dev, "rx");
        if (rt_is_err_or_null(pcm->rx))
        {
            err = pcm->rx ? rt_ptr_err(pcm->rx) : -RT_ENOSYS;
            goto _fail;
        }
    }

    rt_spin_lock(&pcm_nodes_lock);
    rt_list_insert_before(&pcm_nodes, &pcm->list);
    rt_spin_unlock(&pcm_nodes_lock);

    dev->user_data = pcm;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, pcm);

    LOG_D("%s: %s DMA path ready", rt_dm_dev_get_name(dev),
            pcm->is_hdmi ? "HDMI" : "I2S");

    return RT_EOK;

_fail:
    spacemit_pcm_free(pcm);
    return err;
}

static rt_err_t spacemit_pcm_remove(struct rt_platform_device *pdev)
{
    struct spacemit_pcm *pcm = pdev->parent.user_data;

    if (!pcm)
    {
        return RT_EOK;
    }

    rt_spin_lock(&pcm_nodes_lock);
    rt_list_remove(&pcm->list);
    rt_spin_unlock(&pcm_nodes_lock);

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    spacemit_pcm_free(pcm);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_pcm_ofw_ids[] =
{
    { .compatible = "spacemit,spacemit-snd-dma0" },
    { .compatible = "spacemit,spacemit-snd-dma1" },
    { .compatible = "spacemit,spacemit-snd-dma-hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pcm_driver =
{
    .name = "spacemit-audio-pcm",
    .ids = spacemit_pcm_ofw_ids,
    .probe = spacemit_pcm_probe,
    .remove = spacemit_pcm_remove,
};

static int spacemit_pcm_register(void)
{
    rt_platform_driver_register(&spacemit_pcm_driver);
    return 0;
}
INIT_DEVICE_EXPORT(spacemit_pcm_register);
