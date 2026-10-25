/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * 2026-10-23     GuEe-GUI     first version
 */

#define DBG_TAG "regulator.axp313a"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "regulator_dm.h"

#define AXP313A_VERSION                 0x03
#define AXP313A_OUTPUT_CONTROL          0x10
#define AXP313A_DCDC1_CONTROL           0x13
#define AXP313A_DCDC2_CONTROL           0x14
#define AXP313A_DCDC3_CONTROL           0x15
#define AXP313A_ALDO1_CONTROL           0x16
#define AXP313A_DLDO1_CONTROL           0x17

#define AXP313A_CHIP_ID_MASK            0xcf
#define AXP1530_CHIP_ID                 0x48
#define AXP313A_CHIP_ID                 0x4b

#define AXP313A_DCDC_VOLTAGE_MASK       0x7f
#define AXP313A_LDO_VOLTAGE_MASK        0x1f

enum axp313a_rail_id
{
    AXP313A_DCDC1,
    AXP313A_DCDC2,
    AXP313A_DCDC3,
    AXP313A_ALDO1,
    AXP313A_DLDO1,
    AXP313A_RAIL_COUNT,
};

enum axp313a_voltage_range
{
    AXP313A_VOLTAGE_DCDC1,
    AXP313A_VOLTAGE_DCDC23,
    AXP313A_VOLTAGE_DCDC3,
    AXP313A_VOLTAGE_LDO,
};

struct axp313a_rail_info
{
    const char *name;
    const char *legacy_name;
    rt_uint8_t voltage_reg;
    rt_uint8_t voltage_mask;
    rt_uint8_t enable_mask;
    rt_uint8_t max_selector;
    enum axp313a_voltage_range voltage_range;
};

/*
 * DCDC3's 2.2 V to 2.5 V range follows the vendor BSP and Linux driver;
 * it differs from the AXP313A datasheet but has been verified in hardware.
 */
static const struct axp313a_rail_info axp313a_rails[] =
{
    [AXP313A_DCDC1] =
    {
        .name = "dcdc1",
        .voltage_reg = AXP313A_DCDC1_CONTROL,
        .voltage_mask = AXP313A_DCDC_VOLTAGE_MASK,
        .enable_mask = RT_BIT(0),
        .max_selector = 106,
        .voltage_range = AXP313A_VOLTAGE_DCDC1,
    },
    [AXP313A_DCDC2] =
    {
        .name = "dcdc2",
        .voltage_reg = AXP313A_DCDC2_CONTROL,
        .voltage_mask = AXP313A_DCDC_VOLTAGE_MASK,
        .enable_mask = RT_BIT(1),
        .max_selector = 87,
        .voltage_range = AXP313A_VOLTAGE_DCDC23,
    },
    [AXP313A_DCDC3] =
    {
        .name = "dcdc3",
        .voltage_reg = AXP313A_DCDC3_CONTROL,
        .voltage_mask = AXP313A_DCDC_VOLTAGE_MASK,
        .enable_mask = RT_BIT(2),
        .max_selector = 102,
        .voltage_range = AXP313A_VOLTAGE_DCDC3,
    },
    [AXP313A_ALDO1] =
    {
        .name = "aldo1",
        .legacy_name = "ldo1",
        .voltage_reg = AXP313A_ALDO1_CONTROL,
        .voltage_mask = AXP313A_LDO_VOLTAGE_MASK,
        .enable_mask = RT_BIT(3),
        .max_selector = 30,
        .voltage_range = AXP313A_VOLTAGE_LDO,
    },
    [AXP313A_DLDO1] =
    {
        .name = "dldo1",
        .legacy_name = "ldo2",
        .voltage_reg = AXP313A_DLDO1_CONTROL,
        .voltage_mask = AXP313A_LDO_VOLTAGE_MASK,
        .enable_mask = RT_BIT(4),
        .max_selector = 30,
        .voltage_range = AXP313A_VOLTAGE_LDO,
    },
};

struct axp313a
{
    struct rt_i2c_client *client;
    struct rt_mutex lock;
};

