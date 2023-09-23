/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fsmcc.c
 * Created Date: 2023-06-19 11:12:23
 * Last Modified: 2023-06-30 13:17:16
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */

#include "fsmcc.h"
#include "ftypes.h"



/**
@name: FSmcccSmcCall
@msg: 执行SMC（Secure Monitor Call）指令。
@param {unsigned long} arg0: 第一个参数传递给SMC调用。
@param {unsigned long} arg1: 第二个参数传递给SMC调用。
@param {unsigned long} arg2: 第三个参数传递给SMC调用。
@param {unsigned long} arg3: 第四个参数传递给SMC调用。
@param {unsigned long} arg4: 第五个参数传递给SMC调用。
@param {unsigned long} arg5: 第六个参数传递给SMC调用。
@param {unsigned long} arg6: 第七个参数传递给SMC调用。
@param {unsigned long} arg7: 第八个参数传递给SMC调用。
@param {struct FSmcccRes*} res: 结构体指针，用于保存SMC调用的结果。
@note: 此函数执行SMC（Secure Monitor Call）指令，并将结果保存在提供的结构体指针中。
*/
void FSmcccSmcCall(unsigned long arg0, unsigned long arg1,
                                   unsigned long arg2, unsigned long arg3,
                                   unsigned long arg4, unsigned long arg5,
                                   unsigned long arg6, unsigned long arg7,
                                   struct FSmcccRes *res)
{
    register unsigned long x0 asm("x0") = arg0;
    register unsigned long x1 asm("x1") = arg1;
    register unsigned long x2 asm("x2") = arg2;
    register unsigned long x3 asm("x3") = arg3;
    register unsigned long x4 asm("x4") = arg4;
    register unsigned long x5 asm("x5") = arg5;
    register unsigned long x6 asm("x6") = arg6;
    register unsigned long x7 asm("x7") = arg7;

    asm volatile(
        "smc #0\n"
        : "+r"(x0), "+r"(x1), "+r"(x2), "+r"(x3),
          "+r"(x4), "+r"(x5), "+r"(x6), "+r"(x7)
        :
        : "memory");

    res->a0 = x0;
    res->a1 = x1;
    res->a2 = x2;
    res->a3 = x3;
}

/**
@name: FSmcccHvcCall
@msg: 执行HVC（虚拟化监管CALL）指令。
@param {unsigned long} arg0: 第一个参数传递给HVC调用。
@param {unsigned long} arg1: 第二个参数传递给HVC调用。
@param {unsigned long} arg2: 第三个参数传递给HVC调用。
@param {unsigned long} arg3: 第四个参数传递给HVC调用。
@param {unsigned long} arg4: 第五个参数传递给HVC调用。
@param {unsigned long} arg5: 第六个参数传递给HVC调用。
@param {unsigned long} arg6: 第七个参数传递给HVC调用。
@param {unsigned long} arg7: 第八个参数传递给HVC调用。
@param {struct FSmcccRes*} res: 结构体指针，用于保存HVC调用的结果。
@note: 此函数执行SMC（虚拟化监管CALL）指令，并将结果保存在提供的结构体指针中。
*/
void FSmcccHvcCall(unsigned long arg0, unsigned long arg1,
                                   unsigned long arg2, unsigned long arg3,
                                   unsigned long arg4, unsigned long arg5,
                                   unsigned long arg6, unsigned long arg7,
                                   struct FSmcccRes *res)
{
    register unsigned long x0 asm("x0") = arg0;
    register unsigned long x1 asm("x1") = arg1;
    register unsigned long x2 asm("x2") = arg2;
    register unsigned long x3 asm("x3") = arg3;
    register unsigned long x4 asm("x4") = arg4;
    register unsigned long x5 asm("x5") = arg5;
    register unsigned long x6 asm("x6") = arg6;
    register unsigned long x7 asm("x7") = arg7;

    asm volatile(
        "hvc #0\n"
        : "+r"(x0), "+r"(x1), "+r"(x2), "+r"(x3),
          "+r"(x4), "+r"(x5), "+r"(x6), "+r"(x7)
        :
        : "memory");

    res->a0 = x0;
    res->a1 = x1;
    res->a2 = x2;
    res->a3 = x3;
}

