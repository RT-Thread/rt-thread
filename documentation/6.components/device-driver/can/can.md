@page page_device_can CAN device

# CAN bus device framework

RT-Thread exposes CAN controllers as **`RT_Device_Class_CAN`** devices. The framework in **`components/drivers/can/dev_can.c`** provides interrupt-driven RX/TX FIFOs, optional **hardware filters**, **CAN-FD** message layout, **blocking** and **non-blocking** send paths, and periodic **bus status** polling. Board and SoC drivers implement **`struct rt_can_ops`** and register with **`rt_hw_can_register()`**.

**`can_dm.c`** is **not** the bus core — it only supplies ISO 11898 DLC/length helpers (`can_dlc2len`, `can_len2dlc`). See @ref page_device_can_dm.

Header: `components/drivers/include/drivers/dev_can.h`. Core: `components/drivers/can/dev_can.c`.

## Architecture

```
  Application / FinSH
        │ rt_device_find / open / read / write / control
        ▼
  struct rt_can_device  (dev_can.c)
        │ software RX FIFO, TX mailboxes, nb_tx ringbuffer
        │ rt_hw_can_isr()  ← BSP ISR
        ▼
  struct rt_can_ops
        │ configure / control / sendmsg / recvmsg / sendmsg_nonblocking
        ▼
  SoC CAN / CAN-FD controller (BSP or bsp/*/dm/can/)
```

| Component | File | Role |
| --- | --- | --- |
| **Framework** | `dev_can.c` | Device ops, FIFOs, ISR demux, `rt_hw_can_register` |
| **FD DLC helpers** | `can_dm.c`, `can_dm.h` | DLC ↔ byte length (FD payloads) |
| **DM SoC example** | `bsp/rockchip/dm/can/canfd-rockchip.c` | OFW platform driver + `rt_hw_can_register` |
| **Legacy BSP** | e.g. `bsp/stm32/.../drv_can.c`, `drv_fdcan.c` | HAL-based `rt_can_ops` |

With **`RT_USING_DM`**, SoC-specific CAN drivers may live under **`SOC_DM_CAN_DIR`** (see `can/Kconfig`).

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_CAN`** | Build `components/drivers/can/` |
| **`RT_CAN_USING_HDR`** | Per-filter RX lists and filter callbacks (`rt_can_hdr`) |
| **`RT_CAN_USING_CANFD`** | 64-byte payload, `fd_frame` / `brs`, bit-timing fields in `can_configure` |
| **`RT_CANMSG_BOX_SZ`** | Software RX buffer depth (messages) |
| **`RT_CANSND_BOX_NUM`** | Concurrent blocking TX slots (match HW mailboxes) |
| **`RT_CANSND_MSG_TIMEOUT`** | Blocking send completion timeout (ticks) |
| **`RT_CAN_NB_TX_FIFO_SIZE`** | Non-blocking TX ring buffer (bytes); size ≥ N × `sizeof(struct rt_can_msg)` |
| **`RT_CAN_MALLOC_NB_TX_BUFFER`** | Allocate NB ring at `open` instead of static pool in `rt_can_device` |

Optional (not in core Kconfig): **`RT_CAN_USING_BUS_HOOK`** — periodic `bus_hook` from status timer.

---

# Access CAN devices (applications)

## Find and open

```c
#define CAN_DEV_NAME "can1"

rt_device_t candev = rt_device_find(CAN_DEV_NAME);
rt_device_open(candev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
```

| Open flag | Effect |
| --- | --- |
| **`RT_DEVICE_FLAG_INT_RX`** | Allocates software RX FIFO; driver enables RX IRQ via `control(SET_INT, INT_RX)` |
| **`RT_DEVICE_FLAG_INT_TX`** | Allocates TX mailbox pool + semaphore; enables TX IRQ |
| **`RT_DEVICE_FLAG_RDWR`** | Set at register time (`rt_hw_can_register`) |

**`read`** only works with **`INT_RX`** and `ref_count > 0`. **`write`** requires the device to be opened; size must be a multiple of **`sizeof(struct rt_can_msg)`**.

Register **`rt_device_set_rx_indicate()`** to wake a thread when frames arrive (see example in `dev_can.h` Doxygen block).

## Receive

```c
struct rt_can_msg rx_msg;
rx_msg.hdr_index = -1;   /* -1: any frame; >=0: specific filter bank (RT_CAN_USING_HDR) */

rt_ssize_t n = rt_device_read(candev, 0, &rx_msg, sizeof(rx_msg));
```

Batch read: pass an array of `rt_can_msg` and divide returned bytes by `sizeof(struct rt_can_msg)`.

## Send — blocking vs non-blocking

| Mode | How | Behavior |
| --- | --- | --- |
| **Blocking** | Default (`nonblocking == 0`), thread context, `INT_TX` open | Waits for HW mailbox + `RT_CAN_EVENT_TX_DONE` / `FAIL` |
| **Non-blocking** | `msg.nonblocking = 1`, or call from ISR | Uses `sendmsg_nonblocking`; overflow → `nb_tx_rb` ring |
| **Private mailbox** | `RT_CAN_CMD_SET_PRIV` + `msg.priv` = mailbox index | `_can_int_tx_priv` — fixed TX slot per message |

```c
struct rt_can_msg tx = {0};
tx.id = 0x123;
tx.ide = RT_CAN_STDID;
tx.rtr = RT_CAN_DTR;
tx.len = 8;
tx.data[0] = 0x11;
rt_device_write(candev, 0, &tx, sizeof(tx));   /* blocking */

tx.nonblocking = 1;
rt_device_write(candev, 0, &tx, sizeof(tx));   /* accept or enqueue */
```

**`RT_CANSND_MSG_TIMEOUT`** applies to blocking waits. Non-blocking path needs **`ops->sendmsg_nonblocking`** implemented in the low-level driver.

## Control commands (`rt_device_control`)

| Command | Value | Argument | Role |
| --- | --- | --- | --- |
| **`RT_DEVICE_CTRL_CONFIG`** | — | `struct can_configure *` | Re-`configure` (baud, mode, box sizes) |
| **`RT_CAN_CMD_SET_BAUD`** | `0x14` | baud (driver-defined) | Set arbitration bitrate |
| **`RT_CAN_CMD_SET_BAUD_FD`** | `0x1B` | baud | CAN-FD data phase bitrate |
| **`RT_CAN_CMD_SET_BITTIMING`** | `0x1C` | `struct rt_can_bit_timing_config *` | Custom prescaler/segments |
| **`RT_CAN_CMD_SET_MODE`** | `0x15` | mode | `RT_CAN_MODE_NORMAL` / `LISTEN` / `LOOPBACK` / `LOOPBACKANLISTEN` |
| **`RT_CAN_CMD_SET_PRIV`** | `0x16` | `RT_CAN_MODE_PRIV` / `NOPRIV` | Private TX mailbox mode |
| **`RT_CAN_CMD_SET_FILTER`** | `0x13` | `struct rt_can_filter_config *` | HW filters (needs **`RT_CAN_USING_HDR`**) |
| **`RT_CAN_CMD_SET_CANFD`** | `0x1A` | enable flag | Enable FD in driver |
| **`RT_CAN_CMD_START`** | `0x1D` | non-zero / zero | Start or stop controller |
| **`RT_CAN_CMD_GET_STATUS`** | `0x17` | `struct rt_can_status *` | Error counters, pkg stats |
| **`RT_CAN_CMD_SET_STATUS_IND`** | `0x18` | `rt_can_status_ind_type_t` | User callback on timer tick |
| **`RT_CAN_CMD_SET_BUS_HOOK`** | `0x19` | `rt_can_bus_hook` | Periodic hook (if enabled) |
| **`RT_DEVICE_CTRL_SET_INT` / `CLR_INT`** | — | `RT_DEVICE_FLAG_INT_RX/TX`, `RT_DEVICE_CAN_INT_ERR` | IRQ mask (used internally on open/close) |

Typical bring-up sequence:

1. `rt_device_open(..., INT_TX | INT_RX)`
2. `RT_CAN_CMD_SET_BAUD` / `SET_BITTIMING` / `SET_CANFD` as needed
3. `RT_CAN_CMD_SET_FILTER` (optional)
4. `RT_CAN_CMD_SET_MODE`
5. `RT_CAN_CMD_START` with non-zero argument

On **`close`**, the framework calls **`RT_CAN_CMD_START`** with **`RT_FALSE`** to stop the controller.

### Baud presets (`enum CANBAUD`)

`CAN1MBaud`, `CAN800kBaud`, `CAN500kBaud`, `CAN250kBaud`, `CAN125kBaud`, `CAN100kBaud`, `CAN50kBaud`, `CAN20kBaud`, `CAN10kBaud` — used in **`can_configure.baud_rate`**.

### Default configuration macro

```c
struct can_configure cfg = CANDEFAULTCONFIG;
cfg.baud_rate = CAN500kBaud;
cfg.msgboxsz = RT_CANMSG_BOX_SZ;
cfg.sndboxnumber = RT_CANSND_BOX_NUM;
```

---

## Message layout (`struct rt_can_msg`)

| Field | Meaning |
| --- | --- |
| **`id`** (29 bits) | CAN ID |
| **`ide`** | `RT_CAN_STDID` (0) or `RT_CAN_EXTID` (1) |
| **`rtr`** | `RT_CAN_DTR` (data) or `RT_CAN_RTR` (remote) |
| **`len`** | DLC or payload length (driver may expect bytes or DLC; FD drivers often use `can_len2dlc`) |
| **`priv`** | TX mailbox index in private mode |
| **`hdr_index`** | RX: matched filter bank; set **-1** before read for any frame |
| **`nonblocking`** | 1 → non-blocking send path |
| **`fd_frame` / `brs`** | CAN-FD (`RT_CAN_USING_CANFD`) |
| **`data[]`** | 8 bytes (classic) or 64 bytes (FD) |

---

## Hardware filters (`RT_CAN_USING_HDR`)

```c
struct rt_can_filter_item items[] = {
    RT_CAN_FILTER_STD_INIT(0x100, RT_NULL, RT_NULL),
    {0x555, 0, 0, 0, 0x7FF, 7},  /* fixed bank #7 */
};
struct rt_can_filter_config cfg = {
    .count = sizeof(items)/sizeof(items[0]),
    .actived = 1,
    .items = items,
};
rt_device_control(candev, RT_CAN_CMD_SET_FILTER, &cfg);
```

| Filter field | Role |
| --- | --- |
| **`mode`** | `RT_CAN_MODE_MASK` (0) or `RT_CAN_MODE_LIST` (1) |
| **`mask`** | Mask mode: 1 = bit must match |
| **`hdr_bank`** | -1 = driver assigns; ≥0 = fixed bank |
| **`rxfifo`** | `CAN_RX_FIFO0` or `CAN_RX_FIFO1` |
| **`ind` / `args`** | Optional per-filter RX callback |

Framework mirrors filters into **`can->hdr[]`** and routes RX frames to per-bank lists when **`hdr_index`** matches.

Helper macros: **`RT_CAN_FILTER_ITEM_INIT`**, **`RT_CAN_FILTER_EXT_INIT`**, **`RT_CAN_STD_RMT_FILTER_INIT`**, etc. (`dev_can.h`).

---

## CAN-FD

Enable **`RT_CAN_USING_CANFD`** in Kconfig and in driver:

- **`can_configure.enable_canfd`**, **`baud_rate_fd`**
- **`use_bit_timing`** + **`can_timing`** / **`canfd_timing`** (`struct rt_can_bit_timing`)
- **`RT_CAN_CMD_SET_CANFD`**, **`RT_CAN_CMD_SET_BAUD_FD`**, **`RT_CAN_CMD_SET_BITTIMING`**

Set **`rt_can_msg.fd_frame`** and **`brs`** on TX; on RX use **`can_dlc2len()`** if HW returns DLC nibble (@ref page_device_can_dm).

---

## Status and errors

**`struct rt_can_status`** — REC/TEC, **`errcode`** (`RT_CAN_BUS_*`), packet/drop counters, error type histogram.

Periodic timer (**`can_configure.ticks`**, default from driver) calls **`RT_CAN_CMD_GET_STATUS`** and optional **`status_indicate`** callback.

**`enum RT_CAN_STATUS_MODE`**: `NORMAL`, `ERRWARNING`, `ERRPASSIVE`, `BUSOFF` (derived from **`errcode`** in FinSH **`canstat`**).

FinSH (when **`RT_USING_FINSH`**): **`canstat can1`** — exported from `dev_can.c`.

---

## Driver author guide

### `struct rt_can_ops`

| Op | Required | Role |
| --- | --- | --- |
| **`configure`** | Yes | Apply `struct can_configure` (baud, mode, FD) |
| **`control`** | Yes | IOCTL commands above, `SET_INT`/`CLR_INT` |
| **`sendmsg`** | For blocking TX | `boxno` = mailbox index |
| **`recvmsg`** | For IRQ RX | `fifo` = HW RX FIFO index; fill `rt_can_msg` |
| **`sendmsg_nonblocking`** | For NB TX / ISR | Return **`RT_EOK`** or **`-RT_EBUSY`** |

### Register

```c
struct rt_can_device my_can;
struct can_configure cfg = CANDEFAULTCONFIG;
/* fill cfg, set my_can.config */
my_can.config = cfg;

rt_err_t rt_hw_can_register(struct rt_can_device *can,
                            const char *name,
                            const struct rt_can_ops *ops,
                            void *user_data);
```

Device name is typically **`can0`**, **`can1`**, … Auto-naming: **`rt_dm_dev_set_name_auto(&can->parent, "can")`** in DM drivers (Rockchip).

### ISR contract — `rt_hw_can_isr()`

BSP ISR calls **`rt_hw_can_isr(can, event)`**:

| `event & 0xff` | Meaning |
| --- | --- |
| **`RT_CAN_EVENT_RX_IND`** (0x01) | Frame received; **`event >> 8`** = RX FIFO index |
| **`RT_CAN_EVENT_RXOF_IND`** (0x06) | RX overflow (still tries one recv) |
| **`RT_CAN_EVENT_TX_DONE`** (0x02) | Mailbox **`event >> 8`** completed OK |
| **`RT_CAN_EVENT_TX_FAIL`** (0x03) | Mailbox transmission failed |

After **`TX_DONE`**, framework drains **`nb_tx_rb`** via **`sendmsg_nonblocking`**.

**`recvmsg`** must return byte count or **-1** if no frame. Populate **`hdr_index`** when hardware reports filter match.

### DM platform driver pattern (Rockchip)

1. **`RT_PLATFORM_DRIVER_EXPORT`** with **`rt_ofw_node_id`** (`compatible`)
2. **`probe`**: map reg/IRQ, **`rt_clk_get`**, **`rt_reset_control_get`**, deassert reset
3. Fill **`can_configure`** (bit timing from DT or constants)
4. **`rt_hw_interrupt_install`**, **`rt_hw_can_register`**
5. **`remove`**: mask IRQ, **`rt_device_unregister`**

Reference: `bsp/rockchip/dm/can/canfd-rockchip.c` — uses **`can_dm.h`** for FD DLC encoding.

### BSP drivers using this framework (examples)

| BSP / path | Notes |
| --- | --- |
| STM32 `drv_can.c` / `drv_fdcan.c` | Classic + FDCAN |
| NXP i.MX / MCX `drv_can.c` | FlexCAN |
| WCH, Renesas, Phytium, Synwit, Nuvoton | Various `rt_hw_can_register` |
| Rockchip `canfd-rockchip.c` | DM + OFW |

---

## Engineer checklist

1. **Probe**: reset → clock → pinmux → transceiver enable/regulator → init HW → **`rt_hw_can_register`**
2. **ISR**: keep minimal — **`recvmsg`** + **`rt_hw_can_isr`**; no blocking in ISR
3. **Filters / baud**: configure before **`RT_CAN_CMD_START`**
4. **Mailbox count**: set **`sndboxnumber`** to match hardware TX buffers
5. **FD**: increase **`RT_CAN_NB_TX_FIFO_SIZE`** — `sizeof(struct rt_can_msg)` is much larger with 64-byte payload
6. **Termination & transceiver STB**: board-level; not handled by framework

## Pitfalls

- **Open without `INT_RX`/`INT_TX`** — `read`/`write` return **`-RT_ENOSYS`**
- **Non-blocking without `sendmsg_nonblocking`** — `write` with `nonblocking=1` fails
- **RX FIFO full** — oldest frame dropped (`dropedrcvpkg`); increase **`msgboxsz`** or read faster
- **Bus-off** — check **`RT_CAN_CMD_GET_STATUS`**; recovery is driver/BSP specific
- **DLC vs length on FD** — use **`can_len2dlc`/`can_dlc2len`** consistently (@ref page_device_can_dm)
- **Multiple `open`** — `ref_count` > 1 skips FIFO teardown on close; design single-owner stacks

## See also

- @ref page_device_can_dm — FD DLC helpers
- `components/drivers/include/drivers/dev_can.h` — full API and application example
- `components/drivers/can/dev_can.c`
- `components/drivers/can/readme-zh.txt` — legacy Chinese notes for driver porting
- @ref page_device_ofw — DT matching for DM CAN
- @ref page_device_clk, @ref page_device_reset, @ref page_device_regulator — probe dependencies
