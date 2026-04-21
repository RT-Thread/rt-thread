/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CSI_RV_ENCODING_H__
#define __CSI_RV_ENCODING_H__

/* ===== User-level CSRs ===== */

/* User Trap Setup (N-extension) */
#define CSR_USTATUS         0x000
#define CSR_UIE             0x004
#define CSR_UTVEC           0x005

/* User Trap Handling (N-extension) */
#define CSR_USCRATCH        0x040
#define CSR_UEPC            0x041
#define CSR_UCAUSE          0x042
#define CSR_UTVAL           0x043
#define CSR_UIP             0x044

/* User Floating-point CSRs */
#define CSR_FFLAGS          0x001
#define CSR_FRM             0x002
#define CSR_FCSR            0x003

/* User Vector CSRs */
#define CSR_VSTART          0x008
#define CSR_VXSAT           0x009
#define CSR_VXRM            0x00A
#define CSR_VCSR            0x00F
#define CSR_VL              0xC20
#define CSR_VTYPE           0xC21
#define CSR_VLENB           0xC22

/* User Counters/Timers */
#define CSR_CYCLE           0xc00
#define CSR_TIME            0xc01
#define CSR_INSTRET         0xc02
#define CSR_HPMCOUNTER3     0xc03
#define CSR_HPMCOUNTER4     0xc04
#define CSR_HPMCOUNTER5     0xc05
#define CSR_HPMCOUNTER6     0xc06
#define CSR_HPMCOUNTER7     0xc07
#define CSR_HPMCOUNTER8     0xc08
#define CSR_HPMCOUNTER9     0xc09
#define CSR_HPMCOUNTER10    0xc0a
#define CSR_HPMCOUNTER11    0xc0b
#define CSR_HPMCOUNTER12    0xc0c
#define CSR_HPMCOUNTER13    0xc0d
#define CSR_HPMCOUNTER14    0xc0e
#define CSR_HPMCOUNTER15    0xc0f
#define CSR_HPMCOUNTER16    0xc10
#define CSR_HPMCOUNTER17    0xc11
#define CSR_HPMCOUNTER18    0xc12
#define CSR_HPMCOUNTER19    0xc13
#define CSR_HPMCOUNTER20    0xc14
#define CSR_HPMCOUNTER21    0xc15
#define CSR_HPMCOUNTER22    0xc16
#define CSR_HPMCOUNTER23    0xc17
#define CSR_HPMCOUNTER24    0xc18
#define CSR_HPMCOUNTER25    0xc19
#define CSR_HPMCOUNTER26    0xc1a
#define CSR_HPMCOUNTER27    0xc1b
#define CSR_HPMCOUNTER28    0xc1c
#define CSR_HPMCOUNTER29    0xc1d
#define CSR_HPMCOUNTER30    0xc1e
#define CSR_HPMCOUNTER31    0xc1f
#define CSR_CYCLEH          0xc80
#define CSR_TIMEH           0xc81
#define CSR_INSTRETH        0xc82
#define CSR_HPMCOUNTER3H    0xc83
#define CSR_HPMCOUNTER4H    0xc84
#define CSR_HPMCOUNTER5H    0xc85
#define CSR_HPMCOUNTER6H    0xc86
#define CSR_HPMCOUNTER7H    0xc87
#define CSR_HPMCOUNTER8H    0xc88
#define CSR_HPMCOUNTER9H    0xc89
#define CSR_HPMCOUNTER10H   0xc8a
#define CSR_HPMCOUNTER11H   0xc8b
#define CSR_HPMCOUNTER12H   0xc8c
#define CSR_HPMCOUNTER13H   0xc8d
#define CSR_HPMCOUNTER14H   0xc8e
#define CSR_HPMCOUNTER15H   0xc8f
#define CSR_HPMCOUNTER16H   0xc90
#define CSR_HPMCOUNTER17H   0xc91
#define CSR_HPMCOUNTER18H   0xc92
#define CSR_HPMCOUNTER19H   0xc93
#define CSR_HPMCOUNTER20H   0xc94
#define CSR_HPMCOUNTER21H   0xc95
#define CSR_HPMCOUNTER22H   0xc96
#define CSR_HPMCOUNTER23H   0xc97
#define CSR_HPMCOUNTER24H   0xc98
#define CSR_HPMCOUNTER25H   0xc99
#define CSR_HPMCOUNTER26H   0xc9a
#define CSR_HPMCOUNTER27H   0xc9b
#define CSR_HPMCOUNTER28H   0xc9c
#define CSR_HPMCOUNTER29H   0xc9d
#define CSR_HPMCOUNTER30H   0xc9e
#define CSR_HPMCOUNTER31H   0xc9f

/* ===== Supervisor-level CSRs ===== */

/* Supervisor Trap Setup */
#define CSR_SSTATUS         0x100
#define CSR_SIE             0x104
#define CSR_STVEC           0x105
#define CSR_SCOUNTEREN      0x106

/* Supervisor Counter Overflow CSR */
#define CSR_SCOUNTOVF       0xda0

/* Supervisor Configuration */
#define CSR_SENVCFG         0x10a

/* Supervisor Trap Handling */
#define CSR_SSCRATCH        0x140
#define CSR_SEPC            0x141
#define CSR_SCAUSE          0x142
#define CSR_STVAL           0x143
#define CSR_SIP             0x144

