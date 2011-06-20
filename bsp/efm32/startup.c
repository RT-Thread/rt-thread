/******************************************************************//**
 * @file 		interrupt.c
 * @brief 	This file is part of RT-Thread RTOS
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	Bernard, onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2006-08-31 	Bernard 		first implementation
 * 2010-12-29	onelife		Modify for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup efm32
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include <rtthread.h>

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* External variables -----------------------------------------------------------*/
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end;
#endif

/* Private variables ------------------------------------------------------------*/
/* External function prototypes --------------------------------------------------*/
extern int  rt_application_init(void);
#ifdef RT_USING_FINSH
extern void finsh_system_init(void);
extern void finsh_set_device(const char* device);
#endif

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
#ifdef  DEBUG
/******************************************************************//**
 * @brief
 * 	Reports the name of the source file and the source line number where the assert error 
 * has occurred.
 *
 * @details
 *
 * @note
 *
 * @param[in] file
 * 	Pointer to the source file name
 *
 * @param[in] line
 * 	Assert error line source number
 *********************************************************************/
void assert_failed(u8* file, u32 line)
{
	rt_kprintf("\n\r Wrong parameter value detected on\r\n");
	rt_kprintf("       file  %s\r\n", file);
	rt_kprintf("       line  %d\r\n", line);

	while (1) ;
}
#endif

/******************************************************************//**
 * @brief
 * 	Startup RT-Thread 
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
void rtthread_startup(void)
{
	/* init board */
	rt_hw_board_init();

#ifdef RT_USING_HEAP
	#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)EFM32_SRAM_END);
	#elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void*)EFM32_SRAM_END);
	#else
	/* init memory system */
	rt_system_heap_init((void*)&__bss_end, (void*)EFM32_SRAM_END);
	#endif
#endif

	/* enable interrupt */
	rt_hw_interrupt_enable(0x0UL);

	/* init drivers */
	rt_hw_driver_init();

	/* show version */
	rt_show_version();
	
	/* init tick */
	rt_system_tick_init();

	/* init kernel object */
	rt_system_object_init();

	/* init timer system */
	rt_system_timer_init();

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init all device */
	rt_device_init_all();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
	finsh_set_device(CONSOLE_DEVICE);
#endif

    /* init timer thread */
    rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* init application */
	rt_application_init();	

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

/******************************************************************//**
 * @brief
 * 	Program entry point
 *
 * @details
 *
 * @note
 *
 *********************************************************************/
int main(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();

	/* init system setting */
	SystemInit();

	/* startup RT-Thread RTOS */
	rtthread_startup();

	return 0;
}

/******************************************************************//**
 * @}
*********************************************************************/
