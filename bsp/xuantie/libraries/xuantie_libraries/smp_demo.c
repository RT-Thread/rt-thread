/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <rtthread.h>
#include <rthw.h>

static int g_count;
rt_hw_spinlock_t spinlock;

static void thread_entry(void *parameter)
{
    int id;

    while (1) {
        id = rt_hw_cpu_id();
        rt_hw_spin_lock(&spinlock);
        printf("[%s] in %d core, count:%d \r\n", rt_thread_self()->parent.name, id, g_count++);
        rt_hw_spin_unlock(&spinlock);
        rt_thread_mdelay(1000);
    }
}

void smp_example(void)
{
    printf("smp demo start!\r\n");
    rt_hw_spin_lock_init(&spinlock);
    for (long i = 0; i < CONFIG_NR_CPUS; i++) {
        char buf[32];
        rt_thread_t tid;

        snprintf(buf, sizeof(buf), "thread_%ld", i);
        tid = rt_thread_create(buf, thread_entry, RT_NULL, CONFIG_APP_TASK_STACK_SIZE, 10, 5);
        if (tid == RT_NULL) {
            printf("create %s failed!\r\n", buf);
            continue;
        }
        rt_thread_control(tid, RT_THREAD_CTRL_BIND_CPU, (void *)i);
        rt_thread_startup(tid);
    }
}
