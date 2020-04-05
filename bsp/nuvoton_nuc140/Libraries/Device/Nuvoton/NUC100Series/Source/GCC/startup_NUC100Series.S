/****************************************************************************//**
 * @file     startup_M0518.S
 * @version  V1.00
 * @brief    CMSIS Device Startup File
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/



    .syntax unified
    .arch   armv8 - m.base
    
    .section .stack
    .align  3
#ifndef Stack_Size
    .equ    Stack_Size, 0x00000400
#endif
    .global __StackTop
    .global __StackLimit
__StackLimit:
    .space  Stack_Size
    .size   __StackLimit, . - __StackLimit
__StackTop:
    .size   __StackTop, . - __StackTop
    
    .section .heap
    .align  3
#ifndef Heap_Size
    .equ    Heap_Size, 0x00000100
#endif
    
    .global __HeapBase
    .global __HeapLimit
__HeapBase:
    .if Heap_Size
    .space  Heap_Size
    .endif
    .size   __HeapBase, . - __HeapBase
__HeapLimit:
    .size   __HeapLimit, . - __HeapLimit
    
    .section .vectors
    .align  2
    .global __Vectors
__Vectors:
    .long   __StackTop            /* Top of Stack */
    .long   Reset_Handler         /* Reset Handler */
    .long   NMI_Handler           /* NMI Handler */
    .long   HardFault_Handler     /* Hard Fault Handler */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   SVC_Handler           /* SVCall Handler */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   PendSV_Handler        /* PendSV Handler */
    .long   SysTick_Handler       /* SysTick Handler */
    
    /* External interrupts */
    
    .long   BOD_IRQHandler  
    .long   WDT_IRQHandler  
    .long   EINT0_IRQHandler
    .long   EINT1_IRQHandler
    .long   GPAB_IRQHandler 
    .long   GPCDEF_IRQHandler
    .long   PWMA_IRQHandler  
    .long   PWMB_IRQHandler  
    .long   TMR0_IRQHandler 
    .long   TMR1_IRQHandler 
    .long   TMR2_IRQHandler 
    .long   TMR3_IRQHandler 
    .long   UART02_IRQHandler
    .long   UART1_IRQHandler
    .long   SPI0_IRQHandler  
    .long   SPI1_IRQHandler  
    .long   SPI2_IRQHandler  
    .long   SPI3_IRQHandler  
    .long   I2C0_IRQHandler 
    .long   I2C1_IRQHandler 
    .long   CAN0_IRQHandler  
    .long   CAN1_IRQHandler 
    .long   SC012_IRQHandler 
    .long   USBD_IRQHandler  
    .long   PS2_IRQHandler  
    .long   ACMP_IRQHandler 
    .long   PDMA_IRQHandler
    .long   I2S_IRQHandler 
    .long   PWRWU_IRQHandler
    .long   ADC_IRQHandler
    .long   Default_Handler    
    .long   RTC_IRQHandler    
    
    .size   __Vectors, . - __Vectors
    
    
    
    .text
    .thumb
    .thumb_func
    .align  2
    .global Reset_Handler
    .type   Reset_Handler, % function
    
    
Reset_Handler:
    /*  Firstly it copies data from read only memory to RAM. There are two schemes
     *  to copy. One can copy more than one sections. Another can only copy
     *  one section.  The former scheme needs more instructions and read-only
     *  data to implement than the latter.
     *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */
    
#ifdef __STARTUP_COPY_MULTIPLE
    /*  Multiple sections scheme.
     *
     *  Between symbol address __copy_table_start__ and __copy_table_end__,
     *  there are array of triplets, each of which specify:
     *    offset 0: LMA of start of a section to copy from
     *    offset 4: VMA of start of a section to copy to
     *    offset 8: size of the section to copy. Must be multiply of 4
     *
     *  All addresses must be aligned to 4 bytes boundary.
     */
    ldr r4, = __copy_table_start__
    ldr r5, = __copy_table_end__
    
