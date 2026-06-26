@page page_device_power_domain Power domain

# Power domain (`rt_dm_power_domain`)

Header: **`components/drivers/include/drivers/core/power_domain.h`**. Core: **`components/drivers/core/power_domain.c`**.

A **power domain** models a switchable SoC power island (GPU block, USB PHY, display cluster, …). Consumers reference domains in DT via **`power-domains`**; the **provider** driver registers **`struct rt_dm_power_domain`** (or a **proxy**) and implements **`power_on` / `power_off`**.

This is **not** system shutdown (@ref page_device_dm_power) and **not** a regulator rail (@ref page_device_regulator).

In-tree provider example: **`components/drivers/pmdomain/pm-domain-scmi.c`** (SCMI **`genpd`**).

---

## End-to-end flow

### Consumer (device with `power-domains` in DT)

```
platform_probe (platform.c)
        |
        v
rt_dm_power_domain_attach(dev, RT_TRUE)
        |
        +-- Parse first phandle in "power-domains" (index 0 only in attach)
        +-- Resolve provider rt_ofw_data → domain or proxy->ofw_parse()
        +-- domain->attach_dev(domain, dev) [optional]
        +-- if on: rt_dm_power_domain_power_on(domain)
        |
        v
pdrv->probe(pdev)    /* MMIO safe after domain on */
```

On **remove/shutdown** / failed probe:

```
rt_dm_power_domain_detach(dev, RT_TRUE)   /* optional power_off */
```

**`-RT_EEMPTY`**: no **`power-domains`** property — @ref page_device_platform treats this as OK.

### Provider (controller / firmware)

```
Driver probe (platform / SCMI)
        |
        v
Per domain: fill power_on, power_off [, attach_dev, detach_dev]
        |
        v
rt_dm_power_domain_register(domain)
        |
        +-- For DT phandle resolution: rt_ofw_data(provider_np) = domain
        |     OR proxy + rt_dm_power_domain_proxy_ofw_bind(np)
        |
        v
Consumer attach / get_by_index → power_on when ref transitions 0→1 usage
```

---

## Device tree

**Consumer:**

```dts
gpu@0x10000000 {
    compatible = "vendor,gpu";
    reg = <0x10000000 0x10000>;
    power-domains = <&pd_gpu>;
    /* optional: */
    power-domain-names = "core";
};
```

| Property | Role |
| --- | --- |
| **`power-domains`** | Phandle(s) to provider; cells per **`#power-domain-cells`** |
| **`power-domain-names`** | Maps names to index for **`rt_dm_power_domain_get_by_name`** |

**Provider** node must expose **`#power-domain-cells`** and bind **`rt_ofw_data`** to either:

| `rt_ofw_data` object name | Type |
| --- | --- |
| **`PMD`** (`RT_POWER_DOMAIN_OBJ_NAME`) | Direct **`struct rt_dm_power_domain`** |
| **`PMP`** (`RT_POWER_DOMAIN_PROXY_OBJ_NAME`) | **`struct rt_dm_power_domain_proxy`** with **`ofw_parse`** |

OFW core registers these in **`ofw.c`** object table.

---

## Registering a provider (important)

### Direct domain

```c
struct my_pd {
    struct rt_dm_power_domain domain;
    void __iomem *regs;
};

static rt_err_t my_pd_power_on(struct rt_dm_power_domain *domain)
{
    struct my_pd *pd = rt_container_of(domain, struct my_pd, domain);
    /* enable island — may sleep (I2C/SCMI/MMIO) */
    return RT_EOK;
}

static rt_err_t my_pd_power_off(struct rt_dm_power_domain *domain)
{
    ...
    return RT_EOK;
}

static rt_err_t my_pd_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct my_pd *pd = rt_calloc(1, sizeof(*pd));

    pd->domain.dev = dev;
    pd->domain.power_on = my_pd_power_on;
    pd->domain.power_off = my_pd_power_off;

    rt_dm_power_domain_register(&pd->domain);
    rt_ofw_data(dev->ofw_node) = &pd->domain;   /* object name becomes "PMD" */

    return RT_EOK;
}
```

**`rt_dm_power_domain_register`**: initializes lists, **`ref`**, spinlock — does **not** touch hardware.

### Proxy (multiple domains per node)

When one DT node represents many domains (SCMI, generic genpd):

```c
static struct rt_dm_power_domain *my_proxy_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    return &domains[args->args[0]];   /* cell index selects domain */
}

/* probe: register each domain, then */
proxy->ofw_parse = my_proxy_parse;
rt_dm_power_domain_proxy_ofw_bind(proxy, provider_ofw_node);
```

