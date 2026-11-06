/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "usb.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdint.h>

struct sunxi_musb_data
{
    rt_uint32_t phy_iscr_offset;
    rt_uint32_t phy_dpdm_pullup_mask;
    rt_uint32_t phy_id_pullup_mask;
    rt_uint32_t phy_force_id_mask;
    rt_uint32_t phy_force_id_device;
    rt_uint32_t phy_force_vbus_mask;
    rt_uint32_t phy_force_vbus_valid;
    rt_uint32_t phy_ctrl_offset;
    rt_uint32_t phy_siddq_mask;
    rt_uint32_t phy_vbus_valid_mask;
    rt_uint32_t phy_sel_offset;
    rt_uint32_t phy_otg_select_mask;
    rt_uint32_t vend0_offset;
    rt_uint8_t vend0_bus_select_mask;
    rt_uint32_t syscfg_boot_rammap_offset;
    rt_uint32_t syscfg_usb_sram_mask;
};

struct sunxi_musb
{
    struct rt_clk *bus_clk;
    struct rt_clk *otg_clk;
    struct rt_reset_control *phy_reset;
    struct rt_reset_control *controller_reset;
    struct rt_syscon *syscon;
    const struct sunxi_musb_data *data;
    void *base;
    int irq;
};

static struct sunxi_musb *sunxi_musb0;

extern void USBD_IRQHandler(rt_uint8_t busid);

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM_CHARDEV
extern void cdc_acm_chardev_init(uint8_t busid, uintptr_t reg_base);
#endif

static void sunxi_musb_phy_device_mode(struct sunxi_musb *musb)
{
    rt_uint32_t value;
    volatile rt_uint8_t *vend0;

    /* Force the shared OTG PHY into peripheral mode before soft-connect. */
    value = HWREG32(musb->base + musb->data->phy_iscr_offset);
    value |= musb->data->phy_dpdm_pullup_mask | musb->data->phy_id_pullup_mask;
    value &= ~(musb->data->phy_force_id_mask | musb->data->phy_force_vbus_mask);
    value |= musb->data->phy_force_id_device | musb->data->phy_force_vbus_valid;
    HWREG32(musb->base + musb->data->phy_iscr_offset) = value;

    value = HWREG32(musb->base + musb->data->phy_ctrl_offset);
    value |= musb->data->phy_vbus_valid_mask;
    value &= ~musb->data->phy_siddq_mask;
    HWREG32(musb->base + musb->data->phy_ctrl_offset) = value;

    value = HWREG32(musb->base + musb->data->phy_sel_offset);
    value |= musb->data->phy_otg_select_mask;
    HWREG32(musb->base + musb->data->phy_sel_offset) = value;

    vend0 = (volatile rt_uint8_t *)(musb->base + musb->data->vend0_offset);
    *vend0 |= musb->data->vend0_bus_select_mask;

    rt_syscon_update_bits(musb->syscon, musb->data->syscfg_boot_rammap_offset,
            musb->data->syscfg_usb_sram_mask, 0);
}

static void sunxi_musb_isr(int vector, void *param)
{
    RT_UNUSED(vector);
    RT_UNUSED(param);

    USBD_IRQHandler(0);
}

/* Called by CherryUSB after it has registered the MUSB register base. */
void usb_dc_low_level_init(void)
{
    RT_ASSERT(sunxi_musb0 != RT_NULL);

    sunxi_musb_phy_device_mode(sunxi_musb0);
}

static void sunxi_musb_free(struct sunxi_musb *musb)
{
    if (!rt_is_err_or_null(musb->controller_reset))
    {
        rt_reset_control_assert(musb->controller_reset);
        rt_reset_control_put(musb->controller_reset);
    }
    if (!rt_is_err_or_null(musb->phy_reset))
    {
        rt_reset_control_assert(musb->phy_reset);
        rt_reset_control_put(musb->phy_reset);
    }
    if (!rt_is_err_or_null(musb->otg_clk))
    {
        rt_clk_disable_unprepare(musb->otg_clk);
        rt_clk_put(musb->otg_clk);
    }
    if (!rt_is_err_or_null(musb->bus_clk))
    {
        rt_clk_disable_unprepare(musb->bus_clk);
        rt_clk_put(musb->bus_clk);
    }
    if (musb->base)
    {
        rt_iounmap(musb->base);
    }
    rt_free(musb);
}

