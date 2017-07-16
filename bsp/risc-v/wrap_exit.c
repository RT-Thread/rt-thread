#include <reent.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_PTHREADS 
#include <pthread.h>
#endif


void
__wrap__exit (int status)
{
#ifdef RT_USING_MODULE
	rt_module_t module;

	module = rt_module_self();
	if (module != RT_NULL)
	{
		struct rt_list_node *list;
		struct rt_object *object;

		rt_enter_critical();
		
        /* delete all threads in the module */
        list = &module->module_object[RT_Object_Class_Thread].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_thread_detach((rt_thread_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_thread_delete((rt_thread_t)object);
            }
        }
		/* delete main thread */
		rt_thread_delete(module->module_thread);
		rt_exit_critical();

		/* re-schedule */
		rt_schedule();
	}
#endif
	
	rt_kprintf("thread:%s exit with %d\n", rt_thread_self()->name, status);
	RT_ASSERT(0);

	while (1);
}
