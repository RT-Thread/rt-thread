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
 * FilePath: fsemaphore_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:15
 * Description:  This file is for semaphore static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/23    init commit
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fsemaphore.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FSemaConfig fsema_cfg_tbl[FSEMA_INSTANCE_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FSemaLoopkupConfig
 * @msg: 获取Semaphore的默认配置
 * @return {const FSemaConfig *} Semaphore的默认配置
 * @param {u32} instance_id, Semaphore的实例id
 */
const FSemaConfig *FSemaLoopkupConfig(u32 instance_id)
{
    const FSemaConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FSEMA_INSTANCE_NUM; index++)
    {
        if (fsema_cfg_tbl[index].id == instance_id)
        {
            ptr = &fsema_cfg_tbl[index];
            break;
        }
    }

    return (const FSemaConfig *)ptr;
}