struct axp313a_rail
{
    struct rt_regulator_node regulator;
    struct rt_regulator_param param;
    struct axp313a *pmic;
    const struct axp313a_rail_info *info;
};

static rt_err_t axp313a_read_unlocked(struct axp313a *pmic, rt_uint8_t reg,
        rt_uint8_t *value)
{
    int ret;
    struct rt_i2c_msg msgs[] =
    {
        {
            .addr = pmic->client->client_addr,
            .flags = RT_I2C_WR,
            .buf = &reg,
            .len = sizeof(reg),
        },
        {
            .addr = pmic->client->client_addr,
            .flags = RT_I2C_RD,
            .buf = value,
            .len = sizeof(*value),
        },
    };

    ret = rt_i2c_transfer(pmic->client->bus, msgs, RT_ARRAY_SIZE(msgs));

    return ret == RT_ARRAY_SIZE(msgs) ? RT_EOK :
            ret < 0 ? (rt_err_t)ret : -RT_EIO;
}

static rt_err_t axp313a_write_unlocked(struct axp313a *pmic, rt_uint8_t reg,
        rt_uint8_t value)
{
    int ret;
    rt_uint8_t values[] = { reg, value };
    struct rt_i2c_msg msg =
    {
        .addr = pmic->client->client_addr,
        .flags = RT_I2C_WR,
        .buf = values,
        .len = sizeof(values),
    };

    ret = rt_i2c_transfer(pmic->client->bus, &msg, 1);

    return ret == 1 ? RT_EOK : ret < 0 ? (rt_err_t)ret : -RT_EIO;
}

static rt_err_t axp313a_read(struct axp313a *pmic, rt_uint8_t reg,
        rt_uint8_t *value)
{
    rt_err_t err;

    rt_mutex_take(&pmic->lock, RT_WAITING_FOREVER);
    err = axp313a_read_unlocked(pmic, reg, value);
    rt_mutex_release(&pmic->lock);

    return err;
}

static rt_err_t axp313a_update_bits(struct axp313a *pmic, rt_uint8_t reg,
        rt_uint8_t mask, rt_uint8_t value)
{
    rt_err_t err;
    rt_uint8_t old;
    rt_uint8_t updated;

    rt_mutex_take(&pmic->lock, RT_WAITING_FOREVER);

    err = axp313a_read_unlocked(pmic, reg, &old);
    if (!err)
    {
        updated = (old & ~mask) | (value & mask);

        if (updated != old)
        {
            err = axp313a_write_unlocked(pmic, reg, updated);
        }
    }

    rt_mutex_release(&pmic->lock);

    return err;
}

static int axp313a_list_voltage(const struct axp313a_rail_info *info,
        unsigned int selector)
{
    if (selector > info->max_selector)
    {
        return -RT_EINVAL;
    }

    switch (info->voltage_range)
    {
    case AXP313A_VOLTAGE_DCDC1:
        if (selector >= 88)
        {
            return 1600000 + (selector - 88) * 100000;
        }
        /* fall through */
    case AXP313A_VOLTAGE_DCDC23:
    case AXP313A_VOLTAGE_DCDC3:
        return selector <= 70 ?
                500000 + selector * 10000 :
                1220000 + (selector - 71) * 20000;

    case AXP313A_VOLTAGE_LDO:
        return 500000 + selector * 100000;
    }

    return -RT_EINVAL;
}

static rt_err_t axp313a_enable(struct rt_regulator_node *node)
{
    struct axp313a_rail *rail = node->priv;

    return axp313a_update_bits(rail->pmic, AXP313A_OUTPUT_CONTROL,
            rail->info->enable_mask, rail->info->enable_mask);
}

static rt_err_t axp313a_disable(struct rt_regulator_node *node)
{
    struct axp313a_rail *rail = node->priv;

    return axp313a_update_bits(rail->pmic, AXP313A_OUTPUT_CONTROL,
            rail->info->enable_mask, 0);
}

static rt_bool_t axp313a_is_enabled(struct rt_regulator_node *node)
{
    struct axp313a_rail *rail = node->priv;
    rt_uint8_t value;

    return !axp313a_read(rail->pmic, AXP313A_OUTPUT_CONTROL, &value) &&
            !!(value & rail->info->enable_mask);
}

static int axp313a_get_voltage(struct rt_regulator_node *node)
{
    struct axp313a_rail *rail = node->priv;
    rt_uint8_t value;
    rt_err_t err;

    err = axp313a_read(rail->pmic, rail->info->voltage_reg, &value);

    return err ? err : axp313a_list_voltage(rail->info,
            value & rail->info->voltage_mask);
}

static rt_err_t axp313a_set_voltage(struct rt_regulator_node *node,
        int min_uvolt, int max_uvolt)
{
    struct axp313a_rail *rail = node->priv;
    unsigned int selector;
    int voltage;

    if (min_uvolt > max_uvolt)
    {
        return -RT_EINVAL;
    }

    for (selector = 0; selector <= rail->info->max_selector; ++selector)
    {
        voltage = axp313a_list_voltage(rail->info, selector);

        if (voltage >= min_uvolt && voltage <= max_uvolt)
        {
            return axp313a_update_bits(rail->pmic, rail->info->voltage_reg,
                    rail->info->voltage_mask, selector);
        }
    }

    return -RT_EINVAL;
}

static const struct rt_regulator_ops axp313a_ops =
{
    .enable = axp313a_enable,
    .disable = axp313a_disable,
    .is_enabled = axp313a_is_enabled,
    .set_voltage = axp313a_set_voltage,
    .get_voltage = axp313a_get_voltage,
};

static rt_err_t axp313a_rail_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint8_t output;
    struct axp313a_rail *rail;

    if (pdev->dev_id >= AXP313A_RAIL_COUNT)
    {
        return -RT_EINVAL;
    }

    rail = rt_calloc(1, sizeof(*rail));
    if (!rail)
    {
        return -RT_ENOMEM;
    }

    rail->pmic = pdev->priv;
    rail->info = &axp313a_rails[pdev->dev_id];

    if ((err = regulator_ofw_parse(pdev->parent.ofw_node, &rail->param)))
    {
        goto _fail;
    }

    if (!rail->param.name)
    {
        rail->param.name = ((struct rt_ofw_node *)pdev->parent.ofw_node)->name;
    }

    rail->regulator.dev = &pdev->parent;
    rail->regulator.priv = rail;
    rail->regulator.param = &rail->param;
    rail->regulator.supply_name = rail->param.name;
    rail->regulator.ops = &axp313a_ops;

    /* Ensure I2C access is working without modifying firmware settings. */
    if ((err = axp313a_read(rail->pmic, AXP313A_OUTPUT_CONTROL, &output)))
    {
        goto _fail;
    }

    if ((rail->param.always_on || rail->param.boot_on) &&
            !(output & rail->info->enable_mask))
    {
        if ((err = axp313a_enable(&rail->regulator)))
        {
            goto _fail;
        }
    }

    if ((err = rt_regulator_register(&rail->regulator)))
    {
        goto _fail;
    }

    pdev->parent.user_data = rail;

    return RT_EOK;

_fail:
    rt_free(rail);

    return err;
}

static rt_err_t axp313a_rail_remove(struct rt_platform_device *pdev)
{
    struct axp313a_rail *rail = pdev->parent.user_data;
    rt_err_t err;

    if (!rail)
    {
        return RT_EOK;
    }

    err = rt_regulator_unregister(&rail->regulator);
    if (err)
    {
        return err;
    }

    rt_ofw_data(pdev->parent.ofw_node) = RT_NULL;
    pdev->parent.user_data = RT_NULL;
    rt_free(rail);

    return RT_EOK;
}

static struct rt_platform_driver axp313a_rail_driver =
{
    .name = "axp313a-regulator",
    .probe = axp313a_rail_probe,
    .remove = axp313a_rail_remove,
};

static void axp313a_free_children(struct rt_platform_device **children)
{
    unsigned int index;

    for (index = 0; index < AXP313A_RAIL_COUNT; ++index)
    {
        if (children[index])
        {
            rt_ofw_node_put(children[index]->parent.ofw_node);
            rt_free(children[index]);
        }
    }
}

static rt_err_t axp313a_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_uint8_t chip_id;
    unsigned int index;
    struct axp313a *pmic;
    struct rt_ofw_node *regulators;
    struct rt_platform_device *children[AXP313A_RAIL_COUNT] = { 0 };

    pmic = rt_calloc(1, sizeof(*pmic));
    if (!pmic)
    {
        return -RT_ENOMEM;
    }

    pmic->client = client;
    if ((err = rt_mutex_init(&pmic->lock, "axp313", RT_IPC_FLAG_PRIO)))
    {
        goto _free_pmic;
    }

    if ((err = axp313a_read(pmic, AXP313A_VERSION, &chip_id)))
    {
        goto _detach_lock;
    }

    chip_id &= AXP313A_CHIP_ID_MASK;
    if (chip_id != AXP1530_CHIP_ID && chip_id != AXP313A_CHIP_ID)
    {
        err = -RT_EINVAL;
        goto _detach_lock;
    }

    regulators = rt_ofw_get_child_by_tag(client->parent.ofw_node, "regulators");
    if (!regulators)
    {
        err = -RT_EINVAL;
        goto _detach_lock;
    }

    for (index = 0; index < AXP313A_RAIL_COUNT; ++index)
    {
        const struct axp313a_rail_info *info = &axp313a_rails[index];
        struct rt_ofw_node *node;

        node = rt_ofw_get_child_by_tag(regulators, info->name);
        if (!node && info->legacy_name)
        {
            node = rt_ofw_get_child_by_tag(regulators, info->legacy_name);
        }

        if (!node)
        {
            continue;
        }

        if (!rt_ofw_node_is_available(node))
        {
            rt_ofw_node_put(node);
            continue;
        }

        children[index] = rt_platform_device_alloc("axp313a-regulator");
        if (!children[index])
        {
            rt_ofw_node_put(node);
            err = -RT_ENOMEM;
            goto _put_regulators;
        }

        children[index]->dev_id = index;
        children[index]->priv = pmic;
        children[index]->parent.ofw_node = node;
    }

    rt_ofw_node_put(regulators);
    client->parent.user_data = pmic;

    for (index = 0; index < AXP313A_RAIL_COUNT; ++index)
    {
        struct rt_ofw_node *node;
        struct rt_platform_device *child = children[index];

        if (!child)
        {
            continue;
        }

        node = child->parent.ofw_node;
        node->dev = &child->parent;

        err = rt_platform_device_register(child);
        if (err)
        {
            LOG_E("%s registration failed: %s", axp313a_rails[index].name, rt_strerror(err));
        }
        else if (!child->parent.drv)
        {
            LOG_E("%s is not available: regulator probe failed", axp313a_rails[index].name);
        }
    }

    LOG_D("PMIC ID %02x, preserving firmware voltage settings", chip_id);

    return RT_EOK;

_put_regulators:
    rt_ofw_node_put(regulators);
    axp313a_free_children(children);

_detach_lock:
    rt_mutex_detach(&pmic->lock);

_free_pmic:
    rt_free(pmic);

    return err;
}

static rt_err_t axp313a_remove(struct rt_i2c_client *client)
{
    /* The PMIC supplies the running system and owns permanent child devices. */
    return -RT_EBUSY;
}

static const struct rt_ofw_node_id axp313a_ids[] =
{
    { .compatible = "x-powers,axp313a" },
    { .compatible = "x-powers,axp1530" },
    { /* sentinel */ },
};

static struct rt_i2c_driver axp313a_driver =
{
    .ofw_ids = axp313a_ids,
    .probe = axp313a_probe,
    .remove = axp313a_remove,
};

static int axp313a_register(void)
{
    rt_platform_driver_register(&axp313a_rail_driver);
    rt_i2c_driver_register(&axp313a_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(axp313a_register);
