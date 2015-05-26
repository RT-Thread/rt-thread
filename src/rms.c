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

static rt_int16_t rt_rms_scheduler_lock_nest;
extern volatile rt_uint8_t rt_interrupt_nest;
struct rt_rms *rt_current_rms = RT_NULL;
static rt_uint8_t rt_rms_current_priority;
static float utilization = 0;
static rt_list_t rt_rms_tablele[RT_THREAD_PRIORITY_MAX];
static rt_list_t rt_rms_idle_table[RT_THREAD_PRIORITY_MAX];
static rt_list_t rt_rms_zombie_table[RT_THREAD_PRIORITY_MAX];
static struct rt_rms idle_rms;

#ifndef IDLE_THREAD_STACK_SIZE
#define IDLE_THREAD_STACK_SIZE  256
#endif
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_rms_stack[IDLE_THREAD_STACK_SIZE];

#if RT_THREAD_PRIORITY_MAX > 32
static rt_uint32_t rt_rms_ready_priority_group;  
rt_uint8_t rt_rms_table[32];
#else
static rt_uint32_t rt_rms_ready_priority_group;
#endif  

void rt_rms_exit(void)
{
    struct rt_rms *rms;
    register rt_base_t level;
    
    /* get current rms */
    rms = rt_current_rms;
    
    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    
    /* remove from schedule */
    rt_schedule_remove_rms(rms);
    /* change stat */
    rms->thread->stat = RT_RMS_CLOSE;
    
    /* remove it from timer list */
    rt_timer_detach(&rms->rms_timer);
    rt_timer_detach(&rms->thread->thread_timer);
    if(rt_object_is_systemobject((rt_object_t)rms->thread) == RT_TRUE)
    {
        rt_object_detach((rt_object_t)rms->thread);
    }
    rt_list_remove(&(rms->thread->tlist));
    rt_list_remove(&(rms->rlist));
    /* enable interrupt */
    rt_hw_interrupt_enable(level);
    
    /* switch to next task */
    rt_rms_schedule();
}

static rt_err_t _rt_rms_init(struct rt_rms *rms,
                             rt_uint8_t period,
                 rt_uint8_t wcet)
{
    /* init rms list */
    rt_list_init(&(rms->rlist));
    
    rms->thread->stat = RT_RMS_INIT;
    rms->period = period;
    rms->wcet = wcet;
    rms->utilization = (float)wcet / period;
    rms->deadline = rt_tick_get() + rms->period;
    
    utilization += rms->utilization;
    RT_ASSERT(utilization <= 1);
    /* init the rms timer for activating next job */
    rt_timer_init(&(rms->rms_timer),
        rms->thread->name,
        rt_rms_wakeup,
        (void *)rms->period,
        rms->period,
        RT_TIMER_FLAG_PERIODIC);
    /* start the rms timer */               
    rt_timer_start(&(rms->rms_timer));
    
    return RT_RMS_EOK;
}                            

/**
 * This function will start a rms task and put it to system ready queue
 */ 
rt_rms_t rt_rms_startup(rt_rms_t rms)
{
    /* rms check */
    RT_ASSERT(rms != RT_NULL);
    RT_ASSERT(rms->thread->stat == RT_RMS_INIT);
    
    /* set current priority to init priority */
    rms->thread->current_priority = rms->thread->init_priority;
#if RT_THREAD_PRIORITY_MAX > 32
    rms->thread->number = rms->thread->current_priority >> 3;
    rms->thread->number_mask = 1L << rms->thread->number;
    rms->thread->high_mask = 1L << (rms->thread->current_priority & 0x07);
#else
    rms->thread->number_mask = 1L << rms->thread->current_priority;
#endif

    /* change rms stat */
    rms->thread->stat = RT_RMS_SLEEP;
    
    /* resume rms task */
    rt_rms_resume(rms);
    if(rt_rms_self() != RT_NULL)
    {
         /* do a scheduling */
    rt_rms_schedule();
    }       
    
    return RT_RMS_EOK;
}

/**
 * This function will create a rms object and allocate rms object memory and stack
 */
rt_rms_t rt_rms_create(const char *name,
            void (*entry)(void *parameter),
            void *parameter,
            rt_uint32_t stack_size,
            rt_uint32_t tick,
            rt_uint8_t period,
            rt_uint8_t wcet)
{
    struct rt_rms  *rms;
    
    rms = (struct rt_rms *)rt_object_allocate(RT_Object_Class_Thread, name);
                                        
    if(rms->thread == RT_NULL)
        return RT_NULL;
    
<<<<<<< HEAD
#ifndef RT_RMS_ACCURACY
#define RT_RMS_ACCURACY 1
#endif	
    /* create a thread object */
    rms->thread = rt_thread_create(name, entry, parameter, stack_size, period / RT_RMS_ACCURACY, tick);
=======
    /* create a thread object */
    rms->thread = rt_thread_create(name, entry, parameter, stack_size, period, tick);
>>>>>>> b5d64d63b4fdf48b8490807ef79ddeb64fef615e
    _rt_rms_init(rms, period, wcet);    
    
    return rms;
}

/**
 * This funciton will initialize a rms thread
 */
rt_err_t rt_rms_init(struct rt_rms *rms,
            const char *name,
            void (*entry)(void *parameter),
            void *parameter,
            void *stack_start,
            rt_uint32_t stack_size,
            rt_uint8_t period,
            rt_uint32_t tick,
            rt_uint8_t wcet)
{
    RT_ASSERT(rms != RT_NULL);
    RT_ASSERT(stack_start != RT_NULL);
    
    rms->thread = (struct rt_thread *)rt_object_allocate(RT_Object_Class_Thread, name);
    RT_ASSERT(rt_thread_init(rms->thread, name, entry, parameter, stack_start, stack_size,
                            period, tick) == RT_EOK);
    return _rt_rms_init(rms, period, wcet);                 
}

/**
 * insert a task into the idle queue
 * when a periodic job finishes at the end of its period, it should call the rt_end_cycle() explicitly
 */
void rt_end_cycle(void)
{
    register rt_base_t level;
    rt_int32_t deadline;
    struct rt_rms *rms;
    rt_tick_t tick;
    
    rms = rt_current_rms;
    deadline = rt_current_rms->deadline;
    tick = rt_tick_get();
    
    RT_ASSERT(rt_current_rms->deadline >= tick);
    if(tick < deadline)
    {
        level = rt_hw_interrupt_disable();
    /* remove from ready queue */       
    rt_schedule_remove_rms(rt_current_rms);
    rms->thread->stat = RT_RMS_IDLE;

    /* insert into idle queue */        
    rt_list_insert_before(&(rt_rms_idle_table[rms->thread->current_priority]),
                            &(rms->rlist));
    
    rt_hw_interrupt_enable(level);  
    }
    else
    {
        deadline += rt_current_rms->period;
    rt_current_rms->deadline = deadline;
    rt_current_rms->thread->stat = RT_RMS_READY;
    }

        rt_rms_schedule();
}


/**
 * RM Scheduling clock ISR 
 */
void rt_rms_wakeup(void *parameter)
{
    register struct rt_rms *rms;
    rt_int8_t count = 0;
    rt_tick_t tick = 0;
    rt_ubase_t priority = (rt_ubase_t)parameter;
    
    tick = rt_tick_get();
    /* awake idle tasks */
    rms = rt_list_entry(rt_rms_idle_table[priority].next, struct rt_rms, rlist);
    if(rms != RT_NULL && rms->deadline <= tick && rms->thread->stat == RT_RMS_IDLE)
    {
        
        rms->deadline += rms->period;
    rms->thread->stat = RT_RMS_READY;
    rt_list_remove(&(rt_rms_idle_table[priority]));

    rt_schedule_insert_rms(rms);
            
    count++;
    }
    
    rms = rt_list_entry(rt_rms_zombie_table[priority].next, struct rt_rms, rlist);
    /* remove all zombie tasks for which their deadline is expired */
    if(rms != RT_NULL && rms->deadline <= tick && rms->thread->stat == RT_RMS_ZOMBIE)
    {
    utilization -= rms->utilization;
    rms->thread->stat = RT_RMS_CLOSE;
    rt_list_remove(&(rt_rms_zombie_table[priority]));
    rt_rms_delete(rms);
    count ++;
    }
    
    /* if at least a task has been awakened, call the scheduler */
    if(count > 0)
    {
        rt_rms_schedule();
    }
}

