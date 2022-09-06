# PSoC 6 Cortex M0+ prebuilt images

### Overview

Prebuilt application images are executed on the Cortex M0+ core of the PSoC 6 dual-core MCU.
The images are provided as C arrays ready to be compiled as part of the Cortex M4 application.
The Cortex M0+ application code is placed to internal flash by the Cortex M4 linker script.

Note: Each application image has a variant based on the hardware die (e.g.
psoc6_01, psoc6_02, psoc6_03, ...) it is supported on. An #ifdef at the top of
each .c file automatically controls which version is used so there is no need
to specify a particular image.

### Images

* [COMPONENT_CM0P_SLEEP](./COMPONENT_CM0P_SLEEP/README.md)

    This image starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x10002000
    and puts CM0+ core into a deep sleep mode.

* [COMPONENT_CM0P_CRYPTO](./COMPONENT_CM0P_CRYPTO/README.md)

    This image starts crypto server on CM0+ core,
    starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x10008000
    and puts CM0+ core into a deep sleep mode.

* [COMPONENT_CM0P_BLESS](./COMPONENT_CM0P_BLESS/README.md)

    This image starts BLE controller on CM0+ core,
    starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x10020000
    and puts CM0+ core into a deep sleep mode.

* [COMPONENT_CM0P_SECURE](./COMPONENT_CM0P_SECURE/README.md)

    This image starts CM4 core at address corresponding
    to Secure Boot policy, sets required security settings,
    initializes and executes code of Protected Register Access
    driver, puts CM0+ core into a deep sleep mode.

### More information
Use the following links for more information, as needed:
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)

---
Copyright (c) Cypress Semiconductor Corporation, 2020.
