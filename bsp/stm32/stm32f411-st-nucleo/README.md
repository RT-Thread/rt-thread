# STM32F411-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F411RE @100MHz, 512KB FLASH,  128KB RAM

The STM32F411xC/xE devices are based on the high-performance Arm® Cortex® -M4 32-bit RISC core operating at a frequency of up to 100 MHz. The Cortex®-M4 core features a Floating point unit (FPU) single precision which supports all Arm single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

The STM32F411xC/xE belongs to the STM32 Dynamic Efficiency™ product line (with products combining power efficiency, performance and integration) while adding a new innovative feature called Batch Acquisition Mode (BAM) allowing to save even more power consumption during data batching.
The STM32F411xC/xE incorporate high-speed embedded memories (up to 512 Kbytes of Flash memory, 128 Kbytes of SRAM), and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB bus and a 32-bit multi-AHB bus matrix.
All devices offer one 12-bit ADC, a low-power RTC, six general-purpose 16-bit timers including one PWM timer for motor control, two general-purpose 32-bit timers. They also feature standard and advanced communication interfaces.
The STM32F411xC/xE operate in the - 40 to + 125 °C temperature range from a 1.7 (PDR OFF) to 3.6 V power supply. A comprehensive set of power-saving mode allows the design of low-power applications.
These features make the STM32F411xC/xE microcontrollers suitable for a wide range of applications.

#### KEY FEATURES

- Dynamic Efficiency Line with BAM (Batch Acquisition Mode)
  - 1.7 V to 3.6 V power supply
  - 40°C to 85/105/125 °C temperature range
- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait state execution from Flash memory, frequency up to 100 MHz, memory protection unit, 125 DMIPS/1.25 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 512 Kbytes of Flash memory
  - 128 Kbytes of SRAM
- Clock, reset and supply management
  - 1.7 V to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - 4-to-26 MHz crystal oscillator
  - Internal 16 MHz factory-trimmed RC
  - 32 kHz oscillator for RTC with calibration
  - Internal 32 kHz RC with calibration
- Power consumption
  - Run: 100 μA/MHz (peripheral off)
  - Stop (Flash in Stop mode, fast wakeup time): 42 μA Typ @ 25C; 65 μA max @25 °C
  - Stop (Flash in Deep power down mode, slow wakeup time): down to 9 μA @ 25 °C; 28 μA max @25 °C
  - Standby: 1.8 μA @25 °C / 1.7 V without RTC; 11 μA @85 °C @1.7 V
  - VBAT supply for RTC: 1 μA @25 °C
- 1×12-bit, 2.4 MSPS A/D converter: up to 16 channels
- General-purpose DMA: 16-stream DMA controllers with FIFOs and burst support
- Up to 11 timers: up to six 16-bit, two 32-bit timers up to 100 MHz, each with up to four IC/OC/PWM or pulse counter and quadrature (incremental) encoder input, two watchdog timers (independent and window) and a SysTick timer
- Debug mode
  - Serial wire debug (SWD) & JTAG interfaces
  - Cortex®-M4 Embedded Trace Macrocell™
- Up to 81 I/O ports with interrupt capability
  - Up to 78 fast I/Os up to 100 MHz
  - Up to 77 5 V-tolerant I/Os
- Up to 13 communication interfaces
  - Up to 3 x I2C interfaces (SMBus/PMBus)
  - Up to 3 USARTs (2 x 12.5 Mbit/s, 1 x 6.25 Mbit/s), ISO 7816 interface, LIN, IrDA, modem control)
  - Up to 5 SPI/I2Ss (up to 50 Mbit/s, SPI or I2S audio protocol), SPI2 and SPI3 with muxed full-duplex I2S to achieve audio class accuracy via internal audio PLL or external clock
  - SDIO interface (SD/MMC/eMMC)
  - Advanced connectivity: USB 2.0 full-speed device/host/OTG controller with on-chip PHY
- CRC calculation unit
- 96-bit unique ID
- RTC: subsecond accuracy, hardware calendar
- All packages (WLCSP49, LQFP64/100, UFQFPN48, UFBGA100) are ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32F411RE ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32f411re.html#documentation) |          STM32F411RE datasheet and other resources           |



## Maintained By

[misonyo](https://github.com/misonyo)

misonyo@foxmail.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf