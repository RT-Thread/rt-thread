/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:43:06
 * @Description:  This files is for gmac static init
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac.h"
#include "ft_parameters.h"

extern FGmac_Config_t Gmac_ConfigTable[FT_GMAC_INSTANCES_NUM];

FGmac_Config_t *Ft_Gmac_LookupConfig(u32 InstanceId)
{
    FGmac_Config_t *CfgPtr = NULL;
    u32 Index;
    for (Index = 0; Index < (u32)FT_GMAC_INSTANCES_NUM; Index++)
    {
        if (Gmac_ConfigTable[Index].InstanceId == InstanceId)
        {
            CfgPtr = &Gmac_ConfigTable[Index];
            break;
        }
    }

    return (FGmac_Config_t *)CfgPtr;
}
