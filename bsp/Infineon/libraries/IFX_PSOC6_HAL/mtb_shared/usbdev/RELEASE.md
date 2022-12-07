# USB Device Middleware Library 2.10

## What's Included?

For a complete description of the USB Device Middleware, refer to
[README.md](./README.md) and the
[USB Device API Reference](https://infineon.github.io/usbdev/usbfs_dev_api_reference_manual/html/index.html).
The revision history of the USB Device Middleware is also available in the
[API Reference Changelog](https://infineon.github.io/usbdev/usbfs_dev_api_reference_manual/html/index.html#group_usb_dev_changelog).

New in this release:

* Updated the middleware to support configurations without any data endpoints.
* Added support for the PMG1 Family of MCUs.
* Updated the middleware to comply with MISRA-C:2012 standard.

## Defect Fixes

* Fixed an issue in vendor class request handling.

## USB Device Specific Instructions

The user must ensure that the parameters selected in the USB Device personality
are aligned with the descriptor configuration in the USB Configurator, because
there is no connection between the USB Device personality in the Device
Configurator and USB Configurator.

Specifically, parameter "Endpoints Mask" in the USB personality must be aligned
with the endpoints selected in the USB Configurator. If DMA Automatic mode is
selected, parameter  "Endpoint Buffer Size" must be aligned with the total size
of the endpoint buffers allocated in the USB Configurator.

## Known Issues

| Problem | Workaround |
| ------- | ---------- |
| The USB Device ignores LPM requests after wake up from Deep Sleep. | Call USBFS driver Cy_USBFS_Dev_Drv_Lpm_SetResponse() after calling Cy_USBFS_Dev_Drv_Resume() to restore response to the LPM packets. |
| The USB Device modes with DMA do not work after wake up from Deep Sleep, due to incorrect restore of the ARB_CFG register. | Save ARB_CFG values before entering Deep Sleep and restore it after calling of Cy_USBFS_Dev_Drv_Resume. |

## Supported Software and Tools

This version of the USB Device Middleware was validated for compatibility with the following Software and Tools:

| Software and Tools                                             | Version |
| :---                                                           | :----:  |
| ModusToolbox™ Software Environment                             | 2.3     |
| - ModusToolbox™ Device Configurator                            | 3.0     |
| - ModusToolbox™ USB Device Personality in Device Configurator  | 1.1     |
| - ModusToolbox™ USB Device Configurator                        | 2.30    |
| MTB CAT1A Peripheral Driver Library (PDL)                      | 2.2.1   |
| MTB CAT2 Peripheral Driver Library (PDL)                       | 1.2.0   |
| GCC Compiler                                                   | 9.3.1   |
| IAR Compiler                                                   | 8.42.2  |
| ARM Compiler 6                                                 | 6.16    |

## More information

For a more information, refer to [README.md](./README.md)

---
© 2019-2021, CYPRESS™ Semiconductor Corporation (an Infineon company)
or an affiliate of CYPRESS™ Semiconductor Corporation.
