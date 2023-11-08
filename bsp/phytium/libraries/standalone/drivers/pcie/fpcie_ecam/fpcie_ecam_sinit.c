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
 * FilePath: fpcie_sinit.c
 * Created Date: 2023-08-01 09:08:08
 * Last Modified: 2023-08-07 08:58:42
 * Description:  This file is for pcie ecam configuration table
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */


#include "fpcie_ecam.h"
#include "fparameters.h"

extern FPcieEcamConfig FPcieEcamConfigTable[FPCIE_ECAM_INSTANCE_NUM];


FPcieEcamConfig *FPcieEcamLookupConfig(u32 instance_id)
{
    FPcieEcamConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FPCIE_ECAM_INSTANCE_NUM; index++)
    {
        if (FPcieEcamConfigTable[index].instance_id == instance_id)
        {
            ptr = &FPcieEcamConfigTable[index];
            break;
        }
    }

    return (FPcieEcamConfig *)ptr;
}
