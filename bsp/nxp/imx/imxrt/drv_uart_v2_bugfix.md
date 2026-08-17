# Bug Fix: Serial V2 Driver (`drv_uart_v2.c`) for imxrt BSP

## Background

When switching from `RT_USING_SERIAL_V1` to `RT_USING_SERIAL_V2` in `rtconfig.h`, the serial
console (e.g., `uart1`) did not produce any output and the system appeared to hang. V1 worked
correctly under the same hardware configuration.

---

## Bug 1: `ops->transmit` Was NULL Without DMA (Critical)

### Root Cause

The Serial V2 framework (`dev_serial_v2.c`) **always** calls `serial->ops->transmit()` when
sending data, regardless of whether DMA is used. In the original driver the `imxrt_transmit`
function and its assignment in `imxrt_uart_ops` were both wrapped inside:

```c
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
...
#endif
```

When DMA was not enabled, `ops.transmit` was set to `RT_NULL`, causing a null-pointer dereference
the first time the framework tried to transmit data.

In contrast, the Serial V1 `rt_uart_ops` ends with `dma_transmit`, which is only called by the
V1 framework when DMA is explicitly requested, so a NULL value there caused no crash.

### Fix

Move `imxrt_transmit` outside the DMA preprocessor guard so it is always compiled and always
assigned to `imxrt_uart_ops.transmit`. The DMA-specific path is kept inside the function with
an inner `#ifdef`:

```c
static rt_ssize_t imxrt_transmit(struct rt_serial_device *serial,
                                 rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    struct imxrt_uart *uart = rt_container_of(serial, struct imxrt_uart, serial);

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_DMA)
    if (uart->dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        /* ... DMA TX path ... */
    }
#endif

    if (size == 0)
    {
        /* size == 0: V2 signals "kick TX interrupt to drain ring buffer" */
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
        return 0;
    }

    /* Blocking polled transmit for non-DMA path */
    rt_uint8_t *ptr = buf;
    rt_size_t sent = size;
    while (sent--)
    {
        LPUART_WriteByte(uart->uart_base, *ptr++);
        while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag))
            ;
    }
    return (rt_ssize_t)(ptr - buf);
}

static const struct rt_uart_ops imxrt_uart_ops = {
    imxrt_configure,
    imxrt_control,
    imxrt_putc,
    imxrt_getc,
    imxrt_transmit,   /* always valid, never NULL */
};
```

---

## Bug 2: Spurious `RT_SERIAL_EVENT_TX_DONE` in ISR (Secondary)

### Root Cause

The original ISR fired `RT_SERIAL_EVENT_TX_DONE` whenever `kLPUART_TxDataRegEmptyFlag` was set:

```c
if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag)
{
    LPUART_DisableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DONE);
}
```

`kLPUART_TxDataRegEmptyFlag` is a hardware status flag that is **always set** when the TX data
register is empty (i.e., essentially always when the UART is idle). This caused `TX_DONE` to be
reported on every ISR entry even when no transmission was in progress, confusing the V2 upper
layer.

### Fix

Gate the TX_DONE path on whether the TX empty interrupt is actually enabled:

```c
if ((LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag) &&
    (LPUART_GetEnabledInterrupts(uart->uart_base) & kLPUART_TxDataRegEmptyInterruptEnable))
{
    LPUART_DisableInterrupts(uart->uart_base, kLPUART_TxDataRegEmptyInterruptEnable);
    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DONE);
}
```

This mirrors the standard pattern used in most RT-Thread LPUART drivers.

---

## Summary

| # | File | Issue | Impact |
|---|------|-------|--------|
| 1 | `drv_uart_v2.c` | `ops->transmit` was `NULL` without DMA | Null-pointer crash, no output with Serial V2 |
| 2 | `drv_uart_v2.c` | TX_DONE fired unconditionally on every ISR | Spurious TX completion events, broken transmit flow |
