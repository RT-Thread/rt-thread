# STM32G071-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32G071RB @64MHz, 128KB FLASH,  36KB RAM

The STM32G071x8/xB mainstream microcontrollers are based on high-performance Arm® Cortex®-M0+ 32-bit RISC core operating at up to 64 MHz frequency. Offering a high level of integration, they are suitable for a wide range of applications in consumer, industrial and appliance domains and ready for the Internet of Things (IoT) solutions.

The devices incorporate a memory protection unit (MPU), high-speed embedded memories (up to 128 Kbytes of Flash program memory with read protection, write protection, proprietary code protection, and securable area, and 36 Kbytes of SRAM), DMA and an extensive range of system functions, enhanced I/Os and peripherals. The devices offer standard communication interfaces (two I2Cs, two SPIs / one I2S, one HDMI CEC, and four USARTs), one 12-bit ADC (2.5 MSps) with up to 19 channels, one 12-bit DAC with two channels, two fast comparators, an internal voltage reference buffer, a low-power RTC, an advanced control PWM timer running at up to double the CPU frequency, five general-purpose 16-bit timers with one running at up to double the CPU frequency, a 32-bit general-purpose timer, two basic timers, two low-power 16-bit timers, two watchdog timers, and a SysTick timer. The STM32G071x8/xB devices provide a fully integrated USB Type-C Power Delivery controller.
The devices operate within ambient temperatures from -40 to 125°C. They can operate with supply voltages from 1.7 V to 3.6 V. Optimized dynamic consumption combined with a comprehensive set of power-saving modes, low-power timers and low-power UART, allows the design of low-power applications.
VBAT direct battery input allows keeping RTC and backup registers powered.
The devices come in packages with 28 to 64 pins.

#### KEY FEATURES

- Core: Arm® 32-bit Cortex®-M0+ CPU, frequency up to 64 MHz
- -40°C to 85°C/105°C/125°C operating temperature
- Memories
  - Up to 128 Kbytes of Flash memory with protection and securable area
  - 36 Kbytes of SRAM (32 Kbytes with HW parity check)
- CRC calculation unit
- Reset and power management
  - Voltage range: 1.7 V to 3.6 V
  - Power-on/Power-down reset (POR/PDR)
  - Programmable Brownout reset (BOR)
  - Programmable voltage detector (PVD)
  - Low-power modes:Sleep, Stop, Standby, Shutdown
  - VBAT supply for RTC and backup registers
- Clock management
  - 4 to 48 MHz crystal oscillator
  - 32 kHz crystal oscillator with calibration
  - Internal 16 MHz RC with PLL option (±1 %)
  - Internal 32 kHz RC oscillator (±5 %)
- Up to 60 fast I/Os
  - All mappable on external interrupt vectors
  - Multiple 5 V-tolerant I/Os
- 7-channel DMA controller with flexible mapping
- 12-bit, 0.4 µs ADC (up to 16 ext. channels)
  - Up to 16-bit with hardware oversampling
  - Conversion range: 0 to 3.6V

- Two 12-bit DACs, low-power sample-and-hold
- Two fast low-power analog comparators, with programmable input and output, rail-to-rail
- 14 timers (two 128 MHz capable): 16-bit for advanced motor control, one 32-bit and five 16-bit general-purpose, two basic 16-bit, two low-power 16-bit, two watchdogs, SysTick timer
- Calendar RTC with alarm and periodic wakeup from Stop/Standby/Shutdown
- Communication interfaces
  - Two I2C-bus interfaces supporting Fast-mode Plus (1 Mbit/s) with extra current sink, one supporting SMBus/PMBus and wakeup from Stop mode
  - Four USARTs with master/slave synchronous SPI; two supporting ISO7816 interface, LIN, IrDA capability, auto baud rate detection and wakeup feature
  - One low-power UART
  - Two SPIs (32 Mbit/s) with 4- to 16-bit programmable bitframe, one multiplexed with I2S interface
  - HDMI CEC interface, wakeup on header
- USB Type-C™ Power Delivery controller
- Development support: serial wire debug (SWD)
- 96-bit unique ID
- All packages ECOPACK®2 compliant



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32G071RB ST Official Website](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-g071rb.html#documentation) |          STM32G071RB datasheet and other resources           |



## Maintained By

[gztss](https://github.com/gztss)



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf