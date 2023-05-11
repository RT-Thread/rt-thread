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
 * FilePath: fxmac_sinit.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for the implementation of the xmac driver's static
 * initialization functionality.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac.h"
#include "fparameters.h"

extern const FXmacConfig fxmac_cfg_tbl[FXMAC_NUM];

const FXmacConfig *FXmacLookupConfig(u32 instance_id)
{
    const FXmacConfig *cfg_ptr = NULL;
    u32 index;
    for (index = 0; index < (u32)FXMAC_NUM; index++)
    {
        if (fxmac_cfg_tbl[index].instance_id == instance_id)
        {
            cfg_ptr = &fxmac_cfg_tbl[index];
            break;
        }
    }

    return (const FXmacConfig *)cfg_ptr;
}
