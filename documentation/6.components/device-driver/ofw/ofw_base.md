@page page_device_ofw_base OFW nodes and properties

# OFW core (`base.c`, `ofw.c`)

Node tree, properties, phandles, matching, stubs, and **`rt_ofw_parse_object`**. Boot: @ref page_device_ofw_boot. IO: @ref page_device_ofw_io. IRQ: @ref page_device_ofw_irq.

Headers: **`drivers/ofw.h`**. Sources: **`components/drivers/ofw/base.c`**, **`ofw.c`**.

---

## Core types

| Type | Role |
| --- | --- |
| **`struct rt_ofw_prop`** | Property list entry: **`name`**, **`length`**, **`value`** |
| **`struct rt_ofw_node`** | **`full_name`**, **`phandle`**, **`props`**, tree links, **`ref`**, **`flags`**, **`rt_data`**, optional **`dev`** |
| **`struct rt_ofw_cell_args`** | Parsed phandle + specifier (**`args[]`**, max **`RT_OFW_MAX_CELL_ARGS`**) |
| **`struct rt_ofw_node_id`** | **`compatible`** / **`name`** / **`type`** match table row |
| **`struct rt_ofw_stub`** | Early probe: **`ids`**, **`handler(np, id)`** |

### Node flags (`RT_OFW_F_*`)

| Flag | Meaning |
| --- | --- |
| **`RT_OFW_F_SYSTEM`** | Meta node (`/`, `/cpus`, `/chosen`, …) — platform walk skips |
| **`RT_OFW_F_READLY`** | Stub or driver already bound |
| **`RT_OFW_F_PLATFORM`** | **`rt_platform_device`** created |
| **`RT_OFW_F_OVERLAY`** | From applied DT overlay |

APIs: **`rt_ofw_node_set_flag`**, **`rt_ofw_node_test_flag`**, **`rt_ofw_node_clear_flag`**.

---

## Lifetime

| API | Role |
| --- | --- |
| **`rt_ofw_node_get` / `rt_ofw_node_put`** | Reference count on **`np`** |
| **`rt_ofw_node_destroy`** | Tear down subtree when applicable |
| **`rt_ofw_data(np)`** | Driver private pointer in **`np->rt_data`** |

---

## Finding nodes

| API | Role |
| --- | --- |
| **`rt_ofw_find_node_by_path`** | Absolute path (`/soc/uart@1000`) |
| **`rt_ofw_find_node_by_compatible`** | DFS from **`from`** (**`RT_NULL`** = whole tree) |
| **`rt_ofw_find_node_by_ids` / `_r`** | Match **`rt_ofw_node_id`** table |
| **`rt_ofw_find_node_by_phandle`** | Resolve numeric phandle |
| **`rt_ofw_find_node_by_name`**, **`_by_prop`**, **`_by_tag`**, **`_by_type`** | Other keys |
| **`rt_ofw_get_parent`**, **`rt_ofw_get_next_*`** | Walk tree |
| **`rt_ofw_foreach_*` macros** | Prefer macros in **`ofw.h`** over manual sibling loops |

**Availability**: **`rt_ofw_node_is_available`** (**`status`**), **`rt_ofw_machine_is_compatible`** (root).

---

## Properties

| API | Role |
| --- | --- |
| **`rt_ofw_get_prop`** | Find property by name |
| **`rt_ofw_prop_read_raw`** | Blob + length |
| **`rt_ofw_prop_read_u8/u16/u32/s32/u64/string/bool`** | Typed index 0 |
| **`rt_ofw_prop_read_*_index`**, **`*_array_index`** | Multi-element |
| **`rt_ofw_prop_count_of_u32`** (etc.) | Element count |
| **`rt_ofw_append_prop`** | Runtime append (rare) |

---

## Phandles

| API | Role |
| --- | --- |
| **`rt_ofw_parse_phandle`** | Single phandle property by index |
| **`rt_ofw_parse_phandle_cells`** | List + **`#*-cells`** → **`rt_ofw_cell_args`** |
| **`rt_ofw_count_phandle_cells`** | Entry count in list |
| **`rt_ofw_parse_object`** | Find named object in composite **`rt_ofw_data`** |

**`ofw.c`** registers **`#clock-cells`**, **`#reset-cells`**, **`#power-domain-cells`** object layouts when those subsystems are enabled.

---

## Matching and stubs

| API / macro | Role |
| --- | --- |
| **`rt_ofw_node_match`**, **`rt_ofw_prop_match`** | Match **`compatible`** against **`rt_ofw_node_id[]`** |
| **`RT_OFW_STUB_EXPORT`** | Link stub into **`.rt_ofw_data.stub.*`** |
| **`rt_ofw_stub_probe_range`** | Run stubs on a node (class ranges via **`RT_OFW_STUB_RANGE_EXPORT`**) |

Used by early serial, hwcache, and other non-platform bindings.

---

## Aliases and CPU

| API | Role |
| --- | --- |
| **`rt_ofw_get_alias_node`**, **`rt_ofw_get_alias_id`** | **`/aliases`** resolution |
| **`rt_ofw_get_cpu_node`**, **`rt_ofw_foreach_cpu_node`** | CPU nodes under **`/cpus`** |
| **`rt_ofw_get_cpu_id`**, **`rt_ofw_get_cpu_hwid`** | MPIDR / hardware ID |
| **`rt_ofw_map_id`** | Generic **`*-map`** / **`*-map-mask`** lookup |

**`ofw_alias_scan`** runs during unflatten (**`base.c`**).

---

## Console and debug

| API | Role |
| --- | --- |
| **`rt_ofw_console_setup`** | Console from **`/chosen`** |
| **`rt_ofw_node_dump_dts`** | Print subtree as DTS-like text (**`RT_USING_CONSOLE`**) |

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Leaked **`np`** | Always **`put`** after **`get`** |
| Wrong phandle index | Check **`rt_ofw_count_phandle_cells`** and **`*-names`** |
| **`compatible` order** | Most specific first in driver **`ids[]`** |
| **`rt_ofw_data` before probe** | **`rt_platform_ofw_request`** on provider |

## See also

- @ref page_device_ofw
- @ref page_device_ofw_platform
- @ref page_device_ofw_io
- @ref page_device_ofw_irq
