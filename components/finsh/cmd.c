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
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#ifdef RT_USING_FINSH
#include <finsh.h>

#define LIST_FIND_OBJ_NR 8

static long clear(void)
{
    rt_kprintf("\x1b[2J\x1b[H");

    return 0;
}
MSH_CMD_EXPORT(clear, clear the terminal screen);

extern void rt_show_version(void);
long version(void)
{
    rt_show_version();

    return 0;
}
MSH_CMD_EXPORT(version, show RT-Thread version information);

rt_inline void object_split(int len)
{
    while (len--) rt_kprintf("-");
}

typedef struct
{
    rt_list_t *list;
    rt_list_t **array;
    rt_uint8_t type;
    int nr;             /* input: max nr, can't be 0 */
    int nr_out;         /* out: got nr */
} list_get_next_t;

static void list_find_init(list_get_next_t *p, rt_uint8_t type, rt_list_t **array, int nr)
{
    struct rt_object_information *info;
    rt_list_t *list;

    info = rt_object_get_information((enum rt_object_class_type)type);
    list = &info->object_list;

    p->list = list;
    p->type = type;
    p->array = array;
    p->nr = nr;
    p->nr_out = 0;
}

static rt_list_t *list_get_next(rt_list_t *current, list_get_next_t *arg)
{
    int first_flag = 0;
    rt_base_t level;
    rt_list_t *node, *list;
    rt_list_t **array;
    int nr;

    arg->nr_out = 0;

    if (!arg->nr || !arg->type)
    {
        return (rt_list_t *)RT_NULL;
    }

    list = arg->list;

    if (!current) /* find first */
    {
        node = list;
        first_flag = 1;
    }
    else
    {
        node = current;
    }

    level = rt_hw_interrupt_disable();

    if (!first_flag)
    {
        struct rt_object *obj;
        /* The node in the list? */
        obj = rt_list_entry(node, struct rt_object, list);
        if ((obj->type & ~RT_Object_Class_Static) != arg->type)
        {
            rt_hw_interrupt_enable(level);
            return (rt_list_t *)RT_NULL;
        }
    }

    nr = 0;
    array = arg->array;
    while (1)
    {
        node = node->next;

        if (node == list)
        {
            node = (rt_list_t *)RT_NULL;
            break;
        }
        nr++;
        *array++ = node;
        if (nr == arg->nr)
        {
            break;
        }
    }

    rt_hw_interrupt_enable(level);
    arg->nr_out = nr;
    return node;
}

long list_thread(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;
    const char *item_title = "thread";
    int maxlen;

    list_find_init(&find_arg, RT_Object_Class_Thread, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

#ifdef RT_USING_SMP
    rt_kprintf("%-*.*s cpu bind pri  status      sp     stack size max used left tick  error\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" --- ---- ---  ------- ---------- ----------  ------  ---------- ---\n");
#else
    rt_kprintf("%-*.*s pri  status      sp     stack size max used left tick  error\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---  ------- ---------- ----------  ------  ---------- ---\n");
#endif /*RT_USING_SMP*/

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_thread thread_info, *thread;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();

                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }
                /* copy info */
                rt_memcpy(&thread_info, obj, sizeof thread_info);
                rt_hw_interrupt_enable(level);

                thread = (struct rt_thread *)obj;
                {
                    rt_uint8_t stat;
                    rt_uint8_t *ptr;

#ifdef RT_USING_SMP
                    if (thread->oncpu != RT_CPU_DETACHED)
                        rt_kprintf("%-*.*s %3d %3d %4d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->oncpu, thread->bind_cpu, thread->current_priority);
                    else
                        rt_kprintf("%-*.*s N/A %3d %4d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->bind_cpu, thread->current_priority);

#else
                    rt_kprintf("%-*.*s %3d ", maxlen, RT_NAME_MAX, thread->parent.name, thread->current_priority);
#endif /*RT_USING_SMP*/
                    stat = (thread->stat & RT_THREAD_STAT_MASK);
                    if (stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
                    else if ((stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK) rt_kprintf(" suspend");
                    else if (stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
                    else if (stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");
                    else if (stat == RT_THREAD_RUNNING) rt_kprintf(" running");

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
                    ptr = (rt_uint8_t *)thread->stack_addr + thread->stack_size - 1;
                    while (*ptr == '#')ptr --;

                    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
                               ((rt_ubase_t)thread->sp - (rt_ubase_t)thread->stack_addr),
                               thread->stack_size,
                               ((rt_ubase_t)ptr - (rt_ubase_t)thread->stack_addr) * 100 / thread->stack_size,
                               thread->remaining_tick,
                               thread->error);
#else
                    ptr = (rt_uint8_t *)thread->stack_addr;
                    while (*ptr == '#') ptr ++;
                    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %s\n",
                               thread->stack_size + ((rt_ubase_t)thread->stack_addr - (rt_ubase_t)thread->sp),
                               thread->stack_size,
                               (thread->stack_size - ((rt_ubase_t) ptr - (rt_ubase_t) thread->stack_addr)) * 100
                               / thread->stack_size,
                               thread->remaining_tick,
                               rt_strerror(thread->error));
#endif
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}

static void show_wait_queue(struct rt_list_node *list)
{
    struct rt_thread *thread;
    struct rt_list_node *node;

    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, tlist);
        rt_kprintf("%.*s", RT_NAME_MAX, thread->parent.name);

        if (node->next != list)
            rt_kprintf("/");
    }
}

#ifdef RT_USING_SEMAPHORE
long list_sem(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "semaphore";

    list_find_init(&find_arg, RT_Object_Class_Semaphore, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s v   suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" --- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_semaphore *sem;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }
                rt_hw_interrupt_enable(level);

                sem = (struct rt_semaphore *)obj;
                if (!rt_list_isempty(&sem->parent.suspend_thread))
                {
                    rt_kprintf("%-*.*s %03d %d:",
                               maxlen, RT_NAME_MAX,
                               sem->parent.parent.name,
                               sem->value,
                               rt_list_len(&sem->parent.suspend_thread));
                    show_wait_queue(&(sem->parent.suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s %03d %d\n",
                               maxlen, RT_NAME_MAX,
                               sem->parent.parent.name,
                               sem->value,
                               rt_list_len(&sem->parent.suspend_thread));
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_SEMAPHORE */

#ifdef RT_USING_EVENT
long list_event(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "event";

    list_find_init(&find_arg, RT_Object_Class_Event, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s      set    suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf("  ---------- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_event *e;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                e = (struct rt_event *)obj;
                if (!rt_list_isempty(&e->parent.suspend_thread))
                {
                    rt_kprintf("%-*.*s  0x%08x %03d:",
                               maxlen, RT_NAME_MAX,
                               e->parent.parent.name,
                               e->set,
                               rt_list_len(&e->parent.suspend_thread));
                    show_wait_queue(&(e->parent.suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s  0x%08x 0\n",
                               maxlen, RT_NAME_MAX, e->parent.parent.name, e->set);
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_EVENT */

#ifdef RT_USING_MUTEX
long list_mutex(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "mutex";

    list_find_init(&find_arg, RT_Object_Class_Mutex, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s   owner  hold priority suspend thread \n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" -------- ---- -------- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_mutex *m;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                m = (struct rt_mutex *)obj;
                if (!rt_list_isempty(&m->parent.suspend_thread))
                {
                    rt_kprintf("%-*.*s %-8.*s %04d %8d  %04d ",
                           maxlen, RT_NAME_MAX,
                           m->parent.parent.name,
                           RT_NAME_MAX,
                           m->owner->parent.name,
                           m->hold,
                           m->priority,
                           rt_list_len(&m->parent.suspend_thread));
                    show_wait_queue(&(m->parent.suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s %-8.*s %04d %8d  %04d\n",
                           maxlen, RT_NAME_MAX,
                           m->parent.parent.name,
                           RT_NAME_MAX,
                           m->owner->parent.name,
                           m->hold,
                           m->priority,
                           rt_list_len(&m->parent.suspend_thread));
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_MUTEX */

#ifdef RT_USING_MAILBOX
long list_mailbox(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "mailbox";

    list_find_init(&find_arg, RT_Object_Class_MailBox, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s entry size suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  ---- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_mailbox *m;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                m = (struct rt_mailbox *)obj;
                if (!rt_list_isempty(&m->parent.suspend_thread))
                {
                    rt_kprintf("%-*.*s %04d  %04d %d:",
                               maxlen, RT_NAME_MAX,
                               m->parent.parent.name,
                               m->entry,
                               m->size,
                               rt_list_len(&m->parent.suspend_thread));
                    show_wait_queue(&(m->parent.suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s %04d  %04d %d\n",
                               maxlen, RT_NAME_MAX,
                               m->parent.parent.name,
                               m->entry,
                               m->size,
                               rt_list_len(&m->parent.suspend_thread));
                }

            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_MAILBOX */

#ifdef RT_USING_MESSAGEQUEUE
long list_msgqueue(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "msgqueue";

    list_find_init(&find_arg, RT_Object_Class_MessageQueue, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s entry suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_messagequeue *m;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                m = (struct rt_messagequeue *)obj;
                if (!rt_list_isempty(&m->parent.suspend_thread))
                {
                    rt_kprintf("%-*.*s %04d  %d:",
                               maxlen, RT_NAME_MAX,
                               m->parent.parent.name,
                               m->entry,
                               rt_list_len(&m->parent.suspend_thread));
                    show_wait_queue(&(m->parent.suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s %04d  %d\n",
                               maxlen, RT_NAME_MAX,
                               m->parent.parent.name,
                               m->entry,
                               rt_list_len(&m->parent.suspend_thread));
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_MESSAGEQUEUE */

#ifdef RT_USING_MEMHEAP
long list_memheap(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "memheap";

    list_find_init(&find_arg, RT_Object_Class_MemHeap, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s  pool size  max used size available size\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---------- ------------- --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_memheap *mh;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                mh = (struct rt_memheap *)obj;

                rt_kprintf("%-*.*s %-010d %-013d %-05d\n",
                           maxlen, RT_NAME_MAX,
                           mh->parent.name,
                           mh->pool_size,
                           mh->max_used_size,
                           mh->available_size);

            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_MEMHEAP */

#ifdef RT_USING_MEMPOOL
long list_mempool(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "mempool";

    list_find_init(&find_arg, RT_Object_Class_MemPool, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s block total free suspend thread\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ----  ----  ---- --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_mempool *mp;
                int suspend_thread_count;
                rt_list_t *node;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                mp = (struct rt_mempool *)obj;

                suspend_thread_count = 0;
                rt_list_for_each(node, &mp->suspend_thread)
                {
                    suspend_thread_count++;
                }

                if (suspend_thread_count > 0)
                {
                    rt_kprintf("%-*.*s %04d  %04d  %04d %d:",
                               maxlen, RT_NAME_MAX,
                               mp->parent.name,
                               mp->block_size,
                               mp->block_total_count,
                               mp->block_free_count,
                               suspend_thread_count);
                    show_wait_queue(&(mp->suspend_thread));
                    rt_kprintf("\n");
                }
                else
                {
                    rt_kprintf("%-*.*s %04d  %04d  %04d %d\n",
                               maxlen, RT_NAME_MAX,
                               mp->parent.name,
                               mp->block_size,
                               mp->block_total_count,
                               mp->block_free_count,
                               suspend_thread_count);
                }
            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_MEMPOOL */

long list_timer(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    int maxlen;
    const char *item_title = "timer";

    list_find_init(&find_arg, RT_Object_Class_Timer, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s  periodic   timeout    activated     mode\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" ---------- ---------- ----------- ---------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_timer *timer;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                timer = (struct rt_timer *)obj;
                rt_kprintf("%-*.*s 0x%08x 0x%08x ",
                           maxlen, RT_NAME_MAX,
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

            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

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

long list_device(void)
{
    rt_base_t level;
    list_get_next_t find_arg;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;
    const char *device_type;

    int maxlen;
    const char *item_title = "device";

    list_find_init(&find_arg, RT_Object_Class_Device, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));

    maxlen = RT_NAME_MAX;

    rt_kprintf("%-*.*s         type         ref count\n", maxlen, maxlen, item_title);
    object_split(maxlen);
    rt_kprintf(" -------------------- ----------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_device *device;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_hw_interrupt_disable();
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_hw_interrupt_enable(level);
                    continue;
                }

                rt_hw_interrupt_enable(level);

                device = (struct rt_device *)obj;
                device_type = "Unknown";
                if (device->type < RT_Device_Class_Unknown &&
                    device_type_str[device->type] != RT_NULL)
                {
                    device_type = device_type_str[device->type];
                }
                rt_kprintf("%-*.*s %-20s %-8d\n",
                           maxlen, RT_NAME_MAX,
                           device->parent.name,
                           device_type,
                           device->ref_count);

            }
        }
    }
    while (next != (rt_list_t *)RT_NULL);

    return 0;
}
#endif /* RT_USING_DEVICE */

int cmd_list(int argc, char **argv)
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
MSH_CMD_EXPORT_ALIAS(cmd_list, list, list objects);

#endif /* RT_USING_FINSH */
