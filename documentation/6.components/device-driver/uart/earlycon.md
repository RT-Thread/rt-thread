@page page_device_uart_earlycon UART early console

# Early console (before full UART driver)

Early output runs **before** the normal **`rt_serial_device`** / **`rt_hw_serial_register`** path: a minimal **putc** hook is installed from FDT **`/chosen`** **`stdout-path`** and/or **`earlycon=`** in **`bootargs`**.

Sources:

- **8250 / NS16550 / DW APB**: `components/drivers/serial/device/8250/early.c`
- **Hypervisor console**: `components/drivers/serial/device/serial-early-hvc.c`

Baud/format/base parsing: **`serial_cfg_from_args`**, **`serial_base_from_args`** in **`serial_dm.c`** — see @ref page_device_uart_dm.

---

## 8250 earlycon (`early.c`)

### Registration

**`RT_FDT_EARLYCON_EXPORT`** entries (examples):

| Symbol | `earlycon` name | Example compatible |
| --- | --- | --- |
| `ns16550` | `uart8250` | `ns16550`, `ns16550a` |
| `dw8250` | `uart8250` | `snps,dw-apb-uart` |
| `tegra20` | `uart8250` | `nvidia,tegra20-uart` |
| `bcm2835aux` | `uart8250` | `brcm,bcm2835-aux-uart` |

Bootargs example:

```text
earlycon=uart8250,mmio32,0x10009000,115200n8
```

The FDT earlycon core passes **`options`** into **`serial8250_early_fdt_setup`**, which calls **`serial8250_config`** then maps MMIO with **`rt_ioremap_early`**.

### `serial8250_early_putc`

Polls **UART LSR** (**TEMT | THRE**) after writing **UART_TX**—safe with interrupts masked. Installed as **`con->console_putc`**.

### Lifecycle: `serial8250_early_kick`

| `why` | Action |
| --- | --- |
| `FDT_EARLYCON_KICK_UPDATE` | **`rt_ioremap`** full mapping when switching from early to runtime map |
| `FDT_EARLYCON_KICK_COMPLETED` | **`rt_iounmap`** early mapping after the platform driver owns the port |

If **`config.baud_rate`** is zero at setup, firmware already programmed the UART; the code only clears **IER**.

### Divisor

When **`serial->freq`** is set, **`init_serial`** programs **DLL/DLM** from **`freq / (16 * baud_rate)`**.

---

## HVC earlycon (`serial-early-hvc.c`)

```c
RT_FDT_EARLYCON_EXPORT(hvc, "hvc", "vmrt-thread,hvc-console", hvc_early_setup);
```

- **`hvc_early_setup`** calls **`rt_hv_version`**; on success **`console_putc`** → **`rt_hv_console(c)`**.
- No MMIO **`reg`**—hypervisor console path.

---

## Handoff to full driver

1. Earlycon prints via **`rt_kprintf`** / **`console_putc`**.
2. Platform probe (e.g. **`8250-ofw`**) maps the same UART, **`serial_dev_set_name`**, **`rt_hw_serial_register`** → **`uartN`** for apps.
3. Early mapping is released on **`FDT_EARLYCON_KICK_COMPLETED`** when the serial core finishes transition.

Do not leave early **putc** and the full driver writing the same UART without the kick handshake.

---

## Pitfalls

- **`reg-shift`**: early defaults may differ from DT **`reg-shift`** in probe—keep them consistent for your IP.
- **Options buffer**: **`serial_cfg_from_args`** may modify the string ( **`OFW`** suffix).
- **RX**: early path is **TX-only**; input needs the full UART driver or another console backend.

---

## See also

- @ref page_device_uart_dm
- @ref page_device_uart
- @ref page_device_ofw — **`chosen`**, **`stdout-path`**
- `components/drivers/serial/device/8250/core.c`, `8250-ofw.c`
