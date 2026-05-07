#include <string.h>
#include "rtthread.h"
#include "finsh.h"
#include "fee_api.h"
#include "fee_cfg.h"
#include "fee_port.h"
#include "fee_internal.h"
#include "fee_onflash.h"

#define FEE_TEST_POLL_BUDGET         (20000U)
#define FEE_TEST_GC_WRITE_COUNT      (160U)
#define FEE_TEST_LAYOUT_MAX_RECORDS  (12U)
#define FEE_TEST_FLASH_WINDOW_BYTES  (96U)
#define FEE_TEST_CKPT_MAGIC          (0x4645434BUL)

typedef struct
{
    rt_tick_t tick;
    uint32_t ms;
} fee_test_stamp_t;

typedef struct
{
    rt_tick_t ticks;
    uint32_t ms;
} fee_test_duration_t;

typedef struct
{
    uint32_t free_offset;
    uint32_t active_generation;
    uint8_t active_sector;
    uint8_t dst_sector;
    uint8_t spare_sector;
    uint8_t sector_count;
    uint32_t reserved;
} fee_test_ckpt_lane_state_t;

typedef struct
{
    fee_test_ckpt_lane_state_t lane[FEE_LANE_COUNT];
    uint32_t entry_count;
    fee_ckpt_cache_entry_t entries[FEE_CACHE_MAX_ENTRIES];
} fee_test_ckpt_payload_t;

typedef struct
{
    uint32_t magic;
    uint32_t format_version;
    uint32_t generation;
    fee_test_ckpt_payload_t payload;
    uint32_t payload_crc;
    uint32_t commit_marker;
    uint32_t reserved[4];
} fee_test_ckpt_image_t;

static uint32_t fee_test_crc32_accumulate(const uint8_t *data, uint32_t len)
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

static uint32_t fee_test_ckpt_payload_crc(const fee_test_ckpt_image_t *image)
{
    return fee_test_crc32_accumulate((const uint8_t *)&image->payload,
        (uint32_t)sizeof(image->payload));
}

static rt_bool_t fee_test_ckpt_is_valid(const fee_test_ckpt_image_t *image)
{
    if (image == RT_NULL)
    {
        return RT_FALSE;
    }

    if ((image->magic != FEE_TEST_CKPT_MAGIC) ||
        (image->format_version != FEE_CFG_FORMAT_VERSION) ||
        (image->commit_marker != FEE_COMMIT_MARKER))
    {
        return RT_FALSE;
    }

    if (image->payload.entry_count > FEE_CACHE_MAX_ENTRIES)
    {
        return RT_FALSE;
    }

    return (image->payload_crc == fee_test_ckpt_payload_crc(image)) ? RT_TRUE : RT_FALSE;
}

static fee_test_stamp_t fee_test_stamp_now(void)
{
    fee_test_stamp_t stamp;

    stamp.tick = rt_tick_get();
    stamp.ms = rt_tick_get_millisecond();
    return stamp;
}

static fee_test_duration_t fee_test_elapsed(fee_test_stamp_t start, fee_test_stamp_t end)
{
    fee_test_duration_t duration;

    duration.ticks = end.tick - start.tick;
    duration.ms = end.ms - start.ms;
    return duration;
}

static int fee_test_wait_full_ready(uint32_t budget, uint32_t *loops)
{
    uint32_t used_loops = 0U;

    while (budget > 0U)
    {
        fee_init_state_t state = fee_get_init_state();

        if (state == FEE_INIT_FULL_READY)
        {
            if (loops != RT_NULL)
            {
                *loops = used_loops;
            }
            return 0;
        }

        if (state == FEE_INIT_FAILED)
        {
            break;
        }

        fee_mainfunction();
        ++used_loops;
        --budget;
    }

    if (loops != RT_NULL)
    {
        *loops = used_loops;
    }

    return -1;
}

static int fee_test_wait_idle(uint32_t budget, uint32_t *loops)
{
    uint32_t used_loops = 0U;

    while (budget > 0U)
    {
        fee_job_result_t job_result;

        fee_mainfunction();
        ++used_loops;
        job_result = fee_get_job_result();

        if ((fee_get_init_state() == FEE_INIT_FULL_READY) &&
            (fee_get_memif_status() == FEE_STATUS_IDLE) &&
            (job_result != FEE_JOB_PENDING))
        {
            if (loops != RT_NULL)
            {
                *loops = used_loops;
            }
            return (job_result == FEE_JOB_FAILED) ? -1 : 0;
        }

        if ((fee_get_init_state() == FEE_INIT_FAILED) || (job_result == FEE_JOB_FAILED))
        {
            break;
        }

        --budget;
    }

    if (loops != RT_NULL)
    {
        *loops = used_loops;
    }

    return -1;
}

