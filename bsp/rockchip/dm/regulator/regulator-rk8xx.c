/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#define DBG_TAG "regulator.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "regulator_dm.h"
#include "rk8xx.h"

/* Field Definitions */
#define RK808_BUCK_VSEL_MASK        0x3f
#define RK808_BUCK4_VSEL_MASK       0xf
#define RK808_LDO_VSEL_MASK         0x1f

#define RK809_BUCK5_VSEL_MASK       0x7

#define RK817_LDO_VSEL_MASK         0x7f
#define RK817_BOOST_VSEL_MASK       0x7
#define RK817_BUCK_VSEL_MASK        0x7f

#define RK818_BUCK_VSEL_MASK        0x3f
#define RK818_BUCK4_VSEL_MASK       0x1f
#define RK818_LDO_VSEL_MASK         0x1f
#define RK818_LDO3_ON_VSEL_MASK     0xf
#define RK818_BOOST_ON_VSEL_MASK    0xe0

#define RK806_DCDC_SLP_REG_OFFSET   0x0a
#define RK806_NLDO_SLP_REG_OFFSET   0x05
#define RK806_PLDO_SLP_REG_OFFSET   0x06

#define RK806_BUCK_SEL_CNT          0xff
#define RK806_LDO_SEL_CNT           0xff

/* Ramp rate definitions for buck1 / buck2 only */
#define RK808_RAMP_RATE_OFFSET      3
#define RK808_RAMP_RATE_MASK        (3 << RK808_RAMP_RATE_OFFSET)
#define RK808_RAMP_RATE_2MV_PER_US  (0 << RK808_RAMP_RATE_OFFSET)
#define RK808_RAMP_RATE_4MV_PER_US  (1 << RK808_RAMP_RATE_OFFSET)
#define RK808_RAMP_RATE_6MV_PER_US  (2 << RK808_RAMP_RATE_OFFSET)
#define RK808_RAMP_RATE_10MV_PER_US (3 << RK808_RAMP_RATE_OFFSET)

#define RK808_DVS2_POL              RT_BIT(2)
#define RK808_DVS1_POL              RT_BIT(1)

/* Offset from XXX_ON_VSEL to XXX_SLP_VSEL */
#define RK808_SLP_REG_OFFSET        1
/* Offset from XXX_ON_VSEL to XXX_DVS_VSEL */
#define RK808_DVS_REG_OFFSET        2
/* max steps for increase voltage of Buck1/2, equal 100mv*/
#define MAX_STEPS_ONE_TIME          8
#define MAX_PIN_NR                  2

#define ENABLE_MASK(id)             (RT_BIT(id) | RT_BIT(4 + (id)))
#define DISABLE_VAL(id)             (RT_BIT(4 + (id)))

struct rk8xx_regulator_range
{
    int min;
    int min_sel;
    int max_sel;
    int step;
};

#define RK8XX_REGULATOR_RANGE(UVOLT_MIN, MIN_SEL, MAX_SEL, UVOLT_STEP) \
{                       \
    .min = UVOLT_MIN,   \
    .min_sel = MIN_SEL, \
    .max_sel = MAX_SEL, \
    .step = UVOLT_STEP, \
}

struct rk8xx_regulator_desc
{
    const char *name;
    const char *supply_name;

    const struct rt_regulator_ops *ops;

    int voltages_nr;
    int uvolt_min;
    int uvolt_step;

    int ranges_nr;
    const struct rk8xx_regulator_range *ranges;

    rt_uint32_t vsel_reg;
    rt_uint32_t vsel_mask;
    rt_uint32_t enable_reg;
    rt_uint32_t enable_mask;
    rt_uint32_t enable_val;
    rt_uint32_t disable_val;
};

#define RK8XX_REGULATOR_DESC(NAME, SUPPLY_NAME, \
        OPS,                                    \
        VOLTAGES_NR, UVOLT_MIN, UVOLT_STEP,     \
        RANGES_NR, RANGES,                      \
        VSEL_REG, VSEL_MASK, ENABLE_REG,        \
        ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
{                                               \
    .name = NAME,                               \
    .supply_name = SUPPLY_NAME,                 \
    .ops = &OPS,                                \
    .voltages_nr = VOLTAGES_NR,                 \
    .uvolt_min = UVOLT_MIN,                     \
    .uvolt_step = UVOLT_STEP,                   \
    .ranges_nr = RANGES_NR,                     \
    .ranges = RANGES,                           \
    .vsel_reg = VSEL_REG,                       \
    .vsel_mask = VSEL_MASK,                     \
    .enable_reg = ENABLE_REG,                   \
    .enable_mask = ENABLE_MASK,                 \
    .enable_val = ENABLE_VAL,                   \
    .disable_val = DISABLE_VAL,                 \
}

#define RK8XX_REGULATOR_VOLT(NAME, SUPPLY_NAME, OPS,        \
        VOLTAGES_NR, UVOLT_MIN, UVOLT_STEP,                 \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
    RK8XX_REGULATOR_DESC(NAME, SUPPLY_NAME, OPS,            \
        VOLTAGES_NR, UVOLT_MIN, UVOLT_STEP,                 \
        0, RT_NULL,                                         \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)

