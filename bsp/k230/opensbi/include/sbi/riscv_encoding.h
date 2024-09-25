/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __RISCV_ENCODING_H__
#define __RISCV_ENCODING_H__

#include <sbi/sbi_const.h>

/* clang-format off */
#define MSTATUS_SIE			_UL(0x00000002)
#define MSTATUS_MIE			_UL(0x00000008)
#define MSTATUS_SPIE_SHIFT		5
#define MSTATUS_SPIE			(_UL(1) << MSTATUS_SPIE_SHIFT)
#define MSTATUS_UBE			_UL(0x00000040)
#define MSTATUS_MPIE			_UL(0x00000080)
#define MSTATUS_SPP_SHIFT		8
#define MSTATUS_SPP			(_UL(1) << MSTATUS_SPP_SHIFT)
#define MSTATUS_MPP_SHIFT		11
#define MSTATUS_MPP			(_UL(3) << MSTATUS_MPP_SHIFT)
#define MSTATUS_FS			_UL(0x00006000)
#define MSTATUS_XS			_UL(0x00018000)
#define MSTATUS_VS			_UL(0x01800000)
#define MSTATUS_MPRV			_UL(0x00020000)
#define MSTATUS_SUM			_UL(0x00040000)
#define MSTATUS_MXR			_UL(0x00080000)
#define MSTATUS_TVM			_UL(0x00100000)
#define MSTATUS_TW			_UL(0x00200000)
#define MSTATUS_TSR			_UL(0x00400000)
#define MSTATUS32_SD			_UL(0x80000000)
#if __riscv_xlen == 64
#define MSTATUS_UXL			_ULL(0x0000000300000000)
#define MSTATUS_SXL			_ULL(0x0000000C00000000)
#define MSTATUS_SBE			_ULL(0x0000001000000000)
#define MSTATUS_MBE			_ULL(0x0000002000000000)
#define MSTATUS_MPV			_ULL(0x0000008000000000)
#else
#define MSTATUSH_SBE			_UL(0x00000010)
#define MSTATUSH_MBE			_UL(0x00000020)
#define MSTATUSH_MPV			_UL(0x00000080)
#endif
#define MSTATUS32_SD			_UL(0x80000000)
#define MSTATUS64_SD			_ULL(0x8000000000000000)

#define SSTATUS_SIE			MSTATUS_SIE
#define SSTATUS_SPIE_SHIFT		MSTATUS_SPIE_SHIFT
#define SSTATUS_SPIE			MSTATUS_SPIE
#define SSTATUS_SPP_SHIFT		MSTATUS_SPP_SHIFT
#define SSTATUS_SPP			MSTATUS_SPP
#define SSTATUS_FS			MSTATUS_FS
#define SSTATUS_XS			MSTATUS_XS
#define SSTATUS_VS			MSTATUS_VS
#define SSTATUS_SUM			MSTATUS_SUM
#define SSTATUS_MXR			MSTATUS_MXR
#define SSTATUS32_SD			MSTATUS32_SD
#define SSTATUS64_UXL			MSTATUS_UXL
#define SSTATUS64_SD			MSTATUS64_SD

#if __riscv_xlen == 64
#define HSTATUS_VSXL			_UL(0x300000000)
#define HSTATUS_VSXL_SHIFT		32
#endif
#define HSTATUS_VTSR			_UL(0x00400000)
#define HSTATUS_VTW			_UL(0x00200000)
#define HSTATUS_VTVM			_UL(0x00100000)
#define HSTATUS_VGEIN			_UL(0x0003f000)
#define HSTATUS_VGEIN_SHIFT		12
#define HSTATUS_HU			_UL(0x00000200)
#define HSTATUS_SPVP			_UL(0x00000100)
#define HSTATUS_SPV			_UL(0x00000080)
#define HSTATUS_GVA			_UL(0x00000040)
#define HSTATUS_VSBE			_UL(0x00000020)

#define IRQ_S_SOFT			1
#define IRQ_VS_SOFT			2
#define IRQ_M_SOFT			3
#define IRQ_S_TIMER			5
#define IRQ_VS_TIMER			6
#define IRQ_M_TIMER			7
#define IRQ_S_EXT			9
#define IRQ_VS_EXT			10
#define IRQ_M_EXT			11
#define IRQ_S_GEXT			12

