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
 * FilePath: fsmcc.h
 * Created Date: 2023-06-16 11:30:49
 * Last Modified: 2023-06-16 15:47:29
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0      huanghe   2023-06-16        first init
 */
#ifndef ARCH_ARMV8_AARCH32_SMCC_H
#define ARCH_ARMV8_AARCH32_SMCC_H



#ifdef __cplusplus
extern "C"
{
#endif
#include "ftypes.h"

struct FSmcccRes {
    unsigned long a0;
    unsigned long a1;
    unsigned long a2;
    unsigned long a3;
};


void FSmcccHvcCall(unsigned long arg0, unsigned long arg1,
                                   unsigned long arg2, unsigned long arg3,
                                   unsigned long arg4, unsigned long arg5,
                                   unsigned long arg6, unsigned long arg7,
                                   struct FSmcccRes *res) ;



void FSmcccSmcCall(unsigned long arg0, unsigned long arg1,
                                   unsigned long arg2, unsigned long arg3,
                                   unsigned long arg4, unsigned long arg5,
                                   unsigned long arg6, unsigned long arg7,
                                   struct FSmcccRes *res) ;

void FSmcccSmcGetSocIdCall(struct FSmcccRes *res) ;

#ifdef __cplusplus
}
#endif

#endif // !FT_SMC_H
