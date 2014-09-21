#include <rtthread.h>
#include <board.h>

static void led_thread_entry(void* parameter)
{
    /* Configure GPIO as Output mode */
    GPIO_Init(GPIO_GROUP_GPIO, 0xFFFFFFFF);
    GPIO_EnableOutput(GPIO_GROUP_GPIO, 0x81010101);

    // LED4, 200ns period
    GPIO_InitPwm(GPIO_PWM_CHANNEL_GPIO_31, 100, 100);
    GPIO_EnablePwm(GPIO_PWM_CHANNEL_GPIO_31, TRUE);

    while(1)
    {
        GPIO_Write(GPIO_GROUP_GPIO, 0x01010101, 0x55555555);
        rt_thread_delay(RT_TICK_PER_SECOND/3);
        GPIO_Write(GPIO_GROUP_GPIO, 0x01010101, 0xAAAAAAAA);
        rt_thread_delay(RT_TICK_PER_SECOND/3);
    }
}

static int led_thread_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("led",
                           led_thread_entry,
                           RT_NULL,
                           2048,
                           RT_THREAD_PRIORITY_MAX - 1,
                           1);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(led_thread_init);
