/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fnand_id.h
 * Date: 2022-07-06 14:19:15
 * LastEditTime: 2022-07-06 14:19:15
 * Description:  This file is for functions in this file are the read id required functions
 * for this driver. 
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#ifndef FNAND_ID_H
#define FNAND_ID_H


#include "ftypes.h"
#include "fnand.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct FNandManuFacturerOps
{
    FError(*detect)(FNand *instance_p, FNandId *id_p, u32 chip_addr); /* detect chip */
    int (*init)(FNand *instance_p, u32 chip_addr);
    void (*cleanup)(FNand *instance_p, u32 chip_addr);
};


typedef struct
{
    int id;
    char *name;
    const struct FNandManuFacturerOps *ops;
} FNandManuFacturer;

FError FNandDetect(FNand *instance_p);

#ifdef __cplusplus
}
#endif

#endif