/**
 * This function will return self rms thread
 */
 rt_rms_t rt_rms_self(void)
 {
     return rt_current_rms;
     
 }

 /**
  * This task will delete the rms task
  */
 rt_err_t rt_rms_delete(rt_rms_t rms)
 {
     
     RT_ASSERT(rms != RT_NULL);
     
     rt_timer_detach(&rms->thread->thread_timer);
     rt_timer_detach(&rms->rms_timer);
     
     rms->thread->stat = RT_RMS_CLOSE;
     rt_object_detach((rt_object_t)rms->thread);
     rt_list_remove(&(rms->thread->tlist));
     rt_list_remove(&(rms->rlist)); 
     
     return RT_RMS_EOK;
 }
 
 /**
  * This function will add the zombie task to zombie queue, when time expired,
  * this task will be deleted
  */
 rt_err_t rt_rms_detach(rt_rms_t rms)
 {
     rt_base_t level;
     level = rt_hw_interrupt_disable();
    /* remove from ready queue */       
    rt_schedule_remove_rms(rms);
    rms->thread->stat = RT_RMS_ZOMBIE;

    /* insert into idle queue */        
    rt_list_insert_before(&(rt_rms_zombie_table[rms->thread->current_priority]),
                            &(rms->rlist));
    
    rt_hw_interrupt_enable(level);

    return RT_RMS_EOK;  
 } 
  
/**
 * This function will initialize the rm(rate monotonic) scheduler
 * Initialize the idle queue, zombie queue and utilization of CPU.
 */
void rt_system_rms_scheduler_init(void)
{
    register rt_base_t offset;
    
    rt_rms_scheduler_lock_nest = 0;
    /* initialize the queue for idle tasks and zombie tasks */
    for(offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset++)
    {
        rt_list_init(&rt_rms_tablele[offset]);
        rt_list_init(&rt_rms_idle_table[offset]);
        rt_list_init(&rt_rms_zombie_table[offset]);
    }
    
    rt_rms_current_priority = RT_THREAD_PRIORITY_MAX - 1;
    rt_current_rms = RT_NULL;
    
    /* initialize the idle, zombie priority group */
    rt_rms_ready_priority_group = 0;
    
#if RT_THREAD_PRIORITY_MAX > 32
    rt_memset(rt_rms_table, 0, sizeof(rt_rms_table));
#endif
    
    /* initialize the cpu utilization */
    utilization = 0;
}

/* This function will startup scheduler */
void rt_system_rms_scheduler_start(void)
{
    register struct rt_rms *to_rms;
    register rt_ubase_t highest_ready_priority;
    
#if RT_THREAD_PRIORITY_MAX > 32 
    register rt_ubase_t number;
    
    number = __rt_ffs(rt_rms_ready_priority_group) - 1;
    highest_ready_priority = (number << 3) + __rt_ffs(rt_rms_ready_priority_group[number]) - 1;
#else
    highest_ready_priority = __rt_ffs(rt_rms_ready_priority_group) - 1;
#endif
    to_rms = rt_list_entry(rt_rms_tablele[highest_ready_priority].next,
                            struct rt_rms,
                            rlist);
                            
    rt_current_rms = to_rms;
    
    rt_hw_context_switch_to((rt_uint32_t)&to_rms->thread->sp);  
    
}

/**
 * This function will perform one rms schedule.
 */
