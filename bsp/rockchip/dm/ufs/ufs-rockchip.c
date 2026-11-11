/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/ufs.h>

#define DBG_TAG "ufs.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SEL_TX_LANE0                0x0
#define SEL_TX_LANE1                0x1
#define SEL_RX_LANE0                0x4
#define SEL_RX_LANE1                0x5

#define MPHY_CFG                    0x200
#define MPHY_CFG_ENABLE             0x40
#define MPHY_CFG_DISABLE            0x0

#define MIB_T_DBG_CPORT_TX_ENDIAN   0xc022
#define MIB_T_DBG_CPORT_RX_ENDIAN   0xc023

#define PA_LOCAL_TX_LCC_ENABLE      0x155e
#define N_DEVICEID                  0x1560
#define N_DEVICEID_VALID            0x1561
#define T_PEERDEVICEID              0x4021
#define T_CONNECTIONSTATE           0x4020

#define CMN_REG23                   0x08c
#define CMN_REG25                   0x094
#define TRSV0_REG08                 0x0e0
#define TRSV1_REG08                 0x220
#define TRSV0_REG14                 0x110
#define TRSV1_REG14                 0x250
#define TRSV0_REG15                 0x134
#define TRSV1_REG15                 0x274
#define TRSV0_REG16                 0x128
#define TRSV1_REG16                 0x268
#define TRSV0_REG17                 0x12c
#define TRSV1_REG17                 0x26c
#define TRSV0_REG18                 0x120
#define TRSV1_REG18                 0x260
#define TRSV0_REG29                 0x164
#define TRSV1_REG29                 0x2a4
#define TRSV0_REG2E                 0x178
#define TRSV1_REG2E                 0x2b8
#define TRSV0_REG3C                 0x1b0
#define TRSV1_REG3C                 0x2f0
#define TRSV0_REG3D                 0x1b4
#define TRSV1_REG3D                 0x2f4

#define UIC_ARG_MIB_SEL(attr, sel)  ((((rt_uint32_t)(attr)) & 0xffffu) << 16 | (((rt_uint32_t)(sel)) & 0xffffu))

struct rockchip_ufs_host
{
    struct rt_ufs_host parent;

    void *mphy_base;

    rt_base_t rst_pin;
    rt_uint8_t rst_active_val;

    struct rt_reset_control *rstc;
    struct rt_clk *ref_out_clk;
    struct rt_clk_array *clk_arr;

    rt_uint32_t phy_config_mode;
};

#define ufs_sys_writel(base, val, reg)          HWREG32((base) + (reg)) = (val)

static const rt_uint8_t rk3576_phy_value[15][4] =
{
    { 0x03, 0x38, 0x50, 0x80 },
    { 0x03, 0x14, 0x58, 0x80 },
    { 0x03, 0x26, 0x58, 0x80 },
    { 0x03, 0x49, 0x58, 0x80 },
    { 0x03, 0x5a, 0x58, 0x80 },
    { 0xc3, 0x38, 0x50, 0xc0 },
    { 0xc3, 0x14, 0x58, 0xc0 },
    { 0xc3, 0x26, 0x58, 0xc0 },
    { 0xc3, 0x49, 0x58, 0xc0 },
    { 0xc3, 0x5a, 0x58, 0xc0 },
    { 0x43, 0x38, 0x50, 0xc0 },
    { 0x43, 0x14, 0x58, 0xc0 },
    { 0x43, 0x26, 0x58, 0xc0 },
    { 0x43, 0x49, 0x58, 0xc0 },
    { 0x43, 0x5a, 0x58, 0xc0 }
};

static void rk3576_controller_reset(struct rockchip_ufs_host *rkufs)
{
    if (rkufs->rstc && !rt_is_err(rkufs->rstc))
    {
        rt_reset_control_assert(rkufs->rstc);
        rt_hw_us_delay(1);
        rt_reset_control_deassert(rkufs->rstc);
    }
}

