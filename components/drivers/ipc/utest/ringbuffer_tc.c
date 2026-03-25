/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-16     RyanCW       add ringbuffer utest
 */

/**
 * Test Case Name: IPC Ringbuffer Test
 *
 * Test Objectives:
 * - Validate basic ringbuffer APIs and boundary behavior.
 * - Cover put_force overwrite paths (drop-length <, =, > tail).
 * - Reproduce legacy put_force corner cases in wrapped state.
 * - Ensure peek does not consume data and get_direct consumes data.
 *
 * Test Scenarios:
 * - Alignment and init checks, including minimum aligned size.
 * - Basic put/get/peek and zero-length operations.
 * - Put boundaries (exact full, overflow truncation, oversize input).
 * - putchar/putchar_force on full buffer (including tail-index path).
 * - Wrap-around read/write, peek contiguous segment.
 * - Tail-equals-length edges for put/peek/get_direct.
 * - put_force oversize keeps latest bytes.
 * - put_force overwrite correctness with drop-length branches.
 * - Deterministic stress with a reference model.
 *
 * Dependencies:
 * - RT_USING_UTEST must be enabled (select "RT-Thread Utestcases").
 * - RT_UTEST_RINGBUFFER must be enabled (Kernel Components -> Drivers -> IPC Test).
 */

#include <utest.h>
#include <ipc/ringbuffer.h>
#include <stdlib.h>

#define RINGBUFFER_ALIGN_POOL_SIZE 18
#define RINGBUFFER_POOL_SIZE       16
#define RINGBUFFER_WRAP_POOL_SIZE  8

#define RINGBUFFER_REF_MAX         64
#define RINGBUFFER_STRESS_SIZE     32
#define RINGBUFFER_STRESS_STEPS    300
#define RINGBUFFER_STRESS_DATA_MAX (RINGBUFFER_REF_MAX * 2)
#define RINGBUFFER_STRESS_SEED     0x1A2B3C4Du

/*
 * Reference model for stress test.
 *
 * Semantics we assume (used as expected behavior):
 * - put: write up to available space, drop the remainder.
 * - put_force: always accept all bytes; if overflow, drop oldest bytes and
 *   keep the latest data with total length == buffer size.
 * - get/getchar: consume data in FIFO order.
 * - peek: return the first contiguous readable segment without consuming.
 *
 * These helpers are file-local and not part of RT APIs. If model and
 * implementation disagree, the mismatch indicates either a bug or a spec
 * mismatch that needs review.
 */
struct rb_ref
{
    rt_uint8_t buf[RINGBUFFER_REF_MAX];
    rt_uint32_t size;
    rt_uint32_t head;
    rt_uint32_t len;
};

/* Reference model helpers (file-local). */
static void rb_ref_init(struct rb_ref *ref, rt_uint32_t size)
{
    RT_ASSERT(ref != RT_NULL);
    RT_ASSERT(size <= RINGBUFFER_REF_MAX);

    ref->size = size;
    ref->head = 0;
    ref->len = 0;
}

static rt_uint32_t rb_ref_tail(const struct rb_ref *ref)
{
    return (ref->head + ref->len) % ref->size;
}

static rt_size_t rb_ref_put(struct rb_ref *ref, const rt_uint8_t *data, rt_uint32_t len)
{
    rt_uint32_t space;
    rt_uint32_t tail;
    rt_uint32_t first;

    if (len == 0)
        return 0;

    space = ref->size - ref->len;
    if (space == 0)
        return 0;

    if (len > space)
        len = space;

    tail = rb_ref_tail(ref);
    first = ref->size - tail;
    if (first > len)
        first = len;

    rt_memcpy(&ref->buf[tail], data, first);
    if (len > first)
        rt_memcpy(&ref->buf[0], data + first, len - first);

    ref->len += len;
    return len;
}

static rt_size_t rb_ref_put_force(struct rb_ref *ref, const rt_uint8_t *data, rt_uint32_t len)
{
    rt_uint32_t space;
    rt_uint32_t drop;
    rt_uint32_t tail;
    rt_uint32_t first;

    if (len == 0)
        return 0;

    if (len > ref->size)
    {
        data = &data[len - ref->size];
        len = ref->size;
    }

    space = ref->size - ref->len;
    if (len > space)
    {
        drop = len - space;
        ref->head = (ref->head + drop) % ref->size;
        ref->len -= drop;
    }

    tail = rb_ref_tail(ref);
    first = ref->size - tail;
    if (first > len)
        first = len;

    rt_memcpy(&ref->buf[tail], data, first);
    if (len > first)
        rt_memcpy(&ref->buf[0], data + first, len - first);

    ref->len += len;
    return len;
}

static rt_size_t rb_ref_get(struct rb_ref *ref, rt_uint8_t *out, rt_uint32_t len)
{
    rt_uint32_t first;

    if (len == 0 || ref->len == 0)
        return 0;

    if (len > ref->len)
        len = ref->len;

    first = ref->size - ref->head;
    if (first > len)
        first = len;

    rt_memcpy(out, &ref->buf[ref->head], first);
    if (len > first)
        rt_memcpy(out + first, &ref->buf[0], len - first);

    ref->head = (ref->head + len) % ref->size;
    ref->len -= len;
    return len;
}

static rt_size_t rb_ref_peek(struct rb_ref *ref, rt_uint8_t *out)
{
    rt_uint32_t first;
    rt_uint32_t len;

    if (ref->len == 0)
        return 0;

    first = ref->size - ref->head;
    len = ref->len < first ? ref->len : first;
    rt_memcpy(out, &ref->buf[ref->head], len);
    return len;
}

/* Verify size alignment, minimum aligned size, and full write behavior after init. */
static void ringbuffer_align_tc(void)
{
    rt_uint8_t pool_align[RINGBUFFER_ALIGN_POOL_SIZE] = {0};
    struct rt_ringbuffer rb_align;
    rt_uint32_t align_size;
    rt_uint32_t expect_size;
    rt_uint8_t data[RINGBUFFER_ALIGN_POOL_SIZE] = {0};

    rt_ringbuffer_init(&rb_align, pool_align, sizeof(pool_align));
    align_size = rt_ringbuffer_get_size(&rb_align);
    expect_size = RT_ALIGN_DOWN(sizeof(pool_align), RT_ALIGN_SIZE);
    uassert_int_equal(align_size, expect_size);

    for (rt_uint32_t i = 0; i < align_size; i++)
        data[i] = (rt_uint8_t)i;

    uassert_int_equal(rt_ringbuffer_put(&rb_align, data, align_size), align_size);
    uassert_int_equal(rt_ringbuffer_data_len(&rb_align), align_size);

    /* Minimum aligned size should be accepted. */
    {
        rt_uint8_t min_pool[RT_ALIGN_SIZE] = {0};
        struct rt_ringbuffer rb_min;

        rt_ringbuffer_init(&rb_min, min_pool, sizeof(min_pool));
        uassert_int_equal(rt_ringbuffer_get_size(&rb_min), RT_ALIGN_SIZE);
    }
}

/* Validate empty-buffer behaviors and zero-length operations. */
static void ringbuffer_basic_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint32_t size;
    rt_uint8_t *peek_ptr = RT_NULL;
    rt_uint8_t *direct_ptr = RT_NULL;
    rt_size_t peek_len;
    rt_uint8_t out[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint8_t ch = 0;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    size = rt_ringbuffer_get_size(&rb);
    uassert_int_equal(size, sizeof(pool));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
    uassert_int_equal(rt_ringbuffer_space_len(&rb), size);

    peek_len = rt_ringbuffer_peek(&rb, &peek_ptr);
    uassert_int_equal(peek_len, 0);
    uassert_ptr_equal(peek_ptr, RT_NULL);

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), 0);
    uassert_int_equal(rt_ringbuffer_getchar(&rb, &ch), 0);
    uassert_int_equal(rt_ringbuffer_get_direct(&rb, &direct_ptr), 0);
    uassert_ptr_equal(direct_ptr, RT_NULL);

    uassert_int_equal(rt_ringbuffer_put(&rb, out, 0), 0);
    uassert_int_equal(rt_ringbuffer_put_force(&rb, out, 0), 0);
}

/* Validate put/peek/get; peek must not consume data. */
static void ringbuffer_put_peek_get_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data1[] = {1, 2, 3, 4, 5};
    rt_uint8_t out[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint8_t *peek_ptr = RT_NULL;
    rt_size_t peek_len;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, data1, sizeof(data1)), sizeof(data1));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), sizeof(data1));

    peek_len = rt_ringbuffer_peek(&rb, &peek_ptr);
    uassert_int_equal(peek_len, sizeof(data1));
    uassert_ptr_equal(peek_ptr, pool);
    uassert_buf_equal(peek_ptr, data1, sizeof(data1));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), sizeof(data1));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(data1));
    uassert_buf_equal(out, data1, sizeof(data1));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
}

