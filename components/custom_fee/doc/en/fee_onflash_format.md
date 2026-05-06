# FEE On-Flash Format

## 1. Purpose

This document defines the persistent layout used by `custom_fee`:

- lane and sector organization
- sector header format
- record header format
- commit-tail format
- checkpoint chunk format
- acceptance rules during recovery

This format is the contract between core FEE logic and the flash backend.

## 2. Design principles

1. All persistent structures must respect the backend programming unit.
2. User-visible consistency depends on persistent commit markers, not on RAM.
3. The final commit marker is the single visibility point for new data.
4. Old data remains readable until the new copy is committed.
5. Except for meta structures, record payload is append-only.

## 3. Common rules

### 3.1 Alignment

- address unit: byte
- minimum alignment: `max(8, program_unit)`
- fast-lane records should prefer wordline-friendly alignment
- normal and bulk records must be aligned to the chosen record alignment

Useful definition:

```text
record_span = align_up(header_len + payload_len + tail_len, record_align)
```

### 3.2 Lane identifiers

| Lane | Value | Purpose |
| --- | --- | --- |
| `META` | `0x01` | checkpoint and super-state |
| `FAST` | `0x02` | latency-sensitive blocks |
| `NORMAL` | `0x03` | standard blocks |
| `BULK` | `0x04` | large or infrequent large blocks |

### 3.3 Sector states

| State | Value | Meaning |
| --- | --- | --- |
| `ERASED` | `0xFF` | blank sector |
| `PREPARE` | `0x11` | header written, not active yet |
| `ACTIVE` | `0x22` | append target |
| `GC_DST` | `0x33` | GC destination |
| `OLD_PENDING_ERASE` | `0x44` | replaced, waiting for erase |
| `BAD` | `0x55` | invalid or damaged |

Legal direction is one-way: prepare to active or GC destination, then old, then
erased.

## 4. Sector header

Recommended fixed size: `64 B`.

Core fields:

- `magic`
- `format_version`
- `lane_id`
- `state`
- `generation`
- `erase_count`
- `data_start`
- `data_end`
- `hdr_seq`
- `hdr_crc`
- `commit_marker`

A sector header is valid only when magic, version, CRC, commit marker, and
state/lane combination all pass validation.

## 5. Record header

Recommended fixed size: `32 B`.

Core fields:

- `magic`
- `block_id`
- `record_type`
- `flags`
- `data_len`
- `header_len`
- `seq`
- `generation`
- `prev_addr_hint`
- `hdr_crc`

### 5.1 Record types

| Type | Value | Meaning |
| --- | --- | --- |
| `DATA` | `0xD1` | normal payload |
| `TOMBSTONE` | `0xD2` | invalidation record |
| `CKPT_CHUNK` | `0xC1` | checkpoint fragment |

### 5.2 Flags

- `PREPARE`: write started
- `COPIED`: created by GC move
- `ROLLBACK`: created by explicit rollback

## 6. Commit tail

Recommended fixed size: `16 B`.

Core fields:

- `data_crc`
- `tail_crc`
- `tail_flags`
- `commit_marker`

Required write order:

1. record header
2. payload
3. first 12 bytes of commit tail
4. final commit marker

During recovery, a record is accepted only if header, payload readability, tail
CRC, and final commit marker are all valid.

## 7. Special records

### 7.1 Tombstone

Rules:

- `record_type = TOMBSTONE`
- `data_len = 0`
- no payload
- `seq = old_seq + 1`

### 7.2 Checkpoint chunk

Checkpoint data lives only in the `META` lane and is stored as:

```text
RecordHeader(type = CKPT_CHUNK)
CheckpointChunkPayload
CommitTail
```

The payload should include:

- `ckpt_generation`
- `chunk_index`
- `chunk_count`
- `chunk_bytes`
- `payload_crc`
- serialized chunk data

A full checkpoint is considered complete only when the last chunk is committed.

## 8. Versioning strategy

- major version change means incompatible format
- minor version change means compatible extension
- incompatible records must not be mixed inside a lane

Suggested encoding:

```text
format_version = (major << 8) | minor
```

## 9. Implementation split

- `fee_onflash.h`: constants, structures, and API declarations
- `fee_onflash.c`: encode/decode and validation helpers
- `fee_recovery.c`: walking flash and applying validation
- `fee_ckpt.c`: checkpoint serialization

Example helper surface:

```c
uint32 fee_onflash_calc_record_span(const fee_block_cfg_t *cfg, uint16 data_len);
boolean fee_onflash_validate_sector_header(const uint8 *buf);
boolean fee_onflash_is_record_committed(const uint8 *buf);
```

## 10. Test focus

- valid header but missing commit marker
- valid record header with incomplete tail
- tombstone ordering versus data record ordering
- missing last checkpoint chunk
- format-version rejection and compatibility behavior
