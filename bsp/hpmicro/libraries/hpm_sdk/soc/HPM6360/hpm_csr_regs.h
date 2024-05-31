/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_CSR_H
#define HPM_CSR_H

/* STANDARD CRS address definition */
#define CSR_USTATUS (0x0)
#define CSR_UIE (0x4)
#define CSR_UTVEC (0x5)
#define CSR_USCRATCH (0x40)
#define CSR_UEPC (0x41)
#define CSR_UCAUSE (0x42)
#define CSR_UTVAL (0x43)
#define CSR_UIP (0x44)
#define CSR_SSTATUS (0x100)
#define CSR_SEDELEG (0x102)
#define CSR_SIDELEG (0x103)
#define CSR_SIE (0x104)
#define CSR_STVEC (0x105)
#define CSR_SSCRATCH (0x140)
#define CSR_SEPC (0x141)
#define CSR_SCAUSE (0x142)
#define CSR_STVAL (0x143)
#define CSR_SIP (0x144)
#define CSR_SATP (0x180)
#define CSR_MSTATUS (0x300)
#define CSR_MISA (0x301)
#define CSR_MEDELEG (0x302)
#define CSR_MIDELEG (0x303)
#define CSR_MIE (0x304)
#define CSR_MTVEC (0x305)
#define CSR_MCOUNTEREN (0x306)
#define CSR_MHPMEVENT3 (0x323)
#define CSR_MHPMEVENT4 (0x324)
#define CSR_MHPMEVENT5 (0x325)
#define CSR_MHPMEVENT6 (0x326)
#define CSR_MSCRATCH (0x340)
#define CSR_MEPC (0x341)
#define CSR_MCAUSE (0x342)
#define CSR_MTVAL (0x343)
#define CSR_MIP (0x344)
#define CSR_PMPCFG0 (0x3A0)
#define CSR_PMPCFG1 (0x3A1)
#define CSR_PMPCFG2 (0x3A2)
#define CSR_PMPCFG3 (0x3A3)
#define CSR_PMPADDR0 (0x3B0)
#define CSR_PMPADDR1 (0x3B1)
#define CSR_PMPADDR2 (0x3B2)
#define CSR_PMPADDR3 (0x3B3)
#define CSR_PMPADDR4 (0x3B4)
#define CSR_PMPADDR5 (0x3B5)
#define CSR_PMPADDR6 (0x3B6)
#define CSR_PMPADDR7 (0x3B7)
#define CSR_PMPADDR8 (0x3B8)
#define CSR_PMPADDR9 (0x3B9)
#define CSR_PMPADDR10 (0x3BA)
#define CSR_PMPADDR11 (0x3BB)
#define CSR_PMPADDR12 (0x3BC)
#define CSR_PMPADDR13 (0x3BD)
#define CSR_PMPADDR14 (0x3BE)
#define CSR_PMPADDR15 (0x3BF)
#define CSR_TSELECT (0x7A0)
#define CSR_TDATA1 (0x7A1)
#define CSR_MCONTROL (0x7A1)
#define CSR_ICOUNT (0x7A1)
#define CSR_ITRIGGER (0x7A1)
#define CSR_ETRIGGER (0x7A1)
#define CSR_TDATA2 (0x7A2)
#define CSR_TDATA3 (0x7A3)
#define CSR_TEXTRA (0x7A3)
#define CSR_TINFO (0x7A4)
#define CSR_TCONTROL (0x7A5)
#define CSR_MCONTEXT (0x7A8)
#define CSR_SCONTEXT (0x7AA)
#define CSR_DCSR (0x7B0)
#define CSR_DPC (0x7B1)
#define CSR_DSCRATCH0 (0x7B2)
#define CSR_DSCRATCH1 (0x7B3)
#define CSR_MCYCLE (0xB00)
#define CSR_MINSTRET (0xB02)
#define CSR_MHPMCOUNTER3 (0xB03)
#define CSR_MHPMCOUNTER4 (0xB04)
#define CSR_MHPMCOUNTER5 (0xB05)
#define CSR_MHPMCOUNTER6 (0xB06)
#define CSR_MCYCLEH (0xB80)
#define CSR_MINSTRETH (0xB82)
#define CSR_MHPMCOUNTER3H (0xB83)
#define CSR_MHPMCOUNTER4H (0xB84)
#define CSR_MHPMCOUNTER5H (0xB85)
#define CSR_MHPMCOUNTER6H (0xB86)
#define CSR_PMACFG0 (0xBC0)
#define CSR_PMACFG1 (0xBC1)
#define CSR_PMACFG2 (0xBC2)
#define CSR_PMACFG3 (0xBC3)
#define CSR_PMAADDR0 (0xBD0)
#define CSR_PMAADDR1 (0xBD1)
#define CSR_PMAADDR2 (0xBD2)
#define CSR_PMAADDR3 (0xBD3)
#define CSR_PMAADDR4 (0xBD4)
#define CSR_PMAADDR5 (0xBD5)
#define CSR_PMAADDR6 (0xBD6)
#define CSR_PMAADDR7 (0xBD7)
#define CSR_PMAADDR8 (0xBD8)
#define CSR_PMAADDR9 (0xBD9)
#define CSR_PMAADDR10 (0xBDA)
#define CSR_PMAADDR11 (0xBDB)
#define CSR_PMAADDR12 (0xBDC)
#define CSR_PMAADDR13 (0xBDD)
#define CSR_PMAADDR14 (0xBDE)
#define CSR_PMAADDR15 (0xBDF)
#define CSR_CYCLE (0xC00)
#define CSR_CYCLEH (0xC80)
#define CSR_MVENDORID (0xF11)
#define CSR_MARCHID (0xF12)
#define CSR_MIMPID (0xF13)
#define CSR_MHARTID (0xF14)

/* NON-STANDARD CRS address definition */
#define CSR_SCOUNTEREN (0x106)
#define CSR_MCOUNTINHIBIT (0x320)
#define CSR_MILMB (0x7C0)
#define CSR_MDLMB (0x7C1)
#define CSR_MECC_CODE (0x7C2)
#define CSR_MNVEC (0x7C3)
#define CSR_MXSTATUS (0x7C4)
#define CSR_MPFT_CTL (0x7C5)
#define CSR_MHSP_CTL (0x7C6)
#define CSR_MSP_BOUND (0x7C7)
#define CSR_MSP_BASE (0x7C8)
#define CSR_MDCAUSE (0x7C9)
#define CSR_MCACHE_CTL (0x7CA)
#define CSR_MCCTLBEGINADDR (0x7CB)
#define CSR_MCCTLCOMMAND (0x7CC)
#define CSR_MCCTLDATA (0x7CD)
#define CSR_MCOUNTERWEN (0x7CE)
#define CSR_MCOUNTERINTEN (0x7CF)
#define CSR_MMISC_CTL (0x7D0)
#define CSR_MCOUNTERMASK_M (0x7D1)
#define CSR_MCOUNTERMASK_S (0x7D2)
#define CSR_MCOUNTERMASK_U (0x7D3)
#define CSR_MCOUNTEROVF (0x7D4)
#define CSR_MSLIDELEG (0x7D5)
#define CSR_MCLK_CTL (0x7DF)
#define CSR_DEXC2DBG (0x7E0)
#define CSR_DDCAUSE (0x7E1)
#define CSR_UITB (0x800)
#define CSR_UCODE (0x801)
#define CSR_UDCAUSE (0x809)
#define CSR_UCCTLBEGINADDR (0x80B)
#define CSR_UCCTLCOMMAND (0x80C)
#define CSR_SLIE (0x9C4)
#define CSR_SLIP (0x9C5)
#define CSR_SDCAUSE (0x9C9)
#define CSR_SCCTLDATA (0x9CD)
#define CSR_SCOUNTERINTEN (0x9CF)
#define CSR_SCOUNTERMASK_M (0x9D1)
#define CSR_SCOUNTERMASK_S (0x9D2)
#define CSR_SCOUNTERMASK_U (0x9D3)
#define CSR_SCOUNTEROVF (0x9D4)
#define CSR_SCOUNTINHIBIT (0x9E0)
#define CSR_SHPMEVENT3 (0x9E3)
#define CSR_SHPMEVENT4 (0x9E4)
#define CSR_SHPMEVENT5 (0x9E5)
#define CSR_SHPMEVENT6 (0x9E6)
#define CSR_MICM_CFG (0xFC0)
#define CSR_MDCM_CFG (0xFC1)
#define CSR_MMSC_CFG (0xFC2)
#define CSR_MMSC_CFG2 (0xFC3)

/* STANDARD CRS register bitfiled definitions */

/* Bitfield definition for register: USTATUS */
/*
 * UPIE (RW)
 *
 * UPIE holds the value of the UIE bit prior to a trap.
 */
#define CSR_USTATUS_UPIE_MASK (0x10U)
#define CSR_USTATUS_UPIE_SHIFT (4U)
#define CSR_USTATUS_UPIE_SET(x) (((uint32_t)(x) << CSR_USTATUS_UPIE_SHIFT) & CSR_USTATUS_UPIE_MASK)
#define CSR_USTATUS_UPIE_GET(x) (((uint32_t)(x) & CSR_USTATUS_UPIE_MASK) >> CSR_USTATUS_UPIE_SHIFT)

/*
 * UIE (RW)
 *
 * U mode interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_USTATUS_UIE_MASK (0x1U)
#define CSR_USTATUS_UIE_SHIFT (0U)
#define CSR_USTATUS_UIE_SET(x) (((uint32_t)(x) << CSR_USTATUS_UIE_SHIFT) & CSR_USTATUS_UIE_MASK)
#define CSR_USTATUS_UIE_GET(x) (((uint32_t)(x) & CSR_USTATUS_UIE_MASK) >> CSR_USTATUS_UIE_SHIFT)

/* Bitfield definition for register: UIE */
/*
 * UEIE (RW)
 *
 * U mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_UIE_UEIE_MASK (0x100U)
#define CSR_UIE_UEIE_SHIFT (8U)
#define CSR_UIE_UEIE_SET(x) (((uint32_t)(x) << CSR_UIE_UEIE_SHIFT) & CSR_UIE_UEIE_MASK)
#define CSR_UIE_UEIE_GET(x) (((uint32_t)(x) & CSR_UIE_UEIE_MASK) >> CSR_UIE_UEIE_SHIFT)

/*
 * UTIE (RW)
 *
 * U mode timer interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_UIE_UTIE_MASK (0x10U)
#define CSR_UIE_UTIE_SHIFT (4U)
#define CSR_UIE_UTIE_SET(x) (((uint32_t)(x) << CSR_UIE_UTIE_SHIFT) & CSR_UIE_UTIE_MASK)
#define CSR_UIE_UTIE_GET(x) (((uint32_t)(x) & CSR_UIE_UTIE_MASK) >> CSR_UIE_UTIE_SHIFT)

/*
 * USIE (RW)
 *
 * U mode software interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_UIE_USIE_MASK (0x1U)
#define CSR_UIE_USIE_SHIFT (0U)
#define CSR_UIE_USIE_SET(x) (((uint32_t)(x) << CSR_UIE_USIE_SHIFT) & CSR_UIE_USIE_MASK)
#define CSR_UIE_USIE_GET(x) (((uint32_t)(x) & CSR_UIE_USIE_MASK) >> CSR_UIE_USIE_SHIFT)

/* Bitfield definition for register: UTVEC */
/*
 * BASE_31_2 (RW)
 *
 * Base address for interrupt and exception handlers. See description above for alignment requirements when PLIC is in the vector mode.
 */
#define CSR_UTVEC_BASE_31_2_MASK (0xFFFFFFFCUL)
#define CSR_UTVEC_BASE_31_2_SHIFT (2U)
#define CSR_UTVEC_BASE_31_2_SET(x) (((uint32_t)(x) << CSR_UTVEC_BASE_31_2_SHIFT) & CSR_UTVEC_BASE_31_2_MASK)
#define CSR_UTVEC_BASE_31_2_GET(x) (((uint32_t)(x) & CSR_UTVEC_BASE_31_2_MASK) >> CSR_UTVEC_BASE_31_2_SHIFT)

/* Bitfield definition for register: USCRATCH */
/*
 * USCRATCH (RW)
 *
 * Scratch register storage.
 */
#define CSR_USCRATCH_USCRATCH_MASK (0xFFFFFFFFUL)
#define CSR_USCRATCH_USCRATCH_SHIFT (0U)
#define CSR_USCRATCH_USCRATCH_SET(x) (((uint32_t)(x) << CSR_USCRATCH_USCRATCH_SHIFT) & CSR_USCRATCH_USCRATCH_MASK)
#define CSR_USCRATCH_USCRATCH_GET(x) (((uint32_t)(x) & CSR_USCRATCH_USCRATCH_MASK) >> CSR_USCRATCH_USCRATCH_SHIFT)

/* Bitfield definition for register: UEPC */
/*
 * EPC (RW)
 *
 * Exception program counter.
 */
#define CSR_UEPC_EPC_MASK (0xFFFFFFFEUL)
#define CSR_UEPC_EPC_SHIFT (1U)
#define CSR_UEPC_EPC_SET(x) (((uint32_t)(x) << CSR_UEPC_EPC_SHIFT) & CSR_UEPC_EPC_MASK)
#define CSR_UEPC_EPC_GET(x) (((uint32_t)(x) & CSR_UEPC_EPC_MASK) >> CSR_UEPC_EPC_SHIFT)

/* Bitfield definition for register: UCAUSE */
/*
 * INTERRUPT (RW)
 *
 * Interrupt.
 */
#define CSR_UCAUSE_INTERRUPT_MASK (0x80000000UL)
#define CSR_UCAUSE_INTERRUPT_SHIFT (31U)
#define CSR_UCAUSE_INTERRUPT_SET(x) (((uint32_t)(x) << CSR_UCAUSE_INTERRUPT_SHIFT) & CSR_UCAUSE_INTERRUPT_MASK)
#define CSR_UCAUSE_INTERRUPT_GET(x) (((uint32_t)(x) & CSR_UCAUSE_INTERRUPT_MASK) >> CSR_UCAUSE_INTERRUPT_SHIFT)

/*
 * EXCEPTION_CODE (RW)
 *
 * Exception Code.
 * When interrupt is 1:
 * 0:User software interrupt
 * 4:User timer interrupt
 * 8:User external interrupt
 * When interrupt is 0:
 * 0:Instruction address misaligned
 * 1:Instruction access fault
 * 2:Illegal instruction
 * 3:Breakpoint
 * 4:Load address misaligned
 * 5:Load access fault
 * 6:Store/AMO address misaligned
 * 7:Store/AMO access fault
 * 8:Environment call from U-mode
 * 9-11:Reserved
 * 12:Instruction page fault
 * 13:Load page fault
 * 14:Reserved
 * 15:Store/AMO page fault
 * 32：Stack overflow exception
 * 33:Stack underflow exception
 * 40-47:Reserved
 */
#define CSR_UCAUSE_EXCEPTION_CODE_MASK (0x3FFU)
#define CSR_UCAUSE_EXCEPTION_CODE_SHIFT (0U)
#define CSR_UCAUSE_EXCEPTION_CODE_SET(x) (((uint32_t)(x) << CSR_UCAUSE_EXCEPTION_CODE_SHIFT) & CSR_UCAUSE_EXCEPTION_CODE_MASK)
#define CSR_UCAUSE_EXCEPTION_CODE_GET(x) (((uint32_t)(x) & CSR_UCAUSE_EXCEPTION_CODE_MASK) >> CSR_UCAUSE_EXCEPTION_CODE_SHIFT)

/* Bitfield definition for register: UTVAL */
/*
 * UTVAL (RW)
 *
 * Exception-specific information for software trap handling.
 */
#define CSR_UTVAL_UTVAL_MASK (0xFFFFFFFFUL)
#define CSR_UTVAL_UTVAL_SHIFT (0U)
#define CSR_UTVAL_UTVAL_SET(x) (((uint32_t)(x) << CSR_UTVAL_UTVAL_SHIFT) & CSR_UTVAL_UTVAL_MASK)
#define CSR_UTVAL_UTVAL_GET(x) (((uint32_t)(x) & CSR_UTVAL_UTVAL_MASK) >> CSR_UTVAL_UTVAL_SHIFT)

/* Bitfield definition for register: UIP */
/*
 * UEIP (RW)
 *
 * U mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_UIP_UEIP_MASK (0x100U)
#define CSR_UIP_UEIP_SHIFT (8U)
#define CSR_UIP_UEIP_SET(x) (((uint32_t)(x) << CSR_UIP_UEIP_SHIFT) & CSR_UIP_UEIP_MASK)
#define CSR_UIP_UEIP_GET(x) (((uint32_t)(x) & CSR_UIP_UEIP_MASK) >> CSR_UIP_UEIP_SHIFT)

/*
 * UTIP (RW)
 *
 * U mode timer interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_UIP_UTIP_MASK (0x10U)
#define CSR_UIP_UTIP_SHIFT (4U)
#define CSR_UIP_UTIP_SET(x) (((uint32_t)(x) << CSR_UIP_UTIP_SHIFT) & CSR_UIP_UTIP_MASK)
#define CSR_UIP_UTIP_GET(x) (((uint32_t)(x) & CSR_UIP_UTIP_MASK) >> CSR_UIP_UTIP_SHIFT)

/*
 * USIP (RW)
 *
 * U mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_UIP_USIP_MASK (0x1U)
#define CSR_UIP_USIP_SHIFT (0U)
#define CSR_UIP_USIP_SET(x) (((uint32_t)(x) << CSR_UIP_USIP_SHIFT) & CSR_UIP_USIP_MASK)
#define CSR_UIP_USIP_GET(x) (((uint32_t)(x) & CSR_UIP_USIP_MASK) >> CSR_UIP_USIP_SHIFT)

/* Bitfield definition for register: SSTATUS */
/*
 * SD (RO)
 *
 * SD summarizes whether either the FS field or XS field is dirty.
 */
#define CSR_SSTATUS_SD_MASK (0x80000000UL)
#define CSR_SSTATUS_SD_SHIFT (31U)
#define CSR_SSTATUS_SD_GET(x) (((uint32_t)(x) & CSR_SSTATUS_SD_MASK) >> CSR_SSTATUS_SD_SHIFT)

/*
 * MXR (RW)
 *
 * MXR controls whether execute-only pages are readable. It has no effect when page-based virtual memory is not in effect.
 * 0:Execute-only pages are not readable
 * 1:Execute-only pages are readable
 */
#define CSR_SSTATUS_MXR_MASK (0x80000UL)
#define CSR_SSTATUS_MXR_SHIFT (19U)
#define CSR_SSTATUS_MXR_SET(x) (((uint32_t)(x) << CSR_SSTATUS_MXR_SHIFT) & CSR_SSTATUS_MXR_MASK)
#define CSR_SSTATUS_MXR_GET(x) (((uint32_t)(x) & CSR_SSTATUS_MXR_MASK) >> CSR_SSTATUS_MXR_SHIFT)

/*
 * SUM (RW)
 *
 * SUM controls whether a S-mode load/store instruction to a user accessible page is allowed or not when page translation is enabled. It is in effect in two scenarios: (a) M-mode with MPRV=1 and MPP=S, and (b) in S-mode. It has no effect when page-based virtual memory is not in effect. A page is user accessible when the U bit of the corresponding PTE entry is 1.
 * 0:Not Allowed
 * 1:Allowed
 */
#define CSR_SSTATUS_SUM_MASK (0x40000UL)
#define CSR_SSTATUS_SUM_SHIFT (18U)
#define CSR_SSTATUS_SUM_SET(x) (((uint32_t)(x) << CSR_SSTATUS_SUM_SHIFT) & CSR_SSTATUS_SUM_MASK)
#define CSR_SSTATUS_SUM_GET(x) (((uint32_t)(x) & CSR_SSTATUS_SUM_MASK) >> CSR_SSTATUS_SUM_SHIFT)

/*
 * XS (RO)
 *
 * XS holds the status of the architectural states (ACE registers) of ACE instructions. The value of this field is zero if ACE extension is not configured.
 * This field is primarily managed by software. The processor hardware assists the state managements in two regards:
 * Illegal instruction exceptions are triggeredwhen XS is Off.
 * XS is updated to the Dirty state with the execution of ACE instructions when XS is not Off.
 * Changing the setting of this field has no effect on the contents of ACE states. In particular, setting XS to Off does not destroy the states, nor does setting XS to Initial clear the contents.
 * The same copy of XS bits are shared by both mstatus and sstatus. Normally the supervisor mode privileged software would use the XS bits to manage deferred context switches of ACE states. Machine mode software should be more conservative in managing context switches using XS bits
 * 0:Off
 * 1:Initial
 * 2:Clean
 * 3:Dirty
 */
#define CSR_SSTATUS_XS_MASK (0x18000UL)
#define CSR_SSTATUS_XS_SHIFT (15U)
#define CSR_SSTATUS_XS_GET(x) (((uint32_t)(x) & CSR_SSTATUS_XS_MASK) >> CSR_SSTATUS_XS_SHIFT)

/*
 * FS (RW)
 *
 * FS holds the status of the architectural states of the floating-point unit, including the fcsr CSR and f0 – f31 floating-point data registers. The value of this field is zero and read-only if the processor does not have FPU.
 * This field is primarily managed by software. The processor hardware assists the state managements in two regards:
 * Attempts to access fcsr or any f register raise an illegal-instruction exception when FS is Off.
 * Otherwise, FS is updated to the Dirty state by any instruction that updates fcsr or any f register.
 * Changing the setting of this field has no effect on the contents of the floating-point register states. In particular, setting FS to Off does not destroy the states, nor does setting FS to Initial clear the contents.
 * The same copy of FS bits are shared by both mstatus and sstatus. Normally the supervisor mode privileged software would use the FS bits to manage deferred context switches of FPU states. Machine mode software should be more conservative in managing context switches using FS bits.
 * 0:Off
 * 1:Initial
 * 2:Clean
 * 3:Dirty
 */
#define CSR_SSTATUS_FS_MASK (0x6000U)
#define CSR_SSTATUS_FS_SHIFT (13U)
#define CSR_SSTATUS_FS_SET(x) (((uint32_t)(x) << CSR_SSTATUS_FS_SHIFT) & CSR_SSTATUS_FS_MASK)
#define CSR_SSTATUS_FS_GET(x) (((uint32_t)(x) & CSR_SSTATUS_FS_MASK) >> CSR_SSTATUS_FS_SHIFT)

/*
 * SPP (RW)
 *
 * SPP holds the privilege mode prior to a trap. Encoding is 1 for S-mode and 0 for U-mode.
 */
#define CSR_SSTATUS_SPP_MASK (0x100U)
#define CSR_SSTATUS_SPP_SHIFT (8U)
#define CSR_SSTATUS_SPP_SET(x) (((uint32_t)(x) << CSR_SSTATUS_SPP_SHIFT) & CSR_SSTATUS_SPP_MASK)
#define CSR_SSTATUS_SPP_GET(x) (((uint32_t)(x) & CSR_SSTATUS_SPP_MASK) >> CSR_SSTATUS_SPP_SHIFT)

/*
 * SPIE (RW)
 *
 * SPIE holds the value of the SIE bit prior to a trap.
 */
#define CSR_SSTATUS_SPIE_MASK (0x20U)
#define CSR_SSTATUS_SPIE_SHIFT (5U)
#define CSR_SSTATUS_SPIE_SET(x) (((uint32_t)(x) << CSR_SSTATUS_SPIE_SHIFT) & CSR_SSTATUS_SPIE_MASK)
#define CSR_SSTATUS_SPIE_GET(x) (((uint32_t)(x) & CSR_SSTATUS_SPIE_MASK) >> CSR_SSTATUS_SPIE_SHIFT)

/*
 * UPIE (RW)
 *
 * UPIE holds the value of the UIE bit prior to a trap.
 */
#define CSR_SSTATUS_UPIE_MASK (0x10U)
#define CSR_SSTATUS_UPIE_SHIFT (4U)
#define CSR_SSTATUS_UPIE_SET(x) (((uint32_t)(x) << CSR_SSTATUS_UPIE_SHIFT) & CSR_SSTATUS_UPIE_MASK)
#define CSR_SSTATUS_UPIE_GET(x) (((uint32_t)(x) & CSR_SSTATUS_UPIE_MASK) >> CSR_SSTATUS_UPIE_SHIFT)

/*
 * SIE (RW)
 *
 * S mode interrupt enable bit
 * 0 Disabled
 * 1 Enabled
 */
#define CSR_SSTATUS_SIE_MASK (0x2U)
#define CSR_SSTATUS_SIE_SHIFT (1U)
#define CSR_SSTATUS_SIE_SET(x) (((uint32_t)(x) << CSR_SSTATUS_SIE_SHIFT) & CSR_SSTATUS_SIE_MASK)
#define CSR_SSTATUS_SIE_GET(x) (((uint32_t)(x) & CSR_SSTATUS_SIE_MASK) >> CSR_SSTATUS_SIE_SHIFT)

/*
 * UIE (RW)
 *
 * U mode interrupt enable bit.
 * 0 Disabled
 * 1 Enabled
 */
#define CSR_SSTATUS_UIE_MASK (0x1U)
#define CSR_SSTATUS_UIE_SHIFT (0U)
#define CSR_SSTATUS_UIE_SET(x) (((uint32_t)(x) << CSR_SSTATUS_UIE_SHIFT) & CSR_SSTATUS_UIE_MASK)
#define CSR_SSTATUS_UIE_GET(x) (((uint32_t)(x) & CSR_SSTATUS_UIE_MASK) >> CSR_SSTATUS_UIE_SHIFT)

/* Bitfield definition for register: SEDELEG */
/*
 * SPF (RW)
 *
 * SPF indicates whether a Store/AMO Page Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_SPF_MASK (0x8000U)
#define CSR_SEDELEG_SPF_SHIFT (15U)
#define CSR_SEDELEG_SPF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_SPF_SHIFT) & CSR_SEDELEG_SPF_MASK)
#define CSR_SEDELEG_SPF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_SPF_MASK) >> CSR_SEDELEG_SPF_SHIFT)

/*
 * LPF (RW)
 *
 * LPF indicates whether a Load Page Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_LPF_MASK (0x2000U)
#define CSR_SEDELEG_LPF_SHIFT (13U)
#define CSR_SEDELEG_LPF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_LPF_SHIFT) & CSR_SEDELEG_LPF_MASK)
#define CSR_SEDELEG_LPF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_LPF_MASK) >> CSR_SEDELEG_LPF_SHIFT)

/*
 * IPF (RW)
 *
 * IPF indicates whether an Instruction Page Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_IPF_MASK (0x1000U)
#define CSR_SEDELEG_IPF_SHIFT (12U)
#define CSR_SEDELEG_IPF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_IPF_SHIFT) & CSR_SEDELEG_IPF_MASK)
#define CSR_SEDELEG_IPF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_IPF_MASK) >> CSR_SEDELEG_IPF_SHIFT)

/*
 * UEC (RW)
 *
 * UEC indicates whether an exception triggered by environment call from U-mode will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_UEC_MASK (0x100U)
#define CSR_SEDELEG_UEC_SHIFT (8U)
#define CSR_SEDELEG_UEC_SET(x) (((uint32_t)(x) << CSR_SEDELEG_UEC_SHIFT) & CSR_SEDELEG_UEC_MASK)
#define CSR_SEDELEG_UEC_GET(x) (((uint32_t)(x) & CSR_SEDELEG_UEC_MASK) >> CSR_SEDELEG_UEC_SHIFT)

/*
 * SAF (RW)
 *
 * SAF indicates whether a Store/AMO Access Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_SAF_MASK (0x80U)
#define CSR_SEDELEG_SAF_SHIFT (7U)
#define CSR_SEDELEG_SAF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_SAF_SHIFT) & CSR_SEDELEG_SAF_MASK)
#define CSR_SEDELEG_SAF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_SAF_MASK) >> CSR_SEDELEG_SAF_SHIFT)

/*
 * SAM (RW)
 *
 * SAM indicates whether a Store/AMO Address Misaligned exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_SAM_MASK (0x40U)
#define CSR_SEDELEG_SAM_SHIFT (6U)
#define CSR_SEDELEG_SAM_SET(x) (((uint32_t)(x) << CSR_SEDELEG_SAM_SHIFT) & CSR_SEDELEG_SAM_MASK)
#define CSR_SEDELEG_SAM_GET(x) (((uint32_t)(x) & CSR_SEDELEG_SAM_MASK) >> CSR_SEDELEG_SAM_SHIFT)

/*
 * LAF (RW)
 *
 * LAF indicates whether a Load Access Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_LAF_MASK (0x20U)
#define CSR_SEDELEG_LAF_SHIFT (5U)
#define CSR_SEDELEG_LAF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_LAF_SHIFT) & CSR_SEDELEG_LAF_MASK)
#define CSR_SEDELEG_LAF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_LAF_MASK) >> CSR_SEDELEG_LAF_SHIFT)

/*
 * LAM (RW)
 *
 * LAM indicates whether a Load Address Misaligned exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_LAM_MASK (0x10U)
#define CSR_SEDELEG_LAM_SHIFT (4U)
#define CSR_SEDELEG_LAM_SET(x) (((uint32_t)(x) << CSR_SEDELEG_LAM_SHIFT) & CSR_SEDELEG_LAM_MASK)
#define CSR_SEDELEG_LAM_GET(x) (((uint32_t)(x) & CSR_SEDELEG_LAM_MASK) >> CSR_SEDELEG_LAM_SHIFT)

/*
 * B (RW)
 *
 * B indicates whether an exception triggered by breakpoint will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_B_MASK (0x8U)
#define CSR_SEDELEG_B_SHIFT (3U)
#define CSR_SEDELEG_B_SET(x) (((uint32_t)(x) << CSR_SEDELEG_B_SHIFT) & CSR_SEDELEG_B_MASK)
#define CSR_SEDELEG_B_GET(x) (((uint32_t)(x) & CSR_SEDELEG_B_MASK) >> CSR_SEDELEG_B_SHIFT)

/*
 * II (RW)
 *
 * II indicates whether an Illegal Instruction exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_II_MASK (0x4U)
#define CSR_SEDELEG_II_SHIFT (2U)
#define CSR_SEDELEG_II_SET(x) (((uint32_t)(x) << CSR_SEDELEG_II_SHIFT) & CSR_SEDELEG_II_MASK)
#define CSR_SEDELEG_II_GET(x) (((uint32_t)(x) & CSR_SEDELEG_II_MASK) >> CSR_SEDELEG_II_SHIFT)

/*
 * IAF (RW)
 *
 * IAF indicates whether an Instruction Access Fault exception will be delegated to U-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_IAF_MASK (0x2U)
#define CSR_SEDELEG_IAF_SHIFT (1U)
#define CSR_SEDELEG_IAF_SET(x) (((uint32_t)(x) << CSR_SEDELEG_IAF_SHIFT) & CSR_SEDELEG_IAF_MASK)
#define CSR_SEDELEG_IAF_GET(x) (((uint32_t)(x) & CSR_SEDELEG_IAF_MASK) >> CSR_SEDELEG_IAF_SHIFT)

/*
 * IAM (RW)
 *
 * IAM indicates whether an Instruction Address Misaligned exception will be delegated to U-mode..
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SEDELEG_IAM_MASK (0x1U)
#define CSR_SEDELEG_IAM_SHIFT (0U)
#define CSR_SEDELEG_IAM_SET(x) (((uint32_t)(x) << CSR_SEDELEG_IAM_SHIFT) & CSR_SEDELEG_IAM_MASK)
#define CSR_SEDELEG_IAM_GET(x) (((uint32_t)(x) & CSR_SEDELEG_IAM_MASK) >> CSR_SEDELEG_IAM_SHIFT)

/* Bitfield definition for register: SIDELEG */
/*
 * UEI (RW)
 *
 * UEI indicates whether an U-mode external interrupt will be delegated to S-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SIDELEG_UEI_MASK (0x100U)
#define CSR_SIDELEG_UEI_SHIFT (8U)
#define CSR_SIDELEG_UEI_SET(x) (((uint32_t)(x) << CSR_SIDELEG_UEI_SHIFT) & CSR_SIDELEG_UEI_MASK)
#define CSR_SIDELEG_UEI_GET(x) (((uint32_t)(x) & CSR_SIDELEG_UEI_MASK) >> CSR_SIDELEG_UEI_SHIFT)

/*
 * UTI (RW)
 *
 * UTI indicates whether an U-mode timer interrupt will be delegated to S-mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SIDELEG_UTI_MASK (0x10U)
#define CSR_SIDELEG_UTI_SHIFT (4U)
#define CSR_SIDELEG_UTI_SET(x) (((uint32_t)(x) << CSR_SIDELEG_UTI_SHIFT) & CSR_SIDELEG_UTI_MASK)
#define CSR_SIDELEG_UTI_GET(x) (((uint32_t)(x) & CSR_SIDELEG_UTI_MASK) >> CSR_SIDELEG_UTI_SHIFT)

/*
 * USI (RW)
 *
 * USI indicates whether an U-mode software interrupt will be delegated to S-mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_SIDELEG_USI_MASK (0x1U)
#define CSR_SIDELEG_USI_SHIFT (0U)
#define CSR_SIDELEG_USI_SET(x) (((uint32_t)(x) << CSR_SIDELEG_USI_SHIFT) & CSR_SIDELEG_USI_MASK)
#define CSR_SIDELEG_USI_GET(x) (((uint32_t)(x) & CSR_SIDELEG_USI_MASK) >> CSR_SIDELEG_USI_SHIFT)

/* Bitfield definition for register: SIE */
/*
 * SEIE (RW)
 *
 * S mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_SEIE_MASK (0x200U)
#define CSR_SIE_SEIE_SHIFT (9U)
#define CSR_SIE_SEIE_SET(x) (((uint32_t)(x) << CSR_SIE_SEIE_SHIFT) & CSR_SIE_SEIE_MASK)
#define CSR_SIE_SEIE_GET(x) (((uint32_t)(x) & CSR_SIE_SEIE_MASK) >> CSR_SIE_SEIE_SHIFT)

/*
 * UEIE (RW)
 *
 * U mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_UEIE_MASK (0x100U)
#define CSR_SIE_UEIE_SHIFT (8U)
#define CSR_SIE_UEIE_SET(x) (((uint32_t)(x) << CSR_SIE_UEIE_SHIFT) & CSR_SIE_UEIE_MASK)
#define CSR_SIE_UEIE_GET(x) (((uint32_t)(x) & CSR_SIE_UEIE_MASK) >> CSR_SIE_UEIE_SHIFT)

/*
 * STIE (RW)
 *
 * S mode timer interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_STIE_MASK (0x20U)
#define CSR_SIE_STIE_SHIFT (5U)
#define CSR_SIE_STIE_SET(x) (((uint32_t)(x) << CSR_SIE_STIE_SHIFT) & CSR_SIE_STIE_MASK)
#define CSR_SIE_STIE_GET(x) (((uint32_t)(x) & CSR_SIE_STIE_MASK) >> CSR_SIE_STIE_SHIFT)

/*
 * UTIE (RW)
 *
 * U mode timer interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_UTIE_MASK (0x10U)
#define CSR_SIE_UTIE_SHIFT (4U)
#define CSR_SIE_UTIE_SET(x) (((uint32_t)(x) << CSR_SIE_UTIE_SHIFT) & CSR_SIE_UTIE_MASK)
#define CSR_SIE_UTIE_GET(x) (((uint32_t)(x) & CSR_SIE_UTIE_MASK) >> CSR_SIE_UTIE_SHIFT)

/*
 * SSIE (RW)
 *
 * S mode software interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_SSIE_MASK (0x2U)
#define CSR_SIE_SSIE_SHIFT (1U)
#define CSR_SIE_SSIE_SET(x) (((uint32_t)(x) << CSR_SIE_SSIE_SHIFT) & CSR_SIE_SSIE_MASK)
#define CSR_SIE_SSIE_GET(x) (((uint32_t)(x) & CSR_SIE_SSIE_MASK) >> CSR_SIE_SSIE_SHIFT)

/*
 * USIE (RW)
 *
 * U mode software interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_SIE_USIE_MASK (0x1U)
#define CSR_SIE_USIE_SHIFT (0U)
#define CSR_SIE_USIE_SET(x) (((uint32_t)(x) << CSR_SIE_USIE_SHIFT) & CSR_SIE_USIE_MASK)
#define CSR_SIE_USIE_GET(x) (((uint32_t)(x) & CSR_SIE_USIE_MASK) >> CSR_SIE_USIE_SHIFT)

/* Bitfield definition for register: STVEC */
/*
 * BASE_31_2 (RW)
 *
 * Base address for interrupt and exception handlers. See description above for alignment requirements when PLIC is in the vector mode.
 */
#define CSR_STVEC_BASE_31_2_MASK (0xFFFFFFFCUL)
#define CSR_STVEC_BASE_31_2_SHIFT (2U)
#define CSR_STVEC_BASE_31_2_SET(x) (((uint32_t)(x) << CSR_STVEC_BASE_31_2_SHIFT) & CSR_STVEC_BASE_31_2_MASK)
#define CSR_STVEC_BASE_31_2_GET(x) (((uint32_t)(x) & CSR_STVEC_BASE_31_2_MASK) >> CSR_STVEC_BASE_31_2_SHIFT)

/* Bitfield definition for register: SSCRATCH */
/*
 * SSCRATCH (RW)
 *
 * Scratch register storage.
 */
#define CSR_SSCRATCH_SSCRATCH_MASK (0xFFFFFFFFUL)
#define CSR_SSCRATCH_SSCRATCH_SHIFT (0U)
#define CSR_SSCRATCH_SSCRATCH_SET(x) (((uint32_t)(x) << CSR_SSCRATCH_SSCRATCH_SHIFT) & CSR_SSCRATCH_SSCRATCH_MASK)
#define CSR_SSCRATCH_SSCRATCH_GET(x) (((uint32_t)(x) & CSR_SSCRATCH_SSCRATCH_MASK) >> CSR_SSCRATCH_SSCRATCH_SHIFT)

/* Bitfield definition for register: SEPC */
/*
 * EPC (RW)
 *
 * Exception program counter.
 */
#define CSR_SEPC_EPC_MASK (0xFFFFFFFEUL)
#define CSR_SEPC_EPC_SHIFT (1U)
#define CSR_SEPC_EPC_SET(x) (((uint32_t)(x) << CSR_SEPC_EPC_SHIFT) & CSR_SEPC_EPC_MASK)
#define CSR_SEPC_EPC_GET(x) (((uint32_t)(x) & CSR_SEPC_EPC_MASK) >> CSR_SEPC_EPC_SHIFT)

