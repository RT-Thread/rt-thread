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
 * FilePath: fooxx.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


/***************************** Include Files *********************************/

#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "foox_hw.h"
#include "fooxx.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/* 此文件主要为了完成用户对外接口，用户可以使用这些接口直接开始工作 */

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */

/**
 * @name: FooxxCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {Fooxx} *instance_p is a pointer to the driver instance.
 * @param {FooxxConfig} *config_p is a reference to a structure containing information
 *                      about a specific driver.
 * @return SUCCESS if initialization was successful
 *         ERROR
 */
FError FooxxCfgInitialize(Fooxx *instance_p, FooxxConfig *config_p)
{

}

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */