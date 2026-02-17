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

#define DBG_TAG "soc.rockchip.io-domain"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX_SUPPLIES    16

/*
 * The max voltage for 1.8V and 3.3V come from the Rockchip datasheet under
 * "Recommended Operating Conditions" for "Digital GPIO".   When the typical
 * is 3.3V the max is 3.6V.  When the typical is 1.8V the max is 1.98V.
 *
 * They are used like this:
 * - If the voltage on a rail is above the "1.8" voltage (1.98V) we'll tell the
 *   SoC we're at 3.3.
 * - If the voltage on a rail is above the "3.3" voltage (3.6V) we'll consider
 *   that to be an error.
 */
#define MAX_VOLTAGE_1_8 1980000
#define MAX_VOLTAGE_3_3 3600000

struct rockchip_iodomain;

struct rockchip_iodomain_supply
{
    struct rockchip_iodomain *domain;
    struct rt_regulator *reg;
    struct rt_regulator_notifier notifier;
    int idx;
};

struct rockchip_iodomain_soc_data
{
    int grf_offset;
    const char *supply_names[MAX_SUPPLIES];
    void (*init)(struct rockchip_iodomain *domain);
    rt_err_t (*write)(struct rockchip_iodomain_supply *supply, int uvolt);
};

struct rockchip_iodomain
{
    struct rt_device *dev;
    struct rt_syscon *grf;
    const struct rockchip_iodomain_soc_data *soc_data;
    struct rockchip_iodomain_supply supplies[MAX_SUPPLIES];

    rt_err_t (*write)(struct rockchip_iodomain_supply *supply, int uvolt);
};

#define PX30_IO_VSEL                    0x180
#define PX30_IO_VSEL_VCCIO6_SRC         RT_BIT(0)
#define PX30_IO_VSEL_VCCIO6_SUPPLY_NUM  1

