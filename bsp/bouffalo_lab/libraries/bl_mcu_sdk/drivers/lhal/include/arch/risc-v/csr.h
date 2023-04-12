/****************************************************************************
 * arch/risc-v/include/csr.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather, only indirectly
 * through nuttx/irq.h
 */

#ifndef __ARCH_RISCV_INCLUDE_CSR_H
#define __ARCH_RISCV_INCLUDE_CSR_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* User Trap Registers */

#define CSR_USTATUS         0x000
#define CSR_UIE             0x004
#define CSR_UTVEC           0x005

/* User Trap Handling Registers */

#define CSR_USCRATCH        0x040
#define CSR_UEPC            0x041
#define CSR_UCAUSE          0x042
#define CSR_UTVAL           0x043
#define CSR_UIP             0x044

/* User Floating-Point Registers */

#define CSR_FFLAGS          0x001
#define CSR_FRM             0x002
#define CSR_FCSR            0x003

/* User Counter/Times Registers */

#define CSR_CYCLE           0xC00
#define CSR_TIME            0xC01
#define CSR_INSTRET         0xC02
#define CSR_HPCOUNTER3      0xC03
#define CSR_HPCOUNTER4      0xC04
#define CSR_HPCOUNTER5      0xC05
#define CSR_HPCOUNTER6      0xC06
#define CSR_HPCOUNTER7      0xC07
#define CSR_HPCOUNTER8      0xC08
#define CSR_HPCOUNTER9      0xC09
#define CSR_HPCOUNTER10     0xC0A
#define CSR_HPCOUNTER11     0xC0B
#define CSR_HPCOUNTER12     0xC0C
#define CSR_HPCOUNTER13     0xC0D
#define CSR_HPCOUNTER14     0xC0E
#define CSR_HPCOUNTER15     0xC0F
#define CSR_HPCOUNTER16     0xC10
#define CSR_HPCOUNTER17     0xC11
#define CSR_HPCOUNTER18     0xC12
#define CSR_HPCOUNTER19     0xC13
#define CSR_HPCOUNTER20     0xC14
#define CSR_HPCOUNTER21     0xC15
#define CSR_HPCOUNTER22     0xC16
#define CSR_HPCOUNTER24     0xC17
#define CSR_HPCOUNTER25     0xC18
#define CSR_HPCOUNTER26     0xC19
#define CSR_HPCOUNTER27     0xC1A
#define CSR_HPCOUNTER28     0xC1B
#define CSR_HPCOUNTER29     0xC1C
#define CSR_HPCOUNTER30     0xC1D
#define CSR_HPCOUNTER31     0xC1F
#define CSR_CYCLEH          0xC80
#define CSR_TIMEH           0xC81
#define CSR_INSTRETH        0xC82
#define CSR_HPCOUNTER3H     0xC83
#define CSR_HPCOUNTER4H     0xC84
#define CSR_HPCOUNTER5H     0xC85
#define CSR_HPCOUNTER6H     0xC86
#define CSR_HPCOUNTER7H     0xC87
#define CSR_HPCOUNTER8H     0xC88
#define CSR_HPCOUNTER9H     0xC89
#define CSR_HPCOUNTER10H    0xC8A
#define CSR_HPCOUNTER11H    0xC8B
#define CSR_HPCOUNTER12H    0xC8C
#define CSR_HPCOUNTER13H    0xC8D
#define CSR_HPCOUNTER14H    0xC8E
#define CSR_HPCOUNTER15H    0xC8F
#define CSR_HPCOUNTER16H    0xC90
#define CSR_HPCOUNTER17H    0xC91
#define CSR_HPCOUNTER18H    0xC92
#define CSR_HPCOUNTER19H    0xC93
#define CSR_HPCOUNTER20H    0xC94
#define CSR_HPCOUNTER21H    0xC95
#define CSR_HPCOUNTER22H    0xC96
#define CSR_HPCOUNTER24H    0xC97
#define CSR_HPCOUNTER25H    0xC98
#define CSR_HPCOUNTER26H    0xC99
#define CSR_HPCOUNTER27H    0xC9A
#define CSR_HPCOUNTER28H    0xC9B
#define CSR_HPCOUNTER29H    0xC9C
#define CSR_HPCOUNTER30H    0xC9D
#define CSR_HPCOUNTER31H    0xC9F

/* Supervisor Trap Setup Registers */

#define CSR_SSTATUS         0x100
#define CSR_SEDELEG         0x102
#define CSR_SIDELEG         0x103
#define CSR_SIE             0x104
#define CSR_STVEC           0x105
#define CSR_SCOUNTEREN      0x106

/* Supervisor Trap Handling Registers */

#define CSR_SSCRATCH        0x140
#define CSR_SEPC            0x141
#define CSR_SCAUSE          0x142
#define CSR_STVAL           0x143
#define CSR_SIP             0x144

/* Supervisor Protection and Translation Registers */

#define CSR_SATP            0x180

/* Machine Information Registers */