#define MIP_SSIP			(_UL(1) << IRQ_S_SOFT)
#define MIP_VSSIP			(_UL(1) << IRQ_VS_SOFT)
#define MIP_MSIP			(_UL(1) << IRQ_M_SOFT)
#define MIP_STIP			(_UL(1) << IRQ_S_TIMER)
#define MIP_VSTIP			(_UL(1) << IRQ_VS_TIMER)
#define MIP_MTIP			(_UL(1) << IRQ_M_TIMER)
#define MIP_SEIP			(_UL(1) << IRQ_S_EXT)
#define MIP_VSEIP			(_UL(1) << IRQ_VS_EXT)
#define MIP_MEIP			(_UL(1) << IRQ_M_EXT)
#define MIP_SGEIP			(_UL(1) << IRQ_S_GEXT)

#define SIP_SSIP			MIP_SSIP
#define SIP_STIP			MIP_STIP

#define PRV_U				_UL(0)
#define PRV_S				_UL(1)
#define PRV_M				_UL(3)

#define SATP32_MODE			_UL(0x80000000)
#define SATP32_ASID			_UL(0x7FC00000)
#define SATP32_PPN			_UL(0x003FFFFF)
#define SATP64_MODE			_ULL(0xF000000000000000)
#define SATP64_ASID			_ULL(0x0FFFF00000000000)
#define SATP64_PPN			_ULL(0x00000FFFFFFFFFFF)

#define SATP_MODE_OFF			_UL(0)
#define SATP_MODE_SV32			_UL(1)
#define SATP_MODE_SV39			_UL(8)
#define SATP_MODE_SV48			_UL(9)
#define SATP_MODE_SV57			_UL(10)
#define SATP_MODE_SV64			_UL(11)

#define HGATP_MODE_OFF			_UL(0)
#define HGATP_MODE_SV32X4		_UL(1)
#define HGATP_MODE_SV39X4		_UL(8)
#define HGATP_MODE_SV48X4		_UL(9)

#define HGATP32_MODE_SHIFT		31
#define HGATP32_VMID_SHIFT		22
#define HGATP32_VMID_MASK		_UL(0x1FC00000)
#define HGATP32_PPN			_UL(0x003FFFFF)

#define HGATP64_MODE_SHIFT		60
#define HGATP64_VMID_SHIFT		44
#define HGATP64_VMID_MASK		_ULL(0x03FFF00000000000)
#define HGATP64_PPN			_ULL(0x00000FFFFFFFFFFF)

#define PMP_R				_UL(0x01)
#define PMP_W				_UL(0x02)
#define PMP_X				_UL(0x04)
#define PMP_A				_UL(0x18)
#define PMP_A_TOR			_UL(0x08)
#define PMP_A_NA4			_UL(0x10)
#define PMP_A_NAPOT			_UL(0x18)
#define PMP_L				_UL(0x80)

#define PMP_SHIFT			2
#define PMP_COUNT			64
#if __riscv_xlen == 64
#define PMP_ADDR_MASK			((_ULL(0x1) << 54) - 1)
#else
#define PMP_ADDR_MASK			_UL(0xFFFFFFFF)
#endif

#if __riscv_xlen == 64
#define MSTATUS_SD			MSTATUS64_SD
#define SSTATUS_SD			SSTATUS64_SD
#define SATP_MODE			SATP64_MODE

#define HGATP_PPN			HGATP64_PPN
#define HGATP_VMID_SHIFT		HGATP64_VMID_SHIFT
#define HGATP_VMID_MASK			HGATP64_VMID_MASK
#define HGATP_MODE_SHIFT		HGATP64_MODE_SHIFT
#else
#define MSTATUS_SD			MSTATUS32_SD
#define SSTATUS_SD			SSTATUS32_SD
#define SATP_MODE			SATP32_MODE

#define HGATP_PPN			HGATP32_PPN
#define HGATP_VMID_SHIFT		HGATP32_VMID_SHIFT
#define HGATP_VMID_MASK			HGATP32_VMID_MASK
#define HGATP_MODE_SHIFT		HGATP32_MODE_SHIFT
#endif

/* ===== User-level CSRs ===== */

/* User Trap Setup (N-extension) */
#define CSR_USTATUS			0x000
#define CSR_UIE				0x004
#define CSR_UTVEC			0x005

/* User Trap Handling (N-extension) */
#define CSR_USCRATCH			0x040
#define CSR_UEPC			0x041
#define CSR_UCAUSE			0x042
#define CSR_UTVAL			0x043
#define CSR_UIP				0x044

/* User Floating-point CSRs */
#define CSR_FFLAGS			0x001
#define CSR_FRM				0x002
#define CSR_FCSR			0x003

/* User Counters/Timers */
#define CSR_CYCLE			0xc00
#define CSR_TIME			0xc01
#define CSR_INSTRET			0xc02
#define CSR_HPMCOUNTER3			0xc03
#define CSR_HPMCOUNTER4			0xc04
#define CSR_HPMCOUNTER5			0xc05
#define CSR_HPMCOUNTER6			0xc06
#define CSR_HPMCOUNTER7			0xc07
#define CSR_HPMCOUNTER8			0xc08
#define CSR_HPMCOUNTER9			0xc09
#define CSR_HPMCOUNTER10		0xc0a
#define CSR_HPMCOUNTER11		0xc0b
#define CSR_HPMCOUNTER12		0xc0c
#define CSR_HPMCOUNTER13		0xc0d
#define CSR_HPMCOUNTER14		0xc0e
#define CSR_HPMCOUNTER15		0xc0f
#define CSR_HPMCOUNTER16		0xc10
#define CSR_HPMCOUNTER17		0xc11
#define CSR_HPMCOUNTER18		0xc12
#define CSR_HPMCOUNTER19		0xc13
#define CSR_HPMCOUNTER20		0xc14
#define CSR_HPMCOUNTER21		0xc15
#define CSR_HPMCOUNTER22		0xc16
#define CSR_HPMCOUNTER23		0xc17
#define CSR_HPMCOUNTER24		0xc18
#define CSR_HPMCOUNTER25		0xc19
#define CSR_HPMCOUNTER26		0xc1a
#define CSR_HPMCOUNTER27		0xc1b
#define CSR_HPMCOUNTER28		0xc1c
#define CSR_HPMCOUNTER29		0xc1d
#define CSR_HPMCOUNTER30		0xc1e
#define CSR_HPMCOUNTER31		0xc1f
#define CSR_CYCLEH			0xc80
#define CSR_TIMEH			0xc81
#define CSR_INSTRETH			0xc82
#define CSR_HPMCOUNTER3H		0xc83
#define CSR_HPMCOUNTER4H		0xc84
#define CSR_HPMCOUNTER5H		0xc85
#define CSR_HPMCOUNTER6H		0xc86
#define CSR_HPMCOUNTER7H		0xc87
#define CSR_HPMCOUNTER8H		0xc88
#define CSR_HPMCOUNTER9H		0xc89
#define CSR_HPMCOUNTER10H		0xc8a
#define CSR_HPMCOUNTER11H		0xc8b
#define CSR_HPMCOUNTER12H		0xc8c
#define CSR_HPMCOUNTER13H		0xc8d
#define CSR_HPMCOUNTER14H		0xc8e
#define CSR_HPMCOUNTER15H		0xc8f
#define CSR_HPMCOUNTER16H		0xc90
#define CSR_HPMCOUNTER17H		0xc91
#define CSR_HPMCOUNTER18H		0xc92
#define CSR_HPMCOUNTER19H		0xc93
#define CSR_HPMCOUNTER20H		0xc94
#define CSR_HPMCOUNTER21H		0xc95
#define CSR_HPMCOUNTER22H		0xc96
#define CSR_HPMCOUNTER23H		0xc97
#define CSR_HPMCOUNTER24H		0xc98
#define CSR_HPMCOUNTER25H		0xc99
#define CSR_HPMCOUNTER26H		0xc9a
#define CSR_HPMCOUNTER27H		0xc9b
#define CSR_HPMCOUNTER28H		0xc9c
#define CSR_HPMCOUNTER29H		0xc9d
#define CSR_HPMCOUNTER30H		0xc9e
#define CSR_HPMCOUNTER31H		0xc9f

/* ===== Supervisor-level CSRs ===== */