Reference: **`scmi_pm_domain_probe`** — registers **`num_domains`** entries, binds proxy on SCMI device node.

### Child domains

```c
rt_dm_power_domain_register_child(parent, child);
```

Sets **`child->parent_domain`**. **`power_on(parent)`** recursively powers on children listed in **`parent->child_nodes`** (BSP must link children into that list if hierarchy is used). **`unregister_child`** removes the child when the parent is idle.

---

## Consumer API

| API | Role |
| --- | --- |
| **`rt_dm_power_domain_attach(dev, on)`** | Link **`dev`** to **first** **`power-domains`** entry; **`on==RT_TRUE`** → **`power_on`** |
| **`rt_dm_power_domain_detach(dev, off)`** | Unlink; **`off==RT_TRUE`** → **`power_off`** |
| **`rt_dm_power_domain_get_by_index(dev, index)`** | Resolve domain pointer (no refcount change in **`put`** today) |
| **`rt_dm_power_domain_get_by_name(dev, name)`** | Uses **`power-domain-names`** |
| **`rt_dm_power_domain_put(domain)`** | Currently no-op success — hold domain via attach lifecycle |
| **`rt_dm_power_domain_power_on/off(domain)`** | Explicit on/off with **`ref`** counting |

### Reference counting

- **`rt_ref_init`**: domain starts at refcount **1** (idle / registered).
- **`power_on`**: if **`ref == 1`**, calls hardware **`power_on`**, then **`ref_get`**.
- **`power_off`**: **`ref_put`**; when **`ref` returns to 1**, calls hardware **`power_off`**.

Multiple consumers should share one domain through **`attach`** + refcount, not duplicate **`power_on`** without coordination.

### Manual use in driver

Usually **unnecessary** — platform bus already calls **`attach(dev, RT_TRUE)`**.

Extra domains (index > 0):

```c
struct rt_dm_power_domain *pd = rt_dm_power_domain_get_by_index(dev, 1);
if (pd)
    rt_dm_power_domain_power_on(pd);
```

**`attach` only handles index 0** (see comment in **`power_domain.c`**).

---

## Optional callbacks

| Callback | Role |
| --- | --- |
| **`attach_dev` / `detach_dev`** | Provider notified when a consumer links (clock/regulator coordination) |
| **`pirv`** | Provider private pointer (upstream spelling) |

---

## Platform bus integration

From **`platform_probe`**:

```c
err = rt_dm_power_domain_attach(dev, RT_TRUE);
if (err && err != -RT_EEMPTY)
    return err;
```

Failed driver **`probe`** → **`rt_dm_power_domain_detach(dev, RT_TRUE)`**.

**RPMsg** and **PCI PME** also call **`attach`** where DT requires it.

---

## Recommended sequencing

With regulator and reset (@ref page_device_power, @ref page_device_clk):

```
regulator enable (if needed)
    → power domain on (attach or power_on)
    → clock / reset release
    → rt_dm_dev_iomap + driver init
```

Power **off** for suspend (if implemented): reverse order per SoC manual - often **`idle clocks` -> `reset assert` -> `power_off`**.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_PMDOMAIN_SCMI`** | SCMI power protocol → **`pm-domain-scmi.c`** |
| **`SOC_DM_PMDOMAIN_DIR`** | BSP-specific genpd drivers |

Requires **`RT_USING_DM`** and **`RT_USING_OFW`** for DT phandle parsing.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| No **`rt_ofw_data` on provider** | **`ofw_find_power_domain`** fails — bind domain or proxy at provider probe |
| **`attach` only index 0** | Use **`get_by_index(1, …)`** + **`power_on`** for more domains |
| **`-RT_EEMPTY` vs error** | Missing property is normal; log real failures only |
| **`power_on` in IRQ** | Callbacks may sleep — use thread context |
| **`put` is stub** | Rely on **`detach`** / **`power_off`** for lifecycle |
| **Provider not probed before consumer** | Ensure provider driver probes first or defer consumer |
| Confuse with **`rt_dm_power_off_handler`** | Domain = IP block; handler = whole system off |

---

## See also

- @ref page_device_power — stack overview
- @ref page_device_platform — auto **`attach`** in probe
- @ref page_device_regulator
- @ref page_device_ofw — phandles, **`#power-domain-cells`**
- @ref page_device_scmi_agent — SCMI provider
- `components/drivers/core/power_domain.c`
- `components/drivers/pmdomain/pm-domain-scmi.c`
