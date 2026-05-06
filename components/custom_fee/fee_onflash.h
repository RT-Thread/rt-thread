#ifndef CUSTOM_FEE_ONFLASH_H
#define CUSTOM_FEE_ONFLASH_H

#include <stdint.h>
#include "fee_cfg.h"
#include "fee_api.h"

#define FEE_SECTOR_MAGIC        (0x46454553UL)
#define FEE_RECORD_MAGIC        (0x46454552UL)
#define FEE_COMMIT_MARKER       (0x434F4D4DUL)

typedef enum
{
    FEE_SECTOR_ERASED = 0xFF,
    FEE_SECTOR_PREPARE = 0x11,
    FEE_SECTOR_ACTIVE = 0x22,
    FEE_SECTOR_GC_DST = 0x33,
    FEE_SECTOR_OLD_PENDING_ERASE = 0x44,
    FEE_SECTOR_BAD = 0x55
} fee_sector_state_t;

typedef enum
{
    FEE_RECORD_DATA = 0xD1,
    FEE_RECORD_TOMBSTONE = 0xD2,
    FEE_RECORD_CKPT_CHUNK = 0xC1
} fee_record_type_t;

typedef struct
{
    uint32_t magic;
    uint16_t format_version;
    uint8_t lane_id;
    uint8_t state;
    uint32_t generation;
    uint32_t erase_count;
    uint32_t data_start;
    uint32_t data_end;
    uint32_t hdr_seq;
    uint32_t hdr_crc;
    uint32_t commit_marker;
    uint32_t reserved[7];
} fee_sector_header_t;

typedef struct
{
    uint32_t magic;
    uint16_t block_id;
    uint8_t record_type;
    uint8_t flags;
    uint16_t data_len;
    uint16_t header_len;
    uint32_t seq;
    uint32_t generation;
    uint32_t prev_addr_hint;
    uint32_t hdr_crc;
    uint32_t reserved;
} fee_record_header_t;

typedef struct
{
    uint32_t data_crc;
    uint32_t tail_crc;
    uint32_t tail_flags;
    uint32_t commit_marker;
} fee_commit_tail_t;

uint32_t fee_onflash_align_up(uint32_t value, uint32_t align);
uint32_t fee_onflash_calc_record_span(const fee_block_cfg_t *cfg, uint16_t data_len);
fee_ret_t fee_onflash_encode_record_header(fee_record_header_t *header,
    uint16_t block_id, uint8_t record_type, uint16_t data_len, uint32_t seq);
fee_ret_t fee_onflash_encode_commit_tail(fee_commit_tail_t *tail, const uint8_t *data, uint16_t len);
rt_bool_t fee_onflash_is_record_committed(const fee_commit_tail_t *tail);
rt_bool_t fee_onflash_validate_sector_header(const fee_sector_header_t *header);

#endif
