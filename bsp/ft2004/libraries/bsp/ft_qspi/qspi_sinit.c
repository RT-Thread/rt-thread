/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 13:22:01
 * @LastEditTime: 2021-04-07 13:22:01
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_qspi.h"
#include "ft_parameters.h"

extern FQSpi_Config_t FqSpi_ConfigTable[FT_QSPI_NUM];

FQSpi_Config_t *FQSpi_LookupConfig(u32 instanceId)
{
    FQSpi_Config_t *pFQSpi_Config_t = NULL;

    u32 Index;
    for (Index = 0; Index < (u32)FT_GMAC_INSTANCES_NUM; Index++)
    {
        if (FqSpi_ConfigTable[Index].instanceId == instanceId)
        {
            pFQSpi_Config_t = &FqSpi_ConfigTable[Index];
            break;
        }
    }

    return pFQSpi_Config_t;
}