/* Bitfield definition for register: SCAUSE */
/*
 * INTERRUPT (RW)
 *
 * Interrupt.
 */
#define CSR_SCAUSE_INTERRUPT_MASK (0x80000000UL)
#define CSR_SCAUSE_INTERRUPT_SHIFT (31U)
#define CSR_SCAUSE_INTERRUPT_SET(x) (((uint32_t)(x) << CSR_SCAUSE_INTERRUPT_SHIFT) & CSR_SCAUSE_INTERRUPT_MASK)
#define CSR_SCAUSE_INTERRUPT_GET(x) (((uint32_t)(x) & CSR_SCAUSE_INTERRUPT_MASK) >> CSR_SCAUSE_INTERRUPT_SHIFT)

/*
 * EXCEPTION_CODE (RW)
 *
 * Exception Code.
 * When interrupt is 1:
 * 0:User software interrupt
 * 1:Supervisor software interrupt
 * 4:User timer interrupt
 * 5:Supervisor timer interrupt
 * 8:User external interrupt
 * 9:Supervisor external interrupt
 * 256+16:Slave port ECC error interrupt (S-mode)
 * 256+17:Bus write transaction error interrupt (S-mode)
 * 256+18:Performance monitor overflow interrupt(S-mode)
 * When interrupt is 0:
 * 0:Instruction address misaligned
 * 1:Instruction access fault
 * 2:Illegal instruction
 * 3:Breakpoint
 * 4:Load address misaligned
 * 5:Load access fault
 * 6:Store/AMO address misaligned
 * 7:Store/AMO access fault
 * 8:Environment call from U-mode
 * 9:Environment call from S-mode
 * 11:10:Reserved
 * 12:Instruction page fault
 * 13:Load page fault
 * 14:Reserved
 * 15:Store/AMO page fault
 * 32:Stack overflow exception
 * 33:Stack underflow exception
 * 40-47:Reserved
 */
#define CSR_SCAUSE_EXCEPTION_CODE_MASK (0x3FFU)
#define CSR_SCAUSE_EXCEPTION_CODE_SHIFT (0U)
#define CSR_SCAUSE_EXCEPTION_CODE_SET(x) (((uint32_t)(x) << CSR_SCAUSE_EXCEPTION_CODE_SHIFT) & CSR_SCAUSE_EXCEPTION_CODE_MASK)
#define CSR_SCAUSE_EXCEPTION_CODE_GET(x) (((uint32_t)(x) & CSR_SCAUSE_EXCEPTION_CODE_MASK) >> CSR_SCAUSE_EXCEPTION_CODE_SHIFT)

/* Bitfield definition for register: STVAL */
/*
 * STVAL (RW)
 *
 * Exception-specific information for software trap handling.
 */
#define CSR_STVAL_STVAL_MASK (0xFFFFFFFFUL)
#define CSR_STVAL_STVAL_SHIFT (0U)
#define CSR_STVAL_STVAL_SET(x) (((uint32_t)(x) << CSR_STVAL_STVAL_SHIFT) & CSR_STVAL_STVAL_MASK)
#define CSR_STVAL_STVAL_GET(x) (((uint32_t)(x) & CSR_STVAL_STVAL_MASK) >> CSR_STVAL_STVAL_SHIFT)

/* Bitfield definition for register: SIP */
/*
 * SEIP (RO)
 *
 * S mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_SEIP_MASK (0x200U)
#define CSR_SIP_SEIP_SHIFT (9U)
#define CSR_SIP_SEIP_GET(x) (((uint32_t)(x) & CSR_SIP_SEIP_MASK) >> CSR_SIP_SEIP_SHIFT)

/*
 * UEIP (RW)
 *
 * U mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_UEIP_MASK (0x100U)
#define CSR_SIP_UEIP_SHIFT (8U)
#define CSR_SIP_UEIP_SET(x) (((uint32_t)(x) << CSR_SIP_UEIP_SHIFT) & CSR_SIP_UEIP_MASK)
#define CSR_SIP_UEIP_GET(x) (((uint32_t)(x) & CSR_SIP_UEIP_MASK) >> CSR_SIP_UEIP_SHIFT)

/*
 * STIP (RO)
 *
 * S mode timer interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_STIP_MASK (0x20U)
#define CSR_SIP_STIP_SHIFT (5U)
#define CSR_SIP_STIP_GET(x) (((uint32_t)(x) & CSR_SIP_STIP_MASK) >> CSR_SIP_STIP_SHIFT)

/*
 * UTIP (RO)
 *
 * U mode timer interrupt pending bit
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_UTIP_MASK (0x10U)
#define CSR_SIP_UTIP_SHIFT (4U)
#define CSR_SIP_UTIP_GET(x) (((uint32_t)(x) & CSR_SIP_UTIP_MASK) >> CSR_SIP_UTIP_SHIFT)

/*
 * SSIP (RW)
 *
 * S mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_SSIP_MASK (0x2U)
#define CSR_SIP_SSIP_SHIFT (1U)
#define CSR_SIP_SSIP_SET(x) (((uint32_t)(x) << CSR_SIP_SSIP_SHIFT) & CSR_SIP_SSIP_MASK)
#define CSR_SIP_SSIP_GET(x) (((uint32_t)(x) & CSR_SIP_SSIP_MASK) >> CSR_SIP_SSIP_SHIFT)

/*
 * USIP (RW)
 *
 * U mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_SIP_USIP_MASK (0x1U)
#define CSR_SIP_USIP_SHIFT (0U)
#define CSR_SIP_USIP_SET(x) (((uint32_t)(x) << CSR_SIP_USIP_SHIFT) & CSR_SIP_USIP_MASK)
#define CSR_SIP_USIP_GET(x) (((uint32_t)(x) & CSR_SIP_USIP_MASK) >> CSR_SIP_USIP_SHIFT)

/* Bitfield definition for register: SATP */
/*
 * MODE (RW)
 *
 * MODE holds the page translation mode. When MODE is Bare, virtual addresses are equal to physical addresses in S-mode. When MMU is
 * not supported in the product, this CSR will be
 * hardwired to 0.
 * 0:No page translation
 * 1:Page-based 32-bit virtual addressing
 */
#define CSR_SATP_MODE_MASK (0x80000000UL)
#define CSR_SATP_MODE_SHIFT (31U)
#define CSR_SATP_MODE_SET(x) (((uint32_t)(x) << CSR_SATP_MODE_SHIFT) & CSR_SATP_MODE_MASK)
#define CSR_SATP_MODE_GET(x) (((uint32_t)(x) & CSR_SATP_MODE_MASK) >> CSR_SATP_MODE_SHIFT)

/*
 * ASID (RW)
 *
 * ASID holds the address space identifier.
 */
#define CSR_SATP_ASID_MASK (0x7FC00000UL)
#define CSR_SATP_ASID_SHIFT (22U)
#define CSR_SATP_ASID_SET(x) (((uint32_t)(x) << CSR_SATP_ASID_SHIFT) & CSR_SATP_ASID_MASK)
#define CSR_SATP_ASID_GET(x) (((uint32_t)(x) & CSR_SATP_ASID_MASK) >> CSR_SATP_ASID_SHIFT)

/*
 * PPN (RW)
 *
 * PPN holds the physical page number of the root page table.
 */
#define CSR_SATP_PPN_MASK (0x3FFFFFUL)
#define CSR_SATP_PPN_SHIFT (0U)
#define CSR_SATP_PPN_SET(x) (((uint32_t)(x) << CSR_SATP_PPN_SHIFT) & CSR_SATP_PPN_MASK)
#define CSR_SATP_PPN_GET(x) (((uint32_t)(x) & CSR_SATP_PPN_MASK) >> CSR_SATP_PPN_SHIFT)

/* Bitfield definition for register: MSTATUS */
/*
 * SD (RO)
 *
 * SD summarizes whether either the FS field or XS field is dirty.
 */
#define CSR_MSTATUS_SD_MASK (0x80000000UL)
#define CSR_MSTATUS_SD_SHIFT (31U)
#define CSR_MSTATUS_SD_GET(x) (((uint32_t)(x) & CSR_MSTATUS_SD_MASK) >> CSR_MSTATUS_SD_SHIFT)

/*
 * TSR (RW)
 *
 * TSR controls whether executing SRET instructions in S-mode will raise illegal instruction exceptions. It is hardwired to 0 when S-mode is not supported.
 * 0: Normal execution
 * 1: Raising exceptions
 */
#define CSR_MSTATUS_TSR_MASK (0x400000UL)
#define CSR_MSTATUS_TSR_SHIFT (22U)
#define CSR_MSTATUS_TSR_SET(x) (((uint32_t)(x) << CSR_MSTATUS_TSR_SHIFT) & CSR_MSTATUS_TSR_MASK)
#define CSR_MSTATUS_TSR_GET(x) (((uint32_t)(x) & CSR_MSTATUS_TSR_MASK) >> CSR_MSTATUS_TSR_SHIFT)

/*
 * TW (RW)
 *
 * TW controls whether executing WFI instructions in S-mode will raise illegal instruction exceptions. It is hardwired to 0 when S-mode is not supported.
 * 0: Normal execution
 * 1: Raising exceptions
 */
#define CSR_MSTATUS_TW_MASK (0x200000UL)
#define CSR_MSTATUS_TW_SHIFT (21U)
#define CSR_MSTATUS_TW_SET(x) (((uint32_t)(x) << CSR_MSTATUS_TW_SHIFT) & CSR_MSTATUS_TW_MASK)
#define CSR_MSTATUS_TW_GET(x) (((uint32_t)(x) & CSR_MSTATUS_TW_MASK) >> CSR_MSTATUS_TW_SHIFT)

/*
 * TVM (RW)
 *
 * TVM controls whether performing certain virtual memory operations in S-mode will raise illegal instruction exceptions. The operations include accessing the satp register and executing the SFENCE.VMA instruction. It is hardwired to 0 when S-mode is not supported.
 * 0:Normal execution
 * 1:Raising exceptions
 */
#define CSR_MSTATUS_TVM_MASK (0x100000UL)
#define CSR_MSTATUS_TVM_SHIFT (20U)
#define CSR_MSTATUS_TVM_SET(x) (((uint32_t)(x) << CSR_MSTATUS_TVM_SHIFT) & CSR_MSTATUS_TVM_MASK)
#define CSR_MSTATUS_TVM_GET(x) (((uint32_t)(x) & CSR_MSTATUS_TVM_MASK) >> CSR_MSTATUS_TVM_SHIFT)

/*
 * MXR (RW)
 *
 * MXR controls whether execute-only pages are readable. It has no effect when page-based virtual memory is not in effect
 * 0:Execute-only pages are not readable
 * 1:Execute-only pages are readable
 */
#define CSR_MSTATUS_MXR_MASK (0x80000UL)
#define CSR_MSTATUS_MXR_SHIFT (19U)
#define CSR_MSTATUS_MXR_SET(x) (((uint32_t)(x) << CSR_MSTATUS_MXR_SHIFT) & CSR_MSTATUS_MXR_MASK)
#define CSR_MSTATUS_MXR_GET(x) (((uint32_t)(x) & CSR_MSTATUS_MXR_MASK) >> CSR_MSTATUS_MXR_SHIFT)

/*
 * SUM (RW)
 *
 * SUM controls whether a S-mode load/store instruction to a user accessible page is allowed or not when page translation is enabled. It is in effect in two scenarios: (a) M-mode with MPRV=1 and MPP=S, and (b) in S-mode. It has no effect when page-based virtual memory is not in effect. A page is user accessible when the U bit of the corresponding PTE entry is 1. It is hardwired to 0 when S-mode is not supported.
 * 0:Not Allowed
 * 1:Allowed
 */
#define CSR_MSTATUS_SUM_MASK (0x40000UL)
#define CSR_MSTATUS_SUM_SHIFT (18U)
#define CSR_MSTATUS_SUM_SET(x) (((uint32_t)(x) << CSR_MSTATUS_SUM_SHIFT) & CSR_MSTATUS_SUM_MASK)
#define CSR_MSTATUS_SUM_GET(x) (((uint32_t)(x) & CSR_MSTATUS_SUM_MASK) >> CSR_MSTATUS_SUM_SHIFT)

/*
 * MPRV (RW)
 *
 * When the MPRV bit is set, the memory access privilege for load and store are specified by the MPP field. When U-mode is not available, this field is hardwired to 0.
 */
#define CSR_MSTATUS_MPRV_MASK (0x20000UL)
#define CSR_MSTATUS_MPRV_SHIFT (17U)
#define CSR_MSTATUS_MPRV_SET(x) (((uint32_t)(x) << CSR_MSTATUS_MPRV_SHIFT) & CSR_MSTATUS_MPRV_MASK)
#define CSR_MSTATUS_MPRV_GET(x) (((uint32_t)(x) & CSR_MSTATUS_MPRV_MASK) >> CSR_MSTATUS_MPRV_SHIFT)

/*
 * XS (RO)
 *
 * XS holds the status of the architectural states (ACE registers) of ACE instructions. The value of this field is zero if ACE extension is not configured. This field is primarily managed by software. The processor hardware assists the state managements in two regards:
 * Illegal instruction exceptions are triggered when XS is Off.
 * XS is updated to the Dirty state with the execution of ACE instructions when XS is not Off. Changing the setting of this field has no effect on the contents of ACE states. In particular, setting XS to Off does not destroy the states, nor does setting XS to Initial clear the contents.
 * 0:Off
 * 1:Initial
 * 2:Clean
 * 3:Dirty
 */
#define CSR_MSTATUS_XS_MASK (0x18000UL)
#define CSR_MSTATUS_XS_SHIFT (15U)
#define CSR_MSTATUS_XS_GET(x) (((uint32_t)(x) & CSR_MSTATUS_XS_MASK) >> CSR_MSTATUS_XS_SHIFT)

/*
 * FS (RW)
 *
 * FS holds the status of the architectural states of the floating-point unit, including the fcsr CSR and f0 – f31 floating-point data registers. The value of this field is zero and read-only if the processor does not have FPU. This field is primarily managed by software. The processor hardware assists the state
 * managements in two regards:
 * Attempts to access fcsr or any f register raise an illegal-instruction exception when FS is Off.
 * FS is updated to the Dirty state with the execution of any instruction that updates fcsr or any f register when FS is Initial or Clean. Changing the setting of this field has no effect on the contents of the floating-point register states. In particular, setting FS to Off does not destroy the states, nor does setting FS to Initial clear the contents.
 * 0:Off
 * 1:Initial
 * 2:Clean
 * 3:Dirty
 */
#define CSR_MSTATUS_FS_MASK (0x6000U)
#define CSR_MSTATUS_FS_SHIFT (13U)
#define CSR_MSTATUS_FS_SET(x) (((uint32_t)(x) << CSR_MSTATUS_FS_SHIFT) & CSR_MSTATUS_FS_MASK)
#define CSR_MSTATUS_FS_GET(x) (((uint32_t)(x) & CSR_MSTATUS_FS_MASK) >> CSR_MSTATUS_FS_SHIFT)

/*
 * MPP (RW)
 *
 * MPP holds the privilege mode prior to a trap. Encoding for privilege mode is described in Table5. When U-mode is not available, this field is hardwired to 3.
 */
#define CSR_MSTATUS_MPP_MASK (0x1800U)
#define CSR_MSTATUS_MPP_SHIFT (11U)
#define CSR_MSTATUS_MPP_SET(x) (((uint32_t)(x) << CSR_MSTATUS_MPP_SHIFT) & CSR_MSTATUS_MPP_MASK)
#define CSR_MSTATUS_MPP_GET(x) (((uint32_t)(x) & CSR_MSTATUS_MPP_MASK) >> CSR_MSTATUS_MPP_SHIFT)

/*
 * SPP (RW)
 *
 * SPP holds the privilege mode prior to a trap. Encoding is 1 for S-mode and 0 for U-mode.
 */
#define CSR_MSTATUS_SPP_MASK (0x100U)
#define CSR_MSTATUS_SPP_SHIFT (8U)
#define CSR_MSTATUS_SPP_SET(x) (((uint32_t)(x) << CSR_MSTATUS_SPP_SHIFT) & CSR_MSTATUS_SPP_MASK)
#define CSR_MSTATUS_SPP_GET(x) (((uint32_t)(x) & CSR_MSTATUS_SPP_MASK) >> CSR_MSTATUS_SPP_SHIFT)

/*
 * MPIE (RW)
 *
 * MPIE holds the value of the MIE bit prior to a trap.
 */
#define CSR_MSTATUS_MPIE_MASK (0x80U)
#define CSR_MSTATUS_MPIE_SHIFT (7U)
#define CSR_MSTATUS_MPIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_MPIE_SHIFT) & CSR_MSTATUS_MPIE_MASK)
#define CSR_MSTATUS_MPIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_MPIE_MASK) >> CSR_MSTATUS_MPIE_SHIFT)

/*
 * SPIE (RW)
 *
 * SPIE holds the value of the SIE bit prior to a trap.
 */
#define CSR_MSTATUS_SPIE_MASK (0x20U)
#define CSR_MSTATUS_SPIE_SHIFT (5U)
#define CSR_MSTATUS_SPIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_SPIE_SHIFT) & CSR_MSTATUS_SPIE_MASK)
#define CSR_MSTATUS_SPIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_SPIE_MASK) >> CSR_MSTATUS_SPIE_SHIFT)

/*
 * UPIE (RW)
 *
 * UPIE holds the value of the UIE bit prior to a trap.
 */
#define CSR_MSTATUS_UPIE_MASK (0x10U)
#define CSR_MSTATUS_UPIE_SHIFT (4U)
#define CSR_MSTATUS_UPIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_UPIE_SHIFT) & CSR_MSTATUS_UPIE_MASK)
#define CSR_MSTATUS_UPIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_UPIE_MASK) >> CSR_MSTATUS_UPIE_SHIFT)

/*
 * MIE (RW)
 *
 * M mode interrupt enable bit.
 * 0: Disabled
 * 1: Enabled
 */
#define CSR_MSTATUS_MIE_MASK (0x8U)
#define CSR_MSTATUS_MIE_SHIFT (3U)
#define CSR_MSTATUS_MIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_MIE_SHIFT) & CSR_MSTATUS_MIE_MASK)
#define CSR_MSTATUS_MIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_MIE_MASK) >> CSR_MSTATUS_MIE_SHIFT)

/*
 * SIE (RW)
 *
 * S mode interrupt enable bit.
 * 0: Disabled
 * 1: Enabled
 */
#define CSR_MSTATUS_SIE_MASK (0x2U)
#define CSR_MSTATUS_SIE_SHIFT (1U)
#define CSR_MSTATUS_SIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_SIE_SHIFT) & CSR_MSTATUS_SIE_MASK)
#define CSR_MSTATUS_SIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_SIE_MASK) >> CSR_MSTATUS_SIE_SHIFT)

/*
 * UIE (RW)
 *
 * U mode interrupt enable bit.
 * 0: Disabled
 * 1: Enabled
 */
#define CSR_MSTATUS_UIE_MASK (0x1U)
#define CSR_MSTATUS_UIE_SHIFT (0U)
#define CSR_MSTATUS_UIE_SET(x) (((uint32_t)(x) << CSR_MSTATUS_UIE_SHIFT) & CSR_MSTATUS_UIE_MASK)
#define CSR_MSTATUS_UIE_GET(x) (((uint32_t)(x) & CSR_MSTATUS_UIE_MASK) >> CSR_MSTATUS_UIE_SHIFT)

/* Bitfield definition for register: MISA */
/*
 * BASE (RO)
 *
 * The general-purpose register width of the native base integer ISA.
 * 0:Reserved
 * 1:32
 * 2:64
 * 3:128
 */
#define CSR_MISA_BASE_MASK (0xC0000000UL)
#define CSR_MISA_BASE_SHIFT (30U)
#define CSR_MISA_BASE_GET(x) (((uint32_t)(x) & CSR_MISA_BASE_MASK) >> CSR_MISA_BASE_SHIFT)

/*
 * Z (RO)
 *
 * Reserved
 */
#define CSR_MISA_Z_MASK (0x2000000UL)
#define CSR_MISA_Z_SHIFT (25U)
#define CSR_MISA_Z_GET(x) (((uint32_t)(x) & CSR_MISA_Z_MASK) >> CSR_MISA_Z_SHIFT)

/*
 * Y (RO)
 *
 * Reserved
 */
#define CSR_MISA_Y_MASK (0x1000000UL)
#define CSR_MISA_Y_SHIFT (24U)
#define CSR_MISA_Y_GET(x) (((uint32_t)(x) & CSR_MISA_Y_MASK) >> CSR_MISA_Y_SHIFT)

/*
 * X (RO)
 *
 * Non-standard extensions present
 */
#define CSR_MISA_X_MASK (0x800000UL)
#define CSR_MISA_X_SHIFT (23U)
#define CSR_MISA_X_GET(x) (((uint32_t)(x) & CSR_MISA_X_MASK) >> CSR_MISA_X_SHIFT)

/*
 * W (RO)
 *
 * Reserved
 */
#define CSR_MISA_W_MASK (0x400000UL)
#define CSR_MISA_W_SHIFT (22U)
#define CSR_MISA_W_GET(x) (((uint32_t)(x) & CSR_MISA_W_MASK) >> CSR_MISA_W_SHIFT)

/*
 * V (RO)
 *
 * Tentatively reserved for Vector extension
 */
#define CSR_MISA_V_MASK (0x200000UL)
#define CSR_MISA_V_SHIFT (21U)
#define CSR_MISA_V_GET(x) (((uint32_t)(x) & CSR_MISA_V_MASK) >> CSR_MISA_V_SHIFT)

/*
 * U (RO)
 *
 * User mode implemented
 * 0:Machine
 * 1:Machine + User / Machine + Supervisor + User
 */
#define CSR_MISA_U_MASK (0x100000UL)
#define CSR_MISA_U_SHIFT (20U)
#define CSR_MISA_U_GET(x) (((uint32_t)(x) & CSR_MISA_U_MASK) >> CSR_MISA_U_SHIFT)

/*
 * T (RO)
 *
 * Tentatively reserved for Transactional Memory extension
 */
#define CSR_MISA_T_MASK (0x80000UL)
#define CSR_MISA_T_SHIFT (19U)
#define CSR_MISA_T_GET(x) (((uint32_t)(x) & CSR_MISA_T_MASK) >> CSR_MISA_T_SHIFT)

/*
 * S (RO)
 *
 * Supervisor mode implemented
 * 0:Machine / Machine + User
 * 1:Machine + Supervisor + User
 */
#define CSR_MISA_S_MASK (0x40000UL)
#define CSR_MISA_S_SHIFT (18U)
#define CSR_MISA_S_GET(x) (((uint32_t)(x) & CSR_MISA_S_MASK) >> CSR_MISA_S_SHIFT)

/*
 * R (RO)
 *
 * Reserved
 */
#define CSR_MISA_R_MASK (0x20000UL)
#define CSR_MISA_R_SHIFT (17U)
#define CSR_MISA_R_GET(x) (((uint32_t)(x) & CSR_MISA_R_MASK) >> CSR_MISA_R_SHIFT)

/*
 * Q (RO)
 *
 * Quad-precision floating-point extension
 */
#define CSR_MISA_Q_MASK (0x10000UL)
#define CSR_MISA_Q_SHIFT (16U)
#define CSR_MISA_Q_GET(x) (((uint32_t)(x) & CSR_MISA_Q_MASK) >> CSR_MISA_Q_SHIFT)

/*
 * P (RO)
 *
 * Tentatively reserved for Packed-SIMD extension
 */
#define CSR_MISA_P_MASK (0x8000U)
#define CSR_MISA_P_SHIFT (15U)
#define CSR_MISA_P_GET(x) (((uint32_t)(x) & CSR_MISA_P_MASK) >> CSR_MISA_P_SHIFT)

/*
 * O (RO)
 *
 * Reserved
 */
#define CSR_MISA_O_MASK (0x4000U)
#define CSR_MISA_O_SHIFT (14U)
#define CSR_MISA_O_GET(x) (((uint32_t)(x) & CSR_MISA_O_MASK) >> CSR_MISA_O_SHIFT)

/*
 * N (RO)
 *
 * User-level interrupts supported
 * 0:no
 * 1:yes
 */
#define CSR_MISA_N_MASK (0x2000U)
#define CSR_MISA_N_SHIFT (13U)
#define CSR_MISA_N_GET(x) (((uint32_t)(x) & CSR_MISA_N_MASK) >> CSR_MISA_N_SHIFT)

/*
 * M (RO)
 *
 * Integer Multiply/Divide extension
 */
#define CSR_MISA_M_MASK (0x1000U)
#define CSR_MISA_M_SHIFT (12U)
#define CSR_MISA_M_GET(x) (((uint32_t)(x) & CSR_MISA_M_MASK) >> CSR_MISA_M_SHIFT)

/*
 * L (RO)
 *
 * Tentatively reserved for Decimal Floating-Point extension
 */
#define CSR_MISA_L_MASK (0x800U)
#define CSR_MISA_L_SHIFT (11U)
#define CSR_MISA_L_GET(x) (((uint32_t)(x) & CSR_MISA_L_MASK) >> CSR_MISA_L_SHIFT)

/*
 * K (RO)
 *
 * Reserved
 */
#define CSR_MISA_K_MASK (0x400U)
#define CSR_MISA_K_SHIFT (10U)
#define CSR_MISA_K_GET(x) (((uint32_t)(x) & CSR_MISA_K_MASK) >> CSR_MISA_K_SHIFT)

/*
 * J (RO)
 *
 * Tentatively reserved for Dynamically Translated Languages extension
 */
#define CSR_MISA_J_MASK (0x200U)
#define CSR_MISA_J_SHIFT (9U)
#define CSR_MISA_J_GET(x) (((uint32_t)(x) & CSR_MISA_J_MASK) >> CSR_MISA_J_SHIFT)

/*
 * I (RO)
 *
 * RV32I/64I/128I base ISA
 */
#define CSR_MISA_I_MASK (0x100U)
#define CSR_MISA_I_SHIFT (8U)
#define CSR_MISA_I_GET(x) (((uint32_t)(x) & CSR_MISA_I_MASK) >> CSR_MISA_I_SHIFT)

/*
 * H (RO)
 *
 * Reserved
 */
#define CSR_MISA_H_MASK (0x80U)
#define CSR_MISA_H_SHIFT (7U)
#define CSR_MISA_H_GET(x) (((uint32_t)(x) & CSR_MISA_H_MASK) >> CSR_MISA_H_SHIFT)

/*
 * G (RO)
 *
 * Additional standard extensions present
 */
#define CSR_MISA_G_MASK (0x40U)
#define CSR_MISA_G_SHIFT (6U)
#define CSR_MISA_G_GET(x) (((uint32_t)(x) & CSR_MISA_G_MASK) >> CSR_MISA_G_SHIFT)

/*
 * F (RO)
 *
 * Single-precision floating-point extension
 * 0:none
 * 1:double+single precision / single precision
 */
#define CSR_MISA_F_MASK (0x20U)
#define CSR_MISA_F_SHIFT (5U)
#define CSR_MISA_F_GET(x) (((uint32_t)(x) & CSR_MISA_F_MASK) >> CSR_MISA_F_SHIFT)

/*
 * E (RO)
 *
 * RV32E base ISA
 */
#define CSR_MISA_E_MASK (0x10U)
#define CSR_MISA_E_SHIFT (4U)
#define CSR_MISA_E_GET(x) (((uint32_t)(x) & CSR_MISA_E_MASK) >> CSR_MISA_E_SHIFT)

/*
 * D (RO)
 *
 * Double-precision floating-point extension
 * 0:single precision / none
 * 1:double+single precision
 */
#define CSR_MISA_D_MASK (0x8U)
#define CSR_MISA_D_SHIFT (3U)
#define CSR_MISA_D_GET(x) (((uint32_t)(x) & CSR_MISA_D_MASK) >> CSR_MISA_D_SHIFT)

/*
 * C (RO)
 *
 * Compressed extension
 */
#define CSR_MISA_C_MASK (0x4U)
#define CSR_MISA_C_SHIFT (2U)
#define CSR_MISA_C_GET(x) (((uint32_t)(x) & CSR_MISA_C_MASK) >> CSR_MISA_C_SHIFT)

/*
 * B (RO)
 *
 * Tentatively reserved for Bit operations extension
 */
#define CSR_MISA_B_MASK (0x2U)
#define CSR_MISA_B_SHIFT (1U)
#define CSR_MISA_B_GET(x) (((uint32_t)(x) & CSR_MISA_B_MASK) >> CSR_MISA_B_SHIFT)

/*
 * A (RO)
 *
 * Atomic extension
 * 0:no
 * 1:yes
 */
#define CSR_MISA_A_MASK (0x1U)
#define CSR_MISA_A_SHIFT (0U)
#define CSR_MISA_A_GET(x) (((uint32_t)(x) & CSR_MISA_A_MASK) >> CSR_MISA_A_SHIFT)

/* Bitfield definition for register: MEDELEG */
/*
 * SPF (RW)
 *
 * SPF indicates whether a Store/AMO Page Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_SPF_MASK (0x8000U)
#define CSR_MEDELEG_SPF_SHIFT (15U)
#define CSR_MEDELEG_SPF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_SPF_SHIFT) & CSR_MEDELEG_SPF_MASK)
#define CSR_MEDELEG_SPF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_SPF_MASK) >> CSR_MEDELEG_SPF_SHIFT)

/*
 * LPF (RW)
 *
 * LPF indicates whether a Load Page Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_LPF_MASK (0x2000U)
#define CSR_MEDELEG_LPF_SHIFT (13U)
#define CSR_MEDELEG_LPF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_LPF_SHIFT) & CSR_MEDELEG_LPF_MASK)
#define CSR_MEDELEG_LPF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_LPF_MASK) >> CSR_MEDELEG_LPF_SHIFT)

/*
 * IPF (RW)
 *
 * IPF indicates whether an Instruction Page Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_IPF_MASK (0x1000U)
#define CSR_MEDELEG_IPF_SHIFT (12U)
#define CSR_MEDELEG_IPF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_IPF_SHIFT) & CSR_MEDELEG_IPF_MASK)
#define CSR_MEDELEG_IPF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_IPF_MASK) >> CSR_MEDELEG_IPF_SHIFT)

/*
 * SEC (RW)
 *
 * SEC indicates whether an exception triggered by environment call from S-mode will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_SEC_MASK (0x200U)
#define CSR_MEDELEG_SEC_SHIFT (9U)
#define CSR_MEDELEG_SEC_SET(x) (((uint32_t)(x) << CSR_MEDELEG_SEC_SHIFT) & CSR_MEDELEG_SEC_MASK)
#define CSR_MEDELEG_SEC_GET(x) (((uint32_t)(x) & CSR_MEDELEG_SEC_MASK) >> CSR_MEDELEG_SEC_SHIFT)

/*
 * UEC (RW)
 *
 * UEC indicates whether an exception triggered by environment call from U-mode will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_UEC_MASK (0x100U)
#define CSR_MEDELEG_UEC_SHIFT (8U)
#define CSR_MEDELEG_UEC_SET(x) (((uint32_t)(x) << CSR_MEDELEG_UEC_SHIFT) & CSR_MEDELEG_UEC_MASK)
#define CSR_MEDELEG_UEC_GET(x) (((uint32_t)(x) & CSR_MEDELEG_UEC_MASK) >> CSR_MEDELEG_UEC_SHIFT)

/*
 * SAF (RW)
 *
 * SAF indicates whether a Store/AMO Access Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_SAF_MASK (0x80U)
#define CSR_MEDELEG_SAF_SHIFT (7U)
#define CSR_MEDELEG_SAF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_SAF_SHIFT) & CSR_MEDELEG_SAF_MASK)
#define CSR_MEDELEG_SAF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_SAF_MASK) >> CSR_MEDELEG_SAF_SHIFT)

/*
 * SAM (RW)
 *
 * SAM indicates whether a Store/AMO Address Misaligned exception will be delegated to S-mode
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_SAM_MASK (0x40U)
#define CSR_MEDELEG_SAM_SHIFT (6U)
#define CSR_MEDELEG_SAM_SET(x) (((uint32_t)(x) << CSR_MEDELEG_SAM_SHIFT) & CSR_MEDELEG_SAM_MASK)
#define CSR_MEDELEG_SAM_GET(x) (((uint32_t)(x) & CSR_MEDELEG_SAM_MASK) >> CSR_MEDELEG_SAM_SHIFT)

/*
 * LAF (RW)
 *
 * LAF indicates whether a Load Access Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_LAF_MASK (0x20U)
#define CSR_MEDELEG_LAF_SHIFT (5U)
#define CSR_MEDELEG_LAF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_LAF_SHIFT) & CSR_MEDELEG_LAF_MASK)
#define CSR_MEDELEG_LAF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_LAF_MASK) >> CSR_MEDELEG_LAF_SHIFT)

/*
 * LAM (RW)
 *
 * LAM indicates whether a Load Address Misaligned exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_LAM_MASK (0x10U)
#define CSR_MEDELEG_LAM_SHIFT (4U)
#define CSR_MEDELEG_LAM_SET(x) (((uint32_t)(x) << CSR_MEDELEG_LAM_SHIFT) & CSR_MEDELEG_LAM_MASK)
#define CSR_MEDELEG_LAM_GET(x) (((uint32_t)(x) & CSR_MEDELEG_LAM_MASK) >> CSR_MEDELEG_LAM_SHIFT)

/*
 * II (RW)
 *
 * II indicates whether an Illegal Instruction exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_II_MASK (0x4U)
#define CSR_MEDELEG_II_SHIFT (2U)
#define CSR_MEDELEG_II_SET(x) (((uint32_t)(x) << CSR_MEDELEG_II_SHIFT) & CSR_MEDELEG_II_MASK)
#define CSR_MEDELEG_II_GET(x) (((uint32_t)(x) & CSR_MEDELEG_II_MASK) >> CSR_MEDELEG_II_SHIFT)

/*
 * IAF (RW)
 *
 * IAF indicates whether an Instruction Access Fault exception will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_IAF_MASK (0x2U)
#define CSR_MEDELEG_IAF_SHIFT (1U)
#define CSR_MEDELEG_IAF_SET(x) (((uint32_t)(x) << CSR_MEDELEG_IAF_SHIFT) & CSR_MEDELEG_IAF_MASK)
#define CSR_MEDELEG_IAF_GET(x) (((uint32_t)(x) & CSR_MEDELEG_IAF_MASK) >> CSR_MEDELEG_IAF_SHIFT)

/*
 * IAM (RW)
 *
 * IAM indicates whether an Instruction Address Misaligned exception will be delegated to S-Mode
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MEDELEG_IAM_MASK (0x1U)
#define CSR_MEDELEG_IAM_SHIFT (0U)
#define CSR_MEDELEG_IAM_SET(x) (((uint32_t)(x) << CSR_MEDELEG_IAM_SHIFT) & CSR_MEDELEG_IAM_MASK)
#define CSR_MEDELEG_IAM_GET(x) (((uint32_t)(x) & CSR_MEDELEG_IAM_MASK) >> CSR_MEDELEG_IAM_SHIFT)

/* Bitfield definition for register: MIDELEG */
/*
 * SEI (RW)
 *
 * SEI indicates whether an S-mode external interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_SEI_MASK (0x200U)
#define CSR_MIDELEG_SEI_SHIFT (9U)
#define CSR_MIDELEG_SEI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_SEI_SHIFT) & CSR_MIDELEG_SEI_MASK)
#define CSR_MIDELEG_SEI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_SEI_MASK) >> CSR_MIDELEG_SEI_SHIFT)

/*
 * UEI (RW)
 *
 * UEI indicates whether an U-mode external interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_UEI_MASK (0x100U)
#define CSR_MIDELEG_UEI_SHIFT (8U)
#define CSR_MIDELEG_UEI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_UEI_SHIFT) & CSR_MIDELEG_UEI_MASK)
#define CSR_MIDELEG_UEI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_UEI_MASK) >> CSR_MIDELEG_UEI_SHIFT)

/*
 * STI (RW)
 *
 * STI indicates whether an S-mode timer interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_STI_MASK (0x20U)
#define CSR_MIDELEG_STI_SHIFT (5U)
#define CSR_MIDELEG_STI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_STI_SHIFT) & CSR_MIDELEG_STI_MASK)
#define CSR_MIDELEG_STI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_STI_MASK) >> CSR_MIDELEG_STI_SHIFT)

/*
 * UTI (RW)
 *
 * UTI indicates whether an U-mode timer interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_UTI_MASK (0x10U)
#define CSR_MIDELEG_UTI_SHIFT (4U)
#define CSR_MIDELEG_UTI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_UTI_SHIFT) & CSR_MIDELEG_UTI_MASK)
#define CSR_MIDELEG_UTI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_UTI_MASK) >> CSR_MIDELEG_UTI_SHIFT)

/*
 * SSI (RW)
 *
 * SSI indicates whether an S-mode software interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_SSI_MASK (0x2U)
#define CSR_MIDELEG_SSI_SHIFT (1U)
#define CSR_MIDELEG_SSI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_SSI_SHIFT) & CSR_MIDELEG_SSI_MASK)
#define CSR_MIDELEG_SSI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_SSI_MASK) >> CSR_MIDELEG_SSI_SHIFT)

/*
 * USI (RW)
 *
 * USI indicates whether an U-mode software interrupt will be delegated to S-mode.
 * 0:Not delegate
 * 1:delegate
 */
#define CSR_MIDELEG_USI_MASK (0x1U)
#define CSR_MIDELEG_USI_SHIFT (0U)
#define CSR_MIDELEG_USI_SET(x) (((uint32_t)(x) << CSR_MIDELEG_USI_SHIFT) & CSR_MIDELEG_USI_MASK)
#define CSR_MIDELEG_USI_GET(x) (((uint32_t)(x) & CSR_MIDELEG_USI_MASK) >> CSR_MIDELEG_USI_SHIFT)

/* Bitfield definition for register: MIE */
/*
 * PMOVI (RW)
 *
 * Performance monitor overflow local interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_PMOVI_MASK (0x40000UL)
#define CSR_MIE_PMOVI_SHIFT (18U)
#define CSR_MIE_PMOVI_SET(x) (((uint32_t)(x) << CSR_MIE_PMOVI_SHIFT) & CSR_MIE_PMOVI_MASK)
#define CSR_MIE_PMOVI_GET(x) (((uint32_t)(x) & CSR_MIE_PMOVI_MASK) >> CSR_MIE_PMOVI_SHIFT)

/*
 * BWEI (RW)
 *
 * Bus read/write transaction error local interrupt enable bit. The processor may receive bus errors on load/store instructions or cache writebacks.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_BWEI_MASK (0x20000UL)
#define CSR_MIE_BWEI_SHIFT (17U)
#define CSR_MIE_BWEI_SET(x) (((uint32_t)(x) << CSR_MIE_BWEI_SHIFT) & CSR_MIE_BWEI_MASK)
#define CSR_MIE_BWEI_GET(x) (((uint32_t)(x) & CSR_MIE_BWEI_MASK) >> CSR_MIE_BWEI_SHIFT)

/*
 * IMECCI (RW)
 *
 * Imprecise ECC error local interrupt enable bit. The processor may receive imprecise ECC errors on slave port accesses or cache writebacks.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_IMECCI_MASK (0x10000UL)
#define CSR_MIE_IMECCI_SHIFT (16U)
#define CSR_MIE_IMECCI_SET(x) (((uint32_t)(x) << CSR_MIE_IMECCI_SHIFT) & CSR_MIE_IMECCI_MASK)
#define CSR_MIE_IMECCI_GET(x) (((uint32_t)(x) & CSR_MIE_IMECCI_MASK) >> CSR_MIE_IMECCI_SHIFT)

/*
 * MEIE (RW)
 *
 * M mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_MEIE_MASK (0x800U)
#define CSR_MIE_MEIE_SHIFT (11U)
#define CSR_MIE_MEIE_SET(x) (((uint32_t)(x) << CSR_MIE_MEIE_SHIFT) & CSR_MIE_MEIE_MASK)
#define CSR_MIE_MEIE_GET(x) (((uint32_t)(x) & CSR_MIE_MEIE_MASK) >> CSR_MIE_MEIE_SHIFT)

/*
 * SEIE (RW)
 *
 * S mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_SEIE_MASK (0x200U)
#define CSR_MIE_SEIE_SHIFT (9U)
#define CSR_MIE_SEIE_SET(x) (((uint32_t)(x) << CSR_MIE_SEIE_SHIFT) & CSR_MIE_SEIE_MASK)
#define CSR_MIE_SEIE_GET(x) (((uint32_t)(x) & CSR_MIE_SEIE_MASK) >> CSR_MIE_SEIE_SHIFT)

/*
 * UEIE (RW)
 *
 * U mode external interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_UEIE_MASK (0x100U)
#define CSR_MIE_UEIE_SHIFT (8U)
#define CSR_MIE_UEIE_SET(x) (((uint32_t)(x) << CSR_MIE_UEIE_SHIFT) & CSR_MIE_UEIE_MASK)
#define CSR_MIE_UEIE_GET(x) (((uint32_t)(x) & CSR_MIE_UEIE_MASK) >> CSR_MIE_UEIE_SHIFT)

/*
 * MTIE (RW)
 *
 * M mode timer interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_MTIE_MASK (0x80U)
#define CSR_MIE_MTIE_SHIFT (7U)
#define CSR_MIE_MTIE_SET(x) (((uint32_t)(x) << CSR_MIE_MTIE_SHIFT) & CSR_MIE_MTIE_MASK)
#define CSR_MIE_MTIE_GET(x) (((uint32_t)(x) & CSR_MIE_MTIE_MASK) >> CSR_MIE_MTIE_SHIFT)

/*
 * STIE (RW)
 *
 * S mode timer interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_STIE_MASK (0x20U)
#define CSR_MIE_STIE_SHIFT (5U)
#define CSR_MIE_STIE_SET(x) (((uint32_t)(x) << CSR_MIE_STIE_SHIFT) & CSR_MIE_STIE_MASK)
#define CSR_MIE_STIE_GET(x) (((uint32_t)(x) & CSR_MIE_STIE_MASK) >> CSR_MIE_STIE_SHIFT)

/*
 * UTIE (RW)
 *
 * U mode timer interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_UTIE_MASK (0x10U)
#define CSR_MIE_UTIE_SHIFT (4U)
#define CSR_MIE_UTIE_SET(x) (((uint32_t)(x) << CSR_MIE_UTIE_SHIFT) & CSR_MIE_UTIE_MASK)
#define CSR_MIE_UTIE_GET(x) (((uint32_t)(x) & CSR_MIE_UTIE_MASK) >> CSR_MIE_UTIE_SHIFT)

/*
 * MSIE (RW)
 *
 * M mode software interrupt enable bit
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_MSIE_MASK (0x8U)
#define CSR_MIE_MSIE_SHIFT (3U)
#define CSR_MIE_MSIE_SET(x) (((uint32_t)(x) << CSR_MIE_MSIE_SHIFT) & CSR_MIE_MSIE_MASK)
#define CSR_MIE_MSIE_GET(x) (((uint32_t)(x) & CSR_MIE_MSIE_MASK) >> CSR_MIE_MSIE_SHIFT)

/*
 * SSIE (RW)
 *
 * S mode software interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_SSIE_MASK (0x2U)
#define CSR_MIE_SSIE_SHIFT (1U)
#define CSR_MIE_SSIE_SET(x) (((uint32_t)(x) << CSR_MIE_SSIE_SHIFT) & CSR_MIE_SSIE_MASK)
#define CSR_MIE_SSIE_GET(x) (((uint32_t)(x) & CSR_MIE_SSIE_MASK) >> CSR_MIE_SSIE_SHIFT)

/*
 * USIE (RW)
 *
 * U mode software interrupt enable bit.
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MIE_USIE_MASK (0x1U)
#define CSR_MIE_USIE_SHIFT (0U)
#define CSR_MIE_USIE_SET(x) (((uint32_t)(x) << CSR_MIE_USIE_SHIFT) & CSR_MIE_USIE_MASK)
#define CSR_MIE_USIE_GET(x) (((uint32_t)(x) & CSR_MIE_USIE_MASK) >> CSR_MIE_USIE_SHIFT)

/* Bitfield definition for register: MTVEC */
/*
 * BASE_31_2 (RW)
 *
 * Base address for interrupt and exception handlers. See description above for alignment requirements when PLIC is in the vector mode
 */
#define CSR_MTVEC_BASE_31_2_MASK (0xFFFFFFFCUL)
#define CSR_MTVEC_BASE_31_2_SHIFT (2U)
#define CSR_MTVEC_BASE_31_2_SET(x) (((uint32_t)(x) << CSR_MTVEC_BASE_31_2_SHIFT) & CSR_MTVEC_BASE_31_2_MASK)
#define CSR_MTVEC_BASE_31_2_GET(x) (((uint32_t)(x) & CSR_MTVEC_BASE_31_2_MASK) >> CSR_MTVEC_BASE_31_2_SHIFT)

/* Bitfield definition for register: MCOUNTEREN */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_HPM6_MASK (0x40U)
#define CSR_MCOUNTEREN_HPM6_SHIFT (6U)
#define CSR_MCOUNTEREN_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_HPM6_SHIFT) & CSR_MCOUNTEREN_HPM6_MASK)
#define CSR_MCOUNTEREN_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_HPM6_MASK) >> CSR_MCOUNTEREN_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_HPM5_MASK (0x20U)
#define CSR_MCOUNTEREN_HPM5_SHIFT (5U)
#define CSR_MCOUNTEREN_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_HPM5_SHIFT) & CSR_MCOUNTEREN_HPM5_MASK)
#define CSR_MCOUNTEREN_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_HPM5_MASK) >> CSR_MCOUNTEREN_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_HPM4_MASK (0x10U)
#define CSR_MCOUNTEREN_HPM4_SHIFT (4U)
#define CSR_MCOUNTEREN_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_HPM4_SHIFT) & CSR_MCOUNTEREN_HPM4_MASK)
#define CSR_MCOUNTEREN_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_HPM4_MASK) >> CSR_MCOUNTEREN_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_HPM3_MASK (0x8U)
#define CSR_MCOUNTEREN_HPM3_SHIFT (3U)
#define CSR_MCOUNTEREN_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_HPM3_SHIFT) & CSR_MCOUNTEREN_HPM3_MASK)
#define CSR_MCOUNTEREN_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_HPM3_MASK) >> CSR_MCOUNTEREN_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_IR_MASK (0x4U)
#define CSR_MCOUNTEREN_IR_SHIFT (2U)
#define CSR_MCOUNTEREN_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_IR_SHIFT) & CSR_MCOUNTEREN_IR_MASK)
#define CSR_MCOUNTEREN_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_IR_MASK) >> CSR_MCOUNTEREN_IR_SHIFT)

/*
 * TM (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_TM_MASK (0x2U)
#define CSR_MCOUNTEREN_TM_SHIFT (1U)
#define CSR_MCOUNTEREN_TM_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_TM_SHIFT) & CSR_MCOUNTEREN_TM_MASK)
#define CSR_MCOUNTEREN_TM_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_TM_MASK) >> CSR_MCOUNTEREN_TM_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEREN_CY_MASK (0x1U)
#define CSR_MCOUNTEREN_CY_SHIFT (0U)
#define CSR_MCOUNTEREN_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTEREN_CY_SHIFT) & CSR_MCOUNTEREN_CY_MASK)
#define CSR_MCOUNTEREN_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTEREN_CY_MASK) >> CSR_MCOUNTEREN_CY_SHIFT)

/* Bitfield definition for register: MHPMEVENT3 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT3_SEL_MASK (0x1F0U)
#define CSR_MHPMEVENT3_SEL_SHIFT (4U)
#define CSR_MHPMEVENT3_SEL_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT3_SEL_SHIFT) & CSR_MHPMEVENT3_SEL_MASK)
#define CSR_MHPMEVENT3_SEL_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT3_SEL_MASK) >> CSR_MHPMEVENT3_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT3_TYPE_MASK (0xFU)
#define CSR_MHPMEVENT3_TYPE_SHIFT (0U)
#define CSR_MHPMEVENT3_TYPE_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT3_TYPE_SHIFT) & CSR_MHPMEVENT3_TYPE_MASK)
#define CSR_MHPMEVENT3_TYPE_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT3_TYPE_MASK) >> CSR_MHPMEVENT3_TYPE_SHIFT)

/* Bitfield definition for register: MHPMEVENT4 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT4_SEL_MASK (0x1F0U)
#define CSR_MHPMEVENT4_SEL_SHIFT (4U)
#define CSR_MHPMEVENT4_SEL_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT4_SEL_SHIFT) & CSR_MHPMEVENT4_SEL_MASK)
#define CSR_MHPMEVENT4_SEL_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT4_SEL_MASK) >> CSR_MHPMEVENT4_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT4_TYPE_MASK (0xFU)
#define CSR_MHPMEVENT4_TYPE_SHIFT (0U)
#define CSR_MHPMEVENT4_TYPE_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT4_TYPE_SHIFT) & CSR_MHPMEVENT4_TYPE_MASK)
#define CSR_MHPMEVENT4_TYPE_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT4_TYPE_MASK) >> CSR_MHPMEVENT4_TYPE_SHIFT)

/* Bitfield definition for register: MHPMEVENT5 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT5_SEL_MASK (0x1F0U)
#define CSR_MHPMEVENT5_SEL_SHIFT (4U)
#define CSR_MHPMEVENT5_SEL_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT5_SEL_SHIFT) & CSR_MHPMEVENT5_SEL_MASK)
#define CSR_MHPMEVENT5_SEL_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT5_SEL_MASK) >> CSR_MHPMEVENT5_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT5_TYPE_MASK (0xFU)
#define CSR_MHPMEVENT5_TYPE_SHIFT (0U)
#define CSR_MHPMEVENT5_TYPE_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT5_TYPE_SHIFT) & CSR_MHPMEVENT5_TYPE_MASK)
#define CSR_MHPMEVENT5_TYPE_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT5_TYPE_MASK) >> CSR_MHPMEVENT5_TYPE_SHIFT)

/* Bitfield definition for register: MHPMEVENT6 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT6_SEL_MASK (0x1F0U)
#define CSR_MHPMEVENT6_SEL_SHIFT (4U)
#define CSR_MHPMEVENT6_SEL_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT6_SEL_SHIFT) & CSR_MHPMEVENT6_SEL_MASK)
#define CSR_MHPMEVENT6_SEL_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT6_SEL_MASK) >> CSR_MHPMEVENT6_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_MHPMEVENT6_TYPE_MASK (0xFU)
#define CSR_MHPMEVENT6_TYPE_SHIFT (0U)
#define CSR_MHPMEVENT6_TYPE_SET(x) (((uint32_t)(x) << CSR_MHPMEVENT6_TYPE_SHIFT) & CSR_MHPMEVENT6_TYPE_MASK)
#define CSR_MHPMEVENT6_TYPE_GET(x) (((uint32_t)(x) & CSR_MHPMEVENT6_TYPE_MASK) >> CSR_MHPMEVENT6_TYPE_SHIFT)

/* Bitfield definition for register: MSCRATCH */
/*
 * MSCRATCH (RW)
 *
 * Scratch register storage.
 */
#define CSR_MSCRATCH_MSCRATCH_MASK (0xFFFFFFFFUL)
#define CSR_MSCRATCH_MSCRATCH_SHIFT (0U)
#define CSR_MSCRATCH_MSCRATCH_SET(x) (((uint32_t)(x) << CSR_MSCRATCH_MSCRATCH_SHIFT) & CSR_MSCRATCH_MSCRATCH_MASK)
#define CSR_MSCRATCH_MSCRATCH_GET(x) (((uint32_t)(x) & CSR_MSCRATCH_MSCRATCH_MASK) >> CSR_MSCRATCH_MSCRATCH_SHIFT)

/* Bitfield definition for register: MEPC */
/*
 * EPC (RW)
 *
 * Exception program counter.
 */
#define CSR_MEPC_EPC_MASK (0xFFFFFFFEUL)
#define CSR_MEPC_EPC_SHIFT (1U)
#define CSR_MEPC_EPC_SET(x) (((uint32_t)(x) << CSR_MEPC_EPC_SHIFT) & CSR_MEPC_EPC_MASK)
#define CSR_MEPC_EPC_GET(x) (((uint32_t)(x) & CSR_MEPC_EPC_MASK) >> CSR_MEPC_EPC_SHIFT)

/* Bitfield definition for register: MCAUSE */
/*
 * INTERRUPT (RW)
 *
 * Interrupt
 */
#define CSR_MCAUSE_INTERRUPT_MASK (0x80000000UL)
#define CSR_MCAUSE_INTERRUPT_SHIFT (31U)
#define CSR_MCAUSE_INTERRUPT_SET(x) (((uint32_t)(x) << CSR_MCAUSE_INTERRUPT_SHIFT) & CSR_MCAUSE_INTERRUPT_MASK)
#define CSR_MCAUSE_INTERRUPT_GET(x) (((uint32_t)(x) & CSR_MCAUSE_INTERRUPT_MASK) >> CSR_MCAUSE_INTERRUPT_SHIFT)

/*
 * EXCEPTION_CODE (RW)
 *
 * Exception code
 * When interrupt is 1, the value means:
 * 0:User software interrupt
 * 1:Supervisor software interrupt
 * 3:Machine software interrupt
 * 4:User timer interrupt
 * 5:Supervisor timer interrupt
 * 7:Machine timer interrupt
 * 8:User external interrupt
 * 9:Supervisor external interrupt
 * 11:Machine external interrupt
 * 16:Imprecise ECC error interrupt (slave port accesses, D-Cache evictions, and nonblocking load/stores) (M-mode)
 * 17:Bus read/write transaction error interrupt (M-mode)
 * 18:Performance monitor overflow interrupt (M-mode)
 * 256+16:Imprecise ECC error interrupt (slave port accesses, D-Cache evictions, and nonblocking load/stores) (S-mode)
 * 256+17:Bus write transaction error interrupt (S-mode)
 * 256+18:Performance monitor overflow interrupt (S-mode)
 * When interrupt bit is 0, the value means:
 * 0:Instruction address misaligned
 * 1:Instruction access fault
 * 2:Illegal instruction
 * 3:Breakpoint
 * 4:Load address misaligned
 * 5:Load access fault
 * 6:Store/AMO address misaligned
 * 7:Store/AMO access fault
 * 8:Environment call from U-mode
 * 9:Environment call from S-mode
 * 11:Environment call from M-mode
 * 32:Stack overflow exception
 * 33:Stack underflow exception
 * 40-47:Reserved
 */
#define CSR_MCAUSE_EXCEPTION_CODE_MASK (0xFFFU)
#define CSR_MCAUSE_EXCEPTION_CODE_SHIFT (0U)
#define CSR_MCAUSE_EXCEPTION_CODE_SET(x) (((uint32_t)(x) << CSR_MCAUSE_EXCEPTION_CODE_SHIFT) & CSR_MCAUSE_EXCEPTION_CODE_MASK)
#define CSR_MCAUSE_EXCEPTION_CODE_GET(x) (((uint32_t)(x) & CSR_MCAUSE_EXCEPTION_CODE_MASK) >> CSR_MCAUSE_EXCEPTION_CODE_SHIFT)

/* Bitfield definition for register: MTVAL */
/*
 * MTVAL (RW)
 *
 * Exception-specific information for software trap handling.
 */
#define CSR_MTVAL_MTVAL_MASK (0xFFFFFFFFUL)
#define CSR_MTVAL_MTVAL_SHIFT (0U)
#define CSR_MTVAL_MTVAL_SET(x) (((uint32_t)(x) << CSR_MTVAL_MTVAL_SHIFT) & CSR_MTVAL_MTVAL_MASK)
#define CSR_MTVAL_MTVAL_GET(x) (((uint32_t)(x) & CSR_MTVAL_MTVAL_MASK) >> CSR_MTVAL_MTVAL_SHIFT)

/* Bitfield definition for register: MIP */
/*
 * PMOVI (RW)
 *
 * Performance monitor overflow local interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_PMOVI_MASK (0x40000UL)
#define CSR_MIP_PMOVI_SHIFT (18U)
#define CSR_MIP_PMOVI_SET(x) (((uint32_t)(x) << CSR_MIP_PMOVI_SHIFT) & CSR_MIP_PMOVI_MASK)
#define CSR_MIP_PMOVI_GET(x) (((uint32_t)(x) & CSR_MIP_PMOVI_MASK) >> CSR_MIP_PMOVI_SHIFT)

/*
 * BWEI (RW)
 *
 * Bus read/write transaction error local interrupt pending bit. The processor may receive bus errors on load/store instructions or cache writebacks.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_BWEI_MASK (0x20000UL)
#define CSR_MIP_BWEI_SHIFT (17U)
#define CSR_MIP_BWEI_SET(x) (((uint32_t)(x) << CSR_MIP_BWEI_SHIFT) & CSR_MIP_BWEI_MASK)
#define CSR_MIP_BWEI_GET(x) (((uint32_t)(x) & CSR_MIP_BWEI_MASK) >> CSR_MIP_BWEI_SHIFT)

/*
 * IMECCI (RW)
 *
 * Imprecise ECC error local interrupt enable bit. The processor may receive imprecise ECC errors on slave port accesses or cache writebacks.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_IMECCI_MASK (0x10000UL)
#define CSR_MIP_IMECCI_SHIFT (16U)
#define CSR_MIP_IMECCI_SET(x) (((uint32_t)(x) << CSR_MIP_IMECCI_SHIFT) & CSR_MIP_IMECCI_MASK)
#define CSR_MIP_IMECCI_GET(x) (((uint32_t)(x) & CSR_MIP_IMECCI_MASK) >> CSR_MIP_IMECCI_SHIFT)

/*
 * MEIP (RW)
 *
 * M mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_MEIP_MASK (0x800U)
#define CSR_MIP_MEIP_SHIFT (11U)
#define CSR_MIP_MEIP_SET(x) (((uint32_t)(x) << CSR_MIP_MEIP_SHIFT) & CSR_MIP_MEIP_MASK)
#define CSR_MIP_MEIP_GET(x) (((uint32_t)(x) & CSR_MIP_MEIP_MASK) >> CSR_MIP_MEIP_SHIFT)

/*
 * SEIP (RW)
 *
 * S mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_SEIP_MASK (0x200U)
#define CSR_MIP_SEIP_SHIFT (9U)
#define CSR_MIP_SEIP_SET(x) (((uint32_t)(x) << CSR_MIP_SEIP_SHIFT) & CSR_MIP_SEIP_MASK)
#define CSR_MIP_SEIP_GET(x) (((uint32_t)(x) & CSR_MIP_SEIP_MASK) >> CSR_MIP_SEIP_SHIFT)

/*
 * UEIP (RW)
 *
 * U mode external interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_UEIP_MASK (0x100U)
#define CSR_MIP_UEIP_SHIFT (8U)
#define CSR_MIP_UEIP_SET(x) (((uint32_t)(x) << CSR_MIP_UEIP_SHIFT) & CSR_MIP_UEIP_MASK)
#define CSR_MIP_UEIP_GET(x) (((uint32_t)(x) & CSR_MIP_UEIP_MASK) >> CSR_MIP_UEIP_SHIFT)

/*
 * MTIP (RW)
 *
 * M mode timer interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_MTIP_MASK (0x80U)
#define CSR_MIP_MTIP_SHIFT (7U)
#define CSR_MIP_MTIP_SET(x) (((uint32_t)(x) << CSR_MIP_MTIP_SHIFT) & CSR_MIP_MTIP_MASK)
#define CSR_MIP_MTIP_GET(x) (((uint32_t)(x) & CSR_MIP_MTIP_MASK) >> CSR_MIP_MTIP_SHIFT)

/*
 * STIP (RW)
 *
 * S mode timer interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_STIP_MASK (0x20U)
#define CSR_MIP_STIP_SHIFT (5U)
#define CSR_MIP_STIP_SET(x) (((uint32_t)(x) << CSR_MIP_STIP_SHIFT) & CSR_MIP_STIP_MASK)
#define CSR_MIP_STIP_GET(x) (((uint32_t)(x) & CSR_MIP_STIP_MASK) >> CSR_MIP_STIP_SHIFT)

/*
 * UTIP (RW)
 *
 * U mode timer interrupt pending bit
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_UTIP_MASK (0x10U)
#define CSR_MIP_UTIP_SHIFT (4U)
#define CSR_MIP_UTIP_SET(x) (((uint32_t)(x) << CSR_MIP_UTIP_SHIFT) & CSR_MIP_UTIP_MASK)
#define CSR_MIP_UTIP_GET(x) (((uint32_t)(x) & CSR_MIP_UTIP_MASK) >> CSR_MIP_UTIP_SHIFT)

/*
 * MSIP (RW)
 *
 * M mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_MSIP_MASK (0x8U)
#define CSR_MIP_MSIP_SHIFT (3U)
#define CSR_MIP_MSIP_SET(x) (((uint32_t)(x) << CSR_MIP_MSIP_SHIFT) & CSR_MIP_MSIP_MASK)
#define CSR_MIP_MSIP_GET(x) (((uint32_t)(x) & CSR_MIP_MSIP_MASK) >> CSR_MIP_MSIP_SHIFT)

/*
 * SSIP (RW)
 *
 * S mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_SSIP_MASK (0x2U)
#define CSR_MIP_SSIP_SHIFT (1U)
#define CSR_MIP_SSIP_SET(x) (((uint32_t)(x) << CSR_MIP_SSIP_SHIFT) & CSR_MIP_SSIP_MASK)
#define CSR_MIP_SSIP_GET(x) (((uint32_t)(x) & CSR_MIP_SSIP_MASK) >> CSR_MIP_SSIP_SHIFT)

/*
 * USIP (RW)
 *
 * U mode software interrupt pending bit.
 * 0:Not pending
 * 1:Pending
 */
#define CSR_MIP_USIP_MASK (0x1U)
#define CSR_MIP_USIP_SHIFT (0U)
#define CSR_MIP_USIP_SET(x) (((uint32_t)(x) << CSR_MIP_USIP_SHIFT) & CSR_MIP_USIP_MASK)
#define CSR_MIP_USIP_GET(x) (((uint32_t)(x) & CSR_MIP_USIP_MASK) >> CSR_MIP_USIP_SHIFT)

/* Bitfield definition for register: PMPCFG0 */
/*
 * PMP3CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG0_PMP3CFG_MASK (0xFF000000UL)
#define CSR_PMPCFG0_PMP3CFG_SHIFT (24U)
#define CSR_PMPCFG0_PMP3CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG0_PMP3CFG_SHIFT) & CSR_PMPCFG0_PMP3CFG_MASK)
#define CSR_PMPCFG0_PMP3CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG0_PMP3CFG_MASK) >> CSR_PMPCFG0_PMP3CFG_SHIFT)

/*
 * PMP2CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG0_PMP2CFG_MASK (0xFF0000UL)
#define CSR_PMPCFG0_PMP2CFG_SHIFT (16U)
#define CSR_PMPCFG0_PMP2CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG0_PMP2CFG_SHIFT) & CSR_PMPCFG0_PMP2CFG_MASK)
#define CSR_PMPCFG0_PMP2CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG0_PMP2CFG_MASK) >> CSR_PMPCFG0_PMP2CFG_SHIFT)

/*
 * PMP1CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG0_PMP1CFG_MASK (0xFF00U)
#define CSR_PMPCFG0_PMP1CFG_SHIFT (8U)
#define CSR_PMPCFG0_PMP1CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG0_PMP1CFG_SHIFT) & CSR_PMPCFG0_PMP1CFG_MASK)
#define CSR_PMPCFG0_PMP1CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG0_PMP1CFG_MASK) >> CSR_PMPCFG0_PMP1CFG_SHIFT)

/*
 * PMP0CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG0_PMP0CFG_MASK (0xFFU)
#define CSR_PMPCFG0_PMP0CFG_SHIFT (0U)
#define CSR_PMPCFG0_PMP0CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG0_PMP0CFG_SHIFT) & CSR_PMPCFG0_PMP0CFG_MASK)
#define CSR_PMPCFG0_PMP0CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG0_PMP0CFG_MASK) >> CSR_PMPCFG0_PMP0CFG_SHIFT)

/* Bitfield definition for register: PMPCFG1 */
/*
 * PMP7CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG1_PMP7CFG_MASK (0xFF000000UL)
#define CSR_PMPCFG1_PMP7CFG_SHIFT (24U)
#define CSR_PMPCFG1_PMP7CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG1_PMP7CFG_SHIFT) & CSR_PMPCFG1_PMP7CFG_MASK)
#define CSR_PMPCFG1_PMP7CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG1_PMP7CFG_MASK) >> CSR_PMPCFG1_PMP7CFG_SHIFT)

/*
 * PMP6CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG1_PMP6CFG_MASK (0xFF0000UL)
#define CSR_PMPCFG1_PMP6CFG_SHIFT (16U)
#define CSR_PMPCFG1_PMP6CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG1_PMP6CFG_SHIFT) & CSR_PMPCFG1_PMP6CFG_MASK)
#define CSR_PMPCFG1_PMP6CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG1_PMP6CFG_MASK) >> CSR_PMPCFG1_PMP6CFG_SHIFT)

/*
 * PMP5CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG1_PMP5CFG_MASK (0xFF00U)
#define CSR_PMPCFG1_PMP5CFG_SHIFT (8U)
#define CSR_PMPCFG1_PMP5CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG1_PMP5CFG_SHIFT) & CSR_PMPCFG1_PMP5CFG_MASK)
#define CSR_PMPCFG1_PMP5CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG1_PMP5CFG_MASK) >> CSR_PMPCFG1_PMP5CFG_SHIFT)

/*
 * PMP4CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG1_PMP4CFG_MASK (0xFFU)
#define CSR_PMPCFG1_PMP4CFG_SHIFT (0U)
#define CSR_PMPCFG1_PMP4CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG1_PMP4CFG_SHIFT) & CSR_PMPCFG1_PMP4CFG_MASK)
#define CSR_PMPCFG1_PMP4CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG1_PMP4CFG_MASK) >> CSR_PMPCFG1_PMP4CFG_SHIFT)

/* Bitfield definition for register: PMPCFG2 */
/*
 * PMP11CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG2_PMP11CFG_MASK (0xFF000000UL)
#define CSR_PMPCFG2_PMP11CFG_SHIFT (24U)
#define CSR_PMPCFG2_PMP11CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG2_PMP11CFG_SHIFT) & CSR_PMPCFG2_PMP11CFG_MASK)
#define CSR_PMPCFG2_PMP11CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG2_PMP11CFG_MASK) >> CSR_PMPCFG2_PMP11CFG_SHIFT)

/*
 * PMP10CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG2_PMP10CFG_MASK (0xFF0000UL)
#define CSR_PMPCFG2_PMP10CFG_SHIFT (16U)
#define CSR_PMPCFG2_PMP10CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG2_PMP10CFG_SHIFT) & CSR_PMPCFG2_PMP10CFG_MASK)
#define CSR_PMPCFG2_PMP10CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG2_PMP10CFG_MASK) >> CSR_PMPCFG2_PMP10CFG_SHIFT)

/*
 * PMP9CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG2_PMP9CFG_MASK (0xFF00U)
#define CSR_PMPCFG2_PMP9CFG_SHIFT (8U)
#define CSR_PMPCFG2_PMP9CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG2_PMP9CFG_SHIFT) & CSR_PMPCFG2_PMP9CFG_MASK)
#define CSR_PMPCFG2_PMP9CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG2_PMP9CFG_MASK) >> CSR_PMPCFG2_PMP9CFG_SHIFT)

/*
 * PMP8CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG2_PMP8CFG_MASK (0xFFU)
#define CSR_PMPCFG2_PMP8CFG_SHIFT (0U)
#define CSR_PMPCFG2_PMP8CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG2_PMP8CFG_SHIFT) & CSR_PMPCFG2_PMP8CFG_MASK)
#define CSR_PMPCFG2_PMP8CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG2_PMP8CFG_MASK) >> CSR_PMPCFG2_PMP8CFG_SHIFT)

/* Bitfield definition for register: PMPCFG3 */
/*
 * PMP15CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG3_PMP15CFG_MASK (0xFF000000UL)
#define CSR_PMPCFG3_PMP15CFG_SHIFT (24U)
#define CSR_PMPCFG3_PMP15CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG3_PMP15CFG_SHIFT) & CSR_PMPCFG3_PMP15CFG_MASK)
#define CSR_PMPCFG3_PMP15CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG3_PMP15CFG_MASK) >> CSR_PMPCFG3_PMP15CFG_SHIFT)

/*
 * PMP14CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG3_PMP14CFG_MASK (0xFF0000UL)
#define CSR_PMPCFG3_PMP14CFG_SHIFT (16U)
#define CSR_PMPCFG3_PMP14CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG3_PMP14CFG_SHIFT) & CSR_PMPCFG3_PMP14CFG_MASK)
#define CSR_PMPCFG3_PMP14CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG3_PMP14CFG_MASK) >> CSR_PMPCFG3_PMP14CFG_SHIFT)

/*
 * PMP13CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG3_PMP13CFG_MASK (0xFF00U)
#define CSR_PMPCFG3_PMP13CFG_SHIFT (8U)
#define CSR_PMPCFG3_PMP13CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG3_PMP13CFG_SHIFT) & CSR_PMPCFG3_PMP13CFG_MASK)
#define CSR_PMPCFG3_PMP13CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG3_PMP13CFG_MASK) >> CSR_PMPCFG3_PMP13CFG_SHIFT)

/*
 * PMP12CFG (RW)
 *
 * See PMPCFG Table
 */
#define CSR_PMPCFG3_PMP12CFG_MASK (0xFFU)
#define CSR_PMPCFG3_PMP12CFG_SHIFT (0U)
#define CSR_PMPCFG3_PMP12CFG_SET(x) (((uint32_t)(x) << CSR_PMPCFG3_PMP12CFG_SHIFT) & CSR_PMPCFG3_PMP12CFG_MASK)
#define CSR_PMPCFG3_PMP12CFG_GET(x) (((uint32_t)(x) & CSR_PMPCFG3_PMP12CFG_MASK) >> CSR_PMPCFG3_PMP12CFG_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * Register Content :  Match Size(Byte)
 * aaaa. . . aaa0         8
 * aaaa. . . aa01         16
 * aaaa. . . a011         32
 * . . .                          . . .
 * aa01. . . 1111         2^{XLEN}
 * a011. . . 1111         2^{XLEN+1}
 * 0111. . . 1111         2^{XLEN+2}
 * 1111. . . 1111         2^{XLEN+3*1}
 */
#define CSR_PMPADDR0_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR0_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR0_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR0_PMPADDR_31_2_SHIFT) & CSR_PMPADDR0_PMPADDR_31_2_MASK)
#define CSR_PMPADDR0_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR0_PMPADDR_31_2_MASK) >> CSR_PMPADDR0_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR1_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR1_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR1_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR1_PMPADDR_31_2_SHIFT) & CSR_PMPADDR1_PMPADDR_31_2_MASK)
#define CSR_PMPADDR1_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR1_PMPADDR_31_2_MASK) >> CSR_PMPADDR1_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR2_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR2_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR2_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR2_PMPADDR_31_2_SHIFT) & CSR_PMPADDR2_PMPADDR_31_2_MASK)
#define CSR_PMPADDR2_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR2_PMPADDR_31_2_MASK) >> CSR_PMPADDR2_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR3_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR3_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR3_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR3_PMPADDR_31_2_SHIFT) & CSR_PMPADDR3_PMPADDR_31_2_MASK)
#define CSR_PMPADDR3_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR3_PMPADDR_31_2_MASK) >> CSR_PMPADDR3_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR4_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR4_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR4_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR4_PMPADDR_31_2_SHIFT) & CSR_PMPADDR4_PMPADDR_31_2_MASK)
#define CSR_PMPADDR4_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR4_PMPADDR_31_2_MASK) >> CSR_PMPADDR4_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR5_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR5_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR5_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR5_PMPADDR_31_2_SHIFT) & CSR_PMPADDR5_PMPADDR_31_2_MASK)
#define CSR_PMPADDR5_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR5_PMPADDR_31_2_MASK) >> CSR_PMPADDR5_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR6_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR6_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR6_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR6_PMPADDR_31_2_SHIFT) & CSR_PMPADDR6_PMPADDR_31_2_MASK)
#define CSR_PMPADDR6_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR6_PMPADDR_31_2_MASK) >> CSR_PMPADDR6_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR7_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR7_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR7_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR7_PMPADDR_31_2_SHIFT) & CSR_PMPADDR7_PMPADDR_31_2_MASK)
#define CSR_PMPADDR7_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR7_PMPADDR_31_2_MASK) >> CSR_PMPADDR7_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR8_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR8_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR8_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR8_PMPADDR_31_2_SHIFT) & CSR_PMPADDR8_PMPADDR_31_2_MASK)
#define CSR_PMPADDR8_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR8_PMPADDR_31_2_MASK) >> CSR_PMPADDR8_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR9_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR9_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR9_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR9_PMPADDR_31_2_SHIFT) & CSR_PMPADDR9_PMPADDR_31_2_MASK)
#define CSR_PMPADDR9_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR9_PMPADDR_31_2_MASK) >> CSR_PMPADDR9_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR10_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR10_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR10_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR10_PMPADDR_31_2_SHIFT) & CSR_PMPADDR10_PMPADDR_31_2_MASK)
#define CSR_PMPADDR10_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR10_PMPADDR_31_2_MASK) >> CSR_PMPADDR10_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR11_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR11_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR11_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR11_PMPADDR_31_2_SHIFT) & CSR_PMPADDR11_PMPADDR_31_2_MASK)
#define CSR_PMPADDR11_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR11_PMPADDR_31_2_MASK) >> CSR_PMPADDR11_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR12_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR12_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR12_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR12_PMPADDR_31_2_SHIFT) & CSR_PMPADDR12_PMPADDR_31_2_MASK)
#define CSR_PMPADDR12_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR12_PMPADDR_31_2_MASK) >> CSR_PMPADDR12_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR13_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR13_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR13_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR13_PMPADDR_31_2_SHIFT) & CSR_PMPADDR13_PMPADDR_31_2_MASK)
#define CSR_PMPADDR13_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR13_PMPADDR_31_2_MASK) >> CSR_PMPADDR13_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR14_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR14_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR14_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR14_PMPADDR_31_2_SHIFT) & CSR_PMPADDR14_PMPADDR_31_2_MASK)
#define CSR_PMPADDR14_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR14_PMPADDR_31_2_MASK) >> CSR_PMPADDR14_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMPADDR */
/*
 * PMPADDR_31_2 (RW)
 *
 * same as pmpaddr0
 */
#define CSR_PMPADDR15_PMPADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMPADDR15_PMPADDR_31_2_SHIFT (2U)
#define CSR_PMPADDR15_PMPADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMPADDR15_PMPADDR_31_2_SHIFT) & CSR_PMPADDR15_PMPADDR_31_2_MASK)
#define CSR_PMPADDR15_PMPADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMPADDR15_PMPADDR_31_2_MASK) >> CSR_PMPADDR15_PMPADDR_31_2_SHIFT)

/* Bitfield definition for register: TSELECT */
/*
 * TRIGGER_INDEX (RW)
 *
 * This register determines which trigger is accessible through other trigger registers.
 */
#define CSR_TSELECT_TRIGGER_INDEX_MASK (0xFFFFFFFFUL)
#define CSR_TSELECT_TRIGGER_INDEX_SHIFT (0U)
#define CSR_TSELECT_TRIGGER_INDEX_SET(x) (((uint32_t)(x) << CSR_TSELECT_TRIGGER_INDEX_SHIFT) & CSR_TSELECT_TRIGGER_INDEX_MASK)
#define CSR_TSELECT_TRIGGER_INDEX_GET(x) (((uint32_t)(x) & CSR_TSELECT_TRIGGER_INDEX_MASK) >> CSR_TSELECT_TRIGGER_INDEX_SHIFT)

/* Bitfield definition for register: TDATA1 */
/*
 * TYPE (RW)
 *
 * Indicates the trigger type.
 * 0:The selected trigger is invalid.
 * 2:The selected trigger is an address/data match trigger.
 * 3:The selected trigger is an instruction count trigger
 * 4:The selected trigger is an interrupt trigger.
 * 5:The selected trigger is an exception trigger.
 */
