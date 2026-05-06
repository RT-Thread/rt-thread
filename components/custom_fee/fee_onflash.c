#include "fee_onflash.h"
#include <string.h>

static uint32_t fee_onflash_crc32_accumulate(const uint8_t *data, uint32_t len)
{
    uint32_t crc = 0U;
    uint32_t i;

    if (data == RT_NULL)
    {
        return 0U;
    }

    for (i = 0U; i < len; ++i)
    {
        crc = (crc << 5) - crc + data[i];
    }

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
    header->hdr_crc = fee_onflash_crc32_accumulate((const uint8_t *)header,
        (uint32_t)sizeof(*header) - (uint32_t)sizeof(header->reserved) - (uint32_t)sizeof(header->hdr_crc));

    return FEE_E_OK;
}

fee_ret_t fee_onflash_encode_commit_tail(fee_commit_tail_t *tail, const uint8_t *data, uint16_t len)
{
    if (tail == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    tail->data_crc = fee_onflash_crc32_accumulate(data, len);
    tail->tail_flags = 0U;
    tail->tail_crc = fee_onflash_crc32_accumulate((const uint8_t *)tail,
        (uint32_t)sizeof(*tail) - (uint32_t)sizeof(tail->commit_marker));
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

    if (header->commit_marker != FEE_COMMIT_MARKER)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}
