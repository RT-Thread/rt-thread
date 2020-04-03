/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/03/26     Huaqi        Nuclei RISC-V Core porting code.
 */

#ifndef __CPUPORT_H__
#define __CPUPORT_H__

#include <rtconfig.h>
#include <nuclei_sdk_soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Scheduler utilities. */
#define portYIELD() 															\
{																				\
	/* Set a software interrupt(SWI) request to request a context switch. */    \
	SysTimer_SetSWIRQ();                                                        \
	/* Barriers are normally not required but do ensure the code is completely	\
	within the specified behaviour for the architecture. */						\
	__RWMB();										                            \
	__FENCE_I();										                        \
}


#ifdef __cplusplus
}
#endif

#endif
