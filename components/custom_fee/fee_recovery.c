#include "fee_internal.h"

static fee_flash_caps_t g_fee_caps;
static uint8_t g_fee_tail_scan_lane = (uint8_t)FEE_LANE_FAST;

static rt_bool_t fee_recovery_is_business_lane(uint8_t lane)
{
    if ((lane == (uint8_t)FEE_LANE_FAST) ||
        (lane == (uint8_t)FEE_LANE_NORMAL) ||
        (lane == (uint8_t)FEE_LANE_BULK))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static void fee_recovery_set_lane_layout(uint8_t lane, uint32_t base_addr)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];

    lane_ctx->base_addr = base_addr;
    lane_ctx->data_start = base_addr +
        fee_onflash_align_up((uint32_t)sizeof(fee_sector_header_t), g_fee_caps.program_unit);
    lane_ctx->limit_addr = base_addr + g_fee_caps.erase_unit;
    lane_ctx->scan_start = FEE_INVALID_ADDR;
}

static fee_ret_t fee_recovery_assign_layout(void)
{
    if (g_fee_caps.total_size < (g_fee_caps.erase_unit * 5U))
    {
        return FEE_E_NOT_OK;
    }

    g_fee_ctx.lane[FEE_LANE_META].base_addr = 0U;
    g_fee_ctx.lane[FEE_LANE_META].limit_addr = g_fee_caps.erase_unit * 2U;
    fee_recovery_set_lane_layout((uint8_t)FEE_LANE_FAST, g_fee_caps.erase_unit * 2U);
    fee_recovery_set_lane_layout((uint8_t)FEE_LANE_NORMAL, g_fee_caps.erase_unit * 3U);
    fee_recovery_set_lane_layout((uint8_t)FEE_LANE_BULK, g_fee_caps.erase_unit * 4U);

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_format_lane_sector(uint8_t lane)
{
    fee_sector_header_t header;
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];

    (void)memset(&header, 0, sizeof(header));
    header.magic = FEE_SECTOR_MAGIC;
    header.format_version = FEE_CFG_FORMAT_VERSION;
    header.lane_id = lane;
    header.state = (uint8_t)FEE_SECTOR_ACTIVE;
    header.generation = 1U;
    header.data_start = lane_ctx->data_start;
    header.data_end = lane_ctx->limit_addr;
    header.commit_marker = FEE_COMMIT_MARKER;

    if (fee_port_erase(lane_ctx->base_addr, g_fee_caps.erase_unit) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    if (fee_port_write(lane_ctx->base_addr, (const uint8_t *)&header, (uint32_t)sizeof(header)) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    lane_ctx->free_offset = lane_ctx->data_start;
    lane_ctx->scan_start = lane_ctx->data_start;
    lane_ctx->active_sector = 0U;
    g_fee_ctx.checkpoint_dirty = 1U;

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_open_lane_sector(uint8_t lane)
{
    fee_sector_header_t header;
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    fee_ret_t ret;

    ret = fee_port_read(lane_ctx->base_addr, (uint8_t *)&header, (uint32_t)sizeof(header));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if ((!fee_onflash_validate_sector_header(&header)) ||
        (header.lane_id != lane) ||
        (header.data_start != lane_ctx->data_start) ||
        (header.data_end != lane_ctx->limit_addr))
    {
        return fee_recovery_format_lane_sector(lane);
    }

    if ((lane_ctx->free_offset < header.data_start) || (lane_ctx->free_offset > header.data_end))
    {
        lane_ctx->free_offset = header.data_start;
    }

    if ((lane_ctx->scan_start < header.data_start) || (lane_ctx->scan_start > header.data_end))
    {
        lane_ctx->scan_start = lane_ctx->free_offset;
    }

    lane_ctx->active_sector = 0U;
    return FEE_E_OK;
}

static fee_ret_t fee_recovery_open_all_lanes(void)
{
    uint8_t lane;

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        fee_ret_t ret = fee_recovery_open_lane_sector(lane);

        if (ret != FEE_E_OK)
        {
            return ret;
        }
    }

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_scan_lane_records(uint8_t lane)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    fee_record_header_t header;
    fee_commit_tail_t tail;
    const fee_block_cfg_t *cfg;
    uint32_t addr;
    uint32_t next_addr;
    uint32_t tail_addr;
    fee_ret_t ret;

    addr = lane_ctx->scan_start;

    while ((addr + (uint32_t)sizeof(header) + (uint32_t)sizeof(tail)) <= lane_ctx->limit_addr)
    {
        ret = fee_port_read(addr, (uint8_t *)&header, (uint32_t)sizeof(header));
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        if (header.magic != FEE_RECORD_MAGIC)
        {
            break;
        }

        cfg = fee_cfg_find_block(header.block_id);
        if ((cfg == RT_NULL) || (cfg->lane_type != lane))
        {
            return FEE_E_NOT_OK;
        }

        tail_addr = addr + (uint32_t)sizeof(header) +
            fee_onflash_align_up((uint32_t)header.data_len, g_fee_caps.program_unit);
        ret = fee_port_read(tail_addr, (uint8_t *)&tail, (uint32_t)sizeof(tail));
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        if (!fee_onflash_is_record_committed(&tail))
        {
            break;
        }

        if (header.record_type == FEE_RECORD_DATA)
        {
            fee_cache_update_data(header.block_id, cfg->lane_type, addr, header.data_len, header.seq);
        }
        else if (header.record_type == FEE_RECORD_TOMBSTONE)
        {
            fee_cache_update_tombstone(header.block_id, cfg->lane_type, addr, header.seq);
        }

        next_addr = addr + fee_onflash_calc_record_span(cfg, header.data_len);
        if (next_addr <= addr)
        {
            return FEE_E_NOT_OK;
        }

        addr = next_addr;
    }

    lane_ctx->free_offset = addr;
    lane_ctx->scan_start = addr;
    return FEE_E_OK;
}

fee_ret_t fee_recovery_start(void)
{
    fee_ret_t ret;

    g_fee_ctx.init_state = FEE_INIT_META_SCAN;
    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;

    ret = fee_port_get_caps(&g_fee_caps);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.init_state = FEE_INIT_FAILED;
        return ret;
    }

    ret = fee_recovery_assign_layout();
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.init_state = FEE_INIT_FAILED;
        return ret;
    }

    g_fee_tail_scan_lane = (uint8_t)FEE_LANE_FAST;

    return FEE_E_OK;
}