.L_loop0:
    cmp r4, r5
    bge .L_loop0_done
    ldr r1, [r4]
    ldr r2, [r4, #4]
    ldr r3, [r4, #8]
    
.L_loop0_0:
    subs    r3, #4
    blt .L_loop0_0_done
    ldr r0, [r1, r3]
    str r0, [r2, r3]
    b   .L_loop0_0
    
.L_loop0_0_done:
    adds    r4, #12
    b   .L_loop0
    
.L_loop0_done:
#else
    /*  Single section scheme.
     *
     *  The ranges of copy from/to are specified by following symbols
     *    __etext: LMA of start of the section to copy from. Usually end of text
     *    __data_start__: VMA of start of the section to copy to
     *    __data_end__: VMA of end of the section to copy to
     *
     *  All addresses must be aligned to 4 bytes boundary.
     */
    ldr r1, = __etext
    ldr r2, = __data_start__
    ldr r3, = __data_end__
    
    subs    r3, r2
    ble .L_loop1_done
    
.L_loop1:
    subs    r3, #4
    ldr r0, [r1, r3]
    str r0, [r2, r3]
    bgt .L_loop1
    
.L_loop1_done:
#endif /*__STARTUP_COPY_MULTIPLE */
    
    /*  This part of work usually is done in C library startup code. Otherwise,
     *  define this macro to enable it in this startup.
     *
     *  There are two schemes too. One can clear multiple BSS sections. Another
     *  can only clear one section. The former is more size expensive than the
     *  latter.
     *
     *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
     *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
     */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
    /*  Multiple sections scheme.
     *
     *  Between symbol address __copy_table_start__ and __copy_table_end__,
     *  there are array of tuples specifying:
     *    offset 0: Start of a BSS section
     *    offset 4: Size of this BSS section. Must be multiply of 4
     */
    ldr r3, = __zero_table_start__
    ldr r4, = __zero_table_end__
    
.L_loop2:
    cmp r3, r4
    bge .L_loop2_done
    ldr r1, [r3]
    ldr r2, [r3, #4]
    movs    r0, 0
    
.L_loop2_0:
    subs    r2, #4
    blt .L_loop2_0_done
    str r0, [r1, r2]
    b   .L_loop2_0
.L_loop2_0_done:
    
    adds    r3, #8
    b   .L_loop2
.L_loop2_done:

#elif defined (__STARTUP_CLEAR_BSS)
    /*  Single BSS section scheme.
     *
     *  The BSS section is specified by following symbols
     *    __bss_start__: start of the BSS section.
     *    __bss_end__: end of the BSS section.
     *
     *  Both addresses must be aligned to 4 bytes boundary.
     */
    ldr r1, = __bss_start__
    ldr r2, = __bss_end__

    movs    r0, 0

    subs    r2, r1
    ble .L_loop3_done

.L_loop3:
    subs    r2, #4
    str r0, [r1, r2]
    bgt .L_loop3
.L_loop3_done:
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */
    
    
    
#ifndef __NO_SYSTEM_INIT
    bl  SystemInit
#endif
    
    
#ifndef __START
#define __START _start
#endif
    bl  __START
    
    .pool
    .size   Reset_Handler, . - Reset_Handler
    
    .align  1
    .thumb_func
    .weak   Default_Handler
    .type   Default_Handler, % function
    
Default_Handler:
    b   .
    .size   Default_Handler, . - Default_Handler
    
    /*    Macro to define default handlers. Default handler
     *    will be weak symbol and just dead loops. They can be
     *    overwritten by other handlers */
     
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm
    
    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler


    def_irq_handler BOD_IRQHandler
    def_irq_handler WDT_IRQHandler
    def_irq_handler EINT0_IRQHandler
    def_irq_handler EINT1_IRQHandler
    def_irq_handler GPAB_IRQHandler
    def_irq_handler GPCDEF_IRQHandler
    def_irq_handler PWMA_IRQHandler
    def_irq_handler PWMB_IRQHandler
    def_irq_handler TMR0_IRQHandler
    def_irq_handler TMR1_IRQHandler
    def_irq_handler TMR2_IRQHandler
    def_irq_handler TMR3_IRQHandler
    def_irq_handler UART02_IRQHandler
    def_irq_handler UART1_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler SPI2_IRQHandler
    def_irq_handler SPI3_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler CAN0_IRQHandler
    def_irq_handler CAN1_IRQHandler
    def_irq_handler SC012_IRQHandler
    def_irq_handler USBD_IRQHandler
    def_irq_handler PS2_IRQHandler
    def_irq_handler ACMP_IRQHandler
    def_irq_handler PDMA_IRQHandler
    def_irq_handler I2S_IRQHandler
    def_irq_handler PWRWU_IRQHandler
    def_irq_handler ADC_IRQHandler
    def_irq_handler RTC_IRQHandler
    
    
    /* ;int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0) */
    .align 2
    .thumb_func
    .type SH_DoCommand, % function
    
SH_DoCommand:
    
    BKPT   0xAB                /* ; Wait ICE or HardFault */
    //LDR    R3, = SH_Return
    MOV    R4, lr
    BLX    R3                  /* ; Call SH_Return. The return value is in R0 */
    BX     R4                  /* ; Return value = R0 */
    .size  SH_DoCommand, . - SH_DoCommand
    
    .align  2
    .thumb_func
    .global __PC
    .type   __PC, % function
    
    .end
