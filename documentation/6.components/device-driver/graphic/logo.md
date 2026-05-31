@page page_device_graphic_logo Boot Logo

# Boot Logo (PPM)

Implementation: **`components/drivers/graphic/logo/logo.c`**. Build converts a **PPM** asset into **`logo.inc`** (RGB triplets) at compile time. At runtime **`rt_graphic_logo_render()`** draws the logo centered on the framebuffer when a **`rt_graphic_device`** registers.

Graphic stack overview: @ref page_device_graphic_dm.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_GRAPHIC_LOGO`** | Enable logo subsystem; selects **`RT_GRAPHIC_FB`** |
| **`RT_GRAPHIC_LOGO_NONE`** | No built-in image — use **`rt_graphic_logo_change()`** at runtime |
| **`RT_GRAPHIC_LOGO_RT_THREAD_CLUT224`** | Embed **`logo-rt-thread-clut224.ppm`** (default) |
| **`RT_GRAPHIC_LOGO_RT_THREAD_WHITE_CLUT224`** | White variant PPM |
| **`SOC_DM_GRAPHIC_LOGO_DIR`** | BSP adds custom logo choices via **`Kconfig`** / **`Kconfig.path`** |

Custom BSP logos: define **`RT_GRAPHIC_LOGO_<NAME>`** in Kconfig and **`RT_GRAPHIC_LOGO_<NAME>_PATH`** (string, path to `.ppm`). **`logo/SConscript`** parses the file and generates **`logo.inc`**.

---

## When the logo is drawn

```
rt_graphic_device_register(gdev)
        |
        v
rt_graphic_logo_render(gdev)   /* graphic.c; errors logged at DBG only */
        |
        +-- open fb device, GET_INFO, POWERON
        +-- blit PPM RGB -> framebuffer (centered)
        +-- RTGRAPHIC_CTRL_RECT_UPDATE + WAIT_VSYNC
        +-- startup_logo = NULL  (one-shot; frees built-in use)
