/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-18 13:43:09
 * @Description:  This files is for type definition
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_types.h"
#include "ft_assert.h"

/************* 全局变量 用于判断驱动是否出现断言 *****************/
u32 Ft_assertStatus;

/************** 断言是否需要无限等待，1 等待，0不等待  ******************/
s32 Ft_assertWait = 1;

/* 当断言发生时，将会调用此函数 */
static Ft_assertCallback Ft_assertCallbackRoutine = NULL;

/************************** Function Prototypes ******************************/
void Ft_assert(FT_IN char *File, s32 Line)
{
    if (Ft_assertCallbackRoutine != NULL)
    {
        Ft_assertCallbackRoutine(File, Line);
    }

    while (Ft_assertWait != 0)
    {
    }
}

void Ft_assertSetCallBack(Ft_assertCallback Routine)
{
    Ft_assertCallbackRoutine = Routine;
}
