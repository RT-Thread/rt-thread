# STM32F412-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F412ZG @100MHz, 1024KB FLASH,  256KB RAM

STM32F412xE/G devices are based on the high-performance Arm® Cortex® -M4 32-bit RISC core operating at a frequency of up to 100 MHz. Their Cortex®-M4 core features a Floating point unit (FPU) single precision which supports all Arm single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

STM32F412xE/G devices belong to the STM32 Dynamic Efficiency™ product line (with products combining power efficiency, performance and integration) while adding a new innovative feature called Batch Acquisition Mode (BAM) allowing even more power consumption saving during data batching.
STM32F412xE/G devices incorporate high-speed embedded memories (up to 1 Mbyte of Flash memory, 256 Kbytes of SRAM), and an extensive range of enhanced I/Os and peripherals connected to two APB buses, three AHB buses and a 32-bit multi-AHB bus matrix.
All devices offer one 12-bit ADC, a low-power RTC, twelve general-purpose 16-bit timers, two PWM timers for motor control and two general-purpose 32-bit timers.
They also feature standard and advanced communication interfaces:
In addition, STM32F412xE/G devices embed advanced peripherals:
STM32F412xE/G devices are offered in 7 packages ranging from 48 to 144 pins. The set of available peripherals depends on the selected package.
The STM32F412xE/G operates in the -40 to +125 °C temperature range from a 1.7 (PDR OFF) to 3.6 V power supply. A comprehensive set of power-saving modes allows the design of low-power applications.
These features make the STM32F412xE/G microcontrollers suitable for a wide range of applications.

#### KEY FEATURES

- Dynamic Efficiency Line with BAM (Batch Acquisition Mode)
- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait state execution from Flash memory, frequency up to 100 MHz, memory protection unit, 125 DMIPS/1.25 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 1 Mbyte of Flash memory
  - 256 Kbyte of SRAM
  - Flexible external static memory controller with up to 16-bit data bus: SRAM, PSRAM, NOR Flash memory
  - Dual mode Quad-SPI interface
- LCD parallel interface, 8080/6800 modes
- Clock, reset and supply management
  - 1.7 V to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - 4-to-26 MHz crystal oscillator
  - Internal 16 MHz factory-trimmed RC
  - 32 kHz oscillator for RTC with calibration
  - Internal 32 kHz RC with calibration
- Power consumption
  - Run: 112 μA/MHz (peripheral off)
  - Stop (Flash in Stop mode, fast wakeup time): 50 μA Typ @ 25 °C; 75 μA max @25 °C
  - Stop (Flash in Deep power down mode, slow wakeup time): down to 18 μA @ 25 °C; 40 μA max @25 °C
  - Standby: 2.4 μA @25 °C / 1.7 V without RTC; 12 μA @85 °C @1.7 V
  - VBAT supply for RTC: 1 μA @25 °C
- 1×12-bit, 2.4 MSPS ADC: up to 16 channels
- 2xdigital filters for sigma delta modulator, 4xPDM interfaces, stereo microphone support
- General-purpose DMA: 16-stream DMA

- Up to 17 timers: up to twelve 16-bit timers, two 32-bit timers up to 100 MHz each with up to four IC/OC/PWM or pulse counter and quadrature (incremental) encoder input, two watchdog timers (independent and window), one SysTick timer
- Debug mode
  - Serial wire debug (SWD) & JTAG
  - Cortex®-M4 Embedded Trace Macrocell™
- Up to 114 I/O ports with interrupt capability
  - Up to 109 fast I/Os up to 100 MHz
  - Up to 114 five V-tolerant I/Os
- Up to 17 communication interfaces
  - Up to 4xI2C interfaces (SMBus/PMBus)
  - Up to 4 USARTs (2x12.5 Mbit/s, 2x6.25 Mbit/s), ISO 7816 interface, LIN, IrDA, modem control)
  - Up to 5 SPI/I2Ss (up to 50 Mbit/s, SPI or I2S audio protocol), out of which 2 muxed full-duplex I2S interfaces
  - SDIO interface (SD/MMC/eMMC)
  - Advanced connectivity: USB 2.0 full-speed device/host/OTG controller with PHY
  - 2xCAN (2.0B Active)
- True random number generator
- CRC calculation unit
- 96-bit unique ID
- RTC: subsecond accuracy, hardware calendar
- All packages are ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32F412ZG ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32f412zg.html#documentation) |          STM32F412ZG datasheet and other resources           |



## Maintained By

[flybreak](https://github.com/guozhanxin)  g1171407708@163.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf
