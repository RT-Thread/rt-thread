@page page_device_uart_dm UART device model (DM)

# UART / serial DM helpers

Kconfig uses **`RT_USING_SERIAL`**; registered device names are **`uart0`**, **`uart1`**, … Implementation directory: **`components/drivers/serial/`** (serial core + controller drivers).

| Piece | Built when | Source |
| --- | --- | --- |
| Serial framework | **`RT_USING_SERIAL`** | `dev_serial.c` or `dev_serial_v2.c` |
| DM naming / bootargs parse | **`RT_USING_DM`** | `serial_dm.c` |
| OFW platform drivers (8250, PL011, …) | **`RT_USING_DM`** + **`RT_USING_SERIAL`** | `serial/device/*` (`host/Kconfig`) |

Header: **`components/drivers/include/drivers/serial_dm.h`**.

Application **`rt_device_find("uart2")`** usage: @ref page_device_uart. Early TX before probe: @ref page_device_uart_earlycon.

---

## `serial_dev_set_name`

```c
int serial_dev_set_name(struct rt_serial_device *sdev);
```

- With **`RT_USING_OFW`**, tries DTS alias id for **`serial`** then **`uart`** on **`sdev->parent.ofw_node`**.
- Otherwise uses an atomic counter seeded from **`rt_ofw_get_alias_last_id("serial")`** / **`uart`** so extra ports do not collide with aliased indices.
- Sets the parent **`rt_device`** name to **`uart%u`** via **`rt_dm_dev_set_name`**.

**`INIT_PLATFORM_EXPORT(serial_dm_naming_framework_init)`** runs before platform UART probes to initialize **`uid_min`**.

Prefer **`aliases { serial0 = &uart0 }`** or **`uart0 = &…`** in DTS so names match board docs and FinSH/console scripts.

---

## Boot argument parsing

### `serial_cfg_from_args`

```c
struct serial_configure serial_cfg_from_args(char *str);
```

Parses the **earlycon / console** option tail (after the MMIO base in **`earlycon=`** strings):

| Segment | Meaning |
| --- | --- |
| Leading digits | Baud rate (default from **`RT_SERIAL_CONFIG_DEFAULT`** if missing) |
| `n` / `o` / `e` | Parity none / odd / even |
| One digit | Data bits |
| `r` | RTS/CTS (`RT_SERIAL_FLOWCONTROL_CTSRTS`) |

Example: **`115200n8`** → 115200, no parity, 8 data bits.

If the string ends with the four-byte suffix **`OFW`**, that marker is cleared—firmware earlycon handoff so the full driver does not re-parse stale bootargs text. **Pass a writable buffer** when this path is used.

### `serial_base_from_args`

```c
void *serial_base_from_args(char *str);
```

Finds **`0x`** in the option string and parses a hexadecimal **physical base** for early bring-up (before OFW **`iomap`**).

### `serial_for_each_args`

Macro to iterate comma-separated sub-arguments in a boot string (multi-earlycon lists).

---

## Typical platform `probe` (8250 / PL011)

1. Map registers: **`rt_ofw_iomap(np, 0)`** or **`rt_dm_dev_iomap(dev, 0)`** (driver-specific).
2. **`rt_ofw_get_irq`** / **`rt_dm_dev_get_irq`** for the interrupt line.
3. Optional **`rt_clk_get`**, **`rt_reset_control_get`**, **`current-speed`**, **`reg-shift`** from DT.
4. Fill **`struct rt_serial_device`** / SoC wrapper, **`serial_dev_set_name`** (often inside **`serial8250_setup`** / driver `setup`).
5. **`rt_hw_serial_register(&serial->parent, name, flags, priv)`** — exposes **`uartN`** to applications.

Example OFW 8250: **`components/drivers/serial/device/8250/8250-ofw.c`**, **`core.c`** (`serial8250_setup`).

RX DMA: request a channel from @ref page_device_dma; completion feeds the serial ISR (**`rt_hw_serial_isr`**, events **`RT_SERIAL_EVENT_RX_DMADONE`**).

---

## Pitfalls

- **Alias vs probe order**: ports without aliases get **`uart0`**, **`uart1`** in registration order—not always DTS label order.
- **Pinctrl**: apply **`pinctrl-0`** (or board init) **before** first TX—see @ref page_device_pinctrl.
- **Console vs app**: reopening the shell UART can conflict—document exclusive use or use Serial V2 policy if enabled (**`RT_USING_SERIAL_V2`**).
- **`RT_DEVICE_CTRL_CONFIG`**: must reach hardware in the driver **`control`** / **`configure`** path or users see wrong baud after open.

---

## See also

- @ref page_device_uart — application API
- @ref page_device_uart_earlycon — FDT **`earlycon`**, **`stdout-path`**
- @ref page_device_platform — platform driver registration
- @ref page_device_dma
- `components/drivers/include/drivers/dev_serial.h`, `dev_serial_v2.h`
- `components/drivers/serial/serial_dm.c`
