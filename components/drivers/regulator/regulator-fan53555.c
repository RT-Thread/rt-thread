/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#define DBG_TAG "regulator.fan53555"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "regulator_dm.h"

/* Voltage setting */
#define FAN53555_VSEL0          0x00
#define FAN53555_VSEL1          0x01

#define TCS4525_VSEL0           0x11
#define TCS4525_VSEL1           0x10
#define TCS4525_TIME            0x13
#define TCS4525_COMMAND         0x14
#define TCS4525_LIMCONF         0x16

#define RK8600_VSEL0            FAN53555_VSEL0
#define RK8600_VSEL1            FAN53555_VSEL1
#define RK8602_VSEL0            0x06
#define RK8602_VSEL1            0x07
#define RK860X_MAX_SET          0x08

/* Control register */
#define FAN53555_CONTROL        0x02
/* IC Type */
#define FAN53555_ID1            0x03
/* IC mask version */
#define FAN53555_ID2            0x04
/* Monitor register */
#define FAN53555_MONITOR        0x05

/* VSEL bit definitions */
#define VSEL_BUCK_EN            RT_BIT(7)
#define VSEL_MODE               RT_BIT(6)
#define RK8600_VSEL_NSEL_MASK   0x3f
#define RK8602_VSEL_NSEL_MASK   0xff
/* Chip ID */
#define DIE_ID                  0x0f
#define DIE_REV                 0x0f
/* Control bit definitions */
#define CTL_OUTPUT_DISCHG       RT_BIT(7)
#define CTL_SLEW_MASK           (0x7 << 4)
#define CTL_SLEW_SHIFT          4
#define CTL_RESET               RT_BIT(2)
#define CTL_MODE_VSEL0_MODE     RT_BIT(0)
#define CTL_MODE_VSEL1_MODE     RT_BIT(1)

#define FAN53555_NVOLTAGES      64      /* Numbers of voltages */
#define FAN53526_NVOLTAGES      128
#define RK8600_NVOLTAGES        FAN53555_NVOLTAGES
#define RK8602_NVOLTAGES        160

#define TCS_VSEL0_MODE          RT_BIT(7)
#define TCS_VSEL1_MODE          RT_BIT(6)

#define TCS_SLEW_MASK           (0x3 << 3)
#define TCS_SLEW_SHIFT          3

/* VSEL ID */
enum
{
    FAN53555_VSEL_ID_0 = 0,
    FAN53555_VSEL_ID_1,
};

enum fan53555_vendor
{
    FAN53526_VENDOR_FAIRCHILD = 0,
    FAN53555_VENDOR_FAIRCHILD,
    RK8600_VENDOR_ROCKCHIP,     /* RK8600, RK8601 */
    RK8602_VENDOR_ROCKCHIP,     /* RK8602, RK8603 */
    FAN53555_VENDOR_SILERGY,
    FAN53526_VENDOR_TCS,
};

enum
{
    FAN53526_CHIP_ID_01 = 1,
};

enum
{
    FAN53526_CHIP_REV_08 = 8,
};

/* IC Type */
enum
{
    FAN53555_CHIP_ID_00 = 0,
    FAN53555_CHIP_ID_01,
    FAN53555_CHIP_ID_02,
    FAN53555_CHIP_ID_03,
    FAN53555_CHIP_ID_04,
    FAN53555_CHIP_ID_05,
    FAN53555_CHIP_ID_08 = 8,
};

enum
{
    RK8600_CHIP_ID_08 = 8,  /* RK8600, RK8601 */
    RK8602_CHIP_ID_10 = 10, /* RK8602, RK8603 */
};

enum
{
    TCS4525_CHIP_ID_12 = 12,
};

enum
{
    TCS4526_CHIP_ID_00 = 0,
};

/* IC mask revision */
enum
{
    FAN53555_CHIP_REV_00 = 0x3,
    FAN53555_CHIP_REV_13 = 0xf,
};

enum
{
    SILERGY_SYR82X = 8,
    SILERGY_SYR83X = 9,
};

