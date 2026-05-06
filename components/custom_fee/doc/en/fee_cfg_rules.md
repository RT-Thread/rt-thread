# FEE Configuration Rules

## 1. Purpose

This document defines block configuration, lane mapping, capacity planning, and
compile-time validation rules.

The configuration model should:

- reject invalid layouts at build time
- keep lane responsibilities explicit
- make startup and capacity budgets calculable

## 2. Block configuration model

Recommended fields:

```c
typedef struct
{
    uint16 block_id;
    uint16 max_len;
    uint8 block_class;
    uint8 lane_type;
    uint8 endurance_class;
    uint8 keep_prev_copy;
    uint8 allow_rollback;
    uint8 crc_mode;
    uint16 record_align;
    uint8 boot_critical;
} fee_block_cfg_t;
```

## 3. Block classes

| Class | Intent |
| --- | --- |
| `FAST` | immediate-style, low-latency block |
| `NORMAL` | regular configuration or state data |
| `BULK` | large or infrequent large blocks |
| `META` | checkpoint and internal super-state only |

## 4. Lane mapping rules

Mandatory mapping:

1. fast blocks go to fast lane only
2. normal blocks go to normal lane only
3. bulk blocks go to bulk lane only
4. business blocks never go to meta lane

If the upper layer marks a block as immediate, configuration should map it to
the fast lane automatically.

## 5. Size and alignment

Record size budget:

```text
record_span(i) = align(record_header + max_len(i) + commit_tail, record_align(i))
```

Recommended categories:

| Category | Payload hint | Rule |
| --- | --- | --- |
| small | `<= 448 B` | aim for single-wordline commit |
| medium | `449 B .. 2048 B` | multi-wordline is acceptable |
| large | `> 2048 B` | default to bulk lane |

Hard rules:

- fast blocks must fit the configured single-record fast limit
- fast blocks should not span multiple wordlines
- bulk blocks should not be configured as immediate
- rollback-capable blocks must keep previous copy

## 6. Capacity planning

Suggested formulas:

```text
live_span(i)  = record_span(i) * (keep_prev_copy(i) ? 2 : 1)
lane_live     = sum(live_span(i))
lane_payload  = sector_count(lane) * sector_usable_bytes - lane_mgmt_bytes
lane_headroom = max_burst_records(lane) * max_record_span(lane) + switch_guard(lane)
```

Required relation:

```text
lane_payload >= lane_live + lane_headroom + gc_fragment_guard
```

Useful defaults:

- fast lane burst budget: `2 .. 4`
- normal lane burst budget: `1 .. 2`
- bulk lane burst budget: `1`
- GC fragment guard: at least two largest records in the lane

## 7. Startup-time related knobs

Useful configuration items:

- `boot_critical`
- background checkpoint thresholds
- forced checkpoint thresholds
- max uncheckpointed records per lane
- max uncheckpointed bytes per lane
- max tail-scan pages per lane

## 8. Compile-time validation checklist

Validate at least:

1. unique `block_id`
2. `max_len > 0`
3. `record_align >= program_unit`
4. fast block size fits fast-lane constraints
5. rollback implies previous-copy retention
6. lane capacity covers live data and headroom
7. checkpoint image fits meta-lane capacity
8. boot-critical blocks are checkpoint-eligible

## 9. Example

```c
static const fee_block_cfg_t fee_block_table[] =
{
    { .block_id = 1, .max_len = 32,   .block_class = FEE_BLOCK_FAST,   .lane_type = FEE_LANE_FAST,   .keep_prev_copy = 1, .allow_rollback = 1, .boot_critical = 1 },
    { .block_id = 2, .max_len = 256,  .block_class = FEE_BLOCK_NORMAL, .lane_type = FEE_LANE_NORMAL, .keep_prev_copy = 1, .allow_rollback = 1, .boot_critical = 0 },
    { .block_id = 3, .max_len = 4096, .block_class = FEE_BLOCK_BULK,   .lane_type = FEE_LANE_BULK,   .keep_prev_copy = 0, .allow_rollback = 0, .boot_critical = 0 },
};
```

## 10. Test focus

- reject illegal immediate large blocks at build time
- reject lane-capacity overflow at build time
- report missing checkpoint space for boot-critical blocks
- reject record alignment below program-unit requirement