static rt_err_t rk3576_phy_parameter_init(struct rockchip_ufs_host *rkufs)
{
    rt_uint32_t try_case = rkufs->phy_config_mode;
    rt_uint32_t value;

    if (!rkufs->mphy_base)
    {
        return -RT_EIO;
    }

    if (try_case >= RT_ARRAY_SIZE(rk3576_phy_value))
    {
        try_case = 0;
    }

    ufs_sys_writel(rkufs->mphy_base, 0x80, CMN_REG23);
    ufs_sys_writel(rkufs->mphy_base, 0xb5, TRSV0_REG14);
    ufs_sys_writel(rkufs->mphy_base, 0xb5, TRSV1_REG14);

    value = rk3576_phy_value[try_case][0];
    ufs_sys_writel(rkufs->mphy_base, value, TRSV0_REG15);
    ufs_sys_writel(rkufs->mphy_base, value, TRSV1_REG15);

    value = rk3576_phy_value[try_case][1];
    ufs_sys_writel(rkufs->mphy_base, value, TRSV0_REG08);
    ufs_sys_writel(rkufs->mphy_base, value, TRSV1_REG08);

    value = rk3576_phy_value[try_case][2];
    ufs_sys_writel(rkufs->mphy_base, value, TRSV0_REG29);
    ufs_sys_writel(rkufs->mphy_base, value, TRSV1_REG29);

    value = rk3576_phy_value[try_case][3];
    ufs_sys_writel(rkufs->mphy_base, value, TRSV0_REG2E);
    ufs_sys_writel(rkufs->mphy_base, value, TRSV1_REG2E);

    ufs_sys_writel(rkufs->mphy_base, 0x18, TRSV0_REG3C);
    ufs_sys_writel(rkufs->mphy_base, 0x18, TRSV1_REG3C);

    ufs_sys_writel(rkufs->mphy_base, 0x03, TRSV0_REG16);
    ufs_sys_writel(rkufs->mphy_base, 0x03, TRSV1_REG16);

    ufs_sys_writel(rkufs->mphy_base, 0x20, TRSV0_REG17);
    ufs_sys_writel(rkufs->mphy_base, 0x20, TRSV1_REG17);

    ufs_sys_writel(rkufs->mphy_base, 0xc0, TRSV0_REG18);
    ufs_sys_writel(rkufs->mphy_base, 0xc0, TRSV1_REG18);

    ufs_sys_writel(rkufs->mphy_base, 0x03, CMN_REG25);
    ufs_sys_writel(rkufs->mphy_base, 0x03, TRSV0_REG3D);
    ufs_sys_writel(rkufs->mphy_base, 0x03, TRSV1_REG3D);

    ufs_sys_writel(rkufs->mphy_base, 0xc0, CMN_REG23);
    rt_hw_us_delay(1);
    ufs_sys_writel(rkufs->mphy_base, 0x00, CMN_REG23);
    rt_hw_us_delay(200);

    return RT_EOK;
}

