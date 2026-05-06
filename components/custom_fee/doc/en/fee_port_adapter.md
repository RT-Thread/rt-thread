# FEE Port Adapter

## 1. Purpose

This document defines the adapter boundary between `custom_fee` and a concrete
flash backend.

Goals:

- keep FEE core independent from backend-specific details
- support both real flash and RAM-backed mock backends
- freeze a minimal set of read, write, erase, and status interfaces

## 2. Design principles

1. FEE must not assume arbitrary backend write granularity.
2. Header, payload, and tail slicing must follow reported capabilities.
3. The port layer translates backend semantics into FEE-consumable behavior.
4. Only one backend flash job may be active at a time.

## 3. Capability reporting

Recommended capability structure:

```c
typedef struct
{
    uint16 read_unit;
    uint16 program_unit;
    uint32 erase_unit;
    uint16 preferred_chunk;
    uint8 supports_suspend;
    uint8 supports_compare;
} fee_flash_caps_t;
```

Key meanings:

- minimum read unit
- minimum program unit
- erase granularity
- preferred transfer chunk
- optional suspend support
- optional compare support

## 4. Required interface

```c
fee_ret_t fee_port_init(void);
fee_ret_t fee_port_get_caps(fee_flash_caps_t *caps);
fee_ret_t fee_port_read(uint32_t addr, uint8_t *dst, uint32_t len);
fee_ret_t fee_port_write(uint32_t addr, const uint8_t *src, uint32_t len);
fee_ret_t fee_port_erase(uint32_t addr, uint32_t len);
fee_ret_t fee_port_get_status(void);
fee_ret_t fee_port_get_job_result(void);
```

Optional helpers:

```c
void fee_port_mainfunction(void);
fee_ret_t fee_port_cancel(void);
fee_ret_t fee_port_compare(uint32_t addr, const uint8_t *src, uint32_t len);
```

## 5. Semantic rules

### 5.1 Parameter rules

- addresses must satisfy backend alignment
- lengths must be compatible with the operation granularity
- invalid parameters should be rejected explicitly, not silently fixed

### 5.2 Job model

The preferred abstraction is an asynchronous job model:

- write and erase start a job
- status and result are polled later
- `fee_mainfunction()` drives polling through the port layer

If the concrete driver is synchronous, the port layer should still emulate a
consistent job-state view for the FEE core.

### 5.3 Error model

Differentiate at least:

- parameter error
- driver busy
- media failure
- compare or ECC failure
- uninitialized backend

## 6. Alignment and chunking

General rules:

```text
header_len % program_unit == 0
tail_len % program_unit == 0
payload_chunk % preferred_chunk == 0 or payload_chunk % program_unit == 0
erase_len % erase_unit == 0
```

Lane-specific bias:

- fast lane prefers fewer jobs
- normal lane balances throughput and recoverability
- bulk lane prefers large contiguous chunks

## 7. Backend mapping

The intended port implementation may wrap a real MCU flash driver or a RAM mock.
The adapter should centralize:

- address translation
- return-code translation
- alignment checks
- optional statistics collection

## 8. RAM mock backend

Before real hardware integration, a RAM-backed backend is useful for:

- on-flash format validation
- checkpoint and recovery logic
- scheduler and GC state transitions

The mock backend should still obey realistic granularity and single-job
constraints. A permissive mock hides bugs.

## 9. Test focus

- reject misaligned writes
- queue correctly when backend is busy
- expose job result transitions clearly
- keep upper-layer behavior independent from backend type
