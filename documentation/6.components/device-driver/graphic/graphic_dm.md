@page page_device_graphic_dm Graphics (DM)

# Graphics subsystem (device model)

RT-Thread **graphic DM** (`components/drivers/include/drivers/graphic.h`, `components/drivers/graphic/graphic.c`) wraps display controllers as **`struct rt_graphic_device`**: multi-**plane** framebuffers, **EDID**, optional **backlight**, Linux-style **fb** ioctls, and legacy **`rt_device_graphic_ops`** via **`rt_graphic_device_switch_primary`**.

App-facing pixel formats and **`RTGRAPHIC_CTRL_*`** live in **`drivers/classes/graphic.h`**. DM types, planes, and registration APIs are in **`graphic.h`**.

Implementation split:

| File | Role |
| --- | --- |
| **`graphic.c`** | Device register, `control`, planes, EDID parse, auto-update timer, OFW backlight |
| **`graphic_simple.c`** | Synthetic EDID + **`rt_graphic_device_simple_register`** |
| **`graphic_primary.c`** | **`rt_graphic_device_switch_primary`** → `set_pixel` / `draw_hline` on primary FB |
| **`framebuffer/fb-simple.c`** | DT **`simple-framebuffer`** — @ref page_device_graphic_framebuffer |

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DM`** | Required parent |
| **`RT_USING_GRAPHIC`** | Core graphic stack (`graphic.c`, `graphic_primary.c`, `graphic_simple.c`) |
| **`RT_GRAPHIC_FB`** | Framebuffer drivers (e.g. **`simple-framebuffer`**) |
| **`RT_GRAPHIC_BACKLIGHT`** | Backlight class + PWM/GPIO — @ref page_device_graphic_backlight |
| **`RT_GRAPHIC_LOGO`** | Boot logo render on register — @ref page_device_graphic_logo |

---

## Architecture

```
  Controller driver (DSI, LCD, simple-fb, …)
        |
        |  alloc_plane + plane_ops (update / fb_remap / fb_cleanup)
        v
  struct rt_graphic_device
    primary_plane  (required, one)
    cursor_plane   (optional, one)
    overlay_nodes  (0..N)
    edid, ops, backlight, update_timer
        |
        |  rt_graphic_device_register  ->  rt_device "fbN"
        v
  Apps: rt_device_find + RTGRAPHIC_CTRL_* / read-write FB
        |
        |  rt_graphic_device_switch_primary(gdev)
        v
  dev->user_data = rt_device_graphic_ops (graphic_primary.c)
