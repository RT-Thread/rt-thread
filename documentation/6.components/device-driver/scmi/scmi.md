@page page_device_scmi SCMI firmware protocol

# SCMI (System Control and Management Interface)

On AArch64 platforms, **secure firmware** (TF-A, SCP, vendor EL3) often owns clocks, regulators, resets, and power domains. The OS talks to that firmware through **SCMI** instead of touching the same hardware directly.

RT-Thread splits the stack into:

| Layer | Location | Role |
| --- | --- | --- |
| **Message / protocol IDs** | `components/drivers/include/drivers/scmi.h` | Payload structs, `SCMI_PROTOCOL_ID_*`, `RT_SCMI_MSG_*` helpers |
| **SCMI bus** | `components/drivers/firmware/arm_scmi/bus.c` | Match `rt_scmi_driver` ↔ `rt_scmi_device` by protocol (and optional name) |
| **Agent + transport** | `components/drivers/firmware/arm_scmi/` | Platform driver `arm-scmi`, shared memory, mailbox / SMC / virtio |
| **Protocol providers** | `*-scmi.c` under clk, regulator, reset, … | `probe` on SCMI bus → register normal DM consumers (`rt_clk_*`, `rt_regulator_*`, …) |

Transport details: @ref page_device_scmi_agent.

**Kconfig**: `RT_FIRMWARE_ARM_SCMI` (needs `RT_USING_FIRMWARE`, `RT_USING_OFW`, Cortex-A / ARMv8). Enable mailbox and/or SMC transport options as your DT uses.

---

## End-to-end flow

```
DT: compatible "arm,scmi" (+ mboxes/shmem or smc-id)
        ↓
INIT_SUBSYS: platform driver "arm-scmi" registered (agent.c)
        ↓
INIT_PLATFORM: platform device probe → scmi_probe()
        ├─ agent_ops->setup()     bind transport
        ├─ scmi_channels_setup()  foreach child "reg" → rt_scmi_device_register()
        └─ register BASE protocol device (0x10)
        ↓
INIT_DEVICE (or SUBSYS for clk): RT_SCMI_DRIVER_EXPORT / rt_scmi_driver_register()
        ↓
scmi bus match(protocol_id [, name]) → driver->probe(sdev)
        ↓
Provider registers clk / regulator / reset / genpd / …
        ↓
Other drivers consume via normal OFW (clocks = <&…>, resets = <&…>, …)
```

Application and most drivers **never call SCMI directly**; they use the same APIs as MMIO backends (`rt_clk_get_by_index`, `rt_regulator_get`, `rt_reset_control_get`, …).

---

## Data structures (`scmi.h`)

```c
struct rt_scmi_device {
    struct rt_device parent;   /* parent.ofw_node, parent.bus, parent.drv */
    const char *name;          /* optional; used in bus match */
    rt_uint8_t protocol_id;    /* from child node property "reg" */
    struct scmi_agent *agent;
};

struct rt_scmi_device_id {
    rt_uint8_t protocol_id;
    const char *name;          /* NULL = match any name for this protocol */
};

struct rt_scmi_driver {
    struct rt_driver parent;
    const char *name;
    const struct rt_scmi_device_id *ids;   /* sentinel: protocol_id == 0 */
    rt_err_t (*probe)(struct rt_scmi_device *sdev);
    rt_err_t (*remove)(struct rt_scmi_device *sdev);
    rt_err_t (*shutdown)(struct rt_scmi_device *sdev);
};
```

**Bus match** (`bus.c`): for each `ids[]` entry, `id->protocol_id == device->protocol_id`, and if `id->name` is set it must equal `device->name` (from OFW `protocol-name` or similar on the channel node).

---

## Boot and init order

| Export / register | Level | What runs |
| --- | --- | --- |
| `scmi_bus_init` | `INIT_CORE_EXPORT` | `rt_bus_register(&scmi_bus)` |
| `scmi_drv_register` (`arm-scmi` platform driver) | `INIT_SUBSYS_EXPORT` | Agent ready before bulk DT probe |
| `platform_ofw_device_probe` | `INIT_PLATFORM_EXPORT` | Creates `arm,scmi` platform device → `scmi_probe` |
| `RT_SCMI_DRIVER_EXPORT(...)` | `INIT_DEVICE_EXPORT` | Protocol driver registers → probes pending `rt_scmi_device`s |
| `scmi_clk_drv_register` | `INIT_SUBSYS_EXPORT` | **Exception**: `clk-scmi.c` calls `rt_scmi_driver_register()` manually (earlier than `RT_SCMI_DRIVER_EXPORT`) |

If a protocol driver registers **after** its `rt_scmi_device` already exists, `rt_bus_add_driver` walks devices and runs `probe` (same pattern as platform bus).

---

## Sending a message

All transports funnel through:

```c
rt_err_t rt_scmi_process_msg(struct rt_scmi_device *sdev, struct rt_scmi_msg *msg);
```

Build payloads with typed structs in `scmi.h` and:

```c
struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_VOLTAGE_DOMAIN_LEVEL_SET, &in, &out);
err = rt_scmi_process_msg(sdev, &msg);
/* check err, then out.status (firmware SCMI status, not always -errno) */
```

