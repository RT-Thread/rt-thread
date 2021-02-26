# STM32F446-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32F446ZE @180MHz, 512KB FLASH,  128KB RAM

The STM32F446xC/E devices are based on the high-performance Arm® Cortex®-M4 32-bit RISC core operating at a frequency of up to 180 MHz. The Cortex-M4 core features a floating point unit (FPU) single precision supporting all Arm® single-precision data-processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) that enhances application security.

The STM32F446xC/E devices incorporate high-speed embedded memories (Flash memory up to 512 Kbytes, up to 128 Kbytes of SRAM), up to 4 Kbytes of backup SRAM, and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB buses and a 32-bit multi-AHB bus matrix.
All devices offer three 12-bit ADCs, two DACs, a low-power RTC, twelve general-purpose 16-bit timers including two PWM timers for motor control, two general-purpose 32-bit timers.
They also feature standard and advanced communication interfaces.

#### KEY FEATURES

- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator) allowing 0-wait state execution from Flash memory, frequency up to 180 MHz, MPU, 225 DMIPS/1.25 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - 512 Kbytes of Flash memory
  - 128 Kbytes of SRAM
  - Flexible external memory controller with up to 16-bit data bus: SRAM, PSRAM, SDRAM/LPSDR SDRAM, NOR/NAND Flash memories
  - Dual mode QuadSPI interface
- LCD parallel interface, 8080/6800 modes
- Clock, reset and supply management
  - 1.7 V to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - 4 to 26 MHz crystal oscillator
  - Internal 16 MHz factory-trimmed RC (1% accuracy)
  - 32 kHz oscillator for RTC with calibration
  - Internal 32 kHz RC with calibration
- Low power
  - Sleep, Stop and Standby modes
  - VBAT supply for RTC, 20×32 bit backup registers plus optional 4 KB backup SRAM
- 3× 12-bit, 2.4 MSPS ADC: up to 24 channels and 7.2 MSPS in triple interleaved mode
- 2× 12-bit D/A converters
- General-purpose DMA: 16-stream DMA controller with FIFOs and burst support
- Up to 17 timers: 2x watchdog, 1x SysTick timer and up to twelve 16-bit and two 32-bit timers up to 180 MHz, each with up to four IC/OC/PWM or pulse counter

- Debug mode
  - SWD and JTAG interfaces
  - Cortex®-M4 Trace Macrocell™
- Up to 114 I/O ports with interrupt capability
  - Up to 111 fast I/Os up to 90 MHz
  - Up to 112 5 V-tolerant I/Os
- Up to 20 communication interfaces
  - SPDIF-Rx
  - Up to 4× I2C interfaces (SMBus/PMBus)
  - Up to four USARTs and two UARTs (11.25 Mbit/s, ISO7816 interface, LIN, IrDA, modem control)
  - Up to four SPIs (45 Mbits/s), three with muxed I2S for audio class accuracy via internal audio PLL or external clock
  - 2x SAI (serial audio interface)
  - 2× CAN (2.0B Active)
  - SDIO interface
  - Consumer electronics control (CEC) I/F
- Advanced connectivity
  - USB 2.0 full-speed device/host/OTG controller with on-chip PHY
  - USB 2.0 high-speed/full-speed device/host/OTG controller with dedicated DMA, on-chip full-speed PHY and ULPI
  - Dedicated USB power rail enabling on-chip PHYs operation throughout the entire MCU power supply range
- 8- to 14-bit parallel camera interface up to 54 Mbytes/s
- CRC calculation unit
- RTC: subsecond accuracy, hardware calendar
- 96-bit unique ID



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32F446ZE ST Official Website](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus/stm32-high-performance-mcus/stm32f4-series/stm32f446/stm32f446ze.html#documentation) |          STM32F446ZE datasheet and other resources           |



## Maintained By

qihengchuan8888@163.com



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf