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

static uint32_t fee_recovery_sector_data_start(uint32_t sector_base)
{
    return sector_base + fee_onflash_align_up((uint32_t)sizeof(fee_sector_header_t), g_fee_caps.program_unit);
}

static uint32_t fee_recovery_lane_sector_base(uint8_t lane, uint8_t sector_idx)
{
    return g_fee_ctx.lane[lane].range_base + ((uint32_t)sector_idx * g_fee_caps.erase_unit);
}

static rt_bool_t fee_recovery_addr_in_sector(uint32_t sector_base, uint32_t addr)
{
    if ((addr >= sector_base) && (addr <= (sector_base + g_fee_caps.erase_unit)))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static void fee_recovery_set_lane_range(uint8_t lane, uint32_t range_base, uint8_t sector_count)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    uint32_t max_span;

    lane_ctx->range_base = range_base;
    lane_ctx->range_limit = range_base + ((uint32_t)sector_count * g_fee_caps.erase_unit);
    lane_ctx->sector_count = sector_count;
    lane_ctx->active_sector = 0U;
    lane_ctx->dst_sector = 0U;
    lane_ctx->spare_sector = (sector_count > 1U) ? 1U : 0U;
    lane_ctx->base_addr = range_base;
    lane_ctx->data_start = fee_recovery_sector_data_start(range_base);
    lane_ctx->limit_addr = range_base + g_fee_caps.erase_unit;
    lane_ctx->scan_start = FEE_INVALID_ADDR;
    lane_ctx->active_generation = 0U;

    max_span = fee_cfg_get_lane_max_span(lane);
    if (max_span == 0U)
    {
        max_span = FEE_CFG_ALIGN_UNIT;
    }

    if ((lane == (uint8_t)FEE_LANE_NORMAL) && (sector_count > 1U))
    {
        lane_ctx->gc_start_threshold = max_span * 2U;
        lane_ctx->gc_force_threshold = max_span;
    }
    else
    {
        lane_ctx->gc_start_threshold = 0U;
        lane_ctx->gc_force_threshold = 0U;
    }
}

