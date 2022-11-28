/*
 * Copyright (C) 2020 allwinnertech Ltd.
 */

#include <ffs.h>
#include <log.h>
#include <stddef.h>
#include <sunxi_hal_regulator.h>
#include <sunxi_hal_regulator_private.h>

static int voltage2val(struct regulator_desc *info, int voltage, u8 *reg_val)
{
    const struct regulator_linear_range *range;
    int i;

    if (!info->linear_ranges) {
        *reg_val = (voltage - info->min_uv + info->step1_uv - 1)
            / info->step1_uv;
        return 0;
    }

    for (i = 0; i < info->n_linear_ranges; i++) {
        int linear_max_uV;

        range = &info->linear_ranges[i];
        linear_max_uV = range->min_uV +
            (range->max_sel - range->min_sel) * range->uV_step;

        if (!(voltage <= linear_max_uV && voltage >= range->min_uV))
            continue;

        /* range->uV_step == 0 means fixed voltage range */
        if (range->uV_step == 0) {
            *reg_val = 0;
        } else {
            *reg_val = (voltage - range->min_uV) / range->uV_step;
        }

        *reg_val += range->min_sel;
        return 0;
    }

    return -1;
}

static int val2voltage(struct regulator_desc *info, u8 reg_val, int *voltage)
{
    const struct regulator_linear_range *range = info->linear_ranges;
    int i;

    if (!info->linear_ranges) {
        *voltage = info->min_uv + info->step1_uv * reg_val;
        return 0;
    }

    for (i = 0; i < info->n_linear_ranges; i++, range++) {
        if (!(reg_val <= range->max_sel && reg_val >= range->min_sel))
            continue;

        *voltage = (reg_val - range->min_sel) * range->uV_step +
               range->min_uV;
        return 0;
    }

    return -1;
}

static int axp_regulator_set_voltage(struct regulator_dev *rdev, int target_uV)
{
    unsigned char id = REGULATOR_ID(rdev->flag);
    struct regulator_desc *pd = (struct regulator_desc *)rdev->private;
    struct regulator_desc *info = &pd[id];
    u8 val;

    if (voltage2val(info, target_uV, &val))
        return -1;

    val <<= ffs(info->vol_mask) - 1;
    return hal_axp_byte_update(rdev, info->vol_reg, val, info->vol_mask);
}

static int axp_regulator_get_voltage(struct regulator_dev *rdev, int *vol_uV)
{
    unsigned char id = REGULATOR_ID(rdev->flag);
    struct regulator_desc *pd = (struct regulator_desc *)rdev->private;
    struct regulator_desc *info = &pd[id];
    u8 val;
    int ret;

    ret = hal_axp_byte_read(rdev, info->vol_reg, &val);
    if (ret)
        return ret;

    val &= info->vol_mask;
    val >>= ffs(info->vol_mask) - 1;
    if (val2voltage(info, val, vol_uV))
        return -1;

    return 0;
}

static int axp_regulator_enable(struct regulator_dev *rdev)
{
    unsigned char id = REGULATOR_ID(rdev->flag);
    struct regulator_desc *pd = (struct regulator_desc *)rdev->private;
    struct regulator_desc *info = &pd[id];
    u8 reg_val = 0;

    reg_val = info->enable_val;
    if (!reg_val)
        reg_val = info->enable_mask;

    return hal_axp_byte_update(rdev, info->enable_reg,
                   reg_val, info->enable_mask);
}

static int axp_regulator_disable(struct regulator_dev *rdev)
{
    unsigned char id = REGULATOR_ID(rdev->flag);
    struct regulator_desc *pd = (struct regulator_desc *)rdev->private;
    struct regulator_desc *info = &pd[id];
    u8 reg_val = 0;

    reg_val = info->disable_val;
    if (!reg_val)
        reg_val = ~info->enable_mask;

    return hal_axp_byte_update(rdev, info->enable_reg,
                   reg_val, info->enable_mask);
}

struct regulator_ops axp_regulator_ops = {
    .set_voltage    = axp_regulator_set_voltage,
    .get_voltage    = axp_regulator_get_voltage,
    .enable     = axp_regulator_enable,
    .disable    = axp_regulator_disable,
};
