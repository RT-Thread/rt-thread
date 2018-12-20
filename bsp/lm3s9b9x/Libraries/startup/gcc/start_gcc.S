  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */  
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
/* restore original stack pointer */  
  ldr   sp, =_estack       /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */  
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4
    
LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =_sbss
  b  LoopFillZerobss
/* Zero fill the bss segment. */  
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4
    
LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss
/* Call the application's entry point.*/
  bl  main
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None     
 * @retval : None       
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
  
/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/    
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors
    
    
g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  Default_Handler                     //NMI_Handler
  .word  HardFault_Handler
  .word  Default_Handler                     //MemManage_Handler
  .word  Default_Handler                     //BusFault_Handler
  .word  Default_Handler                     //UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  Default_Handler                     //SVC_Handler
  .word  Default_Handler                     //DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  rt_hw_timer_handler
  .word  Default_Handler                     // GPIO Port A              
  .word  Default_Handler                     // GPIO Port B              
  .word  Default_Handler                     // GPIO Port C              
  .word  Default_Handler                     // GPIO Port D              
  .word  Default_Handler                     // GPIO Port E              
  .word  rt_hw_uart_isr_1                      // UART0 Rx and Tx           
  .word  Default_Handler                     // UART1 Rx and Tx          
  .word  Default_Handler                     // SSI Rx and Tx            
  .word  Default_Handler                     // I2C Master and Slave     
  .word  Default_Handler                     // PWM Fault                
  .word  Default_Handler                     // PWM Generator 0          
  .word  Default_Handler                     // PWM Generator 1          
  .word  Default_Handler                     // PWM Generator 2          
  .word  Default_Handler                     // Quadrature Encoder       
  .word  Default_Handler                     // ADC Sequence 0           
  .word  Default_Handler                     // ADC Sequence 1           
  .word  Default_Handler                     // ADC Sequence 2           
  .word  Default_Handler                     // ADC Sequence 3           
  .word  Default_Handler                     // Watchdog timer           
  .word  Default_Handler                     // Timer 0 subtimer A       
  .word  Default_Handler                     // Timer 0 subtimer B       
  .word  Default_Handler                     // Timer 1 subtimer A       
  .word  Default_Handler                     // Timer 1 subtimer B       
  .word  Default_Handler                     // Timer 2 subtimer A       
  .word  Default_Handler                     // Timer 2 subtimer B       
  .word  Default_Handler                     // Analog Comparator 0      
  .word  Default_Handler                     // Analog Comparator 1      
  .word  Default_Handler                     // Analog Comparator 2      
  .word  Default_Handler                     // System Control (PLL, OSC,
  .word  Default_Handler                     // FLASH Control            
  .word  Default_Handler                     // GPIO Port F              
  .word  Default_Handler                     // GPIO Port G              
  .word  Default_Handler                     // GPIO Port H              
  .word  Default_Handler                     // UART2 Rx and Tx          
  .word  Default_Handler                     // SSI1 Rx and Tx           
  .word  Default_Handler                     // Timer 3 subtimer A       
  .word  Default_Handler                     // Timer 3 subtimer B       
  .word  Default_Handler                     // I2C1 Master and Slave    
  .word  Default_Handler                     // Quadrature Encoder 1     
  .word  Default_Handler                     // CAN0                     
  .word  Default_Handler                     // CAN1                     
  .word  Default_Handler                     // CAN2                     
  .word  luminaryif_isr                            // Ethernet              
  .word  Default_Handler                     // Hibernate                
  .word  Default_Handler                     // USB0                     
  .word  Default_Handler                     // PWM Generator 3          
  .word  Default_Handler                     // uDMA Software Transfer   
  .word  Default_Handler                       // uDMA Error               
