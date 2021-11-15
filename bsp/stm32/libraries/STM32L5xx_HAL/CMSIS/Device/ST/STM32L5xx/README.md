# STM32CubeL5 CMSIS Device MCU Component

## Overview

**STM32Cube** is an STMicroelectronics original initiative to ease the developers life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform, delivered for each STM32 series.
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product
   * The STM32 HAL-LL drivers : an abstraction drivers layer, the API ensuring maximized portability across the STM32 portfolio
   * The BSP Drivers of each evaluation or demonstration board provided by this STM32 series
   * A consistent set of middlewares components such as RTOS, USB, FatFS, Graphics, STM32_TouchSensing_Library ...
   * A full set of software projects (basic examples, applications or demonstrations) for each board provided by this STM32 series

Two models of publication are proposed for the STM32Cube embedded software :
   * The monolithic **MCU Package** : all STM32Cube software modules of one STM32 series are present (Drivers, Middlewares, Projects, Utilities) in the repo (usual name **STM32Cubexx**, xx corresponding to the STM32 series)
   * The **MCU component** : progressively from November 2019, each STM32Cube software module being part of the STM32Cube MCU Package, will be delivered as an individual repo, allowing the user to select and get only the required software functions.

## Description

This **cmsis_device_l5** MCU component repo is one element of the STM32CubeL5 MCU embedded software package, providing the **cmsis device** part.

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/cmsis_device_l5/blob/master/Release_Notes.html).

## Compatibility information

In this table, you can find the successive versions of this CMSIS Device component, in-line with the corresponding versions of the full MCU package:

CMSIS Device L5 | CMSIS Core | Was delivered in the full MCU package
--------------- | ---------- | -------------------------------------
Tag v1.0.0 | Tag v5.4.0_cm33 | Tag v1.1.0
Tag v1.0.2 | Tag v5.4.0_cm33 | Tag v1.2.0
Tag v1.0.3 | Tag v5.6.0_cm33 | Tag v1.3.0
Tag v1.0.4 | Tag v5.6.0_cm33 | Tag v1.4.0 (and following, if any, till next tag)

The full **STM32CubeL5** MCU package is available [here](https://github.com/STMicroelectronics/STM32CubeL5).

## Troubleshooting

If you have any issue with the **Software content** of this repo, you can [file an issue on Github](https://github.com/STMicroelectronics/cmsis_device_l5/issues/new).

For any other question related to the product, the tools, the environment, you can submit a topic on the [ST Community/STM32 MCUs forum](https://community.st.com/s/group/0F90X000000AXsASAW/stm32-mcus).