#define RK8XX_REGULATOR_VOLT_RANGE(NAME, SUPPLY_NAME, OPS,  \
        MIN, MAX, STEP,                                     \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
    RK8XX_REGULATOR_DESC(NAME, SUPPLY_NAME, OPS,            \
        (((MAX) - (MIN)) / (STEP) + 1), MIN, STEP,          \
        0, RT_NULL,                                         \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)

#define RK8XX_REGULATOR_VOLT_RANGES(NAME, SUPPLY_NAME, OPS, \
        VOLTAGES_NR, RANGES,                                \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
    RK8XX_REGULATOR_DESC(NAME, SUPPLY_NAME, OPS,            \
        VOLTAGES_NR, 0, 0,                                  \
        RT_ARRAY_SIZE(RANGES), RANGES,                      \
        VSEL_REG, VSEL_MASK,                                \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)

#define RK8XX_REGULATOR_SWITCH_DESC(NAME, SUPPLY_NAME, OPS, \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
    RK8XX_REGULATOR_DESC(NAME, SUPPLY_NAME, OPS,            \
        1, 0, 0,                                            \
        0, RT_NULL,                                         \
        0, 0,                                               \
        ENABLE_REG, ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)

struct rk8xx_regulator
{
    struct rt_regulator_node parent;
    struct rt_regulator_param param;

    rt_ubase_t pin;

    struct rt_device device;
    struct rk8xx *rk8xx;
    struct rt_ofw_node *ofw_node;

    const struct rk8xx_regulator_desc *desc;
};

#define raw_to_rk8xx_regulator(raw) rt_container_of(raw, struct rk8xx_regulator, parent)

static int regulator_voltage_from_selector(struct rk8xx_regulator *rk8xx_reg,
        int selector)
{
    int uvolt = -1;
    const struct rk8xx_regulator_desc *desc = rk8xx_reg->desc;

    if (desc->ranges_nr)
    {
        const struct rk8xx_regulator_range *range = &desc->ranges[0];

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

static int regulator_voltage_to_selector_range(struct rk8xx_regulator *rk8xx_reg,
        int min_uvolt, int max_uvolt)
{
    int selector = 0, max, uvolt, i;
    const struct rk8xx_regulator_range *range;
    const struct rk8xx_regulator_desc *desc = rk8xx_reg->desc;

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

        uvolt = regulator_voltage_from_selector(rk8xx_reg, selector);

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

static int regulator_voltage_to_selector(struct rk8xx_regulator *rk8xx_reg,
        int min_uvolt, int max_uvolt)
{
    int selector, uvolt;

    /* Allow uvolt_step to be 0 for fixed voltage */
    if (rk8xx_reg->desc->voltages_nr == 1 && rk8xx_reg->desc->uvolt_step == 0)
    {
        if (min_uvolt <= rk8xx_reg->desc->uvolt_min && rk8xx_reg->desc->uvolt_min <= max_uvolt)
        {
            return 0;
        }
        else
        {
            return -RT_EINVAL;
        }
    }

    if (!rk8xx_reg->desc->uvolt_step)
    {
        return -RT_EINVAL;
    }

    if (min_uvolt < rk8xx_reg->desc->uvolt_min)
    {
        min_uvolt = rk8xx_reg->desc->uvolt_min;
    }

    selector = RT_DIV_ROUND_UP(min_uvolt - rk8xx_reg->desc->uvolt_min, rk8xx_reg->desc->uvolt_step);

    if (selector < 0)
    {
        return selector;
    }

    /* Map back into a voltage to verify we're still in bounds */
    uvolt = regulator_voltage_from_selector(rk8xx_reg, selector);

    if (uvolt < min_uvolt || uvolt > max_uvolt)
    {
        return -RT_EINVAL;
    }

    return selector;
}

static rt_err_t rk8xx_regulator_enable(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    val = rk8xx_reg->desc->enable_val;

    if (!val)
    {
        val = rk8xx_reg->desc->enable_mask;
    }

    return rk8xx_update_bits(rk8xx_reg->rk8xx, rk8xx_reg->desc->enable_reg,
            rk8xx_reg->desc->enable_mask, val);
}

static rt_err_t rk8xx_regulator_disable(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    val = rk8xx_reg->desc->disable_val;

    return rk8xx_update_bits(rk8xx_reg->rk8xx, rk8xx_reg->desc->enable_reg,
            rk8xx_reg->desc->enable_mask, val);
}

static rt_bool_t rk8xx_regulator_is_enabled(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    val = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->enable_reg);

    if ((rt_err_t)val < 0)
    {
        return RT_FALSE;
    }

    val &= rk8xx_reg->desc->enable_mask;

    if (rk8xx_reg->desc->enable_val)
    {
        return val == rk8xx_reg->desc->enable_val;
    }

    return val != 0;
}

static rt_err_t rk8xx_regulator_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    int selector;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    selector = regulator_voltage_to_selector(rk8xx_reg, min_uvolt, max_uvolt);

    if (selector < 0)
    {
        if (selector == -RT_EINVAL)
        {
            selector = regulator_voltage_to_selector_range(rk8xx_reg,
                    min_uvolt, max_uvolt);

            if (selector < 0)
            {
                return -RT_EINVAL;
            }
        }
    }

    selector <<= __rt_ffs(rk8xx_reg->desc->vsel_mask) - 1;

    return rk8xx_update_bits(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg,
            rk8xx_reg->desc->vsel_mask, selector);
}

static int rk8xx_regulator_get_voltage(struct rt_regulator_node *reg_np)
{
    int uvolt;
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    val = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg);

    if ((rt_err_t)val < 0)
    {
        return val;
    }

    val &= rk8xx_reg->desc->vsel_mask;
    val >>= __rt_ffs(rk8xx_reg->desc->vsel_mask) - 1;

    uvolt = regulator_voltage_from_selector(rk8xx_reg, val);

    return uvolt < 0 ? -RT_EINVAL : uvolt;
}

/* wmsk */
static rt_bool_t rk8xx_regulator_wmsk_is_enabled(struct rt_regulator_node *reg_np)
{
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    val = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->enable_reg);

    if ((rt_err_t)val < 0)
    {
        return RT_FALSE;
    }

    val |= rk8xx_reg->desc->enable_mask & 0xf0;
    val &= rk8xx_reg->desc->enable_mask;

    if (rk8xx_reg->desc->enable_val)
    {
        return val == rk8xx_reg->desc->enable_val;
    }

    return val != 0;
}

/* buck */
static rt_err_t rk8xx_regulator_buck_set_voltage_no_pin(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    rt_err_t err;
    int delta_sel, selector;
    rt_uint32_t old_sel, tmp, val, mask;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    selector = regulator_voltage_to_selector(rk8xx_reg, min_uvolt, max_uvolt);

    if (selector < 0)
    {
        if (selector == -RT_EINVAL)
        {
            selector = regulator_voltage_to_selector_range(rk8xx_reg,
                    min_uvolt, max_uvolt);

            if (selector < 0)
            {
                return -RT_EINVAL;
            }
        }
    }

    val = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg);

    if ((rt_err_t)val < 0)
    {
        return (rt_err_t)val;
    }

    mask = rk8xx_reg->desc->vsel_mask;
    tmp = val & ~mask;
    old_sel = val & mask;
    old_sel >>= __rt_ffs(mask) - 1;
    delta_sel = selector - old_sel;

    while (delta_sel > MAX_STEPS_ONE_TIME)
    {
        old_sel += MAX_STEPS_ONE_TIME;
        val = old_sel << (__rt_ffs(mask) - 1);
        val |= tmp;

        rk8xx_write(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg, val);
        delta_sel = selector - old_sel;
    }

    selector <<= __rt_ffs(mask) - 1;
    val = tmp | selector;
    err = rk8xx_write(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg, val);

    /* wait 1us to make sure the target voltage to be stable */
    rt_hw_us_delay(1);

    return err;
}

static rt_err_t rk8xx_regulator_buck_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    rt_err_t err;
    int selector;
    rt_ssize_t gpio_level;
    rt_uint32_t reg, old_sel;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    if ((rt_base_t)rk8xx_reg->pin < 0)
    {
        return rk8xx_regulator_buck_set_voltage_no_pin(reg_np, min_uvolt, max_uvolt);
    }

    selector = regulator_voltage_to_selector(rk8xx_reg, min_uvolt, max_uvolt);

    if (selector < 0)
    {
        if (selector == -RT_EINVAL)
        {
            selector = regulator_voltage_to_selector_range(rk8xx_reg,
                    min_uvolt, max_uvolt);

            if (selector < 0)
            {
                return -RT_EINVAL;
            }
        }
    }

    reg = rk8xx_reg->desc->vsel_reg;

    gpio_level = rt_pin_read(rk8xx_reg->pin);

    if (gpio_level == 0)
    {
        reg += RK808_DVS_REG_OFFSET;
        old_sel = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg);
    }
    else
    {
        old_sel = rk8xx_read(rk8xx_reg->rk8xx, reg + RK808_DVS_REG_OFFSET);
    }

    if ((rt_err_t)old_sel < 0)
    {
        return -RT_EIO;
    }

    selector <<= __rt_ffs(rk8xx_reg->desc->vsel_mask) - 1;
    selector |= old_sel & ~rk8xx_reg->desc->vsel_mask;

    err = rk8xx_write(rk8xx_reg->rk8xx, reg, selector);

    if (err)
    {
        return err;
    }

    rt_pin_write(rk8xx_reg->pin, !gpio_level);

    return err;
}

static int rk8xx_regulator_buck_get_voltage(struct rt_regulator_node *reg_np)
{
    int uvolt;
    rt_uint32_t val;
    struct rk8xx_regulator *rk8xx_reg = raw_to_rk8xx_regulator(reg_np);

    if ((rt_base_t)rk8xx_reg->pin < 0 || rt_pin_read(rk8xx_reg->pin) == 0)
    {
        return rk8xx_regulator_get_voltage(reg_np);
    }

    val = rk8xx_read(rk8xx_reg->rk8xx, rk8xx_reg->desc->vsel_reg + RK808_DVS_REG_OFFSET);

    if ((rt_err_t)val < 0)
    {
        return (int)val;
    }

    val &= rk8xx_reg->desc->vsel_mask;
    val >>= __rt_ffs(rk8xx_reg->desc->vsel_mask) - 1;

    uvolt = regulator_voltage_from_selector(rk8xx_reg, val);

    return uvolt < 0 ? -RT_EINVAL : uvolt;
}

