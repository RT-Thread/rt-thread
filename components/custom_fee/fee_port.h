#ifndef CUSTOM_FEE_PORT_H
#define CUSTOM_FEE_PORT_H

#include <stdint.h>
#include "fee_api.h"

typedef struct
{
    uint32_t total_size;
    uint16_t read_unit;
    uint16_t program_unit;
    uint32_t erase_unit;
    uint16_t preferred_chunk;
    uint8_t supports_suspend;
    uint8_t supports_compare;
} fee_flash_caps_t;

typedef struct
{
    uint32_t init_calls;
    uint32_t poll_calls;
    uint32_t read_calls;
    uint32_t read_bytes;
    uint32_t write_calls;
    uint32_t write_bytes;
    uint32_t erase_calls;
    uint32_t erase_bytes;
} fee_port_debug_stats_t;

fee_ret_t fee_port_init(void);
fee_ret_t fee_port_get_caps(fee_flash_caps_t *caps);
fee_ret_t fee_port_read(uint32_t addr, uint8_t *dst, uint32_t len);
fee_ret_t fee_port_write(uint32_t addr, const uint8_t *src, uint32_t len);
fee_ret_t fee_port_erase(uint32_t addr, uint32_t len);
void fee_port_mainfunction(void);
fee_status_t fee_port_get_status(void);
fee_job_result_t fee_port_get_job_result(void);
fee_ret_t fee_port_debug_reset_stats(void);
fee_ret_t fee_port_debug_get_stats(fee_port_debug_stats_t *stats);
fee_ret_t fee_port_debug_get_storage(const uint8_t **storage, uint32_t *size);

#endif
