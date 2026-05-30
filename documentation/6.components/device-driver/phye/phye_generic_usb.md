@page page_device_phye_generic_usb Generic USB PHY

# Generic USB PHY (`phye-generic-usb.c`)

Minimal PHY provider for **`usb-nop-xceiv`** — reset, clock, and regulators without complex **`set_mode`**.

Kconfig: **`RT_PHYE_GENERIC_USB`** (requires **`RT_USING_PHYE`**).

---

## Device tree

```dts
usb_phy: usb-phy {
    compatible = "usb-nop-xceiv";
    clocks = <&usb_clk>;
    clock-frequency = <24000000>;
    vcc-supply = <&usb_vcc>;
    vbus-supply = <&usb_vbus>;   /* optional */
    reset-gpios = <&gpio PHY_RST GPIO_ACTIVE_LOW>;
};
```

Consumer (e.g. DWC3):

```dts
usb3: usb@... {
    phys = <&usb_phy>;
    phy-names = "usb";
};
```

---

## Operations

| `rt_phye_ops` | Behavior |
| --- | --- |
| **`power_on`** | **`vcc`** enable → **`clk_prepare_enable`** → **`reset`** pulse (15 ms assert, 20 ms deassert) |
| **`power_off`** | **`vcc`** disable, clock off |
| **`reset`** | GPIO reset only |

No **`init`**, **`exit`**, or **`set_mode`** — USB mode assumed fixed after power-on.

---

## Probe flow

1. **`reset`** GPIO from **`reset-gpios`**  
2. **`main_clk`** via **`rt_clk_get_by_name`**; optional **`clock-frequency`**  
3. **`vcc`**, **`vbus`** regulators — **`vbus`** enabled at probe if present  
4. **`rt_phye_register`**

**`INIT_PLATFORM_EXPORT(generic_usb_phy_drv_register)`** — registers platform driver at init.

---

## Consumer usage

```c
phy = rt_phye_get_by_name(dev, "usb");
rt_phye_power_on(phy);   /* often sufficient for nop-xceiv */
/* start USB controller */
```

Use **`rt_phye_init`** only if provider adds **`init`** later.

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Wrong clock rate | Set **`clock-frequency`** in DTS |
| **`vbus` always on** | Probe enables **`vbus`** — OK for host; device role may differ |
| Expect **`set_mode` for SS** | Add SoC PHY driver or extend ops |

## See also

- @ref page_device_phye_provider
- @ref page_device_phye_consumer
- @ref page_device_phye
