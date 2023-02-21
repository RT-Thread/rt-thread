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

#if defined(BSP_USING_UMCTL2)

#include "drv_common.h"

rt_err_t nu_umctl2_init(void)
{
    UMCTL2->PCTRL_0 = UMCTL2_PCTRL_0_port_en_Msk;  //[0x0490]
    UMCTL2->PCTRL_1 = UMCTL2_PCTRL_1_port_en_Msk;  //[0x0540]
    UMCTL2->PCTRL_2 = UMCTL2_PCTRL_2_port_en_Msk;  //[0x05f0]
    UMCTL2->PCTRL_3 = UMCTL2_PCTRL_3_port_en_Msk;  //[0x06a0]

    UMCTL2->PCTRL_4 = UMCTL2_PCTRL_4_port_en_Msk;  //[0x0750]
    UMCTL2->PCTRL_5 = UMCTL2_PCTRL_5_port_en_Msk;  //[0x0800]
    UMCTL2->PCTRL_6 = UMCTL2_PCTRL_6_port_en_Msk;  //[0x08b0]
    UMCTL2->PCTRL_7 = UMCTL2_PCTRL_7_port_en_Msk;  //[0x0960]

    return RT_EOK;
}

#endif //#if defined(BSP_USING_UMCTL2)
