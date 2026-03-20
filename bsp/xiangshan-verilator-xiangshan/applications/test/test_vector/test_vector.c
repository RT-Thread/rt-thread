/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <rthw.h>
#include <string.h>
#include <stdlib.h>

#if defined(RT_USING_UTEST) && defined(ENABLE_VECTOR)
#include <utest.h>
#include <ext_context.h>

void rt_hw_vector_ctx_restore(void *buf);
void rt_hw_vector_ctx_save(void *buf);

/**
 * ==============================================================
 * TEST FEATURE
 * Use libc `memcpy` which employing V extension codes
 * to test V extension features
 * ==============================================================
 */
static char *constant = "hello,it's a nice day and i'm happy to see you\n";
#define ARR_SIZE 4096
static char array[ARR_SIZE];

static void test_feature(void)
{
    memcpy(array, constant, sizeof array);
    char *src = constant;
    char *dst = array;
    int error = 0;

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        if (src[i] != dst[i])
        {
            error = 1;
            break;
        }
    }

    uassert_false(error);
}

/**
 * ==============================================================
 * TEST CONTEXT SAVING
 * Create 2 threads employing V extension, verify V states are
 * not modified by each other
 * ==============================================================
 */
#define TEST_THREAD 2
#define VECTOR_CTX_BYTES (CTX_VECTOR_REG_NR * REGBYTES)
void *ctx_vector[TEST_THREAD * 2];

static rt_sem_t sem;

void dump_frame(void *frame)
{
    uint64_t *content = frame;
    for (size_t i = 0; i < VECTOR_CTX_BYTES / 8; i++)
    {
        rt_kprintf("%x ", content[i]);
    }
    rt_kprintf("\n");
}

static void vector_child(void *param)
{
    void **ctx = param;
    uint64_t *reg = ctx[0];
    uint64_t vtype;
    uint64_t vl;

    rt_sem_release(sem);

    rt_hw_vector_ctx_restore(ctx[0]);

    /* STAGE 2, save t2 context */
    test_feature();

    /**
     * @brief vtype & vl will be modified after context saving,
     * it's ok because it will be recover after context restoring
     * We restore these states manually here.
     */
    asm volatile("csrr %0, vtype":"=r"(vtype));
    asm volatile("csrr %0, vl":"=r"(vl));
    rt_hw_vector_ctx_save(ctx[0]);

    rt_memcpy(ctx[1], ctx[0], VECTOR_CTX_BYTES);

    rt_thread_yield();

    asm volatile("vsetvl x0, %0, %1"::"r"(vl), "r"(vtype));
    rt_hw_vector_ctx_save(ctx[0]);

    uassert_false(rt_memcmp(ctx[1], ctx[0], VECTOR_CTX_BYTES));
}

/**
 * @brief Test if context save/restore codes work properly
 */
static void test_context()
{
    rt_thread_t child;
    uint64_t vtype;
    uint64_t vl;

    for (size_t i = 0; i < TEST_THREAD; i++)
    {
        ctx_vector[i * 2] = calloc(VECTOR_CTX_BYTES, 1);
        ctx_vector[i * 2 + 1] = calloc(VECTOR_CTX_BYTES, 1);
    }
    rt_hw_vector_ctx_restore(ctx_vector[0]);

    child = rt_thread_create("test_vector_child", vector_child, &ctx_vector[2], 4096, 10, 20);

    /* STAGE 1, save t1 context */
    /* assuming that rt libc memcpy do not use vector instruction */
    asm volatile("csrr %0, vtype":"=r"(vtype));
    asm volatile("csrr %0, vl":"=r"(vl));
    rt_hw_vector_ctx_save(ctx_vector[0]);

    rt_memcpy(ctx_vector[1], ctx_vector[0], VECTOR_CTX_BYTES);

    rt_thread_startup(child);
    rt_sem_take(sem, 0);

    /* STAGE 3, verify t1 context */
    asm volatile("vsetvl x0, %0, %1"::"r"(vl), "r"(vtype));
    rt_hw_vector_ctx_save(ctx_vector[0]);
    uassert_false(rt_memcmp(ctx_vector[1], ctx_vector[0], VECTOR_CTX_BYTES));

    rt_thread_yield();
}

/**
 * ==============================================================
 * TEST NO VECTOR raise error and recover
 * ==============================================================
 */

static void test_no_vector()
{
    asm volatile ("li t0, 0x600\n"
                "csrc sstatus, t0");
    test_feature();
    uassert_true(1);
}

static rt_err_t utest_tc_init(void)
{
    sem = rt_sem_create("test_ctx", 0, RT_IPC_FLAG_FIFO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_delete(sem);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_feature);
    UTEST_UNIT_RUN(test_context);
    UTEST_UNIT_RUN(test_no_vector);
}

UTEST_TC_EXPORT(testcase, "testcases.libcpu.vector", utest_tc_init, utest_tc_cleanup, 10);
#endif /* RT_USING_UTEST && ENABLE_VECTOR */
