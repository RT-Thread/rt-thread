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

#define DBG_TAG "soc.k1x-rproc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-spacemit.h>

#define K1X_MBOX_VQ0_ID                 0
#define K1X_MBOX_VQ1_ID                 1

#define FW_BOOT_ENTRY_REG_OFFSET        0x88
#define FW_BOOTUP_REG_OFFSET            0x30
#define FW_AON_PER_CLK_RST_CTL_REG      0x2c

#define FW_DDR_REGMAP_BASE_REG_OFFSET   0xc0

#define AUDIO_PMU_VOTE_REG_OFFSET       0x20

#define DEV_PM_QOS_CLK_GATE             1
#define DEV_PM_QOS_REGULATOR_GATE       2
#define DEV_PM_QOS_PM_DOMAIN_GATE       4
#define DEV_PM_QOS_DEFAULT              7

static char *const mb_name[] =
{
    [K1X_MBOX_VQ0_ID] = "vq0",
    [K1X_MBOX_VQ1_ID] = "vq1",
};

struct spacemit_rproc_mbox
{
    struct rt_mbox_client parent;

    struct rt_mbox_chan *chan;

    int vq_id;
    struct rt_completion mb_comp;
};

struct spacemit_rproc
{
    struct rt_device parent;

    void *bootc_mem_base;
    void *sysctrl_mem_base;

    struct rt_clk *core_clk;
    struct rt_clk *apb_clk;
    struct rt_reset_control *core_rstc;

    rt_uint32_t apb_clk_rate;
    rt_uint32_t apb_clk_rate_default;
    rt_uint32_t ddr_remap_base;
    rt_uint32_t fw_entry_point;
    struct spacemit_rproc_mbox mb[RT_ARRAY_SIZE(mb_name)];
};

static rt_ssize_t spacemit_rproc_write(rt_device_t dev, rt_off_t pos,
        const void *buffer, rt_size_t size)
{
    rt_err_t err;
    struct spacemit_rproc *rproc = rt_container_of(dev, struct spacemit_rproc, parent);

    if (pos >= RT_ARRAY_SIZE(rproc->mb))
    {
        return -RT_EINVAL;
    }

    err = rt_mbox_send(rproc->mb[pos].chan, buffer ? : "kick", RT_WAITING_FOREVER);

    return err ? err : size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops spacemit_rproc_ops =
{
    .write = spacemit_rproc_write,
};
#endif

static rt_err_t spacemit_rproc_prepare(struct spacemit_rproc *rproc)
{
    /* De-assert the clk */
    rt_reset_control_assert(rproc->core_rstc);
    rt_reset_control_deassert(rproc->core_rstc);

    /* Enable clocks explicitly (RT-Thread may keep them gated by default) */
    rt_clk_enable(rproc->core_clk);
    rt_clk_enable(rproc->apb_clk);

    /* Set apb clk rate */
    rt_clk_set_rate(rproc->apb_clk, rproc->apb_clk_rate);

    return RT_EOK;
}

static rt_err_t spacemit_rproc_start(struct spacemit_rproc *rproc)
{
    /* Enable ipc2ap clk & reset--> rcpu side */
    HWREG32(rproc->bootc_mem_base + FW_AON_PER_CLK_RST_CTL_REG) = 0xff;

    /* Set the boot-entry */
    HWREG32(rproc->sysctrl_mem_base + FW_BOOT_ENTRY_REG_OFFSET) = rproc->fw_entry_point;

    /* Set ddr map */
    HWREG32(rproc->sysctrl_mem_base + FW_DDR_REGMAP_BASE_REG_OFFSET) = rproc->ddr_remap_base;

    /* Lanching up firmware */
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 1;

    return RT_EOK;
}

static rt_err_t spacemit_rproc_stop(struct spacemit_rproc *rproc)
{
    /* Hold the rcpu */
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 0;

    rt_reset_control_assert(rproc->core_rstc);

    /* Gate clocks after reset asserted */
    rt_clk_disable(rproc->apb_clk);
    rt_clk_disable(rproc->core_clk);

    return RT_EOK;
}

static void spacemit_rproc_mbox_rx_callback(struct rt_mbox_client *client, void *data)
{
    struct spacemit_rproc_mbox *mb = rt_container_of(client, struct spacemit_rproc_mbox, parent);

    rt_completion_done(&mb->mb_comp);
}

static rt_err_t spacemit_rproc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *fw_name, *name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_rproc *rproc = rt_calloc(1, sizeof(*rproc));

    if (!rproc)
    {
        return -RT_ENOMEM;
    }

    rproc->bootc_mem_base = rt_dm_dev_iomap(dev, 0);
    if (!rproc->bootc_mem_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rproc->sysctrl_mem_base = rt_dm_dev_iomap(dev, 1);
    if (!rproc->sysctrl_mem_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rproc->core_rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(rproc->core_rstc))
    {
        err = rt_ptr_err(rproc->core_rstc);
        goto _fail;
    }

    rproc->core_clk = rt_clk_get_by_name(dev, "core");
    if (rt_is_err(rproc->core_clk))
    {
        err = rt_ptr_err(rproc->core_clk);
        goto _fail;
    }

    rproc->apb_clk = rt_clk_get_by_name(dev, "apb");
    if (rt_is_err(rproc->apb_clk))
    {
        err = rt_ptr_err(rproc->apb_clk);
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "apb-clk-rate", &rproc->apb_clk_rate)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "ddr-remap-base", &rproc->ddr_remap_base)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_string(dev, "firmware-name", &fw_name)))
    {
        goto _fail;
    }

    if (!(name = rt_dm_dev_get_prop_fuzzy_name(dev, "-entry-point$")))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, name, &rproc->fw_entry_point)))
    {
        goto _fail;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->mb); ++i)
    {
        struct spacemit_rproc_mbox *mb = &rproc->mb[i];

        rt_completion_init(&mb->mb_comp);

        mb->parent.dev = dev;
        mb->parent.rx_callback = spacemit_rproc_mbox_rx_callback;

        mb->chan = rt_mbox_request_by_name(&mb->parent, mb_name[i]);

        if (rt_is_err_or_null(mb->chan))
        {
            err = -RT_EINVAL;
            LOG_E("Request mailbox fail");
            goto _fail;
        }
    }

    spacemit_rproc_prepare(rproc);

    if ((err = spacemit_firmware_load_elf(fw_name, rproc->ddr_remap_base)))
    {
        LOG_E("Run firmware %s fail", fw_name);
        goto _fail;
    }

    spacemit_rproc_start(rproc);

    rt_dm_dev_set_name(&rproc->parent, "rproc-%s", fw_name);
    name = rt_dm_dev_get_name(&rproc->parent);

    rproc->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    rproc->parent.ops = &spacemit_rproc_ops;
