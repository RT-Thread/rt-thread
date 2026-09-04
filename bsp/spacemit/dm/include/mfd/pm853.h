/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __PM853_H__
#define __PM853_H__

enum
{
    PM853_ID_DCDC1,
    PM853_ID_DCDC2,
    PM853_ID_DCDC3,
    PM853_ID_DCDC4,
    PM853_ID_DCDC5,
    PM853_ID_LDO1,
    PM853_ID_LDO2,
    PM853_ID_LDO3,
    PM853_ID_LDO4,
    PM853_ID_LDO5,
    PM853_ID_LDO6,
    PM853_ID_LDO7,
    PM853_ID_LDO8,
    PM853_ID_LDO9,
    PM853_ID_LDO10,
    PM853_ID_LDO11,
    PM853_ID_LDO12,
    PM853_ID_LDO13,
    PM853_ID_LDO14,
    PM853_ID_LDO15,
    PM853_ID_LDO16,
    PM853_ID_LDO17,
    PM853_ID_LDO18,
    PM853_ID_LDO19,
    PM853_ID_LDO20,
    PM853_ID_LDO21,
    PM853_ID_LDO22,
    PM853_ID_LDO5_SW,
};

#define PM853_LDO_BUCK_EN_REG0          0x11
#define PM853_LDO_BUCK_EN_REG1          0x12
#define PM853_LDO_BUCK_EN_REG2          0x13
#define PM853_LDO_BUCK_EN_REG3          0x14

#define PM853_BUCK1_EN_MSK              0x1
#define PM853_BUCK2_EN_MSK              0x2
#define PM853_BUCK3_EN_MSK              0x4
#define PM853_BUCK4_EN_MSK              0x8
#define PM853_BUCK5_EN_MSK              0x10

#define PM853_LDO1_EN_MSK               0x20
#define PM853_LDO2_EN_MSK               0x40
#define PM853_LDO3_EN_MSK               0x80
#define PM853_LDO4_EN_MSK               0x1
#define PM853_LDO5_EN_MSK               0x2
#define PM853_LDO6_EN_MSK               0x4
#define PM853_LDO7_EN_MSK               0x8
#define PM853_LDO8_EN_MSK               0x10
#define PM853_LDO9_EN_MSK               0x20
#define PM853_LDO10_EN_MSK              0x40
#define PM853_LDO11_EN_MSK              0x80
#define PM853_LDO12_EN_MSK              0x1
#define PM853_LDO13_EN_MSK              0x2
#define PM853_LDO14_EN_MSK              0x4
#define PM853_LDO15_EN_MSK              0x8
#define PM853_LDO16_EN_MSK              0x10
#define PM853_LDO17_EN_MSK              0x20
#define PM853_LDO18_EN_MSK              0x40
#define PM853_LDO19_EN_MSK              0x80
#define PM853_LDO20_EN_MSK              0x1
#define PM853_LDO21_EN_MSK              0x2
#define PM853_LDO22_EN_MSK              0x4
#define PM853_SW_EN_MSK                 0x8


#define PM853_BUCK1_VSEL_REG            0x30
#define PM853_BUCK2_VSEL_REG            0x50
#define PM853_BUCK3_VSEL_REG            0x60
#define PM853_BUCK4_VSEL_REG            0x80
#define PM853_BUCK5_VSEL_REG            0x90

#define PM853_BUCK1_VSEL_MSK            0x7f
#define PM853_BUCK2_VSEL_MSK            0x7f
#define PM853_BUCK3_VSEL_MSK            0x7f
#define PM853_BUCK4_VSEL_MSK            0x7f
#define PM853_BUCK5_VSEL_MSK            0x7f

#define PM853_LDO_VSEL_MSK              0xf
#define PM853_LDO1_VSEL_REG             0xb1
#define PM853_LDO2_VSEL_REG             0xb4
#define PM853_LDO3_VSEL_REG             0xb7
#define PM853_LDO4_VSEL_REG             0xba
#define PM853_LDO5_VSEL_REG             0xbd
#define PM853_LDO6_VSEL_REG             0xc0
#define PM853_LDO7_VSEL_REG             0xc3
#define PM853_LDO8_VSEL_REG             0xc6
#define PM853_LDO9_VSEL_REG             0xc9
#define PM853_LDO10_VSEL_REG            0xcc
#define PM853_LDO11_VSEL_REG            0xcf
#define PM853_LDO12_VSEL_REG            0xd2
#define PM853_LDO13_VSEL_REG            0xd5
#define PM853_LDO14_VSEL_REG            0xd8
#define PM853_LDO15_VSEL_REG            0xdb
#define PM853_LDO16_VSEL_REG            0xde
#define PM853_LDO17_VSEL_REG            0xe1
#define PM853_LDO18_VSEL_REG            0xe4
#define PM853_LDO19_VSEL_REG            0xe7
#define PM853_LDO20_VSEL_REG            0xea
#define PM853_LDO21_VSEL_REG            0xed
#define PM853_LDO22_VSEL_REG            0xf0