/* Verify putchar/getchar FIFO behavior and length updates. */
static void ringbuffer_putchar_getchar_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t ch = 0;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_putchar(&rb, 0x11), 1);
    uassert_int_equal(rt_ringbuffer_putchar(&rb, 0x22), 1);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 2);
    uassert_int_equal(rt_ringbuffer_space_len(&rb), rt_ringbuffer_get_size(&rb) - 2);

    uassert_int_equal(rt_ringbuffer_getchar(&rb, &ch), 1);
    uassert_int_equal(ch, 0x11);
    uassert_int_equal(rt_ringbuffer_getchar(&rb, &ch), 1);
    uassert_int_equal(ch, 0x22);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
}

/* Verify reset clears content and restores space. */
static void ringbuffer_reset_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data[] = {1, 2, 3, 4};
    rt_uint8_t *peek_ptr = RT_NULL;
    rt_size_t peek_len;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    uassert_int_equal(rt_ringbuffer_put(&rb, data, sizeof(data)), sizeof(data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), sizeof(data));

    rt_ringbuffer_reset(&rb);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
    uassert_int_equal(rt_ringbuffer_space_len(&rb), rt_ringbuffer_get_size(&rb));

    peek_len = rt_ringbuffer_peek(&rb, &peek_ptr);
    uassert_int_equal(peek_len, 0);
    uassert_ptr_equal(peek_ptr, RT_NULL);
}

/* Verify put boundaries: exact full, overflow truncation, and oversize input. */
static void ringbuffer_put_boundary_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t full_data[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint8_t data2[12];
    rt_uint8_t data3[8];
    rt_uint8_t expect_overflow[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint8_t big_data[RINGBUFFER_POOL_SIZE + 4];
    rt_uint8_t expect_big[RINGBUFFER_POOL_SIZE];
    rt_uint8_t out[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint32_t size;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    size = rt_ringbuffer_get_size(&rb);

    for (rt_uint32_t i = 0; i < sizeof(full_data); i++)
        full_data[i] = (rt_uint8_t)i;

    uassert_int_equal(rt_ringbuffer_put(&rb, full_data, sizeof(full_data)), size);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);
    uassert_int_equal(rt_ringbuffer_put(&rb, full_data, 1), 0);

    /* Reset and verify overflow truncation behavior. */
    rt_ringbuffer_reset(&rb);

    for (rt_uint32_t i = 0; i < sizeof(data2); i++)
        data2[i] = (rt_uint8_t)(10 + i);
    for (rt_uint32_t i = 0; i < sizeof(data3); i++)
        data3[i] = (rt_uint8_t)(30 + i);

    uassert_int_equal(rt_ringbuffer_put(&rb, data2, sizeof(data2)), sizeof(data2));
    uassert_int_equal(rt_ringbuffer_put(&rb, data3, sizeof(data3)), 4);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);
    uassert_int_equal(rt_ringbuffer_space_len(&rb), 0);

    rt_memcpy(expect_overflow, data2, sizeof(data2));
    rt_memcpy(&expect_overflow[sizeof(data2)], data3, 4);

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), size);
    uassert_buf_equal(out, expect_overflow, size);

    /* Reset and verify single oversize put keeps the first size bytes. */
    rt_ringbuffer_reset(&rb);
    for (rt_uint32_t i = 0; i < sizeof(big_data); i++)
        big_data[i] = (rt_uint8_t)(80 + i);
    rt_memcpy(expect_big, big_data, sizeof(expect_big));

    uassert_int_equal(rt_ringbuffer_put(&rb, big_data, sizeof(big_data)), size);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), size);
    uassert_buf_equal(out, expect_big, size);
}

/* Verify get boundaries: length > data and length == 0. */
static void ringbuffer_get_boundary_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data[] = {1, 2, 3, 4};
    rt_uint8_t out[RINGBUFFER_POOL_SIZE] = {0};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    uassert_int_equal(rt_ringbuffer_put(&rb, data, sizeof(data)), sizeof(data));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(data));
    uassert_buf_equal(out, data, sizeof(data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);

    /* Reset and verify get(0) does not consume data. */
    rt_ringbuffer_reset(&rb);
    uassert_int_equal(rt_ringbuffer_put(&rb, data, sizeof(data)), sizeof(data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 0), 0);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), sizeof(data));
}

