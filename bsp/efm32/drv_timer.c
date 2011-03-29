/******************************************************************//**
 * @file 		drv_timer.c
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
 * 2011-01-18	onelife		Initial creation for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup efm32
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "drv_timer.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
#define TIMER_TopCalculate(p) \
		(p * (EFM32_HFXO_FREQUENCY / (1 << TMR_CFG_PRESCALER) / 1000))

/* Private variables ------------------------------------------------------------*/
#ifdef RT_USING_TIMER1
	static struct rt_device timer1_device;
#endif
#ifdef RT_USING_TIMER2
	static struct rt_device timer2_device;
#endif

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize Timer device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 *********************************************************************/
 static rt_err_t rt_hs_timer_init (rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_timer_device_t *timer;

	timer = (struct efm32_timer_device_t *)(dev->user_data);

	timer->hook.cbFunc = RT_NULL;
	timer->hook.userPtr = RT_NULL;

	return RT_EOK;
}

/******************************************************************//**
* @brief
*	Configure Timer device
*
* @details
*
* @note
*
* @param[in] dev
*	Pointer to device descriptor
*
* @param[in] cmd
*	Timer control command
*
* @param[in] args
*	Arguments
*
* @return
*	Error code
*********************************************************************/
static rt_err_t rt_hs_timer_control (
	rt_device_t 	dev, 
	rt_uint8_t 		cmd, 
	void 			*args)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_timer_device_t *timer;

	timer = (struct efm32_timer_device_t *)(dev->user_data);

	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* Suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		TIMER_Enable(timer->timer_device, false);
		break;

	case RT_DEVICE_CTRL_RESUME:
		/* Resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		TIMER_Enable(timer->timer_device, true);
		break;

	case RT_DEVICE_CTRL_TIMER_PERIOD:
		{
			/* change device setting */
			struct efm32_timer_control_t *control;
			rt_uint32_t running;

			control = (struct efm32_timer_control_t *)args;
			running = timer->timer_device->STATUS & 0x00000001;
			
			TIMER_Enable(timer->timer_device, false);
			timer->timer_device->CNT = _TIMER_CNT_RESETVALUE;
			TIMER_TopSet(timer->timer_device, TIMER_TopCalculate(control->period));
			timer->hook.cbFunc = control->hook.cbFunc;
			timer->hook.userPtr = control->hook.userPtr;
			if (running)
			{
				TIMER_Enable(timer->timer_device, true);
			}
		}
		break;
	}

	return RT_EOK;
}

/******************************************************************//**
* @brief
*	Register Timer device
*
* @details
*
* @note
*
* @param[in] device
*	Pointer to device descriptor
*
* @param[in] name
*	Device name
*
* @param[in] flag
*	Configuration flags
*
* @param[in] timer
*	Pointer to Timer device descriptor 
*
* @return
*	Error code
*********************************************************************/
rt_err_t rt_hw_timer_register(
	rt_device_t		device, 
	const char		*name, 
	rt_uint32_t		flag, 
	struct efm32_timer_device_t *timer)
{
	RT_ASSERT(device != RT_NULL);

	device->type 		= RT_Device_Class_Char; /* fixme: should be timer type*/
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_hs_timer_init;
	device->open		= RT_NULL;
	device->close		= RT_NULL;
	device->read 		= RT_NULL;
	device->write 		= RT_NULL;
	device->control 	= rt_hs_timer_control;
	device->user_data	= timer;

	/* register a character device */
	return rt_device_register(device, name, flag);
}

/******************************************************************//**
 * @brief
 *	Timer counter overflow interrupt handler
 *
 * @details
 *
 * @note
 *********************************************************************/
void rt_hw_timer_isr(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_timer_device_t *timer;

	timer = (struct efm32_timer_device_t *)(dev->user_data);

	if (timer->hook.cbFunc != RT_NULL)
	{
		(timer->hook.cbFunc)(timer->hook.userPtr);
	}
}