#define CSR_TDATA1_TYPE_MASK (0xF0000000UL)
#define CSR_TDATA1_TYPE_SHIFT (28U)
#define CSR_TDATA1_TYPE_SET(x) (((uint32_t)(x) << CSR_TDATA1_TYPE_SHIFT) & CSR_TDATA1_TYPE_MASK)
#define CSR_TDATA1_TYPE_GET(x) (((uint32_t)(x) & CSR_TDATA1_TYPE_MASK) >> CSR_TDATA1_TYPE_SHIFT)

/*
 * DMODE (RW)
 *
 * Setting this field to indicate the trigger is used by Debug Mode.
 * 0:Both Debug-mode and M-mode can write the currently selected trigger registers.
 * 1:Only Debug Mode can write the currently selected trigger registers. Writes from M-mode is ignored.
 */
#define CSR_TDATA1_DMODE_MASK (0x8000000UL)
#define CSR_TDATA1_DMODE_SHIFT (27U)
#define CSR_TDATA1_DMODE_SET(x) (((uint32_t)(x) << CSR_TDATA1_DMODE_SHIFT) & CSR_TDATA1_DMODE_MASK)
#define CSR_TDATA1_DMODE_GET(x) (((uint32_t)(x) & CSR_TDATA1_DMODE_MASK) >> CSR_TDATA1_DMODE_SHIFT)

/*
 * DATA (RW)
 *
 * Trigger-specific data
 */
#define CSR_TDATA1_DATA_MASK (0x7FFFFFFUL)
#define CSR_TDATA1_DATA_SHIFT (0U)
#define CSR_TDATA1_DATA_SET(x) (((uint32_t)(x) << CSR_TDATA1_DATA_SHIFT) & CSR_TDATA1_DATA_MASK)
#define CSR_TDATA1_DATA_GET(x) (((uint32_t)(x) & CSR_TDATA1_DATA_MASK) >> CSR_TDATA1_DATA_SHIFT)

/* Bitfield definition for register: MCONTROL */
/*
 * TYPE (RW)
 *
 * Indicates the trigger type.
 * 0:The selected trigger is invalid.
 * 2:The selected trigger is an address/data match trigger.
 */
#define CSR_MCONTROL_TYPE_MASK (0xF0000000UL)
#define CSR_MCONTROL_TYPE_SHIFT (28U)
#define CSR_MCONTROL_TYPE_SET(x) (((uint32_t)(x) << CSR_MCONTROL_TYPE_SHIFT) & CSR_MCONTROL_TYPE_MASK)
#define CSR_MCONTROL_TYPE_GET(x) (((uint32_t)(x) & CSR_MCONTROL_TYPE_MASK) >> CSR_MCONTROL_TYPE_SHIFT)

/*
 * DMODE (RW)
 *
 * Setting this field to indicate the trigger is used by Debug Mode.
 * 0:Both Debug-mode and M-mode can write the currently selected trigger registers
 * 1:Only Debug Mode can write the currently selected trigger registers. Writes from M-mode is ignored.
 */
#define CSR_MCONTROL_DMODE_MASK (0x8000000UL)
#define CSR_MCONTROL_DMODE_SHIFT (27U)
#define CSR_MCONTROL_DMODE_SET(x) (((uint32_t)(x) << CSR_MCONTROL_DMODE_SHIFT) & CSR_MCONTROL_DMODE_MASK)
#define CSR_MCONTROL_DMODE_GET(x) (((uint32_t)(x) & CSR_MCONTROL_DMODE_MASK) >> CSR_MCONTROL_DMODE_SHIFT)

/*
 * MASKMAX (RO)
 *
 * Indicates the largest naturally aligned range supported by the hardware is 2ˆ12 bytes.
 */
#define CSR_MCONTROL_MASKMAX_MASK (0x7E00000UL)
#define CSR_MCONTROL_MASKMAX_SHIFT (21U)
#define CSR_MCONTROL_MASKMAX_GET(x) (((uint32_t)(x) & CSR_MCONTROL_MASKMAX_MASK) >> CSR_MCONTROL_MASKMAX_SHIFT)

/*
 * ACTION (RW)
 *
 * Setting this field to select what happens when this trigger matches.
 * 0:Raise a breakpoint exception
 * 1:Enter Debug Mode. (Only supported when DMODE is 1.)
 */
#define CSR_MCONTROL_ACTION_MASK (0xF000U)
#define CSR_MCONTROL_ACTION_SHIFT (12U)
#define CSR_MCONTROL_ACTION_SET(x) (((uint32_t)(x) << CSR_MCONTROL_ACTION_SHIFT) & CSR_MCONTROL_ACTION_MASK)
#define CSR_MCONTROL_ACTION_GET(x) (((uint32_t)(x) & CSR_MCONTROL_ACTION_MASK) >> CSR_MCONTROL_ACTION_SHIFT)

/*
 * CHAIN (RW)
 *
 * Setting this field to enable trigger chain.
 * 0:When this trigger matches, the configured action is taken.
 * 1:While this trigger does not match, it prevents the trigger with the next index from matching.
 * If Number of Triggers is 2, this field is hardwired to 0 on trigger 1 (tselect = 1).
 * If Number of Triggers is 4, this field is hardwired
 * to 0 on trigger 3 (tselect = 3).
 * If Number of Triggers is 8, this field is hardwired to 0 on trigger 3 and trigger 7 (tselect = 3 or 7).
 */
#define CSR_MCONTROL_CHAIN_MASK (0x800U)
#define CSR_MCONTROL_CHAIN_SHIFT (11U)
#define CSR_MCONTROL_CHAIN_SET(x) (((uint32_t)(x) << CSR_MCONTROL_CHAIN_SHIFT) & CSR_MCONTROL_CHAIN_MASK)
#define CSR_MCONTROL_CHAIN_GET(x) (((uint32_t)(x) & CSR_MCONTROL_CHAIN_MASK) >> CSR_MCONTROL_CHAIN_SHIFT)

/*
 * MATCH (RW)
 *
 * Setting this field to select the matching scheme. 0:Matches when the value equals tdata2. 1:Matches when the top M bits of the value match the top M bits of tdata2. M is 31 minus the index of the least-significant bit containing 0 in tdata2.
 * 2:Matches when the value is greater than (unsigned) or equal to tdata2.
 * 3:Matches when the value is less than (unsigned) tdata2
 */
#define CSR_MCONTROL_MATCH_MASK (0x780U)
#define CSR_MCONTROL_MATCH_SHIFT (7U)
#define CSR_MCONTROL_MATCH_SET(x) (((uint32_t)(x) << CSR_MCONTROL_MATCH_SHIFT) & CSR_MCONTROL_MATCH_MASK)
#define CSR_MCONTROL_MATCH_GET(x) (((uint32_t)(x) & CSR_MCONTROL_MATCH_MASK) >> CSR_MCONTROL_MATCH_SHIFT)

/*
 * M (RW)
 *
 * Setting this field to enable this trigger in M-mode.
 */
#define CSR_MCONTROL_M_MASK (0x40U)
#define CSR_MCONTROL_M_SHIFT (6U)
#define CSR_MCONTROL_M_SET(x) (((uint32_t)(x) << CSR_MCONTROL_M_SHIFT) & CSR_MCONTROL_M_MASK)
#define CSR_MCONTROL_M_GET(x) (((uint32_t)(x) & CSR_MCONTROL_M_MASK) >> CSR_MCONTROL_M_SHIFT)

/*
 * S (RW)
 *
 * Setting this field to enable this trigger in S-mode.
 */
#define CSR_MCONTROL_S_MASK (0x10U)
#define CSR_MCONTROL_S_SHIFT (4U)
#define CSR_MCONTROL_S_SET(x) (((uint32_t)(x) << CSR_MCONTROL_S_SHIFT) & CSR_MCONTROL_S_MASK)
#define CSR_MCONTROL_S_GET(x) (((uint32_t)(x) & CSR_MCONTROL_S_MASK) >> CSR_MCONTROL_S_SHIFT)

/*
 * U (RW)
 *
 * Setting this field to enable this trigger in U-mode.
 */
#define CSR_MCONTROL_U_MASK (0x8U)
#define CSR_MCONTROL_U_SHIFT (3U)
#define CSR_MCONTROL_U_SET(x) (((uint32_t)(x) << CSR_MCONTROL_U_SHIFT) & CSR_MCONTROL_U_MASK)
#define CSR_MCONTROL_U_GET(x) (((uint32_t)(x) & CSR_MCONTROL_U_MASK) >> CSR_MCONTROL_U_SHIFT)

/*
 * EXECUTE (RW)
 *
 * Setting this field to enable this trigger to compare virtual address of an instruction.
 */
#define CSR_MCONTROL_EXECUTE_MASK (0x4U)
#define CSR_MCONTROL_EXECUTE_SHIFT (2U)
#define CSR_MCONTROL_EXECUTE_SET(x) (((uint32_t)(x) << CSR_MCONTROL_EXECUTE_SHIFT) & CSR_MCONTROL_EXECUTE_MASK)
#define CSR_MCONTROL_EXECUTE_GET(x) (((uint32_t)(x) & CSR_MCONTROL_EXECUTE_MASK) >> CSR_MCONTROL_EXECUTE_SHIFT)

/*
 * STORE (RW)
 *
 * Setting this field to enable this trigger to compare virtual address of a store.
 */
#define CSR_MCONTROL_STORE_MASK (0x2U)
#define CSR_MCONTROL_STORE_SHIFT (1U)
#define CSR_MCONTROL_STORE_SET(x) (((uint32_t)(x) << CSR_MCONTROL_STORE_SHIFT) & CSR_MCONTROL_STORE_MASK)
#define CSR_MCONTROL_STORE_GET(x) (((uint32_t)(x) & CSR_MCONTROL_STORE_MASK) >> CSR_MCONTROL_STORE_SHIFT)

/*
 * LOAD (RW)
 *
 * Setting this field to enable this trigger to compare virtual address of a load.
 */
#define CSR_MCONTROL_LOAD_MASK (0x1U)
#define CSR_MCONTROL_LOAD_SHIFT (0U)
#define CSR_MCONTROL_LOAD_SET(x) (((uint32_t)(x) << CSR_MCONTROL_LOAD_SHIFT) & CSR_MCONTROL_LOAD_MASK)
#define CSR_MCONTROL_LOAD_GET(x) (((uint32_t)(x) & CSR_MCONTROL_LOAD_MASK) >> CSR_MCONTROL_LOAD_SHIFT)

/* Bitfield definition for register: ICOUNT */
/*
 * TYPE (RW)
 *
 * The selected trigger is an instruction count trigger.
 */
#define CSR_ICOUNT_TYPE_MASK (0xF0000000UL)
#define CSR_ICOUNT_TYPE_SHIFT (28U)
#define CSR_ICOUNT_TYPE_SET(x) (((uint32_t)(x) << CSR_ICOUNT_TYPE_SHIFT) & CSR_ICOUNT_TYPE_MASK)
#define CSR_ICOUNT_TYPE_GET(x) (((uint32_t)(x) & CSR_ICOUNT_TYPE_MASK) >> CSR_ICOUNT_TYPE_SHIFT)

/*
 * DMODE (RW)
 *
 * Setting this field to indicate the trigger is used by Debug Mode.
 * 0:Both Debug-mode and M-mode can write the currently selected trigger registers.
 * 1:Only Debug Mode can write the currently selected trigger registers. Writes from M-mode is ignored.
 */
#define CSR_ICOUNT_DMODE_MASK (0x8000000UL)
#define CSR_ICOUNT_DMODE_SHIFT (27U)
#define CSR_ICOUNT_DMODE_SET(x) (((uint32_t)(x) << CSR_ICOUNT_DMODE_SHIFT) & CSR_ICOUNT_DMODE_MASK)
#define CSR_ICOUNT_DMODE_GET(x) (((uint32_t)(x) & CSR_ICOUNT_DMODE_MASK) >> CSR_ICOUNT_DMODE_SHIFT)

/*
 * COUNT (RO)
 *
 * This field is hardwired to 1 for single-stepping support
 */
#define CSR_ICOUNT_COUNT_MASK (0x400U)
#define CSR_ICOUNT_COUNT_SHIFT (10U)
#define CSR_ICOUNT_COUNT_GET(x) (((uint32_t)(x) & CSR_ICOUNT_COUNT_MASK) >> CSR_ICOUNT_COUNT_SHIFT)

/*
 * M (RW)
 *
 * Setting this field to enable this trigger in M-mode.
 */
#define CSR_ICOUNT_M_MASK (0x200U)
#define CSR_ICOUNT_M_SHIFT (9U)
#define CSR_ICOUNT_M_SET(x) (((uint32_t)(x) << CSR_ICOUNT_M_SHIFT) & CSR_ICOUNT_M_MASK)
#define CSR_ICOUNT_M_GET(x) (((uint32_t)(x) & CSR_ICOUNT_M_MASK) >> CSR_ICOUNT_M_SHIFT)

/*
 * S (RW)
 *
 * Setting this field to enable this trigger in S-mode.
 */
#define CSR_ICOUNT_S_MASK (0x80U)
#define CSR_ICOUNT_S_SHIFT (7U)
#define CSR_ICOUNT_S_SET(x) (((uint32_t)(x) << CSR_ICOUNT_S_SHIFT) & CSR_ICOUNT_S_MASK)
#define CSR_ICOUNT_S_GET(x) (((uint32_t)(x) & CSR_ICOUNT_S_MASK) >> CSR_ICOUNT_S_SHIFT)

/*
 * U (RW)
 *
 * Setting this field to enable this trigger in U-mode.
 */
#define CSR_ICOUNT_U_MASK (0x40U)
#define CSR_ICOUNT_U_SHIFT (6U)
#define CSR_ICOUNT_U_SET(x) (((uint32_t)(x) << CSR_ICOUNT_U_SHIFT) & CSR_ICOUNT_U_MASK)
#define CSR_ICOUNT_U_GET(x) (((uint32_t)(x) & CSR_ICOUNT_U_MASK) >> CSR_ICOUNT_U_SHIFT)

/*
 * ACTION (RW)
 *
 * Setting this field to select what happens when this trigger matches.
 * 0:Raise a breakpoint exception
 * 1:Enter Debug Mode. (Only supported when DMODE is 1.)
 */
#define CSR_ICOUNT_ACTION_MASK (0x3FU)
#define CSR_ICOUNT_ACTION_SHIFT (0U)
#define CSR_ICOUNT_ACTION_SET(x) (((uint32_t)(x) << CSR_ICOUNT_ACTION_SHIFT) & CSR_ICOUNT_ACTION_MASK)
#define CSR_ICOUNT_ACTION_GET(x) (((uint32_t)(x) & CSR_ICOUNT_ACTION_MASK) >> CSR_ICOUNT_ACTION_SHIFT)

/* Bitfield definition for register: ITRIGGER */
/*
 * TYPE (RW)
 *
 * The selected trigger is an interrupt trigger.
 */
#define CSR_ITRIGGER_TYPE_MASK (0xF0000000UL)
#define CSR_ITRIGGER_TYPE_SHIFT (28U)
#define CSR_ITRIGGER_TYPE_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_TYPE_SHIFT) & CSR_ITRIGGER_TYPE_MASK)
#define CSR_ITRIGGER_TYPE_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_TYPE_MASK) >> CSR_ITRIGGER_TYPE_SHIFT)

/*
 * DMODE (RW)
 *
 * Setting this field to indicate the trigger is used by Debug Mode.
 * 0:Both Debug-mode and M-mode can write the currently selected trigger registers.
 * 1:Only Debug Mode can write the currently selected trigger registers. Writes from M-mode is ignored.
 */
#define CSR_ITRIGGER_DMODE_MASK (0x8000000UL)
#define CSR_ITRIGGER_DMODE_SHIFT (27U)
#define CSR_ITRIGGER_DMODE_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_DMODE_SHIFT) & CSR_ITRIGGER_DMODE_MASK)
#define CSR_ITRIGGER_DMODE_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_DMODE_MASK) >> CSR_ITRIGGER_DMODE_SHIFT)

/*
 * M (RW)
 *
 * Setting this field to enable this trigger in M-mode.
 */
#define CSR_ITRIGGER_M_MASK (0x200U)
#define CSR_ITRIGGER_M_SHIFT (9U)
#define CSR_ITRIGGER_M_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_M_SHIFT) & CSR_ITRIGGER_M_MASK)
#define CSR_ITRIGGER_M_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_M_MASK) >> CSR_ITRIGGER_M_SHIFT)

/*
 * S (RW)
 *
 * Setting this field to enable this trigger in S-mode.
 */
#define CSR_ITRIGGER_S_MASK (0x80U)
#define CSR_ITRIGGER_S_SHIFT (7U)
#define CSR_ITRIGGER_S_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_S_SHIFT) & CSR_ITRIGGER_S_MASK)
#define CSR_ITRIGGER_S_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_S_MASK) >> CSR_ITRIGGER_S_SHIFT)

/*
 * U (RW)
 *
 * Setting this field to enable this trigger in U-mode.
 */
#define CSR_ITRIGGER_U_MASK (0x40U)
#define CSR_ITRIGGER_U_SHIFT (6U)
#define CSR_ITRIGGER_U_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_U_SHIFT) & CSR_ITRIGGER_U_MASK)
#define CSR_ITRIGGER_U_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_U_MASK) >> CSR_ITRIGGER_U_SHIFT)

/*
 * ACTION (RW)
 *
 * Setting this field to select what happens when this trigger matches.
 * 0:Raise a breakpoint exception.
 * 1:Enter Debug Mode. (Only supported when DMODE is 1.)
 */
#define CSR_ITRIGGER_ACTION_MASK (0x3FU)
#define CSR_ITRIGGER_ACTION_SHIFT (0U)
#define CSR_ITRIGGER_ACTION_SET(x) (((uint32_t)(x) << CSR_ITRIGGER_ACTION_SHIFT) & CSR_ITRIGGER_ACTION_MASK)
#define CSR_ITRIGGER_ACTION_GET(x) (((uint32_t)(x) & CSR_ITRIGGER_ACTION_MASK) >> CSR_ITRIGGER_ACTION_SHIFT)

/* Bitfield definition for register: ETRIGGER */
/*
 * TYPE (RW)
 *
 * The selected trigger is an exception trigger.
 */
#define CSR_ETRIGGER_TYPE_MASK (0xF0000000UL)
#define CSR_ETRIGGER_TYPE_SHIFT (28U)
#define CSR_ETRIGGER_TYPE_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_TYPE_SHIFT) & CSR_ETRIGGER_TYPE_MASK)
#define CSR_ETRIGGER_TYPE_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_TYPE_MASK) >> CSR_ETRIGGER_TYPE_SHIFT)

/*
 * DMODE (RW)
 *
 * Setting this field to indicate the trigger is used by Debug Mode.
 * 0:Both Debug-mode and M-mode can write the currently selected trigger registers.
 * 1:Only Debug Mode can write the currently selected trigger registers. Writes from M-mode is ignored.
 */
#define CSR_ETRIGGER_DMODE_MASK (0x8000000UL)
#define CSR_ETRIGGER_DMODE_SHIFT (27U)
#define CSR_ETRIGGER_DMODE_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_DMODE_SHIFT) & CSR_ETRIGGER_DMODE_MASK)
#define CSR_ETRIGGER_DMODE_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_DMODE_MASK) >> CSR_ETRIGGER_DMODE_SHIFT)

/*
 * NMI (RW)
 *
 * Setting this field to enable this trigger in non-maskable interrupts, regardless of the values of s, u, and m.
 */
#define CSR_ETRIGGER_NMI_MASK (0x400U)
#define CSR_ETRIGGER_NMI_SHIFT (10U)
#define CSR_ETRIGGER_NMI_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_NMI_SHIFT) & CSR_ETRIGGER_NMI_MASK)
#define CSR_ETRIGGER_NMI_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_NMI_MASK) >> CSR_ETRIGGER_NMI_SHIFT)

/*
 * M (RW)
 *
 * Setting this field to enable this trigger in M-mode.
 */
#define CSR_ETRIGGER_M_MASK (0x200U)
#define CSR_ETRIGGER_M_SHIFT (9U)
#define CSR_ETRIGGER_M_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_M_SHIFT) & CSR_ETRIGGER_M_MASK)
#define CSR_ETRIGGER_M_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_M_MASK) >> CSR_ETRIGGER_M_SHIFT)

/*
 * S (RW)
 *
 * Setting this field to enable this trigger in S-mode.
 */
#define CSR_ETRIGGER_S_MASK (0x80U)
#define CSR_ETRIGGER_S_SHIFT (7U)
#define CSR_ETRIGGER_S_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_S_SHIFT) & CSR_ETRIGGER_S_MASK)
#define CSR_ETRIGGER_S_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_S_MASK) >> CSR_ETRIGGER_S_SHIFT)

/*
 * U (RW)
 *
 * Setting this field to enable this trigger in U-mode.
 */
#define CSR_ETRIGGER_U_MASK (0x40U)
#define CSR_ETRIGGER_U_SHIFT (6U)
#define CSR_ETRIGGER_U_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_U_SHIFT) & CSR_ETRIGGER_U_MASK)
#define CSR_ETRIGGER_U_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_U_MASK) >> CSR_ETRIGGER_U_SHIFT)

/*
 * ACTION (RW)
 *
 * Setting this field to select what happens when this trigger matches.
 * 0:Raise a breakpoint exception
 * 1:Enter Debug Mode. (Only supported when DMODE is 1.)
 */
#define CSR_ETRIGGER_ACTION_MASK (0x3FU)
#define CSR_ETRIGGER_ACTION_SHIFT (0U)
#define CSR_ETRIGGER_ACTION_SET(x) (((uint32_t)(x) << CSR_ETRIGGER_ACTION_SHIFT) & CSR_ETRIGGER_ACTION_MASK)
#define CSR_ETRIGGER_ACTION_GET(x) (((uint32_t)(x) & CSR_ETRIGGER_ACTION_MASK) >> CSR_ETRIGGER_ACTION_SHIFT)

/* Bitfield definition for register: TDATA2 */
/*
 * DATA (RW)
 *
 * This register provides accesses to the tdata2 register of the currently selected trigger registers selected by the tselect register, and it holds trigger-specific data..
 */
#define CSR_TDATA2_DATA_MASK (0xFFFFFFFFUL)
#define CSR_TDATA2_DATA_SHIFT (0U)
#define CSR_TDATA2_DATA_SET(x) (((uint32_t)(x) << CSR_TDATA2_DATA_SHIFT) & CSR_TDATA2_DATA_MASK)
#define CSR_TDATA2_DATA_GET(x) (((uint32_t)(x) & CSR_TDATA2_DATA_MASK) >> CSR_TDATA2_DATA_SHIFT)

/* Bitfield definition for register: TDATA3 */
/*
 * DATA (RW)
 *
 * This register provides accesses to the tdata3 register of the currently selected trigger registers selected by the tselect register, and it holds trigger-specific data..
 */
#define CSR_TDATA3_DATA_MASK (0xFFFFFFFFUL)
#define CSR_TDATA3_DATA_SHIFT (0U)
#define CSR_TDATA3_DATA_SET(x) (((uint32_t)(x) << CSR_TDATA3_DATA_SHIFT) & CSR_TDATA3_DATA_MASK)
#define CSR_TDATA3_DATA_GET(x) (((uint32_t)(x) & CSR_TDATA3_DATA_MASK) >> CSR_TDATA3_DATA_SHIFT)

/* Bitfield definition for register: TEXTRA */
/*
 * MVALUE (RW)
 *
 * Data used together with MSELECT.
 */
#define CSR_TEXTRA_MVALUE_MASK (0xFC000000UL)
#define CSR_TEXTRA_MVALUE_SHIFT (26U)
#define CSR_TEXTRA_MVALUE_SET(x) (((uint32_t)(x) << CSR_TEXTRA_MVALUE_SHIFT) & CSR_TEXTRA_MVALUE_MASK)
#define CSR_TEXTRA_MVALUE_GET(x) (((uint32_t)(x) & CSR_TEXTRA_MVALUE_MASK) >> CSR_TEXTRA_MVALUE_SHIFT)

/*
 * MSELECT (RW)
 *
 * 0:Ignore MVALUE.
 * 1:This trigger will only match if the lower bits of mcontext equal MVALUE.
 */
#define CSR_TEXTRA_MSELECT_MASK (0x2000000UL)
#define CSR_TEXTRA_MSELECT_SHIFT (25U)
#define CSR_TEXTRA_MSELECT_SET(x) (((uint32_t)(x) << CSR_TEXTRA_MSELECT_SHIFT) & CSR_TEXTRA_MSELECT_MASK)
#define CSR_TEXTRA_MSELECT_GET(x) (((uint32_t)(x) & CSR_TEXTRA_MSELECT_MASK) >> CSR_TEXTRA_MSELECT_SHIFT)

/*
 * SVALUE (RW)
 *
 * Data used together with SSELECT.
 */
#define CSR_TEXTRA_SVALUE_MASK (0x7FCU)
#define CSR_TEXTRA_SVALUE_SHIFT (2U)
#define CSR_TEXTRA_SVALUE_SET(x) (((uint32_t)(x) << CSR_TEXTRA_SVALUE_SHIFT) & CSR_TEXTRA_SVALUE_MASK)
#define CSR_TEXTRA_SVALUE_GET(x) (((uint32_t)(x) & CSR_TEXTRA_SVALUE_MASK) >> CSR_TEXTRA_SVALUE_SHIFT)

/*
 * SSELECT (RW)
 *
 * 0:Ignore MVALUE
 * 1:This trigger will only match if the lower bits of scontext equal SVALUE
 * 2This trigger will only match if satp.ASID equals SVALUE.
 */
#define CSR_TEXTRA_SSELECT_MASK (0x3U)
#define CSR_TEXTRA_SSELECT_SHIFT (0U)
#define CSR_TEXTRA_SSELECT_SET(x) (((uint32_t)(x) << CSR_TEXTRA_SSELECT_SHIFT) & CSR_TEXTRA_SSELECT_MASK)
#define CSR_TEXTRA_SSELECT_GET(x) (((uint32_t)(x) & CSR_TEXTRA_SSELECT_MASK) >> CSR_TEXTRA_SSELECT_SHIFT)

/* Bitfield definition for register: TINFO */
/*
 * INFO (RO)
 *
 * One bit for each possible type in tdata1. Bit N corresponds to type N. If the bit is set, then that
 * type is supported by the currently selected trigger. If the currently selected trigger does not exist, this field contains 1.
 * 0:When this bit is set, there is no trigger at this tselect
 * 1:Reserved and hardwired to 0.
 * 2：When this bit is set, the selected trigger supports type of address/data match trigger
 * 3:When this bit is set, the selected trigger supports type of instruction count trigger.
 * 4:When this bit is set, the selected trigger supports type of interrupt trigger
 * 5:When this bit is set, the selected trigger supports type of exception trigger
 * 15:When this bit is set, the selected trigger exists (so enumeration shouldn’t terminate), but is not currently available.
 * Others:Reserved for future use.
 */
#define CSR_TINFO_INFO_MASK (0xFFFFU)
#define CSR_TINFO_INFO_SHIFT (0U)
#define CSR_TINFO_INFO_GET(x) (((uint32_t)(x) & CSR_TINFO_INFO_MASK) >> CSR_TINFO_INFO_SHIFT)

/* Bitfield definition for register: TCONTROL */
/*
 * MPTE (RW)
 *
 * M-mode previous trigger enable field. When a trap into M-mode is taken, MPTE is set to the value of MTE.
 */
#define CSR_TCONTROL_MPTE_MASK (0x80U)
#define CSR_TCONTROL_MPTE_SHIFT (7U)
#define CSR_TCONTROL_MPTE_SET(x) (((uint32_t)(x) << CSR_TCONTROL_MPTE_SHIFT) & CSR_TCONTROL_MPTE_MASK)
#define CSR_TCONTROL_MPTE_GET(x) (((uint32_t)(x) & CSR_TCONTROL_MPTE_MASK) >> CSR_TCONTROL_MPTE_SHIFT)

/*
 * MTE (RW)
 *
 * M-mode trigger enable field. When a trap into M-mode is taken, MTE is set to 0. When the MRET instruction is executed, MTE is set to the value of MPTE.
 * 0:Triggers do not match/fire while the hart is in M-mode.
 * 1:Triggers do match/fire while the hart is in M-mode.
 */
#define CSR_TCONTROL_MTE_MASK (0x8U)
#define CSR_TCONTROL_MTE_SHIFT (3U)
#define CSR_TCONTROL_MTE_SET(x) (((uint32_t)(x) << CSR_TCONTROL_MTE_SHIFT) & CSR_TCONTROL_MTE_MASK)
#define CSR_TCONTROL_MTE_GET(x) (((uint32_t)(x) & CSR_TCONTROL_MTE_MASK) >> CSR_TCONTROL_MTE_SHIFT)

/* Bitfield definition for register: MCONTEXT */
/*
 * MCONTEXT (RW)
 *
 * Machine mode software can write a context number to this register, which can be used to set triggers that only fire in that specific context.
 */
#define CSR_MCONTEXT_MCONTEXT_MASK (0x3FU)
#define CSR_MCONTEXT_MCONTEXT_SHIFT (0U)
#define CSR_MCONTEXT_MCONTEXT_SET(x) (((uint32_t)(x) << CSR_MCONTEXT_MCONTEXT_SHIFT) & CSR_MCONTEXT_MCONTEXT_MASK)
#define CSR_MCONTEXT_MCONTEXT_GET(x) (((uint32_t)(x) & CSR_MCONTEXT_MCONTEXT_MASK) >> CSR_MCONTEXT_MCONTEXT_SHIFT)

/* Bitfield definition for register: SCONTEXT */
/*
 * SCONTEXT (RW)
 *
 * Machine mode software can write a context number to this register, which can be used to set triggers that only fire in that specific context.
 */
#define CSR_SCONTEXT_SCONTEXT_MASK (0x1FFU)
#define CSR_SCONTEXT_SCONTEXT_SHIFT (0U)
#define CSR_SCONTEXT_SCONTEXT_SET(x) (((uint32_t)(x) << CSR_SCONTEXT_SCONTEXT_SHIFT) & CSR_SCONTEXT_SCONTEXT_MASK)
#define CSR_SCONTEXT_SCONTEXT_GET(x) (((uint32_t)(x) & CSR_SCONTEXT_SCONTEXT_MASK) >> CSR_SCONTEXT_SCONTEXT_SHIFT)

/* Bitfield definition for register: DCSR */
/*
 * XDEBUGVER (RO)
 *
 * Version of the external debugger. 0 indicates that no external debugger exists and 4 indicates that the external debugger conforms to the RISC-V External Debug Support (TD003) V0.13
 */
#define CSR_DCSR_XDEBUGVER_MASK (0xF0000000UL)
#define CSR_DCSR_XDEBUGVER_SHIFT (28U)
#define CSR_DCSR_XDEBUGVER_GET(x) (((uint32_t)(x) & CSR_DCSR_XDEBUGVER_MASK) >> CSR_DCSR_XDEBUGVER_SHIFT)

/*
 * EBREAKM (RW)
 *
 * This bit controls the behavior of EBREAK instructions in Machine Mode
 * 0:Generate a regular breakpoint exception
 * 1:Enter Debug Mode
 */
#define CSR_DCSR_EBREAKM_MASK (0x8000U)
#define CSR_DCSR_EBREAKM_SHIFT (15U)
#define CSR_DCSR_EBREAKM_SET(x) (((uint32_t)(x) << CSR_DCSR_EBREAKM_SHIFT) & CSR_DCSR_EBREAKM_MASK)
#define CSR_DCSR_EBREAKM_GET(x) (((uint32_t)(x) & CSR_DCSR_EBREAKM_MASK) >> CSR_DCSR_EBREAKM_SHIFT)

/*
 * EBREAKS (RW)
 *
 * This bit controls the behavior of EBREAK instructions in Supervisor Mode.
 * 0:Generate a regular breakpoint exception
 * 1:Enter Debug Mode
 */
#define CSR_DCSR_EBREAKS_MASK (0x2000U)
#define CSR_DCSR_EBREAKS_SHIFT (13U)
#define CSR_DCSR_EBREAKS_SET(x) (((uint32_t)(x) << CSR_DCSR_EBREAKS_SHIFT) & CSR_DCSR_EBREAKS_MASK)
#define CSR_DCSR_EBREAKS_GET(x) (((uint32_t)(x) & CSR_DCSR_EBREAKS_MASK) >> CSR_DCSR_EBREAKS_SHIFT)

/*
 * EBREAKU (RW)
 *
 * This bit controls the behavior of EBREAK instructions in User/Application Mode
 * 0:Generate a regular breakpoint exception
 * 1:Enter Debug Mode
 */
#define CSR_DCSR_EBREAKU_MASK (0x1000U)
#define CSR_DCSR_EBREAKU_SHIFT (12U)
#define CSR_DCSR_EBREAKU_SET(x) (((uint32_t)(x) << CSR_DCSR_EBREAKU_SHIFT) & CSR_DCSR_EBREAKU_MASK)
#define CSR_DCSR_EBREAKU_GET(x) (((uint32_t)(x) & CSR_DCSR_EBREAKU_MASK) >> CSR_DCSR_EBREAKU_SHIFT)

/*
 * STEPIE (RW)
 *
 * This bit controls whether interrupts are enabled during single stepping
 * 0:Disable interrupts during single stepping
 * 1:Allow interrupts in single stepping
 */
#define CSR_DCSR_STEPIE_MASK (0x800U)
#define CSR_DCSR_STEPIE_SHIFT (11U)
#define CSR_DCSR_STEPIE_SET(x) (((uint32_t)(x) << CSR_DCSR_STEPIE_SHIFT) & CSR_DCSR_STEPIE_MASK)
#define CSR_DCSR_STEPIE_GET(x) (((uint32_t)(x) & CSR_DCSR_STEPIE_MASK) >> CSR_DCSR_STEPIE_SHIFT)

/*
 * STOPCOUNT (RW)
 *
 * This bit controls whether performance counters are stopped in Debug Mode.
 * 0:Do not stop counters in Debug Mode
 * 1:Stop counters in Debug Mode
 */
#define CSR_DCSR_STOPCOUNT_MASK (0x400U)
#define CSR_DCSR_STOPCOUNT_SHIFT (10U)
#define CSR_DCSR_STOPCOUNT_SET(x) (((uint32_t)(x) << CSR_DCSR_STOPCOUNT_SHIFT) & CSR_DCSR_STOPCOUNT_MASK)
#define CSR_DCSR_STOPCOUNT_GET(x) (((uint32_t)(x) & CSR_DCSR_STOPCOUNT_MASK) >> CSR_DCSR_STOPCOUNT_SHIFT)

/*
 * STOPTIME (RW)
 *
 * This bit controls whether timers are stopped in Debug Mode. The processor only drives its stoptime output pin to 1 if it is in Debug Mode and this bit is set. Integration effort is required to make timers in the platform observe this pin to really stop them.
 * 0:Do not stop timers in Debug Mode
 * 1:Stop timers in Debug Mode
 */
#define CSR_DCSR_STOPTIME_MASK (0x200U)
#define CSR_DCSR_STOPTIME_SHIFT (9U)
#define CSR_DCSR_STOPTIME_SET(x) (((uint32_t)(x) << CSR_DCSR_STOPTIME_SHIFT) & CSR_DCSR_STOPTIME_MASK)
#define CSR_DCSR_STOPTIME_GET(x) (((uint32_t)(x) & CSR_DCSR_STOPTIME_MASK) >> CSR_DCSR_STOPTIME_SHIFT)

/*
 * CAUSE (RO)
 *
 * Reason why Debug Mode was entered. When there are multiple reasons to enter Debug Mode, the priority to determine the CAUSE value will be: trigger module > EBREAK > halt-on-reset > halt request > single step. Halt requests are requests issued by the external debugger
 * 0:Reserved
 * 1:EBREAK
 * 2:Trigger module
 * 3:Halt request
 * 4:Single step
 * 5:Halt-on-reset
 * 6-7:Reserved
 */
#define CSR_DCSR_CAUSE_MASK (0x1C0U)
#define CSR_DCSR_CAUSE_SHIFT (6U)
#define CSR_DCSR_CAUSE_GET(x) (((uint32_t)(x) & CSR_DCSR_CAUSE_MASK) >> CSR_DCSR_CAUSE_SHIFT)

/*
 * MPRVEN (RW)
 *
 * This bit controls whether mstatus.MPRV takes effect in Debug Mode.
 * 0:MPRV in mstatus is ignored in Debug Mode.
 * 1:MPRV in mstatus takes effect in Debug Mode.
 */
#define CSR_DCSR_MPRVEN_MASK (0x10U)
#define CSR_DCSR_MPRVEN_SHIFT (4U)
#define CSR_DCSR_MPRVEN_SET(x) (((uint32_t)(x) << CSR_DCSR_MPRVEN_SHIFT) & CSR_DCSR_MPRVEN_MASK)
#define CSR_DCSR_MPRVEN_GET(x) (((uint32_t)(x) & CSR_DCSR_MPRVEN_MASK) >> CSR_DCSR_MPRVEN_SHIFT)

/*
 * NMIP (RO)
 *
 * When this bit is set, there is a Non-Maskable-Interrupt (NMI) pending for the hart. Since an NMI can indicate a hardware error condition, reliable debugging may no longer be possible once this bit becomes set.
 */
#define CSR_DCSR_NMIP_MASK (0x8U)
#define CSR_DCSR_NMIP_SHIFT (3U)
#define CSR_DCSR_NMIP_GET(x) (((uint32_t)(x) & CSR_DCSR_NMIP_MASK) >> CSR_DCSR_NMIP_SHIFT)

/*
 * STEP (RW)
 *
 * This bit controls whether non-Debug Mode instruction execution is in the single step mode. When set, the hart returns to Debug Mode after a single instruction execution. If the instruction does not complete due to an exception, the hart will immediately enter Debug Mode before executing the trap handler, with appropriate exception registers set.
 * 0:Single Step Mode is off
 * 1:Single Step Mode is on
 */
#define CSR_DCSR_STEP_MASK (0x4U)
#define CSR_DCSR_STEP_SHIFT (2U)
#define CSR_DCSR_STEP_SET(x) (((uint32_t)(x) << CSR_DCSR_STEP_SHIFT) & CSR_DCSR_STEP_MASK)
#define CSR_DCSR_STEP_GET(x) (((uint32_t)(x) & CSR_DCSR_STEP_MASK) >> CSR_DCSR_STEP_SHIFT)

/*
 * PRV (RW)
 *
 * The privilege level that the hart was operating in when Debug Mode was entered. The external debugger can modify this value to change the hart’s privilege level when exiting Debug Mode.
 * 0:User/Application
 * 1:Supervisor
 * 2:Reserved
 * 3:Machine
 */
