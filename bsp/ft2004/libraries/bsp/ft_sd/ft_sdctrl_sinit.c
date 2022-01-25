/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-05-25 16:47:14
 * @Description:  This files is for sd ctrl static initialization
 *
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl.h"
#include "ft_parameters.h"

extern FSdCtrl_Config_t FSdCtrl_Config[FT_SDC_NUM];

FSdCtrl_Config_t *FSdCtrl_LookupConfig(u32 instanceId)
{
    FSdCtrl_Config_t *CfgPtr = NULL;
    u32 Index;
    for (Index = 0; Index < (u32)FT_GMAC_INSTANCES_NUM; Index++)
    {
        if (FSdCtrl_Config[Index].instanceId == instanceId)
        {
            CfgPtr = &FSdCtrl_Config[Index];
            break;
        }
    }

    return (FSdCtrl_Config_t *)CfgPtr;
}
