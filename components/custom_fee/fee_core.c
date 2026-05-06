#include "fee_internal.h"

static fee_ret_t fee_core_read_header(uint32_t addr, fee_record_header_t *header)
{
    return fee_port_read(addr, (uint8_t *)header, (uint32_t)sizeof(*header));
}

static fee_ret_t fee_core_read_tail(uint32_t addr, uint16_t data_len, fee_commit_tail_t *tail)
{
    uint32_t stored_len = fee_onflash_align_up((uint32_t)data_len, FEE_CFG_ALIGN_UNIT);
    uint32_t tail_addr = addr + (uint32_t)sizeof(fee_record_header_t) + stored_len;

    return fee_port_read(tail_addr, (uint8_t *)tail, (uint32_t)sizeof(*tail));
}

static uint32_t fee_core_record_next_addr(const fee_block_cfg_t *cfg, uint16_t data_len)
{
    return fee_onflash_calc_record_span(cfg, data_len);
}

static fee_ret_t fee_core_append_record(uint16_t block_id, const uint8_t *src, uint16_t len,
    uint8_t record_type, uint8_t lane, uint32_t *out_addr, uint32_t *out_seq)
{
    const fee_block_cfg_t *cfg;
    fee_cache_entry_t *entry;
    fee_flash_caps_t caps;
    fee_record_header_t header;
    fee_commit_tail_t tail;
    uint8_t padded_buf[FEE_CFG_DEFAULT_MAX_LEN + FEE_CFG_ALIGN_UNIT];
    uint32_t addr;
    uint32_t next_addr;
    uint32_t seq;
    uint32_t stored_len;
    fee_ret_t ret;

    cfg = fee_cfg_find_block(block_id);
    if (cfg == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    if ((record_type == FEE_RECORD_DATA) && ((src == RT_NULL) || (len == 0U) || (len > cfg->max_len)))
    {
        return FEE_E_PARAM;
    }

    if (fee_port_get_caps(&caps) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    addr = g_fee_ctx.lane[lane].free_offset;
    entry = fee_cache_lookup(block_id);
    seq = (entry == RT_NULL) ? 1U : (entry->seq + 1U);
    next_addr = addr + fee_core_record_next_addr(cfg, len);
    stored_len = fee_onflash_align_up((uint32_t)len, caps.program_unit);

    if (next_addr > caps.total_size)
    {
        return FEE_E_BUSY;
    }

    ret = fee_onflash_encode_record_header(&header, block_id, record_type, len, seq);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_onflash_encode_commit_tail(&tail, src, len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_write(addr, (const uint8_t *)&header, (uint32_t)sizeof(header));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (len > 0U)
    {
        (void)memset(padded_buf, 0, sizeof(padded_buf));
        (void)memcpy(padded_buf, src, len);
        ret = fee_port_write(addr + (uint32_t)sizeof(header), padded_buf, stored_len);
        if (ret != FEE_E_OK)
        {
            return ret;
        }
    }

    ret = fee_port_write(addr + (uint32_t)sizeof(header) + stored_len,
        (const uint8_t *)&tail, (uint32_t)sizeof(tail));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_ctx.lane[lane].free_offset = next_addr;
    g_fee_ctx.lane[lane].dirty_record_count++;
    g_fee_ctx.lane[lane].dirty_bytes += (next_addr - addr);
    g_fee_ctx.checkpoint_dirty = 1U;

    if (out_addr != RT_NULL)
    {
        *out_addr = addr;
    }

    if (out_seq != RT_NULL)
    {
        *out_seq = seq;
    }

    return FEE_E_OK;
}

static fee_ret_t fee_core_read_payload(uint32_t addr, uint16_t offset, uint8_t *dst, uint16_t len)
{
    fee_record_header_t header;
    fee_commit_tail_t tail;
    fee_ret_t ret;

    ret = fee_core_read_header(addr, &header);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if ((header.magic != FEE_RECORD_MAGIC) || (header.record_type != FEE_RECORD_DATA))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_core_read_tail(addr, header.data_len, &tail);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (!fee_onflash_is_record_committed(&tail))
    {
        return FEE_E_NOT_OK;
    }

    if (((uint32_t)offset + (uint32_t)len) > (uint32_t)header.data_len)
    {
        return FEE_E_PARAM;
    }

    return fee_port_read(addr + (uint32_t)sizeof(header) + (uint32_t)offset, dst, len);
}

void fee_core_reset_context(void)
{
    (void)memset(&g_fee_ctx, 0, sizeof(g_fee_ctx));
    g_fee_ctx.status = FEE_STATUS_UNINIT;
    g_fee_ctx.job_result = FEE_JOB_NONE;
    g_fee_ctx.init_state = FEE_INIT_RESET;
}

fee_ret_t fee_core_init(void)
{
    fee_cache_init();
    fee_ckpt_init();
    fee_lane_fast_init();
    fee_lane_log_init();
    fee_lane_bulk_init();

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    g_fee_ctx.lane[FEE_LANE_FAST].free_offset = FEE_INVALID_ADDR;
    g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = FEE_INVALID_ADDR;
    g_fee_ctx.lane[FEE_LANE_BULK].free_offset = FEE_INVALID_ADDR;

    return fee_recovery_start();
}

fee_ret_t fee_core_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len)
{
    fee_cache_entry_t *entry;
    fee_ret_t ret;

    if (!fee_recovery_can_read_block(block_id))
    {
        return FEE_E_BUSY;
    }

    entry = fee_cache_lookup(block_id);
    if ((entry == RT_NULL) || (entry->cur_valid == 0U))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_core_read_payload(entry->cur_addr, offset, dst, len);
    if ((ret != FEE_E_OK) && (entry->prev_valid != 0U))
    {
        ret = fee_core_read_payload(entry->prev_addr, offset, dst, len);
    }

    return ret;
}

fee_ret_t fee_core_write(uint16_t block_id, const uint8_t *src, uint16_t len)
{
    const fee_block_cfg_t *cfg;
    uint32_t addr;
    uint32_t seq;
    fee_ret_t ret;

    if (g_fee_ctx.init_state != FEE_INIT_FULL_READY)
    {
        return FEE_E_BUSY;
    }

    cfg = fee_cfg_find_block(block_id);
    if ((cfg == RT_NULL) || (len > cfg->max_len))
    {
        return FEE_E_PARAM;
    }

    ret = fee_core_append_record(block_id, src, len, FEE_RECORD_DATA, cfg->lane_type, &addr, &seq);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }

    fee_cache_update_data(block_id, cfg->lane_type, addr, len, seq);
    ret = fee_ckpt_flush();
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }
    g_fee_ctx.status = FEE_STATUS_IDLE;
    g_fee_ctx.job_result = FEE_JOB_OK;

    return FEE_E_OK;
}

fee_ret_t fee_core_invalidate(uint16_t block_id)
{
    const fee_block_cfg_t *cfg;
    uint32_t addr;
    uint32_t seq;
    fee_ret_t ret;

    if (g_fee_ctx.init_state != FEE_INIT_FULL_READY)
    {
        return FEE_E_BUSY;
    }

    cfg = fee_cfg_find_block(block_id);
    if (cfg == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    ret = fee_core_append_record(block_id, (const uint8_t *)"", 0U, FEE_RECORD_TOMBSTONE,
        cfg->lane_type, &addr, &seq);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }

    fee_cache_update_tombstone(block_id, cfg->lane_type, addr, seq);
    ret = fee_ckpt_flush();
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        return ret;
    }
    g_fee_ctx.status = FEE_STATUS_IDLE;
    g_fee_ctx.job_result = FEE_JOB_OK;

    return FEE_E_OK;
}

fee_ret_t fee_core_rollback(uint16_t block_id)
{
    fee_cache_entry_t *entry;
    uint8_t buffer[FEE_CFG_DEFAULT_MAX_LEN];
    fee_record_header_t prev_header;
    fee_ret_t ret;

    if (g_fee_ctx.init_state != FEE_INIT_FULL_READY)
    {
        return FEE_E_BUSY;
    }

    entry = fee_cache_lookup(block_id);
    if ((entry == RT_NULL) || (entry->prev_valid == 0U))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_core_read_header(entry->prev_addr, &prev_header);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (prev_header.data_len > (uint16_t)sizeof(buffer))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_core_read_payload(entry->prev_addr, 0U, buffer, prev_header.data_len);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    return fee_core_write(block_id, buffer, prev_header.data_len);
}

void fee_core_mainfunction(void)
{
    if (g_fee_ctx.init_state == FEE_INIT_FULL_READY)
    {
        g_fee_ctx.status = FEE_STATUS_IDLE;
        if (g_fee_ctx.job_result == FEE_JOB_PENDING)
        {
            g_fee_ctx.job_result = FEE_JOB_OK;
        }
    }
}