#define CSR_MVENDORID       0xF11
#define CSR_MARCHID         0xF12
#define CSR_MIMPID          0xF13
#define CSR_MHARTID         0xF14

/* Machine Trap Registers */

#define CSR_MSTATUS         0x300
#define CSR_MISA            0x301
#define CSR_MEDELEG         0x302
#define CSR_MIDELEG         0x303
#define CSR_MIE             0x304
#define CSR_MTVEC           0x305
#define CSR_MCOUNTEREN      0x306

/* Machine Trap Handling */

#define CSR_MSCRATCH        0x340
#define CSR_MEPC            0x341
#define CSR_MCAUSE          0x342
#define CSR_MTVAL           0x343
#define CSR_MIP             0x344

/* Machine Protection and Translation */

#define CSR_PMPCFG0         0x3A0
#define CSR_PMPCFG1         0x3A1
#define CSR_PMPCFG2         0x3A2
#define CSR_PMPCFG3         0x3A3
#define CSR_PMPADDR0        0x3B0
#define CSR_PMPADDR1        0x3B1
#define CSR_PMPADDR2        0x3B2
#define CSR_PMPADDR3        0x3B3
#define CSR_PMPADDR4        0x3B4
#define CSR_PMPADDR5        0x3B5
#define CSR_PMPADDR6        0x3B6
#define CSR_PMPADDR7        0x3B7
#define CSR_PMPADDR8        0x3B8
#define CSR_PMPADDR9        0x3B9
#define CSR_PMPADDR10       0x3BA
#define CSR_PMPADDR11       0x3BB
#define CSR_PMPADDR12       0x3BC
#define CSR_PMPADDR13       0x3BD
#define CSR_PMPADDR14       0x3BE
#define CSR_PMPADDR15       0x3BF

/* Machine Timers and Counters */

#define CSR_MCYCLE          0xB00
#define CSR_MINSTRET        0xB02
#define CSR_MHPMCOUNTER3    0xB03
#define CSR_MHPMCOUNTER4    0xB04
#define CSR_MHPMCOUNTER5    0xB05
#define CSR_MHPMCOUNTER6    0xB06
#define CSR_MHPMCOUNTER7    0xB07
#define CSR_MHPMCOUNTER8    0xB08
#define CSR_MHPMCOUNTER9    0xB09
#define CSR_MHPMCOUNTER10   0xB0A
#define CSR_MHPMCOUNTER11   0xB0B
#define CSR_MHPMCOUNTER12   0xB0C
#define CSR_MHPMCOUNTER13   0xB0D
#define CSR_MHPMCOUNTER14   0xB0E
#define CSR_MHPMCOUNTER15   0xB0F
#define CSR_MHPMCOUNTER16   0xB10
#define CSR_MHPMCOUNTER17   0xB11
#define CSR_MHPMCOUNTER18   0xB12
#define CSR_MHPMCOUNTER19   0xB13
#define CSR_MHPMCOUNTER20   0xB14
#define CSR_MHPMCOUNTER21   0xB15
#define CSR_MHPMCOUNTER22   0xB16
#define CSR_MHPMCOUNTER23   0xB17
#define CSR_MHPMCOUNTER24   0xB18
#define CSR_MHPMCOUNTER25   0xB19
#define CSR_MHPMCOUNTER26   0xB1A
#define CSR_MHPMCOUNTER27   0xB1B
#define CSR_MHPMCOUNTER28   0xB1C
#define CSR_MHPMCOUNTER29   0xB1D
#define CSR_MHPMCOUNTER30   0xB1E
#define CSR_MHPMCOUNTER31   0xB1F
#define CSR_MCYCLEH         0xB80
#define CSR_MINSTRETH       0xB82
#define CSR_MHPMCOUNTER3H   0xB83
#define CSR_MHPMCOUNTER4H   0xB84
#define CSR_MHPMCOUNTER5H   0xB85
#define CSR_MHPMCOUNTER6H   0xB86
#define CSR_MHPMCOUNTER7H   0xB87
#define CSR_MHPMCOUNTER8H   0xB88
#define CSR_MHPMCOUNTER9H   0xB89
#define CSR_MHPMCOUNTER10H  0xB8A
#define CSR_MHPMCOUNTER11H  0xB8B
#define CSR_MHPMCOUNTER12H  0xB8C
#define CSR_MHPMCOUNTER13H  0xB8D
#define CSR_MHPMCOUNTER14H  0xB8E
#define CSR_MHPMCOUNTER15H  0xB8F
#define CSR_MHPMCOUNTER16H  0xB90
#define CSR_MHPMCOUNTER17H  0xB91
#define CSR_MHPMCOUNTER18H  0xB92
#define CSR_MHPMCOUNTER19H  0xB93
#define CSR_MHPMCOUNTER20H  0xB94
#define CSR_MHPMCOUNTER21H  0xB95
#define CSR_MHPMCOUNTER22H  0xB96
#define CSR_MHPMCOUNTER23H  0xB97
#define CSR_MHPMCOUNTER24H  0xB98
#define CSR_MHPMCOUNTER25H  0xB99
#define CSR_MHPMCOUNTER26H  0xB9A
#define CSR_MHPMCOUNTER27H  0xB9B
#define CSR_MHPMCOUNTER28H  0xB9C
#define CSR_MHPMCOUNTER29H  0xB9D
#define CSR_MHPMCOUNTER30H  0xB9E
#define CSR_MHPMCOUNTER31H  0xB9F