```

- Runs when a graphic device successfully **registers** (see **`graphic.c`**).
- Requires **`RT_GRAPHIC_LOGO`** and non-empty **`startup_logo`** (built-in or **`rt_graphic_logo_change`**).
- If logo is larger than **`var.xres` / `var.yres`**, render fails with **`-RT_EINVAL`**.

---

## Runtime API (`graphic.h`)

### `rt_graphic_logo_change`

```c
rt_err_t rt_graphic_logo_change(void *data, int width, int height, int color_max);
```

| Arguments | Meaning |
| --- | --- |
| **`data`** | Pointer to **packed RGB** bytes (`width * height * 3`), same order as PPM pixmap data |
| **`width` / `height`** | Logo size in pixels |
| **`color_max`** | Max channel value in **`data`** (PPM **max pixel value**, e.g. **255** or **15**) |

| Call pattern | Effect |
| --- | --- |
| **`data == NULL` && all sizes 0** | Disable logo (**`startup_logo = NULL`**) |
| Valid **`data` + dimensions** | Replace logo used on next **`rt_graphic_logo_render`** |
| Otherwise | **`-RT_EINVAL`** |

Use with **`RT_GRAPHIC_LOGO_NONE`** or to override the built-in clut224 asset before the first **`register`**.

### `rt_graphic_logo_render`

```c
rt_err_t rt_graphic_logo_render(struct rt_graphic_device *gdev);
```

Normally called from **`rt_graphic_device_register()`** — drivers rarely invoke it directly. Steps:

1. **`rt_device_open`** on the graphic **`rt_device`**
2. **`FBIOGET_VSCREENINFO`** — grayscale vs RGB bitfield layout
3. **`RTGRAPHIC_CTRL_GET_INFO`** — framebuffer base + pitch
4. **`RTGRAPHIC_CTRL_POWERON`**
5. Center logo: **`rect.x/y = (screen - logo) / 2`**
6. Per-pixel color remap into **`bits_per_pixel`**
7. **`RTGRAPHIC_CTRL_RECT_UPDATE`** + **`RTGRAPHIC_CTRL_WAIT_VSYNC`**
8. Clears **`startup_logo`** (one-shot)

Without **`RT_GRAPHIC_LOGO`**, both APIs compile to inline no-ops returning **`RT_EOK`**.

---

## Build-time PPM → `logo.inc`

**`logo/SConscript`** (when a logo path is selected):

1. Read PPM header (**P1–P3** ASCII path in script).
2. Parse **`width height`**, **`max_pixel_value`**, pixel stream.
3. Emit **`logo.inc`**: rows of **`R,G,B`** byte triplets.
4. Define **`__STARTUP_LOGO_WIDTH__`**, **`__STARTUP_LOGO_HEIGHT__`**, **`__STARTUP_LOGO_COLOR_MAX__`**.

**`logo.c`** includes **`logo.inc`** into **`builtin_logo[]`** when all three macros are non-zero.

---

## Supported PPM variants

| Magic | Kind | Encoding | Notes |
| --- | --- | --- | --- |
| P1 | Bitmap | ASCII | Build script ASCII path |
| P2 | Graymap | ASCII | Build script ASCII path |
| P3 | Pixmap | ASCII | Typical for clut224 logos |
| P4 | Bitmap | Binary | Convert to P3 for embed |
| P5 | Graymap | Binary | Convert to P3 for embed |
| P6 | Pixmap | Binary | Use **`pnmnoraw`** → P3 for SConscript |

Runtime rendering always uses **RGB triplets** in memory.

---

## ASCII PPM layout

```text
# <magic>: P1 / P2 / P3 …
# <comment>
<width> <height>
<max_pixel_value>
<data…>
```

### Example (P3, 4×4)

```text
P3
# Standard 15-color test logo
4 4
15
0  0  0    0  0  0    0  0  0    15 0  15
0  0  0    0  15 7    0  0  0    0  0  0
0  0  0    0  0  0    0  15 7    0  0  0
15 0  15   0  0  0    0  0  0    0  0  0
```

|  | Col 0 | Col 1 | Col 2 | Col 3 |
| --- | --- | --- | --- | --- |
| **Row 0** | 0,0,0 | 0,0,0 | 0,0,0 | 15,0,15 |
| **Row 1** | 0,0,0 | 0,15,7 | 0,0,0 | 0,0,0 |
| **Row 2** | 0,0,0 | 0,0,0 | 0,15,7 | 0,0,0 |
| **Row 3** | 15,0,15 | 0,0,0 | 0,0,0 | 0,0,0 |

---

## Generating a logo file

1. Convert source image to PPM:

```bash
magick <input>.png <output>.ppm
```

2. Reduce to **224** colors (clut224 path):

```bash
ppmquant 224 <input>.ppm > <tmp>_224.ppm
```

3. ASCII PPM for SConscript:

```bash
pnmnoraw <tmp>_224.ppm > logo-<name>-clut224.ppm
```

4. Point BSP **`RT_GRAPHIC_LOGO_<NAME>_PATH`** at the file, or replace in-tree **`logo-rt-thread-clut224.ppm`**.

---

## Offline preview

Open **`components/drivers/graphic/logo/logo.html`** in a browser to preview a PPM before building.

---

## BSP / integration quick notes

| Topic | Guidance |
| --- | --- |
| **Asset size** | Large PPM bloats **`logo.inc`** and slows boot — keep resolution modest. |
| **Display readiness** | Logo runs at **`register`** — enable backlight after first frame if needed (@ref page_device_graphic_backlight). |
| **Format** | Invalid PPM fails SConscript at build time; validate in CI. |
| **One-shot** | After first render, **`startup_logo`** is cleared — call **`rt_graphic_logo_change`** again for another splash. |

---

## Pitfalls

- **Logo bigger than mode**: **`-RT_EINVAL`** — match PPM to panel resolution.
- **`RT_GRAPHIC_LOGO_NONE` without `logo_change`**: no logo (by design).
- **Binary P6 without conversion**: SConscript may not parse — use **`pnmnoraw`**.

---

## See also

- @ref page_device_graphic_dm
- @ref page_device_graphic_framebuffer
- `components/drivers/graphic/logo/logo.c`, `logo/SConscript`
- `components/drivers/include/drivers/graphic.h`