/* Supervisor Trap Setup */
#define CSR_SSTATUS			0x100
#define CSR_SEDELEG			0x102
#define CSR_SIDELEG			0x103
#define CSR_SIE				0x104
#define CSR_STVEC			0x105
#define CSR_SCOUNTEREN			0x106

/* Supervisor Trap Handling */
#define CSR_SSCRATCH			0x140
#define CSR_SEPC			0x141
#define CSR_SCAUSE			0x142
#define CSR_STVAL			0x143
#define CSR_SIP				0x144

/* Supervisor Protection and Translation */
#define CSR_SATP			0x180

/* ===== Hypervisor-level CSRs ===== */

/* Hypervisor Trap Setup (H-extension) */
#define CSR_HSTATUS			0x600
#define CSR_HEDELEG			0x602
#define CSR_HIDELEG			0x603
#define CSR_HIE				0x604
#define CSR_HCOUNTEREN			0x606
#define CSR_HGEIE			0x607

/* Hypervisor Trap Handling (H-extension) */
#define CSR_HTVAL			0x643
#define CSR_HIP				0x644
#define CSR_HVIP			0x645
#define CSR_HTINST			0x64a
#define CSR_HGEIP			0xe12

/* Hypervisor Protection and Translation (H-extension) */
#define CSR_HGATP			0x680

/* Hypervisor Counter/Timer Virtualization Registers (H-extension) */
#define CSR_HTIMEDELTA			0x605
#define CSR_HTIMEDELTAH			0x615

/* Virtual Supervisor Registers (H-extension) */
#define CSR_VSSTATUS			0x200
#define CSR_VSIE			0x204
#define CSR_VSTVEC			0x205
#define CSR_VSSCRATCH			0x240
#define CSR_VSEPC			0x241
#define CSR_VSCAUSE			0x242
#define CSR_VSTVAL			0x243
#define CSR_VSIP			0x244
#define CSR_VSATP			0x280

/* ===== Machine-level CSRs ===== */

/* Machine Information Registers */
#define CSR_MVENDORID			0xf11
#define CSR_MARCHID			0xf12
#define CSR_MIMPID			0xf13
#define CSR_MHARTID			0xf14

/* Machine Trap Setup */
#define CSR_MSTATUS			0x300
#define CSR_MISA			0x301
#define CSR_MEDELEG			0x302
#define CSR_MIDELEG			0x303
#define CSR_MIE				0x304
#define CSR_MTVEC			0x305
#define CSR_MCOUNTEREN			0x306
#define CSR_MSTATUSH			0x310

/* Machine Trap Handling */
#define CSR_MSCRATCH			0x340
#define CSR_MEPC			0x341
#define CSR_MCAUSE			0x342
#define CSR_MTVAL			0x343
#define CSR_MIP				0x344
#define CSR_MTINST			0x34a
#define CSR_MTVAL2			0x34b

