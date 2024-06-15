# define LREG lw
# define SREG sw
# define REGBYTES 4

// <<< Use Configuration Wizard in Context Menu >>>

#define MSTATUS_PRV1 0x1880

.global __initial_sp

// <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:4>
// <i> Config the stack size for the application
#define		StackSize		0x400


.section .app_stack,"aw",@nobits
.align 2
Stack_Mem:
.space StackSize
__initial_sp:


// <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// <i> Config the heap size for the application
#define		HeapSize		0x200

.global __heap_start
.global __heap_end
.section .bss,"aw",@nobits
.align 2
Heap_Mem:
__heap_start:
.space HeapSize
__heap_end:


.section .vectors, "aw", @progbits
    .align  6
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:	                                   //#totally 0~63 entries                                                                                
    .rept   3                                    //                                                                                            
	.long   0                                  //                                                                                            
	.endr                                      //                                                                                            
	.long   SW_handler          //     ##3                                                                                        
  .rept   3                                    //                                                                                                
	.long   0                                  //                                                                                                
	.endr                                      //                                                                                                
	.long   CLINT_Handler                      //     ##7                                                                                        
	.rept   3                                  //                                                                                                
	.long   0                                  //     
	.endr                                      //     
	.long   MACHINE_MODE_EXTERNAL_Handler      //     ##11 no used
	.rept   4                                  //     ##12~15 reserved
	.long   0                                  //
	.endr                                      //

/* External interrupts */
//##------------------------------------------------------------	
	.long   WWDT_Handler                       //     ##16 0    
	.long   IWDT_Handler                       //     ##17 1    
	.long   LVD_Handler                        //     ##18 2    
	.long   CSU_Handler                        //     ##19 3    
	.long   CMU_Handler                        //     ##20 4    
	.long   EXTI0_3_Handler                    //     ##21 5    
	.long   EXTI4_7_Handler                    //     ##22 6    
	.long   EXTI8_11_Handler                   //     ##23 7    
	.long   EXTI12_15_Handler                  //     ##24 8    
	.long   DMA_Handler                        //     ##25 9    
	.long   0                                  //     ##26 10   
	.long   USB_Handler                        //     ##27 11   
	.long   ADC_Handler                        //     ##28 12   
	.long   AD16C4T_UP_TRIG_COM_Handler        //     ##29 13   
	.long   AD16C4T_CC_Handler                 //     ##30 14   
	.long   BSTIM0_Handler                     //     ##31 15   
	.long   0                                  //     ##   16   
	.long   GPTIMB0_Handler                    //     ##33 17   
	.long   GPTIMB1_Handler                    //     ##34 18   
	.long   GPTIMB2_Handler                    //     ##35 19   
	.long   0                                  //     ##   20   
	.long   AD16C4T_Handler                    //     ##37 21   
	.long   0                                  //     ##   22   
	.long   I2C0_Handler                       //     ##39 23   
	.long   I2C1_Handler                       //     ##40 24   
	.long   SPI0_I2S0_Handler                  //     ##41 25   
	.long   SPI1_I2S1_Handler                  //     ##42 26   
	.long   EUART0_Handler                     //     ##43 27   
	.long   EUART1_Handler                     //     ##44 28   
	.long   CUART0_Handler                     //     ##45 29   
	.long   CUART1_Handler                     //     ##46 30   
	.long   CUART2_Handler                     //     ##47 31   
//##---------------------------------------------------

/*
 * For importing variable or functions from other c or assemble files.
 */
.global __main
.global handle_trap

  .section ".text.init"
  .globl Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

.option push
.option norelax
    la      gp, __global_pointer$
