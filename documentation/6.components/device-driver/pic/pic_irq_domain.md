@page page_device_pic_irq_domain PIC virtual IRQ domain

# Virtual IRQ allocation (`pic.c`)

How RT-Thread turns many interrupt controllers into one **global IRQ space** drivers can use.

---

## Global table `_pirq_hash[]`

- Size: **`MAX_HANDLERS`** (Kconfig, default 256)
- Each slot is a **`struct rt_pic_irq`** with **`irq`**, **`hwirq`**, **`pic`**, ISR list, optional **`parent`**

Allocation pointer **`_pirq_hash_idx`**:

| Region | Indices | Purpose |
| --- | --- | --- |
| **IPI** | `0 … RT_MAX_IPI-1` | SMP inter-processor interrupts |
| **PIC domains** | `_pirq_hash_idx` upward | Each **`rt_pic_linear_irq`** takes a contiguous block |

**`rt_pic_config_ipi`** uses fixed low indices. Peripheral IRQs come from **`rt_pic_config_irq`**.

---

## Per-controller window

**`rt_pic_linear_irq(pic, irq_nr)`** (under global lock):

```c
pic->irq_start = _pirq_hash_idx;   /* first virtual IRQ for this PIC */
pic->irq_nr    = irq_nr;
pic->pirqs     = &_pirq_hash[pic->irq_start];
_pirq_hash_idx += irq_nr;
```

Example (GICv2 with 988 SPIs):

- **`irq_nr = max_irq + 1 - 32`** (SGI/PPI handled separately)
- Virtual IRQs might be **`[RT_MAX_IPI, RT_MAX_IPI + irq_nr)`**
- **`irq_index = hwirq - 32`** for SPI hwirq 32 → index 0

---

## Mapping API

```c
int rt_pic_config_irq(struct rt_pic *pic, int irq_index, int hwirq);
int rt_pic_config_ipi(struct rt_pic *pic, int ipi_index, int hwirq);
```

| Input | Meaning |
| --- | --- |
| **`irq_index`** | Offset within this PIC's window |
| **`hwirq`** | Hardware ID in that controller |
| **Return value** | **Global virtual IRQ** = **`pic->irq_start + irq_index`** |

Lookup:

| API | Returns |
| --- | --- |
| **`rt_pic_find_irq(pic, irq_index)`** | **`&pic->pirqs[irq_index]`** |
| **`rt_pic_find_pirq(pic, virtual_irq)`** | **`pirq`** if **`virtual_irq`** in range |
| **`irq2pirq(irq)`** | Global lookup for **`rt_pic_irq_*`** wrappers |

---

## `struct rt_pic_irq` fields

| Field | Role |
| --- | --- |
| **`irq`** | Virtual IRQ (global); **`-1`** = slot unused |
| **`hwirq`** | Controller-specific line |
| **`mode`** | Edge/level (`RT_IRQ_MODE_*`) |
| **`pic`** | Owning **`struct rt_pic *`** |
| **`parent`** | Cascade parent **`pirq`** |
| **`children_nodes`** | Routed children if **`RT_PIC_F_IRQ_ROUTING`** |
| **`isr`** | Handler chain |

---

## IPI vs device IRQ

| | IPI | Device IRQ |
| --- | --- | --- |
| Config | **`rt_pic_config_ipi`** | **`rt_pic_config_irq`** or **`irq_map`** |
| Affinity | All CPUs set in **`config_ipi`** | Per **`irq_set_affinity`** |
| Dispatch | GIC trap reads hwirq &lt; 16 → **`rt_pic_find_ipi`** | hwirq ≥ 32 → **`rt_pic_find_irq`** |

---

## Debug

With MSH: **`list_irq`** / **`list_irq all`** ( **`pic.c`** ) dumps virtual IRQ, PIC name, hwirq, mode, handlers.

**`rt_pic_linear_irq`** comment: intended for production PIC registration; **`rt_pic_cancel_irq`** only for failed init teardown.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **`MAX_HANDLERS` too small** | Sum all PIC **`irq_nr`** + IPI + headroom |
| Use hwirq as **`rt_pic_attach_irq` argument** | Always use **virtual `irq`** from **`rt_dm_dev_get_irq`** / **`irq_map`** |
| Re-**`config_irq`** on busy slot | **`config_pirq`** asserts empty ISR lists if PIC changes |

## See also

- @ref page_device_pic_core
- @ref page_device_pic_ofw