fee_ret_t fee_recovery_step(void)
{
    fee_ret_t ret;

    if (g_fee_ctx.init_state == FEE_INIT_META_SCAN)
    {
        ret = fee_ckpt_restore();
        (void)ret;

        ret = fee_recovery_open_all_lanes();
        if (ret != FEE_E_OK)
        {
            g_fee_ctx.init_state = FEE_INIT_FAILED;
            return ret;
        }

        g_fee_ctx.init_state = FEE_INIT_CKPT_READY;
        return FEE_E_OK;
    }

    if (g_fee_ctx.init_state == FEE_INIT_CKPT_READY)
    {
        g_fee_ctx.init_state = FEE_INIT_TAIL_SCAN;
        return FEE_E_OK;
    }

    if (g_fee_ctx.init_state == FEE_INIT_TAIL_SCAN)
    {
        while ((g_fee_tail_scan_lane < (uint8_t)FEE_LANE_COUNT) &&
               (fee_recovery_is_business_lane(g_fee_tail_scan_lane) == RT_FALSE))
        {
            ++g_fee_tail_scan_lane;
        }

        if (g_fee_tail_scan_lane >= (uint8_t)FEE_LANE_COUNT)
        {
            g_fee_ctx.init_state = FEE_INIT_FULL_READY;
            g_fee_ctx.status = FEE_STATUS_IDLE;
            g_fee_ctx.job_result = FEE_JOB_OK;
            return FEE_E_OK;
        }

        ret = fee_recovery_scan_lane_records(g_fee_tail_scan_lane);
        if (ret != FEE_E_OK)
        {
            g_fee_ctx.init_state = FEE_INIT_FAILED;
            return ret;
        }

        ++g_fee_tail_scan_lane;

        if (g_fee_tail_scan_lane >= (uint8_t)FEE_LANE_COUNT)
        {
            g_fee_ctx.init_state = FEE_INIT_FULL_READY;
            g_fee_ctx.status = FEE_STATUS_IDLE;
            g_fee_ctx.job_result = FEE_JOB_OK;
        }

        return FEE_E_OK;
    }

    return FEE_E_OK;
}

rt_bool_t fee_recovery_can_read_block(uint16_t block_id)
{
    if (fee_cfg_find_block(block_id) == RT_NULL)
    {
        return RT_FALSE;
    }

    if (g_fee_ctx.init_state == FEE_INIT_FULL_READY)
    {
        return RT_TRUE;
    }

    if ((g_fee_ctx.init_state == FEE_INIT_CKPT_READY) || (g_fee_ctx.init_state == FEE_INIT_TAIL_SCAN))
    {
        return fee_cfg_is_boot_critical(block_id);
    }

    return RT_FALSE;
}

rt_bool_t fee_recovery_is_full_ready(void)
{
    return (g_fee_ctx.init_state == FEE_INIT_FULL_READY) ? RT_TRUE : RT_FALSE;
}
