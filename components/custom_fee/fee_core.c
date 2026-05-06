#include "fee_internal.h"

static fee_ret_t fee_core_read_header(uint32_t addr, fee_record_header_t *header)
{
    return fee_port_read(addr, (uint8_t *)header, (uint32_t)sizeof(*header));
}

static fee_ret_t fee_core_read_tail(uint32_t addr, uint16_t data_len, fee_commit_tail_t *tail)
{
    fee_flash_caps_t caps;
    uint32_t stored_len;
    uint32_t tail_addr;

    if (fee_port_get_caps(&caps) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    stored_len = fee_onflash_align_up((uint32_t)data_len, caps.program_unit);
    tail_addr = addr + (uint32_t)sizeof(fee_record_header_t) + stored_len;

    return fee_port_read(tail_addr, (uint8_t *)tail, (uint32_t)sizeof(*tail));
}

static uint32_t fee_core_record_next_addr(const fee_block_cfg_t *cfg, uint16_t data_len)
{
    return fee_onflash_calc_record_span(cfg, data_len);
}

static void fee_core_update_gc_request(uint8_t lane)
{
    fee_lane_ctx_t *lane_ctx;
    uint32_t remaining_bytes;

    if ((lane <= (uint8_t)FEE_LANE_META) || (lane >= (uint8_t)FEE_LANE_COUNT))
    {
        return;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    if ((lane_ctx->sector_count < 2U) || (lane_ctx->limit_addr <= lane_ctx->free_offset))
    {
        return;
    }

    remaining_bytes = lane_ctx->limit_addr - lane_ctx->free_offset;

    if ((lane_ctx->gc_start_threshold != 0U) && (remaining_bytes <= lane_ctx->gc_start_threshold))
    {
        lane_ctx->gc_requested = 1U;
    }

    if ((lane_ctx->gc_force_threshold != 0U) && (remaining_bytes <= lane_ctx->gc_force_threshold))
    {
        lane_ctx->gc_force = 1U;
    }
}

static uint32_t fee_core_ckpt_record_threshold(uint8_t lane, rt_bool_t force_flush)
{
    if (lane == (uint8_t)FEE_LANE_FAST)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_RECORDS_FAST : FEE_CFG_CKPT_BG_RECORDS_FAST;
    }

    if (lane == (uint8_t)FEE_LANE_NORMAL)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_RECORDS_NORMAL : FEE_CFG_CKPT_BG_RECORDS_NORMAL;
    }

    if (lane == (uint8_t)FEE_LANE_BULK)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_RECORDS_BULK : FEE_CFG_CKPT_BG_RECORDS_BULK;
    }

    return 0U;
}

static uint32_t fee_core_ckpt_byte_threshold(uint8_t lane, rt_bool_t force_flush)
{
    if (lane == (uint8_t)FEE_LANE_FAST)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_BYTES_FAST : FEE_CFG_CKPT_BG_BYTES_FAST;
    }

    if (lane == (uint8_t)FEE_LANE_NORMAL)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_BYTES_NORMAL : FEE_CFG_CKPT_BG_BYTES_NORMAL;
    }

    if (lane == (uint8_t)FEE_LANE_BULK)
    {
        return force_flush ? FEE_CFG_CKPT_FORCE_BYTES_BULK : FEE_CFG_CKPT_BG_BYTES_BULK;
    }

    return 0U;
}

