/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     hqfang       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <nuclei_sdk_hal.h>

#ifdef RT_USING_SERIAL
/* Currently UART IRQ is not connected,
 * So I use task to interact with uart input
 */
#define SERIAL_THREAD_STACK_SIZE    396
static rt_uint8_t serial_stack[SERIAL_THREAD_STACK_SIZE];
static struct rt_thread serial_tid;
extern void rt_hw_serial_rcvtsk(void *parameter);

void board_serial_init(void)
{
    rt_thread_init(&serial_tid, "serrxsim", rt_hw_serial_rcvtsk,
            (void *)NULL, serial_stack, SERIAL_THREAD_STACK_SIZE, 5, 5);
    rt_thread_startup(&serial_tid);
}
#endif  /* RT_USING_SERIAL */

int main(void)
{
#ifdef RT_USING_SERIAL
    board_serial_init();
#endif  /* RT_USING_SERIAL */
}

/******************** end of file *******************/

