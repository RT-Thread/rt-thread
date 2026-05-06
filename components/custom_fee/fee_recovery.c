#include "fee_internal.h"

static fee_flash_caps_t g_fee_caps;
static uint32_t g_fee_normal_base;
static uint32_t g_fee_normal_scan_start;

static fee_ret_t fee_recovery_get_layout(uint32_t *normal_base)
{
    if (g_fee_caps.total_size < (g_fee_caps.erase_unit * 3U))
    {
        return FEE_E_NOT_OK;
    }

    if (normal_base != RT_NULL)
    {
        *normal_base = g_fee_caps.erase_unit * 2U;
    }

    return FEE_E_OK;
}

static uint32_t fee_recovery_data_start(void)
{
    return g_fee_normal_base + fee_onflash_align_up((uint32_t)sizeof(fee_sector_header_t), g_fee_caps.program_unit);
}

static fee_ret_t fee_recovery_format_default_sector(void)
{
    fee_sector_header_t header;

    fee_cache_init();
    (void)memset(&header, 0, sizeof(header));
    header.magic = FEE_SECTOR_MAGIC;
    header.format_version = FEE_CFG_FORMAT_VERSION;
    header.lane_id = (uint8_t)FEE_LANE_NORMAL;
    header.state = (uint8_t)FEE_SECTOR_ACTIVE;
    header.generation = 1U;
    header.data_start = fee_recovery_data_start();
    header.data_end = g_fee_normal_base + g_fee_caps.erase_unit;
    header.commit_marker = FEE_COMMIT_MARKER;

    if (fee_port_erase(g_fee_normal_base, g_fee_caps.erase_unit) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    if (fee_port_write(g_fee_normal_base, (const uint8_t *)&header, (uint32_t)sizeof(header)) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = header.data_start;
    g_fee_ctx.lane[FEE_LANE_NORMAL].active_sector = 0U;
    g_fee_ctx.checkpoint_dirty = 1U;
    g_fee_normal_scan_start = header.data_start;

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_open_default_sector(void)
{
    fee_sector_header_t header;
    fee_ret_t ret;

    ret = fee_port_read(g_fee_normal_base, (uint8_t *)&header, (uint32_t)sizeof(header));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (!fee_onflash_validate_sector_header(&header))
    {
        return fee_recovery_format_default_sector();
    }

    g_fee_ctx.lane[FEE_LANE_NORMAL].active_sector = 0U;

    if ((g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset < header.data_start) ||
        (g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset > header.data_end))
    {
        g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = header.data_start;
    }

    if (g_fee_normal_scan_start < header.data_start)
    {
        g_fee_normal_scan_start = header.data_start;
    }

    if (g_fee_normal_scan_start > header.data_end)
    {
        g_fee_normal_scan_start = header.data_start;
    }

    return FEE_E_OK;
}

static fee_ret_t fee_recovery_scan_records(void)
{
    fee_record_header_t header;
    fee_commit_tail_t tail;
    const fee_block_cfg_t *cfg;
    uint32_t addr;
    uint32_t next_addr;
    fee_ret_t ret;

    addr = g_fee_normal_scan_start;

    while ((addr + (uint32_t)sizeof(header) + (uint32_t)sizeof(tail)) <= (g_fee_normal_base + g_fee_caps.erase_unit))
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

        ret = fee_port_read(addr + (uint32_t)sizeof(header) +
                fee_onflash_align_up((uint32_t)header.data_len, FEE_CFG_ALIGN_UNIT),
            (uint8_t *)&tail, (uint32_t)sizeof(tail));
        if (ret != FEE_E_OK)
        {
            return ret;
        }

        if (!fee_onflash_is_record_committed(&tail))
        {
            break;
        }

        cfg = fee_cfg_find_block(header.block_id);
        if (cfg == RT_NULL)
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

    g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = addr;
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

    ret = fee_recovery_get_layout(&g_fee_normal_base);
    if (ret != FEE_E_OK)
    {
        g_fee_ctx.init_state = FEE_INIT_FAILED;
        return ret;
    }

    g_fee_normal_scan_start = fee_recovery_data_start();

    return FEE_E_OK;
}

fee_ret_t fee_recovery_step(void)
{
    fee_ret_t ret;

    if (g_fee_ctx.init_state == FEE_INIT_META_SCAN)
    {
        ret = fee_ckpt_restore();
        if (ret == FEE_E_OK)
        {
            g_fee_normal_scan_start = g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset;
        }
        else
        {
            g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = fee_recovery_data_start();
            g_fee_normal_scan_start = fee_recovery_data_start();
        }

        ret = fee_recovery_open_default_sector();
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
        ret = fee_recovery_scan_records();
        if (ret != FEE_E_OK)
        {
            g_fee_ctx.init_state = FEE_INIT_FAILED;
            return ret;
        }

        g_fee_ctx.init_state = FEE_INIT_FULL_READY;
        g_fee_ctx.status = FEE_STATUS_IDLE;
        g_fee_ctx.job_result = FEE_JOB_OK;
        return FEE_E_OK;
    }

    return FEE_E_OK;
}

rt_bool_t fee_recovery_can_read_block(uint16_t block_id)
{
    (void)block_id;

    if (g_fee_ctx.init_state == FEE_INIT_FULL_READY)
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

rt_bool_t fee_recovery_is_full_ready(void)
{
    return (g_fee_ctx.init_state == FEE_INIT_FULL_READY) ? RT_TRUE : RT_FALSE;
}
