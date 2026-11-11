/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rtdevice.h>
#include <rtthread.h>

#define DBG_TAG "phye.generic.usb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct generic_usb_phy
{
    struct rt_phye parent;

    rt_base_t rst_pin;
    rt_uint8_t rst_active_val;

    struct rt_clk *clk;
    struct rt_regulator *vcc;
    struct rt_regulator *vbus;
};

#define raw_to_generic_usb_phy(raw) rt_container_of(raw, struct generic_usb_phy, parent)

static rt_err_t generic_usb_phy_reset(struct rt_phye *phye)
{
    struct generic_usb_phy *usb_phy = raw_to_generic_usb_phy(phye);

    if (usb_phy->rst_pin == PIN_NONE)
    {
        return RT_EOK;
    }

    rt_pin_mode(usb_phy->rst_pin, PIN_MODE_OUTPUT);

    rt_pin_write(usb_phy->rst_pin, usb_phy->rst_active_val);
    rt_hw_us_delay(15000);

    rt_pin_write(usb_phy->rst_pin, !usb_phy->rst_active_val);
    rt_hw_us_delay(20000);

    return RT_EOK;
}

static rt_err_t generic_usb_phy_power_on(struct rt_phye *phye)
{
    rt_err_t err;
    struct generic_usb_phy *usb_phy = raw_to_generic_usb_phy(phye);

    if (usb_phy->vcc && (err = rt_regulator_enable(usb_phy->vcc)))
    {
        return err;
    }

    if ((err = rt_clk_prepare_enable(usb_phy->clk)))
    {
        if (usb_phy->vcc)
        {
            rt_regulator_disable(usb_phy->vcc);
        }

        return err;
    }

    return generic_usb_phy_reset(phye);
}

static rt_err_t generic_usb_phy_power_off(struct rt_phye *phye)
{
    rt_err_t err;
    struct generic_usb_phy *usb_phy = raw_to_generic_usb_phy(phye);

    if (usb_phy->vcc && (err = rt_regulator_disable(usb_phy->vcc)))
    {
        return err;
    }

    rt_clk_disable_unprepare(usb_phy->clk);

    return RT_EOK;
}

static const struct rt_phye_ops generic_usb_phy_ops =
{
    .reset = generic_usb_phy_reset,
    .power_on = generic_usb_phy_power_on,
    .power_off = generic_usb_phy_power_off,
};

static void generic_usb_phy_free(struct generic_usb_phy *usb_phy)
{
    if (!rt_is_err_or_null(usb_phy->clk))
    {
        rt_clk_put(usb_phy->clk);
    }

    if (!rt_is_err_or_null(usb_phy->vcc))
    {
        rt_regulator_put(usb_phy->vcc);
    }

    if (!rt_is_err_or_null(usb_phy->vbus))
    {
        rt_regulator_put(usb_phy->vbus);
    }

    rt_free(usb_phy);
}

static rt_err_t generic_usb_phy_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t rate;
    struct rt_phye *phy;
    struct rt_device *dev = &pdev->parent;
    struct generic_usb_phy *usb_phy = rt_calloc(1, sizeof(*usb_phy));

    if (!usb_phy)
    {
        return -RT_ENOMEM;
    }

    usb_phy->rst_pin = rt_pin_get_named_pin(dev, "reset", 0,
            RT_NULL, &usb_phy->rst_active_val);

    if (usb_phy->rst_pin < 0 && usb_phy->rst_pin != PIN_NONE)
    {
        err = usb_phy->rst_pin;
        goto _fail;
    }

    usb_phy->clk = rt_clk_get_by_name(dev, "main_clk");

    if (rt_is_err(usb_phy->clk))
    {
        err = rt_ptr_err(usb_phy->clk);
        goto _fail;
    }

    if (!rt_dm_dev_prop_read_u32(dev, "clock-frequency", &rate))
    {
        if ((err = rt_clk_set_rate(usb_phy->clk, rate)))
        {
            goto _fail;
        }
    }

    usb_phy->vcc = rt_regulator_get(dev, "vcc");

    if (rt_is_err(usb_phy->vcc))
    {
        err = rt_ptr_err(usb_phy->vcc);
        goto _fail;
    }

    usb_phy->vbus = rt_regulator_get(dev, "vbus");

    if (rt_is_err(usb_phy->vbus))
    {
        err = rt_ptr_err(usb_phy->vbus);
        goto _fail;
    }

    if (usb_phy->vbus && (err = rt_regulator_enable(usb_phy->vbus)))
    {
        goto _fail;
    }

    dev->user_data = usb_phy;

    phy = &usb_phy->parent;
    phy->dev = dev;
    phy->ops = &generic_usb_phy_ops;

    if ((err = rt_phye_register(phy)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    generic_usb_phy_free(usb_phy);

    return err;
}

static rt_err_t generic_usb_phy_remove(struct rt_platform_device *pdev)
{
    struct generic_usb_phy *usb_phy = pdev->parent.user_data;

    rt_phye_unregister(&usb_phy->parent);

    if (usb_phy->vbus)
    {
        rt_regulator_disable(usb_phy->vbus);
    }

    generic_usb_phy_free(usb_phy);

    return RT_EOK;
}

static const struct rt_ofw_node_id generic_usb_phy_ofw_ids[] =
{
    { .compatible = "usb-nop-xceiv" },
    { /* sentinel */ }
};

static struct rt_platform_driver generic_usb_phy_driver =
{
    .name = "phy-generic-usb",
    .ids = generic_usb_phy_ofw_ids,

    .probe = generic_usb_phy_probe,
    .remove = generic_usb_phy_remove,
};

static int generic_usb_phy_drv_register(void)
{
    rt_platform_driver_register(&generic_usb_phy_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(generic_usb_phy_drv_register);
