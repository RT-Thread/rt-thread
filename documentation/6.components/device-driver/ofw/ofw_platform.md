@page page_device_ofw_platform OFW platform enumeration

# Platform bus enumeration (`platform_ofw.c`)

Walk the unflattened tree and register **`struct rt_platform_device`** for driver **`probe`**. Core OFW APIs: @ref page_device_ofw_base.

Source: **`components/drivers/core/platform_ofw.c`**. Platform driver API: @ref page_device_platform.

---

## Probe order

**`INIT_PLATFORM_EXPORT(platform_ofw_device_probe)`**:

1. **`/clocks`** subtree (providers before consumers)
2. **`/`** root (depth-first)
3. **`/firmware`**
4. **`/chosen/simple-framebuffer`** (if present)

---

## Child walk

For each **available** child of **`parent_np`**:

| Skip when | Reason |
| --- | --- |
| **`np->dev` set** | Already instantiated |
| **`RT_OFW_F_SYSTEM` or `RT_OFW_F_READLY`** | Meta or bound node |
| No **`compatible`** and no real name | Anonymous container |

| **`compatible` in `platform_ofw_ids`** | Action |
| --- | --- |
| **`simple-bus`**, **`simple-mfd`**, **`isa`**, **`arm,amba-bus`** | Recurse **`platform_ofw_device_probe_once(np)`** first |
| Leaf | **`alloc_ofw_platform_device`** → **`rt_platform_device_register`** |

**`ofw_device_rename`**: **`reg`**-based name (`%lx.%.*s`) when decodable, else hierarchical path.

---

## `rt_platform_ofw_request`

```c
rt_err_t rt_platform_ofw_request(struct rt_ofw_node *np);
```

| State | Behavior |
| --- | --- |
| No **`np->dev`** | Create pdev, register (runs **`probe`**) |
| **`dev` without driver** | **`rt_bus_reload_driver_device`** |
| Probed | **`RT_EOK`** |

Call from consumers after **`rt_ofw_parse_phandle_cells`** when provider **`rt_ofw_data`** is NULL.

---

## Other APIs

| API | Role |
| --- | --- |
| **`rt_platform_ofw_device_probe_child`** | Register single child under non-root parent |
| **`rt_platform_ofw_free`** | Clear **`RT_OFW_F_PLATFORM`**, **`rt_ofw_node_put`**, free pdev |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Clock provider late | Ensure **`/clocks`** nodes probe first (built-in order) |
| No **`rt_platform_ofw_request`** | Provider never probes — phandle parse succeeds but **`rt_ofw_data`** NULL |
| Bus not in **`platform_ofw_ids`** | Children still register as leaf platform devices if **`compatible`** present |

## See also

- @ref page_device_ofw
- @ref page_device_ofw_boot
- @ref page_device_platform
- @ref page_device_bus
