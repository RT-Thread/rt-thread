@page page_device_mailbox Mailbox subsystem

# Mailbox subsystem (API)

Header: **`components/drivers/include/drivers/mailbox.h`**. Core: **`components/drivers/mailbox/mailbox.c`**.

The mailbox layer is a **lock-aware wrapper** around hardware **doorbell / message-slot** IPs: one side **sends** a small notification, the peer is woken by **IRQ** and handles **`rx_callback`**. Use for **AMP IPC**, **SCMI** doorbells, **remoteproc** handshakes, and **PIC**-backed mailboxes—not bulk DMA.

Device-tree binding and **`rt-thread,pic-mailbox`**: @ref page_device_mailbox_dm.

---

## When to use this API

| Use mailbox when… | Prefer something else when… |
| --- | --- |
| You need a **hardware channel** with **IRQ to peer** (SoC mailbox IP, PIC mailbox). | **Thread-to-thread** only: semaphore, message queue, completion. |
| Firmware expects **doorbell + shared memory** (SCMI, AMP). | **Large payloads** — put data in SRAM, pass a **pointer** or single word. |
| DT exposes **`mboxes` / `#mbox-cells` / `mbox-names`**. | No controller: implement **`rt_mbox_controller_ops`** and register first. |
| Named **RPMsg** endpoints and bus matching are required. | @ref page_device_rpmsg |

---

## Roles

| Role | Responsibility |
| --- | --- |
| **Controller driver** | **`rt_mbox_controller_register`**: **`num_chans`**, **`ops`**. Implements **`send`**, **`release`**, optional **`peek`**, **`request`**, **`ofw_parse`**. Calls **`rt_mbox_send_done`** when HW TX completes (if applicable). |
| **Client driver** | **`struct rt_mbox_client`** on consumer **`rt_device`**: **`tx_prepare`**, **`tx_done`**, **`rx_callback`**. **`rt_mbox_request_by_index`** or **`by_name`**. |

---

## Data structures

```c
struct rt_mbox_controller {
    struct rt_device *dev;
    const struct rt_mbox_controller_ops *ops;
    rt_size_t num_chans;
    struct rt_mbox_chan *chans;
};

struct rt_mbox_controller_ops {
    rt_err_t (*request)(struct rt_mbox_chan *);
    void (*release)(struct rt_mbox_chan *);
    rt_err_t (*send)(struct rt_mbox_chan *, const void *data);
    rt_bool_t (*peek)(struct rt_mbox_chan *);
    int (*ofw_parse)(struct rt_mbox_controller *, struct rt_ofw_cell_args *);
};

struct rt_mbox_client {
    struct rt_device *dev;
    void (*rx_callback)(struct rt_mbox_client *, void *data);
    void (*tx_prepare)(struct rt_mbox_client *, const void *data);
    void (*tx_done)(struct rt_mbox_client *, const void *data, rt_err_t err);
};
```

---

## Requesting a channel

```c
struct rt_mbox_chan *rt_mbox_request_by_index(struct rt_mbox_client *client, int index);
struct rt_mbox_chan *rt_mbox_request_by_name(struct rt_mbox_client *client, char *name);
rt_err_t rt_mbox_release(struct rt_mbox_chan *chan);
```

| API | Returns |
| --- | --- |
| **`request_by_index`** | Channel pointer or **error pointer** (`rt_is_err_ptr`) |
| **`request_by_name`** | Channel, **error pointer**, or **`NULL`** if name not in **`mbox-names`** |

**Prerequisites**: valid **`client->dev->ofw_node`**; provider probed (**`rt_ofw_data`** = controller). Optional **`ops->request`** runs after channel selection; on failure core **`release`**s and returns error pointer.

---

## Sending: `rt_mbox_send`

```c
rt_err_t rt_mbox_send(struct rt_mbox_chan *chan, const void *data, rt_uint32_t timeout_ms);
void rt_mbox_send_done(struct rt_mbox_chan *chan, rt_err_t err);
```

**Flow** (under **`chan->lock`**):

1. Optional **`client->tx_prepare(client, data)`**
2. **`ctrl->ops->send(chan, data)`** — return value is **only** the ops result
3. On success: store **`chan->data`**, clear **`complete`**; if **`timeout_ms != RT_WAITING_FOREVER`**, start one-shot timer
4. On send failure: **`complete = RT_TRUE`** immediately

**`RT_EOK` from `rt_mbox_send`** means the controller **accepted** the submission, not that **`tx_done`** ran.

**`rt_mbox_send_done`**: clears **`chan->data`**, calls **`tx_done`**, sets **`complete = RT_TRUE`**. Controller must invoke after HW TX finish (or on error). Timer calls it with **`-RT_ETIMEOUT`** if still incomplete.

**Implications**:

- Do not free **`data`** (or pointed buffer) until **`tx_done`** or synchronous send failure
- **`tx_prepare`** runs **with channel spinlock** — non-blocking only
- **`RT_WAITING_FOREVER`**: no timer; requires **`send_done`** from controller for **`tx_done`** (see @ref page_device_mailbox_dm for PIC caveat)

---

## Receiving: `rt_mbox_recv`

```c
rt_err_t rt_mbox_recv(struct rt_mbox_chan *chan, void *data);
```

Does **not** read hardware. Invokes **`client->rx_callback(client, data)`** if set. **Controller ISR** reads registers/FIFO, then passes payload pointer (e.g. local **`uint32_t`**) into **`rt_mbox_recv`**.

---

## `rt_mbox_peek`

```c
rt_bool_t rt_mbox_peek(struct rt_mbox_chan *chan);
```

Forwards to **`ops->peek`** if present; else **`RT_FALSE`**.

---

## Controller unregister

**`rt_mbox_controller_unregister`**: removes from global list, **`rt_dm_dev_unbind_fwdata`**, **`rt_mbox_release`** on every channel (reverse order), frees **`chans`**. **`release`** must be safe even if **`request`** never ran for a channel.

---

## Example (client sketch)

```c
static void my_rx(struct rt_mbox_client *cl, void *data)
{
    rt_uint32_t msg = *(rt_uint32_t *)data;
    /* handle doorbell */
}

static void my_tx_done(struct rt_mbox_client *cl, const void *data, rt_err_t err)
{
    /* release buffer */
}

static struct rt_mbox_client mbox_cl = {
    .dev = &my_pdev->parent,
    .rx_callback = my_rx,
    .tx_done = my_tx_done,
};

static int my_probe(struct rt_platform_device *pdev)
{
    struct rt_mbox_chan *chan;

    mbox_cl.dev = &pdev->parent;
    chan = rt_mbox_request_by_name(&mbox_cl, "tx");
    if (!chan || rt_is_err_ptr(chan))
        return -RT_ERROR;

    rt_uint32_t doorbell = MY_MSG_ID;
    return rt_mbox_send(chan, &doorbell, 100);  /* 100 ms tx timeout */
}
```

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **No `send_done` in controller** | Use finite timeout or fire-and-forget (@ref page_device_mailbox_dm — PIC) |
| **`release` NULL** | Always implement **`ops->release`** |
| **Blocking in `tx_prepare`** | Deadlock risk under spinlock |
| **Confusing return types** | Distinguish **`NULL`** (name) vs **`rt_err_ptr`** (index) |

---

## See also

- @ref page_device_mailbox_dm
- @ref page_device_rpmsg
- @ref page_device_scmi
- @ref page_device_pic
- `components/drivers/mailbox/mailbox.c`
- `components/drivers/mailbox/mailbox-pic.c`
