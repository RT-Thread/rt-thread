@page page_device_numa NUMA helpers

# NUMA (non-uniform memory access)

**`components/drivers/core/numa.c`** provides lightweight helpers to map **CPUs**, **devices**, and **physical addresses** to NUMA nodes on multi-socket / multi-die platforms. The code is **not** a full NUMA allocator—it parses device-tree tables when enabled and exposes three query APIs in **`drivers/core/numa.h`**.

Built with **`RT_USING_DM`** (always linked from **`core/SConscript`**). Runtime tables are populated only when **`RT_USING_OFW`** and boot **`numa=on`** are active.

---

## Enabling NUMA

| Requirement | Detail |
| --- | --- |
| **`RT_USING_DM`** | **`numa.c`** in core drivers |
| **`RT_USING_OFW`** | **`INIT_CORE_EXPORT(numa_ofw_init)`** parses DT |
| **Boot argument** | **`numa=on`** in **`chosen/bootargs`** (exact string after **`numa=`**) |

If **`numa=`** is missing or not **`on`**, **`numa_enabled`** stays false and APIs behave as **single-node fallback** (see below).

---

## Initialization (`numa_ofw_init`)

```
  bootargs: numa=on
        |
        v
  For each CPU node: read numa-node-id → cpu_numa_map[cpuid]
        |
        v
  For each memory@ node with numa-node-id:
        record [start, end) per reg entry on numa_memory_nodes list
```

| DT source | Stored as |
| --- | --- |
| **CPU** nodes | **`cpu_numa_map[i]`** = **`numa-node-id`** ( **`i`** = enumeration order, capped at **`RT_CPUS_NR`** ) |
| **`device_type = "memory"`** + **`numa-node-id`** | Linked **`struct numa_memory`** ranges (**`start`/`end`** physical) |

There is **no** hot-plug update—tables are fixed at core init.

---

## API

```c
int rt_numa_cpu_id(int cpuid);
int rt_numa_device_id(struct rt_device *dev);
rt_err_t rt_numa_memory_affinity(rt_uint64_t phy_addr, rt_bitmap_t *out_affinity);
```

### `rt_numa_cpu_id`

| Condition | Return |
| --- | --- |
| NUMA disabled | **`-RT_ENOSYS`** |
| **`cpuid >= RT_CPUS_NR`** | **`-RT_EINVAL`** |
| Otherwise | **`cpu_numa_map[cpuid]`** (node id from DT, or **`-RT_ENOSYS`** if never set) |

### `rt_numa_device_id`

| Condition | Return |
| --- | --- |
| NUMA disabled | **`(int)(uint32_t)-RT_ENOSYS`** (legacy cast in source) |
| **`numa-node-id` property present** on **`dev->ofw_node`** | Parsed **u32** node id |
| Property missing / read error | Prop-read error code as **int** |

Use on **`rt_device`** objects that carry an OFW node (PCI, platform, etc.).

### `rt_numa_memory_affinity`

Given a **physical address**, fills **`out_affinity`** ( **`RT_BITMAP_LEN(RT_CPUS_NR)`** words) with CPUs whose **`rt_numa_cpu_id`** matches the memory region's node.

| Condition | Return |
| --- | --- |
| **`out_affinity == NULL`** | **`-RT_EINVAL`** |
| NUMA disabled | Sets **CPU 0** only, **`RT_EOK`** |
| Address inside a recorded range | CPUs on same node set in bitmap, **`RT_EOK`** |
| No matching range | **`-RT_EEMPTY`** |

Typical use: pick an IRQ affinity mask or thread CPU set for DMA buffers allocated at **`phy_addr`**.

---

## Device tree examples

### Bootargs

```dts
/ {
    chosen {
        bootargs = "numa=on";
    };
};
```

### CPUs and memory

```dts
cpu@0 {
    device_type = "cpu";
    reg = <0>;
    numa-node-id = <0>;
};

cpu@100 {
    device_type = "cpu";
    reg = <0x100>;
    numa-node-id = <1>;
};

memory@0 {
    device_type = "memory";
    reg = <0x0 0x80000000>;
    numa-node-id = <0>;
};

memory@80000000 {
    device_type = "memory";
    reg = <0x80000000 0x80000000>;
    numa-node-id = <1>;
};
```

### Device node

```dts
nvme@1,0 {
    /* ... */
    numa-node-id = <0>;
};
```

---

## Integration in-tree

| Consumer | Usage |
| --- | --- |
| **NVMe** | **`INIT_SECONDARY_CPU_EXPORT(nvme_queue_affinify_fixup)`** sets per-queue IRQ affinity (@ref page_device_nvme_dm) |
| **Future DMA / drivers** | Call **`rt_numa_memory_affinity`** when pinning buffers or IRQs |

No other in-tree callers are required for NUMA to be useful—BSPs can query node ids when placing shared memory for AMP.

---

## When to use

| Use **`rt_numa_*`** when… | Skip when… |
| --- | --- |
| BSP documents multiple nodes and **`numa=on`**. | Single RAM bank; **`rt_numa_cpu_id`** always maps to one node. |
| You pin **IRQ affinity** or **thread CPU** near PCIe/DMA memory. | All devices are local and symmetric. |
| Cross-node latency matters for storage/net. | Firmware hides NUMA (uniform UMA). |

Treat node ids as **hints**—hardware may still allow remote access.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Forgot `numa=on`** | All APIs behave as UMA (memory affinity → CPU 0 only). |
| **CPU map vs logical id** | **`cpu_numa_map`** indexed by **enumeration order**, not necessarily **`rt_hw_cpu_id()`** unless DT order matches—verify BSP. |
| **`rt_numa_device_id` without property** | Returns error from prop read—not **0**. |
| **Address not in table** | **`rt_numa_memory_affinity`** → **`-RT_EEMPTY`** — extend DT memory nodes or fall back. |
| **No hotplug** | Memory map changes are not tracked after boot. |

---

## See also

- @ref page_device_nvme_dm — IRQ affinity fixup
- @ref page_device_dma
- @ref page_device_ofw
- `components/drivers/include/drivers/core/numa.h`
- `components/drivers/core/numa.c`
