//*****************************************************************************
//
//  am_reg_sysctrl.h
//! @file
//!
//! @brief Register macros for the SYSCTRL module
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_REG_SYSCTRL_H
#define AM_REG_SYSCTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_SYSCTRL_NUM_MODULES                   1
#define AM_REG_SYSCTRLn(n) \
    (REG_SYSCTRL_BASEADDR + 0x00000000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_SYSCTRL_ICTR_O                        0xE000E004
#define AM_REG_SYSCTRL_ACTLR_O                       0xE000E008
#define AM_REG_SYSCTRL_ICSR_O                        0xE000ED04
#define AM_REG_SYSCTRL_VTOR_O                        0xE000ED08
#define AM_REG_SYSCTRL_AIRCR_O                       0xE000ED0C
#define AM_REG_SYSCTRL_SCR_O                         0xE000ED10
#define AM_REG_SYSCTRL_CCR_O                         0xE000ED14
#define AM_REG_SYSCTRL_SHPR1_O                       0xE000ED18
#define AM_REG_SYSCTRL_SHPR2_O                       0xE000ED1C
#define AM_REG_SYSCTRL_SHPR3_O                       0xE000ED20
#define AM_REG_SYSCTRL_SHCSR_O                       0xE000ED24
#define AM_REG_SYSCTRL_CFSR_O                        0xE000ED28
#define AM_REG_SYSCTRL_HFSR_O                        0xE000ED2C
#define AM_REG_SYSCTRL_MMFAR_O                       0xE000ED34
#define AM_REG_SYSCTRL_BFAR_O                        0xE000ED38
#define AM_REG_SYSCTRL_CPACR_O                       0xE000ED88
#define AM_REG_SYSCTRL_DEMCR_O                       0xE000EDFC
#define AM_REG_SYSCTRL_STIR_O                        0xE000EF00
#define AM_REG_SYSCTRL_FPCCR_O                       0xE000EF34
#define AM_REG_SYSCTRL_FPCAR_O                       0xE000EF38
#define AM_REG_SYSCTRL_FPDSCR_O                      0xE000EF3C

//*****************************************************************************
//
// SYSCTRL_ICTR - Interrupt Controller Type Register (NVIC)
//
//*****************************************************************************
// Total number of interrupt lines in groups of 32.
#define AM_REG_SYSCTRL_ICTR_INTLINESNUM_S            0
#define AM_REG_SYSCTRL_ICTR_INTLINESNUM_M            0x0000000F
#define AM_REG_SYSCTRL_ICTR_INTLINESNUM(n)           (((uint32_t)(n) << 0) & 0x0000000F)

//*****************************************************************************
//
// SYSCTRL_ACTLR - Auxilliary Control Register
//
//*****************************************************************************
// Disables lazy stacking of floating point context.
#define AM_REG_SYSCTRL_ACTLR_DISFPCA_S               9
#define AM_REG_SYSCTRL_ACTLR_DISFPCA_M               0x00000200
#define AM_REG_SYSCTRL_ACTLR_DISFPCA(n)              (((uint32_t)(n) << 9) & 0x00000200)

// Disables floating point instructions completing out of order with respect to
// integer instructions.
#define AM_REG_SYSCTRL_ACTLR_DISOOFP_S               8
#define AM_REG_SYSCTRL_ACTLR_DISOOFP_M               0x00000100
#define AM_REG_SYSCTRL_ACTLR_DISOOFP(n)              (((uint32_t)(n) << 8) & 0x00000100)

// Disables folding of IT instructions.
#define AM_REG_SYSCTRL_ACTLR_DISFOLD_S               2
#define AM_REG_SYSCTRL_ACTLR_DISFOLD_M               0x00000004
#define AM_REG_SYSCTRL_ACTLR_DISFOLD(n)              (((uint32_t)(n) << 2) & 0x00000004)

// Disables write buffer use during default memory map accesses.
#define AM_REG_SYSCTRL_ACTLR_DISDEFWBUF_S            1
#define AM_REG_SYSCTRL_ACTLR_DISDEFWBUF_M            0x00000002
#define AM_REG_SYSCTRL_ACTLR_DISDEFWBUF(n)           (((uint32_t)(n) << 1) & 0x00000002)

// Disables interruption of multi-cycle instructions.
#define AM_REG_SYSCTRL_ACTLR_DISMCYCINT_S            0
#define AM_REG_SYSCTRL_ACTLR_DISMCYCINT_M            0x00000001
#define AM_REG_SYSCTRL_ACTLR_DISMCYCINT(n)           (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_ICSR - Interrupt Control and State Register
//
//*****************************************************************************
// Pend an NMI exception.
#define AM_REG_SYSCTRL_ICSR_NMIPENDSET_S             31
#define AM_REG_SYSCTRL_ICSR_NMIPENDSET_M             0x80000000
#define AM_REG_SYSCTRL_ICSR_NMIPENDSET(n)            (((uint32_t)(n) << 31) & 0x80000000)

// Set the PendSV interrupt as pending.
#define AM_REG_SYSCTRL_ICSR_PENDSVSET_S              28
#define AM_REG_SYSCTRL_ICSR_PENDSVSET_M              0x10000000
#define AM_REG_SYSCTRL_ICSR_PENDSVSET(n)             (((uint32_t)(n) << 28) & 0x10000000)

// Remove the pending status of the PendSV exception.
#define AM_REG_SYSCTRL_ICSR_PENDSVCLR_S              27
#define AM_REG_SYSCTRL_ICSR_PENDSVCLR_M              0x08000000
#define AM_REG_SYSCTRL_ICSR_PENDSVCLR(n)             (((uint32_t)(n) << 27) & 0x08000000)

// Set the SysTick exception as pending.
#define AM_REG_SYSCTRL_ICSR_PENDSTSET_S              26
#define AM_REG_SYSCTRL_ICSR_PENDSTSET_M              0x04000000
#define AM_REG_SYSCTRL_ICSR_PENDSTSET(n)             (((uint32_t)(n) << 26) & 0x04000000)

// Remove the pending status of the SysTick exception.
#define AM_REG_SYSCTRL_ICSR_PENDSTCLR_S              25
#define AM_REG_SYSCTRL_ICSR_PENDSTCLR_M              0x02000000
#define AM_REG_SYSCTRL_ICSR_PENDSTCLR(n)             (((uint32_t)(n) << 25) & 0x02000000)

// Indicates whether a pending exception will be serviced on exit from debug
// halt state.
#define AM_REG_SYSCTRL_ICSR_ISRPREEMPT_S             23
#define AM_REG_SYSCTRL_ICSR_ISRPREEMPT_M             0x00800000
#define AM_REG_SYSCTRL_ICSR_ISRPREEMPT(n)            (((uint32_t)(n) << 23) & 0x00800000)

// Indicates whether an external interrupt, generated by the NVIC, is pending.
#define AM_REG_SYSCTRL_ICSR_ISRPENDING_S             22
#define AM_REG_SYSCTRL_ICSR_ISRPENDING_M             0x00400000
#define AM_REG_SYSCTRL_ICSR_ISRPENDING(n)            (((uint32_t)(n) << 22) & 0x00400000)

// The exception number of the highest priority pending exception.
#define AM_REG_SYSCTRL_ICSR_VECTPENDING_S            12
#define AM_REG_SYSCTRL_ICSR_VECTPENDING_M            0x001FF000
#define AM_REG_SYSCTRL_ICSR_VECTPENDING(n)           (((uint32_t)(n) << 12) & 0x001FF000)

// Indicates whether there is an active exception other than the exception shown
// by IPSR.
#define AM_REG_SYSCTRL_ICSR_RETTOBASE_S              11
#define AM_REG_SYSCTRL_ICSR_RETTOBASE_M              0x00000800
#define AM_REG_SYSCTRL_ICSR_RETTOBASE(n)             (((uint32_t)(n) << 11) & 0x00000800)

// The exception number of the current executing exception.
#define AM_REG_SYSCTRL_ICSR_VECTACTIVE_S             0
#define AM_REG_SYSCTRL_ICSR_VECTACTIVE_M             0x000001FF
#define AM_REG_SYSCTRL_ICSR_VECTACTIVE(n)            (((uint32_t)(n) << 0) & 0x000001FF)

//*****************************************************************************
//
// SYSCTRL_VTOR - Vector Table Offset Register.
//
//*****************************************************************************
// Vector table base address.
#define AM_REG_SYSCTRL_VTOR_VALUE_S                  0
#define AM_REG_SYSCTRL_VTOR_VALUE_M                  0xFFFFFFFF
#define AM_REG_SYSCTRL_VTOR_VALUE(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SYSCTRL_AIRCR - Application Interrupt and Reset Control Register.
//
//*****************************************************************************
// Register writes must write 0x5FA to this field, otherwise the write is
// ignored.
#define AM_REG_SYSCTRL_AIRCR_VECTKEY_S               16
#define AM_REG_SYSCTRL_AIRCR_VECTKEY_M               0xFFFF0000
#define AM_REG_SYSCTRL_AIRCR_VECTKEY(n)              (((uint32_t)(n) << 16) & 0xFFFF0000)

// Indicates endianness of memory architecture. (Little = 0, Big = 1)
#define AM_REG_SYSCTRL_AIRCR_ENDIANNESS_S            15
#define AM_REG_SYSCTRL_AIRCR_ENDIANNESS_M            0x00008000
#define AM_REG_SYSCTRL_AIRCR_ENDIANNESS(n)           (((uint32_t)(n) << 15) & 0x00008000)

// Priority grouping, indicates the binary point position.
#define AM_REG_SYSCTRL_AIRCR_PRIGROUP_S              8
#define AM_REG_SYSCTRL_AIRCR_PRIGROUP_M              0x00000700
#define AM_REG_SYSCTRL_AIRCR_PRIGROUP(n)             (((uint32_t)(n) << 8) & 0x00000700)

// Writing a 1 to this bit reqests a local reset.
#define AM_REG_SYSCTRL_AIRCR_SYSRESETREQ_S           2
#define AM_REG_SYSCTRL_AIRCR_SYSRESETREQ_M           0x00000004
#define AM_REG_SYSCTRL_AIRCR_SYSRESETREQ(n)          (((uint32_t)(n) << 2) & 0x00000004)

// Writing a 1 to this bit clears all active state information for fixed and
// configurable exceptions.
#define AM_REG_SYSCTRL_AIRCR_VECTCLRACTIVE_S         1
#define AM_REG_SYSCTRL_AIRCR_VECTCLRACTIVE_M         0x00000002
#define AM_REG_SYSCTRL_AIRCR_VECTCLRACTIVE(n)        (((uint32_t)(n) << 1) & 0x00000002)

// Writing a 1 to this bit causes a local system reset.
#define AM_REG_SYSCTRL_AIRCR_VECTRESET_S             0
#define AM_REG_SYSCTRL_AIRCR_VECTRESET_M             0x00000001
#define AM_REG_SYSCTRL_AIRCR_VECTRESET(n)            (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_SCR - System Control Register.
//
//*****************************************************************************
// Determines whether a pending interrupt is a wakeup event.
#define AM_REG_SYSCTRL_SCR_SEVONPEND_S               4
#define AM_REG_SYSCTRL_SCR_SEVONPEND_M               0x00000010
#define AM_REG_SYSCTRL_SCR_SEVONPEND(n)              (((uint32_t)(n) << 4) & 0x00000010)

// Determines whether the sleep mode should be regular or deep sleep
#define AM_REG_SYSCTRL_SCR_SLEEPDEEP_S               2
#define AM_REG_SYSCTRL_SCR_SLEEPDEEP_M               0x00000004
#define AM_REG_SYSCTRL_SCR_SLEEPDEEP(n)              (((uint32_t)(n) << 2) & 0x00000004)

// Determines whether the processor shoudl automatically sleep when an ISR
// returns to the base-level.
#define AM_REG_SYSCTRL_SCR_SLEEPONEXIT_S             1
#define AM_REG_SYSCTRL_SCR_SLEEPONEXIT_M             0x00000002
#define AM_REG_SYSCTRL_SCR_SLEEPONEXIT(n)            (((uint32_t)(n) << 1) & 0x00000002)

//*****************************************************************************
//
// SYSCTRL_CCR - Configuration and Control Register.
//
//*****************************************************************************
// Set to force 8-byte alignment for the stack pointer.
#define AM_REG_SYSCTRL_CCR_STKALIGN_S                9
#define AM_REG_SYSCTRL_CCR_STKALIGN_M                0x00000200
#define AM_REG_SYSCTRL_CCR_STKALIGN(n)               (((uint32_t)(n) << 9) & 0x00000200)

// Set to ignore precise data access faults during hard fault handlers.
#define AM_REG_SYSCTRL_CCR_BFHFNMIGN_S               8
#define AM_REG_SYSCTRL_CCR_BFHFNMIGN_M               0x00000100
#define AM_REG_SYSCTRL_CCR_BFHFNMIGN(n)              (((uint32_t)(n) << 8) & 0x00000100)

// Set to enable trapping on divide-by-zero.
#define AM_REG_SYSCTRL_CCR_DIV0TRP_S                 4
#define AM_REG_SYSCTRL_CCR_DIV0TRP_M                 0x00000010
#define AM_REG_SYSCTRL_CCR_DIV0TRP(n)                (((uint32_t)(n) << 4) & 0x00000010)

// Set to enable trapping of unaligned word or halfword accesses.
#define AM_REG_SYSCTRL_CCR_UNALIGNTRP_S              3
#define AM_REG_SYSCTRL_CCR_UNALIGNTRP_M              0x00000008
#define AM_REG_SYSCTRL_CCR_UNALIGNTRP(n)             (((uint32_t)(n) << 3) & 0x00000008)

// Set to allow unpriveleged software to access the STIR
#define AM_REG_SYSCTRL_CCR_USERSETMPEND_S            1
#define AM_REG_SYSCTRL_CCR_USERSETMPEND_M            0x00000002
#define AM_REG_SYSCTRL_CCR_USERSETMPEND(n)           (((uint32_t)(n) << 1) & 0x00000002)

// Set to enable the processor to enter Thread mode at an execution priority
// other than base level.
#define AM_REG_SYSCTRL_CCR_NONBASETHRDENA_S          0
#define AM_REG_SYSCTRL_CCR_NONBASETHRDENA_M          0x00000001
#define AM_REG_SYSCTRL_CCR_NONBASETHRDENA(n)         (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_SHPR1 - System Handler Priority Register 1.
//
//*****************************************************************************
// Reserved for priority of system handler 7.
#define AM_REG_SYSCTRL_SHPR1_PRI_7_S                 24
#define AM_REG_SYSCTRL_SHPR1_PRI_7_M                 0xFF000000
#define AM_REG_SYSCTRL_SHPR1_PRI_7(n)                (((uint32_t)(n) << 24) & 0xFF000000)

// Priority of system handler 6, UsageFault.
#define AM_REG_SYSCTRL_SHPR1_PRI_6_S                 16
#define AM_REG_SYSCTRL_SHPR1_PRI_6_M                 0x00FF0000
#define AM_REG_SYSCTRL_SHPR1_PRI_6(n)                (((uint32_t)(n) << 16) & 0x00FF0000)

// Priority of system handler 5, BusFault.
#define AM_REG_SYSCTRL_SHPR1_PRI_5_S                 8
#define AM_REG_SYSCTRL_SHPR1_PRI_5_M                 0x0000FF00
#define AM_REG_SYSCTRL_SHPR1_PRI_5(n)                (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority of system handler 4, MemManage.
#define AM_REG_SYSCTRL_SHPR1_PRI_4_S                 0
#define AM_REG_SYSCTRL_SHPR1_PRI_4_M                 0x000000FF
#define AM_REG_SYSCTRL_SHPR1_PRI_4(n)                (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// SYSCTRL_SHPR2 - System Handler Priority Register 2.
//
//*****************************************************************************
// Priority of system handler 11, SVCall.
#define AM_REG_SYSCTRL_SHPR2_PRI_11_S                24
#define AM_REG_SYSCTRL_SHPR2_PRI_11_M                0xFF000000
#define AM_REG_SYSCTRL_SHPR2_PRI_11(n)               (((uint32_t)(n) << 24) & 0xFF000000)

// Reserved for priority of system handler 10.
#define AM_REG_SYSCTRL_SHPR2_PRI_10_S                16
#define AM_REG_SYSCTRL_SHPR2_PRI_10_M                0x00FF0000
#define AM_REG_SYSCTRL_SHPR2_PRI_10(n)               (((uint32_t)(n) << 16) & 0x00FF0000)

// Reserved for priority of system handler 9.
#define AM_REG_SYSCTRL_SHPR2_PRI_9_S                 8
#define AM_REG_SYSCTRL_SHPR2_PRI_9_M                 0x0000FF00
#define AM_REG_SYSCTRL_SHPR2_PRI_9(n)                (((uint32_t)(n) << 8) & 0x0000FF00)

// Reserved for priority of system handler 8.
#define AM_REG_SYSCTRL_SHPR2_PRI_8_S                 0
#define AM_REG_SYSCTRL_SHPR2_PRI_8_M                 0x000000FF
#define AM_REG_SYSCTRL_SHPR2_PRI_8(n)                (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// SYSCTRL_SHPR3 - System Handler Priority Register 3.
//
//*****************************************************************************
// Priority of system handler 15, SysTick.
#define AM_REG_SYSCTRL_SHPR3_PRI_15_S                24
#define AM_REG_SYSCTRL_SHPR3_PRI_15_M                0xFF000000
#define AM_REG_SYSCTRL_SHPR3_PRI_15(n)               (((uint32_t)(n) << 24) & 0xFF000000)

// Priority of system handler 14, PendSV.
#define AM_REG_SYSCTRL_SHPR3_PRI_14_S                16
#define AM_REG_SYSCTRL_SHPR3_PRI_14_M                0x00FF0000
#define AM_REG_SYSCTRL_SHPR3_PRI_14(n)               (((uint32_t)(n) << 16) & 0x00FF0000)

// Reserved for priority of system handler 13.
#define AM_REG_SYSCTRL_SHPR3_PRI_13_S                8
#define AM_REG_SYSCTRL_SHPR3_PRI_13_M                0x0000FF00
#define AM_REG_SYSCTRL_SHPR3_PRI_13(n)               (((uint32_t)(n) << 8) & 0x0000FF00)

// Priority of system handler 12, DebugMonitor.
#define AM_REG_SYSCTRL_SHPR3_PRI_12_S                0
#define AM_REG_SYSCTRL_SHPR3_PRI_12_M                0x000000FF
#define AM_REG_SYSCTRL_SHPR3_PRI_12(n)               (((uint32_t)(n) << 0) & 0x000000FF)

//*****************************************************************************
//
// SYSCTRL_SHCSR - System Handler Control and State Register.
//
//*****************************************************************************
// Set to enable UsageFault.
#define AM_REG_SYSCTRL_SHCSR_USAGEFAULTENA_S         18
#define AM_REG_SYSCTRL_SHCSR_USAGEFAULTENA_M         0x00040000
#define AM_REG_SYSCTRL_SHCSR_USAGEFAULTENA(n)        (((uint32_t)(n) << 18) & 0x00040000)

// Set to enable BusFault.
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTENA_S           17
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTENA_M           0x00020000
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTENA(n)          (((uint32_t)(n) << 17) & 0x00020000)

// Set to enable MemManageFault.
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTENA_S           16
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTENA_M           0x00010000
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTENA(n)          (((uint32_t)(n) << 16) & 0x00010000)

// Set to pend the SVCall exception.
#define AM_REG_SYSCTRL_SHCSR_SVCALLPENDED_S          15
#define AM_REG_SYSCTRL_SHCSR_SVCALLPENDED_M          0x00008000
#define AM_REG_SYSCTRL_SHCSR_SVCALLPENDED(n)         (((uint32_t)(n) << 15) & 0x00008000)

// Set to pend the BusFault exception.
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTPENDED_S        14
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTPENDED_M        0x00004000
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTPENDED(n)       (((uint32_t)(n) << 14) & 0x00004000)

// Set to pend the MemManageFault exception.
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTPENDED_S        13
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTPENDED_M        0x00002000
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTPENDED(n)       (((uint32_t)(n) << 13) & 0x00002000)

// Set to pend the UsageFault exception.
#define AM_REG_SYSCTRL_SHCSR_USGFAULTPENDED_S        12
#define AM_REG_SYSCTRL_SHCSR_USGFAULTPENDED_M        0x00001000
#define AM_REG_SYSCTRL_SHCSR_USGFAULTPENDED(n)       (((uint32_t)(n) << 12) & 0x00001000)

// Set when SysTick is active.
#define AM_REG_SYSCTRL_SHCSR_SYSTICKACT_S            11
#define AM_REG_SYSCTRL_SHCSR_SYSTICKACT_M            0x00000800
#define AM_REG_SYSCTRL_SHCSR_SYSTICKACT(n)           (((uint32_t)(n) << 11) & 0x00000800)

// Set when PendSV is active.
#define AM_REG_SYSCTRL_SHCSR_PENDSVACT_S             10
#define AM_REG_SYSCTRL_SHCSR_PENDSVACT_M             0x00000400
#define AM_REG_SYSCTRL_SHCSR_PENDSVACT(n)            (((uint32_t)(n) << 10) & 0x00000400)

// Set when Monitor is active.
#define AM_REG_SYSCTRL_SHCSR_MONITORACT_S            8
#define AM_REG_SYSCTRL_SHCSR_MONITORACT_M            0x00000100
#define AM_REG_SYSCTRL_SHCSR_MONITORACT(n)           (((uint32_t)(n) << 8) & 0x00000100)

// Set when SVCall is active.
#define AM_REG_SYSCTRL_SHCSR_SVCALLACT_S             7
#define AM_REG_SYSCTRL_SHCSR_SVCALLACT_M             0x00000080
#define AM_REG_SYSCTRL_SHCSR_SVCALLACT(n)            (((uint32_t)(n) << 7) & 0x00000080)

// Set when UsageFault is active.
#define AM_REG_SYSCTRL_SHCSR_USGFAULTACT_S           3
#define AM_REG_SYSCTRL_SHCSR_USGFAULTACT_M           0x00000008
#define AM_REG_SYSCTRL_SHCSR_USGFAULTACT(n)          (((uint32_t)(n) << 3) & 0x00000008)

// Set when BusFault is active.
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTACT_S           1
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTACT_M           0x00000002
#define AM_REG_SYSCTRL_SHCSR_BUSFAULTACT(n)          (((uint32_t)(n) << 1) & 0x00000002)

// Set when MemManageFault is active.
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTACT_S           0
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTACT_M           0x00000001
#define AM_REG_SYSCTRL_SHCSR_MEMFAULTACT(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_CFSR - Configurable Fault Status Register.
//
//*****************************************************************************
// Divide by zero error has occurred.
#define AM_REG_SYSCTRL_CFSR_DIVBYZERO_S              25
#define AM_REG_SYSCTRL_CFSR_DIVBYZERO_M              0x02000000
#define AM_REG_SYSCTRL_CFSR_DIVBYZERO(n)             (((uint32_t)(n) << 25) & 0x02000000)

// Unaligned access error has occurred.
#define AM_REG_SYSCTRL_CFSR_UNALIGNED_S              24
#define AM_REG_SYSCTRL_CFSR_UNALIGNED_M              0x01000000
#define AM_REG_SYSCTRL_CFSR_UNALIGNED(n)             (((uint32_t)(n) << 24) & 0x01000000)

// A coprocessor access error has occurred.
#define AM_REG_SYSCTRL_CFSR_NOCP_S                   19
#define AM_REG_SYSCTRL_CFSR_NOCP_M                   0x00080000
#define AM_REG_SYSCTRL_CFSR_NOCP(n)                  (((uint32_t)(n) << 19) & 0x00080000)

// An integrity check error has occurred on EXC_RETURN.
#define AM_REG_SYSCTRL_CFSR_INVPC_S                  18
#define AM_REG_SYSCTRL_CFSR_INVPC_M                  0x00040000
#define AM_REG_SYSCTRL_CFSR_INVPC(n)                 (((uint32_t)(n) << 18) & 0x00040000)

// Instruction executed with invalid EPSR.T or EPSR.IT field.
#define AM_REG_SYSCTRL_CFSR_INVSTATE_S               17
#define AM_REG_SYSCTRL_CFSR_INVSTATE_M               0x00020000
#define AM_REG_SYSCTRL_CFSR_INVSTATE(n)              (((uint32_t)(n) << 17) & 0x00020000)

// Processor attempted to execute an undefined instruction.
#define AM_REG_SYSCTRL_CFSR_UNDEFINSTR_S             16
#define AM_REG_SYSCTRL_CFSR_UNDEFINSTR_M             0x00010000
#define AM_REG_SYSCTRL_CFSR_UNDEFINSTR(n)            (((uint32_t)(n) << 16) & 0x00010000)

// BFAR has valid contents.
#define AM_REG_SYSCTRL_CFSR_BFARVALID_S              15
#define AM_REG_SYSCTRL_CFSR_BFARVALID_M              0x00008000
#define AM_REG_SYSCTRL_CFSR_BFARVALID(n)             (((uint32_t)(n) << 15) & 0x00008000)

// A bus fault occurred during FP lazy state preservation.
#define AM_REG_SYSCTRL_CFSR_LSPERR_S                 13
#define AM_REG_SYSCTRL_CFSR_LSPERR_M                 0x00002000
#define AM_REG_SYSCTRL_CFSR_LSPERR(n)                (((uint32_t)(n) << 13) & 0x00002000)

// A derived bus fault has occurred on exception entry.
#define AM_REG_SYSCTRL_CFSR_STKERR_S                 12
#define AM_REG_SYSCTRL_CFSR_STKERR_M                 0x00001000
#define AM_REG_SYSCTRL_CFSR_STKERR(n)                (((uint32_t)(n) << 12) & 0x00001000)

// A derived bus fault has occurred on exception return.
#define AM_REG_SYSCTRL_CFSR_UNSTKERR_S               11
#define AM_REG_SYSCTRL_CFSR_UNSTKERR_M               0x00000800
#define AM_REG_SYSCTRL_CFSR_UNSTKERR(n)              (((uint32_t)(n) << 11) & 0x00000800)

// Imprecise data access error has occurred.
#define AM_REG_SYSCTRL_CFSR_IMPRECISERR_S            10
#define AM_REG_SYSCTRL_CFSR_IMPRECISERR_M            0x00000400
#define AM_REG_SYSCTRL_CFSR_IMPRECISERR(n)           (((uint32_t)(n) << 10) & 0x00000400)

// A precise data access has occurrred. The faulting address is in BFAR.
#define AM_REG_SYSCTRL_CFSR_PRECISERR_S              9
#define AM_REG_SYSCTRL_CFSR_PRECISERR_M              0x00000200
#define AM_REG_SYSCTRL_CFSR_PRECISERR(n)             (((uint32_t)(n) << 9) & 0x00000200)

// A bus fault on an instruction prefetch has occurred.
#define AM_REG_SYSCTRL_CFSR_IBUSERR_S                8
#define AM_REG_SYSCTRL_CFSR_IBUSERR_M                0x00000100
#define AM_REG_SYSCTRL_CFSR_IBUSERR(n)               (((uint32_t)(n) << 8) & 0x00000100)

// MMAR has valid contents.
#define AM_REG_SYSCTRL_CFSR_MMARVALID_S              7
#define AM_REG_SYSCTRL_CFSR_MMARVALID_M              0x00000080
#define AM_REG_SYSCTRL_CFSR_MMARVALID(n)             (((uint32_t)(n) << 7) & 0x00000080)

// MemManage fault occurred during FP lazy state preservation.
#define AM_REG_SYSCTRL_CFSR_MLSPERR_S                5
#define AM_REG_SYSCTRL_CFSR_MLSPERR_M                0x00000020
#define AM_REG_SYSCTRL_CFSR_MLSPERR(n)               (((uint32_t)(n) << 5) & 0x00000020)

// Derived MemManage fault occurred on exception entry.
#define AM_REG_SYSCTRL_CFSR_MSTKERR_S                4
#define AM_REG_SYSCTRL_CFSR_MSTKERR_M                0x00000010
#define AM_REG_SYSCTRL_CFSR_MSTKERR(n)               (((uint32_t)(n) << 4) & 0x00000010)

// Derived MemManage fault occurred on exception return.
#define AM_REG_SYSCTRL_CFSR_MUNSTKER_S               3
#define AM_REG_SYSCTRL_CFSR_MUNSTKER_M               0x00000008
#define AM_REG_SYSCTRL_CFSR_MUNSTKER(n)              (((uint32_t)(n) << 3) & 0x00000008)

// Data access violation. Address is in MMAR.
#define AM_REG_SYSCTRL_CFSR_DACCVIOL_S               1
#define AM_REG_SYSCTRL_CFSR_DACCVIOL_M               0x00000002
#define AM_REG_SYSCTRL_CFSR_DACCVIOL(n)              (((uint32_t)(n) << 1) & 0x00000002)

// MPU or Execute Never default memory map access violation.
#define AM_REG_SYSCTRL_CFSR_IACCVIOL_S               0
#define AM_REG_SYSCTRL_CFSR_IACCVIOL_M               0x00000001
#define AM_REG_SYSCTRL_CFSR_IACCVIOL(n)              (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_HFSR - Hard Fault Status Register.
//
//*****************************************************************************
// Debug event has occurred.
#define AM_REG_SYSCTRL_HFSR_DEBUGEVT_S               31
#define AM_REG_SYSCTRL_HFSR_DEBUGEVT_M               0x80000000
#define AM_REG_SYSCTRL_HFSR_DEBUGEVT(n)              (((uint32_t)(n) << 31) & 0x80000000)

// Processor has elevated a configurable-priority fault to a HardFault.
#define AM_REG_SYSCTRL_HFSR_FORCED_S                 30
#define AM_REG_SYSCTRL_HFSR_FORCED_M                 0x40000000
#define AM_REG_SYSCTRL_HFSR_FORCED(n)                (((uint32_t)(n) << 30) & 0x40000000)

// Vector table read fault has occurred.
#define AM_REG_SYSCTRL_HFSR_VECTTBL_S                1
#define AM_REG_SYSCTRL_HFSR_VECTTBL_M                0x00000002
#define AM_REG_SYSCTRL_HFSR_VECTTBL(n)               (((uint32_t)(n) << 1) & 0x00000002)

//*****************************************************************************
//
// SYSCTRL_MMFAR - MemManage Fault Address Register.
//
//*****************************************************************************
// Address of the memory location that caused an MMU fault.
#define AM_REG_SYSCTRL_MMFAR_ADDRESS_S               0
#define AM_REG_SYSCTRL_MMFAR_ADDRESS_M               0xFFFFFFFF
#define AM_REG_SYSCTRL_MMFAR_ADDRESS(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SYSCTRL_BFAR - Bus Fault Address Register.
//
//*****************************************************************************
// Address of the memory location that caused an Bus fault.
#define AM_REG_SYSCTRL_BFAR_ADDRESS_S                0
#define AM_REG_SYSCTRL_BFAR_ADDRESS_M                0xFFFFFFFF
#define AM_REG_SYSCTRL_BFAR_ADDRESS(n)               (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SYSCTRL_CPACR - Coprocessor Access Control Register.
//
//*****************************************************************************
// Access priveleges for the Floating point unit. Must always match CP10.
#define AM_REG_SYSCTRL_CPACR_CP11_S                  22
#define AM_REG_SYSCTRL_CPACR_CP11_M                  0x00C00000
#define AM_REG_SYSCTRL_CPACR_CP11(n)                 (((uint32_t)(n) << 22) & 0x00C00000)

// Access priveleges for the Floating point unit. Must always match CP11.
#define AM_REG_SYSCTRL_CPACR_CP10_S                  20
#define AM_REG_SYSCTRL_CPACR_CP10_M                  0x00300000
#define AM_REG_SYSCTRL_CPACR_CP10(n)                 (((uint32_t)(n) << 20) & 0x00300000)

//*****************************************************************************
//
// SYSCTRL_DEMCR - Debug Exception and Monitor Control Register
//
//*****************************************************************************
// Global enable for all DWT and ITM features.
#define AM_REG_SYSCTRL_DEMCR_TRCENA_S                24
#define AM_REG_SYSCTRL_DEMCR_TRCENA_M                0x01000000
#define AM_REG_SYSCTRL_DEMCR_TRCENA(n)               (((uint32_t)(n) << 24) & 0x01000000)

//*****************************************************************************
//
// SYSCTRL_STIR - Software Triggered Interrupt Register
//
//*****************************************************************************
// Vector number of the interrupt that should be triggered.
#define AM_REG_SYSCTRL_STIR_INTID_S                  0
#define AM_REG_SYSCTRL_STIR_INTID_M                  0xFFFFFFFF
#define AM_REG_SYSCTRL_STIR_INTID(n)                 (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SYSCTRL_FPCCR - Floating-Point Context Control Register.
//
//*****************************************************************************
// Set to enable automatic saving of FP registers on exception entry.
#define AM_REG_SYSCTRL_FPCCR_ASPEN_S                 31
#define AM_REG_SYSCTRL_FPCCR_ASPEN_M                 0x80000000
#define AM_REG_SYSCTRL_FPCCR_ASPEN(n)                (((uint32_t)(n) << 31) & 0x80000000)

// Set to enable lazy context saving of FP registers on exception entry.
#define AM_REG_SYSCTRL_FPCCR_LSPEN_S                 30
#define AM_REG_SYSCTRL_FPCCR_LSPEN_M                 0x40000000
#define AM_REG_SYSCTRL_FPCCR_LSPEN(n)                (((uint32_t)(n) << 30) & 0x40000000)

// Able to set DebugMonitor exception to pending on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_MONRDY_S                8
#define AM_REG_SYSCTRL_FPCCR_MONRDY_M                0x00000100
#define AM_REG_SYSCTRL_FPCCR_MONRDY(n)               (((uint32_t)(n) << 8) & 0x00000100)

// Able to set BusFault exception to pending on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_BFRDY_S                 6
#define AM_REG_SYSCTRL_FPCCR_BFRDY_M                 0x00000040
#define AM_REG_SYSCTRL_FPCCR_BFRDY(n)                (((uint32_t)(n) << 6) & 0x00000040)

// Able to set MemManage exception to pending on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_MMRDY_S                 5
#define AM_REG_SYSCTRL_FPCCR_MMRDY_M                 0x00000020
#define AM_REG_SYSCTRL_FPCCR_MMRDY(n)                (((uint32_t)(n) << 5) & 0x00000020)

// Able to set HardFault exception to pending on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_HFRDY_S                 4
#define AM_REG_SYSCTRL_FPCCR_HFRDY_M                 0x00000010
#define AM_REG_SYSCTRL_FPCCR_HFRDY(n)                (((uint32_t)(n) << 4) & 0x00000010)

// Running from Thread mode on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_THREAD_S                3
#define AM_REG_SYSCTRL_FPCCR_THREAD_M                0x00000008
#define AM_REG_SYSCTRL_FPCCR_THREAD(n)               (((uint32_t)(n) << 3) & 0x00000008)

// Running from unprivileged mode on last FP stack allocation.
#define AM_REG_SYSCTRL_FPCCR_USER_S                  1
#define AM_REG_SYSCTRL_FPCCR_USER_M                  0x00000002
#define AM_REG_SYSCTRL_FPCCR_USER(n)                 (((uint32_t)(n) << 1) & 0x00000002)

// Lazy state preservation is active.
#define AM_REG_SYSCTRL_FPCCR_LSPACT_S                0
#define AM_REG_SYSCTRL_FPCCR_LSPACT_M                0x00000001
#define AM_REG_SYSCTRL_FPCCR_LSPACT(n)               (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// SYSCTRL_FPCAR - Floating-Point Context Address Register.
//
//*****************************************************************************
// Address of the unpopulated floating-point register space allocated on the
// exception stack frame.
#define AM_REG_SYSCTRL_FPCAR_ADDRESS_S               0
#define AM_REG_SYSCTRL_FPCAR_ADDRESS_M               0xFFFFFFFF
#define AM_REG_SYSCTRL_FPCAR_ADDRESS(n)              (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// SYSCTRL_FPDSCR - Floating-Point Default Status Control Register.
//
//*****************************************************************************
// Default value for FPSCR.AHP.
#define AM_REG_SYSCTRL_FPDSCR_AHP_S                  26
#define AM_REG_SYSCTRL_FPDSCR_AHP_M                  0x04000000
#define AM_REG_SYSCTRL_FPDSCR_AHP(n)                 (((uint32_t)(n) << 26) & 0x04000000)

// Default value for FPSCR.DN.
#define AM_REG_SYSCTRL_FPDSCR_DN_S                   25
#define AM_REG_SYSCTRL_FPDSCR_DN_M                   0x02000000
#define AM_REG_SYSCTRL_FPDSCR_DN(n)                  (((uint32_t)(n) << 25) & 0x02000000)

// Default value for FPSCR.FZ.
#define AM_REG_SYSCTRL_FPDSCR_FZ_S                   24
#define AM_REG_SYSCTRL_FPDSCR_FZ_M                   0x01000000
#define AM_REG_SYSCTRL_FPDSCR_FZ(n)                  (((uint32_t)(n) << 24) & 0x01000000)

// Default value for FPSCR.RMode.
#define AM_REG_SYSCTRL_FPDSCR_RMODE_S                22
#define AM_REG_SYSCTRL_FPDSCR_RMODE_M                0x00C00000
#define AM_REG_SYSCTRL_FPDSCR_RMODE(n)               (((uint32_t)(n) << 22) & 0x00C00000)

#endif // AM_REG_SYSCTRL_H