/* Verify put_force without overflow when write wraps; FIFO order preserved. */
static void ringbuffer_put_force_no_overflow_wrap_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data_a[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t data_b[] = {10, 11, 12, 13};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect[] = {4, 5, 6, 10, 11, 12, 13};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, data_a, sizeof(data_a)),
                      sizeof(data_a));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 3), 3);
    uassert_buf_equal(out, data_a, 3);

    uassert_int_equal(rt_ringbuffer_put_force(&rb, data_b, sizeof(data_b)),
                      sizeof(data_b));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 7);

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(expect)), sizeof(expect));
    uassert_buf_equal(out, expect, sizeof(expect));
}

/* Verify putchar on full fails and putchar_force overwrites oldest byte. */
static void ringbuffer_putchar_force_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t out[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint8_t expect_full[RINGBUFFER_POOL_SIZE] = {0};
    rt_uint32_t size;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    size = rt_ringbuffer_get_size(&rb);

    for (rt_uint32_t i = 0; i < size; i++)
    {
        rt_size_t res = rt_ringbuffer_putchar(&rb, (rt_uint8_t)i);
        if (i == 0)
            uassert_int_equal(res, 1);
    }

    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);
    uassert_int_equal(rt_ringbuffer_putchar(&rb, 0xEE), 0);
    uassert_int_equal(rt_ringbuffer_put(&rb, out, 1), 0);

    uassert_int_equal(rt_ringbuffer_putchar_force(&rb, 0xA5), 1);

    for (rt_uint32_t i = 0; i < size - 1; i++)
        expect_full[i] = (rt_uint8_t)(i + 1);
    expect_full[size - 1] = 0xA5;

    uassert_int_equal(rt_ringbuffer_get(&rb, out, size), size);
    uassert_buf_equal(out, expect_full, size);
}

/* Verify putchar_force full-buffer path when write_index is at tail. */
static void ringbuffer_putchar_force_tail_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t full_data[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t refill[] = {10, 11, 12, 13, 14, 15, 16};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect[] = {10, 11, 12, 13, 14, 15, 16, 0xAA};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    for (rt_uint32_t i = 0; i < sizeof(full_data); i++)
        full_data[i] = (rt_uint8_t)i;

    uassert_int_equal(rt_ringbuffer_put(&rb, full_data, sizeof(full_data)),
                      sizeof(full_data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 7), 7);
    uassert_buf_equal(out, full_data, 7);

    uassert_int_equal(rt_ringbuffer_put(&rb, refill, sizeof(refill)),
                      sizeof(refill));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_putchar_force(&rb, 0xAA), 1);
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect, sizeof(expect));
}

/* Verify wrap-around order and contiguous peek segment. */
static void ringbuffer_wrap_peek_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t w1[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t w2[] = {10, 11, 12, 13, 14, 15};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t *peek_ptr = RT_NULL;
    rt_size_t peek_len;
    rt_uint8_t expect_peek[] = {5, 6, 10, 11};
    rt_uint8_t expect_tail[] = {12, 13, 14, 15};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, w1, sizeof(w1)), sizeof(w1));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 4), 4);
    uassert_buf_equal(out, w1, 4);

    uassert_int_equal(rt_ringbuffer_put(&rb, w2, sizeof(w2)), sizeof(w2));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    peek_len = rt_ringbuffer_peek(&rb, &peek_ptr);
    uassert_int_equal(peek_len, 4);
    uassert_ptr_equal(peek_ptr, &pool[4]);
    uassert_buf_equal(peek_ptr, expect_peek, sizeof(expect_peek));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, 4), 4);
    uassert_buf_equal(out, expect_peek, sizeof(expect_peek));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, 4), 4);
    uassert_buf_equal(out, expect_tail, sizeof(expect_tail));
}

/* Verify tail-equals-length edges (tail = buffer end) and empty offset. */
static void ringbuffer_tail_equal_len_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data1[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t data2[] = {7, 8};
    rt_uint8_t full[] = {1, 2, 3, 4, 5, 6, 7, 8};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t *ptr = RT_NULL;
    rt_size_t len;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    /* Put with length exactly equal to tail space should wrap correctly. */
    uassert_int_equal(rt_ringbuffer_put(&rb, data1, sizeof(data1)), sizeof(data1));
    uassert_int_equal(rt_ringbuffer_put(&rb, data2, sizeof(data2)), sizeof(data2));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, full, sizeof(full));

    /* Empty buffer with non-zero indices should still work. */
    rt_ringbuffer_reset(&rb);
    uassert_int_equal(rt_ringbuffer_put(&rb, data1, sizeof(data1)), sizeof(data1));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(data1)), sizeof(data1));
    uassert_int_equal(rt_ringbuffer_put(&rb, data2, sizeof(data2)), sizeof(data2));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(data2)), sizeof(data2));
    uassert_buf_equal(out, data2, sizeof(data2));

    /* Peek/get_direct when tail equals length should return the last segment. */
    rt_ringbuffer_reset(&rb);
    uassert_int_equal(rt_ringbuffer_put(&rb, full, sizeof(full)), sizeof(full));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 6), 6);

    len = rt_ringbuffer_peek(&rb, &ptr);
    uassert_int_equal(len, 2);
    uassert_ptr_equal(ptr, &pool[6]);
    uassert_buf_equal(ptr, &full[6], 2);

    len = rt_ringbuffer_get_direct(&rb, &ptr);
    uassert_int_equal(len, 2);
    uassert_ptr_equal(ptr, &pool[6]);
    uassert_buf_equal(ptr, &full[6], 2);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
}

/* Verify oversize put_force keeps latest bytes on empty and non-empty buffers. */
static void ringbuffer_force_oversize_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t exist[] = {1, 2, 3};
    rt_uint8_t big_data[12];
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect_over[8] = {5, 6, 7, 8, 9, 10, 11, 12};
    rt_uint32_t size;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    size = rt_ringbuffer_get_size(&rb);

    for (rt_uint32_t i = 0; i < sizeof(big_data); i++)
        big_data[i] = (rt_uint8_t)(1 + i);

    /* Oversize write on empty buffer keeps the latest bytes. */
    uassert_int_equal(rt_ringbuffer_put_force(&rb, big_data, sizeof(big_data)),
                      size);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect_over, sizeof(expect_over));

    /* Oversize write drops existing data and keeps latest bytes. */
    rt_ringbuffer_reset(&rb);
    uassert_int_equal(rt_ringbuffer_put(&rb, exist, sizeof(exist)), sizeof(exist));

    uassert_int_equal(rt_ringbuffer_put_force(&rb, big_data, sizeof(big_data)),
                      size);
    uassert_int_equal(rt_ringbuffer_data_len(&rb), size);

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect_over, sizeof(expect_over));
}

/* Reproduce wrapped-state put_force overwrite bug (white-box seed). */
static void ringbuffer_force_wrapped_bug_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t force_data[] = {60, 61, 62, 63, 64};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect_force[] = {52, 53, 54, 60, 61, 62, 63, 64};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    /*
     * Seed a wrapped state (write_index < read_index, mirrors equal).
     * This white-box setup makes the legacy bug deterministic.
     */
    rb.read_mirror = 0;
    rb.write_mirror = 0;
    rb.read_index = 5;
    rb.write_index = 2;

    pool[5] = 50;
    pool[6] = 51;
    pool[7] = 52;
    pool[0] = 53;
    pool[1] = 54;

    uassert_int_equal(rt_ringbuffer_put_force(&rb, force_data, sizeof(force_data)),
                      sizeof(force_data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect_force, sizeof(expect_force));
}

/* Verify drop_length < tail with no write wrap; order preserved. */
static void ringbuffer_force_drop_less_tail_nowrap_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t fill_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    rt_uint8_t force_wrap[] = {20, 21, 22, 23, 24, 25, 26};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect_wrap[8] = {8, 20, 21, 22, 23, 24, 25, 26};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, fill_data, sizeof(fill_data)),
                      sizeof(fill_data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 6), 6);

    uassert_int_equal(rt_ringbuffer_put_force(&rb, force_wrap, sizeof(force_wrap)),
                      sizeof(force_wrap));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect_wrap, sizeof(expect_wrap));
}

