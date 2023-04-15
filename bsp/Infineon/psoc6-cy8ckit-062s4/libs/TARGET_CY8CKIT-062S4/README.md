# CY8CKIT-062S4 BSP

## Overview

The PSoC™ 62S4 Pioneer Kit is a low-cost hardware platform that enables design and debug of the PSoC™ 62S4 Line (CY8C6244LQI-S4D92).

![](docs/html/board.png)

To use code from the BSP, simply include a reference to `cybsp.h`.

## Features

### Kit Features:

* Delivers dual-cores, with a 150-MHz Arm Cortex-M4 as the primary application processor and a 100-MHz Arm Cortex-M0+ as the secondary processor. 
* 256-KB Flash and 128-KB SRAM for customer application on CM4
* One-time-programmable (OTP) 1-Kb eFuse array
* Two 12-bit 2-Msps SAR ADCs with synchronized sampling, differential and single-ended modes, 16-channel sequencer with result averaging, and Deep Sleep operation 
* Two opamps with low-power operation modes and Two low-power comparators available in Deep Sleep and Hibernate modes
* Onboard Thermistor and Ambient Light Sensor. 
* Serial memory interface
* Industry-leading CAPSENSE
* Ambient Light Sensor
* Thermistor

### Kit Contents:

* CY8CKIT-062S4 evaluation board
* USB Type-A to Micro-B cable
* Quick Start Guide
* Six jumper wires (5 inches each)

## BSP Configuration

The BSP has a few hooks that allow its behavior to be configured. Some of these items are enabled by default while others must be explicitly enabled. Items enabled by default are specified in the CY8CKIT-062S4.mk file. The items that are enabled can be changed by creating a custom BSP or by editing the application makefile.

Components:
* Device specific category reference (e.g.: CAT1) - This component, enabled by default, pulls in any device specific code for this board.

Defines:
* CYBSP_WIFI_CAPABLE - This define, disabled by default, causes the BSP to initialize the interface to an onboard wireless chip if it has one.
* CY_USING_HAL - This define, enabled by default, specifies that the HAL is intended to be used by the application. This will cause the BSP to include the applicable header file and to initialize the system level drivers.
* CYBSP_CUSTOM_SYSCLK_PM_CALLBACK - This define, disabled by default, causes the BSP to skip registering its default SysClk Power Management callback, if any, and instead to invoke the application-defined function `cybsp_register_custom_sysclk_pm_callback` to register an application-specific callback.

### Clock Configuration

| Clock    | Source    | Output Frequency |
|----------|-----------|------------------|
| FLL      | IMO       | 100.0 MHz        |
| PLL      | IMO       | 48.0 MHz         |
| CLK_HF0  | CLK_PATH0 | 100 MHz          |

### Power Configuration

* System Active Power Mode: LP
* System Idle Power Mode: Deep Sleep
* VDDA Voltage: 3300 mV
* VDDD Voltage: 3300 mV

See the [BSP Setttings][settings] for additional board specific configuration settings.

## API Reference Manual

The CY8CKIT-062S4 Board Support Package provides a set of APIs to configure, initialize and use the board resources.

See the [BSP API Reference Manual][api] for the complete list of the provided interfaces.

## More information
* [CY8CKIT-062S4 BSP API Reference Manual][api]
* [CY8CKIT-062S4 Documentation](http://www.cypress.com/CY8CKIT-062S4)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

[api]: https://infineon.github.io/TARGET_CY8CKIT-062S4/html/modules.html
[settings]: https://infineon.github.io/TARGET_CY8CKIT-062S4/html/md_bsp_settings.html

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2022.