.option pop

    la      a0, Default_Handler                      
    ori     a0, a0, 3
    csrw    mtvec, a0

    la      a0, __Vectors
    csrw    mtvt, a0
	
    la      sp, g_top_irqstack

    /* Load data section */
    la      a0, __erodata
    la      a1, __data_start__
    la      a2, __data_end__
    bgeu    a1, a2, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:

    /* Clear bss section */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, (a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:
    jal     entry

    .size   Reset_Handler, . - Reset_Handler

  .align  6
  .weak   Default_Handler
  .global Default_Handler
  .type   Default_Handler, %function
Default_Handler:
  addi sp, sp, -272

  SREG x1, 1*REGBYTES(sp)
  SREG x2, 2*REGBYTES(sp)
  SREG x3, 3*REGBYTES(sp)
  SREG x4, 4*REGBYTES(sp)
  SREG x5, 5*REGBYTES(sp)
  SREG x6, 6*REGBYTES(sp)
  SREG x7, 7*REGBYTES(sp)
  SREG x8, 8*REGBYTES(sp)
  SREG x9, 9*REGBYTES(sp)
  SREG x10, 10*REGBYTES(sp)
  SREG x11, 11*REGBYTES(sp)
  SREG x12, 12*REGBYTES(sp)
  SREG x13, 13*REGBYTES(sp)
  SREG x14, 14*REGBYTES(sp)
  SREG x15, 15*REGBYTES(sp)

  csrr a0, mcause
  csrr a1, mepc
  mv a2, sp
  jal handle_trap
  csrw mepc, a0

  # Remain in M-mode after eret
  li t0, MSTATUS_PRV1
  csrs mstatus, t0

  LREG x1, 1*REGBYTES(sp)
  LREG x2, 2*REGBYTES(sp)
  LREG x3, 3*REGBYTES(sp)
  LREG x4, 4*REGBYTES(sp)
  LREG x5, 5*REGBYTES(sp)
  LREG x6, 6*REGBYTES(sp)
  LREG x7, 7*REGBYTES(sp)
  LREG x8, 8*REGBYTES(sp)
  LREG x9, 9*REGBYTES(sp)
  LREG x10, 10*REGBYTES(sp)
  LREG x11, 11*REGBYTES(sp)
  LREG x12, 12*REGBYTES(sp)
  LREG x13, 13*REGBYTES(sp)
  LREG x14, 14*REGBYTES(sp)
  LREG x15, 15*REGBYTES(sp)

  addi sp, sp, 272
  mret

  .weak  SW_handler
  .globl SW_handler
  .type  SW_handler, %function
SW_handler:

  .weak  CLINT_Handler
  .globl CLINT_Handler
  .type  CLINT_Handler, %function
CLINT_Handler:

  .weak  MACHINE_MODE_EXTERNAL_Handler
  .globl MACHINE_MODE_EXTERNAL_Handler
  .type  MACHINE_MODE_EXTERNAL_Handler, %function
MACHINE_MODE_EXTERNAL_Handler:

  .weak  WWDT_Handler
  .globl WWDT_Handler
  .type  WWDT_Handler, %function
WWDT_Handler:

  .weak  IWDT_Handler
  .globl IWDT_Handler
  .type  IWDT_Handler, %function
IWDT_Handler:

  .weak  LVD_Handler
  .globl LVD_Handler
  .type  LVD_Handler, %function
LVD_Handler:

  .weak  CSU_Handler
  .globl CSU_Handler
  .type  CSU_Handler, %function
CSU_Handler:

  .weak  CMU_Handler
  .globl CMU_Handler
  .type  CMU_Handler, %function
CMU_Handler:

  .weak  EXTI0_3_Handler
  .globl EXTI0_3_Handler
  .type  EXTI0_3_Handler, %function
EXTI0_3_Handler:

  .weak  EXTI4_7_Handler
  .globl EXTI4_7_Handler
  .type  EXTI4_7_Handler, %function
EXTI4_7_Handler:

  .weak  EXTI8_11_Handler
  .globl EXTI8_11_Handler
  .type  EXTI8_11_Handler, %function
EXTI8_11_Handler:

  .weak  EXTI12_15_Handler
  .globl EXTI12_15_Handler
  .type  EXTI12_15_Handler, %function
EXTI12_15_Handler:

  .weak  DMA_Handler
  .globl DMA_Handler
  .type  DMA_Handler, %function
DMA_Handler:

  .weak  USB_Handler
  .globl USB_Handler
  .type  USB_Handler, %function
USB_Handler:

  .weak ADC_Handler
  .globl ADC_Handler
  .type  ADC_Handler, %function
ADC_Handler:

  .weak  AD16C4T_UP_TRIG_COM_Handler
  .globl AD16C4T_UP_TRIG_COM_Handler
  .type  AD16C4T_UP_TRIG_COM_Handler, %function
AD16C4T_UP_TRIG_COM_Handler:

  .weak  AD16C4T_CC_Handler
  .globl AD16C4T_CC_Handler
  .type  AD16C4T_CC_Handler, %function
AD16C4T_CC_Handler:

  .weak  BSTIM0_Handler
  .globl BSTIM0_Handler
  .type  BSTIM0_Handler, %function
BSTIM0_Handler:

  .weak  GPTIMB0_Handler
  .globl GPTIMB0_Handler
  .type  GPTIMB0_Handler, %function
GPTIMB0_Handler:

  .weak  GPTIMB1_Handler
  .globl GPTIMB1_Handler
  .type  GPTIMB1_Handler, %function
GPTIMB1_Handler:

  .weak  GPTIMB2_Handler
  .globl GPTIMB2_Handler
  .type  GPTIMB2_Handler, %function
GPTIMB2_Handler:

  .weak  AD16C4T_Handler
  .globl AD16C4T_Handler
  .type  AD16C4T_Handler, %function
AD16C4T_Handler:

  .weak  I2C0_Handler
  .globl I2C0_Handler
  .type  I2C0_Handler, %function
I2C0_Handler:

  .weak  I2C1_Handler
  .globl I2C1_Handler
  .type  I2C1_Handler, %function
I2C1_Handler:

  .weak  SPI0_I2S0_Handler
  .globl SPI0_I2S0_Handler
  .type  SPI0_I2S0_Handler, %function
SPI0_I2S0_Handler:

  .weak  SPI1_I2S1_Handler
  .globl SPI1_I2S1_Handler
  .type  SPI1_I2S1_Handler, %function
SPI1_I2S1_Handler:

  .weak  EUART0_Handler
  .globl EUART0_Handler
  .type  EUART0_Handler, %function
EUART0_Handler:

  .weak  EUART1_Handler
  .globl EUART1_Handler
  .type  EUART1_Handler, %function
EUART1_Handler:

  .weak  CUART0_Handler
  .globl CUART0_Handler
  .type  CUART0_Handler, %function
CUART0_Handler:

  .weak  CUART1_Handler
  .globl CUART1_Handler
  .type  CUART1_Handler, %function
CUART1_Handler:

  .weak  CUART2_Handler
  .globl CUART2_Handler
  .type  CUART2_Handler, %function
CUART2_Handler:

__exit:
    j      __exit

//##---------------------------------------------------
.section .bss

    .align  3
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space  StackSize            //CONFIG_ARCH_INTERRUPTSTACK
g_top_irqstack:
