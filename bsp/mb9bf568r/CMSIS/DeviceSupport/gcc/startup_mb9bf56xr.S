/**************************************************************************//**
 * @file     startup_<Device>.s
 * @brief    CMSIS Cortex-M# Core Device Startup File for
 *           Device <Device>
 * @version  V3.01
 * @date     06. March 2012
 *
 * @note     Version CodeSourcery Sourcery G++ Lite (with CS3)
 * Copyright (C) 2012 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Stack_Size, 0x00000400
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack_size
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem


/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Heap_Size,  0x00000100
    
    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:


/* Vector Table */

    .section ".cs3.interrupt_vector"
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object

__cs3_interrupt_vector_cortex_m:
    .long   __cs3_stack                 /* Top of Stack                 */
    .long   __cs3_reset                 /* Reset Handler                */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
/* ToDo:  Add here the vectors for the device specific external interrupts handler */
    .long   CSV_Handler                 /* 0: Clock Super Visor */
    .long   SWDT_Handler                /* 1: Software Watchdog Timer */
    .long   LVD_Handler                 /* 2: Low Voltage Detector */
    .long   MFT_WG_IRQHandler           /* 3: Wave Form Generator / DTIF */
    .long   INT0_7_Handler              /* 4: External Interrupt Request ch.0 to ch.7 */
    .long   INT8_15_Handler             /* 5: External Interrupt Request ch.8 to ch.15 */
    .long   DT_Handler                  /* 6: Dual Timer / Quad Decoder */
    .long   MFS0RX_IRQHandler           /* 7: MultiFunction Serial ch.0 */
    .long   MFS0TX_IRQHandler           /* 8: MultiFunction Serial ch.0 */
    .long   MFS1RX_IRQHandler           /* 9: MultiFunction Serial ch.1 */
    .long   MFS1TX_IRQHandler           /* 10: MultiFunction Serial ch.1 */
    .long   MFS2RX_IRQHandler           /* 11: MultiFunction Serial ch.2 */
    .long   MFS2TX_IRQHandler           /* 12: MultiFunction Serial ch.2 */
    .long   MFS3RX_IRQHandler           /* 13: MultiFunction Serial ch.3 */
    .long   MFS3TX_IRQHandler           /* 14: MultiFunction Serial ch.3 */
    .long   MFS4RX_IRQHandler           /* 15: MultiFunction Serial ch.4 */
    .long   MFS4TX_IRQHandler           /* 16: MultiFunction Serial ch.4 */
    .long   MFS5RX_IRQHandler           /* 17: MultiFunction Serial ch.5 */
    .long   MFS5TX_IRQHandler           /* 18: MultiFunction Serial ch.5 */
    .long   MFS6RX_IRQHandler           /* 19: MultiFunction Serial ch.6 */
    .long   MFS6TX_IRQHandler           /* 20: MultiFunction Serial ch.6 */
    .long   MFS7RX_IRQHandler           /* 21: MultiFunction Serial ch.7 */
    .long   MFS7TX_IRQHandler           /* 22: MultiFunction Serial ch.7 */
    .long   PPG_Handler                 /* 23: PPG */
    .long   TIM_IRQHandler              /* 24: OSC / PLL / Watch Counter */
    .long   ADC0_IRQHandler             /* 25: ADC0 */
    .long   ADC1_IRQHandler             /* 26: ADC1 */
    .long   ADC2_IRQHandler             /* 27: ADC2 */
    .long   MFT_FRT_IRQHandler          /* 28: Free-run Timer */
    .long   MFT_IPC_IRQHandler          /* 29: Input Capture */
    .long   MFT_OPC_IRQHandler          /* 30: Output Compare */
    .long   BT_IRQHandler               /* 31: Base Timer ch.0 to ch.7 */
    .long   CAN0_IRQHandler             /* 32: CAN ch.0 */
    .long   CAN1_IRQHandler             /* 33: CAN ch.1 */
    .long   USBF_Handler                /* 34: USB Function */
    .long   USB_Handler                 /* 35: USB Function / USB HOST */
    .long   RESERVED_1_IRQHandler       /* 36: Reserved */
    .long   RESERVED_2_IRQHandler       /* 37: Reserved */
    .long   DMAC0_Handler               /* 38: DMAC ch.0 */
    .long   DMAC1_Handler               /* 39: DMAC ch.1 */
    .long   DMAC2_Handler               /* 40: DMAC ch.2 */
    .long   DMAC3_Handler               /* 41: DMAC ch.3 */
    .long   DMAC4_Handler               /* 42: DMAC ch.4 */
    .long   DMAC5_Handler               /* 43: DMAC ch.5 */
    .long   DMAC6_Handler               /* 44: DMAC ch.6 */
    .long   DMAC7_Handler               /* 45: DMAC ch.7 */
    .long   RESERVED_3_IRQHandler       /* 46: Reserved */
    .long   RESERVED_4_IRQHandler       /* 47: Reserved */

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section .cs3.reset,"x",%progbits
    .thumb_func
    .globl  __cs3_reset_cortex_m
    .globl  _start
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
_start:
    .fnstart
    LDR     R0, =SystemInit
    BLX     R0
    LDR     R0,=_start
    BX      R0
    .pool
    .cantunwind
    .fnend
    .size   __cs3_reset_cortex_m,.-__cs3_reset_cortex_m

    .section ".text"

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

