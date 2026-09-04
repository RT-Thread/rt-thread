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
#include <rtthread.h>

#ifdef RT_USING_SMP

#include <rtatomic.h>
#include <smp_call.h>
#include <stdlib.h>

#define SMP_TEST_DEFAULT_ROUNDS 100
#define SMP_TEST_STACK_SIZE     4096
#define SMP_TEST_PRIORITY       12
#define SMP_TEST_WAIT_TICK      (RT_TICK_PER_SECOND * 5)

struct smp_test_worker_arg
{
    int cpu;
    int rounds;
    rt_atomic_t *hits;
    rt_atomic_t *errors;
    rt_sem_t done;
};

static rt_atomic_t smp_call_hits[RT_CPUS_NR];
static rt_atomic_t smp_worker_hits[RT_CPUS_NR];
static rt_atomic_t smp_test_errors;

static void smp_test_call(void *parameter)
{
    int cpu = rt_hw_cpu_id();

    RT_UNUSED(parameter);

    if (cpu < 0 || cpu >= RT_CPUS_NR)
    {
        rt_atomic_add(&smp_test_errors, 1);
        return;
    }

    rt_atomic_add(&smp_call_hits[cpu], 1);
}

static void smp_test_worker(void *parameter)
{
    struct smp_test_worker_arg *arg = parameter;
    int i;

    for (i = 0; i < arg->rounds; i++)
    {
        if (rt_hw_cpu_id() != arg->cpu)
        {
            rt_atomic_add(arg->errors, 1);
        }
        rt_atomic_add(&arg->hits[arg->cpu], 1);
        rt_thread_yield();
    }

    rt_sem_release(arg->done);
}

static int smp_test(int argc, char **argv)
{
    int rounds = SMP_TEST_DEFAULT_ROUNDS;
    rt_thread_t workers[RT_CPUS_NR] = { RT_NULL };
    struct smp_test_worker_arg worker_args[RT_CPUS_NR];
    rt_sem_t done = RT_NULL;
    int result = 0;
    int i, cpu, round;

    if (argc > 2)
    {
        rt_kprintf("usage: smp_test [rounds]\n");
        return -RT_EINVAL;
    }

    if (argc == 2)
    {
        rounds = (int)strtoul(argv[1], RT_NULL, 0);
    }

    if (rounds <= 0 || rounds > 100000)
    {
        rt_kprintf("rounds must be in range 1..100000\n");
        return -RT_EINVAL;
    }

    if (RT_CPUS_NR < 2)
    {
        rt_kprintf("smp_test requires at least 2 CPUs\n");
        return -RT_ENOSYS;
    }

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        rt_atomic_store(&smp_call_hits[i], 0);
        rt_atomic_store(&smp_worker_hits[i], 0);
    }
    rt_atomic_store(&smp_test_errors, 0);

    done = rt_sem_create("smpdone", 0, RT_IPC_FLAG_FIFO);
    if (done == RT_NULL)
    {
        rt_kprintf("smp_test: create semaphore failed\n");
        return -RT_ENOMEM;
    }

    /* create and bind every worker before starting any of them */
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        worker_args[i].cpu = i;
        worker_args[i].rounds = rounds;
        worker_args[i].hits = smp_worker_hits;
        worker_args[i].errors = &smp_test_errors;
        worker_args[i].done = done;

        workers[i] = rt_thread_create("smpwrk", smp_test_worker,
                                      &worker_args[i], SMP_TEST_STACK_SIZE,
                                      SMP_TEST_PRIORITY, 10);
        if (workers[i] == RT_NULL ||
            rt_thread_control(workers[i], RT_THREAD_CTRL_BIND_CPU,
                              (void *)(rt_ubase_t)i) != RT_EOK)
        {
            rt_kprintf("smp_test: create/bind worker %d failed\n", i);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        rt_thread_startup(workers[i]);
    }

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        if (rt_sem_take(done, SMP_TEST_WAIT_TICK) != RT_EOK)
        {
            rt_kprintf("smp_test: worker %d timeout\n", i);
            result = -RT_ETIMEOUT;
            goto __exit;
        }
    }

    /* a synchronous SMP call must run exactly once on every selected CPU */
    for (round = 0; round < rounds; round++)
    {
        for (cpu = 0; cpu < RT_CPUS_NR; cpu++)
        {
            rt_smp_call_cpu_mask(1U << cpu, smp_test_call, RT_NULL,
                                 SMP_CALL_WAIT_ALL);
        }
    }

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        rt_atomic_t worker_hits = rt_atomic_load(&smp_worker_hits[i]);
        rt_atomic_t call_hits = rt_atomic_load(&smp_call_hits[i]);

        rt_kprintf("cpu%d: worker=%ld/%d, smp_call=%ld/%d\n", i,
                   (long)worker_hits, rounds, (long)call_hits, rounds);
        if (worker_hits != rounds || call_hits != rounds)
        {
            result = -RT_ERROR;
        }
    }

    if (rt_atomic_load(&smp_test_errors) != 0)
    {
        result = -RT_ERROR;
    }

    rt_kprintf("smp_test: %s (errors=%ld)\n",
               result == 0 ? "PASS" : "FAIL",
               (long)rt_atomic_load(&smp_test_errors));

__exit:
    rt_sem_delete(done);
    return result;
}
MSH_CMD_EXPORT(smp_test, run xiaohui C908 SMP test);

#endif /* RT_USING_SMP */
