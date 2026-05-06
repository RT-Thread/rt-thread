#include "fee_internal.h"

#define FEE_GC_PREV_VALID_FLAG      (0x02UL)
#define FEE_GC_MOVE_MAX             (FEE_CACHE_MAX_ENTRIES * 2U)
#define FEE_GC_COPY_BUFFER_SIZE     (2048U)

typedef struct
{
    uint16_t block_id;
    uint32_t old_addr;
    uint32_t new_addr;
} fee_gc_move_t;

static rt_bool_t fee_gc_lane_supports_reclaim(uint8_t lane)
{
    if ((lane == (uint8_t)FEE_LANE_NORMAL) &&
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

static fee_ret_t fee_gc_prepare_sector(uint8_t lane, uint8_t sector_idx, uint8_t state,
    uint32_t generation, const fee_flash_caps_t *caps)
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

    if (fee_port_erase(sector_base, caps->erase_unit) != FEE_E_OK)
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

static fee_ret_t fee_gc_copy_cache_record(uint16_t block_id, uint32_t src_addr, uint32_t dst_limit,
    uint32_t *dst_cursor, fee_gc_move_t *moves, uint16_t *move_count, const fee_flash_caps_t *caps)
{
    const fee_block_cfg_t *cfg = fee_cfg_find_block(block_id);
    uint32_t span;
    fee_ret_t ret;

    if ((cfg == RT_NULL) || (dst_cursor == RT_NULL) || (moves == RT_NULL) || (move_count == RT_NULL))
    {
        return FEE_E_NOT_OK;
    }

    if (*move_count >= FEE_GC_MOVE_MAX)
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_gc_copy_record(src_addr, *dst_cursor, dst_limit, cfg, caps, &span);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    moves[*move_count].block_id = block_id;
    moves[*move_count].old_addr = src_addr;
    moves[*move_count].new_addr = *dst_cursor;
    *dst_cursor += span;
    *move_count = (uint16_t)(*move_count + 1U);

    return FEE_E_OK;
}

static fee_ret_t fee_gc_copy_live_entries(uint8_t lane, uint32_t src_base, uint32_t src_limit,
    uint32_t dst_limit, uint32_t *dst_cursor, fee_gc_move_t *moves, uint16_t *move_count,
    const fee_flash_caps_t *caps)
{
    fee_ckpt_cache_entry_t entries[FEE_CACHE_MAX_ENTRIES];
    uint16_t entry_count;
    uint16_t idx;

    entry_count = fee_cache_export_ckpt(&entries[0], FEE_CACHE_MAX_ENTRIES);

    for (idx = 0U; idx < entry_count; ++idx)
    {
        if (entries[idx].lane != lane)
        {
            continue;
        }

        if (((entries[idx].flags & FEE_GC_PREV_VALID_FLAG) != 0UL) &&
            fee_gc_addr_in_sector(src_base, src_limit, entries[idx].prev_addr))
        {
            fee_ret_t ret = fee_gc_copy_cache_record((uint16_t)entries[idx].block_id, entries[idx].prev_addr,
                dst_limit, dst_cursor, moves, move_count, caps);

            if (ret != FEE_E_OK)
            {
                return ret;
            }
        }

        if ((entries[idx].cur_addr != FEE_INVALID_ADDR) &&
            (entries[idx].cur_addr != entries[idx].prev_addr) &&
            fee_gc_addr_in_sector(src_base, src_limit, entries[idx].cur_addr))
        {
            fee_ret_t ret = fee_gc_copy_cache_record((uint16_t)entries[idx].block_id, entries[idx].cur_addr,
                dst_limit, dst_cursor, moves, move_count, caps);

            if (ret != FEE_E_OK)
            {
                return ret;
            }
        }
    }

    return FEE_E_OK;
}

static void fee_gc_apply_moves(const fee_gc_move_t *moves, uint16_t move_count)
{
    uint16_t idx;

    for (idx = 0U; idx < move_count; ++idx)
    {
        fee_cache_relocate_address(moves[idx].block_id, moves[idx].old_addr, moves[idx].new_addr);
    }
}

static fee_ret_t fee_gc_run_normal_lane(void)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[FEE_LANE_NORMAL];
    fee_flash_caps_t caps;
    fee_gc_move_t moves[FEE_GC_MOVE_MAX];
    uint16_t move_count = 0U;
    uint8_t src_sector;
    uint8_t dst_sector;
    uint32_t src_base;
    uint32_t dst_base;
    uint32_t src_limit;
    uint32_t dst_limit;
    uint32_t dst_cursor;
    uint32_t dst_data_start;
    fee_ret_t ret;

    if (fee_gc_lane_supports_reclaim((uint8_t)FEE_LANE_NORMAL) == RT_FALSE)
    {
        return FEE_E_NOT_OK;
    }

    ret = fee_port_get_caps(&caps);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    src_sector = lane_ctx->active_sector;
    dst_sector = (uint8_t)((src_sector + 1U) % lane_ctx->sector_count);
    src_base = lane_ctx->base_addr;
    src_limit = lane_ctx->limit_addr;
    dst_base = fee_gc_sector_base(lane_ctx, &caps, dst_sector);
    dst_limit = dst_base + caps.erase_unit;
    dst_data_start = fee_gc_sector_data_start(dst_base, &caps);
    dst_cursor = dst_data_start;

    ret = fee_gc_prepare_sector((uint8_t)FEE_LANE_NORMAL, dst_sector, (uint8_t)FEE_SECTOR_GC_DST,
        lane_ctx->active_generation + 1U, &caps);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_gc_copy_live_entries((uint8_t)FEE_LANE_NORMAL, src_base, src_limit, dst_limit,
        &dst_cursor, &moves[0], &move_count, &caps);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    fee_gc_apply_moves(&moves[0], move_count);
    lane_ctx->active_sector = dst_sector;
    lane_ctx->dst_sector = dst_sector;
    lane_ctx->spare_sector = src_sector;
    lane_ctx->base_addr = dst_base;
    lane_ctx->data_start = dst_data_start;
    lane_ctx->limit_addr = dst_limit;
    lane_ctx->scan_start = dst_cursor;
    lane_ctx->free_offset = dst_cursor;
    lane_ctx->active_generation += 1U;
    lane_ctx->gc_requested = 0U;
    lane_ctx->gc_force = 0U;

    ret = fee_ckpt_flush();
    if (ret != FEE_E_OK)
    {
        lane_ctx->gc_requested = 1U;
        return ret;
    }

    ret = fee_port_erase(src_base, caps.erase_unit);
    if (ret != FEE_E_OK)
    {
        lane_ctx->gc_requested = 1U;
        return ret;
    }

    return FEE_E_OK;
}

fee_ret_t fee_gc_reclaim_sync(uint8_t lane)
{
    if (lane != (uint8_t)FEE_LANE_NORMAL)
    {
        return FEE_E_NOT_OK;
    }

    return fee_gc_run_normal_lane();
}

void fee_gc_mainfunction(void)
{
    fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[FEE_LANE_NORMAL];

    if (fee_recovery_is_full_ready() == RT_FALSE)
    {
        return;
    }

    if (fee_gc_lane_supports_reclaim((uint8_t)FEE_LANE_NORMAL) == RT_FALSE)
    {
        return;
    }

    if ((lane_ctx->gc_requested == 0U) && (lane_ctx->gc_force == 0U))
    {
        return;
    }

    if (g_fee_ctx.status != FEE_STATUS_IDLE)
    {
        return;
    }

    (void)fee_gc_run_normal_lane();
}
