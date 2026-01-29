/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "regulator.spacemit-pmic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "regulator_dm.h"

#define __SPACEMIT_REGULATOR_INTERNAL
static const struct rt_regulator_ops pmic_dcdc_ldo_ops, pmic_switch_ops;

#include <mfd/spacemit-pmic.h>

struct spacemit_pmic_regulator
{
    struct rt_regulator_node parent;
    struct rt_regulator_param param;

    struct rt_device device;
    struct spacemit_pmic *pmic;
    struct rt_ofw_node *ofw_node;

    const struct spacemit_pmic_regulator_desc *desc;
};

#define raw_to_spacemit_pmic_regulator(raw) rt_container_of(raw, struct spacemit_pmic_regulator, parent)

static int regulator_voltage_from_selector(struct spacemit_pmic_regulator *pmic_reg,
        int selector)
{
    int uvolt = -1;
    const struct spacemit_pmic_regulator_desc *desc = pmic_reg->desc;

    if (desc->ranges_nr)
    {
        const struct spacemit_pmic_regulator_range *range = &desc->ranges[0];

        for (int i = desc->ranges_nr - 1; i >= 0; --i, ++range)
        {
            if (range->min_sel <= selector && range->max_sel >= selector)
            {
                if (range->min_sel > selector || range->max_sel < selector)
                {
                    return -RT_EINVAL;
                }

                uvolt = range->min + (selector - range->min_sel) * range->step;

                break;
            }
        }
    }
    else if (desc->voltages_nr)
    {
        if (selector >= desc->voltages_nr)
        {
            return -RT_EINVAL;
        }

        return desc->uvolt_min + (desc->uvolt_step * selector);
    }
    else
    {
        LOG_E("Regulator %s-%s voltages info not found", desc->name, desc->supply_name);
    }

    return uvolt;
}

static int regulator_voltage_to_selector_range(struct spacemit_pmic_regulator *pmic_reg,
        int min_uvolt, int max_uvolt)
{
    int selector = 0, max, uvolt, i;
    const struct spacemit_pmic_regulator_range *range;
    const struct spacemit_pmic_regulator_desc *desc = pmic_reg->desc;

    if (!desc->ranges)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < desc->ranges_nr; ++i)
    {
        range = &desc->ranges[i];
        max = range->min + (range->max_sel - range->min_sel) * range->step;

        if (max < min_uvolt)
        {
            continue;
        }

        if (range->min > min_uvolt)
        {
            selector = range->min_sel;
        }
        else if (range->step == 0)
        {
            selector = range->max_sel;
        }
        else
        {
            selector = RT_DIV_ROUND_UP(min_uvolt - range->min, range->step)
                + range->min_sel;
        }

        uvolt = regulator_voltage_from_selector(pmic_reg, selector);

        if (uvolt >= min_uvolt && uvolt <= max_uvolt)
        {
            break;
        }
    }

    if (i == desc->ranges_nr)
    {
        return -RT_EINVAL;
    }

    return selector;
}

static int regulator_voltage_to_selector(struct spacemit_pmic_regulator *pmic_reg,
        int min_uvolt, int max_uvolt)
{
    int selector, uvolt;

    /* Allow uvolt_step to be 0 for fixed voltage */
    if (pmic_reg->desc->voltages_nr == 1 && pmic_reg->desc->uvolt_step == 0)
    {
        if (min_uvolt <= pmic_reg->desc->uvolt_min && pmic_reg->desc->uvolt_min <= max_uvolt)
        {
            return 0;
        }
        else
        {
            return -RT_EINVAL;
        }
    }

    if (!pmic_reg->desc->uvolt_step)
    {
        return -RT_EINVAL;
    }

    if (min_uvolt < pmic_reg->desc->uvolt_min)
    {
        min_uvolt = pmic_reg->desc->uvolt_min;
    }

    selector = RT_DIV_ROUND_UP(min_uvolt - pmic_reg->desc->uvolt_min, pmic_reg->desc->uvolt_step);

    if (selector < 0)
    {
        return selector;
    }

    /* Map back into a voltage to verify we're still in bounds */
    uvolt = regulator_voltage_from_selector(pmic_reg, selector);

    if (uvolt < min_uvolt || uvolt > max_uvolt)
    {
        return -RT_EINVAL;
    }

    return selector;
}

static rt_err_t spacemit_pmic_regulator_enable(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct spacemit_pmic_regulator *pmic_reg = raw_to_spacemit_pmic_regulator(reg_np);

    val = pmic_reg->desc->enable_val;

    if (!val)
    {
        val = pmic_reg->desc->enable_mask;
    }

    return spacemit_pmic_update_bits(pmic_reg->pmic, pmic_reg->desc->enable_reg,
            pmic_reg->desc->enable_mask, val);
}

static rt_err_t spacemit_pmic_regulator_disable(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct spacemit_pmic_regulator *pmic_reg = raw_to_spacemit_pmic_regulator(reg_np);

    val = pmic_reg->desc->disable_val;

    return spacemit_pmic_update_bits(pmic_reg->pmic, pmic_reg->desc->enable_reg,
            pmic_reg->desc->enable_mask, val);
}

static rt_bool_t spacemit_pmic_regulator_is_enabled(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct spacemit_pmic_regulator *pmic_reg = raw_to_spacemit_pmic_regulator(reg_np);

    val = spacemit_pmic_read(pmic_reg->pmic, pmic_reg->desc->enable_reg);

    if ((rt_err_t)val < 0)
    {
        return RT_FALSE;
    }

    val &= pmic_reg->desc->enable_mask;

    if (pmic_reg->desc->enable_val)
    {
        return val == pmic_reg->desc->enable_val;
    }

    return val != 0;
}

