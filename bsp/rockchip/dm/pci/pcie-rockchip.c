/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-rockchip.h"

#define rockchip_pcie_read_addr(addr)   rockchip_pcie_read(rk_pcie, addr)
/* 100 ms max wait time for PHY PLLs to lock */
#define RK_PHY_PLL_LOCK_TIMEOUT_US      100000
/* Sleep should be less than 20ms */
#define RK_PHY_PLL_LOCK_SLEEP_US        1000

rt_err_t rockchip_pcie_ofw_parse(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct rt_device *dev = rk_pcie->dev;

    if (rk_pcie->is_rc)
    {
        rk_pcie->axi_base = rt_dm_dev_iomap_by_name(dev, "axi-base");

        if (!rk_pcie->axi_base)
        {
            return -RT_EIO;
        }
    }
    else
    {
        if ((err = rt_dm_dev_get_address_by_name(dev, "mem-base",
            &rk_pcie->mem_base_addr, &rk_pcie->mem_base_size)))
        {
            return err;
        }
    }

    rk_pcie->apb_base = rt_dm_dev_iomap_by_name(dev, "apb-base");

    if (!rk_pcie->apb_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((err = rockchip_pcie_get_phys(rk_pcie)))
    {
        goto _fail;
    }

    rk_pcie->num_lanes = 1;
    err = rt_dm_dev_prop_read_u32(dev, "num-lanes", &rk_pcie->num_lanes);
    if (!err && (rk_pcie->num_lanes == 0 || rk_pcie->num_lanes == 3 || rk_pcie->num_lanes > 4))
    {
        rk_pcie->num_lanes = 1;
    }

    rk_pcie->link_gen = -1;
    rt_dm_dev_prop_read_u32(dev, "max-link-speed", &rk_pcie->link_gen);
    if (rk_pcie->link_gen < 0 || rk_pcie->link_gen > 2)
    {
        rk_pcie->link_gen = 2;
    }

    rk_pcie->core_rstc = rt_reset_control_get_by_name(dev, "core");
    if (rt_is_err(rk_pcie->core_rstc))
    {
        err = rt_ptr_err(rk_pcie->core_rstc);
        goto _fail;
    }

    rk_pcie->mgmt_rstc = rt_reset_control_get_by_name(dev, "mgmt");
    if (rt_is_err(rk_pcie->mgmt_rstc))
    {
        err = rt_ptr_err(rk_pcie->mgmt_rstc);
        goto _fail;
    }

    rk_pcie->mgmt_sticky_rstc = rt_reset_control_get_by_name(dev, "mgmt-sticky");
    if (rt_is_err(rk_pcie->mgmt_sticky_rstc))
    {
        err = rt_ptr_err(rk_pcie->mgmt_sticky_rstc);
        goto _fail;
    }

    rk_pcie->pipe_rstc = rt_reset_control_get_by_name(dev, "pipe");
    if (rt_is_err(rk_pcie->pipe_rstc))
    {
        err = rt_ptr_err(rk_pcie->pipe_rstc);
        goto _fail;
    }

    rk_pcie->pm_rstc = rt_reset_control_get_by_name(dev, "pm");
    if (rt_is_err(rk_pcie->pm_rstc))
    {
        err = rt_ptr_err(rk_pcie->pm_rstc);
        goto _fail;
    }

    rk_pcie->pclk_rstc = rt_reset_control_get_by_name(dev, "pclk");
    if (rt_is_err(rk_pcie->pclk_rstc))
    {
        err = rt_ptr_err(rk_pcie->pclk_rstc);
        goto _fail;
    }

    rk_pcie->aclk_rstc = rt_reset_control_get_by_name(dev, "aclk");
    if (rt_is_err(rk_pcie->aclk_rstc))
    {
        err = rt_ptr_err(rk_pcie->aclk_rstc);
        goto _fail;
    }

    if (rk_pcie->is_rc)
    {
        rt_uint8_t mode;

        rk_pcie->ep_pin = rt_pin_get_named_pin(dev, "ep", 0, &mode, &rk_pcie->active_val);

        if (rk_pcie->ep_pin < 0 && rk_pcie->ep_pin != PIN_NONE)
        {
            err = rk_pcie->ep_pin;
            goto _fail;
        }
        else if (rk_pcie->ep_pin >= 0)
        {
            rt_pin_mode(rk_pcie->ep_pin, mode);
        }
    }

    rk_pcie->aclk_pcie = rt_clk_get_by_name(dev, "aclk");
    if (rt_is_err(rk_pcie->aclk_pcie))
    {
        err = rt_ptr_err(rk_pcie->aclk_pcie);
        goto _fail;
    }

    rk_pcie->aclk_perf_pcie = rt_clk_get_by_name(dev, "aclk-perf");
    if (rt_is_err(rk_pcie->aclk_perf_pcie))
    {
        err = rt_ptr_err(rk_pcie->aclk_perf_pcie);
        goto _fail;
    }

    rk_pcie->hclk_pcie = rt_clk_get_by_name(dev, "hclk");
    if (rt_is_err(rk_pcie->hclk_pcie))
    {
        err = rt_ptr_err(rk_pcie->hclk_pcie);
        goto _fail;
    }

    rk_pcie->clk_pcie_pm = rt_clk_get_by_name(dev, "pm");
    if (rt_is_err(rk_pcie->clk_pcie_pm))
    {
        err = rt_ptr_err(rk_pcie->clk_pcie_pm);
        goto _fail;
    }

    return RT_EOK;

_fail:
    rockchip_pcie_common_free(rk_pcie);

    return err;
}

rt_err_t rockchip_pcie_init_port(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    rt_uint32_t regs;

    if ((err = rt_reset_control_assert(rk_pcie->aclk_rstc)))
    {
        LOG_E("Assert aclk_rstc error = %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_reset_control_assert(rk_pcie->pclk_rstc)))
    {
        LOG_E("Assert pclk_rstc error = %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_reset_control_assert(rk_pcie->pm_rstc)))
    {
        LOG_E("Assert pm_rstc error = %s", rt_strerror(err));
        return err;
    }

    for (int i = 0; i < MAX_LANE_NUM; i++)
    {
        if ((err = rt_phye_init(rk_pcie->phys[i])))
        {
            LOG_E("Init phy%d err %d", i, err);
            goto _err_exit_phy;
        }
    }

    if ((err = rt_reset_control_assert(rk_pcie->core_rstc)))
    {
        LOG_E("Assert core_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if ((err = rt_reset_control_assert(rk_pcie->mgmt_rstc)))
    {
        LOG_E("Assert mgmt_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if ((err = rt_reset_control_assert(rk_pcie->mgmt_sticky_rstc)))
    {
        LOG_E("Assert mgmt_sticky_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if ((err = rt_reset_control_assert(rk_pcie->pipe_rstc)))
    {
        LOG_E("Assert pipe_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    rt_hw_us_delay(10);

    if ((err = rt_reset_control_deassert(rk_pcie->pm_rstc)))
    {
        LOG_E("Deassert pm_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if ((err = rt_reset_control_deassert(rk_pcie->aclk_rstc)))
    {
        LOG_E("Deassert aclk_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if ((err = rt_reset_control_deassert(rk_pcie->pclk_rstc)))
    {
        LOG_E("Deassert pclk_rstc error = %s", rt_strerror(err));
        goto _err_exit_phy;
    }

    if (rk_pcie->link_gen == 2)
    {
        rockchip_pcie_write(rk_pcie, PCIE_CLIENT_GEN_SEL_2, PCIE_CLIENT_CONFIG);
    }
    else
    {
        rockchip_pcie_write(rk_pcie, PCIE_CLIENT_GEN_SEL_1, PCIE_CLIENT_CONFIG);
    }

    regs = PCIE_CLIENT_LINK_TRAIN_ENABLE | PCIE_CLIENT_ARI_ENABLE |
            PCIE_CLIENT_CONF_LANE_NUM(rk_pcie->num_lanes);

    if (rk_pcie->is_rc)
    {
        regs |= PCIE_CLIENT_CONF_ENABLE | PCIE_CLIENT_MODE_RC;
    }
    else
    {
        regs |= PCIE_CLIENT_CONF_DISABLE | PCIE_CLIENT_MODE_EP;
    }

    rockchip_pcie_write(rk_pcie, regs, PCIE_CLIENT_CONFIG);

    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        if ((err = rt_phye_power_on(rk_pcie->phys[i])))
        {
            LOG_E("Power on PHY(%d) error = %s", i, rt_strerror(err));
            goto _err_power_off_phy;
        }
    }

    err = readx_poll_timeout(rockchip_pcie_read_addr,
            PCIE_CLIENT_SIDE_BAND_STATUS, regs, !(regs & PCIE_CLIENT_PHY_ST),
            RK_PHY_PLL_LOCK_SLEEP_US, RK_PHY_PLL_LOCK_TIMEOUT_US);

    if (err)
    {
        LOG_E("PHY PLLs could not lock, %d", err);
        goto _err_power_off_phy;
    }

    /*
     * Please don't reorder the deassert sequence of the following
     * four reset pins.
     */
    if ((err = rt_reset_control_deassert(rk_pcie->mgmt_sticky_rstc)))
    {
        LOG_E("Deassert mgmt_sticky_rstc error = %s", rt_strerror(err));
        goto _err_power_off_phy;
    }

    if ((err = rt_reset_control_deassert(rk_pcie->core_rstc)))
    {
        LOG_E("Deassert core_rstc error = %s", rt_strerror(err));
        goto _err_power_off_phy;
    }

    if ((err = rt_reset_control_deassert(rk_pcie->mgmt_rstc)))
    {
        LOG_E("Deassert mgmt_rstc error = %s", rt_strerror(err));
        goto _err_power_off_phy;
    }

    if ((err = rt_reset_control_deassert(rk_pcie->pipe_rstc)))
    {
        LOG_E("Deassert pipe_rstc error = %s", rt_strerror(err));
        goto _err_power_off_phy;
    }

    return RT_EOK;

_err_power_off_phy:
    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        rt_phye_power_off(rk_pcie->phys[i]);
    }

_err_exit_phy:
    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        rt_phye_exit(rk_pcie->phys[i]);
    }

    return err;
}

rt_err_t rockchip_pcie_get_phys(struct rockchip_pcie *rk_pcie)
{
    char name[16];
    struct rt_phye *phy;
    struct rt_device *dev = rk_pcie->dev;

    phy = rt_phye_get_by_name(dev, "pcie-phy");

    if (!rt_is_err_or_null(phy))
    {
        rk_pcie->legacy_phy = RT_TRUE;
        rk_pcie->phys[0] = phy;

        LOG_W("legacy phy model is deprecated");
        return RT_EOK;
    }

    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        rt_snprintf(name, sizeof(name), "pcie-phy-%u", i);

        phy = rt_phye_get_by_name(dev, name);

        if (rt_is_err(phy))
        {
            LOG_E("Missing phy for lane %u", i);
            return rt_ptr_err(phy);
        }

        rk_pcie->phys[i] = phy;
    }

    return RT_EOK;
}

void rockchip_pcie_deinit_phys(struct rockchip_pcie *rk_pcie)
{
    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        struct rt_phye *phy = rk_pcie->phys[i];

        /* Inactive lanes are already powered off */
        if (rk_pcie->lanes_map & RT_BIT(i))
        {
            rt_phye_power_off(phy);
        }

        rt_phye_exit(phy);
        rt_phye_put(phy);
    }
}

rt_err_t rockchip_pcie_enable_clocks(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;

    if ((err = rt_clk_prepare_enable(rk_pcie->aclk_pcie)))
    {
        LOG_E("Unable to enable aclk_pcie clock");
        return err;
    }

    if ((err = rt_clk_prepare_enable(rk_pcie->aclk_perf_pcie)))
    {
        LOG_E("Unable to enable aclk_perf_pcie clock");
        goto _err_aclk_perf_pcie;
    }

    if ((err = rt_clk_prepare_enable(rk_pcie->hclk_pcie)))
    {
        LOG_E("Unable to enable hclk_pcie clock");
        goto _err_hclk_pcie;
    }

    if ((err = rt_clk_prepare_enable(rk_pcie->clk_pcie_pm)))
    {
        LOG_E("Unable to enable clk_pcie_pm clock");
        goto _err_clk_pcie_pm;
    }

    return 0;

_err_clk_pcie_pm:
    rt_clk_disable_unprepare(rk_pcie->hclk_pcie);
_err_hclk_pcie:

    rt_clk_disable_unprepare(rk_pcie->aclk_perf_pcie);

_err_aclk_perf_pcie:
    rt_clk_disable_unprepare(rk_pcie->aclk_pcie);

    return err;
}

void rockchip_pcie_disable_clocks(struct rockchip_pcie *rk_pcie)
{
    rt_clk_disable_unprepare(rk_pcie->clk_pcie_pm);
    rt_clk_disable_unprepare(rk_pcie->hclk_pcie);
    rt_clk_disable_unprepare(rk_pcie->aclk_perf_pcie);
    rt_clk_disable_unprepare(rk_pcie->aclk_pcie);
}

void rockchip_pcie_common_free(struct rockchip_pcie *rk_pcie)
{
    if (!rt_is_err_or_null(rk_pcie->aclk_pcie))
    {
        rt_clk_put(rk_pcie->aclk_pcie);
    }

    if (!rt_is_err_or_null(rk_pcie->aclk_perf_pcie))
    {
        rt_clk_put(rk_pcie->aclk_perf_pcie);
    }

    if (!rt_is_err_or_null(rk_pcie->hclk_pcie))
    {
        rt_clk_put(rk_pcie->hclk_pcie);
    }

    if (!rt_is_err_or_null(rk_pcie->clk_pcie_pm))
    {
        rt_clk_put(rk_pcie->clk_pcie_pm);
    }

    if (!rt_is_err_or_null(rk_pcie->core_rstc))
    {
        rt_reset_control_put(rk_pcie->core_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->mgmt_rstc))
    {
        rt_reset_control_put(rk_pcie->mgmt_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->mgmt_sticky_rstc))
    {
        rt_reset_control_put(rk_pcie->mgmt_sticky_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->pipe_rstc))
    {
        rt_reset_control_put(rk_pcie->pipe_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->pm_rstc))
    {
        rt_reset_control_put(rk_pcie->pm_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->pclk_rstc))
    {
        rt_reset_control_put(rk_pcie->pclk_rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->aclk_rstc))
    {
        rt_reset_control_put(rk_pcie->aclk_rstc);
    }

    if (rk_pcie->axi_base)
    {
        rt_iounmap(rk_pcie->apb_base);
    }

    if (rk_pcie->apb_base)
    {
        rt_iounmap(rk_pcie->apb_base);
    }
}

void rockchip_pcie_cfg_configuration_accesses(struct rockchip_pcie *rk_pcie, rt_uint32_t type)
{
    rt_uint32_t ob_desc_0;

    /* Configuration Accesses for region 0 */
    rockchip_pcie_write(rk_pcie, 0x0, PCIE_RC_BAR_CONF);

    rockchip_pcie_write(rk_pcie,
            (RC_REGION_0_ADDR_TRANS_L + RC_REGION_0_PASS_BITS),
            PCIE_CORE_OB_REGION_ADDR0);
    rockchip_pcie_write(rk_pcie,
            RC_REGION_0_ADDR_TRANS_H,
            PCIE_CORE_OB_REGION_ADDR1);

    ob_desc_0 = rockchip_pcie_read(rk_pcie, PCIE_CORE_OB_REGION_DESC0);
    ob_desc_0 &= ~(RC_REGION_0_TYPE_MASK);
    ob_desc_0 |= (type | (0x1 << 23));

    rockchip_pcie_write(rk_pcie, ob_desc_0, PCIE_CORE_OB_REGION_DESC0);
    rockchip_pcie_write(rk_pcie, 0x0, PCIE_CORE_OB_REGION_DESC1);
}