void rt_rms_schedule(void)
{
    rt_base_t level;
    struct rt_rms *to_rms;
    struct rt_rms *from_rms;
    
    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    
    if(rt_rms_scheduler_lock_nest == 0)
    {
        register rt_ubase_t highest_ready_priority;
        
#if RT_THREAD_PRIORITY_MAX <= 32
        highest_ready_priority = __rt_ffs(rt_rms_ready_priority_group) - 1;
#else
        register rt_ubase_t number;
        number = __rt_ffs(rt_rms_ready_priority_group) - 1;
        highest_ready_priority = (number << 3) + __rt_ffs(rt_rms_tablele[number]) - 1;
#endif

        /* get switch to rms */
        to_rms = rt_list_entry(rt_rms_tablele[highest_ready_priority].next,
                               struct rt_rms,
                               rlist);
        if(to_rms != rt_current_rms)
        {
            rt_rms_current_priority = (rt_uint8_t)highest_ready_priority;
            from_rms = rt_current_rms;
            rt_current_rms = to_rms;
            
            /* switch to new thread */
            RT_DEBUG_LOG(RT_DEBUG_SCHEDULER,
                         ("[%d]switch to priority#%d "
                          "thread:%.*s(sp:0x%p), "
                          "from thread:%.*s(sp: 0x%p)\n",
                          rt_interrupt_nest, highest_ready_priority,
                          RT_NAME_MAX, to_rms->thread->name, to_rms->thread->sp,
                          RT_NAME_MAX, from_rms->thread->name, from_rms->thread->sp));
 
#ifdef RT_USING_OVERFLOW_CHECK
            _rt_scheduler_stack_check(to_rms->thread);
#endif 
                          
            if(rt_interrupt_nest == 0)
            {

                    rt_hw_context_switch((rt_uint32_t)&from_rms->thread->sp,
                                        (rt_uint32_t)&to_rms->thread->sp);

            }
            else
            {
                RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("switch in interrupt\n"));
                

                    rt_hw_context_switch_interrupt((rt_uint32_t)&from_rms->thread->sp,
                                     (rt_uint32_t)&to_rms->thread->sp);

            }   
            
        }       
    
    }
    rt_hw_interrupt_enable(level);
}


 /**
  * This funciton will insert a rms thread to system ready queue.
  */
 void rt_schedule_insert_rms(struct rt_rms *rms)
 {
     register rt_base_t temp;
     
     RT_ASSERT(rms != RT_NULL);
     
     temp = rt_hw_interrupt_disable();
     
     rms->thread->stat = RT_RMS_READY;
     
     rt_list_insert_before(&(rt_rms_tablele[rms->thread->current_priority]),
                            &(rms->rlist));

#if RT_THREAD_RIORITY_MAX > 32
     rt_thread_priority_table[rms->thread->number] |= rms->thread->high_mask;
#endif
     rt_rms_ready_priority_group |= rms->thread->number_mask;

     rt_hw_interrupt_enable(temp);  
 }
 
 /**
  * This function will resume a rms task and put it into ready queue
  */
 rt_err_t rt_rms_resume(rt_rms_t rms)
 {
     register rt_base_t temp;
     
     /* rms check */
     RT_ASSERT(rms != RT_NULL);
     
     temp = rt_hw_interrupt_disable();
     
     rt_list_remove(&(rms->rlist));
     rt_timer_stop(&rms->thread->thread_timer);
     rt_hw_interrupt_enable(temp);
     
     rt_schedule_insert_rms(rms);
     
     return RT_RMS_EOK;
 }
 
 /**
  * This function will remove a rms task from system ready queue.
  */
 void rt_schedule_remove_rms(struct rt_rms *rms)
 {
     register rt_base_t temp;
     
     RT_ASSERT(rms != RT_NULL);
     
     /* disable interrupt */
     temp = rt_hw_interrupt_disable();
     /* remove thread from ready list */
     rt_list_remove(&(rms->rlist));
     if(rt_list_isempty(&(rt_rms_tablele[rms->thread->current_priority])))
     {
#if RT_THREAD_PRIORITY_MAX > 32
        rt_rms_ready_table[rms->thread->number] &= ~rms->thread->high_mask;
        if(rt_rms_ready_table[rms->thread->number] == 0)
        {
            rt_rms_ready_priority_group &= ~rms->thread->number_mask;
        }       
#else
        rt_rms_ready_priority_group &= ~rms->thread->number_mask;
#endif  
     }
     
     /* enable interrupt */
     rt_hw_interrupt_enable(temp);
 }
 
 static void rt_rms_idle_entry(void *parameter)
 {
     rt_current_rms = &idle_rms;
     while(1)
     {
         ;
     }
 }
 
 /**
  * This function will initialize the idle rms, then start it. 
  */
 void rt_rms_idle_init(void)
 {
     /* initialize idle rms */
     rt_rms_init(&idle_rms, "idle_rms",
                rt_rms_idle_entry, RT_NULL,
                &rt_rms_stack[0],
                sizeof(rt_rms_stack),
                RT_THREAD_PRIORITY_MAX - 1,
                RT_THREAD_PRIORITY_MAX - 1, 0);
     
     /* startup */
     rt_rms_startup(&idle_rms);
 }
#endif
 
