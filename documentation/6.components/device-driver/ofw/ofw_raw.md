@page page_device_ofw_raw OFW raw FDT helpers

# Raw FDT editing (`raw.c`)

Optional **in-place** libfdt helpers for firmware, loaders, or tools that modify the blob **before** **`rt_fdt_unflatten`**. Runtime drivers normally use @ref page_device_ofw_base after unflatten.

Header: **`drivers/ofw_raw.h`**. Source: **`components/drivers/ofw/raw.c`**.

---

## When to use

| Use raw API | Use `rt_ofw_*` |
| --- | --- |
| Patch DTB in RAM pre-boot | Driver **`probe`** on live tree |
| Add **`/chosen`** properties from bootloader | Read **`reg` / `interrupts`** |
| Install initrd nodes | Platform enumeration |

---

## API highlights

| API / macro | Role |
| --- | --- |
| **`fdt_add_subnode_possible`** | Add child if space in blob |
| **`fdt_add_mem_rsv_possible`** | Add memory reserve entry |
| **`fdt_setprop_cstring`** | Set string property |
| **`fdt_setprop_cells`**, **`fdt_appendprop_cells`** | U32 cell arrays (endian-safe) |
| **`fdt_setprop_uxx`** | 8/16/32/64-bit property |
| **`fdt_getprop_u8` … `fdt_getprop_s32`** | Typed read on blob offset |
| **`fdt_io_addr_cells`**, **`fdt_io_size_cells`** | Cells on raw node offset |
| **`fdt_install_initrd`** | Add **`linux,initrd-*`** under **`chosen`** |

**`FDT_SIZE_MAX`**, **`FDT_PADDING_SIZE`** — growth limits when expanding tree.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Blob too small | Reserve padding at build time; check return codes |
| Edit after unflatten | Tree and blob may diverge — rebuild or only edit pre-unflatten |
| Endianness | Use **`fdt_setprop_cells`**, not raw **`fdt_setprop`** for integers |

## See also

- @ref page_device_ofw_boot
- @ref page_device_dtc
- libfdt: **`components/drivers/ofw/libfdt/`**
