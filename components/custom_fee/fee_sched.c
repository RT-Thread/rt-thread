#include "fee_internal.h"

fee_ret_t fee_sched_submit_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len)
{
    return fee_core_read(block_id, offset, dst, len);
}

fee_ret_t fee_sched_submit_write(uint16_t block_id, const uint8_t *src, uint16_t len)
{
    fee_ret_t ret;

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    ret = fee_core_write(block_id, src, len);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.status = fee_recovery_is_full_ready() ? FEE_STATUS_IDLE : FEE_STATUS_BUSY_INTERNAL;
        g_fee_ctx.job_result = FEE_JOB_FAILED;
    }

    return ret;
}

fee_ret_t fee_sched_submit_invalidate(uint16_t block_id)
{
    fee_ret_t ret;

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    ret = fee_core_invalidate(block_id);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.status = fee_recovery_is_full_ready() ? FEE_STATUS_IDLE : FEE_STATUS_BUSY_INTERNAL;
        g_fee_ctx.job_result = FEE_JOB_FAILED;
    }

    return ret;
}

fee_ret_t fee_sched_submit_rollback(uint16_t block_id)
{
    fee_ret_t ret;

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    ret = fee_core_rollback(block_id);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.status = fee_recovery_is_full_ready() ? FEE_STATUS_IDLE : FEE_STATUS_BUSY_INTERNAL;
        g_fee_ctx.job_result = FEE_JOB_FAILED;
    }

    return ret;
}

void fee_sched_mainfunction(void)
{
}