static const struct rt_regulator_ops rk8xx_regulator_ops =
{
    .enable = rk8xx_regulator_enable,
    .disable = rk8xx_regulator_disable,
    .is_enabled = rk8xx_regulator_is_enabled,
    .set_voltage = rk8xx_regulator_set_voltage,
    .get_voltage = rk8xx_regulator_get_voltage,
};

static const struct rt_regulator_ops rk8xx_regulator_wmsk_ops =
{
    .enable = rk8xx_regulator_enable,
    .disable = rk8xx_regulator_disable,
    .is_enabled = rk8xx_regulator_wmsk_is_enabled,
    .set_voltage = rk8xx_regulator_set_voltage,
    .get_voltage = rk8xx_regulator_get_voltage,
};

static const struct rt_regulator_ops rk8xx_regulator_buck_ops =
{
    .enable = rk8xx_regulator_enable,
    .disable = rk8xx_regulator_disable,
    .is_enabled = rk8xx_regulator_is_enabled,
    .set_voltage = rk8xx_regulator_buck_set_voltage,
    .get_voltage = rk8xx_regulator_buck_get_voltage,
};

static const struct rt_regulator_ops rk8xx_regulator_switch_ops =
{
    .enable = rk8xx_regulator_enable,
    .disable = rk8xx_regulator_disable,
    .is_enabled = rk8xx_regulator_is_enabled,
};

static const struct rt_regulator_ops rk8xx_regulator_switch_wmsk_ops =
{
    .enable = rk8xx_regulator_enable,
    .disable = rk8xx_regulator_disable,
    .is_enabled = rk8xx_regulator_wmsk_is_enabled,
};

static const struct rk8xx_regulator_range rk805_buck_1_2_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(712500, 0, 59, 12500),
    RK8XX_REGULATOR_RANGE(1800000, 60, 62, 200000),
    RK8XX_REGULATOR_RANGE(2300000, 63, 63, 0),
};

