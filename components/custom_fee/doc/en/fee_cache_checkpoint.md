# FEE Cache And Checkpoint

## 1. Purpose

This document defines RAM cache structure, checkpoint content, update triggers,
and startup-tail bounds.

The design focus is:

- O(1)-style block lookup after initialization
- bounded startup work
- a clean split between runtime cache and persistent checkpoint image

## 2. RAM model

### 2.1 Block cache entry

Each block entry should track:

- lane ownership
- current address
- previous address
- sequence number
- data length
- current and previous validity
- current and previous sector identity

This matches the rollback-capable "current plus previous copy" model used by the
core implementation.

### 2.2 Lane context

Each lane needs:

- active sector
- destination sector
- spare sector
- GC cursor and state
- free offset
- GC thresholds
- dirty record and dirty byte counters

### 2.3 Super context

The global context should hold:

- lane contexts
- checkpoint generation
- checkpoint dirty flag
- initialization state
- module status and latest job result

## 3. Cache update rules

Recommended rules:

1. do not update cache before record commit completes
2. after a committed data write, shift current to previous and install new current
3. after a committed tombstone, mark current invalid
4. after a committed rollback, promote copied previous data to current

## 4. Checkpoint content

### 4.1 Required content

- checkpoint generation
- per-lane active, destination, and spare role
- per-lane free offset
- per-lane dirty counters
- per-block current address
- per-block previous address
- per-block sequence number

### 4.2 Optional content

- boot-critical bitmap
- statistics snapshot
- creation timestamp

## 5. When to flush checkpoint

### 5.1 Background triggers

Request a background checkpoint when:

- a lane completes a GC switch
- dirty-record count reaches a background threshold
- dirty-byte count reaches a background threshold
- a boot-critical block changes

### 5.2 Forced triggers

Force checkpoint when:

- dirty-record count reaches force threshold
- dirty-byte count reaches force threshold
- uncheckpointed record budget is about to be exceeded
- uncheckpointed byte budget is about to be exceeded

## 6. Tail-scan bound

Checkpoint is not only a performance optimization. It is also a startup-time
budgeting mechanism.

Per lane, maintain explicit limits for:

- maximum uncheckpointed records
- maximum uncheckpointed bytes
- maximum tail-scan pages

That enables a bounded boot statement such as:

```text
T_boot_tail_scan <= sum(lane_scan_time(max_tail_scan_pages_per_lane))
```

## 7. Checkpoint write flow

### 7.1 Chunking

Large block maps may be split into multiple checkpoint chunks.

### 7.2 Commit procedure

1. write checkpoint metadata
2. write chunk payload
3. commit each chunk
4. make the new checkpoint live when the final chunk is committed

### 7.3 Effect after commit

- the old checkpoint stays available until a later successful rotation
- in-RAM checkpoint generation increments
- dirty counters can be cleared

## 8. Suggested module split

- `fee_cache.c`: lookup, update, relocation, conflict resolution
- `fee_ckpt.c`: serialize, flush, restore checkpoint image

Example helper surface:

```c
uint16_t fee_cache_export_ckpt(...);
void fee_cache_import_ckpt(...);
fee_ret_t fee_ckpt_restore(void);
fee_ret_t fee_ckpt_flush(void);
```

## 9. Test focus

- correct current/previous rotation after repeated writes
- correct current/previous relation after rollback
- interrupted checkpoint-chunk write
- forced checkpoint when dirty-byte limit is reached
- startup tail scan staying inside configured page budget