struct fan53555_regulator
{
    struct rt_regulator_node parent;
    struct rt_regulator_param param;

    struct rt_i2c_client *client;

    rt_ubase_t vsel_pin;

    /* IC Type and Rev */
    int chip_id;
    int chip_rev;
    enum fan53555_vendor vendor;

    rt_uint32_t limit_volt;

    /* Voltage setting register */
    rt_uint32_t vol_reg;
    rt_uint32_t vol_mask;
    rt_uint32_t sleep_reg;
    rt_uint32_t en_reg;
    rt_uint32_t sleep_en_reg;
    /* Mode */
    rt_uint32_t mode_reg;
    rt_uint32_t mode_mask;
    /* Slew rate */
    rt_uint32_t slew_reg;
    rt_uint32_t slew_mask;
    rt_uint32_t slew_shift;
    /* Voltage range and step(linear) */
    rt_uint32_t vsel_min;
    rt_uint32_t vsel_step;
    rt_uint32_t vsel_count;

    /* Voltage slew rate limiting */
    rt_uint32_t slew_rate;
    rt_uint32_t sleep_vsel_id;

    const int *ramp_delay_table;
    int ramp_delay_nr;
};

#define raw_to_fan53555_regulator(raw) rt_container_of(raw, struct fan53555_regulator, parent)

static rt_uint32_t fan53555_vol_mask(rt_uint32_t vsel_count)
{
    rt_uint32_t bit;

    if (!vsel_count)
    {
        return 0;
    }

    bit = 32 - __rt_clz(vsel_count - 1);

    return (1U << bit) - 1;
}

static const int slew_rates[] =
{
    64000, 32000, 16000, 8000, 4000, 2000, 1000, 500,
};

static const int tcs_slew_rates[] =
{
    18700, 9300, 4600, 2300,
};

static rt_err_t fan53555_regulator_write(struct fan53555_regulator *freg,
        rt_uint8_t reg, rt_uint8_t value)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[1];
    rt_uint8_t data[sizeof(reg) + sizeof(value)] = { reg };
    struct rt_i2c_client *client = freg->client;

    rt_memcpy(&data[sizeof(reg)], &value, sizeof(value));

    msg[0].buf = data;
    msg[0].addr = client->client_addr;
    msg[0].len = sizeof(data);
    msg[0].flags = RT_I2C_WR;

    res = rt_i2c_transfer(client->bus, msg, 1);

    return res > 0 ? RT_EOK : res;
}

static rt_err_t fan53555_regulator_read(struct fan53555_regulator *freg,
        rt_uint8_t reg, rt_uint8_t *values)
{
    rt_int32_t res;
    struct rt_i2c_msg msg[2];
    struct rt_i2c_client *client = freg->client;

    msg[0].buf = &reg;
    msg[0].addr = client->client_addr;
    msg[0].len = sizeof(reg);
    msg[0].flags = RT_I2C_WR;

    msg[1].buf = (rt_uint8_t *)values;
    msg[1].addr = client->client_addr;
    msg[1].len = sizeof(*values);
    msg[1].flags = RT_I2C_RD;

    res = rt_i2c_transfer(client->bus, msg, 2);

    return res >= 2 ? RT_EOK : (res < 0 ? (rt_err_t)res : -RT_EIO);
}

static rt_err_t fan53555_regulator_update_bits(struct fan53555_regulator *freg,
        rt_uint8_t reg, rt_uint8_t mask, rt_uint8_t data)
{
    rt_err_t err;
    rt_uint8_t old, tmp;

    if ((err = fan53555_regulator_read(freg, reg, &old)))
    {
        return err;
    }

    tmp = old & ~mask;
    tmp |= (data & mask);

    return fan53555_regulator_write(freg, reg, tmp);
}

static rt_err_t fan53555_regulator_enable(struct rt_regulator_node *reg_np)
{
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if (freg->vsel_pin >= 0)
    {
        rt_pin_mode(freg->vsel_pin, PIN_MODE_OUTPUT);
        rt_pin_write(freg->vsel_pin, !freg->sleep_vsel_id);

        return RT_EOK;
    }

    return fan53555_regulator_update_bits(freg, freg->en_reg, VSEL_BUCK_EN, VSEL_BUCK_EN);
}

