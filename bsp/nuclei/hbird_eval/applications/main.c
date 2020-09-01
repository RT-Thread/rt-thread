/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-23     tyustli      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <nuclei_sdk_hal.h>

#define THREAD_PRIORITY 19
#define THREAD_STACK_SIZE 396
#define THREAD_TIMESLICE 5
#define THREAD_NUM       2
// #define APP_DEBUG_PRINT

/*　Align stack when using static thread　*/
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_stack[THREAD_NUM][THREAD_STACK_SIZE];
static struct rt_thread tid[THREAD_NUM];

/* Thread entry function */
static void thread_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1) {
#ifdef APP_DEBUG_PRINT
        rt_kprintf("thread %d count: %d\n", (rt_uint32_t)parameter, count++);
#endif
        rt_thread_mdelay(500);
        if (((uint32_t)parameter) % 2) {
            gpio_toggle(GPIO, SOC_LED_BLUE_GPIO_MASK);
        } else {
            gpio_toggle(GPIO, SOC_LED_GREEN_GPIO_MASK);
        }
    }
}

/* Thread demo */
int create_thread_demo(void)
{
    int i;
    static char tname[9] = "thread";
    
    for (i = 0; i < THREAD_NUM; i ++) {
        /* Create static threads */
        tname[6] = i/10 + '0';
        tname[7] = i%10 + '0';
        tname[8] = '\0';
        rt_thread_init(&tid[i], tname, thread_entry, (void *)i, thread_stack[i],
                   THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    }

    /* Startup threads  */
    for (i = 0; i < THREAD_NUM; i ++) {
        rt_thread_startup(&tid[i]);
    }

    return 0;
}

void board_gpio_init(void)
{
    gpio_enable_input(GPIO, SOC_BUTTON_GPIO_MASK);
    gpio_set_pue(GPIO, SOC_BUTTON_GPIO_MASK, GPIO_BIT_ALL_ONE);

    gpio_enable_output(GPIO, SOC_LED_GPIO_MASK);
    gpio_write(GPIO, SOC_LED_GPIO_MASK, GPIO_BIT_ALL_ZERO);
}

#ifdef RT_USING_SERIAL

#define SERIAL_THREAD_STACK_SIZE 396
static rt_uint8_t serial_stack[SERIAL_THREAD_STACK_SIZE];
static struct rt_thread serial_tid;
extern void rt_hw_serial_thread_entry(void *parameter);

void board_serial_init(void)
{
    rt_thread_init(&serial_tid, "serrxsim", rt_hw_serial_thread_entry,
            (void *)NULL, serial_stack, SERIAL_THREAD_STACK_SIZE, 5, 5);
    rt_thread_startup(&serial_tid);
}
#endif  /* RT_USING_SERIAL */

int main(void)
{
    rt_uint32_t count = 0;

    board_gpio_init();
    create_thread_demo();

#ifdef RT_USING_SERIAL
    board_serial_init();
#endif  /* RT_USING_SERIAL */

    while (1) {
#ifdef APP_DEBUG_PRINT
        rt_kprintf("Main thread count: %d\n", count++);
#endif
        rt_thread_mdelay(1000);
        gpio_toggle(GPIO, SOC_LED_RED_GPIO_MASK);
    }
}

/******************** end of file *******************/

