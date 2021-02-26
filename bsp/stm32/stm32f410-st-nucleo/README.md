# STM32F410-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F410RB @100MHz, 128KB FLASH,  32KB RAM

The STM32F410x8/B devices are based on the high-performance ARM®Cortex® -M4 32-bit RISC core operating at a frequency of up to 100 MHz. Their Cortex®-M4 core features a Floating point unit (FPU) single precision which supports all ARM single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances application security.

The STM32F410x8/B belong to the STM32 Dynamic Efficiency™ product line (with products combining power efficiency, performance and integration) while adding a new innovative feature called Batch Acquisition Mode (BAM) allowing to save even more power consumption during data batching.

The STM32F410x8/B incorporate high-speed embedded memories (up to 128 Kbytes of Flash memory, 32 Kbytes of SRAM), and an extensive range of enhanced I/Os and peripherals connected to two APB buses, one AHB bus and a 32-bit multi-AHB bus matrix.

All devices offer one 12-bit ADC, one 12-bit DAC, a low-power RTC, three general-purpose 16-bit timers, one PWM timer for motor control, one general-purpose 32-bit timers and one 16-bit low-power timer. They also feature standard and advanced communication interfaces.

#### KEY FEATURES

- Dynamic Efficiency Line with BAM (Batch Acquisition Mode)
- Core: ARM®32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait state execution from Flash memory, frequency up to 100 MHz, memory protection unit, 125 DMIPS/1.25 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 128 Kbytes of Flash memory
  - 512 bytes of OTP memory
  - 32 Kbytes of SRAM
- Clock, reset and supply management
  - 1.7 V to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - 4-to-26 MHz crystal oscillator
  - Internal 16 MHz factory-trimmed RC
  - 32 kHz oscillator for RTC with calibration
  - Internal 32 kHz RC with calibration
- Power consumption
  - Run: 89 μA/MHz (peripheral off)
  - Stop (Flash in Stop mode, fast wakeup time): 40 μA Typ @ 25 °C; 49 μA max @25 °C
  - Stop (Flash in Deep power down mode, fast wakeup time): down to 6 μA @ 25 °C; 14 μA max @25 °C
  - Standby: 2.4 μA @25 °C / 1.7 V without RTC; 12 μA @85 °C @1.7 V
  - VBATsupply for RTC: 1 μA @25 °C
- 1×12-bit, 2.4 MSPS ADC: up to 16 channels
- 1×12-bit D/A converter
- General-purpose DMA: 16-stream DMA controllers with FIFOs and burst support
- Up to 9 timers
  - One 16-bit advanced motor-control timer
  - One low-power timer (available in Stop mode)
  - Three 16-bit general purpose timers
  - One 32-bit timer up to 100 MHz with up to four IC/OC/PWM or pulse counter and quadrature (incremental) encoder input
  - Two watchdog timers (independent window)
  - SysTick timer

- Debug mode
  - Serial wire debug (SWD) & JTAG interfaces
  - Cortex®-M4 Embedded Trace Macrocell™
- Up to 50 I/O ports with interrupt capability
  - Up to 45 fast I/Os up to 100 MHz
  - Up to 49 5 V-tolerant I/Os
- Up to 9 communication interfaces
  - Up to 3x I2C interfaces (SMBus/PMBus) including 1x I2C Fast-mode at 1 MHz
  - Up to 3 USARTs (2 x 12.5 Mbit/s, 1 x 6.25 Mbit/s), ISO 7816 interface, LIN, IrDA, modem control)
  - Up to 3 SPI/I2Ss (up to 50 Mbit/s SPI or I2S audio protocol)
- True random number generator
- CRC calculation unit
- 96-bit unique ID
- RTC: subsecond accuracy, hardware calendar
- All packages are ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32F410RB ST Official Website](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus/stm32-high-performance-mcus/stm32f4-series/stm32f410/stm32f410rb.html#documentation) |          STM32F410RB datasheet and other resources           |



## Maintained By

[tanglj86](https://github.com/tanglj86/rt-thread)  

tanglj86@gmail.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf