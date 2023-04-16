# CAT1 Hardware Abstraction Layer (HAL) Release Notes
The CAT1 Hardware Abstraction Layer (HAL) provides an implementation of the Hardware Abstraction Layer for the PSoC™ 6 and XMC7000/T2G-B-H families of chips. This API provides convenience methods for initializing and manipulating different hardware peripherals. Depending on the specific chip being used, not all features may be supported.

On devices which contain multiple cores, this library is supported on all cores. If HAL is used on multiple cores at the same time, the application is responsible for ensuring that each peripheral is only used on one core at a given time. This can be achieved by calling cyhal_hwmgr_reserve() on the core(s) where a particular resource is not expected to be used. This ensures the HAL is aware the resource is in use and does not use it in a conflicting manner.

### What's Included?
This release of the CAT1 HAL includes support for the following drivers:
* ADC
* Clock
* Comparator
* CRC
* DAC
* DMA
* EZ-I2C
* Flash
* GPIO
* Hardware Manager
* KeyScan
* I2C
* I2S
* Interconnect
* IPC
* LowPower Timer (LPTimer)
* OpAmp
* PDM/PCM
* Power Management (SysPM)
* PWM
* QSPI
* Quadrature Decoder (QuadDec)
* RTC
* SDHC
* SDIO
* SPI
* System
* TDM
* Timer
* True Random Number Generator (TRNG)
* UART
* USB Device
* WDT

### What Changed?
#### v2.3.0
* Add new SPI APIs
* Fix incorrect base address calculation on some devices in SCB-based drivers (UART, SPI, I2C, EZI2C).
* Extend documentation on pins and triggers to cover additional devices.
#### v2.2.0
* Production support for CAT1C devices
* Improve interrupt handling when running on on CM0+ core
* Add new I2C slave APIs
* Add driver for inter-processor communication (IPC)
* Add new function `cyhal_system_reset_device`
NOTE: This version requires udb-sdio-whd 1.2.0 or later
#### v2.1.0
* Pre-production support for CAT1B devices
* Fixed a few bugs in various drivers
#### v2.0.1
This patch release addresses issues in several drivers:
* RTC:
  1. Do not use RTOS delay even in RTOS-aware mode, to avoid ordering requirements between RTC and RTOS init.
* PWM:
  1. Fix incorrect period/duty cycle calculation when a `line_n` (inverted) output pin is used as the sole,
     non-inverted PWM output.
* PWM/Timer/QuadDec
  1. Fix level/edge nature of the source not being honored in `cyhal_*_connect_digital`.
  2. Add `cyhal_*_connect_digital2` API to allow explicitly specifying edge type (rising/falling/both). This supercedes
     `cyhal_connect_digital`, which defaults to rising edge when the source is an "edge" signal.
#### v2.0.0
This major version update includes changes that break API compatibility with prior releases. Each major or breaking change is described below:
* Clock:
  1. Renamed cyhal_resource_inst_t CYHAL_CLOCK_&lt;name&gt; constants with CYHAL_CLOCK_RSC_&lt;name&gt;. Created new CYHAL_CLOCK_&lt;name&gt; constants of type cyhal_clock_t.
  2. Replaced cyhal_clock_init with cyhal_clock_reserve.
  3. Removed div_type & div_num from cyhal_clock_t.
* DMA:
  1. cyhal_dma_enable must be called after configuring the DMA, but before a trigger will initiate a transfer
* Flash:
  1. The data buffer passed to functions must be from SRAM, the driver no longer contains a scratch buffer to copy into.
* GPIO:
  1. cyhal_gpio_enable_output updated to require a new argument to specify whether the signal is level or edge based.
  2. cyhal_gpio_connect_digital no longer takes the signal type parameter.
  3. cyhal_gpio_register_callback now takes a structure containing details about the callback.
  4. Removed deprecated functions cyhal_gpio_register_irq & cyhal_gpio_irq_enable
* I2C:
  1. Removed deprecated functions cyhal_i2c_register_irq & cyhal_i2c_irq_enable
* I2S/TDM:
  1. The mclk GPIO selection is moved into the RX/TX specific pins struct. This allows RX and TX to use separate mclk pins on devices that support this;
  see the device datasheet for details. For devices which only support a single MCLK pin shared between RX and TX, there is no change in functionality; when
  calling `cyhal_i2s_init` or `cyhal_tdm_init` the same `cyhal_gpio_t` value should be provided for both RX and TX.
* PWM:
  1. cyhal_pwm_connect_digital no longer takes the signal type parameter.
  2. cyhal_pwm_init will always produce a non-inverted waveform on the specified pin, even if that pin natively produces an inverted
     output (for example, the `line_compl` pins on PSoC™ devices). This improves consistency with the behavior of cyhal_pwm_init_adv.
