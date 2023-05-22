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
 * FilePath: fooxx_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:15
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */



/* - This file contains the implementation of driver's static initialization functionality.
- 驱动静态初始化  */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fooxx.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FooxxConfig FOOXX_CONFIG_TBL[NUM];

/************************** Function Prototypes ******************************/
const FooxxConfig *FooxxLookupConfig(u32 instance_id)
{
    const FooxxConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)NUM; index++)
    {
        if (FOOXX_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FOOXX_CONFIG_TBL[index];
            break;
        }
    }

    return (const FooxxConfig *)ptr;
}