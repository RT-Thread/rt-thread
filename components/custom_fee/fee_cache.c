#include "fee_internal.h"

#define FEE_CKPT_FLAG_CUR_VALID   (0x01UL)
#define FEE_CKPT_FLAG_PREV_VALID  (0x02UL)
#define FEE_CACHE_INDEX_SIZE      (64U)
#define FEE_CACHE_INDEX_EMPTY     (0xFFFFU)

typedef struct
{
    uint8_t used;
    uint16_t block_id;
    fee_cache_entry_t entry;
} fee_cache_slot_t;

static fee_cache_slot_t g_fee_cache[FEE_CACHE_MAX_ENTRIES];
static uint16_t g_fee_cache_index[FEE_CACHE_INDEX_SIZE];

static rt_bool_t fee_cache_addr_in_lane(uint8_t lane, uint32_t addr)
{
    const fee_lane_ctx_t *lane_ctx;

    if ((lane >= (uint8_t)FEE_LANE_COUNT) || (addr == FEE_INVALID_ADDR))
    {
        return RT_FALSE;
    }

    lane_ctx = &g_fee_ctx.lane[lane];
    if ((addr < lane_ctx->range_base) || (addr >= lane_ctx->range_limit))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static uint32_t fee_cache_hash_block_id(uint16_t block_id)
{
    return ((uint32_t)block_id % FEE_CACHE_INDEX_SIZE);
}

static rt_bool_t fee_cache_bind_slot(uint16_t block_id, uint16_t slot_idx)
{
    uint32_t probe;
    uint32_t start;

    probe = fee_cache_hash_block_id(block_id);
    start = probe;

    do
    {
        if ((g_fee_cache_index[probe] == FEE_CACHE_INDEX_EMPTY) ||
            (g_fee_cache_index[probe] == slot_idx))
        {
            g_fee_cache_index[probe] = slot_idx;
            return RT_TRUE;
        }

        probe = (probe + 1U) % FEE_CACHE_INDEX_SIZE;
    } while (probe != start);

    return RT_FALSE;
}

static fee_cache_slot_t *fee_cache_find_slot(uint16_t block_id)
{
    uint32_t probe;
    uint32_t start;

    probe = fee_cache_hash_block_id(block_id);
    start = probe;

    do
    {
        uint16_t slot_idx = g_fee_cache_index[probe];

        if (slot_idx == FEE_CACHE_INDEX_EMPTY)
        {
            return RT_NULL;
        }

        if ((slot_idx < FEE_CACHE_MAX_ENTRIES) &&
            (g_fee_cache[slot_idx].used != 0U) &&
            (g_fee_cache[slot_idx].block_id == block_id))
        {
            return &g_fee_cache[slot_idx];
        }

        probe = (probe + 1U) % FEE_CACHE_INDEX_SIZE;
    } while (probe != start);

    return RT_NULL;
}

static fee_cache_slot_t *fee_cache_alloc_slot(uint16_t block_id)
{
    uint32_t idx;

    for (idx = 0U; idx < FEE_CACHE_MAX_ENTRIES; ++idx)
    {
        if (g_fee_cache[idx].used == 0U)
        {
            if (fee_cache_bind_slot(block_id, (uint16_t)idx) == RT_FALSE)
            {
                return RT_NULL;
            }

            g_fee_cache[idx].used = 1U;
            g_fee_cache[idx].block_id = block_id;
            g_fee_cache[idx].entry.cur_addr = FEE_INVALID_ADDR;
            g_fee_cache[idx].entry.prev_addr = FEE_INVALID_ADDR;
            return &g_fee_cache[idx];
        }
    }

    return RT_NULL;
}

void fee_cache_init(void)
{
    (void)memset(g_fee_cache, 0, sizeof(g_fee_cache));
    (void)memset(g_fee_cache_index, 0xFF, sizeof(g_fee_cache_index));
}

fee_cache_entry_t *fee_cache_lookup(uint16_t block_id)
{
    fee_cache_slot_t *slot = fee_cache_find_slot(block_id);

    if (slot == RT_NULL)
    {
        return RT_NULL;
    }

    return &slot->entry;
}

void fee_cache_update_data(uint16_t block_id, uint8_t lane, uint32_t addr, uint16_t len, uint32_t seq)
{
    fee_cache_slot_t *slot = fee_cache_find_slot(block_id);

    if (slot == RT_NULL)
    {
        slot = fee_cache_alloc_slot(block_id);
    }

    if (slot == RT_NULL)
    {
        return;
    }

    if (slot->entry.cur_valid != 0U)
    {
        slot->entry.prev_addr = slot->entry.cur_addr;
        slot->entry.prev_valid = slot->entry.cur_valid;
        slot->entry.prev_sector = slot->entry.cur_sector;
    }

    slot->entry.lane = lane;
    slot->entry.cur_addr = addr;
    slot->entry.cur_valid = 1U;
    slot->entry.cur_sector = 0U;
    slot->entry.len = len;
    slot->entry.seq = seq;
}

void fee_cache_update_tombstone(uint16_t block_id, uint8_t lane, uint32_t addr, uint32_t seq)
{
    fee_cache_slot_t *slot = fee_cache_find_slot(block_id);

    if (slot == RT_NULL)
    {
        slot = fee_cache_alloc_slot(block_id);
    }

    if (slot == RT_NULL)
    {
        return;
    }

    if (slot->entry.cur_valid != 0U)
    {
        slot->entry.prev_addr = slot->entry.cur_addr;
        slot->entry.prev_valid = slot->entry.cur_valid;
        slot->entry.prev_sector = slot->entry.cur_sector;
    }

    slot->entry.lane = lane;
    slot->entry.cur_addr = addr;
    slot->entry.cur_valid = 0U;
    slot->entry.cur_sector = 0U;
    slot->entry.seq = seq;
}

void fee_cache_relocate_address(uint16_t block_id, uint32_t old_addr, uint32_t new_addr)
{
    fee_cache_slot_t *slot = fee_cache_find_slot(block_id);

    if ((slot == RT_NULL) || (old_addr == FEE_INVALID_ADDR) || (new_addr == FEE_INVALID_ADDR))
    {
        return;
    }

    if (slot->entry.cur_addr == old_addr)
    {
        slot->entry.cur_addr = new_addr;
    }

    if (slot->entry.prev_addr == old_addr)
    {
        slot->entry.prev_addr = new_addr;
    }
}

uint16_t fee_cache_export_ckpt(fee_ckpt_cache_entry_t *entries, uint16_t max_entries)
{
    uint16_t count = 0U;
    uint32_t idx;

    if (entries == RT_NULL)
    {
        return 0U;
    }

    for (idx = 0U; idx < FEE_CACHE_MAX_ENTRIES; ++idx)
    {
        uint32_t flags = 0U;

        if ((g_fee_cache[idx].used == 0U) || (count >= max_entries))
        {
            continue;
        }

        if (g_fee_cache[idx].entry.cur_valid != 0U)
        {
            flags |= FEE_CKPT_FLAG_CUR_VALID;
        }

        if (g_fee_cache[idx].entry.prev_valid != 0U)
        {
            flags |= FEE_CKPT_FLAG_PREV_VALID;
        }

        entries[count].block_id = g_fee_cache[idx].block_id;
        entries[count].lane = g_fee_cache[idx].entry.lane;
        entries[count].flags = flags;
        entries[count].len = g_fee_cache[idx].entry.len;
        entries[count].cur_addr = g_fee_cache[idx].entry.cur_addr;
        entries[count].prev_addr = g_fee_cache[idx].entry.prev_addr;
        entries[count].seq = g_fee_cache[idx].entry.seq;
        entries[count].reserved = 0U;
        ++count;
    }

    return count;
}

void fee_cache_import_ckpt(const fee_ckpt_cache_entry_t *entries, uint16_t entry_count)
{
    uint16_t idx;

    fee_cache_init();

    if (entries == RT_NULL)
    {
        return;
    }

    for (idx = 0U; (idx < entry_count) && (idx < FEE_CACHE_MAX_ENTRIES); ++idx)
    {
        const fee_block_cfg_t *cfg = fee_cfg_find_block((uint16_t)entries[idx].block_id);
        fee_cache_slot_t *slot;
        uint8_t lane = (uint8_t)entries[idx].lane;

        if ((cfg == RT_NULL) || (cfg->lane_type != lane) ||
            ((entries[idx].cur_addr != FEE_INVALID_ADDR) &&
             (fee_cache_addr_in_lane(lane, entries[idx].cur_addr) == RT_FALSE)) ||
            ((entries[idx].prev_addr != FEE_INVALID_ADDR) &&
             (fee_cache_addr_in_lane(lane, entries[idx].prev_addr) == RT_FALSE)) ||
            (((entries[idx].flags & FEE_CKPT_FLAG_PREV_VALID) != 0UL) &&
             (entries[idx].prev_addr == FEE_INVALID_ADDR)) ||
            (((entries[idx].flags & FEE_CKPT_FLAG_CUR_VALID) != 0UL) &&
             (entries[idx].cur_addr == FEE_INVALID_ADDR)) ||
            ((entries[idx].prev_addr != FEE_INVALID_ADDR) && (entries[idx].prev_addr == entries[idx].cur_addr)))
        {
            continue;
        }

        slot = fee_cache_alloc_slot((uint16_t)entries[idx].block_id);
        if (slot == RT_NULL)
        {
            break;
        }

        slot->entry.lane = (uint8_t)entries[idx].lane;
        slot->entry.cur_addr = entries[idx].cur_addr;
        slot->entry.prev_addr = entries[idx].prev_addr;
        slot->entry.seq = entries[idx].seq;
        slot->entry.len = (uint16_t)entries[idx].len;
        slot->entry.cur_valid = ((entries[idx].flags & FEE_CKPT_FLAG_CUR_VALID) != 0UL) ? 1U : 0U;
        slot->entry.prev_valid = ((entries[idx].flags & FEE_CKPT_FLAG_PREV_VALID) != 0UL) ? 1U : 0U;
        slot->entry.cur_sector = 0U;
        slot->entry.prev_sector = 0U;
    }
}