/* Supervisor CLIC CSRs */
#define CSR_STVT            0x107
#define CSR_SNXTI           0x145
#define CSR_SINTSTATUS      0xDB1
#define CSR_SINTTHRESH      0x147
#define CSR_SSCRATCHCSW     0x148
#define CSR_SSCRATCHCSWL    0x149

/* Sstc extension */
#define CSR_STIMECMP        0x14D
#define CSR_STIMECMPH       0x15D

/* Supervisor Protection and Translation */
#define CSR_SATP            0x180

/* Supervisor Debug/Trace */
#define CSR_SCONTEXT        0x5a8

/* Supervisor-Level Window to Indirectly Accessed Registers (AIA) */
#define CSR_SISELECT        0x150
#define CSR_SIREG           0x151
#define CSR_SIREG2          0x152
#define CSR_SIREG3          0x153
#define CSR_SIREG4          0x155
#define CSR_SIREG5          0x156
#define CSR_SIREG6          0x157

/* Supervisor-Level Interrupts (AIA) */
#define CSR_STOPEI          0x15c
#define CSR_STOPI           0xdb0

/* Supervisor-Level High-Half CSRs (AIA) */
#define CSR_SIEH            0x114
#define CSR_SIPH            0x154

/* Supervisor stateen CSRs */
#define CSR_SSTATEEN0       0x10C
#define CSR_SSTATEEN1       0x10D
#define CSR_SSTATEEN2       0x10E
#define CSR_SSTATEEN3       0x10F

/* ===== Hypervisor-level CSRs ===== */

/* Hypervisor Trap Setup (H-extension) */
#define CSR_HSTATUS         0x600
#define CSR_HEDELEG         0x602
#define CSR_HIDELEG         0x603
#define CSR_HIE             0x604
#define CSR_HCOUNTEREN      0x606
#define CSR_HGEIE           0x607

/* Hypervisor Configuration */
#define CSR_HENVCFG         0x60a
#define CSR_HENVCFGH        0x61a

/* Hypervisor Trap Handling (H-extension) */
#define CSR_HTVAL           0x643
#define CSR_HIP             0x644
#define CSR_HVIP            0x645
#define CSR_HTINST          0x64a
#define CSR_HGEIP           0xe12

/* Hypervisor Protection and Translation (H-extension) */
#define CSR_HGATP           0x680

/* Hypervisor Counter/Timer Virtualization Registers (H-extension) */
#define CSR_HTIMEDELTA      0x605
#define CSR_HTIMEDELTAH     0x615

/* Virtual Supervisor Registers (H-extension) */
#define CSR_VSSTATUS        0x200
#define CSR_VSIE            0x204
#define CSR_VSTVEC          0x205
#define CSR_VSSCRATCH       0x240
#define CSR_VSEPC           0x241
#define CSR_VSCAUSE         0x242
#define CSR_VSTVAL          0x243
#define CSR_VSIP            0x244
#define CSR_VSATP           0x280

/* Virtual Interrupts and Interrupt Priorities (H-extension with AIA) */
#define CSR_HVIEN           0x608
#define CSR_HVICTL          0x609
#define CSR_HVIPRIO1        0x646
#define CSR_HVIPRIO2        0x647

/* VS-Level Window to Indirectly Accessed Registers (H-extension with AIA) */
#define CSR_VSISELECT       0x250
#define CSR_VSIREG          0x251

/* VS-Level Interrupts (H-extension with AIA) */
#define CSR_VSTOPEI         0x25c
#define CSR_VSTOPI          0xeb0

/* Hypervisor and VS-Level High-Half CSRs (H-extension with AIA) */
#define CSR_HIDELEGH        0x613
#define CSR_HVIENH          0x618
#define CSR_HVIPH           0x655
#define CSR_HVIPRIO1H       0x656
#define CSR_HVIPRIO2H       0x657
#define CSR_VSIEH           0x214
#define CSR_VSIPH           0x254

/* Hypervisor stateen CSRs */
#define CSR_HSTATEEN0       0x60C
#define CSR_HSTATEEN0H      0x61C
#define CSR_HSTATEEN1       0x60D
#define CSR_HSTATEEN1H      0x61D
#define CSR_HSTATEEN2       0x60E
#define CSR_HSTATEEN2H      0x61E
#define CSR_HSTATEEN3       0x60F
#define CSR_HSTATEEN3H      0x61F

/* ===== Machine-level CSRs ===== */

/* Machine Information Registers */
#define CSR_MVENDORID       0xf11
#define CSR_MARCHID         0xf12
#define CSR_MIMPID          0xf13
#define CSR_MHARTID         0xf14
#define CSR_MCONFIGPTR      0xf15

/* Machine Trap Setup */
#define CSR_MSTATUS         0x300
#define CSR_MISA            0x301
#define CSR_MEDELEG         0x302
#define CSR_MIDELEG         0x303
#define CSR_MIE             0x304
#define CSR_MTVEC           0x305
#define CSR_MCOUNTEREN      0x306
#define CSR_MSTATUSH        0x310

/* Machine Configuration */
#define CSR_MENVCFG         0x30a
#define CSR_MENVCFGH        0x31a

/* Machine Trap Handling */
#define CSR_MSCRATCH        0x340
#define CSR_MEPC            0x341
#define CSR_MCAUSE          0x342
#define CSR_MTVAL           0x343
#define CSR_MIP             0x344
#define CSR_MTINST          0x34a
#define CSR_MTVAL2          0x34b

/* Machine CLIC CSRs */
#define CSR_MTVT            0x307
#define CSR_MNXTI           0x345
#define CSR_MINTSTATUS      0xFB1
#define CSR_MINTTHRESH      0x347
#define CSR_MSCRATCHCSW     0x348
#define CSR_MSCRATCHCSWL    0x349

/* Machine Memory Protection */
#define CSR_PMPCFG0         0x3a0
#define CSR_PMPCFG1         0x3a1
#define CSR_PMPCFG2         0x3a2
#define CSR_PMPCFG3         0x3a3
#define CSR_PMPCFG4         0x3a4
#define CSR_PMPCFG5         0x3a5
#define CSR_PMPCFG6         0x3a6
#define CSR_PMPCFG7         0x3a7
#define CSR_PMPCFG8         0x3a8
#define CSR_PMPCFG9         0x3a9
#define CSR_PMPCFG10        0x3aa
#define CSR_PMPCFG11        0x3ab
#define CSR_PMPCFG12        0x3ac
#define CSR_PMPCFG13        0x3ad
#define CSR_PMPCFG14        0x3ae
#define CSR_PMPCFG15        0x3af
#define CSR_PMPADDR0        0x3b0
#define CSR_PMPADDR1        0x3b1
#define CSR_PMPADDR2        0x3b2
#define CSR_PMPADDR3        0x3b3
#define CSR_PMPADDR4        0x3b4
#define CSR_PMPADDR5        0x3b5
#define CSR_PMPADDR6        0x3b6
#define CSR_PMPADDR7        0x3b7
#define CSR_PMPADDR8        0x3b8
#define CSR_PMPADDR9        0x3b9
#define CSR_PMPADDR10       0x3ba
#define CSR_PMPADDR11       0x3bb
#define CSR_PMPADDR12       0x3bc
#define CSR_PMPADDR13       0x3bd
#define CSR_PMPADDR14       0x3be
#define CSR_PMPADDR15       0x3bf
#define CSR_PMPADDR16       0x3c0
#define CSR_PMPADDR17       0x3c1
#define CSR_PMPADDR18       0x3c2
#define CSR_PMPADDR19       0x3c3
#define CSR_PMPADDR20       0x3c4
#define CSR_PMPADDR21       0x3c5
#define CSR_PMPADDR22       0x3c6
#define CSR_PMPADDR23       0x3c7
#define CSR_PMPADDR24       0x3c8
#define CSR_PMPADDR25       0x3c9
#define CSR_PMPADDR26       0x3ca
#define CSR_PMPADDR27       0x3cb
#define CSR_PMPADDR28       0x3cc
#define CSR_PMPADDR29       0x3cd
#define CSR_PMPADDR30       0x3ce
#define CSR_PMPADDR31       0x3cf
#define CSR_PMPADDR32       0x3d0
#define CSR_PMPADDR33       0x3d1
#define CSR_PMPADDR34       0x3d2
#define CSR_PMPADDR35       0x3d3
#define CSR_PMPADDR36       0x3d4
#define CSR_PMPADDR37       0x3d5
#define CSR_PMPADDR38       0x3d6
#define CSR_PMPADDR39       0x3d7
#define CSR_PMPADDR40       0x3d8
#define CSR_PMPADDR41       0x3d9
#define CSR_PMPADDR42       0x3da
#define CSR_PMPADDR43       0x3db
#define CSR_PMPADDR44       0x3dc
#define CSR_PMPADDR45       0x3dd
#define CSR_PMPADDR46       0x3de
#define CSR_PMPADDR47       0x3df
#define CSR_PMPADDR48       0x3e0
#define CSR_PMPADDR49       0x3e1
#define CSR_PMPADDR50       0x3e2
#define CSR_PMPADDR51       0x3e3
#define CSR_PMPADDR52       0x3e4
#define CSR_PMPADDR53       0x3e5
#define CSR_PMPADDR54       0x3e6
#define CSR_PMPADDR55       0x3e7
#define CSR_PMPADDR56       0x3e8
#define CSR_PMPADDR57       0x3e9
#define CSR_PMPADDR58       0x3ea
#define CSR_PMPADDR59       0x3eb
#define CSR_PMPADDR60       0x3ec
#define CSR_PMPADDR61       0x3ed
#define CSR_PMPADDR62       0x3ee
#define CSR_PMPADDR63       0x3ef

/* Machine Counters/Timers */
#define CSR_MCYCLE          0xb00
#define CSR_MINSTRET        0xb02
#define CSR_MHPMCOUNTER3    0xb03
#define CSR_MHPMCOUNTER4    0xb04
#define CSR_MHPMCOUNTER5    0xb05
#define CSR_MHPMCOUNTER6    0xb06
#define CSR_MHPMCOUNTER7    0xb07
#define CSR_MHPMCOUNTER8    0xb08
#define CSR_MHPMCOUNTER9    0xb09
#define CSR_MHPMCOUNTER10   0xb0a
#define CSR_MHPMCOUNTER11   0xb0b
#define CSR_MHPMCOUNTER12   0xb0c
#define CSR_MHPMCOUNTER13   0xb0d
#define CSR_MHPMCOUNTER14   0xb0e
#define CSR_MHPMCOUNTER15   0xb0f
#define CSR_MHPMCOUNTER16   0xb10
#define CSR_MHPMCOUNTER17   0xb11
#define CSR_MHPMCOUNTER18   0xb12
#define CSR_MHPMCOUNTER19   0xb13
#define CSR_MHPMCOUNTER20   0xb14
#define CSR_MHPMCOUNTER21   0xb15
#define CSR_MHPMCOUNTER22   0xb16
#define CSR_MHPMCOUNTER23   0xb17
#define CSR_MHPMCOUNTER24   0xb18
#define CSR_MHPMCOUNTER25   0xb19
#define CSR_MHPMCOUNTER26   0xb1a
#define CSR_MHPMCOUNTER27   0xb1b
#define CSR_MHPMCOUNTER28   0xb1c
#define CSR_MHPMCOUNTER29   0xb1d
#define CSR_MHPMCOUNTER30   0xb1e
#define CSR_MHPMCOUNTER31   0xb1f
#define CSR_MCYCLEH         0xb80
#define CSR_MINSTRETH       0xb82
#define CSR_MHPMCOUNTER3H   0xb83
#define CSR_MHPMCOUNTER4H   0xb84
#define CSR_MHPMCOUNTER5H   0xb85
#define CSR_MHPMCOUNTER6H   0xb86
#define CSR_MHPMCOUNTER7H   0xb87
#define CSR_MHPMCOUNTER8H   0xb88
#define CSR_MHPMCOUNTER9H   0xb89
#define CSR_MHPMCOUNTER10H  0xb8a
#define CSR_MHPMCOUNTER11H  0xb8b
#define CSR_MHPMCOUNTER12H  0xb8c
#define CSR_MHPMCOUNTER13H  0xb8d
#define CSR_MHPMCOUNTER14H  0xb8e
#define CSR_MHPMCOUNTER15H  0xb8f
#define CSR_MHPMCOUNTER16H  0xb90
#define CSR_MHPMCOUNTER17H  0xb91
#define CSR_MHPMCOUNTER18H  0xb92
#define CSR_MHPMCOUNTER19H  0xb93
#define CSR_MHPMCOUNTER20H  0xb94
#define CSR_MHPMCOUNTER21H  0xb95
#define CSR_MHPMCOUNTER22H  0xb96
#define CSR_MHPMCOUNTER23H  0xb97
#define CSR_MHPMCOUNTER24H  0xb98
#define CSR_MHPMCOUNTER25H  0xb99
#define CSR_MHPMCOUNTER26H  0xb9a
#define CSR_MHPMCOUNTER27H  0xb9b
#define CSR_MHPMCOUNTER28H  0xb9c
#define CSR_MHPMCOUNTER29H  0xb9d
#define CSR_MHPMCOUNTER30H  0xb9e
#define CSR_MHPMCOUNTER31H  0xb9f

/* Machine Counter Setup */
#define CSR_MCOUNTINHIBIT   0x320
#define CSR_MCYCLECFG       0x321
#define CSR_MINSTRETCFG     0x322
#define CSR_MHPMEVENT3      0x323
#define CSR_MHPMEVENT4      0x324
#define CSR_MHPMEVENT5      0x325
#define CSR_MHPMEVENT6      0x326
#define CSR_MHPMEVENT7      0x327
#define CSR_MHPMEVENT8      0x328
#define CSR_MHPMEVENT9      0x329
#define CSR_MHPMEVENT10     0x32a
#define CSR_MHPMEVENT11     0x32b
#define CSR_MHPMEVENT12     0x32c
#define CSR_MHPMEVENT13     0x32d
#define CSR_MHPMEVENT14     0x32e
#define CSR_MHPMEVENT15     0x32f
#define CSR_MHPMEVENT16     0x330
#define CSR_MHPMEVENT17     0x331
#define CSR_MHPMEVENT18     0x332
#define CSR_MHPMEVENT19     0x333
#define CSR_MHPMEVENT20     0x334
#define CSR_MHPMEVENT21     0x335
#define CSR_MHPMEVENT22     0x336
#define CSR_MHPMEVENT23     0x337
#define CSR_MHPMEVENT24     0x338
#define CSR_MHPMEVENT25     0x339
#define CSR_MHPMEVENT26     0x33a
#define CSR_MHPMEVENT27     0x33b
#define CSR_MHPMEVENT28     0x33c
#define CSR_MHPMEVENT29     0x33d
#define CSR_MHPMEVENT30     0x33e
#define CSR_MHPMEVENT31     0x33f