#else
    rproc->parent.write = spacemit_rproc_write;
#endif

    if ((err = rt_device_register(&rproc->parent, name, RT_DEVICE_FLAG_WRONLY)))
    {
        goto _fail;
    }

    dev->user_data = rproc;

    return RT_EOK;

_fail:
    if (rproc->bootc_mem_base)
    {
        rt_iounmap(rproc->bootc_mem_base);
    }
    if (rproc->sysctrl_mem_base)
    {
        rt_iounmap(rproc->sysctrl_mem_base);
    }

    if (!rt_is_err_or_null(rproc->core_rstc))
    {
        rt_reset_control_put(rproc->core_rstc);
    }
    if (!rt_is_err_or_null(rproc->core_clk))
    {
        rt_clk_put(rproc->core_clk);
    }
    if (!rt_is_err_or_null(rproc->apb_clk))
    {
        rt_clk_put(rproc->apb_clk);
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->mb); ++i)
    {
        struct spacemit_rproc_mbox *mb = &rproc->mb[i];

        if (!rt_is_err_or_null(mb->chan))
        {
            rt_mbox_release(mb->chan);
        }
    }

    rt_free(rproc);

    return err;
}

static rt_err_t spacemit_rproc_shutdown(struct rt_platform_device *pdev)
{
    struct spacemit_rproc *rproc = pdev->parent.user_data;

    spacemit_rproc_stop(rproc);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_rproc_ofw_ids[] =
{
    { .compatible = "spacemit,k1-x-rproc" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_rproc_driver =
{
    .name = "spacemit-rproc",
    .ids = spacemit_rproc_ofw_ids,

    .probe = spacemit_rproc_probe,
    .shutdown = spacemit_rproc_shutdown,
};

static int spacemit_rproc_drv_register(void)
{
    rt_platform_driver_register(&spacemit_rproc_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_rproc_drv_register);
