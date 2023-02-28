/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-20      Wayne        First version
*
******************************************************************************/

#include "rtthread.h"

#if defined(BSP_USING_SSPCC)

#include "drv_common.h"

rt_err_t nu_sspcc_init(void)
{
    int i, j;

    /* Enable SSPCC clock. */
    CLK->APBCLK2 |= CLK_APBCLK2_SSPCCEN_Msk;

    /* Assign all SRAM1 capacity to TZNS. */
    SSPCC->SRAMSB = 0;

    /* Set all GPIO security set to TZNS. */
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 14; j++)
        {
            SSPCC_SetRealm_GPIO(GPIO_BASE + (j * 0x40), i, SSPCC_SSET_TZNS);
        }
    }

    return RT_EOK;
}

#endif //#if defined(BSP_USING_SSPCC)
