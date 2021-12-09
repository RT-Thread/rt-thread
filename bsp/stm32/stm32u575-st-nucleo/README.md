# NUCLEO-STM32U575ZI-Q- BSP Introduction

[中文](README_zh.md)

## MCU: STM32U575ZI @110MHz, 2048 KB FLASH,  786 KB RAM

The STM32U575xx devices belong to an ultra-low-power microcontrollers family (STM32U5 Series) based on the high-performance Arm® Cortex®-M33 32-bit RISC core. They operate at a frequency of up to 160 MHz.

The Cortex®-M33 core features a single-precision FPU (floating-point unit), that supports all the Arm® single-precision data-processing instructions and all the data types.

The Cortex®-M33 core also implements a full set of DSP (digital signal processing) instructions and a MPU (memory protection unit) that enhances the application security.

The devices embed high-speed memories (up to 2 Mbytes of Flash memory and 786 Kbytes of SRAM), a FSMC (flexible external memory controller) for static memories (for devices with packages of 90 pins and more), two Octo-SPI Flash memory interfaces  (at least one Quad-SPI available on all packages) and an extensive range of enhanced I/Os and peripherals connected to three APB buses, three AHB buses and a 32-bit multi-AHB bus matrix.

The devices offer security foundation compliant  with the TBSA (trusted-based security architecture) requirements from Arm®. It embeds the necessary security features to implement a secure boot, secure data storage and secure firmware update. Besides these capabilities, the devices incorporate a secure firmware installation feature, that allows the customer to secure the provisioning of the code during its production. A flexible lifecycle is managed thanks to multiple levels of readout protection and debug unlock with password. Firmware hardware isolation is supported thanks to securable peripherals, memories and I/Os, and privilege configuration of peripherals and memories.

The devices feature several protection mechanisms for embedded Flash memory and SRAM: readout protection, write protection, secure and hide protection areas.

The devices embed several peripherals reinforcing security: with DPA resistancea HASH hardware accelerator, and a true random number generator.

The devices offer active tamper detection and protection against transient and environmental perturbation attacks,  thanks to several internal monitoring generating secret data erase in case of attack. This helps to fit the PCI requirements for point of sales applications.

The devices offer one fast 14-bit ADC (2.5 Msps), one 12-bit ADC (2.5 Msps), two comparators, two operational amplifiers, two DAC channels, an internal voltage reference buffer, a         low-power RTC, four 32-bit general-purpose timers, two 16-bit PWM timers dedicated to motor control, three 16-bit general-purpose timers, two 16-bit basic timers and four 16-bit low-power timers.

The devices support a MDF (multi-function digital filter) with six filters dedicated to the connection of external sigma-delta modulators. Another low-power digital filter dedicated to audio signals is embedded (ADF), with one filter supporting sound-activity detection. The devices embed also a Chrom-ART Accelerator dedicated to graphic applications, and mathematical accelerators (a trigonometric functions accelerator plus a filter mathematical accelerator). In addition, up to 24 capacitive sensing channels are available.

The devices also feature standard and advanced communication interfaces such as: four I2Cs, three SPIs, three USARTs, two UARTs, one low-power UART, two SAIs, one digital camera interface (DCMI), two SDMMCs, one FDCAN, one USB OTG full-speed, one USB Type-C /USB Power Delivery controller, and one generic synchronous 8-/16-bit PSSI (parallel data input/output slave interface).

The devices operate in the –40 to +85 °C (+105 °C junction) and –40 to +125 °C (+130 °C junction) temperature ranges from a 1.71 to 3.6 V power supply.

A comprehensive set of power-saving modes allow the design of low-power applications. Many peripherals (including communication, analog, timers and audio peripherals) can be functional and autonomous down to Stop mode with direct memory access, thanks to LPBAM support (low-power background autonomous mode).

Some independent power supplies are supported like an analog independent supply input for ADC, DACs, OPAMPs and comparators, a 3.3 V dedicated supply input for USB and up to 14 I/Os, that can be supplied independently down to 1.08 V. A VBAT input is available for connecting a backup battery in order to preserve the RTC functionality and to backup 3232-bit registers and 2-Kbyte SRAM.

The devices offer eight packages from 48 to 169 pins.

#### KEY FEATURES

- Includes ST state-of-the-art patented technology

- Ultra-low-power with FlexPowerControl
  - 1.71 V to 3.6 V power supply
  - –40 °C to +85/125 °C temperature range
  -  Low-power background autonomous mode (LPBAM): autonomous peripherals with DMA, functional down to Stop 2 mode
  - VBAT mode: supply for RTC, 32 x 32-bit backup registers and 2-Kbyte backup SRAM
  - 160 nA Shutdown mode (24 wakeup pins)
  - 210 nA Standby mode (24 wakeup pins)
  - 440 nA Standby mode with RTC
  - 1.9 μA Stop 3 mode with 16-Kbyte SRAM4.3 µA Stop 3 mode with full SRAM
  - 4.0 µA Stop 2 mode with 16-Kbyte SRAM
  - 8.95 µA Stop 2 mode with full SRAM
  - 19.5 μA/MHz Run mode @ 3.3 V

