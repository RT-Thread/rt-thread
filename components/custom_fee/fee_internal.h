#ifndef CUSTOM_FEE_INTERNAL_H
#define CUSTOM_FEE_INTERNAL_H

#include <string.h>
#include "fee_api.h"
#include "fee_cfg.h"
#include "fee_port.h"
#include "fee_onflash.h"

#define FEE_INVALID_ADDR         (0xFFFFFFFFUL)
#define FEE_CACHE_MAX_ENTRIES    (32U)

typedef struct
{
    uint8_t lane;
    uint32_t cur_addr;
    uint32_t prev_addr;
    uint32_t seq;
    uint16_t len;
    uint8_t cur_valid;
    uint8_t prev_valid;
    uint8_t cur_sector;
    uint8_t prev_sector;
} fee_cache_entry_t;

typedef struct
{
    uint8_t active_sector;
    uint8_t dst_sector;
    uint8_t spare_sector;
    uint8_t sector_count;
    uint16_t gc_cursor;
    uint8_t gc_state;
    uint8_t gc_requested;
    uint8_t gc_force;
    uint32_t range_base;
    uint32_t range_limit;
    uint32_t base_addr;
    uint32_t data_start;
    uint32_t limit_addr;
    uint32_t scan_start;
    uint32_t free_offset;
    uint32_t active_generation;
    uint32_t gc_start_threshold;
    uint32_t gc_force_threshold;
    uint32_t dirty_record_count;
    uint32_t dirty_bytes;
} fee_lane_ctx_t;

typedef struct
{
    fee_lane_ctx_t lane[FEE_LANE_COUNT];
    fee_status_t status;
    fee_job_result_t job_result;
    fee_init_state_t init_state;
    uint32_t checkpoint_generation;
    uint8_t checkpoint_dirty;
} fee_super_ctx_t;

typedef struct
{
    uint16_t block_id;
    uint16_t offset;
    uint16_t len;
    const uint8_t *src;
    uint8_t *dst;
} fee_request_t;

typedef enum
{
    FEE_REQ_NONE = 0,
    FEE_REQ_WRITE,
    FEE_REQ_INVALIDATE,
    FEE_REQ_ROLLBACK
} fee_request_type_t;

typedef struct
{
    uint32_t block_id;
    uint32_t lane;
    uint32_t flags;
    uint32_t len;
    uint32_t cur_addr;
    uint32_t prev_addr;
    uint32_t seq;
    uint32_t reserved;
} fee_ckpt_cache_entry_t;

extern fee_super_ctx_t g_fee_ctx;

void fee_core_reset_context(void);
fee_ret_t fee_core_init(void);
fee_ret_t fee_core_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
fee_ret_t fee_core_write(uint16_t block_id, const uint8_t *src, uint16_t len);
fee_ret_t fee_core_invalidate(uint16_t block_id);
fee_ret_t fee_core_rollback(uint16_t block_id);
void fee_core_mainfunction(void);

fee_ret_t fee_sched_submit_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
fee_ret_t fee_sched_submit_write(uint16_t block_id, const uint8_t *src, uint16_t len);
fee_ret_t fee_sched_submit_invalidate(uint16_t block_id);
fee_ret_t fee_sched_submit_rollback(uint16_t block_id);
void fee_sched_mainfunction(void);
rt_bool_t fee_sched_has_pending_work(void);

fee_ret_t fee_recovery_start(void);
fee_ret_t fee_recovery_step(void);
rt_bool_t fee_recovery_can_read_block(uint16_t block_id);
rt_bool_t fee_recovery_is_full_ready(void);

void fee_gc_mainfunction(void);
fee_ret_t fee_gc_reclaim_sync(uint8_t lane);
void fee_cache_init(void);
fee_cache_entry_t *fee_cache_lookup(uint16_t block_id);
void fee_cache_update_data(uint16_t block_id, uint8_t lane, uint32_t addr, uint16_t len, uint32_t seq);
void fee_cache_update_tombstone(uint16_t block_id, uint8_t lane, uint32_t addr, uint32_t seq);
void fee_cache_relocate_address(uint16_t block_id, uint32_t old_addr, uint32_t new_addr);
uint16_t fee_cache_export_ckpt(fee_ckpt_cache_entry_t *entries, uint16_t max_entries);
void fee_cache_import_ckpt(const fee_ckpt_cache_entry_t *entries, uint16_t entry_count);
void fee_ckpt_init(void);
fee_ret_t fee_ckpt_restore(void);
fee_ret_t fee_ckpt_flush(void);
void fee_lane_fast_init(void);
void fee_lane_log_init(void);
void fee_lane_bulk_init(void);

#endif
