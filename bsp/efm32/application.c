/******************************************************************//**
 * @file 		application.c
 * @brief 	application tasks
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
 * 2009-01-05 	Bernard 		first version
 * 2010-12-29	onelife		Modify for EFM32
 * 2011-05-06	onelife		Add SPI Flash DEMO
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

#include "dev_led.h"
#ifdef EFM32_USING_SFLASH
#include "dev_sflash.h"
#endif

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
rt_uint32_t	rt_system_status = 0;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
void rt_demo_thread_entry(void* parameter)
{
#ifdef EFM32_USING_SFLASH
	rt_uint8_t i;
	rt_uint8_t test[] = "123456789ABCDEF";
	rt_uint8_t buf[30], buf2[30];

	efm_spiFash_cmd(sflash_inst_rdid_l, EFM32_NO_DATA, buf, sizeof(buf));
	rt_kprintf("Manuf ID: %x\n", buf[0]);
	rt_kprintf("Memory type: %x\n", buf[1]);
	rt_kprintf("Memory capacity: %x\n", buf[2]);
	rt_kprintf("CFD length: %x\n", buf[3]);
	rt_kprintf("CFD: %x%x%x...%x%x\n", buf[4], buf[5], buf[6], buf[18], buf[19]);

	efm_spiFash_cmd(sflash_inst_wren, EFM32_NO_DATA, EFM32_NO_POINTER, EFM32_NO_DATA);
	do
	{
		efm_spiFash_cmd(sflash_inst_rdsr, EFM32_NO_DATA, buf2, sizeof(buf2));
		rt_kprintf("Status: %x\n", buf2[0]);
	} while (buf2[0] == 0xFF);
	rt_kprintf("Status: %x\n", buf2[0]);

	//efm_spiFash_cmd(sflash_inst_pp, 0x000003F8, test, sizeof(test) - 1);

	efm_spiFash_cmd(sflash_inst_rdsr, EFM32_NO_DATA, buf2, sizeof(buf2));
	rt_kprintf("Status: %x\n", buf2[0]);
	
	efm_spiFash_cmd(sflash_inst_read, 0x00000300, buf, sizeof(buf));
	rt_kprintf("READ: \n");
	for (i = 0; i < sizeof(buf); i++)
	{
		rt_kprintf("%c\n", buf[i]);
	}

	//efm_spiFash_deinit();
#endif
}

void rt_led_thread_entry(void* parameter)
{
	rt_uint8_t n = 0;

	rt_hw_led_on(0);
	rt_hw_led_on(1);
	rt_hw_led_on(2);
	rt_hw_led_on(3);

	while(1)
	{
		/* Toggle a led per second */
		rt_hw_led_toggle(n++);
		if (n == LEDS_MAX_NUMBER)
		{
			n =0;
		}
		rt_thread_delay(100);
	}
}

int rt_application_init()
{
	rt_thread_t demo_thread, led_thread;

#if (defined(EFM32_G290_DK) && defined(EFM32_USING_SFLASH))
	/* Enable SPI access to Flash */
	DVK_writeRegister(BC_SPI_CFG, 0);
	efm_spiFash_init();
#endif

	/* Initialize all device drivers (dev_?.c) */
	if (rt_hw_led_init() != RT_EOK)
	{
		rt_kprintf("*** Failed to initialize LED driver!");
		while(1); //Or do something?
	}
	if (rt_hw_misc_init() != RT_EOK)
	{
		rt_kprintf("*** Failed to miscellaneous driver!");
		while(1); //Or do something?
	}

#if (RT_THREAD_PRIORITY_MAX == 32)
	demo_thread = rt_thread_create(
		"demo",
		rt_demo_thread_entry, 
		RT_NULL,
		2048, 
		3, 
		20);

	led_thread = rt_thread_create(
		"led",
		rt_led_thread_entry, 
		RT_NULL,
		256,
		3, 
		20);
#else
#endif

	if(demo_thread != RT_NULL)
	{
		rt_kprintf("demo sp:%x\n", demo_thread->sp);
		rt_thread_startup(demo_thread);
	}

	if(led_thread != RT_NULL)
	{
		rt_thread_startup(led_thread);
	}

	return 0;
}

/******************************************************************//**
 * @}
*********************************************************************/