/* Machine Memory Protection */
#define CSR_PMPCFG0			0x3a0
#define CSR_PMPCFG1			0x3a1
#define CSR_PMPCFG2			0x3a2
#define CSR_PMPCFG3			0x3a3
#define CSR_PMPCFG4			0x3a4
#define CSR_PMPCFG5			0x3a5
#define CSR_PMPCFG6			0x3a6
#define CSR_PMPCFG7			0x3a7
#define CSR_PMPCFG8			0x3a8
#define CSR_PMPCFG9			0x3a9
#define CSR_PMPCFG10			0x3aa
#define CSR_PMPCFG11			0x3ab
#define CSR_PMPCFG12			0x3ac
#define CSR_PMPCFG13			0x3ad
#define CSR_PMPCFG14			0x3ae
#define CSR_PMPCFG15			0x3af
#define CSR_PMPADDR0			0x3b0
#define CSR_PMPADDR1			0x3b1
#define CSR_PMPADDR2			0x3b2
#define CSR_PMPADDR3			0x3b3
#define CSR_PMPADDR4			0x3b4
#define CSR_PMPADDR5			0x3b5
#define CSR_PMPADDR6			0x3b6
#define CSR_PMPADDR7			0x3b7
#define CSR_PMPADDR8			0x3b8
#define CSR_PMPADDR9			0x3b9
#define CSR_PMPADDR10			0x3ba
#define CSR_PMPADDR11			0x3bb
#define CSR_PMPADDR12			0x3bc
#define CSR_PMPADDR13			0x3bd
#define CSR_PMPADDR14			0x3be
#define CSR_PMPADDR15			0x3bf
#define CSR_PMPADDR16			0x3c0
#define CSR_PMPADDR17			0x3c1
#define CSR_PMPADDR18			0x3c2
#define CSR_PMPADDR19			0x3c3
#define CSR_PMPADDR20			0x3c4
#define CSR_PMPADDR21			0x3c5
#define CSR_PMPADDR22			0x3c6
#define CSR_PMPADDR23			0x3c7
#define CSR_PMPADDR24			0x3c8
#define CSR_PMPADDR25			0x3c9
#define CSR_PMPADDR26			0x3ca
#define CSR_PMPADDR27			0x3cb
#define CSR_PMPADDR28			0x3cc
#define CSR_PMPADDR29			0x3cd
#define CSR_PMPADDR30			0x3ce
#define CSR_PMPADDR31			0x3cf
#define CSR_PMPADDR32			0x3d0
#define CSR_PMPADDR33			0x3d1
#define CSR_PMPADDR34			0x3d2
#define CSR_PMPADDR35			0x3d3
#define CSR_PMPADDR36			0x3d4
#define CSR_PMPADDR37			0x3d5
#define CSR_PMPADDR38			0x3d6
#define CSR_PMPADDR39			0x3d7
#define CSR_PMPADDR40			0x3d8
#define CSR_PMPADDR41			0x3d9
#define CSR_PMPADDR42			0x3da
#define CSR_PMPADDR43			0x3db
#define CSR_PMPADDR44			0x3dc
#define CSR_PMPADDR45			0x3dd
#define CSR_PMPADDR46			0x3de
#define CSR_PMPADDR47			0x3df
#define CSR_PMPADDR48			0x3e0
#define CSR_PMPADDR49			0x3e1
#define CSR_PMPADDR50			0x3e2
#define CSR_PMPADDR51			0x3e3
#define CSR_PMPADDR52			0x3e4
#define CSR_PMPADDR53			0x3e5
#define CSR_PMPADDR54			0x3e6
#define CSR_PMPADDR55			0x3e7
#define CSR_PMPADDR56			0x3e8
#define CSR_PMPADDR57			0x3e9
#define CSR_PMPADDR58			0x3ea
#define CSR_PMPADDR59			0x3eb
#define CSR_PMPADDR60			0x3ec
#define CSR_PMPADDR61			0x3ed
#define CSR_PMPADDR62			0x3ee
#define CSR_PMPADDR63			0x3ef

