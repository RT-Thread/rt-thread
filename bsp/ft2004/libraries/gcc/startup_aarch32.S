

.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.section .Startup_Aarch32, "a"
.global Startup_Aarch32  				/* 全局标号 */

Startup_Aarch32:



    MRS    r1, cpsr
    BIC    r1, r1, #0x0000001F
    ORR    r1, r1, #0x13 | (1<<7) | (1<<6)
    MSR    cpsr, r1

    /* 
     * SPSR does not have pre-defined reset value. 
     * Here correct endianess (BE bit) in SPSR
    */

    MRS    r0, spsr
    BIC    r0, r0, #(0x1 << 9)          /* Little Endian */
    MSR    spsr_x, r0


    b Startup_Ft_Aarch32

    .size    Startup_Aarch32, . - Startup_Aarch32
    .text
    .arm


.syntax unified
.arch armv8-a

.section .Startup_Ft_Aarch32, "a"
.align 2
.global Startup_Ft_Aarch32  				/* 全局标号 */

Startup_Ft_Aarch32:
    
    ldr     pc, =Reset_Handler           /* Reset                  */
    ldr     pc, =Undefined_Handler       /* Undefined instructions */
    ldr     pc, =SVC_Handler             /* Supervisor Call        */
    ldr     pc, =PrefAbort_Handler       /* Prefetch abort         */
       /*     ldr     pc, =DataAbort_Handler Data abort             */
    ldr     pc, =DataAbort_Handler
    .word   0                            /* RESERVED               */
    ldr     pc, =IRQ_Handler             /* IRQ interrupt          */
    ldr     pc, =FIQ_Handler             /* FIQ interrupt          */

    .size    Startup_Ft_Aarch32, . - Startup_Ft_Aarch32
    .text
    .arm



    .arm
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid i						/* Mask interrupts */


	/* 关闭I,DCache和MMU 
	 * 采取读-改-写的方式。
	 */
	mrc     p15, 0, r0, c1, c0, 0     /* 读取CP15的C1寄存器到R0中       		        	*/
    bic     r0,  r0, #(0x1 << 12)     /* 清除C1寄存器的bit12位(I位)，关闭I Cache            	*/
    bic     r0,  r0, #(0x1 <<  2)     /* 清除C1寄存器的bit2(C位)，关闭D Cache    				*/
    bic     r0,  r0, #0x2             /* 清除C1寄存器的bit1(A位)，关闭对齐						*/   
    bic     r0,  r0, #(0x1 << 11)     /* 清除C1寄存器的bit11(Z位)，关闭分支预测					*/
    bic     r0,  r0, #0x1             /* 清除C1寄存器的bit0(M位)，关闭MMU				       	*/
    mcr     p15, 0, r0, c1, c0, 0     /* 将r0寄存器中的值写入到CP15的C1寄存器中	 				*/
    

    /* 设置用户堆栈 */
    /* Set up stack for IRQ, System/User and Supervisor Modes */
	/* 进入IRQ模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x12 	/* r0或上0x13,表示使用IRQ模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =__IStackTop	

	/* 进入SYS模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x1f 	/* r0或上0x13,表示使用SYS模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =__CStackTop	

	/* 进入SVC模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x13 	/* r0或上0x13,表示使用SVC模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =__CStackTop	
    



#ifndef NO_RTOS
    ldr     r0,=SystemInit
    blx     r0

    MOV R0, #(0xF << 20) // Enable CP10 & CP11 function
    MCR P15, 0, R0, C1, C0, 2 // Write the Coprocessor Access Control 
    ISB // Register (CPACR).
    // Switch on the FP and NEON hardware.
    MOV R1, #(0x1 << 30)
    VMSR FPEXC, R1

#endif

   cpsie i				/* 打开全局中断 */

   /* b main 跳转到main函数 			 	*/
   b main 



.macro push_svc_reg
    sub     sp, sp, #17 * 4         @/* Sizeof(struct ft_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    mrs     r6, spsr                @/* Save CPSR                       */
    str     lr, [r0, #15*4]         @/* Push PC                         */
    str     r6, [r0, #16*4]         @/* Push CPSR                       */
    cps     #Mode_SVC
    str     sp, [r0, #13*4]         @/* Save calling SP                 */
    str     lr, [r0, #14*4]         @/* Save calling PC                 */
.endm



/* Undefined_Handler */
    .align  2
    .arm
    .weak Undefined_Handler
    .type Undefined_Handler, %function
Undefined_Handler:
    b Undefine_debug
    b Undefined_Handler
    .size Undefined_Handler, . - Undefined_Handler


    .align 2
    .arm
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    b Svc_debug
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

    .align 2
    .arm
    .weak PrefAbort_Handler
    .type PrefAbort_Handler, %function
PrefAbort_Handler:
    b PrefAbort_debug
    ldr   r0,=PrefAbort_Handler
    bx    r0
    .size PrefAbort_Handler, . - PrefAbort_Handler


    .align 5
    .arm
    .weak DataAbort_Handler
    .type DataAbort_Handler, %function
DataAbort_Handler:
    push_svc_reg
    bl Ft_Arrch32_trap_dabt
    b .

    .align 4
    .arm
    .weak IRQ_Handler
    .type IRQ_Handler, %function
IRQ_Handler:
    push    {lr}                         /* Save return address+4                                */
    push    {r0-r3, r12}                 /* Push caller save registers                           */

    MRS     r0, spsr                     /* Save SPRS to allow interrupt reentry                 */
    push    {r0}
    
    /* Get GIC base address                        MRC     P15, 4, r1, C15, C0, 0         */
    
    //<! get iar 
    mrc p15, 0, r0, c12, c12, 0
    isb

    push    {r0, r1}

    CPS     #0x13                        /* Change to Supervisor mode to allow interrupt reentry */
    
    push    {lr}                         /* Save Supervisor lr                                   */
   
#if 1 
    LDR     r2, =System_IrqHandler
    BLX     r2                           /*  b irq_debug Call SystemIrqHandler with param GCC                 */
#endif

    POP     {lr}

    CPS     #0x12                        /* Back to IRQ mode                                     */

    POP     {r0, r1}

    POP     {r0}
    MSR     spsr_cxsf, r0

    POP     {r0-r3, r12}
    POP     {lr}
    SUBS    pc, lr, #4
    .size IRQ_Handler, . - IRQ_Handler



    .align 2
    .arm
    .weak FIQ_Handler
    .type FIQ_Handler, %function
FIQ_Handler:
    bl frq_debug
    ldr   r0,=FIQ_Handler
    bx    r0
    .size FIQ_Handler, . - FIQ_Handler

    .end



