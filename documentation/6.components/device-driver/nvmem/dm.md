@page page_device_nvmem_dm NVMEM device model (DM)

# NVMEM under `RT_USING_DM`

**`RT_USING_NVMEM`** builds **`nvmem.c`** only. **Provider** drivers register **`struct rt_nvmem_device`** and set **`rt_ofw_data(provider_np)`**. **Consumers** parse **`nvmem-cells`** phandles.

API: @ref page_device_nvmem. Sources: **`nvmem.c`**, **`nvmem.h`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required |
| **`RT_USING_OFW`** | Required |
| **`RT_USING_PIN`** | Optional **`wp`** GPIO |
| **`RT_USING_NVMEM`** | Core; selects **`RT_USING_ADT_REF`** |
| **`SOC_DM_NVMEM_DIR`** | BSP OTP/eFuse/EEPROM drivers |

No **`rt_bus`** — provider **`reg_read`/`reg_write`** + OFW lookup only.

---

## Architecture

```
  BSP provider (efuse/otp/eeprom)
        | rt_nvmem_device_register, rt_ofw_data = ndev
        v
  Consumer: nvmem-cells = <&provider N>;
        v
  rt_nvmem_get_cell_by_name → rt_nvmem_cell_read/write
        v
  rt_nvmem_put_cell
```

---

## Provider DT

```dts
efuse: efuse@110000 {
    compatible = "vendor,soc-efuse";
    reg = <0x110000 0x1000>;
    #address-cells = <1>;
    #size-cells = <1>;
    #nvmem-cell-cells = <1>;
    read-only;

    mac@0 { reg = <0x00 0x06>; };
};
```

| Property | Role |
| --- | --- |
| **`#nvmem-cell-cells`** | Usually **1** — phandle arg = cell index |
| **`read-only`** | Forces read-only at register |
| **`wp`** | Write-protect GPIO (unless **`ignore_wp`**) |

---

## Consumer DT

```dts
gmac: ethernet@0 {
    nvmem-cells = <&efuse 0>;
    nvmem-cell-names = "mac-address";
};
```

**`ofw_nvmem_get_cell`** order:

1. **`rt_ofw_data(cell_np)`** if cached
2. Match **`append_cell`** static list by index/id
3. Allocate dynamic cell from child **`reg`** (**`offset`**, **`bytes`**)

Dynamic cells are **`free_able`** and removed on last **`put_cell`**.

---

## Provider checklist

1. Implement **`reg_read`**; **`reg_write`** only if programmable.
2. Set **`size`**, **`parent.ofw_node`**, callbacks.
3. **`rt_nvmem_device_register`**.
4. Optional **`append_cell`** for fixed index/id layouts.
5. **`remove`**: all **`put_cell`**, then **`unregister`** when ref is 1.
6. Add driver under **`SOC_DM_NVMEM_DIR`**.

---

## Bit-packed cells

**`bit_offset`** / **`nbits`** on **`struct rt_nvmem_cell`**: core masks after byte read; write merges into existing bytes. Prefer byte-aligned **`reg = <offset length>`**; validate parsing in **`nvmem.c`** or use **`append_cell`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Provider not probed | **`rt_platform_ofw_request`** first |
| **`#nvmem-cell-cells` mismatch** | Match provider binding |
| Concurrent OTP | Serialize in **`reg_read`/`reg_write`** |
| **`unregister` EBUSY** | Release all cell refs |

---

## See also

- @ref page_device_nvmem
- @ref page_device_iio_dm
- @ref page_device_ofw