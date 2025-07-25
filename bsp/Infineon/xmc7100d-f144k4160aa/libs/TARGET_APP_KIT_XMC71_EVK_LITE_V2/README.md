# KIT_XMC71_EVK_LITE_V2 BSP

## Overview

The KIT_XMC71_EVK_LITE_V2, a 100-pin evaluation board is based on the XMC7100 family of devices. XMC7100 MCU is designed for  industrial applications. The evaluation board carries a XMC7100D microcontroller,and headers compatible with Arduino for interfacing Arduino shields. In addition, the board features an on-board programmer/debugger (KitProg3),  a 512-Mbit QSPI NOR flash, CAN FD transceiver, Ethernet PHY transceiver with RJ45 connector interface,  a Shield2Go connector interface and MikroBUS connector interface, two user LEDs, one potentiometer, and two push buttons.  The board supports operating voltages from 3.3 V to 5.0 V for XMC7100D device.

**Note:**
KIT_XMC71_EVK_LITE_V2 is the board support package for the XMC7100 Lite Evaluation board  with XMC7100D-F100K4160 MCU. Replace the XMC7100D-F176K4160 (default device) on the  XMC7100 Lite Evaluation board with XMC7100D-F100K4160 to use this BSP.



To use code from the BSP, simply include a reference to `cybsp.h`.

## Features

### Kit Features:

* XMC7100D-F100K4160 8MB Flash 100-pin TEQFP device
* Programming interface (Arm® Standard JTAG, Cortex® Debug + ETM with Arm® ETM Mictor)
* Reset control with manual reset switch and voltage supervision
* CAN FD interface
* Ethernet interface
* One 512-Mbit external Quad SPI NOR Flash that provides a fast, expandable memory for data and code
* KitProg3 on-board SWD programmer/debugger, USB-UART and USB-I2C bridge functionality
* A Shield2Go connector interface and a MikroBUS connector interface
* Selectable input supply voltages of 3.3 V and 5.0 V for the XMC7100D device
* Two user LEDs, two user buttons, and a reset button for the XMC7100D device
* A potentiometer which can be used to simulate analog sensor output
* A mode button and a mode LED for KitProg3

### Kit Contents:

* XMC7100 evaluation board
* USB Type-A to Micro-B cable
* Quick start guide (printed on the kit package)

## BSP Configuration

The BSP has a few hooks that allow its behavior to be configured. Some of these items are enabled by default while others must be explicitly enabled. Items enabled by default are specified in the KIT_XMC71_EVK_LITE_V2.mk file. The items that are enabled can be changed by creating a custom BSP or by editing the application makefile.

Components:
* Device specific category reference (e.g.: CAT1) - This component, enabled by default, pulls in any device specific code for this board.

Defines:
* CYBSP_WIFI_CAPABLE - This define, disabled by default, causes the BSP to initialize the interface to an onboard wireless chip if it has one.
* CY_USING_HAL - This define, enabled by default, specifies that the HAL is intended to be used by the application. This will cause the BSP to include the applicable header file and to initialize the system level drivers.
* CYBSP_CUSTOM_SYSCLK_PM_CALLBACK - This define, disabled by default, causes the BSP to skip registering its default SysClk Power Management callback, if any, and instead to invoke the application-defined function `cybsp_register_custom_sysclk_pm_callback` to register an application-specific callback.

### Clock Configuration

| Clock    | Source    | Output Frequency |
|----------|-----------|------------------|
| FLL      | ECO       | 100.0 MHz        |
| PLL      | ECO       | 200.0 MHz        |
| CLK_HF0  | CLK_PATH0 | 100 MHz          |
| CLK_HF1  | CLK_PATH1 | 250 MHz          |
| CLK_HF2  | CLK_PATH4 | 100 MHz          |
| CLK_HF3  | CLK_PATH4 | 100 MHz          |
| CLK_HF4  | CLK_PATH4 | 50 MHz           |
| CLK_HF5  | CLK_PATH2 | 125 MHz          |
| CLK_HF6  | CLK_PATH4 | 200 MHz          |
| CLK_HF7  | CLK_PATH5 | 0 MHz            |

### Power Configuration

* System Idle Power Mode: Deep Sleep
* VDDA Voltage: 3300 mV
* VDDD Voltage: 3300 mV

See the [BSP Setttings][settings] for additional board specific configuration settings.

## API Reference Manual

The KIT_XMC71_EVK_LITE_V2 Board Support Package provides a set of APIs to configure, initialize and use the board resources.

See the [BSP API Reference Manual][api] for the complete list of the provided interfaces.

## More information
* [KIT_XMC71_EVK_LITE_V2 BSP API Reference Manual][api]
* [KIT_XMC71_EVK_LITE_V2 Documentation](https://www.infineon.com/KIT_XMC71_EVK_LITE_V1)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

[api]: https://infineon.github.io/TARGET_KIT_XMC71_EVK_LITE_V2/html/modules.html
[settings]: https://infineon.github.io/TARGET_KIT_XMC71_EVK_LITE_V2/html/md_bsp_settings.html

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2024.