static rt_err_t spacemit_pmic_regulator_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    int selector;
    struct spacemit_pmic_regulator *pmic_reg = raw_to_spacemit_pmic_regulator(reg_np);

    selector = regulator_voltage_to_selector(pmic_reg, min_uvolt, max_uvolt);

    if (selector < 0)
    {
        if (selector == -RT_EINVAL)
        {
            selector = regulator_voltage_to_selector_range(pmic_reg,
                    min_uvolt, max_uvolt);

            if (selector < 0)
            {
                return -RT_EINVAL;
            }
        }
    }

    selector <<= __rt_ffs(pmic_reg->desc->vsel_mask) - 1;

    return spacemit_pmic_update_bits(pmic_reg->pmic, pmic_reg->desc->vsel_reg,
            pmic_reg->desc->vsel_mask, selector);
}

static int spacemit_pmic_regulator_get_voltage(struct rt_regulator_node *reg_np)
{
    int uvolt;
    rt_uint32_t val;
    struct spacemit_pmic_regulator *pmic_reg = raw_to_spacemit_pmic_regulator(reg_np);

    val = spacemit_pmic_read(pmic_reg->pmic, pmic_reg->desc->vsel_reg);

    if ((rt_err_t)val < 0)
    {
        return val;
    }

    val &= pmic_reg->desc->vsel_mask;
    val >>= __rt_ffs(pmic_reg->desc->vsel_mask) - 1;

    uvolt = regulator_voltage_from_selector(pmic_reg, val);

    return uvolt < 0 ? -RT_EINVAL : uvolt;
}

static const struct rt_regulator_ops pmic_dcdc_ldo_ops =
{
    .enable = spacemit_pmic_regulator_enable,
    .disable = spacemit_pmic_regulator_disable,
    .is_enabled = spacemit_pmic_regulator_is_enabled,
    .set_voltage = spacemit_pmic_regulator_set_voltage,
    .get_voltage = spacemit_pmic_regulator_get_voltage,
};

static const struct rt_regulator_ops pmic_switch_ops =
{
    .enable = spacemit_pmic_regulator_enable,
    .disable = spacemit_pmic_regulator_disable,
    .is_enabled = spacemit_pmic_regulator_is_enabled,
};

static rt_err_t append_spacemit_pmic_regulator(struct spacemit_pmic *pmic,
        struct rt_ofw_node *np, const struct spacemit_pmic_regulator_desc *desc, int id)
{
    rt_err_t err = RT_EOK;
    struct rt_regulator_node *rgp;
    struct spacemit_pmic_regulator *pmic_reg;

    pmic_reg = rt_calloc(1, sizeof(*pmic_reg));

    if (!pmic_reg)
    {
        return -RT_ENOMEM;
    }

    pmic_reg->pmic = pmic;
    pmic_reg->desc = &desc[id];

    regulator_ofw_parse(np, &pmic_reg->param);

    rgp = &pmic_reg->parent;
    rgp->supply_name = pmic_reg->param.name;
    rgp->ops = pmic_reg->desc->ops;
    rgp->param = &pmic_reg->param;
    rgp->dev = &pmic_reg->device;

    rgp->dev->ofw_node = np;

    if ((err = rt_regulator_register(rgp)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(pmic_reg);

    return err;
}

static rt_err_t spacemit_pmic_regulator_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_ofw_node *np, *regulators_np = pdev->parent.ofw_node;
    struct spacemit_pmic *pmic = pdev->priv, *pmic_sub;
    const struct spacemit_pmic_regulator_data *data = pdev->id->data;
    struct spacemit_pmic_regulator *pmic_reg = rt_calloc(1, sizeof(*pmic_reg));

    if (!pmic_reg)
    {
        return -RT_ENOMEM;
    }

    if (rt_ofw_node_is_compatible(regulators_np, "pmic,regulator,pm853"))
    {
        if (!(pmic_sub = rt_calloc(1, sizeof(*pmic_sub))))
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        rt_memcpy(pmic_sub, pmic, sizeof(*pmic));
        pmic_sub->addr_offset = 1;

        pmic_reg->pmic = pmic_sub;
    }
    else
    {
        pmic_reg->pmic = pmic;
    }

    for (int i = 0; i < data->desc_nr; ++i)
    {
        const char *name = data->desc[i].name;

        if (!(np = rt_ofw_get_child_by_tag(regulators_np, name)))
        {
            continue;
        }

        rt_ofw_node_put(np);

        if ((err = append_spacemit_pmic_regulator(pmic, np, data->desc, i)))
        {
            LOG_E("Append spacemit PMIC regulator %s fail error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));

            if (err == -RT_ENOMEM)
            {
                return err;
            }
        }
    }

    return RT_EOK;
_fail:
    rt_free(pmic_reg);

    return err;
}

static const struct rt_ofw_node_id spacemit_pmic_regulator_ofw_ids[] =
{
    { .compatible = "pmic,regulator,spm8821", .data = &spm8821_regulator_data },
    { .compatible = "pmic,regulator,pm853", .data = &pm853_regulator_data },
    { .compatible = "pmic,regulator,sy8810l", .data = &sy8810l_regulator_data },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_pmic_regulator_driver =
{
    .name = "spacemit-pmic-regulator",
    .ids = spacemit_pmic_regulator_ofw_ids,

    .probe = spacemit_pmic_regulator_probe,
};

static int spacemit_pmic_regulator_register(void)
{
    rt_platform_driver_register(&spacemit_pmic_regulator_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_pmic_regulator_register);
