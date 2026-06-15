@page page_device_mailbox_dm Mailbox device model (DM)

# Mailbox under `RT_USING_DM`

**`RT_USING_MBOX`** builds **`mailbox.c`** (controller registry, OFW **`mboxes`** resolution, **`rt_mbox_send`** / **`recv`**) and optionally **`mailbox-pic.c`** (**`rt-thread,pic-mailbox`**). The layer is a **Linux-style mailbox framework**: controllers expose channels; clients request by DT phandle and exchange **small payloads** (often one **`uint32_t`** or a pointer to shared memory).

Client/controller API semantics: @ref page_device_mailbox.

Sources: **`components/drivers/mailbox/mailbox.c`**, **`mailbox-pic.c`**, **`components/drivers/include/drivers/mailbox.h`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required |
| **`RT_USING_OFW`** | Required — **`mboxes`**, **`#mbox-cells`**, **`mbox-names`** |
| **`RT_USING_MBOX`** | Core **`mailbox.c`** |
| **`RT_MBOX_PIC`** | In-tree **`rt-thread,pic-mailbox`** (default **y** when MBOX on) |
| **`SOC_DM_MBOX_DIR`** | BSP adds SoC mailbox controllers |

There is **no separate mailbox `rt_bus`** — providers register **`struct rt_mbox_controller`** and bind **`rt_ofw_data(provider_np) = ctrl`**.

---

## Architecture

```
  Mailbox controller driver (platform)
        |
        |  rt_mbox_controller_register(ctrl)
        |  rt_dm_dev_bind_fwdata(dev, NULL, ctrl)
        v
  Provider OFW node  (#mbox-cells, rt_ofw_data = ctrl)
        |
        |  Consumer: mboxes = <&mbox 0>; mbox-names = "tx";
        v
  rt_mbox_request_by_index / by_name(client)
        |
        |  ofw_parse → channel index
        |  ops->request(chan)  [optional]
        |  chan->client = client
        v
  Client: rt_mbox_send / rt_mbox_recv path
        |
        +-- tx_prepare → ops->send → [timer] → rt_mbox_send_done → tx_done
        +-- ISR: read HW → rt_mbox_recv → rx_callback
```

| Role | Object | Responsibility |
| --- | --- | --- |
| **Controller** | **`struct rt_mbox_controller`** | **`num_chans`**, **`ops`**, per-chan timer (created by core) |
| **Channel** | **`struct rt_mbox_chan`** | Binds **`client`**, **`priv`**, send state |
| **Client** | **`struct rt_mbox_client`** | Lives on consumer **`rt_device`**; **`rx_callback`**, **`tx_*`** |

---

## Controller registration

```c
rt_err_t rt_mbox_controller_register(struct rt_mbox_controller *ctrl);
rt_err_t rt_mbox_controller_unregister(struct rt_mbox_controller *ctrl);
```

| Check | Detail |
| --- | --- |
| **`ctrl->dev`**, **`ops`**, **`num_chans > 0`** | Required or **`-RT_EINVAL`** |
| **`ops->send`**, **`ops->release`** | **De facto mandatory** — unregister always calls **`release`** per channel |
| **`ops->request`**, **`ops->peek`**, **`ops->ofw_parse`** | Optional |
| **Per-channel timer** | One-shot; used when **`rt_mbox_send(..., timeout_ms)`** is not **`RT_WAITING_FOREVER`** |

**`ofw_parse`**: custom channel index from **`mboxes`** cells; default parser expects **one cell** = channel index.

---

## Consumer device tree

```dts
scmi: scmi {
    compatible = "arm,scmi";
    mboxes = <&pic_mbox 0>;
    mbox-names = "tx";
};

remote: remoteproc@0 {
    mboxes = <&vendor_mbox 2>, <&vendor_mbox 3>;
    mbox-names = "tx", "rx";
};
```

| Property | Role |
| --- | --- |
| **`mboxes`** | Phandle list + **`#mbox-cells`** per controller |
| **`mbox-names`** | Optional; used with **`rt_mbox_request_by_name`** |
| **`#mbox-cells`** | On **provider** node (default **1** = channel id) |