static fee_ret_t fee_recovery_assign_layout(void)
{
    if (g_fee_caps.total_size < (g_fee_caps.erase_unit * 6U))
    {
        return FEE_E_NOT_OK;
    }

    fee_recovery_set_lane_range((uint8_t)FEE_LANE_META, 0U, 2U);
    fee_recovery_set_lane_range((uint8_t)FEE_LANE_FAST, g_fee_caps.erase_unit * 2U, 1U);
    fee_recovery_set_lane_range((uint8_t)FEE_LANE_NORMAL, g_fee_caps.erase_unit * 3U, 2U);
    fee_recovery_set_lane_range((uint8_t)FEE_LANE_BULK, g_fee_caps.erase_unit * 5U, 1U);

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_format_lane_sector(uint8_t lane, uint8_t sector_idx,
    uint8_t state, uint32_t generation, rt_bool_t erase_first)
{
    fee_sector_header_t header;
    uint32_t sector_base = fee_recovery_lane_sector_base(lane, sector_idx);
    uint32_t data_start = fee_recovery_sector_data_start(sector_base);
    uint32_t data_end = sector_base + g_fee_caps.erase_unit;

    (void)memset(&header, 0, sizeof(header));
    header.magic = FEE_SECTOR_MAGIC;
    header.format_version = FEE_CFG_FORMAT_VERSION;
    header.lane_id = lane;
    header.state = state;
    header.generation = generation;
    header.data_start = data_start;
    header.data_end = data_end;
    header.commit_marker = FEE_COMMIT_MARKER;

    if ((erase_first != RT_FALSE) && (fee_port_erase(sector_base, g_fee_caps.erase_unit) != FEE_E_OK))
    {
        return FEE_E_NOT_OK;
    }

    if (fee_port_write(sector_base, (const uint8_t *)&header, (uint32_t)sizeof(header)) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    return FEE_E_OK;
}

static rt_bool_t fee_recovery_is_valid_lane_header(uint8_t lane, const fee_sector_header_t *header,
    uint32_t sector_base)
{
    if (!fee_onflash_validate_sector_header(header))
    {
        return RT_FALSE;
    }

    if ((header->lane_id != lane) ||
        (header->data_start != fee_recovery_sector_data_start(sector_base)) ||
        (header->data_end != (sector_base + g_fee_caps.erase_unit)))
    {
        return RT_FALSE;
    }

    if ((header->state != (uint8_t)FEE_SECTOR_ACTIVE) &&
        (header->state != (uint8_t)FEE_SECTOR_GC_DST))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void fee_recovery_select_active_sector(uint8_t lane, uint8_t sector_idx, uint32_t generation)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    uint32_t sector_base = fee_recovery_lane_sector_base(lane, sector_idx);
    uint32_t data_start = fee_recovery_sector_data_start(sector_base);
    uint32_t data_end = sector_base + g_fee_caps.erase_unit;

    lane_ctx->active_sector = sector_idx;
    lane_ctx->dst_sector = sector_idx;
    lane_ctx->spare_sector = (lane_ctx->sector_count > 1U) ?
        (uint8_t)((sector_idx + 1U) % lane_ctx->sector_count) : sector_idx;
    lane_ctx->base_addr = sector_base;
    lane_ctx->data_start = data_start;
    lane_ctx->limit_addr = data_end;
    lane_ctx->active_generation = generation;

    if ((lane_ctx->free_offset < data_start) || (lane_ctx->free_offset > data_end))
    {
        lane_ctx->free_offset = data_start;
    }

    if ((lane_ctx->scan_start < data_start) || (lane_ctx->scan_start > data_end))
    {
        lane_ctx->scan_start = lane_ctx->free_offset;
    }
}

static fee_ret_t fee_recovery_open_single_sector_lane(uint8_t lane)
{
    fee_sector_header_t header;
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    uint32_t sector_base = fee_recovery_lane_sector_base(lane, 0U);
    fee_ret_t ret;

    ret = fee_port_read(sector_base, (uint8_t *)&header, (uint32_t)sizeof(header));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (fee_recovery_is_valid_lane_header(lane, &header, sector_base) == RT_FALSE)
    {
        ret = fee_recovery_format_lane_sector(lane, 0U, (uint8_t)FEE_SECTOR_ACTIVE, 1U, RT_TRUE);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        lane_ctx->free_offset = fee_recovery_sector_data_start(sector_base);
        lane_ctx->scan_start = lane_ctx->free_offset;
        fee_recovery_select_active_sector(lane, 0U, 1U);
        g_fee_ctx.checkpoint_dirty = 1U;
        return FEE_E_OK;
    }

    fee_recovery_select_active_sector(lane, 0U, header.generation);
    return FEE_E_OK;
}

static fee_ret_t fee_recovery_open_normal_lane(void)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[FEE_LANE_NORMAL];
    fee_sector_header_t headers[2];
    rt_bool_t valid[2];
    uint8_t idx;
    uint8_t selected_idx = 0xFFU;
    uint8_t selected_active = 0xFFU;
    uint8_t selected_gc_dst = 0xFFU;
    fee_ret_t ret;

    for (idx = 0U; idx < 2U; ++idx)
    {
        uint32_t sector_base = fee_recovery_lane_sector_base((uint8_t)FEE_LANE_NORMAL, idx);

        ret = fee_port_read(sector_base, (uint8_t *)&headers[idx], (uint32_t)sizeof(headers[idx]));
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        valid[idx] = fee_recovery_is_valid_lane_header((uint8_t)FEE_LANE_NORMAL, &headers[idx], sector_base);
        if (valid[idx] == RT_FALSE)
        {
            continue;
        }

        if (fee_recovery_addr_in_sector(sector_base, lane_ctx->free_offset) != RT_FALSE)
        {
            selected_idx = idx;
        }

        if (headers[idx].state == (uint8_t)FEE_SECTOR_ACTIVE)
        {
            if ((selected_active == 0xFFU) || (headers[idx].generation > headers[selected_active].generation))
            {
                selected_active = idx;
            }
        }
        else if ((selected_gc_dst == 0xFFU) || (headers[idx].generation > headers[selected_gc_dst].generation))
        {
            selected_gc_dst = idx;
        }
    }

    if ((valid[0] == RT_FALSE) && (valid[1] == RT_FALSE))
    {
        ret = fee_recovery_format_lane_sector((uint8_t)FEE_LANE_NORMAL, 0U,
            (uint8_t)FEE_SECTOR_ACTIVE, 1U, RT_TRUE);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        ret = fee_port_erase(fee_recovery_lane_sector_base((uint8_t)FEE_LANE_NORMAL, 1U), g_fee_caps.erase_unit);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        lane_ctx->free_offset = fee_recovery_sector_data_start(fee_recovery_lane_sector_base((uint8_t)FEE_LANE_NORMAL, 0U));
        lane_ctx->scan_start = lane_ctx->free_offset;
        fee_recovery_select_active_sector((uint8_t)FEE_LANE_NORMAL, 0U, 1U);
        lane_ctx->spare_sector = 1U;
        g_fee_ctx.checkpoint_dirty = 1U;
        return FEE_E_OK;
    }

    if ((selected_idx == 0xFFU) && (selected_active != 0xFFU))
    {
        selected_idx = selected_active;
    }

    if ((selected_idx == 0xFFU) && (selected_gc_dst != 0xFFU))
    {
        selected_idx = selected_gc_dst;
    }

    if (selected_idx == 0xFFU)
    {
        selected_idx = (valid[0] != RT_FALSE) ? 0U : 1U;
    }

    fee_recovery_select_active_sector((uint8_t)FEE_LANE_NORMAL, selected_idx, headers[selected_idx].generation);
    return FEE_E_OK;
}

static fee_ret_t fee_recovery_open_lane(uint8_t lane)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];

    if (lane_ctx->sector_count > 1U)
    {
        return fee_recovery_open_normal_lane();
    }

    return fee_recovery_open_single_sector_lane(lane);
}

static fee_ret_t fee_recovery_open_all_lanes(void)
{
    uint8_t lane;

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        fee_ret_t ret = fee_recovery_open_lane(lane);

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
