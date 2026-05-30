@page page_device_ofw Open Firmware (OFW)

# Open Firmware (OFW) overview

RT-Thread **OFW** parses the boot **DTB** into **`struct rt_ofw_node`**, then exposes property I/O, addressing, interrupts, and platform device enumeration. Implementation mirrors **`components/drivers/ofw/`** source layout.

| Source / header | Documentation |
| --- | --- |
| **`base.c`**, **`ofw.c`** — `ofw.h` | @ref page_device_ofw_base |
| **`fdt.c`** — `ofw_fdt.h` | @ref page_device_ofw_boot |
| **`io.c`** — `ofw_io.h` | @ref page_device_ofw_io |
| **`irq.c`** — `ofw_irq.h` | @ref page_device_ofw_irq |
| **`raw.c`** — `ofw_raw.h` | @ref page_device_ofw_raw |
| **`core/platform_ofw.c`** | @ref page_device_ofw_platform |
| Build **DTS → DTB** | @ref page_device_dtc |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_OFW`** | OFW + libfdt; requires **`RT_USING_DM`** |
| **`RT_USING_BUILTIN_FDT`** | Link **`RT_BUILTIN_FDT_PATH`** (default `rtthread.dtb`) |
| **`RT_FDT_EARLYCON_MSG_SIZE`** | Early console ring (KB, default 128) |
| **`RT_USING_OFW_BUS_RANGES_NUMBER`** | Cached **`ranges`** slots (4 or 8) |

---

## Typical driver flow

```
  Bootloader DTB
       → rt_fdt_prefetch / scan_memory / unflatten   (@ref page_device_ofw_boot)
       → INIT_PLATFORM_EXPORT(platform_ofw_device_probe) (@ref page_device_ofw_platform)
       → driver probe(np): reg/irq/phandles
            rt_ofw_get_address + rt_dm_dev_iomap     (@ref page_device_ofw_io)
            rt_ofw_get_irq / rt_ofw_map_irq          (@ref page_device_ofw_irq)
            rt_ofw_parse_phandle_cells + rt_platform_ofw_request (@ref page_device_ofw_base)
```

---

## Phandle consumer pattern

Most DM subsystems share the same parse sequence:

1. **`rt_ofw_parse_phandle_cells(np, "clocks", "#clock-cells", index, &args)`**
2. **`provider_np = args.data`**; if **`!rt_ofw_data(provider_np)`** → **`rt_platform_ofw_request(provider_np)`**
3. Use subsystem API (**`rt_clk_get_by_index`**, **`rt_mbox_request_channel`**, …)

| Property | `#*-cells` | See also |
| --- | --- | --- |
| **`clocks`** | **`#clock-cells`** | @ref page_device_clk |
| **`resets`** | **`#reset-cells`** | reset DM |
| **`mboxes`** | **`#mbox-cells`** | @ref page_device_mailbox_dm |
| **`io-channels`** | **`#io-channel-cells`** | @ref page_device_iio_dm |
| **`nvmem-cells`** | **`#nvmem-cell-cells`** | @ref page_device_nvmem_dm |

**`rt_ofw_parse_object(np, obj_name, "#clock-cells")`** resolves composite objects in **`rt_ofw_data`** when one node exports multiple controllers.

---

## Driver quick notes

| Topic | Guidance |
| --- | --- |
| **`status`** | Use **`rt_ofw_node_is_available`** before attaching hardware |
| **`reg`** | Use **`rt_ofw_io_*`** / **`rt_ofw_get_address`** — never hard-code parent **`#address-cells`** |
| **IRQ** | Direct **`interrupts`** vs bridge **`interrupt-map`** — see @ref page_device_ofw_irq |
| **Refs** | Pair **`rt_ofw_node_get`** / **`rt_ofw_node_put`** when caching **`np`** |
| **`compatible`** | Most specific string first in DTS and **`rt_ofw_node_id`** table |

---

## Normative references

- [Device Tree Specification](https://devicetree-specification.readthedocs.io/)
- **`components/drivers/include/dt-bindings/`** — include from DTS via cpp

## See also

- `components/drivers/ofw/` — implementation
- @ref page_device_platform
- @ref page_device_bus
- @ref page_device_dm
