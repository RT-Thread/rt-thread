# FEE Scheduler And GC

## 1. Purpose

This document defines request scheduling, `BUSY_INTERNAL` meaning, and
background garbage collection behavior.

The design aims to keep:

- low tail latency for fast-lane requests
- accepted API calls during internal background work
- deterministic priority for cache-hit reads

## 2. Scheduling principles

1. only one flash job may be in flight at a time
2. user-facing fast requests outrank background work
3. cache-hit reads outrank checkpoint and GC
4. checkpoint and GC run only when no higher-priority user work is pending
5. GC fairness across lanes is required

## 3. Request classes

| Class | Content | Priority note |
| --- | --- | --- |
| `READ_FAST_PATH` | cache-hit reads | outranks background work |
| `URGENT_QUEUE` | fast write, invalidate, rollback | immediate-style behavior |
| `NORMAL_QUEUE` | normal and bulk write-style work | regular user traffic |
| `BACKGROUND` | checkpoint, GC, deferred erase | idle-time work |

## 4. Meaning of `BUSY_INTERNAL`

`BUSY_INTERNAL` means the module is doing internal recovery, checkpoint, or GC
work. It does not mean all new API calls must be rejected.

Recommended acceptance:

| Request | Behavior while busy internal |
| --- | --- |
| `Read` | accepted; cache-hit reads keep priority |
| `FAST Write` | accepted into urgent queue |
| `NORMAL/BULK Write` | accepted into normal queue |
| `Invalidate` | accepted and queued |
| `Rollback` | accepted and serialized with same-block writes |

## 5. Main scheduling loop

Recommended dispatch order:

```c
fee_port_mainfunction();
if (flash_is_busy()) return;
if (read_fast_pending()) dispatch_read_fast();
else if (urgent_queue_not_empty()) dispatch_urgent_request();
else if (normal_queue_not_empty()) dispatch_normal_request();
else if (checkpoint_force_due()) dispatch_checkpoint();
else if (gc_force_pending()) dispatch_force_gc_lane();
else if (checkpoint_bg_due()) dispatch_checkpoint();
else if (gc_bg_pending()) dispatch_gc_round_robin();
```

## 6. Read path

### 6.1 Cache-hit read

When a block is present in RAM cache and recovery state allows reading:

1. resolve physical address immediately
2. dispatch the read as soon as the backend is free
3. keep it ahead of checkpoint and GC work

### 6.2 Cache miss

A cache miss should not trigger a rescue full-flash scan. Return a bounded
result instead:

- `BUSY` if recovery is not complete
- empty, invalid, or inconsistent if recovery is complete and no valid copy exists

## 7. GC policy

Each lane maintains local GC state such as:

- requested
- force-required
- in-progress state

Each scheduler tick may advance only one bounded GC step for one lane, for
example:

- copy one live block
- write one sector header
- poll one erase job

## 8. Lane priority

Suggested force-GC priority:

1. fast lane force
2. normal lane force
3. bulk lane force
4. round-robin among background requests

## 9. Fairness rules

- stop background work from jumping the queue if normal or bulk user requests
  exceed a wait threshold
- allow fast requests to preempt not-yet-started background work
- do not interrupt an already issued flash operation
- serialize write, invalidate, and rollback for the same block

## 10. GC state machine

Suggested states:

```text
GC_IDLE
GC_PREPARE_DST
GC_COPY_ONE
GC_SWITCH_COMMIT
GC_OLD_PENDING_ERASE
GC_FINISH
```

State intent:

- prepare destination sector
- copy one live block at a time
- switch active role explicitly
- erase old sector later in background

## 11. Checkpoint and GC interaction

- checkpoint should be requested soon after a lane role switch
- a lagging checkpoint must not block the new active sector from continuing
- if checkpoint falls behind too far, forced checkpoint policy must correct it

## 12. Suggested interfaces

```c
void fee_sched_mainfunction(void);
fee_ret_t fee_sched_submit_read(...);
fee_ret_t fee_sched_submit_write(...);
fee_ret_t fee_sched_submit_invalidate(...);
fee_ret_t fee_sched_submit_rollback(...);
rt_bool_t fee_sched_has_pending_work(void);
```

## 13. Test focus

- cache-hit reads still win when checkpoint is due
- fast write preempts normal-lane GC
- long normal backlog forces background work to yield
- force-GC priority versus requested-GC priority
- same-block write plus rollback serialization
