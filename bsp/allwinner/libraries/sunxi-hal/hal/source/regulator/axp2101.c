/*
 * Copyright (C) 2020 allwinnertech Ltd.
 */

#include <sunxi_hal_regulator.h>
#include <sunxi_hal_regulator_private.h>
#include <type.h>

#define AXP2101_DCDC_CFG0       (0x80)
#define AXP2101_DCDC1_CFG       (0x82)
#define AXP2101_DCDC2_CFG       (0x83)
#define AXP2101_DCDC3_CFG       (0x84)
#define AXP2101_DCDC4_CFG       (0x85)
#define AXP2101_DCDC5_CFG       (0x86)
#define AXP2101_LDO_EN_CFG0     (0x90)
#define AXP2101_LDO_EN_CFG1     (0x91)
#define AXP2101_ALDO1_CFG       (0x92)
#define AXP2101_ALDO2_CFG       (0x93)
#define AXP2101_ALDO3_CFG       (0x94)
#define AXP2101_ALDO4_CFG       (0x95)
#define AXP2101_BLDO1_CFG       (0x96)
#define AXP2101_BLDO2_CFG       (0x97)
#define AXP2101_CPUSLD_CFG      (0x98)
#define AXP2101_DLDO1_CFG       (0x99)
#define AXP2101_DLDO2_CFG       (0x9A)

static const struct regulator_linear_range axp2101_dcdc2_ranges[] = {
    REGULATOR_LINEAR_RANGE(500000, 0x0, 0x46, 10000),
    REGULATOR_LINEAR_RANGE(1220000, 0x47, 0x57, 20000),
};

static const struct regulator_linear_range axp2101_dcdc3_ranges[] = {
    REGULATOR_LINEAR_RANGE(500000, 0x0, 0x46, 10000),
    REGULATOR_LINEAR_RANGE(1220000, 0x47, 0x57, 20000),
    REGULATOR_LINEAR_RANGE(1600000, 0x58, 0x6a, 100000),
};

static const struct regulator_linear_range axp2101_dcdc4_ranges[] = {
    REGULATOR_LINEAR_RANGE(500000, 0x0, 0x46, 10000),
    REGULATOR_LINEAR_RANGE(1220000, 0x47, 0x66, 20000),
};

static const struct regulator_linear_range axp2101_dcdc5_ranges[] = {
    REGULATOR_LINEAR_RANGE(1400000, 0x0, 0x17, 100000),
    REGULATOR_LINEAR_RANGE(1200000, 0x19, 0x19, 0),
};

const struct regulator_desc axp2101_regulators[] = {
    AXP_DESC(1500, 3400, 100, AXP2101_DCDC1_CFG, 0x1f,
         AXP2101_DCDC_CFG0, BIT(0)),
    AXP_DESC_RANGES(axp2101_dcdc2_ranges, AXP2101_DCDC2_CFG, 0x7f,
            AXP2101_DCDC_CFG0, BIT(1)),
    AXP_DESC_RANGES(axp2101_dcdc3_ranges, AXP2101_DCDC3_CFG, 0x7f,
            AXP2101_DCDC_CFG0, BIT(2)),
    AXP_DESC_RANGES(axp2101_dcdc4_ranges, AXP2101_DCDC4_CFG, 0x7f,
            AXP2101_DCDC_CFG0, BIT(3)),
    AXP_DESC_RANGES(axp2101_dcdc5_ranges, AXP2101_DCDC5_CFG, 0x1f,
            AXP2101_DCDC_CFG0, BIT(4)),
    AXP_DESC(500, 3500, 100, AXP2101_ALDO1_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(0)),
    AXP_DESC(500, 3500, 100, AXP2101_ALDO2_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(1)),
    AXP_DESC(500, 3500, 100, AXP2101_ALDO3_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(2)),
    AXP_DESC(500, 3500, 100, AXP2101_ALDO4_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(3)),
    AXP_DESC(500, 3500, 100, AXP2101_BLDO1_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(4)),
    AXP_DESC(500, 3500, 100, AXP2101_BLDO2_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(5)),
    AXP_DESC(500, 3500, 100, AXP2101_DLDO1_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(7)),
    AXP_DESC(500, 1400, 50, AXP2101_DLDO2_CFG, 0x1f, AXP2101_LDO_EN_CFG1,
         BIT(0)),
    AXP_DESC(500, 1400, 50, AXP2101_CPUSLD_CFG, 0x1f, AXP2101_LDO_EN_CFG0,
         BIT(6)),
};