/* Machine Counters/Timers */
#define CSR_MCYCLE			0xb00
#define CSR_MINSTRET			0xb02
#define CSR_MHPMCOUNTER3		0xb03
#define CSR_MHPMCOUNTER4		0xb04
#define CSR_MHPMCOUNTER5		0xb05
#define CSR_MHPMCOUNTER6		0xb06
#define CSR_MHPMCOUNTER7		0xb07
#define CSR_MHPMCOUNTER8		0xb08
#define CSR_MHPMCOUNTER9		0xb09
#define CSR_MHPMCOUNTER10		0xb0a
#define CSR_MHPMCOUNTER11		0xb0b
#define CSR_MHPMCOUNTER12		0xb0c
#define CSR_MHPMCOUNTER13		0xb0d
#define CSR_MHPMCOUNTER14		0xb0e
#define CSR_MHPMCOUNTER15		0xb0f
#define CSR_MHPMCOUNTER16		0xb10
#define CSR_MHPMCOUNTER17		0xb11
#define CSR_MHPMCOUNTER18		0xb12
#define CSR_MHPMCOUNTER19		0xb13
#define CSR_MHPMCOUNTER20		0xb14
#define CSR_MHPMCOUNTER21		0xb15
#define CSR_MHPMCOUNTER22		0xb16
#define CSR_MHPMCOUNTER23		0xb17
#define CSR_MHPMCOUNTER24		0xb18
#define CSR_MHPMCOUNTER25		0xb19
#define CSR_MHPMCOUNTER26		0xb1a
#define CSR_MHPMCOUNTER27		0xb1b
#define CSR_MHPMCOUNTER28		0xb1c
#define CSR_MHPMCOUNTER29		0xb1d
#define CSR_MHPMCOUNTER30		0xb1e
#define CSR_MHPMCOUNTER31		0xb1f
#define CSR_MCYCLEH			0xb80
#define CSR_MINSTRETH			0xb82
#define CSR_MHPMCOUNTER3H		0xb83
#define CSR_MHPMCOUNTER4H		0xb84
#define CSR_MHPMCOUNTER5H		0xb85
#define CSR_MHPMCOUNTER6H		0xb86
#define CSR_MHPMCOUNTER7H		0xb87
#define CSR_MHPMCOUNTER8H		0xb88
#define CSR_MHPMCOUNTER9H		0xb89
#define CSR_MHPMCOUNTER10H		0xb8a
#define CSR_MHPMCOUNTER11H		0xb8b
#define CSR_MHPMCOUNTER12H		0xb8c
#define CSR_MHPMCOUNTER13H		0xb8d
#define CSR_MHPMCOUNTER14H		0xb8e
#define CSR_MHPMCOUNTER15H		0xb8f
#define CSR_MHPMCOUNTER16H		0xb90
#define CSR_MHPMCOUNTER17H		0xb91
#define CSR_MHPMCOUNTER18H		0xb92
#define CSR_MHPMCOUNTER19H		0xb93
#define CSR_MHPMCOUNTER20H		0xb94
#define CSR_MHPMCOUNTER21H		0xb95
#define CSR_MHPMCOUNTER22H		0xb96
#define CSR_MHPMCOUNTER23H		0xb97
#define CSR_MHPMCOUNTER24H		0xb98
#define CSR_MHPMCOUNTER25H		0xb99
#define CSR_MHPMCOUNTER26H		0xb9a
#define CSR_MHPMCOUNTER27H		0xb9b
#define CSR_MHPMCOUNTER28H		0xb9c
#define CSR_MHPMCOUNTER29H		0xb9d
#define CSR_MHPMCOUNTER30H		0xb9e
#define CSR_MHPMCOUNTER31H		0xb9f

/* Machine Counter Setup */
#define CSR_MCOUNTINHIBIT		0x320
#define CSR_MHPMEVENT3			0x323
#define CSR_MHPMEVENT4			0x324
#define CSR_MHPMEVENT5			0x325
#define CSR_MHPMEVENT6			0x326
#define CSR_MHPMEVENT7			0x327
#define CSR_MHPMEVENT8			0x328
#define CSR_MHPMEVENT9			0x329
#define CSR_MHPMEVENT10			0x32a
#define CSR_MHPMEVENT11			0x32b
#define CSR_MHPMEVENT12			0x32c
#define CSR_MHPMEVENT13			0x32d
#define CSR_MHPMEVENT14			0x32e
#define CSR_MHPMEVENT15			0x32f
#define CSR_MHPMEVENT16			0x330
#define CSR_MHPMEVENT17			0x331
#define CSR_MHPMEVENT18			0x332
#define CSR_MHPMEVENT19			0x333
#define CSR_MHPMEVENT20			0x334
#define CSR_MHPMEVENT21			0x335
#define CSR_MHPMEVENT22			0x336
#define CSR_MHPMEVENT23			0x337
#define CSR_MHPMEVENT24			0x338
#define CSR_MHPMEVENT25			0x339
#define CSR_MHPMEVENT26			0x33a
#define CSR_MHPMEVENT27			0x33b
#define CSR_MHPMEVENT28			0x33c
#define CSR_MHPMEVENT29			0x33d
#define CSR_MHPMEVENT30			0x33e
#define CSR_MHPMEVENT31			0x33f

/* Debug/Trace Registers */
#define CSR_TSELECT			0x7a0
#define CSR_TDATA1			0x7a1
#define CSR_TDATA2			0x7a2
#define CSR_TDATA3			0x7a3

/* Debug Mode Registers */
#define CSR_DCSR			0x7b0
#define CSR_DPC				0x7b1
#define CSR_DSCRATCH0			0x7b2
#define CSR_DSCRATCH1			0x7b3

/* ===== Trap/Exception Causes ===== */

