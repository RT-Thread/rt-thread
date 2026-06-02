@page page_device_input_uapi Input userspace API (UAPI)

# Input event UAPI (`RT_INPUT_UAPI`)

**`input_uapi.c`** exposes each **`rt_input_device`** as a **Linux-compatible** character device for POSIX userspace (Smart / LWP + DFS). IOCTLs and **`struct input_event`** are defined in **`drivers/input_uapi.h`** (aligned with **`include/uapi/linux/input.h`**).

DM overview and driver binding: @ref page_device_input_dm. In-kernel reporters and handlers: @ref page_device_input.

Sources: **`components/drivers/input/input_uapi.c`**, **`components/drivers/include/drivers/input_uapi.h`**.

---

## Kconfig

| Option | Default | Role |
| --- | --- | --- |
| **`RT_INPUT_UAPI`** | **y** if **`RT_USING_SMART`**, else **n** | Build **`input_uapi.c`**, attach **`dfs_file_ops`** in **`input_uapi_init`** |
| **`RT_INPUT_UAPI_EVENT_MAX`** | **128** | Ring buffer slots (**`struct input_event`** per device) |
| **`RT_UAPI_FAKE_BLOCK`** | **y** | **`O_NONBLOCK`** empty **`read`** returns synthetic **`SYN_REPORT`** instead of **`-EAGAIN`** |

**Dependencies**: **`RT_USING_INPUT`**, **`RT_USING_KTIME`**, **`RT_USING_POSIX_DEVIO`**.

---

## Architecture

```
  rt_input_report_* → rt_input_sync
        → rt_input_event (input.c)
              → input_uapi_event (if ref_count > 0)
                    ring buffer + ktime timestamp
                    SYN_REPORT → sync_count++, wake wait_queue
        → read() / poll(POLLIN) on /dev/inputN
```

| Hook | When |
| --- | --- |
| **`input_uapi_init`** | **`rt_input_device_register`** — allocates **`struct input_uapi`**, sets **`idev->parent.fops`** |
| **`input_uapi_event`** | Every **`rt_input_event`** while UAPI enabled |
| **`input_uapi_finit`** | **`rt_input_device_unregister`** — free UAPI state |

Registered device names are **`input0`**, **`input1`**, … (**`rt_dm_ida`** in **`input.c`**). Open via devfs:

```c
int fd = open("/dev/input0", O_RDONLY);
```

**`input_uapi_event`** returns without queuing when **`idev->parent.ref_count == 0`** — userspace must **`open`** the node before events appear.

---

## Event format

| | Kernel handler path | UAPI queue |
| --- | --- | --- |
| Struct | **`struct rt_input_event`** (`drivers/input.h`) | **`struct input_event`** (`input_uapi.h`) |
| Time | **`rt_tick_t tick`** | **`struct timeval`** from **`rt_ktime_boottime_get_us`** |
| Codes | **`dt-bindings/input/event-codes.h`** | Same |

**`struct input_absinfo`** returned by **`EVIOCGABS`** matches **`struct rt_input_absinfo`** (**`RT_ASSERT`** on layout in **`input_uapi_init`**).

---

## Ring buffer and framing

**`struct input_uapi`** holds:

- Atomic **`read_idx`**, **`write_idx`**, **`sync_count`**
- **`events[RT_INPUT_UAPI_EVENT_MAX]`**
- Optional **`grabbed_file`** for **`EVIOCGRAB`**

On each kernel event copy, **`write_idx`** advances. When **`type == EV_SYN`** and **`code == SYN_REPORT`**, **`sync_count`** increments and **`rt_wqueue_wakeup`** runs.

**`read`** drains events until the user buffer is full or a **`SYN_REPORT`** completes one frame; each consumed frame decrements **`sync_count`**.

**Overflow**: if the next write would overwrite unread data, the event is **dropped** (warning log). Raise **`RT_INPUT_UAPI_EVENT_MAX`** for high-rate touch streams.

---

## `read()` / `poll()` / `write()`

| Behavior | Detail |
| --- | --- |
| **Min size** | **`count != 0`** and **`count < sizeof(struct input_event)`** → **`-EINVAL`** |
| **`count == 0`** | Allowed (availability check after wait) |
| **Blocking** | Waits on **`idev->parent.wait_queue`** until **`sync_count > 0`** |
| **`O_NONBLOCK`** | Empty queue → **`-EAGAIN`**, or fake **`SYN_REPORT`** if **`RT_UAPI_FAKE_BLOCK`** |
| **`poll`** | **`POLLIN`** when **`sync_count > 0`** (**`O_RDONLY`** / **`O_RDWR`** only) |
| **`write`** | **`-ENOSYS`** |

**Grab**: if another **`dfs_file`** holds **`EVIOCGRAB`**, **`read`** returns **`-EAGAIN`**.

---

## `ioctl()` (implemented)

| IOCTL | Purpose |
| --- | --- |
| **`EVIOCGVERSION`** | **`EV_VERSION`** (`0x010001`) |
| **`EVIOCGID`** | Virtual ID: bustype **`0x06`**, vendor **`0x5354`**, product **`0x4556`**, version **`RT_VER_NUM >> 16`** |
| **`EVIOCGNAME(len)`** | Device name (**`inputN`**) |
| **`EVIOCGPROP(len)`** | Property bitmap (direct-touch bit when buffer large enough) |
| **`EVIOCGBIT(ev, len)`** | Type bitmap (**`ev==0`**) or **`EV_KEY`/`EV_REL`/`EV_ABS`** maps |
| **`EVIOCGABS(abs)`** | Axis **`struct input_absinfo`** |
| **`EVIOCGRAB`** | Exclusive grab; non-zero **`args`** grabs; second grabber **`-EBUSY`** |

**`EVIOCSABS`**, force-feedback, and other Linux input IOCTLs → **`-EINVAL`**.

---

## Userspace example

```c
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <drivers/input_uapi.h>

void listen_input0(void)
{
    struct input_event ev[64];
    struct pollfd pfd = { .fd = open("/dev/input0", O_RDONLY), .events = POLLIN };

    for (;;)
    {
        if (poll(&pfd, 1, -1) <= 0)
            continue;

        ssize_t n = read(pfd.fd, ev, sizeof(ev));
        if (n <= 0)
            continue;

        for (int i = 0; i < n / (int)sizeof(struct input_event); ++i)
        {
            /* ev[i].type, ev[i].code, ev[i].value */
        }
    }
}
```

Use **`rt_input_add_handler`** in kernel; use UAPI when a POSIX process (e.g. **`evtest`**) reads the same event stream.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **No events before `open`** | **`ref_count`** gate in **`input_uapi_event`** |
| **Unregister with open fd** | **`rt_input_device_unregister`** checks **`ref_count`** — close fds first |
| **Grab conflicts** | Release with **`EVIOCGRAB`** and zero argument |
| **Touch bursts** | Increase **`RT_INPUT_UAPI_EVENT_MAX`** or read faster |
| **`RT_UAPI_FAKE_BLOCK`** | Disable for strict **`-EAGAIN`** on empty non-blocking reads |

---

## See also

- @ref page_device_input_dm
- @ref page_device_input
- `components/drivers/include/drivers/input_uapi.h`
- `components/drivers/input/Kconfig`
