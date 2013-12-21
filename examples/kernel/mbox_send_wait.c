/*
 * 程序清单：邮箱例程_发送阻塞
 *
 * 这个程序用来测试邮箱发送时候的阻塞情况。
 *
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;

/* 邮箱控制块 */
static struct rt_mailbox mb;
/* 用于放邮件的内存池 */
static char mb_pool[32];

static char mb_str1[] = "I'm a mail!";
static char mb_str2[] = "this is another mail!";

/* 线程1入口 */
static void thread1_entry(void* parameter)
{
    unsigned char* str;

    while (1)
    {
        /* 从邮箱中收取邮件 */
        if (rt_mb_recv(&mb, (rt_uint32_t*)&str, RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_kprintf("thread1: get a mail from mailbox, the content:%s\n", str);

            /* 延时20个OS Tick */
            rt_thread_delay(50);
        }
    }
}

/* 线程2入口 */
static void thread2_entry(void* parameter)
{
    rt_uint8_t count;
    char  *str;

    count = 0;
    while (1)
    {
        count ++;
        if (count & 0x1)
        {
            /* 发送mb_str1地址到邮箱中 */
            str = mb_str1;
        }
        else
        {
            /* 发送mb_str2地址到邮箱中 */
            str = mb_str2;
        }

        /* 不停的发送邮件，如果满了则等待10个tick，然后超时 */
        if( rt_mb_send_wait(&mb, (rt_uint32_t)str,10) == RT_EOK )
            rt_kprintf("thread2: sent a mail to mailbox, the content:%s\n", str);
        else
            rt_kprintf("thread2: timeout while waiting to send a mail.\n");
    }
}

int mbox_send_wait_init()
{
    /* 初始化一个mailbox */
    rt_mb_init(&mb,
               "mbt",             /* 名称是mbt */
               &mb_pool[0],       /* 邮箱用到的内存池是mb_pool */
               sizeof(mb_pool)/4, /* 大小是mb_pool大小除以4，因为一封邮件的大小是4字节 */
               RT_IPC_FLAG_FIFO); /* 采用FIFO方式进行线程等待 */

    /* 创建线程1 */
    tid1 = rt_thread_create("t1",
                            thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
                            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    tid2 = rt_thread_create("t2",
                            thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
                            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 删除线程 */
    if (tid1 != RT_NULL && tid1->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid1);
    if (tid2 != RT_NULL && tid2->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid2);

    /* 执行邮箱对象脱离 */
    rt_mb_detach(&mb);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_mbox_send_wait()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    mbox_send_wait_init();

    /* 返回TestCase运行的最长时间 */
    return 300;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_mbox_send_wait, a example of mailbox send wait);
#else
/* 用户应用入口 */
int rt_application_init()
{
    mbox_send_wait_init();

    return 0;
}
#endif