#define CAUSE_MISALIGNED_FETCH		0x0
#define CAUSE_FETCH_ACCESS		0x1
#define CAUSE_ILLEGAL_INSTRUCTION	0x2
#define CAUSE_BREAKPOINT		0x3
#define CAUSE_MISALIGNED_LOAD		0x4
#define CAUSE_LOAD_ACCESS		0x5
#define CAUSE_MISALIGNED_STORE		0x6
#define CAUSE_STORE_ACCESS		0x7
#define CAUSE_USER_ECALL		0x8
#define CAUSE_SUPERVISOR_ECALL		0x9
#define CAUSE_VIRTUAL_SUPERVISOR_ECALL	0xa
#define CAUSE_MACHINE_ECALL		0xb
#define CAUSE_FETCH_PAGE_FAULT		0xc
#define CAUSE_LOAD_PAGE_FAULT		0xd
#define CAUSE_STORE_PAGE_FAULT		0xf
#define CAUSE_FETCH_GUEST_PAGE_FAULT	0x14
#define CAUSE_LOAD_GUEST_PAGE_FAULT	0x15
#define CAUSE_VIRTUAL_INST_FAULT	0x16
#define CAUSE_STORE_GUEST_PAGE_FAULT	0x17

/* ===== Instruction Encodings ===== */

#define INSN_MATCH_LB			0x3
#define INSN_MASK_LB			0x707f
#define INSN_MATCH_LH			0x1003
#define INSN_MASK_LH			0x707f
#define INSN_MATCH_LW			0x2003
#define INSN_MASK_LW			0x707f
#define INSN_MATCH_LD			0x3003
#define INSN_MASK_LD			0x707f
#define INSN_MATCH_LBU			0x4003
#define INSN_MASK_LBU			0x707f
#define INSN_MATCH_LHU			0x5003
#define INSN_MASK_LHU			0x707f
#define INSN_MATCH_LWU			0x6003
#define INSN_MASK_LWU			0x707f
#define INSN_MATCH_SB			0x23
#define INSN_MASK_SB			0x707f
#define INSN_MATCH_SH			0x1023
#define INSN_MASK_SH			0x707f
#define INSN_MATCH_SW			0x2023
#define INSN_MASK_SW			0x707f
#define INSN_MATCH_SD			0x3023
#define INSN_MASK_SD			0x707f

#define INSN_MATCH_FLW			0x2007
#define INSN_MASK_FLW			0x707f
#define INSN_MATCH_FLD			0x3007
#define INSN_MASK_FLD			0x707f
#define INSN_MATCH_FLQ			0x4007
#define INSN_MASK_FLQ			0x707f
#define INSN_MATCH_FSW			0x2027
#define INSN_MASK_FSW			0x707f
#define INSN_MATCH_FSD			0x3027
#define INSN_MASK_FSD			0x707f
#define INSN_MATCH_FSQ			0x4027
#define INSN_MASK_FSQ			0x707f

#define INSN_MATCH_C_LD			0x6000
#define INSN_MASK_C_LD			0xe003
#define INSN_MATCH_C_SD			0xe000
#define INSN_MASK_C_SD			0xe003
#define INSN_MATCH_C_LW			0x4000
#define INSN_MASK_C_LW			0xe003
#define INSN_MATCH_C_SW			0xc000
#define INSN_MASK_C_SW			0xe003
#define INSN_MATCH_C_LDSP		0x6002
#define INSN_MASK_C_LDSP		0xe003
#define INSN_MATCH_C_SDSP		0xe002
#define INSN_MASK_C_SDSP		0xe003
#define INSN_MATCH_C_LWSP		0x4002
#define INSN_MASK_C_LWSP		0xe003
#define INSN_MATCH_C_SWSP		0xc002
#define INSN_MASK_C_SWSP		0xe003

#define INSN_MATCH_C_FLD		0x2000
#define INSN_MASK_C_FLD			0xe003
#define INSN_MATCH_C_FLW		0x6000
#define INSN_MASK_C_FLW			0xe003
#define INSN_MATCH_C_FSD		0xa000
#define INSN_MASK_C_FSD			0xe003
#define INSN_MATCH_C_FSW		0xe000
#define INSN_MASK_C_FSW			0xe003
#define INSN_MATCH_C_FLDSP		0x2002
#define INSN_MASK_C_FLDSP		0xe003
#define INSN_MATCH_C_FSDSP		0xa002
#define INSN_MASK_C_FSDSP		0xe003
#define INSN_MATCH_C_FLWSP		0x6002
#define INSN_MASK_C_FLWSP		0xe003
#define INSN_MATCH_C_FSWSP		0xe002
#define INSN_MASK_C_FSWSP		0xe003