#define CSR_DCSR_PRV_MASK (0x3U)
#define CSR_DCSR_PRV_SHIFT (0U)
#define CSR_DCSR_PRV_SET(x) (((uint32_t)(x) << CSR_DCSR_PRV_SHIFT) & CSR_DCSR_PRV_MASK)
#define CSR_DCSR_PRV_GET(x) (((uint32_t)(x) & CSR_DCSR_PRV_MASK) >> CSR_DCSR_PRV_SHIFT)

/* Bitfield definition for register: DPC */
/*
 * DPC (RW)
 *
 * Debug Program Counter. Bit 0 is hardwired to 0.
 */
#define CSR_DPC_DPC_MASK (0xFFFFFFFFUL)
#define CSR_DPC_DPC_SHIFT (0U)
#define CSR_DPC_DPC_SET(x) (((uint32_t)(x) << CSR_DPC_DPC_SHIFT) & CSR_DPC_DPC_MASK)
#define CSR_DPC_DPC_GET(x) (((uint32_t)(x) & CSR_DPC_DPC_MASK) >> CSR_DPC_DPC_SHIFT)

/* Bitfield definition for register: DSCRATCH0 */
/*
 * DSCRATCH (RO)
 *
 * A scratch register that is reserved for use by Debug Module.
 */
#define CSR_DSCRATCH0_DSCRATCH_MASK (0xFFFFFFFFUL)
#define CSR_DSCRATCH0_DSCRATCH_SHIFT (0U)
#define CSR_DSCRATCH0_DSCRATCH_GET(x) (((uint32_t)(x) & CSR_DSCRATCH0_DSCRATCH_MASK) >> CSR_DSCRATCH0_DSCRATCH_SHIFT)

/* Bitfield definition for register: DSCRATCH1 */
/*
 * DSCRATCH (RO)
 *
 * A scratch register that is reserved for use by Debug Module.
 */
#define CSR_DSCRATCH1_DSCRATCH_MASK (0xFFFFFFFFUL)
#define CSR_DSCRATCH1_DSCRATCH_SHIFT (0U)
#define CSR_DSCRATCH1_DSCRATCH_GET(x) (((uint32_t)(x) & CSR_DSCRATCH1_DSCRATCH_MASK) >> CSR_DSCRATCH1_DSCRATCH_SHIFT)

/* Bitfield definition for register: MCYCLE */
/*
 * COUNTER (RW)
 *
 * the lower 32 bits of Machine Cycle Counter
 */
#define CSR_MCYCLE_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MCYCLE_COUNTER_SHIFT (0U)
#define CSR_MCYCLE_COUNTER_SET(x) (((uint32_t)(x) << CSR_MCYCLE_COUNTER_SHIFT) & CSR_MCYCLE_COUNTER_MASK)
#define CSR_MCYCLE_COUNTER_GET(x) (((uint32_t)(x) & CSR_MCYCLE_COUNTER_MASK) >> CSR_MCYCLE_COUNTER_SHIFT)

/* Bitfield definition for register: MINSTRET */
/*
 * COUNTER (RW)
 *
 * the lower 32 bits of Machine Instruction-Retired Counter
 */
#define CSR_MINSTRET_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MINSTRET_COUNTER_SHIFT (0U)
#define CSR_MINSTRET_COUNTER_SET(x) (((uint32_t)(x) << CSR_MINSTRET_COUNTER_SHIFT) & CSR_MINSTRET_COUNTER_MASK)
#define CSR_MINSTRET_COUNTER_GET(x) (((uint32_t)(x) & CSR_MINSTRET_COUNTER_MASK) >> CSR_MINSTRET_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER3 */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent3
 */
#define CSR_MHPMCOUNTER3_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER3_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER3_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER3_COUNTER_SHIFT) & CSR_MHPMCOUNTER3_COUNTER_MASK)
#define CSR_MHPMCOUNTER3_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER3_COUNTER_MASK) >> CSR_MHPMCOUNTER3_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER4 */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent4
 */
#define CSR_MHPMCOUNTER4_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER4_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER4_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER4_COUNTER_SHIFT) & CSR_MHPMCOUNTER4_COUNTER_MASK)
#define CSR_MHPMCOUNTER4_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER4_COUNTER_MASK) >> CSR_MHPMCOUNTER4_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER5 */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent5
 */
#define CSR_MHPMCOUNTER5_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER5_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER5_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER5_COUNTER_SHIFT) & CSR_MHPMCOUNTER5_COUNTER_MASK)
#define CSR_MHPMCOUNTER5_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER5_COUNTER_MASK) >> CSR_MHPMCOUNTER5_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER6 */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent6
 */
#define CSR_MHPMCOUNTER6_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER6_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER6_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER6_COUNTER_SHIFT) & CSR_MHPMCOUNTER6_COUNTER_MASK)
#define CSR_MHPMCOUNTER6_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER6_COUNTER_MASK) >> CSR_MHPMCOUNTER6_COUNTER_SHIFT)

/* Bitfield definition for register: MCYCLEH */
/*
 * COUNTER (RW)
 *
 * the higher 32 bits of Machine Cycle Counter
 */
#define CSR_MCYCLEH_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MCYCLEH_COUNTER_SHIFT (0U)
#define CSR_MCYCLEH_COUNTER_SET(x) (((uint32_t)(x) << CSR_MCYCLEH_COUNTER_SHIFT) & CSR_MCYCLEH_COUNTER_MASK)
#define CSR_MCYCLEH_COUNTER_GET(x) (((uint32_t)(x) & CSR_MCYCLEH_COUNTER_MASK) >> CSR_MCYCLEH_COUNTER_SHIFT)

/* Bitfield definition for register: MINSTRETH */
/*
 * COUNTER (RW)
 *
 * the higher 32 bits of Machine Instruction-Retired Counter
 */
#define CSR_MINSTRETH_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MINSTRETH_COUNTER_SHIFT (0U)
#define CSR_MINSTRETH_COUNTER_SET(x) (((uint32_t)(x) << CSR_MINSTRETH_COUNTER_SHIFT) & CSR_MINSTRETH_COUNTER_MASK)
#define CSR_MINSTRETH_COUNTER_GET(x) (((uint32_t)(x) & CSR_MINSTRETH_COUNTER_MASK) >> CSR_MINSTRETH_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER3H */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent3
 */
#define CSR_MHPMCOUNTER3H_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER3H_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER3H_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER3H_COUNTER_SHIFT) & CSR_MHPMCOUNTER3H_COUNTER_MASK)
#define CSR_MHPMCOUNTER3H_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER3H_COUNTER_MASK) >> CSR_MHPMCOUNTER3H_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER4H */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent4
 */
#define CSR_MHPMCOUNTER4H_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER4H_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER4H_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER4H_COUNTER_SHIFT) & CSR_MHPMCOUNTER4H_COUNTER_MASK)
#define CSR_MHPMCOUNTER4H_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER4H_COUNTER_MASK) >> CSR_MHPMCOUNTER4H_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER5H */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent5
 */
#define CSR_MHPMCOUNTER5H_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER5H_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER5H_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER5H_COUNTER_SHIFT) & CSR_MHPMCOUNTER5H_COUNTER_MASK)
#define CSR_MHPMCOUNTER5H_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER5H_COUNTER_MASK) >> CSR_MHPMCOUNTER5H_COUNTER_SHIFT)

/* Bitfield definition for register: MHPMCOUNTER6H */
/*
 * COUNTER (RW)
 *
 * count the num- ber of events selected by mhpmevent6
 */
#define CSR_MHPMCOUNTER6H_COUNTER_MASK (0xFFFFFFFFUL)
#define CSR_MHPMCOUNTER6H_COUNTER_SHIFT (0U)
#define CSR_MHPMCOUNTER6H_COUNTER_SET(x) (((uint32_t)(x) << CSR_MHPMCOUNTER6H_COUNTER_SHIFT) & CSR_MHPMCOUNTER6H_COUNTER_MASK)
#define CSR_MHPMCOUNTER6H_COUNTER_GET(x) (((uint32_t)(x) & CSR_MHPMCOUNTER6H_COUNTER_MASK) >> CSR_MHPMCOUNTER6H_COUNTER_SHIFT)

/* Bitfield definition for register: PMACFG0 */
/*
 * PMA3CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG0_PMA3CFG_MASK (0xFF000000UL)
#define CSR_PMACFG0_PMA3CFG_SHIFT (24U)
#define CSR_PMACFG0_PMA3CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG0_PMA3CFG_SHIFT) & CSR_PMACFG0_PMA3CFG_MASK)
#define CSR_PMACFG0_PMA3CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG0_PMA3CFG_MASK) >> CSR_PMACFG0_PMA3CFG_SHIFT)

/*
 * PMA2CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG0_PMA2CFG_MASK (0xFF0000UL)
#define CSR_PMACFG0_PMA2CFG_SHIFT (16U)
#define CSR_PMACFG0_PMA2CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG0_PMA2CFG_SHIFT) & CSR_PMACFG0_PMA2CFG_MASK)
#define CSR_PMACFG0_PMA2CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG0_PMA2CFG_MASK) >> CSR_PMACFG0_PMA2CFG_SHIFT)

/*
 * PMA1CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG0_PMA1CFG_MASK (0xFF00U)
#define CSR_PMACFG0_PMA1CFG_SHIFT (8U)
#define CSR_PMACFG0_PMA1CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG0_PMA1CFG_SHIFT) & CSR_PMACFG0_PMA1CFG_MASK)
#define CSR_PMACFG0_PMA1CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG0_PMA1CFG_MASK) >> CSR_PMACFG0_PMA1CFG_SHIFT)

/*
 * PMA0CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG0_PMA0CFG_MASK (0xFFU)
#define CSR_PMACFG0_PMA0CFG_SHIFT (0U)
#define CSR_PMACFG0_PMA0CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG0_PMA0CFG_SHIFT) & CSR_PMACFG0_PMA0CFG_MASK)
#define CSR_PMACFG0_PMA0CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG0_PMA0CFG_MASK) >> CSR_PMACFG0_PMA0CFG_SHIFT)

/* Bitfield definition for register: PMACFG1 */
/*
 * PMA7CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG1_PMA7CFG_MASK (0xFF000000UL)
#define CSR_PMACFG1_PMA7CFG_SHIFT (24U)
#define CSR_PMACFG1_PMA7CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG1_PMA7CFG_SHIFT) & CSR_PMACFG1_PMA7CFG_MASK)
#define CSR_PMACFG1_PMA7CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG1_PMA7CFG_MASK) >> CSR_PMACFG1_PMA7CFG_SHIFT)

/*
 * PMA6CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG1_PMA6CFG_MASK (0xFF0000UL)
#define CSR_PMACFG1_PMA6CFG_SHIFT (16U)
#define CSR_PMACFG1_PMA6CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG1_PMA6CFG_SHIFT) & CSR_PMACFG1_PMA6CFG_MASK)
#define CSR_PMACFG1_PMA6CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG1_PMA6CFG_MASK) >> CSR_PMACFG1_PMA6CFG_SHIFT)

/*
 * PMA5CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG1_PMA5CFG_MASK (0xFF00U)
#define CSR_PMACFG1_PMA5CFG_SHIFT (8U)
#define CSR_PMACFG1_PMA5CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG1_PMA5CFG_SHIFT) & CSR_PMACFG1_PMA5CFG_MASK)
#define CSR_PMACFG1_PMA5CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG1_PMA5CFG_MASK) >> CSR_PMACFG1_PMA5CFG_SHIFT)

/*
 * PMA4CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG1_PMA4CFG_MASK (0xFFU)
#define CSR_PMACFG1_PMA4CFG_SHIFT (0U)
#define CSR_PMACFG1_PMA4CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG1_PMA4CFG_SHIFT) & CSR_PMACFG1_PMA4CFG_MASK)
#define CSR_PMACFG1_PMA4CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG1_PMA4CFG_MASK) >> CSR_PMACFG1_PMA4CFG_SHIFT)

/* Bitfield definition for register: PMACFG2 */
/*
 * PMA11CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG2_PMA11CFG_MASK (0xFF000000UL)
#define CSR_PMACFG2_PMA11CFG_SHIFT (24U)
#define CSR_PMACFG2_PMA11CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG2_PMA11CFG_SHIFT) & CSR_PMACFG2_PMA11CFG_MASK)
#define CSR_PMACFG2_PMA11CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG2_PMA11CFG_MASK) >> CSR_PMACFG2_PMA11CFG_SHIFT)

/*
 * PMA10CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG2_PMA10CFG_MASK (0xFF0000UL)
#define CSR_PMACFG2_PMA10CFG_SHIFT (16U)
#define CSR_PMACFG2_PMA10CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG2_PMA10CFG_SHIFT) & CSR_PMACFG2_PMA10CFG_MASK)
#define CSR_PMACFG2_PMA10CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG2_PMA10CFG_MASK) >> CSR_PMACFG2_PMA10CFG_SHIFT)

/*
 * PMA9CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG2_PMA9CFG_MASK (0xFF00U)
#define CSR_PMACFG2_PMA9CFG_SHIFT (8U)
#define CSR_PMACFG2_PMA9CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG2_PMA9CFG_SHIFT) & CSR_PMACFG2_PMA9CFG_MASK)
#define CSR_PMACFG2_PMA9CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG2_PMA9CFG_MASK) >> CSR_PMACFG2_PMA9CFG_SHIFT)

/*
 * PMA8CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG2_PMA8CFG_MASK (0xFFU)
#define CSR_PMACFG2_PMA8CFG_SHIFT (0U)
#define CSR_PMACFG2_PMA8CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG2_PMA8CFG_SHIFT) & CSR_PMACFG2_PMA8CFG_MASK)
#define CSR_PMACFG2_PMA8CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG2_PMA8CFG_MASK) >> CSR_PMACFG2_PMA8CFG_SHIFT)

/* Bitfield definition for register: PMACFG3 */
/*
 * PMA15CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG3_PMA15CFG_MASK (0xFF000000UL)
#define CSR_PMACFG3_PMA15CFG_SHIFT (24U)
#define CSR_PMACFG3_PMA15CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG3_PMA15CFG_SHIFT) & CSR_PMACFG3_PMA15CFG_MASK)
#define CSR_PMACFG3_PMA15CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG3_PMA15CFG_MASK) >> CSR_PMACFG3_PMA15CFG_SHIFT)

/*
 * PMA14CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG3_PMA14CFG_MASK (0xFF0000UL)
#define CSR_PMACFG3_PMA14CFG_SHIFT (16U)
#define CSR_PMACFG3_PMA14CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG3_PMA14CFG_SHIFT) & CSR_PMACFG3_PMA14CFG_MASK)
#define CSR_PMACFG3_PMA14CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG3_PMA14CFG_MASK) >> CSR_PMACFG3_PMA14CFG_SHIFT)

/*
 * PMA13CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG3_PMA13CFG_MASK (0xFF00U)
#define CSR_PMACFG3_PMA13CFG_SHIFT (8U)
#define CSR_PMACFG3_PMA13CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG3_PMA13CFG_SHIFT) & CSR_PMACFG3_PMA13CFG_MASK)
#define CSR_PMACFG3_PMA13CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG3_PMA13CFG_MASK) >> CSR_PMACFG3_PMA13CFG_SHIFT)

/*
 * PMA12CFG (RW)
 *
 * See PMACFG Table
 */
#define CSR_PMACFG3_PMA12CFG_MASK (0xFFU)
#define CSR_PMACFG3_PMA12CFG_SHIFT (0U)
#define CSR_PMACFG3_PMA12CFG_SET(x) (((uint32_t)(x) << CSR_PMACFG3_PMA12CFG_SHIFT) & CSR_PMACFG3_PMA12CFG_MASK)
#define CSR_PMACFG3_PMA12CFG_GET(x) (((uint32_t)(x) & CSR_PMACFG3_PMA12CFG_MASK) >> CSR_PMACFG3_PMA12CFG_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * Register Content     :     Match Size(Byte)
 * aaaa. . . aaaaaaaaaaa       Reserved
 * . . . . . .
 * aaaa. . . aa011111111      Reserved
 * aaaa. . . a0111111111      2^{12}
 * aaaa. . . 01111111111      2^{13}
 * . . . . . .
 * aa01. . . 11111111111      2^{XLEN}
 * a011. . . 11111111111      2^{XLEN+1}
 * 0111. . . 11111111111      2^{XLEN+2}
 * 1111. . . 11111111111      Reserved
 */
#define CSR_PMAADDR0_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR0_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR0_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR0_PMAADDR_31_2_SHIFT) & CSR_PMAADDR0_PMAADDR_31_2_MASK)
#define CSR_PMAADDR0_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR0_PMAADDR_31_2_MASK) >> CSR_PMAADDR0_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR1_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR1_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR1_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR1_PMAADDR_31_2_SHIFT) & CSR_PMAADDR1_PMAADDR_31_2_MASK)
#define CSR_PMAADDR1_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR1_PMAADDR_31_2_MASK) >> CSR_PMAADDR1_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR2_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR2_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR2_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR2_PMAADDR_31_2_SHIFT) & CSR_PMAADDR2_PMAADDR_31_2_MASK)
#define CSR_PMAADDR2_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR2_PMAADDR_31_2_MASK) >> CSR_PMAADDR2_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR3_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR3_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR3_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR3_PMAADDR_31_2_SHIFT) & CSR_PMAADDR3_PMAADDR_31_2_MASK)
#define CSR_PMAADDR3_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR3_PMAADDR_31_2_MASK) >> CSR_PMAADDR3_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR4_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR4_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR4_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR4_PMAADDR_31_2_SHIFT) & CSR_PMAADDR4_PMAADDR_31_2_MASK)
#define CSR_PMAADDR4_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR4_PMAADDR_31_2_MASK) >> CSR_PMAADDR4_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR5_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR5_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR5_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR5_PMAADDR_31_2_SHIFT) & CSR_PMAADDR5_PMAADDR_31_2_MASK)
#define CSR_PMAADDR5_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR5_PMAADDR_31_2_MASK) >> CSR_PMAADDR5_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR6_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR6_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR6_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR6_PMAADDR_31_2_SHIFT) & CSR_PMAADDR6_PMAADDR_31_2_MASK)
#define CSR_PMAADDR6_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR6_PMAADDR_31_2_MASK) >> CSR_PMAADDR6_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR7_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR7_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR7_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR7_PMAADDR_31_2_SHIFT) & CSR_PMAADDR7_PMAADDR_31_2_MASK)
#define CSR_PMAADDR7_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR7_PMAADDR_31_2_MASK) >> CSR_PMAADDR7_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR8_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR8_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR8_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR8_PMAADDR_31_2_SHIFT) & CSR_PMAADDR8_PMAADDR_31_2_MASK)
#define CSR_PMAADDR8_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR8_PMAADDR_31_2_MASK) >> CSR_PMAADDR8_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR9_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR9_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR9_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR9_PMAADDR_31_2_SHIFT) & CSR_PMAADDR9_PMAADDR_31_2_MASK)
#define CSR_PMAADDR9_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR9_PMAADDR_31_2_MASK) >> CSR_PMAADDR9_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR10_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR10_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR10_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR10_PMAADDR_31_2_SHIFT) & CSR_PMAADDR10_PMAADDR_31_2_MASK)
#define CSR_PMAADDR10_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR10_PMAADDR_31_2_MASK) >> CSR_PMAADDR10_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR11_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR11_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR11_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR11_PMAADDR_31_2_SHIFT) & CSR_PMAADDR11_PMAADDR_31_2_MASK)
#define CSR_PMAADDR11_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR11_PMAADDR_31_2_MASK) >> CSR_PMAADDR11_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR12_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR12_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR12_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR12_PMAADDR_31_2_SHIFT) & CSR_PMAADDR12_PMAADDR_31_2_MASK)
#define CSR_PMAADDR12_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR12_PMAADDR_31_2_MASK) >> CSR_PMAADDR12_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR13_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR13_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR13_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR13_PMAADDR_31_2_SHIFT) & CSR_PMAADDR13_PMAADDR_31_2_MASK)
#define CSR_PMAADDR13_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR13_PMAADDR_31_2_MASK) >> CSR_PMAADDR13_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR14_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR14_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR14_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR14_PMAADDR_31_2_SHIFT) & CSR_PMAADDR14_PMAADDR_31_2_MASK)
#define CSR_PMAADDR14_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR14_PMAADDR_31_2_MASK) >> CSR_PMAADDR14_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register array: PMAADDR */
/*
 * PMAADDR_31_2 (RW)
 *
 * same as PMAADDR0
 */
#define CSR_PMAADDR15_PMAADDR_31_2_MASK (0xFFFFFFFCUL)
#define CSR_PMAADDR15_PMAADDR_31_2_SHIFT (2U)
#define CSR_PMAADDR15_PMAADDR_31_2_SET(x) (((uint32_t)(x) << CSR_PMAADDR15_PMAADDR_31_2_SHIFT) & CSR_PMAADDR15_PMAADDR_31_2_MASK)
#define CSR_PMAADDR15_PMAADDR_31_2_GET(x) (((uint32_t)(x) & CSR_PMAADDR15_PMAADDR_31_2_MASK) >> CSR_PMAADDR15_PMAADDR_31_2_SHIFT)

/* Bitfield definition for register: CYCLE */
/*
 * CYCLE (RW)
 *
 * Cycle Counter
 */
#define CSR_CYCLE_CYCLE_MASK (0xFFFFFFFFUL)
#define CSR_CYCLE_CYCLE_SHIFT (0U)
#define CSR_CYCLE_CYCLE_SET(x) (((uint32_t)(x) << CSR_CYCLE_CYCLE_SHIFT) & CSR_CYCLE_CYCLE_MASK)
#define CSR_CYCLE_CYCLE_GET(x) (((uint32_t)(x) & CSR_CYCLE_CYCLE_MASK) >> CSR_CYCLE_CYCLE_SHIFT)

/* Bitfield definition for register: CYCLEH */
/*
 * CYCLEH (RW)
 *
 * Cycle Counter Higher 32-bit
 */
#define CSR_CYCLEH_CYCLEH_MASK (0xFFFFFFFFUL)
#define CSR_CYCLEH_CYCLEH_SHIFT (0U)
#define CSR_CYCLEH_CYCLEH_SET(x) (((uint32_t)(x) << CSR_CYCLEH_CYCLEH_SHIFT) & CSR_CYCLEH_CYCLEH_MASK)
#define CSR_CYCLEH_CYCLEH_GET(x) (((uint32_t)(x) & CSR_CYCLEH_CYCLEH_MASK) >> CSR_CYCLEH_CYCLEH_SHIFT)

/* Bitfield definition for register: MVENDORID */
/*
 * MVENDORID (RO)
 *
 * The manufacturer ID
 */
#define CSR_MVENDORID_MVENDORID_MASK (0xFFFFFFFFUL)
#define CSR_MVENDORID_MVENDORID_SHIFT (0U)
#define CSR_MVENDORID_MVENDORID_GET(x) (((uint32_t)(x) & CSR_MVENDORID_MVENDORID_MASK) >> CSR_MVENDORID_MVENDORID_SHIFT)

/* Bitfield definition for register: MARCHID */
/*
 * CPU_ID (RO)
 *
 * CPU ID
 */
#define CSR_MARCHID_CPU_ID_MASK (0x7FFFFFFFUL)
#define CSR_MARCHID_CPU_ID_SHIFT (0U)
#define CSR_MARCHID_CPU_ID_GET(x) (((uint32_t)(x) & CSR_MARCHID_CPU_ID_MASK) >> CSR_MARCHID_CPU_ID_SHIFT)

/* Bitfield definition for register: MIMPID */
/*
 * MAJOR (RO)
 *
 * Revision major
 */
#define CSR_MIMPID_MAJOR_MASK (0xFFFFFF00UL)
#define CSR_MIMPID_MAJOR_SHIFT (8U)
#define CSR_MIMPID_MAJOR_GET(x) (((uint32_t)(x) & CSR_MIMPID_MAJOR_MASK) >> CSR_MIMPID_MAJOR_SHIFT)

/*
 * MINOR (RO)
 *
 * Revision minor
 */
#define CSR_MIMPID_MINOR_MASK (0xF0U)
#define CSR_MIMPID_MINOR_SHIFT (4U)
#define CSR_MIMPID_MINOR_GET(x) (((uint32_t)(x) & CSR_MIMPID_MINOR_MASK) >> CSR_MIMPID_MINOR_SHIFT)

/*
 * EXTENSION (RO)
 *
 * Revision extension
 */
#define CSR_MIMPID_EXTENSION_MASK (0xFU)
#define CSR_MIMPID_EXTENSION_SHIFT (0U)
#define CSR_MIMPID_EXTENSION_GET(x) (((uint32_t)(x) & CSR_MIMPID_EXTENSION_MASK) >> CSR_MIMPID_EXTENSION_SHIFT)

/* Bitfield definition for register: MHARTID */
/*
 * MHARTID (RO)
 *
 * Hart ID
 */
#define CSR_MHARTID_MHARTID_MASK (0xFFFFFFFFUL)
#define CSR_MHARTID_MHARTID_SHIFT (0U)
#define CSR_MHARTID_MHARTID_GET(x) (((uint32_t)(x) & CSR_MHARTID_MHARTID_MASK) >> CSR_MHARTID_MHARTID_SHIFT)

/* NON-STANDARD CRS register bitfiled definitions */

/* Bitfield definition for register: SCOUNTEREN */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_HPM6_MASK (0x40U)
#define CSR_SCOUNTEREN_HPM6_SHIFT (6U)
#define CSR_SCOUNTEREN_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_HPM6_SHIFT) & CSR_SCOUNTEREN_HPM6_MASK)
#define CSR_SCOUNTEREN_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_HPM6_MASK) >> CSR_SCOUNTEREN_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_HPM5_MASK (0x20U)
#define CSR_SCOUNTEREN_HPM5_SHIFT (5U)
#define CSR_SCOUNTEREN_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_HPM5_SHIFT) & CSR_SCOUNTEREN_HPM5_MASK)
#define CSR_SCOUNTEREN_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_HPM5_MASK) >> CSR_SCOUNTEREN_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_HPM4_MASK (0x10U)
#define CSR_SCOUNTEREN_HPM4_SHIFT (4U)
#define CSR_SCOUNTEREN_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_HPM4_SHIFT) & CSR_SCOUNTEREN_HPM4_MASK)
#define CSR_SCOUNTEREN_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_HPM4_MASK) >> CSR_SCOUNTEREN_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_HPM3_MASK (0x8U)
#define CSR_SCOUNTEREN_HPM3_SHIFT (3U)
#define CSR_SCOUNTEREN_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_HPM3_SHIFT) & CSR_SCOUNTEREN_HPM3_MASK)
#define CSR_SCOUNTEREN_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_HPM3_MASK) >> CSR_SCOUNTEREN_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_IR_MASK (0x4U)
#define CSR_SCOUNTEREN_IR_SHIFT (2U)
#define CSR_SCOUNTEREN_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_IR_SHIFT) & CSR_SCOUNTEREN_IR_MASK)
#define CSR_SCOUNTEREN_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_IR_MASK) >> CSR_SCOUNTEREN_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEREN_CY_MASK (0x1U)
#define CSR_SCOUNTEREN_CY_SHIFT (0U)
#define CSR_SCOUNTEREN_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTEREN_CY_SHIFT) & CSR_SCOUNTEREN_CY_MASK)
#define CSR_SCOUNTEREN_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTEREN_CY_MASK) >> CSR_SCOUNTEREN_CY_SHIFT)

/* Bitfield definition for register: MCOUNTINHIBIT */
/*
 * HPM6 (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_HPM6_MASK (0x40U)
#define CSR_MCOUNTINHIBIT_HPM6_SHIFT (6U)
#define CSR_MCOUNTINHIBIT_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_HPM6_SHIFT) & CSR_MCOUNTINHIBIT_HPM6_MASK)
#define CSR_MCOUNTINHIBIT_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_HPM6_MASK) >> CSR_MCOUNTINHIBIT_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_HPM5_MASK (0x20U)
#define CSR_MCOUNTINHIBIT_HPM5_SHIFT (5U)
#define CSR_MCOUNTINHIBIT_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_HPM5_SHIFT) & CSR_MCOUNTINHIBIT_HPM5_MASK)
#define CSR_MCOUNTINHIBIT_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_HPM5_MASK) >> CSR_MCOUNTINHIBIT_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_HPM4_MASK (0x10U)
#define CSR_MCOUNTINHIBIT_HPM4_SHIFT (4U)
#define CSR_MCOUNTINHIBIT_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_HPM4_SHIFT) & CSR_MCOUNTINHIBIT_HPM4_MASK)
#define CSR_MCOUNTINHIBIT_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_HPM4_MASK) >> CSR_MCOUNTINHIBIT_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_HPM3_MASK (0x8U)
#define CSR_MCOUNTINHIBIT_HPM3_SHIFT (3U)
#define CSR_MCOUNTINHIBIT_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_HPM3_SHIFT) & CSR_MCOUNTINHIBIT_HPM3_MASK)
#define CSR_MCOUNTINHIBIT_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_HPM3_MASK) >> CSR_MCOUNTINHIBIT_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_IR_MASK (0x4U)
#define CSR_MCOUNTINHIBIT_IR_SHIFT (2U)
#define CSR_MCOUNTINHIBIT_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_IR_SHIFT) & CSR_MCOUNTINHIBIT_IR_MASK)
#define CSR_MCOUNTINHIBIT_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_IR_MASK) >> CSR_MCOUNTINHIBIT_IR_SHIFT)

/*
 * TM (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_TM_MASK (0x2U)
#define CSR_MCOUNTINHIBIT_TM_SHIFT (1U)
#define CSR_MCOUNTINHIBIT_TM_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_TM_SHIFT) & CSR_MCOUNTINHIBIT_TM_MASK)
#define CSR_MCOUNTINHIBIT_TM_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_TM_MASK) >> CSR_MCOUNTINHIBIT_TM_SHIFT)

/*
 * CY (RW)
 *
 * See register description.
 */
#define CSR_MCOUNTINHIBIT_CY_MASK (0x1U)
#define CSR_MCOUNTINHIBIT_CY_SHIFT (0U)
#define CSR_MCOUNTINHIBIT_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTINHIBIT_CY_SHIFT) & CSR_MCOUNTINHIBIT_CY_MASK)
#define CSR_MCOUNTINHIBIT_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTINHIBIT_CY_MASK) >> CSR_MCOUNTINHIBIT_CY_SHIFT)

/* Bitfield definition for register: MILMB */
/*
 * IBPA (RO)
 *
 * The base physical address of ILM. It has to be an integer multiple of the ILM size
 */
#define CSR_MILMB_IBPA_MASK (0xFFFFFC00UL)
#define CSR_MILMB_IBPA_SHIFT (10U)
#define CSR_MILMB_IBPA_GET(x) (((uint32_t)(x) & CSR_MILMB_IBPA_MASK) >> CSR_MILMB_IBPA_SHIFT)

/*
 * RWECC (RW)
 *
 * Controls diagnostic accesses of ECC codes of the ILM RAMs. When set, load/store to ILM reads/writes ECC codes to the mecc_code register. This bit can be set for injecting ECC errors to test the ECC handler.
 * 0:Disable diagnostic accesses of ECC codes
 * 1:Enable diagnostic accesses of ECC codes
 */
#define CSR_MILMB_RWECC_MASK (0x8U)
#define CSR_MILMB_RWECC_SHIFT (3U)
#define CSR_MILMB_RWECC_SET(x) (((uint32_t)(x) << CSR_MILMB_RWECC_SHIFT) & CSR_MILMB_RWECC_MASK)
#define CSR_MILMB_RWECC_GET(x) (((uint32_t)(x) & CSR_MILMB_RWECC_MASK) >> CSR_MILMB_RWECC_SHIFT)

/*
 * ECCEN (RW)
 *
 * Parity/ECC enable control:
 * 0:Disable parity/ECC
 * 1:Reserved
 * 2:Generate exceptions only on uncorrectable parity/ECC errors
 * 3:Generate exceptions on any type of parity/ECC errors
 */
#define CSR_MILMB_ECCEN_MASK (0x6U)
#define CSR_MILMB_ECCEN_SHIFT (1U)
#define CSR_MILMB_ECCEN_SET(x) (((uint32_t)(x) << CSR_MILMB_ECCEN_SHIFT) & CSR_MILMB_ECCEN_MASK)
#define CSR_MILMB_ECCEN_GET(x) (((uint32_t)(x) & CSR_MILMB_ECCEN_MASK) >> CSR_MILMB_ECCEN_SHIFT)

/*
 * IEN (RO)
 *
 * ILM enable control:
 * 0:ILM is disabled
 * 1:ILM is enabled
 */
#define CSR_MILMB_IEN_MASK (0x1U)
#define CSR_MILMB_IEN_SHIFT (0U)
#define CSR_MILMB_IEN_GET(x) (((uint32_t)(x) & CSR_MILMB_IEN_MASK) >> CSR_MILMB_IEN_SHIFT)

/* Bitfield definition for register: MDLMB */
/*
 * DBPA (RO)
 *
 * The base physical address of DLM. It has to be an integer multiple of the DLM size
 */
#define CSR_MDLMB_DBPA_MASK (0xFFFFFC00UL)
#define CSR_MDLMB_DBPA_SHIFT (10U)
#define CSR_MDLMB_DBPA_GET(x) (((uint32_t)(x) & CSR_MDLMB_DBPA_MASK) >> CSR_MDLMB_DBPA_SHIFT)

/*
 * RWECC (RW)
 *
 * Controls diagnostic accesses of ECC codes of the DLM RAMs. When set, load/store to DLM reads/writes ECC codes to the mecc_code register. This bit can be set for injecting ECC errors to test the ECC handler.
 * 0:Disable diagnostic accesses of ECC codes
 * 1:Enable diagnostic accesses of ECC codes
 */
#define CSR_MDLMB_RWECC_MASK (0x8U)
#define CSR_MDLMB_RWECC_SHIFT (3U)
#define CSR_MDLMB_RWECC_SET(x) (((uint32_t)(x) << CSR_MDLMB_RWECC_SHIFT) & CSR_MDLMB_RWECC_MASK)
#define CSR_MDLMB_RWECC_GET(x) (((uint32_t)(x) & CSR_MDLMB_RWECC_MASK) >> CSR_MDLMB_RWECC_SHIFT)

/*
 * ECCEN (RW)
 *
 * Parity/ECC enable control:
 * 0:Disable parity/ECC
 * 1:Reserved
 * 2:Generate exceptions only on uncorrectable parity/ECC errors
 * 3:Generate exceptions on any type of parity/ECC errors
 */
#define CSR_MDLMB_ECCEN_MASK (0x6U)
#define CSR_MDLMB_ECCEN_SHIFT (1U)
#define CSR_MDLMB_ECCEN_SET(x) (((uint32_t)(x) << CSR_MDLMB_ECCEN_SHIFT) & CSR_MDLMB_ECCEN_MASK)
#define CSR_MDLMB_ECCEN_GET(x) (((uint32_t)(x) & CSR_MDLMB_ECCEN_MASK) >> CSR_MDLMB_ECCEN_SHIFT)

/*
 * DEN (RO)
 *
 * DLM enable control:
 * 0:DLM is disabled
 * 1:DLM is enabled
 */
#define CSR_MDLMB_DEN_MASK (0x1U)
#define CSR_MDLMB_DEN_SHIFT (0U)
#define CSR_MDLMB_DEN_GET(x) (((uint32_t)(x) & CSR_MDLMB_DEN_MASK) >> CSR_MDLMB_DEN_SHIFT)

/* Bitfield definition for register: MECC_CODE */
/*
 * INSN (RO)
 *
 * Indicates if the parity/ECC error is caused by instruction fetch or data access.
 * 0:Data access
 * 1:Instruction fetch
 */
#define CSR_MECC_CODE_INSN_MASK (0x400000UL)
#define CSR_MECC_CODE_INSN_SHIFT (22U)
#define CSR_MECC_CODE_INSN_GET(x) (((uint32_t)(x) & CSR_MECC_CODE_INSN_MASK) >> CSR_MECC_CODE_INSN_SHIFT)

/*
 * RAMID (RO)
 *
 * The ID of RAM that caused parity/ECC errors.
 * This bit is updated on parity/ECC error exceptions.
 * 0–1:Reserved
 * 2:Tag RAM of I-Cache
 * 3:Data RAM of I-Cache
 * 4:Tag RAM of D-Cache
 * 5:Data RAM of D-Cache
 * 6:Tag RAM of TLB
 * 7:Data RAM of TLB
 * 8:ILM
 * 9:DLM
 * 10–15:Reserved
 */
#define CSR_MECC_CODE_RAMID_MASK (0x3C0000UL)
#define CSR_MECC_CODE_RAMID_SHIFT (18U)
#define CSR_MECC_CODE_RAMID_GET(x) (((uint32_t)(x) & CSR_MECC_CODE_RAMID_MASK) >> CSR_MECC_CODE_RAMID_SHIFT)

/*
 * P (RO)
 *
 * Precise error. This bit is updated on parity/ECC error exceptions.
 * 0:Imprecise error
 * 1:Precise error
 */
#define CSR_MECC_CODE_P_MASK (0x20000UL)
#define CSR_MECC_CODE_P_SHIFT (17U)
#define CSR_MECC_CODE_P_GET(x) (((uint32_t)(x) & CSR_MECC_CODE_P_MASK) >> CSR_MECC_CODE_P_SHIFT)

/*
 * C (RO)
 *
 * Correctable error. This bit is updated on parity/ECC error exceptions.
 * 0:Uncorrectable error
 * 1:Correctable error
 */
#define CSR_MECC_CODE_C_MASK (0x10000UL)
#define CSR_MECC_CODE_C_SHIFT (16U)
#define CSR_MECC_CODE_C_GET(x) (((uint32_t)(x) & CSR_MECC_CODE_C_MASK) >> CSR_MECC_CODE_C_SHIFT)

/*
 * CODE (RW)
 *
 * This field records the ECC value on ECC error exceptions. This field is also used to read/write the ECC codes when diagnostic access of ECC codes are enabled (milmb.RWECC or mdlmb.RWECC is 1).
 */
#define CSR_MECC_CODE_CODE_MASK (0x7FU)
#define CSR_MECC_CODE_CODE_SHIFT (0U)
#define CSR_MECC_CODE_CODE_SET(x) (((uint32_t)(x) << CSR_MECC_CODE_CODE_SHIFT) & CSR_MECC_CODE_CODE_MASK)
#define CSR_MECC_CODE_CODE_GET(x) (((uint32_t)(x) & CSR_MECC_CODE_CODE_MASK) >> CSR_MECC_CODE_CODE_SHIFT)

/* Bitfield definition for register: MNVEC */
/*
 * MNVEC (RO)
 *
 * Base address of the NMI handler. Its value is the zero-extended value of the reset_vector.
 */
#define CSR_MNVEC_MNVEC_MASK (0xFFFFFFFFUL)
#define CSR_MNVEC_MNVEC_SHIFT (0U)
#define CSR_MNVEC_MNVEC_GET(x) (((uint32_t)(x) & CSR_MNVEC_MNVEC_MASK) >> CSR_MNVEC_MNVEC_SHIFT)

/* Bitfield definition for register: MXSTATUS */
/*
 * PDME (RW)
 *
 * For saving previous DME state on entering a trap. This field is hardwired to 0 if data cache and data local memory are not supported.
 */
#define CSR_MXSTATUS_PDME_MASK (0x20U)
#define CSR_MXSTATUS_PDME_SHIFT (5U)
#define CSR_MXSTATUS_PDME_SET(x) (((uint32_t)(x) << CSR_MXSTATUS_PDME_SHIFT) & CSR_MXSTATUS_PDME_MASK)
#define CSR_MXSTATUS_PDME_GET(x) (((uint32_t)(x) & CSR_MXSTATUS_PDME_MASK) >> CSR_MXSTATUS_PDME_SHIFT)

/*
 * DME (RW)
 *
 * Data Machine Error flag. It indicates an exception occurred at the data cache or data local memory (DLM). Load/store accesses will bypass D-Cache when this bit is set. The exception handler should clear this bit after the machine error has been dealt with.
 */
#define CSR_MXSTATUS_DME_MASK (0x10U)
#define CSR_MXSTATUS_DME_SHIFT (4U)
#define CSR_MXSTATUS_DME_SET(x) (((uint32_t)(x) << CSR_MXSTATUS_DME_SHIFT) & CSR_MXSTATUS_DME_MASK)
#define CSR_MXSTATUS_DME_GET(x) (((uint32_t)(x) & CSR_MXSTATUS_DME_MASK) >> CSR_MXSTATUS_DME_SHIFT)

/*
 * PPFT_EN (RW)
 *
 * When mcause is imprecise exception (in the form of an interrupt), the PM field records the privileged mode of the instruction that caused the imprecise exception. The PM field encoding
 * is defined as follows:
 * 0: User mode
 * 1: Supervisor mode
 * 2: Reserved
 * 3: Machine mode
 */
#define CSR_MXSTATUS_PPFT_EN_MASK (0x2U)
#define CSR_MXSTATUS_PPFT_EN_SHIFT (1U)
#define CSR_MXSTATUS_PPFT_EN_SET(x) (((uint32_t)(x) << CSR_MXSTATUS_PPFT_EN_SHIFT) & CSR_MXSTATUS_PPFT_EN_MASK)
#define CSR_MXSTATUS_PPFT_EN_GET(x) (((uint32_t)(x) & CSR_MXSTATUS_PPFT_EN_MASK) >> CSR_MXSTATUS_PPFT_EN_SHIFT)

/*
 * PFT_EN (RW)
 *
 * Enable performance throttling. When throttling is enabled, the processor executes instructions at the performance level specified in mpft_ctl.T_LEVEL. On entering a trap:
 * PPFT_EN  <= PFT_EN;
 * PFT_EN <= mpft_ctl.FAST_INT ? 0 :PFT_EN;
 * On executing an MRET instruction:
 * PFT_EN <= PPFT_EN;
 * This field is hardwired to 0 if the PowerBrake feature is not supported.
 */
#define CSR_MXSTATUS_PFT_EN_MASK (0x1U)
#define CSR_MXSTATUS_PFT_EN_SHIFT (0U)
#define CSR_MXSTATUS_PFT_EN_SET(x) (((uint32_t)(x) << CSR_MXSTATUS_PFT_EN_SHIFT) & CSR_MXSTATUS_PFT_EN_MASK)
#define CSR_MXSTATUS_PFT_EN_GET(x) (((uint32_t)(x) & CSR_MXSTATUS_PFT_EN_MASK) >> CSR_MXSTATUS_PFT_EN_SHIFT)

/* Bitfield definition for register: MPFT_CTL */
/*
 * FAST_INT (RW)
 *
 * Fast interrupt response. If this field is set, mxstatus.PFT_EN will be automatically cleared when the processor enters an interrupt handler.
 */
#define CSR_MPFT_CTL_FAST_INT_MASK (0x100U)
#define CSR_MPFT_CTL_FAST_INT_SHIFT (8U)
#define CSR_MPFT_CTL_FAST_INT_SET(x) (((uint32_t)(x) << CSR_MPFT_CTL_FAST_INT_SHIFT) & CSR_MPFT_CTL_FAST_INT_MASK)
#define CSR_MPFT_CTL_FAST_INT_GET(x) (((uint32_t)(x) & CSR_MPFT_CTL_FAST_INT_MASK) >> CSR_MPFT_CTL_FAST_INT_SHIFT)

/*
 * T_LEVEL (RW)
 *
 * Throttling Level. The processor has the highest performance at throttling level 0 and the lowest
 * performance at throttling level 15.
 * 0:Level 0 (the highest performance)
 * 1-14:Level 1-14
 * 15:Level 15 (the lowest performance)
 */
#define CSR_MPFT_CTL_T_LEVEL_MASK (0xF0U)
#define CSR_MPFT_CTL_T_LEVEL_SHIFT (4U)
#define CSR_MPFT_CTL_T_LEVEL_SET(x) (((uint32_t)(x) << CSR_MPFT_CTL_T_LEVEL_SHIFT) & CSR_MPFT_CTL_T_LEVEL_MASK)
#define CSR_MPFT_CTL_T_LEVEL_GET(x) (((uint32_t)(x) & CSR_MPFT_CTL_T_LEVEL_MASK) >> CSR_MPFT_CTL_T_LEVEL_SHIFT)

/* Bitfield definition for register: MHSP_CTL */
/*
 * M (RW)
 *
 * Enables the SP protection and recording mechanism in Machine mode
 * 0:The mechanism is disabled in Machine mode.
 * 1: The mechanism is enabled in Machine mode.
 */
#define CSR_MHSP_CTL_M_MASK (0x20U)
#define CSR_MHSP_CTL_M_SHIFT (5U)
#define CSR_MHSP_CTL_M_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_M_SHIFT) & CSR_MHSP_CTL_M_MASK)
#define CSR_MHSP_CTL_M_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_M_MASK) >> CSR_MHSP_CTL_M_SHIFT)

/*
 * S (RW)
 *
 * Enables the SP protection and recording mechanism in Supervisor mode
 * 0:The mechanism is disabled in Supervisor mode
 * 1:The mechanism is enabled in Supervisor mode
 */
#define CSR_MHSP_CTL_S_MASK (0x10U)
#define CSR_MHSP_CTL_S_SHIFT (4U)
#define CSR_MHSP_CTL_S_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_S_SHIFT) & CSR_MHSP_CTL_S_MASK)
#define CSR_MHSP_CTL_S_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_S_MASK) >> CSR_MHSP_CTL_S_SHIFT)

/*
 * U (RW)
 *
 * Enables the SP protection and recording mechanism in User mode
 * 0:The mechanism is disabled in User mode
 * 1:The mechanism is enabled in User mode.
 */
#define CSR_MHSP_CTL_U_MASK (0x8U)
#define CSR_MHSP_CTL_U_SHIFT (3U)
#define CSR_MHSP_CTL_U_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_U_SHIFT) & CSR_MHSP_CTL_U_MASK)
#define CSR_MHSP_CTL_U_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_U_MASK) >> CSR_MHSP_CTL_U_SHIFT)

/*
 * SCHM (RW)
 *
 * Selects the operating scheme of the stack protection and recording mechanism
 * 0:Stack overflow/underflow detection
 * 1:Top-of-stack recording
 */
#define CSR_MHSP_CTL_SCHM_MASK (0x4U)
#define CSR_MHSP_CTL_SCHM_SHIFT (2U)
#define CSR_MHSP_CTL_SCHM_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_SCHM_SHIFT) & CSR_MHSP_CTL_SCHM_MASK)
#define CSR_MHSP_CTL_SCHM_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_SCHM_MASK) >> CSR_MHSP_CTL_SCHM_SHIFT)

/*
 * UDF_EN (RW)
 *
 * Enable bit for the stack underflow protection mechanism. This bit will be cleared to 0 automatically by hardware when a stack protection (overflow or underflow) exception is taken.
 * 0:The stack underflow protection is disabled
 * 1:The stack underflow protection is enabled.
 */
#define CSR_MHSP_CTL_UDF_EN_MASK (0x2U)
#define CSR_MHSP_CTL_UDF_EN_SHIFT (1U)
#define CSR_MHSP_CTL_UDF_EN_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_UDF_EN_SHIFT) & CSR_MHSP_CTL_UDF_EN_MASK)
#define CSR_MHSP_CTL_UDF_EN_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_UDF_EN_MASK) >> CSR_MHSP_CTL_UDF_EN_SHIFT)

/*
 * OVF_EN (RW)
 *
 * Enable bit for the stack overflow protection and recording mechanism. This bit will be cleared to 0 automatically by hardware when a stack protection (overflow or underflow) exception is taken.
 * 0:The stack overflow protection and recording mechanism are disabled.
 * 1:The stack overflow protection and recording mechanism are enabled.
 */
#define CSR_MHSP_CTL_OVF_EN_MASK (0x1U)
#define CSR_MHSP_CTL_OVF_EN_SHIFT (0U)
#define CSR_MHSP_CTL_OVF_EN_SET(x) (((uint32_t)(x) << CSR_MHSP_CTL_OVF_EN_SHIFT) & CSR_MHSP_CTL_OVF_EN_MASK)
#define CSR_MHSP_CTL_OVF_EN_GET(x) (((uint32_t)(x) & CSR_MHSP_CTL_OVF_EN_MASK) >> CSR_MHSP_CTL_OVF_EN_SHIFT)

/* Bitfield definition for register: MSP_BOUND */
/*
 * MSP_BOUND (RW)
 *
 * Machine SP Bound
 */
#define CSR_MSP_BOUND_MSP_BOUND_MASK (0xFFFFFFFFUL)
#define CSR_MSP_BOUND_MSP_BOUND_SHIFT (0U)
#define CSR_MSP_BOUND_MSP_BOUND_SET(x) (((uint32_t)(x) << CSR_MSP_BOUND_MSP_BOUND_SHIFT) & CSR_MSP_BOUND_MSP_BOUND_MASK)
#define CSR_MSP_BOUND_MSP_BOUND_GET(x) (((uint32_t)(x) & CSR_MSP_BOUND_MSP_BOUND_MASK) >> CSR_MSP_BOUND_MSP_BOUND_SHIFT)

/* Bitfield definition for register: MSP_BASE */
/*
 * SP_BASE (RW)
 *
 * Machine SP base
 */
#define CSR_MSP_BASE_SP_BASE_MASK (0xFFFFFFFFUL)
#define CSR_MSP_BASE_SP_BASE_SHIFT (0U)
#define CSR_MSP_BASE_SP_BASE_SET(x) (((uint32_t)(x) << CSR_MSP_BASE_SP_BASE_SHIFT) & CSR_MSP_BASE_SP_BASE_MASK)
#define CSR_MSP_BASE_SP_BASE_GET(x) (((uint32_t)(x) & CSR_MSP_BASE_SP_BASE_MASK) >> CSR_MSP_BASE_SP_BASE_SHIFT)

/* Bitfield definition for register: MDCAUSE */
/*
 * PM (RW)
 *
 * When mcause is imprecise exception (in the form of an interrupt), the PM field records the privileged mode of the instruction that caused the imprecise exception. The PM field encoding is defined as follows:
 * 0: User mode
 * 1: Supervisor mode
 * 2: Reserved
 * 3: Machine mode
 */
#define CSR_MDCAUSE_PM_MASK (0x60U)
#define CSR_MDCAUSE_PM_SHIFT (5U)
#define CSR_MDCAUSE_PM_SET(x) (((uint32_t)(x) << CSR_MDCAUSE_PM_SHIFT) & CSR_MDCAUSE_PM_MASK)
#define CSR_MDCAUSE_PM_GET(x) (((uint32_t)(x) & CSR_MDCAUSE_PM_MASK) >> CSR_MDCAUSE_PM_SHIFT)

/*
 * MDCAUSE (RW)
 *
 * This register further disambiguates causes of traps recorded in the mcause register.
 * The value of MDCAUSE for precise exception:
 *   When mcause == 1 (Instruction access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP instruction access violation; 3:Bus error; 4:PMA empty hole access
 *   When mcause == 2 (Illegal instruction):
 *     0:Please parse the mtval CSR; 1:FP disabled exception; 2:ACE disabled exception
 *   When mcause == 5 (Load access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP load access violation; 3:Bus error; 4:Misaligned address; 5:PMA empty hole access; 6:PMA attribute inconsistency; 7:PMA NAMO exception
 *   When mcause == 7 (Store access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP load access violation; 3:Bus error; 4:Misaligned address; 5:PMA empty hole access; 6:PMA attribute inconsistency; 7:PMA NAMO exception
 * The value of MDCAUSE for imprecise exception:
 *   When mcause == Local Interrupt 16 or Local Interrupt 272 (16 + 256) (ECC error local interrupt)
 *     0:Reserved; 1:LM slave port ECC/Parity error; 2:Imprecise store ECC/Parity error; 3:Imprecise load ECC/Parity error
 *   When mcause == Local Interrupt 17 or Local Interrupt 273 (17 + 256) (Bus read/write transaction error local interrupt)
 *     0:Reserved; 1:Bus read error; 2:Bus write error; 3:PMP error caused by load instructions; 4:PMP error caused by store instructions; 5:PMA error caused by load instructions; 6:PMA error caused by store instructions
 */
#define CSR_MDCAUSE_MDCAUSE_MASK (0x7U)
#define CSR_MDCAUSE_MDCAUSE_SHIFT (0U)
#define CSR_MDCAUSE_MDCAUSE_SET(x) (((uint32_t)(x) << CSR_MDCAUSE_MDCAUSE_SHIFT) & CSR_MDCAUSE_MDCAUSE_MASK)
#define CSR_MDCAUSE_MDCAUSE_GET(x) (((uint32_t)(x) & CSR_MDCAUSE_MDCAUSE_MASK) >> CSR_MDCAUSE_MDCAUSE_SHIFT)

/* Bitfield definition for register: MCACHE_CTL */
/*
 * DC_WAROUND (RW)
 *
 * Cache Write-Around threshold
 * 0:Disables streaming. All cacheable write misses allocate a cache line according to PMA settings.
 * 1:Stop allocating D-Cache entries regardless of PMA settings after consecutive stores to 4 cache lines.
 * 2:Stop allocating D-Cache entries regardless of PMA settings after consecutive stores to 64 cache lines.
 * 3:Stop allocating D-Cache entries regardless of PMA settings after consecutive stores to 128 cache lines.
 */
#define CSR_MCACHE_CTL_DC_WAROUND_MASK (0x6000U)
#define CSR_MCACHE_CTL_DC_WAROUND_SHIFT (13U)
#define CSR_MCACHE_CTL_DC_WAROUND_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_DC_WAROUND_SHIFT) & CSR_MCACHE_CTL_DC_WAROUND_MASK)
#define CSR_MCACHE_CTL_DC_WAROUND_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DC_WAROUND_MASK) >> CSR_MCACHE_CTL_DC_WAROUND_SHIFT)

/*
 * DC_FIRST_WORD (RO)
 *
 * Cache miss allocation filling policy
 * 0:Cache line data is returned critical (double) word first
 * 1:Cache line data is returned the lowest address (double) word first
 */
#define CSR_MCACHE_CTL_DC_FIRST_WORD_MASK (0x1000U)
#define CSR_MCACHE_CTL_DC_FIRST_WORD_SHIFT (12U)
#define CSR_MCACHE_CTL_DC_FIRST_WORD_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DC_FIRST_WORD_MASK) >> CSR_MCACHE_CTL_DC_FIRST_WORD_SHIFT)

/*
 * IC_FIRST_WORD (RO)
 *
 * Cache miss allocation filling policy
 * 0:Cache line data is returned critical (double) word first
 * 1:Cache line data is returned the lowest address (double) word first
 */
#define CSR_MCACHE_CTL_IC_FIRST_WORD_MASK (0x800U)
#define CSR_MCACHE_CTL_IC_FIRST_WORD_SHIFT (11U)
#define CSR_MCACHE_CTL_IC_FIRST_WORD_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_IC_FIRST_WORD_MASK) >> CSR_MCACHE_CTL_IC_FIRST_WORD_SHIFT)

/*
 * DPREF_EN (RW)
 *
 * This bit controls hardware prefetch for load/store accesses to cacheable memory regions when D-Cache size is not 0
 * 0:Disable hardware prefetch on load/store memory accesses
 * 1:Enable hardware prefetch on load/store memory accesses
 */
#define CSR_MCACHE_CTL_DPREF_EN_MASK (0x400U)
#define CSR_MCACHE_CTL_DPREF_EN_SHIFT (10U)
#define CSR_MCACHE_CTL_DPREF_EN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_DPREF_EN_SHIFT) & CSR_MCACHE_CTL_DPREF_EN_MASK)
#define CSR_MCACHE_CTL_DPREF_EN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DPREF_EN_MASK) >> CSR_MCACHE_CTL_DPREF_EN_SHIFT)

/*
 * IPREF_EN (RW)
 *
 * This bit controls hardware prefetch for instruction fetches to cacheable memory regions when Cache size is not 0
 * 0:Disable hardware prefetch on instruction fetches
 * 1:Enable hardware prefetch on instruction fetches
 */
#define CSR_MCACHE_CTL_IPREF_EN_MASK (0x200U)
#define CSR_MCACHE_CTL_IPREF_EN_SHIFT (9U)
#define CSR_MCACHE_CTL_IPREF_EN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_IPREF_EN_SHIFT) & CSR_MCACHE_CTL_IPREF_EN_MASK)
#define CSR_MCACHE_CTL_IPREF_EN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_IPREF_EN_MASK) >> CSR_MCACHE_CTL_IPREF_EN_SHIFT)

/*
 * CCTL_SUEN (RW)
 *
 * Enable bit for Superuser-mode and User-mode software to access ucctlbeginaddr and ucctlcommand CSRs
 * 0:Disable ucctlbeginaddr and ucctlcommand accesses in S/U mode
 * 1:Enable ucctlbeginaddr and ucctlcommand accesses in S/U mode
 */
#define CSR_MCACHE_CTL_CCTL_SUEN_MASK (0x100U)
#define CSR_MCACHE_CTL_CCTL_SUEN_SHIFT (8U)
#define CSR_MCACHE_CTL_CCTL_SUEN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_CCTL_SUEN_SHIFT) & CSR_MCACHE_CTL_CCTL_SUEN_MASK)
#define CSR_MCACHE_CTL_CCTL_SUEN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_CCTL_SUEN_MASK) >> CSR_MCACHE_CTL_CCTL_SUEN_SHIFT)

/*
 * DC_RWECC (RW)
 *
 * Controls diagnostic accesses of ECC codes of the data cache RAMs. It is set to enable CCTL operations to access the ECC codes. This bit can be set for injecting ECC errors to test the ECC handler
 * 0:Disable diagnostic accesses of ECC codes
 * 1:Enable diagnostic accesses of ECC codes
 */
#define CSR_MCACHE_CTL_DC_RWECC_MASK (0x80U)
#define CSR_MCACHE_CTL_DC_RWECC_SHIFT (7U)
#define CSR_MCACHE_CTL_DC_RWECC_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_DC_RWECC_SHIFT) & CSR_MCACHE_CTL_DC_RWECC_MASK)
#define CSR_MCACHE_CTL_DC_RWECC_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DC_RWECC_MASK) >> CSR_MCACHE_CTL_DC_RWECC_SHIFT)

/*
 * IC_RWECC (RW)
 *
 * Controls diagnostic accesses of ECC codes of the instruction cache RAMs. It is set to enable CCTL operations to access the ECC codes . This bit can be set for injecting ECC errors to test the ECC handler.
 * 0:Disable diagnostic accesses of ECC codes
 * 1:Enable diagnostic accesses of ECC codes
 */
#define CSR_MCACHE_CTL_IC_RWECC_MASK (0x40U)
#define CSR_MCACHE_CTL_IC_RWECC_SHIFT (6U)
#define CSR_MCACHE_CTL_IC_RWECC_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_IC_RWECC_SHIFT) & CSR_MCACHE_CTL_IC_RWECC_MASK)
#define CSR_MCACHE_CTL_IC_RWECC_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_IC_RWECC_MASK) >> CSR_MCACHE_CTL_IC_RWECC_SHIFT)

/*
 * DC_ECCEN (RW)
 *
 * Parity/ECC error checking enable control for the
 * data cache.
 * 0:Disable parity/ECC
 * 1:Reserved
 * 2:Generate exceptions only on uncorrectable parity/ECC errors
 * 3:Generate exceptions on any type of parity/ECC errors
 */
#define CSR_MCACHE_CTL_DC_ECCEN_MASK (0x30U)
#define CSR_MCACHE_CTL_DC_ECCEN_SHIFT (4U)
#define CSR_MCACHE_CTL_DC_ECCEN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_DC_ECCEN_SHIFT) & CSR_MCACHE_CTL_DC_ECCEN_MASK)
#define CSR_MCACHE_CTL_DC_ECCEN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DC_ECCEN_MASK) >> CSR_MCACHE_CTL_DC_ECCEN_SHIFT)

/*
 * IC_ECCEN (RW)
 *
 * Parity/ECC error checking enable control for the
 * instruction cache
 * 0:Disable parity/ECC
 * 1:Reserved
 * 2:Generate exceptions only on uncorrectable parity/ECC errors
 * 3:Generate exceptions on any type of parity/ECC errors
 */
#define CSR_MCACHE_CTL_IC_ECCEN_MASK (0xCU)
#define CSR_MCACHE_CTL_IC_ECCEN_SHIFT (2U)
#define CSR_MCACHE_CTL_IC_ECCEN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_IC_ECCEN_SHIFT) & CSR_MCACHE_CTL_IC_ECCEN_MASK)
#define CSR_MCACHE_CTL_IC_ECCEN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_IC_ECCEN_MASK) >> CSR_MCACHE_CTL_IC_ECCEN_SHIFT)

/*
 * DC_EN (RW)
 *
 * Controls if the data cache is enabled or not.
 * 0:D-Cache is disabled
 * 1:D-Cache is enabled
 */
#define CSR_MCACHE_CTL_DC_EN_MASK (0x2U)
#define CSR_MCACHE_CTL_DC_EN_SHIFT (1U)
#define CSR_MCACHE_CTL_DC_EN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_DC_EN_SHIFT) & CSR_MCACHE_CTL_DC_EN_MASK)
#define CSR_MCACHE_CTL_DC_EN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_DC_EN_MASK) >> CSR_MCACHE_CTL_DC_EN_SHIFT)

/*
 * IC_EN (RW)
 *
 * Controls if the instruction cache is enabled or not.
 * 0:I-Cache is disabled
 * 1:I-Cache is enabled
 */
#define CSR_MCACHE_CTL_IC_EN_MASK (0x1U)
#define CSR_MCACHE_CTL_IC_EN_SHIFT (0U)
#define CSR_MCACHE_CTL_IC_EN_SET(x) (((uint32_t)(x) << CSR_MCACHE_CTL_IC_EN_SHIFT) & CSR_MCACHE_CTL_IC_EN_MASK)
#define CSR_MCACHE_CTL_IC_EN_GET(x) (((uint32_t)(x) & CSR_MCACHE_CTL_IC_EN_MASK) >> CSR_MCACHE_CTL_IC_EN_SHIFT)

/* Bitfield definition for register: MCCTLBEGINADDR */
/*
 * VA (RW)
 *
 * This register holds the address information required by CCTL operations
 */
#define CSR_MCCTLBEGINADDR_VA_MASK (0xFFFFFFFFUL)
#define CSR_MCCTLBEGINADDR_VA_SHIFT (0U)
#define CSR_MCCTLBEGINADDR_VA_SET(x) (((uint32_t)(x) << CSR_MCCTLBEGINADDR_VA_SHIFT) & CSR_MCCTLBEGINADDR_VA_MASK)
#define CSR_MCCTLBEGINADDR_VA_GET(x) (((uint32_t)(x) & CSR_MCCTLBEGINADDR_VA_MASK) >> CSR_MCCTLBEGINADDR_VA_SHIFT)

/* Bitfield definition for register: MCCTLCOMMAND */
/*
 * VA (RW)
 *
 * See CCTL Command Definition Table
 */
#define CSR_MCCTLCOMMAND_VA_MASK (0x1FU)
#define CSR_MCCTLCOMMAND_VA_SHIFT (0U)
#define CSR_MCCTLCOMMAND_VA_SET(x) (((uint32_t)(x) << CSR_MCCTLCOMMAND_VA_SHIFT) & CSR_MCCTLCOMMAND_VA_MASK)
#define CSR_MCCTLCOMMAND_VA_GET(x) (((uint32_t)(x) & CSR_MCCTLCOMMAND_VA_MASK) >> CSR_MCCTLCOMMAND_VA_SHIFT)

/* Bitfield definition for register: MCCTLDATA */
/*
 * VA (RW)
 *
 * See CCTL Commands Which Access mcctldata Table
 */
#define CSR_MCCTLDATA_VA_MASK (0x1FU)
#define CSR_MCCTLDATA_VA_SHIFT (0U)
#define CSR_MCCTLDATA_VA_SET(x) (((uint32_t)(x) << CSR_MCCTLDATA_VA_SHIFT) & CSR_MCCTLDATA_VA_MASK)
#define CSR_MCCTLDATA_VA_GET(x) (((uint32_t)(x) & CSR_MCCTLDATA_VA_MASK) >> CSR_MCCTLDATA_VA_SHIFT)

/* Bitfield definition for register: MCOUNTERWEN */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_HPM6_MASK (0x40U)
#define CSR_MCOUNTERWEN_HPM6_SHIFT (6U)
#define CSR_MCOUNTERWEN_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_HPM6_SHIFT) & CSR_MCOUNTERWEN_HPM6_MASK)
#define CSR_MCOUNTERWEN_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_HPM6_MASK) >> CSR_MCOUNTERWEN_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_HPM5_MASK (0x20U)
#define CSR_MCOUNTERWEN_HPM5_SHIFT (5U)
#define CSR_MCOUNTERWEN_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_HPM5_SHIFT) & CSR_MCOUNTERWEN_HPM5_MASK)
#define CSR_MCOUNTERWEN_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_HPM5_MASK) >> CSR_MCOUNTERWEN_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_HPM4_MASK (0x10U)
#define CSR_MCOUNTERWEN_HPM4_SHIFT (4U)
#define CSR_MCOUNTERWEN_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_HPM4_SHIFT) & CSR_MCOUNTERWEN_HPM4_MASK)
#define CSR_MCOUNTERWEN_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_HPM4_MASK) >> CSR_MCOUNTERWEN_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_HPM3_MASK (0x8U)
#define CSR_MCOUNTERWEN_HPM3_SHIFT (3U)
#define CSR_MCOUNTERWEN_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_HPM3_SHIFT) & CSR_MCOUNTERWEN_HPM3_MASK)
#define CSR_MCOUNTERWEN_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_HPM3_MASK) >> CSR_MCOUNTERWEN_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_IR_MASK (0x4U)
#define CSR_MCOUNTERWEN_IR_SHIFT (2U)
#define CSR_MCOUNTERWEN_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_IR_SHIFT) & CSR_MCOUNTERWEN_IR_MASK)
#define CSR_MCOUNTERWEN_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_IR_MASK) >> CSR_MCOUNTERWEN_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERWEN_CY_MASK (0x1U)
#define CSR_MCOUNTERWEN_CY_SHIFT (0U)
#define CSR_MCOUNTERWEN_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTERWEN_CY_SHIFT) & CSR_MCOUNTERWEN_CY_MASK)
#define CSR_MCOUNTERWEN_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTERWEN_CY_MASK) >> CSR_MCOUNTERWEN_CY_SHIFT)

/* Bitfield definition for register: MCOUNTERINTEN */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_HPM6_MASK (0x40U)
#define CSR_MCOUNTERINTEN_HPM6_SHIFT (6U)
#define CSR_MCOUNTERINTEN_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_HPM6_SHIFT) & CSR_MCOUNTERINTEN_HPM6_MASK)
#define CSR_MCOUNTERINTEN_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_HPM6_MASK) >> CSR_MCOUNTERINTEN_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_HPM5_MASK (0x20U)
#define CSR_MCOUNTERINTEN_HPM5_SHIFT (5U)
#define CSR_MCOUNTERINTEN_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_HPM5_SHIFT) & CSR_MCOUNTERINTEN_HPM5_MASK)
#define CSR_MCOUNTERINTEN_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_HPM5_MASK) >> CSR_MCOUNTERINTEN_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_HPM4_MASK (0x10U)
#define CSR_MCOUNTERINTEN_HPM4_SHIFT (4U)
#define CSR_MCOUNTERINTEN_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_HPM4_SHIFT) & CSR_MCOUNTERINTEN_HPM4_MASK)
#define CSR_MCOUNTERINTEN_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_HPM4_MASK) >> CSR_MCOUNTERINTEN_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_HPM3_MASK (0x8U)
#define CSR_MCOUNTERINTEN_HPM3_SHIFT (3U)
#define CSR_MCOUNTERINTEN_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_HPM3_SHIFT) & CSR_MCOUNTERINTEN_HPM3_MASK)
#define CSR_MCOUNTERINTEN_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_HPM3_MASK) >> CSR_MCOUNTERINTEN_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_IR_MASK (0x4U)
#define CSR_MCOUNTERINTEN_IR_SHIFT (2U)
#define CSR_MCOUNTERINTEN_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_IR_SHIFT) & CSR_MCOUNTERINTEN_IR_MASK)
#define CSR_MCOUNTERINTEN_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_IR_MASK) >> CSR_MCOUNTERINTEN_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERINTEN_CY_MASK (0x1U)
#define CSR_MCOUNTERINTEN_CY_SHIFT (0U)
#define CSR_MCOUNTERINTEN_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTERINTEN_CY_SHIFT) & CSR_MCOUNTERINTEN_CY_MASK)
#define CSR_MCOUNTERINTEN_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTERINTEN_CY_MASK) >> CSR_MCOUNTERINTEN_CY_SHIFT)

/* Bitfield definition for register: MMISC_CTL */
/*
 * NBLD_EN (RW)
 *
 * This field controls the blocking behavior of load instructions. When this bit is clear, load instructions accessing non-device regions are blocking. When this bit is set, load instructions will not be blocking on such occasions and bus errors will no longer be reported synchronously.
 * 0:Load to memory regions are blocking.
 * 1:Load to memory regions are non-blocking.
 */
#define CSR_MMISC_CTL_NBLD_EN_MASK (0x100U)
#define CSR_MMISC_CTL_NBLD_EN_SHIFT (8U)
#define CSR_MMISC_CTL_NBLD_EN_SET(x) (((uint32_t)(x) << CSR_MMISC_CTL_NBLD_EN_SHIFT) & CSR_MMISC_CTL_NBLD_EN_MASK)
#define CSR_MMISC_CTL_NBLD_EN_GET(x) (((uint32_t)(x) & CSR_MMISC_CTL_NBLD_EN_MASK) >> CSR_MMISC_CTL_NBLD_EN_SHIFT)

/*
 * MSA_UNA (RW)
 *
 * This field controls whether the load/store instructions can access misaligned memory locations without generating Address Misaligned exceptions.
 * Supported instructions: LW/LH/LHU/SW/SH
 * 0:Misaligned accesses generate Address Misaligned exceptions.
 * 1:Misaligned accesses generate Address Misaligned exceptions.
 */
#define CSR_MMISC_CTL_MSA_UNA_MASK (0x40U)
#define CSR_MMISC_CTL_MSA_UNA_SHIFT (6U)
#define CSR_MMISC_CTL_MSA_UNA_SET(x) (((uint32_t)(x) << CSR_MMISC_CTL_MSA_UNA_SHIFT) & CSR_MMISC_CTL_MSA_UNA_MASK)
#define CSR_MMISC_CTL_MSA_UNA_GET(x) (((uint32_t)(x) & CSR_MMISC_CTL_MSA_UNA_MASK) >> CSR_MMISC_CTL_MSA_UNA_SHIFT)

/*
 * BRPE (RW)
 *
 * Branch prediction enable bit. This bit controls all branch prediction structures.
 * 0:Disabled
 * 1:Enabled
 * This bit is hardwired to 0 if branch prediction structure is not supported.
 */
#define CSR_MMISC_CTL_BRPE_MASK (0x8U)
#define CSR_MMISC_CTL_BRPE_SHIFT (3U)
#define CSR_MMISC_CTL_BRPE_SET(x) (((uint32_t)(x) << CSR_MMISC_CTL_BRPE_SHIFT) & CSR_MMISC_CTL_BRPE_MASK)
#define CSR_MMISC_CTL_BRPE_GET(x) (((uint32_t)(x) & CSR_MMISC_CTL_BRPE_MASK) >> CSR_MMISC_CTL_BRPE_SHIFT)

/*
 * RVCOMPM (RW)
 *
 * RISC-V compatibility mode enable bit. If the compatibility mode is turned on, all specific instructions become reserved instructions
 * 0:Disabled
 * 1:Enabled
 */
#define CSR_MMISC_CTL_RVCOMPM_MASK (0x4U)
#define CSR_MMISC_CTL_RVCOMPM_SHIFT (2U)
#define CSR_MMISC_CTL_RVCOMPM_SET(x) (((uint32_t)(x) << CSR_MMISC_CTL_RVCOMPM_SHIFT) & CSR_MMISC_CTL_RVCOMPM_MASK)
#define CSR_MMISC_CTL_RVCOMPM_GET(x) (((uint32_t)(x) & CSR_MMISC_CTL_RVCOMPM_MASK) >> CSR_MMISC_CTL_RVCOMPM_SHIFT)

/*
 * VEC_PLIC (RW)
 *
 * Selects the operation mode of PLIC:
 * 0:Regular mode
 * 1:Vector mode
 * Please note that both this bit and the vector mode enable bit (VECTORED) of the Feature Enable Register in NCEPLIC100 should be turned on for the vectored interrupt support to work correctly. This bit is hardwired to 0 if the vectored PLIC feature is not supported.
 */
#define CSR_MMISC_CTL_VEC_PLIC_MASK (0x2U)
#define CSR_MMISC_CTL_VEC_PLIC_SHIFT (1U)
#define CSR_MMISC_CTL_VEC_PLIC_SET(x) (((uint32_t)(x) << CSR_MMISC_CTL_VEC_PLIC_SHIFT) & CSR_MMISC_CTL_VEC_PLIC_MASK)
#define CSR_MMISC_CTL_VEC_PLIC_GET(x) (((uint32_t)(x) & CSR_MMISC_CTL_VEC_PLIC_MASK) >> CSR_MMISC_CTL_VEC_PLIC_SHIFT)

/* Bitfield definition for register: MCOUNTERMASK_M */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_HPM6_MASK (0x40U)
#define CSR_MCOUNTERMASK_M_HPM6_SHIFT (6U)
#define CSR_MCOUNTERMASK_M_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_HPM6_SHIFT) & CSR_MCOUNTERMASK_M_HPM6_MASK)
#define CSR_MCOUNTERMASK_M_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_HPM6_MASK) >> CSR_MCOUNTERMASK_M_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_HPM5_MASK (0x20U)
#define CSR_MCOUNTERMASK_M_HPM5_SHIFT (5U)
#define CSR_MCOUNTERMASK_M_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_HPM5_SHIFT) & CSR_MCOUNTERMASK_M_HPM5_MASK)
#define CSR_MCOUNTERMASK_M_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_HPM5_MASK) >> CSR_MCOUNTERMASK_M_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_HPM4_MASK (0x10U)
#define CSR_MCOUNTERMASK_M_HPM4_SHIFT (4U)
#define CSR_MCOUNTERMASK_M_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_HPM4_SHIFT) & CSR_MCOUNTERMASK_M_HPM4_MASK)
#define CSR_MCOUNTERMASK_M_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_HPM4_MASK) >> CSR_MCOUNTERMASK_M_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_HPM3_MASK (0x8U)
#define CSR_MCOUNTERMASK_M_HPM3_SHIFT (3U)
#define CSR_MCOUNTERMASK_M_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_HPM3_SHIFT) & CSR_MCOUNTERMASK_M_HPM3_MASK)
#define CSR_MCOUNTERMASK_M_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_HPM3_MASK) >> CSR_MCOUNTERMASK_M_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_IR_MASK (0x4U)
#define CSR_MCOUNTERMASK_M_IR_SHIFT (2U)
#define CSR_MCOUNTERMASK_M_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_IR_SHIFT) & CSR_MCOUNTERMASK_M_IR_MASK)
#define CSR_MCOUNTERMASK_M_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_IR_MASK) >> CSR_MCOUNTERMASK_M_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_M_CY_MASK (0x1U)
#define CSR_MCOUNTERMASK_M_CY_SHIFT (0U)
#define CSR_MCOUNTERMASK_M_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_M_CY_SHIFT) & CSR_MCOUNTERMASK_M_CY_MASK)
#define CSR_MCOUNTERMASK_M_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_M_CY_MASK) >> CSR_MCOUNTERMASK_M_CY_SHIFT)

