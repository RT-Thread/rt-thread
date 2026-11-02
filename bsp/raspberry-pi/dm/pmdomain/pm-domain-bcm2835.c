/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pm-domain.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <bcm2835-pm.h>
#include <dt-bindings/power/bcm2835-pm.h>

#define PM_GNRIC                        0x00
#define PM_AUDIO                        0x04
#define PM_STATUS                       0x18
#define PM_RSTC                         0x1c
#define PM_RSTS                         0x20
#define PM_WDOG                         0x24
#define PM_PADS0                        0x28
#define PM_PADS2                        0x2c
#define PM_PADS3                        0x30
#define PM_PADS4                        0x34
#define PM_PADS5                        0x38
#define PM_PADS6                        0x3c
#define PM_CAM0                         0x44
#define PM_CAM0_LDOHPEN                 RT_BIT(2)
#define PM_CAM0_LDOLPEN                 RT_BIT(1)
#define PM_CAM0_CTRLEN                  RT_BIT(0)

#define PM_CAM1                         0x48
#define PM_CAM1_LDOHPEN                 RT_BIT(2)
#define PM_CAM1_LDOLPEN                 RT_BIT(1)
#define PM_CAM1_CTRLEN                  RT_BIT(0)

#define PM_CCP2TX                       0x4c
#define PM_CCP2TX_LDOEN                 RT_BIT(1)
#define PM_CCP2TX_CTRLEN                RT_BIT(0)

#define PM_DSI0                         0x50
#define PM_DSI0_LDOHPEN                 RT_BIT(2)
#define PM_DSI0_LDOLPEN                 RT_BIT(1)
#define PM_DSI0_CTRLEN                  RT_BIT(0)

#define PM_DSI1                         0x54
#define PM_DSI1_LDOHPEN                 RT_BIT(2)
#define PM_DSI1_LDOLPEN                 RT_BIT(1)
#define PM_DSI1_CTRLEN                  RT_BIT(0)

#define PM_HDMI                         0x58
#define PM_HDMI_RSTDR                   RT_BIT(19)
#define PM_HDMI_LDOPD                   RT_BIT(1)
#define PM_HDMI_CTRLEN                  RT_BIT(0)

#define PM_USB                          0x5c
/*
 * The power gates must be enabled with this bit before enabling the LDO in the
 * USB block.
 */
#define PM_USB_CTRLEN                   RT_BIT(0)

#define PM_PXLDO                        0x60
#define PM_PXBG                         0x64
#define PM_DFT                          0x68
#define PM_SMPS                         0x6c
#define PM_XOSC                         0x70
#define PM_SPAREW                       0x74
#define PM_SPARER                       0x78
#define PM_AVS_RSTDR                    0x7c
#define PM_AVS_STAT                     0x80
#define PM_AVS_EVENT                    0x84
#define PM_AVS_INTEN                    0x88
#define PM_DUMMY                        0xfc

#define PM_IMAGE                        0x108
#define PM_GRAFX                        0x10c
#define PM_PROC                         0x110
#define PM_GRAFX_2712                   0x304
#define PM_ENAB                         RT_BIT(12)
#define PM_ISPRSTN                      RT_BIT(8)
#define PM_H264RSTN                     RT_BIT(7)
#define PM_PERIRSTN                     RT_BIT(6)
#define PM_V3DRSTN                      RT_BIT(6)
#define PM_ISFUNC                       RT_BIT(5)
#define PM_MRDONE                       RT_BIT(4)
#define PM_MEMREP                       RT_BIT(3)
#define PM_ISPOW                        RT_BIT(2)
#define PM_POWOK                        RT_BIT(1)
#define PM_POWUP                        RT_BIT(0)
#define PM_INRUSH_SHIFT                 13
#define PM_INRUSH_3_5_MA                0
#define PM_INRUSH_5_MA                  1
#define PM_INRUSH_10_MA                 2
#define PM_INRUSH_20_MA                 3
#define PM_INRUSH_MASK                  (3 << PM_INRUSH_SHIFT)