static const struct rk8xx_regulator_desc rk805_desc[] =
{
    RK8XX_REGULATOR_DESC("DCDC_REG1", "vcc1", rk8xx_regulator_ops,
            64, 0, 0,
            RT_ARRAY_SIZE(rk805_buck_1_2_voltage_ranges), rk805_buck_1_2_voltage_ranges,
            RK805_BUCK1_ON_VSEL_REG, RK818_BUCK_VSEL_MASK,
            RK805_DCDC_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_DESC("DCDC_REG2", "vcc2", rk8xx_regulator_ops,
            64, 0, 0,
            RT_ARRAY_SIZE(rk805_buck_1_2_voltage_ranges), rk805_buck_1_2_voltage_ranges,
            RK805_BUCK2_ON_VSEL_REG, RK818_BUCK_VSEL_MASK,
            RK805_DCDC_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("DCDC_REG3", "vcc3", rk8xx_regulator_switch_ops,
            RK805_DCDC_EN_REG, RT_BIT(2), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("DCDC_REG4", "vcc4", rk8xx_regulator_ops,
            800000, 3400000, 100000,
            RK805_BUCK4_ON_VSEL_REG, RK818_BUCK4_VSEL_MASK,
            RK805_DCDC_EN_REG, RT_BIT(3), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG1", "vcc5", rk8xx_regulator_ops,
            800000, 3400000, 100000,
            RK805_LDO1_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK805_LDO_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG2", "vcc5", rk8xx_regulator_ops,
            800000, 3400000, 100000,
            RK805_LDO2_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK805_LDO_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG3", "vcc6", rk8xx_regulator_ops,
            800000, 3400000, 100000,
            RK805_LDO3_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK805_LDO_EN_REG, RT_BIT(2), 0, 0),
};

static const struct rk8xx_regulator_range rk806_buck_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(500000, 0, 160, 6250),
    RK8XX_REGULATOR_RANGE(1500000, 161, 237, 25000),
    RK8XX_REGULATOR_RANGE(3400000, 238, 255, 0),
};

static const struct rk8xx_regulator_range rk806_ldo_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(500000, 0, 232, 12500),
    RK8XX_REGULATOR_RANGE(3400000, 233, 255, 0),
};

static const struct rk8xx_regulator_desc rk806_desc[] =
{
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG1", "vcc1", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK1_ON_VSEL, 0xff,
            RK806_POWER_EN0, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG2", "vcc2", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK2_ON_VSEL, 0xff,
            RK806_POWER_EN0, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG3", "vcc3", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK3_ON_VSEL, 0xff,
            RK806_POWER_EN0, ENABLE_MASK(2), ENABLE_MASK(2), DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG4", "vcc4", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK4_ON_VSEL, 0xff,
            RK806_POWER_EN0, ENABLE_MASK(3), ENABLE_MASK(3), DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG5", "vcc5", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK5_ON_VSEL, 0xff,
            RK806_POWER_EN1, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG6", "vcc6", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK6_ON_VSEL, 0xff,
            RK806_POWER_EN1, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG7", "vcc7", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK7_ON_VSEL, 0xff,
            RK806_POWER_EN1, ENABLE_MASK(2), ENABLE_MASK(2), DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG8", "vcc8", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK8_ON_VSEL, 0xff,
            RK806_POWER_EN1, ENABLE_MASK(3), ENABLE_MASK(3), DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG9", "vcc9", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK9_ON_VSEL, 0xff,
            RK806_POWER_EN2, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGES("DCDC_REG10", "vcc10", rk8xx_regulator_wmsk_ops,
            RK806_BUCK_SEL_CNT, rk806_buck_voltage_ranges,
            RK806_BUCK10_ON_VSEL, 0xff,
            RK806_POWER_EN2, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),

    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG1", "vcc13", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_NLDO1_ON_VSEL, 0xff,
            RK806_POWER_EN3, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG2", "vcc13", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_NLDO2_ON_VSEL, 0xff,
            RK806_POWER_EN3, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG3", "vcc13", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_NLDO3_ON_VSEL, 0xff,
            RK806_POWER_EN3, ENABLE_MASK(2), ENABLE_MASK(2), DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG4", "vcc14", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_NLDO4_ON_VSEL, 0xff,
            RK806_POWER_EN3, ENABLE_MASK(3), ENABLE_MASK(3), DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG5", "vcc14", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_NLDO5_ON_VSEL, 0xff,
            RK806_POWER_EN5, ENABLE_MASK(2), ENABLE_MASK(2), DISABLE_VAL(2)),

    RK8XX_REGULATOR_VOLT_RANGES("PLDO_REG6", "vcc11", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO1_ON_VSEL, 0xff,
            RK806_POWER_EN4, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGES("NLDO_REG1", "vcc11", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO2_ON_VSEL, 0xff,
            RK806_POWER_EN4, ENABLE_MASK(2), ENABLE_MASK(2), DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGES("NLDO_REG2", "vcc11", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO3_ON_VSEL, 0xff,
            RK806_POWER_EN4, ENABLE_MASK(3), ENABLE_MASK(3), DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGES("NLDO_REG3", "vcc12", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO4_ON_VSEL, 0xff,
            RK806_POWER_EN5, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGES("NLDO_REG4", "vcc12", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO5_ON_VSEL, 0xff,
            RK806_POWER_EN5, ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),

    RK8XX_REGULATOR_VOLT_RANGES("NLDO_REG5", "vcca", rk8xx_regulator_ops,
            RK806_LDO_SEL_CNT, rk806_ldo_voltage_ranges,
            RK806_PLDO6_ON_VSEL, 0xff,
            RK806_POWER_EN4, ENABLE_MASK(0), ENABLE_MASK(0), DISABLE_VAL(0)),
};

static const struct rk8xx_regulator_range rk808_ldo3_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(800000, 0, 13, 100000),
    RK8XX_REGULATOR_RANGE(2500000, 15, 15, 0),
};

static const struct rk8xx_regulator_desc rk808_desc[] =
{
    RK8XX_REGULATOR_VOLT("DCDC_REG1", "vcc1", rk8xx_regulator_buck_ops,
            64, 712500, 12500,
            RK808_BUCK1_ON_VSEL_REG, RK808_BUCK_VSEL_MASK,
            RK808_DCDC_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_VOLT("DCDC_REG2", "vcc2", rk8xx_regulator_buck_ops,
            64, 712500, 12500,
            RK808_BUCK2_ON_VSEL_REG, RK808_BUCK_VSEL_MASK,
            RK808_DCDC_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("DCDC_REG3", "vcc3", rk8xx_regulator_switch_ops,
            RK808_DCDC_EN_REG, RT_BIT(2), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("DCDC_REG4", "vcc4", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_BUCK4_ON_VSEL_REG, RK808_BUCK4_VSEL_MASK,
            RK808_DCDC_EN_REG, RT_BIT(3), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG1", "vcc6", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_LDO1_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG2", "vcc6", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_LDO2_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_DESC("LDO_REG3", "vcc7", rk8xx_regulator_ops,
            16, 0, 0,
            RT_ARRAY_SIZE(rk808_ldo3_voltage_ranges), rk808_ldo3_voltage_ranges,
            RK808_LDO3_ON_VSEL_REG, RK808_BUCK4_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(2), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG4", "vcc9", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_LDO4_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(3), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG5", "vcc9", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_LDO5_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(4), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG6", "vcc10", rk8xx_regulator_ops,
            800000, 2500000, 100000,
            RK808_LDO6_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(5), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG7", "vcc7", rk8xx_regulator_ops,
            800000, 2500000, 100000,
            RK808_LDO7_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(6), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG8", "vcc11", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK808_LDO8_ON_VSEL_REG, RK808_LDO_VSEL_MASK,
            RK808_LDO_EN_REG, RT_BIT(7), 0, 0),

    RK8XX_REGULATOR_SWITCH_DESC("SWITCH_REG1", "vcc8", rk8xx_regulator_switch_ops,
            RK808_DCDC_EN_REG, RT_BIT(5), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("SWITCH_REG2", "vcc12", rk8xx_regulator_switch_ops,
            RK808_DCDC_EN_REG, RT_BIT(6), 0, 0),
};

#define RK817_BUCK1_MIN0    500000
#define RK817_BUCK1_MAX0    1500000

#define RK817_BUCK1_MIN1    1600000
#define RK817_BUCK1_MAX1    2400000

#define RK817_BUCK3_MAX1    3400000

#define RK817_BUCK1_STP0    12500
#define RK817_BUCK1_STP1    100000

#define RK817_BUCK1_SEL0    ((RK817_BUCK1_MAX0 - RK817_BUCK1_MIN0) / RK817_BUCK1_STP0)
#define RK817_BUCK1_SEL1    ((RK817_BUCK1_MAX1 - RK817_BUCK1_MIN1) / RK817_BUCK1_STP1)
#define RK817_BUCK3_SEL1    ((RK817_BUCK3_MAX1 - RK817_BUCK1_MIN1) / RK817_BUCK1_STP1)

#define RK817_BUCK1_SEL_CNT (RK817_BUCK1_SEL0 + RK817_BUCK1_SEL1 + 1)
#define RK817_BUCK3_SEL_CNT (RK817_BUCK1_SEL0 + RK817_BUCK3_SEL1 + 1)

static const struct rk8xx_regulator_range rk817_buck1_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(RK817_BUCK1_MIN0, 0, RK817_BUCK1_SEL0, RK817_BUCK1_STP0),
    RK8XX_REGULATOR_RANGE(RK817_BUCK1_MIN1, RK817_BUCK1_SEL0 + 1, RK817_BUCK1_SEL_CNT, RK817_BUCK1_STP1),
};

static const struct rk8xx_regulator_range rk817_buck3_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(RK817_BUCK1_MIN0, 0, RK817_BUCK1_SEL0, RK817_BUCK1_STP0),
    RK8XX_REGULATOR_RANGE(RK817_BUCK1_MIN1, RK817_BUCK1_SEL0 + 1, RK817_BUCK3_SEL_CNT, RK817_BUCK1_STP1),
};

#define RK809_BUCK5_SEL_CNT 8

static const struct rk8xx_regulator_range rk809_buck5_voltage_ranges[] =
{
    RK8XX_REGULATOR_RANGE(1500000, 0, 0, 0),
    RK8XX_REGULATOR_RANGE(1800000, 1, 3, 200000),
    RK8XX_REGULATOR_RANGE(2800000, 4, 5, 200000),
    RK8XX_REGULATOR_RANGE(3300000, 6, 7, 300000),
};

static const struct rk8xx_regulator_desc rk809_desc[] =
{
    RK8XX_REGULATOR_DESC("DCDC_REG1", "vcc1", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK1_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC1), ENABLE_MASK(RK817_ID_DCDC1), DISABLE_VAL(RK817_ID_DCDC1)),
    RK8XX_REGULATOR_DESC("DCDC_REG2", "vcc2", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK2_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC2), ENABLE_MASK(RK817_ID_DCDC2), DISABLE_VAL(RK817_ID_DCDC2)),
    RK8XX_REGULATOR_DESC("DCDC_REG3", "vcc3", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK3_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC3), ENABLE_MASK(RK817_ID_DCDC3), DISABLE_VAL(RK817_ID_DCDC3)),
    RK8XX_REGULATOR_DESC("DCDC_REG4", "vcc4", rk8xx_regulator_wmsk_ops,
            RK817_BUCK3_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck3_voltage_ranges), rk817_buck3_voltage_ranges,
            RK817_BUCK4_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC4), ENABLE_MASK(RK817_ID_DCDC4), DISABLE_VAL(RK817_ID_DCDC4)),

    RK8XX_REGULATOR_DESC("DCDC_REG5", "vcc9", rk8xx_regulator_wmsk_ops,
            RK809_BUCK5_SEL_CNT, 0, 0,
            RT_ARRAY_SIZE(rk809_buck5_voltage_ranges), rk809_buck5_voltage_ranges,
            RK809_BUCK5_CONFIG(0), RK809_BUCK5_VSEL_MASK,
            RK817_POWER_EN_REG(3), ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG1", "vcc5", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(0), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(0), 0, DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG2", "vcc5", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(1), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(1), 0, DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG3", "vcc5", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(2), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG4", "vcc6", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(3), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(3), 0, DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG5", "vcc6", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(4), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(0), 0, DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG6", "vcc6", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(5), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(1), 0, DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG7", "vcc7", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(6), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG8", "vcc7", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(7), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(3), 0, DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG9", "vcc7", rk8xx_regulator_wmsk_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(8), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(3), ENABLE_MASK(0), 0, DISABLE_VAL(0)),

    RK8XX_REGULATOR_SWITCH_DESC("SWITCH_REG1", "vcc9", rk8xx_regulator_switch_wmsk_ops,
            RK817_POWER_EN_REG(3), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
    RK8XX_REGULATOR_SWITCH_DESC("SWITCH_REG2", "vcc8", rk8xx_regulator_switch_wmsk_ops,
            RK817_POWER_EN_REG(3), ENABLE_MASK(3), 0, DISABLE_VAL(3)),
};

static const struct rk8xx_regulator_desc rk817_desc[] =
{
    RK8XX_REGULATOR_DESC("DCDC_REG1", "vcc1", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK1_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC1), ENABLE_MASK(RK817_ID_DCDC1), DISABLE_VAL(RK817_ID_DCDC1)),
    RK8XX_REGULATOR_DESC("DCDC_REG2", "vcc2", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK2_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC2), ENABLE_MASK(RK817_ID_DCDC2), DISABLE_VAL(RK817_ID_DCDC2)),
    RK8XX_REGULATOR_DESC("DCDC_REG3", "vcc3", rk8xx_regulator_wmsk_ops,
            RK817_BUCK1_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck1_voltage_ranges), rk817_buck1_voltage_ranges,
            RK817_BUCK3_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC3), ENABLE_MASK(RK817_ID_DCDC3), DISABLE_VAL(RK817_ID_DCDC3)),
    RK8XX_REGULATOR_DESC("DCDC_REG4", "vcc4", rk8xx_regulator_wmsk_ops,
            RK817_BUCK3_SEL_CNT + 1, 0, 0,
            RT_ARRAY_SIZE(rk817_buck3_voltage_ranges), rk817_buck3_voltage_ranges,
            RK817_BUCK4_ON_VSEL_REG, RK817_BUCK_VSEL_MASK,
            RK817_POWER_EN_REG(0), ENABLE_MASK(RK817_ID_DCDC4), ENABLE_MASK(RK817_ID_DCDC4), DISABLE_VAL(RK817_ID_DCDC4)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG1", "vcc5", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(0), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(0), 0, DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG2", "vcc5", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(1), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(1), 0, DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG3", "vcc5", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(2), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG4", "vcc6", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(3), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(1), ENABLE_MASK(3), 0, DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG5", "vcc6", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(4), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(0), 0, DISABLE_VAL(0)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG6", "vcc6", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(5), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(1), 0, DISABLE_VAL(1)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG7", "vcc7", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(6), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG8", "vcc7", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(7), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(2), ENABLE_MASK(3), 0, DISABLE_VAL(3)),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG9", "vcc7", rk8xx_regulator_ops,
            600000, 3400000, 25000,
            RK817_LDO_ON_VSEL_REG(8), RK817_LDO_VSEL_MASK,
            RK817_POWER_EN_REG(3), ENABLE_MASK(0), 0, DISABLE_VAL(0)),

    RK8XX_REGULATOR_VOLT_RANGE("BOOST", "vcc8", rk8xx_regulator_wmsk_ops,
            4700000, 5400000, 100000,
            RK817_BOOST_OTG_CFG, RK817_BOOST_VSEL_MASK,
            RK817_POWER_EN_REG(3), ENABLE_MASK(1), ENABLE_MASK(1), DISABLE_VAL(1)),
    RK8XX_REGULATOR_SWITCH_DESC("OTG_SWITCH", "vcc9", rk8xx_regulator_switch_wmsk_ops,
            RK817_POWER_EN_REG(3), ENABLE_MASK(2), 0, DISABLE_VAL(2)),
};