#define SPACEMIT_PM853_MAX_REG          0xf1

#define PM853_DESC(_id, _match, _supply, _nv, _vr, _vm, _er, _em, _lr) \
    SPACEMIT_PMIC_REGULATOR_DESC_COMMON(_id, _match, _supply, _nv, _vr, _vm, _er, _em, _lr, pmic_dcdc_ldo_ops)

#define PM853_DESC_SWITCH(_id, _match, _supply, _ereg, _emask) \
    SPACEMIT_PMIC_REGULATOR_DESC_SWITCH_COM(_id, _match, _supply, _ereg, _emask, 0, 0, pmic_switch_ops)

#ifdef __SPACEMIT_REGULATOR_INTERNAL
static const struct spacemit_pmic_regulator_range pm853_buck_ranges1[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(480000, 0x0, 0x50, 10000),
    SPACEMIT_PMIC_REGULATOR_RANGE(1320000, 0x51, 0x7F, 40000),
};

static const struct spacemit_pmic_regulator_range pm853_buck_ranges2[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(600000, 0x0, 0x50, 12500),
    SPACEMIT_PMIC_REGULATOR_RANGE(1650000, 0x51, 0x7F, 50000),
};

static const struct spacemit_pmic_regulator_range pm853_ldo_ranges1[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(1200000, 0x0, 0x6, 100000),
    SPACEMIT_PMIC_REGULATOR_RANGE(1850000, 0x7, 0x8, 50000),
    SPACEMIT_PMIC_REGULATOR_RANGE(2750000, 0x9, 0xc, 50000),
    SPACEMIT_PMIC_REGULATOR_RANGE(3000000, 13, 14, 100000),
    SPACEMIT_PMIC_REGULATOR_RANGE(3300000, 15, 15, 0),
};

static const struct spacemit_pmic_regulator_range pm853_ldo_ranges2[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(1600000, 0x0, 0x3, 100000),
};

static const struct spacemit_pmic_regulator_range pm853_ldo_ranges3[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(1200000, 0x0, 0xf, 50000),
};

static const struct spacemit_pmic_regulator_range pm853_ldo_ranges4[] =
{
    SPACEMIT_PMIC_REGULATOR_RANGE(1000000, 0x0, 0x7, 50000),
};