```

| Layer | Responsibility |
| --- | --- |
| **`rt_graphic_plane_ops`** | Hardware: allocate FB, push pixels to display (**`update`**), teardown (**`fb_cleanup`**) |
| **`rt_graphic_device_ops`** | Device-wide: **DPMS**, **vsync**, brightness, vendor **`control`** |
| **`graphic.c`** | Standard **`rt_device`** API, rect update, mode set, hotplug, periodic flush timer |

---

## Core structures

### `struct rt_graphic_plane`

| Field | Meaning |
| --- | --- |
| **`type`** | **`PRIMARY`** (one), **`CURSOR`** (one), **`OVERLAY`** (list) |
| **`mode` / `modes[]`** | **`RTGRAPHIC_PIXEL_FORMAT_*`** from `classes/graphic.h` |
| **`framebuffer`**, **`line_length`**, **`screen_len`**, **`framebuffer_len`** | CPU-visible buffer; may be multi-buffer if **`framebuffer_len > screen_len`** |
| **`ops`** | Driver callbacks (see below) |

### `struct rt_graphic_plane_ops`

| Callback | When called | Contract |
| --- | --- | --- |
| **`fb_remap`** | Mode or resolution change | Allocate/map FB for **`mode`** + **`rect`**; set **`plane->framebuffer`** |
| **`fb_cleanup`** | Before remap / del_plane | Release HW resources (unmap, unref GPU resource) |
| **`update`** | **`RTGRAPHIC_CTRL_RECT_UPDATE`** or auto timer | Push **`rect`** region to display; **`width/height == 0`** may mean “position only” (cursor) |
| **`fb_pan_display`** | **`RTGRAPHIC_CTRL_PAN_DISPLAY`** / `open` | Point scanout at offset inside **`framebuffer`** |
| **`prop_set`** | Optional | Z-order, rotate, alpha (**`enum rt_graphic_plane_prop`**) |

### `struct rt_graphic_device_ops`

| Callback | Role |
| --- | --- |
| **`dpms_switch`** | **`RT_GRAPHIC_DPMS_*`** — often ties to **`rt_graphic_device_update_auto`** period |
| **`wait_vsync`** | **`RTGRAPHIC_CTRL_WAIT_VSYNC`** |
| **`set_brightness` / `get_brightness`** | Panel brightness; may defer to **`gdev->backlight`** |
| **`get_status`** | Optional connector status |
| **`current_plane`** | Override plane used for **`GET_INFO`** / updates (default: primary) |
| **`control`** | Vendor-specific commands (optional 3D / acceleration path) |

### EDID

**`struct edid`** in **`graphic.h`** mirrors VESA EDID layout. **`RTGRAPHIC_CTRL_GET_EXT`** copies **`gdev->edid`**. On register, if primary plane has no size, **`graphic_edid_res()`** picks mode from detailed timings.

**`rt_graphic_device_simple_edid(gdev, w, h, refresh_hz)`** (`graphic_simple.c`) builds a minimal EDID when hardware has no DDC (fixed panels, simple bring-up).

---

## Registration API

| API | Role |
| --- | --- |
| **`rt_graphic_device_alloc_plane(gdev, priv_size, ops, modes, modes_nr, type)`** | Allocate plane; **`priv[0]`** tail for driver data |
| **`rt_graphic_device_add_plane(gdev, plane)`** | Attach primary/cursor/overlay; assigns **`plane_ida`** id |
| **`rt_graphic_device_register(gdev)`** | Requires **`primary_plane`**; names device **`fb%u`** via **`RT_DM_IDA`**; maps FB from EDID if size zero |
| **`rt_graphic_device_unregister(gdev)`** | DPMS off, stop timer, del all planes, **`rt_device_unregister`** |
| **`rt_graphic_device_simple_register(...)`** | Alloc primary plane + synthetic EDID + register (no full EDID path) |
| **`rt_graphic_device_simple_unregister(gdev)`** | Alias for **`unregister`** |

**Naming**: **`RT_DM_IDA_INIT(GRAPHIC_FRAMEBUFFER)`** → devices **`fb0`**, **`fb1`**, …

**OFW backlight**: during **`register`**, **`graphic_ofw_init`** resolves **`backlight`** phandle on **`dev->ofw_node`** and opens the backlight device.

---

## Application / framework controls

From **`classes/graphic.h`** (handled in **`graphic.c`** **`_graphic_control`**):

| Command | Behavior |
| --- | --- |
| **`RTGRAPHIC_CTRL_RECT_UPDATE`** | **`plane->ops->update(plane, rect)`** on current plane |
| **`RTGRAPHIC_CTRL_SET_MODE`** | **`fb_remap`** if mode is in **`plane->modes[]`** |
| **`RTGRAPHIC_CTRL_GET_INFO`** | Fills **`rt_device_graphic_info`** from current plane |
| **`RTGRAPHIC_CTRL_POWERON` / `POWEROFF`** | DPMS + optional backlight power |
| **`RTGRAPHIC_CTRL_PAN_DISPLAY`** | Offset within framebuffer (double-buffer) |
| **`RTGRAPHIC_CTRL_WAIT_VSYNC`** | Driver **`wait_vsync`** |
| **`RT_DEVICE_CTRL_CURSOR_*`** | Cursor plane position / bitmap |
| **`FBIOGET_VSCREENINFO` / `FBIOPUT_VSCREENINFO`** | Linux fb var screeninfo (when enabled) |

**Auto flush**: **`rt_graphic_device_update_auto(gdev, ms)`** starts a periodic timer (**default idea: `RT_GRAPHIC_UPDATE_MS` = 16**) that calls **`update`** on primary, overlays, and cursor. **`rt_graphic_device_enter` / `leave`** stop/restart the timer around modeset (hotplug).

**Hotplug**: **`rt_graphic_device_hotplug_event(gdev)`** re-parses EDID size, **`fb_remap`** primary, then fires **`event_notify`**.

---

## Primary display helpers (`graphic_primary.c`)

```c
struct rt_device_graphic_ops *rt_graphic_device_switch_primary(struct rt_graphic_device *gdev);
```

- Sets global **`primary_gdev`** and returns **`rt_device_graphic_ops`** matching primary plane **bpp** (8/16/24/32/64).
- Legacy macro in **`graphic.h`**: **`rt_graphix_ops(dev)`** calls **`switch_primary`** then reads **`dev->user_data`**.
- Used by **finsh / LVGL / logo** code that draws via **`set_pixel`** / **`draw_hline`** without **`RTGRAPHIC_CTRL_RECT_UPDATE`**.

After **`register`**, call **`switch_primary`** on the head you want for **`rt_graphix_ops`**.

---

## Typical controller `probe` (SoC)

```c
static const rt_uint32_t my_modes[] = {
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
};

