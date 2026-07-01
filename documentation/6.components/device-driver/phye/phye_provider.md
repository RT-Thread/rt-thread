@page page_device_phye_provider Phye provider driver

# Implementing a PHY provider

Platform (or other) driver that owns PHY registers and exports **`struct rt_phye`**.

---

## Minimal template

```c
struct my_phy {
    struct rt_phye phye;
    void __iomem *regs;
    struct rt_clk *clk;
    /* mode, calibration, ... */
};

static rt_err_t my_phy_power_on(struct rt_phye *phye)
{
    struct my_phy *p = rt_container_of(phye, struct my_phy, phye);
    return rt_clk_prepare_enable(p->clk);
}

static rt_err_t my_phy_set_mode(struct rt_phye *phye,
        enum rt_phye_mode mode, int submode)
{
    /* program PHY for mode / submode */
    return RT_EOK;
}

static const struct rt_phye_ops my_phy_ops = {
    .power_on  = my_phy_power_on,
    .power_off = my_phy_power_off,
    .set_mode  = my_phy_set_mode,
    .ofw_parse = my_phy_ofw_parse,
};

static rt_err_t my_phy_probe(struct rt_platform_device *pdev)
{
    struct my_phy *p = rt_calloc(1, sizeof(*p));
    p->phye.dev = &pdev->parent;
    p->phye.ops = &my_phy_ops;
    return rt_phye_register(&p->phye);
}
```

---

## Probe checklist

1. **`rt_dm_dev_iomap`** / clocks / resets / regulators per TRM  
2. Fill **`rt_phye_ops`** — only implement needed ops  
3. **`phye->dev = &pdev->parent`**  
4. **`rt_phye_register(&phye)`** — binds **`rt_ofw_data`** for consumers  
5. Do **not** call **`set_mode`** for a specific host here — consumers select mode  

---

## `ofw_parse`

```c
static rt_err_t my_phy_ofw_parse(struct rt_phye *phye,
        struct rt_ofw_cell_args *args)
{
    /* args->args[0..args_count-1] from #phy-cells */
    /* store in container struct for set_mode */
    return RT_EOK;
}
```

Return error if cells are invalid — consumer **`get`** fails and host **`probe`** aborts.

---

## Unregister

**`remove`**: **`rt_phye_unregister`** then free resources. Fails if consumers still hold references (**`-RT_EBUSY`**).

---

## BSP placement

SoC-specific drivers often live under **`SOC_DM_PHYE_DIR`** (Kconfig **`osource`**). Enable in menuconfig alongside **`RT_USING_PHYE`**.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Forgot **`rt_phye_register`** | **`rt_ofw_data`** NULL — consumer sees missing PHY |
| Mode in **`probe`** | Host may need different mode — use **`set_mode`** from consumer |
| Shared PHY | Refcount in core helps; exclusive mux still needs driver policy |

## See also

- @ref page_device_phye_core
- @ref page_device_phye_ofw
- @ref page_device_phye_generic_usb
