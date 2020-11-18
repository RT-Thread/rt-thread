# STM32F072-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F072RB @48MHz, 128KB FLASH,  16KB RAM

The STM32F072x8/xB microcontrollers incorporate the high-performance ARM®Cortex®-M0 32-bit RISC core operating at up to 48 MHz frequency, high-speed embedded memories (up to 128 Kbytes of Flash memory and 16 Kbytes of SRAM), and an extensive range of enhanced peripherals and I/Os. All devices offer standard communication interfaces (two I2Cs, two SPI/I2S, one HDMI CEC and four USARTs), one USB Full-speed device (crystal-less), one CAN, one 12-bit ADC, one 12-bit DAC with two channels, seven 16-bit timers, one 32-bit timer and an advanced-control PWM timer.

The STM32F072x8/xB microcontrollers operate in the -40 to +85 °C and -40 to +105 °C temperature ranges, from a 2.0 to 3.6 V power supply. A comprehensive set of power-saving modes allows the design of low-power applications.
The STM32F072x8/xB microcontrollers include devices in seven different packages ranging from 48 pins to 100 pins with a die form also available upon request. Depending on the device chosen, different sets of peripherals are included.
These features make the STM32F072x8/xB microcontrollers suitable for a wide range of applications such as application control and user interfaces, hand-held equipment, A/V receivers and digital TV, PC peripherals, gaming and GPS platforms, industrial applications, PLCs, inverters, printers, scanners, alarm systems, video intercoms and HVACs.

#### KEY FEATURES

- Core: ARM®32-bit Cortex®-M0 CPU, frequency up to 48 MHz

- Memories

  - 64 to 128 Kbytes of Flash memory
  - 16 Kbytes of SRAM with HW parity

- CRC calculation unit

- Reset and power management

  - Digital and I/O supply: VDD= 2.0 V to 3.6 V
  - Analog supply: VDDA= VDDto 3.6 V
  - Selected I/Os: VDDIO2= 1.65 V to 3.6 V
  - Power-on/Power down reset (POR/PDR)
  - Programmable voltage detector (PVD)
  - Low power modes: Sleep, Stop, Standby
  - VBATsupply for RTC and backup registers

- Clock management

  - 4 to 32 MHz crystal oscillator
  - 32 kHz oscillator for RTC with calibration
  - Internal 8 MHz RC with x6 PLL option
  - Internal 40 kHz RC oscillator
  - Internal 48 MHz oscillator with automatic trimming based on ext. synchronization

- Up to 87 fast I/Os

  - All mappable on external interrupt vectors
  - Up to 68 I/Os with 5V tolerant capability and 19 with independent supply VDDIO2

- Seven-channel DMA controller

- One 12-bit, 1.0 μs ADC (up to 16 channels)

  - Conversion range: 0 to 3.6 V
  - Separate analog supply: 2.4 V to 3.6 V

- One 12-bit D/A converter (with 2 channels)

- Two fast low-power analog comparators with programmable input and output

- Up to 24 capacitive sensing channels for touchkey, linear and rotary touch sensors

- Calendar RTC with alarm and periodic wakeup from Stop/Standby

- 12 timers

  - One 16-bit advanced-control timer for six-channel PWM output
  - One 32-bit and seven 16-bit timers, with up to four IC/OC, OCN, usable for IR control decoding or DAC control
  - Independent and system watchdog timers
  - SysTick timer

- Communication interfaces

  - Two I2C interfaces supporting Fast Mode Plus (1 Mbit/s) with 20 mA current sink, one supporting SMBus/PMBus and wakeup
  - Four USARTs supporting master synchronous SPI and modem control, two with ISO7816 interface, LIN, IrDA, auto baud rate detection and wakeup feature
  - Two SPIs (18 Mbit/s) with 4 to 16 programmable bit frames, and with I2S interface multiplexed
  - CAN interface
  - USB 2.0 full-speed interface, able to run from internal 48 MHz oscillator and with BCD and LPM support

- HDMI CEC wakeup on header reception

- Serial wire debug (SWD)

- 96-bit unique ID

- All packages ECOPACK®2



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32F072RB ST Official Website](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus/stm32-mainstream-mcus/stm32f0-series/stm32f0x2/stm32f072rb.html#documentation) |          STM32F072RB datasheet and other resources           |



## Maintained By

[刘恒](https://github.com/lhxzui)

iuzxhl@qq.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf