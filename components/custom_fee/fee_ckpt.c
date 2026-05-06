#include "fee_internal.h"

#define FEE_CKPT_MAGIC           (0x4645434BUL)
#define FEE_CKPT_ENTRY_MAX       (FEE_CACHE_MAX_ENTRIES)

typedef struct
{
    uint32_t free_offset;
    uint32_t active_generation;
    uint8_t active_sector;
    uint8_t dst_sector;
    uint8_t spare_sector;
    uint8_t sector_count;
    uint32_t reserved;
} fee_ckpt_lane_state_t;

typedef struct
{
    fee_ckpt_lane_state_t lane[FEE_LANE_COUNT];
    uint32_t entry_count;
    fee_ckpt_cache_entry_t entries[FEE_CKPT_ENTRY_MAX];
} fee_ckpt_payload_t;

typedef struct
{
    uint32_t magic;
    uint32_t format_version;
    uint32_t generation;
    fee_ckpt_payload_t payload;
    uint32_t payload_crc;
    uint32_t commit_marker;
    uint32_t reserved[4];
} fee_ckpt_image_t;

static uint32_t g_fee_ckpt_active_base = FEE_INVALID_ADDR;
static uint8_t g_fee_ckpt_restored = 0U;

static uint32_t fee_ckpt_crc32_accumulate(const uint8_t *data, uint32_t len)
{
    uint32_t crc = 0U;
    uint32_t idx;

    if (data == RT_NULL)
    {
        return 0U;
    }

    for (idx = 0U; idx < len; ++idx)
    {
        crc = (crc << 5) - crc + data[idx];
    }

    return crc;
}

static fee_ret_t fee_ckpt_get_layout(uint32_t *meta0_base, uint32_t *meta1_base)
{
    fee_flash_caps_t caps;
    fee_ret_t ret;

    ret = fee_port_get_caps(&caps);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (caps.total_size < (caps.erase_unit * fee_cfg_get_total_sector_count()))
    {
        return FEE_E_NOT_OK;
    }

    if (meta0_base != RT_NULL)
    {
        *meta0_base = 0U;
    }

    if (meta1_base != RT_NULL)
    {
        *meta1_base = caps.erase_unit;
    }

    return FEE_E_OK;
}

static uint32_t fee_ckpt_payload_crc(const fee_ckpt_image_t *image)
{
    return fee_ckpt_crc32_accumulate((const uint8_t *)&image->payload,
        (uint32_t)sizeof(image->payload));
}

static rt_bool_t fee_ckpt_is_valid(const fee_ckpt_image_t *image)
{
    if (image == RT_NULL)
    {
        return RT_FALSE;
    }

    if ((image->magic != FEE_CKPT_MAGIC) ||
        (image->format_version != FEE_CFG_FORMAT_VERSION) ||
        (image->commit_marker != FEE_COMMIT_MARKER))
    {
        return RT_FALSE;
    }

    if (image->payload.entry_count > FEE_CKPT_ENTRY_MAX)
    {
        return RT_FALSE;
    }

    return (image->payload_crc == fee_ckpt_payload_crc(image)) ? RT_TRUE : RT_FALSE;
}

static void fee_ckpt_capture_lane_state(uint8_t lane, fee_ckpt_lane_state_t *state)
{
    const fee_lane_ctx_t *lane_ctx;

    if ((state == RT_NULL) || (lane >= (uint8_t)FEE_LANE_COUNT))
    {
        return;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    (void)memset(state, 0, sizeof(*state));
    state->free_offset = lane_ctx->free_offset;
    state->active_generation = lane_ctx->active_generation;
    state->active_sector = lane_ctx->active_sector;
    state->dst_sector = lane_ctx->dst_sector;
    state->spare_sector = lane_ctx->spare_sector;
    state->sector_count = lane_ctx->sector_count;
}

static rt_bool_t fee_ckpt_validate_lane_state(uint8_t lane, const fee_ckpt_lane_state_t *state)
{
    const fee_lane_ctx_t *lane_ctx;
    uint8_t expected_sector_count;

    if ((state == RT_NULL) || (lane <= (uint8_t)FEE_LANE_META) || (lane >= (uint8_t)FEE_LANE_COUNT))
    {
        return RT_FALSE;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    expected_sector_count = lane_ctx->sector_count;
    if ((expected_sector_count == 0U) || (state->sector_count != expected_sector_count))
    {
        return RT_FALSE;
    }

    if ((state->active_generation == 0U) ||
        (state->active_sector >= expected_sector_count) ||
        (state->dst_sector >= expected_sector_count) ||
        (state->spare_sector >= expected_sector_count))
    {
        return RT_FALSE;
    }

    if (expected_sector_count == 1U)
    {
        if ((state->active_sector != 0U) || (state->dst_sector != 0U) || (state->spare_sector != 0U))
        {
            return RT_FALSE;
        }
    }
    else
    {
        if (state->active_sector == state->dst_sector)
        {
            return RT_FALSE;
        }

        if (state->spare_sector == state->active_sector)
        {
            return RT_FALSE;
        }

        if ((expected_sector_count > 2U) && (state->spare_sector == state->dst_sector))
        {
            return RT_FALSE;
        }
    }

    if ((state->free_offset < lane_ctx->range_base) || (state->free_offset > lane_ctx->range_limit))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void fee_ckpt_apply_lane_state(uint8_t lane, const fee_ckpt_lane_state_t *state)
{
    fee_lane_ctx_t *lane_ctx;

    if ((state == RT_NULL) || (lane <= (uint8_t)FEE_LANE_META) || (lane >= (uint8_t)FEE_LANE_COUNT))
    {
        return;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    lane_ctx->active_sector = state->active_sector;
    lane_ctx->dst_sector = state->dst_sector;
    lane_ctx->spare_sector = state->spare_sector;
    lane_ctx->gc_old_sector = state->active_sector;
    lane_ctx->active_generation = state->active_generation;
    lane_ctx->free_offset = state->free_offset;
    lane_ctx->scan_start = state->free_offset;
}

void fee_ckpt_init(void)
{
    g_fee_ckpt_active_base = FEE_INVALID_ADDR;
    g_fee_ckpt_restored = 0U;
}

static void fee_ckpt_reset_dirty_accounting(void)
{
    uint8_t lane;

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        g_fee_ctx.lane[lane].dirty_record_count = 0U;
        g_fee_ctx.lane[lane].dirty_bytes = 0U;
    }
}

fee_ret_t fee_ckpt_restore(void)
{
    fee_ckpt_image_t image0;
    fee_ckpt_image_t image1;
    const fee_ckpt_image_t *selected = RT_NULL;
    uint32_t meta0_base;
    uint32_t meta1_base;
    uint8_t lane;
    fee_ret_t ret;

    g_fee_ckpt_restored = 0U;

    ret = fee_ckpt_get_layout(&meta0_base, &meta1_base);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_read(meta0_base, (uint8_t *)&image0, (uint32_t)sizeof(image0));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_read(meta1_base, (uint8_t *)&image1, (uint32_t)sizeof(image1));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    if (fee_ckpt_is_valid(&image0) && fee_ckpt_is_valid(&image1))
    {
        if (image0.generation >= image1.generation)
        {
            selected = &image0;
            g_fee_ckpt_active_base = meta0_base;
        }
        else
        {
            selected = &image1;
            g_fee_ckpt_active_base = meta1_base;
        }
    }
    else if (fee_ckpt_is_valid(&image0))
    {
        selected = &image0;
        g_fee_ckpt_active_base = meta0_base;
    }
    else if (fee_ckpt_is_valid(&image1))
    {
        selected = &image1;
        g_fee_ckpt_active_base = meta1_base;
    }

    if (selected == RT_NULL)
    {
        return FEE_E_NOT_OK;
    }

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        if (fee_ckpt_validate_lane_state(lane, &selected->payload.lane[lane]) == RT_FALSE)
        {
            return FEE_E_NOT_OK;
        }
    }

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        fee_ckpt_apply_lane_state(lane, &selected->payload.lane[lane]);
    }

    fee_cache_import_ckpt(&selected->payload.entries[0], (uint16_t)selected->payload.entry_count);
    g_fee_ctx.checkpoint_generation = selected->generation;
    g_fee_ctx.checkpoint_dirty = 0U;
    g_fee_ctx.checkpoint_requested = 0U;
    g_fee_ctx.checkpoint_force = 0U;
    g_fee_ckpt_restored = 1U;

    return FEE_E_OK;
}

fee_ret_t fee_ckpt_flush(void)
{
    fee_ckpt_image_t image;
    uint32_t meta0_base;
    uint32_t meta1_base;
    uint32_t target_base;
    fee_ret_t ret;

    ret = fee_ckpt_get_layout(&meta0_base, &meta1_base);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    target_base = (g_fee_ckpt_active_base == meta0_base) ? meta1_base : meta0_base;

    (void)memset(&image, 0, sizeof(image));
    image.magic = FEE_CKPT_MAGIC;
    image.format_version = FEE_CFG_FORMAT_VERSION;
    image.generation = g_fee_ctx.checkpoint_generation + 1U;
    fee_ckpt_capture_lane_state((uint8_t)FEE_LANE_FAST, &image.payload.lane[FEE_LANE_FAST]);
    fee_ckpt_capture_lane_state((uint8_t)FEE_LANE_NORMAL, &image.payload.lane[FEE_LANE_NORMAL]);
    fee_ckpt_capture_lane_state((uint8_t)FEE_LANE_BULK, &image.payload.lane[FEE_LANE_BULK]);
    image.payload.entry_count = fee_cache_export_ckpt(&image.payload.entries[0], FEE_CKPT_ENTRY_MAX);
    image.payload_crc = fee_ckpt_payload_crc(&image);
    image.commit_marker = FEE_COMMIT_MARKER;

    ret = fee_port_erase(target_base, meta1_base - meta0_base);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    ret = fee_port_write(target_base, (const uint8_t *)&image, (uint32_t)sizeof(image));
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_ckpt_active_base = target_base;
    g_fee_ctx.checkpoint_generation = image.generation;
    g_fee_ctx.checkpoint_dirty = 0U;
    g_fee_ctx.checkpoint_requested = 0U;
    g_fee_ctx.checkpoint_force = 0U;
    g_fee_ckpt_restored = 1U;
    fee_ckpt_reset_dirty_accounting();

    return FEE_E_OK;
}

rt_bool_t fee_ckpt_has_restored_image(void)
{
    return (g_fee_ckpt_restored != 0U) ? RT_TRUE : RT_FALSE;
}
