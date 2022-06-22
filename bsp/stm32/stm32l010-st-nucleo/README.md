# STM32L010-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32L010RB @32MHz, 128KB FLASH,  20KB RAM

#### KEY FEATURES

- Ultra-low-power platform
  - 1.8 V to 3.6 V power supply
  - –40 to 85 °C temperature range
  - 0.29 µA Standby mode (2 wakeup pins)
  - 0.43 µA Stop mode (16 wakeup lines)
  - 0.86 µA Stop mode + RTC + 20-Kbyte RAM retention
  - Down to 93 µA/MHz in Run mode
  - 5 µs wakeup time (from Flash memory)
  - 41 µA 12-bit ADC conversion at 10 ksps
- Core: Arm® 32-bit Cortex®-M0+
  - From 32 kHz to 32 MHz
  - 0.95 DMIPS/MHz
- Reset and supply management
  - Ultra-low-power BOR (brownout reset) with 5 selectable thresholds
  - Ultra-low-power POR/PDR
- Clock sources
  - 0 to 32 MHz external clock
  - 32 kHz oscillator for RTC with calibration
  - High-speed internal 16 MHz factory-trimmed RC (±1%)
  - Internal low-power 37 kHz RC
  - Internal multispeed low-power 65 kHz to 4.2 MHz RC
  - PLL for CPU clock
- Pre-programmed bootloader
  - USART, I2C, SPI supported
- Development support
  - Serial wire debug supported
- 51 fast I/Os (45 I/Os 5-Volt tolerant)
- Memories
  - 128-Kbyte Flash memory
  - 20-Kbyte RAM
  - 512 bytes of data EEPROM
  - 20-byte backup register
  - Sector protection against R/W operation
- Analog peripherals
  - 12-bit ADC 1.14 Msps up to 16 channels (down to 1.8 V)

- 7-channel DMA controller, supporting ADC, SPI, I2C, USART and timers
- 4x peripherals communication interface
- 1x USART (ISO7816), 1x LPUART (low power)
- 1x SPI 16 Mbit/s
- 1x I2C (SMBus/PMBus)
- 8x timers: 1x 16-bit with up to 4 channels, 2x 16-bit with up to 2 channels, 1x 16-bit ultra-low-power timer, 1x SysTick, 1x RTC and 2x watchdogs (independent/window)
- CRC calculation unit, 96-bit unique ID
- LFQFP64 package is ECOPACK2 compliant



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32L010RB ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32l010rb.html#documentation) |          STM32L010RB datasheet and other resources           |



## Maintained By

 [xph](https://github.com/xupenghu), <xupenghu@outlook.com>



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf