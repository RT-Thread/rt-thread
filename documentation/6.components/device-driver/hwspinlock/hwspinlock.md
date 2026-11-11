@page page_device_hwspinlock Hardware spinlock

# Hardware spinlock (hwspinlock)

RT-Thread **hwspinlock** (`components/drivers/hwspinlock/`) models **SoC hardware mutex registers** shared across **heterogeneous CPUs** (AMP), **remote processors**, or firmware—not the same as a single-OS **`rt_spinlock`**. A **bank** (one controller IP) exports many **`rt_hwspinlock`** instances; consumers acquire through **`rt_hwspin_*`** or device-tree **`hwlocks`**.

Public API: **`components/drivers/include/drivers/hwspinlock.h`**. DM types: **`components/drivers/hwspinlock/hwspinlock_dm.h`**. Core: **`components/drivers/hwspinlock/hwspinlock.c`**.

SoC-specific controllers are added under **`SOC_DM_HWSPINLOCK_DIR`** in the BSP Kconfig.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required parent |
| **`RT_USING_OFW`** | Required — phandle parsing for **`hwlocks`** |
| **`RT_USING_HWSPINLOCK`** | Build **`hwspinlock.c`**; selects **`RT_USING_ADT`** / **`RT_USING_ADT_REF`** |
| **`SOC_DM_HWSPINLOCK_DIR`** | BSP adds platform drivers (e.g. mailbox companion lock IP) |

---

## Architecture

```
  SoC hwspinlock controller (platform driver)
        |
        |  hwspinlock_bank_alloc + fill ops
        |  rt_hwspinlock_bank_register(bank)
        v
  Global bank list + rt_ofw_data(provider_np) = bank
        |
        |  Consumer: hwlocks = <&hwlock0 3>; hwlock-names = "mbox";
        v
  rt_ofw_get_hwspinlock_by_name(np, "mbox")
        |
        v
  rt_hwspin_lock_timeout_irqsave(hwlock, ms, &flags)
        ... shared MMIO / mailbox ...
  rt_hwspin_unlock_irqrestore(hwlock, &flags)
        |
        v
  rt_hwspinlock_put(hwlock)   /* release allocation, not unlock */
```

| Object | Role |
| --- | --- |
| **`struct rt_hwspinlock_bank`** | One controller: **`dev`**, **`ops`**, **`base_id`**, **`locks[]`** |
| **`struct rt_hwspinlock`** | One hardware lock index; per-lock software **`rt_spinlock`** guards metadata |
| **`struct rt_hwspinlock_ops`** | **`trylock`**, **`unlock`**, optional **`relax`** (WFE / yield in busy-wait) |

**Two layers of locking**:

1. **Software** **`hwlock->lock`** — protects the bank’s bookkeeping while calling ops (optional **irqsave** via **`out_irq_level`**).
2. **Hardware** **`ops->trylock/unlock`** — the actual cross-core exclusion in silicon.

**`rt_hw_dmb()`** is issued after acquire and before release for visibility ordering.

---

## Provider: register a bank

```c
struct my_hwlock_drv {
    struct rt_hwspinlock_bank *bank;
};

static rt_err_t my_hwlock_trylock(struct rt_hwspinlock *hwlock)
{
    int id = hwspinlock_find_id(hwlock);
    /* read lock register: RT_EOK or -RT_EBUSY */
}

static void my_hwlock_unlock(struct rt_hwspinlock *hwlock)
{
    int id = hwspinlock_find_id(hwlock);
    /* write release */
}

static void my_hwlock_relax(struct rt_hwspinlock *hwlock)
{
    rt_hw_cpu_relax();  /* or WFE per TRM */
}

static const struct rt_hwspinlock_ops my_hwlock_ops = {
    .trylock = my_hwlock_trylock,
    .unlock  = my_hwlock_unlock,
    .relax   = my_hwlock_relax,
};

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct my_hwlock_drv *priv;
    int num_locks = 32;

    priv->bank = hwspinlock_bank_alloc(priv, num_locks);
    priv->bank->dev = &pdev->parent;
    priv->bank->ops = &my_hwlock_ops;
    priv->bank->base_id = 0;   /* global ID offset for DT indices */
    priv->bank->locks_nr = num_locks;

    return rt_hwspinlock_bank_register(priv->bank);
}
```

**`rt_hwspinlock_bank_register`** requirements:

- **`bank`**, **`bank->dev`**, **`bank->ops`**, **`locks_nr > 0`**
- Initializes each **`locks[i].bank`**, **`used = false`**, software spinlock
- Links bank on global list; **`rt_dm_dev_bind_fwdata(dev, NULL, bank)`** for OFW lookup

**`rt_hwspinlock_bank_unregister`**: succeeds only when **`rt_ref_read(&bank->ref) == 1`** (no outstanding **`get`** references)—else **`-RT_EBUSY`**.

---

## Consumer API

### Lock / unlock

| API | IRQ save | Behavior |
| --- | --- | --- |
| **`rt_hwspin_trylock_raw`** | optional **`out_irq_level`** | One try; **`-RT_EBUSY`** if hardware busy |
| **`rt_hwspin_lock_timeout_raw`** | optional | Retries until success or **`timeout_ms`** → **`-RT_ETIMEOUT`**; calls **`ops->relax`** while waiting |
| **`rt_hwspin_unlock_raw`** | restore if provided | **`ops->unlock`** then release software lock |

Convenience inlines: **`rt_hwspin_trylock`**, **`rt_hwspin_trylock_irqsave`**, **`rt_hwspin_lock_timeout`**, **`rt_hwspin_lock_timeout_irqsave`**, matching **`unlock`** variants.

**Rules**:

- **Do not sleep** while holding the hardware lock (same as spinlocks).
- **Pair lock/unlock** on the same core that acquired the hardware lock (AMP contract).
- **`unlock` does not clear `used`** — allocation is separate from locking.

### Allocate a lock handle

| API | Role |
| --- | --- |
| **`rt_hwspinlock_get()`** | First free lock in any registered bank |
| **`rt_hwspinlock_get_by_index(dev, index)`** | Via consumer’s OFW node |
| **`rt_hwspinlock_get_by_name(dev, name)`** | Match **`hwlock-names`** |
| **`rt_ofw_get_hwspinlock_by_index(np, index)`** | Parse **`hwlocks`** + **`#hwlock-cells`** |
| **`rt_ofw_get_hwspinlock_by_name(np, name)`** | Index from **`hwlock-names`** |
| **`rt_hwspinlock_put(hwlock)`** | Clear **`used`**, **`rt_ref_put`** on bank — **does not unlock** |

**OFW parse** (`hwspinlock.c`):

```dts
hwspinlock: hwspinlock@... {
    compatible = "vendor,hwspinlock";
    #hwlock-cells = <1>;
};

remote_ip: device@... {
    hwlocks = <&hwspinlock 5>;
    hwlock-names = "ipc";
};
```

1. **`rt_ofw_parse_phandle_cells(np, "hwlocks", "#hwlock-cells", index, &args)`**
2. **`rt_platform_ofw_request(bank_np)`** if provider not probed
3. **`bank = rt_ofw_data(bank_np)`**; lock id = **`bank->base_id + args.args[0]`** (requires **`args_count == 1`**)
4. Marks **`hwlock->used`** and **`rt_ref_get(&bank->ref)`**

---

## When to use hwspinlock vs `rt_spinlock`

| Use **hwspinlock** when… | Use **`rt_spinlock`** when… |
| --- | --- |
| **Another CPU / DSP / M-core** can touch the same resource without sharing RT-Thread. | Only RT-Thread SMP CPUs coordinate, all under one OS. |
| TRM or firmware defines **hardware lock index** before mailbox/shared SRAM access. | Exclusion inside one kernel with IRQ disable or SMP spinlock is enough. |
| **Mailbox / rpmsg** handshake doc lists lock IDs. | Short critical section on local driver private data. |

Typical scenarios: **AMP**, **heterogeneous multicore**, **CPU ↔ remoteproc** register blocks, **shared message SRAM** between Linux and RT-Thread.

---

## Integration with mailbox / rpmsg

Agree on a **fixed lock index map** in DTS and in remote firmware (e.g. lock **0** = mailbox header, lock **1** = virtio queue). See @ref page_device_mailbox and @ref page_device_rpmsg.

Suggested **lock order** (document in BSP): acquire **hwspinlock before** ringing doorbell / sending mailbox, release **after** MMIO writes visible—avoid holding hwlock while waiting on a blocking IPC call from the other side.

---

## Engineer checklist

1. **Provider**: **`hwspinlock_bank_alloc`**, implement **`trylock`/`unlock`/`relax`**, set **`base_id`** consistently with DT indices, **`rt_hwspinlock_bank_register`**.
2. **Consumer**: **`rt_ofw_get_hwspinlock_by_name`** in **`probe`**; **`put`** in **`remove`**.
3. **Critical section**: **`lock_timeout_irqsave`** → short MMIO → **`unlock_irqrestore`**.
4. **Teardown**: ensure all locks **unlocked** and **`put`** before **`bank_unregister`**.

---

## Pitfalls

- **`rt_hwspinlock_put` without unlock** — next **`get`** may see hardware still owned by this or another core.
- **Wrong `#hwlock-cells` or index** — **`rt_ofw_get_*`** returns **`RT_ENOSYS`** or wrong slot → silent corruption.
- **Sleep while holding hwlock** — deadlock remote core or violate **`relax`** busy-wait assumptions.
- **Recursive acquire** — not supported (hardware + software locks).
- **Cross-core unlock** — undefined on most IPs; always unlock on acquirer CPU.
- **Deadlock with mailbox**: ISR holds lock A, thread waits on IPC that needs A on other core—define global lock ordering.
- **`unregister` with active refs** — **`-RT_EBUSY`**; remote side may still hold hardware lock even if ref count looks idle.

---

## See also

- `components/drivers/include/drivers/hwspinlock.h`
- `components/drivers/hwspinlock/hwspinlock_dm.h`, `hwspinlock.c`
- @ref page_device_dm — **`rt_dm_dev_bind_fwdata`**, **`rt_platform_ofw_request`**
- @ref page_device_ofw — phandle / **`#hwlock-cells`**
- @ref page_device_mailbox, @ref page_device_rpmsg
- @ref page_device_platform