/* Verify drop_length > tail; read mirror flips and order preserved. */
static void ringbuffer_force_drop_greater_tail_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t fill_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    rt_uint8_t add_data[4] = {10, 11, 12, 13};
    rt_uint8_t force_data[5] = {20, 21, 22, 23, 24};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect[8] = {11, 12, 13, 20, 21, 22, 23, 24};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, fill_data, sizeof(fill_data)),
                      sizeof(fill_data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 6), 6);
    uassert_int_equal(rt_ringbuffer_put(&rb, add_data, sizeof(add_data)),
                      sizeof(add_data));

    uassert_int_equal(rt_ringbuffer_put_force(&rb, force_data, sizeof(force_data)),
                      sizeof(force_data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect, sizeof(expect));
}

/* Verify drop_length < tail with write wrap; order preserved. */
static void ringbuffer_force_drop_less_tail_wrap_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t fill_data[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t force_data[] = {10, 11, 12, 13, 14, 15, 16};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    rt_uint8_t expect[] = {6, 10, 11, 12, 13, 14, 15, 16};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, fill_data, sizeof(fill_data)),
                      sizeof(fill_data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 2), 2);

    uassert_int_equal(rt_ringbuffer_put_force(&rb, force_data, sizeof(force_data)),
                      sizeof(force_data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, expect, sizeof(expect));
}

/* Verify get_direct consumes data and returns contiguous segment. */
static void ringbuffer_get_direct_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t data[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t *ptr = RT_NULL;
    rt_size_t len;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, data, sizeof(data)), sizeof(data));
    len = rt_ringbuffer_get_direct(&rb, &ptr);
    uassert_int_equal(len, sizeof(data));
    uassert_not_null(ptr);
    uassert_buf_equal(ptr, data, sizeof(data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
}

/* Verify get_direct on wrapped buffer returns two segments. */
static void ringbuffer_get_direct_wrap_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t w1[] = {1, 2, 3, 4, 5, 6};
    rt_uint8_t w2[] = {10, 11, 12, 13, 14, 15};
    rt_uint8_t out[4] = {0};
    rt_uint8_t *ptr = RT_NULL;
    rt_size_t len;
    rt_uint8_t expect_first[] = {5, 6, 10, 11};
    rt_uint8_t expect_second[] = {12, 13, 14, 15};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, w1, sizeof(w1)), sizeof(w1));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_int_equal(rt_ringbuffer_put(&rb, w2, sizeof(w2)), sizeof(w2));

    len = rt_ringbuffer_get_direct(&rb, &ptr);
    uassert_int_equal(len, sizeof(expect_first));
    uassert_ptr_equal(ptr, &pool[4]);
    uassert_buf_equal(ptr, expect_first, sizeof(expect_first));

    len = rt_ringbuffer_get_direct(&rb, &ptr);
    uassert_int_equal(len, sizeof(expect_second));
    uassert_ptr_equal(ptr, &pool[0]);
    uassert_buf_equal(ptr, expect_second, sizeof(expect_second));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), 0);
}

/* Verify drop_length == tail; read index lands on buffer end. */
static void ringbuffer_force_drop_equal_tail_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_WRAP_POOL_SIZE] = {0};
    struct rt_ringbuffer rb;
    rt_uint8_t fill_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    rt_uint8_t force_data[8] = {10, 11, 12, 13, 14, 15, 16, 17};
    rt_uint8_t out[RINGBUFFER_WRAP_POOL_SIZE] = {0};

    rt_ringbuffer_init(&rb, pool, sizeof(pool));

    uassert_int_equal(rt_ringbuffer_put(&rb, fill_data, sizeof(fill_data)),
                      sizeof(fill_data));
    uassert_int_equal(rt_ringbuffer_get(&rb, out, 7), 7);

    uassert_int_equal(rt_ringbuffer_put_force(&rb, force_data, sizeof(force_data)),
                      sizeof(force_data));
    uassert_int_equal(rt_ringbuffer_data_len(&rb), rt_ringbuffer_get_size(&rb));

    uassert_int_equal(rt_ringbuffer_get(&rb, out, sizeof(out)), sizeof(out));
    uassert_buf_equal(out, force_data, sizeof(force_data));
}

#ifdef RT_USING_HEAP
/* Verify heap-based create/destroy paths. */
static void ringbuffer_heap_tc(void)
{
    struct rt_ringbuffer *rb = rt_ringbuffer_create(RINGBUFFER_POOL_SIZE);
    struct rt_ringbuffer *rb_align = RT_NULL;
    struct rt_ringbuffer *rb_min = RT_NULL;

    uassert_not_null(rb);
    if (rb == RT_NULL)
        return;

    uassert_int_equal(rt_ringbuffer_get_size(rb), RINGBUFFER_POOL_SIZE);
    rt_ringbuffer_destroy(rb);

    rb_align = rt_ringbuffer_create(RINGBUFFER_ALIGN_POOL_SIZE);
    uassert_not_null(rb_align);
    if (rb_align == RT_NULL)
        return;

    uassert_int_equal(rt_ringbuffer_get_size(rb_align),
                      RT_ALIGN_DOWN(RINGBUFFER_ALIGN_POOL_SIZE, RT_ALIGN_SIZE));
    rt_ringbuffer_destroy(rb_align);

    rb_min = rt_ringbuffer_create(RT_ALIGN_SIZE);
    uassert_not_null(rb_min);
    if (rb_min == RT_NULL)
        return;

    uassert_int_equal(rt_ringbuffer_get_size(rb_min), RT_ALIGN_SIZE);
    rt_ringbuffer_destroy(rb_min);
}
#endif