static rt_bool_t fee_core_lane_hits_ckpt_threshold(uint8_t lane, rt_bool_t force_flush)
{
    fee_lane_ctx_t *lane_ctx;
    uint32_t record_threshold;
    uint32_t byte_threshold;

    if ((lane >= FEE_LANE_COUNT) || (lane == (uint8_t)FEE_LANE_META))
    {
        return RT_FALSE;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    record_threshold = fee_core_ckpt_record_threshold(lane, force_flush);
    byte_threshold = fee_core_ckpt_byte_threshold(lane, force_flush);

    if ((record_threshold != 0U) && (lane_ctx->dirty_record_count >= record_threshold))
    {
        return RT_TRUE;
    }

    if ((byte_threshold != 0U) && (lane_ctx->dirty_bytes >= byte_threshold))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_bool_t fee_core_should_force_ckpt(const fee_block_cfg_t *cfg)
{
    if (cfg == RT_NULL)
    {
        return RT_FALSE;
    }

    if ((cfg->boot_critical != 0U) || (cfg->lane_type == (uint8_t)FEE_LANE_FAST))
    {
        return RT_TRUE;
    }

    return fee_core_lane_hits_ckpt_threshold(cfg->lane_type, RT_TRUE);
}

static rt_bool_t fee_core_should_flush_ckpt_background(void)
{
    uint8_t lane;

    if (g_fee_ctx.checkpoint_dirty == 0U)
    {
        return RT_FALSE;
    }

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        if (fee_core_lane_hits_ckpt_threshold(lane, RT_FALSE) == RT_TRUE)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static fee_ret_t fee_core_checkpoint_after_update(const fee_block_cfg_t *cfg)
{
    if (fee_core_should_force_ckpt(cfg) == RT_FALSE)
    {
        return FEE_E_OK;
    }

    return fee_ckpt_flush();
}

static fee_ret_t fee_core_append_record(uint16_t block_id, const uint8_t *src, uint16_t len,
    uint8_t record_type, uint8_t lane, uint32_t *out_addr, uint32_t *out_seq)
{
    const fee_block_cfg_t *cfg;
    fee_cache_entry_t *entry;
    fee_flash_caps_t caps;
    fee_record_header_t header;
    fee_commit_tail_t tail;
    uint8_t padded_buf[FEE_CFG_MAX_BLOCK_LEN + FEE_CFG_ALIGN_UNIT];
    fee_lane_ctx_t *lane_ctx;
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

    if (lane >= FEE_LANE_COUNT)
    {
        return FEE_E_PARAM;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    if ((lane_ctx->free_offset == FEE_INVALID_ADDR) ||
        (lane_ctx->data_start == 0U) || (lane_ctx->limit_addr <= lane_ctx->data_start))
    {
        return FEE_E_NOT_OK;
    }

    addr = lane_ctx->free_offset;
    stored_len = fee_onflash_align_up((uint32_t)len, caps.program_unit);

    if (stored_len > sizeof(padded_buf))
    {
        return FEE_E_PARAM;
    }

    next_addr = addr + fee_core_record_next_addr(cfg, len);
    if (next_addr > lane_ctx->limit_addr)
    {
        if (lane_ctx->sector_count > 1U)
        {
            lane_ctx->gc_requested = 1U;
            lane_ctx->gc_force = 1U;
            if (fee_gc_reclaim_sync(lane) == FEE_E_OK)
            {
                addr = lane_ctx->free_offset;
                next_addr = addr + fee_core_record_next_addr(cfg, len);
            }
        }

        if (next_addr > lane_ctx->limit_addr)
        {
            return FEE_E_BUSY;
        }
    }

    entry = fee_cache_lookup(block_id);
    seq = (entry == RT_NULL) ? 1U : (entry->seq + 1U);

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

    lane_ctx->free_offset = next_addr;
    lane_ctx->dirty_record_count++;
    lane_ctx->dirty_bytes += (next_addr - addr);
    g_fee_ctx.checkpoint_dirty = 1U;
    fee_core_update_gc_request(lane);

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
    fee_ret_t ret;

    ret = fee_cfg_validate_table();
    if (ret != FEE_E_OK)
    {
        return ret;
    }

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
    g_fee_ctx.lane[FEE_LANE_FAST].scan_start = FEE_INVALID_ADDR;
    g_fee_ctx.lane[FEE_LANE_NORMAL].scan_start = FEE_INVALID_ADDR;
    g_fee_ctx.lane[FEE_LANE_BULK].scan_start = FEE_INVALID_ADDR;

    return fee_recovery_start();
}

fee_ret_t fee_core_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len)
{
    fee_cache_entry_t *entry;
    const fee_block_cfg_t *cfg;
    fee_ret_t ret;

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
    ret = fee_core_checkpoint_after_update(cfg);
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
    ret = fee_core_checkpoint_after_update(cfg);
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
    uint8_t buffer[FEE_CFG_MAX_BLOCK_LEN];
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
        if (fee_core_should_flush_ckpt_background() == RT_TRUE)
        {
            if (fee_ckpt_flush() != FEE_E_OK)
            {
                g_fee_ctx.job_result = FEE_JOB_FAILED;
            }
        }

        g_fee_ctx.status = FEE_STATUS_IDLE;
        if (g_fee_ctx.job_result == FEE_JOB_PENDING)
        {
            g_fee_ctx.job_result = FEE_JOB_OK;
        }
    }
}
