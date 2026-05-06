#include "fee_internal.h"

#define FEE_CKPT_MAGIC           (0x4645434BUL)
#define FEE_CKPT_ENTRY_MAX       (FEE_CACHE_MAX_ENTRIES)

typedef struct
{
    uint32_t fast_free_offset;
    uint32_t normal_free_offset;
    uint32_t bulk_free_offset;
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

    if (caps.total_size < (caps.erase_unit * 8U))
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

void fee_ckpt_init(void)
{
    g_fee_ckpt_active_base = FEE_INVALID_ADDR;
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
    fee_ret_t ret;

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

    fee_cache_import_ckpt(&selected->payload.entries[0], (uint16_t)selected->payload.entry_count);
    g_fee_ctx.checkpoint_generation = selected->generation;
    g_fee_ctx.lane[FEE_LANE_FAST].free_offset = selected->payload.fast_free_offset;
    g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset = selected->payload.normal_free_offset;
    g_fee_ctx.lane[FEE_LANE_BULK].free_offset = selected->payload.bulk_free_offset;
    g_fee_ctx.checkpoint_dirty = 0U;

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
    image.payload.fast_free_offset = g_fee_ctx.lane[FEE_LANE_FAST].free_offset;
    image.payload.normal_free_offset = g_fee_ctx.lane[FEE_LANE_NORMAL].free_offset;
    image.payload.bulk_free_offset = g_fee_ctx.lane[FEE_LANE_BULK].free_offset;
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
    fee_ckpt_reset_dirty_accounting();

    return FEE_E_OK;
}
