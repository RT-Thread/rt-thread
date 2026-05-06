# FEE Redesign Overview

## 1. Purpose

This document describes the redesigned `custom_fee` architecture for fixed
logical blocks stored in Data Flash. The redesign is intentionally optimized for
predictable block access rather than generic key-value storage.

It keeps the properties that matter for an embedded FEE implementation:

- append-only persistence
- power-loss recovery
- rollback to the previous committed copy
- background checkpoint and garbage collection
- bounded startup recovery work

Companion documents:

- [fee_onflash_format.md](./fee_onflash_format.md)
- [fee_boot_recovery.md](./fee_boot_recovery.md)
- [fee_port_adapter.md](./fee_port_adapter.md)
- [fee_scheduler_gc.md](./fee_scheduler_gc.md)
- [fee_cache_checkpoint.md](./fee_cache_checkpoint.md)
- [fee_cfg_rules.md](./fee_cfg_rules.md)

## 2. Goals

### 2.1 Main goals

- address data by fixed `block_id`
- keep writes append-only
- use RAM cache for O(1)-style lookup after initialization
- recover cleanly from power loss
- keep one previous copy for rollback-capable blocks
- run GC incrementally with bounded work per scheduler tick
- keep flash geometry configurable through the port layer

### 2.2 Non-goals

- no generic KV database behavior
- no free-form string keys or range scans
- no requirement to clone every AUTOSAR Fee extension in phase 1

## 3. Why redesign

The redesign starts from a simple observation: AUTOSAR requires recoverable
asynchronous semantics, not a general-purpose database layout.

For a fixed block catalog, tighter layout rules buy lower latency:

- cache-based reads instead of repeated media scans
- lane isolation for fast and slow traffic
- checkpoint-driven startup instead of full history rebuild
- GC that copies live blocks from RAM metadata, not by rescanning all records

## 4. Design constraints

The design assumes real flash constraints still dominate behavior:

- programming granularity matters
- erase operations can block progress
- wordline alignment matters for large writes
- startup recovery needs a hard tail-scan budget

That leads to these design choices:

- explicit flash capability reporting
- lane-local sector rings
- commit-tail based validity
- checkpoint thresholds that prevent unbounded tail growth

## 5. Architecture

The recommended module split is:

```text
Application / NvM adapter
  -> fee_api.c
    -> fee_sched.c
    -> fee_core.c
    -> fee_gc.c
    -> fee_recovery.c
    -> fee_cache.c
    -> fee_ckpt.c
    -> fee_lane_fast.c
    -> fee_lane_log.c
    -> fee_lane_bulk.c
    -> fee_port_*.c
      -> flash backend
```

Responsibilities:

- `fee_api.c`: user-facing API and parameter checks
- `fee_sched.c`: request classes, queues, and dispatch priority
- `fee_core.c`: read/write/invalidate/rollback flow
- `fee_gc.c`: per-lane GC state machine
- `fee_recovery.c`: boot restore, tail scan, interrupted-GC recovery
- `fee_cache.c`: block lookup cache and address relocation
- `fee_ckpt.c`: checkpoint packing, write, and restore
- `fee_onflash.c`: encoding and validation of persistent structures
- `fee_cfg.*`: block table and lane/static limits

## 6. Storage model

### 6.1 Lane roles

The design separates data into lanes:

- `META`: checkpoint and super-state data
- `FAST`: immediate or latency-sensitive blocks
- `NORMAL`: regular blocks
- `BULK`: large or infrequent large blocks

Recommended topology:

- `FAST`: 3-sector ring
- `NORMAL`: 3-sector ring
- `BULK`: 2-sector or 3-sector ring
- `META`: dual-checkpoint copies

### 6.2 Sector layout

Each sector contains:

```text
SectorHeader
Record 0
Record 1
...
free area
```

Sector headers carry lane, state, generation, and integrity data.

### 6.3 Record layout

Each record is:

```text
RecordHeader
Payload
CommitTail
```

The last persistent write is always the `commit_marker` in the tail. A record
without a committed tail is ignored during recovery.

## 7. RAM cache and checkpoint

The in-memory model tracks:

- current and previous physical address per block
- per-lane active, destination, and spare sectors
- free offsets and GC state
- checkpoint generation and dirty state

Checkpoint exists for one reason: startup cost must be bounded. The implementation
should never depend on average-case boot time only. Instead it should keep
explicit limits on uncheckpointed records, bytes, and scan pages.

## 8. Core flows

### 8.1 Initialization

Recommended phases:

1. reset context
2. read flash capabilities
3. restore checkpoint if valid
4. expose `CKPT_READY` for boot-critical blocks
5. tail-scan the post-checkpoint region
6. enter `FULL_READY`

### 8.2 Write

Recommended write sequence:

1. validate block config and size
2. reserve space in the target lane
3. write record header
4. write payload
5. write commit tail except the final marker
6. write final commit marker
7. update cache and dirty counters

### 8.3 Read

Read should use RAM cache, not a fallback full-media scan. If the block is not
available in cache yet, the result should be `BUSY` or "no valid copy", not an
unbounded rescue scan.

### 8.4 Invalidate and rollback

- invalidate appends a tombstone record
- rollback creates a new current copy from the previous committed version
- the previous copy can stay available for recovery and comparison

## 9. Garbage collection

GC is lane-local and incremental.

Key rules:

- trigger early, not only at complete exhaustion
- move at most one bounded unit of work per tick
- copy live blocks based on RAM metadata
- commit lane switch explicitly
- erase the old sector later in background

Suggested states:

```text
GC_IDLE
GC_PREPARE_DST
GC_COPY_ONE
GC_SWITCH_ACTIVE
GC_ERASE_OLD
```

Compared with scan-heavy designs, this shortens GC tail latency because the work
is proportional to live blocks, not to all historical records in a sector.

## 10. Power-loss safety

The persistence model must not rely on transient RAM decisions.

Safety rules:

- new data is not visible before the commit marker is written
- old committed data remains readable until new data is committed
- interrupted GC is resolved using committed sector headers, record tails, and
  generations
- stale checkpoint is corrected by tail scan and sector-header arbitration

## 11. External API direction

The minimum public API should stay small:

```c
fee_init
fee_read
fee_write
fee_invalidate
fee_get_status
fee_rollback
fee_mainfunction
```

Internally, configuration should map immediate-style blocks to `FAST` lane
behavior instead of keeping separate ad hoc persistence logic.

## 12. Source layout and rollout

Recommended rollout:

1. Phase 1: boot, read, write, invalidate, checkpoint, basic recovery
2. Phase 2: rollback, bulk lane, stronger diagnostics
3. Phase 3: production hardening, endurance policy, richer tooling

## 13. Test focus

The redesign should be validated against:

- interrupted single-block writes
- interrupted GC lane switch
- stale or partially corrupt checkpoint copies
- fast-lane latency under background GC
- startup tail-scan limits
- rollback correctness
