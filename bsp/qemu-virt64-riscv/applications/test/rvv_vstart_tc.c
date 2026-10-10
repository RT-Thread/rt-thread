/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-10     Piyush Patle  Test zero and nonzero RVV restart indices
 */

#include <rtthread.h>

/* Run rvv_vstart_test in msh, or testcases.libcpu.rvv_vstart with UTest. */
#if defined(ENABLE_VECTOR) && (defined(RT_USING_UTEST) || defined(FINSH_USING_MSH))
#include "rvv_context.h"

/* RV64 vector frames contain four control words followed by v0 through v31. */
#define VECTOR_CONTROL_WORDS 4
#define VECTOR_GUARD         0x5a5a5a5aUL

struct vector_test_frame
{
    rt_ubase_t before[2];
    rt_ubase_t image[CTX_VECTOR_REG_NR];
    rt_ubase_t after[2];
};

static struct vector_test_frame expected;
static struct vector_test_frame observed;
static struct vector_test_frame saved;

void rvv_vstart_probe(const rt_ubase_t *input, rt_ubase_t *output, rt_ubase_t *backup);

static void frame_init(struct vector_test_frame *frame)
{
    rt_memset(frame, 0, sizeof(*frame));
    frame->before[0] = frame->before[1] = VECTOR_GUARD;
    frame->after[0] = frame->after[1] = VECTOR_GUARD;
}

static rt_bool_t frame_guards_valid(const struct vector_test_frame *frame)
{
    return frame->before[0] == VECTOR_GUARD && frame->before[1] == VECTOR_GUARD &&
           frame->after[0] == VECTOR_GUARD && frame->after[1] == VECTOR_GUARD;
}

static int rvv_vstart_test(void)
{
    rt_ubase_t vlenb;
    rt_ubase_t starts[3];
    rt_uint8_t *payload = (rt_uint8_t *)&expected.image[VECTOR_CONTROL_WORDS];
    rt_size_t payload_size = sizeof(expected.image) - VECTOR_CONTROL_WORDS * sizeof(rt_ubase_t);
    rt_size_t i;
    rt_size_t j;

    __asm__ volatile("csrr %0, vlenb" : "=r"(vlenb));
    if (payload_size != 32 * vlenb)
    {
        rt_kprintf("RVV test: configured frame does not match vlenb=%lu\n", vlenb);
        return -RT_ERROR;
    }

    frame_init(&expected);
    for (i = 0; i < payload_size; i++)
    {
        payload[i] = (rt_uint8_t)(i * 37 + i / vlenb + 0x5a);
    }

    starts[0] = 0;
    starts[1] = 1;
    starts[2] = vlenb - 1;

    for (i = 0; i < sizeof(starts) / sizeof(starts[0]); i++)
    {
        for (j = 0; j < 3; j++)
        {
            expected.image[0] = starts[i];
            expected.image[1] = 0;       /* e8, m1, tail/mask undisturbed */
            expected.image[2] = vlenb;
            expected.image[3] = j * 3;  /* Exercise vxrm and vxsat through vcsr. */
            frame_init(&observed);
            frame_init(&saved);

            rvv_vstart_probe(expected.image, observed.image, saved.image);

            if (!frame_guards_valid(&expected) || !frame_guards_valid(&observed) ||
                !frame_guards_valid(&saved) ||
                rt_memcmp(expected.image, observed.image, sizeof(expected.image)) != 0)
            {
                rt_kprintf("RVV restore failed: vstart expected=%lu observed=%lu\n",
                           starts[i], observed.image[0]);
                return -RT_ERROR;
            }
        }
    }

    rt_kprintf("RVV restore passed: vlenb=%lu, 9 control/register checks\n", vlenb);
    return RT_EOK;
}

#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(rvv_vstart_test, Test RVV restart index and complete frame restoration);
#endif

#ifdef RT_USING_UTEST
#include <utest.h>

static void testcase(void)
{
    uassert_int_equal(rvv_vstart_test(), RT_EOK);
}

UTEST_TC_EXPORT(testcase, "testcases.libcpu.rvv_vstart", RT_NULL, RT_NULL, 10);
#endif
#endif
