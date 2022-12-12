# MTB CAT1 Peripheral Driver Library v2.4.0

Please refer to the [README.md](./README.md) and the
[PDL API Reference Manual](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/index.html)
for a complete description of the Peripheral Driver Library.

Some restrictions apply to the PSoC 64 devices configuration. Please refer to [PRA (Protected Register Access)](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__pra.html) driver documentation for the details.

## New Features

* Support for CAT1B device. Please refer [CYW20829](https://www.infineon.com/cms/en/product/promopages/airoc20829)
* New PSoC 6A 256K MPNs added: CY8C6244AZQ-S4D92, CY8C6244LQQ-S4D92, CY8C6244AZQ-S4D93, CY8C6144AZQ-S4F92, CY8C6144LQQ-S4F92, CY8C6144AZQ-S4F93, CY8C4588AZQ-H685, CY8C4588AZQ-H686

## Build Changes

## Personalities Changes

* Updated Personalities: canfd-1.0, coex-1.0, counter_v2-1.0, lpcomp-1.0, pwm_ver2-1.0, quaddec_ver2-1.0, saradc-1.0, shiftreg_v2-1.0, smartio-1.0, debug-1.0, power-1.3, sysclock-1.2, tickclk-1.0
* New Personalities: adcmic-0.1, canfd-2.0, ezi2c-2.0, i2c-3.0, keyscan-1.0, lin-1.0, mcwdt-2.0, pdm_pcm-2.0, rtc-2.0, smartio-2.0, smif_ver2-1.0, spi-2.0, tdm-1.0, uart-2.0, althf-1.1, bakclk-2.0, dma-2.0, extclk-2.0, fll-3.0, hfclk-2.0, hvilo-2.0, iho-1.0, imo-2.0, lfclk-2.0, mfclk-2.0, mfo-2.0, pathmux-2.0, pclk-2.0, pilo-2.0, pin_intrinsic-2.0, pin-2.0, power-2.0, pumpclk 2.0, sysclock-2.0, tickclk-2.0, timerclk-2.0, wco-2.0

## Added Drivers

Following drivers are added for CAT1B device support:
* [ADC MIC](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__adcmic.html)
* [Cryptolite](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__cryptolite.html)
* [KeyScan](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__keyscan.html)
* [LIN](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__lin.html)
* [PDM-PCM Converter V2](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__pdm__pcm__v2.html)
* [TDM/I2S](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__tdm.html)
* [Startup CAT1B](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__system__config__cm33.html)


## Updated Drivers

* [CRYPTO 2.50](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__crypto.html)
* [CSD 1.20](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__csd.html)
* [DMA 2.50](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__dma.html)
* [DMAC 1.30](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__dmac.html)
* [EFUSE 2.10](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__efuse.html)
* [FLASH 3.60](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__flash.html)
* [GPIO 1.60](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__gpio.html)
* [I2S 2.30](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__i2s.html)
* [IPC 1.70](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__ipc.html)
* [LPCOMP 1.40](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__lpcomp.html)
* [LVD 1.50](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__lvd.html)
* [MCWDT 1.60](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__mcwdt.html)
* [MCWDT 1.60](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__mcwdt.html)
* [PROT 1.70](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__prot.html)
* [RTC 2.60](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__rtc.html)
* [SCB 2.90](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__scb.html)
* [SDHOST 2.00](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__sd__host.html)
* [SMIF 2.30](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__smif.html)
* [SYSCLK 3.40](https://cypresssemiconductorco.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__sysclk.html)
* [SYSINT 1.70](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__sysint.html)
* [SYSLIB 3.10](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__syslib.html)
* [SYSPM 5.70](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__syspm.html)
* [SYSTICK 1.50](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__arm__system__timer.html)
* [TCPWM 1.40](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__tcpwm.html)
* [TRIGMUX 1.40](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__trigmux.html)
* [WDT 1.40](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__wdt.html)


### Drivers with patch version updates

* [PDM/PCM 2.30.1](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/group__group__pdm__pcm.html)

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


## Defect Fixes

See the Changelog section of each Driver in the [PDL API Reference](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/modules.html) for all fixes and updates.

## Supported Software and Tools

This version of PDL was validated for compatibility with the following Software and Tools:

| Software and Tools                                                            | Version      |
| :---                                                                          | :----        |
| [Infineon Core Library](https://github.com/Infineon/core-lib)                 | 1.3.0        |
| [Infineon HAL](https://github.com/Infineon/mtb-hal-cat1)                      | 2.0.1        |
| CMSIS-Core(M)                                                                 | 5.4.0        |
| GCC Compiler                                                                  | 10.3.1       |
| IAR Compiler                                                                  | 8.42.2       |
| ARM Compiler 6                                                                | 6.13         |
| FreeRTOS                                                                      | 10.4.302     |

## More information

* [Peripheral Driver Library README.md](./README.md)
* [Peripheral Driver Library API Reference Manual](https://infineon.github.io/mtb-pdl-cat1/pdl_api_reference_manual/html/index.html)
* [ModusToolbox Software Environment, Quick Start Guide, Documentation, and Videos](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
* [ModusToolbox Device Configurator Tool Guide](https://www.infineon.com/dgdl/Infineon-ModusToolbox_Device_Configurator_Guide_4-UserManual-v01_00-EN.pdf?fileId=8ac78c8c7d718a49017d99ab297631cb)
* [AN210781 Getting Started with PSoC 6 MCU with Bluetooth Low Energy (BLE) Connectivity](http://www.cypress.com/an210781)
* [PSoC 6 Technical Reference Manuals](https://edit.infineon.com/cms/en/search.html#!term=psoc6%20technical%20reference%20manual&view=downloads)
* [PSoC 6 MCU Datasheets](https://edit.infineon.com/cms/en/search.html?intc=searchkwr-return#!view=downloads&term=psoc6&doc_group=Data%20Sheet)
* [CYW20829](https://www.infineon.com/cms/en/product/promopages/airoc20829)
* [Infineon](http://www.infineon.com)

---
© Cypress Semiconductor Corporation (an Infineon company), 2022.