/* For RV32 */
#define CSR_MCYCLECFGH      0x721
#define CSR_MINSTRETCFGH    0x722
#define CSR_MHPMEVENT3H     0x723
#define CSR_MHPMEVENT4H     0x724
#define CSR_MHPMEVENT5H     0x725
#define CSR_MHPMEVENT6H     0x726
#define CSR_MHPMEVENT7H     0x727
#define CSR_MHPMEVENT8H     0x728
#define CSR_MHPMEVENT9H     0x729
#define CSR_MHPMEVENT10H    0x72a
#define CSR_MHPMEVENT11H    0x72b
#define CSR_MHPMEVENT12H    0x72c
#define CSR_MHPMEVENT13H    0x72d
#define CSR_MHPMEVENT14H    0x72e
#define CSR_MHPMEVENT15H    0x72f
#define CSR_MHPMEVENT16H    0x730
#define CSR_MHPMEVENT17H    0x731
#define CSR_MHPMEVENT18H    0x732
#define CSR_MHPMEVENT19H    0x733
#define CSR_MHPMEVENT20H    0x734
#define CSR_MHPMEVENT21H    0x735
#define CSR_MHPMEVENT22H    0x736
#define CSR_MHPMEVENT23H    0x737
#define CSR_MHPMEVENT24H    0x738
#define CSR_MHPMEVENT25H    0x739
#define CSR_MHPMEVENT26H    0x73a
#define CSR_MHPMEVENT27H    0x73b
#define CSR_MHPMEVENT28H    0x73c
#define CSR_MHPMEVENT29H    0x73d
#define CSR_MHPMEVENT30H    0x73e
#define CSR_MHPMEVENT31H    0x73f

/* Machine Security Configuration CSR (mseccfg) */
#define CSR_MSECCFG         0x747
#define CSR_MSECCFGH        0x757

/* Debug/Trace Registers */
#define CSR_TSELECT         0x7a0
#define CSR_TDATA1          0x7a1
#define CSR_TDATA2          0x7a2
#define CSR_TDATA3          0x7a3
#define CSR_TINFO           0x7a4
#define CSR_TCONTROL        0x7a5
#define CSR_MCONTEXT        0x7a8

/* Debug Mode Registers */
#define CSR_DCSR            0x7b0
#define CSR_DPC             0x7b1
#define CSR_DSCRATCH0       0x7b2
#define CSR_DSCRATCH1       0x7b3

/* Machine-Level Window to Indirectly Accessed Registers */
#define CSR_MISELECT        0x350
#define CSR_MIREG           0x351
#define CSR_MIREG2          0x352
#define CSR_MIREG3          0x353
#define CSR_MIREG4          0x355
#define CSR_MIREG5          0x356
#define CSR_MIREG6          0x357

/* Machine-Level Interrupts (AIA) */
#define CSR_MTOPEI          0x35c
#define CSR_MTOPI           0xfb0

/* Virtual Interrupts for Supervisor Level (AIA) */
#define CSR_MVIEN           0x308
#define CSR_MVIP            0x309

/* Smstateen extension registers */
/* Machine stateen CSRs */
#define CSR_MSTATEEN0       0x30C
#define CSR_MSTATEEN0H      0x31C
#define CSR_MSTATEEN1       0x30D
#define CSR_MSTATEEN1H      0x31D
#define CSR_MSTATEEN2       0x30E
#define CSR_MSTATEEN2H      0x31E
#define CSR_MSTATEEN3       0x30F
#define CSR_MSTATEEN3H      0x31F

/* Machine-Level High-Half CSRs (AIA) */
#define CSR_MIDELEGH        0x313
#define CSR_MIEH            0x314
#define CSR_MVIENH          0x318
#define CSR_MVIPH           0x319
#define CSR_MIPH            0x354

/* XuanTie custom */
/* Machine-Level XuanTie custom CSRs */
#define CSR_MXSTATUS        0x7c0
#define CSR_MHCR            0x7c1
#define CSR_MCOR            0x7c2
#define CSR_MCCR2           0x7c3
#define CSR_MCER2           0x7c4
#define CSR_MHINT           0x7c5
#define CSR_MRMR            0x7c6
#define CSR_MRVBR           0x7c7
#define CSR_MCER            0x7c8
#define CSR_MCOUNTERWEN     0x7c9
#define CSR_MHINT2          0x7cc
#define CSR_MHINT3          0x7cd
#define CSR_MHINT4          0x7ce
#define CSR_MHPMEVENT0      0x7e0
#define CSR_MHPMEVENT2      0x7e1
#define CSR_MHPMCR          0x7f0
#define CSR_MHPMSR          0x7f1
#define CSR_MHPMER          0x7f2
#define CSR_MSMPR           0x7f3
#define CSR_MZONEID         0x7f5
#define CSR_MLLCPID         0x7f6
#define CSR_MLLWP           0x7f7

#define CSR_MCINS           0x7d2
#define CSR_MCINDEX         0x7d3
#define CSR_MCDATA0         0x7d4
#define CSR_MCDATA1         0x7d5
#define CSR_MEICR           0x7d6
#define CSR_MEICR2          0x7d7
#define CSR_MBEADDR         0x7d8

#define CSR_MCPUID          0xfc0
#define CSR_MAPBADDR        0xfc1

#define CSR_MHALTCAUSE      0xfe0
#define CSR_MDBGINFO        0xfe1
#define CSR_MPCFIFO         0xfe2
#define CSR_MDBGINFO2       0xfe3

#define CSR_MNASTATUS       0x8000000000000210

