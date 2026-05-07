#include <string.h>
#include "rtthread.h"
#include "finsh.h"
#include "fee_api.h"
#include "fee_cfg.h"
#include "fee_port.h"

#define FEE_TEST_POLL_BUDGET      (20000U)
#define FEE_TEST_GC_WRITE_COUNT   (160U)

static int fee_test_wait_full_ready(uint32_t budget)
{
    while (budget > 0U)
    {
        fee_init_state_t state = fee_get_init_state();

        if (state == FEE_INIT_FULL_READY)
        {
            return 0;
        }

        if (state == FEE_INIT_FAILED)
        {
            return -1;
        }

        fee_mainfunction();
        --budget;
    }

    return -1;
}

static int fee_test_wait_idle(uint32_t budget)
{
    while (budget > 0U)
    {
        fee_job_result_t job_result;

        fee_mainfunction();
        job_result = fee_get_job_result();

        if ((fee_get_init_state() == FEE_INIT_FULL_READY) &&
            (fee_get_memif_status() == FEE_STATUS_IDLE) &&
            (job_result != FEE_JOB_PENDING))
        {
            return (job_result == FEE_JOB_FAILED) ? -1 : 0;
        }

        if ((fee_get_init_state() == FEE_INIT_FAILED) || (job_result == FEE_JOB_FAILED))
        {
            return -1;
        }

        --budget;
    }

    return -1;
}

static void fee_test_fill_pattern(uint8_t *buf, uint16_t len, uint8_t seed)
{
    uint16_t idx;

    for (idx = 0U; idx < len; ++idx)
    {
        buf[idx] = (uint8_t)(seed + (uint8_t)(idx * 3U));
    }
}

static int fee_test_expect_ret(const char *step, fee_ret_t actual, fee_ret_t expected)
{
    if (actual != expected)
    {
        rt_kprintf("custom_fee_test: %s failed, ret=%u expected=%u\n",
            step, (unsigned)actual, (unsigned)expected);
        return -1;
    }

    return 0;
}

static int fee_test_expect_readback(uint16_t block_id, const uint8_t *expect, uint16_t len)
{
    uint8_t readback[FEE_CFG_MAX_BLOCK_LEN];
    fee_ret_t ret;

    if (len > (uint16_t)sizeof(readback))
    {
        rt_kprintf("custom_fee_test: readback len too large: %u\n", (unsigned)len);
        return -1;
    }

    (void)memset(readback, 0, sizeof(readback));
    ret = fee_read(block_id, 0U, readback, len);
    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: fee_read block=%u ret=%u\n",
            (unsigned)block_id, (unsigned)ret);
        return -1;
    }

    if (memcmp(readback, expect, len) != 0)
    {
        rt_kprintf("custom_fee_test: readback mismatch on block=%u\n", (unsigned)block_id);
        return -1;
    }

    return 0;
}

static int fee_test_reset_backend(void)
{
    fee_flash_caps_t caps;
    uint32_t used_bytes;
    uint32_t idx;
    fee_ret_t ret;

    ret = fee_port_init();
    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: fee_port_init failed ret=%u\n", (unsigned)ret);
        return -1;
    }

    ret = fee_port_get_caps(&caps);
    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: fee_port_get_caps failed ret=%u\n", (unsigned)ret);
        return -1;
    }

    used_bytes = fee_cfg_get_total_sector_count() * caps.erase_unit;
    if (used_bytes > caps.total_size)
    {
        rt_kprintf("custom_fee_test: backend too small, used=0x%08x total=0x%08x\n",
            (unsigned)used_bytes, (unsigned)caps.total_size);
        return -1;
    }

    for (idx = 0U; idx < fee_cfg_get_total_sector_count(); ++idx)
    {
        ret = fee_port_erase(idx * caps.erase_unit, caps.erase_unit);
        if (ret != FEE_E_OK)
        {
            rt_kprintf("custom_fee_test: erase sector=%u failed ret=%u\n",
                (unsigned)idx, (unsigned)ret);
            return -1;
        }
    }

    return 0;
}

