/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#include "sdhci.h"

int mmc_regulator_get_supply(struct mmc_host *mmc)
{
    mmc->supply.vmmc  = -RT_NULL;
    mmc->supply.vqmmc = -RT_NULL;

    return 0;
}
int regulator_get_current_limit(struct regulator *regulator)
{
    return 0;
}

int regulator_is_supported_voltage(struct regulator *regulator,

                                   int min_uV, int max_uV)
{
    return 0;
}

int regulator_enable(struct regulator *regulator)
{
    return 0;
}
void regulator_disable(struct regulator *regulator)
{
}