static const struct rt_graphic_plane_ops my_plane_ops = {
    .fb_remap   = my_fb_remap,
    .fb_cleanup = my_fb_cleanup,
    .update     = my_fb_update,
};

static rt_err_t my_probe(struct rt_platform_device *pdev)
{
    struct my_drv *priv;
    struct rt_graphic_plane *plane;
    rt_err_t err;

    priv = rt_dm_dev_iomap(pdev->parent.parent, 0);  /* or embed in pdev->priv */
    /* clocks, resets, regulator — @ref page_device_clk, @ref page_device_reset */

    priv->gdev.ops = &my_gdev_ops;

    plane = rt_graphic_device_alloc_plane(&priv->gdev, sizeof(*priv),
            &my_plane_ops, my_modes, RT_ARRAY_SIZE(my_modes),
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);
    if (!plane)
        return -RT_ENOMEM;

    err = rt_graphic_device_add_plane(&priv->gdev, plane);
    if (err)
        goto err;

    /* Fill EDID from DDC or rt_graphic_device_simple_edid() */
    err = rt_graphic_device_register(&priv->gdev);
    if (err)
        goto err;

    rt_graphic_device_switch_primary(&priv->gdev);
    rt_graphic_device_update_auto(&priv->gdev, RT_GRAPHIC_UPDATE_MS);
    return RT_EOK;
}
```

**`simple-framebuffer`**: maps fixed **`reg`** RAM, implements plane ops as CPU memcpy — see @ref page_device_graphic_framebuffer.

---

## PHY, clocks, backlight

| Resource | Document |
| --- | --- |
| **Pixel / link clock** | @ref page_device_clk |
| **DSI/DP PHY** | @ref page_device_phye |
| **Panel backlight** | @ref page_device_graphic_backlight (`backlight` DT property) |
| **Coherent FB / cache** | @ref page_device_hwcache, @ref page_device_dma |

**Bring-up order**: regulator → clock → panel init → **`register`** → backlight **`POWERON`** → **`RTGRAPHIC_CTRL_POWERON`**.

---

## Engineer checklist

1. Implement **`rt_graphic_plane_ops`** (at minimum **`fb_remap`**, **`update`**, **`fb_cleanup`**).
2. **`add_plane` PRIMARY** before **`register`**; cursor/overlay after if needed.
3. Populate **`edid`** or use **`simple_register`** / **`simple_edid`**.
4. **`register`** → **`switch_primary`** for legacy drawing APIs.
5. **`remove`**: **`unregister`** (frees planes); release clocks/reset/regulator in reverse order.
6. Hotplug: call **`hotplug_event`** after EDID/mode change under **`enter`/`leave`**.

---

## Pitfalls

- **Missing `update` with auto timer off**: apps must **`RTGRAPHIC_CTRL_RECT_UPDATE`** after CPU writes or nothing reaches the panel.
- **Primary plane size 0 at register**: core tries EDID **`fb_remap`** — bogus EDID causes probe failure.
- **Two PRIMARY planes**: **`add_plane`** returns **`-RT_EINVAL`**.
- **DMA / cache**: CPU-drawn FB must use correct MMU attributes; sync cache before **`update`** if scanout is non-coherent — @ref page_device_hwcache.
- **`switch_primary` global**: only one **`primary_gdev`** — multi-head apps should use **`rt_device_find("fb1")`** + graphic ctrl, not **`rt_graphix_ops`** alone.
- **DPMS off without stopping updates**: use **`rt_graphic_device_update_auto(gdev, 0)`** or **`enter`** during suspend.

---

## Detailed documents

- @ref page_device_graphic_framebuffer — **`simple-framebuffer`**
- @ref page_device_graphic_backlight — PWM/GPIO backlight
- @ref page_device_graphic_logo — boot logo (PPM)

## See also

- `components/drivers/include/drivers/graphic.h`
- `components/drivers/include/drivers/classes/graphic.h`
- `components/drivers/graphic/graphic.c`, `graphic_simple.c`, `graphic_primary.c`
- @ref page_device_dm — `rt_dm_dev_iomap`, naming
- @ref page_device_platform — `RT_PLATFORM_DRIVER_EXPORT`
