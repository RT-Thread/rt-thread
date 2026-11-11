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

#define DBG_TAG "reset.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SW_INIT_SET         0x00
#define SW_INIT_CLEAR       0x04
#define SW_INIT_STATUS      0x08

#define SW_INIT_BIT(id)     RT_BIT((id) & 0x1f)
#define SW_INIT_BANK(id)    ((id) >> 5)

/*
 * A full bank contains extra registers that we are not utilizing but still
 * qualify as a single bank.
 */
#define SW_INIT_BANK_SIZE   0x18

struct brcmstb_reset
{
    struct rt_reset_controller parent;

    void *regs;
};

static rt_err_t brcmstb_reset_assert(struct rt_reset_control *rstc)
{
    struct brcmstb_reset *brst = rstc->rstcer->priv;
    rt_uint32_t off = SW_INIT_BANK(rstc->id) * SW_INIT_BANK_SIZE;

    HWREG32(brst->regs + off + SW_INIT_SET) = SW_INIT_BIT(rstc->id);

    return RT_EOK;
}

static rt_err_t brcmstb_reset_deassert(struct rt_reset_control *rstc)
{
    struct brcmstb_reset *brst = rstc->rstcer->priv;
    unsigned int off = SW_INIT_BANK(rstc->id) * SW_INIT_BANK_SIZE;

    HWREG32(brst->regs + off + SW_INIT_CLEAR) = SW_INIT_BIT(rstc->id);

    /*
     * Maximum reset delay after de-asserting a line and seeing block
     * operation is typically 14us for the worst case, build some slack here.
     */
    rt_hw_us_delay(150);

    return RT_EOK;
}

static int brcmstb_reset_status(struct rt_reset_control *rstc)
{
    struct brcmstb_reset *brst = rstc->rstcer->priv;
    rt_uint32_t off = SW_INIT_BANK(rstc->id) * SW_INIT_BANK_SIZE;

    return HWREG32(brst->regs + off + SW_INIT_STATUS) & SW_INIT_BIT(rstc->id);
}

const static struct rt_reset_control_ops brcmstb_reset_ops =
{
    .assert = brcmstb_reset_assert,
    .deassert = brcmstb_reset_deassert,
    .status = brcmstb_reset_status,
};

static rt_err_t brcmstb_reset_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_reset_controller *rstcer;
    struct rt_device *dev = &pdev->parent;
    struct brcmstb_reset *brst = rt_calloc(1, sizeof(*brst));

    if (!brst)
    {
        return -RT_ENOMEM;
    }

    brst->regs = rt_dm_dev_iomap(dev, 0);

    if (!brst->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rstcer = &brst->parent;

    rstcer->priv = brst;
    rstcer->ofw_node = dev->ofw_node;
    rstcer->ops = &brcmstb_reset_ops;

    if ((err = rt_reset_controller_register(rstcer)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (brst->regs)
    {
        rt_iounmap(brst->regs);
    }

    rt_free(brst);

    return err;
}

static const struct rt_ofw_node_id brcmstb_reset_ofw_ids[] =
{
    { .compatible = "brcm,brcmstb-reset" },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmstb_reset_driver =
{
    .name = "reset-brcmstb",
    .ids = brcmstb_reset_ofw_ids,

    .probe = brcmstb_reset_probe,
};

static int brcmstb_reset_register(void)
{
    rt_platform_driver_register(&brcmstb_reset_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(brcmstb_reset_register);
