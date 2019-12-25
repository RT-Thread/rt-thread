# Changelog
All notable changes to this project are documented in this file.

## [1.6.2] - 2019-02-12
### Added
- Added the possibility to use the macro NRFX_COREDEP_DELAY_US_LOOP_CYCLES to specify the number of cycles consumed by one iteration of the internal loop in the function nrfx_coredep_delay_us().

### Changed
- Updated MDK to version 8.24.1.

## [1.6.1] - 2019-01-29
### Fixed
- Fixed an issue in the NFCT driver that caused a performance loss on nRF52832. The interrupt configuration is now properly restored after the NRFX_NFCT_EVT_FIELD_LOST event.

## [1.6.0] - 2019-01-18
### Added
- Added support for nRF52811.
- Added support for the legacy peripherals SPI, TWI, and UART in nRF52810.
- Added support for SAMPLERATE in nrf_saadc.h.
- Added clearing of the STOPPED event in the nrfx_saadc_init() function to prevent driver deadlock in some cases.
- Added HALs: BPROT, MPU, MWU.
- Added function for reading the pin input buffer configuration in the GPIO HAL.
- Implemented workaround for nRF9160 anomaly 1 in the I2S driver.

### Changed
- Improved handling of hardware anomalies in the USBD driver.
- Updated MDK to version 8.23.1.

### Fixed
- Fixed the condition in NRFX_WAIT_FOR in the nrfx_saadc_abort() function. The macro now correctly waits for a stop of the driver.
- Fixed the pending interrupt clearing in NVIC in the nrfx_usbd_stop() function. The driver now correctly handles power management.
- Fixed the case when nrfx_uarte_tx_in_progress() function would return an incorrect value. The driver now correctly updates the tx_buffer_length variable internally.

## [1.5.0] - 2018-12-12
### Added
- Added support for nRF9160.
- Added allocator for DPPI.
- Added HALs: DPPI, KMU, REGULATORS, SPU, VMC.
- Added support for DPPI subscription and publishing in HALs related to nRF9160.
- Added support for instances 2 and 3 in SPIS, TWIM, TWIS, and UARTE drivers.

### Changed
- Updated MDK to version 8.21.1.

### Fixed
- Corrected NRFX_I2S_CONFIG_RATIO value in nrfx_config.h. It now correctly uses supported value.

## [1.4.0] - 2018-11-30
### Added
- Added the nrfx_is_word_aligned() function for checking whether an address is word-aligned.
- Added HAL for ACL.
- Added functions for disabling and re-enabling interrupts in the SWI driver.
- Added possibility to completely remove interrupt handling from the WDT driver.

### Changed
- Updated the documentation for the nrfx_uarte_rx() function. It now correctly reflects the actual behavior of the function.

### Fixed
- Corrected the type of the nrfx_uarte_xfer_evt_t structure field that holds the amount of transferred bytes.
- Corrected the way of disabling interrupts in the NFCT driver when moving the peripheral to the disabled state.
- Fixed a typo in the name of the bmRequest field in the nrfx_usbd_setup_t structure. The new correct name is bRequest.
- Fixed the nrfx_ppi_channel_fork_assign() function. It now accepts also pre-programmed channels.
- Fixed handling of long custom instruction responses in the QSPI driver.
- Fixed a bug affecting the conversion of time to ticks in the TIMER HAL.

## [1.3.1] - 2018-09-28
### Fixed
- Corrected the type of nrfx_usbd_ep_status_get() return value.
- Corrected calls to undefined macros in NFCT and USBD drivers.

## [1.3.0] - 2018-09-21
### Added
- Added HAL and driver for NFCT.
- Added driver for USBD.
- Added function for setting the burst mode in the SAADC HAL.
- Added the NRFX_ARRAY_SIZE macro.

### Changed
- Moved the implementation of nrfx_power_clock_irq_handler() to nrfx_power.c, removed nrfx_power_clock.c.

### Fixed
- Replaced ARRAY_SIZE macro calls with NRFX_ARRAY_SIZE ones.

## [1.2.0] - 2018-09-06
### Added
- Added function for checking if a specific channel is enabled in the GPIOTE HAL.
- Added support for using the QDEC driver without LED.
- Added functions for modifying only the event endpoint or only the task endpoint in the PPI HAL.
- Added function for reading the pin pull configuration in the GPIO HAL.

### Changed
- Corrected ISOSPLIT enumerator names in the USBD HAL.

### Fixed
- Fixed a double buffering bug that occurred in the UARTE driver after the RX abort.
- Fixed the TXRX transfers in the TWIM driver. They can now be started after transfers that are not ended with the stop condition.

## [1.1.0] - 2018-06-15
### Added
- Implemented workaround for nRF52832 and nRF52840 anomaly 194 in the I2S driver.
- Implemented workaround for nRF52840 anomaly 195 in the SPIM driver.
- Added HALs for CCM, ECB, and RADIO.
- Extended HALs for GPIO, PPI, SAADC, and USBD.
- Added support for external LFCLK sources.

### Changed
- Corrected handling of transfer lengths in the TWI driver.
- Updated MDK to version 8.17.0.

### Fixed
- Fixed logging in the PPI driver.
- Fixed SPIM interrupt definition for nRF52810.
- Fixed Slave Select configuration in the SPIM driver.
- Corrected default settings for NRF_SPIM3.
- Fixed a typo in the UARTE TXDRDY event definition.
- Corrected the TIMEOUT event clearing in the WDT interrupt handler.

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
- Improved buffer handling in the I2S driver. The API of the driver has been slightly modified.
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
