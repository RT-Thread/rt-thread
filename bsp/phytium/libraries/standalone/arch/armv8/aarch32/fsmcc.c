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
 * Created Date: 2023-06-16 11:30:41
 * Last Modified: 2023-06-30 13:19:25
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0      huanghe   2023-06-16        first init
 */


#include "fsmcc.h"
#include "ftypes.h"


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
    register unsigned long r0 asm("r0") = arg0;
    register unsigned long r1 asm("r1") = arg1;
    register unsigned long r2 asm("r2") = arg2;
    register unsigned long r3 asm("r3") = arg3;
    register unsigned long r4 asm("r4") = arg4;
    register unsigned long r5 asm("r5") = arg5;
    register unsigned long r6 asm("r6") = arg6;
    register unsigned long r7 asm("r7") = arg7;

    asm volatile(
        "hvc #0\n"
        : "+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3),
          "+r"(r4), "+r"(r5), "+r"(r6), "+r"(r7)
        :
        : "memory");

    res->a0 = r0;
    res->a1 = r1;
    res->a2 = r2;
    res->a3 = r3;
}


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
    register unsigned long r0 asm("r0") = arg0;
    register unsigned long r1 asm("r1") = arg1;
    register unsigned long r2 asm("r2") = arg2;
    register unsigned long r3 asm("r3") = arg3;
    register unsigned long r4 asm("r4") = arg4;
    register unsigned long r5 asm("r5") = arg5;
    register unsigned long r6 asm("r6") = arg6;
    register unsigned long r7 asm("r7") = arg7;

    asm volatile(
        "smc #0\n"
        : "+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3),
          "+r"(r4), "+r"(r5), "+r"(r6), "+r"(r7)
        :
        : "memory");

    res->a0 = r0;
    res->a1 = r1;
    res->a2 = r2;
    res->a3 = r3;
}

