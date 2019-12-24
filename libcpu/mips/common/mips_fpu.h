/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef _MIPS_FPU_H_
#define _MIPS_FPU_H_

#ifndef __ASSEMBLY__

#include <mips_regs.h>
/**
 * init hardware FPU
 */
#ifdef RT_USING_FPU
inline void rt_hw_fpu_init(void)
{
    rt_uint32_t c0_status = 0;
    rt_uint32_t c1_status = 0;

    /* Enable CU1 */
    c0_status = read_c0_status();
    c0_status |= (ST0_CU1 | ST0_FR);
    write_c0_status(c0_status);

    /* FCSR Configs */
    c1_status = read_c1_status();
    c1_status |= (FPU_CSR_FS | FPU_CSR_FO | FPU_CSR_FN);    /* Set FS, FO, FN */
    c1_status &= ~(FPU_CSR_ALL_E);                          /* Disable exception */
    c1_status = (c1_status & (~FPU_CSR_RM)) | FPU_CSR_RN;   /* Set RN */
    write_c1_status(c1_status);

    return ;
}
#else
    inline void rt_hw_fpu_init(void){} /* Do nothing */
#endif

#endif

#endif
