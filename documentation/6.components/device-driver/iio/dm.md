@page page_device_iio_dm IIO device model (DM)

# Industrial I/O channel discovery under `RT_USING_DM`

RT-Thread **IIO** support is intentionally **small**: it does **not** implement a full Linux IIO subsystem (no `iio_device` bus, no buffer/trigger framework in-tree). With **`RT_USING_DM`**, **`components/drivers/iio/iio.c`** parses device-tree **`io-channels`** / **`io-channel-names`** (Linux-compatible binding names) and returns an **opaque provider handle** plus a **channel index**.

Data path (read raw ADC counts, scale to mV, trigger buffers, etc.) remains **entirely in the provider driver** (ADC, thermal, PMIC ADC, …).

Overview of the IIO concept: @ref page_device_iio. This page documents **DM phandle resolution** and **provider obligations**.

Sources: **`components/drivers/iio/iio.c`**, **`components/drivers/include/drivers/iio.h`**.

---

## Kconfig / build

| Requirement | Role |
| --- | --- |
| **`RT_USING_DM`** | **`iio/SConscript`** builds **`iio.c`** only when DM is on |
| **`RT_USING_OFW`** | **`ofw_iio_channel_get_by_index`** parses phandles; without OFW, **`get_*` returns `NULL`** |
| Provider driver | Separate Kconfig (e.g. **`RT_USING_ADC`**, SoC SARADC in BSP) — not part of **`iio.c`** |

**`drivers/iio.h`** is included from **`rtdevice.h`**; link **`iio.c`** by enabling **`RT_USING_DM`**.

There is **no** separate **`RT_USING_IIO`** menu entry — IIO glue is a DM companion module.

---

## Architecture

```
  Consumer (platform device, e.g. PMIC / headset / fuel gauge logic)
        |
        |  dev->ofw_node has io-channels / io-channel-names
        v
  rt_iio_channel_get_by_name(dev, "vdd", &ch)
        |
        |  rt_dm_dev_prop_index_of_string("io-channel-names")
        |  rt_ofw_parse_phandle_cells("io-channels", "#io-channel-cells", index)
        v
  Provider OFW node (e.g. saradc, tsadc)
        |
        |  rt_platform_ofw_request if not probed
        |  return rt_ofw_data(provider_np)  /* opaque void * */
        |  *out_channel = specifier args[0]
        v
  Consumer casts cookie to provider private type
        + uses out_channel as logical channel index
        + calls provider-specific read API (rt_adc_*, custom fn, …)
```

**Unlike @ref page_device_i2c_dm**, IIO has **no `rt_bus`** and **no automatic client probe**. Only **phandle lookup** is centralized.

---

## Public API (`iio.h`)

```c
void *rt_iio_channel_get_by_index(struct rt_device *dev, int index, int *out_channel);
void *rt_iio_channel_get_by_name(struct rt_device *dev, const char *name, int *out_channel);
```

| API | Behavior |
| --- | --- |
| **`get_by_index`** | Parse Nth entry in consumer’s **`io-channels`** list |
| **`get_by_name`** | Resolve index via **`io-channel-names`**, then same as **`get_by_index`** |
| **Return value** | **`void *`** = **`rt_ofw_data(provider_np)`** after optional **`rt_platform_ofw_request`** |
| **`out_channel`** | First cell of provider **`#io-channel-cells`** specifier (logical channel number) |

| Input check | Result |
| --- | --- |
| **`dev == NULL`**, **`index < 0`**, **`name == NULL`** | **`NULL`** |
| Consumer has **no `dev->ofw_node`** | **`NULL`** |
| Missing **`io-channels`** / parse error | **`NULL`** |
| Provider not probed | **`rt_platform_ofw_request`** then retry **`rt_ofw_data`** |

There is **no `rt_iio_channel_put`** in the header — lifetime follows the **provider `rt_device`** / platform driver **`remove`**. Do not use the cookie after the provider unregisters.

---

## Device tree bindings

### Provider (ADC / sensor front-end)

```dts
saradc: adc@ff100000 {
    compatible = "rockchip,rk3588-saradc";
    reg = <0x0 0xff100000 0x0 0x100>;
    interrupts = <GIC_SPI 93 IRQ_TYPE_LEVEL_HIGH>;
    clocks = <&cru CLK_SARADC>, <&cru PCLK_SARADC>;
    clock-names = "saradc", "pclk";
    vref-supply = <&vcc_1v8_s0>;

    #io-channel-cells = <1>;
    io-channel-ranges;
};
```

| Property | Role |
| --- | --- |
| **`#io-channel-cells = <1>`** | One integer per phandle in consumer **`io-channels`** |
| **`io-channel-ranges`** | Optional (Linux); presence documents channel map semantics for porters |
| Channel index | **0 … N-1** — meaning defined by **provider driver** (SARADC channel id, TSADC sensor input, …) |

### Consumer

```dts
fuel-gauge {
    compatible = "vendor,fg";
    io-channels = <&saradc 4>, <&saradc 5>;
    io-channel-names = "bat-voltage", "bat-current";
};
```

| Property | Role |
| --- | --- |
| **`io-channels`** | Phandle + one cell per channel (provider + index) |
| **`io-channel-names`** | Optional strings aligned with **`io-channels`** order |

