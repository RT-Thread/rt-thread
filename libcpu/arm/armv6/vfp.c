/*
 * File      : vfp.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-07     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "vfp.h"

#ifdef RT_USING_VFP

rt_uint32_t vfpregs_offset = offsetof(struct rt_thread, vfpregs);

struct vfp_context *last_vfp_context = RT_NULL;

int vfp_switch(rt_uint32_t cmd, struct rt_thread *thread)
{
	rt_uint32_t fpexc;
	//rt_kprintf("%s:%d, %x\n", __func__, cmd, thread);

	switch (cmd) {
		case THREAD_INIT:
		{
			struct vfp_context *vfp = &thread->vfpregs;

			rt_memset(vfp, 0, sizeof(struct vfp_context));
			vfp->fpexc = FPEXC_EN;
			vfp->fpscr = FPSCR_RN;

			if (last_vfp_context == vfp)
				last_vfp_context = RT_NULL;
			vmsr(FPEXC, vmrs(FPEXC) & ~FPEXC_EN);
			break;
		}
		case THREAD_EXIT:
		{
				/* release case: Per-thread VFP cleanup. */
			struct vfp_context *vfp = &thread->vfpregs;

			if (last_vfp_context == vfp)
				last_vfp_context = RT_NULL;
			break;
		}
		default:
			break;
	}

	return 0;
}

int vfp_thread_init(struct rt_thread *thread)
{
	return vfp_switch(THREAD_INIT, thread);
}


int vfp_thread_exit(struct rt_thread *thread)
{
	return vfp_switch(THREAD_EXIT, thread);
}

rt_uint32_t read_vfp_regs(rt_uint32_t *buf)
{
	rt_uint32_t value;
	rt_uint32_t length;
	asm  volatile ("vldmia  %0!, {d0-d15}"
			:
			:"r"(buf)
			:"cc");
	length = 32;
#ifdef RT_USING_VFPv3
	asm  volatile ("vmrs  %0, mvfr0"
			:"=r"(value)
			:);
	if ((value & MVFR0_A_SIMD_MASK) == 2)
	{
		asm  volatile ("vldmia  %0!, {d16-d31}"
				:
				:"r"(buf)
				:"cc");
		length = 64;
	}
	else
	{
		length = 32;
	}
#endif

	return length;
}

void vfp_exception(rt_uint32_t instruction, rt_uint32_t fpexc)
{
	int i = 0;
	int length = 0;
	rt_uint32_t fpscr, fpsid;
#ifdef RT_USING_VFPv3
	unsigned long long vfp_regs[32];
#else
	unsigned long long vfp_regs[16];
#endif

	rt_kprintf("VFP: exception: instruction %08x fpexc %08x\n", instruction, fpexc);
	fpsid = vmrs(FPSID);
	fpscr = vmrs(FPSCR);
	rt_kprintf("VFP: exception: fpsid %08x fpscr %08x\n", fpsid, fpscr);

	length = read_vfp_regs((rt_uint32_t *)vfp_regs);
	rt_kprintf("VFP: exception registers: {s0~s%d}\n", length - 1);
	for(i = 0; i < length; i++)
	{
		if (i && !(i & 0x3))
			rt_kprintf("\n");
		rt_kprintf("0x%08x ", ((rt_uint32_t *)vfp_regs)[i]);
	}
	rt_kprintf("\n");
	
}

void vfp_init(void)
{
	int ret = 0;
	unsigned int value;
	asm  volatile ("mrc p15, 0, %0, c1, c0, 2"
			:"=r"(value)
			:);
	value |= 0xf00000;/*enable CP10, CP11 user access*/
	asm volatile("mcr p15, 0, %0, c1, c0, 2"
			:
			:"r"(value));
#if 0
	asm volatile("fmrx %0, fpexc"
			:"=r"(value));
	value |=(1<<30);
	asm volatile("fmxr fpexc, %0"
			:
			:"r"(value));
#endif
}


#endif
