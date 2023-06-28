#include <rtthread.h>
#include <mp.h>

#define THREAD_PRIORITY      25
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE     5

rt_align(MPU_MIN_REGION_SIZE) rt_uint8_t thread1_private_data[MPU_MIN_REGION_SIZE];

static void thread1_entry(void *parameter)
{
    (void)parameter;
    rt_mem_protection_add_exclusive_region((void *)thread1_private_data, MPU_MIN_REGION_SIZE);
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        // should succeed
        thread1_private_data[i] = i;
    }
}

static void thread2_entry(void *parameter)
{
    (void)parameter;
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        // should fail
        thread1_private_data[i] = i;
    }
}

int mpu_example1()
{
    rt_thread_t tid1 = RT_NULL;
    tid1 = rt_thread_create("thread1",
                           thread1_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    rt_thread_t tid2 = RT_NULL;
    tid2 = rt_thread_create("thread2",
                           thread2_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid1);

    return 0;
}

MSH_CMD_EXPORT(mpu_example1, mpu example 1);
