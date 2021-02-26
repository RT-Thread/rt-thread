# STM32L476-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32L476RG @80MHz, 1024KB FLASH, 128KB RAM

The STM32L476xx devices are the ultra-low-power microcontrollers based on the high-performance Arm® Cortex®-M4 32-bit RISC core operating at a frequency of up to 80 MHz. The Cortex-M4 core features a Floating point unit (FPU) single precision which supports all Arm® single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

The STM32L476xx devices embed high-speed memories (Flash memory up to 1 Mbyte, up to 128 Kbyte of SRAM), a flexible external memory controller (FSMC) for static memories (for devices with packages of 100 pins and more), a Quad SPI flash memories interface (available on all packages) and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB buses and a 32-bit multi-AHB bus matrix.
The STM32L476xx devices embed several protection mechanisms for embedded Flash memory and SRAM: readout protection, write protection, proprietary code readout protection and Firewall.
The devices offer up to three fast 12-bit ADCs (5 Msps), two comparators, two operational amplifiers, two DAC channels, an internal voltage reference buffer, a low-power RTC, two general-purpose 32-bit timer, two 16-bit PWM timers dedicated to motor control, seven general-purpose 16-bit timers, and two 16-bit low-power timers. The devices support four digital filters for external sigma delta modulators (DFSDM).
In addition, up to 24 capacitive sensing channels are available. The devices also embed an integrated LCD driver 8x40 or 4x44, with internal step-up converter.
They also feature standard and advanced communication interfaces.
The STM32L476xx operates in the -40 to +85 °C (+105 °C junction), -40 to +105 °C (+125 °C junction) and -40 to +125 °C (+130 °C junction) temperature ranges from a 1.71 to 3.6 V VDD power supply when using internal LDO regulator and a 1.05 to 1.32V VDD12 power supply when using external SMPS supply. A comprehensive set of power-saving modes allows the design of low-power applications.
Some independent power supplies are supported: analog independent supply input for ADC, DAC, OPAMPs and comparators, 3.3 V dedicated supply input for USB and up to 14 I/Os can be supplied independently down to 1.08V. A VBAT input allows to backup the RTC and backup registers. Dedicated VDD12 power supplies can be used to bypass the internal LDO regulator when connected to an external SMPS.
The STM32L476xx family offers six packages from 64-pin to 144-pin packages.

#### KEY FEATURES

- Ultra-low-power with FlexPowerControl
  - 1.71 V to 3.6 V power supply
  - -40 °C to 85/105/125 °C temperature range
  - 300 nA in VBAT mode: supply for RTC and 32x32-bit backup registers
  - 30 nA Shutdown mode (5 wakeup pins)
  - 120 nA Standby mode (5 wakeup pins)
  - 420 nA Standby mode with RTC
  - 1.1 μA Stop 2 mode, 1.4 μA with RTC
  - 100 μA/MHz run mode (LDO Mode)
  - 39 μA/MHz run mode (@3.3 V SMPS Mode)
  - Batch acquisition mode (BAM)
  - 4 μs wakeup from Stop mode
  - Brown out reset (BOR)
  - Interconnect matrix
- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait-state execution from Flash memory, frequency up to 80 MHz, MPU, 100DMIPS and DSP instructions
- Performance benchmark
  - 1.25 DMIPS/MHz (Drystone 2.1)
  - 273.55 CoreMark® (3.42 CoreMark/MHz @ 80 MHz)
- Energy benchmark
  - 294 ULPMark™ CP score
  - 106 ULPMark™ PP score
- Clock Sources
  - 4 to 48 MHz crystal oscillator
  - 32 kHz crystal oscillator for RTC (LSE)
  - Internal 16 MHz factory-trimmed RC (±1%)
  - Internal low-power 32 kHz RC (±5%)
  - Internal multispeed 100 kHz to 48 MHz oscillator, auto-trimmed by LSE (better than ±0.25 % accuracy)
  - 3 PLLs for system clock, USB, audio, ADC
- Up to 114 fast I/Os, most 5 V-tolerant, up to 14 I/Os with independent supply down to 1.08 V
- RTC with HW calendar, alarms and calibration
- LCD 8× 40 or 4× 44 with step-up converter
- Up to 24 capacitive sensing channels: support touchkey, linear and rotary touch sensors
- 16x timers: 2x 16-bit advanced motor-control, 2x 32-bit and 5x 16-bit general purpose, 2x 16-bit basic, 2x low-power 16-bit timers (available in Stop mode), 2x watchdogs, SysTick timer

- Memories
  - Up to 1 MB Flash, 2 banks read-while-write, proprietary code readout protection
  - Up to 128 KB of SRAM including 32 KB with hardware parity check
  - External memory interface for static memories supporting SRAM, PSRAM, NOR and NAND memories
  - Quad SPI memory interface
- 4x digital filters for sigma delta modulator
- Rich analog peripherals (independent supply)
  - 3x 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling, 200 μA/Msps
  - 2x 12-bit DAC output channels, low-power sample and hold
  - 2x operational amplifiers with built-in PGA
  - 2x ultra-low-power comparators
- 20x communication interfaces
  - USB OTG 2.0 full-speed, LPM and BCD
  - 2x SAIs (serial audio interface)
  - 3x I2C FM+(1 Mbit/s), SMBus/PMBus
  - 5x USARTs (ISO 7816, LIN, IrDA, modem)
  - 1x LPUART (Stop 2 wake-up)
  - 3x SPIs (and 1x Quad SPI)
  - CAN (2.0B Active) and SDMMC interface
  - SWPMI single wire protocol master I/F
  - IRTIM (Infrared interface)
- 14-channel DMA controller
- True random number generator
- CRC calculation unit, 96-bit unique ID
- Development support: serial wire debug (SWD), JTAG, Embedded Trace Macrocell™
- All packages are ECOPACK2® compliant



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32L476RG ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32l476rg.html#documentation) |          STM32L476RG datasheet and other resources           |



## Maintained By

<gycgwzw@gmail.com>



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf