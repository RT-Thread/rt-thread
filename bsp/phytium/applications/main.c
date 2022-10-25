/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: main.c
 * Date: 2022-10-08 23:16:43
 * LastEditTime: 2022-10-08 23:16:44
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */


#include <rthw.h>
#include <rtthread.h>

#include <board.h>

#ifdef RT_USING_SMP

struct rt_thread test_core[RT_CPUS_NR];
static char *core_thread_name[8] = {
    "core0_test",
    "core1_test",
    "core2_test",
    "core3_test",
    "core4_test",
    "core5_test",
    "core6_test",
    "core7_test"};
static rt_uint8_t core_stack[RT_CPUS_NR][1024];

static void demo_core_thread(void *parameter)
{
    rt_base_t level;
    while (1)
    {
        /* code */
        level = rt_cpus_lock();
        rt_kprintf("Hi, core%d \r\n", rt_hw_cpu_id());
        rt_cpus_unlock(level);
        rt_thread_mdelay(2000000);
    }
}

void demo_core(void)
{
    rt_ubase_t i;
    rt_ubase_t cpu_id = 0;
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        cpu_id = i;
        rt_thread_init(&test_core[i],
                       core_thread_name[i],
                       demo_core_thread,
                       RT_NULL,
                       &core_stack[i],
                       1024,
                       20,
                       32);

        rt_thread_control(&test_core[i], RT_THREAD_CTRL_BIND_CPU, (void *)cpu_id);
        rt_thread_startup(&test_core[i]);
    }
}
#endif

int main(void)
{
#ifdef RT_USING_SMP
    demo_core();
#endif
    return RT_EOK;
}