#define CSR_MRPLCNTLST      0xbd8
#define CSR_MCACHELOCK      0xbd9
#define CSR_MCACHERPLPRI0   0xbda
#define CSR_MCACHERPLPRI1   0xbdb
#define CSR_MCACHERPLPRI2   0xbdc
#define CSR_MCACHERPLPRI3   0xbdd
#define CSR_MCACHERPLPRI4   0xbde
#define CSR_MCACHERPLPRI5   0xbdf

/* Supervisor-Level XuanTie custom CSRs */
#define CSR_SXSTATUS        0x5c0
#define CSR_SHCR            0x5c1
#define CSR_SCER2           0x5c2
#define CSR_SCER            0x5c3
#define CSR_SHINT           0x5c6
#define CSR_SHINT2          0x5c7
#define CSR_SHPMINHIBIT     0x5c8
#define CSR_SHPMCR          0x5c9
#define CSR_SHPMSR          0x5ca
#define CSR_SHPMER          0x5cb
#define CSR_SL2PID          0x5cc
#define CSR_SL2WP           0x5cd
#define CSR_SBEADDR         0x5d0
#define CSR_SSBEPA          0x5d1
#define CSR_SSBEPA2         0x5d2
#define CSR_SCYCLE          0x5e0
#define CSR_SINSTRET        0x5e2
#define CSR_SHPMCOUNTER3    0x5e3
#define CSR_SHPMCOUNTER4    0x5e4
#define CSR_SHPMCOUNTER5    0x5e5
#define CSR_SHPMCOUNTER6    0x5e6
#define CSR_SHPMCOUNTER7    0x5e7
#define CSR_SHPMCOUNTER8    0x5e8
#define CSR_SHPMCOUNTER9    0x5e9
#define CSR_SHPMCOUNTER10   0x5ea
#define CSR_SHPMCOUNTER11   0x5eb
#define CSR_SHPMCOUNTER12   0x5ec
#define CSR_SHPMCOUNTER13   0x5ed
#define CSR_SHPMCOUNTER14   0x5ee
#define CSR_SHPMCOUNTER15   0x5ef
#define CSR_SHPMCOUNTER16   0x5f0
#define CSR_SHPMCOUNTER17   0x5f1
#define CSR_SHPMCOUNTER18   0x5f2
#define CSR_SHPMCOUNTER19   0x5f3
#define CSR_SHPMCOUNTER20   0x5f4
#define CSR_SHPMCOUNTER21   0x5f5
#define CSR_SHPMCOUNTER22   0x5f6
#define CSR_SHPMCOUNTER23   0x5f7
#define CSR_SHPMCOUNTER24   0x5f8
#define CSR_SHPMCOUNTER25   0x5f9
#define CSR_SHPMCOUNTER26   0x5fa
#define CSR_SHPMCOUNTER27   0x5fb
#define CSR_SHPMCOUNTER28   0x5fc
#define CSR_SHPMCOUNTER29   0x5fd
#define CSR_SHPMCOUNTER30   0x5fe
#define CSR_SHPMCOUNTER31   0x5ff
#define CSR_SCYCLEH         0x9e0
#define CSR_SINSTRETH       0x9e2
#define CSR_SHPMCOUNTER3H   0x9e3
#define CSR_SHPMCOUNTER4H   0x9e4
#define CSR_SHPMCOUNTER5H   0x9e5
#define CSR_SHPMCOUNTER6H   0x9e6
#define CSR_SHPMCOUNTER7H   0x9e7
#define CSR_SHPMCOUNTER8H   0x9e8
#define CSR_SHPMCOUNTER9H   0x9e9
#define CSR_SHPMCOUNTER10H  0x9ea
#define CSR_SHPMCOUNTER11H  0x9eb
#define CSR_SHPMCOUNTER12H  0x9ec
#define CSR_SHPMCOUNTER13H  0x9ed
#define CSR_SHPMCOUNTER14H  0x9ee
#define CSR_SHPMCOUNTER15H  0x9ef
#define CSR_SHPMCOUNTER16H  0x9f0
#define CSR_SHPMCOUNTER17H  0x9f1
#define CSR_SHPMCOUNTER18H  0x9f2
#define CSR_SHPMCOUNTER19H  0x9f3
#define CSR_SHPMCOUNTER20H  0x9f4
#define CSR_SHPMCOUNTER21H  0x9f5
#define CSR_SHPMCOUNTER22H  0x9f6
#define CSR_SHPMCOUNTER23H  0x9f7
#define CSR_SHPMCOUNTER24H  0x9f8
#define CSR_SHPMCOUNTER25H  0x9f9
#define CSR_SHPMCOUNTER26H  0x9fa
#define CSR_SHPMCOUNTER27H  0x9fb
#define CSR_SHPMCOUNTER28H  0x9fc
#define CSR_SHPMCOUNTER29H  0x9fd
#define CSR_SHPMCOUNTER30H  0x9fe
#define CSR_SHPMCOUNTER31H  0x9ff

#define CSR_SRPLCNTLST      0x9d8
#define CSR_SCACHELOCK      0x9d9
#define CSR_SCACHERPLPRI0   0x9da
#define CSR_SCACHERPLPRI1   0x9db
#define CSR_SCACHERPLPRI2   0x9dc
#define CSR_SCACHERPLPRI3   0x9dd
#define CSR_SCACHERPLPRI4   0x9de
#define CSR_SCACHERPLPRI5   0x9df

