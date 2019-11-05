

#include <rtthread.h>
#include "board.h"
#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif


#ifdef RT_USING_GDB
#include <gdb_stub.h>
#endif

extern int demo_init(void);

void rt_init_thread_entry(void* parameter)
{
    parameter = parameter;
    /* GDB STUB */
#ifdef RT_USING_GDB
    gdb_set_device("uart6");
    gdb_start();
#endif

#ifdef RT_USING_FINSH
    finsh_system_init();
#endif

    demo_init();
  
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
        
    return 0;
}

/*@}*/
