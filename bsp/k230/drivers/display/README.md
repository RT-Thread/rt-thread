# K230 Display Driver

This driver enables the ATK K230D ST7701 MIPI-DSI panel without linking the
hard-float `libvo.a`. The implementation is intentionally small:

- `drv_display.c` registers RT-Thread graphic devices `lcd` and `fb0`.
- `panel_common.c`, `bus_dsi.c`, and `panels/` describe the panel, GPIO reset,
  backlight, MIPI-DSI bus, and timing.
- `vo/` contains the lightweight VO/DSI register code that replaces the old
  `libvo.a` dependency.

## Configuration

Enable:

```text
BSP_USING_DISPLAY=y
```

The Kconfig option selects the RT-Thread device, device-ops, and pin APIs used
by this driver. The build is handled by `drivers/display/SConscript`; it builds
the local VO/DSI source files and does not link `libvo.a`.

## Device Interface

The driver registers:

- `lcd`: compatible RT-Thread graphic device name.
- `fb0`: framebuffer-style graphic device intended for device-file access.

Both devices share one RGB565 framebuffer. `RTGRAPHIC_CTRL_GET_INFO` returns
`struct rt_device_graphic_info`:

- `pixel_format`: `RTGRAPHIC_PIXEL_FORMAT_RGB565`
- `bits_per_pixel`: `16`
- `pitch`: bytes per line
- `width`, `height`: panel active size
- `framebuffer`, `smem_len`: kernel framebuffer address and size

Supported controls:

- `RTGRAPHIC_CTRL_GET_INFO`
- `RTGRAPHIC_CTRL_RECT_UPDATE`
- `RTGRAPHIC_CTRL_POWERON`
- `RTGRAPHIC_CTRL_POWEROFF`
- `RTGRAPHIC_CTRL_SET_BRIGHTNESS`
- `RTGRAPHIC_CTRL_GET_BRIGHTNESS`
- `RTGRAPHIC_CTRL_WAIT_VSYNC`

`read()` and `write()` operate on byte offsets in the RGB565 framebuffer. Writes
flush the CPU data cache for the updated range.

## Kernel Shell Example

```text
list_device
list_display
display_demo
```

`display_demo` opens `fb0`, queries `RTGRAPHIC_CTRL_GET_INFO`, writes an RGB565
test pattern, then calls `RTGRAPHIC_CTRL_RECT_UPDATE`.

## User-Space Example

```c
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main(void)
{
    int fd = open("/dev/fb0", O_RDWR);
    uint16_t line[480];

    if (fd < 0)
        return -1;

    for (int x = 0; x < 480; x++)
        line[x] = 0xf800; /* red in RGB565 */

    for (int y = 0; y < 640; y++)
        write(fd, line, sizeof(line));

    close(fd);
    return 0;
}
```

Use RGB565 pixels. For partial updates, seek to `y * pitch + x * 2` before
writing if the user-space C library exposes `lseek()` for device files.

## Notes

This driver does not implement hardware acceleration. It only provides a CPU
framebuffer and the minimum panel/DSI/VO setup needed for display bring-up.

The current local VO source covers reset, timing, mixer, background, DSI, and
register remap. The original hard-float `libvo.a` also contains lower-level
video/OSD layer address, stride, and format functions. Those functions must be
implemented from verified register definitions before claiming full framebuffer
scanout on hardware. Until then, `fb0` device-file drawing is present and cache
coherent, while actual panel scanout requires board validation.