static rt_err_t fan53555_regulator_disable(struct rt_regulator_node *reg_np)
{
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if (freg->vsel_pin >= 0)
    {
        rt_pin_mode(freg->vsel_pin, PIN_MODE_OUTPUT);
        rt_pin_write(freg->vsel_pin, freg->sleep_vsel_id);

        return RT_EOK;
    }

    return fan53555_regulator_update_bits(freg, freg->en_reg, VSEL_BUCK_EN, 0);
}

static rt_bool_t fan53555_regulator_is_enabled(struct rt_regulator_node *reg_np)
{
    rt_err_t err;
    rt_uint8_t val;
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if (freg->vsel_pin >= 0)
    {
        rt_uint8_t pin_val;

        rt_pin_mode(freg->vsel_pin, PIN_MODE_INPUT);
        pin_val = rt_pin_read(freg->vsel_pin);

        return freg->sleep_vsel_id ? !pin_val : pin_val;
    }

    if ((err = fan53555_regulator_read(freg, freg->en_reg, &val)))
    {
        LOG_E("Read %s register error = %s", "enable", rt_strerror(err));

        return RT_FALSE;
    }

    if (val & VSEL_BUCK_EN)
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_err_t fan53555_regulator_set_voltage(struct rt_regulator_node *reg_np,
        int min_uvolt, int max_uvolt)
{
    int uvolt;
    rt_uint8_t selector;
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if (freg->vsel_count == 1 && freg->vsel_step == 0)
    {
        if (min_uvolt <= freg->vsel_min && freg->vsel_min <= max_uvolt)
        {
            return 0;
        }
        else
        {
            return -RT_EINVAL;
        }
    }

    if (!freg->vsel_step)
    {
        return -RT_EINVAL;
    }

    if (min_uvolt < freg->vsel_min)
    {
        min_uvolt = freg->vsel_min;
    }

    selector = RT_DIV_ROUND_UP(min_uvolt - freg->vsel_min, freg->vsel_step);

    if ((rt_int8_t)selector < 0)
    {
        return selector;
    }

    if (selector >= freg->vsel_count)
    {
        return -RT_EINVAL;
    }

    uvolt = freg->vsel_min + (freg->vsel_step * selector);

    if (uvolt < min_uvolt || uvolt > max_uvolt)
    {
        return -RT_EINVAL;
    }

    selector <<= __rt_ffs(freg->vol_mask) - 1;

    return fan53555_regulator_update_bits(freg, freg->vol_reg, freg->vol_mask, selector);
}

static int fan53555_regulator_get_voltage(struct rt_regulator_node *reg_np)
{
    rt_err_t err;
    rt_uint8_t selector;
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if ((err = fan53555_regulator_read(freg, freg->vol_reg, &selector)))
    {
        return err;
    }

    selector = (selector & freg->vol_mask) >> (__rt_ffs(freg->vol_mask) - 1);

    if (selector >= freg->vsel_count)
    {
        return -RT_EINVAL;
    }

    return freg->vsel_min + (freg->vsel_step * selector);
}

static rt_err_t fan53555_regulator_set_mode(struct rt_regulator_node *reg_np,
        rt_uint32_t mode)
{
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    switch (mode)
    {
    case RT_REGULATOR_MODE_FAST:
        fan53555_regulator_update_bits(freg,
                freg->mode_reg, freg->mode_mask, freg->mode_mask);
        break;

    case RT_REGULATOR_MODE_NORMAL:
        fan53555_regulator_update_bits(freg,
                freg->mode_reg, freg->mode_mask, 0);
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_int32_t fan53555_regulator_get_mode(struct rt_regulator_node *reg_np)
{
    rt_err_t err;
    rt_uint8_t val;
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    if ((err = fan53555_regulator_read(freg, freg->mode_reg, &val)))
    {
        LOG_E("Read %s register error = %s", "mode", rt_strerror(err));

        return RT_FALSE;
    }

    if (val & freg->mode_mask)
    {
        return RT_REGULATOR_MODE_FAST;
    }
    else
    {
        return RT_REGULATOR_MODE_NORMAL;
    }
}

static rt_err_t fan53555_regulator_set_ramp_delay(struct rt_regulator_node *reg_np,
        int ramp)
{
    int regval = -1, ramp_delay_nr;
    const int *ramp_delay_table;
    struct fan53555_regulator *freg = raw_to_fan53555_regulator(reg_np);

    ramp_delay_nr = freg->ramp_delay_nr;
    ramp_delay_table = freg->ramp_delay_table;

    for (int i = 0; i < ramp_delay_nr; ++i)
    {
        if (ramp <= ramp_delay_table[i])
        {
            regval = i;
            continue;
        }

        break;
    }

    if (regval < 0)
    {
        LOG_E("unsupported ramp value %d", ramp);

        return -RT_EINVAL;
    }

    return fan53555_regulator_update_bits(freg, freg->slew_reg,
            freg->slew_mask, regval << freg->slew_shift);
}

static const struct rt_regulator_ops fan53555_regulator_switch_ops =
{
    .enable = fan53555_regulator_enable,
    .disable = fan53555_regulator_disable,
    .is_enabled = fan53555_regulator_is_enabled,
    .set_voltage = fan53555_regulator_set_voltage,
    .get_voltage = fan53555_regulator_get_voltage,
    .set_mode = fan53555_regulator_set_mode,
    .get_mode = fan53555_regulator_get_mode,
    .set_ramp_delay = fan53555_regulator_set_ramp_delay,
};

#ifdef RT_USING_OFW
static rt_err_t fan53555_regulator_parse_ofw(struct fan53555_regulator *freg,
        struct rt_device *dev)
{
    rt_err_t err;
    struct rt_ofw_node *np = dev->ofw_node;

    if ((err = regulator_ofw_parse(np, &freg->param)))
    {
        return err;
    }

    rt_ofw_prop_read_u32(np, "limit-microvolt", &freg->limit_volt);

    rt_ofw_prop_read_u32(np, "fcs,suspend-voltage-selector", &freg->sleep_vsel_id);
    rt_ofw_prop_read_u32(np, "rockchip,suspend-voltage-selector", &freg->sleep_vsel_id);

    freg->vsel_pin = rt_ofw_get_named_pin(np, "vsel", 0, RT_NULL, RT_NULL);
    if (freg->vsel_pin < 0)
    {
        freg->vsel_pin = PIN_NONE;
    }

    return RT_EOK;
}
#else
static rt_err_t fan53555_regulator_parse_ofw(struct fan53555_regulator *freg,
        struct rt_device *dev)
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

static rt_err_t fan53555_regulator_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_uint8_t val;
    rt_bool_t hw_always_on;
    rt_uint32_t ramp_delay;
    struct rt_regulator_node *rgp;
    struct rt_device *dev = &client->parent;
    struct fan53555_regulator *freg = rt_calloc(1, sizeof(*freg));

    if (!freg)
    {
        return -RT_ENOMEM;
    }

    if ((err = fan53555_regulator_parse_ofw(freg, dev)))
    {
        goto _fail;
    }

    if (dev->ofw_node)
    {
        freg->vendor = (rt_ubase_t)client->ofw_id->data;
    }
    else
    {
        if (!freg->param.ramp_delay)
        {
            int slew_idx = freg->slew_rate;

            if (slew_idx > RT_ARRAY_SIZE(slew_rates))
            {
                LOG_E("Invalid slew rate");

                err = -RT_EINVAL;
                goto _fail;
            }

            freg->param.ramp_delay = slew_rates[slew_idx];
        }

        freg->vendor = (rt_ubase_t)rt_i2c_client_id_data(client);
    }
    freg->client = client;

    /* Get chip ID */
    if ((err = fan53555_regulator_read(freg, FAN53555_ID1, &val)))
    {
        LOG_E("%s: read ID1 failed: %s", client->name, rt_strerror(err));
        goto _fail;
    }
    freg->chip_id = val & DIE_ID;

    /* Get chip revision */
    if ((err = fan53555_regulator_read(freg, FAN53555_ID2, &val)))
    {
        LOG_E("%s: read ID2 failed: %s", client->name, rt_strerror(err));
        goto _fail;
    }
    freg->chip_rev = val & DIE_REV;

    if (freg->sleep_vsel_id > FAN53555_VSEL_ID_1)
    {
        LOG_E("Invalid vsel-id = %d", freg->sleep_vsel_id);
        goto _fail;
    }

    /*
     * For 00,01 options:
     *  VOUT = 0.7125V + NSELx * 12.5mV, from 0.7125 to 1.5V.
     * For 02,03 options:
     *  VOUT = 0.5V + NSELx * 6.25mV, from 0.5 to 1.5V.
     */

    /* Setup voltage control register */
    freg->vol_reg = 0xff;
    switch (freg->vendor)
    {
    case FAN53526_VENDOR_FAIRCHILD:
    case FAN53555_VENDOR_FAIRCHILD:
    case FAN53555_VENDOR_SILERGY:
        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->sleep_reg = FAN53555_VSEL0;
            freg->vol_reg = FAN53555_VSEL1;
            break;

        case FAN53555_VSEL_ID_1:
            freg->sleep_reg = FAN53555_VSEL1;
            freg->vol_reg = FAN53555_VSEL0;
            break;

        default:
            break;
        }
        freg->sleep_en_reg = freg->sleep_reg;
        freg->en_reg = freg->vol_reg;
        break;

    case RK8600_VENDOR_ROCKCHIP:
        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->sleep_reg = RK8600_VSEL0;
            freg->vol_reg = RK8600_VSEL1;
            break;

        case FAN53555_VSEL_ID_1:
            freg->sleep_reg = RK8600_VSEL1;
            freg->vol_reg = RK8600_VSEL0;
            break;

        default:
            break;
        }
        freg->sleep_en_reg = freg->sleep_reg;
        freg->en_reg = freg->vol_reg;
        freg->vol_reg = RK8600_VSEL_NSEL_MASK;
        break;

    case RK8602_VENDOR_ROCKCHIP:
        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->sleep_reg = RK8602_VSEL0;
            freg->vol_reg = RK8602_VSEL1;
            freg->sleep_en_reg = RK8600_VSEL0;
            freg->en_reg = RK8600_VSEL1;
            break;

        case FAN53555_VSEL_ID_1:
            freg->sleep_reg = RK8602_VSEL1;
            freg->vol_reg = RK8602_VSEL0;
            freg->sleep_en_reg = RK8600_VSEL1;
            freg->en_reg = RK8600_VSEL0;
            break;

        default:
            break;
        }
        freg->vol_reg = RK8602_VSEL_NSEL_MASK;
        break;

    case FAN53526_VENDOR_TCS:
        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->sleep_reg = TCS4525_VSEL0;
            freg->vol_reg = TCS4525_VSEL1;
            break;

        case FAN53555_VSEL_ID_1:
            freg->sleep_reg = TCS4525_VSEL1;
            freg->vol_reg = TCS4525_VSEL0;
            break;

        default:
            break;
        }
        freg->sleep_en_reg = freg->sleep_reg;
        freg->en_reg = freg->vol_reg;
        break;

    default:
        break;
    }

    /* Setup mode control register */
    switch (freg->vendor)
    {
    case FAN53526_VENDOR_FAIRCHILD:
        freg->mode_reg = FAN53555_CONTROL;

        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->mode_mask = CTL_MODE_VSEL1_MODE;
            break;

        case FAN53555_VSEL_ID_1:
            freg->mode_mask = CTL_MODE_VSEL0_MODE;
            break;

        default:
            break;
        }
        break;
    case FAN53555_VENDOR_FAIRCHILD:
    case FAN53555_VENDOR_SILERGY:
    case RK8600_VENDOR_ROCKCHIP:
        freg->mode_reg = freg->vol_reg;
        freg->mode_mask = VSEL_MODE;
        break;

    case RK8602_VENDOR_ROCKCHIP:
        freg->mode_mask = VSEL_MODE;

        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->mode_reg = RK8600_VSEL1;
            break;

        case FAN53555_VSEL_ID_1:
            freg->mode_reg = RK8600_VSEL0;
            break;

        default:
            break;
        }
        break;

    case FAN53526_VENDOR_TCS:
        freg->mode_reg = TCS4525_COMMAND;

        switch (freg->sleep_vsel_id)
        {
        case FAN53555_VSEL_ID_0:
            freg->mode_mask = TCS_VSEL1_MODE;
            break;

        case FAN53555_VSEL_ID_1:
            freg->mode_mask = TCS_VSEL0_MODE;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

    /* Setup voltage range */
    switch (freg->vendor)
    {
    case FAN53526_VENDOR_FAIRCHILD:
        /* Init voltage range and step */
        switch (freg->chip_id)
        {
        case FAN53526_CHIP_ID_01:
            switch (freg->chip_rev)
            {
            case FAN53526_CHIP_REV_08:
                freg->vsel_min = 600000;
                freg->vsel_step = 6250;
                break;

            default:
                LOG_E("Chip ID %d with rev %d not supported",
                        freg->chip_id, freg->chip_rev);
                err = -RT_EINVAL;
                goto _fail;
            }
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }

        freg->slew_reg = FAN53555_CONTROL;
        freg->slew_mask = CTL_SLEW_MASK;
        freg->slew_shift = CTL_SLEW_SHIFT;
        freg->ramp_delay_table = slew_rates;
        freg->ramp_delay_nr = RT_ARRAY_SIZE(slew_rates);
        freg->vsel_count = FAN53526_NVOLTAGES;
        break;

    case FAN53555_VENDOR_FAIRCHILD:
        /* Init voltage range and step */
        switch (freg->chip_id) {
        case FAN53555_CHIP_ID_00:
            switch (freg->chip_rev)
            {
            case FAN53555_CHIP_REV_00:
                freg->vsel_min = 600000;
                freg->vsel_step = 10000;
                break;

            case FAN53555_CHIP_REV_13:
                freg->vsel_min = 800000;
                freg->vsel_step = 10000;
                break;

            default:
                LOG_E("Chip ID %d with rev %d not supported",
                        freg->chip_id, freg->chip_rev);
                err = -RT_EINVAL;
                goto _fail;
            }
            break;
        case FAN53555_CHIP_ID_01:
        case FAN53555_CHIP_ID_03:
        case FAN53555_CHIP_ID_05:
        case FAN53555_CHIP_ID_08:
            freg->vsel_min = 600000;
            freg->vsel_step = 10000;
            break;

        case FAN53555_CHIP_ID_04:
            freg->vsel_min = 603000;
            freg->vsel_step = 12826;
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }

        freg->slew_reg = FAN53555_CONTROL;
        freg->slew_mask = CTL_SLEW_MASK;
        freg->slew_shift = CTL_SLEW_SHIFT;
        freg->ramp_delay_table = slew_rates;
        freg->ramp_delay_nr = RT_ARRAY_SIZE(slew_rates);
        freg->vsel_count = FAN53555_NVOLTAGES;
        break;

    case FAN53555_VENDOR_SILERGY:
        /* Init voltage range and step */
        switch (freg->chip_id)
        {
        case SILERGY_SYR82X:
        case SILERGY_SYR83X:
            freg->vsel_min = 712500;
            freg->vsel_step = 12500;
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }

        freg->slew_reg = FAN53555_CONTROL;
        freg->slew_mask = CTL_SLEW_MASK;
        freg->slew_shift = CTL_SLEW_SHIFT;
        freg->ramp_delay_table = slew_rates;
        freg->ramp_delay_nr = RT_ARRAY_SIZE(slew_rates);
        freg->vsel_count = FAN53555_NVOLTAGES;
        break;

    case RK8600_VENDOR_ROCKCHIP:
        /* Init voltage range and step */
        switch (freg->chip_id)
        {
        case RK8600_CHIP_ID_08:
            freg->vsel_min = 712500;
            freg->vsel_step = 12500;
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }

        freg->slew_reg = FAN53555_CONTROL;
        freg->slew_mask = CTL_SLEW_MASK;
        freg->slew_shift = CTL_SLEW_SHIFT;
        freg->ramp_delay_table = slew_rates;
        freg->ramp_delay_nr = RT_ARRAY_SIZE(slew_rates);
        freg->vsel_count = RK8600_NVOLTAGES;
        break;

    case RK8602_VENDOR_ROCKCHIP:
        /* Init voltage range and step */
        switch (freg->chip_id)
        {
        case RK8602_CHIP_ID_10:
            freg->vsel_min = 500000;
            freg->vsel_step = 6250;
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }

        freg->slew_reg = FAN53555_CONTROL;
        freg->slew_mask = CTL_SLEW_MASK;
        freg->slew_shift = CTL_SLEW_SHIFT;
        freg->ramp_delay_table = slew_rates;
        freg->ramp_delay_nr = RT_ARRAY_SIZE(slew_rates);
        freg->vsel_count = RK8602_NVOLTAGES;
        break;

    case FAN53526_VENDOR_TCS:
        switch (freg->chip_id)
        {
        case TCS4525_CHIP_ID_12:
        case TCS4526_CHIP_ID_00:
            freg->slew_reg = TCS4525_TIME;
            freg->slew_mask = TCS_SLEW_MASK;
            freg->slew_shift = TCS_SLEW_SHIFT;
            freg->ramp_delay_table = tcs_slew_rates;
            freg->ramp_delay_nr = RT_ARRAY_SIZE(tcs_slew_rates);

            /* Init voltage range and step */
            freg->vsel_min = 600000;
            freg->vsel_step = 6250;
            freg->vsel_count = FAN53526_NVOLTAGES;
            break;

        default:
            LOG_E("Chip ID %d not supported", freg->chip_id);
            err = -RT_EINVAL;
            goto _fail;
        }
        break;

    default:
        break;
    }

    if (freg->limit_volt)
    {
        if (freg->limit_volt < freg->vsel_min || freg->limit_volt > 1500000)
        {
            freg->limit_volt = 1500000;
        }

        val = (freg->limit_volt - freg->vsel_min) / freg->vsel_step;

        if (freg->vendor == FAN53526_VENDOR_TCS)
        {
            err = fan53555_regulator_write(freg, TCS4525_LIMCONF, val);
        }
        else
        {
            err = fan53555_regulator_write(freg, RK860X_MAX_SET, val);
        }

        if (err)
        {
            LOG_E("%s: Failed to set limit voltage", client->name);
            goto _fail;
        }
    }

    freg->vol_mask = fan53555_vol_mask(freg->vsel_count);

    rgp = &freg->parent;
    rgp->ops = &fan53555_regulator_switch_ops;
    rgp->param = &freg->param;
    rgp->dev = &client->parent;
    rgp->supply_name = freg->param.name;

    freg->param.enable_delay = 400;

    client->parent.user_data = freg;

    /*
     * U-Boot/loader already enables always-on rails (e.g. vdd_cpu).
     * Skip boot-time enable/ramp I2C in rt_regulator_register() to avoid
     * blocking early boot on a shared PMU I2C bus.
     */
    hw_always_on = freg->param.always_on;
    ramp_delay = freg->param.ramp_delay;
    if (hw_always_on)
    {
        freg->param.boot_on = RT_FALSE;
        freg->param.always_on = RT_FALSE;
        freg->param.ramp_delay = 0;
        freg->param.ramp_disable = RT_TRUE;
    }

    if ((err = rt_regulator_register(rgp)))
    {
        goto _fail;
    }

    if (hw_always_on)
    {
        rt_atomic_store(&rgp->enabled_count, 1);
    }

    if (ramp_delay)
    {
        err = fan53555_regulator_set_ramp_delay(rgp, ramp_delay);
        if (err)
        {
            LOG_W("%s: set ramp %u us failed: %s", client->name,
                  ramp_delay, rt_strerror(err));
        }
    }

    return RT_EOK;

_fail:
    rt_free(freg);

    return err;
}

