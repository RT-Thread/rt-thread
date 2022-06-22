# STM32G070-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32G070RB @64MHz, 128KB FLASH,  36KB RAM

The STM32G070CB/KB/RB mainstream microcontrollers are based on high-performance Arm® Cortex®-M0+ 32-bit RISC core operating at up to 64 MHz frequency. Offering a high level of integration, they are suitable for a wide range of applications in consumer, industrial and appliance domains and ready for the Internet of Things (IoT) solutions.

The devices incorporate a memory protection unit (MPU), high-speed embedded memories (128 Kbytes of Flash program memory with read protection, write protection, and 36 Kbytes of SRAM), DMA and an extensive range of system functions, enhanced I/Os and peripherals. The devices offer standard communication interfaces (two I2Cs, two SPIs / one I2S, and four USARTs), one 12-bit ADC (2.5 MSps) with up to 19 channels, a low-power RTC, an advanced control PWM timer, five general-purpose 16-bit timers, two basic timers, two watchdog timers, and a SysTick timer.
The devices operate within ambient temperatures from -40 to 85°C. They can operate with supply voltages from 2.0 V to 3.6 V. Optimized dynamic consumption combined with a comprehensive set of power-saving modes allows the design of low-power applications.
VBAT direct battery input allows keeping RTC and backup registers powered.
The devices come in packages with 32 to 64 pins.

#### KEY FEATURES

- Core: Arm® 32-bit Cortex®-M0+ CPU, frequency up to 64 MHz
- -40°C to 85°C operating temperature
- Memories
  - 128 Kbytes of Flash memory with protection
  - 36 Kbytes of SRAM (32 Kbytes with HW parity check)
- CRC calculation unit
- Reset and power management
  - Voltage range: 2.0 V to 3.6 V
  - Power-on/Power-down reset (POR/PDR)
  - Low-power modes:Sleep, Stop, Standby
  - VBAT supply for RTC and backup registers
- Clock management
  - 4 to 48 MHz crystal oscillator
  - 32 kHz crystal oscillator with calibration
  - Internal 16 MHz RC with PLL option
  - Internal 32 kHz RC oscillator (±5 %)
- Up to 59 fast I/Os
  - All mappable on external interrupt vectors
  - Multiple 5 V-tolerant I/Os

- 7-channel DMA controller with flexible mapping
- 12-bit, 0.4 µs ADC (up to 16 ext. channels)
  - Up to 16-bit with hardware oversampling
  - Conversion range: 0 to 3.6V
- 11 timers: 16-bit for advanced motor control, five 16-bit general-purpose, two basic 16-bit, two watchdogs, SysTick timer
- Calendar RTC with alarm and periodic wakeup from Stop/Standby
- Communication interfaces
  - Two I2C-bus interfaces supporting Fast-mode Plus (1 Mbit/s) with extra current sink, one supporting SMBus/PMBus and wakeup from Stop mode
  - Four USARTs with master/slave synchronous SPI; two supporting ISO7816 interface, LIN, IrDA capability, auto baud rate detection and wakeup feature
  - Two SPIs (32 Mbit/s) with 4- to 16-bit programmable bitframe, one multiplexed with I2S interface
- Development support: serial wire debug (SWD)
- All packages ECOPACK 2 compliant



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32G070RB ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32g070rb.html#documentation) |          STM32G070RB datasheet and other resources           |



## Maintained By

[NU-LL](https://github.com/NU-LL)



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf