/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

int main(int argc, char **argv)
{
    rt_kprintf("Hello RK2108 RT-Thread!\n");

    return RT_EOK;
}

void _start()
{
    extern int rtthread_startup(void);

    rtthread_startup();
}
