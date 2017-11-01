/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2013-11-15     bright       add RCC initial and print RCC freq function
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "usart.h"

/**
 * @addtogroup STM32
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

/**
* @brief  Inserts a delay time.
* @param  nCount: specifies the delay time length.
* @retval None
*/
static void Delay(__IO uint32_t nCount)
{
	/* Decrement nCount value */
	while (nCount != 0)
	{
		nCount--;
	}
}

/**
 * This RCC initial for system.
 * use HSI clock source and pll
 * HSI = 8; sysclk = 8/2 * 12 = 48MHZ
 * sysclk source is pllclk
 * AHB prescaler is 1, HCLK = SYSCKL = SystemCoreClock = 48MHZ
 */
static void RCC_Configuration(void)
{
	RCC_DeInit();
	/* setup HSI */
	RCC_HSICmd(ENABLE);
	/* Configure PLL source is HSI */
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	/* Configure SYSCLK source is PLL */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	/* Conigure AHB prescaler value is 1 */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	/* Delay for RCC setup */
	Delay(0x3FFFF);
	/* Update SystemCoreClock value from RCC configure */
	SystemCoreClockUpdate();
}

#ifdef PRINT_RCC_FREQ_INFO
/**
 * print RCC freq information
 *
 * for example:
 *
 * SYSCLK_Frequency is 48000000HZ
 * PCLK_Frequency is 48000000HZ
 * HCLK_Frequency is 48000000HZ
 * CECCLK_Frequency is 32786HZ
 * ADCCLK_Frequency is 14000000HZ
 * USART1CLK_Frequency is 48000000HZ
 * I2C1CLK_Frequency is 8000000HZ
 * SystemCoreClock is 48000000HZ
 *
 */
void print_rcc_freq_info(void)
{
	RCC_ClocksTypeDef RCC_ClockFreq;

	RCC_GetClocksFreq(&RCC_ClockFreq);

	rt_kprintf("\nSYSCLK_Frequency is %dHZ", RCC_ClockFreq.SYSCLK_Frequency);
	rt_kprintf("\nPCLK_Frequency is %dHZ", RCC_ClockFreq.PCLK_Frequency);
	rt_kprintf("\nHCLK_Frequency is %dHZ", RCC_ClockFreq.HCLK_Frequency);

	rt_kprintf("\nCECCLK_Frequency is %dHZ", RCC_ClockFreq.CECCLK_Frequency);
	rt_kprintf("\nADCCLK_Frequency is %dHZ", RCC_ClockFreq.ADCCLK_Frequency);
	rt_kprintf("\nUSART1CLK_Frequency is %dHZ", RCC_ClockFreq.USART1CLK_Frequency);
	rt_kprintf("\nI2C1CLK_Frequency is %dHZ", RCC_ClockFreq.I2C1CLK_Frequency);
	rt_kprintf("\nSystemCoreClock is %dHZ\n", SystemCoreClock);
}
#endif

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}
/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure the SysTick */
	RCC_Configuration();
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

	/* Initial usart deriver, and set console device */
	rt_hw_usart_init();
#ifdef RT_USING_CONSOLE
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
	/* Print RCC freq info */
#ifdef PRINT_RCC_FREQ_INFO
	print_rcc_freq_info();
#endif
	/* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
