@page page_device_rpmsg_char RPMsg character device

# RPMsg char driver (`rpmsg_char.c`)

**`RT_RPMSG_DRIVER_EXPORT(rpmsg_char_driver)`** — matches **`rt_rpmsg_device`** with **`id.name`** **`rpmsg-char`** or **`rpmsg-raw`** (set by **`virtio-rpmsg.c`**).

Prerequisite: transport + **`rt_rpmsg_device_register`** — see @ref page_device_rpmsg (VirtIO stack).

---

## Topology

| Device | Name pattern | Ops |
| --- | --- | --- |
| Control | **`rpmsg_charN`** | **`control`** only — create/destroy endpoints |
| Per endpoint | **`rpmsg_<src>x<dst>`** | **`read` / `write` / `control`** |

**`probe`**: allocates **`rpmsg_char_ctrl`**, stores in **`rdev->parent.user_data`**, registers control **`rt_device`**.

---

## Create endpoint

On control device:

```c
struct rt_rpmsg_endpoint_info info;

rt_strncpy(info.name, "my-channel", RT_RPMSG_NAME_SIZE);
info.src = local_addr;
info.dst = remote_addr;

rt_device_control(ctrl, RT_DEVICE_CTRL_RPMSG_CREATE_EPT, &info);
```

Flow:

1. Default name **`rpmsg-raw`** if **`info.name`** empty
2. **`rt_rpmsg_create_endpoint(rdev, &info, rpmsg_char_rx_callback)`**
3. Ring buffer pool: **`RT_RPMSG_CHAR_MSG_MAX`** × **`RT_RPMSG_CHAR_MSG_SIZE_MAX`** (Kconfig)
4. Register char device **`rpmsg_%ux%u`**

---

## Data path

| Direction | Path |
| --- | --- |
| **TX** | **`write`** → **`rt_rpmsg_send`** |
| **RX** | VirtIO/backend → endpoint cb → **`rt_ringbuffer_put`** → **`read`** |
| **Overwrite** | **`RT_DEVICE_CTRL_RPMSG_DATA_OVERWRITE`** → **`put_force`** when full |

RX matching uses **`find_endpoint`** with **`dst = incoming src`**, **`src = ANY`** — addresses must match how the endpoint was created.

---

## Destroy

**`RT_DEVICE_CTRL_RPMSG_DESTROY_EPT`**: deferred via **`rt_work`** until **`ref_count == 1`** and device closed.

---

## See also

- @ref page_device_rpmsg
- `components/drivers/rpmsg/rpmsg_char.c`
