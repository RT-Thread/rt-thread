/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#ifndef __GIC_V3_H__
#define __GIC_V3_H__

#include <rthw.h>
#include <board.h>

#define __get_gicv3_reg(CR, Rt) __asm volatile("MRC " CR  \
                                                 : "=r"(Rt) \
                                                 :          \
                                                 : "memory")
#define __set_gicv3_reg(CR, Rt) __asm volatile("MCR " CR \
                                                 :         \
                                                 : "r"(Rt) \
                                                 : "memory")


/* AArch32 System register interface to GICv3 */
#define ICC_IAR0    "p15, 0, %0, c12, c8, 0"
#define ICC_IAR1    "p15, 0, %0, c12, c12, 0"
#define ICC_EOIR0   "p15, 0, %0, c12, c8, 1"
#define ICC_EOIR1   "p15, 0, %0, c12, c12, 1"
#define ICC_HPPIR0  "p15, 0, %0, c12, c8, 2"
#define ICC_HPPIR1  "p15, 0, %0, c12, c12, 2"
#define ICC_BPR0    "p15, 0, %0, c12, c8, 3"
#define ICC_BPR1    "p15, 0, %0, c12, c12, 3"
#define ICC_DIR     "p15, 0, %0, c12, c11, 1"
#define ICC_PMR     "p15, 0, %0, c4, c6, 0"
#define ICC_RPR     "p15, 0, %0, c12, c11, 3"
#define ICC_CTLR    "p15, 0, %0, c12, c12, 4"
#define ICC_MCTLR   "p15, 6, %0, c12, c12, 4"
#define ICC_SRE     "p15, 0, %0, c12, c12, 5"
#define ICC_HSRE    "p15, 4, %0, c12, c9, 5"
#define ICC_MSRE    "p15, 6, %0, c12, c12, 5"
#define ICC_IGRPEN0 "p15, 0, %0, c12, c12, 6"
#define ICC_IGRPEN1 "p15, 0, %0, c12, c12, 7"
#define ICC_MGRPEN1 "p15, 6, %0, c12, c12, 7"

#define __REG32(x) (*((volatile unsigned int*)((rt_uint32_t)x)))

#define ROUTED_TO_ALL (1)
#define ROUTED_TO_SPEC (0)

/** Macro to access the Distributor Control Register (GICD_CTLR)
*/
#define GICD_CTLR_RWP ((unsigned int)1<<31)
#define GICD_CTLR_E1NWF (1<<7)
#define GICD_CTLR_DS (1<<6)     // 当两种安全模式被同时支持时，可以通过GICD_CTLR.DS==1关闭其中一个，只支持non-secure模式
#define GICD_CTLR_ARE_NS (1<<5)
#define GICD_CTLR_ARE_S (1<<4)
#define GICD_CTLR_ENGRP1S (1<<2)    // secure group 1
#define GICD_CTLR_ENGRP1NS (1<<1)   // non-secure group 1
#define GICD_CTLR_ENGRP0 (1<<0)     // group 0

/** Macro to access the Redistributor Control Register (GICR_CTLR)
*/
#define GICR_CTLR_UWP (1<<31)
#define GICR_CTLR_DPG1S (1<<26)
#define GICR_CTLR_DPG1NS (1<<25)
#define GICR_CTLR_DPG0 (1<<24)
#define GICR_CTLR_RWP (1<<3)
#define GICR_CTLR_IR (1<<2)
#define GICR_CTLR_CES (1<<1)
#define GICR_CTLR_EnableLPI (1<<0)

/** Macro to access the Generic Interrupt Controller Interface (GICC)
*/
#define GIC_CPU_CTRL(hw_base)               __REG32((hw_base) + 0x00U)
#define GIC_CPU_PRIMASK(hw_base)            __REG32((hw_base) + 0x04U)
#define GIC_CPU_BINPOINT(hw_base)           __REG32((hw_base) + 0x08U)
#define GIC_CPU_INTACK(hw_base)             __REG32((hw_base) + 0x0cU)
#define GIC_CPU_EOI(hw_base)                __REG32((hw_base) + 0x10U)
#define GIC_CPU_RUNNINGPRI(hw_base)         __REG32((hw_base) + 0x14U)
#define GIC_CPU_HIGHPRI(hw_base)            __REG32((hw_base) + 0x18U)
#define GIC_CPU_IIDR(hw_base)               __REG32((hw_base) + 0xFCU)

/** Macro to access the Generic Interrupt Controller Distributor (GICD)
*/
#define GIC_DIST_CTRL(hw_base)              __REG32((hw_base) + 0x000U)
#define GIC_DIST_TYPE(hw_base)              __REG32((hw_base) + 0x004U)
#define GIC_DIST_IGROUP(hw_base, n)         __REG32((hw_base) + 0x080U + ((n)/32U) * 4U)
#define GIC_DIST_ENABLE_SET(hw_base, n)     __REG32((hw_base) + 0x100U + ((n)/32U) * 4U)
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x180U + ((n)/32U) * 4U)
#define GIC_DIST_PENDING_SET(hw_base, n)    __REG32((hw_base) + 0x200U + ((n)/32U) * 4U)
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  __REG32((hw_base) + 0x280U + ((n)/32U) * 4U)
#define GIC_DIST_ACTIVE_SET(hw_base, n)     __REG32((hw_base) + 0x300U + ((n)/32U) * 4U)
#define GIC_DIST_ACTIVE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x380U + ((n)/32U) * 4U)
#define GIC_DIST_PRI(hw_base, n)            __REG32((hw_base) + 0x400U + ((n)/4U) * 4U)
#define GIC_DIST_TARGET(hw_base, n)         __REG32((hw_base) + 0x800U + ((n)/4U) * 4U)
#define GIC_DIST_CONFIG(hw_base, n)         __REG32((hw_base) + 0xc00U + ((n)/16U) * 4U)
#define GIC_DIST_SOFTINT(hw_base)           __REG32((hw_base) + 0xf00U)
#define GIC_DIST_CPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf10U + ((n)/4U) * 4U)
#define GIC_DIST_SPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf20U + ((n)/4U) * 4U)
#define GIC_DIST_ICPIDR2(hw_base)           __REG32((hw_base) + 0xfe8U)
#define GIC_DIST_IROUTER_LOW(hw_base, n)    __REG32((hw_base) + 0x6000U + (n)*8U)
#define GIC_DIST_IROUTER_HIGH(hw_base, n)   __REG32((hw_base) + 0x6000U + (n)*8U + 4)

/* SGI base address  is at 64K offset from Redistributor base address */
#define GIC_RSGI_OFFSET 0x10000

/** Macro to access the Generic Interrupt Controller Redistributor (GICD)
*/
#define GIC_RDIST_CTRL(hw_base)              __REG32((hw_base) + 0x000U)
#define GIC_RDIST_IIDR(hw_base)              __REG32((hw_base) + 0x004U)
#define GIC_RDIST_TYPER(hw_base)             __REG32((hw_base) + 0x008U)
#define GIC_RDIST_TSTATUSR(hw_base)          __REG32((hw_base) + 0x010U)
#define GIC_RDIST_WAKER(hw_base)             __REG32((hw_base) + 0x014U)
#define GIC_RDIST_SETLPIR(hw_base)           __REG32((hw_base) + 0x040U)
#define GIC_RDIST_CLRLPIR(hw_base)           __REG32((hw_base) + 0x048U)
#define GIC_RDIST_PROPBASER(hw_base)         __REG32((hw_base) + 0x070U)
#define GIC_RDIST_PENDBASER(hw_base)         __REG32((hw_base) + 0x078U)
#define GIC_RDIST_INVLPIR(hw_base)           __REG32((hw_base) + 0x0A0U)
#define GIC_RDIST_INVALLR(hw_base)           __REG32((hw_base) + 0x0B0U)
#define GIC_RDIST_SYNCR(hw_base)             __REG32((hw_base) + 0x0C0U)

