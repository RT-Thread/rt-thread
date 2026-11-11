#include "rtconfig.h"    
    .text
    .align 4
    .section ".EL2_core_exceptions_table", "ax"
    .globl  EL2_core_exceptions_table
    .type   EL2_core_exceptions_table, %function
EL2_core_exceptions_table:
    b   EL2_Reset_Handler             /* Reset Handler */
    b   EL2_Undefined_Handler         /* Undefined Handler */
    b   EL2_HVC_Handler               /* SVCall Handler */
    b   EL2_Prefetch_Handler          /* Prefetch Handler */
    b   EL2_Abort_Handler             /* Abort Handler */
    b   EL2_Trap_Handler              /* Reserved */
    b   EL2_IRQ_Handler               /* IRQ Handler */
    b   EL2_FIQ_Handler               /* FIQ Handler */

    .arm
    .align 4
    .section ".EL1_core_exceptions_table", "ax"
EL1_core_exceptions_table:
    b   EL1_Reset_Handler
    b   Undefined_Handler
    b   SVC_Handler
    b   Prefetch_Handler
    b   Abort_Handler
    b   Reserved_Handler
    b   IRQ_Handler
    b   FIQ_Handler 

/* Reset Handler */
    .text
    .align 4
    .section ".EL2_Reset_Handler", "ax"
    .globl  EL2_Reset_Handler
    .type   EL2_Reset_Handler, %function
EL2_Reset_Handler:
    mov r0, #0
    mov r1, r0
    mov r2, r0
    mov r3, r0
    mov r4, r0
    mov r5, r0
    mov r6, r0
    mov r7, r0
    mov r8, r0
    mov r9, r0
    mov r10, r0
    mov r11, r0
    mov r12, r0

#ifdef RT_USING_FPU
    mrc   p15,     #0x00, r2, c1, c0, #0x02
    orr   r2,      r2, #0xF00000
    mcr   p15,     #0x00, r2, c1, c0, #0x02

    fmrx  r2,      fpexc
    orr   r2,      r2,   #0x40000000
    fmxr  fpexc,   r2
#endif

    ldr r0, =0x23000003
    MCR p15, 0, r0, c15, c0, 0

    /*---------------TCM Initialization-------------------*/
    ldr r0, =0x0A000000        /* ATCM base address */
    ldr r1, =0x00010000        /* TCM size: 64KB */
    mov r2, #0                 /* Clear value */
tcm_init_loop:
    str r2, [r0], #4           /* Write and increment */
    subs r1, r1, #4             /* Decrement counter */
    bne tcm_init_loop           /* Continue if not zero */
    dsb                         /* Data synchronization barrier */
    isb                         /* Instruction synchronization barrier */

    b MPU_Init

MPU_Init:
    mrc p15, 4, r0, c1, c0, 0 /* Read HSCTLR */
    and r0, r0, #0xFFFFFFFE /* set HSCTLR.M bit to 0, disable EL2 MPU */
    mcr p15, 4, r0, c1, c0, 0 /* write HSCTLR */

    mrc p15, 0, r0, c1, c0, 0 /* Read SCTLR */
    and r0, r0, #0xFFFFFFFE /* set SCTLR.M bit to 0, disable EL1 MPU */
    mcr p15, 0, r0, c1, c0, 0 /* write SCTLR */

    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(0x1 << 12)    /*icache */
    orr r0, r0, #(0x1 << 2)     /*dcache */
    mcr p15, 0, r0, c1, c0, 0

