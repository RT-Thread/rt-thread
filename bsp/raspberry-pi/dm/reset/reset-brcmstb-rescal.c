/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "reset.brcmstb-rescal"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#define BRCM_RESCAL_START           0x0
#define   BRCM_RESCAL_START_BIT     RT_BIT(0)
#define BRCM_RESCAL_CTRL            0x4
#define BRCM_RESCAL_STATUS          0x8
#define   BRCM_RESCAL_STATUS_BIT    RT_BIT(0)

struct brcm_rescal_reset
{
    struct rt_reset_controller parent;

    void *regs;
};

static rt_err_t brcm_rescal_reset_ofw_parse(struct rt_reset_control *rstc, struct rt_ofw_cell_args *args)
{
    args->args[0] = 0;

    return RT_EOK;
}

static rt_err_t brcm_rescal_reset_reset(struct rt_reset_control *rstc)
{
    rt_uint32_t reg;
    struct brcm_rescal_reset *brrst = rstc->rstcer->priv;

    reg = HWREG32(brrst->regs + BRCM_RESCAL_START);
    HWREG32(brrst->regs + BRCM_RESCAL_START) = reg | BRCM_RESCAL_START_BIT;
    reg = HWREG32(brrst->regs + BRCM_RESCAL_START);

    if (!(reg & BRCM_RESCAL_START_BIT))
    {
        LOG_E("Failed to start SATA/PCIe rescal");

        return -RT_EIO;
    }

    for (rt_uint32_t time = 0; time < 1000; time += 100)
    {
        reg = HWREG32(brrst->regs + BRCM_RESCAL_STATUS);

        if (reg & BRCM_RESCAL_STATUS_BIT)
        {
            goto _status_ok;
        }

        rt_hw_us_delay(100);

        rt_hw_cpu_relax();
    }

    LOG_E("Time out on SATA/PCIe rescal");

    return -RT_ETIMEOUT;

_status_ok:
    reg = HWREG32(brrst->regs + BRCM_RESCAL_START);
    HWREG32(brrst->regs + BRCM_RESCAL_START) = reg & ~BRCM_RESCAL_START_BIT;

    LOG_D("SATA/PCIe rescal success");

    return RT_EOK;
}

static rt_err_t brcm_rescal_reset_assert(struct rt_reset_control *rstc)
{
    return RT_EOK;
}

static rt_err_t brcm_rescal_reset_deassert(struct rt_reset_control *rstc)
{
    return brcm_rescal_reset_reset(rstc);
}

const static struct rt_reset_control_ops brcm_rescal_reset_ops =
{
    .ofw_parse = brcm_rescal_reset_ofw_parse,
    .reset = brcm_rescal_reset_reset,
    .assert = brcm_rescal_reset_assert,
    .deassert = brcm_rescal_reset_deassert,
};

static rt_err_t brcm_rescal_reset_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_reset_controller *rstcer;
    struct rt_device *dev = &pdev->parent;
    struct brcm_rescal_reset *brrst = rt_calloc(1, sizeof(*brrst));

    if (!brrst)
    {
        return -RT_ENOMEM;
    }

    brrst->regs = rt_dm_dev_iomap(dev, 0);

    if (!brrst->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rstcer = &brrst->parent;

    rstcer->priv = brrst;
    rstcer->ofw_node = dev->ofw_node;
    rstcer->ops = &brcm_rescal_reset_ops;

    if ((err = rt_reset_controller_register(rstcer)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (brrst->regs)
    {
        rt_iounmap(brrst->regs);
    }

    rt_free(brrst);

    return err;
}

static const struct rt_ofw_node_id brcm_rescal_reset_ofw_ids[] =
{
    { .compatible = "brcm,bcm7216-pcie-sata-rescal" },
    { /* sentinel */ }
};

static struct rt_platform_driver brcm_rescal_reset_driver =
{
    .name = "reset-brcm-rescal",
    .ids = brcm_rescal_reset_ofw_ids,

    .probe = brcm_rescal_reset_probe,
};

static int brcm_rescal_reset_register(void)
{
    rt_platform_driver_register(&brcm_rescal_reset_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(brcm_rescal_reset_register);
