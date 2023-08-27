#include <rtthread.h>
#include <mp.h>

#define THREAD_PRIORITY      25
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE     5

rt_align(MPU_MIN_REGION_SIZE) rt_uint8_t ro_data[MPU_MIN_REGION_SIZE];

static void thread1_entry(void *parameter)
{
    (void)parameter;
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        ro_data[i] = i;
        rt_kprintf("ro_data[%d] = %d\n", i, ro_data[i]);
    }
    rt_mem_region_t ro_region = {
        .start = (void *)ro_data,
        .size = MPU_MIN_REGION_SIZE,
        .attr = RT_MEM_REGION_P_RO_U_RO,
    };
    rt_mem_protection_add_region(RT_NULL, &ro_region);
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        // should succeed
        rt_kprintf("ro_data[%d] = %d\n", i, ro_data[i]);
    }
    rt_thread_delay(RT_TICK_PER_SECOND * 1);
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        // should fail
        ro_data[i] = i;
    }
}

static void thread2_entry(void *parameter)
{
    (void)parameter;
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        // should succeed
        ro_data[i] = i;
    }
}

int mpu_example2()
{
    rt_thread_t tid1 = RT_NULL;
    tid1 = rt_thread_create("thread1",
                           thread1_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY - 1,
                           THREAD_TIMESLICE);
    rt_thread_startup(tid1);
    rt_thread_t tid2 = RT_NULL;
    tid2 = rt_thread_create("thread2",
                           thread2_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);
    rt_thread_startup(tid2);

    return 0;
}

MSH_CMD_EXPORT(mpu_example2, mpu example 2);