/* User-Level XuanTie custom CSRs */
#define CSR_TWCOUNTER       0x804
#define CSR_FXCR            0x800
#define CSR_XMRSTART        0x801
#define CSR_XMCSR           0x802
#define CSR_XMSIZE          0x803
#define CSR_XMLENB          0xcc0
#define CSR_XRLENB          0xcc1
#define CSR_XMISA           0xcc2

#define CSR_URPLCNTLST      0x8e8
#define CSR_UCACHELOCK      0x8e9
#define CSR_UCACHERPLPRI0   0x8ea
#define CSR_UCACHERPLPRI1   0x8eb
#define CSR_UCACHERPLPRI2   0x8ec
#define CSR_UCACHERPLPRI3   0x8ed
#define CSR_UCACHERPLPRI4   0x8ee
#define CSR_UCACHERPLPRI5   0x8ef

////////////////////////////////////////////////////////////////////////
/* MMIO registers For xSelect */
#ifndef CONFIG_SPMP_MMIO_BASE
#define SPMP_MMIO_BASE 0x80000E00UL
#else
#define SPMP_MMIO_BASE CONFIG_SPMP_MMIO_BASE
#endif
/*
miselect#0 mireg → spmpaddr[0], mireg2 → spmpcfg[0]
miselect#1 mireg → spmpaddr[1], mireg2 → spmpcfg[1]
… …
miselect#63 mireg → spmpaddr[63], mireg2 → spmpcfg[63]
*/

/*
siselect#0: sireg → spmpaddr[0], sireg2 → spmpcfg[0]
siselect#1: sireg → spmpaddr[1], sireg2 → spmpcfg[1]
… …
siselect#63: sireg → spmpaddr[63], sireg2 → spmpcfg[63]
*/

