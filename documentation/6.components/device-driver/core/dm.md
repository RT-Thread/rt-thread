@page page_device_dm Device model helpers (dm.h)

# Device-side DM helpers

Header: `components/drivers/include/drivers/core/dm.h`. Implementation: `components/drivers/core/dm.c`.

These APIs sit **below** bus matching (`documentation/6.components/device-driver/core/bus.md`) and **above** subsystem drivers: a `probe` typically calls **`rt_dm_dev_iomap`**, **`rt_dm_dev_get_irq`**, and property readers, then registers the functional device (block, netdev, etc.).

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| **`ofw_node` required** | Most helpers return **`-RT_ENOSYS`** or **NULL** when **`dev->ofw_node`** is unset—bind the node in platform probe or **`rt_dm_dev_bind_fwdata`**. |
| **IRQ needs PIC** | **`rt_dm_dev_get_irq*`** is compiled only with **`RT_USING_OFW`** and **`RT_USING_PIC`**. |
| **Property errors** | Inline **`rt_dm_dev_prop_read_u32`** returns **`RT_EOK`** only when the read count is **> 0**; negative counts are cast to **`rt_err_t`**—check return values. |
| **IDA names** | **`rt_dm_ida_alloc`** is per **`master_id`**—do not mix block and other masters on the same **`struct rt_dm_ida`**. |

## ID allocation (`rt_dm_ida`)

Used when a subsystem needs stable numeric suffixes (e.g. **`nvme0`**, partition children):

| API | Role |
| --- | --- |
| `rt_dm_ida_init(ida, id)` | Initialize bitmap + **`MASTER_ID_*`** from **`master_id.h`**. |
| `rt_dm_ida_alloc(ida)` | Allocate lowest free id in **0 … 255**. |
| `rt_dm_ida_take(ida, id)` | Reserve a specific id (returns **`RT_FALSE`** if taken). |
| `rt_dm_ida_free(ida, id)` | Release id. |
| `rt_dm_device_find(master_id, device_id)` | Find **`rt_device`** by master/slave id pair. |

## Device naming

| API | Role |
| --- | --- |
| `rt_dm_dev_set_name(dev, fmt, …)` | Format **`dev->parent.name`** (truncated to **`RT_NAME_MAX`**). |
| `rt_dm_dev_set_name_auto(dev, prefix)` | Append auto id from internal IDA. |
| `rt_dm_dev_get_name` / `rt_dm_dev_get_name_id` | Query current name / numeric suffix. |

## Address and MMIO

| API | Role |
| --- | --- |
| `rt_dm_dev_get_address_count` | Number of **`reg`** windows (OFW). |
| `rt_dm_dev_get_address` / `_by_name` | Physical base + size for index or named resource. |
| `rt_dm_dev_get_address_array` | Pack multiple regions into **`out_regs`**. |
| `rt_dm_dev_iomap` / `_by_name` | Map **`reg`** index or name to CPU virtual address. |

Without **`RT_USING_OFW`**, address/IOMAP calls do not resolve hardware description.

## Interrupts

| API | Role |
| --- | --- |
| `rt_dm_dev_get_irq_count` | Number of interrupt specifiers. |
| `rt_dm_dev_get_irq(dev, index)` | Linux-style interrupt index (**0** = first cell group). |
| `rt_dm_dev_get_irq_by_name` | Match **`interrupt-names`**. |

Install the handler in your driver after obtaining the vector; PIC maps OFW cells to a usable IRQ number.

## Firmware properties

Typed readers (arrays and index variants):

- **`rt_dm_dev_prop_read_u8/u16/u32/u64`** and **`_array_index`**
- **`rt_dm_dev_prop_read_string`** / **`_array_index`**
- **`rt_dm_dev_prop_read_bool`**
- **`rt_dm_dev_prop_count_of_*`**, **`rt_dm_dev_prop_index_of_string`**
- **`rt_dm_dev_get_prop_fuzzy_name`** — suffix/substring match for property names

**`rt_dm_dev_is_big_endian(dev)`** reflects the device endianness flag for MMIO accessors.

## Bind driver private data to OFW node

```c
void rt_dm_dev_bind_fwdata(rt_device_t dev, void *fw_np, void *data);
void rt_dm_dev_unbind_fwdata(rt_device_t dev, void *fw_np);
```

- Sets **`dev->ofw_node`** if it was NULL and assigns **`rt_ofw_data(np) = data`** (controller **`priv`**, **`rt_mbox_controller`**, etc.).
- Consumers resolve providers via **`rt_ofw_data(provider_np)`** after **`rt_platform_ofw_request`**.

## SMP

**`rt_dm_secondary_cpu_init()`** is the BSP hook for secondary CPUs in DM bring-up (weak/no-op if unused).

## Typical `probe` sequence

1. Match on **`compatible`** (platform bus).
2. **`rt_dm_dev_bind_fwdata(dev, np, priv)`**.
3. Optional **`rt_dm_power_domain_attach(dev, RT_TRUE)`** — see **`documentation/6.components/device-driver/core/power.md`**.
4. **`regs = rt_dm_dev_iomap(dev, 0)`**, **`irq = rt_dm_dev_get_irq(dev, 0)`**.
5. Read **`clocks` / `resets` / `dmas`** via property helpers or dedicated frameworks.
6. Register **`rt_device`** / subsystem object; on failure unwind in reverse order.

## Pitfalls

- **Double `bind_fwdata`** with conflicting **`data`** pointers confuses mailbox/clock clients—one owner per OFW node.
- **`iomap` without `reg`**: returns **NULL**; verify DTS and **`status = "okay"`**.
- **Assuming `prop_read_*` zero-fills**: on failure, output may be untouched—initialize locals first.

## See also

- Bus / driver binding: `documentation/6.components/device-driver/core/bus.md`
- Platform bus: `documentation/6.components/device-driver/platform/platform.md`
- OFW runtime: `documentation/6.components/device-driver/ofw/ofw.md`
- Power off / domains: `documentation/6.components/device-driver/core/power.md`, `documentation/6.components/device-driver/power_domain/power_domain.md`
- Header: `components/drivers/include/drivers/core/dm.h`
