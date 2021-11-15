# STM32CubeU5 CMSIS Device MCU Component

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/cmsis_device_u5.svg?color=brightgreen)

## Overview

**STM32Cube** is an STMicroelectronics original initiative to ease the developers life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform delivered for each STM32 series.
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product.
   * The STM32 HAL-LL drivers, an abstraction layer offering a set of APIs ensuring maximized portability across the STM32 portfolio.
   * The BSP drivers of each evaluation, demonstration or nucleo board provided for this STM32 series.
   * A consistent set of middleware libraries such as RTOS, USB, FatFS, graphics, touch sensing library...
   * A full set of software projects (basic examples, applications, and demonstrations) for each board provided for this STM32 series.

Two models of publication are proposed for the STM32Cube embedded software:
   * The monolithic **MCU Package**: all STM32Cube software modules of one STM32 series are present (Drivers, Middleware, Projects, Utilities) in the repository (usual name **STM32Cubexx**, xx corresponding to the STM32 series).
   * The **MCU component**: each STM32Cube software module being part of the STM32Cube MCU Package, is delivered as an individual repository, allowing the user to select and get only the required software functions.
   
## Description

This **cmsis_device_u5** MCU component repo is one element of the STM32CubeU5 MCU embedded software package, providing the **cmsis device** part.

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/cmsis_device_u5/blob/main/Release_Notes.html).

## Compatibility information

In this table, you can find the successive versions of this CMSIS Device component, in-line with the corresponding versions of the full MCU package:

CMSIS Device U5 | CMSIS Core      | Was delivered in the full MCU package
--------------- | --------------- | -------------------------------------
Tag v1.0.0      | Tag v5.6.0_cm33 | Tag v1.0.0 (and following, if any, till next CMSIS tag)
Tag v1.0.1      | Tag v5.6.0_cm33 | Tag v1.0.1 (and following, if any, till next CMSIS tag)


The full **STM32CubeU5** MCU package is available [here](https://github.com/STMicroelectronics/STM32CubeU5).

## Troubleshooting

Please refer to the [CONTRIBUTING.md](CONTRIBUTING.md) guide.
