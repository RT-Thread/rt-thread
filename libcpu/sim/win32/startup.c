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
INIT_EXPORT(rti_board_end, "1_end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "6_end");

/**
 * Find next init function
 */
static const struct rt_init_desc* rt_init_find_next(const char* lv,
    unsigned int* begin, unsigned int* end)
{
    const struct rt_init_desc* ptr;
    const struct rt_init_desc* ret_ptr = RT_NULL;

    while (begin < end)
    {
        if (*begin != 0)
        {
            ptr = (const struct rt_init_desc*)begin;
            if (ret_ptr != RT_NULL)
            {
                if (rt_strcmp(lv, ptr->level) < 0 &&
                    rt_strcmp(ret_ptr->level, ptr->level) > 0)
                {
                    ret_ptr = ptr;
                }
            }
            else
            {
                if (rt_strcmp(lv, ptr->level) < 0)
                {
                    ret_ptr = ptr;
                }
            }
            begin += (sizeof(struct rt_init_desc) / sizeof(unsigned int));
        }
        else
        {
            begin++;
        }
    }
    return ret_ptr;
}

/**
 * RT-Thread Components Initialization for board
 */
void rt_components_board_init(void)
{
    const struct rt_init_desc* ptr;
    const char* lv_start = "0__rt_init_rti_start";
    const char* lv_end = "1_end__rt_init_rti_board_end";
    unsigned int* ptr_begin = (unsigned int*)&__rti_fn_begin;
    unsigned int* ptr_end = (unsigned int*)&__rti_fn_end;
    int result;

    ptr_begin += (sizeof(struct rt_init_desc) / sizeof(unsigned int));
    while (*ptr_begin == 0) ptr_begin++;
    do ptr_end--; while (*ptr_end == 0);

    while (1)
    {
        ptr = rt_init_find_next(lv_start, ptr_begin, ptr_end);
        if (ptr == RT_NULL ||
            rt_strcmp(ptr->level, lv_end) >= 0)
        {
            break;
        }
        if (ptr->fn)
        {
#if RT_DEBUG_INIT
            rt_kprintf("initialize %s", ptr->fn_name);
            result = ptr->fn();
            rt_kprintf(":%d done\n", result);
#else
            result = ptr->fn();
#endif
        }
        lv_start = ptr->level;
    };
}

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
    const struct rt_init_desc* ptr;
    const char* lv_start = "1_end__rt_init_rti_board_end";
    const char* lv_end = "6_end__rt_init_rti_end";
    unsigned int* ptr_begin = (unsigned int*)&__rti_fn_begin;
    unsigned int* ptr_end = (unsigned int*)&__rti_fn_end;
    int result;

    ptr_begin += (sizeof(struct rt_init_desc) / sizeof(unsigned int));
    while (*ptr_begin == 0) ptr_begin++;
    do ptr_end--; while (*ptr_end == 0);

    while (1)
    {
        ptr = rt_init_find_next(lv_start, ptr_begin, ptr_end);
        if (ptr == RT_NULL ||
            rt_strcmp(ptr->level, lv_end) >= 0)
        {
            break;
        }
        if (ptr->fn)
        {
#if RT_DEBUG_INIT
            rt_kprintf("initialize %s", ptr->fn_name);
            result = ptr->fn();
            rt_kprintf(":%d done\n", result);
#else
            result = ptr->fn();
#endif
        }
        lv_start = ptr->level;
    };
}
#endif   /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_USER_MAIN

void rt_application_init(void);
void rt_hw_board_init(void);
int rtthread_startup(void);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
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
#if defined(__CC_ARM) || defined(__CLANG_ARM)
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
