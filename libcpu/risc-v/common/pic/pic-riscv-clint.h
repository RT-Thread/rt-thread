/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PIC_RISCV_CLINT_H__
#define __PIC_RISCV_CLINT_H__

#include <rtthread.h>

extern rt_uint32_t *riscv_aclint_ipi_base;

void clint_send_ipi(int cpu);
void clint_clear_ipi(void);

#ifndef PIC_DISABLE_DM
rt_err_t riscv_clint_ofw_init(void);
#endif

#endif /* __PIC_RISCV_CLINT_H__ */
