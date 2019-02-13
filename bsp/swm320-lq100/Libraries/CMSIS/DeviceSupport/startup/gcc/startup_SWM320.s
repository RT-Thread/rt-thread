
  .syntax unified
  .cpu cortex-m4
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
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

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
  ldr   sp, =_estack    		 /* set stack pointer */

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
  bl  entry
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b  Infinite_Loop
    .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
    .section  .isr_vector,"a",%progbits
    .type  g_pfnVectors, %object
    .size  g_pfnVectors, .-g_pfnVectors
    
g_pfnVectors:
    .word  _estack
    .word  Reset_Handler
    .word  NMI_Handler
    .word  HardFault_Handler
    .word  MemManage_Handler
    .word  BusFault_Handler
    .word  UsageFault_Handler
    .word  0
    .word  0
    .word  0
    .word  0
    .word  SVC_Handler
    .word  DebugMon_Handler
    .word  0
    .word  PendSV_Handler
    .word  SysTick_Handler
  
    /* External Interrupts */
    .word     GPIOA0_Handler
    .word     GPIOA1_Handler
    .word     GPIOA2_Handler
    .word     GPIOA3_Handler
    .word     GPIOA4_Handler
    .word     GPIOA5_Handler
    .word     GPIOA6_Handler
    .word     GPIOA7_Handler
    .word     GPIOB0_Handler
    .word     GPIOB1_Handler
    .word     GPIOB2_Handler
    .word     GPIOB3_Handler
    .word     GPIOB4_Handler
    .word     GPIOB5_Handler
    .word     GPIOB6_Handler
    .word     GPIOB7_Handler
    .word     GPIOC0_Handler
    .word     GPIOC1_Handler
    .word     GPIOC2_Handler
    .word     GPIOC3_Handler
    .word     GPIOC4_Handler
    .word     GPIOC5_Handler
    .word     GPIOC6_Handler
    .word     GPIOC7_Handler                                 
    .word     GPIOM0_Handler
    .word     GPIOM1_Handler
    .word     GPIOM2_Handler
    .word     GPIOM3_Handler
    .word     GPIOM4_Handler
    .word     GPIOM5_Handler
    .word     GPIOM6_Handler
    .word     GPIOM7_Handler                                            
    .word     DMA_Handler
    .word     LCD_Handler
    .word     NORFLC_Handler
    .word     CAN_Handler
    .word     PULSE_Handler
    .word     WDT_Handler
    .word     PWM_Handler
    .word     UART0_Handler
    .word     UART1_Handler
    .word     UART2_Handler
    .word     UART3_Handler
    .word     0
    .word     I2C0_Handler
    .word     I2C1_Handler
    .word     SPI0_Handler
    .word     ADC0_Handler
    .word     RTC_Handler
    .word     ANAC_Handler
    .word     SDIO_Handler
    .word     GPIOA_Handler
    .word     GPIOB_Handler
    .word     GPIOC_Handler
    .word     GPIOM_Handler
    .word     GPION_Handler
    .word     GPIOP_Handler
    .word     ADC1_Handler
    .word     FPU_Handler
    .word     SPI1_Handler
    .word     TIMR0_Handler
    .word     TIMR1_Handler
    .word     TIMR2_Handler
    .word     TIMR3_Handler
    .word     TIMR4_Handler
    .word     TIMR5_Handler  
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
* 
*******************************************************************************/
    .weak      NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak      HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak      MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler

    .weak      BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler

    .weak      UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler

    .weak      SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak      DebugMon_Handler
    .thumb_set DebugMon_Handler,Default_Handler

    .weak      PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak      SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler              

    .weak      GPIOA0_Handler                   
    .thumb_set GPIOA0_Handler,Default_Handler      

    .weak      GPIOA1_Handler      
    .thumb_set GPIOA1_Handler,Default_Handler

    .weak      GPIOA2_Handler            
    .thumb_set GPIOA2_Handler,Default_Handler

    .weak      GPIOA3_Handler                  
    .thumb_set GPIOA3_Handler,Default_Handler

    .weak      GPIOA4_Handler         
    .thumb_set GPIOA4_Handler,Default_Handler

    .weak      GPIOA5_Handler      
    .thumb_set GPIOA5_Handler,Default_Handler

    .weak      GPIOA6_Handler         
    .thumb_set GPIOA6_Handler,Default_Handler

    .weak      GPIOA7_Handler         
    .thumb_set GPIOA7_Handler,Default_Handler

    .weak      GPIOB0_Handler         
    .thumb_set GPIOB0_Handler,Default_Handler 

    .weak      GPIOB1_Handler         
    .thumb_set GPIOB1_Handler,Default_Handler

    .weak      GPIOB2_Handler         
    .thumb_set GPIOB2_Handler,Default_Handler

    .weak      GPIOB3_Handler               
    .thumb_set GPIOB3_Handler,Default_Handler

    .weak      GPIOB4_Handler               
    .thumb_set GPIOB4_Handler,Default_Handler

    .weak      GPIOB5_Handler               
    .thumb_set GPIOB5_Handler,Default_Handler

    .weak      GPIOB6_Handler               
    .thumb_set GPIOB6_Handler,Default_Handler 

    .weak      GPIOB7_Handler              
    .thumb_set GPIOB7_Handler,Default_Handler

    .weak      GPIOC0_Handler               
    .thumb_set GPIOC0_Handler,Default_Handler

    .weak      GPIOC1_Handler               
    .thumb_set GPIOC1_Handler,Default_Handler

    .weak      GPIOC2_Handler      
    .thumb_set GPIOC2_Handler,Default_Handler

    .weak      GPIOC3_Handler   
    .thumb_set GPIOC3_Handler,Default_Handler

    .weak      GPIOC4_Handler            
    .thumb_set GPIOC4_Handler,Default_Handler

    .weak      GPIOC5_Handler            
    .thumb_set GPIOC5_Handler,Default_Handler

    .weak      GPIOC6_Handler      
    .thumb_set GPIOC6_Handler,Default_Handler

    .weak      GPIOC7_Handler   
    .thumb_set GPIOC7_Handler,Default_Handler

    .weak      GPIOM0_Handler            
    .thumb_set GPIOM0_Handler,Default_Handler

    .weak      GPIOM1_Handler            
    .thumb_set GPIOM1_Handler,Default_Handler

    .weak      GPIOM2_Handler            
    .thumb_set GPIOM2_Handler,Default_Handler

    .weak      GPIOM3_Handler   
    .thumb_set GPIOM3_Handler,Default_Handler

    .weak      GPIOM4_Handler   
    .thumb_set GPIOM4_Handler,Default_Handler

    .weak      GPIOM5_Handler   
    .thumb_set GPIOM5_Handler,Default_Handler

    .weak      GPIOM6_Handler   
    .thumb_set GPIOM6_Handler,Default_Handler
        
    .weak      GPIOM7_Handler            
    .thumb_set GPIOM7_Handler,Default_Handler

    .weak      DMA_Handler            
    .thumb_set DMA_Handler,Default_Handler

    .weak      LCD_Handler      
    .thumb_set LCD_Handler,Default_Handler

    .weak      NORFLC_Handler      
    .thumb_set NORFLC_Handler,Default_Handler
                
    .weak      CAN_Handler               
    .thumb_set CAN_Handler,Default_Handler

    .weak      PULSE_Handler               
    .thumb_set PULSE_Handler,Default_Handler

    .weak      WDT_Handler         
    .thumb_set WDT_Handler,Default_Handler

    .weak      PWM_Handler               
    .thumb_set PWM_Handler,Default_Handler

    .weak      UART0_Handler            
    .thumb_set UART0_Handler,Default_Handler

    .weak      UART1_Handler            
    .thumb_set UART1_Handler,Default_Handler

    .weak      UART2_Handler            
    .thumb_set UART2_Handler,Default_Handler

    .weak      UART3_Handler               
    .thumb_set UART3_Handler,Default_Handler

    .weak      I2C0_Handler               
    .thumb_set I2C0_Handler,Default_Handler

    .weak      I2C1_Handler               
    .thumb_set I2C1_Handler,Default_Handler

    .weak      SPI0_Handler               
    .thumb_set SPI0_Handler,Default_Handler

    .weak      ADC0_Handler               
    .thumb_set ADC0_Handler,Default_Handler

    .weak      RTC_Handler      
    .thumb_set RTC_Handler,Default_Handler

    .weak      ANAC_Handler               
    .thumb_set ANAC_Handler,Default_Handler

    .weak      SDIO_Handler               
    .thumb_set SDIO_Handler,Default_Handler

    .weak      GPIOA_Handler               
    .thumb_set GPIOA_Handler,Default_Handler

    .weak      GPIOB_Handler      
    .thumb_set GPIOB_Handler,Default_Handler

    .weak      GPIOC_Handler   
    .thumb_set GPIOC_Handler,Default_Handler

    .weak      GPIOM_Handler   
    .thumb_set GPIOM_Handler,Default_Handler

    .weak      GPION_Handler                  
    .thumb_set GPION_Handler,Default_Handler  

    .weak      GPIOP_Handler                  
    .thumb_set GPIOP_Handler,Default_Handler 

    .weak      ADC1_Handler                  
    .thumb_set ADC1_Handler,Default_Handler 

    .weak      FPU_Handler                  
    .thumb_set FPU_Handler,Default_Handler 

    .weak      SPI1_Handler                  
    .thumb_set SPI1_Handler,Default_Handler 

    .weak      TIMR0_Handler                  
    .thumb_set TIMR0_Handler,Default_Handler 

    .weak      TIMR1_Handler                  
    .thumb_set TIMR1_Handler,Default_Handler 

    .weak      TIMR2_Handler                  
    .thumb_set TIMR2_Handler,Default_Handler 

    .weak      TIMR3_Handler                  
    .thumb_set TIMR3_Handler,Default_Handler 

    .weak      TIMR4_Handler                  
    .thumb_set TIMR4_Handler,Default_Handler 

    .weak      TIMR5_Handler                  
    .thumb_set TIMR5_Handler,Default_Handler 

