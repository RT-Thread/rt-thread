/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-04     tyx          first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_USER_MAIN
#ifndef RT_MAIN_THREAD_STACK_SIZE
#define RT_MAIN_THREAD_STACK_SIZE     2048
#endif
#ifndef RT_MAIN_THREAD_PRIORITY
#define RT_MAIN_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 3)
#endif
#endif

#ifdef RT_USING_COMPONENTS_INIT
/*
 * Components Initialization will initialize some driver and components as following
 * order:
 * rti_start         --> 0
 * BOARD_EXPORT      --> 1
 * rti_board_end     --> 1.end
 *
 * DEVICE_EXPORT     --> 2
 * COMPONENT_EXPORT  --> 3
 * FS_EXPORT         --> 4
 * ENV_EXPORT        --> 5
 * APP_EXPORT        --> 6
 *
 * rti_end           --> 6.end
 *
 * These automatically initialization, the driver or component initial function must
 * be defined with:
 * INIT_BOARD_EXPORT(fn);
 * INIT_DEVICE_EXPORT(fn);
 * ...
 * INIT_APP_EXPORT(fn);
 * etc.
 */

#pragma section("rti_fn$a", read)
const char __rti_fn_begin_name[] = "__rti_fn_start";
__declspec(allocate("rti_fn$a")) const struct rt_init_desc __rti_fn_begin =
{
    __rti_fn_begin_name,
    NULL
};

#pragma section("rti_fn$z", read)
const char __rti_fn_end_name[] = "__rti_fn_end";
__declspec(allocate("rti_fn$z")) const struct rt_init_desc __rti_fn_end =
{
    __rti_fn_end_name,
    NULL
};

static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "6.end");

struct rt_init_tag
{
    const char *level;
    init_fn_t fn;
#if RT_DEBUG_INIT
    const char *fn_name;
#endif
};

static rt_size_t rt_init_num = 0;
static struct rt_init_tag rt_init_table[2048] = { 0 };
static rt_bool_t rt_init_flag = RT_FALSE;

static int rt_init_objects_sort(void)
{
    rt_size_t index_i, index_j;
    struct rt_init_tag init_temp = { 0 };
    unsigned int *ptr_begin = (unsigned int *)&__rti_fn_begin;
    unsigned int *ptr_end = (unsigned int *)&__rti_fn_end;
    struct rt_init_tag *table = rt_init_table;
    ptr_begin += (sizeof(struct rt_init_desc) / sizeof(unsigned int));

    if (rt_init_flag)
        return rt_init_num;

    while (*ptr_begin == 0)
        ptr_begin++;

    do (ptr_end--);
    while (*ptr_end == 0);

    while (ptr_begin < ptr_end)
    {
        if (*ptr_begin != 0)
        {
            table->level = ((struct rt_init_desc *)ptr_begin)->level;
            table->fn = ((struct rt_init_desc *)ptr_begin)->fn;
#if RT_DEBUG_INIT
            table->fn_name = ((struct rt_init_desc *)ptr_begin)->fn_name;
#endif
            ptr_begin += sizeof(struct rt_init_desc) / sizeof(unsigned int);
            table++;
            rt_init_num += 1;
        }
        else
        {
            ptr_begin++;
        }
    }

    if (rt_init_num == 0) /* no need sort */
        return rt_init_num;

    /* bubble sort algorithms */
    for (index_i = 0; index_i < (rt_init_num - 1); index_i++)
    {
        for (index_j = 0; index_j < ((rt_init_num - 1) - index_i); index_j++)
        {
            if (rt_strcmp(rt_init_table[index_j].level, rt_init_table[index_j + 1].level) > 0)
            {
                init_temp = rt_init_table[index_j];
                rt_init_table[index_j] = rt_init_table[index_j + 1];
                rt_init_table[index_j + 1] = init_temp;
            }
        }
    }

    rt_init_flag = RT_TRUE;
    return rt_init_num;
}

/**
 * RT-Thread Components Initialization for board
 */
void rt_components_board_init(void)
{
    const char* lv_start = ".rti_fn.0";
    const char* lv_end = ".rti_fn.1.end";
    rt_size_t index_i;
    int result;

    rt_init_objects_sort();

    for (index_i = 0; index_i < rt_init_num; index_i++)
    {
        if (rt_init_table[index_i].fn)
        {
            if (rt_strcmp(rt_init_table[index_i].level, lv_end) >= 0)
            {
                break;
            }
#if RT_DEBUG_INIT
            rt_kprintf("initialize %s", rt_init_table[index_i].fn_name);
            result = rt_init_table[index_i].fn();
            rt_kprintf(":%d done\n", result);
#else
            result = rt_init_table[index_i].fn();
#endif
        }
    }
}

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
    const char* lv_start = ".rti_fn.1.end";
    const char* lv_end = ".rti_fn.6.end";
    int result;
    rt_size_t index_i;

    rt_init_objects_sort();

    for (index_i = 0; index_i < rt_init_num; index_i++)
    {
        if (rt_init_table[index_i].fn)
        {
            if (rt_strcmp(rt_init_table[index_i].level, lv_start) <= 0)
            {
                continue;
            }
            if (rt_strcmp(rt_init_table[index_i].level, lv_end) >= 0)
            {
                break;
            }
#if RT_DEBUG_INIT
            rt_kprintf("initialize %s", rt_init_table[index_i].fn_name);
            result = rt_init_table[index_i].fn();
            rt_kprintf(":%d done\n", result);
#else
            result = rt_init_table[index_i].fn();
#endif
        }
    }
}
#endif   /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_USER_MAIN

void rt_application_init(void);
void rt_hw_board_init(void);
int rtthread_startup(void);

#if defined(__ARMCC_VERSION)
extern int $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    rtthread_startup();
    return 0;
}
#elif defined(__ICCARM__)
extern int main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int __low_level_init(void)
{
    // call IAR table copy function.
    __iar_data_init3();
    rtthread_startup();
    return 0;
}
#elif defined(__GNUC__)
/* Add -eentry to arm-none-eabi-gcc argument */
int entry(void)
{
    rtthread_startup();
    return 0;
}
#endif

#ifndef RT_USING_HEAP
/* if there is not enable heap, we should use static thread and stack. */
ALIGN(8)
static rt_uint8_t main_stack[RT_MAIN_THREAD_STACK_SIZE];
struct rt_thread main_thread;
#endif

/* the system main thread */
void main_thread_entry(void *parameter)
{
    extern int main(void);

#ifdef RT_USING_COMPONENTS_INIT
    /* RT-Thread components initialization */
    rt_components_init();
#endif

#ifdef RT_USING_SMP
    rt_hw_secondary_cpu_up();
#endif
    /* invoke system main function */
#if defined(__ARMCC_VERSION)
    {
        extern int $Super$$main(void);
        $Super$$main(); /* for ARMCC. */
    }
#elif defined(__ICCARM__) || defined(__GNUC__) || defined(__TASKING__) || defined(_MSC_VER)
    main();
#endif
}

void rt_application_init(void)
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    tid = rt_thread_create("main", main_thread_entry, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(tid != RT_NULL);
#else
    rt_err_t result;

    tid = &main_thread;
    result = rt_thread_init(tid, "main", main_thread_entry, RT_NULL,
                            main_stack, sizeof(main_stack), RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(result == RT_EOK);

    /* if not define RT_USING_HEAP, using to eliminate the warning */
    (void)result;
#endif

    rt_thread_startup(tid);
}

int rtthread_startup(void)
{
    rt_hw_interrupt_disable();

    /* board level initialization
     * NOTE: please initialize heap inside board initialization.
     */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* timer system initialization */
    rt_system_timer_init();

    /* scheduler system initialization */
    rt_system_scheduler_init();

#ifdef RT_USING_SIGNALS
    /* signal system initialization */
    rt_system_signal_init();
#endif

    /* create init_thread */
    rt_application_init();

    /* timer thread initialization */
    rt_system_timer_thread_init();

    /* idle thread initialization */
    rt_thread_idle_init();

#ifdef RT_USING_SMP
    rt_hw_spin_lock(&_cpus_lock);
#endif /*RT_USING_SMP*/

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return 0;
}
#endif
