@page page_device_pic_core PIC core framework

# Core framework (`pic.c`, `pic_rthw.c`)

Registration, ISR attach, trap dispatch, and global IRQ control wrappers.

---

## `struct rt_pic` / `struct rt_pic_ops`

| `rt_pic_ops` | Role |
| --- | --- |
| **`irq_init` / `irq_finit`** | Controller-wide setup (called from **`rt_pic_irq_init`**) |
| **`irq_enable` / `irq_disable`** | Optional gate |
| **`irq_mask` / `irq_unmask`** | Mask line at hardware |
| **`irq_ack` / `irq_eoi`** | Acknowledge / end of interrupt |
| **`irq_map`** | **Allocate virtual IRQ** from hwirq + mode (required for OFW) |
| **`irq_parse`** | Decode **`#interrupt-cells`** into **`out_pirq`** (required for OFW) |
| **`irq_set_priority` / `irq_set_affinity` / `irq_set_triger_mode`** | Configuration |
| **`irq_send_ipi`** | SMP IPI |
| MSI: **`irq_alloc_msi`**, **`irq_compose_msi_msg`**, … | @ref page_device_pic_msi |
| **`flags`** | **`RT_PIC_F_IRQ_ROUTING`** — parent dispatches children in **`rt_pic_handle_isr`** |

---

## Trap path (root PIC)

Root PIC (CPU-facing) registers a **trap handler**:

```c
rt_pic_add_traps(my_root_handler, pic);
```

CPU exception → **`rt_pic_do_traps()`** → first handler returning **`RT_TRUE`**:

1. Read hwirq from hardware (e.g. GIC IAR in `pic-gicv2.c`)
2. Map to **`pirq`** (IPI vs SPI)
3. **`irq_ack`** → **`rt_pic_handle_isr(pirq)`** → **`irq_eoi`**

Child PICs without traps are reached via **cascade** or **dedicated parent ISR** (@ref page_device_pic_cascade).

---

## `rt_pic_handle_isr`

1. If **`children_nodes`** non-empty: for each child, **`irq_ack`**, recursive **`rt_pic_handle_isr(child)`**, **`irq_eoi`**
2. Call primary **`pirq->isr.action.handler(irq, param)`**
3. Call chained ISRs on **`pirq->isr.list`**

Used by root trap and by software demux (e.g. Rockchip PCIe legacy ISR).

---

## Attach / detach

```c
rt_err_t rt_pic_attach_irq(int irq, rt_isr_handler_t handler, void *uid,
        const char *name, int flags);
rt_err_t rt_pic_detach_irq(int irq, void *uid);
```

- **`irq`**: **virtual** global number
- First handler uses embedded **`pirq->isr`**; additional handlers malloc **`struct rt_pic_isr`** nodes
- **`rt_hw_interrupt_install`** in **`pic_rthw.c`** wraps **`rt_pic_attach_irq`**

---

## Global IRQ API

Thin wrappers: **`irq2pirq(irq)`** → **`pirq->pic->ops->…`**

```c
void rt_pic_irq_mask(int irq);
void rt_pic_irq_unmask(int irq);
void rt_pic_irq_eoi(int irq);
/* … priority, affinity, trigger mode, IPI … */
```

**`rt_hw_interrupt_mask` / `umask`** in arch code call these.

---

## Init refcount (`phye`-style pattern in phye.c — here init/power on PIC is per-op at device level)

For **`rt_phye`**-like refcount see phye; PIC uses **per-`pirq` ISR** and **init_count** only inside individual drivers.

PIC core **`rt_phye_init`** N/A — use **`irq_map`** once per DT line.

---

## `rt_pic_register` pattern (provider)

There is no single **`rt_pic_register`** — providers:

1. Embed **`struct rt_pic`** in driver private data
2. Set **`ops`**, **`priv_data`**
3. **`rt_pic_linear_irq`**
4. **`rt_ofw_data(np) = &pic`** (or **`rt_dm_dev_bind_fwdata`**)
5. Optional **`rt_pic_user_extends`**, **`rt_pic_add_traps`**

---

## See also

- @ref page_device_pic_irq_domain
- @ref page_device_pic_cascade
- @ref page_device_pic_ofw
