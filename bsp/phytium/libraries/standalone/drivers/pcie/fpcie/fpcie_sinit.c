/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 08:59:22
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "fpcie.h"
#include "fparameters.h"

extern FPcieConfig FPcieConfigTable[FT_PCIE_NUM];


FPcieConfig *FPcieLookupConfig(u32 instance_id)
{
    FPcieConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FT_PCIE_NUM; index++)
    {
        if (FPcieConfigTable[index].instance_id == instance_id)
        {
            ptr = &FPcieConfigTable[index];
            break;
        }
    }

    return (FPcieConfig *)ptr;
}