/* Bitfield definition for register: MCOUNTERMASK_S */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_HPM6_MASK (0x40U)
#define CSR_MCOUNTERMASK_S_HPM6_SHIFT (6U)
#define CSR_MCOUNTERMASK_S_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_HPM6_SHIFT) & CSR_MCOUNTERMASK_S_HPM6_MASK)
#define CSR_MCOUNTERMASK_S_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_HPM6_MASK) >> CSR_MCOUNTERMASK_S_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_HPM5_MASK (0x20U)
#define CSR_MCOUNTERMASK_S_HPM5_SHIFT (5U)
#define CSR_MCOUNTERMASK_S_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_HPM5_SHIFT) & CSR_MCOUNTERMASK_S_HPM5_MASK)
#define CSR_MCOUNTERMASK_S_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_HPM5_MASK) >> CSR_MCOUNTERMASK_S_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_HPM4_MASK (0x10U)
#define CSR_MCOUNTERMASK_S_HPM4_SHIFT (4U)
#define CSR_MCOUNTERMASK_S_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_HPM4_SHIFT) & CSR_MCOUNTERMASK_S_HPM4_MASK)
#define CSR_MCOUNTERMASK_S_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_HPM4_MASK) >> CSR_MCOUNTERMASK_S_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_HPM3_MASK (0x8U)
#define CSR_MCOUNTERMASK_S_HPM3_SHIFT (3U)
#define CSR_MCOUNTERMASK_S_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_HPM3_SHIFT) & CSR_MCOUNTERMASK_S_HPM3_MASK)
#define CSR_MCOUNTERMASK_S_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_HPM3_MASK) >> CSR_MCOUNTERMASK_S_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_IR_MASK (0x4U)
#define CSR_MCOUNTERMASK_S_IR_SHIFT (2U)
#define CSR_MCOUNTERMASK_S_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_IR_SHIFT) & CSR_MCOUNTERMASK_S_IR_MASK)
#define CSR_MCOUNTERMASK_S_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_IR_MASK) >> CSR_MCOUNTERMASK_S_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_S_CY_MASK (0x1U)
#define CSR_MCOUNTERMASK_S_CY_SHIFT (0U)
#define CSR_MCOUNTERMASK_S_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_S_CY_SHIFT) & CSR_MCOUNTERMASK_S_CY_MASK)
#define CSR_MCOUNTERMASK_S_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_S_CY_MASK) >> CSR_MCOUNTERMASK_S_CY_SHIFT)

/* Bitfield definition for register: MCOUNTERMASK_U */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_HPM6_MASK (0x40U)
#define CSR_MCOUNTERMASK_U_HPM6_SHIFT (6U)
#define CSR_MCOUNTERMASK_U_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_HPM6_SHIFT) & CSR_MCOUNTERMASK_U_HPM6_MASK)
#define CSR_MCOUNTERMASK_U_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_HPM6_MASK) >> CSR_MCOUNTERMASK_U_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_HPM5_MASK (0x20U)
#define CSR_MCOUNTERMASK_U_HPM5_SHIFT (5U)
#define CSR_MCOUNTERMASK_U_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_HPM5_SHIFT) & CSR_MCOUNTERMASK_U_HPM5_MASK)
#define CSR_MCOUNTERMASK_U_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_HPM5_MASK) >> CSR_MCOUNTERMASK_U_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_HPM4_MASK (0x10U)
#define CSR_MCOUNTERMASK_U_HPM4_SHIFT (4U)
#define CSR_MCOUNTERMASK_U_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_HPM4_SHIFT) & CSR_MCOUNTERMASK_U_HPM4_MASK)
#define CSR_MCOUNTERMASK_U_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_HPM4_MASK) >> CSR_MCOUNTERMASK_U_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_HPM3_MASK (0x8U)
#define CSR_MCOUNTERMASK_U_HPM3_SHIFT (3U)
#define CSR_MCOUNTERMASK_U_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_HPM3_SHIFT) & CSR_MCOUNTERMASK_U_HPM3_MASK)
#define CSR_MCOUNTERMASK_U_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_HPM3_MASK) >> CSR_MCOUNTERMASK_U_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_IR_MASK (0x4U)
#define CSR_MCOUNTERMASK_U_IR_SHIFT (2U)
#define CSR_MCOUNTERMASK_U_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_IR_SHIFT) & CSR_MCOUNTERMASK_U_IR_MASK)
#define CSR_MCOUNTERMASK_U_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_IR_MASK) >> CSR_MCOUNTERMASK_U_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTERMASK_U_CY_MASK (0x1U)
#define CSR_MCOUNTERMASK_U_CY_SHIFT (0U)
#define CSR_MCOUNTERMASK_U_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTERMASK_U_CY_SHIFT) & CSR_MCOUNTERMASK_U_CY_MASK)
#define CSR_MCOUNTERMASK_U_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTERMASK_U_CY_MASK) >> CSR_MCOUNTERMASK_U_CY_SHIFT)

/* Bitfield definition for register: MCOUNTEROVF */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_HPM6_MASK (0x40U)
#define CSR_MCOUNTEROVF_HPM6_SHIFT (6U)
#define CSR_MCOUNTEROVF_HPM6_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_HPM6_SHIFT) & CSR_MCOUNTEROVF_HPM6_MASK)
#define CSR_MCOUNTEROVF_HPM6_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_HPM6_MASK) >> CSR_MCOUNTEROVF_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_HPM5_MASK (0x20U)
#define CSR_MCOUNTEROVF_HPM5_SHIFT (5U)
#define CSR_MCOUNTEROVF_HPM5_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_HPM5_SHIFT) & CSR_MCOUNTEROVF_HPM5_MASK)
#define CSR_MCOUNTEROVF_HPM5_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_HPM5_MASK) >> CSR_MCOUNTEROVF_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_HPM4_MASK (0x10U)
#define CSR_MCOUNTEROVF_HPM4_SHIFT (4U)
#define CSR_MCOUNTEROVF_HPM4_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_HPM4_SHIFT) & CSR_MCOUNTEROVF_HPM4_MASK)
#define CSR_MCOUNTEROVF_HPM4_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_HPM4_MASK) >> CSR_MCOUNTEROVF_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_HPM3_MASK (0x8U)
#define CSR_MCOUNTEROVF_HPM3_SHIFT (3U)
#define CSR_MCOUNTEROVF_HPM3_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_HPM3_SHIFT) & CSR_MCOUNTEROVF_HPM3_MASK)
#define CSR_MCOUNTEROVF_HPM3_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_HPM3_MASK) >> CSR_MCOUNTEROVF_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_IR_MASK (0x4U)
#define CSR_MCOUNTEROVF_IR_SHIFT (2U)
#define CSR_MCOUNTEROVF_IR_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_IR_SHIFT) & CSR_MCOUNTEROVF_IR_MASK)
#define CSR_MCOUNTEROVF_IR_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_IR_MASK) >> CSR_MCOUNTEROVF_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_MCOUNTEROVF_CY_MASK (0x1U)
#define CSR_MCOUNTEROVF_CY_SHIFT (0U)
#define CSR_MCOUNTEROVF_CY_SET(x) (((uint32_t)(x) << CSR_MCOUNTEROVF_CY_SHIFT) & CSR_MCOUNTEROVF_CY_MASK)
#define CSR_MCOUNTEROVF_CY_GET(x) (((uint32_t)(x) & CSR_MCOUNTEROVF_CY_MASK) >> CSR_MCOUNTEROVF_CY_SHIFT)

/* Bitfield definition for register: MSLIDELEG */
/*
 * PMOVI (RW)
 *
 * Delegate S-mode performance monitor overflow local interrupt to S-mode.
 * 0:Do not delegate to S-mode.
 * 1:Delegate to S-mode.
 */
#define CSR_MSLIDELEG_PMOVI_MASK (0x40000UL)
#define CSR_MSLIDELEG_PMOVI_SHIFT (18U)
#define CSR_MSLIDELEG_PMOVI_SET(x) (((uint32_t)(x) << CSR_MSLIDELEG_PMOVI_SHIFT) & CSR_MSLIDELEG_PMOVI_MASK)
#define CSR_MSLIDELEG_PMOVI_GET(x) (((uint32_t)(x) & CSR_MSLIDELEG_PMOVI_MASK) >> CSR_MSLIDELEG_PMOVI_SHIFT)

/*
 * BWEI (RW)
 *
 * Delegate S-mode bus read/write transaction error local interrupt to S-mode
 * 0:Do not delegate to S-mode.
 * 1:Delegate to S-mode.
 */
#define CSR_MSLIDELEG_BWEI_MASK (0x20000UL)
#define CSR_MSLIDELEG_BWEI_SHIFT (17U)
#define CSR_MSLIDELEG_BWEI_SET(x) (((uint32_t)(x) << CSR_MSLIDELEG_BWEI_SHIFT) & CSR_MSLIDELEG_BWEI_MASK)
#define CSR_MSLIDELEG_BWEI_GET(x) (((uint32_t)(x) & CSR_MSLIDELEG_BWEI_MASK) >> CSR_MSLIDELEG_BWEI_SHIFT)

/*
 * IMECCI (RW)
 *
 * Delegate S-mode slave-port ECC error local interrupt to S-mode
 * 0:Do not delegate to S-mode.
 * 1:Delegate to S-mode.
 */
#define CSR_MSLIDELEG_IMECCI_MASK (0x10000UL)
#define CSR_MSLIDELEG_IMECCI_SHIFT (16U)
#define CSR_MSLIDELEG_IMECCI_SET(x) (((uint32_t)(x) << CSR_MSLIDELEG_IMECCI_SHIFT) & CSR_MSLIDELEG_IMECCI_MASK)
#define CSR_MSLIDELEG_IMECCI_GET(x) (((uint32_t)(x) & CSR_MSLIDELEG_IMECCI_MASK) >> CSR_MSLIDELEG_IMECCI_SHIFT)

/* Bitfield definition for register: MCLK_CTL */
/*
 * FUNIT (RW)
 *
 * Level 2 clock gating enable for function units listed in the following table.
 * 16:integer arithmetic unit
 * 17:integer permutation unit
 * 18:integer mask unit
 * 19:integer division unit
 * 20:integer multiply and add unit
 * 21:floating-point multiply and add
 * unit
 * 22:floating-point miscellaneous unit
 * 23:floating-point division unit
 * 24:load/store unit
 * 31:25:Reserved
 */
#define CSR_MCLK_CTL_FUNIT_MASK (0xFFFF0000UL)
#define CSR_MCLK_CTL_FUNIT_SHIFT (16U)
#define CSR_MCLK_CTL_FUNIT_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_FUNIT_SHIFT) & CSR_MCLK_CTL_FUNIT_MASK)
#define CSR_MCLK_CTL_FUNIT_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_FUNIT_MASK) >> CSR_MCLK_CTL_FUNIT_SHIFT)

/*
 * VI (RW)
 *
 * Level 1 clock gating enable for the vector/floating-point issue queues.
 */
#define CSR_MCLK_CTL_VI_MASK (0x8000U)
#define CSR_MCLK_CTL_VI_SHIFT (15U)
#define CSR_MCLK_CTL_VI_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_VI_SHIFT) & CSR_MCLK_CTL_VI_MASK)
#define CSR_MCLK_CTL_VI_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_VI_MASK) >> CSR_MCLK_CTL_VI_SHIFT)

/*
 * VR (RW)
 *
 * Level 1 clock gating enable for the vector/floating-point register file.
 */
#define CSR_MCLK_CTL_VR_MASK (0x4000U)
#define CSR_MCLK_CTL_VR_SHIFT (14U)
#define CSR_MCLK_CTL_VR_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_VR_SHIFT) & CSR_MCLK_CTL_VR_MASK)
#define CSR_MCLK_CTL_VR_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_VR_MASK) >> CSR_MCLK_CTL_VR_SHIFT)

/*
 * AQ (RW)
 *
 * Level 1 clock gating enable for ACE load/store queues.
 */
#define CSR_MCLK_CTL_AQ_MASK (0x2000U)
#define CSR_MCLK_CTL_AQ_SHIFT (13U)
#define CSR_MCLK_CTL_AQ_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_AQ_SHIFT) & CSR_MCLK_CTL_AQ_MASK)
#define CSR_MCLK_CTL_AQ_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_AQ_MASK) >> CSR_MCLK_CTL_AQ_SHIFT)

/*
 * DQ (RW)
 *
 * Level 1 clock gating enable for data cache load/store queues.
 */
#define CSR_MCLK_CTL_DQ_MASK (0x1000U)
#define CSR_MCLK_CTL_DQ_SHIFT (12U)
#define CSR_MCLK_CTL_DQ_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_DQ_SHIFT) & CSR_MCLK_CTL_DQ_MASK)
#define CSR_MCLK_CTL_DQ_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_DQ_MASK) >> CSR_MCLK_CTL_DQ_SHIFT)

/*
 * UQ (RW)
 *
 * Level 1 clock gating enable for uncached queues
 */
#define CSR_MCLK_CTL_UQ_MASK (0x800U)
#define CSR_MCLK_CTL_UQ_SHIFT (11U)
#define CSR_MCLK_CTL_UQ_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_UQ_SHIFT) & CSR_MCLK_CTL_UQ_MASK)
#define CSR_MCLK_CTL_UQ_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_UQ_MASK) >> CSR_MCLK_CTL_UQ_SHIFT)

/*
 * FP (RW)
 *
 * Level 1 clock gating enable for scalar floating point issue unit and queues.
 */
#define CSR_MCLK_CTL_FP_MASK (0x400U)
#define CSR_MCLK_CTL_FP_SHIFT (10U)
#define CSR_MCLK_CTL_FP_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_FP_SHIFT) & CSR_MCLK_CTL_FP_MASK)
#define CSR_MCLK_CTL_FP_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_FP_MASK) >> CSR_MCLK_CTL_FP_SHIFT)

/*
 * CLKGATE (RW)
 *
 * One-hot clock gating levels.
 * 0:Level 1 clock gating in module level
 * 1:Level 2 clock gating in unit level
 * 2:Level 3 clock gating in VPU level
 * 7:3:Reserved
 */
#define CSR_MCLK_CTL_CLKGATE_MASK (0xFFU)
#define CSR_MCLK_CTL_CLKGATE_SHIFT (0U)
#define CSR_MCLK_CTL_CLKGATE_SET(x) (((uint32_t)(x) << CSR_MCLK_CTL_CLKGATE_SHIFT) & CSR_MCLK_CTL_CLKGATE_MASK)
#define CSR_MCLK_CTL_CLKGATE_GET(x) (((uint32_t)(x) & CSR_MCLK_CTL_CLKGATE_MASK) >> CSR_MCLK_CTL_CLKGATE_SHIFT)

/* Bitfield definition for register: DEXC2DBG */
/*
 * PMOV (RW)
 *
 * Indicates whether performance counter overflow interrupts are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_PMOV_MASK (0x80000UL)
#define CSR_DEXC2DBG_PMOV_SHIFT (19U)
#define CSR_DEXC2DBG_PMOV_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_PMOV_SHIFT) & CSR_DEXC2DBG_PMOV_MASK)
#define CSR_DEXC2DBG_PMOV_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_PMOV_MASK) >> CSR_DEXC2DBG_PMOV_SHIFT)

/*
 * SPF (RW)
 *
 * Indicates whether store page fault exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_SPF_MASK (0x40000UL)
#define CSR_DEXC2DBG_SPF_SHIFT (18U)
#define CSR_DEXC2DBG_SPF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_SPF_SHIFT) & CSR_DEXC2DBG_SPF_MASK)
#define CSR_DEXC2DBG_SPF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_SPF_MASK) >> CSR_DEXC2DBG_SPF_SHIFT)

/*
 * LPF (RW)
 *
 * Indicates whether load fault exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_LPF_MASK (0x20000UL)
#define CSR_DEXC2DBG_LPF_SHIFT (17U)
#define CSR_DEXC2DBG_LPF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_LPF_SHIFT) & CSR_DEXC2DBG_LPF_MASK)
#define CSR_DEXC2DBG_LPF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_LPF_MASK) >> CSR_DEXC2DBG_LPF_SHIFT)

/*
 * IPF (RW)
 *
 * Indicates whether instruction page fault exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_IPF_MASK (0x10000UL)
#define CSR_DEXC2DBG_IPF_SHIFT (16U)
#define CSR_DEXC2DBG_IPF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_IPF_SHIFT) & CSR_DEXC2DBG_IPF_MASK)
#define CSR_DEXC2DBG_IPF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_IPF_MASK) >> CSR_DEXC2DBG_IPF_SHIFT)

/*
 * BWE (RW)
 *
 * Indicates whether Bus-write Transaction Error local interrupts are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_BWE_MASK (0x8000U)
#define CSR_DEXC2DBG_BWE_SHIFT (15U)
#define CSR_DEXC2DBG_BWE_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_BWE_SHIFT) & CSR_DEXC2DBG_BWE_MASK)
#define CSR_DEXC2DBG_BWE_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_BWE_MASK) >> CSR_DEXC2DBG_BWE_SHIFT)

/*
 * SLPECC (RW)
 *
 * Indicates whether local memory slave port ECC Error local interrupts are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_SLPECC_MASK (0x4000U)
#define CSR_DEXC2DBG_SLPECC_SHIFT (14U)
#define CSR_DEXC2DBG_SLPECC_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_SLPECC_SHIFT) & CSR_DEXC2DBG_SLPECC_MASK)
#define CSR_DEXC2DBG_SLPECC_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_SLPECC_MASK) >> CSR_DEXC2DBG_SLPECC_SHIFT)

/*
 * ACE (RW)
 *
 * Indicates whether ACE-related exceptions are redirected to enter Debug Mode. This bit is present only when mmsc_cfg.ACE is set
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_ACE_MASK (0x2000U)
#define CSR_DEXC2DBG_ACE_SHIFT (13U)
#define CSR_DEXC2DBG_ACE_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_ACE_SHIFT) & CSR_DEXC2DBG_ACE_MASK)
#define CSR_DEXC2DBG_ACE_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_ACE_MASK) >> CSR_DEXC2DBG_ACE_SHIFT)

/*
 * HSP (RW)
 *
 * Indicates whether Stack Protection exceptions are redirected to enter Debug Mode. This bit is present only when mmsc_cfg.HSP is set.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_HSP_MASK (0x1000U)
#define CSR_DEXC2DBG_HSP_SHIFT (12U)
#define CSR_DEXC2DBG_HSP_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_HSP_SHIFT) & CSR_DEXC2DBG_HSP_MASK)
#define CSR_DEXC2DBG_HSP_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_HSP_MASK) >> CSR_DEXC2DBG_HSP_SHIFT)

/*
 * MEC (RW)
 *
 * Indicates whether M-mode Environment Call exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_MEC_MASK (0x800U)
#define CSR_DEXC2DBG_MEC_SHIFT (11U)
#define CSR_DEXC2DBG_MEC_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_MEC_SHIFT) & CSR_DEXC2DBG_MEC_MASK)
#define CSR_DEXC2DBG_MEC_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_MEC_MASK) >> CSR_DEXC2DBG_MEC_SHIFT)

/*
 * SEC (RW)
 *
 * Indicates whether S-mode Environment Call exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_SEC_MASK (0x200U)
#define CSR_DEXC2DBG_SEC_SHIFT (9U)
#define CSR_DEXC2DBG_SEC_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_SEC_SHIFT) & CSR_DEXC2DBG_SEC_MASK)
#define CSR_DEXC2DBG_SEC_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_SEC_MASK) >> CSR_DEXC2DBG_SEC_SHIFT)

/*
 * UEC (RW)
 *
 * Indicates whether U-mode Environment Call exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_UEC_MASK (0x100U)
#define CSR_DEXC2DBG_UEC_SHIFT (8U)
#define CSR_DEXC2DBG_UEC_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_UEC_SHIFT) & CSR_DEXC2DBG_UEC_MASK)
#define CSR_DEXC2DBG_UEC_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_UEC_MASK) >> CSR_DEXC2DBG_UEC_SHIFT)

/*
 * SAF (RW)
 *
 * Indicates whether Store Access Fault exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_SAF_MASK (0x80U)
#define CSR_DEXC2DBG_SAF_SHIFT (7U)
#define CSR_DEXC2DBG_SAF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_SAF_SHIFT) & CSR_DEXC2DBG_SAF_MASK)
#define CSR_DEXC2DBG_SAF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_SAF_MASK) >> CSR_DEXC2DBG_SAF_SHIFT)

/*
 * SAM (RW)
 *
 * Indicates whether Store Access Misaligned exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_SAM_MASK (0x40U)
#define CSR_DEXC2DBG_SAM_SHIFT (6U)
#define CSR_DEXC2DBG_SAM_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_SAM_SHIFT) & CSR_DEXC2DBG_SAM_MASK)
#define CSR_DEXC2DBG_SAM_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_SAM_MASK) >> CSR_DEXC2DBG_SAM_SHIFT)

/*
 * LAF (RW)
 *
 * Indicates whether Load Access Fault exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_LAF_MASK (0x20U)
#define CSR_DEXC2DBG_LAF_SHIFT (5U)
#define CSR_DEXC2DBG_LAF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_LAF_SHIFT) & CSR_DEXC2DBG_LAF_MASK)
#define CSR_DEXC2DBG_LAF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_LAF_MASK) >> CSR_DEXC2DBG_LAF_SHIFT)

/*
 * LAM (RW)
 *
 * Indicates whether Load Access Misaligned exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_LAM_MASK (0x10U)
#define CSR_DEXC2DBG_LAM_SHIFT (4U)
#define CSR_DEXC2DBG_LAM_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_LAM_SHIFT) & CSR_DEXC2DBG_LAM_MASK)
#define CSR_DEXC2DBG_LAM_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_LAM_MASK) >> CSR_DEXC2DBG_LAM_SHIFT)

/*
 * NMI (RW)
 *
 * Indicates whether Non-Maskable Interrupt
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_NMI_MASK (0x8U)
#define CSR_DEXC2DBG_NMI_SHIFT (3U)
#define CSR_DEXC2DBG_NMI_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_NMI_SHIFT) & CSR_DEXC2DBG_NMI_MASK)
#define CSR_DEXC2DBG_NMI_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_NMI_MASK) >> CSR_DEXC2DBG_NMI_SHIFT)

/*
 * II (RW)
 *
 * Indicates whether Illegal Instruction exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_II_MASK (0x4U)
#define CSR_DEXC2DBG_II_SHIFT (2U)
#define CSR_DEXC2DBG_II_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_II_SHIFT) & CSR_DEXC2DBG_II_MASK)
#define CSR_DEXC2DBG_II_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_II_MASK) >> CSR_DEXC2DBG_II_SHIFT)

/*
 * IAF (RW)
 *
 * Indicates whether Instruction Access Fault exceptions are redirected to enter Debug Mode
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_IAF_MASK (0x2U)
#define CSR_DEXC2DBG_IAF_SHIFT (1U)
#define CSR_DEXC2DBG_IAF_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_IAF_SHIFT) & CSR_DEXC2DBG_IAF_MASK)
#define CSR_DEXC2DBG_IAF_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_IAF_MASK) >> CSR_DEXC2DBG_IAF_SHIFT)

/*
 * IAM (RW)
 *
 * Indicates whether Instruction Access Misaligned exceptions are redirected to enter Debug Mode.
 * 0:Do not redirect
 * 1:Redirect
 */
#define CSR_DEXC2DBG_IAM_MASK (0x1U)
#define CSR_DEXC2DBG_IAM_SHIFT (0U)
#define CSR_DEXC2DBG_IAM_SET(x) (((uint32_t)(x) << CSR_DEXC2DBG_IAM_SHIFT) & CSR_DEXC2DBG_IAM_MASK)
#define CSR_DEXC2DBG_IAM_GET(x) (((uint32_t)(x) & CSR_DEXC2DBG_IAM_MASK) >> CSR_DEXC2DBG_IAM_SHIFT)

/* Bitfield definition for register: DDCAUSE */
/*
 * SUBTYPE (RO)
 *
 * Subtypes for main type.
 * The table below lists the subtypes for DCSR.CAUSE==1 and DDCAUSE.MAINTYPE==3.
 * 0:Illegal instruction
 * 1:Privileged instruction
 * 2:Non-existent CSR
 * 3:Privilege CSR access
 * 4:Read-only CSR update
 */
#define CSR_DDCAUSE_SUBTYPE_MASK (0xFF00U)
#define CSR_DDCAUSE_SUBTYPE_SHIFT (8U)
#define CSR_DDCAUSE_SUBTYPE_GET(x) (((uint32_t)(x) & CSR_DDCAUSE_SUBTYPE_MASK) >> CSR_DDCAUSE_SUBTYPE_SHIFT)

/*
 * MAINTYPE (RO)
 *
 * Cause for redirection to Debug Mode.
 * 0:Software Breakpoint (EBREAK)
 * 1:Instruction Access Misaligned (IAM)
 * 2:Instruction Access Fault (IAF)
 * 3:Illegal Instruction (II)
 * 4:Non-Maskable Interrupt (NMI)
 * 5:Load Access Misaligned (LAM)
 * 6:Load Access Fault (LAF)
 * 7:Store Access Misaligned (SAM)
 * 8:Store Access Fault (SAF)
 * 9:U-mode Environment Call (UEC)
 * 10:S-mode Environment Call (SEC)
 * 11:Instruction page fault
 * 12:M-mode Environment Call (MEC)
 * 13:Load page fault
 * 14:Reserved
 * 15:Store/AMO page fault
 * 16:Imprecise ECC error
 * 17;Bus write transaction error
 * 18:Performance Counter overflow
 * 19–31:Reserved
 * 32:Stack overflow exception
 * 33:Stack underflow exception
 * 34:ACE disabled exception
 * 35–39:Reserved
 * 40–47:ACE exception
 * ≥48:Reserved
 */
#define CSR_DDCAUSE_MAINTYPE_MASK (0xFFU)
#define CSR_DDCAUSE_MAINTYPE_SHIFT (0U)
#define CSR_DDCAUSE_MAINTYPE_GET(x) (((uint32_t)(x) & CSR_DDCAUSE_MAINTYPE_MASK) >> CSR_DDCAUSE_MAINTYPE_SHIFT)

/* Bitfield definition for register: UITB */
/*
 * ADDR (RW)
 *
 * The base address of the CoDense instruction table. This field is reserved if uitb.HW == 1.
 */
#define CSR_UITB_ADDR_MASK (0xFFFFFFFCUL)
#define CSR_UITB_ADDR_SHIFT (2U)
#define CSR_UITB_ADDR_SET(x) (((uint32_t)(x) << CSR_UITB_ADDR_SHIFT) & CSR_UITB_ADDR_MASK)
#define CSR_UITB_ADDR_GET(x) (((uint32_t)(x) & CSR_UITB_ADDR_MASK) >> CSR_UITB_ADDR_SHIFT)

/*
 * HW (RO)
 *
 * This bit specifies if the CoDense instruction table is hardwired.
 * 0:The instruction table is located in memory. uitb.ADDR should be initialized to point to the table before using the CoDense instructions.
 * 1:The instruction table is hardwired. Initialization of uitb.ADDR is not needed before using the CoDense instructions.
 */
#define CSR_UITB_HW_MASK (0x1U)
#define CSR_UITB_HW_SHIFT (0U)
#define CSR_UITB_HW_GET(x) (((uint32_t)(x) & CSR_UITB_HW_MASK) >> CSR_UITB_HW_SHIFT)

/* Bitfield definition for register: UCODE */
/*
 * OV (RW)
 *
 * Overflow flag. It will be set by DSP instructions with a saturated result.
 * 0:A saturated result is not generated
 * 1:A saturated result is generated
 */
#define CSR_UCODE_OV_MASK (0x1U)
#define CSR_UCODE_OV_SHIFT (0U)
#define CSR_UCODE_OV_SET(x) (((uint32_t)(x) << CSR_UCODE_OV_SHIFT) & CSR_UCODE_OV_MASK)
#define CSR_UCODE_OV_GET(x) (((uint32_t)(x) & CSR_UCODE_OV_MASK) >> CSR_UCODE_OV_SHIFT)

/* Bitfield definition for register: UDCAUSE */
/*
 * UDCAUSE (RW)
 *
 * This register further disambiguates causes of traps recorded in the ucause register. See the list below for details.
 * The value of UDCAUSE for precise exception:
 * When ucause == 1 (Instruction access fault)
 * 0:Reserved
 * 1:ECC/Parity error
 * 2:PMP instruction access violation
 * 3:Bus error
 * 4:PMA empty hole access
 * When ucause == 2 (Illegal instruction)
 * 0:Please parse the utval CSR
 * 1:FP disabled exception
 * 2:ACE disabled exception
 * When ucause == 5 (Load access fault)
 * 0:Reserved
 * 1:ECC/Parity error
 * 2:PMP load access violation
 * 3:Bus error
 * 4:Misaligned address
 * 5:PMA empty hole access
 * 6:PMA attribute inconsistency
 * 7:PMA NAMO exception
 * When ucause == 7 (Store access fault)
 * 0:Reserved
 * 1:ECC/Parity error
 * 2:PMP store access violation
 * 3:Bus error
 * 4:Misaligned address
 * 5:PMA empty hole access
 * 6:PMA attribute inconsistency
 * 7:PMA NAMO exception
 */
#define CSR_UDCAUSE_UDCAUSE_MASK (0x7U)
#define CSR_UDCAUSE_UDCAUSE_SHIFT (0U)
#define CSR_UDCAUSE_UDCAUSE_SET(x) (((uint32_t)(x) << CSR_UDCAUSE_UDCAUSE_SHIFT) & CSR_UDCAUSE_UDCAUSE_MASK)
#define CSR_UDCAUSE_UDCAUSE_GET(x) (((uint32_t)(x) & CSR_UDCAUSE_UDCAUSE_MASK) >> CSR_UDCAUSE_UDCAUSE_SHIFT)

/* Bitfield definition for register: UCCTLBEGINADDR */
/*
 * VA (RW)
 *
 * It is an alias to the mcctlbeginaddr register and it is only accessible to Supervisor-mode and User-mode software when mcache_ctl.CCTL_SUEN is 1. Otherwise illegal instruction exceptions will be triggered.
 */
#define CSR_UCCTLBEGINADDR_VA_MASK (0xFFFFFFFFUL)
#define CSR_UCCTLBEGINADDR_VA_SHIFT (0U)
#define CSR_UCCTLBEGINADDR_VA_SET(x) (((uint32_t)(x) << CSR_UCCTLBEGINADDR_VA_SHIFT) & CSR_UCCTLBEGINADDR_VA_MASK)
#define CSR_UCCTLBEGINADDR_VA_GET(x) (((uint32_t)(x) & CSR_UCCTLBEGINADDR_VA_MASK) >> CSR_UCCTLBEGINADDR_VA_SHIFT)

/* Bitfield definition for register: UCCTLCOMMAND */
/*
 * VA (RW)
 *
 * See User CCTL Command Definition Table
 */
#define CSR_UCCTLCOMMAND_VA_MASK (0x1FU)
#define CSR_UCCTLCOMMAND_VA_SHIFT (0U)
#define CSR_UCCTLCOMMAND_VA_SET(x) (((uint32_t)(x) << CSR_UCCTLCOMMAND_VA_SHIFT) & CSR_UCCTLCOMMAND_VA_MASK)
#define CSR_UCCTLCOMMAND_VA_GET(x) (((uint32_t)(x) & CSR_UCCTLCOMMAND_VA_MASK) >> CSR_UCCTLCOMMAND_VA_SHIFT)

/* Bitfield definition for register: SLIE */
/*
 * PMOVI (RW)
 *
 * Enable S-mode performance monitor overflow local interrupt.
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIE_PMOVI_MASK (0x40000UL)
#define CSR_SLIE_PMOVI_SHIFT (18U)
#define CSR_SLIE_PMOVI_SET(x) (((uint32_t)(x) << CSR_SLIE_PMOVI_SHIFT) & CSR_SLIE_PMOVI_MASK)
#define CSR_SLIE_PMOVI_GET(x) (((uint32_t)(x) & CSR_SLIE_PMOVI_MASK) >> CSR_SLIE_PMOVI_SHIFT)

/*
 * BWEI (RW)
 *
 * Enable S-mode bus read/write transaction error local interrupt. The processor may receive bus errors on load/store instructions or cache writebacks.
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIE_BWEI_MASK (0x20000UL)
#define CSR_SLIE_BWEI_SHIFT (17U)
#define CSR_SLIE_BWEI_SET(x) (((uint32_t)(x) << CSR_SLIE_BWEI_SHIFT) & CSR_SLIE_BWEI_MASK)
#define CSR_SLIE_BWEI_GET(x) (((uint32_t)(x) & CSR_SLIE_BWEI_MASK) >> CSR_SLIE_BWEI_SHIFT)

/*
 * IMECCI (RW)
 *
 * Enable S-mode slave-port ECC error local interrupt.
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIE_IMECCI_MASK (0x10000UL)
#define CSR_SLIE_IMECCI_SHIFT (16U)
#define CSR_SLIE_IMECCI_SET(x) (((uint32_t)(x) << CSR_SLIE_IMECCI_SHIFT) & CSR_SLIE_IMECCI_MASK)
#define CSR_SLIE_IMECCI_GET(x) (((uint32_t)(x) & CSR_SLIE_IMECCI_MASK) >> CSR_SLIE_IMECCI_SHIFT)

/* Bitfield definition for register: SLIP */
/*
 * PMOVI (RW)
 *
 * Pending control and status of S-mode performance monitor overflow local interrupt.
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIP_PMOVI_MASK (0x40000UL)
#define CSR_SLIP_PMOVI_SHIFT (18U)
#define CSR_SLIP_PMOVI_SET(x) (((uint32_t)(x) << CSR_SLIP_PMOVI_SHIFT) & CSR_SLIP_PMOVI_MASK)
#define CSR_SLIP_PMOVI_GET(x) (((uint32_t)(x) & CSR_SLIP_PMOVI_MASK) >> CSR_SLIP_PMOVI_SHIFT)

/*
 * BWEI (RW)
 *
 * Pending control and status of S-mode bus read/write transaction error local interrupt. The processor may receive bus errors on load/store instructions or cache writebacks.
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIP_BWEI_MASK (0x20000UL)
#define CSR_SLIP_BWEI_SHIFT (17U)
#define CSR_SLIP_BWEI_SET(x) (((uint32_t)(x) << CSR_SLIP_BWEI_SHIFT) & CSR_SLIP_BWEI_MASK)
#define CSR_SLIP_BWEI_GET(x) (((uint32_t)(x) & CSR_SLIP_BWEI_MASK) >> CSR_SLIP_BWEI_SHIFT)

/*
 * IMECCI (RW)
 *
 * Pending control and status of S-mode slave-port ECC error local interrupt..
 * 0:Local interrupt is not enabled.
 * 1:Local interrupt is enabled
 */
#define CSR_SLIP_IMECCI_MASK (0x10000UL)
#define CSR_SLIP_IMECCI_SHIFT (16U)
#define CSR_SLIP_IMECCI_SET(x) (((uint32_t)(x) << CSR_SLIP_IMECCI_SHIFT) & CSR_SLIP_IMECCI_MASK)
#define CSR_SLIP_IMECCI_GET(x) (((uint32_t)(x) & CSR_SLIP_IMECCI_MASK) >> CSR_SLIP_IMECCI_SHIFT)

/* Bitfield definition for register: SDCAUSE */
/*
 * PM (RW)
 *
 * When scause is imprecise exception (in the form of an interrupt), the PM field records the privileged mode of the instruction that caused the imprecise exception. The PM field encoding is defined as follows:
 * 0:User mode
 * 1:Supervisor mode
 * 2:Reserved
 * 3:Machine mode
 */
#define CSR_SDCAUSE_PM_MASK (0x60U)
#define CSR_SDCAUSE_PM_SHIFT (5U)
#define CSR_SDCAUSE_PM_SET(x) (((uint32_t)(x) << CSR_SDCAUSE_PM_SHIFT) & CSR_SDCAUSE_PM_MASK)
#define CSR_SDCAUSE_PM_GET(x) (((uint32_t)(x) & CSR_SDCAUSE_PM_MASK) >> CSR_SDCAUSE_PM_SHIFT)

/*
 * SDCAUSE (RW)
 *
 * This register further disambiguates causes of traps recorded in the scause register. See the list below for details.
 * The value of SDCAUSE for precise exception:
 *   When scause == 1 (Instruction access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP instruction access violation; 3:Bus error; 4:PMA empty hole access
 *   When scause == 2 (Illegal instruction):
 *     0:Please parse the stval CSR; 1:FP disabled exception; 2:ACE disabled exception
 *   When scause == 5 (Load access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP load access violation; 3:Bus error; 4:Misaligned address; 5:PMA empty hole access; 6:PMA attribute inconsistency; 7:PMA NAMO exception
 *   When scause == 7 (Store access fault):
 *     0:Reserved; 1:ECC/Parity error; 2:PMP load access violation; 3:Bus error; 4:Misaligned address; 5:PMA empty hole access; 6:PMA attribute inconsistency; 7:PMA NAMO exception
 * The value of SDCAUSE for imprecise exception:
 *   When scause == Local Interrupt 16 or Local Interrupt 272 (16 + 256) (ECC error local interrupt)
 *     0:Reserved; 1:LM slave port ECC/Parity error; 2:Imprecise store ECC/Parity error; 3:Imprecise load ECC/Parity error
 *   When scause == Local Interrupt 17 or Local Interrupt 273 (17 + 256) (Bus read/write transaction error local interrupt)
 *     0:Reserved; 1:Bus read error; 2:Bus write error; 3:PMP error caused by load instructions; 4:PMP error caused by store instructions; 5:PMA error caused by load instructions; 6:PMA error caused by store instructions
 */
#define CSR_SDCAUSE_SDCAUSE_MASK (0x7U)
#define CSR_SDCAUSE_SDCAUSE_SHIFT (0U)
#define CSR_SDCAUSE_SDCAUSE_SET(x) (((uint32_t)(x) << CSR_SDCAUSE_SDCAUSE_SHIFT) & CSR_SDCAUSE_SDCAUSE_MASK)
#define CSR_SDCAUSE_SDCAUSE_GET(x) (((uint32_t)(x) & CSR_SDCAUSE_SDCAUSE_MASK) >> CSR_SDCAUSE_SDCAUSE_SHIFT)

/* Bitfield definition for register: SCCTLDATA */
/*
 * VA (RW)
 *
 * See CCTL Commands Which Access mcctldata Table
 */
#define CSR_SCCTLDATA_VA_MASK (0x1FU)
#define CSR_SCCTLDATA_VA_SHIFT (0U)
#define CSR_SCCTLDATA_VA_SET(x) (((uint32_t)(x) << CSR_SCCTLDATA_VA_SHIFT) & CSR_SCCTLDATA_VA_MASK)
#define CSR_SCCTLDATA_VA_GET(x) (((uint32_t)(x) & CSR_SCCTLDATA_VA_MASK) >> CSR_SCCTLDATA_VA_SHIFT)