disalbe_mpu_region_loop:
    mov r0, r3  /* select region */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    mrc p15, 4, r0, c6, c3, 1 /* Read From HPRLAR */
    and r0, r0, #0xFFFFFFFE
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */

    mrc p15, 0, r0, c6, c3, 1 /* Read From PRLAR */
    and r0, r0, #0xFFFFFFFE
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    add r3, r3, #1
    cmp r3, #24             /* hsm has only 16 mpu regions */
    blt disalbe_mpu_region_loop

    /* region 0 cluster0/cluster1 tcm */
    /* normal memory attribute        */
    ldr r0, =0                /* Region 0 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x08000000       /* Start address */
    orr r0, r0, #0x2          /* SH=0, AP=1, XN=0*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x0AFFFFFF      /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x3          /* AttrIndex=1, non-cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 1 mcu sram (uncacheable)---------------*/
    /* normal memory attribute */
    ldr r0, =1                /* Region 1 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x0C800000       /* Start address */
    orr r0, r0, #0x2          /* SH=0, AP=1, XN=0*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x0CAAFFFF       /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x3          /* AttrIndex=1, non-cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 2 image read-only (cacheable, executable)---------------*/
    /* 0x0CAB0000 ~ (__image_rw_start__ - 64), startup/text/rodata */
    ldr r0, =2                /* Region 2 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x0CAB0000       /* Start: FLASH_STARTUP (64-byte aligned) */
    orr r0, r0, #0x6          /* SH=0, AP=3, XN=0 */
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =__image_rw_start__ /* End address: __image_rw_start__ is 64-byte aligned */
    sub r0, r0, #0x40         /* Limit = __image_rw_start__ - 64 */
    orr r0, r0, #0x1          /* AttrIndex=0, cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

 /*---------------region 4 image read-write (cacheable, XN)----------------*/
    ldr r0, =4                /* Region 4 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =__image_rw_start__ /* __image_rw_start__ is 64-byte aligned */
    and r0, r0, #0xFFFFFFC0   /* Ensure 64-byte alignment */
    orr r0, r0, #0x12         /* SH=0, AP=1, XN=1 */
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =__image_rw_end__ /* End address: __image_rw_end__ is 64-byte aligned */
    sub r0, r0, #0x40         /* Limit = __image_rw_end__ - 64 */
    orr r0, r0, #0x1          /* AttrIndex=0, cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /* Keep __image_rw_end__ ~ OS_HEAP_START_ADDR unmapped as a guard gap. */
    
    /*---------------region 5 RTOS heap (cacheable, XN)----------------*/
    ldr r0, =5                /* Region 5 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =OS_HEAP_START_ADDR   /* OS_HEAP_START_ADDR is 64-byte aligned */
    and r0, r0, #0xFFFFFFC0       /* Ensure 64-byte alignment */
    orr r0, r0, #0x12             /* SH=0, AP=1, XN=1 */
    mcr p15, 4, r0, c6, c3, 0     /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0     /* Write PRBAR */

    ldr r0, =OS_HEAP_END_ADDR     /* End address: OS_HEAP_END_ADDR is 64-byte aligned */
    sub r0, r0, #0x40             /* Limit = OS_HEAP_END_ADDR - 64 */
    orr r0, r0, #0x1              /* AttrIndex=0, cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1     /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1     /* Write PRLAR */

    /*---------------region 11 shared/reserved SRAM (non-cacheable, XN)----------------*/
    ldr r0, =11               /* Region 11 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =OS_HEAP_END_ADDR     /* OS_HEAP_END_ADDR is 64-byte aligned */
    and r0, r0, #0xFFFFFFC0   /* Ensure 64-byte alignment */
    orr r0, r0, #0x12         /* SH=0, AP=1, XN=1 */
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x0CDFFFFF       /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x3          /* AttrIndex=1, non-cacheable, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 6 internal gic & peripheral---------------*/
    /* device memory attribute            */
    ldr r0, =6                /* Region 6 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x22000000       /* Start address */
    orr r0, r0, #0x13         /* SH=2, AP=1, XN=1*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x223FFFFF       /* End address */
    sub r0, r0, #1
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x7          /* AttrIndex=3, device memory, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 7 peripheral---------------*/
    /* device memory attribute */
    ldr r0, =7                /* Region 7 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x23000000       /* Start address */
    orr r0, r0, #0x13         /* SH=2, AP=1, XN=1*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x2FFFFFFF       /* End address */
    sub r0, r0, #1
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x7          /* AttrIndex=3, device memory, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

   /*---------------region 8 CPUSYS------------------*/
    ldr r0, =8                /* Region 8 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x30000000       /* Start address */
    orr r0, r0, #0x13          /* SH=2, AP=1, XN=1*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x3FFFFFFF     /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x7          /* AttrIndex=3, device memory, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 9 DDR-------------------*/
    ldr r0, =9                /* Region 9 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x80000000       /* Start address */
    orr r0, r0, #0x2          /* SH=0, AP=1, XN=0*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0xFFFFFFFF     /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x3          /* AttrIndex=1, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------region 10 xspi-------------------*/
    /* device memory attribute            */
    ldr r0, =10               /* Region 10 */
    mcr p15, 4, r0, c6, c2, 1 /* Write HPRSELR */
    mcr p15, 0, r0, c6, c2, 1 /* Write PRSELR */

    ldr r0, =0x18000000         /* Start address */
    orr r0, r0, #0x13          /* SH=2, AP=1, XN=1*/
    mcr p15, 4, r0, c6, c3, 0 /* Write HPRBAR */
    mcr p15, 0, r0, c6, c3, 0 /* Write PRBAR */

    ldr r0, =0x1FFFFFFF       /* End address */
    and r0, r0, #0xFFFFFFC0
    orr r0, r0, #0x7          /* AttrIndex=3, device memory, enable region */
    mcr p15, 4, r0, c6, c3, 1 /* Write HPRLAR */
    mcr p15, 0, r0, c6, c3, 1 /* Write PRLAR */

    /*---------------SET MAIR/HMAIR-------------------*/
    ldr r0, =0x44FF            /* attr0(FF): normal memory, write-back non-transient */
                               /* attr1(44): normal memory, non-cacheable */
                               /* attr2~3(00): Device-nGnRnE memory */
    mcr p15, 4, r0, c10, c2, 0 /* Write HMAIR0 */
    mcr p15, 0, r0, c10, c2, 0 /* Write MAIR0 */

    ldr r0, =0x04              /* attr4~7(04/00): Device-nGnRnE memory */
    mcr p15, 4, r0, c10, c2, 1 /* Write HMAIR1 */
    mcr p15, 0, r0, c10, c2, 1 /* Write MAIR1 */

mpu_enable:
    mrc p15, 4, r0, c1, c0, 0 /* Read HSCTLR */
    orr r0, r0, #0x1          /* Enable MPU */
    dsb
    mcr p15, 4, r0, c1, c0, 0 /* Write HSCTLR */
    isb

    mrc p15, 0, r0, c1, c0, 0 /* Read SCTLR */
    orr r0, r0, #0x1          /* Enable MPU */
    dsb
    mcr p15, 0, r0, c1, c0, 0 /* Write SCTLR */
    isb

/* ARMv8-R cores are in EL2 (hypervisor mode) after reset, and we need
   to descend to EL1 (supervisor mode) or EL0 (user mode) */

/* Init HVBAR (Hypervisor Vector Base Address Register) */
    ldr r0, =EL2_core_exceptions_table
    mcr p15, 4, r0, c12, c0, 0 /* Move to Coprocessor from ARM Register */

/* Init VBAR (Vector Base Address Register) */
    ldr r0, =EL1_core_exceptions_table
    mcr p15, 0, r0, c12, c0, 0 /* Move to Coprocessor from ARM Register */

init_mcu_stack:
    ldr r3, =__StackTop
    mov SP, r3

    bl init_bss

    /* Init ELR_hyp with EL1_Reset_Handler so eret can descend from EL2 to EL1. */
    ldr r0, =EL1_Reset_Handler
    msr ELR_hyp, r0

    mrs r0, SPSR_hyp
    and r0, r0, #~0x00FF        /* r0 = r0 & FFFF FFE0. Clear SPSR_hyp bits [4:0] -> Execution state bit + Mode bits. */

    /* Return to EL1 system mode with interrupts masked until EL1 stack setup is done. */
    orr r0, r0, #0x1f
    bic r0, r0, #(0x1 << 5)
    msr SPSR_hyp, r0

    /* Configure the GIC CPU Interface */
    /* Disable group 0 interrupts */
    mov r0, #0x00
    mcr p15, 0, r0, c12, c12, 6 /* Write to ICC_IGRPEN0 */

    /* Enable group 1 interrupts */
    mov r0, #0x01
    mcr p15, 0, r0, c12, c12, 7 /* Write to ICC_IGRPEN1 */

    /* Set the interrupt priority mask to biggest value - 0x1F */
    /* Interrupts with all priorities are allowed. */

    mov r0, #0xF8 /* The priority bitfield is shifted with 3 bits - 0x1F becomes 0xF8 */
    mcr p15, 0, r0, c4, c6, 0 /* Write to ICC_PMR */

    /* Set the binary point for group 0 and group 1 interrupts */
    mov r0, #0
    mcr p15, 0, r0, c12, c8, 3  /* Write to ICC_BPR0 */
    mcr p15, 0, r0, c12, c12, 3 /* Write to ICC_BPR1 */

    /* Exception return - will jump to address pointed by ELR_hyp (main) */
    eret /* When executed in Hyp mode, ERET loads the PC from ELR_hyp and loads the CPSR from SPSR_hyp */


    .text
    .align 4
    .globl  EL1_Reset_Handler
    .type   EL1_Reset_Handler, %function
