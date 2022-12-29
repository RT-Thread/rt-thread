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

#if defined(BSP_USING_SSMCC)

#include "drv_common.h"

rt_err_t nu_ssmcc_init(void)
{
    CLK->APBCLK2 |= CLK_APBCLK2_SSMCCEN_Msk;

    /* set region 0 to secure region, non-secure and m4 all can access */
    SSMCC_SetRegion0(SSMCC_SECURE_READ | SSMCC_SECURE_WRITE | SSMCC_NONSECURE_READ | SSMCC_NONSECURE_WRITE | SSMCC_M4NS_READ | SSMCC_M4NS_WRITE);

    return RT_EOK;
}

#endif //#if defined(BSP_USING_SSMCC)
