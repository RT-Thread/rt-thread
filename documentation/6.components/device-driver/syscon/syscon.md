@page page_device_syscon System controller (Syscon)

# Syscon (system control registers)

**Syscon** is a small DM helper for a **shared MMIO register block** that several drivers touch (reboot magic, boot mode, LED bits, strap latches). One **`struct rt_syscon`** maps the region once and serializes **32-bit** accesses with a per-instance spinlock.

| Piece | Path |
| --- | --- |
| API | `components/drivers/include/drivers/syscon.h` |
| Provider | `components/drivers/mfd/mfd-syscon.c` |
| Kconfig | **`RT_USING_MFD`** → **`RT_MFD_SYSCON`** (needs **`RT_USING_DM`**, **`RT_USING_OFW`**) |

---

## End-to-end flow

```
DT: compatible "syscon" (+ reg)
        ↓
INIT_SUBSYS: platform driver "mfd-syscon" registered
        ↓
INIT_PLATFORM: platform device probe → syscon_probe()
        ├─ rt_ofw_get_address → rt_ioremap
        ├─ insert on global _syscon_nodes list
        └─ rt_ofw_data(np) = syscon
        ↓
Consumer (reboot, LED, …) in its probe:
        rt_syscon_find_by_ofw_phandle(np, "regmap")
        or rt_syscon_find_by_ofw_node(parent_np)
        ↓
rt_syscon_read / write / update_bits (spinlock, HWREG32)
```

**Lazy probe**: If a node was not probed at init but is **`compatible = "syscon"`** or **`"simple-mfd"`**, **`rt_syscon_find_by_ofw_node`** can run **`syscon_probe`** on a stack **`rt_platform_device`** and then return **`rt_ofw_data(np)`**. Prefer normal DT probe for the syscon node so **`iomem_base`** exists before consumers start.

---

## `struct rt_syscon`

```c
struct rt_syscon {
    rt_list_t list;
    struct rt_ofw_node *np;
    void *iomem_base;
    rt_size_t iomem_size;      /* byte size of mapped region */
    struct rt_spinlock rw_lock;
};
```

| Field | Set by |
| --- | --- |
| `np` | Syscon DT node |
| `iomem_base` / `iomem_size` | First **`reg`** region in **`syscon_probe`** |
| `list` | Global registry **`_syscon_nodes`** (lookup under **`_syscon_nodes_lock`**) |

Published to OFW: **`rt_ofw_data(syscon_np) = syscon`** after probe.

---

## Provider driver (`mfd-syscon.c`)

```c
static const struct rt_ofw_node_id syscon_ofw_ids[] = {
    { .compatible = "syscon" },
    { /* sentinel */ },
};

static struct rt_platform_driver syscon_driver = {
    .name = "mfd-syscon",
    .ids = syscon_ofw_ids,
    .probe = syscon_probe,
    .remove = syscon_remove,
};
INIT_SUBSYS_EXPORT(syscon_drv_register);
```

| Step (`syscon_probe`) | Action |
| --- | --- |
| Map | **`rt_ofw_get_address(np, 0, &addr, &size)`** → **`rt_ioremap`** |
| Register | Insert into **`_syscon_nodes`**, init **`rw_lock`** |
| Publish | **`rt_ofw_data(np) = syscon`**, **`pdev->parent.user_data = syscon`** |

**`compatible = "simple-mfd"`** is **not** in **`syscon_ofw_ids`**; those nodes are only handled via **`rt_syscon_find_by_ofw_node`** lazy probe (or as parent of children that call **`find`** on the parent).

---

## Access API

All three functions use **byte offset** into **`iomem_base`** (must satisfy **`offset < iomem_size`**). Each access is one **32-bit** **`HWREG32`** — offsets are **not** auto-scaled to word index.

```c
rt_err_t rt_syscon_read(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t *out_val);
rt_err_t rt_syscon_write(struct rt_syscon *syscon, rt_off_t offset, rt_uint32_t val);
rt_err_t rt_syscon_update_bits(struct rt_syscon *syscon, rt_off_t offset,
        rt_uint32_t mask, rt_uint32_t val);
```

**`rt_syscon_update_bits`** (under spinlock):

```text
new = (old & ~mask) | (val & mask)
```

Only bits set in **`mask`** are changed; **`val`** bits outside **`mask`** are ignored. Safe for typical RMW glue; **W1C** / hardware that ignores read data may need a dedicated driver instead of blind **`update_bits`**.

Callable from thread or ISR context (spinlock-based); keep critical sections short.

---

## Lookup helpers

| API | Use |
| --- | --- |
| **`rt_syscon_find_by_ofw_node(np)`** | Direct syscon (or **`simple-mfd`**) node; walks global list, else lazy **`syscon_probe`** |
| **`rt_syscon_find_by_ofw_phandle(np, "regmap")`** | Consumer node property → target syscon (Linux-style **`regmap`** phandle) |
| **`rt_syscon_find_by_ofw_compatible("vendor,foo-syscon")`** | First matching compatible in DT |

Returns **`RT_NULL`** if map fails or compatible is not **`syscon`** / **`simple-mfd`** (for lazy path).

---

## Device tree

### Provider node

```dts
syscon: syscon@10000000 {
    compatible = "syscon";
    reg = <0x10000000 0x1000>;
};
```

### Consumer: reboot (`syscon-reboot`)

```dts
reboot {
    compatible = "syscon-reboot";
    regmap = <&syscon>;
    offset = <0x200>;
    mask = <0x1>;
    value = <0x1>;
};
```

Kconfig: **`RT_POWER_RESET_SYSCON_REBOOT`**. Installs **`rt_dm_machine_reset`** hook that calls **`rt_syscon_update_bits`**.

### Consumer: poweroff (`syscon-poweroff`)

Same pattern with **`compatible = "syscon-poweroff"`** → **`rt_dm_machine_poweroff`**.

### Consumer: reboot mode (`syscon-reboot-mode`)

Child under syscon (or parent resolved via **`rt_ofw_get_parent`**); writes boot mode magic via **`reboot-mode`** helper.

### Consumer: LED (`register-bit-led`)

```dts
syscon: syscon@10000000 {
    compatible = "syscon";
    reg = <0x10000000 0x100>;

    led0 {
        compatible = "register-bit-led";
        offset = <0x4>;
        mask = <0x10>;
        default-state = "off";
    };
};
```

**`led-syscon.c`**: **`rt_syscon_find_by_ofw_node(parent)`**, **`rt_syscon_read` / `update_bits`** for on/off. See @ref page_device_led_dm.

---

## Kconfig and related drivers

| Option | Role |
| --- | --- |
| **`RT_USING_MFD`** | MFD menu (requires **`RT_USING_DM`**) |
| **`RT_MFD_SYSCON`** | Build **`mfd-syscon.c`** |
| **`RT_POWER_RESET_SYSCON_REBOOT`** | `power/reset/syscon-reboot.c` |
| **`RT_POWER_RESET_SYSCON_POWEROFF`** | `power/reset/syscon-poweroff.c` |
| **`RT_POWER_RESET_SYSCON_REBOOT_MODE`** | `power/reset/syscon-reboot-mode.c` |
| **`RT_LED_SYSCON`** | `led/led-syscon.c` |

---

## Writing a consumer driver

1. In **`probe`**, obtain **`struct rt_syscon *`** via phandle or parent node — do not **`rt_ioremap`** the same **`reg`** again.
2. Parse **`offset`**, **`mask`**, **`value`** (or chip-specific properties) from your DT node.
3. Use **`rt_syscon_read`** for status; **`rt_syscon_update_bits`** for controlled bit changes.
4. Coordinate with @ref page_device_power_board_reset if you hook **`rt_dm_machine_reset`** / **`rt_dm_machine_poweroff`** (only one handler).

---

## Pitfalls

- **Offset vs register index**: API uses **byte** offset; register *N* is often **`N * 4`** depending on TRM.
- **Region size**: **`offset >= iomem_size`** → **`-RT_EINVAL`** — extend **`reg`** in DTS if layout needs more space.
- **64-bit / 16-bit only registers**: not supported by this API — use a dedicated MMIO driver.
- **Lazy vs platform probe**: consumers that **`find`** before syscon **`INIT_PLATFORM`** probe may rely on lazy probe; ordering bugs are easier if the syscon node is a normal platform device probed first.
- **Mask/value**: **`update_bits(..., mask, val)`** clears all **`mask`** bits then sets **`val & mask`** — do not use for status bits that clear on read (W1C).
- **Duplicate mapping**: multiple drivers **`ioremap`** the same physical address without syscon → races; centralize on one **`rt_syscon`**.

---

## See also

- @ref page_device_platform — **`RT_PLATFORM_DRIVER_EXPORT`**, probe order
- @ref page_device_power_board_reset — machine reset / poweroff hooks
- @ref page_device_led_dm — **`register-bit-led`**
- @ref page_device_ofw — phandles, **`rt_ofw_data`**
- `components/drivers/include/drivers/syscon.h`
- `components/drivers/mfd/mfd-syscon.c`