EL1_Reset_Handler:
/* Divide the non-USR mode stack area between the 5 non-USR modes */
    /* ABT,UND get 1/10 each. HYP, SVC,FIQ,IRQ get 1/5 each. */
    ldr         r3, =__StackTop
    ldr         r2, =__StackLimit
    sub         r2, r3, r2     /* r2 : size in bytes */
    mov 	    r4, #2
    udiv        r1, r2, r4     /* r1 : size divided by 2 */
    and         r1, r1, #~0x0f /* r1 size alligned to 16 bytes */

    /* Setup the stack for supervisor mode (entered from reset) */
    mrs         r0, cpsr
    and         r0, r0, #~0x00FF
    orr         r0, r0, #0x0033
    msr         cpsr_c, r0
    sub         r3, r3, r1
    mov         SP, r3         /* top of stack to SP_svc */

    ldr         r3, =__StackTop_exc
    ldr         r2, =__StackLimit_exc
    sub         r2, r3, r2     /* r2 : size in bytes */
    mov 		r4, #4
    udiv        r1, r2, r4     /* r1 : size divided by 4 */
    and         r1, r1, #~0x0f /* r1 size alligned to 16 bytes */

    /* Go to FIQ mode and set stack (below the previous one) */
    mrs         r0, cpsr
    and         r0, r0, #~0x003F
    orr         r0, r0, #0x0031
    msr         cpsr_c, r0
    sub         r3, r3, r1
    mov         SP, r3

    /* Go to IRQ mode and set stack (below the previous one) */
    mrs         r0, cpsr
    and         r0, r0, #~0x003F
    orr         r0, r0, #0x0032
    msr         cpsr_c, r0
    sub         r3, r3, r1
    mov         SP, r3

    /* Go to ABORT mode and set stack (below the previous one) */
    mrs         r0, cpsr
    and         r0, r0, #~0x003F
    orr         r0, r0, #0x0037
    msr         cpsr_c, r0
    sub         r3, r3, r1
    mov         SP, r3

    /* Go to UNDEF mode and set stack (below the previous one) */
    mrs         r0, cpsr
    and         r0, r0, #~0x003F
    orr         r0, r0, #0x003b
    msr         cpsr_c, r0
    sub         r3, r3, r1
    mov         SP, r3

    /* Go to SYSTEM mode and set stack to the top of the reserved area */
    /*   This is also the stack for user mode */
    mrs         r0, cpsr
    and         r0, r0, #~0x003F
    orr         r0, r0, #0x003F
    msr         cpsr_c, r0

    ldr         r3, =__StackTop_exc
    mov         SP, r3

   /* Enable IRQ and FIQ interrupts for the system/user mode */
    cpsie   i               /* Unmask interrupts (IRQ)*/
    cpsie   f               /* Unmask fast interrupts (FIQ)*/

    /* Go to supervisor mode */
    mrs         r0, cpsr
    and         r0, r0, #~0x00FF
    orr         r0, r0, #0x0033
    msr         cpsr_c, r0
    /* Jump to the entry() method */
    bl entry

    /* Should never get here */
    b .

    .text
    .align 4
    .globl  init_bss
    .type   init_bss, %function
init_bss:
    ldr     r1, =__bss_start
    ldr     r2, =__bss_end
    mov     r0, #0

.clear_bss_loop:
    cmp     r1, r2
    bcs     .init_done
    str     r0, [r1], #4
    b       .clear_bss_loop

.init_done:
    bx      lr
