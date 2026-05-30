@page page_device_graphic_backlight Backlight devices

# Backlight subsystem

Header: `components/drivers/include/drivers/backlight.h`. Core: **`components/drivers/graphic/backlight/backlight.c`**. PWM and GPIO backends: **`backlight-pwm.c`**, **`backlight-gpio.c`**.

Graphic stack overview: @ref page_device_graphic_dm.

## `struct rt_backlight_device`

Extends **`rt_device`**. Properties include **`max_brightness`**, **`brightness`**, power state. Drivers implement brightness through ops registered with the core.

### Core device behavior (`backlight.c`)

| Op | Behavior |
| --- | --- |
| `read` | ASCII decimal of current brightness |
| `write` | Parse integer string, clamp to **`max_brightness`**, call **`rt_backlight_set_brightness`** |

**`RT_DM_IDA_INIT(GRAPHIC_BACKLIGHT)`** assigns stable DM names on register.

## PWM backlight (`pwm-backlight`)

**Compatible**: typically **`pwm-backlight`** (see driver OFW table in source).

| DT / property | Role |
| --- | --- |
| `pwms` | PWM channel for dimming |
| `brightness-levels` | Optional non-linear LUT |
| `default-brightness-level` | Boot brightness index |
| `enable-gpios` | Panel enable pin |
| `power-supply` | Optional **`rt_regulator`** before PWM |

Probe enables regulator (if any), maps brightness levels, registers **`rt_backlight_device`**.

## GPIO backlight (`gpio-backlight`)

Simple on/off or few-level backlight using a GPIO line (see `backlight-gpio.c` OFW ids).

## Driver / BSP quick notes

| Topic | Guidance |
| --- | --- |
| Enable order | Regulator → enable GPIO → PWM duty |
| Thermal | High brightness may interact with @ref page_device_thermal policies |
| Userspace | Writing `"128\n"` to device node sets brightness (see core `write`) |

## See also

- @ref page_device_graphic_dm
- @ref page_device_regulator
- `components/drivers/graphic/backlight/backlight.c`
- `components/drivers/graphic/backlight/backlight-pwm.c`