#define PM_PASSWORD                     0x5a000000

#define PM_WDOG_TIME_SET                0x000fffff
#define PM_RSTC_WRCFG_CLR               0xffffffcf
#define PM_RSTS_HADWRH_SET              0x00000040
#define PM_RSTC_WRCFG_SET               0x00000030
#define PM_RSTC_WRCFG_FULL_RESET        0x00000020
#define PM_RSTC_RESET                   0x00000102

#define PM_READ(reg)                    HWREG32(power->base + (reg))
#define PM_WRITE(reg, val)              HWREG32(power->base + (reg)) = PM_PASSWORD | (val)

#define ASB_BRDG_VERSION                0x00
#define ASB_CPR_CTRL                    0x04

#define ASB_V3D_S_CTRL                  0x08
#define ASB_V3D_M_CTRL                  0x0c
#define ASB_ISP_S_CTRL                  0x10
#define ASB_ISP_M_CTRL                  0x14
#define ASB_H264_S_CTRL                 0x18
#define ASB_H264_M_CTRL                 0x1c

#define ASB_REQ_STOP                    RT_BIT(0)
#define ASB_ACK                         RT_BIT(1)
#define ASB_EMPTY                       RT_BIT(2)
#define ASB_FULL                        RT_BIT(3)

#define ASB_AXI_BRDG_ID                 0x20

#define BCM2835_BRDG_ID                 0x62726467

struct bcm2835_power;

struct bcm2835_power_domain
{
    struct rt_dm_power_domain parent;
    const char *name;

    rt_uint32_t domain;
    struct rt_clk *clk;
    struct bcm2835_power *power;
};

#define raw_to_rpi_bcm2835_power_domain(raw) rt_container_of(raw, struct bcm2835_power_domain, parent)

struct bcm2835_power
{
    struct rt_dm_power_domain_proxy proxy_parent;
    struct rt_reset_controller rstc_parent;

    void *base;         /* PM registers. */
    void *asb;          /* AXI Async bridge registers. */
    void *rpivid_asb;   /* RPiVid bridge registers. */

    struct bcm2835_power_domain domains[BCM2835_POWER_DOMAIN_COUNT];
};

#define raw_to_bcm2835_power(raw) rt_container_of(raw, struct bcm2835_power, proxy_parent)

static rt_err_t bcm2835_asb_control(struct bcm2835_power *power, int reg, rt_bool_t enable)
{
    rt_uint32_t val;
    rt_bool_t timeout;
    void *base = power->asb;

    switch (reg)
    {
    case 0:
        return RT_EOK;

    case ASB_V3D_S_CTRL:
    case ASB_V3D_M_CTRL:
        if (power->rpivid_asb)
        {
            base = power->rpivid_asb;
        }
        break;

    default:
        return -RT_EINVAL;
    }

    timeout = RT_FALSE;

    /* Enable the module's async AXI bridges. */
    if (enable)
    {
        val = HWREG32(base + reg) & ~ASB_REQ_STOP;
    }
    else
    {
        val = HWREG32(base + reg) | ASB_REQ_STOP;
    }

    HWREG32(base + reg) = PM_PASSWORD | val;

    while (!!(HWREG32(base + reg) & ASB_ACK) == enable)
    {
        if (timeout)
        {
            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(1);
        timeout = RT_TRUE;

        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static rt_err_t bcm2835_asb_enable(struct bcm2835_power *power, int reg)
{
    return bcm2835_asb_control(power, reg, RT_TRUE);
}

static rt_err_t bcm2835_asb_disable(struct bcm2835_power *power, int reg)
{
    return bcm2835_asb_control(power, reg, RT_FALSE);
}

static rt_err_t bcm2835_power_power_off(struct bcm2835_power_domain *pd, int pm_reg)
{
    struct bcm2835_power *power = pd->power;

    /* We don't run this on BCM2711 */
    if (power->rpivid_asb)
    {
        return RT_EOK;
    }

    /* Enable functional isolation */
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISFUNC);

    /* Enable electrical isolation */
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISPOW);

    /* Open the power switches. */
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_POWUP);

    return RT_EOK;
}

