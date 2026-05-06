# custom_fee

`custom_fee` is a fixed-block Flash EEPROM Emulation (FEE) component for embedded
systems. It targets deterministic block storage rather than a general-purpose KV
database, with append-only writes, checkpoint-assisted boot recovery, and
background garbage collection.

## Implemented scope

The current source tree already contains the main control flow and data-model
building blocks for the component:

- Public API entry points in [fee_api.h](./fee_api.h)
  and [fee_api.c](./fee_api.c)
- Request submission and foreground/background arbitration in
  [fee_sched.c](./fee_sched.c)
- Core read, write, invalidate, rollback, and record validation logic in
  [fee_core.c](./fee_core.c)
- RAM cache maintenance and checkpoint import/export in
  [fee_cache.c](./fee_cache.c) and
  [fee_ckpt.c](./fee_ckpt.c)
- Boot recovery, checkpoint restore, tail scan, and interrupted-GC handling in
  [fee_recovery.c](./fee_recovery.c)
- Incremental garbage collection state handling in
  [fee_gc.c](./fee_gc.c)
- On-flash header, tail, and record helpers in
  [fee_onflash.h](./fee_onflash.h) and
  [fee_onflash.c](./fee_onflash.c)
- Static block and lane configuration in
  [fee_cfg.h](./fee_cfg.h) and
  [fee_cfg.c](./fee_cfg.c)

## Functional characteristics

At the component level, the current implementation is designed around these
behaviors:

- Block-oriented access by `block_id`
- Synchronous reads plus queued writes, invalidates, and rollbacks
- Current-copy and previous-copy tracking for rollback and tolerant recovery
- RAM cache lookup after initialization instead of full media scans on every read
- Checkpoint-based startup acceleration with staged initialization states
- Lane-based isolation for fast, normal, and bulk traffic
- Background GC and checkpoint work driven by `fee_mainfunction()`
- Record-level commit markers and CRC validation for power-loss recovery

## Public API

The user-facing API currently exposed by
[fee_api.h](./fee_api.h) is:

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

## Directory layout

- [doc/README.md](./doc/README.md): documentation index
- [doc/en/README.md](./doc/en/README.md): English documents
- [doc/zh/README.md](./doc/zh/README.md): Chinese documents
- Source files in the repository root: API, scheduler, GC, recovery, cache,
  checkpoint, on-flash format, and configuration modules
- [Kconfig](./Kconfig) and
  [SConscript](./SConscript): integration hooks

## Documentation sets

Two separated documentation sets are now provided:

- English: [doc/en/README.md](./doc/en/README.md)
- Chinese: [doc/zh/README.md](./doc/zh/README.md)

Recommended entry points:

- Architecture and redesign baseline:
  [doc/en/fee_redesign.md](./doc/en/fee_redesign.md)
- Public API and usage:
  [doc/en/fee_API.md](./doc/en/fee_API.md)
- Diagnostic test interpretation:
  [doc/en/fee_diag_test.md](./doc/en/fee_diag_test.md)

## Current repository status

This repository snapshot is still an integration-oriented implementation set,
not a production-complete drop-in release.

- The core module logic and design documents are present.
- The documentation references a `fee_port` adapter layer and test backends as
  part of the intended integration model.
- The corresponding adapter and test source files are not included in this
  snapshot, so bring-up still requires project-side integration work.

## Quick integration notes

1. Configure the component in [Kconfig](./Kconfig).
2. Define the block table and flash capabilities required by the target.
3. Call `fee_init()` during boot.
4. Drive `fee_mainfunction()` periodically.
5. Treat `fee_write()`, `fee_invalidate()`, and `fee_rollback()` as queued jobs
   and observe completion through status/job-result APIs.

