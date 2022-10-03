/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2021-06-29     Wayne        the first version
 */

/* GICv2 - Distributor Registers */
#define GICD_CTLR        0x0000
#define GICD_TYPER       0x0004
#define GICD_IIDR        0x0008
#define GICD_STATUSR     0x0010
#define GICD_SETSPI_NSR  0x0040
#define GICD_CLRSPI_NSR  0x0048
#define GICD_SETSPI_SR   0x0050
#define GICD_CLRSPI_SR   0x0058
#define GICD_SEIR        0x0068
#define GICD_IGROUPRn    0x0080
#define GICD_ISENABLERn  0x0100
#define GICD_ICENABLERn  0x0180
#define GICD_ISPENDRn    0x0200
#define GICD_ICPENDRn    0x0280
#define GICD_ISACTIVERn  0x0300
#define GICD_ICACTIVERn  0x0380
#define GICD_IPRIORITYRn 0x0400
#define GICD_ITARGETSRn  0x0800
#define GICD_ICFGR       0x0c00
#define GICD_IGROUPMODRn 0x0d00
#define GICD_NSACRn      0x0e00
#define GICD_SGIR        0x0f00
#define GICD_CPENDSGIRn  0x0f10
#define GICD_SPENDSGIRn  0x0f20
#define GICD_IROUTERn    0x6000

/* GICv2 - CPU Interface Memory Mapped Registers */
#define GICC_CTLR        0x0000
#define GICC_PMR         0x0004
#define GICC_BPR         0x0008
#define GICC_IAR         0x000C
#define GICC_EOIR        0x0010
#define GICC_RPR         0x0014
#define GICC_HPPIR       0x0018
#define GICC_ABPR        0x001c
#define GICC_AIAR        0x0020
#define GICC_AEOIR       0x0024
#define GICC_AHPPIR      0x0028
#define GICC_APRn        0x00d0
#define GICC_NSAPRn      0x00e0
#define GICC_IIDR        0x00fc
#define GICC_DIR         0x1000

.section ".text.entrypoint"
.global _start

_start:
    /* Give execution address for secondary CPU */
    adr     x20, .
    mov     sp, x20

    /*=============================================================*/
    /*      Enable the SMP bit.                                    */
    /*=============================================================*/
    mrs x0, S3_1_C15_C2_1
    orr x0, x0, #(1<<6)
    msr S3_1_C15_C2_1, x0

    /*=============================================================*/
    /*      Read CPU id                                            */
    /*      Primary core(id=0): Help Secondary core leaving.       */
    /*      Secondary core(id>0): Notice 'Ready' to Primary core.  */
    /*=============================================================*/
    /* MPIDR_EL1: Multi-Processor Affinity Register */
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, .L__cpu_0

.L__current_cpu_idle:
    /*=============================================================*/
    /*      Secondary CPU notification                             */
    /*=============================================================*/
    wfe                     /* Wait for Primary CPU's notification */

    mov     x0, #0x48              /* if (*(0x40460048)==0)        */
    movk    x0, #0x4046, LSL #16   /*     goto L__current_cpu_idle */
    ldr     x1, [x0]               /* else                         */
    cmp     x1, #0                 /*     *(0x4046004C)=_start     */
    b.eq    .L__current_cpu_idle   /*     goto L__cpus_trans_state */
    add     x0, x0, #4
    str     w1, [x0]

    b       .L__cpus_trans_state

.L__cpu_0:

    // *(0x4046004C) = 0
    mov     x0, #0x4C
    movk    x0, #0x4046, LSL #16
    mov     x1, xzr
    str     w1, [x0]

    mov     x10, #0x1000          /* 4096 times looping */
.L__cpu_0_loop:
    sub     x10, x10, #0x1
    cmp     x10, #0
    b.eq    .L__cpus_trans_state
    /*=============================================================*/
    /*      Help CPU-1 to leave IBR.                               */
    /*=============================================================*/
    mov     x0, #0x48            /* *(0x40460048) = _start    */
    movk    x0, #0x4046, LSL #16
    mov     x1, x20
    str     w1, [x0]

    sev                          /* Wakeup Secondary CPU      */

    add     x0, x0, #4           /* if(*(0x4046004C)!=_start) */
    ldr     w2, [x0]             /*     goto L__cpu_0_loop    */
    cmp     x1, x2
    bne     .L__cpu_0_loop

.L__cpus_trans_state:

    /*=============================================================*/
    /*      Initialize Gtimer. Set frequency to 12MHz.             */
    /*=============================================================*/
    mov     x0, #0x1B00
    movk    x0, #0xB7, LSL #16
    msr     CNTFRQ_EL0, x0

    /*=============================================================*/
    /*      Enable GICv2.                                          */
    /*      Assign all IRQs to secure group.                       */
    /*=============================================================*/
    /* Route to secure Group */
    mov     x0, #0x1000
    movk    x0, #0x5080, LSL #16
    mov     w9, #0x3
    str     w9, [x0, GICD_CTLR]
    ldr     w9, [x0, GICD_TYPER]
    and     w10, w9, #0x1f
    cbz     w10, 1f
    add     x11, x0, GICD_IGROUPRn
    mov     w9, #0
    str     w9, [x11], #0x04
0:  str     w9, [x11], #0x04
    sub     w10,  w10, #0x1
    cbnz    w10,  0b

    mov     x1, #0x2000
    movk    x1, #0x5080, LSL #16
    mov     w0,  #3
    str     w0,  [x1]

    mov     w0, #1 << 7
    str     w0, [x1, #4]
1:
    mov     x0, #0x1000
    movk    x0, #0x5080, LSL #16
    mov     x1, #0x2000
    movk    x1, #0x5080, LSL #16

    mov     w9, #0
    str     w9, [x0, GICD_IGROUPRn]
    mov     w9, #0x1
    str     w9, [x0, GICD_ISENABLERn]

    mov     w9, #0x1e7
    str     w9, [x1, GICC_CTLR]

    mov     w9, #0x1 << 7
    str     w9, [x1, GICC_PMR]

    /*=============================================================*/
    /*      Enable FP/SIMD at EL1                                  */
    /*=============================================================*/
    mov	x0, #(3 << 20)
    msr	cpacr_el1, x0               /* Enable FP/SIMD at EL1 */

    /*=============================================================*/
    /*      Initialize sctlr_el1                                   */
    /*=============================================================*/
    mov x0, xzr
    orr x0, x0, #(1 << 29)          /* Enable LSMAOE at EL1 */
    orr x0, x0, #(1 << 28)          /* Enable nTLSMD at EL1 */
    orr x0, x0, #(1 << 23)          /* Enable SPAN at EL1 */
    orr x0, x0, #(1 << 22)          /* Enable EIS at EL1 */
    orr x0, x0, #(1 << 20)          /* Enable TSCXT at EL1 */
    orr x0, x0, #(1 << 11)          /* Enable EOS at EL1 */
    msr sctlr_el1, x0

    /*=============================================================*/
    /*      Initialize scr_el3                                     */
    /*=============================================================*/
    mov x0, xzr
    /* RW, Lower levels are all AArch32. */
    orr x0, x0, #(1 << 9)           /* Enable SIF */
    orr x0, x0, #(1 << 8)           /* Enable HCE */
    orr x0, x0, #(1 << 7)           /* Enable SMD */
    orr x0, x0, #(1 << 5)           /* RES1[5:4] */
    orr x0, x0, #(1 << 4)
    /* Disable FIQ routing */
    /* Disable IRQ routing */
    /* Disable NS */
    msr scr_el3, x0

    /*=============================================================*/
    /*      Initialize spsr_el3                                    */
    /*=============================================================*/
    mov x0, xzr
    mov x0, #0b00011          /* AARCH32_SVC */
    orr x0, x0, #(1 << 8)     /* Enable SError and External Abort. */
    orr x0, x0, #(1 << 7)     /* IRQ interrupt Process state mask. */
    orr x0, x0, #(1 << 6)     /* FIQ interrupt Process state mask. */
    orr x0, x0, #(1 << 4)     /* FIQ interrupt Process state mask. */
    msr spsr_el3, x0

    /*=============================================================*/
    /*      Initialize elr_el3                                     */
    /*      Jump to Secure AARCH32_SVC from EL3.                   */
    /*=============================================================*/
    adr x0, .aarch32_code     /* Exception return to aarch32_code  */
    msr elr_el3, x0
    eret

.aarch32_code:

