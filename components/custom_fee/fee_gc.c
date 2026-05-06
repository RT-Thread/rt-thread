#include "fee_internal.h"

#define FEE_GC_PREV_VALID_FLAG      (0x02UL)
#define FEE_GC_COPY_BUFFER_SIZE     (2048U)

static rt_bool_t fee_gc_lane_supports_reclaim(uint8_t lane)
{
    if ((lane > (uint8_t)FEE_LANE_META) &&
        (lane < (uint8_t)FEE_LANE_COUNT) &&
        (g_fee_ctx.lane[lane].sector_count > 1U))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_bool_t fee_gc_addr_in_sector(uint32_t sector_base, uint32_t sector_limit, uint32_t addr)
{
    if ((addr >= sector_base) && (addr < sector_limit))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static uint32_t fee_gc_sector_base(const fee_lane_ctx_t *lane_ctx, const fee_flash_caps_t *caps, uint8_t sector_idx)
{
    return lane_ctx->range_base + ((uint32_t)sector_idx * caps->erase_unit);
}

static uint32_t fee_gc_sector_data_start(uint32_t sector_base, const fee_flash_caps_t *caps)
{
    return sector_base + fee_onflash_align_up((uint32_t)sizeof(fee_sector_header_t), caps->program_unit);
}

static fee_ret_t fee_gc_write_sector_header(uint8_t lane, uint8_t sector_idx, uint8_t state,
    uint32_t generation, const fee_flash_caps_t *caps, rt_bool_t erase_first)
{
    fee_sector_header_t header;
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    uint32_t sector_base = fee_gc_sector_base(lane_ctx, caps, sector_idx);

    (void)memset(&header, 0, sizeof(header));
    header.magic = FEE_SECTOR_MAGIC;
    header.format_version = FEE_CFG_FORMAT_VERSION;
    header.lane_id = lane;
    header.state = state;
    header.generation = generation;
    header.data_start = fee_gc_sector_data_start(sector_base, caps);
    header.data_end = sector_base + caps->erase_unit;
    header.commit_marker = FEE_COMMIT_MARKER;

    if ((erase_first != RT_FALSE) && (fee_port_erase(sector_base, caps->erase_unit) != FEE_E_OK))
    {
        return FEE_E_NOT_OK;
    }

    if (fee_port_write(sector_base, (const uint8_t *)&header, (uint32_t)sizeof(header)) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    return FEE_E_OK;
}

static fee_ret_t fee_gc_copy_record(uint32_t src_addr, uint32_t dst_addr, uint32_t dst_limit,
    const fee_block_cfg_t *cfg, const fee_flash_caps_t *caps, uint32_t *out_span)
{
    fee_record_header_t header;
    fee_commit_tail_t tail;
    uint8_t buffer[FEE_GC_COPY_BUFFER_SIZE];
    uint32_t stored_len;
    uint32_t tail_addr;
    uint32_t span;
    fee_ret_t ret;

    ret = fee_port_read(src_addr, (uint8_t *)&header, (uint32_t)sizeof(header));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if ((header.magic != FEE_RECORD_MAGIC) || (cfg == RT_NULL))
    {
        return FEE_E_NOT_OK;
    }

    span = fee_onflash_calc_record_span(cfg, header.data_len);
    if (span > (uint32_t)sizeof(buffer))
    {
        return FEE_E_NOT_OK;
    }

    if ((dst_addr + span) > dst_limit)
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_port_read(src_addr, &buffer[0], span);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    stored_len = fee_onflash_align_up((uint32_t)header.data_len, caps->program_unit);
    tail_addr = (uint32_t)sizeof(header) + stored_len;
    if ((tail_addr + (uint32_t)sizeof(tail)) > span)
    {
        return FEE_E_NOT_OK;
    }

    (void)memcpy(&tail, &buffer[tail_addr], sizeof(tail));
    if (!fee_onflash_is_record_committed(&tail))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_port_write(dst_addr, &buffer[0], span);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (out_span != RT_NULL)
    {
        *out_span = span;
    }

    return FEE_E_OK;
}

static fee_ret_t fee_gc_copy_one_cache_record(uint16_t block_id, uint32_t src_addr, uint32_t dst_limit,
    uint32_t *dst_cursor, const fee_flash_caps_t *caps)
{
    const fee_block_cfg_t *cfg = fee_cfg_find_block(block_id);
    uint32_t span;
    fee_ret_t ret;

    if ((cfg == RT_NULL) || (dst_cursor == RT_NULL))
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_gc_copy_record(src_addr, *dst_cursor, dst_limit, cfg, caps, &span);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    fee_cache_relocate_address(block_id, src_addr, *dst_cursor);
    *dst_cursor += span;
    return FEE_E_OK;
}

static fee_ret_t fee_gc_copy_one_live_record(uint8_t lane, const fee_flash_caps_t *caps, rt_bool_t *copied)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    fee_ckpt_cache_entry_t entries[FEE_CACHE_MAX_ENTRIES];
    uint16_t entry_count;
    uint32_t cursor;
    uint32_t total_cursor;
    uint32_t src_base;
    uint32_t src_limit;
    uint32_t dst_limit;

    if (copied == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    src_base = fee_gc_sector_base(lane_ctx, caps, lane_ctx->gc_old_sector);
    src_limit = src_base + caps->erase_unit;
    dst_limit = fee_gc_sector_base(lane_ctx, caps, lane_ctx->dst_sector) + caps->erase_unit;
    entry_count = fee_cache_export_ckpt(&entries[0], FEE_CACHE_MAX_ENTRIES);
    total_cursor = (uint32_t)entry_count * 2U;

    for (cursor = (uint32_t)lane_ctx->gc_cursor; cursor < total_cursor; ++cursor)
    {
        uint16_t entry_idx = (uint16_t)(cursor / 2U);
        rt_bool_t use_prev = ((cursor & 1UL) == 0UL) ? RT_TRUE : RT_FALSE;
        uint32_t src_addr = FEE_INVALID_ADDR;

        if (entries[entry_idx].lane != lane)
        {
            continue;
        }

        if (use_prev != RT_FALSE)
        {
            if (((entries[entry_idx].flags & FEE_GC_PREV_VALID_FLAG) != 0UL) &&
                fee_gc_addr_in_sector(src_base, src_limit, entries[entry_idx].prev_addr))
            {
                src_addr = entries[entry_idx].prev_addr;
            }
        }
        else if ((entries[entry_idx].cur_addr != FEE_INVALID_ADDR) &&
                 (entries[entry_idx].cur_addr != entries[entry_idx].prev_addr) &&
                 fee_gc_addr_in_sector(src_base, src_limit, entries[entry_idx].cur_addr))
        {
            src_addr = entries[entry_idx].cur_addr;
        }

        if (src_addr == FEE_INVALID_ADDR)
        {
            continue;
        }

        if (fee_gc_copy_one_cache_record((uint16_t)entries[entry_idx].block_id, src_addr, dst_limit,
            &lane_ctx->gc_write_offset, caps) != FEE_E_OK)
        {
            return FEE_E_NOT_OK;
        }

        lane_ctx->gc_cursor = (uint16_t)(cursor + 1U);
        *copied = RT_TRUE;
        return FEE_E_OK;
    }

    lane_ctx->gc_cursor = (uint16_t)total_cursor;
    *copied = RT_FALSE;
    return FEE_E_OK;
}

static uint8_t fee_gc_choose_dst_sector(const fee_lane_ctx_t *lane_ctx)
{
    uint8_t idx;

    if ((lane_ctx->spare_sector < lane_ctx->sector_count) &&
        (lane_ctx->spare_sector != lane_ctx->active_sector))
    {
        return lane_ctx->spare_sector;
    }

    for (idx = 0U; idx < lane_ctx->sector_count; ++idx)
    {
        if (idx != lane_ctx->active_sector)
        {
            return idx;
        }
    }

    return lane_ctx->active_sector;
}

static fee_ret_t fee_gc_step_lane(uint8_t lane)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    fee_flash_caps_t caps;
    fee_ret_t ret;

    if (fee_gc_lane_supports_reclaim(lane) == RT_FALSE)
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_port_get_caps(&caps);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (lane_ctx->gc_state == (uint8_t)FEE_GC_IDLE)
    {
        if ((lane_ctx->gc_requested == 0U) && (lane_ctx->gc_force == 0U))
        {
            return FEE_E_OK;
        }

        lane_ctx->gc_old_sector = lane_ctx->active_sector;
        lane_ctx->dst_sector = fee_gc_choose_dst_sector(lane_ctx);
        if (lane_ctx->dst_sector == lane_ctx->active_sector)
        {
            return FEE_E_NOT_OK;
        }

        lane_ctx->gc_state = (uint8_t)FEE_GC_PREPARE_DST;
        lane_ctx->gc_cursor = 0U;
        lane_ctx->gc_write_offset = FEE_INVALID_ADDR;
        return FEE_E_OK;
    }

    if (lane_ctx->gc_state == (uint8_t)FEE_GC_PREPARE_DST)
    {
        uint32_t dst_base = fee_gc_sector_base(lane_ctx, &caps, lane_ctx->dst_sector);

        ret = fee_gc_write_sector_header(lane, lane_ctx->dst_sector, (uint8_t)FEE_SECTOR_GC_DST,
            lane_ctx->active_generation + 1U, &caps, RT_TRUE);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        lane_ctx->gc_write_offset = fee_gc_sector_data_start(dst_base, &caps);
        lane_ctx->gc_state = (uint8_t)FEE_GC_COPY_ONE;
        return FEE_E_OK;
    }

    if (lane_ctx->gc_state == (uint8_t)FEE_GC_COPY_ONE)
    {
        rt_bool_t copied = RT_FALSE;

        ret = fee_gc_copy_one_live_record(lane, &caps, &copied);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        if (copied == RT_FALSE)
        {
            lane_ctx->gc_state = (uint8_t)FEE_GC_SWITCH_ACTIVE;
        }

        return FEE_E_OK;
    }

    if (lane_ctx->gc_state == (uint8_t)FEE_GC_SWITCH_ACTIVE)
    {
        uint32_t dst_base = fee_gc_sector_base(lane_ctx, &caps, lane_ctx->dst_sector);

        ret = fee_gc_write_sector_header(lane, lane_ctx->dst_sector, (uint8_t)FEE_SECTOR_ACTIVE,
            lane_ctx->active_generation + 1U, &caps, RT_FALSE);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        lane_ctx->active_sector = lane_ctx->dst_sector;
        lane_ctx->base_addr = dst_base;
        lane_ctx->data_start = fee_gc_sector_data_start(dst_base, &caps);
        lane_ctx->limit_addr = dst_base + caps.erase_unit;
        lane_ctx->free_offset = lane_ctx->gc_write_offset;
        lane_ctx->scan_start = lane_ctx->free_offset;
        lane_ctx->active_generation += 1U;
        lane_ctx->spare_sector = lane_ctx->gc_old_sector;
        g_fee_ctx.checkpoint_dirty = 1U;
        g_fee_ctx.checkpoint_requested = 1U;
        lane_ctx->gc_state = (uint8_t)FEE_GC_ERASE_OLD;
        return FEE_E_OK;
    }

    if (lane_ctx->gc_state == (uint8_t)FEE_GC_ERASE_OLD)
    {
        ret = fee_port_erase(fee_gc_sector_base(lane_ctx, &caps, lane_ctx->gc_old_sector), caps.erase_unit);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        lane_ctx->dst_sector = lane_ctx->spare_sector;
        lane_ctx->gc_state = (uint8_t)FEE_GC_IDLE;
        lane_ctx->gc_cursor = 0U;
        lane_ctx->gc_requested = 0U;
        lane_ctx->gc_force = 0U;
        lane_ctx->gc_write_offset = FEE_INVALID_ADDR;
        return FEE_E_OK;
    }

    return FEE_E_NOT_OK;
}

fee_ret_t fee_gc_reclaim_sync(uint8_t lane)
{
    uint16_t step_budget = (uint16_t)(FEE_CACHE_MAX_ENTRIES * 2U + 8U);
    fee_ret_t ret = FEE_E_OK;

    if (fee_gc_lane_supports_reclaim(lane) == RT_FALSE)
    {
        return FEE_E_NOT_OK;
    }

    g_fee_ctx.lane[lane].gc_requested = 1U;
    g_fee_ctx.lane[lane].gc_force = 1U;

    while (step_budget > 0U)
    {
        ret = fee_gc_step_lane(lane);
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        if (g_fee_ctx.lane[lane].gc_state == (uint8_t)FEE_GC_IDLE)
        {
            return FEE_E_OK;
        }

        --step_budget;
    }

    return FEE_E_BUSY;
}

rt_bool_t fee_gc_lane_blocks_io(uint8_t lane)
{
    if ((lane >= (uint8_t)FEE_LANE_COUNT) || (lane <= (uint8_t)FEE_LANE_META))
    {
        return RT_FALSE;
    }

    if ((g_fee_ctx.lane[lane].gc_state != (uint8_t)FEE_GC_IDLE) &&
        (g_fee_ctx.lane[lane].gc_state != (uint8_t)FEE_GC_ERASE_OLD))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

rt_bool_t fee_gc_has_background_work(void)
{
    uint8_t lane;

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        if ((g_fee_ctx.lane[lane].gc_state != (uint8_t)FEE_GC_IDLE) ||
            (g_fee_ctx.lane[lane].gc_requested != 0U) ||
            (g_fee_ctx.lane[lane].gc_force != 0U))
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

rt_bool_t fee_gc_allows_checkpoint(void)
{
    uint8_t lane;

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        if ((g_fee_ctx.lane[lane].gc_state == (uint8_t)FEE_GC_PREPARE_DST) ||
            (g_fee_ctx.lane[lane].gc_state == (uint8_t)FEE_GC_COPY_ONE) ||
            (g_fee_ctx.lane[lane].gc_state == (uint8_t)FEE_GC_SWITCH_ACTIVE))
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

void fee_gc_mainfunction(void)
{
    uint8_t lane;
    uint8_t target_lane = (uint8_t)FEE_LANE_COUNT;

    if (fee_recovery_is_full_ready() == RT_FALSE)
    {
        return;
    }

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        if (g_fee_ctx.lane[lane].gc_state != (uint8_t)FEE_GC_IDLE)
        {
            target_lane = lane;
            break;
        }
    }

    if (target_lane == (uint8_t)FEE_LANE_COUNT)
    {
        for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
        {
            if ((fee_gc_lane_supports_reclaim(lane) != RT_FALSE) &&
                (g_fee_ctx.lane[lane].gc_force != 0U))
            {
                target_lane = lane;
                break;
            }
        }
    }

    if (target_lane == (uint8_t)FEE_LANE_COUNT)
    {
        for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
        {
            if ((fee_gc_lane_supports_reclaim(lane) != RT_FALSE) &&
                (g_fee_ctx.lane[lane].gc_requested != 0U))
            {
                target_lane = lane;
                break;
            }
        }
    }

    if (target_lane < (uint8_t)FEE_LANE_COUNT)
    {
        if (fee_gc_step_lane(target_lane) != FEE_E_OK)
        {
            g_fee_ctx.job_result = FEE_JOB_FAILED;
        }
    }
}
