#ifndef CUSTOM_FEE_CFG_H
#define CUSTOM_FEE_CFG_H

#include <stdint.h>
#include "fee_api.h"

typedef enum
{
    FEE_LANE_META = 0,
    FEE_LANE_FAST,
    FEE_LANE_NORMAL,
    FEE_LANE_BULK,
    FEE_LANE_COUNT
} fee_lane_t;

typedef enum
{
    FEE_BLOCK_META = 0,
    FEE_BLOCK_FAST,
    FEE_BLOCK_NORMAL,
    FEE_BLOCK_BULK
} fee_block_class_t;

typedef enum
{
    FEE_ENDURANCE_HOT = 0,
    FEE_ENDURANCE_WARM,
    FEE_ENDURANCE_COLD
} fee_endurance_class_t;

typedef enum
{
    FEE_CRC_NONE = 0,
    FEE_CRC16,
    FEE_CRC32
} fee_crc_mode_t;

typedef struct
{
    uint16_t block_id;
    uint16_t max_len;
    uint8_t block_class;
    uint8_t lane_type;
    uint8_t endurance_class;
    uint8_t keep_prev_copy;
    uint8_t allow_rollback;
    uint8_t crc_mode;
    uint16_t record_align;
    uint8_t boot_critical;
} fee_block_cfg_t;

#define FEE_CFG_FORMAT_VERSION              (0x0100U)
#define FEE_CFG_ALIGN_UNIT                  (8U)
#define FEE_CFG_WORDLINE_SIZE               (512U)
#define FEE_CFG_FAST_SINGLE_RECORD_LIMIT    (512U)
#define FEE_CFG_MAX_PENDING_REQUESTS        (8U)
#define FEE_CFG_MAX_BLOCK_LEN               (1024U)

const fee_block_cfg_t *fee_cfg_find_block(uint16_t block_id);
const fee_block_cfg_t *fee_cfg_get_block_table(void);
uint16_t fee_cfg_get_block_count(void);
fee_ret_t fee_cfg_validate_table(void);
rt_bool_t fee_cfg_is_boot_critical(uint16_t block_id);

#endif
