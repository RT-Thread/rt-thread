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
 * FilePath: foox_role.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:03
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


/*
    - 一些驱动模块，直接操作硬件的I/O接口，无法实现有意义的操作，此时需要针对中间件或者用户使用习惯设计此模块 （i2c,nand,eth）
    - 部分场景适用, 分角色的 I/O 操作
    - 此模块的函数原型，在fooxx.h 中声明一次，方便用户或者中间件层调用

*/


/***************************** Include Files *********************************/

#include "fio.h"
#include "foox_hw.h"
#include "fooxx.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/

