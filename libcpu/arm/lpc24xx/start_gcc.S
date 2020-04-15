/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 * 2011-03-17     Bernard      update to 0.4.x
 */

#define WDMOD          (0xE0000000 + 0x00)
#define VICIntEnClr    (0xFFFFF000 + 0x014)
#define VICVectAddr    (0xFFFFF000 + 0xF00)
#define VICIntSelect   (0xFFFFF000 + 0x00C)
#define PLLCFG         (0xE01FC000 + 0x084)
#define PLLCON         (0xE01FC000 + 0x080)
#define PLLFEED        (0xE01FC000 + 0x08C)
#define PLLSTAT        (0xE01FC000 + 0x088)
#define CCLKCFG        (0xE01FC000 + 0x104)
#define MEMMAP         (0xE01FC000 + 0x040)     
#define SCS            (0xE01FC000 + 0x1A0)     
#define CLKSRCSEL      (0xE01FC000 + 0x10C)
#define MAMCR          (0xE01FC000 + 0x000)
#define MAMTIM         (0xE01FC000 + 0x004)

/* stack memory */
.section .bss.noinit
.equ    IRQ_STACK_SIZE, 0x00000200
.equ    FIQ_STACK_SIZE, 0x00000100
.equ    UDF_STACK_SIZE, 0x00000004
.equ    ABT_STACK_SIZE, 0x00000004
.equ    SVC_STACK_SIZE, 0x00000200

.space  IRQ_STACK_SIZE
IRQ_STACK:

.space  FIQ_STACK_SIZE
FIQ_STACK:

.space  UDF_STACK_SIZE
UDF_STACK:

.space  ABT_STACK_SIZE
ABT_STACK:

.space  SVC_STACK_SIZE
SVC_STACK:

.section .init, "ax"
.code 32
.globl _start
_start:
        b reset
        ldr     pc, _vector_undef
        ldr     pc, _vector_swi
        ldr     pc, _vector_pabt
        ldr     pc, _vector_dabt
        ldr     pc, _vector_resv
        ldr     pc, _vector_irq
        ldr     pc, _vector_fiq

_vector_undef:  .word vector_undef
_vector_swi:    .word vector_swi
_vector_pabt:   .word vector_pabt
_vector_dabt:   .word vector_dabt
_vector_resv:   .word vector_resv
_vector_irq:    .word vector_irq
_vector_fiq:    .word vector_fiq

.balignl        16,0xdeadbeef

/*
 * rtthread kernel start and end
 * which are defined in linker script
 */
.globl _rtthread_start
_rtthread_start:
        .word _start
        
.globl _rtthread_end
_rtthread_end:
        .word  _end

/*
 * rtthread bss start and end which are defined in linker script
 */
.globl _bss_start
_bss_start:     
        .word __bss_start
        
.globl _bss_end
_bss_end:
        .word __bss_end

.text
.code 32

/* the system entry */
reset:
        /* enter svc mode */
        msr cpsr_c, #SVCMODE|NOINT
        
        /*watch dog disable */
        ldr r0,=WDMOD
        ldr r1,=0x0             
        str r1,[r0]
        
        /* all interrupt disable */
        ldr r0,=VICIntEnClr
        ldr r1,=0xffffffff
        str r1,[r0]
        
        ldr     r1, =VICVectAddr
        ldr     r0, =0x00
        str     r0, [r1]
        
        ldr     r1, =VICIntSelect
        ldr     r0, =0x00
        str     r0, [r1]        
        
        /* setup stack */
        bl              stack_setup

        /* copy .data to SRAM */
        ldr     r1, =_sidata            /* .data start in image */
        ldr     r2, =_edata             /* .data end in image   */
        ldr     r3, =_sdata             /* sram data start      */
data_loop:
        ldr     r0, [r1, #0]
        str     r0, [r3]

        add     r1, r1, #4
        add     r3, r3, #4

        cmp     r3, r2                   /* check if data to clear */
        blo     data_loop                /* loop until done        */

        /* clear .bss */
        mov     r0,#0                   /* get a zero */
        ldr     r1,=__bss_start         /* bss start  */
        ldr     r2,=__bss_end           /* bss end    */
        
bss_loop:
        cmp     r1,r2                   /* check if data to clear */
        strlo   r0,[r1],#4              /* clear 4 bytes          */
        blo     bss_loop                /* loop until done        */

        /* call C++ constructors of global objects */
        ldr     r0, =__ctors_start__
        ldr     r1, =__ctors_end__

ctor_loop:
        cmp     r0, r1
        beq     ctor_end
        ldr     r2, [r0], #4
        stmfd   sp!, {r0-r1}
        mov     lr, pc
        bx      r2
        ldmfd   sp!, {r0-r1}
        b       ctor_loop       
ctor_end:

        /* start RT-Thread Kernel               */
        ldr     pc, _rtthread_startup

_rtthread_startup: 
        .word rtthread_startup

        .equ USERMODE,  0x10
        .equ FIQMODE,   0x11
        .equ IRQMODE,   0x12
        .equ SVCMODE,   0x13
        .equ ABORTMODE, 0x17
        .equ UNDEFMODE, 0x1b
        .equ MODEMASK,  0x1f
        .equ NOINT,             0xc0

/* exception handlers */
vector_undef:   bl rt_hw_trap_udef
vector_swi:     bl rt_hw_trap_swi
vector_pabt:    bl rt_hw_trap_pabt
vector_dabt:    bl rt_hw_trap_dabt
vector_resv:    bl rt_hw_trap_resv

.globl rt_interrupt_enter
.globl rt_interrupt_leave
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
vector_irq:     
        stmfd   sp!, {r0-r12,lr}
        bl      rt_interrupt_enter
        bl      rt_hw_trap_irq
        bl      rt_interrupt_leave

        /* if rt_thread_switch_interrupt_flag set,
         * jump to _interrupt_thread_switch and don't return
         */
        ldr     r0, =rt_thread_switch_interrupt_flag
        ldr     r1, [r0]
        cmp     r1, #1
        beq     _interrupt_thread_switch

        ldmfd   sp!, {r0-r12,lr}
        subs    pc, lr, #4

        .align  5
vector_fiq:
        stmfd   sp!,{r0-r7,lr}
        bl      rt_hw_trap_fiq
        ldmfd   sp!,{r0-r7,lr}
        subs    pc,lr,#4

_interrupt_thread_switch:
        mov     r1, #0          /* clear rt_thread_switch_interrupt_flag */
        str     r1, [r0]

        ldmfd   sp!, {r0-r12,lr} /* reload saved registers */
        stmfd   sp!, {r0-r3}    /* save r0-r3 */
        mov     r1, sp
        add     sp, sp, #16     /*  restore sp */
        sub     r2, lr, #4      /* save old task's pc to r2 */

        mrs     r3, spsr        /* disable interrupt */
        orr     r0, r3, #NOINT
        msr     spsr_c, r0

        ldr     r0,  =.+8       /* switch to interrupted task's stack */
        movs    pc, r0

        stmfd   sp!, {r2}       /* push old task's pc */
        stmfd   sp!, {r4-r12,lr} /* push old task's lr,r12-r4 */
        mov     r4, r1          /* Special optimised code below */
        mov     r5, r3
        ldmfd   r4!, {r0-r3}
        stmfd   sp!, {r0-r3}    /* push old task's r3-r0 */
        stmfd   sp!, {r5}       /* push old task's psr */
        mrs     r4, spsr
        stmfd   sp!, {r4}       /* push old task's spsr */

        ldr     r4, =rt_interrupt_from_thread
        ldr     r5, [r4]
        str     sp, [r5]        /* store sp in preempted tasks's TCB */

        ldr     r6, =rt_interrupt_to_thread
        ldr     r6, [r6]
        ldr     sp, [r6]        /* get new task's stack pointer */

        ldmfd   sp!, {r4}       /* pop new task's spsr */
        msr     SPSR_cxsf, r4
        ldmfd   sp!, {r4}       /* pop new task's psr */
        msr     CPSR_cxsf, r4

        ldmfd sp!, {r0-r12,lr,pc} /* pop new task's r0-r12,lr & pc */

stack_setup:
        mrs     r0, cpsr
        bic     r0, r0, #MODEMASK
        orr     r1, r0, #UNDEFMODE|NOINT
        msr     cpsr_cxsf, r1                   /* undef mode */
        ldr     sp, =UDF_STACK

        orr     r1,r0,#ABORTMODE|NOINT
        msr     cpsr_cxsf,r1                    /* abort mode */
        ldr     sp, =ABT_STACK

        orr     r1,r0,#IRQMODE|NOINT
        msr     cpsr_cxsf,r1                    /* IRQ mode */
        ldr     sp, =IRQ_STACK

        orr     r1,r0,#FIQMODE|NOINT
        msr     cpsr_cxsf,r1                    /* FIQ mode */
        ldr     sp, =FIQ_STACK

        bic     r0,r0,#MODEMASK
        orr     r1,r0,#SVCMODE|NOINT
        msr     cpsr_cxsf,r1                    /* SVC mode */
        ldr     sp, =SVC_STACK

        /* USER mode is not initialized. */
        mov     pc,lr                           /* The LR register may be not valid for the mode changes.*/