**`get_by_name(dev, "bat-voltage", &ch)`** → cookie = saradc private struct, **`ch == 4`**.

---

## Provider driver contract

The provider must expose **`rt_ofw_data(provider_np)`** before consumers resolve channels.

Typical pattern (from **`adc-rockchip_saradc.c`**):

```c
static rt_err_t rockchip_saradc_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rockchip_saradc *rk_saradc = rt_calloc(1, sizeof(*rk_saradc));

    /* clocks, regulator, iomap, irq, rt_hw_adc_register(...) */

    rt_dm_dev_bind_fwdata(dev, RT_NULL, rk_saradc);
    return RT_EOK;
}

static rt_err_t rockchip_saradc_remove(struct rt_platform_device *pdev)
{
    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    /* unregister ADC, free resources */
}
```

| Obligation | Detail |
| --- | --- |
| **`rt_dm_dev_bind_fwdata(dev, NULL, priv)`** | Sets **`rt_ofw_data(dev->ofw_node) = priv`** (@ref page_device_dm) |
| **`#io-channel-cells`** in DTS | Must match **`args_count == 1`** in **`iio.c`** (otherwise lookup fails) |
| **Probe before consumer** | Or rely on **`rt_platform_ofw_request`** during **`get_*`** |
| **Document channel map** | What index **0, 1, 2…** mean (pin / internal mux / TSADC sensor) |

Returned cookie is usually the **provider’s private struct** (`struct rockchip_saradc *`, etc.) — **not** a portable `struct iio_channel`. Consumers in the same BSP cast to the known type.

---

## Consumer driver pattern

```c
#include <drivers/iio.h>

static rt_err_t my_consumer_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    void *iio_priv;
    int ch;

    iio_priv = rt_iio_channel_get_by_name(dev, "bat-voltage", &ch);
    if (!iio_priv)
    {
        return -RT_EINVAL;
    }

    priv->saradc = (struct rockchip_saradc *)iio_priv;
    priv->channel = ch;

    /* Use priv->saradc + priv->channel with provider helpers
     * e.g. rt_adc_enable/read on &priv->saradc->parent, or direct HW access */
    return RT_EOK;
}
```

| Step | Notes |
| --- | --- |
| Call **`get_*` in `probe`** | After consumer **`ofw_node`** is set; provider may be deferred-probed by **`rt_platform_ofw_request`** |
| Store **cookie + `out_channel`** | Cookie = provider priv; **`ch`** selects logical input |
| **No standard read API** | Pair with **`rt_adc_*`**, **`rt_sensor_*`**, or vendor functions |
| **`remove`** | Drop pointers; do not call **`get_*`** again |

---

## Relation to ADC / sensor frameworks

| Framework | Role vs IIO |
| --- | --- |
| **@ref page_device_adc** | **`rt_adc_device`** is often the **provider** registered by SARADC; IIO only **discovers** which channel another driver needs |
| **Sensor framework** | Separate path (`rt_sensor_*`); may coexist — do not confuse sensor bus with IIO phandles |

IIO is **glue for DT `io-channels`**, not a replacement for **`rt_device_find("adc0")`**.

---

## Comparison with Linux IIO

| Linux | RT-Thread DM IIO |
| --- | --- |
| `struct iio_channel` + `iio_channel_get()` | Opaque **`void *`** + **`out_channel` int |
| `iio_read_channel_raw()` etc. | **Not in-tree** — provider-specific |
| IIO core + buffers/triggers | **Not implemented** |

Porting focus: reproduce **DT property names** and **channel indices**; reimplement read path against local ADC driver.

---

## Engineer checklist

1. **Provider DTS**: **`#io-channel-cells = <1>`**; document channel index meanings.
2. **Provider probe**: **`rt_dm_dev_bind_fwdata`** with stable **`priv`** pointer.
3. **Consumer DTS**: **`io-channels`** + optional **`io-channel-names`**.
4. **Consumer probe**: **`rt_iio_channel_get_by_*`**, check **`NULL`**, store cookie + index.
5. **Reads**: use provider APIs; honor **`rt_adc_enable` / mutex** rules of that driver.
6. **Teardown**: consumer **`remove`** first or ensure no use-after-free when provider exits.

---

## Pitfalls

- **Opaque pointer is provider-specific** — do not cast to a fictional `struct iio_channel`.
- **`args_count != 1`** — **`iio.c` returns failure**; multi-cell specifiers are unsupported today.
- **Missing `bind_fwdata`** — **`get_*` returns NULL** even if ADC device registered.
- **Consumer without `ofw_node`** — always **`NULL`** (no manual fallback in **`iio.c`**).
- **Wrong channel index** — parse succeeds but reads wrong pin / garbage data.
- **No refcount on cookie** — provider **`remove`** while consumer still holds pointer → UAF.
- **Assuming full IIO stack** — scaling, sysfs, buffer DMA are out of scope for **`iio.c`**.

---

## See also

- @ref page_device_iio — role and limits summary
- @ref page_device_dm — **`rt_dm_dev_bind_fwdata`**, property helpers
- @ref page_device_ofw — **`rt_ofw_parse_phandle_cells`**
- @ref page_device_platform — consumer/provider **`probe`**
- @ref page_device_adc — typical provider (**`rt_hw_adc_register`**)
- `components/drivers/iio/iio.c`
- `components/drivers/include/drivers/iio.h`
