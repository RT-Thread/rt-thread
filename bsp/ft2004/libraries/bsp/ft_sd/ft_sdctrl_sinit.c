/*
 * @ : Copyright (c) 2020 Phytium Information Technology(TianJin), Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-19 17:05:14
 * @Description:  This files is for sd ctrl static initialization
 * 
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl.h"
#include "ft_parameters.h"

extern FSdCtrl_Config_t FSdCtrl_Config[FT_SDC_NUM];

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {u32} instanceId
 */
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
