#include "tc_comm.h"
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_TC
#define TC_PRIORITY        25
#define TC_STACK_SIZE    0x400

static rt_uint8_t _tc_stat;
static struct rt_semaphore _tc_sem;
static struct rt_thread _tc_thread;
static rt_uint8_t _tc_stack[TC_STACK_SIZE];
static char _tc_prefix[64];
static const char* _tc_current;
static void (*_tc_cleanup)(void) = RT_NULL;

static rt_uint32_t _tc_scale = 1;
FINSH_VAR_EXPORT(_tc_scale, finsh_type_int, the testcase timer timeout scale)

static rt_uint32_t _tc_loop;

void tc_thread_entry(void* parameter)
{
    unsigned int fail_count = 0;
    struct finsh_syscall* index;

    /* create tc semaphore */
    rt_sem_init(&_tc_sem, "tc", 0, RT_IPC_FLAG_FIFO);

    do {
        for (index = _syscall_table_begin; index < _syscall_table_end; FINSH_NEXT_SYSCALL(index))
        {
            /* search testcase */
            if (rt_strstr(index->name, _tc_prefix) == index->name)
            {
                long tick;

                _tc_current = index->name + 4;
                rt_kprintf("Run TestCase: %s\n", _tc_current);
                _tc_stat = TC_STAT_PASSED | TC_STAT_RUNNING;
                tick = index->func();
                if (tick > 0)
                {
                    /* Make sure we are going to be blocked. */
                    rt_sem_control(&_tc_sem, RT_IPC_CMD_RESET, 0);
                    rt_sem_take(&_tc_sem, tick * _tc_scale);
                }

                if (_tc_cleanup != RT_NULL)
                {
                    /* perform testcase cleanup */
                    _tc_cleanup();
                    _tc_cleanup = RT_NULL;
                }

                if (_tc_stat & TC_STAT_RUNNING)
                {
                    rt_kprintf("TestCase[%s] exit with stat TC_STAT_RUNNING."
                               " Please fix the TC.\n",
                               _tc_current);
                    /* If the TC forgot to clear the flag, we do it. */
                    _tc_stat &= ~TC_STAT_RUNNING;
                }

                if (_tc_stat & TC_STAT_FAILED)
                {
                    rt_kprintf("TestCase[%s] failed\n", _tc_current);
                    fail_count++;
                }
                else
                {
                    rt_kprintf("TestCase[%s] passed\n", _tc_current);
                }
            }
        }
    } while (_tc_loop);

    rt_kprintf("RT-Thread TestCase Running Done!\n");
    if (fail_count)
    {
        rt_kprintf("%d tests failed\n", fail_count);
    }
    else
    {
        rt_kprintf("All tests passed\n");
    }
    /* detach tc semaphore */
    rt_sem_detach(&_tc_sem);
}

void tc_stop()
{
    _tc_loop = 0;

    rt_thread_delay(10 * RT_TICK_PER_SECOND);
    if (_tc_thread.stat != RT_THREAD_INIT)
    {
        /* lock scheduler */
        rt_enter_critical();

        /* detach old tc thread */
        rt_thread_detach(&_tc_thread);
        rt_sem_detach(&_tc_sem);

        /* unlock scheduler */
        rt_exit_critical();
    }
    rt_thread_delay(RT_TICK_PER_SECOND/2);
}
FINSH_FUNCTION_EXPORT(tc_stop, stop testcase thread);

void tc_done(rt_uint8_t stat)
{
    _tc_stat |= stat;
    _tc_stat &= ~TC_STAT_RUNNING;

    /* release semaphore */
    rt_sem_release(&_tc_sem);
}

void tc_stat(rt_uint8_t stat)
{
    if (stat & TC_STAT_FAILED)
    {
        rt_kprintf("TestCases[%s] failed\n", _tc_current);
    }
    _tc_stat |= stat;
}

void tc_cleanup(void (*cleanup)())
{
    _tc_cleanup = cleanup;
}

void tc_start(const char* tc_prefix)
{
    rt_err_t result;

    /* tesecase prefix is null */
    if (tc_prefix == RT_NULL)
    {
        rt_kprintf("TestCase Usage: tc_start(prefix)\n\n");
        rt_kprintf("list_tc() can list all testcases.\n");
        return ;
    }

    /* init tc thread */
    if (_tc_stat & TC_STAT_RUNNING)
    {
        /* stop old tc thread */
        tc_stop();
    }

    rt_memset(_tc_prefix, 0, sizeof(_tc_prefix));
    rt_snprintf(_tc_prefix, sizeof(_tc_prefix), "_tc_%s", tc_prefix);

    result = rt_thread_init(&_tc_thread, "tc",
                            tc_thread_entry, RT_NULL,
                            &_tc_stack[0], sizeof(_tc_stack),
                            TC_PRIORITY - 3, 5);

    /* set tc stat */
    _tc_stat = TC_STAT_RUNNING | TC_STAT_FAILED;

    if (result == RT_EOK)
        rt_thread_startup(&_tc_thread);
}
FINSH_FUNCTION_EXPORT(tc_start, start testcase with testcase prefix or name);

void tc_loop(const char *tc_prefix)
{
    _tc_loop = 1;
    tc_start(tc_prefix);
}
FINSH_FUNCTION_EXPORT(tc_loop, start testcase with testcase prefix or name in loop mode);

void list_tc()
{
    struct finsh_syscall* index;

    rt_kprintf("TestCases List:\n");
    for (index = _syscall_table_begin; index < _syscall_table_end; FINSH_NEXT_SYSCALL(index))
    {
        /* search testcase */
        if (rt_strstr(index->name, "_tc_") == index->name)
        {
#ifdef FINSH_USING_DESCRIPTION
            rt_kprintf("%-16s -- %s\n", index->name + 4, index->desc);
#else
            rt_kprintf("%s\n", index->name + 4);
#endif
        }
    }
}
FINSH_FUNCTION_EXPORT(list_tc, list all testcases);
#endif