#define INSN_MASK_WFI			0xffffff00
#define INSN_MATCH_WFI			0x10500000

#define INSN_16BIT_MASK			0x3
#define INSN_32BIT_MASK			0x1c

#define INSN_IS_16BIT(insn)		\
	(((insn) & INSN_16BIT_MASK) != INSN_16BIT_MASK)
#define INSN_IS_32BIT(insn)		\
	(((insn) & INSN_16BIT_MASK) == INSN_16BIT_MASK && \
	 ((insn) & INSN_32BIT_MASK) != INSN_32BIT_MASK)

#define INSN_LEN(insn)			(INSN_IS_16BIT(insn) ? 2 : 4)

#if __riscv_xlen == 64
#define LOG_REGBYTES			3
#else
#define LOG_REGBYTES			2
#endif
#define REGBYTES			(1 << LOG_REGBYTES)

#define SH_RD				7
#define SH_RS1				15
#define SH_RS2				20
#define SH_RS2C				2

#define RV_X(x, s, n)			(((x) >> (s)) & ((1 << (n)) - 1))
#define RVC_LW_IMM(x)			((RV_X(x, 6, 1) << 2) | \
					 (RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 5, 1) << 6))
#define RVC_LD_IMM(x)			((RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 5, 2) << 6))
#define RVC_LWSP_IMM(x)			((RV_X(x, 4, 3) << 2) | \
					 (RV_X(x, 12, 1) << 5) | \
					 (RV_X(x, 2, 2) << 6))
#define RVC_LDSP_IMM(x)			((RV_X(x, 5, 2) << 3) | \
					 (RV_X(x, 12, 1) << 5) | \
					 (RV_X(x, 2, 3) << 6))
#define RVC_SWSP_IMM(x)			((RV_X(x, 9, 4) << 2) | \
					 (RV_X(x, 7, 2) << 6))
#define RVC_SDSP_IMM(x)			((RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 7, 3) << 6))
#define RVC_RS1S(insn)			(8 + RV_X(insn, SH_RD, 3))
#define RVC_RS2S(insn)			(8 + RV_X(insn, SH_RS2C, 3))
#define RVC_RS2(insn)			RV_X(insn, SH_RS2C, 5)

#define SHIFT_RIGHT(x, y)		\
	((y) < 0 ? ((x) << -(y)) : ((x) >> (y)))

#define REG_MASK			\
	((1 << (5 + LOG_REGBYTES)) - (1 << LOG_REGBYTES))

#define REG_OFFSET(insn, pos)		\
	(SHIFT_RIGHT((insn), (pos) - LOG_REGBYTES) & REG_MASK)

#define REG_PTR(insn, pos, regs)	\
	(ulong *)((ulong)(regs) + REG_OFFSET(insn, pos))

#define GET_RM(insn)			(((insn) >> 12) & 7)

#define GET_RS1(insn, regs)		(*REG_PTR(insn, SH_RS1, regs))
#define GET_RS2(insn, regs)		(*REG_PTR(insn, SH_RS2, regs))
#define GET_RS1S(insn, regs)		(*REG_PTR(RVC_RS1S(insn), 0, regs))
#define GET_RS2S(insn, regs)		(*REG_PTR(RVC_RS2S(insn), 0, regs))
#define GET_RS2C(insn, regs)		(*REG_PTR(insn, SH_RS2C, regs))
#define GET_SP(regs)			(*REG_PTR(2, 0, regs))
#define SET_RD(insn, regs, val)		(*REG_PTR(insn, SH_RD, regs) = (val))
#define IMM_I(insn)			((s32)(insn) >> 20)
#define IMM_S(insn)			(((s32)(insn) >> 25 << 5) | \
					 (s32)(((insn) >> 7) & 0x1f))
#define MASK_FUNCT3			0x7000

/* clang-format on */

#endif
