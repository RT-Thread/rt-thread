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
 * FilePath: fgic_cpu_interface.h
 * Date: 2022-03-28 14:55:27
 * LastEditTime: 2022-03-28 14:55:27
 * Description:  This file is for gic register definition and operation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */


#ifndef FGIC_CPU_INTERFACE_H
#define FGIC_CPU_INTERFACE_H

#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FGIC_ICC_SGI1R_INTID_MASK 0xFULL  /* The INTID of the SGI. */

#define GICC_SGIR_IRM_BITS SGI_ROUTING_MODE

typedef enum
{
    GICC_SRE_SRE = (1 << 0),
    GICC_SRE_DFB = (1 << 1),
    GICC_SRE_DIB = (1 << 2),
    GICC_SRE_ENABLE = (1 << 3)
} GICC_SRE_BITS;

typedef enum
{
    GICC_CTLR_CBPR = (1 << 0),
    GICC_CTLR_CBPR_EL1S = (1 << 0),
    GICC_CTLR_EOIMODE = (1 << 1),
    GICC_CTLR_CBPR_EL1NS = (1 << 1),
    GICC_CTLR_EOIMODE_EL3 = (1 << 2),
    GICC_CTLR_EOIMODE_EL1S = (1 << 3),
    GICC_CTLR_EOIMODE_EL1NS = (1 << 4), /* GICC_EOIR and GICC_AEOIR provide priority drop functionality only. GICC_DIR provides interrupt deactivation functionality.  */
    GICC_CTLR_RM = (1 << 5),
    GICC_CTLR_PMHE = (1 << 6)
} GICC_CTLR_BITS;


#ifdef __aarch64__

void FGicSetICC_SRE_EL3(GICC_SRE_BITS bits);
void FGicSetICC_SRE_EL2(GICC_SRE_BITS bits);
void FGicSetICC_SRE_EL1(GICC_SRE_BITS bits);
u32 FGicGetICC_SRE_EL3(void);
u32 FGicGetICC_SRE_EL2(void);
u32 FGicGetICC_SRE_EL1(void);
void FGicEnableGroup0(void);
void FGicDisableGroup0(void);
void FGicEnableGroup1_EL1(void);
void FGicEnableGroup1_EL3(void);
void FGicDisableGroup1_EL1(void);
void FGicDisableGroup1_EL3(void);
void FGicSetICC_CTLR_EL3(GICC_CTLR_BITS reg_bits);
void FGicSetICC_CTLR_EL1(GICC_CTLR_BITS reg_bits);
u32 FGicGetICC_CTLR_EL3(void);
u32 FGicGetICC_CTLR_EL1(void);
u32 FGicWriteICC_APR0(void);
s32 FGicGetICC_APR1(void);
void FGicSetICC_EOIR0(u32 intnum);
void FGicSetICC_EOIR1(u32 intnum);
void FGicSetICC_DIR(u32 intnum);
void FGicSetICC_PMR(u32 priority_mask);
u32 FGicGetICC_PMR(void);
u32 FGicGetICC_BPR1(void);
void FGicSetICC_BPR1(u32 binary_point);
u32 FGicGetICC_BPR0(void);
void FGicSetICC_BPR0(u32 binary_point);
u32 FGicGetICC_HPPIR1(void);
void FGicSetICC_HPPIR1(u32 binary_point);
u32 FGicGetICC_HPPIR0(void);
void FGicSetICC_HPPIR0(u32 binary_point);
u32 FGicGetICC_RPR(void);
/* SGI interface */
void FGicSetICC_SGI0R(u32 intnum, u32 target_list, GICC_SGIR_IRM_BITS mode, u64 affinity_list);
void FGicSetICC_SGI1R(u32 intnum, u32 target_list, GICC_SGIR_IRM_BITS mode, u64 affinity_list);
void FGicSetICC_ASGI1R(u32 intnum, u32 target_list, GICC_SGIR_IRM_BITS mode, u64 affinity_list);



#else /* aarch32 */



/* For AArch32 state,  accesses to GIC registers that are visible in the System register */
#define FGIC_SYS_READ32(CR, Rt) __asm__ volatile("MRC " CR  \
        : "=r"(Rt) \
        :          \
        : "memory")
#define FGIC_SYS_WRITE32(CR, Rt) __asm__ volatile("MCR " CR \
        :         \
        : "r"(Rt) \
        : "memory")