static const struct rk8xx_regulator_desc rk818_desc[] =
{
    RK8XX_REGULATOR_VOLT("DCDC_REG1", "vcc1", rk8xx_regulator_ops,
            64, 712500, 12500,
            RK818_BUCK1_ON_VSEL_REG, RK818_BUCK_VSEL_MASK,
            RK818_DCDC_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_VOLT("DCDC_REG2", "vcc2", rk8xx_regulator_ops,
            64, 712500, 12500,
            RK818_BUCK2_ON_VSEL_REG, RK818_BUCK_VSEL_MASK,
            RK818_DCDC_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("DCDC_REG3", "vcc3", rk8xx_regulator_switch_ops,
            RK818_DCDC_EN_REG, RT_BIT(2), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("DCDC_REG4", "vcc4", rk8xx_regulator_ops,
            1800000, 3600000, 100000,
            RK818_BUCK4_ON_VSEL_REG, RK818_BUCK4_VSEL_MASK,
            RK818_DCDC_EN_REG, RT_BIT(3), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("DCDC_BOOST", "boost", rk8xx_regulator_ops,
            4700000, 5400000, 100000,
            RK818_BOOST_LDO9_ON_VSEL_REG, RK818_BOOST_ON_VSEL_MASK,
            RK818_DCDC_EN_REG, RT_BIT(4), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG1", "vcc6", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_LDO1_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG2", "vcc6", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_LDO2_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(1), 0, 0),
    RK8XX_REGULATOR_DESC("LDO_REG3", "vcc7", rk8xx_regulator_ops,
            16, 0, 0,
            RT_ARRAY_SIZE(rk808_ldo3_voltage_ranges), rk808_ldo3_voltage_ranges,
            RK818_LDO3_ON_VSEL_REG, RK818_LDO3_ON_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(2), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG4", "vcc8", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_LDO4_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(3), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG5", "vcc7", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_LDO5_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(4), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG6", "vcc8", rk8xx_regulator_ops,
            800000, 2500000, 100000,
            RK818_LDO6_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(5), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG7", "vcc7", rk8xx_regulator_ops,
            800000, 2500000, 100000,
            RK818_LDO7_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(6), 0, 0),
    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG8", "vcc8", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_LDO8_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_LDO_EN_REG, RT_BIT(7), 0, 0),

    RK8XX_REGULATOR_VOLT_RANGE("LDO_REG9", "vcc9", rk8xx_regulator_ops,
            1800000, 3400000, 100000,
            RK818_BOOST_LDO9_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
            RK818_DCDC_EN_REG, RT_BIT(5), 0, 0),

    RK8XX_REGULATOR_SWITCH_DESC("SWITCH_REG", "vcc9", rk8xx_regulator_switch_ops,
            RK818_DCDC_EN_REG, RT_BIT(6), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("HDMI_SWITCH", "h_5v", rk8xx_regulator_switch_ops,
            RK818_H5V_EN_REG, RT_BIT(0), 0, 0),
    RK8XX_REGULATOR_SWITCH_DESC("OTG_SWITCH", "usb", rk8xx_regulator_switch_ops,
            RK818_DCDC_EN_REG, RT_BIT(7), 0, 0),
};

static rt_err_t append_rk8xx_regulator(struct rk8xx *rk8xx, struct rt_ofw_node *np,
        const struct rk8xx_regulator_desc *desc_table, int id)
{
    rt_err_t err = RT_EOK;
    struct rt_regulator_node *rgp;
    struct rk8xx_regulator *rk8xx_reg;

    rk8xx_reg = rt_calloc(1, sizeof(*rk8xx_reg));

    if (!rk8xx_reg)
    {
        return -RT_ENOMEM;
    }

    rk8xx_reg->rk8xx = rk8xx;
    rk8xx_reg->desc = &desc_table[id];

    regulator_ofw_parse(np, &rk8xx_reg->param);

    rgp = &rk8xx_reg->parent;
    rgp->ops = rk8xx_reg->desc->ops;
    rgp->param = &rk8xx_reg->param;
    rgp->dev = &rk8xx_reg->device;

    rgp->dev->ofw_node = np;

    if (id < MAX_PIN_NR)
    {
        rt_uint32_t tmp;
        rt_uint8_t mode, value;

        rk8xx_reg->pin = rt_ofw_get_named_pin(rk8xx->dev->ofw_node,
                "dvs", id, &mode, &value);

        if ((rt_base_t)rk8xx_reg->pin >= 0)
        {
            rt_pin_mode(rk8xx_reg->pin, mode);
            rt_pin_write(rk8xx_reg->pin, value);

            tmp = id ? RK808_DVS2_POL : RK808_DVS1_POL;
            rk8xx_update_bits(rk8xx, RK808_IO_POL_REG, tmp,
                    rt_pin_read(rk8xx_reg->pin) == PIN_LOW ? 0 : tmp);
        }
    }

    if ((err = rt_regulator_register(rgp)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(rk8xx_reg);

    return err;
}

static rt_err_t rk8xx_regulator_probe(struct rt_platform_device *pdev)
{
    int desc_nr;
    rt_err_t err;
    struct rk8xx *rk8xx = pdev->priv;
    struct rt_ofw_node *np, *regulators_np = pdev->parent.ofw_node;
    const struct rk8xx_regulator_desc *desc_table;

    switch (rk8xx->variant)
    {
    case RK805_ID:
        desc_table = rk805_desc;
        desc_nr = RT_ARRAY_SIZE(rk805_desc);
        break;

    case RK806_ID:
        desc_table = rk806_desc;
        desc_nr = RT_ARRAY_SIZE(rk806_desc);
        break;

    case RK808_ID:
        desc_table = rk808_desc;
        desc_nr = RT_ARRAY_SIZE(rk808_desc);
        break;

    case RK809_ID:
        desc_table = rk809_desc;
        desc_nr = RT_ARRAY_SIZE(rk809_desc);
        break;

    case RK817_ID:
        desc_table = rk817_desc;
        desc_nr = RT_ARRAY_SIZE(rk817_desc);
        break;

    case RK818_ID:
        desc_table = rk818_desc;
        desc_nr = RT_ARRAY_SIZE(rk818_desc);
        break;

    default:
        return -RT_ENOSYS;
    }

    for (int i = 0; i < desc_nr; ++i)
    {
        const char *name = desc_table[i].name;

        if (!(np = rt_ofw_get_child_by_tag(regulators_np, name)))
        {
            continue;
        }

        rt_ofw_node_put(np);

        if ((err = append_rk8xx_regulator(rk8xx, np, desc_table, i)))
        {
            LOG_E("Append RK8XX regulator %s fail error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));

            if (err == -RT_ENOMEM)
            {
                return err;
            }
        }
    }

    return RT_EOK;
}

static struct rt_platform_driver rk8xx_regulator_driver =
{
    .name = "rk8xx-regulator",
    .probe = rk8xx_regulator_probe,
};

static int rk8xx_regulator_register(void)
{
    rt_platform_driver_register(&rk8xx_regulator_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rk8xx_regulator_register);
