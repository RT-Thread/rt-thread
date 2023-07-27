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
 * FilePath: fsmp.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-17 17:58:14
 * Description:  This files is for a way to provide spinlocks for multicore operations
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * v1.1   carl      2022-12-30   add init function
 * v1.2   cark      2023-02-28   Use GCC built-in functions to implement spinlock 
 */

#if 0

#include "fsmp.h"
#include "sdkconfig.h"
#include "ftypes.h"
#include "fatomic.h"


typedef struct  
{
	int v;
}FCpuLock;


#ifdef CONFIG_SPIN_MEM
    FCpuLock *_lock = (FCpuLock *)CONFIG_SPIN_MEM;
#else
    FCpuLock _static_lock ;
    FCpuLock *_lock = &_static_lock ;
#endif


void SpinUnlock(void)
{
    FATOMIC_UNLOCK(_lock->v);
}

void SpinLock(void)
{

    while(FATOMIC_LOCK(_lock->v,1))
    {

    }
   
}

void SpinInit(void)
{
    FATOMIC_UNLOCK(_lock->v);
}

#endif