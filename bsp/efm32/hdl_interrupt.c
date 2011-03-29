/******************************************************************//**
 * @file 		hdl_interrupt.c
 * @brief 	USART driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-29	onelife		Initial creation for EFM32
 *********************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
efm32_irq_hook_t dmaCbTable[DMA_CHAN_COUNT * 2]	= {RT_NULL};
efm32_irq_hook_t timerCbTable[TIMER_COUNT] 		= {RT_NULL};
efm32_irq_hook_t rtcCbTable[RTC_COUNT] 			= {RT_NULL};
efm32_irq_hook_t gpioCbTable[16] 				= {RT_NULL};
efm32_irq_hook_t acmpCbTable[ACMP_COUNT] 		= {RT_NULL};
efm32_irq_hook_t usartCbTable[USART_COUNT * 2] 	= {RT_NULL};
efm32_irq_hook_t iicCbTable[I2C_COUNT] 			= {RT_NULL};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************//**
* @brief
*	NMI exception handler
*
* @details
*
* @note
*********************************************************************/
void NMI_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[NMI_Handler: NOP]\n");
#endif
}

/******************************************************************//**
* @brief
*	Memory manage exception handler
*
* @details
*
* @note
*********************************************************************/
void MemManage_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[MemManage_Handler: infinite loop]\n");
#endif
	while (1);
}

/******************************************************************//**
* @brief
*	Bus fault exception handler
*
* @details
*
* @note
*********************************************************************/
void BusFault_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[BusFault_Handler: infinite loop]\n");
#endif
	while (1);
}

/******************************************************************//**
* @brief
*	Usage fault exception handler
*
* @details
*
* @note
*********************************************************************/
void UsageFault_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[UsageFault_Handler: infinite loop]\n");
#endif
	while (1);
}

/******************************************************************//**
* @brief
*	Supervisor call exception handler
*
* @details
*
* @note
*********************************************************************/
void SVC_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[SVC_Handler: NOP]\n");
#endif
}

/******************************************************************//**
* @brief
*	 Debug monitor exception handler
*
* @details
*
* @note
*********************************************************************/
void DebugMon_Handler(void)
{
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("[DebugMon_Handler: NOP]\n");
#endif
}

/******************************************************************//**
 * @brief
 * 	System tick timer interrupt handler
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
void rt_hw_timer_handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

/**********************************************************************
 *                 STM32F10x Peripherals Interrupt Handlers 
 *  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the 
 *  available peripheral interrupt handler's name please refer to the startup 
 *  file (startup_stm32f10x_xx.s). 
/*********************************************************************/

/******************************************************************//**
 * @brief
 * 	Common DMA interrupt handler
 *
 * @details
 * 	
 * @note
 *
 *********************************************************************/
void DMA_IRQHandler_All(unsigned int channel, bool primary, void *user)
{
    /* enter interrupt */
    rt_interrupt_enter();

	/* invoke callback function */
	if (dmaCbTable[channel].cbFunc != RT_NULL)
	{
		(dmaCbTable[channel].cbFunc)(dmaCbTable[channel].userPtr);
	}

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common Timer1 interrupt handler
 *
 * @details
 * 	This function handles Timer1 counter overflow interrupt request
 *
 * @note
 *
 *********************************************************************/
void TIMER1_IRQHandler(void)
{
	if (TIMER1->IF & TIMER_IF_OF)
	{
		/* invoke callback function */
		if (timerCbTable[1].cbFunc != RT_NULL)
		{
			(timerCbTable[1].cbFunc)(timerCbTable[1].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(TIMER1->IFC), _TIMER_IF_OF_SHIFT, 0x1UL);
	}
}

/******************************************************************//**
 * @brief
 * 	Common Timer2 interrupt handler
 *
 * @details
 * 	This function handles Timer2 counter overflow interrupt request
 *
 * @note
 *
 *********************************************************************/
void TIMER2_IRQHandler(void)
{
	if (TIMER2->IF & TIMER_IF_OF)
	{
		/* invoke callback function */
		if (timerCbTable[2].cbFunc != RT_NULL)
		{
			(timerCbTable[2].cbFunc)(timerCbTable[2].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(TIMER2->IFC), _TIMER_IF_OF_SHIFT, 0x1UL);
	}
}

/******************************************************************//**
 * @brief
 * 	Common RTC interrupt handler
 *
 * @details
 * 	This function handles RTC counter overflow interrupt request
 *
 * @note
 *
 *********************************************************************/
void RTC_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

	if (RTC->IF & RTC_IF_OF)
	{
		/* invoke callback function */
		if (rtcCbTable[0].cbFunc != RT_NULL)
		{
			(rtcCbTable[0].cbFunc)(rtcCbTable[0].userPtr);
		}
	}
	
    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common even number GPIO interrupt handler
 *
 * @details
 * 	
 * @note
 *
 *********************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
	rt_uint16_t flag, n;
	
    /* enter interrupt */
    rt_interrupt_enter();

	 /* invoke callback function */
	flag = (rt_uint16_t)(GPIO->IF & 0xFFFF);
	for ( n = 0; flag > 0; flag = flag >> 2, n = n + 2)
	{
		if ((flag & 0x0001) && (gpioCbTable[n].cbFunc != RT_NULL))
		{
			(gpioCbTable[n].cbFunc)(gpioCbTable[n].userPtr);
		}
	}

	/* clear interrupt */
	GPIO->IFC = 0x5555UL;

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common odd number GPIO interrupt handler
 *
 * @details
 * 	
 * @note
 *
 *********************************************************************/
void GPIO_ODD_IRQHandler(void)
{
	rt_uint16_t flag, n;
	
    /* enter interrupt */
    rt_interrupt_enter();

	 /* invoke callback function */
	flag = (rt_uint16_t)(GPIO->IF & 0xFFFF) >> 1;
	for ( n = 1; flag > 0; flag = flag >> 2, n = n + 2)
	{
		if ((flag & 0x0001) && (gpioCbTable[n].cbFunc != RT_NULL))
		{
			(gpioCbTable[n].cbFunc)(gpioCbTable[n].userPtr);
		}
	}

	/* clear interrupt */
	GPIO->IFC = 0xAAAAUL;

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common ACMP interrupt handler
 *
 * @details
 * 	This function handles ACMP edge trigger interrupt request
 *
 * @note
 *
 *********************************************************************/
void ACMP0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

	if (ACMP0->IF & ACMP_IF_EDGE)
	{
		/* invoke callback function */
		if (acmpCbTable[0].cbFunc != RT_NULL)
		{
			(acmpCbTable[0].cbFunc)(acmpCbTable[0].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(ACMP0->IFC), _ACMP_IF_EDGE_SHIFT, 0x1UL);
	}

	if (ACMP1->IF & ACMP_IF_EDGE)
	{
		/* invoke callback function */
		if (acmpCbTable[1].cbFunc != RT_NULL)
		{
			(acmpCbTable[1].cbFunc)(acmpCbTable[1].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(ACMP1->IFC), _ACMP_IF_EDGE_SHIFT, 0x1UL);
	}

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common USART0 TX interrupt handler
 *
 * @details
 * 	This function handles USART0 TX complete interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART0_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

	if (USART0->IF & USART_IF_TXC)
	{
		/* invoke callback function */
		if (usartCbTable[0].cbFunc != RT_NULL)
		{
			(usartCbTable[0].cbFunc)(usartCbTable[0].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(USART0->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
	}

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common USART0 RX interrupt handler
 *
 * @details
 * 	This function handles USART0 RX data valid interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART0_RX_IRQHandler(void)
{
	if (USART0->IF & USART_IF_RXDATAV)
	{
		/* invoke callback function */
		if (usartCbTable[1].cbFunc != RT_NULL)
		{
			(usartCbTable[1].cbFunc)(usartCbTable[1].userPtr);
		}
	}
}

/******************************************************************//**
 * @brief
 * 	Common USART1 TX interrupt handler
 *
 * @details
 * 	This function handles USART1 TX complete interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART1_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

	if (USART1->IF & USART_IF_TXC)
	{
		/* invoke callback function */
		if (usartCbTable[2].cbFunc != RT_NULL)
		{
			(usartCbTable[2].cbFunc)(usartCbTable[2].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(USART1->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
	}

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common USART1 RX interrupt handler
 *
 * @details
 * 	This function handles USART1 RX data valid interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART1_RX_IRQHandler(void)
{
	if (USART1->IF & USART_IF_RXDATAV)
	{
		/* invoke callback function */
		if (usartCbTable[3].cbFunc != RT_NULL)
		{
			(usartCbTable[3].cbFunc)(usartCbTable[3].userPtr);
		}
	}
}

/******************************************************************//**
 * @brief
 * 	Common USART2 TX interrupt handler
 *
 * @details
 * 	This function handles USART2 TX complete interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART2_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

	if (USART2->IF & USART_IF_TXC)
	{
		/* invoke callback function */
		if (usartCbTable[4].cbFunc != RT_NULL)
		{
			(usartCbTable[4].cbFunc)(usartCbTable[4].userPtr);
		}

		/* clear interrupt */
		BITBAND_Peripheral(&(USART2->IFC), _USART_IF_TXC_SHIFT, 0x1UL);
	}

    /* leave interrupt */
    rt_interrupt_leave();
}

/******************************************************************//**
 * @brief
 * 	Common USART2 RX interrupt handler
 *
 * @details
 * 	This function handles USART2 RX data valid interrupt request
 *
 * @note
 *
 *********************************************************************/
void USART2_RX_IRQHandler(void)
{
	if (USART2->IF & USART_IF_RXDATAV)
	{
		/* invoke callback function */
		if (usartCbTable[5].cbFunc != RT_NULL)
		{
			(usartCbTable[5].cbFunc)(usartCbTable[5].userPtr);
		}
	}
}

/******************************************************************//**
 * @brief
 * 	Common IIC0 interrupt handler
 *
 * @details
 * 	This function handles IIC0 slave mode interrupt requests
 *
 * @note
 *
 *********************************************************************/
void I2C0_IRQHandler(void)
{
	if ((I2C0->IF & I2C_IF_ADDR) || \
		(I2C0->IF & I2C_IF_RXDATAV) || \
		(I2C0->IF & I2C_IF_SSTOP))
	{
		/* invoke callback function */
		if (iicCbTable[0].cbFunc != RT_NULL)
		{
			(iicCbTable[0].cbFunc)(iicCbTable[0].userPtr);
		}
	}

	I2C_IntClear(I2C0, I2C_IFC_ADDR | I2C_IFC_SSTOP);
}

/******************************************************************//**
 * @brief
 * 	EFM32 common interrupt handlers register function
 *
 * @details
 * 	
 * @note
 *
 *********************************************************************/
rt_err_t efm32_irq_hook_register(efm32_irq_hook_init_t *hook)
{
	switch (hook->type)
	{
	case efm32_irq_type_dma:
		dmaCbTable[hook->unit].cbFunc = hook->cbFunc;
		dmaCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_rtc:
		rtcCbTable[hook->unit].cbFunc = hook->cbFunc;
		rtcCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_timer:
		timerCbTable[hook->unit].cbFunc = hook->cbFunc;
		timerCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_gpio:
		gpioCbTable[hook->unit].cbFunc = hook->cbFunc;
		gpioCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_acmp:
		acmpCbTable[hook->unit].cbFunc = hook->cbFunc;
		acmpCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_usart:
		usartCbTable[hook->unit].cbFunc = hook->cbFunc;
		usartCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	case efm32_irq_type_iic:
		iicCbTable[hook->unit].cbFunc = hook->cbFunc;
		iicCbTable[hook->unit].userPtr = hook->userPtr;
		break;

	default:
		break;
	}
#ifdef RT_IRQHDL_DEBUG
	rt_kprintf("Hook Registered: type: %s, unit: %x, cbFunc: %x, userPtr: %x\n", \
		hook->type, hook->unit, hook->cbFunc, hook->userPtr);
#endif
}

/******************************************************************//**
 * @}
*********************************************************************/
