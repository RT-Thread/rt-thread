@page page_device_ofw_boot OFW boot and FDT

# FDT bring-up (`fdt.c`)

Raw **DTB** → **memblock** → unflattened **`rt_ofw_node`** tree. After unflatten, use **`rt_ofw_*`** (@ref page_device_ofw_base), not **`rt_fdt_*`**, unless still touching the blob.

Header: **`drivers/ofw_fdt.h`**. Source: **`components/drivers/ofw/fdt.c`**.

---

## Boot sequence

```
  rt_fdt_prefetch(fdt)
       → rt_fdt_scan_root()
       → rt_fdt_scan_memory()      /* memblock */
       → rt_fdt_scan_initrd()      /* optional */
       → rt_fdt_unflatten()        /* rt_ofw_node tree */
       → INIT_PLATFORM_EXPORT(platform_ofw_device_probe)
```

Global nodes (**`ofw_internal.h`**): **`ofw_node_root`**, **`ofw_node_cpus`**, **`ofw_node_chosen`**, **`ofw_node_aliases`**, **`ofw_node_reserved_memory`**.

---

## API (blob phase)

| API | Role |
| --- | --- |
| **`rt_fdt_prefetch`** | Store **`_fdt`**, validate header, **`rt_fdt_scan_root`** |
| **`rt_fdt_scan_root`** | Root **`#address-cells` / `#size-cells`** |
| **`rt_fdt_scan_memory`** | **`device_type = "memory"`** → **`rt_memblock_add_memory`** |
| **`rt_fdt_scan_initrd`** | Reserve initrd range |
| **`rt_fdt_unflatten`** | Build in-memory tree; **`ofw_alias_scan`**; phandle hash |
| **`rt_fdt_unflatten_single`** | Unflatten with explicit **`fdt`** pointer |
| **`rt_fdt_device_is_available`** | **`status`** on blob node (pre-unflatten) |

### Chosen / bootargs

| API | Role |
| --- | --- |
| **`rt_fdt_scan_chosen_stdout`** | **`stdout-path`** |
| **`rt_fdt_bootargs_select`** | Parse **`bootargs`** token |
| **`rt_ofw_bootargs_select`** | Same on unflattened tree |

### Early console

| API / macro | Role |
| --- | --- |
| **`RT_FDT_EARLYCON_EXPORT`** | Register **`rt_fdt_earlycon_id`** in linker section |
| **`rt_fdt_earlycon_output`** | Print before UART driver probe |
| **`rt_fdt_earlycon_kick`** | Hand off to real console |

### libfdt helpers

| API | Role |
| --- | --- |
| **`rt_fdt_read_number`**, **`rt_fdt_next_cell`** | Cell decoding |
| **`rt_fdt_translate_address`** | Address on raw blob |

---

## Memory and reserved regions

| Source | Effect |
| --- | --- |
| DTB **`/memreserve`** | **`rt_memblock_reserve_memory`** |
| **`/reserved-memory`** nodes | Validated **`reg`** (+ **`ranges`**) |
| **`rt_fdt_scan_initrd`** | Initrd carve-out |

Unflatten marks system nodes with **`RT_OFW_F_SYSTEM | RT_OFW_F_READLY`** so they are not platform devices.

---

## Builtin DTB

**`RT_USING_BUILTIN_FDT`** embeds **`RT_BUILTIN_FDT_PATH`**. Build flow: @ref page_device_dtc.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`rt_fdt_*` after unflatten** | Prefer **`rt_ofw_*`** for properties |
| Missing **`/cpus`** | **`RT_ASSERT`** in unflatten — BSP must supply |
| Memory scan skipped | Call **`scan_memory`** before allocator use |

## See also

- @ref page_device_ofw
- @ref page_device_ofw_platform
- @ref page_device_ofw_raw
- @ref page_device_dtc
