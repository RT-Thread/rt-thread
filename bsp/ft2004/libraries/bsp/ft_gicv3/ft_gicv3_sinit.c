/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 16:28:25
 * @Description:  This files is for gic v2.0 static init
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_types.h"
#include "ft_assert.h"
#include "ft_parameters.h"
#include "ft_gicv3.h"

/************************** Variable Definitions *****************************/
extern FGicv3_Config_t g_FGicv3_Config_tTable[FT_GICV3_INSTANCES_NUM];

/**
 * @name: Ft_Gicv3_lookupConfig
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {u32} InstanceId
 */
FGicv3_Config_t *FGicv3_LookupConfig(u32 InstanceId)
{
    FGicv3_Config_t *Config = NULL;
    u32 Index = 0;

    for (Index = 0; Index < FT_GICV3_INSTANCES_NUM; Index++)
    {
        if (g_FGicv3_Config_tTable[Index].InstanceId == InstanceId)
        {
            Config = &g_FGicv3_Config_tTable[Index];
            break;
        }
    }

    return Config;
}