#define SPMP_MMIO_SPMPADDR0_SPMPCFG0    (SPMP_MMIO_BASE + 0x00)
#define SPMP_MMIO_SPMPADDR1_SPMPCFG1    (SPMP_MMIO_BASE + 0x01)
#define SPMP_MMIO_SPMPADDR2_SPMPCFG2    (SPMP_MMIO_BASE + 0x02)
#define SPMP_MMIO_SPMPADDR3_SPMPCFG3    (SPMP_MMIO_BASE + 0x03)
#define SPMP_MMIO_SPMPADDR4_SPMPCFG4    (SPMP_MMIO_BASE + 0x04)
#define SPMP_MMIO_SPMPADDR5_SPMPCFG5    (SPMP_MMIO_BASE + 0x05)
#define SPMP_MMIO_SPMPADDR6_SPMPCFG6    (SPMP_MMIO_BASE + 0x06)
#define SPMP_MMIO_SPMPADDR7_SPMPCFG7    (SPMP_MMIO_BASE + 0x07)
#define SPMP_MMIO_SPMPADDR8_SPMPCFG8    (SPMP_MMIO_BASE + 0x08)
#define SPMP_MMIO_SPMPADDR9_SPMPCFG9    (SPMP_MMIO_BASE + 0x09)
#define SPMP_MMIO_SPMPADDR10_SPMPCFG10  (SPMP_MMIO_BASE + 0x0A)
#define SPMP_MMIO_SPMPADDR11_SPMPCFG11  (SPMP_MMIO_BASE + 0x0B)
#define SPMP_MMIO_SPMPADDR12_SPMPCFG12  (SPMP_MMIO_BASE + 0x0C)
#define SPMP_MMIO_SPMPADDR13_SPMPCFG13  (SPMP_MMIO_BASE + 0x0D)
#define SPMP_MMIO_SPMPADDR14_SPMPCFG14  (SPMP_MMIO_BASE + 0x0E)
#define SPMP_MMIO_SPMPADDR15_SPMPCFG15  (SPMP_MMIO_BASE + 0x0F)
#define SPMP_MMIO_SPMPADDR16_SPMPCFG16  (SPMP_MMIO_BASE + 0x10)
#define SPMP_MMIO_SPMPADDR17_SPMPCFG17  (SPMP_MMIO_BASE + 0x11)
#define SPMP_MMIO_SPMPADDR18_SPMPCFG18  (SPMP_MMIO_BASE + 0x12)
#define SPMP_MMIO_SPMPADDR19_SPMPCFG19  (SPMP_MMIO_BASE + 0x13)
#define SPMP_MMIO_SPMPADDR20_SPMPCFG20  (SPMP_MMIO_BASE + 0x14)
#define SPMP_MMIO_SPMPADDR21_SPMPCFG21  (SPMP_MMIO_BASE + 0x15)
#define SPMP_MMIO_SPMPADDR22_SPMPCFG22  (SPMP_MMIO_BASE + 0x16)
#define SPMP_MMIO_SPMPADDR23_SPMPCFG23  (SPMP_MMIO_BASE + 0x17)
#define SPMP_MMIO_SPMPADDR24_SPMPCFG24  (SPMP_MMIO_BASE + 0x18)
#define SPMP_MMIO_SPMPADDR25_SPMPCFG25  (SPMP_MMIO_BASE + 0x19)
#define SPMP_MMIO_SPMPADDR26_SPMPCFG26  (SPMP_MMIO_BASE + 0x1A)
#define SPMP_MMIO_SPMPADDR27_SPMPCFG27  (SPMP_MMIO_BASE + 0x1B)
#define SPMP_MMIO_SPMPADDR28_SPMPCFG28  (SPMP_MMIO_BASE + 0x1C)
#define SPMP_MMIO_SPMPADDR29_SPMPCFG29  (SPMP_MMIO_BASE + 0x1D)
#define SPMP_MMIO_SPMPADDR30_SPMPCFG30  (SPMP_MMIO_BASE + 0x1E)
#define SPMP_MMIO_SPMPADDR31_SPMPCFG31  (SPMP_MMIO_BASE + 0x1F)
#define SPMP_MMIO_SPMPADDR32_SPMPCFG32  (SPMP_MMIO_BASE + 0x20)
#define SPMP_MMIO_SPMPADDR33_SPMPCFG33  (SPMP_MMIO_BASE + 0x21)
#define SPMP_MMIO_SPMPADDR34_SPMPCFG34  (SPMP_MMIO_BASE + 0x22)
#define SPMP_MMIO_SPMPADDR35_SPMPCFG35  (SPMP_MMIO_BASE + 0x23)
#define SPMP_MMIO_SPMPADDR36_SPMPCFG36  (SPMP_MMIO_BASE + 0x24)
#define SPMP_MMIO_SPMPADDR37_SPMPCFG37  (SPMP_MMIO_BASE + 0x25)
#define SPMP_MMIO_SPMPADDR38_SPMPCFG38  (SPMP_MMIO_BASE + 0x26)
#define SPMP_MMIO_SPMPADDR39_SPMPCFG39  (SPMP_MMIO_BASE + 0x27)
#define SPMP_MMIO_SPMPADDR40_SPMPCFG40  (SPMP_MMIO_BASE + 0x28)
#define SPMP_MMIO_SPMPADDR41_SPMPCFG41  (SPMP_MMIO_BASE + 0x29)
#define SPMP_MMIO_SPMPADDR42_SPMPCFG42  (SPMP_MMIO_BASE + 0x2A)
#define SPMP_MMIO_SPMPADDR43_SPMPCFG43  (SPMP_MMIO_BASE + 0x2B)
#define SPMP_MMIO_SPMPADDR44_SPMPCFG44  (SPMP_MMIO_BASE + 0x2C)
#define SPMP_MMIO_SPMPADDR45_SPMPCFG45  (SPMP_MMIO_BASE + 0x2D)
#define SPMP_MMIO_SPMPADDR46_SPMPCFG46  (SPMP_MMIO_BASE + 0x2E)
#define SPMP_MMIO_SPMPADDR47_SPMPCFG47  (SPMP_MMIO_BASE + 0x2F)
#define SPMP_MMIO_SPMPADDR48_SPMPCFG48  (SPMP_MMIO_BASE + 0x30)
#define SPMP_MMIO_SPMPADDR49_SPMPCFG49  (SPMP_MMIO_BASE + 0x31)
#define SPMP_MMIO_SPMPADDR50_SPMPCFG50  (SPMP_MMIO_BASE + 0x32)
#define SPMP_MMIO_SPMPADDR51_SPMPCFG51  (SPMP_MMIO_BASE + 0x33)
#define SPMP_MMIO_SPMPADDR52_SPMPCFG52  (SPMP_MMIO_BASE + 0x34)
#define SPMP_MMIO_SPMPADDR53_SPMPCFG53  (SPMP_MMIO_BASE + 0x35)
#define SPMP_MMIO_SPMPADDR54_SPMPCFG54  (SPMP_MMIO_BASE + 0x36)
#define SPMP_MMIO_SPMPADDR55_SPMPCFG55  (SPMP_MMIO_BASE + 0x37)
#define SPMP_MMIO_SPMPADDR56_SPMPCFG56  (SPMP_MMIO_BASE + 0x38)
#define SPMP_MMIO_SPMPADDR57_SPMPCFG57  (SPMP_MMIO_BASE + 0x39)
#define SPMP_MMIO_SPMPADDR58_SPMPCFG58  (SPMP_MMIO_BASE + 0x3A)
#define SPMP_MMIO_SPMPADDR59_SPMPCFG59  (SPMP_MMIO_BASE + 0x3B)
#define SPMP_MMIO_SPMPADDR60_SPMPCFG60  (SPMP_MMIO_BASE + 0x3C)
#define SPMP_MMIO_SPMPADDR61_SPMPCFG61  (SPMP_MMIO_BASE + 0x3D)
#define SPMP_MMIO_SPMPADDR62_SPMPCFG62  (SPMP_MMIO_BASE + 0x3E)
#define SPMP_MMIO_SPMPADDR63_SPMPCFG63  (SPMP_MMIO_BASE + 0x3F)
#define SPMP_MMIO_SSPMP_SWITCH_SWITCHH  (SPMP_MMIO_BASE + 0x40)
#define SPMP_MMIO_MPMPDELEG             (SPMP_MMIO_BASE + 0x41)

#define PMP_MMIO_PMPSWITCH0             (0x800000c8)
#define PMP_MMIO_PMPSWITCH1             (0x800000c9)

#endif /* __CSI_RV_ENCODING_H__ */