#define FGIC_SYS_WRITE64(cp, op1, Rt, CRm) __asm__ volatile("MCRR p" #cp ", " #op1 ", %Q0, %R0, c" #CRm \
        :                                           \
        : "r"(Rt)                                   \
        : "memory")


#define ICC_IAR0 "p15, 0, %0, c12, c8, 0"
#define ICC_IAR1 "p15, 0, %0, c12, c12, 0"
/* writes to this register to inform the CPU interface
that it has completed the processing */
#define ICC_EOIR0 "p15, 0, %0, c12, c8, 1"
#define ICC_EOIR1 "p15, 0, %0, c12, c12, 1"
/*  GET the INTID of highest priority pending interrupt */
#define ICC_HPPIR0 "p15, 0, %0, c12, c8, 2"
#define ICC_HPPIR1 "p15, 0, %0, c12, c12, 2"
#define ICC_BPR0 "p15, 0, %0, c12, c8, 3"
#define ICC_BPR1 "p15, 0, %0, c12, c12, 3"
#define ICC_DIR "p15, 0, %0, c12, c11, 1"
#define ICC_PMR "p15, 0, %0, c4, c6, 0"
#define ICC_RPR "p15, 0, %0, c12, c11, 3"
#define ICC_CTLR "p15, 0, %0, c12, c12, 4"
#define ICC_MCTLR "p15, 6, %0, c12, c12, 4"
#define ICC_SRE "p15, 0, %0, c12, c12, 5"
#define ICC_HSRE "p15, 4, %0, c12, c9, 5"
#define ICC_MSRE "p15, 6, %0, c12, c12, 5"
#define ICC_IGRPEN0 "p15, 0, %0, c12, c12, 6"
#define ICC_IGRPEN1 "p15, 0, %0, c12, c12, 7"
#define ICC_MGRPEN1 "p15, 6, %0, c12, c12, 7"

#define FGicSetICC_SRE_EL1 FGicSetICC_SRE
#define FGicSetICC_SRE_EL2 FGicSetICC_SRE
#define FGicSetICC_SRE_EL3 FGicSetICC_SRE

/**
 * @name:
 * @msg: void FGicSetICC_SRE(GICC_SRE_BITS bits) --- Interrupt Controller System Register Enable
 * @return {*}
 */