static const struct spacemit_pmic_regulator_desc pm853_reg[] =
{
    /* BUCK */
    PM853_DESC(PM853_ID_DCDC1, "DCDC_REG1", "vcc_sys",
        128, PM853_BUCK1_VSEL_REG, PM853_BUCK1_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_BUCK1_EN_MSK,
        pm853_buck_ranges1),

    PM853_DESC(PM853_ID_DCDC2, "DCDC_REG2", "vcc_sys",
        128, PM853_BUCK2_VSEL_REG, PM853_BUCK2_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_BUCK2_EN_MSK,
        pm853_buck_ranges2),

    PM853_DESC(PM853_ID_DCDC3, "DCDC_REG3", "vcc_sys",
        128, PM853_BUCK3_VSEL_REG, PM853_BUCK3_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_BUCK3_EN_MSK,
        pm853_buck_ranges2),

    PM853_DESC(PM853_ID_DCDC4, "DCDC_REG4", "vcc_sys",
        128, PM853_BUCK4_VSEL_REG, PM853_BUCK4_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_BUCK4_EN_MSK,
        pm853_buck_ranges1),

    PM853_DESC(PM853_ID_DCDC5, "DCDC_REG5", "vcc_sys",
        128, PM853_BUCK5_VSEL_REG, PM853_BUCK5_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_BUCK5_EN_MSK,
        pm853_buck_ranges2),

    /* ALDO */
    PM853_DESC(PM853_ID_LDO1, "LDO_REG1", "vcc_sys",
        16, PM853_LDO1_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_LDO1_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO2, "LDO_REG2", "vcc_sys",
        16, PM853_LDO2_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_LDO2_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO3, "LDO_REG3", "vcc_sys",
        16, PM853_LDO3_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG0, PM853_LDO3_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO4, "LDO_REG4", "vcc_sys",
        16, PM853_LDO4_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO4_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO5, "LDO_REG5", "vcc_sys",
        4, PM853_LDO5_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO5_EN_MSK,
        pm853_ldo_ranges2),

    PM853_DESC(PM853_ID_LDO6, "LDO_REG6", "vcc_sys",
        16, PM853_LDO6_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO6_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO7, "LDO_REG7", "dcdc2",
        16, PM853_LDO7_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO7_EN_MSK,
        pm853_ldo_ranges3),

    PM853_DESC(PM853_ID_LDO8, "LDO_REG8", "vcc_sys",
        16, PM853_LDO8_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO8_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO9, "LDO_REG9", "vcc_sys",
        16, PM853_LDO9_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO9_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO10, "LDO_REG10", "vcc_sys",
        16, PM853_LDO10_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO10_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO11, "LDO_REG11", "dcdc2",
        16, PM853_LDO11_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG1, PM853_LDO11_EN_MSK,
        pm853_ldo_ranges3),

    PM853_DESC(PM853_ID_LDO12, "LDO_REG12", "vcc_sys",
        16, PM853_LDO12_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO12_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO13, "LDO_REG13", "vcc_sys",
        16, PM853_LDO13_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO13_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO14, "LDO_REG14", "vcc_sys",
        16, PM853_LDO14_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO14_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO15, "LDO_REG15", "dcdc2",
        16, PM853_LDO15_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO15_EN_MSK,
        pm853_ldo_ranges3),

    PM853_DESC(PM853_ID_LDO16, "LDO_REG16", "vcc_sys",
        16, PM853_LDO16_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO16_EN_MSK,
        pm853_ldo_ranges1),

    PM853_DESC(PM853_ID_LDO17, "LDO_REG17", "dcdc5",
        8, PM853_LDO17_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO17_EN_MSK,
        pm853_ldo_ranges4),

    PM853_DESC(PM853_ID_LDO18, "LDO_REG18", "dcdc2",
        16, PM853_LDO18_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO18_EN_MSK,
        pm853_ldo_ranges3),

    PM853_DESC(PM853_ID_LDO19, "LDO_REG19", "dcdc5",
        8, PM853_LDO19_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG2, PM853_LDO19_EN_MSK,
        pm853_ldo_ranges4),

    PM853_DESC(PM853_ID_LDO20, "LDO_REG20", "dcdc5",
        8, PM853_LDO20_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG3, PM853_LDO20_EN_MSK,
        pm853_ldo_ranges4),

    PM853_DESC(PM853_ID_LDO21, "LDO_REG21", "dcdc2",
        16, PM853_LDO21_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG3, PM853_LDO21_EN_MSK,
        pm853_ldo_ranges3),

    PM853_DESC(PM853_ID_LDO22, "LDO_REG22", "dcdc5",
        8, PM853_LDO22_VSEL_REG, PM853_LDO_VSEL_MSK,
        PM853_LDO_BUCK_EN_REG3, PM853_LDO22_EN_MSK,
        pm853_ldo_ranges4),

    /* PWR SWITCH */
    PM853_DESC_SWITCH(PM853_ID_LDO5_SW, "SWITCH_REG1", "vcc_sys",
        PM853_LDO_BUCK_EN_REG3, PM853_SW_EN_MSK),
};

static struct spacemit_pmic_regulator_data pm853_regulator_data =
{
    .desc = pm853_reg,
    .desc_nr = RT_ARRAY_SIZE(pm853_reg),
};
#endif /* __SPACEMIT_REGULATOR_INTERNAL */

#ifdef __SPACEMIT_PMIC_INTERNAL
static struct spacemit_pmic_mfd_endpoint pm853_mfd_endpoint[] =
{
    {
        .ofw_name = "spacemit-regulator@pm853",
        .ofw_compatible = "pmic,regulator,pm853",
    },
};

static struct spacemit_pmic_mfd_data pm853_mfd_data =
{
    .regmap_cfg =
    {
        .reg_bits = 8,
        .val_bits = 8,
        .max_register = SPACEMIT_PM853_MAX_REG,
    },
    .endpoint = pm853_mfd_endpoint,
    .endpoint_num = RT_ARRAY_SIZE(pm853_mfd_endpoint),
};
#endif /* __SPACEMIT_PMIC_INTERNAL */

#endif /* __PM853_H__ */