static void px30_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no VCCIO6 supply we should leave things alone */
    if (!domain->supplies[PX30_IO_VSEL_VCCIO6_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set vccio6 iodomain to also use this framework instead of a special gpio. */
    val = PX30_IO_VSEL_VCCIO6_SRC | (PX30_IO_VSEL_VCCIO6_SRC << 16);

    if (rt_syscon_write(domain->grf, PX30_IO_VSEL, val) < 0)
    {
        LOG_W("Couldn't update %s ctrl", "vccio6");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_px30 =
{
    .grf_offset = 0x180,
    .supply_names =
    {
        [1] =
        "vccio6",
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
        "vccio5",
        "vccio-oscgpi",
    },
    .init = px30_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_px30_pmu =
{
    .grf_offset = 0x100,
    .supply_names =
    {
        [14] =
        "pmuio1",
        "pmuio2",
    },
};

/*
 * On the rk3188 the io-domains are handled by a shared register with the lower
 * 8 bits being still being continuing drive-strength settings.
 */
static const struct rockchip_iodomain_soc_data soc_data_rk3188 =
{
    .grf_offset = 0x104,
    .supply_names =
    {
        [8] =
        "ap0",
        "ap1",
        "cif",
        "flash",
        "vccio0",
        "vccio1",
        "lcdc0",
        "lcdc1",
    },
};

static const struct rockchip_iodomain_soc_data soc_data_rk3228 =
{
    .grf_offset = 0x418,
    .supply_names =
    {
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
    },
};

#define RK3288_SOC_CON2             0x24c
#define RK3288_SOC_CON2_FLASH0      RT_BIT(7)
#define RK3288_SOC_FLASH_SUPPLY_NUM 2

static void rk3288_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no flash supply we should leave things alone */
    if (!domain->supplies[RK3288_SOC_FLASH_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set flash0 iodomain to also use this framework instead of a special gpio. */
    val = RK3288_SOC_CON2_FLASH0 | (RK3288_SOC_CON2_FLASH0 << 16);

    if (rt_syscon_write(domain->grf, RK3288_SOC_CON2, val) < 0)
    {
        LOG_W("Couldn't update %s ctrl", "flash0");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_rk3288 =
{
    .grf_offset = 0x380,
    .supply_names =
    {
        "lcdc",     /* LCDC_VDD */
        "dvp",      /* DVPIO_VDD */
        "flash0",   /* FLASH0_VDD (emmc) */
        "flash1",   /* FLASH1_VDD (sdio1) */
        "wifi",     /* APIO3_VDD  (sdio0) */
        "bb",       /* APIO5_VDD */
        "audio",    /* APIO4_VDD */
        "sdcard",   /* SDMMC0_VDD (sdmmc) */
        "gpio30",   /* APIO1_VDD */
        "gpio1830", /* APIO2_VDD */
    },
    .init = rk3288_iodomain_init,
};

#define RK3308_SOC_CON0                 0x300
#define RK3308_SOC_CON0_VCCIO3          RT_BIT(8)
#define RK3308_SOC_VCCIO3_SUPPLY_NUM    3

static void rk3308_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no vccio3 supply we should leave things alone */
    if (!domain->supplies[RK3308_SOC_VCCIO3_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set vccio3 iodomain to also use this framework instead of a special gpio. */
    val = RK3308_SOC_CON0_VCCIO3 | (RK3308_SOC_CON0_VCCIO3 << 16);

    if (rt_syscon_write(domain->grf, RK3308_SOC_CON0, val) < 0)
    {
        LOG_W("Couldn't update %s ctrl", "vccio3");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_rk3308 =
{
    .grf_offset = 0x300,
    .supply_names =
    {
        "vccio0",
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
        "vccio5",
    },
    .init = rk3308_iodomain_init,
};

#define RK3328_SOC_CON4                 0x410
#define RK3328_SOC_CON4_VCCIO2          RT_BIT(7)
#define RK3328_SOC_VCCIO2_SUPPLY_NUM    1

static void rk3328_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no vccio2 supply we should leave things alone */
    if (!domain->supplies[RK3328_SOC_VCCIO2_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set vccio2 iodomain to also use this framework instead of a special gpio. */
    val = RK3328_SOC_CON4_VCCIO2 | (RK3328_SOC_CON4_VCCIO2 << 16);

    if (rt_syscon_write(domain->grf, RK3328_SOC_CON4, val) < 0)
    {
        LOG_W("Couldn't update %s ctrl", "vccio2 vsel");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_rk3328 =
{
    .grf_offset = 0x410,
    .supply_names =
    {
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
        "vccio5",
        "vccio6",
        "pmuio",
    },
    .init = rk3328_iodomain_init,
};

#define RK3368_SOC_CON15            0x43c
#define RK3368_SOC_CON15_FLASH0     RT_BIT(14)
#define RK3368_SOC_FLASH_SUPPLY_NUM 2

static void rk3368_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no flash supply we should leave things alone */
    if (!domain->supplies[RK3368_SOC_FLASH_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set flash0 iodomain to also use this framework instead of a special gpio. */
    val = RK3368_SOC_CON15_FLASH0 | (RK3368_SOC_CON15_FLASH0 << 16);

    if (rt_syscon_write(domain->grf, RK3368_SOC_CON15, val) < 0)
    {
        LOG_W("Couldn't update %s ctrl", "flash0");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_rk3368 =
{
    .grf_offset = 0x900,
    .supply_names =
    {
        RT_NULL,    /* Reserved */
        "dvp",      /* DVPIO_VDD */
        "flash0",   /* FLASH0_VDD (emmc) */
        "wifi",     /* APIO2_VDD (sdio0) */
        RT_NULL,
        "audio",    /* APIO3_VDD */
        "sdcard",   /* SDMMC0_VDD (sdmmc) */
        "gpio30",   /* APIO1_VDD */
        "gpio1830", /* APIO4_VDD (gpujtag) */
    },
    .init = rk3368_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3368_pmu =
{
    .grf_offset = 0x100,
    .supply_names =
    {
        [4] =
        "pmu",      /* PMU IO domain*/
        "vop",      /* LCDC IO domain*/
    },
};

static const struct rockchip_iodomain_soc_data soc_data_rk3399 =
{
    .grf_offset = 0xe640,
    .supply_names =
    {
        "bt656",    /* APIO2_VDD */
        "audio",    /* APIO5_VDD */
        "sdmmc",    /* SDMMC0_VDD */
        "gpio1830", /* APIO4_VDD */
    },
};

#define RK3399_PMUGRF_CON0              0x180
#define RK3399_PMUGRF_CON0_VSEL         RT_BIT(8)
#define RK3399_PMUGRF_VSEL_SUPPLY_NUM   9

static void rk3399_pmu_iodomain_init(struct rockchip_iodomain *domain)
{
    rt_uint32_t val;

    /* if no pmu io supply we should leave things alone */
    if (!domain->supplies[RK3399_PMUGRF_VSEL_SUPPLY_NUM].reg)
    {
        return;
    }

    /* set pmu io iodomain to also use this framework instead of a special gpio. */
    val = RK3399_PMUGRF_CON0_VSEL | (RK3399_PMUGRF_CON0_VSEL << 16);

    if (rt_syscon_write(domain->grf, RK3399_PMUGRF_CON0, val) < 0)
    {
        LOG_W("couldn't update %s ctrl", "pmu io iodomain");
    }
}

static const struct rockchip_iodomain_soc_data soc_data_rk3399_pmu =
{
    .grf_offset = 0x180,
    .supply_names =
    {
        [9] =
        "pmu1830",  /* PMUIO2_VDD */
    },
    .init = rk3399_pmu_iodomain_init,
};

#define RK3568_PMU_GRF_IO_VSEL0 0x0140
#define RK3568_PMU_GRF_IO_VSEL1 0x0144
#define RK3568_PMU_GRF_IO_VSEL2 0x0148

static rt_err_t rk3568_iodomain_write(struct rockchip_iodomain_supply *supply, int uvolt)
{
    rt_uint32_t bit, is_3v3 = uvolt > MAX_VOLTAGE_1_8, val0, val1;
    struct rockchip_iodomain *domain = supply->domain;

    switch (supply->idx)
    {
    case 0: /* pmuio1 */
        break;

    case 1: /* pmuio2 */
        bit = supply->idx;
        val0 = RT_BIT(16 + bit) | (is_3v3 ? 0 : RT_BIT(bit));
        bit = supply->idx + 4;
        val1 = RT_BIT(16 + bit) | (is_3v3 ? RT_BIT(bit) : 0);

        rt_syscon_write(domain->grf, RK3568_PMU_GRF_IO_VSEL2, val0);
        rt_syscon_write(domain->grf, RK3568_PMU_GRF_IO_VSEL2, val1);
        break;

    case 3: /* vccio2 */
        break;

    case 2: /* vccio1 */
    case 4: /* vccio3 */
    case 5: /* vccio4 */
    case 6: /* vccio5 */
    case 7: /* vccio6 */
    case 8: /* vccio7 */
        bit = supply->idx - 1;
        val0 = RT_BIT(16 + bit) | (is_3v3 ? 0 : RT_BIT(bit));
        val1 = RT_BIT(16 + bit) | (is_3v3 ? RT_BIT(bit) : 0);

        rt_syscon_write(domain->grf, RK3568_PMU_GRF_IO_VSEL0, val0);
        rt_syscon_write(domain->grf, RK3568_PMU_GRF_IO_VSEL1, val1);
        break;

    default:
        return -RT_EINVAL;
    }

    return 0;
}

static const struct rockchip_iodomain_soc_data soc_data_rk3568_pmu =
{
    .grf_offset = 0x140,
    .supply_names =
    {
        "pmuio1",
        "pmuio2",
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
        "vccio5",
        "vccio6",
        "vccio7",
    },
    .write = rk3568_iodomain_write,
};

static const struct rockchip_iodomain_soc_data soc_data_rv1108 =
{
    .grf_offset = 0x404,
    .supply_names =
    {
        [11] =
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio5",
        "vccio6",
    },
};

static const struct rockchip_iodomain_soc_data soc_data_rv1108_pmu =
{
    .grf_offset = 0x104,
    .supply_names =
    {
        "pmu",
    },
};

static const struct rockchip_iodomain_soc_data soc_data_rv1126_pmu =
{
    .grf_offset = 0x140,
    .supply_names =
    {
        [1] =
        "vccio1",
        "vccio2",
        "vccio3",
        "vccio4",
        "vccio5",
        "vccio6",
        "vccio7",
        "pmuio0",
        "pmuio1",
    },
};

static rt_err_t rockchip_iodomain_write(struct rockchip_iodomain_supply *supply, int uvolt)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rockchip_iodomain *domain = supply->domain;

    /* set value bit */
    val = (uvolt > MAX_VOLTAGE_1_8) ? 0 : 1;
    val <<= supply->idx;
    /* apply hiword-mask */
    val |= (RT_BIT(supply->idx) << 16);

    if ((err = rt_syscon_write(domain->grf, domain->soc_data->grf_offset, val)))
    {
        LOG_E("Couldn't write to GRF");
    }

    return err;
}

static rt_err_t rockchip_iodomain_notify(struct rt_regulator_notifier *notifier,
        rt_ubase_t msg, void *data)
{
    int uvolt = 0;
    rt_err_t err;
    struct rockchip_iodomain_supply *supply;

    supply = rt_container_of(notifier, struct rockchip_iodomain_supply, notifier);

    if (msg == RT_REGULATOR_MSG_VOLTAGE_CHANGE)
    {
        union rt_regulator_notifier_args *args = data;

        uvolt = rt_max(args->old_uvolt, args->max_uvolt);
    }
    else if (msg == RT_REGULATOR_MSG_VOLTAGE_CHANGE_ERR)
    {
        uvolt = (int)(rt_base_t)data;
    }

    if (uvolt > MAX_VOLTAGE_3_3)
    {
        LOG_E("Voltage too high: %d", uvolt);

        if (msg == RT_REGULATOR_MSG_VOLTAGE_CHANGE)
        {
            return -RT_EIO;
        }
    }

    err = supply->domain->write(supply, uvolt);

    if (err && msg == RT_REGULATOR_MSG_VOLTAGE_CHANGE)
    {
        return -RT_EIO;
    }

    LOG_D("Setting to %d done", uvolt);

    return err;
}

static rt_err_t rockchip_iodomain_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *np, *grf_np;
    struct rockchip_iodomain *domain = rt_calloc(1, sizeof(*domain));

    if (!domain)
    {
        return -RT_ENOMEM;
    }

    domain->dev = &pdev->parent;
    domain->soc_data = pdev->id->data;
    domain->write = domain->soc_data->write ? : rockchip_iodomain_write;

    np = pdev->parent.ofw_node;

    if ((grf_np = rt_ofw_get_parent(np)))
    {
        domain->grf = rt_syscon_find_by_ofw_node(grf_np);
        rt_ofw_node_put(grf_np);
    }
    else
    {
        domain->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");
    }

    if (!domain->grf)
    {
        err = -RT_EIO;

        goto _fail;
    }

    for (int i = 0; i < MAX_SUPPLIES; ++i)
    {
        int uvolt;
        struct rt_regulator *reg;
        struct rockchip_iodomain_supply *supply;
        const char *supply_name = domain->soc_data->supply_names[i];

        if (!supply_name)
        {
            continue;
        }

        supply = &domain->supplies[i];
        reg = rt_regulator_get(domain->dev, supply_name);

        if (rt_is_err(reg))
        {
            err = rt_ptr_err(reg);
            goto _fail;
        }

        if (!reg)
        {
            continue;
        }

        uvolt = rt_regulator_get_voltage(reg);

        if (uvolt < 0)
        {
            /* Maybe is a switch */
            if (uvolt == -RT_ENOSYS)
            {
                rt_regulator_put(reg);
                continue;
            }

            LOG_E("Can't determine voltage: %s", supply_name);

            err = uvolt;
            goto _fail;
        }

        if (uvolt > MAX_VOLTAGE_3_3)
        {
            LOG_E("Voltage too high: %d", uvolt);

            err = -RT_EIO;
            goto _fail;
        }

        supply->idx = i;
        supply->domain = domain;
        supply->reg = reg;
        supply->notifier.callback = rockchip_iodomain_notify;

        if (domain->write(supply, uvolt))
        {
            rt_regulator_put(supply->reg);
            supply->reg = RT_NULL;

            goto _fail;
        }

        if ((err = rt_regulator_notifier_register(supply->reg, &supply->notifier)))
        {
            rt_regulator_put(supply->reg);
            supply->reg = RT_NULL;

            goto _fail;
        }
    }

    if (domain->soc_data->init)
    {
        domain->soc_data->init(domain);
    }

    return RT_EOK;

_fail:
    for (int i = MAX_SUPPLIES - 1; i >= 0; --i)
    {
        struct rockchip_iodomain_supply *supply = &domain->supplies[i];

        if (!rt_is_err_or_null(supply->reg))
        {
            rt_regulator_notifier_unregister(supply->reg, &supply->notifier);
            rt_regulator_put(supply->reg);
        }
    }

    rt_free(domain);

    return err;
}

static const struct rt_ofw_node_id rockchip_iodomain_ofw_ids[] =
{
    { .compatible = "rockchip,px30-io-voltage-domain", .data = &soc_data_px30 },
    { .compatible = "rockchip,px30-pmu-io-voltage-domain", .data = &soc_data_px30_pmu },
    { .compatible = "rockchip,rk3188-io-voltage-domain", .data = &soc_data_rk3188 },
    { .compatible = "rockchip,rk3228-io-voltage-domain", .data = &soc_data_rk3228 },
    { .compatible = "rockchip,rk3288-io-voltage-domain", .data = &soc_data_rk3288 },
    { .compatible = "rockchip,rk3308-io-voltage-domain", .data = &soc_data_rk3308 },
    { .compatible = "rockchip,rk3328-io-voltage-domain", .data = &soc_data_rk3328 },
    { .compatible = "rockchip,rk3368-io-voltage-domain", .data = &soc_data_rk3368 },
    { .compatible = "rockchip,rk3368-pmu-io-voltage-domain", .data = &soc_data_rk3368_pmu },
    { .compatible = "rockchip,rk3399-io-voltage-domain", .data = &soc_data_rk3399 },
    { .compatible = "rockchip,rk3399-pmu-io-voltage-domain", .data = &soc_data_rk3399_pmu },
    { .compatible = "rockchip,rk3568-pmu-io-voltage-domain", .data = &soc_data_rk3568_pmu },
    { .compatible = "rockchip,rv1108-io-voltage-domain", .data = &soc_data_rv1108 },
    { .compatible = "rockchip,rv1108-pmu-io-voltage-domain", .data = &soc_data_rv1108_pmu },
    { .compatible = "rockchip,rv1126-pmu-io-voltage-domain", .data = &soc_data_rv1126_pmu },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_iodomain_driver =
{
    .name = "rockchip-iodomain",
    .ids = rockchip_iodomain_ofw_ids,

    .probe = rockchip_iodomain_probe,
};

static int rockchip_iodomain_register(void)
{
    rt_platform_driver_register(&rockchip_iodomain_driver);

    return 0;
}
INIT_PREV_EXPORT(rockchip_iodomain_register);