static rt_err_t rk3576_phy_init(struct rockchip_ufs_host *rkufs)
{
    rt_err_t err;
    struct rt_ufs_host *ufs = &rkufs->parent;

    if ((err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(PA_LOCAL_TX_LCC_ENABLE, 0), 0)))
    {
        return err;
    }

    if ((err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(MPHY_CFG, 0), MPHY_CFG_ENABLE)))
    {
        return err;
    }

    for (int i = 0; i < 2; ++i)
    {
        if ((err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0xaa, SEL_TX_LANE0 + i), 0x06)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0xa9, SEL_TX_LANE0 + i), 0x02)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0xad, SEL_TX_LANE0 + i), 0x44)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0xac, SEL_TX_LANE0 + i), 0xe6)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0xab, SEL_TX_LANE0 + i), 0x07)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x94, SEL_TX_LANE0 + i), 0x93)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x93, SEL_TX_LANE0 + i), 0xc9)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x7f, SEL_TX_LANE0 + i), 0x00)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x12, SEL_RX_LANE0 + i), 0x06)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x11, SEL_RX_LANE0 + i), 0x00)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x1d, SEL_RX_LANE0 + i), 0x58)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x1c, SEL_RX_LANE0 + i), 0x8c)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x1b, SEL_RX_LANE0 + i), 0x02)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x25, SEL_RX_LANE0 + i), 0xf6)) ||
            (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(0x2f, SEL_RX_LANE0 + i), 0x69)))
        {
            return err;
        }
    }

    if ((err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(MPHY_CFG, 0), MPHY_CFG_DISABLE)))
    {
        return err;
    }

    if ((err = rk3576_phy_parameter_init(rkufs)))
    {
        return err;
    }

    if ((err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(MIB_T_DBG_CPORT_TX_ENDIAN, 0), 0)) ||
        (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(MIB_T_DBG_CPORT_RX_ENDIAN, 0), 0)) ||
        (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(N_DEVICEID, 0), 0)) ||
        (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(N_DEVICEID_VALID, 0), 1)) ||
        (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(T_PEERDEVICEID, 0), 1)) ||
        (err = rt_ufs_dme_set(ufs, UIC_ARG_MIB_SEL(T_CONNECTIONSTATE, 0), 1)))
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t rk3576_ufs_init(struct rt_ufs_host *ufs)
{
    rt_err_t err;
    struct rt_device *dev = ufs->parent.dev;
    struct rockchip_ufs_host *rkufs = rt_container_of(ufs, struct rockchip_ufs_host, parent);

    rkufs->clk_arr = rt_clk_get_array(dev);
    if (rt_is_err(rkufs->clk_arr))
    {
        return rt_ptr_err(rkufs->clk_arr);
    }

    if ((err = rt_clk_array_prepare_enable(rkufs->clk_arr)))
    {
        return err;
    }

    rkufs->ref_out_clk = rt_clk_get_by_name(dev, "ref_out");
    if (rt_is_err(rkufs->ref_out_clk))
    {
        return rt_ptr_err(rkufs->ref_out_clk);
    }

    rt_clk_prepare_enable(rkufs->ref_out_clk);

    rkufs->rstc = rt_reset_control_get_array(dev);
    if (rt_is_err(rkufs->rstc))
    {
        return rt_ptr_err(rkufs->rstc);
    }

    rk3576_controller_reset(rkufs);

    rkufs->rst_pin = rt_pin_get_named_pin(dev, "reset", 0, RT_NULL, &rkufs->rst_active_val);
    if (rkufs->rst_pin >= 0)
    {
        rt_pin_write(rkufs->rst_pin, !rkufs->rst_active_val);
        rt_pin_mode(rkufs->rst_pin, PIN_MODE_OUTPUT);
    }

    if (rt_dm_dev_prop_read_u32(dev, "ufs-phy-config-mode", &rkufs->phy_config_mode))
    {
        rkufs->phy_config_mode = 0;
    }

    return RT_EOK;
}

static rt_err_t rk3576_ufs_exit(struct rt_ufs_host *ufs)
{
    struct rockchip_ufs_host *rkufs = rt_container_of(ufs, struct rockchip_ufs_host, parent);

    if (rkufs->rstc && !rt_is_err(rkufs->rstc))
    {
        rt_reset_control_assert(rkufs->rstc);
        rt_reset_control_put(rkufs->rstc);
        rkufs->rstc = RT_NULL;
    }

    if (rkufs->ref_out_clk && !rt_is_err(rkufs->ref_out_clk))
    {
        rt_clk_disable_unprepare(rkufs->ref_out_clk);
        rkufs->ref_out_clk = RT_NULL;
    }

    if (rkufs->clk_arr && !rt_is_err(rkufs->clk_arr))
    {
        rt_clk_array_disable_unprepare(rkufs->clk_arr);
        rt_clk_array_put(rkufs->clk_arr);
        rkufs->clk_arr = RT_NULL;
    }

    return RT_EOK;
}

