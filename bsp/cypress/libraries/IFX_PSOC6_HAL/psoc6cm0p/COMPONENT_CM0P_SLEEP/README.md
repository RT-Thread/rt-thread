# PSoC 6 Cortex M0+ DeepSleep prebuilt image (CM0P_SLEEP)

### Overview
DeepSleep prebuilt application image is executed on the Cortex M0+ core of the PSoC 6 BLE dual-core MCU.
The image is provided as C array ready to be compiled as part of the Cortex M4 application.
The Cortex M0+ application code is placed to internal flash by the Cortex M4 linker script.

DeepSleep prebuilt image executes the following steps:
- starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x10002000
- puts the CM0+ core into Deep Sleep.

### Usage

This image is used by default by all Cypress BSPs that target PSOC6 Dual-Core MCU.

To use this image in the custom BSP, adjust the BSP target makefile to
add the COMPONENT_CM0P_SLEEP directory to the list of components
discovered by ModusToolbox build system:

```
COMPONENTS+=CM0P_SLEEP
```

Make sure there is a single CM0P_* component included in the COMPONENTS list.

---
Copyright (c) Cypress Semiconductor Corporation, 2019.