**`rt_mbox_request_by_index`** calls **`rt_platform_ofw_request`** on the provider if **`rt_ofw_data`** is empty. Returns **`struct rt_mbox_chan *`** or **error pointer** — test with **`rt_is_err_ptr`**.

**`rt_mbox_request_by_name`**: returns **`NULL`** if the name is missing in **`mbox-names`** (distinct from error pointers).

---

## In-tree: PIC mailbox (`mailbox-pic.c`)

**Compatible**: **`rt-thread,pic-mailbox`**

### Register map (per half)

| Offset | Name | Role |
| --- | --- | --- |
| **`0x00`** | **`MAILBOX_IMASK`** | Channel interrupt mask |
| **`0x04`** | **`MAILBOX_ISTATE`** | Pending / doorbell state |
| **`0x08 + n*4`** | **`MAILBOX_MSG(n)`** | 32-bit message slot per channel |

**`reg`** spans **local + peer** windows (each **`size/2`**). **`position = <0>`** (captain): iomap low half, peer = **`regs + size/2`**, initializes both **`IMASK`/`ISTATE`**. **`position = <1>`**: peer low, local high.

| Property | Role |
| --- | --- |
| **`interrupts`** | Local mailbox IRQ |
| **`peer-interrupts`** | HW IRQ number on peer PIC to poke remote CPU |
| **`uid`** | Device name suffix **`pic-mbox{N}`** |
| **`#mbox-cells = <1>`** | Channel index **0..31** (**`num_chans = 32`**) |

### Send / receive behavior

- **`send`**: waits until peer **`ISTATE`** bit clear; writes **`*(uint32_t *)data`** to **`MAILBOX_MSG(index)`**; sets peer **`ISTATE`** bit; triggers **`rt_pic_irq_set_state_raw`** on **`peer_hwirq`**.
- **ISR**: reads pending **`ISTATE`**, loads **`MAILBOX_MSG`** from **peer** window, **`rt_mbox_recv(chan, &msg)`** per bit.
- **Does not call `rt_mbox_send_done`** — TX completion is **not** hardware-ACKed; use a **finite `timeout_ms`** in **`rt_mbox_send`** if **`tx_done`** matters, or treat send as fire-and-forget.

---

## New controller driver checklist

1. Enable **`RT_USING_MBOX`** (+ BSP Kconfig under **`SOC_DM_MBOX_DIR`**).
2. Allocate **`struct rt_mbox_controller`** + private state; set **`dev`**, **`num_chans`**, **`ops`**.
3. Implement **`send`** (required) and **`release`** (required).
4. Optional **`request`**: unmask channel / enable clock.
5. Optional **`peek`**: non-destructive pending check.
6. Optional **`ofw_parse`**: if **`#mbox-cells`** is not a single channel index.
7. **`rt_mbox_controller_register`** after HW init; store pointer in probe (**`user_data`** or **`rt_ofw_data`**).
8. RX ISR: read hardware, then **`rt_mbox_recv(chan, payload_ptr)`**.
9. If hardware has TX complete IRQ: call **`rt_mbox_send_done(chan, err)`**.
10. **`remove`**: detach IRQ, **`rt_mbox_controller_unregister`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Missing `release`** | Unregister crashes — always provide **`ops->release`** |
| **PIC + `tx_done`** | PIC path never calls **`send_done`** — use timeout or do not rely on **`tx_done`** |
| **`data` lifetime** | Keep buffer valid until **`tx_done`** or synchronous send failure |
| **`tx_prepare` under spinlock** | No blocking calls |
| **Error pointer vs NULL** | **`by_index`** → err ptr; missing **`by_name`** → **`NULL`** |
| **32-bit payload on PIC** | **`send`** dereferences **`uint32_t`** — pass pointer to at least 4 bytes |

---

## See also

- @ref page_device_mailbox
- @ref page_device_rpmsg — often layered above mailbox + shared memory
- @ref page_device_scmi — typical doorbell consumer
- @ref page_device_pic
- @ref page_device_ofw
- `components/drivers/include/drivers/mailbox.h`