* QSPI:
  1. cyhal_qspi_init() function got one additional parameter - shared clock (clk), which will allow users to use multiple HAL drivers which depends on same clock source.
  2. cyhal_qspi_init() now takes io[x] and ssel pins as pointer to cyhal_qspi_slave_pin_config_t structure, that contain mentioned pins.
  3. cyhal_qspi_slave_select_config function was replaced by cyhal_qspi_slave_configure, which provides possibility to add memory slaves with own data lines (instead of shared data lines and own slave select like it was when cyhal_qspi_slave_select_config has been used). cyhal_qspi_slave_config, as cyhal_qspi_init, takes cyhal_qspi_slave_pin_config_t as parameter.
  4. cyhal_qspi_command_t structure was updated: address.value field removed, data_rate field was added into all command subsections.
  5. Added address parameter to all transfer functions (cyhal_qspi_read, cyhal_qspi_read_async, cyhal_qspi_write, cyhal_qspi_write_async anb cyhal_qspi_transfer).
  6. cyhal_qspi_datarate_t enum was added. Corresponding configuration fields are added into each sub-structure of cyhal_qspi_command_t.
* SDHC:
  1. cyhal_sdhc_init() and cyhal_sdhc_init_hw() functions got one additional parameter - shared clock (block_clk), which will allow users to use multiple HAL drivers which depends on same clock source.
* SDIO:
  1. Updated the names of enum cyhal_tranfer_t and its types CYHAL_READ and CYHAL_WRITE to cyhal_sdio_transfer_type_t, CYHAL_SDIO_XFER_TYPE_READ, and CYHAL_SDIO_XFER_TYPE_WRITE, respectively.
  2. Removed deprecated functions cyhal_sdio_register_irq & cyhal_sdio_irq_enable
* Timer:
  1. cyhal_timer_connect_digital no longer takes the signal type parameter.
* UART:
  1. cyhal_uart_set_flow_control function was replaced by cyhal_uart_enable_flow_control, which only controls the enablement status of flow control. CTS / RTS pins are now provided via cyhal_uart_init() function.
* I2C:
  1. The following deprecated functions have been removed: cyhal_i2c_slave_config_write_buff, cyhal_i2c_slave_config_read_buff.
* Other:
  1. Removed cyhal_deprecated.h, and all associated code.
NOTE: This version requires core-lib 1.3.0 or later
#### v1.6.0
* Added new TDM driver
* Added support for 1.8v devices to SDHC/SDIO drivers
* Extended System driver to support registering for other interrupts
* Fixed issues with level trigger signals to the DMA driver
* Fixed a few bugs in various drivers
#### v1.5.0
* Added new Quadrature Decoder (QuadDec) driver
* Added digital hardware connection APIs to drivers
* Fixed a few bugs in various drivers
* Updated SDHC and MXSDHC-based SDIO communication functions to use semaphores in RTOS aware environments for improved performance
* Added optional implementations for SDHC control pin APIs and RTOS aware delay API provided as weak functions in the PDL (Disabled by: DEFINES+=CYHAL_DISABLE_WEAK_FUNC_IMPL)
#### v1.4.0
* Renamed library from psoc6hal to mtb-hal-cat1
* Added support for new PSoC™ 6 S4 devices
* Extended clock support for QSPI and SDHC drivers
* Fixed a few bugs in various drivers
* Minor documentation updates
#### v1.3.0
* Added new Analog Comparator driver
* Added new OpAmp driver
* Extended ADC driver
* Extended DAC driver
* Extended SPI/QSPI drivers to support multiple slave select signals
* Fixed SDHC based SDIO cyhal_sdio_is_busy() function to return status immediately instead of waiting until the transfer completes
* Fixed a few bugs in various drivers
* Minor update for documentation & branding
#### v1.2.1
* Added new option for SysPM driver to support tickless sleep in addition to deepsleep
* Fixed an issue with deep-sleep wake-up in the SDIO and SDHC drivers that could cause intermittent communication failures
* Minor bug fixes and documentation improvements
#### v1.2.0
* Added new Clock driver
* Added new SysPM Power Management driver
* Added new I2S driver
* Added new PDM/PCM driver
* Reduced flash memory usage for a number of drivers
* Improved documentation for a number of drivers
* Fixed a few bugs in various drivers
NOTE: The new SysPM driver needs to be initialized by calling cyhal_syspm_init(). This is done automatically by Board Support Packages version 1.2.0 and later.
#### v1.1.1
* Improved documentation for a number of drivers
* Fixed duplicate symbol definition with PDL 1.4.1 release
* Minor bug fixes
#### v1.1.0
* Added new DMA driver
* Added new EZ-I2C driver
* Extended System driver to allow getting information about reset
* Extended System driver to provide delay functions
* Updated PWM driver to provide additional configuration options
* Updated Timer driver to allow reading the current count
* Updated RTC driver to support Day Light Savings time
* Updated LP Timer driver to improve performance
* Minor updates up avoid potential warnings on some toolchains
* Multiple bug fixes across drivers
#### v1.0.0
* Initial release (ADC, CRC, DAC, Flash, GPIO, Hardware Manager, I2C, LP Timer, PWM, QSPI, RTC, SDHC, SDIO, SPI, System, Timer, TRNG, UART, USB Device, WDT)

### Supported Software and Tools
This version of the CAT1 Hardware Abstraction Layer was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 3.0.0   |
| GCC Compiler                              | 10.3.1  |
| IAR Compiler                              | 9.30.1  |
| ARM Compiler                              | 6.16    |

Minimum required ModusToolbox™ Software Environment: v2.0

### More information
Use the following links for more information, as needed:
* [API Reference Guide](https://infineon.github.io/mtb-hal-cat1/html/modules.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2022.
