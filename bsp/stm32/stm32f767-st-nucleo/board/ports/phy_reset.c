/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-27     luhuadong    first version
 */

#include <board.h>

void phy_reset(void)
{
    /*
     * The PHY reset pin of NUCLEO-F767ZI is connected to the MCU reset pin,
     * so no additional reset is required.
     */

    return ;
}
