# MTB CAT1 Peripheral Driver Library v3.2.0

Please refer to the [README.md](./README.md) and the
[PDL API Reference Manual](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/index.html)
for a complete description of the Peripheral Driver Library.

Some restrictions apply to the PSoC 64 devices configuration. Please refer to [PRA (Protected Register Access)](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__pra.html) driver documentation for the details.

## Implementation Details

* TRNG enchacements to support health monitor check.
* Bug fixes

## Build Changes

## Personalities Changes

* Updated eco-3.0.cypersonality, extclk-3.0.cypersonality, wco-3.0.cypersonality, pin-3.0.cypersonality, and sar-6.0.cypersonality

## Added Drivers

## Updated Drivers

* [SYSPM 5.91](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__syspm.html)
* [CRYPTO 2.70](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__crypto.html)

### Drivers with patch version updates

* [SegLCD 1.10.1](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__seglcd.html)

### Obsoleted part numbers

The ModusToolbox Device Configurator can not create the designs targeting the obsolete PSoC 6 part numbers.

Below is a list of PSoC 6 part numbers obsoleted in psoc6pdl release-v1.6.0, with the suggested next best alternative:

| Obsoleted part number | Next best alternative |
| :---                  | :----                 |
| CY8C624AAZI-D44       | CY8C624AAZI-S2D44     |
| CY8C624AFNI-D43       | CY8C624AFNI-S2D43     |
| CY8C624ABZI-D04       | CY8C624ABZI-S2D04     |
| CY8C624ABZI-D14       | CY8C624ABZI-S2D14     |
| CY8C624AAZI-D14       | CY8C624AAZI-S2D14     |
| CY8C6248AZI-D14       | CY8C6248AZI-S2D14     |
| CY8C6248BZI-D44       | CY8C6248BZI-S2D44     |
| CY8C6248AZI-D44       | CY8C6248AZI-S2D44     |
| CY8C6248FNI-D43       | CY8C6248FNI-S2D43     |
| CY8C624ALQI-D42       | N/A                   |

## Known Issues
* CAT1A: On soft reset, user need to reset back up domain using Cy_SysLib_ResetBackupDomain() to receive Cy_RTC_CenturyInterrupt() callback on Century roll over.
* On building with tools 2.2, user get warning related to the older version of tools used. To avoid this warning, user is advised to migrate to newer tools version or keep working with previous version of this library.  The warning generated is as follows:
  * _#warning "(Library) The referenced 'device support library' contains newer content than is supported. Either downgrade the version of the 'device support library' referenced or upgrade the version of tools being used_
* CAT1C: This release does not support D-CACHE on CAT1C platform


## Defect Fixes

See the Changelog section of each Driver in the [PDL API Reference](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/modules.html) for all fixes and updates.

## Supported Software and Tools

This version of PDL was validated for compatibility with the following Software and Tools:

| Software and Tools                                                            | Version      |
| :---                                                                          | :----        |
| [Infineon Core Library](https://github.com/Infineon/core-lib)                 | 1.3.0        |
| [Infineon HAL](https://github.com/Infineon/mtb-hal-cat1)                      | 2.2.0        |
| CMSIS                                                                         | 5.8.0        |
| GCC Compiler                                                                  | 10.3.1       |
| IAR Compiler                                                                  | 9.3          |
| ARM Compiler 6                                                                | 6.16         |
| FreeRTOS                                                                      | 10.4.303     |

## More information

* [Peripheral Driver Library README.md](./README.md)
* [Peripheral Driver Library API Reference Manual](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/index.html)
* [ModusToolbox Software Environment, Quick Start Guide, Documentation, and Videos](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
* [ModusToolbox Device Configurator Tool Guide](https://www.infineon.com/dgdl/Infineon-ModusToolbox_Device_Configurator_Guide_4-UserManual-v01_00-EN.pdf?fileId=8ac78c8c7d718a49017d99ab297631cb)
* [AN210781 Getting Started with PSoC 6 MCU with Bluetooth Low Energy (BLE) Connectivity](https://www.infineon.com/dgdl/Infineon-AN210781_Getting_Started_with_PSoC_6_MCU_with_Bluetooth_Low_Energy_(BLE)_Connectivity_on_PSoC_Creator-ApplicationNotes-v05_00-EN.pdf?fileId=8ac78c8c7cdc391c017d0d311f536528)
* [PSoC 6](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu/)
* [CYW20829](https://www.infineon.com/cms/en/product/promopages/airoc20829)
* [TV-II-BH8/BH4](https://www.infineon.com/cms/en/product/microcontroller/32-bit-traveo-t2g-arm-cortex-microcontroller/)
* [XMC7000](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc7000-industrial-microcontroller-arm-cortex-m7/)
* [Infineon](http://www.infineon.com)

---
© Cypress Semiconductor Corporation (an Infineon company), 2022.
