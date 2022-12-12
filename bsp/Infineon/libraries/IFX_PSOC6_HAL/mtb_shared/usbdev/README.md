# USB Device Middleware Library

## Overview

The USB Device middleware provides a full-speed
[USB 2.0 Chapter 9 specification](https://usb.org/document-library/usb-20-specification)
compliant device framework. It uses the USBFS driver from
CAT1A/CAT2 Peripheral Driver Library to interface with the hardware.
The middleware provides support for Audio, CDC, HID and Vendor classes.
It also enables implementing support for other classes. The USB Configurator
tool makes it easy to construct a USB Device descriptor.

## Features

* USB Full-Speed Device Framework
* USB Device Configurator
* The following USB Classes are supported:
  * Audio Class
  * CDC: Communication Device Class
  * HID: Human Interface Device
* Adding Custom Class Support
* Vendor-Specific Requests Support
* Power Status Reporting for Self-Powered Devices
* Blocking API Timeout Function Redefinition
* Compliance with [MISRA-C:2012 coding standard](https://www.misra.org.uk/)

## USB Device Specific Instructions

The user must ensure that the parameters selected in the USB Device personality
are aligned with the descriptor configuration in the USB Configurator, because
there is no connection between the USB Device personality in the Device
Configurator and USB Configurator.

Specifically, parameter "Endpoints Mask" in the USB personality must be aligned
with the endpoints selected in the USB Configurator. If DMA Automatic mode is
selected, parameter  "Endpoint Buffer Size" must be aligned with the total size
of the endpoint buffers allocated in the USB Configurator.

## Quick Start

Configure the USB Device using the ModusToolbox™ USB Device personality and
USB Device Configurator. Refer to the
[API Reference Quick Start Guide](https://infineon.github.io/usbdev/usbfs_dev_api_reference_manual/html/index.html)

## More information

The following links provide more information:

* [USB Device Middleware Library Release Notes](./RELEASE.md)
* [USB Device Middleware Library API Reference](https://infineon.github.io/usbdev/usbfs_dev_api_reference_manual/html/index.html)
* [CAT1 Peripheral Driver Library API Reference](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/index.html)
* [CAT2 Peripheral Driver Library API Reference](https://infineon.github.io/mtb-pdl-cat2/pdl_api_reference_manual/html/index.html)
* [ModusToolbox™ Software Environment, Quick Start Guide, Documentation, and Videos](https://www.cypress.com/products/modustoolbox-software-environment)
* [PSoC™ 6 SDK Examples](https://github.com/Infineon?q=mtb-example-psoc6%20NOT%20Deprecated)
* [ModusToolbox™ USB Configurator Tool Guide](https://www.cypress.com/ModusToolboxUSBConfig)
* [ModusToolbox™ Device Configurator Tool Guide](https://www.cypress.com/ModusToolboxDeviceConfig)
* [PSoC™ 6 WiFi-BT Pioneer Kit](http://www.cypress.com/CY8CKIT-062-WiFi-BT)
* [PSoC™ 6 Wi-Fi BT Prototyping Kit](http://www.cypress.com/cy8cproto-062-4343w)
* [PSoC™ 6 MCU Datasheets](http://www.cypress.com/psoc6ds)
* [PSoC™ 6 MCU Application Notes](http://www.cypress.com/psoc6an)
* [PSoC™ 6 MCU Technical Reference Manuals](http://www.cypress.com/psoc6trm)
* [PMG1-S2 Prototyping Kit](http://www.cypress.com/CY7112)
* [PMG1-S3 Prototyping Kit](http://www.cypress.com/CY7113)
* [PMG1 Datasheets](https://www.cypress.com/PMG1DS)
* [CYPRESS™ Semiconductor](http://www.cypress.com)

---
© 2019-2021, CYPRESS™ Semiconductor Corporation (an Infineon company)
or an affiliate of CYPRESS™ Semiconductor Corporation.
