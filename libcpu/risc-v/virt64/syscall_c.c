/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-03     lizhirui     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_LEVEL DBG_WARNING
//#define DBG_LEVEL DBG_INFO
#include <rtdbg.h>

#include <stdint.h>
#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>

#include <stdio.h>

#include "riscv_mmu.h"
#include "stack.h"

typedef rt_size_t (*syscallfunc_t)(rt_size_t,rt_size_t,rt_size_t,rt_size_t,rt_size_t,rt_size_t,rt_size_t);
syscallfunc_t lwp_get_sys_api(uint32_t);

void syscall_handler(struct rt_hw_stack_frame *regs)
{
    if(regs -> a7 == 0)
    {
        rt_kprintf("syscall id = 0!\n");
        while(1);
    }

    if(regs -> a7 == 0xdeadbeef)
    {
        rt_kprintf("syscall id = 0xdeadbeef\n");
        while(1);
    }

	syscallfunc_t syscallfunc = (syscallfunc_t)lwp_get_sys_api(regs -> a7);
	
	if(syscallfunc == RT_NULL)
	{
		rt_kprintf("unsupported syscall!\n");
        while(1);
	}

    LOG_I("\033[36msyscall id = %d,arg0 = 0x%p,arg1 = 0x%p,arg2 = 0x%p,arg3 = 0x%p,arg4 = 0x%p,arg5 = 0x%p,arg6 = 0x%p\n\033[37m",regs -> a7,regs -> a0,regs -> a1,regs -> a2,regs -> a3,regs -> a4,regs -> a5,regs -> a6);
    regs -> a0 = syscallfunc(regs -> a0,regs -> a1,regs -> a2,regs -> a3,regs -> a4,regs -> a5,regs -> a6);
	regs -> a7 = 0;
	regs -> epc += 4;//skip ecall instruction
    LOG_I("\033[36msyscall deal ok,ret = 0x%p\n\033[37m",regs -> a0);
}