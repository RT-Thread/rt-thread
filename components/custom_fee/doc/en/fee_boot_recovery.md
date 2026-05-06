# FEE Boot Recovery

## 1. Purpose

This document defines the boot recovery strategy for `custom_fee`.

It answers three questions:

1. how RAM cache is rebuilt after power-on
2. when a first block read is allowed
3. how recovery behaves when checkpoint or GC state is incomplete

## 2. Recovery goals

- startup time should depend on bounded tail size, not total history size
- boot-critical blocks should become readable as early as possible
- interrupted GC must resolve deterministically
- initialization state must be visible to upper layers

## 3. Initialization states

Recommended states:

| State | Meaning | Readable blocks |
| --- | --- | --- |
| `INIT_RESET` | no flash access yet | none |
| `INIT_META_SCAN` | scanning meta lane and checkpoint copies | none |
| `INIT_CKPT_READY` | checkpoint restored to RAM | boot-critical only |
| `INIT_TAIL_SCAN` | scanning post-checkpoint tail | boot-critical and verified blocks |
| `INIT_FULL_READY` | recovery complete | all configured blocks |
| `INIT_DEGRADED` | checkpoint unusable or conflict resolved conservatively | restricted |
| `INIT_FAILED` | unrecoverable format or media failure | none |

## 4. First-readable point

To support early boot reads, readability is split into two levels:

1. checkpoint-ready read
2. full-ready read

`INIT_CKPT_READY` is allowed only if:

- at least one checkpoint copy is valid
- lane role mapping is reconstructed
- boot-critical blocks required by the checkpoint are present in RAM cache
- no fatal format conflict is detected

If a boot-critical block is missing from the checkpoint view, recovery must keep
scanning or fall back to degraded recovery.

## 5. Checkpoint restore

### 5.1 Checkpoint selection

When two checkpoint copies exist:

1. discard invalid CRC or missing-commit copies
2. pick the highest `ckpt_generation`
3. if generations match, prefer the complete copy
4. if arbitration is still ambiguous, enter degraded recovery

### 5.2 Minimum restored content

Checkpoint restore should rebuild at least:

- per-lane active, destination, and spare roles
- per-lane free offset
- current address per block
- previous address per block
- sequence number per block

Sanity checks should verify:

- addresses stay inside lane range
- current and previous address are not identical
- sequence order is monotonic
- active, destination, and spare do not alias the same sector

## 6. Tail scan

Tail scan exists to cover records written after the latest valid checkpoint.

### 6.1 Goal

It should scan only the post-checkpoint region, not full history.

### 6.2 Required bounds

Recommended configuration limits:

- `max_uncheckpointed_records_per_lane`
- `max_uncheckpointed_bytes_per_lane`
- `max_tail_scan_pages_per_lane`
- `ckpt_force_flush_threshold`

These limits make boot-time scan cost predictable.

### 6.3 Behavior

1. start from the checkpoint's `free_offset`
2. accept committed records and update cache
3. stop a contiguous region when an uncommitted record is reached
4. skip damaged headers by alignment unit and log the anomaly
5. stop at lane `data_end`

## 7. Interrupted GC recovery

RAM state cannot be trusted after reset. Arbitration must use:

- sector generation
- sector state
- committed records

Recommended outcomes:

- old active survives if GC destination was never fully committed
- GC destination becomes new active only when the copy set is complete enough
- conflicting actives trigger degraded arbitration using the newer, more complete
  live map

## 8. Stale checkpoint handling

Checkpoint may lag behind actual flash state. Recovery therefore needs two
phases:

1. build initial cache from checkpoint
2. correct it with tail scan and sector-header arbitration

If checkpoint sector-role data conflicts with valid sector headers, sector headers
win.

## 9. Read semantics during initialization

Recommended `fee_read()` behavior:

| State | Behavior |
| --- | --- |
| `INIT_RESET` / `INIT_META_SCAN` | return busy |
| `INIT_CKPT_READY` | allow boot-critical reads only |
| `INIT_TAIL_SCAN` | allow boot-critical and verified blocks |
| `INIT_FULL_READY` | normal read |
| `INIT_DEGRADED` | restricted read policy |
| `INIT_FAILED` | return failure |

## 10. Suggested implementation split

- `fee_recovery.c`: state machine, checkpoint arbitration, tail scan
- `fee_ckpt.c`: checkpoint parse and materialization
- `fee_cache.c`: cache import and conflict resolution

Suggested helper APIs:

```c
fee_ret_t fee_recovery_start(void);
fee_ret_t fee_recovery_step(void);
rt_bool_t fee_recovery_can_read_block(uint16_t block_id);
rt_bool_t fee_recovery_is_full_ready(void);
```

## 11. Test focus

- checkpoint A valid, checkpoint B corrupt
- checkpoint B newer than checkpoint A
- both checkpoints invalid and degraded recovery path
- power loss during GC switch
- stale checkpoint pointing to an old active sector
- boot-critical block readable at checkpoint-ready stage
