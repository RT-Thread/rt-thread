/*
	此demo用于演示动态线程创建
 */
#include <rtthread.h>
#include "board.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif


static	rt_thread_t tid1 = RT_NULL;
static	rt_thread_t tid2 = RT_NULL;


static void thread1_entry(void* parameter)
{
    rt_uint32_t count = 0;

    rt_kprintf("thread1 dynamicly created ok\n");
    while (1)
    {
        rt_kprintf("thread1 count: %d\n",count++);
        rt_thread_delay(RT_TICK_PER_SECOND); 
    }
}
						
static void thread2_entry(void* parameter)
{		
		rt_uint32_t count = 0;
    rt_kprintf("thread2 dynamicly created ok\n");
	  
		while(1)
    {
				if(count == 3)
					break;
        rt_kprintf("thread2 count: %d\n",count++);
        rt_thread_delay(RT_TICK_PER_SECOND);   
			
    }
    rt_thread_delay(RT_TICK_PER_SECOND * 4);  
    
    rt_thread_delete(tid1);							
    rt_kprintf("thread1 deleted ok\n");
}


int demo_init(void)
{
				
    tid1 = rt_thread_create("thread1",
				thread1_entry,
				RT_NULL,
				512, 6, 10);
	
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);        

    tid2 = rt_thread_create("thread2",
        thread2_entry, 
				RT_NULL,
        512, 6, 10);
		
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    return 0;
}
