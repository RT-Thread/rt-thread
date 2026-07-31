/*
 * Copyright 2021-2025 NXP
 * All rights reserved.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-02     lucas Cao    EtherCAT thread
 */

#include <rtthread.h>
#include <rtdevice.h>

extern void ecat_main(void);

/* EtherCAT thread stack size */
#define ECAT_THREAD_STACK_SIZE  4096
/* EtherCAT thread priority */
#define ECAT_THREAD_PRIORITY    10
/* EtherCAT thread time slice */
#define ECAT_THREAD_TIMESLICE   20

static void ecat_thread_entry(void *parameter)
{
    rt_kprintf("EtherCAT thread started\r\n");
    ecat_main();
}

int ecat_thread_init(void)
{
    rt_thread_t ecat_thread;
    
    /* Create EtherCAT thread */
    ecat_thread = rt_thread_create("ecat",
                                   ecat_thread_entry,
                                   RT_NULL,
                                   ECAT_THREAD_STACK_SIZE,
                                   ECAT_THREAD_PRIORITY,
                                   ECAT_THREAD_TIMESLICE);
    
    if (ecat_thread != RT_NULL)
    {
        rt_thread_startup(ecat_thread);
        rt_kprintf("EtherCAT thread created successfully\r\n");
        return RT_EOK;
    }
    else
    {
        rt_kprintf("EtherCAT thread creation failed\r\n");
        return -RT_ERROR;
    }
}
INIT_APP_EXPORT(ecat_thread_init);