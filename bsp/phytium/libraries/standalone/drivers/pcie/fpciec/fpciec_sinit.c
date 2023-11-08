/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
 * All Rights Reserved.
 * 
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 * 
 * 
 * FilePath: fpcie_c_sinit.c
 * Created Date: 2023-08-02 09:40:22
 * Last Modified: 2023-08-02 13:25:16
 * Description:  This file is for pciec configuration table
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */


#include "fpciec.h"
#include "fparameters.h"

extern FPcieCConfig FPcieCConfigTable[FPCIEC_INSTANCE_NUM];

/**
 * @name: FPcieCLookupConfig
 * @msg: Looks up and retrieves the configuration structure for a specific instance ID.
 * @param {u32} instance_id - The instance ID for which to retrieve the configuration.
 * @return {FPcieCConfig *} - Returns a pointer to the configuration structure, or NULL if not found.
 */
FPcieCConfig *FPcieCLookupConfig(u32 instance_id)
{
    FPcieCConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FPCIEC_INSTANCE_NUM; index++)
    {
        if (FPcieCConfigTable[index].instance_id == instance_id)
        {
            ptr = &FPcieCConfigTable[index];
            break;
        }
    }

    return (FPcieCConfig *)ptr;
}

