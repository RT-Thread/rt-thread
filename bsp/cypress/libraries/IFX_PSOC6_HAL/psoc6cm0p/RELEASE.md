### PSoC 6 Cortex M0+ prebuilt images
Prebuilt application images are executed on the Cortex M0+ core of the PSoC 6 dual-core MCU. The images are provided as C arrays ready to be compiled as part of the Cortex M4 application. The Cortex M0+ application code is placed to internal flash by the Cortex M4 linker script.

### What's Included?
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

### What Changed?

#### v2.2.0
* CM0P_BLESS image is updated with BLESS firmware version bless-5.0.10.347

#### v2.1.4
* Rebuilt with Peripheral Driver Library (mtb-pdl-cat1) version 2.3.1

#### v2.1.3
* Rebuilt with Peripheral Driver Library (mtb-pdl-cat1) version 2.3.0

#### v2.1.2
* COMPONENT_CM0P_SECURE image updated:
  * Do not use default initialization, keep clocks configuration, set by Secure FlashBoot
  * Add supoort for `cysecuretools 3.1.x`
#### v2.1.1
* Rebuild with Peripheral Driver Library (mtb-pdl-cat1) version 2.2.0.
#### v2.1.0
* COMPONENT_CM0P_SECURE image updated to include:
  * WDT management per policy settings
  * Support swap upgrade mode in CypressBootloader
  * External clocks and SRAM power modes management per policy settings
* Rebuild with Peripheral Driver Library (mtb-pdl-cat1) version 2.1.0.
#### v2.0.1
* COMPONENT_CM0P_BLESS image was updated to use BLESS 3.50 Middleware library.
#### v2.0.0
* Rebuilt with Peripheral Driver Library (mtb-pdl-cat1) version 2.0.0.
#### v1.2.1
* Rebuilt with PSoC 6 Peripheral Driver Library (psoc6pdl) version 1.6.1.
#### v1.2.0
* New secure image (COMPONENT_CM0P_SECURE)
* Rebuilt with PSoC 6 Peripheral Driver Library (psoc6pdl) version 1.6.0.
#### v1.1.2
* Rebuilt with PSoC 6 Peripheral Driver Library (psoc6pdl) version 1.5.0.
* COMPONENT_CM0P_BLESS image was updated to use BLESS 3.40 Middleware library. This fixes [CVE-2019-16336](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-16336) and [CVE-2019-17061](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-17061) Vulnerabilities.
#### v1.1.1
* Rebuilt with PSoC 6 Peripheral Driver Library (psoc6pdl) version 1.4.1.
#### v1.1.0
* Rebuilt with PSoC 6 Peripheral Driver Library (psoc6pdl) version 1.4.0.
* COMPONENT_CM0P_BLESS image was updated to use BLESS 3.30 Middleware library
* Increased memory slot in COMPONENT_CM0P_CRYPTO from 32K to 40K

Note: This version is incompatible with PDL versions prior to 1.4.0 when using DeepSleep and UDB based SDIO.
#### v1.0.0
* Initial release

### Product/Asset Specific Instructions
To pick which image is used in an application update the COMPONENTS variable in the Board Support Package (BSP)'s makefile. Depending on which image is selected, an update to the BSPs linker script may also be required to allocate the proper space for the CM0+ image and that the CM4 has the starting address listed above.

### Supported Software and Tools
This version of the (PSoC 6 Cortex M0+ prebuilt images) was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| GCC Compiler                              | 7.4     |
| IAR Compiler                              | 8.32    |
| ARM Compiler 6                            | 6.11    |

### More information
Use the following links for more information, as needed:
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)

---
Copyright (c) Cypress Semiconductor Corporation, 2020.
