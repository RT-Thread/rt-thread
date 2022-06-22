# STM32F413-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F413ZH @100MHz, 1.5 MB FLASH,  320KB RAM

The STM32F413xG/H devices are based on the high-performance Arm® Cortex®-M4 32-bit RISC core operating at a frequency of up to 100 MHz. Their Cortex®-M4 core features a Floating point unit (FPU) single precision which supports all Arm single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

The STM32F413xG/H devices belong to the STM32F4 access product lines (with products combining power efficiency, performance and integration) while adding a new innovative feature called Batch Acquisition Mode (BAM) allowing to save even more power consumption during data batching.
The STM32F413xG/H devices incorporate high-speed embedded memories (up to 1.5 Mbytes of Flash memory, 320 Kbytes of SRAM), and an extensive range of enhanced I/Os and peripherals connected to two APB buses, three AHB buses and a 32-bit multi-AHB bus matrix.
All devices offer a 12-bit ADC, two 12-bit DACs, a low-power RTC, twelve general-purpose 16-bit timers including two PWM timer for motor control, two general-purpose 32-bit timers and a low power timer.
They also feature standard and advanced communication interfaces.

#### KEY FEATURES

- Dynamic Efficiency Line with eBAM (enhanced Batch Acquisition Mode)
  - 1.7 V to 3.6 V power supply
  - -40 °C to 85/105/125 °C temperature range
- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait state execution from Flash memory, frequency up to 100 MHz, memory protection unit, 125 DMIPS/ 1.25 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 1.5 Mbytes of Flash memory
  - 320 Kbytes of SRAM
  - Flexible external static memory controller with up to 16-bit data bus: SRAM, PSRAM, NOR Flash memory
  - Dual mode Quad-SPI interface
- LCD parallel interface, 8080/6800 modes
- Clock, reset and supply management
  - 1.7 to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - 4-to-26 MHz crystal oscillator
  - Internal 16 MHz factory-trimmed RC
  - 32 kHz oscillator for RTC with calibration
  - Internal 32 kHz RC with calibration
- Power consumption
  - Run: 112 μA/MHz (peripheral off)
  - Stop (Flash in Stop mode, fast wakeup time): 42 μA Typ.; 80 μA max @25 °C
  - Stop (Flash in Deep power down mode, slow wakeup time): 15 μA Typ.; 46 μA max @25 °C
  - Standby without RTC: 1.1 μA Typ.; 14.7 μA max at @85 °C
  - VBAT supply for RTC: 1 μA @25 °C
- 2x12-bit D/A converters
- 1×12-bit, 2.4 MSPS ADC: up to 16 channels
- 6x digital filters for sigma delta modulator, 12x PDM interfaces, with stereo microphone and sound source localization support
- General-purpose DMA: 16-stream DMA

- Up to 18 timers: up to twelve 16-bit timers, two 32-bit timers up to 100 MHz each with up to four IC/OC/PWM or pulse counter and quadrature (incremental) encoder input, two watchdog timers (independent and window), one SysTick timer, and a low-power timer
- Debug mode
  - Serial wire debug (SWD) & JTAG
  - Cortex®-M4 Embedded Trace Macrocell™
- Up to 114 I/O ports with interrupt capability
  - Up to 109 fast I/Os up to 100 MHz
  - Up to 114 five V-tolerant I/Os
- Up to 24 communication interfaces
  - Up to 4x I2C interfaces (SMBus/PMBus)
  - Up to 10 UARTS: 4 USARTs / 6 UARTs (2 x 12.5 Mbit/s, 2 x 6.25 Mbit/s), ISO 7816 interface, LIN, IrDA, modem control)
  - Up to 5 SPI/I2Ss (up to 50 Mbit/s, SPI or I2S audio protocol), out of which 2 muxed full-duplex I2S interfaces
  - SDIO interface (SD/MMC/eMMC)
  - Advanced connectivity: USB 2.0 full-speed device/host/OTG controller with PHY
  - 3x CAN (2.0B Active)
  - 1xSAI
- True random number generator
- CRC calculation unit
- 96-bit unique ID
- RTC: subsecond accuracy, hardware calendar
- All packages are ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32F413ZH ST Official Website](https://www.st.com/zh/microcontrollers-microprocessors/stm32f413zh.html#documentation) |          STM32F413ZH datasheet and other resources           |



## Maintained By

[flybreak](https://github.com/guozhanxin)  g1171407708@163.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf