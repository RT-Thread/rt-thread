# custom_fee Public API Guide

## 1. Purpose

This guide is for engineers who use `custom_fee` from application or adapter
code. It focuses on public behavior rather than internal implementation detail.

Use this guide to answer:

- which interfaces are public
- which operations complete immediately and which are queued
- how to observe final completion
- how to integrate the component into a new project

For the on-flash view of records, sectors, and checkpoints, see
[fee_diag_test.md](./fee_diag_test.md).

## 2. Public surface

The stable user-facing header is [fee_api.h](../../fee_api.h).

The currently visible public calls are:

```c
fee_ret_t fee_init(void);
fee_ret_t fee_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
fee_ret_t fee_write(uint16_t block_id, const uint8_t *src, uint16_t len);
fee_ret_t fee_invalidate(uint16_t block_id);
fee_ret_t fee_get_status(uint16_t block_id, fee_block_status_t *status);
fee_ret_t fee_rollback(uint16_t block_id);
void fee_mainfunction(void);

fee_status_t fee_get_memif_status(void);
fee_job_result_t fee_get_job_result(void);
fee_init_state_t fee_get_init_state(void);
```

## 3. Functional characteristics

The current implementation is organized around these behaviors:

- RAM cache lookup after initialization
- synchronous read submission
- queued write, invalidate, and rollback operations
- current-copy plus previous-copy tracking
- checkpoint-based startup recovery
- lane-separated fast, normal, and bulk traffic
- background GC and checkpoint advancement in `fee_mainfunction()`
- CRC and commit-tail based record validation

## 4. Return and state types

### 4.1 `fee_ret_t`

| Value | Meaning |
| --- | --- |
| `FEE_E_OK` | call accepted or operation completed |
| `FEE_E_NOT_OK` | general failure |
| `FEE_E_BUSY` | request cannot proceed yet |
| `FEE_E_UNINIT` | module not initialized |
| `FEE_E_PARAM` | invalid parameter |

### 4.2 `fee_status_t`

| Value | Meaning |
| --- | --- |
| `FEE_STATUS_UNINIT` | module not ready |
| `FEE_STATUS_IDLE` | no pending foreground or background work |
| `FEE_STATUS_BUSY` | user work in progress |
| `FEE_STATUS_BUSY_INTERNAL` | background recovery, checkpoint, or GC is active |

### 4.3 `fee_job_result_t`

| Value | Meaning |
| --- | --- |
| `FEE_JOB_NONE` | no completed job yet |
| `FEE_JOB_OK` | latest job completed successfully |
| `FEE_JOB_PENDING` | latest job still in progress |
| `FEE_JOB_FAILED` | latest job failed |
| `FEE_JOB_CANCELED` | latest job canceled |
| `FEE_JOB_INCONSISTENT` | latest job saw inconsistent data |

### 4.4 `fee_block_status_t`

| Value | Meaning |
| --- | --- |
| `FEE_BLOCK_STATUS_EMPTY` | block has no committed copy |
| `FEE_BLOCK_STATUS_VALID` | current copy is valid |
| `FEE_BLOCK_STATUS_INVALIDATED` | block has been invalidated |
| `FEE_BLOCK_STATUS_INCONSISTENT` | no trustworthy block state |

## 5. API semantics

### 5.1 `fee_init()`

- resets runtime context
- initializes the flash port layer
- starts checkpoint restore and recovery
- returns when checkpoint-ready or full-ready recovery has been established

Use `fee_get_init_state()` to distinguish early readable state from full-ready
state.

### 5.2 `fee_read()`

`fee_read()` is the read entry point for a logical block slice.

Expected behavior:

- validates parameters
- rejects access before initialization
- depends on recovery state for early-boot availability
- reads the latest committed copy known by RAM cache

If a block is not yet readable during recovery, expect `FEE_E_BUSY`.

### 5.3 `fee_write()`

`fee_write()` accepts a write request for a block and queues it through the
scheduler. Treat success from the API as "accepted", not "fully persisted".

The final result is reported later through:

- `fee_get_memif_status()`
- `fee_get_job_result()`
- optionally a follow-up read or block-status query

### 5.4 `fee_invalidate()`

Invalidation is also queued work. The persistent effect is typically a tombstone
record appended to the owning lane.

### 5.5 `fee_rollback()`

Rollback requests the previous committed copy to become current again. It should
be treated like a queued write-style job, not as an immediate metadata flip.

### 5.6 `fee_get_status()`

This call reports block state, not module state. Use it to distinguish empty,
valid, or invalidated blocks after the module is readable.

### 5.7 `fee_mainfunction()`

`fee_mainfunction()` drives the whole asynchronous engine:

- flash-port polling
- remaining recovery steps
- request dispatch
- checkpoint flush
- GC steps
- top-level status updates

If the project does not call this function periodically, queued operations will
not complete.

## 6. Observing final completion

Recommended interpretation:

- `fee_init()` completion is refined by `fee_get_init_state()`
- `fee_read()` success means data has been returned
- `fee_write()` and related calls only confirm request acceptance
- `fee_get_job_result()` reports the latest job outcome at module level

This job result is not block-private. If the application needs strict
per-request tracking, it should serialize requests or add an upper-layer request
context.

## 7. Recommended calling patterns

### 7.1 Simple serialized pattern

This is the safest bring-up pattern:

1. call `fee_init()`
2. wait until `fee_get_init_state()` reaches a readable state
3. issue one write-style request
4. call `fee_mainfunction()` periodically until job result is no longer pending
5. issue the next request

### 7.2 Periodic-task pattern

In a scheduler-based system:

- call `fee_mainfunction()` from a cyclic task
- submit write/invalidate/rollback requests from application code
- poll `fee_get_job_result()` from a manager task or adapter

### 7.3 Early boot-critical reads

Some blocks may be marked boot-critical. Those blocks can become readable before
full recovery is finished if checkpoint restore succeeded.

## 8. Queue and concurrency rules

- reads should stay responsive during `BUSY_INTERNAL`
- fast-lane requests outrank background work
- write, invalidate, and rollback on the same block must serialize
- checkpoint and GC must not monopolize cache-hit reads

## 9. Minimal integration checklist

1. Enable the component in [Kconfig](../../Kconfig).
2. Include [fee_api.h](../../fee_api.h).
3. Provide or integrate the project-specific flash port/backend layer.
4. Define the block table in [fee_cfg.c](../../fee_cfg.c).
5. Call `fee_init()` during boot.
6. Call `fee_mainfunction()` periodically.

## 10. Common mistakes

### 10.1 Treating `fee_write()` success as persistence completion

It only means the request was accepted.

### 10.2 Forgetting to call `fee_mainfunction()`

Without the periodic driver, no queued work advances.

### 10.3 Confusing block status with module status

`fee_get_status()` answers "what is the state of this block", not "is the module
idle".

### 10.4 Assuming job result is tracked per block

The current API exposes a module-level latest job result, not a per-block job
history.

### 10.5 Bypassing the public API

Application code should not drive internal or port-layer helpers directly.

## 11. Minimal example

```c
#include "fee_api.h"

static void app_fee_boot(void)
{
    uint8_t data[32] = {0};

    if (fee_init() != FEE_E_OK)
    {
        return;
    }

    while (fee_get_init_state() != FEE_INIT_FULL_READY)
    {
        fee_mainfunction();
    }

    if (fee_write(1U, data, sizeof(data)) != FEE_E_OK)
    {
        return;
    }

    while (fee_get_job_result() == FEE_JOB_PENDING)
    {
        fee_mainfunction();
    }
}
```
