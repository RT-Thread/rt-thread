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
 * FilePath: fassert.c
 * Date: 2021-04-07 09:53:07
 * LastEditTime: 2022-02-17 18:04:28
 * Description:  This file is for assertion implmentation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/4/5       init commit
 * 1.1   zhugengyu  2022/3/7       re-define assert macro
 */

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "fassert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
typedef struct
{
    u32 status; /* 当前断言状态 */
    FAssertCB cb; /* 断言回调函数 */
} FAssertInfo; /* 断言实例类型 */

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
static void FAssertCallback(const char *file, s32 line, int ret);

/************************** Variable Definitions *****************************/
static FAssertInfo assert_info =
{
    .status = FASSERT_NONE,
    .cb     = FAssertCallback
}; /* 断言实例 */

/*****************************************************************************/
/**
 * @name: FAssertSetStatus
 * @msg: 设置断言状态
 * @return {*}
 * @param {FAssertStatus} status, 断言状态
 */
void FAssertSetStatus(FAssertStatus status)
{
    assert_info.status = status;
}

/**
 * @name: FAssertGetStatus
 * @msg: 获取当前断言状态
 * @return {FAssertStatus} 当前断言状态
 */
FAssertStatus FAssertGetStatus(void)
{
    return assert_info.status;
}

/**
 * @name: FAssertCallback
 * @msg: 默认的断言回调函数
 * @return {*}
 * @param {char} *file, 断言发生的源文件
 * @param {s32} line, 断言发生的源文件行号
 * @param {int} ret, 保留给Non-block断言使用
 */
static void FAssertCallback(const char *file, s32 line, int ret)
{
    f_printk("Assert Error at %s : %ld \r\n", file, line);
}

/**
 * @name: FAssertSetCB
 * @msg: 设置断言回调函数
 * @return {*}
 * @param {FAssertCB} cb, 断言回调函数
 */
void FAssertSetCB(FAssertCB cb)
{
    if (NULL != cb)
    {
        assert_info.cb = cb;
    }
}

/**
 * @name: FAssert
 * @msg: 断言实现
 * @return {*}
 * @param {char} *file, 断言发生的源文件
 * @param {s32} line, 断言发生的源文件行号
 * @param {int} code, 断言发生的退出码，保留给Non-block断言使用
 */
void FAssert(const char *file, s32 line, int code)
{
    if (NULL != assert_info.cb)
    {
        /* 如果要实现Non-block断言，需要在回调中返回 */
        assert_info.cb(file, line, code);
    }

    while (TRUE)
    {
        ;
    }
}