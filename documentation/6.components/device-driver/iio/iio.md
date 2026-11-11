@page page_device_iio Industrial I/O (IIO)

# IIO (Industrial I/O)

Device-tree **`io-channels`** binding and DM integration: @ref page_device_iio_dm.

## Overview

`drivers/iio.h` offers a small **channel discovery** API: `rt_iio_channel_get_by_index` and `rt_iio_channel_get_by_name` resolve a channel handle and index from a `rt_device`. IIO is a light abstraction for **ADC, DAC, temperature, accelerometer**, and similar sensors; data format and calibration are driver-specific.

## Usage

1. Associate consumer and provider via device tree `io-channels` / `io-channel-names` or private matching.
2. Call the `get` helpers for an opaque channel pointer and logical index, then use the provider’s read/write path (usually wrapped inside the driver).

## DM relation

Providers are commonly `platform` devices: `probe` brings up clocks, resets, and calibration, then registers the device. Phandle-based dependencies mirror Linux IIO bindings and ease porting.

## Practical limits (current API)

`drivers/iio.h` only exposes **`rt_iio_channel_get_by_index`** and **`rt_iio_channel_get_by_name`** returning an **opaque `void *`** channel cookie plus **`out_channel`** index. There is **no standard `put`** in this header—lifetime is **owned by the provider `rt_device`**; do not use the handle after the provider unregisters.

## When IIO glue helps

| Use IIO discovery when… | Skip it when… |
| --- | --- |
| Porting **Linux `io-channels`** consumers and you want matching property names. | You already have a **private `ioctl`** between two in-tree drivers. |

## Consumer flow

1. **`get_by_*`** after provider `probe` has finished (phandles resolved).
2. Pass **`out_channel`** index into **your provider’s** read/write routine (implemented alongside the ADC driver).
3. On remove, drop references to the **`rt_device`** only—no separate channel free unless your provider documents one.

## Pitfalls

- **Opaque pointer** is not a `struct iio_channel` like Linux—do not cast blindly across drivers.
- **Missing provider**: returns **`NULL`**—always check before dereference.

## See also

- `components/drivers/include/drivers/iio.h`
- Platform: `documentation/6.components/device-driver/platform/platform.md`