-  Core
  -  Arm® 32-bit Cortex®-M33 CPU with TrustZone®, MPU, DSP, and FPU

-  ART Accelerator
  - 8-Kbyte instruction cache allowing 0-wait-state execution from Flash and external memories: up to 160 MHz, 240 DMIPS
  - 4-Kbyte data cache for external memories

- Power management
  - Embedded regulator (LDO) and SMPSstep-down converter supporting switchon-the-fly and voltage scaling

- Benchmarks
  - 1.5 DMIPS/MHz (Drystone 2.1)
  - 651 CoreMark® (4.07 CoreMark®/MHz)
  - 535 ULPMark™-CP
  - 149 ULPMark™-PP
  - 58.2 ULPMark™-CM
  - 133000 SecureMark™-TLS

- Memories
  ​- 2-Mbyte Flash memory with ECC, 2 banks read-while-write, including 512 Kbytes with 100 kcycles
  - 86-Kbyte SRAM with ECC OFF or 722-Kbyte SRAM including up to 322-Kbyte SRAM with ECC ON
  - External memory interface supporting SRAM, PSRAM, NOR, NAND and FRAM memories
  - 2 Octo-SPI memory interfaces

- Security

  - Arm® TrustZone® and securable I/Os, memories and peripherals
  - Flexible life cycle scheme with RDP and password protected debug
  - Root of trust thanks to unique boot entry and secure hide protection area (HDP)
  - Secure firmware installation (SFI) thanks to embedded root secure services (RSS)
  - Secure firmware upgrade support with TF-M
  - HASH hardware accelerator
  - True random number generator, NIST SP800-90B compliant
  - 96-bit unique ID
  - 512-byte OTP (one-time programmable)
  - Active tampers

- Clock management
  - 4 to 50 MHz crystal oscillator
  - 32 kHz crystal oscillator for RTC (LSE)
  - Internal 16 MHz factory-trimmed RC (±1%)
  - Internal low-power 32 kHz RC (±5%)
  - 2 internal multispeed 100 kHz to 48 MHz oscillators, including one auto-trimmed by LSE (better than ±0.25% accuracy)
  - Internal 48 MHz with clock recovery
  - 3 PLLs for system clock, USB, audio, ADC

- General-purpose input/outputs
  - Up to 136 fast I/Os with interrupt capability most 5V-tolerant and up to 14 I/Os with independent supply down to 1.08 V

- Up to 17 timers and 2 watchdogs
  - 19 timers/watchdogs: 2 16-bit advanced motor-control, 4 32-bit, 5 16-bit, 4 low-power 16-bit (available in Stop mode), 2 SysTick timers and 2 watchdogs
  - RTC with hardware calendar and calibration

- Up to 22 communication peripherals
  -  1 USB Type-C®/USB power delivery controller
  - 1 USB OTG 2.0 full-speed controller
  - 2 SAIs (serial-audio interface)
  - 4 I2C FM+(1 Mbit/s), SMBus/PMBus™
  - 6 USARTs (ISO 7816, LIN, IrDA, modem)
  - 3 SPIs (5x SPIs with the dual OCTOSPI)
  - 1 CAN FD controller
  - 2 SDMMC interfaces
  - 1 multi-function digital filter (6 filters)+ 1 audio digital filter with sound-activity detection
  - Parallel synchronous slave interface

- 16- and 4-channel DMA controllers, functional in Stop mode

- Graphic features
  - Chrom-ART Accelerator (DMA2D) for enhanced graphic content creation
  - 1 digital camera interface

- Mathematical co-processor
  - CORDIC for trigonometric functions acceleration
  - Filter mathematical accelerator (FMAC)

- Up to 24 capacitive sensing channels
  -  Support touch key, linear and rotary touch sensors

- Rich analog peripherals (independent supply)

  - 14-bit ADC 2.5-Msps with hardware oversampling
  - 12-bit ADC 2.5-Msps, with hardware oversampling, autonomous in Stop 2 mode
  - 2 12-bit DAC, low-power sample and hold
  - 2 operational amplifiers with built-in PGA
  - 2 ultra-low-power comparators
  - Development support: serial-wire debug (SWD), JTAG, Embedded Trace Macrocell™ (ETM)

- ECOPACK2 compliant packages

## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32U575ZI ST Official Website](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html) |          STM32U575ZI datasheet and other resources           |

## Maintained By

[liukang](https://github.com/liukangcc)
