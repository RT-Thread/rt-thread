@page page_device_rpmsg RPMsg

@subpage page_device_rpmsg_char
@subpage page_device_rpmsg_ns

# RPMsg subsystem

Header: **`components/drivers/include/drivers/rpmsg.h`**. Core bus: **`components/drivers/rpmsg/rpmsg.c`**.

RPMsg is an **endpoint-oriented IPC bus** on top of a **transport** (VirtIO + shared memory + mailbox in the in-tree example). The core matches **`struct rt_rpmsg_device`** to **`struct rt_rpmsg_driver`** by **`id.name`**, then manages **endpoints** (name + src/dst addresses) and **`send`** via **`struct rt_rpmsg_ops`**.

| Layer | File | Role |
| --- | --- | --- |
| **RPMsg bus** | **`rpmsg/rpmsg.c`** | Endpoints, match **`rpmsg-char`** / **`rpmsg-name-service`** |
| **VirtIO RPMsg device** | **`virtio/virtio-rpmsg.c`** | **`rt_rpmsg_ops`**, virtqueues, NS announce |
| **AMP transport** | **`rpmsg/rpmsg-rt-thread-virtio.c`** | Shared mem, mailbox doorbell, VirtIO transport |
| **Class drivers** | **`rpmsg_char.c`**, **`rpmsg_ns.c`** | Char devices + name service |

**Kconfig**: **`RT_USING_RPMSG`**, **`RT_RPMSG_RT_THREAD_VIRTIO`** (default y), **`RT_RPMSG_CHAR_*`**.

---

## Complete stack (VirtIO example)

This is the **reference integration** in-tree: **`rpmsg-rt-thread-virtio.c`** + **`virtio-rpmsg.c`**.

```
  DT: rt-thread,virtio-rpmsg (master or slave)
        |
        v
  rpmsg_virtio_probe (platform)
        |-- mbox: rt_mbox_request_by_index
        |-- shmem: ioremap from "shmem" phandle
        |-- slab DMA pool in shared RAM
        |-- rt_virtio_device_register (device_id = VIRTIO_DEVICE_ID_RPMSG)
        |
        v
  virtio_rpmsg_probe (virtio driver, RT_VIRTIO_DRIVER_EXPORT)
        |-- virtio_rpmsg_vq_init: rx + tx virtqueues
        |-- rt_rpmsg_device_register(id.name = "rpmsg-char")
        |-- optional: second device "rpmsg-name-service" if VIRTIO_RPMSG_F_NS
        |
        v
  rpmsg bus: match rpmsg_char_driver / rpmsg_ns_driver
        |-- rpmsg_char_probe: control dev rpmsg_charN
        |-- rpmsg_ns_probe: endpoint name-service @ 0x35
        |
        v
  Application: RT_DEVICE_CTRL_RPMSG_CREATE_EPT or NS_CREATE from remote
        |
        v
  rt_rpmsg_send -> virtio_rpmsg_send -> virtqueue kick -> mbox notify peer
```

### Physical pieces

| Piece | DT / code | Role |
| --- | --- | --- |
| **Shared memory** | **`shmem = <&soc_sram>`** | Descriptor rings + virtio buffers + link registers at base |
| **Mailbox** | **`mboxes = <&mbox N>`** | **`RPMSG_VIRTIO_EVENT_LINK`** (exchange queue pointers) and **`EVENT_QUEUE`** (kick) |
| **`queue-max`** | Both sides **must match** | Virtqueue depth |
| **`master` / `slave`** | Property on node | Master publishes queue offsets; slave reads peer TX ring for RX |

**Boot role**: **`rpmsg.mode=master`** or **`slave`** in **`/chosen` bootargs** (`INIT_CORE_EXPORT rpmsg_mode_setup` in **`rpmsg.c`**). Must match firmware on the other core. **`virtio_rpmsg_probe`** swaps RX/TX queue indices for slave vs master.

---

## Device tree example (master + slave)

```dts
/ {
    chosen {
        bootargs = "rpmsg.mode=master";   /* or slave on the other OS */
    };

    soc_sram: memory@60000000 {
        reg = <0x60000000 0x100000>;
    };

    soc_mailbox: mailbox@ ... { /* provider */ };

    rpmsg_virtio0: rpmsg-virtio@0 {
        compatible = "rt-thread,virtio-rpmsg";
        shmem = <&soc_sram>;
        mboxes = <&soc_mailbox 0>;   /* master uses index 0 */
        queue-max = <64>;
        master;
    };
};
```

Remote side (conceptually):

```dts
    rpmsg_virtio1: rpmsg-virtio@0 {
        compatible = "rt-thread,virtio-rpmsg";
        shmem = <&soc_sram>;           /* same region */
        mboxes = <&soc_mailbox 1>;   /* slave uses different mbox index */
        queue-max = <64>;
        slave;
    };
```

After both sides probe: master writes **`MASTER_QUEUE_*`** offsets; **`EVENT_LINK`** makes slave map **`peer_tx_virtq`** and process inbound RPMsg frames.

---

## Layer 1 — Register transport (`rpmsg-rt-thread-virtio`)

**`RT_PLATFORM_DRIVER_EXPORT(rpmsg_virtio_driver)`** — does **not** register **`rt_rpmsg_device`** itself.

**`rpmsg_virtio_probe`** checklist:

1. **`rt_mbox_request_by_index(&mbox_client, 0)`** — **`rx_callback = rpmsg_virtio_rx_callback`**
2. Parse **`shmem`**, **`rt_ioremap_cached`**
3. **`master`** property → **`is_master`**, feature **`VIRTIO_RPMSG_F_NS`** only on master
4. **`rt_slab_init`** on half of shmem (DMA buffers for virtqueues)
5. **`rt_dma_device_set_ops`** — copy to/from shmem for non-coherent AMP
6. Fill **`rt_virtio_device`**: **`VIRTIO_DEVICE_ID_RPMSG`**, **`rpmsg_virtio_trans`**
7. **`rt_virtio_device_register(vdev)`** → triggers **`virtio_rpmsg_probe`**

**Mailbox ISR** (`rpmsg_virtio_rx_callback`):

- **`EVENT_LINK`**: peer published descriptor ring addresses — wire **`peer_tx_virtq`**
- **`EVENT_QUEUE`**: **`rt_virtqueue_isr`** for local virtqueues
- Peer TX avail ring progress → DMA tag fixup → **`used`** index update (feeds virtio RX path)

---

## Layer 2 — Register RPMsg device (`virtio-rpmsg.c`)

**`RT_VIRTIO_DRIVER_EXPORT(virtio_rpmsg_driver)`**

**`virtio_rpmsg_probe`**:

```c
vrpmsg->parent.id.name = "rpmsg-char";
vrpmsg->parent.ops = &virtio_rpmsg_ops;   /* create / destroy / send */
rt_rpmsg_device_register(&vrpmsg->parent);

if (VIRTIO_RPMSG_F_NS) {
    vrpmsg->ns->id.name = "rpmsg-name-service";
    rt_rpmsg_device_register(vrpmsg->ns);
}
```

### `struct rt_rpmsg_ops` (backend contract)

| Op | **`virtio_rpmsg` behavior** |
| --- | --- |
| **`create_endpoint`** | Local: optional **NS CREATE** message to **`RT_RPMSG_NS_ADDR`**. Remote-created: **`src == RT_RPMSG_ADDR_ANY`** |
| **`destroy_endpoint`** | Optional **NS DESTROY** |
| **`send`** | Build **`struct virtio_rpmsg_hdr`** (src, dst, len), **`rt_virtqueue_add_outbuf`**, **`kick`** |

Wire header (**`virtio-rpmsg.h`**):

```c
struct virtio_rpmsg_hdr {
    le32 src, dst, reserved;
    le16 len, flags;
    u8 data[];
};   /* max payload VIRTIO_RPMSG_MAX_BUF_SIZE - sizeof(hdr) */
```

### RX path (`virtio_rpmsg_rx_done`)

1. **`rt_virtqueue_read_buf`** on **RX** queue
2. Find endpoint: **`find_endpoint(rdev, dst=hdr->dst, src=ANY)`**  
   If **`dst == RT_RPMSG_NS_ADDR`** → use **`vrpmsg->ns`** device
3. **`ept->rx_callback(rdev, hdr->src, data, len)`**
4. Re-queue buffer with **`rt_virtqueue_add_inbuf`**

---

## Layer 3 — RPMsg bus (`rpmsg.c`)

### Register a **class driver** (char / NS / custom)

```c
static const struct rt_rpmsg_device_id my_ids[] = {
    { .name = "rpmsg-char" },   /* must match rdev->id.name from backend */
    { },
};

static struct rt_rpmsg_driver my_driver = {
    .ids = my_ids,
    .probe = my_probe,
    .remove = my_remove,
    .rx_callback = my_default_rx,   /* fallback if create_endpoint(..., NULL) */
};
RT_RPMSG_DRIVER_EXPORT(my_driver);
```

**`RT_RPMSG_DRIVER_EXPORT`** → **`INIT_DEVICE_EXPORT`** → **`rt_rpmsg_driver_register`** → probes all **`rt_rpmsg_device`** on bus with matching **`id.name`**.

### Register an **`rt_rpmsg_device`** (custom backend)

If you implement a non-VirtIO link:

```c
rdev->id.name = "rpmsg-char";   /* or your id, but char driver won't bind */
rdev->ops = &my_rpmsg_ops;
rt_rpmsg_device_register(rdev);
```

Bus **`probe`**: **`rt_dm_power_domain_attach`** then **`rdrv->probe(rdev)`**.

---

## Endpoints and addressing

```c
struct rt_rpmsg_endpoint_info info;

rt_strncpy(info.name, "tty", RT_RPMSG_NAME_SIZE);
info.src = 0x400;              /* local address (assigned by you or NS) */
info.dst = 0x401;              /* remote peer */

ept = rt_rpmsg_create_endpoint(rdev, &info, my_rx_cb);
if (rt_is_err(ept))
    return rt_ptr_err(ept);

rt_rpmsg_send(ept, buf, len);
```

| API | Role |
| --- | --- |
| **`rt_rpmsg_create_endpoint`** | **`ops->create_endpoint`**, insert on **`ept_nodes`** |
| **`rt_rpmsg_destroy_endpoint`** | Backend destroy + **`rt_free`** |
| **`rt_rpmsg_find_endpoint`** | Match src/dst/name wildcards (**`RT_RPMSG_ADDR_ANY`**) |
| **`rt_rpmsg_send` / `sendto` / `send_wait`** | **`ops->send`** under **`ept->lock`** |

**RX callback**: per-endpoint **`rx_cb`**, or driver-wide **`struct rt_rpmsg_driver::rx_callback`** if **`rx_cb == NULL`**.

---

## Name service (summary)

Well-known address **`RT_RPMSG_NS_ADDR` (0x35)**. Remote **CREATE** can auto-create endpoints (driver default RX logs only). Local **CREATE** from **`virtio_rpmsg_create_endpoint`** announces name+addr to peer when **`VIRTIO_RPMSG_F_NS`**.

Details: @ref page_device_rpmsg_ns.

---

## Userspace / driver channel (summary)

1. Open control device **`rpmsg_charN`** (from **`rpmsg_char` probe**)
2. **`RT_DEVICE_CTRL_RPMSG_CREATE_EPT`** with **`struct rt_rpmsg_endpoint_info`**
3. Open **`rpmsg_<src>x<dst>`**, **`read`/`write`**

Details: @ref page_device_rpmsg_char.

---

## Bring-up checklist

| Step | Check |
| --- | --- |
| 1 | **`RT_USING_RPMSG`**, **`RT_RPMSG_RT_THREAD_VIRTIO`**, mailbox + shmem drivers |
| 2 | Same **`queue-max`**, same **`shmem`** region, correct **`mboxes`** index per role |
| 3 | **`rpmsg.mode=`** bootarg matches remote |
| 4 | Master has **`master;`** property; slave has **`slave;`** |
| 5 | **`virtio_rpmsg_probe`** succeeds → **`rpmsg_char`** / **`rpmsg-name-service`** on bus |
| 6 | Create endpoint or wait for NS CREATE; verify **`rt_rpmsg_send`** returns OK |
| 7 | @ref page_device_hwspinlock / @ref page_device_mailbox ordering if shared with other AMP IPC |

---

## Custom backend (non-VirtIO)

Implement **`struct rt_rpmsg_ops`** and register **`rt_rpmsg_device`** with an **`id.name`** your class driver matches (or reuse **`rpmsg-char`**):

- **`create_endpoint`**: book-keep addresses / shared memory slots
- **`send`**: push frame with src/dst header to remote
- On RX interrupt: parse header → **`rt_rpmsg_find_endpoint`** → call **`ept->rx_callback`**

Do **not** call **`rt_rpmsg_*`** from ISR if your **`send`** sleeps on virtqueue completion — use workqueue.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`id.name` mismatch** | Backend **`rpmsg-char`** vs driver table **`rpmsg-char`** / **`rpmsg-raw`** |
| **Master/slave queue swap** | Wrong **`rpmsg.mode`** → no RX |
| **`queue-max` mismatch** | Corrupt rings |
| **NS without feature** | Master must advertise **`VIRTIO_RPMSG_F_NS`** |
| **Endpoint without RX cb** | **`create_endpoint(..., NULL)`** needs driver **`rx_callback`** |
| **Buffer size** | Payload ≤ **`VIRTIO_RPMSG_MAX_BUF_SIZE - sizeof(hdr)`** (512 default) |
| **NULL `send` addr** | **`RT_RPMSG_ADDR_ANY`** rejected in **`virtio_rpmsg_send`** |
| **Power domain** | Bus probe attaches domain; **`-RT_EEMPTY`** OK |

---

## See also

- @ref page_device_rpmsg_char
- @ref page_device_rpmsg_ns
- @ref page_device_mailbox
- @ref page_device_hwspinlock
- @ref page_device_platform
- `components/drivers/rpmsg/rpmsg-rt-thread-virtio.c`
- `components/drivers/virtio/virtio-rpmsg.c`
- `components/drivers/virtio/virtio_config/virtio-rpmsg.h`