static rt_err_t bcm2835_power_power_on(struct bcm2835_power_domain *pd, rt_uint32_t pm_reg)
{
    rt_err_t err;
    int inrush;
    rt_bool_t powok, timeout;
    struct bcm2835_power *power = pd->power;

    /* We don't run this on BCM2711 */
    if (power->rpivid_asb)
    {
        return RT_EOK;
    }

    /* If it was already powered on by the fw, leave it that way. */
    if (PM_READ(pm_reg) & PM_POWUP)
    {
        return RT_EOK;
    }

    /*
     * Enable power.  Allowing too much current at once may result
     * in POWOK never getting set, so start low and ramp it up as
     * necessary to succeed.
     */
    powok = RT_FALSE;
    for (inrush = PM_INRUSH_3_5_MA; inrush <= PM_INRUSH_20_MA; ++inrush)
    {
        PM_WRITE(pm_reg, (PM_READ(pm_reg) & ~PM_INRUSH_MASK) |
                (inrush << PM_INRUSH_SHIFT) | PM_POWUP);

        for (int i = 0; i < 3; ++i)
        {
            if ((powok = !!(PM_READ(pm_reg) & PM_POWOK)))
            {
                break;
            }

            rt_hw_us_delay(1);
            rt_hw_cpu_relax();
        }
    }

    if (!powok)
    {
        LOG_E("Timeout waiting for %s power OK", pd->name);

        err = -RT_ETIMEOUT;
        goto _err_disable_powup;
    }

    /* Disable electrical isolation */
    PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISPOW);

    /* Repair memory */
    PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_MEMREP);

    timeout = RT_FALSE;
    while (!(PM_READ(pm_reg) & PM_MRDONE))
    {
        if (timeout)
        {
            LOG_E("Timeout waiting for %s memory repair", pd->name);

            err = -RT_ETIMEOUT;
            goto _err_disable_ispow;
        }

        rt_hw_us_delay(1);
        timeout = RT_TRUE;

        rt_hw_cpu_relax();
    }

    /* Disable functional isolation */
    PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISFUNC);

    return RT_EOK;

_err_disable_ispow:
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISPOW);

_err_disable_powup:
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~(PM_POWUP | PM_INRUSH_MASK));

    return err;
}

static rt_err_t bcm2835_asb_power_on(struct bcm2835_power_domain *pd,
        rt_uint32_t pm_reg, rt_uint32_t asb_m_reg,
        rt_uint32_t asb_s_reg, rt_uint32_t reset_flags)
{
    rt_err_t err;
    struct bcm2835_power *power = pd->power;

    if ((err = rt_clk_prepare_enable(pd->clk)))
    {
        LOG_E("Failed to enable clock for %s", pd->name);
        return err;
    }

    /* Wait 32 clocks for reset to propagate, 1 us will be enough */
    rt_hw_us_delay(1);

    rt_clk_disable_unprepare(pd->clk);

    /* Deassert the resets. */
    PM_WRITE(pm_reg, PM_READ(pm_reg) | reset_flags);

    if ((err = rt_clk_prepare_enable(pd->clk)))
    {
        LOG_E("Failed to enable clock for %s", pd->name);
        goto _err_enable_resets;
    }

    if ((err = bcm2835_asb_enable(power, asb_m_reg)))
    {
        LOG_E("Failed to enable ASB master for %s", pd->name);
        goto _err_disable_clk;
    }

    if ((err = bcm2835_asb_enable(power, asb_s_reg)))
    {
        LOG_E("Failed to enable ASB slave for %s", pd->name);
        goto _err_disable_asb_master;
    }

    return RT_EOK;

_err_disable_asb_master:
    bcm2835_asb_disable(power, asb_m_reg);

_err_disable_clk:
    rt_clk_disable_unprepare(pd->clk);

_err_enable_resets:
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~reset_flags);

    return err;
}