/******************************************************************//**
* @brief
*	Initialize all Timer module related hardware and register Timer device to kernel
*
* @details
*
* @note
*********************************************************************/
void rt_hw_timer_init(void)
{
	struct efm32_timer_device_t	*timer;
	TIMER_Init_TypeDef 			init;
	efm32_irq_hook_init_t		hook;

	/* Set TIMERn parameters */ 
	init.enable 		= false;
	init.debugRun		= true;
	init.prescale		= TMR_CFG_PRESCALER;
	init.clkSel 		= timerClkSelHFPerClk;
	init.fallAction 	= timerInputActionNone;
	init.riseAction 	= timerInputActionNone;
	init.mode			= timerModeUp;
	init.dmaClrAct		= false;
	init.quadModeX4 	= false;
	init.oneShot		= false;
	init.sync			= false;

#ifdef RT_USING_TIMER1
	timer = rt_malloc(sizeof(struct efm32_timer_device_t));
	if (timer == RT_NULL)
	{
#ifdef RT_TIMER_DEBUG
		rt_kprintf("no memory for TIMER1 driver\n");
#endif
		return;
	}
	
	timer->timer_device = TIMER1;
#if (RT_USING_TIMER1 == RT_TIMER_ONCE)
	init.oneShot		= true;
#elif (RT_USING_TIMER1 == RT_TIMER_CONTINUE)
	init.oneShot		= false;
#endif

	/* Enable clock for TIMERn module */
	CMU_ClockEnable(cmuClock_TIMER1, true);

	/* Reset */
	TIMER_Reset(TIMER1);

	/* Configure TIMER */
	TIMER_Init(TIMER1, &init);

	hook.type			= efm32_irq_type_timer;
	hook.unit			= 1;
	hook.cbFunc 		= rt_hw_timer_isr;
	hook.userPtr		= &timer1_device;
	efm32_irq_hook_register(&hook);

	/* Enable overflow interrupt */
	TIMER_IntEnable(TIMER1, TIMER_IF_OF);
	TIMER_IntClear(TIMER1, TIMER_IF_OF);

	/* Enable TIMERn interrupt vector in NVIC */
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, EFM32_IRQ_PRI_DEFAULT);
	NVIC_EnableIRQ(TIMER1_IRQn);

    rt_hw_timer_register(&timer1_device, RT_TIMER1_NAME, 0, timer);	
#endif

#ifdef RT_USING_TIMER2
	timer = rt_malloc(sizeof(struct efm32_timer_device_t));
	if (timer == RT_NULL)
	{
#ifdef RT_TIMER_DEBUG
		rt_kprintf("no memory for TIMER2 driver\n");
#endif
		return;
	}
	
	timer->timer_device = TIMER2;
#if (RT_USING_TIMER2 == RT_TIMER_ONCE)
	init.oneShot		= true;
#elif (RT_USING_TIMER2 == RT_TIMER_CONTINUE)
	init.oneShot		= false;
#endif

	/* Enable clock for TIMERn module */
	CMU_ClockEnable(cmuClock_TIMER2, true);

	/* Reset */
	TIMER_Reset(TIMER2);

	/* Configure TIMER */
	TIMER_Init(TIMER2, &init);

	hook.type			= efm32_irq_type_timer;
	hook.unit			= 2;
	hook.cbFunc 		= rt_hw_timer_isr;
	hook.userPtr		= &timer2_device;
	efm32_irq_hook_register(&hook);

	/* Enable overflow interrupt */
	TIMER_IntEnable(TIMER2, TIMER_IF_OF);
	TIMER_IntClear(TIMER2, TIMER_IF_OF);

	/* Enable TIMERn interrupt vector in NVIC */
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_SetPriority(TIMER2_IRQn, EFM32_IRQ_PRI_DEFAULT);
	NVIC_EnableIRQ(TIMER2_IRQn);

    rt_hw_timer_register(&timer2_device, RT_TIMER2_NAME, 0, timer);	
#endif
}

/******************************************************************//**
 * @}
*********************************************************************/