/* ToDo:  Add here the export definition for the device specific external interrupts handler */ 
/* ToDo:  Add here the names for the device specific external interrupts handler             */
    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ     CSV_Handler                 /* 0: Clock Super Visor */
    IRQ     SWDT_Handler                /* 1: Software Watchdog Timer */
    IRQ     LVD_Handler                 /* 2: Low Voltage Detector */
    IRQ     MFT_WG_IRQHandler           /* 3: Wave Form Generator / DTIF */
    IRQ     INT0_7_Handler              /* 4: External Interrupt Request ch.0 to ch.7 */
    IRQ     INT8_15_Handler             /* 5: External Interrupt Request ch.8 to ch.15 */
    IRQ     DT_Handler                  /* 6: Dual Timer / Quad Decoder */
    IRQ     MFS0RX_IRQHandler           /* 7: MultiFunction Serial ch.0 */
    IRQ     MFS0TX_IRQHandler           /* 8: MultiFunction Serial ch.0 */
    IRQ     MFS1RX_IRQHandler           /* 9: MultiFunction Serial ch.1 */
    IRQ     MFS1TX_IRQHandler           /* 10: MultiFunction Serial ch.1 */
    IRQ     MFS2RX_IRQHandler           /* 11: MultiFunction Serial ch.2 */
    IRQ     MFS2TX_IRQHandler           /* 12: MultiFunction Serial ch.2 */
    IRQ     MFS3RX_IRQHandler           /* 13: MultiFunction Serial ch.3 */
    IRQ     MFS3TX_IRQHandler           /* 14: MultiFunction Serial ch.3 */
    IRQ     MFS4RX_IRQHandler           /* 15: MultiFunction Serial ch.4 */
    IRQ     MFS4TX_IRQHandler           /* 16: MultiFunction Serial ch.4 */
    IRQ     MFS5RX_IRQHandler           /* 17: MultiFunction Serial ch.5 */
    IRQ     MFS5TX_IRQHandler           /* 18: MultiFunction Serial ch.5 */
    IRQ     MFS6RX_IRQHandler           /* 19: MultiFunction Serial ch.6 */
    IRQ     MFS6TX_IRQHandler           /* 20: MultiFunction Serial ch.6 */
    IRQ     MFS7RX_IRQHandler           /* 21: MultiFunction Serial ch.7 */
    IRQ     MFS7TX_IRQHandler           /* 22: MultiFunction Serial ch.7 */
    IRQ     PPG_Handler                 /* 23: PPG */
    IRQ     TIM_IRQHandler              /* 24: OSC / PLL / Watch Counter */
    IRQ     ADC0_IRQHandler             /* 25: ADC0 */
    IRQ     ADC1_IRQHandler             /* 26: ADC1 */
    IRQ     ADC2_IRQHandler             /* 27: ADC2 */
    IRQ     MFT_FRT_IRQHandler          /* 28: Free-run Timer */
    IRQ     MFT_IPC_IRQHandler          /* 29: Input Capture */
    IRQ     MFT_OPC_IRQHandler          /* 30: Output Compare */
    IRQ     BT_IRQHandler               /* 31: Base Timer ch.0 to ch.7 */
    IRQ     CAN0_IRQHandler             /* 32: CAN ch.0 */
    IRQ     CAN1_IRQHandler             /* 33: CAN ch.1 */
    IRQ     USBF_Handler                /* 34: USB Function */
    IRQ     USB_Handler                 /* 35: USB Function / USB HOST */
    IRQ     RESERVED_1_IRQHandler       /* 36: Reserved */
    IRQ     RESERVED_2_IRQHandler       /* 37: Reserved */
    IRQ     DMAC0_Handler               /* 38: DMAC ch.0 */
    IRQ     DMAC1_Handler               /* 39: DMAC ch.1 */
    IRQ     DMAC2_Handler               /* 40: DMAC ch.2 */
    IRQ     DMAC3_Handler               /* 41: DMAC ch.3 */
    IRQ     DMAC4_Handler               /* 42: DMAC ch.4 */
    IRQ     DMAC5_Handler               /* 43: DMAC ch.5 */
    IRQ     DMAC6_Handler               /* 44: DMAC ch.6 */
    IRQ     DMAC7_Handler               /* 45: DMAC ch.7 */
    IRQ     RESERVED_3_IRQHandler       /* 46: Reserved */
    IRQ     RESERVED_4_IRQHandler       /* 47: Reserved */

    .end
