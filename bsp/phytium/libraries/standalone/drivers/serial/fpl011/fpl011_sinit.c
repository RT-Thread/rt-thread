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
 * FilePath: fpl011_sinit.c
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:07:00
 * Description:  This file is for uart static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  add file head 
 */

/***************************** Include Files *********************************/

#include "fpl011.h"
#include "fparameters.h"
#include "sdkconfig.h"

extern FPl011Config FPl011ConfigTable[FUART_NUM];
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
 * @name: FPl011LookupConfig
 * @msg:  Initializes a specific FPl011 instance such that it is ready to be used.
 * @param  contains the ID of the device
 * @return {FPl011Config *}  A pointer to the configuration structure or NULL if the
 *      specified device is not in the system.
 */
const FPl011Config *FPl011LookupConfig(u32 instance_id)
{
    const FPl011Config *cfg_ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FUART_NUM; index++)
    {
        if (FPl011ConfigTable[index].instance_id == instance_id)
        {
            cfg_ptr = &FPl011ConfigTable[index];
            break;
        }
    }

    return (const FPl011Config *)cfg_ptr;
}
