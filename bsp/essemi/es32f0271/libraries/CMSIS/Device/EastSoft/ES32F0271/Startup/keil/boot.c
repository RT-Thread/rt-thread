
//
// Boot (vectors) file for Cortex-M0 Integration Kit
//

#include <stdio.h>
#include <rt_misc.h>
#include <stdint.h>
#include "es32F0271_sub.h"

//
// Build a stand-alone image
//

#pragma import(__use_no_semihosting)


/*----------------------------------------------------------------------*/
/*--------------             Interrupt Handlers           --------------*/
/*----------------------------------------------------------------------*/
// The following functions are defined weakly to allow the user
// to override them at link time simply by declaring their own
// function of the same name.
//
// If no user function is provided, the weak function is used.
//
//------------------------------------ IRQ NMI Handler
__weak void NMI_Handler(void)
{
    while(1);
}
//------------------------------------ IRQ Hard Fault Handler
__weak void HardFault_Handler(void)
{
	//printf("Hard Fault\r\n");
    while(1);
}
//------------------------------------ IRQ SVCall Handler
__weak void SVC_Handler(void)
{
    while(1);
}
//------------------------------------ IRQ PendSV Handler
__weak void PendSV_Handler(void)
{
    while(1);
}
//------------------------------------ IRQ SysTick Handler
__weak void SysTick_Handler(void)
{
    while(1);
}
//------------------------------------ IRQ 31
__weak void USB_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 30
__weak void SUART12_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 29
__weak void UART3_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 28
__weak void UART2_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 27
__weak void UART1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 26
__weak void SPI2_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 25
__weak void SPI1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 24
__weak void I2C2_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 23
__weak void I2C1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 22
__weak void GPTIMC4_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 21
__weak void GPTIMC3_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 20
__weak void GPTIMC2_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 19
__weak void GPTIMC1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 18
__weak void GPTIMB3_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 17
__weak void GPTIMB2_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 16
__weak void GPTIMB1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 15
__weak void GPTIMA1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 14
__weak void BSTIM1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 13
__weak void ADTIM1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 12
__weak void ADC_COMP_IRQHandler(void)
{
   // while(1);
}
//------------------------------------ IRQ 11
__weak void DMA1_CH345_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 10
__weak void DMA1_CH12_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 9
__weak void DMA1_CH0_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 8
//------------------------------------ IRQ 7
__weak void EXTI_4to15_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 6
__weak void EXTI_2to3_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 5
__weak void EXTI_0to1_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 4
//------------------------------------ IRQ 3
__weak void WAKEUP_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 2
__weak void RTC_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 1
__weak void PVD_IRQHandler(void)
{
    while(1);
}
//------------------------------------ IRQ 0
__weak void WWDT_IRQHandler(void)
{
    while(1);
}


/*----------------------------------------------------------------------*/
/*--------------             Defined Handler              --------------*/
/*----------------------------------------------------------------------*/
__weak void Default_IRQHandler(void)
{
    while(1);
}

/*----------------------------------------------------------------------*/
/*--------------     Symbols defined in linker script          ---------*/ 
/*----------------------------------------------------------------------*/ 

extern void __main(void);

/*----------------------------------------------------------------------*/
/*--------------               Reset Handler              --------------*/
/*----------------------------------------------------------------------*/
void Reset_Handler(void)
{
    __main();
    while(1) {;} // In case main() fails
}

/*----------------------------------------------------------------------*/
/*--------------            Set up Vector Table           --------------*/
/*----------------------------------------------------------------------*/
typedef void (*const vect_t)(void) __irq;

vect_t __Vectors[]
__attribute__ ((section("vectors"))) = {
    (vect_t)(SRAM1_BASE+SRAMTOP),//(vect_t)(0x20000F80),     // Top of Stack - Allowing 4 words for DEBUGDRIVERDATA
    (vect_t)Reset_Handler,    // Reset Handler
    (vect_t)NMI_Handler,      // NMI Handler
    (vect_t)HardFault_Handler,// Hard Fault Handler
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    (vect_t)SVC_Handler,      // SVCall Handler
    0,                        // Reserved
    0,                        // Reserved
    (vect_t)PendSV_Handler,   // PendSV Handler
    (vect_t)SysTick_Handler,  // SysTick Handler
    /*----------External Exceptions---------------------------------------------*/
    // External Interrupts 0 - 31
    // These are essentially unused, so will all
    // take the same default handler if invoked.
    // External Interrupts
                                    //|=========================================|
                                    //| IRQ NO. | M621                          |
                                    //|-----------------------------------------|
    (vect_t)WWDT_IRQHandler,        //| 0       | WWDG          |               |
    (vect_t)PVD_IRQHandler,         //| 1       | PVD           | EXTI[20]      |
    (vect_t)RTC_IRQHandler,         //| 2       | RTC           |               |
    (vect_t)WAKEUP_IRQHandler,      //| 3       | WAKEUP        | EXTI[21]      |
    (vect_t)Default_IRQHandler,     //| 4       |               |               |
    (vect_t)EXTI_0to1_IRQHandler,   //| 5       | EXTI[1:0]     | GPIOx[1:0]    |
    (vect_t)EXTI_2to3_IRQHandler,   //| 6       | EXTI[3:2]     | GPIOx[3:2]    |
    (vect_t)EXTI_4to15_IRQHandler,  //| 7       | EXTI[15:4]    | GPIOx[15:4]   |
    (vect_t)Default_IRQHandler,     //| 8       |               |               |
    (vect_t)DMA1_CH0_IRQHandler,    //| 9       | DMA1_CH0      |               |
    (vect_t)DMA1_CH12_IRQHandler,   //| 10      | DMA1_CH12     |               |
    (vect_t)DMA1_CH345_IRQHandler,  //| 11      | DMA1_CH345    |               |
    (vect_t)ADC_COMP_IRQHandler,    //| 12      | ADC/COMP0-3   | EXTI[19:16]   |
    (vect_t)ADTIM1_IRQHandler,      //| 13      | ADTIM1        |               |
    (vect_t)BSTIM1_IRQHandler,      //| 14      | BSTIM1        |               |
    (vect_t)GPTIMA1_IRQHandler,     //| 15      | GPTIMA1       |               |
    (vect_t)GPTIMB1_IRQHandler,     //| 16      | GPTIMB1       |               |
    (vect_t)GPTIMB2_IRQHandler,     //| 17      | GPTIMB2       |               |
    (vect_t)GPTIMB3_IRQHandler,     //| 18      | GPTIMB3       |               |
    (vect_t)GPTIMC1_IRQHandler,     //| 19      | GPTIMC1       |               |
    (vect_t)GPTIMC2_IRQHandler,     //| 20      | GPTIMC2       |               |
    (vect_t)GPTIMC3_IRQHandler,     //| 21      | GPTIMC3       |               |
    (vect_t)GPTIMC4_IRQHandler,     //| 22      | GPTIMC4       |               |
    (vect_t)I2C1_IRQHandler,        //| 23      | I2C1          |               |
    (vect_t)I2C2_IRQHandler,        //| 24      | I2C2          |               |
    (vect_t)SPI1_IRQHandler,        //| 25      | SPI1          |               |
    (vect_t)SPI2_IRQHandler,        //| 26      | SPI2          |               |
    (vect_t)UART1_IRQHandler,       //| 27      | UART1         |               |
    (vect_t)UART2_IRQHandler,       //| 28      | UART2         |               |
    (vect_t)UART3_IRQHandler,       //| 29      | UART3         |               |
    (vect_t)SUART12_IRQHandler,     //| 30      | SUART1/2      |               |
    (vect_t)USB_IRQHandler          //| 31      | USB           |               |
                                    //==========================================|
};


/*----------------------------------------------------------------------*/
/*--------------       Set up initial stack and heap      --------------*/
/*----------------------------------------------------------------------*/
__value_in_regs struct __initial_stackheap
__user_initial_stackheap(unsigned hb, unsigned sb, unsigned hl, unsigned sl)
{
    struct __initial_stackheap s;
    
    s.heap_base   = hb;
    s.stack_base  = sb;
    s.heap_limit  = s.stack_base;
    s.stack_limit = s.heap_base;
    return s;
}

/*----------------------------------------------------------------------*/
/*------   Set test status bits in testbench when main() exits   -------*/
/*----------------------------------------------------------------------*/
void _sys_exit(int return_code)
{
    while(1);
}



