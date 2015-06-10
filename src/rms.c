/*
 *  File : rms.c
 *  This file is part of RT-Thread RTOS
 *  COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Change Logs:
 *  Date           Author       Notes
 *  2015-05-25     hduffddybz   first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_RMS

static void _rt_rms_init(rt_rms_t rms)
{
    rms->rt_rms_stat = RT_RMS_INACTIVE;
    rms->deadline = 0;
}

/**
 * This function will initialize a rms task
 */
void rt_rms_init(rt_rms_t rms, const char *name)
{
    RT_ASSERT(rms != RT_NULL);

    /* rms object initialization */
    rt_object_init((rt_object_t)rms, RT_Object_Class_Rms, name);

    _rt_rms_init(rms);	
}

/**
 * This function will create the rms task
 */
rt_rms_t rt_rms_create(const char *name)
{
    struct rt_rms *rms;
	
    /* allocate a rms object */
    rms = (struct rt_rms *)rt_object_allocate(RT_Object_Class_Rms, name);
    if(rms == RT_NULL)
    {		
        return RT_NULL;
    }	
    /* set status and deadline of rms object */
    _rt_rms_init(rms);

    return rms;
}

/**
 * This function will detach a rms object
 */
rt_err_t rt_rms_detach(rt_rms_t rms)
{
    RT_ASSERT(rms != RT_NULL);
	
    /* change the stat of rms object, the application should call break() manually */	
    rms->rt_rms_stat = RT_RMS_INACTIVE;
    rt_object_detach((rt_object_t)rms);
	
    return RT_EOK;
}

/**
 * This function will delete the rms task
 */
rt_err_t rt_rms_delete(rt_rms_t rms)
{
    RT_ASSERT(rms != RT_NULL);
	
    /* change the stat of rms object, the application should call break() manually */
    rms->rt_rms_stat = RT_RMS_INACTIVE;
    rt_object_delete((rt_object_t)rms);
	
    return RT_EOK;
}

/**
 * This function will set the period of rms task
 */
rt_err_t rt_rms_period(rt_rms_t rms, rt_tick_t period)
{
    rt_tick_t end_time;
    rt_tick_t temp;
    rt_thread_t thread;
	
    RT_ASSERT(rms != RT_NULL);
    RT_ASSERT(period != 0);
	
    switch(rms->rt_rms_stat)
    {
    case RT_RMS_INACTIVE:
        rms->deadline = rt_tick_get() + period;
#ifndef RT_RMS_ACCURACY
#define RT_RMS_ACCURACY		1
#endif			
        temp = period / RT_RMS_ACCURACY;
        thread = rt_thread_self();
        /* change the priority of thread */
        rt_thread_control(thread,
                          RT_THREAD_CTRL_CHANGE_PRIORITY,
                          &temp);
        /* set the stat of rms object */				  
        rms->rt_rms_stat = RT_RMS_ACTIVE;
		
        /* do scheduling when period ends */
        rt_schedule();
		
        return RT_EOK;

    case RT_RMS_ACTIVE:
        end_time = rt_tick_get();

        end_time = rms->deadline - end_time;
        /* guarantee that task did not exceed deadline  */
        if(end_time >= RT_TICK_MAX / 2)
        {
            rt_kprintf("task:%s run exceed deadline\n", rms->parent.name);
            return RT_ERROR;
        }
         
        /* set the next period */		 
        rms->deadline += period;
        /* sleep until next period comes */
        if(end_time != 0)
        {
            rt_thread_delay(end_time);
        }
		
        /* do scheduling when period ends */
        rt_schedule();
		
        return RT_EOK;
			
    default:
        return RT_ERROR;			
    }
}
#endif
