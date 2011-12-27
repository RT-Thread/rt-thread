/**************************************************************************//**
 * @file
 * @brief CMSIS Compatible EFM32 startup file in C for IAR EWARM
 * @author Energy Micro AS
 * @version 2.3.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2011 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#pragma language=extended
#pragma segment="CSTACK"

/* IAR start function */
extern void __iar_program_start(void);
/* CMSIS init function */
extern void SystemInit(void);

/* Auto defined by linker */
extern unsigned char CSTACK$$Limit; 

__weak void Reset_Handler(void)
{
  SystemInit();
  __iar_program_start();
}

__weak void NMI_Handler(void)
{
  while(1);
}

__weak void HardFault_Handler(void)
{
  while(1);
}

__weak void MemManage_Handler(void)
{
  while(1);
}

__weak void BusFault_Handler(void)
{
  while(1);
}

__weak void UsageFault_Handler(void)
{
  while(1);
}

__weak void SVC_Handler(void)
{
  while(1);
}

__weak void DebugMon_Handler(void)
{
  while(1);
}

__weak void PendSV_Handler(void)
{
  while(1);
}

__weak void SysTick_Handler(void)
{
  while(1);
}

__weak void DMA_IRQHandler(void)
{
  while(1);
}

__weak void GPIO_EVEN_IRQHandler(void)
{
  while(1);
}

__weak void TIMER0_IRQHandler(void)
{
  while(1);
}

__weak void USART0_RX_IRQHandler(void)
{
  while(1);
}

__weak void USART0_TX_IRQHandler(void)
{
  while(1);
}

__weak void ACMP0_IRQHandler(void)
{
  while(1);
}

__weak void ADC0_IRQHandler(void)
{
  while(1);
}

__weak void DAC0_IRQHandler(void)
{
  while(1);
}

__weak void I2C0_IRQHandler(void)
{
  while(1);
}

__weak void GPIO_ODD_IRQHandler(void)
{
  while(1);
}

__weak void TIMER1_IRQHandler(void)
{
  while(1);
}

__weak void USART1_RX_IRQHandler(void)
{
  while(1);
}

__weak void USART1_TX_IRQHandler(void)
{
  while(1);
}

__weak void LESENSE_IRQHandler(void)
{
  while(1);
}

__weak void LEUART0_IRQHandler(void)
{
  while(1);
}

__weak void LETIMER0_IRQHandler(void)
{
  while(1);
}

__weak void PCNT0_IRQHandler(void)
{
  while(1);
}

__weak void RTC_IRQHandler(void)
{
  while(1);
}

__weak void CMU_IRQHandler(void)
{
  while(1);
}

__weak void VCMP_IRQHandler(void)
{
  while(1);
}

__weak void LCD_IRQHandler(void)
{
  while(1);
}

__weak void MSC_IRQHandler(void)
{
  while(1);
}

__weak void AES_IRQHandler(void)
{
  while(1);
}


/* With IAR, the CSTACK is defined via project options settings */
#pragma data_alignment=256
#pragma location = ".intvec"
const void * const __vector_table[]=  {
    &CSTACK$$Limit,
    (void *) Reset_Handler,           /*  1 - Reset (start instruction) */
    (void *) NMI_Handler,             /*  2 - NMI */
    (void *) HardFault_Handler,       /*  3 - HardFault */
    (void *) MemManage_Handler,
    (void *) BusFault_Handler,
    (void *) UsageFault_Handler,
    (void *) 0,
    (void *) 0,
    (void *) 0,
    (void *) 0,
    (void *) SVC_Handler,
    (void *) DebugMon_Handler,
    (void *) 0,
    (void *) PendSV_Handler,
    (void *) SysTick_Handler,
    (void *) DMA_IRQHandler,  /* 0 - DMA */
    (void *) GPIO_EVEN_IRQHandler,  /* 1 - GPIO_EVEN */
    (void *) TIMER0_IRQHandler,  /* 2 - TIMER0 */
    (void *) USART0_RX_IRQHandler,  /* 3 - USART0_RX */
    (void *) USART0_TX_IRQHandler,  /* 4 - USART0_TX */
    (void *) ACMP0_IRQHandler,  /* 5 - ACMP0 */
    (void *) ADC0_IRQHandler,  /* 6 - ADC0 */
    (void *) DAC0_IRQHandler,  /* 7 - DAC0 */
    (void *) I2C0_IRQHandler,  /* 8 - I2C0 */
    (void *) GPIO_ODD_IRQHandler,  /* 9 - GPIO_ODD */
    (void *) TIMER1_IRQHandler,  /* 10 - TIMER1 */
    (void *) USART1_RX_IRQHandler,  /* 11 - USART1_RX */
    (void *) USART1_TX_IRQHandler,  /* 12 - USART1_TX */
    (void *) LESENSE_IRQHandler,  /* 13 - LESENSE */
    (void *) LEUART0_IRQHandler,  /* 14 - LEUART0 */
    (void *) LETIMER0_IRQHandler,  /* 15 - LETIMER0 */
    (void *) PCNT0_IRQHandler,  /* 16 - PCNT0 */
    (void *) RTC_IRQHandler,  /* 17 - RTC */
    (void *) CMU_IRQHandler,  /* 18 - CMU */
    (void *) VCMP_IRQHandler,  /* 19 - VCMP */
    (void *) LCD_IRQHandler,  /* 20 - LCD */
    (void *) MSC_IRQHandler,  /* 21 - MSC */
    (void *) AES_IRQHandler,  /* 22 - AES */

};
