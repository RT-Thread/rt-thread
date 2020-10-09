/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-31     luhuadong    first version
 */

#include <board.h>

void phy_reset(void)
{
    /*
     * The PHY reset pin of DISCO-F769NI is connected to the MCU reset pin,
     * so no additional reset is required.
     */
    
    return ;
}