int custom_fee_test(void)
{
    uint8_t fast_a[32];
    uint8_t fast_b[32];
    uint8_t normal_a[64];
    fee_block_status_t status;
    uint32_t idx;

    rt_kprintf("custom_fee_test: start\n");

    fee_test_fill_pattern(fast_a, (uint16_t)sizeof(fast_a), 0x11U);
    fee_test_fill_pattern(fast_b, (uint16_t)sizeof(fast_b), 0x51U);
    fee_test_fill_pattern(normal_a, (uint16_t)sizeof(normal_a), 0x21U);

    if (fee_test_reset_backend() != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("fee_init", fee_init(), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_full_ready(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: init did not reach FULL_READY\n");
        return -1;
    }

    if (fee_test_expect_ret("write fast_a", fee_write(1U, fast_a, (uint16_t)sizeof(fast_a)), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: write fast_a did not complete\n");
        return -1;
    }

    if (fee_test_expect_readback(1U, fast_a, (uint16_t)sizeof(fast_a)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("write fast_b", fee_write(1U, fast_b, (uint16_t)sizeof(fast_b)), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: write fast_b did not complete\n");
        return -1;
    }

    if (fee_test_expect_readback(1U, fast_b, (uint16_t)sizeof(fast_b)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("rollback block1", fee_rollback(1U), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: rollback did not complete\n");
        return -1;
    }

    if (fee_test_expect_readback(1U, fast_a, (uint16_t)sizeof(fast_a)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("write normal_a", fee_write(2U, normal_a, (uint16_t)sizeof(normal_a)), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: write normal_a did not complete\n");
        return -1;
    }

    if (fee_test_expect_readback(2U, normal_a, (uint16_t)sizeof(normal_a)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("re-init", fee_init(), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_full_ready(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: recovery init did not reach FULL_READY\n");
        return -1;
    }

    if (fee_test_expect_readback(1U, fast_a, (uint16_t)sizeof(fast_a)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_readback(2U, normal_a, (uint16_t)sizeof(normal_a)) != 0)
    {
        return -1;
    }

    for (idx = 0U; idx < FEE_TEST_GC_WRITE_COUNT; ++idx)
    {
        fee_test_fill_pattern(fast_b, (uint16_t)sizeof(fast_b), (uint8_t)(0x60U + idx));

        if (fee_test_expect_ret("gc stress write", fee_write(1U, fast_b, (uint16_t)sizeof(fast_b)), FEE_E_OK) != 0)
        {
            rt_kprintf("custom_fee_test: gc stress failed at iter=%u\n", (unsigned)idx);
            return -1;
        }

        if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
        {
            rt_kprintf("custom_fee_test: gc stress did not complete at iter=%u\n", (unsigned)idx);
            return -1;
        }
    }

    fee_test_fill_pattern(fast_b, (uint16_t)sizeof(fast_b), (uint8_t)(0x60U + (FEE_TEST_GC_WRITE_COUNT - 1U)));
    if (fee_test_expect_readback(1U, fast_b, (uint16_t)sizeof(fast_b)) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("invalidate block1", fee_invalidate(1U), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET) != 0)
    {
        rt_kprintf("custom_fee_test: invalidate did not complete\n");
        return -1;
    }

    if (fee_test_expect_ret("get_status", fee_get_status(1U, &status), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (status != FEE_BLOCK_STATUS_INVALIDATED)
    {
        rt_kprintf("custom_fee_test: expected INVALIDATED, got %u\n", (unsigned)status);
        return -1;
    }

    if (fee_test_expect_ret("read invalidated", fee_read(1U, 0U, fast_a, (uint16_t)sizeof(fast_a)), FEE_E_NOT_OK) != 0)
    {
        return -1;
    }

    rt_kprintf("custom_fee_test: PASS\n");
    return 0;
}
MSH_CMD_EXPORT(custom_fee_test, custom fee smoke test);