/* Bitfield definition for register: SCOUNTERINTEN */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_HPM6_MASK (0x40U)
#define CSR_SCOUNTERINTEN_HPM6_SHIFT (6U)
#define CSR_SCOUNTERINTEN_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_HPM6_SHIFT) & CSR_SCOUNTERINTEN_HPM6_MASK)
#define CSR_SCOUNTERINTEN_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_HPM6_MASK) >> CSR_SCOUNTERINTEN_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_HPM5_MASK (0x20U)
#define CSR_SCOUNTERINTEN_HPM5_SHIFT (5U)
#define CSR_SCOUNTERINTEN_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_HPM5_SHIFT) & CSR_SCOUNTERINTEN_HPM5_MASK)
#define CSR_SCOUNTERINTEN_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_HPM5_MASK) >> CSR_SCOUNTERINTEN_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_HPM4_MASK (0x10U)
#define CSR_SCOUNTERINTEN_HPM4_SHIFT (4U)
#define CSR_SCOUNTERINTEN_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_HPM4_SHIFT) & CSR_SCOUNTERINTEN_HPM4_MASK)
#define CSR_SCOUNTERINTEN_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_HPM4_MASK) >> CSR_SCOUNTERINTEN_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_HPM3_MASK (0x8U)
#define CSR_SCOUNTERINTEN_HPM3_SHIFT (3U)
#define CSR_SCOUNTERINTEN_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_HPM3_SHIFT) & CSR_SCOUNTERINTEN_HPM3_MASK)
#define CSR_SCOUNTERINTEN_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_HPM3_MASK) >> CSR_SCOUNTERINTEN_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_IR_MASK (0x4U)
#define CSR_SCOUNTERINTEN_IR_SHIFT (2U)
#define CSR_SCOUNTERINTEN_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_IR_SHIFT) & CSR_SCOUNTERINTEN_IR_MASK)
#define CSR_SCOUNTERINTEN_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_IR_MASK) >> CSR_SCOUNTERINTEN_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERINTEN_CY_MASK (0x1U)
#define CSR_SCOUNTERINTEN_CY_SHIFT (0U)
#define CSR_SCOUNTERINTEN_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTERINTEN_CY_SHIFT) & CSR_SCOUNTERINTEN_CY_MASK)
#define CSR_SCOUNTERINTEN_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTERINTEN_CY_MASK) >> CSR_SCOUNTERINTEN_CY_SHIFT)

/* Bitfield definition for register: SCOUNTERMASK_M */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_HPM6_MASK (0x40U)
#define CSR_SCOUNTERMASK_M_HPM6_SHIFT (6U)
#define CSR_SCOUNTERMASK_M_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_HPM6_SHIFT) & CSR_SCOUNTERMASK_M_HPM6_MASK)
#define CSR_SCOUNTERMASK_M_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_HPM6_MASK) >> CSR_SCOUNTERMASK_M_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_HPM5_MASK (0x20U)
#define CSR_SCOUNTERMASK_M_HPM5_SHIFT (5U)
#define CSR_SCOUNTERMASK_M_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_HPM5_SHIFT) & CSR_SCOUNTERMASK_M_HPM5_MASK)
#define CSR_SCOUNTERMASK_M_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_HPM5_MASK) >> CSR_SCOUNTERMASK_M_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_HPM4_MASK (0x10U)
#define CSR_SCOUNTERMASK_M_HPM4_SHIFT (4U)
#define CSR_SCOUNTERMASK_M_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_HPM4_SHIFT) & CSR_SCOUNTERMASK_M_HPM4_MASK)
#define CSR_SCOUNTERMASK_M_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_HPM4_MASK) >> CSR_SCOUNTERMASK_M_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_HPM3_MASK (0x8U)
#define CSR_SCOUNTERMASK_M_HPM3_SHIFT (3U)
#define CSR_SCOUNTERMASK_M_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_HPM3_SHIFT) & CSR_SCOUNTERMASK_M_HPM3_MASK)
#define CSR_SCOUNTERMASK_M_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_HPM3_MASK) >> CSR_SCOUNTERMASK_M_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_IR_MASK (0x4U)
#define CSR_SCOUNTERMASK_M_IR_SHIFT (2U)
#define CSR_SCOUNTERMASK_M_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_IR_SHIFT) & CSR_SCOUNTERMASK_M_IR_MASK)
#define CSR_SCOUNTERMASK_M_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_IR_MASK) >> CSR_SCOUNTERMASK_M_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_M_CY_MASK (0x1U)
#define CSR_SCOUNTERMASK_M_CY_SHIFT (0U)
#define CSR_SCOUNTERMASK_M_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_M_CY_SHIFT) & CSR_SCOUNTERMASK_M_CY_MASK)
#define CSR_SCOUNTERMASK_M_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_M_CY_MASK) >> CSR_SCOUNTERMASK_M_CY_SHIFT)

/* Bitfield definition for register: SCOUNTERMASK_S */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_HPM6_MASK (0x40U)
#define CSR_SCOUNTERMASK_S_HPM6_SHIFT (6U)
#define CSR_SCOUNTERMASK_S_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_HPM6_SHIFT) & CSR_SCOUNTERMASK_S_HPM6_MASK)
#define CSR_SCOUNTERMASK_S_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_HPM6_MASK) >> CSR_SCOUNTERMASK_S_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_HPM5_MASK (0x20U)
#define CSR_SCOUNTERMASK_S_HPM5_SHIFT (5U)
#define CSR_SCOUNTERMASK_S_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_HPM5_SHIFT) & CSR_SCOUNTERMASK_S_HPM5_MASK)
#define CSR_SCOUNTERMASK_S_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_HPM5_MASK) >> CSR_SCOUNTERMASK_S_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_HPM4_MASK (0x10U)
#define CSR_SCOUNTERMASK_S_HPM4_SHIFT (4U)
#define CSR_SCOUNTERMASK_S_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_HPM4_SHIFT) & CSR_SCOUNTERMASK_S_HPM4_MASK)
#define CSR_SCOUNTERMASK_S_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_HPM4_MASK) >> CSR_SCOUNTERMASK_S_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_HPM3_MASK (0x8U)
#define CSR_SCOUNTERMASK_S_HPM3_SHIFT (3U)
#define CSR_SCOUNTERMASK_S_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_HPM3_SHIFT) & CSR_SCOUNTERMASK_S_HPM3_MASK)
#define CSR_SCOUNTERMASK_S_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_HPM3_MASK) >> CSR_SCOUNTERMASK_S_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_IR_MASK (0x4U)
#define CSR_SCOUNTERMASK_S_IR_SHIFT (2U)
#define CSR_SCOUNTERMASK_S_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_IR_SHIFT) & CSR_SCOUNTERMASK_S_IR_MASK)
#define CSR_SCOUNTERMASK_S_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_IR_MASK) >> CSR_SCOUNTERMASK_S_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_S_CY_MASK (0x1U)
#define CSR_SCOUNTERMASK_S_CY_SHIFT (0U)
#define CSR_SCOUNTERMASK_S_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_S_CY_SHIFT) & CSR_SCOUNTERMASK_S_CY_MASK)
#define CSR_SCOUNTERMASK_S_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_S_CY_MASK) >> CSR_SCOUNTERMASK_S_CY_SHIFT)

/* Bitfield definition for register: SCOUNTERMASK_U */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_HPM6_MASK (0x40U)
#define CSR_SCOUNTERMASK_U_HPM6_SHIFT (6U)
#define CSR_SCOUNTERMASK_U_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_HPM6_SHIFT) & CSR_SCOUNTERMASK_U_HPM6_MASK)
#define CSR_SCOUNTERMASK_U_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_HPM6_MASK) >> CSR_SCOUNTERMASK_U_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_HPM5_MASK (0x20U)
#define CSR_SCOUNTERMASK_U_HPM5_SHIFT (5U)
#define CSR_SCOUNTERMASK_U_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_HPM5_SHIFT) & CSR_SCOUNTERMASK_U_HPM5_MASK)
#define CSR_SCOUNTERMASK_U_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_HPM5_MASK) >> CSR_SCOUNTERMASK_U_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_HPM4_MASK (0x10U)
#define CSR_SCOUNTERMASK_U_HPM4_SHIFT (4U)
#define CSR_SCOUNTERMASK_U_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_HPM4_SHIFT) & CSR_SCOUNTERMASK_U_HPM4_MASK)
#define CSR_SCOUNTERMASK_U_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_HPM4_MASK) >> CSR_SCOUNTERMASK_U_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_HPM3_MASK (0x8U)
#define CSR_SCOUNTERMASK_U_HPM3_SHIFT (3U)
#define CSR_SCOUNTERMASK_U_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_HPM3_SHIFT) & CSR_SCOUNTERMASK_U_HPM3_MASK)
#define CSR_SCOUNTERMASK_U_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_HPM3_MASK) >> CSR_SCOUNTERMASK_U_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_IR_MASK (0x4U)
#define CSR_SCOUNTERMASK_U_IR_SHIFT (2U)
#define CSR_SCOUNTERMASK_U_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_IR_SHIFT) & CSR_SCOUNTERMASK_U_IR_MASK)
#define CSR_SCOUNTERMASK_U_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_IR_MASK) >> CSR_SCOUNTERMASK_U_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTERMASK_U_CY_MASK (0x1U)
#define CSR_SCOUNTERMASK_U_CY_SHIFT (0U)
#define CSR_SCOUNTERMASK_U_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTERMASK_U_CY_SHIFT) & CSR_SCOUNTERMASK_U_CY_MASK)
#define CSR_SCOUNTERMASK_U_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTERMASK_U_CY_MASK) >> CSR_SCOUNTERMASK_U_CY_SHIFT)

/* Bitfield definition for register: SCOUNTEROVF */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_HPM6_MASK (0x40U)
#define CSR_SCOUNTEROVF_HPM6_SHIFT (6U)
#define CSR_SCOUNTEROVF_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_HPM6_SHIFT) & CSR_SCOUNTEROVF_HPM6_MASK)
#define CSR_SCOUNTEROVF_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_HPM6_MASK) >> CSR_SCOUNTEROVF_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_HPM5_MASK (0x20U)
#define CSR_SCOUNTEROVF_HPM5_SHIFT (5U)
#define CSR_SCOUNTEROVF_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_HPM5_SHIFT) & CSR_SCOUNTEROVF_HPM5_MASK)
#define CSR_SCOUNTEROVF_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_HPM5_MASK) >> CSR_SCOUNTEROVF_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_HPM4_MASK (0x10U)
#define CSR_SCOUNTEROVF_HPM4_SHIFT (4U)
#define CSR_SCOUNTEROVF_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_HPM4_SHIFT) & CSR_SCOUNTEROVF_HPM4_MASK)
#define CSR_SCOUNTEROVF_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_HPM4_MASK) >> CSR_SCOUNTEROVF_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_HPM3_MASK (0x8U)
#define CSR_SCOUNTEROVF_HPM3_SHIFT (3U)
#define CSR_SCOUNTEROVF_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_HPM3_SHIFT) & CSR_SCOUNTEROVF_HPM3_MASK)
#define CSR_SCOUNTEROVF_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_HPM3_MASK) >> CSR_SCOUNTEROVF_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_IR_MASK (0x4U)
#define CSR_SCOUNTEROVF_IR_SHIFT (2U)
#define CSR_SCOUNTEROVF_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_IR_SHIFT) & CSR_SCOUNTEROVF_IR_MASK)
#define CSR_SCOUNTEROVF_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_IR_MASK) >> CSR_SCOUNTEROVF_IR_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTEROVF_CY_MASK (0x1U)
#define CSR_SCOUNTEROVF_CY_SHIFT (0U)
#define CSR_SCOUNTEROVF_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTEROVF_CY_SHIFT) & CSR_SCOUNTEROVF_CY_MASK)
#define CSR_SCOUNTEROVF_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTEROVF_CY_MASK) >> CSR_SCOUNTEROVF_CY_SHIFT)

/* Bitfield definition for register: SCOUNTINHIBIT */
/*
 * HPM6 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_HPM6_MASK (0x40U)
#define CSR_SCOUNTINHIBIT_HPM6_SHIFT (6U)
#define CSR_SCOUNTINHIBIT_HPM6_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_HPM6_SHIFT) & CSR_SCOUNTINHIBIT_HPM6_MASK)
#define CSR_SCOUNTINHIBIT_HPM6_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_HPM6_MASK) >> CSR_SCOUNTINHIBIT_HPM6_SHIFT)

/*
 * HPM5 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_HPM5_MASK (0x20U)
#define CSR_SCOUNTINHIBIT_HPM5_SHIFT (5U)
#define CSR_SCOUNTINHIBIT_HPM5_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_HPM5_SHIFT) & CSR_SCOUNTINHIBIT_HPM5_MASK)
#define CSR_SCOUNTINHIBIT_HPM5_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_HPM5_MASK) >> CSR_SCOUNTINHIBIT_HPM5_SHIFT)

/*
 * HPM4 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_HPM4_MASK (0x10U)
#define CSR_SCOUNTINHIBIT_HPM4_SHIFT (4U)
#define CSR_SCOUNTINHIBIT_HPM4_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_HPM4_SHIFT) & CSR_SCOUNTINHIBIT_HPM4_MASK)
#define CSR_SCOUNTINHIBIT_HPM4_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_HPM4_MASK) >> CSR_SCOUNTINHIBIT_HPM4_SHIFT)

/*
 * HPM3 (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_HPM3_MASK (0x8U)
#define CSR_SCOUNTINHIBIT_HPM3_SHIFT (3U)
#define CSR_SCOUNTINHIBIT_HPM3_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_HPM3_SHIFT) & CSR_SCOUNTINHIBIT_HPM3_MASK)
#define CSR_SCOUNTINHIBIT_HPM3_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_HPM3_MASK) >> CSR_SCOUNTINHIBIT_HPM3_SHIFT)

/*
 * IR (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_IR_MASK (0x4U)
#define CSR_SCOUNTINHIBIT_IR_SHIFT (2U)
#define CSR_SCOUNTINHIBIT_IR_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_IR_SHIFT) & CSR_SCOUNTINHIBIT_IR_MASK)
#define CSR_SCOUNTINHIBIT_IR_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_IR_MASK) >> CSR_SCOUNTINHIBIT_IR_SHIFT)

/*
 * TM (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_TM_MASK (0x2U)
#define CSR_SCOUNTINHIBIT_TM_SHIFT (1U)
#define CSR_SCOUNTINHIBIT_TM_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_TM_SHIFT) & CSR_SCOUNTINHIBIT_TM_MASK)
#define CSR_SCOUNTINHIBIT_TM_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_TM_MASK) >> CSR_SCOUNTINHIBIT_TM_SHIFT)

/*
 * CY (RW)
 *
 * See register description
 */
#define CSR_SCOUNTINHIBIT_CY_MASK (0x1U)
#define CSR_SCOUNTINHIBIT_CY_SHIFT (0U)
#define CSR_SCOUNTINHIBIT_CY_SET(x) (((uint32_t)(x) << CSR_SCOUNTINHIBIT_CY_SHIFT) & CSR_SCOUNTINHIBIT_CY_MASK)
#define CSR_SCOUNTINHIBIT_CY_GET(x) (((uint32_t)(x) & CSR_SCOUNTINHIBIT_CY_MASK) >> CSR_SCOUNTINHIBIT_CY_SHIFT)

/* Bitfield definition for register: SHPMEVENT3 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT3_SEL_MASK (0x1F0U)
#define CSR_SHPMEVENT3_SEL_SHIFT (4U)
#define CSR_SHPMEVENT3_SEL_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT3_SEL_SHIFT) & CSR_SHPMEVENT3_SEL_MASK)
#define CSR_SHPMEVENT3_SEL_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT3_SEL_MASK) >> CSR_SHPMEVENT3_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT3_TYPE_MASK (0xFU)
#define CSR_SHPMEVENT3_TYPE_SHIFT (0U)
#define CSR_SHPMEVENT3_TYPE_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT3_TYPE_SHIFT) & CSR_SHPMEVENT3_TYPE_MASK)
#define CSR_SHPMEVENT3_TYPE_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT3_TYPE_MASK) >> CSR_SHPMEVENT3_TYPE_SHIFT)

/* Bitfield definition for register: SHPMEVENT4 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT4_SEL_MASK (0x1F0U)
#define CSR_SHPMEVENT4_SEL_SHIFT (4U)
#define CSR_SHPMEVENT4_SEL_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT4_SEL_SHIFT) & CSR_SHPMEVENT4_SEL_MASK)
#define CSR_SHPMEVENT4_SEL_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT4_SEL_MASK) >> CSR_SHPMEVENT4_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT4_TYPE_MASK (0xFU)
#define CSR_SHPMEVENT4_TYPE_SHIFT (0U)
#define CSR_SHPMEVENT4_TYPE_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT4_TYPE_SHIFT) & CSR_SHPMEVENT4_TYPE_MASK)
#define CSR_SHPMEVENT4_TYPE_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT4_TYPE_MASK) >> CSR_SHPMEVENT4_TYPE_SHIFT)

/* Bitfield definition for register: SHPMEVENT5 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT5_SEL_MASK (0x1F0U)
#define CSR_SHPMEVENT5_SEL_SHIFT (4U)
#define CSR_SHPMEVENT5_SEL_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT5_SEL_SHIFT) & CSR_SHPMEVENT5_SEL_MASK)
#define CSR_SHPMEVENT5_SEL_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT5_SEL_MASK) >> CSR_SHPMEVENT5_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT5_TYPE_MASK (0xFU)
#define CSR_SHPMEVENT5_TYPE_SHIFT (0U)
#define CSR_SHPMEVENT5_TYPE_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT5_TYPE_SHIFT) & CSR_SHPMEVENT5_TYPE_MASK)
#define CSR_SHPMEVENT5_TYPE_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT5_TYPE_MASK) >> CSR_SHPMEVENT5_TYPE_SHIFT)

/* Bitfield definition for register: SHPMEVENT6 */
/*
 * SEL (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT6_SEL_MASK (0x1F0U)
#define CSR_SHPMEVENT6_SEL_SHIFT (4U)
#define CSR_SHPMEVENT6_SEL_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT6_SEL_SHIFT) & CSR_SHPMEVENT6_SEL_MASK)
#define CSR_SHPMEVENT6_SEL_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT6_SEL_MASK) >> CSR_SHPMEVENT6_SEL_SHIFT)

/*
 * TYPE (RW)
 *
 * See Event Selectors table
 */
#define CSR_SHPMEVENT6_TYPE_MASK (0xFU)
#define CSR_SHPMEVENT6_TYPE_SHIFT (0U)
#define CSR_SHPMEVENT6_TYPE_SET(x) (((uint32_t)(x) << CSR_SHPMEVENT6_TYPE_SHIFT) & CSR_SHPMEVENT6_TYPE_MASK)
#define CSR_SHPMEVENT6_TYPE_GET(x) (((uint32_t)(x) & CSR_SHPMEVENT6_TYPE_MASK) >> CSR_SHPMEVENT6_TYPE_SHIFT)

/* Bitfield definition for register: MICM_CFG */
/*
 * SETH (RO)
 *
 * This bit extends the ISET field.
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_SETH_MASK (0x1000000UL)
#define CSR_MICM_CFG_SETH_SHIFT (24U)
#define CSR_MICM_CFG_SETH_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_SETH_MASK) >> CSR_MICM_CFG_SETH_SHIFT)

/*
 * ILM_ECC (RO)
 *
 * ILM soft-error protection scheme
 * 0:No parity/ECC
 * 1:Parity
 * 2:ECC
 * 3:Reserved
 *  ILM is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_ILM_ECC_MASK (0x600000UL)
#define CSR_MICM_CFG_ILM_ECC_SHIFT (21U)
#define CSR_MICM_CFG_ILM_ECC_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ILM_ECC_MASK) >> CSR_MICM_CFG_ILM_ECC_SHIFT)

/*
 * ILMSZ (RO)
 *
 * ILM Size
 * 0:0 Byte
 * 1:1 KiB
 * 2:2 KiB
 * 3:4 KiB
 * 4:8 KiB
 * 5:16 KiB
 * 6:32 KiB
 * 7:64 KiB
 * 8:128 KiB
 * 9:256 KiB
 * 10:512 KiB
 * 11:1 MiB
 * 12:2 MiB
 * 13:4 MiB
 * 14:8 MiB
 * 15:16 MiB
 * 16-31:Reserved
 * When ILM is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_ILMSZ_MASK (0xF8000UL)
#define CSR_MICM_CFG_ILMSZ_SHIFT (15U)
#define CSR_MICM_CFG_ILMSZ_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ILMSZ_MASK) >> CSR_MICM_CFG_ILMSZ_SHIFT)

/*
 * ILMB (RW)
 *
 * Number of ILM base registers present
 * 0:No ILM base register present
 * 1:One ILM base register present
 * 2-7:Reserved
 * When ILM is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_ILMB_MASK (0x7000U)
#define CSR_MICM_CFG_ILMB_SHIFT (12U)
#define CSR_MICM_CFG_ILMB_SET(x) (((uint32_t)(x) << CSR_MICM_CFG_ILMB_SHIFT) & CSR_MICM_CFG_ILMB_MASK)
#define CSR_MICM_CFG_ILMB_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ILMB_MASK) >> CSR_MICM_CFG_ILMB_SHIFT)

/*
 * IC_ECC (RO)
 *
 * Cache soft-error protection scheme
 * 0:No parity/ECC
 * 1:Parity
 * 2:ECC
 * 3:Reserved
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_IC_ECC_MASK (0xC00U)
#define CSR_MICM_CFG_IC_ECC_SHIFT (10U)
#define CSR_MICM_CFG_IC_ECC_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_IC_ECC_MASK) >> CSR_MICM_CFG_IC_ECC_SHIFT)

/*
 * ILCK (RO)
 *
 * I-Cache locking support
 * 0:No locking support
 * 1:With locking support
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_ILCK_MASK (0x200U)
#define CSR_MICM_CFG_ILCK_SHIFT (9U)
#define CSR_MICM_CFG_ILCK_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ILCK_MASK) >> CSR_MICM_CFG_ILCK_SHIFT)

/*
 * ISZ (RO)
 *
 * Cache block (line) size
 * 0:No I-Cache
 * 1:8 bytes
 * 2:16 bytes
 * 3:32 bytes
 * 4:64 bytes
 * 5:128 bytes
 * 6-7:Reserved
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_ISZ_MASK (0x1C0U)
#define CSR_MICM_CFG_ISZ_SHIFT (6U)
#define CSR_MICM_CFG_ISZ_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ISZ_MASK) >> CSR_MICM_CFG_ISZ_SHIFT)

/*
 * IWAY (RO)
 *
 * Associativity of I-Cache
 * 0:Direct-mapped
 * 1:2-way
 * 2:3-way
 * 3:4-way
 * 4:5-way
 * 5:6-way
 * 6:7-way
 * 7:8-way
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MICM_CFG_IWAY_MASK (0x38U)
#define CSR_MICM_CFG_IWAY_SHIFT (3U)
#define CSR_MICM_CFG_IWAY_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_IWAY_MASK) >> CSR_MICM_CFG_IWAY_SHIFT)

/*
 * ISET (RO)
 *
 * I-Cache sets (# of cache lines per way):
 * When micm_cfg.SETH==0:
 * 0:64
 * 1:128
 * 2:256
 * 3:512
 * 4:1024
 * 5:2048
 * 6:4096
 * 7:Reserved
 * When micm_cfg.SETH==1:
 * 0:32
 * 1:16
 * 2:8
 * 3-7:Reserved
 */
#define CSR_MICM_CFG_ISET_MASK (0x7U)
#define CSR_MICM_CFG_ISET_SHIFT (0U)
#define CSR_MICM_CFG_ISET_GET(x) (((uint32_t)(x) & CSR_MICM_CFG_ISET_MASK) >> CSR_MICM_CFG_ISET_SHIFT)

/* Bitfield definition for register: MDCM_CFG */
/*
 * SETH (RO)
 *
 * This bit extends the DSET field.
 * When data cache is not configured, this field should be ignored
 */
#define CSR_MDCM_CFG_SETH_MASK (0x1000000UL)
#define CSR_MDCM_CFG_SETH_SHIFT (24U)
#define CSR_MDCM_CFG_SETH_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_SETH_MASK) >> CSR_MDCM_CFG_SETH_SHIFT)

/*
 * DLM_ECC (RO)
 *
 * DLM soft-error protection scheme
 * 0:No parity/ECC
 * 1:Parity
 * 2:ECC
 * 3:Reserved
 * When DLM is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DLM_ECC_MASK (0x600000UL)
#define CSR_MDCM_CFG_DLM_ECC_SHIFT (21U)
#define CSR_MDCM_CFG_DLM_ECC_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DLM_ECC_MASK) >> CSR_MDCM_CFG_DLM_ECC_SHIFT)

/*
 * DLMSZ (RO)
 *
 * DLM Size
 * 0:0 Byte
 * 1:1 KiB
 * 2:2 KiB
 * 3:4 KiB
 * 4:8 KiB
 * 5:16 KiB
 * 6:32 KiB
 * 7:64 KiB
 * 8:128 KiB
 * 9:256 KiB
 * 10:512 KiB
 * 11:1 MiB
 * 12:2 MiB
 * 13:4 MiB
 * 14:8 MiB
 * 15:16 MiB
 * 16-31:Reserved
 * When ILM is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DLMSZ_MASK (0xF8000UL)
#define CSR_MDCM_CFG_DLMSZ_SHIFT (15U)
#define CSR_MDCM_CFG_DLMSZ_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DLMSZ_MASK) >> CSR_MDCM_CFG_DLMSZ_SHIFT)

/*
 * DLMB (RO)
 *
 * Number of DLM base registers present
 * 0:No DLM base register present
 * 1:One DLM base register present
 * 2-7:Reserved
 * When DLM is not configured, this field should be ignored
 */
#define CSR_MDCM_CFG_DLMB_MASK (0x7000U)
#define CSR_MDCM_CFG_DLMB_SHIFT (12U)
#define CSR_MDCM_CFG_DLMB_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DLMB_MASK) >> CSR_MDCM_CFG_DLMB_SHIFT)

/*
 * DC_ECC (RO)
 *
 * Cache soft-error protection scheme
 * 0:No parity/ECC support
 * 1:Has parity support
 * 2:Has ECC support
 * 3:Reserved
 * When data cache is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DC_ECC_MASK (0xC00U)
#define CSR_MDCM_CFG_DC_ECC_SHIFT (10U)
#define CSR_MDCM_CFG_DC_ECC_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DC_ECC_MASK) >> CSR_MDCM_CFG_DC_ECC_SHIFT)

/*
 * DLCK (RO)
 *
 * D-Cache locking support
 * 0:No locking support
 * 1:With locking support
 * When data cache is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DLCK_MASK (0x200U)
#define CSR_MDCM_CFG_DLCK_SHIFT (9U)
#define CSR_MDCM_CFG_DLCK_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DLCK_MASK) >> CSR_MDCM_CFG_DLCK_SHIFT)

/*
 * DSZ (RO)
 *
 * Cache block (line) size
 * 0:No I-Cache
 * 1:8 bytes
 * 2:16 bytes
 * 3:32 bytes
 * 4:64 bytes
 * 5:128 bytes
 * 6-7:Reserved
 * When instruction cache is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DSZ_MASK (0x1C0U)
#define CSR_MDCM_CFG_DSZ_SHIFT (6U)
#define CSR_MDCM_CFG_DSZ_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DSZ_MASK) >> CSR_MDCM_CFG_DSZ_SHIFT)

/*
 * DWAY (RO)
 *
 * Associativity of D-Cache
 * 0:Direct-mapped
 * 1:2-way
 * 2:3-way
 * 3:4-way
 * 4:5-way
 * 5:6-way
 * 6:7-way
 * 7:8-way
 * When data cache is not configured, this field should be ignored.
 */
#define CSR_MDCM_CFG_DWAY_MASK (0x38U)
#define CSR_MDCM_CFG_DWAY_SHIFT (3U)
#define CSR_MDCM_CFG_DWAY_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DWAY_MASK) >> CSR_MDCM_CFG_DWAY_SHIFT)

/*
 * DSET (RO)
 *
 * D-Cache sets (# of cache lines per way):
 * When mdcm_cfg.SETH==0:
 * 0:64
 * 1:128
 * 2:256
 * 3:512
 * 4:1024
 * 5:2048
 * 6:4096
 * 7:Reserved
 * When mdcm_cfg.SETH==1:
 * 0:32
 * 1:16
 * 2:8
 * 3-7:Reserved
 * When data cache is not configured, this field should be ignored
 */
#define CSR_MDCM_CFG_DSET_MASK (0x7U)
#define CSR_MDCM_CFG_DSET_SHIFT (0U)
#define CSR_MDCM_CFG_DSET_GET(x) (((uint32_t)(x) & CSR_MDCM_CFG_DSET_MASK) >> CSR_MDCM_CFG_DSET_SHIFT)

/* Bitfield definition for register: MMSC_CFG */
/*
 * MSC_EXT (RO)
 *
 * Indicates if the mmsc_cfg2 CSR is present or not.
 * 0:The mmsc_cfg2 CSR is not present.
 * 1:The mmsc_cfg2 CSR is present
 */
#define CSR_MMSC_CFG_MSC_EXT_MASK (0x80000000UL)
#define CSR_MMSC_CFG_MSC_EXT_SHIFT (31U)
#define CSR_MMSC_CFG_MSC_EXT_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_MSC_EXT_MASK) >> CSR_MMSC_CFG_MSC_EXT_SHIFT)

/*
 * PPMA (RO)
 *
 * Indicates if programmable PMA setup with PMA region CSRs is supported or not
 * 0:Programmable PMA setup is not supported.
 * 1:Programmable PMA setup is supported.
 */
#define CSR_MMSC_CFG_PPMA_MASK (0x40000000UL)
#define CSR_MMSC_CFG_PPMA_SHIFT (30U)
#define CSR_MMSC_CFG_PPMA_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_PPMA_MASK) >> CSR_MMSC_CFG_PPMA_SHIFT)

/*
 * EDSP (RO)
 *
 * Indicates if the DSP extension is supported or not
 * 0:The DSP extension is not supported.
 * 1:The DSP extension is supported.
 */
#define CSR_MMSC_CFG_EDSP_MASK (0x20000000UL)
#define CSR_MMSC_CFG_EDSP_SHIFT (29U)
#define CSR_MMSC_CFG_EDSP_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_EDSP_MASK) >> CSR_MMSC_CFG_EDSP_SHIFT)

/*
 * VCCTL (RO)
 *
 * Indicates the version number of CCTL command operation scheme supported by an implementation
 * 0:instruction cache and data cache are not configured.
 * 1:instruction cache or data cache is configured.
 */
#define CSR_MMSC_CFG_VCCTL_MASK (0xC0000UL)
#define CSR_MMSC_CFG_VCCTL_SHIFT (18U)
#define CSR_MMSC_CFG_VCCTL_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_VCCTL_MASK) >> CSR_MMSC_CFG_VCCTL_SHIFT)

/*
 * EFHW (RO)
 *
 * Indicates the support of FLHW and FSHW instructions
 * 0:FLHW and FSHW instructions are not supported
 * 1:FLHW and FSHW instructions are supported.
 */
#define CSR_MMSC_CFG_EFHW_MASK (0x20000UL)
#define CSR_MMSC_CFG_EFHW_SHIFT (17U)
#define CSR_MMSC_CFG_EFHW_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_EFHW_MASK) >> CSR_MMSC_CFG_EFHW_SHIFT)

/*
 * CCTLCSR (RO)
 *
 * Indicates the presence of CSRs for CCTL operations.
 * 0:Feature of CSRs for CCTL operations is not supported.
 * 1:Feature of CSRs for CCTL operations is supported.
 */
#define CSR_MMSC_CFG_CCTLCSR_MASK (0x10000UL)
#define CSR_MMSC_CFG_CCTLCSR_SHIFT (16U)
#define CSR_MMSC_CFG_CCTLCSR_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_CCTLCSR_MASK) >> CSR_MMSC_CFG_CCTLCSR_SHIFT)

/*
 * PMNDS (RO)
 *
 * Indicates if Andes-enhanced performance monitoring feature is present or no.
 * 0:Andes-enhanced performance monitoring feature is not supported.
 * 1:Andes-enhanced performance monitoring feature is supported.
 */
#define CSR_MMSC_CFG_PMNDS_MASK (0x8000U)
#define CSR_MMSC_CFG_PMNDS_SHIFT (15U)
#define CSR_MMSC_CFG_PMNDS_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_PMNDS_MASK) >> CSR_MMSC_CFG_PMNDS_SHIFT)

/*
 * LMSLVP (RO)
 *
 * Indicates if local memory slave port is present or not.
 * 0:Local memory slave port is not present.
 * 1:Local memory slave port is implemented.
 */
#define CSR_MMSC_CFG_LMSLVP_MASK (0x4000U)
#define CSR_MMSC_CFG_LMSLVP_SHIFT (14U)
#define CSR_MMSC_CFG_LMSLVP_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_LMSLVP_MASK) >> CSR_MMSC_CFG_LMSLVP_SHIFT)

/*
 * EV5PE (RO)
 *
 * Indicates whether AndeStar V5 Performance Extension is implemented or not. D45 always implements AndeStar V5 Performance Extension.
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_EV5PE_MASK (0x2000U)
#define CSR_MMSC_CFG_EV5PE_SHIFT (13U)
#define CSR_MMSC_CFG_EV5PE_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_EV5PE_MASK) >> CSR_MMSC_CFG_EV5PE_SHIFT)

/*
 * VPLIC (RO)
 *
 * Indicates whether the Andes Vectored PLIC Extension is implemented or not.
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_VPLIC_MASK (0x1000U)
#define CSR_MMSC_CFG_VPLIC_SHIFT (12U)
#define CSR_MMSC_CFG_VPLIC_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_VPLIC_MASK) >> CSR_MMSC_CFG_VPLIC_SHIFT)

/*
 * ACE (RO)
 *
 * Indicates whether the Andes StackSafe hardware stack protection extension is implemented or not.
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_ACE_MASK (0x40U)
#define CSR_MMSC_CFG_ACE_SHIFT (6U)
#define CSR_MMSC_CFG_ACE_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_ACE_MASK) >> CSR_MMSC_CFG_ACE_SHIFT)

/*
 * HSP (RO)
 *
 * Indicates whether the Andes PowerBrake (Performance Throttling) power/performance scaling extension is implemented or not.
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_HSP_MASK (0x20U)
#define CSR_MMSC_CFG_HSP_SHIFT (5U)
#define CSR_MMSC_CFG_HSP_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_HSP_MASK) >> CSR_MMSC_CFG_HSP_SHIFT)

/*
 * PFT (RO)
 *
 * Indicates whether the Andes PowerBrake (Performance Throttling) power/performance scaling extension is implemented or not
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_PFT_MASK (0x10U)
#define CSR_MMSC_CFG_PFT_SHIFT (4U)
#define CSR_MMSC_CFG_PFT_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_PFT_MASK) >> CSR_MMSC_CFG_PFT_SHIFT)

/*
 * ECD (RO)
 *
 * Indicates whether the Andes CoDense Extension is implemented or not.
 * 0:Not implemented.
 * 1:Implemented.
 */
#define CSR_MMSC_CFG_ECD_MASK (0x8U)
#define CSR_MMSC_CFG_ECD_SHIFT (3U)
#define CSR_MMSC_CFG_ECD_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_ECD_MASK) >> CSR_MMSC_CFG_ECD_SHIFT)

/*
 * TLB_ECC (RO)
 *
 * TLB parity/ECC support configuration.
 * 0:No parity/ECC
 * 1:Parity
 * 2:ECC
 * 3:Reserved
 */
#define CSR_MMSC_CFG_TLB_ECC_MASK (0x6U)
#define CSR_MMSC_CFG_TLB_ECC_SHIFT (1U)
#define CSR_MMSC_CFG_TLB_ECC_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_TLB_ECC_MASK) >> CSR_MMSC_CFG_TLB_ECC_SHIFT)

/*
 * ECC (RO)
 *
 * Indicates whether the parity/ECC soft-error protection is implemented or not.
 * 0:Not implemented.
 * 1:Implemented.
 * The specific parity/ECC scheme used for each protected RAM is specified by the control bits in the following list.
 * micm_cfg.IC_ECC
 * micm_cfg.ILM_ECC
 * mdcm_cfg.DC_ECC
 * mdcm_cfg.DLM_ECC
 * mmsc_cfg.TLB_ECC
 */
#define CSR_MMSC_CFG_ECC_MASK (0x1U)
#define CSR_MMSC_CFG_ECC_SHIFT (0U)
#define CSR_MMSC_CFG_ECC_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG_ECC_MASK) >> CSR_MMSC_CFG_ECC_SHIFT)

/* Bitfield definition for register: MMSC_CFG2 */
/*
 * FINV (RO)
 *
 * Indicates if scalar FPU is implemented in VPU
 * 0:Scalar FPU is not implemented in VPU
 * 1:Scalar FPU is implemented in VPU
 */
#define CSR_MMSC_CFG2_FINV_MASK (0x20U)
#define CSR_MMSC_CFG2_FINV_SHIFT (5U)
#define CSR_MMSC_CFG2_FINV_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG2_FINV_MASK) >> CSR_MMSC_CFG2_FINV_SHIFT)

/*
 * ZFH (RO)
 *
 * Indicates if the FP16 half-precision floating-point extension (Zfh) is supported or not.
 * 0:The FP16 extension is not supported.
 * 1:The FP16 extension is supported
 */
#define CSR_MMSC_CFG2_ZFH_MASK (0x2U)
#define CSR_MMSC_CFG2_ZFH_SHIFT (1U)
#define CSR_MMSC_CFG2_ZFH_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG2_ZFH_MASK) >> CSR_MMSC_CFG2_ZFH_SHIFT)

/*
 * BF16CVT (RO)
 *
 * Indicates if the BFLOAT16 conversion extension
 * is supported or not.
 * 0:The BFLOAT16 conversion extension is not supported
 * 1:The BFLOAT16 conversion extension is supported
 */
#define CSR_MMSC_CFG2_BF16CVT_MASK (0x1U)
#define CSR_MMSC_CFG2_BF16CVT_SHIFT (0U)
#define CSR_MMSC_CFG2_BF16CVT_GET(x) (((uint32_t)(x) & CSR_MMSC_CFG2_BF16CVT_MASK) >> CSR_MMSC_CFG2_BF16CVT_SHIFT)


#endif /* HPM_CSR_H */
