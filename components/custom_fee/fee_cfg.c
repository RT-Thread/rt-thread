#include "fee_cfg.h"
#include "fee_onflash.h"
#include "fee_port.h"

static const fee_block_cfg_t g_fee_block_table[] =
{
    { 1U, 32U,   FEE_BLOCK_FAST,   FEE_LANE_FAST,   FEE_ENDURANCE_HOT,  1U, 1U, FEE_CRC16, 512U, 1U },
    { 2U, 128U,  FEE_BLOCK_NORMAL, FEE_LANE_NORMAL, FEE_ENDURANCE_WARM, 1U, 1U, FEE_CRC32, 8U,   1U },
    { 3U, 256U,  FEE_BLOCK_NORMAL, FEE_LANE_NORMAL, FEE_ENDURANCE_WARM, 1U, 1U, FEE_CRC32, 8U,   0U },
    { 4U, 768U,  FEE_BLOCK_BULK,   FEE_LANE_BULK,   FEE_ENDURANCE_COLD, 0U, 0U, FEE_CRC32, 512U, 0U },
};

static rt_bool_t fee_cfg_lane_matches_class(const fee_block_cfg_t *cfg)
{
    if (cfg == RT_NULL)
    {
        return RT_FALSE;
    }

    if ((cfg->block_class == FEE_BLOCK_FAST) && (cfg->lane_type == FEE_LANE_FAST))
    {
        return RT_TRUE;
    }

    if ((cfg->block_class == FEE_BLOCK_NORMAL) && (cfg->lane_type == FEE_LANE_NORMAL))
    {
        return RT_TRUE;
    }

    if ((cfg->block_class == FEE_BLOCK_BULK) && (cfg->lane_type == FEE_LANE_BULK))
    {
        return RT_TRUE;
    }

    if ((cfg->block_class == FEE_BLOCK_META) && (cfg->lane_type == FEE_LANE_META))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

const fee_block_cfg_t *fee_cfg_find_block(uint16_t block_id)
{
    uint16_t idx;

    for (idx = 0U; idx < fee_cfg_get_block_count(); ++idx)
    {
        if (g_fee_block_table[idx].block_id == block_id)
        {
            return &g_fee_block_table[idx];
        }
    }

    return RT_NULL;
}

const fee_block_cfg_t *fee_cfg_get_block_table(void)
{
    return &g_fee_block_table[0];
}

uint16_t fee_cfg_get_block_count(void)
{
    return (uint16_t)(sizeof(g_fee_block_table) / sizeof(g_fee_block_table[0]));
}

fee_ret_t fee_cfg_validate_table(void)
{
    fee_flash_caps_t caps;
    uint16_t count;
    uint16_t idx;
    uint16_t jdx;

    if (fee_port_get_caps(&caps) != FEE_E_OK)
    {
        return FEE_E_NOT_OK;
    }

    count = fee_cfg_get_block_count();
    if (count == 0U)
    {
        return FEE_E_NOT_OK;
    }

    for (idx = 0U; idx < count; ++idx)
    {
        const fee_block_cfg_t *cfg = &g_fee_block_table[idx];

        if ((cfg->block_id == 0U) || (cfg->max_len == 0U) || (cfg->max_len > FEE_CFG_MAX_BLOCK_LEN))
        {
            return FEE_E_NOT_OK;
        }

        if ((cfg->record_align == 0U) || (cfg->record_align < caps.program_unit) ||
            ((cfg->record_align % caps.program_unit) != 0U))
        {
            return FEE_E_NOT_OK;
        }

        if (fee_cfg_lane_matches_class(cfg) == RT_FALSE)
        {
            return FEE_E_NOT_OK;
        }

        if ((cfg->allow_rollback != 0U) && (cfg->keep_prev_copy == 0U))
        {
            return FEE_E_NOT_OK;
        }

        if ((cfg->block_class == FEE_BLOCK_FAST) &&
            (fee_onflash_calc_record_span(cfg, cfg->max_len) > FEE_CFG_FAST_SINGLE_RECORD_LIMIT))
        {
            return FEE_E_NOT_OK;
        }

        if ((cfg->block_class == FEE_BLOCK_BULK) && (cfg->boot_critical != 0U))
        {
            return FEE_E_NOT_OK;
        }

        for (jdx = (uint16_t)(idx + 1U); jdx < count; ++jdx)
        {
            if (cfg->block_id == g_fee_block_table[jdx].block_id)
            {
                return FEE_E_NOT_OK;
            }
        }
    }

    return FEE_E_OK;
}

rt_bool_t fee_cfg_is_boot_critical(uint16_t block_id)
{
    const fee_block_cfg_t *cfg = fee_cfg_find_block(block_id);

    if (cfg == RT_NULL)
    {
        return RT_FALSE;
    }

    return (cfg->boot_critical != 0U) ? RT_TRUE : RT_FALSE;
}