static rt_err_t fan53555_regulator_shutdown(struct rt_i2c_client *client)
{
    rt_err_t err = RT_EOK;
    struct fan53555_regulator *freg = client->parent.user_data;

    switch (freg->vendor)
    {
    case FAN53555_VENDOR_FAIRCHILD:
    case FAN53555_VENDOR_SILERGY:
        err = fan53555_regulator_update_bits(freg, freg->slew_reg, CTL_RESET, CTL_RESET);
        break;

    case FAN53526_VENDOR_TCS:
        err = fan53555_regulator_update_bits(freg, TCS4525_LIMCONF, CTL_RESET, CTL_RESET);
        break;

    default:
        break;
    }

    if (err < 0)
    {
        LOG_E("Shutdown error = %s", rt_strerror(err));
    }

    return RT_EOK;
}

static const struct rt_i2c_device_id fan53555_regulator_ids[] =
{
    { .name = "fan53526", .data = (void *)FAN53526_VENDOR_FAIRCHILD },
    { .name = "fan53555", .data = (void *)FAN53555_VENDOR_FAIRCHILD },
    { .name = "rk8600", .data = (void *)RK8600_VENDOR_ROCKCHIP },
    { .name = "rk8601", .data = (void *)RK8600_VENDOR_ROCKCHIP },
    { .name = "rk8602", .data = (void *)RK8602_VENDOR_ROCKCHIP },
    { .name = "rk8603", .data = (void *)RK8602_VENDOR_ROCKCHIP },
    { .name = "syr827", .data = (void *)FAN53555_VENDOR_SILERGY },
    { .name = "syr828", .data = (void *)FAN53555_VENDOR_SILERGY },
    { .name = "tcs4525", .data = (void *)FAN53526_VENDOR_TCS },
    { .name = "tcs4526", .data = (void *)FAN53526_VENDOR_TCS },
    { .name = "tcs452x", .data = (void *)FAN53526_VENDOR_TCS },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id fan53555_regulator_ofw_ids[] =
{
    { .compatible = "fcs,fan53526", .data = (void *)FAN53526_VENDOR_FAIRCHILD },
    { .compatible = "fcs,fan53555", .data = (void *)FAN53555_VENDOR_FAIRCHILD },
    { .compatible = "rockchip,rk8600", .data = (void *)RK8600_VENDOR_ROCKCHIP },
    { .compatible = "rockchip,rk8601", .data = (void *)RK8600_VENDOR_ROCKCHIP },
    { .compatible = "rockchip,rk8602", .data = (void *)RK8602_VENDOR_ROCKCHIP },
    { .compatible = "rockchip,rk8603", .data = (void *)RK8602_VENDOR_ROCKCHIP },
    { .compatible = "silergy,syr827", .data = (void *)FAN53555_VENDOR_SILERGY },
    { .compatible = "silergy,syr828", .data = (void *)FAN53555_VENDOR_SILERGY },
    { .compatible = "tcs,tcs4525", .data = (void *)FAN53526_VENDOR_TCS },
    { .compatible = "tcs,tcs4526", .data = (void *)FAN53526_VENDOR_TCS },
    { .compatible = "tcs,tcs452x", .data = (void *)FAN53526_VENDOR_TCS },
    { /* sentinel */ },
};

static struct rt_i2c_driver fan53555_regulator_driver =
{
    .ids = fan53555_regulator_ids,
    .ofw_ids = fan53555_regulator_ofw_ids,

    .probe = fan53555_regulator_probe,
    .shutdown = fan53555_regulator_shutdown,
};
RT_I2C_DRIVER_EXPORT(fan53555_regulator_driver);
