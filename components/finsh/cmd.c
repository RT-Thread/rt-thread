/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      first implementation
 * 2006-05-04     Bernard      add list_thread,
 *                                 list_sem,
 *                                 list_timer
 * 2006-05-20     Bernard      add list_mutex,
 *                                 list_mailbox,
 *                                 list_msgqueue,
 *                                 list_event,
 *                                 list_fevent,
 *                                 list_mempool
 * 2006-06-03     Bernard      display stack information in list_thread
 * 2006-08-10     Bernard      change version to invoke rt_show_version
 * 2008-09-10     Bernard      update the list function for finsh syscall
 *                                 list and sysvar list
 * 2009-05-30     Bernard      add list_device
 * 2010-04-21     yi.qiu       add list_module
 * 2012-04-29     goprife      improve the command line auto-complete feature.
 * 2012-06-02     lgnq         add list_memheap
 * 2012-10-22     Bernard      add MS VC++ patch.
 * 2016-06-02     armink       beautify the list_thread command
 * 2018-11-22     Jesven       list_thread add smp support
 * 2018-12-27     Jesven       Fix the problem that disable interrupt too long in list_thread
 *                             Provide protection for the "first layer of objects" when list_*
 * 2020-04-07     chenhui      add clear
 * 2022-07-02     Stanley Lwin add list command
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2024-02-09     Bernard      fix the version command
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#ifdef RT_USING_FINSH
#include <finsh.h>

#define LIST_DFS_OPT_ID 0x100

static long clear(void)
{
    rt_kprintf("\x1b[2J\x1b[H");

    return 0;
}
MSH_CMD_EXPORT(clear, clear the terminal screen);

static long version(void)
{
    rt_show_version();

    return 0;
}
MSH_CMD_EXPORT(version, show RT-Thread version information);

rt_inline void object_split(int len)
{
    while (len--) rt_kprintf("-");
}

static rt_err_t thread_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    rt_thread_t thread = (rt_thread_t) object;

    rt_uint8_t stat;
    rt_uint8_t *ptr;

#ifdef RT_USING_SMP
    /* no synchronization applied since it's only for debug */
    if (RT_SCHED_CTX(thread).oncpu != RT_CPU_DETACHED)
        rt_kprintf("%-*.*s %3d %3d %4d ", RT_NAME_MAX, RT_NAME_MAX,
                   thread->parent.name, RT_SCHED_CTX(thread).oncpu,
                   RT_SCHED_CTX(thread).bind_cpu,
                   RT_SCHED_PRIV(thread).current_priority);
    else
        rt_kprintf("%-*.*s N/A %3d %4d ", RT_NAME_MAX, RT_NAME_MAX,
                   thread->parent.name,
                   RT_SCHED_CTX(thread).bind_cpu,
                   RT_SCHED_PRIV(thread).current_priority);

#else
    /* no synchronization applied since it's only for debug */
    rt_kprintf("%-*.*s %3d ", RT_NAME_MAX, RT_NAME_MAX, thread->parent.name, RT_SCHED_PRIV(thread).current_priority);
#endif /*RT_USING_SMP*/
    stat = (RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK);
    if (stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
    else if ((stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK) rt_kprintf(" suspend");
    else if (stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
    else if (stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");
    else if (stat == RT_THREAD_RUNNING) rt_kprintf(" running");

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
    ptr = (rt_uint8_t *)thread->stack_addr + thread->stack_size - 1;
    while (*ptr == '#')ptr --;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %s %p\n",
               ((rt_ubase_t)thread->sp - (rt_ubase_t)thread->stack_addr),
               thread->stack_size,
               ((rt_ubase_t)ptr - (rt_ubase_t)thread->stack_addr) * 100 / thread->stack_size,
               thread->remaining_tick,
               rt_strerror(thread->error),
               thread);
#else
    ptr = (rt_uint8_t *)thread->stack_addr;
    while (*ptr == '#') ptr ++;
    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %s %p\n",
               thread->stack_size + ((rt_ubase_t)thread->stack_addr - (rt_ubase_t)thread->sp),
               thread->stack_size,
               (thread->stack_size - ((rt_ubase_t) ptr - (rt_ubase_t) thread->stack_addr)) * 100
               / thread->stack_size,
               RT_SCHED_PRIV(thread).remaining_tick,
               rt_strerror(thread->error),
               thread);
#endif

    return RT_EOK;
}

long list_thread(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    const char *item_title = "thread";
    const size_t tcb_strlen = sizeof(void *) * 2 + 2;
    int maxlen;

    maxlen = RT_NAME_MAX;

#ifdef RT_USING_SMP
    rt_kprintf("%-*.*s cpu bind pri  status      sp     stack size max used left tick   error  tcb addr\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" --- ---- ---  ------- ---------- ----------  ------  ---------- -------");
    rt_kprintf(" ");
    object_split(tcb_strlen);
    rt_kprintf("\n");
#else
    rt_kprintf("%-*.*s pri  status      sp     stack size max used left tick   error  tcb addr\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---  ------- ---------- ----------  ------  ---------- -------");
    rt_kprintf(" ");
    object_split(tcb_strlen);
    rt_kprintf("\n");
#endif /*RT_USING_SMP*/

    rt_object_for_each_safe(RT_Object_Class_Thread, thread_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}

#ifdef RT_USING_SEMAPHORE
static rt_err_t sem_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_semaphore *sem = (struct rt_semaphore *)object;

    if (!rt_list_isempty(&sem->parent.suspend_thread))
    {
        rt_kprintf("%-*.*s %03d %d:",
                   RT_NAME_MAX, RT_NAME_MAX,
                   sem->parent.parent.name,
                   sem->value,
                   rt_list_len(&sem->parent.suspend_thread));
        rt_susp_list_print(&(sem->parent.suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s %03d %d\n",
                   RT_NAME_MAX, RT_NAME_MAX,
                   sem->parent.parent.name,
                   sem->value,
                   rt_list_len(&sem->parent.suspend_thread));
    }

    return RT_EOK;
}

long list_sem(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "semaphore";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s v   suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" --- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_Semaphore, sem_print_, RT_NULL, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_SEMAPHORE */

#ifdef RT_USING_EVENT
static rt_err_t event_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_event *event = (struct rt_event *)object;

    if (!rt_list_isempty(&event->parent.suspend_thread))
    {
        rt_kprintf("%-*.*s  0x%08x %03d:",
                   RT_NAME_MAX, RT_NAME_MAX,
                   event->parent.parent.name,
                   event->set,
                   rt_list_len(&event->parent.suspend_thread));
        rt_susp_list_print(&(event->parent.suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s  0x%08x 0\n",
                   RT_NAME_MAX, RT_NAME_MAX, event->parent.parent.name, event->set);
    }

    return RT_EOK;
}

long list_event(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "event";

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s      set    suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf("  ---------- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_Event, event_print_, RT_NULL, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_EVENT */

#ifdef RT_USING_MUTEX
static rt_err_t mutex_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_mutex *mutex = (struct rt_mutex *)object;

    if (!rt_list_isempty(&mutex->parent.suspend_thread))
    {
        rt_kprintf("%-*.*s %-8.*s %04d %8d  %04d ",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mutex->parent.parent.name,
                   RT_NAME_MAX,
                   (mutex->owner == RT_NULL) ? "(null)" : mutex->owner->parent.name,
                   mutex->hold,
                   mutex->priority,
                   rt_list_len(&mutex->parent.suspend_thread));
        rt_susp_list_print(&(mutex->parent.suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s %-8.*s %04d %8d  %04d\n",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mutex->parent.parent.name,
                   RT_NAME_MAX,
                   (mutex->owner == RT_NULL) ? "(null)" : mutex->owner->parent.name,
                   mutex->hold,
                   mutex->priority,
                   rt_list_len(&mutex->parent.suspend_thread));
    }

    return RT_EOK;
}

long list_mutex(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "mutex";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s   owner  hold priority suspend thread \n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" -------- ---- -------- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_Mutex, mutex_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_MUTEX */

#ifdef RT_USING_MAILBOX
static rt_err_t mailbox_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_mailbox *mailbox = (struct rt_mailbox *)object;

    if (!rt_list_isempty(&mailbox->parent.suspend_thread))
    {
        rt_kprintf("%-*.*s %04d  %04d %d:",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mailbox->parent.parent.name,
                   mailbox->entry,
                   mailbox->size,
                   rt_list_len(&mailbox->parent.suspend_thread));
        rt_susp_list_print(&(mailbox->parent.suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s %04d  %04d %d\n",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mailbox->parent.parent.name,
                   mailbox->entry,
                   mailbox->size,
                   rt_list_len(&mailbox->parent.suspend_thread));
    }

    return RT_EOK;
}

long list_mailbox(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "mailbox";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s entry size suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  ---- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_MailBox, mailbox_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_MAILBOX */

#ifdef RT_USING_MESSAGEQUEUE
static rt_err_t msqueue_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_messagequeue *msgqueue = (struct rt_messagequeue *)object;

    if (!rt_list_isempty(&msgqueue->parent.suspend_thread))
    {
        rt_kprintf("%-*.*s %04d  %d:",
                   RT_NAME_MAX, RT_NAME_MAX,
                   msgqueue->parent.parent.name,
                   msgqueue->entry,
                   rt_list_len(&msgqueue->parent.suspend_thread));
        rt_susp_list_print(&(msgqueue->parent.suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s %04d  %d\n",
                   RT_NAME_MAX, RT_NAME_MAX,
                   msgqueue->parent.parent.name,
                   msgqueue->entry,
                   rt_list_len(&msgqueue->parent.suspend_thread));
    }

    return RT_EOK;
}

long list_msgqueue(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "msgqueue";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s entry suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  --------------\n");

    rt_object_for_each_safe(RT_Object_Class_MessageQueue, msqueue_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_MESSAGEQUEUE */

#ifdef RT_USING_MEMHEAP
static rt_err_t memheap_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_memheap *memheap = (struct rt_memheap *)object;

    rt_kprintf("%-*.*s %-010d %-013d %-05d\n",
               RT_NAME_MAX, RT_NAME_MAX,
               memheap->parent.name,
               memheap->pool_size,
               memheap->max_used_size,
               memheap->available_size);

    return RT_EOK;
}

long list_memheap(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "memheap";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s  pool size  max used size available size\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---------- ------------- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_MemHeap, memheap_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_MEMHEAP */

#ifdef RT_USING_MEMPOOL
static rt_err_t mempool_print_(rt_object_t object, void *data)
{
    int suspend_thread_count;
    rt_list_t *node;

    RT_UNUSED(data);

    struct rt_mempool *mp = (struct rt_mempool *)object;

    suspend_thread_count = 0;
    rt_list_for_each(node, &mp->suspend_thread)
    {
        suspend_thread_count++;
    }

    if (suspend_thread_count > 0)
    {
        rt_kprintf("%-*.*s %04d  %04d  %04d %d:",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mp->parent.name,
                   mp->block_size,
                   mp->block_total_count,
                   mp->block_free_count,
                   suspend_thread_count);
        rt_susp_list_print(&(mp->suspend_thread));
        rt_kprintf("\n");
    }
    else
    {
        rt_kprintf("%-*.*s %04d  %04d  %04d %d\n",
                   RT_NAME_MAX, RT_NAME_MAX,
                   mp->parent.name,
                   mp->block_size,
                   mp->block_total_count,
                   mp->block_free_count,
                   suspend_thread_count);
    }

    return RT_EOK;
}

long list_mempool(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "mempool";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s block total free suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  ----  ---- --------------\n");

    rt_object_for_each_safe(RT_Object_Class_MemPool, mempool_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_MEMPOOL */

static rt_err_t timer_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_timer *timer = (struct rt_timer *)object;

    rt_kprintf("%-*.*s 0x%08x 0x%08x ",
               RT_NAME_MAX, RT_NAME_MAX,
               timer->parent.name,
               timer->init_tick,
               timer->timeout_tick);
    if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        rt_kprintf("activated   ");
    else
        rt_kprintf("deactivated ");
    if (timer->parent.flag & RT_TIMER_FLAG_PERIODIC)
        rt_kprintf("periodic\n");
    else
        rt_kprintf("one shot\n");

    return RT_EOK;
}

long list_timer(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "timer";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s  periodic   timeout    activated     mode\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---------- ---------- ----------- ---------\n");

    rt_object_for_each_safe(RT_Object_Class_Timer, timer_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    rt_kprintf("current tick:0x%08x\n", rt_tick_get());

    return 0;
}

#ifdef RT_USING_DEVICE
static char *const device_type_str[RT_Device_Class_Unknown] =
{
    "Character Device",
    "Block Device",
    "Network Interface",
    "MTD Device",
    "CAN Device",
    "RTC",
    "Sound Device",
    "Graphic Device",
    "I2C Bus",
    "USB Slave Device",
    "USB Host Bus",
    "USB OTG Bus",
    "SPI Bus",
    "SPI Device",
    "SDIO Bus",
    "PM Pseudo Device",
    "Pipe",
    "Portal Device",
    "Timer Device",
    "Miscellaneous Device",
    "Sensor Device",
    "Touch Device",
    "Phy Device",
    "Security Device",
    "WLAN Device",
    "Pin Device",
    "ADC Device",
    "DAC Device",
    "WDT Device",
    "PWM Device",
    "Bus Device",
};

static rt_err_t device_print_(rt_object_t object, void *data)
{
    RT_UNUSED(data);

    struct rt_device *device = (struct rt_device *)object;
    const char *device_type = "Unknown";
    if (device->type < RT_Device_Class_Unknown &&
        device_type_str[device->type] != RT_NULL)
    {
        device_type = device_type_str[device->type];
    }
    rt_kprintf("%-*.*s %-20s %-8d\n",
               RT_NAME_MAX, RT_NAME_MAX,
               device->parent.name,
               device_type,
               device->ref_count);

    return RT_EOK;
}

long list_device(void)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];
    int maxlen;
    const char *item_title = "device";
    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s         type         ref count\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" -------------------- ----------\n");

    rt_object_for_each_safe(RT_Object_Class_Device, device_print_, RT_NULL, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    return 0;
}
#endif /* RT_USING_DEVICE */

#ifndef FINSH_USING_OPTION_COMPLETION
static int cmd_list(int argc, char **argv)
{
    if(argc == 2)
    {
        if(strcmp(argv[1], "thread") == 0)
        {
            list_thread();
        }
        else if(strcmp(argv[1], "timer") == 0)
        {
            list_timer();
        }
#ifdef RT_USING_SEMAPHORE
        else if(strcmp(argv[1], "sem") == 0)
        {
            list_sem();
        }
#endif /* RT_USING_SEMAPHORE */
#ifdef RT_USING_EVENT
        else if(strcmp(argv[1], "event") == 0)
        {
            list_event();
        }
#endif /* RT_USING_EVENT */
#ifdef RT_USING_MUTEX
        else if(strcmp(argv[1], "mutex") == 0)
        {
            list_mutex();
        }
#endif /* RT_USING_MUTEX */
#ifdef RT_USING_MAILBOX
        else if(strcmp(argv[1], "mailbox") == 0)
        {
            list_mailbox();
        }
#endif  /* RT_USING_MAILBOX */
#ifdef RT_USING_MESSAGEQUEUE
        else if(strcmp(argv[1], "msgqueue") == 0)
        {
            list_msgqueue();
        }
#endif /* RT_USING_MESSAGEQUEUE */
#ifdef RT_USING_MEMHEAP
        else if(strcmp(argv[1], "memheap") == 0)
        {
            list_memheap();
        }
#endif /* RT_USING_MEMHEAP */
#ifdef RT_USING_MEMPOOL
        else if(strcmp(argv[1], "mempool") == 0)
        {
            list_mempool();
        }
#endif /* RT_USING_MEMPOOL */
#ifdef RT_USING_DEVICE
        else if(strcmp(argv[1], "device") == 0)
        {
            list_device();
        }
#endif /* RT_USING_DEVICE */
#ifdef RT_USING_DFS
        else if(strcmp(argv[1], "fd") == 0)
        {
            extern int list_fd(void);
            list_fd();
        }
#endif /* RT_USING_DFS */
        else
        {
            goto _usage;
        }

        return 0;
    }

_usage:
    rt_kprintf("Usage: list [options]\n");
    rt_kprintf("[options]:\n");
    rt_kprintf("    %-12s - list threads\n", "thread");
    rt_kprintf("    %-12s - list timers\n", "timer");
#ifdef RT_USING_SEMAPHORE
    rt_kprintf("    %-12s - list semaphores\n", "sem");
#endif /* RT_USING_SEMAPHORE */
#ifdef RT_USING_MUTEX
    rt_kprintf("    %-12s - list mutexs\n", "mutex");
#endif /* RT_USING_MUTEX */
#ifdef RT_USING_EVENT
    rt_kprintf("    %-12s - list events\n", "event");
#endif /* RT_USING_EVENT */
#ifdef RT_USING_MAILBOX
    rt_kprintf("    %-12s - list mailboxs\n", "mailbox");
#endif /* RT_USING_MAILBOX */
#ifdef RT_USING_MESSAGEQUEUE
    rt_kprintf("    %-12s - list message queues\n", "msgqueue");
#endif /* RT_USING_MESSAGEQUEUE */
#ifdef RT_USING_MEMHEAP
    rt_kprintf("    %-12s - list memory heaps\n", "memheap");
#endif /* RT_USING_MEMHEAP */
#ifdef RT_USING_MEMPOOL
    rt_kprintf("    %-12s - list memory pools\n", "mempool");
#endif /* RT_USING_MEMPOOL */
#ifdef RT_USING_DEVICE
    rt_kprintf("    %-12s - list devices\n", "device");
#endif /* RT_USING_DEVICE */
#ifdef RT_USING_DFS
    rt_kprintf("    %-12s - list file descriptors\n", "fd");
#endif /* RT_USING_DFS */

    return 0;
}

#else
CMD_OPTIONS_STATEMENT(cmd_list)
static int cmd_list(int argc, char **argv)
{
    if (argc == 2)
    {
        switch (MSH_OPT_ID_GET(cmd_list))
        {
        case RT_Object_Class_Thread: list_thread(); break;
        case RT_Object_Class_Timer: list_timer(); break;
#ifdef RT_USING_SEMAPHORE
        case RT_Object_Class_Semaphore: list_sem(); break;
#endif /* RT_USING_SEMAPHORE */
#ifdef RT_USING_EVENT
        case RT_Object_Class_Event: list_event(); break;
#endif /* RT_USING_EVENT */
#ifdef RT_USING_MUTEX
        case RT_Object_Class_Mutex: list_mutex(); break;
#endif /* RT_USING_MUTEX */
#ifdef RT_USING_MAILBOX
        case RT_Object_Class_MailBox: list_mailbox(); break;
#endif  /* RT_USING_MAILBOX */
#ifdef RT_USING_MESSAGEQUEUE
        case RT_Object_Class_MessageQueue: list_msgqueue(); break;
#endif /* RT_USING_MESSAGEQUEUE */
#ifdef RT_USING_MEMHEAP
        case RT_Object_Class_MemHeap: list_memheap(); break;
#endif /* RT_USING_MEMHEAP */
#ifdef RT_USING_MEMPOOL
        case RT_Object_Class_MemPool: list_mempool(); break;
#endif /* RT_USING_MEMPOOL */
#ifdef RT_USING_DEVICE
        case RT_Object_Class_Device: list_device(); break;
#endif /* RT_USING_DEVICE */
#ifdef RT_USING_DFS
        case LIST_DFS_OPT_ID:
        {
            extern int list_fd(void);
            list_fd();
            break;
        }
#endif /* RT_USING_DFS */
        default:
            goto _usage;
        };

        return 0;
        }

_usage:
    rt_kprintf("Usage: list [options]\n");
    rt_kprintf("[options]:\n");
    MSH_OPT_DUMP(cmd_list);
    return 0;
}
CMD_OPTIONS_NODE_START(cmd_list)
CMD_OPTIONS_NODE(RT_Object_Class_Thread,       thread,   list threads)
CMD_OPTIONS_NODE(RT_Object_Class_Timer,        timer,    list timers)
#ifdef RT_USING_SEMAPHORE
CMD_OPTIONS_NODE(RT_Object_Class_Semaphore,    sem,      list semaphores)
#endif /* RT_USING_SEMAPHORE */
#ifdef RT_USING_EVENT
CMD_OPTIONS_NODE(RT_Object_Class_Event,        event,    list events)
#endif /* RT_USING_EVENT */
#ifdef RT_USING_MUTEX
CMD_OPTIONS_NODE(RT_Object_Class_Mutex,        mutex,    list mutexs)
#endif /* RT_USING_MUTEX */
#ifdef RT_USING_MAILBOX
CMD_OPTIONS_NODE(RT_Object_Class_MailBox,      mailbox,  list mailboxs)
#endif  /* RT_USING_MAILBOX */
#ifdef RT_USING_MESSAGEQUEUE
CMD_OPTIONS_NODE(RT_Object_Class_MessageQueue, msgqueue, list message queues)
#endif /* RT_USING_MESSAGEQUEUE */
#ifdef RT_USING_MEMHEAP
CMD_OPTIONS_NODE(RT_Object_Class_MemHeap,      memheap,  list memory heaps)
#endif /* RT_USING_MEMHEAP */
#ifdef RT_USING_MEMPOOL
CMD_OPTIONS_NODE(RT_Object_Class_MemPool,      mempool,  list memory pools)
#endif /* RT_USING_MEMPOOL */
#ifdef RT_USING_DEVICE
CMD_OPTIONS_NODE(RT_Object_Class_Device,       device,   list devices)
#endif /* RT_USING_DEVICE */
#ifdef RT_USING_DFS
CMD_OPTIONS_NODE(LIST_DFS_OPT_ID,              fd,       list file descriptors)
#endif /* RT_USING_DFS */
CMD_OPTIONS_NODE_END
#endif /* FINSH_USING_OPTION_COMPLETION */
MSH_CMD_EXPORT_ALIAS(cmd_list, list, list objects, optenable);

#endif /* RT_USING_FINSH */