static rt_err_t bcm2835_asb_power_off(struct bcm2835_power_domain *pd,
        rt_uint32_t pm_reg, rt_uint32_t asb_m_reg,
        rt_uint32_t asb_s_reg, rt_uint32_t reset_flags)
{
    rt_err_t err;
    struct bcm2835_power *power = pd->power;

    if ((err = bcm2835_asb_disable(power, asb_s_reg)))
    {
        LOG_W("Failed to disable ASB slave for %s", pd->name);

        return err;
    }

    if ((err = bcm2835_asb_disable(power, asb_m_reg)))
    {
        LOG_W("Failed to disable ASB master for %s", pd->name);
        bcm2835_asb_enable(power, asb_s_reg);

        return err;
    }

    rt_clk_disable_unprepare(pd->clk);

    /* Assert the resets. */
    PM_WRITE(pm_reg, PM_READ(pm_reg) & ~reset_flags);

    return 0;
}

static rt_err_t bcm2835_power_pd_power_on(struct rt_dm_power_domain *domain)
{
    struct bcm2835_power_domain *pd = raw_to_rpi_bcm2835_power_domain(domain);
    struct bcm2835_power *power = pd->power;

    switch (pd->domain)
    {
    case BCM2835_POWER_DOMAIN_GRAFX:
        return bcm2835_power_power_on(pd, PM_GRAFX);

    case BCM2835_POWER_DOMAIN_GRAFX_V3D:
        if (!power->asb)
        {
            return bcm2835_asb_power_on(pd, PM_GRAFX_2712, 0, 0, PM_V3DRSTN);
        }
        return bcm2835_asb_power_on(pd, PM_GRAFX,
                ASB_V3D_M_CTRL, ASB_V3D_S_CTRL, PM_V3DRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE:
        return bcm2835_power_power_on(pd, PM_IMAGE);

    case BCM2835_POWER_DOMAIN_IMAGE_PERI:
        return bcm2835_asb_power_on(pd, PM_IMAGE, 0, 0, PM_PERIRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE_ISP:
        return bcm2835_asb_power_on(pd, PM_IMAGE,
                ASB_ISP_M_CTRL, ASB_ISP_S_CTRL, PM_ISPRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE_H264:
        return bcm2835_asb_power_on(pd, PM_IMAGE,
                ASB_H264_M_CTRL, ASB_H264_S_CTRL, PM_H264RSTN);

    case BCM2835_POWER_DOMAIN_USB:
        PM_WRITE(PM_USB, PM_USB_CTRLEN);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_DSI0:
        PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN);
        PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN | PM_DSI0_LDOHPEN);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_DSI1:
        PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN);
        PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN | PM_DSI1_LDOHPEN);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_CCP2TX:
        PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN);
        PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN | PM_CCP2TX_LDOEN);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_HDMI:
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_RSTDR);
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_CTRLEN);
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_LDOPD);

        rt_hw_us_delay(150);
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_RSTDR);
        return RT_EOK;

    default:
        LOG_E("Invalid domain %d", pd->domain);

        return -RT_EINVAL;
    }
}

