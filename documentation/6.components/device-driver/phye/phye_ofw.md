@page page_device_phye_ofw Phye and device tree

# Device tree binding (`phye.c`)

Consumers reference PHY providers with standard graph properties. Requires **`RT_USING_OFW`**.

---

## Properties (consumer node)

| Property | Role |
| --- | --- |
| **`phys`** | Phandle list to PHY provider node(s) |
| **`#phy-cells`** | On **provider** — specifier length per entry |
| **`phy-names`** | Optional string ID per entry (for **`rt_phye_get_by_name`**) |

Example (SATA host):

```dts
ahci: sata@... {
    phys = <&sata_phy 0>;
    phy-names = "sata-phy";
};
```

---

## Resolution flow (`ofw_phye_get_by_index`)

```
  rt_ofw_parse_phandle_cells(np, "phys", "#phy-cells", index, &args)
       |
       |  args.data = provider rt_ofw_node *
       v
  rt_platform_ofw_request(provider_np)   /* probe provider if needed */
       |
       v
  phye = rt_ofw_data(provider_np)
       |
       v
  phye->ops->ofw_parse(phye, &args)     /* optional */
```

If **`ofw_parse`** fails, **`get_by_index`** returns **`rt_err_ptr(err)`**.

Provider platform driver must **`rt_phye_register`** in **`probe`** after **`rt_dm_dev_bind_fwdata`**.

---

## Provider node

| Element | Role |
| --- | --- |
| **`compatible`** | Selects PHY driver (SoC or generic) |
| **`#phy-cells`** | Usually `0` or mode/lane index |
| **`clocks` / `resets` / regulators** | Handled in provider **`probe`**, not by core |

Cell semantics are **driver-specific** — document in BSP binding and implement in **`ofw_parse`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Provider not probed | **`rt_platform_ofw_request`** before **`rt_ofw_data`** (core does this) |
| **`ofw_parse` omitted** | **`#phy-cells` ignored** — wrong mode if cells non-zero |
| Index / name mismatch | **`phy-names`** must align with **`phys`** order |
| Missing **`phys`** | **`get_by_index`** returns NULL — fail host **`probe`** |

## See also

- @ref page_device_phye_core
- @ref page_device_ofw_base
- @ref page_device_phye_provider
