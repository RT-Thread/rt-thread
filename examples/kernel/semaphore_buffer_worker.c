/*
 * 程序清单：信号量实现生产者消费者间的互斥
 *
 * 在这个程序中，会创建两个线程，一个是生成者线程worker一个是消费者线程thread
 *
 * 在数据信息生产、消费的过程中，worker负责把数据将写入到环形buffer中，而thread
 * 则从环形buffer中读出。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 一个环形buffer的实现 */
struct rb
{
    rt_uint16_t read_index, write_index;
    rt_uint8_t *buffer_ptr;
    rt_uint16_t buffer_size;
};

/* 指向信号量控制块的指针 */
static rt_sem_t sem = RT_NULL;
/* 指向线程控制块的指针 */
static rt_thread_t tid = RT_NULL, worker = RT_NULL;

/* 环形buffer的内存块（用数组体现出来） */
#define BUFFER_SIZE        256
#define BUFFER_ITEM        32
static rt_uint8_t working_buffer[BUFFER_SIZE];
struct rb working_rb;

/* 初始化环形buffer，size指的是buffer的大小。注：这里并没对数据地址对齐做处理 */
static void rb_init(struct rb* rb, rt_uint8_t *pool, rt_uint16_t size)
{
    RT_ASSERT(rb != RT_NULL);

    /* 对读写指针清零*/
    rb->read_index = rb->write_index = 0;

    /* 设置环形buffer的内存数据块 */
    rb->buffer_ptr = pool;
    rb->buffer_size = size;
}

/* 向环形buffer中写入数据 */
static rt_bool_t rb_put(struct rb* rb, const rt_uint8_t *ptr, rt_uint16_t length)
{
    rt_size_t size;

    /* 判断是否有足够的剩余空间 */
    if (rb->read_index > rb->write_index)
        size = rb->read_index - rb->write_index;
    else
        size = rb->buffer_size - rb->write_index + rb->read_index;

    /* 没有多余的空间 */
    if (size < length) return RT_FALSE;

    if (rb->read_index > rb->write_index)
    {
        /* read_index - write_index 即为总的空余空间 */
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        rb->write_index += length;
    }
    else
    {
        if (rb->buffer_size - rb->write_index > length)
        {
            /* write_index 后面剩余的空间有足够的长度 */
            memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
            rb->write_index += length;
        }
        else
        {
            /*
             * write_index 后面剩余的空间不存在足够的长度，需要把部分数据复制到
             * 前面的剩余空间中
             */
            memcpy(&rb->buffer_ptr[rb->write_index], ptr,
                   rb->buffer_size - rb->write_index);
            memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
                   length - (rb->buffer_size - rb->write_index));
            rb->write_index = length - (rb->buffer_size - rb->write_index);
        }
    }

    return RT_TRUE;
}

/* 从环形buffer中读出数据 */
static rt_bool_t rb_get(struct rb* rb, rt_uint8_t *ptr, rt_uint16_t length)
{
    rt_size_t size;

    /* 判断是否有足够的数据 */
    if (rb->read_index > rb->write_index)
        size = rb->buffer_size - rb->read_index + rb->write_index;
    else
        size = rb->write_index - rb->read_index;

    /* 没有足够的数据 */
    if (size < length) return RT_FALSE;

    if (rb->read_index > rb->write_index)
    {
        if (rb->buffer_size - rb->read_index > length)
        {
            /* read_index的数据足够多，直接复制 */
            memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
            rb->read_index += length;
        }
        else
        {
            /* read_index的数据不够，需要分段复制 */
            memcpy(ptr, &rb->buffer_ptr[rb->read_index],
                   rb->buffer_size - rb->read_index);
            memcpy(&ptr[rb->buffer_size - rb->read_index], &rb->buffer_ptr[0],
                   length - rb->buffer_size + rb->read_index);
            rb->read_index = length - rb->buffer_size + rb->read_index;
        }
    }
    else
    {
        /*
         * read_index要比write_index小，总的数据量够（前面已经有总数据量的判
         * 断），直接复制出数据。
         */
        memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
        rb->read_index += length;
    }

    return RT_TRUE;
}

/* 生产者线程入口 */
static void thread_entry(void* parameter)
{
    rt_bool_t result;
    rt_uint8_t data_buffer[BUFFER_ITEM + 1];

    while (1)
    {
        /* 持有信号量 */
        rt_sem_take(sem, RT_WAITING_FOREVER);
        /* 从环buffer中获得数据 */
        result = rb_get(&working_rb, &data_buffer[0], BUFFER_ITEM);
        /* 释放信号量 */
        rt_sem_release(sem);
        data_buffer[BUFFER_ITEM] = '\0';

        if (result == RT_TRUE)
        {
            /* 获取数据成功，打印数据 */
            rt_kprintf("%s\n", data_buffer);
        }

        /* 做一个5 OS Tick的休眠 */
        rt_thread_delay(5);
    }
}

/* worker线程入口 */
static void worker_entry(void* parameter)
{
    rt_bool_t result;
    rt_uint32_t index, setchar;
    rt_uint8_t  data_buffer[BUFFER_ITEM];

    setchar = 0x21;
    while (1)
    {
        /* 构造数据 */
        for(index = 0; index < BUFFER_ITEM; index++)
        {
            data_buffer[index] = setchar;
            if (++setchar == 0x7f)
                setchar = 0x21;
        }

        /* 持有信号量 */
        rt_sem_take(sem, RT_WAITING_FOREVER);

        /* 把数据放到环形buffer中 */
        result = rb_put(&working_rb, &data_buffer[0], BUFFER_ITEM);
        if (result == RT_FALSE)
        {
            rt_kprintf("put error\n");
        }

        /* 释放信号量 */
        rt_sem_release(sem);

        /* 放入成功，做一个10 OS Tick的休眠 */
        rt_thread_delay(10);
    }
}

int semaphore_buffer_worker_init()
{
    /* 初始化ring buffer */
    rb_init(&working_rb, working_buffer, BUFFER_SIZE);

    /* 创建信号量 */
    sem = rt_sem_create("sem", 1, RT_IPC_FLAG_FIFO);
    if (sem == RT_NULL)
    {
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
        return 0;
    }

    /* 创建线程1 */
    tid = rt_thread_create("thread",
                           thread_entry, RT_NULL, /* 线程入口是thread_entry, 入口参数是RT_NULL */
                           THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    worker = rt_thread_create("worker",
                              worker_entry, RT_NULL, /* 线程入口是worker_entry, 入口参数是RT_NULL */
                              THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (worker != RT_NULL)
        rt_thread_startup(worker);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 删除信号量 */
    if (sem != RT_NULL)
        rt_sem_delete(sem);

    /* 删除线程 */
    if (tid != RT_NULL && tid->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid);
    if (worker != RT_NULL && worker->stat != RT_THREAD_CLOSE)
        rt_thread_delete(worker);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_semaphore_buffer_worker()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    semaphore_buffer_worker_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_semaphore_buffer_worker, a buffer worker with semaphore example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    semaphore_buffer_worker_init();

    return 0;
}
#endif
