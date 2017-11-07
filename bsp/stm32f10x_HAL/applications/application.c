/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2013-07-12     aozima       update for auto initial.
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#include <dfs_posix.h>
extern int dfs_init(void);
#endif

//ALIGN(RT_ALIGN_SIZE)

void rt_init_thread_entry(void *parameter)
{

/* Filesystem Initialization */
#ifdef RT_USING_SPI
    stm32_hw_spi_init();
#endif

#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    dfs_init();
    elm_init();
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("flash0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");
    }
    else
		{
			rt_kprintf("File System initialzation failed!\n");
			dfs_mkfs("elm","flash0");
			HAL_NVIC_SystemReset();
		}
        
#endif /* RT_USING_DFS */
}

int rt_application_init(void)
{
    rt_thread_t init_thread;

//    rt_err_t result;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   1024, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   1024, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
