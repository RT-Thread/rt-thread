#include "fee_onflash.h"
#include <string.h>

static uint32_t fee_onflash_crc32_update(uint32_t crc, const uint8_t *data, uint32_t len)
{
    uint32_t i;

    if (data == RT_NULL)
    {
        return crc;
    }

    for (i = 0U; i < len; ++i)
    {
        crc = (crc << 5) - crc + data[i];
    }

    return crc;
}

static uint32_t fee_onflash_crc32_accumulate(const uint8_t *data, uint32_t len)
{
    return fee_onflash_crc32_update(0U, data, len);
}

static rt_bool_t fee_onflash_is_sector_state_valid(uint8_t state)
{
    if ((state == (uint8_t)FEE_SECTOR_PREPARE) ||
        (state == (uint8_t)FEE_SECTOR_ACTIVE) ||
        (state == (uint8_t)FEE_SECTOR_GC_DST) ||
        (state == (uint8_t)FEE_SECTOR_OLD_PENDING_ERASE) ||
        (state == (uint8_t)FEE_SECTOR_BAD))
    {
        return RT_TRUE;
    }

    return RT_FALSE;
}

static uint32_t fee_onflash_sector_header_crc(const fee_sector_header_t *header)
{
    const uint8_t *raw;
    uint32_t prefix_len;

    if (header == RT_NULL)
    {
        return 0U;
    }

    raw = (const uint8_t *)header;
    prefix_len = (uint32_t)((const uint8_t *)&header->hdr_crc - raw);
    return fee_onflash_crc32_accumulate(raw, prefix_len);
}

static uint32_t fee_onflash_record_header_crc(const fee_record_header_t *header)
{
    const uint8_t *raw;
    uint32_t prefix_len;

    if (header == RT_NULL)
    {
        return 0U;
    }

    raw = (const uint8_t *)header;
    prefix_len = (uint32_t)((const uint8_t *)&header->hdr_crc - raw);
    return fee_onflash_crc32_accumulate(raw, prefix_len);
}

static uint32_t fee_onflash_commit_tail_crc(const fee_commit_tail_t *tail)
{
    uint32_t crc;

    if (tail == RT_NULL)
    {
        return 0U;
    }

    crc = fee_onflash_crc32_update(0U, (const uint8_t *)&tail->data_crc, (uint32_t)sizeof(tail->data_crc));
    crc = fee_onflash_crc32_update(crc, (const uint8_t *)&tail->tail_flags, (uint32_t)sizeof(tail->tail_flags));
    return crc;
}

uint32_t fee_onflash_align_up(uint32_t value, uint32_t align)
{
    if (align == 0U)
    {
        return value;
    }

    return ((value + align - 1U) / align) * align;
}

uint32_t fee_onflash_calc_record_span(const fee_block_cfg_t *cfg, uint16_t data_len)
{
    uint32_t align;
    uint32_t payload_len;
    uint32_t span;

    if (cfg == RT_NULL)
    {
        return 0U;
    }

    align = (cfg->record_align == 0U) ? FEE_CFG_ALIGN_UNIT : cfg->record_align;
    payload_len = fee_onflash_align_up((uint32_t)data_len, FEE_CFG_ALIGN_UNIT);
    span = (uint32_t)sizeof(fee_record_header_t) + payload_len + (uint32_t)sizeof(fee_commit_tail_t);

    return fee_onflash_align_up(span, align);
}

fee_ret_t fee_onflash_encode_sector_header(fee_sector_header_t *header,
    uint8_t lane_id, uint8_t state, uint32_t generation, uint32_t data_start, uint32_t data_end)
{
    if (header == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    if ((fee_onflash_is_sector_state_valid(state) == RT_FALSE) || (data_start >= data_end))
    {
        return FEE_E_PARAM;
    }

    (void)memset(header, 0, sizeof(*header));
    header->magic = FEE_SECTOR_MAGIC;
    header->format_version = FEE_CFG_FORMAT_VERSION;
    header->lane_id = lane_id;
    header->state = state;
    header->generation = generation;
    header->data_start = data_start;
    header->data_end = data_end;
    header->hdr_seq = generation;
    header->hdr_crc = fee_onflash_sector_header_crc(header);
    header->commit_marker = FEE_COMMIT_MARKER;

    return FEE_E_OK;
}

fee_ret_t fee_onflash_encode_record_header(fee_record_header_t *header,
    uint16_t block_id, uint8_t record_type, uint16_t data_len, uint32_t seq)
{
    if (header == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    (void)memset(header, 0, sizeof(*header));
    header->magic = FEE_RECORD_MAGIC;
    header->block_id = block_id;
    header->record_type = record_type;
    header->flags = 0x01U;
    header->data_len = data_len;
    header->header_len = (uint16_t)sizeof(*header);
    header->seq = seq;
    header->hdr_crc = fee_onflash_record_header_crc(header);

    return FEE_E_OK;
}

fee_ret_t fee_onflash_encode_commit_tail(fee_commit_tail_t *tail, const uint8_t *data, uint16_t len)
{
    if (tail == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    (void)memset(tail, 0, sizeof(*tail));
    tail->data_crc = fee_onflash_crc32_accumulate(data, len);
    tail->tail_flags = 0U;
    tail->tail_crc = fee_onflash_commit_tail_crc(tail);
    tail->commit_marker = FEE_COMMIT_MARKER;

    return FEE_E_OK;
}

rt_bool_t fee_onflash_is_record_committed(const fee_commit_tail_t *tail)
{
    if (tail == RT_NULL)
    {
        return RT_FALSE;
    }

    return (tail->commit_marker == FEE_COMMIT_MARKER) ? RT_TRUE : RT_FALSE;
}

rt_bool_t fee_onflash_validate_sector_header(const fee_sector_header_t *header)
{
    if (header == RT_NULL)
    {
        return RT_FALSE;
    }

    if (header->magic != FEE_SECTOR_MAGIC)
    {
        return RT_FALSE;
    }

    if (header->format_version != FEE_CFG_FORMAT_VERSION)
    {
        return RT_FALSE;
    }

    if (fee_onflash_is_sector_state_valid(header->state) == RT_FALSE)
    {
        return RT_FALSE;
    }

    if ((header->data_start == 0U) || (header->data_start >= header->data_end))
    {
        return RT_FALSE;
    }

    if (header->hdr_crc != fee_onflash_sector_header_crc(header))
    {
        return RT_FALSE;
    }

    if (header->commit_marker != FEE_COMMIT_MARKER)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

rt_bool_t fee_onflash_validate_record_header(const fee_record_header_t *header, const fee_block_cfg_t *cfg)
{
    if ((header == RT_NULL) || (cfg == RT_NULL))
    {
        return RT_FALSE;
    }

    if ((header->magic != FEE_RECORD_MAGIC) ||
        (header->block_id != cfg->block_id) ||
        (header->header_len != (uint16_t)sizeof(*header)) ||
        (header->hdr_crc != fee_onflash_record_header_crc(header)))
    {
        return RT_FALSE;
    }

    if ((header->flags & 0xF8U) != 0U)
    {
        return RT_FALSE;
    }

    if ((header->record_type != (uint8_t)FEE_RECORD_DATA) &&
        (header->record_type != (uint8_t)FEE_RECORD_TOMBSTONE))
    {
        return RT_FALSE;
    }

    if (header->record_type == (uint8_t)FEE_RECORD_DATA)
    {
        if ((header->data_len == 0U) || (header->data_len > cfg->max_len))
        {
            return RT_FALSE;
        }
    }
    else if (header->data_len != 0U)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

rt_bool_t fee_onflash_validate_commit_tail(const fee_commit_tail_t *tail)
{
    if (tail == RT_NULL)
    {
        return RT_FALSE;
    }

    if (tail->commit_marker != FEE_COMMIT_MARKER)
    {
        return RT_FALSE;
    }

    return (tail->tail_crc == fee_onflash_commit_tail_crc(tail)) ? RT_TRUE : RT_FALSE;
}

rt_bool_t fee_onflash_validate_payload_crc(const fee_commit_tail_t *tail, const uint8_t *data, uint16_t len)
{
    uint32_t payload_crc;

    if (tail == RT_NULL)
    {
        return RT_FALSE;
    }

    payload_crc = fee_onflash_crc32_accumulate(data, len);
    return (tail->data_crc == payload_crc) ? RT_TRUE : RT_FALSE;
}
