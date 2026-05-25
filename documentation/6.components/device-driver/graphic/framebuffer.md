@page page_device_graphic_framebuffer Simple framebuffer (`simple-framebuffer`)

# `simple-framebuffer` platform driver

Implementation: **`components/drivers/graphic/framebuffer/fb-simple.c`**. Registers a **`struct rt_graphic_device`** from a fixed memory window described in device tree (Linux **`simple-framebuffer`** binding style).

## Device tree (typical)

```dts
framebuffer@0 {
    compatible = "simple-framebuffer";
    reg = <0x0 0x00800000>;
    width = <1920>;
    height = <1080>;
    stride = <7680>;
    format = "a8r8g8b8";   /* see driver format table */
    clocks = <&disp_clk>;  /* optional, RT_USING_CLK */
    power-supplies = <&vdd>; /* optional, RT_USING_REGULATOR */
};
```

## Probe flow

1. Parse **`width`**, **`height`**, **`stride`**, **`format`** → internal **`simplefb_format`** (bits per pixel, RT graphic mode).
2. **`ioremap`** (or use physical) **`reg`** → **`screen_base`**, compute **`screen_size`**.
3. Optional **`rt_clk_array`** prepare/enable; optional regulator **`enable`** array.
4. Fill **`rt_graphic_device`** ops (`set_pixel`, `get_pixel`, `draw_hline`, etc.) and **`rt_device_register`**.

## Supported formats

Driver table maps string names (e.g. **`r5g6b5`**, **`a8r8g8b8`**, **`x8r8g8b8`**) to **`rt_graphic_info`** mode and bpp. Unknown **`format`** fails probe.

## Remove

Disable clocks/regulators, unmap framebuffer memory, unregister graphic device.

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| Cache | CPU-accessible framebuffer RAM must use correct MMU cache attributes; if cacheable, maintain with **`rt_hw_cpu_dcache_ops`** — see @ref page_device_hwcache |
| Stride | Must match hardware line pitch (bytes), not always `width * bpp/8` |
| Primary display | Pair with @ref page_device_graphic_dm / `graphic_primary.c` if multiple heads |
| No GPU | This is **linear FB** only—no command queue; use a SoC GPU driver if you need acceleration |

## See also

- @ref page_device_graphic_dm
- `components/drivers/graphic/framebuffer/fb-simple.c`
- `components/drivers/graphic/graphic.c`
