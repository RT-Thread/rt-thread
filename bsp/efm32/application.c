/******************************************************************//**
 * @file 		application.c
 * @brief 	application tasks
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
 * @author 	Bernard, onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2009-01-05 	Bernard 		first version
 * 2010-12-29	onelife		Modify for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup cortex-m3
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include <board.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
rt_uint32_t rt_system_status = 0;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
void rt_led_thread_entry(void* parameter)
{
//	rt_uint8_t n = 0;
		
	rt_hw_led_on(0);
	rt_hw_led_on(1);
	rt_hw_led_on(2);
	rt_hw_led_on(3);
	
//	while(1)
//	{
		/* light on leds for one second */
//		rt_hw_led_toggle(n++);
//		if (n == 4)
//			n =0;
//		rt_thread_delay(200);
//	}
}

int rt_application_init()
{
	rt_thread_t led_thread;
	rt_thread_t test_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
	led_thread = rt_thread_create(
		"led",
		rt_led_thread_entry, 
		RT_NULL,
		256, 
		3, 
		20);
#else
#endif

	if(led_thread != RT_NULL)
	{
		rt_kprintf("led sp:%x\n", led_thread->sp);
		rt_thread_startup(led_thread);
	}

	return 0;
}

/******************************************************************//**
 * @}
*********************************************************************/