static rt_err_t rk3576_ufs_reset(struct rt_ufs_host *ufs)
{
    struct rockchip_ufs_host *rkufs = rt_container_of(ufs, struct rockchip_ufs_host, parent);

    if (rkufs->rst_pin >= 0)
    {
        rt_pin_write(rkufs->rst_pin, rkufs->rst_active_val);
        rt_hw_us_delay(20);
        rt_pin_write(rkufs->rst_pin, !rkufs->rst_active_val);
        rt_hw_us_delay(20);
    }

    rk3576_controller_reset(rkufs);

    return RT_EOK;
}

static rt_err_t rk3576_hce_enable_notify(struct rt_ufs_host *ufs, enum rt_ufs_notify_change_status status)
{
    struct rockchip_ufs_host *rkufs = rt_container_of(ufs, struct rockchip_ufs_host, parent);
    rt_err_t err;

    if (status == RT_UFS_NOTIFY_CHANGE_STATUS_PRE)
    {
        rk3576_controller_reset(rkufs);
        return RT_EOK;
    }

    if ((err = rt_ufs_dme_reset(ufs)))
    {
        return err;
    }

    if ((err = rt_ufs_dme_enable(ufs)))
    {
        return err;
    }

    return rk3576_phy_init(rkufs);
}

static const struct rt_ufs_ops rk3576_ufs_ops =
{
    .init = rk3576_ufs_init,
    .exit = rk3576_ufs_exit,
    .reset = rk3576_ufs_reset,
    .hce_enable_notify = rk3576_hce_enable_notify,
};

static rt_err_t rockchip_ufs_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_ufs_host *ufs;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_ufs_host *rkufs = rt_calloc(1, sizeof(*rkufs));

    if (!rkufs)
    {
        return -RT_ENOMEM;
    }

    ufs = &rkufs->parent;
    ufs->parent.dev = dev;
    ufs->ops = pdev->id->data;

    ufs->regs = rt_dm_dev_iomap_by_name(dev, "hci");
    if (!ufs->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rkufs->mphy_base = rt_dm_dev_iomap_by_name(dev, "mphy");
    if (!rkufs->mphy_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ufs->irq = rt_dm_dev_get_irq(dev, 0);
    if (ufs->irq < 0)
    {
        err = (rt_err_t)ufs->irq;
        goto _fail;
    }

    if ((err = rt_ufs_host_register(ufs)))
    {
        goto _fail;
    }

    dev->user_data = rkufs;
    pdev->parent.user_data = rkufs;

    return RT_EOK;

_fail:
    if (ufs->regs)
    {
        rt_iounmap(ufs->regs);
    }
    if (rkufs->mphy_base)
    {
        rt_iounmap(rkufs->mphy_base);
    }

    rt_free(rkufs);

    return err;
}

static rt_err_t rockchip_ufs_remove(struct rt_platform_device *pdev)
{
    struct rockchip_ufs_host *rkufs = pdev->parent.user_data;
    struct rt_ufs_host *ufs = &rkufs->parent;

    rt_ufs_host_unregister(ufs);

    if (ufs->regs)
    {
        rt_iounmap(ufs->regs);
    }
    if (rkufs->mphy_base)
    {
        rt_iounmap(rkufs->mphy_base);
    }

    rt_free(rkufs);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_ufs_ofw_ids[] =
{
    { .compatible = "rockchip,rk3576-ufshc", .data = &rk3576_ufs_ops },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_ufs_driver =
{
    .name = "rockchip-ufs",
    .ids = rockchip_ufs_ofw_ids,

    .probe = rockchip_ufs_probe,
    .remove = rockchip_ufs_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_ufs_driver);
