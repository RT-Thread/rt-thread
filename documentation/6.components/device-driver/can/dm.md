@page page_device_can_dm CAN FD DLC helpers (`can_dm`)

# `can_dm` utilities

Header: **`components/drivers/can/can_dm.h`** (also installable as `drivers/can_dm.h` via include path). Implementation: **`components/drivers/can/can_dm.c`** — **only** ISO 11898 DLC/length conversion; **no** device register, OFW, or ISR code.

The CAN **device framework** is **`dev_can.c`** — see @ref page_device_can.

## APIs

```c
rt_uint8_t can_dlc2len(rt_uint8_t can_dlc);
rt_uint8_t can_len2dlc(rt_uint8_t len);
```

### `can_dlc2len`

Maps **CAN FD DLC nibble** (0–15) to **payload byte length**:

| DLC | 0–8 | 9–12 | 13–16 | 17–20 | 21–24 | 25–32 | 33–48 | 49–64 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Bytes | 0–8 | 12 | 16 | 20 | 24 | 32 | 48 | 64 |

Only low **4 bits** of `can_dlc` are used (`can_dlc & 0x0F`).

### `can_len2dlc`

Inverse mapping for lengths **0–64**; returns **`0xf`** if **`len > 64`**.

## Usage in controllers

FD-capable drivers should:

1. Store/transmit hardware DLC using **`can_len2dlc(actual_payload_len)`**.
2. On RX, convert to byte count with **`can_dlc2len(rx_frame.dlc)`** before copying to upper layers.

Classic CAN (≤ 8 bytes) uses DLC 0–8 with identity mapping in both tables.

## CAN ID flags (header only)

`can_dm.h` also defines Linux-style ID flags for drivers that pack ID + type into one word:

| Macro | Value | Meaning |
| --- | --- | --- |
| **`CAN_EFF_FLAG`** | `0x80000000` | Extended frame |
| **`CAN_RTR_FLAG`** | `0x40000000` | Remote frame |
| **`CAN_ERR_FLAG`** | `0x20000000` | Error frame |
| **`CAN_SFF_MASK`** / **`CAN_EFF_MASK`** | — | ID field masks |

These are **not** used by `dev_can.c` (`rt_can_msg` uses separate `ide`/`rtr` bits).

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| Not a DM bus | No `RT_CAN_OFW_DECLARE` in core — platform drivers (e.g. Rockchip `canfd-rockchip.c`) own OFW probe |
| FD vs classic | Do not use DLC > 8 on classic-only controllers |
| Include | `#include "can_dm.h"` or path from driver directory |
| **`can_get_dlc` / `canfd_get_dlc`** | Clamp DLC before `can_dlc2len` |

## See also

- @ref page_device_can
- `components/drivers/can/can_dm.c`
- `components/drivers/can/dev_can.c`
