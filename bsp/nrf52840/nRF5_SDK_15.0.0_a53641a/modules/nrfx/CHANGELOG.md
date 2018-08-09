# Changelog
All notable changes to this project are documented in this file.

## [1.0.0] - 2018-03-21
### Added
- Added the NRFX_WAIT_FOR macro to improve the time-out functionality in QSPI and SAADC drivers.
- Added glue layer macros for checking and modifying the pending status of interrupts.
- Added new enumeration values for interrupts and events in the UARTE HAL.
- Implemented workarounds for nRF52 anomalies 192 and 201 in the CLOCK driver.
- Implemented workaround for nRF52840 anomaly 122 in the QSPI driver.
- Implemented workaround for nRF52840 anomaly 198 in the SPIM driver.

### Changed
- Updated MDK to 8.16.0.
- Extended input pin configuration in the GPIOTE driver.
- Unified the way of checking if a required event handler was provided. Now, all drivers do it with assertions.
- Changed the RNG bias correction configuration option to be enabled by default.
- Refactored the ADC driver and HAL.
- Corrected assertions in the TIMER driver to make it usable in debug version with PPI.
- Improved buffer handling in the I2S driver. The API of the driver has been sligthly modified.
- Enhanced SPIS driver API: added the "p_context" parameter, allowed NULL pointers for zero-length buffers.

### Fixed
- Fixed result value casting in the TEMP HAL.
- Fixed types of conversion result and buffer size in the ADC HAL and driver.
- Fixed time-out in the SAADC driver in abort function.

## [0.8.0] - 2017-12-20
### Added
- Added XIP support in the QSPI driver.
- Implemented Errata 132 in the CLOCK driver.
- Added function for checking if a TIMER instance is enabled.
- Added extended SPIM support.

### Changed
- Updated MDK to 8.15.0. Introduced Segger Embedded Studio startup files.
- Updated drivers: COMP, PWM, QDEC, SAADC, SPIS, TIMER, TWI, TWIS.
- Changed the type used for transfer lengths to 'size_t' in drivers: SPI, SPIM, SPIS, TWI, TWIM, TWIS, UART, UARTE. Introduced checking of EasyDMA transfers limits.
- Updated HALs: COMP, NVMC, UART, UARTE, USBD.
- Updated template files and documentation of configuration options.

### Fixed
- Fixed TWI and TWIM drivers so that they now support GPIOs from all ports.
- Fixed definitions related to compare channels in the TIMER HAL.

### Removed
- Removed the possibility of passing NULL instead of configuration to get default settings during drivers initialization.
- Removed support for UART1 and PRS box #5.

## [0.7.0] - 2017-10-20
### Added
- This CHANGELOG.md file.
- README.md file with simple description and explanations.
- HAL for: ADC, CLOCK, COMP, ECB, EGU, GPIO, GPIOTE, I2S, LPCOMP, NVMC, PDM, POWER, PPI, PWM, QDEC, QSPI, RNG, RTC, SAADC, SPI, SPIM, SPIS, ARM(R) SysTick, TEMP, TIMER, TWI, TWIM, TWIS, UART, UARTE, USBD, WDT.
- Drivers for: ADC, CLOCK, COMP, GPIOTE, I2S, LPCOMP, PDM, POWER, PWM, QDEC, QSPI, RNG, RTC, SAADC, SPI, SPIM, SPIS, ARM(R) SysTick, TIMER, TWI, TWIM, TWIS, UART, UARTE, WDT.
- Allocators for: PPI, SWI/EGU.
- MDK in version 8.14.0.
- Offline documentation for every added driver and simple integration description.
- Template integration files.
