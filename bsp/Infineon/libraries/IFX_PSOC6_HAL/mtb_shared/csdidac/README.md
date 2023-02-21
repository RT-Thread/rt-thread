# Cypress CSDIDAC Middleware Library

### Overview
The CSDIDAC provides an API that allows the CSD HW block IDAC functionality.
It can be useful for devices that do not include other DAC options. 

### Features
* A two-channel IDAC with the 7-bit resolution
* The IDAC A and IDAC B channels can be enabled/disabled independently
* The IDAC A and IDAC B channels can be configured with sourcing/sinking current independently
* The IDAC A and IDAC B channels can be joined to increase a maximum output current
* The IDAC A and IDAC B channels can be enabled/disabled simultaneously by using the CY_CSDIDAC_AB option
* The 0 to 609.6 uA (609600 nA) current range is available for each IDAC channel
* Each IDAC can use independently one of the six available LSB depending on a desired output current

### Quick Start
The CSDIDAC could be configured by the ModusToolbox CSD personality. Refer to the [API Reference Guide Configuration Considerations](https://cypresssemiconductorco.github.io/csdidac/csdidac_api_reference_manual/html/index.html#group_csdidac_configuration).


### More information
The following resources contain more information:
* [CSDIDAC Middleware RELEASE.md](./RELEASE.md)
* [CSDIDAC Middleware API Reference Guide](https://cypresssemiconductorco.github.io/csdidac/csdidac_api_reference_manual/html/index.html)
* [ModusToolbox Software Environment, Quick Start Guide, Documentation, and Videos](https://www.cypress.com/products/modustoolbox-software-environment)
* [CSDIDAC Middleware Code Example for MBED OS](https://github.com/cypresssemiconductorco/mbed-os-example-csdidac)
* [ModusToolbox Device Configurator Tool Guide](https://www.cypress.com/ModusToolboxDeviceConfig)
* [CapSense Middleware API Reference Guide](https://cypresssemiconductorco.github.io/capsense/capsense_api_reference_manual/html/index.html)
* [CSDADC Middleware API Reference Guide](https://cypresssemiconductorco.github.io/csdadc/csdadc_api_reference_manual/html/index.html)
* [PSoC 6 Technical Reference Manual](https://www.cypress.com/documentation/technical-reference-manuals/psoc-6-mcu-psoc-63-ble-architecture-technical-reference)
* [PSoC 63 with BLE Datasheet Programmable System-on-Chip datasheet](http://www.cypress.com/ds218787)
* [PSoC 4000S Family: PSoC 4 Architecture Technical Reference Manual (TRM)](https://www.cypress.com/documentation/technical-reference-manuals/psoc-4000s-family-psoc-4-architecture-technical-reference)
* [PSoC 4100S and PSoC 4100S Plus: PSoC 4 Architecture Technical Reference Manual (TRM)](https://www.cypress.com/documentation/technical-reference-manuals/psoc-4100s-and-psoc-4100s-plus-psoc-4-architecture)
* [Cypress Semiconductor](http://www.cypress.com)
  
---
© Cypress Semiconductor Corporation, 2019.