static void fee_test_fill_pattern(uint8_t *buf, uint16_t len, uint8_t seed)
{
    uint16_t idx;

    for (idx = 0U; idx < len; ++idx)
    {
        buf[idx] = (uint8_t)(seed + (uint8_t)(idx * 3U));
    }
}

static int fee_test_expect_ret(const char *step, fee_ret_t actual, fee_ret_t expected)
{
    if (actual != expected)
    {
        rt_kprintf("custom_fee_test: %s failed, ret=%u expected=%u\n",
            step, (unsigned)actual, (unsigned)expected);
        return -1;
    }

    return 0;
}

static const char *fee_test_lane_name(uint8_t lane)
{
    if (lane == (uint8_t)FEE_LANE_META)
    {
        return "meta";
    }

    if (lane == (uint8_t)FEE_LANE_FAST)
    {
        return "fast";
    }

    if (lane == (uint8_t)FEE_LANE_NORMAL)
    {
        return "normal";
    }

    if (lane == (uint8_t)FEE_LANE_BULK)
    {
        return "bulk";
    }

    return "unknown";
}

static const char *fee_test_sector_state_name(uint8_t state)
{
    if (state == (uint8_t)FEE_SECTOR_PREPARE)
    {
        return "PREPARE";
    }

    if (state == (uint8_t)FEE_SECTOR_ACTIVE)
    {
        return "ACTIVE";
    }

    if (state == (uint8_t)FEE_SECTOR_GC_DST)
    {
        return "GC_DST";
    }

    if (state == (uint8_t)FEE_SECTOR_OLD_PENDING_ERASE)
    {
        return "OLD_PENDING_ERASE";
    }

    if (state == (uint8_t)FEE_SECTOR_BAD)
    {
        return "BAD";
    }

    if (state == (uint8_t)FEE_SECTOR_ERASED)
    {
        return "ERASED";
    }

    return "UNKNOWN";
}

static const char *fee_test_record_type_name(uint8_t type)
{
    if (type == (uint8_t)FEE_RECORD_DATA)
    {
        return "DATA";
    }

    if (type == (uint8_t)FEE_RECORD_TOMBSTONE)
    {
        return "TOMBSTONE";
    }

    if (type == (uint8_t)FEE_RECORD_CKPT_CHUNK)
    {
        return "CKPT_CHUNK";
    }

    return "UNKNOWN";
}

static void fee_test_print_buffer(const char *label, const uint8_t *buf, uint16_t len)
{
    uint16_t idx;

    if ((label == RT_NULL) || (buf == RT_NULL))
    {
        return;
    }

    rt_kprintf("custom_fee_diag_test: %s len=%u\n", label, (unsigned)len);
    for (idx = 0U; idx < len; idx = (uint16_t)(idx + 16U))
    {
        uint16_t line_len = (uint16_t)(len - idx);
        uint16_t jdx;

        if (line_len > 16U)
        {
            line_len = 16U;
        }

        rt_kprintf("custom_fee_diag_test:   %04u:", (unsigned)idx);
        for (jdx = 0U; jdx < line_len; ++jdx)
        {
            rt_kprintf(" %02x", buf[idx + jdx]);
        }
        rt_kprintf("\n");
    }
}

static rt_bool_t fee_test_fetch_debug_stats(fee_port_debug_stats_t *stats)
{
    if (stats == RT_NULL)
    {
        return RT_FALSE;
    }

    if (fee_port_debug_get_stats(stats) != FEE_E_OK)
    {
        (void)memset(stats, 0, sizeof(*stats));
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void fee_test_print_stats(const char *label, const fee_test_duration_t *duration,
    const fee_port_debug_stats_t *stats, rt_bool_t stats_valid, uint32_t wait_loops)
{
    if ((label == RT_NULL) || (duration == RT_NULL))
    {
        return;
    }

    if (stats_valid == RT_FALSE)
    {
        rt_kprintf("custom_fee_diag_test: %s time=%u ms ticks=%lu wait_loops=%u driver[unavailable]\n",
            label, (unsigned)duration->ms, (unsigned long)duration->ticks, (unsigned)wait_loops);
        return;
    }

    rt_kprintf(
        "custom_fee_diag_test: %s time=%u ms ticks=%lu wait_loops=%u "
        "driver[init=%u read=%u/%uB write=%u/%uB erase=%u/%uB poll=%u]\n",
        label,
        (unsigned)duration->ms,
        (unsigned long)duration->ticks,
        (unsigned)wait_loops,
        (unsigned)stats->init_calls,
        (unsigned)stats->read_calls,
        (unsigned)stats->read_bytes,
        (unsigned)stats->write_calls,
        (unsigned)stats->write_bytes,
        (unsigned)stats->erase_calls,
        (unsigned)stats->erase_bytes,
        (unsigned)stats->poll_calls);
}

static rt_bool_t fee_test_storage_copy(const uint8_t *storage, uint32_t flash_size,
    uint32_t addr, void *dst, uint32_t len)
{
    if ((storage == RT_NULL) || (dst == RT_NULL) || (len == 0U))
    {
        return RT_FALSE;
    }

    if ((addr > flash_size) || (len > (flash_size - addr)))
    {
        return RT_FALSE;
    }

    (void)memcpy(dst, &storage[addr], len);
    return RT_TRUE;
}

static rt_bool_t fee_test_storage_is_erased(const uint8_t *storage, uint32_t flash_size,
    uint32_t addr, uint32_t len)
{
    uint32_t idx;

    if ((storage == RT_NULL) || (len == 0U))
    {
        return RT_FALSE;
    }

    if ((addr > flash_size) || (len > (flash_size - addr)))
    {
        return RT_FALSE;
    }

    for (idx = 0U; idx < len; ++idx)
    {
        if (storage[addr + idx] != 0xFFU)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

static void fee_test_dump_hex_window(const char *label, const uint8_t *storage,
    uint32_t flash_size, uint32_t addr, uint32_t len)
{
    uint32_t idx;

    if ((label == RT_NULL) || (storage == RT_NULL) || (len == 0U))
    {
        return;
    }

    if (addr >= flash_size)
    {
        return;
    }

    if (len > (flash_size - addr))
    {
        len = flash_size - addr;
    }

    rt_kprintf("custom_fee_diag_test: %s addr=0x%08x len=%u\n",
        label, (unsigned)addr, (unsigned)len);
    for (idx = 0U; idx < len; idx += 16U)
    {
        uint32_t line_len = len - idx;
        uint32_t jdx;

        if (line_len > 16U)
        {
            line_len = 16U;
        }

        rt_kprintf("custom_fee_diag_test:   0x%08x:", (unsigned)(addr + idx));
        for (jdx = 0U; jdx < line_len; ++jdx)
        {
            rt_kprintf(" %02x", storage[addr + idx + jdx]);
        }
        rt_kprintf("\n");
    }
}

static void fee_test_dump_checkpoint_layout(const uint8_t *storage, uint32_t flash_size,
    const fee_flash_caps_t *caps)
{
    uint32_t idx;

    if ((storage == RT_NULL) || (caps == RT_NULL))
    {
        return;
    }

    for (idx = 0U; idx < FEE_CFG_META_SECTOR_COUNT; ++idx)
    {
        fee_test_ckpt_image_t image;
        uint32_t base = idx * caps->erase_unit;
        rt_bool_t valid;
        uint8_t lane;

        if (fee_test_storage_is_erased(storage, flash_size, base, 64U) != RT_FALSE)
        {
            rt_kprintf("custom_fee_diag_test: meta[%u] base=0x%08x ERASED\n",
                (unsigned)idx, (unsigned)base);
            continue;
        }

        if (fee_test_storage_copy(storage, flash_size, base, &image, (uint32_t)sizeof(image)) == RT_FALSE)
        {
            rt_kprintf("custom_fee_diag_test: meta[%u] base=0x%08x unreadable\n",
                (unsigned)idx, (unsigned)base);
            continue;
        }

        valid = fee_test_ckpt_is_valid(&image);
        rt_kprintf(
            "custom_fee_diag_test: meta[%u] base=0x%08x valid=%u generation=%lu entries=%u commit=0x%08x\n",
            (unsigned)idx,
            (unsigned)base,
            (unsigned)valid,
            (unsigned long)image.generation,
            (unsigned)image.payload.entry_count,
            (unsigned)image.commit_marker);

        if (valid != RT_FALSE)
        {
            for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
            {
                const fee_test_ckpt_lane_state_t *state = &image.payload.lane[lane];

                rt_kprintf(
                    "custom_fee_diag_test:   meta[%u] lane=%s active=%u dst=%u spare=%u "
                    "gen=%lu free=0x%08x\n",
                    (unsigned)idx,
                    fee_test_lane_name(lane),
                    (unsigned)state->active_sector,
                    (unsigned)state->dst_sector,
                    (unsigned)state->spare_sector,
                    (unsigned long)state->active_generation,
                    (unsigned)state->free_offset);
            }
        }

    }
}

static void fee_test_dump_business_lane_layout(uint8_t lane, const uint8_t *storage,
    uint32_t flash_size, const fee_flash_caps_t *caps)
{
    const fee_lane_ctx_t *lane_ctx = &g_fee_ctx.lane[lane];
    uint8_t sector_idx;
    uint32_t active_window_len;

    rt_kprintf(
        "custom_fee_diag_test: lane=%s range=[0x%08x,0x%08x) active=%u dst=%u spare=%u "
        "old=%u free=0x%08x limit=0x%08x dirty_records=%lu dirty_bytes=%lu\n",
        fee_test_lane_name(lane),
        (unsigned)lane_ctx->range_base,
        (unsigned)lane_ctx->range_limit,
        (unsigned)lane_ctx->active_sector,
        (unsigned)lane_ctx->dst_sector,
        (unsigned)lane_ctx->spare_sector,
        (unsigned)lane_ctx->gc_old_sector,
        (unsigned)lane_ctx->free_offset,
        (unsigned)lane_ctx->limit_addr,
        (unsigned long)lane_ctx->dirty_record_count,
        (unsigned long)lane_ctx->dirty_bytes);

    for (sector_idx = 0U; sector_idx < lane_ctx->sector_count; ++sector_idx)
    {
        fee_sector_header_t sector_header;
        uint32_t sector_base = lane_ctx->range_base + ((uint32_t)sector_idx * caps->erase_unit);
        uint32_t addr;
        uint32_t record_count = 0U;
        uint32_t printed_records = 0U;

        if (fee_test_storage_is_erased(storage, flash_size, sector_base,
            (uint32_t)sizeof(fee_sector_header_t)) != RT_FALSE)
        {
            rt_kprintf("custom_fee_diag_test:   sector=%u base=0x%08x ERASED\n",
                (unsigned)sector_idx, (unsigned)sector_base);
            continue;
        }

        if (fee_test_storage_copy(storage, flash_size, sector_base,
            &sector_header, (uint32_t)sizeof(sector_header)) == RT_FALSE)
        {
            rt_kprintf("custom_fee_diag_test:   sector=%u base=0x%08x unreadable\n",
                (unsigned)sector_idx, (unsigned)sector_base);
            continue;
        }

        if (!fee_onflash_validate_sector_header(&sector_header))
        {
            rt_kprintf("custom_fee_diag_test:   sector=%u base=0x%08x raw/unknown\n",
                (unsigned)sector_idx, (unsigned)sector_base);
            fee_test_dump_hex_window("sector raw", storage, flash_size, sector_base, 64U);
            continue;
        }

        rt_kprintf(
            "custom_fee_diag_test:   sector=%u base=0x%08x state=%s generation=%lu "
            "data=[0x%08x,0x%08x)\n",
            (unsigned)sector_idx,
            (unsigned)sector_base,
            fee_test_sector_state_name(sector_header.state),
            (unsigned long)sector_header.generation,
            (unsigned)sector_header.data_start,
            (unsigned)sector_header.data_end);

        addr = sector_header.data_start;
        while ((addr + (uint32_t)sizeof(fee_record_header_t) +
                (uint32_t)sizeof(fee_commit_tail_t)) <= sector_header.data_end)
        {
            fee_record_header_t record_header;
            fee_commit_tail_t tail;
            const fee_block_cfg_t *cfg;
            uint32_t stored_len;
            uint32_t next_addr;
            uint32_t tail_addr;
            rt_bool_t committed;

            if (fee_test_storage_copy(storage, flash_size, addr, &record_header,
                (uint32_t)sizeof(record_header)) == RT_FALSE)
            {
                break;
            }

            if (record_header.magic != FEE_RECORD_MAGIC)
            {
                break;
            }

            cfg = fee_cfg_find_block(record_header.block_id);
            if ((cfg == RT_NULL) || (cfg->lane_type != lane) ||
                (fee_onflash_validate_record_header(&record_header, cfg) == RT_FALSE))
            {
                break;
            }

            stored_len = fee_onflash_align_up((uint32_t)record_header.data_len, caps->program_unit);
            tail_addr = addr + (uint32_t)sizeof(record_header) + stored_len;
            if (fee_test_storage_copy(storage, flash_size, tail_addr, &tail,
                (uint32_t)sizeof(tail)) == RT_FALSE)
            {
                break;
            }

            committed = fee_onflash_validate_commit_tail(&tail);
            if (printed_records < FEE_TEST_LAYOUT_MAX_RECORDS)
            {
                rt_kprintf(
                    "custom_fee_diag_test:     record=%lu addr=0x%08x block=%u type=%s "
                    "seq=%lu len=%u committed=%u prev=0x%08x\n",
                    (unsigned long)record_count,
                    (unsigned)addr,
                    (unsigned)record_header.block_id,
                    fee_test_record_type_name(record_header.record_type),
                    (unsigned long)record_header.seq,
                    (unsigned)record_header.data_len,
                    (unsigned)committed,
                    (unsigned)record_header.prev_addr_hint);
                ++printed_records;
            }

            next_addr = addr + fee_onflash_calc_record_span(cfg, record_header.data_len);
            if ((next_addr <= addr) || (next_addr > sector_header.data_end))
            {
                break;
            }

            addr = next_addr;
            ++record_count;
        }

        if (record_count > printed_records)
        {
            rt_kprintf("custom_fee_diag_test:     ... %lu more record(s) omitted\n",
                (unsigned long)(record_count - printed_records));
        }

        rt_kprintf("custom_fee_diag_test:   sector=%u stop_addr=0x%08x record_count=%lu\n",
            (unsigned)sector_idx, (unsigned)addr, (unsigned long)record_count);
    }

    active_window_len = 0U;
    if ((lane_ctx->base_addr < lane_ctx->free_offset) && (lane_ctx->base_addr < flash_size))
    {
        active_window_len = lane_ctx->free_offset - lane_ctx->base_addr;
        if (active_window_len > FEE_TEST_FLASH_WINDOW_BYTES)
        {
            active_window_len = FEE_TEST_FLASH_WINDOW_BYTES;
        }
    }

    if (active_window_len > 0U)
    {
        fee_test_dump_hex_window("active sector raw", storage, flash_size,
            lane_ctx->base_addr, active_window_len);
    }
}

static void fee_test_dump_flash_layout(const char *stage)
{
    fee_flash_caps_t caps;
    const uint8_t *storage = RT_NULL;
    uint32_t flash_size = 0U;
    uint8_t lane;

    if ((stage == RT_NULL) || (fee_port_get_caps(&caps) != FEE_E_OK))
    {
        rt_kprintf("custom_fee_diag_test: flash layout unavailable\n");
        return;
    }

    if (fee_port_debug_get_storage(&storage, &flash_size) != FEE_E_OK)
    {
        rt_kprintf("custom_fee_diag_test: flash layout unavailable for current driver\n");
        return;
    }

    rt_kprintf(
        "custom_fee_diag_test: flash layout [%s] total=0x%08x erase=0x%08x read_unit=%u "
        "program_unit=%u\n",
        stage,
        (unsigned)caps.total_size,
        (unsigned)caps.erase_unit,
        (unsigned)caps.read_unit,
        (unsigned)caps.program_unit);

    fee_test_dump_checkpoint_layout(storage, flash_size, &caps);

    for (lane = (uint8_t)FEE_LANE_FAST; lane <= (uint8_t)FEE_LANE_BULK; ++lane)
    {
        fee_test_dump_business_lane_layout(lane, storage, flash_size, &caps);
    }
}

static int fee_test_reset_backend(void)
{
    fee_flash_caps_t caps;
    uint32_t used_bytes;
    uint32_t idx;
    fee_ret_t ret;

    ret = fee_port_init();
    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: fee_port_init failed ret=%u\n", (unsigned)ret);
        return -1;
    }

    ret = fee_port_get_caps(&caps);
    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: fee_port_get_caps failed ret=%u\n", (unsigned)ret);
        return -1;
    }

    used_bytes = fee_cfg_get_total_sector_count() * caps.erase_unit;
    if (used_bytes > caps.total_size)
    {
        rt_kprintf("custom_fee_test: backend too small, used=0x%08x total=0x%08x\n",
            (unsigned)used_bytes, (unsigned)caps.total_size);
        return -1;
    }

    for (idx = 0U; idx < fee_cfg_get_total_sector_count(); ++idx)
    {
        ret = fee_port_erase(idx * caps.erase_unit, caps.erase_unit);
        if (ret != FEE_E_OK)
        {
            rt_kprintf("custom_fee_test: erase sector=%u failed ret=%u\n",
                (unsigned)idx, (unsigned)ret);
            return -1;
        }
    }

    return 0;
}

static int fee_test_measure_init(const char *label, rt_bool_t verbose)
{
    fee_test_stamp_t start;
    fee_test_stamp_t end;
    fee_test_duration_t duration;
    fee_port_debug_stats_t stats;
    rt_bool_t stats_valid = RT_FALSE;
    uint32_t wait_loops = 0U;

    (void)fee_port_debug_reset_stats();
    start = fee_test_stamp_now();

    if (fee_test_expect_ret(label, fee_init(), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_full_ready(FEE_TEST_POLL_BUDGET, &wait_loops) != 0)
    {
        rt_kprintf("custom_fee_test: %s did not reach FULL_READY\n", label);
        return -1;
    }

    end = fee_test_stamp_now();
    duration = fee_test_elapsed(start, end);

    if (verbose != RT_FALSE)
    {
        stats_valid = fee_test_fetch_debug_stats(&stats);
        fee_test_print_stats(label, &duration, &stats, stats_valid, wait_loops);
    }

    return 0;
}

static int fee_test_measure_write(uint16_t block_id, const uint8_t *src, uint16_t len,
    const char *label, rt_bool_t verbose)
{
    fee_test_stamp_t start;
    fee_test_stamp_t end;
    fee_test_duration_t duration;
    fee_port_debug_stats_t stats;
    rt_bool_t stats_valid = RT_FALSE;
    uint32_t wait_loops = 0U;

    (void)fee_port_debug_reset_stats();
    start = fee_test_stamp_now();

    if (fee_test_expect_ret(label, fee_write(block_id, src, len), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET, &wait_loops) != 0)
    {
        rt_kprintf("custom_fee_test: %s did not complete\n", label);
        return -1;
    }

    end = fee_test_stamp_now();
    duration = fee_test_elapsed(start, end);

    if (verbose != RT_FALSE)
    {
        stats_valid = fee_test_fetch_debug_stats(&stats);
        fee_test_print_stats(label, &duration, &stats, stats_valid, wait_loops);
        fee_test_print_buffer(label, src, len);
    }

    return 0;
}

static int fee_test_measure_read(uint16_t block_id, const uint8_t *expect, uint16_t len,
    const char *label, rt_bool_t verbose)
{
    uint8_t readback[FEE_CFG_MAX_BLOCK_LEN];
    fee_ret_t ret;
    fee_test_stamp_t start;
    fee_test_stamp_t end;
    fee_test_duration_t duration;
    fee_port_debug_stats_t stats;
    rt_bool_t stats_valid = RT_FALSE;

    if (len > (uint16_t)sizeof(readback))
    {
        rt_kprintf("custom_fee_test: readback len too large: %u\n", (unsigned)len);
        return -1;
    }

    (void)memset(readback, 0, sizeof(readback));
    (void)fee_port_debug_reset_stats();
    start = fee_test_stamp_now();
    ret = fee_read(block_id, 0U, readback, len);
    end = fee_test_stamp_now();

    if (ret != FEE_E_OK)
    {
        rt_kprintf("custom_fee_test: %s ret=%u\n", label, (unsigned)ret);
        return -1;
    }

    if (memcmp(readback, expect, len) != 0)
    {
        rt_kprintf("custom_fee_test: readback mismatch on block=%u for %s\n",
            (unsigned)block_id, label);
        return -1;
    }

    duration = fee_test_elapsed(start, end);
    if (verbose != RT_FALSE)
    {
        stats_valid = fee_test_fetch_debug_stats(&stats);
        fee_test_print_stats(label, &duration, &stats, stats_valid, 0U);
        fee_test_print_buffer(label, readback, len);
    }

    return 0;
}

static int fee_test_measure_action(fee_ret_t actual, const char *label, rt_bool_t verbose)
{
    fee_test_stamp_t start;
    fee_test_stamp_t end;
    fee_test_duration_t duration;
    fee_port_debug_stats_t stats;
    rt_bool_t stats_valid = RT_FALSE;
    uint32_t wait_loops = 0U;

    (void)fee_port_debug_reset_stats();
    start = fee_test_stamp_now();

    if (fee_test_expect_ret(label, actual, FEE_E_OK) != 0)
    {
        return -1;
    }

    if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET, &wait_loops) != 0)
    {
        rt_kprintf("custom_fee_test: %s did not complete\n", label);
        return -1;
    }

    end = fee_test_stamp_now();
    duration = fee_test_elapsed(start, end);

    if (verbose != RT_FALSE)
    {
        stats_valid = fee_test_fetch_debug_stats(&stats);
        fee_test_print_stats(label, &duration, &stats, stats_valid, wait_loops);
    }

    return 0;
}

static int fee_test_measure_failed_read(uint16_t block_id, uint16_t len, fee_ret_t expected,
    const char *label, rt_bool_t verbose)
{
    uint8_t readback[FEE_CFG_MAX_BLOCK_LEN];
    fee_ret_t ret;
    fee_test_stamp_t start;
    fee_test_stamp_t end;
    fee_test_duration_t duration;
    fee_port_debug_stats_t stats;
    rt_bool_t stats_valid = RT_FALSE;

    if (len > (uint16_t)sizeof(readback))
    {
        rt_kprintf("custom_fee_test: failed-read len too large: %u\n", (unsigned)len);
        return -1;
    }

    (void)memset(readback, 0, sizeof(readback));
    (void)fee_port_debug_reset_stats();
    start = fee_test_stamp_now();
    ret = fee_read(block_id, 0U, readback, len);
    end = fee_test_stamp_now();

    if (fee_test_expect_ret(label, ret, expected) != 0)
    {
        return -1;
    }

    duration = fee_test_elapsed(start, end);
    if (verbose != RT_FALSE)
    {
        stats_valid = fee_test_fetch_debug_stats(&stats);
        fee_test_print_stats(label, &duration, &stats, stats_valid, 0U);
    }

    return 0;
}

static int fee_test_run_gc_bench(uint8_t *fast_buf, uint16_t len, rt_bool_t verbose)
{
    rt_tick_t total_ticks = 0U;
    uint32_t total_ms = 0U;
    rt_tick_t gc_total_ticks = 0U;
    uint32_t gc_total_ms = 0U;
    rt_tick_t gc_max_ticks = 0U;
    uint32_t gc_events = 0U;
    uint32_t idx;

    for (idx = 0U; idx < FEE_TEST_GC_WRITE_COUNT; ++idx)
    {
        fee_test_stamp_t start;
        fee_test_stamp_t end;
        fee_test_duration_t duration;
        fee_port_debug_stats_t stats;
        rt_bool_t stats_valid = RT_FALSE;
        uint32_t wait_loops = 0U;

        fee_test_fill_pattern(fast_buf, len, (uint8_t)(0x60U + idx));
        (void)fee_port_debug_reset_stats();
        start = fee_test_stamp_now();

        if (fee_test_expect_ret("gc stress write", fee_write(1U, fast_buf, len), FEE_E_OK) != 0)
        {
            rt_kprintf("custom_fee_test: gc stress failed at iter=%u\n", (unsigned)idx);
            return -1;
        }

        if (fee_test_wait_idle(FEE_TEST_POLL_BUDGET, &wait_loops) != 0)
        {
            rt_kprintf("custom_fee_test: gc stress did not complete at iter=%u\n", (unsigned)idx);
            return -1;
        }

        end = fee_test_stamp_now();
        duration = fee_test_elapsed(start, end);
        total_ticks += duration.ticks;
        total_ms += duration.ms;

        if (verbose != RT_FALSE)
        {
            stats_valid = fee_test_fetch_debug_stats(&stats);
            if ((stats_valid != RT_FALSE) && (stats.erase_calls > 0U))
            {
                ++gc_events;
                gc_total_ticks += duration.ticks;
                gc_total_ms += duration.ms;
                if (duration.ticks > gc_max_ticks)
                {
                    gc_max_ticks = duration.ticks;
                }
            }

            if (stats_valid != RT_FALSE)
            {
                rt_kprintf(
                    "custom_fee_diag_test: gc_write[%03u] time=%u ms ticks=%lu wait_loops=%u "
                    "driver[read=%u/%uB write=%u/%uB erase=%u/%uB poll=%u]\n",
                    (unsigned)idx,
                    (unsigned)duration.ms,
                    (unsigned long)duration.ticks,
                    (unsigned)wait_loops,
                    (unsigned)stats.read_calls,
                    (unsigned)stats.read_bytes,
                    (unsigned)stats.write_calls,
                    (unsigned)stats.write_bytes,
                    (unsigned)stats.erase_calls,
                    (unsigned)stats.erase_bytes,
                    (unsigned)stats.poll_calls);
            }
            else
            {
                rt_kprintf(
                    "custom_fee_diag_test: gc_write[%03u] time=%u ms ticks=%lu wait_loops=%u "
                    "driver[unavailable]\n",
                    (unsigned)idx,
                    (unsigned)duration.ms,
                    (unsigned long)duration.ticks,
                    (unsigned)wait_loops);
            }
        }
    }

    if (verbose != RT_FALSE)
    {
        rt_kprintf(
            "custom_fee_diag_test: gc summary writes=%u total_time=%u ms total_ticks=%lu "
            "gc_events=%u gc_time=%u ms gc_ticks=%lu gc_max_ticks=%lu\n",
            (unsigned)FEE_TEST_GC_WRITE_COUNT,
            (unsigned)total_ms,
            (unsigned long)total_ticks,
            (unsigned)gc_events,
            (unsigned)gc_total_ms,
            (unsigned long)gc_total_ticks,
            (unsigned long)gc_max_ticks);
    }

    return 0;
}

static int fee_test_run(rt_bool_t verbose)
{
    uint8_t fast_a[32];
    uint8_t fast_b[32];
    uint8_t normal_a[64];
    fee_block_status_t status;

    fee_test_fill_pattern(fast_a, (uint16_t)sizeof(fast_a), 0x11U);
    fee_test_fill_pattern(fast_b, (uint16_t)sizeof(fast_b), 0x51U);
    fee_test_fill_pattern(normal_a, (uint16_t)sizeof(normal_a), 0x21U);

    if (fee_test_reset_backend() != 0)
    {
        return -1;
    }

    if (fee_test_measure_init("init", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_write(1U, fast_a, (uint16_t)sizeof(fast_a),
        "write block1 fast_a", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(1U, fast_a, (uint16_t)sizeof(fast_a),
        "read block1 fast_a", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_write(1U, fast_b, (uint16_t)sizeof(fast_b),
        "write block1 fast_b", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(1U, fast_b, (uint16_t)sizeof(fast_b),
        "read block1 fast_b", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_action(fee_rollback(1U), "rollback block1", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(1U, fast_a, (uint16_t)sizeof(fast_a),
        "read block1 rollback", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_write(2U, normal_a, (uint16_t)sizeof(normal_a),
        "write block2 normal_a", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(2U, normal_a, (uint16_t)sizeof(normal_a),
        "read block2 normal_a", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_init("re-init", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(1U, fast_a, (uint16_t)sizeof(fast_a),
        "read block1 after re-init", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_read(2U, normal_a, (uint16_t)sizeof(normal_a),
        "read block2 after re-init", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_run_gc_bench(fast_b, (uint16_t)sizeof(fast_b), verbose) != 0)
    {
        return -1;
    }

    fee_test_fill_pattern(fast_b, (uint16_t)sizeof(fast_b),
        (uint8_t)(0x60U + (FEE_TEST_GC_WRITE_COUNT - 1U)));
    if (fee_test_measure_read(1U, fast_b, (uint16_t)sizeof(fast_b),
        "read block1 after gc", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_measure_action(fee_invalidate(1U), "invalidate block1", verbose) != 0)
    {
        return -1;
    }

    if (fee_test_expect_ret("get_status", fee_get_status(1U, &status), FEE_E_OK) != 0)
    {
        return -1;
    }

    if (status != FEE_BLOCK_STATUS_INVALIDATED)
    {
        rt_kprintf("custom_fee_test: expected INVALIDATED, got %u\n", (unsigned)status);
        return -1;
    }

    if (verbose != RT_FALSE)
    {
        rt_kprintf("custom_fee_diag_test: block1 status after invalidate=%u\n", (unsigned)status);
    }

    if (fee_test_measure_failed_read(1U, (uint16_t)sizeof(fast_a), FEE_E_NOT_OK,
        "read invalidated block1", verbose) != 0)
    {
        return -1;
    }

    if (verbose != RT_FALSE)
    {
        fee_test_dump_flash_layout("final");
    }

    return 0;
}

int custom_fee_test(void)
{
    rt_kprintf("custom_fee_test: start\n");

    if (fee_test_run(RT_FALSE) != 0)
    {
        return -1;
    }

    rt_kprintf("custom_fee_test: PASS\n");
    return 0;
}
MSH_CMD_EXPORT(custom_fee_test, custom fee smoke test);

int custom_fee_diag_test(void)
{
    rt_kprintf("custom_fee_diag_test: start\n");

    if (fee_test_run(RT_TRUE) != 0)
    {
        return -1;
    }

    rt_kprintf("custom_fee_diag_test: PASS\n");
    return 0;
}
MSH_CMD_EXPORT(custom_fee_diag_test, custom fee diagnostic test);
