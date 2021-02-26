# STM32L496-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32L496ZG @80MHz, 1024KB FLASH, 320KB RAM

The STM32L496xx devices are the ultra-low-power microcontrollers based on the high-performance Arm® Cortex®-M4 32-bit RISC core operating at a frequency of up to 80 MHz. The Cortex-M4 core features a Floating point unit (FPU) single precision which supports all Arm® single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

The STM32L496xx devices embed high-speed memories (up to 1 Mbyte of Flash memory, 320 Kbyte of SRAM), a flexible external memory controller (FSMC) for static memories (for devices with packages of 100 pins and more), a Quad SPI flash memories interface (available on all packages) and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB buses and a 32-bit multi-AHB bus matrix.
The STM32L496xx devices embed several protection mechanisms for embedded Flash memory and SRAM: readout protection, write protection, proprietary code readout protection and Firewall.
The devices offer up to three fast 12-bit ADCs (5 Msps), two comparators, two operational amplifiers, two DAC channels, an internal voltage reference buffer, a low-power RTC, two general-purpose 32-bit timer, two 16-bit PWM timers dedicated to motor control, seven general-purpose 16-bit timers, and two 16-bit low-power timers. The devices support four digital filters for external sigma delta modulators (DFSDM).
In addition, up to 24 capacitive sensing channels are available. The devices also embed an integrated LCD driver 8x40 or 4x44, with internal step-up converter.
They also feature standard and advanced communication interfaces.

#### KEY FEATURES

- Ultra-low-power with FlexPowerControl
  - 1.71 V to 3.6 V power supply
  - -40 °C to 85/125 °C temperature range
  - 320 nA in VBAT mode: supply for RTC and 32x32-bit backup registers
  - 25 nA Shutdown mode (5 wakeup pins)
  - 108 nA Standby mode (5 wakeup pins)
  - 426 nA Standby mode with RTC
  - 2.57 µA Stop 2 mode, 2.86 µA Stop 2 with RTC
  - 91 µA/MHz run mode (LDO Mode)
  - 37 μA/MHz run mode (@3.3 V SMPS Mode)
  - Batch acquisition mode (BAM)
  - 5 µs wakeup from Stop mode
  - Brown out reset (BOR) in all modes except shutdown
  - Interconnect matrix
- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait-state execution from Flash memory, frequency up to 80 MHz, MPU, 100 DMIPS and DSP instructions
- Performance benchmark
  - 1.25 DMIPS/MHz (Drystone 2.1)
  - 273.55 Coremark® (3.42 Coremark/MHz @ 80 MHz)
- Energy benchmark
  - 279 ULPMark™ CP score
  - 80.2 ULPMark™ PP score
- 16 x timers: 2 x 16-bit advanced motor-control, 2 x 32-bit and 5 x 16-bit general purpose, 2 x 16-bit basic, 2 x low-power 16-bit timers (available in Stop mode), 2 x watchdogs, SysTick timer
- RTC with HW calendar, alarms and calibration
- Up to 136 fast I/Os, most 5 V-tolerant, up to 14 I/Os with independent supply down to 1.08 V
- Dedicated Chrom-ART Accelerator™ for enhanced graphic content creation (DMA2D)
- 8- to 14-bit camera interface up to 32 MHz (black&white) or 10 MHz (color)
- Memories
  - Up to 1 MB Flash, 2 banks read-while-write, proprietary code readout protection
  - 320 KB of SRAM including 64 KB with hardware parity check
  - External memory interface for static memories supporting SRAM, PSRAM, NOR and NAND memories
  - Dual-flash Quad SPI memory interface

- Clock Sources
  - 4 to 48 MHz crystal oscillator
  - 32 kHz crystal oscillator for RTC (LSE)
  - Internal 16 MHz factory-trimmed RC (±1%)
  - Internal low-power 32 kHz RC (±5%)
  - Internal multispeed 100 kHz to 48 MHz oscillator, auto-trimmed by LSE (better than ±0.25% accuracy)
  - Internal 48 MHz with clock recovery
  - 3 PLLs for system clock, USB, audio, ADC
- LCD 8 × 40 or 4 × 44 with step-up converter
- Up to 24 capacitive sensing channels: support touchkey, linear and rotary touch sensors
- 4 x digital filters for sigma delta modulator
- Rich analog peripherals (independent supply)
  - 3 × 12-bit ADC 5 Msps, up to 16-bit with hardware oversampling, 200 µA/Msps
  - 2 x 12-bit DAC output channels, low-power sample and hold
  - 2 x operational amplifiers with built-in PGA
  - 2 x ultra-low-power comparators
- 20 x communication interfaces
  - USB OTG 2.0 full-speed, LPM and BCD
  - 2 x SAIs (serial audio interface)
  - 4 x I2C FM+(1 Mbit/s), SMBus/PMBus
  - 5 x U(S)ARTs (ISO 7816, LIN, IrDA, modem)
  - 1 x LPUART
  - 3 x SPIs (4 x SPIs with the Quad SPI)
  - 2 x CAN (2.0B Active) and SDMMC
  - SWPMI single wire protocol master I/F
  - IRTIM (Infrared interface)
- 14-channel DMA controller
- True random number generator
- CRC calculation unit, 96-bit unique ID
- Development support: serial wire debug (SWD), JTAG, Embedded Trace Macrocell™



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32L496ZG ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32l496zg.html#documentation) |          STM32L496ZG datasheet and other resources           |



## Maintained By

<super_mcu@qq.com>



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf