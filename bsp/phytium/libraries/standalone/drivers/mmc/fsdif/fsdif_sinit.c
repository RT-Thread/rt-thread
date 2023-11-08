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
 * FilePath: fsdif_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:48:41
 * Description:  This file is for static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fsdif.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FSdifConfig FSDIF_CONFIG_TBL[FSDIF_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FSdifLookupConfig
 * @msg: Get the device instance default configure
 * @return {const FSdifConfig *} default configure
 * @param {u32} instance_id
 */
const FSdifConfig *FSdifLookupConfig(u32 instance_id)
{
    const FSdifConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FSDIF_NUM; index++)
    {
        if (FSDIF_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FSDIF_CONFIG_TBL[index];
            break;
        }
    }

    return (const FSdifConfig *)ptr;
}