@page page_device_scmi_agent SCMI agent transports

# SCMI agent layer

Overview and protocol drivers: @ref page_device_scmi.

Implementation directory: **`components/drivers/firmware/arm_scmi/`**.

The **agent** is the only piece that knows how to move a `struct rt_scmi_msg` across the SoC boundary. Every `rt_scmi_device` on the SCMI bus shares the same **`struct scmi_agent`** instance created during platform **`scmi_probe`**.

---

## Agent object (`agent.h`)

```c
struct scmi_agent_ops {
    const char *name;
    rt_err_t (*setup)(struct scmi_agent *agent, struct rt_device *dev);
    rt_err_t (*process_msg)(struct scmi_agent *agent, struct rt_scmi_msg *msg);
};

struct scmi_agent {
    const struct scmi_agent_ops *ops;
    void *priv;   /* transport state (mailbox, SMC, virtio) */
};
```

| Callback | When it runs |
| --- | --- |
| `setup` | Once per SCMI controller: parse DT, map shmem, request mailbox channel / program SMC |
| `process_msg` | Every `rt_scmi_process_msg()` — serialize request, wait for reply, fill `out_msg` |

`rt_scmi_process_msg()` (`agent.c`) sets `msg->sdev` and calls `agent->ops->process_msg`.

---

## Platform driver registration (`agent.c`)

```c
static const struct rt_ofw_node_id scmi_ofw_ids[] = {
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_MAILBOX
    { .compatible = "arm,scmi", .data = &scmi_agent_mailbox_ops },
#endif
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_SMC
    { .compatible = "arm,scmi-smc", .data = &scmi_agent_smc_ops },
    /* arm,scmi-smc-param, qcom,scmi-smc */
#endif
#ifdef RT_FIRMWARE_ARM_SCMI_TRANSPORT_VIRTIO
    { .compatible = "arm,scmi-virtio", .data = &scmi_agent_virtio_ops },
#endif
    { /* sentinel */ },
};

static struct rt_platform_driver scmi_driver = {
    .name = "arm-scmi",
    .ids = scmi_ofw_ids,
    .probe = scmi_probe,
};
INIT_SUBSYS_EXPORT(scmi_drv_register);
```

**`scmi_probe`** sequence:

1. `agent_ops = pdev->id->data` — transport selected by `compatible`.
2. `agent_ops->setup(agent, &pdev->parent)` — transport private state in `agent->priv`.
3. **`scmi_channels_setup`**: for each available child of the controller node, read **`reg`** → `protocol_id`, allocate `rt_scmi_device`, set `sdev->agent`, `rt_scmi_device_register(sdev)`.
4. Register an extra device for **`SCMI_PROTOCOL_ID_BASE`** (common protocol) on the same agent.

Protocol drivers attach later via the SCMI bus (see main SCMI page).

---

## Shared memory (`shmem.c` / `shmem.h`)

Mailbox and SMC transports place the SCMI frame in **`struct scmi_shared_mem`**:

- `channel_status` — **FREE** / **ERROR** bits; writer clears FREE before sending.
- `msg_header` — built with `scmi_header(message_id, type, protocol_id, token)` from `scmi.h`.
- `msg_payload[]` — command input; reply read back into `msg->out_msg`.

| API | Role |
| --- | --- |
| `scmi_shmem_msg_write(shmem, msg)` | Pack header + `in_msg`, mark channel busy |
| `scmi_shmem_msg_read(shmem, msg)` | Copy reply after firmware marks channel free |
| `scmi_shmem_clear_channel(shmem)` | Reset channel after TX done (mailbox) |

DT **`shmem`** phandle must point at a node with **`compatible = "arm,scmi-shmem"`**; address is **`rt_ioremap`**’d in agent `setup`.

Ensure the mapping matches firmware expectations (often **device / non-cacheable**). If the region is cacheable, flush or invalidate around access per your BSP / TRM.

---

## Mailbox transport (`agent-mailbox.c`)

Depends on **`RT_USING_MBOX`** and `RT_FIRMWARE_ARM_SCMI_TRANSPORT_MAILBOX`.

**Setup**

- Count **`mboxes`** and **`shmem`** phandles; pick channel index when multiple mailboxes exist (e.g. high vs low priority).
- `rt_mbox_request_by_index()` with client callbacks:
  - **`tx_prepare`** → `scmi_shmem_msg_write()`
  - **`tx_done`** → `scmi_shmem_clear_channel()` on success
  - **`rx_callback`** → optional `msg->rx_callback` for async use

**`process_msg`**

- Spinlock around `rt_mbox_send(chan, msg, timeout)` (30 ticks in tree).
- Mailbox driver completes the round trip and fills output via shmem read path.

Typical DT:

```dts
scmi {
    compatible = "arm,scmi";
    mboxes = <&firmware_mbox 0>;
    shmem = <&scmi_shmem>;
};
```

See @ref page_device_mailbox and @ref page_device_mailbox_dm.

---

## SMC transport (`agent-smc.c`)

Depends on **`RT_FIRMWARE_ARM_SCMI_TRANSPORT_SMC`**.

**Setup**

- **`arm,smc-id`** — SMC function number for SCMI.
- Map **`shmem`** like mailbox; optional **`interrupts`** — ISR sets `done` flag.
- Variants with **`arm,scmi-smc-param`** use page/offset fields in `struct scmi_agent_smc` for shared memory location passed in registers.

**`process_msg`**

- Writes message to shmem, issues **`smccc`** call, waits for IRQ or polling `done`, reads reply from shmem.

Use when firmware exposes SCMI only through EL3 traps (no separate mailbox IP).

---

## Virtio transport (`virtio-scmi.c`)

Enabled when **`RT_VIRTIO_SCMI`** / `RT_FIRMWARE_ARM_SCMI_TRANSPORT_VIRTIO` is on. **`compatible = "arm,scmi-virtio"`** selects `scmi_agent_virtio_ops` — SCMI over a virtio queue instead of SoC mailbox/SMC. Typical in guest / hypervisor scenarios.

---

## Error handling

| Return | Meaning |
| --- | --- |
| `-RT_*` from `setup` / `process_msg` | RT-Thread transport failure (ENOMEM, EIO, mbox timeout, …) |
| `out.status` / payload status field | Firmware **`SCMI_ERR_*`** — use `rt_scmi_strerror(status)` for logs |

Do not assume firmware status equals POSIX `-errno` unless your wrapper converts it (protocol drivers often map `SCMI_SUCCESS` to `RT_EOK` explicitly).

---

## See also

- @ref page_device_scmi
- `components/drivers/firmware/arm_scmi/agent.c`
- `components/drivers/firmware/arm_scmi/agent-mailbox.c`
- `components/drivers/firmware/arm_scmi/agent-smc.c`
- `components/drivers/virtio/virtio-scmi.c`
