# STM32L053-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32L053R8 @32MHz, 64KB FLASH,  8KB RAM

The ultra-low-power STM32L053x6/8 microcontrollers incorporate the connectivity power of the universal serial bus (USB 2.0 crystal-less) with the high-performance Arm® Cortex®-M0+ 32-bit RISC core operating at a 32 MHz frequency, a memory protection unit (MPU), high-speed embedded memories (up to 64 Kbytes of Flash program memory, 2 Kbytes of data EEPROM and 8 Kbytes of RAM) plus an extensive range of enhanced I/Os and peripherals.

The STM32L053x6/8 devices provide high power efficiency for a wide range of performance. It is achieved with a large choice of internal and external clock sources, an internal voltage adaptation and several low-power modes.
The STM32L053x6/8 devices offer several analog features, one 12-bit ADC with hardware oversampling, one DAC, two ultra-low-power comparators, several timers, one low-power timer (LPTIM), three general-purpose 16-bit timers and one basic timer, one RTC and one SysTick which can be used as timebases. They also feature two watchdogs, one watchdog with independent clock and window capability and one window watchdog based on bus clock.
Moreover, the STM32L053x6/8 devices embed standard and advanced communication interfaces: up to two I2C, two SPIs, one I2S, two USARTs, a low-power UART (LPUART), and a crystal-less USB. The devices offer up to 24 capacitive sensing channels to simply add touch sensing functionality to any application.
The STM32L053x6/8 also include a real-time clock and a set of backup registers that remain powered in Standby mode.
Finally, their integrated LCD controller has a built-in LCD voltage generator that allows to drive up to 8 multiplexed LCDs with contrast independent of the supply voltage.
The ultra-low-power STM32L053x6/8 devices operate from a 1.8 to 3.6 V power supply (down to 1.65 V at power down) with BOR and from a 1.65 to 3.6 V power supply without BOR option. They are available in the -40 to +125 °C temperature range. A comprehensive set of power-saving modes allows the design of low-power applications.

#### KEY FEATURES

- Ultra-low-power platform
  - 1.65 V to 3.6 V power supply
  - -40 to 125 °C temperature range
  - 0.27 μA Standby mode (2 wakeup pins)
  - 0.4 μA Stop mode (16 wakeup lines)
  - 0.8 μA Stop mode + RTC + 8 KB RAM retention
  - 88 μA/MHz in Run mode
  - 3.5 μs wakeup time (from RAM)
  - 5 μs wakeup time (from Flash memory)
- Core: Arm® 32-bit Cortex®-M0+ with MPU
  - From 32 kHz up to 32 MHz max.
  - 0.95 DMIPS/MHz
- Memories
  - Up to 64 KB Flash memory with ECC
  - 8KB RAM
  - 2 KB of data EEPROM with ECC
  - 20-byte backup register
  - Sector protection against R/W operation
- Up to 51 fast I/Os (45 I/Os 5V tolerant)
- Reset and supply management
  - Ultra-safe, low-power BOR (brownout reset) with 5 selectable thresholds
  - Ultra-low-power POR/PDR
  - Programmable voltage detector (PVD)
- Clock sources
  - 1 to 25 MHz crystal oscillator
  - 32 kHz oscillator for RTC with calibration
  - High speed internal 16 MHz factory-trimmed RC (+/- 1%)
  - Internal low-power 37 kHz RC
  - Internal multispeed low-power 65 kHz to 4.2 MHz RC
  - PLL for CPU clock
- Pre-programmed bootloader
  - USART, SPI supported
- Development support
  - Serial wire debug supported
- LCD driver for up to 8×28segments
  - Support contrast adjustment
  - Support blinking mode
  - Step-up converted on board

- Rich Analog peripherals
  - 12-bit ADC 1.14 Msps up to 16 channels (down to 1.65 V)
  - 12-bit 1 channel DAC with output buffers (down to 1.8 V)
  - 2x ultra-low-power comparators (window mode and wake up capability, down to 1.65 V)
- Up to 24 capacitive sensing channels supporting touchkey, linear and rotary touch sensors
- 7-channel DMA controller, supporting ADC, SPI, I2C, USART, DAC, Timers
- 8x peripheral communication interfaces
  - 1x USB 2.0 crystal-less, battery charging detection and LPM
  - 2x USART (ISO 7816, IrDA), 1x UART (low power)
  - Up to 4x SPI 16 Mbits/s
  - 2x I2C (SMBus/PMBus)
- 9x timers: 1x 16-bit with up to 4 channels, 2x 16-bit with up to 2 channels, 1x 16-bit ultra-low-power timer, 1x SysTick, 1x RTC, 1x 16-bit basic for DAC, and 2x watchdogs (independent/window)
- CRC calculation unit, 96-bit unique ID
- True RNG and firewall protection
- All packages are ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32L053R8 ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32l053r8.html#documentation) |          STM32L053R8 datasheet and other resources           |



## Maintained By

 [sun_shine](https://github.com/xupenghu), <baozitai@163.com>



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf