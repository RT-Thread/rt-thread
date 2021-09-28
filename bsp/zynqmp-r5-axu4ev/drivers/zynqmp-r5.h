/*
 * Copyright (c) 2020-2021, WangHuachen
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-30     WangHuachen  the first version
 */
#ifndef __ZYNQMP_R5_H__
#define __ZYNQMP_R5_H__

#include "xparameters.h"

#define __REG64(x)  (*((volatile rt_uint64_t *)(x)))
#define __REG32(x)  (*((volatile rt_uint32_t *)(x)))
#define __REG16(x)  (*((volatile rt_uint16_t *)(x)))
#define __REG8(x)  (*((volatile rt_uint8_t *)(x)))

#define ZynqMP_CRL_APB_BASEADDR        XPAR_PSU_CRL_APB_S_AXI_BASEADDR
#define ZynqMP_CRL_APB_IOPLL_CTRL       0x020
#define ZynqMP_CRL_APB_IOPLL_CFG       0x024
#define ZynqMP_CRL_APB_UART0_REF_CTRL  0x074
#define ZynqMP_CRL_APB_UART1_REF_CTRL  0x078
#define ZynqMP_CRL_APB_LPD_LSBUS_CTRL  0x0AC
#define ZynqMP_CRL_APB_RESET_CTRL      0x218
#define ZynqMP_RESET_MASK       0x10

#define ZynqMP_GIC_CPU_BASE            XPAR_PSU_RCPU_GIC_BASEADDR       /* Generic interrupt controller CPU interface */
#define ZynqMP_GIC_DIST_BASE           XPAR_PSU_RCPU_GIC_DIST_BASEADDR  /* Generic interrupt controller distributor */

/* ZynqMP on-board gic irq sources */
#define IRQ_ZynqMP_MAXNR       195

#define ARM_GIC_NR_IRQS     IRQ_ZynqMP_MAXNR
/* only one GIC available */
#define ARM_GIC_MAX_NR      1

#define GIC_ACK_INTID_MASK  0x000003FF

#define ZynqMP_R5_0_ID    0
#define ZynqMP_R5_1_ID    1
#define ZynqMP_R5_CPU_ID   ZynqMP_R5_0_ID

static inline unsigned long rt_cpu_get_smp_id(void)
{
    return ZynqMP_R5_CPU_ID;
}

#endif
