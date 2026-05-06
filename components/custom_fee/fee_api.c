#include "fee_internal.h"

fee_super_ctx_t g_fee_ctx;

static fee_ret_t fee_validate_rw_params(uint8_t *dst, const uint8_t *src, uint16_t len)
{
    if ((len > 0U) && (dst == RT_NULL) && (src == RT_NULL))
    {
        return FEE_E_PARAM;
    }

    return FEE_E_OK;
}

fee_ret_t fee_init(void)
{
    fee_ret_t ret;

    fee_core_reset_context();

    ret = fee_port_init();
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.init_state = FEE_INIT_FAILED;
        g_fee_ctx.status = FEE_STATUS_UNINIT;
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }

    ret = fee_core_init();
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.init_state = FEE_INIT_FAILED;
        g_fee_ctx.status = FEE_STATUS_UNINIT;
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }

    while ((g_fee_ctx.init_state != FEE_INIT_CKPT_READY) &&
           (g_fee_ctx.init_state != FEE_INIT_FULL_READY) &&
           (g_fee_ctx.init_state != FEE_INIT_FAILED))
    {
        ret = fee_recovery_step();
        if (ret != FEE_E_OK)
        {
            g_fee_ctx.init_state = FEE_INIT_FAILED;
            g_fee_ctx.status = FEE_STATUS_UNINIT;
            g_fee_ctx.job_result = FEE_JOB_FAILED;
            return ret;
        }
    }

    g_fee_ctx.job_result = FEE_JOB_OK;
    return FEE_E_OK;
}

fee_ret_t fee_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len)
{
    fee_ret_t ret;

    ret = fee_validate_rw_params(dst, RT_NULL, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return FEE_E_UNINIT;
    }

    return fee_sched_submit_read(block_id, offset, dst, len);
}

fee_ret_t fee_write(uint16_t block_id, const uint8_t *src, uint16_t len)
{
    fee_ret_t ret;

    ret = fee_validate_rw_params(RT_NULL, src, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return FEE_E_UNINIT;
    }

    return fee_sched_submit_write(block_id, src, len);
}

fee_ret_t fee_invalidate(uint16_t block_id)
{
    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return FEE_E_UNINIT;
    }

    return fee_sched_submit_invalidate(block_id);
}

fee_ret_t fee_get_status(uint16_t block_id, fee_block_status_t *status)
{
    const fee_block_cfg_t *cfg;
    fee_cache_entry_t *entry;

    if (status == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return FEE_E_UNINIT;
    }

    cfg = fee_cfg_find_block(block_id);
    if (cfg == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    if (!fee_recovery_can_read_block(block_id))
    {
        return FEE_E_BUSY;
    }

    entry = fee_cache_lookup(block_id);
    if (entry == RT_NULL)
    {
        *status = FEE_BLOCK_STATUS_EMPTY;
        return FEE_E_OK;
    }

    if (entry->cur_valid != 0U)
    {
        *status = FEE_BLOCK_STATUS_VALID;
    }
    else if (entry->prev_valid != 0U)
    {
        *status = FEE_BLOCK_STATUS_INVALIDATED;
    }
    else
    {
        *status = FEE_BLOCK_STATUS_EMPTY;
    }

    return FEE_E_OK;
}

fee_ret_t fee_rollback(uint16_t block_id)
{
    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return FEE_E_UNINIT;
    }

    return fee_sched_submit_rollback(block_id);
}

void fee_mainfunction(void)
{
    if (g_fee_ctx.status == FEE_STATUS_UNINIT)
    {
        return;
    }

    fee_port_mainfunction();

    if (!fee_recovery_is_full_ready())
    {
        (void)fee_recovery_step();
    }

    fee_sched_mainfunction();
    fee_gc_mainfunction();
    fee_core_mainfunction();
}

fee_status_t fee_get_memif_status(void)
{
    return g_fee_ctx.status;
}

fee_job_result_t fee_get_job_result(void)
{
    return g_fee_ctx.job_result;
}

fee_init_state_t fee_get_init_state(void)
{
    return g_fee_ctx.init_state;
}