| Helper | Use |
| --- | --- |
| `RT_SCMI_MSG_IN_OUT(id, in, out)` | Fixed-size in + out |
| `RT_SCMI_MSG_IN(id, in)` | Command with input only |
| `RT_SCMI_MSG_OUT(id, out)` | Command with output only |
| `RT_SCMI_MSG_RAW(...)` | Variable buffer sizes |

Firmware returns **`SCMI_SUCCESS`** (0) or negative **`SCMI_ERR_*`** in message status fields; `rt_scmi_strerror()` maps those codes to short names (`agent.c`).

**Threading**: `process_msg` is blocking for mailbox/SMC paths; do not call from ISR unless your transport is explicitly IRQ-safe.

---

## Device tree (controller)

Example mailbox transport (simplified):

```dts
scmi: scmi {
    compatible = "arm,scmi";
    mboxes = <&mbox 0>;
    shmem = <&scmi_shmem>;

    /* Optional per-protocol channel nodes */
    protocol@14 {
        reg = <0x14>;              /* SCMI_PROTOCOL_ID_CLOCK */
        protocol-name = "clocks";  /* must match driver ids[].name if set */
    };
    protocol@17 {
        reg = <0x17>;
        protocol-name = "regulator";
    };
};

scmi_shmem: sram@… {
    compatible = "arm,scmi-shmem";
    reg = <…>;
};
```

| `compatible` | Transport (`agent.c` `scmi_ofw_ids`) |
| --- | --- |
| `arm,scmi` | Mailbox (`agent-mailbox.c`) |
| `arm,scmi-smc`, `arm,scmi-smc-param`, `qcom,scmi-smc` | SMC (`agent-smc.c`) |
| `arm,scmi-virtio` | Virtio (`virtio-scmi.c`, if `RT_FIRMWARE_ARM_SCMI_TRANSPORT_VIRTIO`) |

Child **`reg`** is the protocol ID (same values as `SCMI_PROTOCOL_ID_*` in `scmi.h`). The agent registers one **`rt_scmi_device`** per child; protocol drivers bind to that node’s `parent.ofw_node` for provider-specific subnodes (e.g. `regulators` under voltage protocol).

---

## Built-in protocol drivers

| Protocol ID | `ids[].name` | Source | Registers |
| --- | --- | --- | --- |
| `0x14` CLOCK | `"clocks"` | `clk/clk-scmi.c` | `rt_clk` provider |
| `0x17` VOLTAGE | `"regulator"` | `regulator/regulator-scmi.c` | `rt_regulator_register` |
| `0x16` RESET | (see driver) | `reset/reset-scmi.c` | reset controller |
| `0x11` POWER | `"genpd"` | `pmdomain/pm-domain-scmi.c` | power domain proxy |
| `0x19` PINCTRL | (see driver) | `pinctrl/pinctrl-scmi.c` | pin config via SCMI |
| SENSOR / thermal | (see driver) | `thermal/thermal-scmi.c` | thermal zone |

Consumers in DT stay unchanged: e.g. `clocks = <&scmi_clk 42>;`, `resets = <&scmi_reset 3>;`, `power-domains = <&scmi_pd 1>;` — see @ref page_device_clk, @ref page_device_regulator, @ref page_device_reset, @ref page_device_power_domain, @ref page_device_pinctrl.

---

## Adding a protocol driver

1. Implement `probe(struct rt_scmi_device *sdev)` — use `sdev->parent.ofw_node` and `sdev->agent` is already set.
2. Issue commands with `rt_scmi_process_msg(sdev, &msg)`.
3. Register the high-level provider (clock, regulator, …) your consumers expect.
4. Publish the driver:

```c
static const struct rt_scmi_device_id my_ids[] = {
    { SCMI_PROTOCOL_ID_xxx, "my-protocol-name" },  /* name must match DT if used */
    { /* sentinel */ },
};

static struct rt_scmi_driver my_scmi_driver = {
    .name = "my-scmi",
    .ids = my_ids,
    .probe = my_probe,
};
RT_SCMI_DRIVER_EXPORT(my_scmi_driver);
```

Match **`protocol-name`** on the channel node to `ids[].name` when the table entry sets `name` non-NULL.

---

## Debugging

- Confirm **`arm-scmi` probe** and child `reg` values in logs (`DBG_TAG` `scmi.agent`, `scmi.bus`).
- Mailbox path: mailbox TX/RX, shared memory **channel free** bit (`shmem.c`), 30-tick timeout on `rt_mbox_send`.
- SMC path: `arm,smc-id`, IRQ completion, page/offset for `arm,scmi-smc-param`.
- Version skew: use BASE protocol `SCMI_COM_MSG_VERSION` if commands return `SCMI_ERR_PROTOCOL`.

---

## See also

- @ref page_device_scmi_agent — mailbox, SMC, shmem layout
- @ref page_device_mailbox — doorbell for `arm,scmi`
- `components/drivers/include/drivers/scmi.h`
- `components/drivers/firmware/arm_scmi/agent.c`, `bus.c`
