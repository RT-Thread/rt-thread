/*
 * Copyright (C) 2020 allwinnertech Ltd.
 */

#include <sunxi_hal_regulator.h>
#include <sunxi_hal_regulator_private.h>
extern struct regulator_ops axp_regulator_ops;

#define REGULATOR_PMU_ADDR 0x34
#define REGULATOR_TWI_PORT 4

int hal_regulator_get(unsigned int request_flag, struct regulator_dev *rdev)
{
    int rc;

    rdev->flag = request_flag;

    switch (REGULATOR_TYPE(rdev->flag)) {
    case AXP2101_REGULATOR:
        rdev->flag |= (REGULATOR_PMU_ADDR << AXP_ADDR_SHIFT) |
                  (REGULATOR_TWI_PORT << TWI_PORT_SHIFT);
        rdev->private = (void *)axp2101_regulators;
        rdev->ops = &axp_regulator_ops;
        hal_axp_twi_init(rdev);
        break;
    default:
        goto out;
    }

    return 0;

out:
    return -1;
}
