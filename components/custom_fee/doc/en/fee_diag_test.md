# custom_fee Diagnostic Test Guide

## 1. Purpose

`custom_fee_diag_test` is intended for bring-up and inspection in a controlled
environment such as QEMU plus a RAM-backed flash backend.

The diagnostic flow should help verify:

- block write and readback behavior
- invalidate and rollback semantics
- recovery after re-initialization
- GC trigger behavior
- actual sector, record, and checkpoint layout in the mock flash image

Unlike a simple pass/fail unit test, the diagnostic test should expose timing,
backend access counts, and raw layout interpretation.

## 2. Example execution pattern

In the original RT-Thread bring-up environment, the test is expected to run from
a board-specific shell or automation script. The exact commands depend on the
project integration, but the sequence is usually:

1. build the target
2. boot the test image
3. run the basic `custom_fee_test`
4. run `custom_fee_diag_test`

If the project uses QEMU, keep the flash backend configuration identical to the
expected mock-flash geometry when collecting results.

## 3. Suggested scenario coverage

A practical diagnostic flow should cover:

1. erase or reset the backend and initialize the module
2. write a fast-lane block
3. read it back
4. overwrite it and confirm newest-copy visibility
5. rollback it and confirm previous-copy visibility
6. write a normal block
7. reinitialize and confirm recovery
8. write enough data to trigger fast-lane GC
9. invalidate a block and confirm the invalid result
10. dump the final flash layout

## 4. Useful output fields

Useful per-step metrics include:

- elapsed time
- scheduler ticks or wait loops
- number of backend reads, writes, erases, and polls
- byte counts for each backend operation type

Example interpretation:

- many polls with few writes usually indicates long async completion
- unexpectedly large read counts often indicate poor cache use or recovery drift
- frequent erases during a short scenario may indicate overly aggressive GC

## 5. What the flash dump should show

The dump should let you recognize:

- checkpoint records in the meta lane
- sector headers for active and old sectors
- block records in fast and normal lanes
- tombstones after invalidation
- copied records after GC or rollback

At a high level, a final mock layout should look like:

```text
META lane
  checkpoint records

FAST lane
  sector header
  data records
  possible GC-copied records

NORMAL lane
  sector header
  regular block records
```

## 6. Important structures to decode

### 6.1 Sector header

Confirm:

- magic
- lane id
- sector state
- generation
- commit marker

### 6.2 Record header

Confirm:

- block id
- record type
- flags
- data length
- sequence
- header CRC

### 6.3 Commit tail

Confirm:

- data CRC
- tail CRC
- final commit marker

## 7. Reading diagnostic results

Practical interpretation rules:

- if the latest record is committed and CRC-valid, it should be current
- if rollback was executed, a newer rollback-tagged record should point back to
  the previous logical content
- if a record lacks a final commit marker, recovery must ignore it
- if GC completed correctly, live blocks should appear in the new active sector

## 8. Performance sanity checks

Typical questions to ask:

- do cache-hit reads remain cheap after repeated writes
- does GC advance incrementally rather than in long monopolizing bursts
- does recovery after restart scan only the expected tail region
- do write counts roughly match the expected header, payload, and tail pattern

## 9. Recommended conclusions section

Each test run should end with a short summary:

- whether write, read, rollback, invalidate, and recovery all matched expectation
- whether GC was triggered and completed
- whether the dumped on-flash layout matched the format spec
- whether timing and backend access counts stayed inside the expected budget