/* Deterministic stress test against reference model. */
static void ringbuffer_stress_tc(void)
{
    rt_uint8_t pool[RINGBUFFER_STRESS_SIZE] = {0};
    struct rt_ringbuffer rb;
    struct rb_ref ref;
    rt_uint32_t seed = RINGBUFFER_STRESS_SEED;
    rt_uint8_t tmp_exp[RINGBUFFER_REF_MAX] = {0};
    rt_uint8_t tmp_got[RINGBUFFER_REF_MAX] = {0};
    rt_uint8_t data[RINGBUFFER_STRESS_DATA_MAX] = {0};
    rt_bool_t ok = RT_TRUE;
    rt_uint32_t fail_step = 0;
    rt_uint32_t fail_op = 0;
    rt_uint32_t exp = 0;
    rt_uint32_t got = 0;

    rt_ringbuffer_init(&rb, pool, sizeof(pool));
    rb_ref_init(&ref, RINGBUFFER_STRESS_SIZE);
    srand((unsigned int)seed);

    for (rt_uint32_t i = 0; i < RINGBUFFER_STRESS_STEPS; i++)
    {
        rt_uint32_t op = (rt_uint32_t)(rand() % 7);
        fail_step = i;
        fail_op = op;

        if (op == 0)
        {
            rt_uint32_t len = (rt_uint32_t)(rand() % (RINGBUFFER_STRESS_SIZE * 2)) + 1;
            for (rt_uint32_t j = 0; j < len; j++)
                data[j] = (rt_uint8_t)(rand() & 0xFF);
            exp = (rt_uint32_t)rb_ref_put(&ref, data, len);
            got = (rt_uint32_t)rt_ringbuffer_put(&rb, data, len);
            if (exp != got)
            {
                ok = RT_FALSE;
                break;
            }
        }
        else if (op == 1)
        {
            rt_uint32_t len = (rt_uint32_t)(rand() % (RINGBUFFER_STRESS_SIZE * 2)) + 1;
            for (rt_uint32_t j = 0; j < len; j++)
                data[j] = (rt_uint8_t)(rand() & 0xFF);
            exp = (rt_uint32_t)rb_ref_put_force(&ref, data, len);
            got = (rt_uint32_t)rt_ringbuffer_put_force(&rb, data, len);
            if (exp != got)
            {
                ok = RT_FALSE;
                break;
            }
        }
        else if (op == 2)
        {
            rt_uint8_t ch = (rt_uint8_t)(rand() & 0xFF);
            exp = (rt_uint32_t)rb_ref_put(&ref, &ch, 1);
            got = (rt_uint32_t)rt_ringbuffer_putchar(&rb, ch);
            if (exp != got)
            {
                ok = RT_FALSE;
                break;
            }
        }
        else if (op == 3)
        {
            rt_uint8_t ch = (rt_uint8_t)(rand() & 0xFF);
            exp = (rt_uint32_t)rb_ref_put_force(&ref, &ch, 1);
            got = (rt_uint32_t)rt_ringbuffer_putchar_force(&rb, ch);
            if (exp != got)
            {
                ok = RT_FALSE;
                break;
            }
        }
        else if (op == 4)
        {
            rt_uint32_t len = (rt_uint32_t)(rand() % (RINGBUFFER_STRESS_SIZE * 2)) + 1;
            exp = (rt_uint32_t)rb_ref_get(&ref, tmp_exp, len);
            got = (rt_uint32_t)rt_ringbuffer_get(&rb, tmp_got, len);
            if (exp != got || (exp > 0 && rt_memcmp(tmp_exp, tmp_got, exp) != 0))
            {
                ok = RT_FALSE;
                break;
            }
        }
        else if (op == 5)
        {
            rt_uint8_t ch_exp = 0;
            rt_uint8_t ch_got = 0;
            exp = (rt_uint32_t)rb_ref_get(&ref, &ch_exp, 1);
            got = (rt_uint32_t)rt_ringbuffer_getchar(&rb, &ch_got);
            if (exp != got || (exp == 1 && ch_exp != ch_got))
            {
                ok = RT_FALSE;
                break;
            }
        }
        else
        {
            rt_uint8_t *ptr = RT_NULL;
            exp = (rt_uint32_t)rb_ref_peek(&ref, tmp_exp);
            got = (rt_uint32_t)rt_ringbuffer_peek(&rb, &ptr);
            if (exp != got)
            {
                ok = RT_FALSE;
                break;
            }
            if (exp == 0)
            {
                if (ptr != RT_NULL)
                {
                    ok = RT_FALSE;
                    break;
                }
            }
            else
            {
                if (ptr == RT_NULL || rt_memcmp(ptr, tmp_exp, exp) != 0)
                {
                    ok = RT_FALSE;
                    break;
                }
            }
        }

        if ((rt_uint32_t)rt_ringbuffer_data_len(&rb) != ref.len)
        {
            ok = RT_FALSE;
            break;
        }
        if ((rt_uint32_t)rt_ringbuffer_space_len(&rb) != (ref.size - ref.len))
        {
            ok = RT_FALSE;
            break;
        }
    }

    if (!ok)
    {
        LOG_E("Ringbuffer stress failed: seed=%u step=%u op=%u exp=%u got=%u len=%u",
              (unsigned)seed, (unsigned)fail_step, (unsigned)fail_op,
              (unsigned)exp, (unsigned)got, (unsigned)ref.len);
    }
    uassert_true(ok);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(ringbuffer_align_tc);
    UTEST_UNIT_RUN(ringbuffer_basic_tc);
    UTEST_UNIT_RUN(ringbuffer_put_peek_get_tc);
    UTEST_UNIT_RUN(ringbuffer_putchar_getchar_tc);
    UTEST_UNIT_RUN(ringbuffer_reset_tc);
    UTEST_UNIT_RUN(ringbuffer_put_boundary_tc);
    UTEST_UNIT_RUN(ringbuffer_get_boundary_tc);
    UTEST_UNIT_RUN(ringbuffer_put_force_no_overflow_wrap_tc);
    UTEST_UNIT_RUN(ringbuffer_putchar_force_tc);
    UTEST_UNIT_RUN(ringbuffer_putchar_force_tail_tc);
    UTEST_UNIT_RUN(ringbuffer_wrap_peek_tc);
    UTEST_UNIT_RUN(ringbuffer_tail_equal_len_tc);
    UTEST_UNIT_RUN(ringbuffer_force_oversize_tc);
    UTEST_UNIT_RUN(ringbuffer_force_wrapped_bug_tc);
    UTEST_UNIT_RUN(ringbuffer_force_drop_less_tail_nowrap_tc);
    UTEST_UNIT_RUN(ringbuffer_force_drop_greater_tail_tc);
    UTEST_UNIT_RUN(ringbuffer_force_drop_less_tail_wrap_tc);
    UTEST_UNIT_RUN(ringbuffer_get_direct_tc);
    UTEST_UNIT_RUN(ringbuffer_get_direct_wrap_tc);
    UTEST_UNIT_RUN(ringbuffer_force_drop_equal_tail_tc);
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(ringbuffer_heap_tc);
#endif
    UTEST_UNIT_RUN(ringbuffer_stress_tc);
}

UTEST_TC_EXPORT(testcase, "components.drivers.ipc.ringbuffer", RT_NULL, RT_NULL, 10);