#define GIC_RDISTSGI_IGROUPR0(hw_base, n)    __REG32((hw_base) + GIC_RSGI_OFFSET + 0x080U + (n)*4U)
#define GIC_RDISTSGI_ISENABLER0(hw_base)     __REG32((hw_base) + GIC_RSGI_OFFSET + 0x100U)
#define GIC_RDISTSGI_ICENABLER0(hw_base)     __REG32((hw_base) + GIC_RSGI_OFFSET + 0x180U)
#define GIC_RDISTSGI_ISPENDR0(hw_base)       __REG32((hw_base) + GIC_RSGI_OFFSET + 0x200U)
#define GIC_RDISTSGI_ICPENDR0(hw_base)       __REG32((hw_base) + GIC_RSGI_OFFSET + 0x280U)
#define GIC_RDISTSGI_ISACTIVER0(hw_base)     __REG32((hw_base) + GIC_RSGI_OFFSET + 0x300U)
#define GIC_RDISTSGI_ICACTIVER0(hw_base)     __REG32((hw_base) + GIC_RSGI_OFFSET + 0x380U)
#define GIC_RDISTSGI_IPRIORITYR(hw_base, n)  __REG32((hw_base) + GIC_RSGI_OFFSET + 0x400U + ((n) / 4U) * 4U)
#define GIC_RDISTSGI_ICFGR0(hw_base)         __REG32((hw_base) + GIC_RSGI_OFFSET + 0xC00U)
#define GIC_RDISTSGI_ICFGR1(hw_base)         __REG32((hw_base) + GIC_RSGI_OFFSET + 0xC04U)
#define GIC_RDISTSGI_IGRPMODR0(hw_base, n)   __REG32((hw_base) + GIC_RSGI_OFFSET + 0xD00U + (n)*4)
#define GIC_RDISTSGI_NSACR(hw_base)          __REG32((hw_base) + GIC_RSGI_OFFSET + 0xE00U)   // 当执行一个非安全模式到安全模式的访问

#define GIC_RSGI_AFF1_OFFSET    16
#define GIC_RSGI_AFF2_OFFSET    32
#define GIC_RSGI_AFF3_OFFSET    48

rt_uint32_t arm_gic_cpumask_to_affval(rt_uint32_t *cpu_mask, rt_uint32_t *cluster_id, rt_uint32_t *target_list);
rt_uint64_t get_main_cpu_affval(void);
int arm_gic_get_active_irq(rt_uint32_t index);
void arm_gic_ack(rt_uint32_t index, int irq);

void arm_gic_mask(rt_uint32_t index, int irq);
void arm_gic_umask(rt_uint32_t index, int irq);

rt_uint32_t arm_gic_get_pending_irq(rt_uint32_t index, int irq);
void arm_gic_set_pending_irq(rt_uint32_t index, int irq);
void arm_gic_clear_pending_irq(rt_uint32_t index, int irq);

void arm_gic_set_configuration(rt_uint32_t index, int irq, rt_uint32_t config);
rt_uint32_t arm_gic_get_configuration(rt_uint32_t index, int irq);

void arm_gic_clear_active(rt_uint32_t index, int irq);

void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask);
rt_uint32_t arm_gic_get_target_cpu(rt_uint32_t index, int irq);

void arm_gic_set_priority(rt_uint32_t index, int irq, rt_uint32_t priority);
rt_uint32_t arm_gic_get_priority(rt_uint32_t index, int irq);

void arm_gic_set_interface_prior_mask(rt_uint32_t index, rt_uint32_t priority);
rt_uint32_t arm_gic_get_interface_prior_mask(rt_uint32_t index);

void arm_gic_set_binary_point(rt_uint32_t index, rt_uint32_t binary_point);
rt_uint32_t arm_gic_get_binary_point(rt_uint32_t index);

rt_uint32_t arm_gic_get_irq_status(rt_uint32_t index, int irq);

rt_uint32_t arm_gic_get_high_pending_irq(rt_uint32_t index);

rt_uint32_t arm_gic_get_interface_id(rt_uint32_t index);

void arm_gic_set_group(rt_uint32_t index, int irq, rt_uint32_t group);
rt_uint32_t arm_gic_get_group(rt_uint32_t index, int irq);

int arm_gic_redist_address_set(rt_uint32_t index, rt_uint32_t redist_addr, rt_uint32_t cpu_id);
int arm_gic_cpu_interface_address_set(rt_uint32_t index, rt_uint32_t interface_addr, rt_uint32_t cpu_id);
int arm_gic_dist_init(rt_uint32_t index, rt_uint32_t dist_base, int irq_start);
int arm_gic_cpu_init(rt_uint32_t index);
int arm_gic_redist_init(rt_uint32_t index);

void arm_gic_dump_type(rt_uint32_t index);
void arm_gic_dump(rt_uint32_t index);

void arm_gic_set_system_register_enable_mask(rt_uint32_t index, rt_uint32_t value);
rt_uint32_t arm_gic_get_system_register_enable_mask(rt_uint32_t index);
void arm_gic_secondary_cpu_init(void);

void assemb_dsb_func();
void assemb_isb_func();

#endif

