/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SY8810L_H__
#define __SY8810L_H__

enum
{
    SY8810L_ID_DCDC1,
};

#define SPACEMIT_SY8810L_MAX_REG        0x2

#define SY8810L_BUCK_VSEL_MASK          0x3f
#define SY8810L_BUCK_EN_MASK            0x80

#define SY8810L_BUCK_CTRL_REG           0x1
#define SY8810L_BUCK_VSEL_REG           0x0

#define SY8810L_DESC(_id, _match, _supply, _nv, _vr, _vm, _er, _em, _lr) \
    SPACEMIT_PMIC_REGULATOR_DESC_COMMON(_id, _match, _supply, _nv, _vr, _vm, _er, _em, _lr, pmic_dcdc_ldo_ops)

#ifdef __SPACEMIT_REGULATOR_INTERNAL
static const struct spacemit_pmic_regulator_range sy8810l_buck_ranges[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(600000, 0x0, 0x5a, 10000),
};

static const struct spacemit_pmic_regulator_desc sy8810l_reg[] =
{
    /* BUCK */
    SY8810L_DESC(SY8810L_ID_DCDC1, "EDCDC_REG1", "dcdc1",
        91, SY8810L_BUCK_VSEL_REG, SY8810L_BUCK_VSEL_MASK,
        SY8810L_BUCK_CTRL_REG, SY8810L_BUCK_EN_MASK, sy8810l_buck_ranges),
};

static struct spacemit_pmic_regulator_data sy8810l_regulator_data =
{
    .desc = sy8810l_reg,
    .desc_nr = RT_ARRAY_SIZE(sy8810l_reg),
};
#endif /* __SPACEMIT_REGULATOR_INTERNAL */

#ifdef __SPACEMIT_PMIC_INTERNAL
static struct spacemit_pmic_mfd_endpoint sy8810l_mfd_endpoint[] =
{
    {
        .ofw_name = "spacemit-regulator@sy8810l",
        .ofw_compatible = "pmic,regulator,sy8810l",
    },
};

static struct spacemit_pmic_mfd_data sy8810l_mfd_data =
{
    .regmap_cfg =
    {
        .reg_bits = 8,
        .val_bits = 8,
        .max_register = SPACEMIT_SY8810L_MAX_REG,
    },
    .endpoint = sy8810l_mfd_endpoint,
    .endpoint_num = RT_ARRAY_SIZE(sy8810l_mfd_endpoint),
};
#endif /* __SPACEMIT_PMIC_INTERNAL */

#endif /* __SY8810L_H__ */
