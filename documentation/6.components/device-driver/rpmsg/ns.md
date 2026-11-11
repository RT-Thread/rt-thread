@page page_device_rpmsg_ns RPMsg name service

# RPMsg name service (`rpmsg_ns.c`)

**`RT_RPMSG_DRIVER_EXPORT(rpmsg_ns_driver)`** — matches **`id.name = "rpmsg-name-service"`** (second **`rt_rpmsg_device`** from **`virtio-rpmsg.c`** when **`VIRTIO_RPMSG_F_NS`**).

Stack context: @ref page_device_rpmsg.

---

## Fixed endpoint

**`rpmsg_ns_probe`** creates:

| Field | Value |
| --- | --- |
| **`info.name`** | `"name-service"` |
| **`src` / `dst`** | **`RT_RPMSG_NS_ADDR` (0x35)** |
| RX | **`rpmsg_ns_rx_callback`** |

---

## Wire message

```c
struct rt_rpmsg_ns_msg {
    char name[32];
    le32 addr;
    le32 flags;   /* RT_RPMSG_NS_CREATE or RT_RPMSG_NS_DESTROY */
};
```

**`rpmsg_ns_rx_callback`**:

| Flag | Action |
| --- | --- |
| **CREATE** | **`rt_rpmsg_create_endpoint(rdev, &info, NULL)`** → driver **`rx_callback`** fallback |
| **DESTROY** | **`find_endpoint`** + **`destroy_endpoint`** |

**`virtio_rpmsg`** routes packets with **`dst == 0x35`** to **`vrpmsg->ns`** device, not the char device.

---

## Local CREATE side

When **`virtio_rpmsg_create_endpoint`** runs on a **local** endpoint and **`supp_ns`**:

- Sends **NS CREATE** to **`RT_RPMSG_NS_ADDR`** with **`addr = ept->info.src`** (little-endian on wire)

Remote can then open the announced channel.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Endianness** | **`addr`** is **le32** on wire |
| **CREATE without consumer** | Orphan endpoints until DESTROY |
| **Only master has NS feature** | **`rpmsg_virtio_get_features`** sets **`VIRTIO_RPMSG_F_NS`** on master |

---

## See also

- @ref page_device_rpmsg
- @ref page_device_rpmsg_char
- `components/drivers/rpmsg/rpmsg_ns.c`