static rt_err_t bcm2835_power_pd_power_off(struct rt_dm_power_domain *domain)
{
    struct bcm2835_power_domain *pd = raw_to_rpi_bcm2835_power_domain(domain);
    struct bcm2835_power *power = pd->power;

    switch (pd->domain)
    {
    case BCM2835_POWER_DOMAIN_GRAFX:
        return bcm2835_power_power_off(pd, PM_GRAFX);

    case BCM2835_POWER_DOMAIN_GRAFX_V3D:
        if (!power->asb)
        {
            return bcm2835_asb_power_off(pd, PM_GRAFX_2712, 0, 0, PM_V3DRSTN);
        }
        return bcm2835_asb_power_off(pd, PM_GRAFX,
                ASB_V3D_M_CTRL, ASB_V3D_S_CTRL, PM_V3DRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE:
        return bcm2835_power_power_off(pd, PM_IMAGE);

    case BCM2835_POWER_DOMAIN_IMAGE_PERI:
        return bcm2835_asb_power_off(pd, PM_IMAGE, 0, 0, PM_PERIRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE_ISP:
        return bcm2835_asb_power_off(pd, PM_IMAGE,
                ASB_ISP_M_CTRL, ASB_ISP_S_CTRL, PM_ISPRSTN);

    case BCM2835_POWER_DOMAIN_IMAGE_H264:
        return bcm2835_asb_power_off(pd, PM_IMAGE,
                ASB_H264_M_CTRL, ASB_H264_S_CTRL, PM_H264RSTN);

    case BCM2835_POWER_DOMAIN_USB:
        PM_WRITE(PM_USB, 0);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_DSI0:
        PM_WRITE(PM_DSI0, PM_DSI0_CTRLEN);
        PM_WRITE(PM_DSI0, 0);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_DSI1:
        PM_WRITE(PM_DSI1, PM_DSI1_CTRLEN);
        PM_WRITE(PM_DSI1, 0);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_CCP2TX:
        PM_WRITE(PM_CCP2TX, PM_CCP2TX_CTRLEN);
        PM_WRITE(PM_CCP2TX, 0);
        return RT_EOK;

    case BCM2835_POWER_DOMAIN_HDMI:
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) | PM_HDMI_LDOPD);
        PM_WRITE(PM_HDMI, PM_READ(PM_HDMI) & ~PM_HDMI_CTRLEN);
        return RT_EOK;

    default:
        LOG_E("Invalid domain %d", pd->domain);

        return -RT_EINVAL;
    }
}

static struct rt_dm_power_domain *bcm2835_power_domains_ofw_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    struct bcm2835_power *power = raw_to_bcm2835_power(proxy);

    return &power->domains[args->args[0]].parent;
}

static rt_err_t bcm2835_reset_reset(struct rt_reset_control *rstc)
{
    rt_err_t err;
    struct bcm2835_power_domain *pd;
    struct bcm2835_power *power = rstc->rstcer->priv;

    switch (rstc->id)
    {
    case BCM2835_RESET_V3D:
        pd = &power->domains[BCM2835_POWER_DOMAIN_GRAFX_V3D];
        break;

    case BCM2835_RESET_H264:
        pd = &power->domains[BCM2835_POWER_DOMAIN_IMAGE_H264];
        break;

    case BCM2835_RESET_ISP:
        pd = &power->domains[BCM2835_POWER_DOMAIN_IMAGE_ISP];
        break;

    default:
        LOG_E("Invalid reset id %u", rstc->id);
        return -RT_EINVAL;
    }

    if ((err = bcm2835_power_pd_power_off(&pd->parent)))
    {
        return err;
    }

    return bcm2835_power_pd_power_on(&pd->parent);
}

static int bcm2835_reset_status(struct rt_reset_control *rstc)
{
    struct bcm2835_power *power = rstc->rstcer->priv;

    switch (rstc->id)
    {
    case BCM2835_RESET_V3D:
        return !PM_READ(PM_GRAFX & PM_V3DRSTN);

    case BCM2835_RESET_H264:
        return !PM_READ(PM_IMAGE & PM_H264RSTN);

    case BCM2835_RESET_ISP:
        return !PM_READ(PM_IMAGE & PM_ISPRSTN);

    default:
        return -RT_EINVAL;
    }
}

static const struct rt_reset_control_ops bcm2835_reset_ops =
{
    .reset = bcm2835_reset_reset,
    .status = bcm2835_reset_status,
};

static const char *const power_domain_names[] =
{
    [BCM2835_POWER_DOMAIN_GRAFX] = "grafx",
    [BCM2835_POWER_DOMAIN_GRAFX_V3D] = "v3d",

    [BCM2835_POWER_DOMAIN_IMAGE] = "image",
    [BCM2835_POWER_DOMAIN_IMAGE_PERI] = "peri_image",
    [BCM2835_POWER_DOMAIN_IMAGE_H264] = "h264",
    [BCM2835_POWER_DOMAIN_IMAGE_ISP] = "isp",

    [BCM2835_POWER_DOMAIN_USB] = "usb",
    [BCM2835_POWER_DOMAIN_DSI0] = "dsi0",
    [BCM2835_POWER_DOMAIN_DSI1] = "dsi1",
    [BCM2835_POWER_DOMAIN_CAM0] = "cam0",
    [BCM2835_POWER_DOMAIN_CAM1] = "cam1",
    [BCM2835_POWER_DOMAIN_CCP2TX] = "ccp2tx",
    [BCM2835_POWER_DOMAIN_HDMI] = "hdmi",
};

static rt_err_t bcm2835_init_power_domain(struct bcm2835_power *power,
        struct bcm2835_pm *pm, int id)
{
    const char *name = power_domain_names[id];
    struct bcm2835_power_domain *dom = &power->domains[id];

    dom->clk = rt_ofw_get_clk_by_name(pm->ofw_node, name);

    if (rt_is_err(dom->clk))
    {
        return rt_ptr_err(dom->clk);
    }

    dom->power = power;
    dom->parent.power_on = bcm2835_power_pd_power_on;
    dom->parent.power_off = bcm2835_power_pd_power_off;

    rt_dm_power_domain_register(&dom->parent);

    return RT_EOK;
}

static rt_err_t bcm2835_power_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_reset_controller *rstcer;
    struct bcm2835_pm *pm = pdev->priv;
    struct bcm2835_power *power = rt_calloc(1, sizeof(*power));

    if (!power)
    {
        return -RT_ENOMEM;
    }

    power->base = pm->base;
    power->asb = pm->asb;
    power->rpivid_asb = pm->rpivid_asb;

    if (power->asb)
    {
        rt_uint32_t id = HWREG32(power->asb + ASB_AXI_BRDG_ID);

        /* "BRDG" */
        if (id != BCM2835_BRDG_ID)
        {
            LOG_E("ASB register ID returned 0x%08x", id);

            err = -RT_EINVAL;
            goto _fail;
        }

        if (power->rpivid_asb)
        {
            id = HWREG32(power->rpivid_asb + ASB_AXI_BRDG_ID);
            /* "BRDG" */
            if (id != BCM2835_BRDG_ID)
            {
                LOG_E("RPiVid ASB register ID returned 0x%08x", id);

                err = -RT_EINVAL;
                goto _fail;
            }
        }
    }

    for (int i = 0; i < RT_ARRAY_SIZE(power_domain_names); ++i)
    {
        if ((err = bcm2835_init_power_domain(power, pm, i)))
        {
            goto _free_power_domain;
        }
    }

    power->proxy_parent.ofw_parse = bcm2835_power_domains_ofw_parse;
    rt_dm_power_domain_proxy_ofw_bind(&power->proxy_parent, pm->ofw_node);

    rstcer = &power->rstc_parent;
    rstcer->priv = power;
    rstcer->ofw_node = pm->ofw_node;
    rstcer->ops = &bcm2835_reset_ops;

    rt_reset_controller_register(rstcer);

    return RT_EOK;

_free_power_domain:
    for (int i = 0; i < RT_ARRAY_SIZE(power_domain_names); ++i)
    {
        struct bcm2835_power_domain *dom = &power->domains[i];

        if (!dom->power)
        {
            break;
        }

        rt_dm_power_domain_unregister(&dom->parent);
    }

_fail:
    rt_free(power);

    return err;
}

static struct rt_platform_driver bcm2835_power_driver =
{
    .name = "bcm2835-power",
    .probe = bcm2835_power_probe,
};

static int bcm2835_power_drv_register(void)
{
    rt_platform_driver_register(&bcm2835_power_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2835_power_drv_register);
