/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RT_HW_CPU_H__
#define __RT_HW_CPU_H__

#include <rtdef.h>
#include <cpuport.h>
#include <mm_aspace.h>

#ifdef RT_USING_OFW
#include <drivers/ofw.h>
#endif

#define ID_ERROR __INT64_MAX__
#define MPIDR_AFFINITY_MASK         0x000000ff00ffffffUL

struct cpu_ops_t
{
    const char *method;
    int     (*cpu_init)(rt_uint32_t id, void *param);
    int     (*cpu_boot)(rt_uint32_t id, rt_uint64_t entry);
    void    (*cpu_shutdown)(void);
};
#define sysreg_32(op1, crn, crm, op2)   s3_##op1 ##_##crn ##_##crm ##_##op2
#define sysreg_64(op1, crn, crm, op2)   sysreg_32(op1, crn, crm, op2)

#define MPIDR_AFFINITY_MASK         0x000000ff00ffffffUL

#define MPIDR_LEVEL_BITS_SHIFT      3
#define MPIDR_LEVEL_BITS            (1 << MPIDR_LEVEL_BITS_SHIFT)
#define MPIDR_LEVEL_MASK            ((1 << MPIDR_LEVEL_BITS) - 1)
#define MPIDR_LEVEL_SHIFT(level)    (((1 << (level)) >> 1) << MPIDR_LEVEL_BITS_SHIFT)

#define MPIDR_AFFINITY_LEVEL(mpidr, level) (((mpidr) >> MPIDR_LEVEL_SHIFT(level)) & MPIDR_LEVEL_MASK)

/* GIC registers */
#define ICC_IAR0_SYS    sysreg_64(0, c12,  c8, 0)
#define ICC_IAR1_SYS    sysreg_64(0, c12, c12, 0)
#define ICC_EOIR0_SYS   sysreg_64(0, c12,  c8, 1)
#define ICC_EOIR1_SYS   sysreg_64(0, c12, c12, 1)
#define ICC_HPPIR0_SYS  sysreg_64(0, c12,  c8, 2)
#define ICC_HPPIR1_SYS  sysreg_64(0, c12, c12, 2)
#define ICC_BPR0_SYS    sysreg_64(0, c12,  c8, 3)
#define ICC_BPR1_SYS    sysreg_64(0, c12, c12, 3)
#define ICC_DIR_SYS     sysreg_64(0, c12, c11, 1)
#define ICC_PMR_SYS     sysreg_64(0,  c4,  c6, 0)
#define ICC_RPR_SYS     sysreg_64(0, c12, c11, 3)
#define ICC_CTLR_SYS    sysreg_64(0, c12, c12, 4)
#define ICC_SRE_SYS     sysreg_64(0, c12, c12, 5)
#define ICC_IGRPEN0_SYS sysreg_64(0, c12, c12, 6)
#define ICC_IGRPEN1_SYS sysreg_64(0, c12, c12, 7)
#define ICC_SGI0R_SYS   sysreg_64(0, c12, c11, 7)
#define ICC_SGI1R_SYS   sysreg_64(0, c12, c11, 5)
#define ICC_ASGI1R_SYS  sysreg_64(0, c12, c11, 6)

/* Arch timer registers */
#define CNTP_CTL        CNTP_CTL_EL0    /* EL1 Physical Timer */
#define CNTHP_CTL       CNTHP_CTL_EL2   /* EL2 Non-secure Physical Timer */
#define CNTHPS_CTL      CNTHPS_CTL_EL2  /* EL2 Secure Physical Timer */
#define CNTPS_CTL       CNTPS_CTL_EL1   /* EL3 Physical Timer */
#define CNTV_CTL        CNTV_CTL_EL0    /* EL1 Virtual Timer */
#define CNTHV_CTL       CNTHV_CTL_EL2   /* EL2 Non-secure Virtual Timer */
#define CNTHVS_CTL      CNTHVS_CTL_EL2  /* EL2 Secure Virtual Timer */

#define CNTP_CVAL       CNTP_CVAL_EL0
#define CNTHP_CVAL      CNTHP_CVAL_EL2
#define CNTHPS_CVAL     CNTHPS_CVAL_EL2
#define CNTPS_CVAL      CNTPS_CVAL_EL1
#define CNTV_CVAL       CNTV_CVAL_EL0
#define CNTHV_CVAL      CNTHV_CVAL_EL2
#define CNTHVS_CVAL     CNTHVS_CVAL_EL2

#define CNTP_TVAL       CNTP_TVAL_EL0
#define CNTHP_TVAL      CNTHP_TVAL_EL2
#define CNTHPS_TVAL     CNTHPS_TVAL_EL2
#define CNTPS_TVAL      CNTPS_TVAL_EL1
#define CNTV_TVAL       CNTV_TVAL_EL0
#define CNTHV_TVAL      CNTHV_TVAL_EL2
#define CNTHVS_TVAL     CNTHVS_TVAL_EL2

#define CNTPCT          CNTPCT_EL0
#define CNTVCT          CNTVCT_EL0
#define CNTFRQ          CNTFRQ_EL0
extern rt_uint64_t rt_cpu_mpidr_table[];

#endif /* __RT_HW_CPU_H__ */