/* Machine Counter Setup */

#define CSR_MPHEVENT3       0x323
#define CSR_MPHEVENT4       0x324
#define CSR_MPHEVENT5       0x325
#define CSR_MPHEVENT6       0x326
#define CSR_MPHEVENT7       0x327
#define CSR_MPHEVENT8       0x328
#define CSR_MPHEVENT9       0x329
#define CSR_MPHEVENT10      0x32A
#define CSR_MPHEVENT11      0x32B
#define CSR_MPHEVENT12      0x32C
#define CSR_MPHEVENT13      0x32D
#define CSR_MPHEVENT14      0x32E
#define CSR_MPHEVENT15      0x32F
#define CSR_MPHEVENT16      0x330
#define CSR_MPHEVENT17      0x331
#define CSR_MPHEVENT18      0x332
#define CSR_MPHEVENT19      0x333
#define CSR_MPHEVENT20      0x334
#define CSR_MPHEVENT21      0x335
#define CSR_MPHEVENT22      0x336
#define CSR_MPHEVENT23      0x337
#define CSR_MPHEVENT24      0x338
#define CSR_MPHEVENT25      0x339
#define CSR_MPHEVENT26      0x33A
#define CSR_MPHEVENT27      0x33B
#define CSR_MPHEVENT28      0x33C
#define CSR_MPHEVENT29      0x33D
#define CSR_MPHEVENT30      0x33E
#define CSR_MPHEVENT31      0x33F

/* Debug/Trace Registers */

#define CSR_TSELECT         0x7A0
#define CSR_TDATA1          0x7A1
#define CSR_TDATA2          0x7A2
#define CSR_TDATA3          0x7A3

/* Debug interface CSRs */

#define CSR_DCSR            0x7B0
#define CSR_DPC             0x7B1
#define CSR_DSCRATCH        0x7B2

/* In mstatus register */
#define MSTATUS_SIE       (0x1 << 1)  /* Superior Interrupt Enable */
#define MSTATUS_MIE       (0x1 << 3)  /* Machine Interrupt Enable */
#define MSTATUS_MPIE      (0x1 << 7)  /* Machine Previous Interrupt Enable */
#define MSTATUS_MPPM      (0x3 << 11) /* Machine Previous Privilege (m-mode) */
#define MSTATUS_FS        (0x3 << 13) /* Machine Floating-point Status */
#define MSTATUS_FS_INIT   (0x1 << 13)
#define MSTATUS_FS_CLEAN  (0x2 << 13)
#define MSTATUS_FS_DIRTY  (0x3 << 13)

/* In mie (machine interrupt enable) register */

#define MIE_MSIE      (0x1 << 3)  /* Machine Software Interrupt Enable */
#define MIE_MTIE      (0x1 << 7)  /* Machine Timer Interrupt Enable */
#define MIE_MEIE      (0x1 << 11) /* Machine External Interrupt Enable */

/* In mip (machine interrupt pending) register */

#define MIP_MTIP      (0x1 << 7)

#define CSR_STR(csr) #csr

#define READ_CSR(reg) \
  ({ \
     unsigned long tmp; \
     asm volatile("csrr %0, " CSR_STR(reg) : "=r"(tmp)); \
     tmp; \
  })

#define WRITE_CSR(reg, val) \
  ({ \
     asm volatile("csrw " CSR_STR(reg) ", %0" :: "rK"(val)); \
  })

#define SET_CSR(reg, bits) \
  ({ \
     asm volatile("csrs " CSR_STR(reg) ", %0" :: "rK"(bits)); \
  })

#define CLEAR_CSR(reg, bits) \
  ({ \
     asm volatile("csrc " CSR_STR(reg) ", %0" :: "rK"(bits)); \
  })

/* In pmpcfg (PMP configuration) register */

#define PMPCFG_R        (1 << 0)  /* readable ? */
#define PMPCFG_W        (1 << 1)  /* writeable ? */
#define PMPCFG_X        (1 << 2)  /* excutable ? */
#define PMPCFG_A_OFF    (0 << 3)  /* null region (disabled) */
#define PMPCFG_A_TOR    (1 << 3)  /* top of range */
#define PMPCFG_A_NA4    (2 << 3)  /* naturally aligned four-byte region */
#define PMPCFG_A_NAPOT  (3 << 3)  /* naturally aligned power-of-two region */
#define PMPCFG_A_MASK   (3 << 3)  /* address-matching mode mask */
#define PMPCFG_L        (1 << 7)  /* locked ? */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#endif /* __ARCH_RISCV_INCLUDE_CSR_H */