static rt_err_t sunxi_musb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_musb *musb;

    if (sunxi_musb0)
    {
        return -RT_EBUSY;
    }

    musb = rt_calloc(1, sizeof(*musb));
    if (!musb)
    {
        return -RT_ENOMEM;
    }

    musb->irq = -1;
    musb->data = pdev->id->data;
    musb->base = rt_dm_dev_iomap(dev, 0);
    if (!musb->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    musb->syscon = rt_syscon_find_by_ofw_phandle(dev->ofw_node,
            "allwinner,syscon");
    if (!musb->syscon)
    {
        err = -RT_EIO;
        goto _fail;
    }

    musb->bus_clk = rt_clk_get_by_name(dev, "bus");
    musb->otg_clk = rt_clk_get_by_name(dev, "mod");
    if (rt_is_err(musb->bus_clk) || rt_is_err(musb->otg_clk))
    {
        err = rt_is_err(musb->bus_clk) ? rt_ptr_err(musb->bus_clk) :
                rt_ptr_err(musb->otg_clk);
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(musb->bus_clk)) ||
            (err = rt_clk_prepare_enable(musb->otg_clk)))
    {
        goto _fail;
    }

    musb->phy_reset = rt_reset_control_get_by_name(dev, "phy");
    musb->controller_reset = rt_reset_control_get_by_name(dev, "controller");
    if (rt_is_err(musb->phy_reset) || rt_is_err(musb->controller_reset))
    {
        err = rt_is_err(musb->phy_reset) ? rt_ptr_err(musb->phy_reset) :
                rt_ptr_err(musb->controller_reset);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(musb->phy_reset)))
    {
        goto _fail;
    }
    rt_hw_us_delay(1000);
    if ((err = rt_reset_control_deassert(musb->controller_reset)))
    {
        goto _fail;
    }
    rt_hw_us_delay(1000);

    musb->irq = rt_dm_dev_get_irq(dev, 0);
    if (musb->irq < 0)
    {
        err = musb->irq;
        goto _fail;
    }
    rt_hw_interrupt_install(musb->irq, sunxi_musb_isr, musb, "sunxi-musb");
    rt_hw_interrupt_umask(musb->irq);

    dev->user_data = musb;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, musb);
    sunxi_musb0 = musb;

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM_CHARDEV
    cdc_acm_chardev_init(0, (uintptr_t)musb->base);
#endif

    LOG_D("MUSB device controller ready");
    return RT_EOK;

_fail:
    sunxi_musb_free(musb);
    return err;
}

static rt_err_t sunxi_musb_remove(struct rt_platform_device *pdev)
{
    struct sunxi_musb *musb = pdev->parent.user_data;

    if (musb->irq >= 0)
    {
        rt_hw_interrupt_mask(musb->irq);
        rt_pic_detach_irq(musb->irq, musb);
    }
    sunxi_musb0 = RT_NULL;
    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    sunxi_musb_free(musb);

    return RT_EOK;
}

static const struct sunxi_musb_data sun252i_f101_musb_data =
{
    .phy_iscr_offset = 0x400,
    .phy_dpdm_pullup_mask = RT_BIT(16),
    .phy_id_pullup_mask = RT_BIT(17),
    .phy_force_id_mask = 0xc000,
    .phy_force_id_device = 0xc000,
    .phy_force_vbus_mask = 0x3000,
    .phy_force_vbus_valid = 0x3000,
    .phy_ctrl_offset = 0x410,
    .phy_siddq_mask = RT_BIT(3),
    .phy_vbus_valid_mask = RT_BIT(5),
    .phy_sel_offset = 0x420,
    .phy_otg_select_mask = RT_BIT(0),
    .vend0_offset = 0x43,
    .vend0_bus_select_mask = RT_BIT(0),
    .syscfg_boot_rammap_offset = 0x4,
    .syscfg_usb_sram_mask = RT_BIT(27) | RT_BIT(25),
};

static const struct rt_ofw_node_id sunxi_musb_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-musb", .data = &sun252i_f101_musb_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_musb_driver =
{
    .name = "sunxi-musb",
    .ids = sunxi_musb_ofw_ids,
    .probe = sunxi_musb_probe,
    .remove = sunxi_musb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_musb_driver);