static inline void FGicSetICC_SRE(GICC_SRE_BITS bits)
{
    FGIC_SYS_WRITE32(ICC_SRE, (u32)bits);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


#define FGicGetICC_SRE_EL3 FGicGetICC_SRE
#define FGicGetICC_SRE_EL2 FGicGetICC_SRE
#define FGicGetICC_SRE_EL1 FGicGetICC_SRE

/**
 * @name:
 * @msg: u32 FGicGetICC_SRE(void) --  Interrupt Controller System Register Enable
 * @return {*}
 */
static inline u32 FGicGetICC_SRE(void)
{
    u32 value;

    FGIC_SYS_READ32(ICC_SRE, value);
    return value;
}


/**
 * @name:
 * @msg: void FGicEnableGroup0(void)
 * @return {*}
 */
static inline void FGicEnableGroup0(void)
{
    u32 value = 1;
    FGIC_SYS_WRITE32(ICC_IGRPEN0, value);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg: void FGicDisableGroup0(void)
 * @return {*}
 */
static inline void FGicDisableGroup0(void)
{
    u32 value = 0;
    FGIC_SYS_WRITE32(ICC_IGRPEN0, value);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


#define FGicEnableGroup1_EL3 FGicEnableGroup1
#define FGicEnableGroup1_EL1 FGicEnableGroup1

/**
 * @name:
 * @msg:
 * @return {*}
 */
static inline void FGicEnableGroup1(void)
{
    u32 value = 1;
    FGIC_SYS_WRITE32(ICC_IGRPEN1, value);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}



#define FGicDisableGroup1_EL3 FGicDisableGroup1
#define FGicDisableGroup1_EL1 FGicDisableGroup1

/**
 * @name:
 * @msg: void FGicDisableGroup1(void)
 * @return {*}
 */
static inline void FGicDisableGroup1(void)
{
    u32 value = 0;
    FGIC_SYS_WRITE32(ICC_IGRPEN1, value);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

#define FGicSetICC_CTLR_EL3 FGicSetICC_CTLR
#define FGicSetICC_CTLR_EL1 FGicSetICC_CTLR

/**
 * @name:
 * @msg: void FGicSetICC_CTLR(GICC_CTLR_BITS reg_bits)
 * @return {*}
 */
static inline void FGicSetICC_CTLR(GICC_CTLR_BITS bits)
{
    FGIC_SYS_WRITE32(ICC_CTLR, bits);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

#define FGicGetICC_CTLR_EL3 FGicGetICC_CTLR
#define FGicGetICC_CTLR_EL1 FGicGetICC_CTLR

/**
 * @name:
 * @msg: static inline u32 FGicGetICC_CTLR(void) -- Controls aspects of the behavior of the GIC CPU interface and provides information about the features implemented.
 * @return {*}
 */
static inline u32 FGicGetICC_CTLR(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_CTLR, reg);
    return reg;
}

/**
 * @name:
 * @msg: static inline u32 FGicWriteICC_APR0(void) -- The PE reads this register to obtain the INTID of the signaled Group 0 interrupt.
 * @return {*}
 */
static inline u32 FGicWriteICC_APR0(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_IAR0, reg);
    return reg;
}


/**
 * @name:
 * @msg: static inline s32 FGicGetICC_APR1(void)  -- The PE reads this register to obtain the INTID of the signaled Group 1 interrupt.
 * @return {*}
 */
static inline s32 FGicGetICC_APR1(void)
{
    s32 reg;
    FGIC_SYS_READ32(ICC_IAR1, reg);
    return reg;
}


/**
 * @name:
 * @msg: static inline void FGicSetICC_EOIR0(u32 intnum) -- /* A PE writes to this register to inform the CPU interface that it has completed the processing of the specified Group 0 interrupt
 * @return {*}
 * @param {u32} intnum
 */
static inline void FGicSetICC_EOIR0(u32 intnum)
{
    FGIC_SYS_WRITE32(ICC_EOIR0, intnum);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


/**
 * @name:
 * @msg: static inline void FGicSetICC_EOIR1(u32 intnum) -- /* A PE writes to this register to inform the CPU interface that it has completed the processing of the specified Group 1 interrupt
 * @return {*}
 */
static inline void FGicSetICC_EOIR1(u32 intnum)
{
    FGIC_SYS_WRITE32(ICC_EOIR1, intnum);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg:  static inline void FGicSetICC_DIR(u32 intnum) -- When interrupt priority drop is separated from interrupt deactivation, a write to this register deactivates the specified interrupt.
 * @return {*}
 */
static inline void FGicSetICC_DIR(u32 intnum)
{
    FGIC_SYS_WRITE32(ICC_DIR, intnum);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg: static inline void FGicSetICC_PMR(u32 priority_mask) -- Provides an interrupt priority filter.
 * @return {*}
 */
/**
 * @name:
 * @msg:
 * @param {u32} priority_mask is level for the CPU interface. If the priority of an interrupt is higher than the value
 * indicated by this field, the interface signals the interrupt to the PE.
 */
static inline void FGicSetICC_PMR(u32 priority_mask)
{
    FGIC_SYS_WRITE32(ICC_PMR, priority_mask);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


/**
 * @name:
 * @msg: static inline u32 FGicGetICC_PMR(void)
 * @return {*}
 */
static inline u32 FGicGetICC_PMR(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_PMR, reg);
    return reg;
}


/**
 * @name:
 * @msg:  static inline u32 FGicGetICC_BPR1(void) --- Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 1 interrupt preemption.
 * @return {*}
 */
static inline u32 FGicGetICC_BPR1(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_BPR1, reg);
    return reg;
}

/**
 * @name:
 * @msg:  static inline void FGicSetICC_BPR1(u32 binary_point)
 * @return {*}
 */
static inline void FGicSetICC_BPR1(u32 binary_point)
{
    FGIC_SYS_WRITE32(ICC_BPR1, binary_point);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg:  static inline u32 FGicGetICC_BPR0(void) --- Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 0 interrupt preemption.
 * @return {*}
 */
static inline u32 FGicGetICC_BPR0(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_BPR0, reg);
    return reg;
}


/**
 * @name:
 * @msg:  static inline void FGicSetICC_BPR0(u32 binary_point)
 * @return {*}
 */
static inline void FGicSetICC_BPR0(u32 binary_point)
{
    FGIC_SYS_WRITE32(ICC_BPR0, binary_point);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg:  static inline u32 FGicGetICC_HPPIR1(void) --- Indicates the highest priority pending Group 1 interrupt on the CPU interface.
 * @return {*}
 */
static inline u32 FGicGetICC_HPPIR1(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_HPPIR1, reg);
    return reg;
}


/**
 * @name:
 * @msg:  static inline void FGicSetICC_HPPIR1(u32 binary_point)
 * @return {*}
 */
static inline void FGicSetICC_HPPIR1(u32 binary_point)
{
    FGIC_SYS_WRITE32(ICC_HPPIR1, binary_point);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg:  static inline u32 FGicGetICC_HPPIR0(void) --- Indicates the highest priority pending Group 0 interrupt on the CPU interface.
 * @return {*}
 */
static inline u32 FGicGetICC_HPPIR0(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_HPPIR0, reg);
    return reg;
}


/**
 * @name:
 * @msg:  static inline void FGicSetICC_HPPIR0(u32 binary_point)
 * @return {*}
 */
static inline void FGicSetICC_HPPIR0(u32 binary_point)
{
    FGIC_SYS_WRITE32(ICC_HPPIR0, binary_point);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg:  static inline u32 FGicGetICC_RPR(void) --- Indicates the Running priority of the CPU interface.
 * @return {*}
 */
static inline u32 FGicGetICC_RPR(void)
{
    u32 reg;
    FGIC_SYS_READ32(ICC_RPR, reg);
    return reg;
}
/* SGI interface */

/**
 * @name:
 * @msg: static inline void FGicSetICC_SGI0R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list)    --- Generates Secure Group 0 SGIs
 * @return {*}
 */
/**
 * @name:
 * @msg:
 * @return {*}
 * @param {u32} intnum_bit
 * @param {u32} target_list
 * @param {GICC_SGIR_IRM_BITS} irm_bit
 * @param {u64} affinity_list
 */
static inline void FGicSetICC_SGI0R(u32 intnum_bit, u32 target_list, GICC_SGIR_IRM_BITS irm_bit, u64 affinity_list)
{
    u64 sgi_val;
    sgi_val = intnum_bit; /* The INTID of the SGI. */
    sgi_val |= affinity_list ; /* Aff3.Aff2.Aff1 */
    sgi_val |= irm_bit ; /* Interrupt Routing Mode. */
    sgi_val |= target_list; /* Target List. The set of PEs for which SGI interrupts will be generated. */

    __asm__ volatile("dsb 0xF" ::
                     : "memory");
    FGIC_SYS_WRITE64(15, 2, sgi_val, 12);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}

/**
 * @name:
 * @msg: static inline void FGicSetICC_SGI1R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list)
 * @return {*}
 */
static inline void FGicSetICC_SGI1R(u32 intnum_bit, u32 target_list, GICC_SGIR_IRM_BITS irm_bit, u64 affinity_list)
{
    u64 sgi_val;
    sgi_val = intnum_bit; /* The INTID of the SGI. */
    sgi_val |= affinity_list ; /* Aff3.Aff2.Aff1 */
    sgi_val |= irm_bit ; /* Interrupt Routing Mode. */
    sgi_val |= target_list; /* Target List. The set of PEs for which SGI interrupts will be generated. */

    __asm__ volatile("dsb 0xF" ::
                     : "memory");
    FGIC_SYS_WRITE64(15, 0, sgi_val, 12);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


/**
 * @name:
 * @msg: static inline void FGicSetICC_ASGI1R(u32 intnum,u32 target_list,GICC_SGIR_IRM_BITS mode,u64 affinity_list)
 * @return {*}
 */
static inline void FGicSetICC_ASGI1R(u32 intnum_bit, u32 target_list, GICC_SGIR_IRM_BITS irm_bit, u64 affinity_list)
{
    u64 sgi_val;
    sgi_val = intnum_bit; /* The INTID of the SGI. */
    sgi_val |= affinity_list ; /* Aff3.Aff2.Aff1 */
    sgi_val |= irm_bit ; /* Interrupt Routing Mode. */
    sgi_val |= target_list; /* Target List. The set of PEs for which SGI interrupts will be generated. */

    __asm__ volatile("dsb 0xF" ::
                     : "memory");
    FGIC_SYS_WRITE64(15, 1, sgi_val, 12);
    __asm__ volatile("isb 0xF" ::
                     : "memory");
}


#endif

#ifdef __cplusplus
}
#endif

#endif

