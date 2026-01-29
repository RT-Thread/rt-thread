/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>
#include <dt-bindings/power/k1x_pmu.h>

#define DBG_TAG "pm-domain.spacemit.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX_REGULATOR_PER_DOMAIN        5

#define APMU_POWER_STATUS_REG           0xf0
#define MPMU_AWUCRM_REG                 0x104c

struct spacemit_pmu;

struct spacemit_pm_domain_param
{
    rt_uint32_t reg_pwr_ctrl;
    rt_uint32_t pm_qos;
    rt_uint32_t bit_hw_mode;
    rt_uint32_t bit_sleep2;
    rt_uint32_t bit_sleep1;
    rt_uint32_t bit_isolation;
    rt_uint32_t bit_auto_pwr_on;
    rt_uint32_t bit_hw_pwr_stat;
    rt_uint32_t bit_pwr_stat;
    rt_uint32_t use_hw;
};

struct spacemit_pm_domain
{
    struct rt_dm_power_domain parent;

    int index;
    int supply_count;
    int ref_handle_pm_domain;
    struct spacemit_pmu *pmu;
    struct rt_regulator *supply[MAX_REGULATOR_PER_DOMAIN];

    struct spacemit_pm_domain_param param;
};

#define raw_to_spacemit_pm_domain(raw) rt_container_of(raw, struct spacemit_pm_domain, parent)

struct spacemit_pmu
{
    struct rt_dm_power_domain_proxy parent;

    struct rt_syscon *mpmu_regmap;
    struct rt_syscon *apmu_regmap;

    rt_uint32_t num_domains;
    struct spacemit_pm_domain *domains;
};

#define raw_to_spacemit_pmu(raw) rt_container_of(raw, struct spacemit_pmu, parent)

static rt_err_t spacemit_pd_power_on(struct rt_dm_power_domain *domain)
{
    int loop;
    rt_err_t err;
    rt_uint32_t val;
    struct spacemit_pmu *pmu;
    struct spacemit_pm_domain *spd = raw_to_spacemit_pm_domain(domain);

    if (spd->param.reg_pwr_ctrl == 0)
    {
        return RT_EOK;
    }

    if (spd->ref_handle_pm_domain > 0)
    {
        return RT_EOK;
    }

    /* Enable the supply */
    for (int loop = 0; loop < spd->supply_count; ++loop)
    {
        if ((err = rt_regulator_enable(spd->supply[loop])) && spd->supply[loop])
        {
            return err;
        }
    }

    pmu = spd->pmu;

    rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

    if (val & (1 << spd->param.bit_pwr_stat))
    {
        if (spd->index == K1X_PMU_LCD_PWR_DOMAIN)
        {
            return RT_EOK;
        }

        if (!spd->param.use_hw)
        {
            /* This is the sw type */
            rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
            val &= ~(1 << spd->param.bit_isolation);
            rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

            rt_hw_us_delay(12);

            /* MCU power off */
            rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
            val &= ~((1 << spd->param.bit_sleep1) | (1 << spd->param.bit_sleep2));
            rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

            rt_hw_us_delay(12);

            for (loop = 10000; loop >= 0; --loop)
            {
                rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

                if ((val & (1 << spd->param.bit_pwr_stat)) == 0)
                {
                    break;
                }

                rt_hw_us_delay(5);
            }
        }
        else
        {
            /* LCD */
            rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
            val &= ~(1 << spd->param.bit_auto_pwr_on);
            val &= ~(1 << spd->param.bit_hw_mode);
            rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

            rt_hw_us_delay(20);

            for (loop = 10000; loop >= 0; --loop)
            {
                rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

                if ((val & (1 << spd->param.bit_hw_pwr_stat)) == 0)
                {
                    break;
                }

                rt_hw_us_delay(5);
            }
        }

        if (loop < 0)
        {
            LOG_E("Power on Domain(%d) fail", spd->index);
            return -RT_EBUSY;
        }
    }

    if (!spd->param.use_hw)
    {
        /* mcu power on */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val |= (1 << spd->param.bit_sleep1);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(22);

        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val |= (1 << spd->param.bit_sleep2) | (1 << spd->param.bit_sleep1);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(22);

        /* disable isolation */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val |= (1 << spd->param.bit_isolation);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(12);

        for (loop = 10000; loop >= 0; --loop)
        {
            rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

            if (val & (1 << spd->param.bit_pwr_stat))
            {
                break;
            }

            rt_hw_us_delay(5);
        }
    }
    else
    {
        /* LCD */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val |= (1 << spd->param.bit_auto_pwr_on);
        val |= (1 << spd->param.bit_hw_mode);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(300);

        for (loop = 10000; loop >= 0; --loop)
        {
            rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

            if (val & (1 << spd->param.bit_hw_pwr_stat))
            {
                break;
            }

            rt_hw_us_delay(5);
        }
    }

    if (loop < 0)
    {
        LOG_E("Power on Domain(%d) fail", spd->index);
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_err_t spacemit_pd_power_off(struct rt_dm_power_domain *domain)
{
    int loop;
    rt_err_t err;
    rt_uint32_t val;
    struct spacemit_pmu *pmu;
    struct spacemit_pm_domain *spd = raw_to_spacemit_pm_domain(domain);

    if (spd->param.reg_pwr_ctrl == 0)
    {
        return RT_EOK;
    }

    if (spd->ref_handle_pm_domain > 0)
    {
        return RT_EOK;
    }

    pmu = spd->pmu;

    if (!spd->param.use_hw)
    {
        /* this is the sw type */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val &= ~(1 << spd->param.bit_isolation);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(12);

        /* mcu power off */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val &= ~((1 << spd->param.bit_sleep1) | (1 << spd->param.bit_sleep2));
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(12);

        for (loop = 10000; loop >= 0; --loop)
        {
            rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

            if ((val & (1 << spd->param.bit_pwr_stat)) == 0)
            {
                break;
            }

            rt_hw_us_delay(5);
        }
    }
    else
    {
        /* LCD */
        rt_syscon_read(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, &val);
        val &= ~(1 << spd->param.bit_auto_pwr_on);
        val &= ~(1 << spd->param.bit_hw_mode);
        rt_syscon_write(pmu->apmu_regmap, spd->param.reg_pwr_ctrl, val);

        rt_hw_us_delay(20);

        for (loop = 10000; loop >= 0; --loop)
        {
            rt_syscon_read(pmu->apmu_regmap, APMU_POWER_STATUS_REG, &val);

            if ((val & (1 << spd->param.bit_hw_pwr_stat)) == 0)
            {
                break;
            }

            rt_hw_us_delay(5);
        }
    }

    if (loop < 0)
    {
        LOG_E("Powero ff Domain(%d) fail", spd->index);
        return -RT_EBUSY;
    }

    /* enable the supply */
    for (loop = 0; loop < spd->supply_count; ++loop)
    {
        if ((err = rt_regulator_disable(spd->supply[loop])) && spd->supply[loop])
        {
            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t spacemit_pd_attach_dev(struct rt_dm_power_domain *domain,
        struct rt_device *dev)
{
    struct spacemit_pm_domain *spd = raw_to_spacemit_pm_domain(domain);

    if (rt_ofw_prop_read_bool(dev->ofw_node, "pwr-domain,pm-runtime,no-sleep"))
    {
        ++spd->ref_handle_pm_domain;
    }

    return RT_EOK;
}

static rt_err_t spacemit_pd_detach_dev(struct rt_dm_power_domain *domain,
        struct rt_device *dev)
{
    struct spacemit_pm_domain *spd = raw_to_spacemit_pm_domain(domain);

    if (rt_ofw_prop_read_bool(dev->ofw_node, "pwr-domain,pm-runtime,no-sleep"))
    {
        --spd->ref_handle_pm_domain;
    }

    return RT_EOK;
}

static struct rt_dm_power_domain *spacemit_pmdomain_proxy_ofw_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    struct spacemit_pmu *pmu = raw_to_spacemit_pmu(proxy);

    return &pmu->domains[args->args[0]].parent;
}

static rt_err_t spacemit_pm_add_one_domain(struct spacemit_pmu *pmu,
        struct rt_ofw_node *np)
{
    rt_err_t err;
    rt_uint32_t idx;
    struct rt_device dev;
    struct spacemit_pm_domain *spd;
    struct rt_dm_power_domain *domain;
    const char *strings[MAX_REGULATOR_PER_DOMAIN];

    if ((err = rt_ofw_prop_read_u32(np, "reg", &idx)))
    {
        LOG_E("Failed to read %s domain id (reg) error = %s",
                rt_ofw_node_full_name(np), rt_strerror(err));
        return err;
    }

    spd = &pmu->domains[idx];
    spd->index = idx;

    if ((err = rt_ofw_prop_read_u32(np, "pm_qos", &spd->param.pm_qos)))
    {
        return -RT_EINVAL;
    }

    rt_ofw_prop_read_u32(np, "reg_pwr_ctrl", &spd->param.reg_pwr_ctrl);
    rt_ofw_prop_read_u32(np, "bit_hw_mode", &spd->param.bit_hw_mode);
    rt_ofw_prop_read_u32(np, "bit_sleep2", &spd->param.bit_sleep2);
    rt_ofw_prop_read_u32(np, "bit_sleep1", &spd->param.bit_sleep1);
    rt_ofw_prop_read_u32(np, "bit_isolation", &spd->param.bit_isolation);
    rt_ofw_prop_read_u32(np, "bit_auto_pwr_on", &spd->param.bit_auto_pwr_on);
    rt_ofw_prop_read_u32(np, "bit_hw_pwr_stat", &spd->param.bit_hw_pwr_stat);
    rt_ofw_prop_read_u32(np, "bit_pwr_stat", &spd->param.bit_pwr_stat);
    rt_ofw_prop_read_u32(np, "use_hw", &spd->param.use_hw);

    spd->supply_count = rt_ofw_prop_read_string_array_index(np, "vin-supply-names",
            0, RT_ARRAY_SIZE(strings), strings);

    if (spd->supply_count > 0)
    {
        dev.ofw_node = np;

        for (int i = 0; i < spd->supply_count; ++i)
        {
            spd->supply[i] = rt_regulator_get(&dev, strings[i]);

            if (rt_is_err(spd->supply[i]))
            {
                LOG_E("Regulator supply %s get failed", strings[i]);
                return rt_ptr_err(spd->supply[i]);
            }
        }
    }
    else
    {
        spd->supply_count = 0;
    }

    spd->pmu = pmu;

    domain = &spd->parent;
    domain->power_on = spacemit_pd_power_on;
    domain->power_off = spacemit_pd_power_off;
    domain->attach_dev = spacemit_pd_attach_dev;
    domain->detach_dev = spacemit_pd_detach_dev;

    if ((err = rt_dm_power_domain_register(domain)))
    {
        return err;
    }

    rt_ofw_data(np) = domain;

    return RT_EOK;
}

static rt_err_t spacemit_pm_add_subdomain(struct spacemit_pmu *pmu,
        struct rt_ofw_node *parent)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t idx;
    struct rt_ofw_node *np;
    struct spacemit_pm_domain *child_spd, *parent_spd;

    rt_ofw_foreach_child_node(parent, np)
    {
        if ((err = rt_ofw_prop_read_u32(np, "reg", &idx)))
        {
            LOG_E("Failed to read %s domain id (reg) error = %s",
                    rt_ofw_node_full_name(parent), rt_strerror(err));
            goto _err;
        }

        parent_spd = &pmu->domains[idx];

        if ((err = spacemit_pm_add_one_domain(pmu, np)))
        {
            LOG_E("Failed to handle node %s error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
            goto _err;
        }

        if ((err = rt_ofw_prop_read_u32(np, "reg", &idx)))
        {
            LOG_E("Failed to read %s domain id (reg) error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
            goto _err;
        }

        child_spd = &pmu->domains[idx];

        if ((err = rt_dm_power_domain_register_child(&parent_spd->parent,
                &child_spd->parent)))
        {
            LOG_E("Failed to handle subdomain node %s error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
        }

        spacemit_pm_add_subdomain(pmu, np);
    }

_err:
    rt_ofw_node_put(np);

    return err;
}

static rt_err_t spacemit_pmdomain_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *child;
    struct spacemit_pmu *pmu = rt_calloc(1, sizeof(*pmu));

    if (!pmu)
    {
        return -RT_ENOMEM;
    }

    pmu->mpmu_regmap = rt_syscon_find_by_ofw_compatible("spacemit,spacemit-mpmu");
    pmu->apmu_regmap = rt_syscon_find_by_ofw_compatible("spacemit,spacemit-apmu");

    if (!pmu->mpmu_regmap || !pmu->apmu_regmap)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "domains", &pmu->num_domains))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(pmu->domains = rt_calloc(pmu->num_domains, sizeof(*pmu->domains))))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rt_ofw_foreach_available_child_node(np, child)
    {
        if ((err = spacemit_pm_add_one_domain(pmu, child)))
        {
            LOG_E("Failed to handle node %s error = %s",
                    rt_ofw_node_full_name(child), rt_strerror(err));

            rt_ofw_node_put(child);
            goto _fail;
        }

        if ((err = spacemit_pm_add_subdomain(pmu, child)))
        {
            LOG_E("Failed to handle subdomain node %s error = %s",
                    rt_ofw_node_full_name(child), rt_strerror(err));

            rt_ofw_node_put(child);
            goto _fail;
        }
    }

    pmu->parent.ofw_parse = spacemit_pmdomain_proxy_ofw_parse;
    rt_dm_power_domain_proxy_ofw_bind(&pmu->parent, np);

    return RT_EOK;

_fail:
    if (pmu->domains)
    {
        for (int i = 0; i < pmu->num_domains; ++i)
        {
            struct spacemit_pm_domain *domain = &pmu->domains[i];

            if (domain)
            {
                rt_dm_power_domain_unregister(&domain->parent);
            }
        }

        rt_free(pmu->domains);
    }
    rt_free(pmu);

    return err;
}

static const struct rt_ofw_node_id spacemit_pmdomain_ofw_ids[] =
{
    { .compatible = "spacemit,power-controller", },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmdomain_driver =
{
    .name = "spacemit-pmdomain",
    .ids = spacemit_pmdomain_ofw_ids,

    .probe = spacemit_pmdomain_probe,
};

static int spacemit_pmdomain_drv_register(void)
{
    rt_platform_driver_register(&spacemit_pmdomain_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_pmdomain_drv_register);
