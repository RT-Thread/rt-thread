# STM32H743-Nucleo BSP Introduction

[中文](README_zh.md) 

## MCU: STM32H743ZI @480MHz, 2MB FLASH,  1MB RAM

STM32H742xI/G and STM32H743xI/G devices are based on the high-performance Arm® Cortex®-M7 32-bit RISC core operating at up to 480 MHz. The Cortex® -M7 core features a floating point unit (FPU) which supports Arm® double-precision (IEEE 754 compliant) and single-precision data-processing instructions and data types. STM32H742xI/G and STM32H743xI/G devices support a full set of DSP instructions and a memory protection unit (MPU) to enhance application security.

STM32H742xI/G and STM32H743xI/G devices incorporate high-speed embedded memories with a dual-bank Flash memory of up to 2 Mbytes, up to 1 Mbyte of RAM (including 192 Kbytes of TCM RAM, up to 864 Kbytes of user SRAM and 4 Kbytes of backup SRAM), as well as an extensive range of enhanced I/Os and peripherals connected to APB buses, AHB buses, 2x32-bit multi-AHB bus matrix and a multi layer AXI interconnect supporting internal and external memory access.

#### KEY FEATURES

- Core
  - 32-bit Arm® Cortex®-M7 core with double-precision FPU and L1 cache: 16 Kbytes of data and 16 Kbytes of instruction cache; frequency up to 480 MHz, MPU, 1027 DMIPS/ 2.14 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 2 Mbytes of Flash memory with read-while-write support
  - Up to 1 Mbyte of RAM: 192 Kbytes of TCM RAM (inc. 64 Kbytes of ITCM RAM + 128 Kbytes of DTCM RAM for time critical routines), Up to 864 Kbytes of user SRAM, and 4 Kbytes of SRAM in Backup domain
  - Dual mode Quad-SPI memory interface running up to 133 MHz
  - Flexible external memory controller with up to 32-bit data bus: SRAM, PSRAM, SDRAM/LPSDR SDRAM, NOR/NAND Flash memory clocked up to 100 MHz in Synchronous mode
  - CRC calculation unit
- Security
  - ROP, PC-ROP, active tamper
- General-purpose input/outputs
  - Up to 168 I/O ports with interrupt capability
- Reset and power management
  - 3 separate power domains which can be independently clock-gated or switched off:
    - D1: high-performance capabilities
    - D2: communication peripherals and timers
    - D3: reset/clock control/power management
  - 1.62 to 3.6 V application supply and I/Os
  - POR, PDR, PVD and BOR
  - Dedicated USB power embedding a 3.3 V internal regulator to supply the internal PHYs
  - Embedded regulator (LDO) with configurable scalable output to supply the digital circuitry
  - Voltage scaling in Run and Stop mode (6 configurable ranges)
  - Backup regulator (~0.9 V)
  - Voltage reference for analog peripheral/VREF+
  - Low-power modes: Sleep, Stop, Standby and VBAT supporting battery charging
- Low-power consumption
  - VBAT battery operating mode with charging capability
  - CPU and domain power state monitoring pins
  - 2.95 μA in Standby mode (Backup SRAM OFF, RTC/LSE ON)
- Clock management
  - Internal oscillators: 64 MHz HSI, 48 MHz HSI48, 4 MHz CSI, 32 kHz LSI
  - External oscillators: 4-48 MHz HSE, 32.768 kHz LSE
  - 3× PLLs (1 for the system clock, 2 for kernel clocks) with Fractional mode
- Interconnect matrix

- 4 DMA controllers to unload the CPU
  - 1× high-speed master direct memory access controller (MDMA) with linked list support
  - 2× dual-port DMAs with FIFO
  - 1× basic DMA with request router capabilities
- Up to 35 communication peripherals
  - 4× I2Cs FM+ interfaces (SMBus/PMBus)
  - 4× USARTs/4x UARTs (ISO7816 interface, LIN, IrDA, up to 12.5 Mbit/s) and 1x LPUART
  - 6× SPIs, 3 with muxed duplex I2S audio class accuracy via internal audio PLL or external clock, 1x I2S in LP domain (up to 150 MHz)
  - 4x SAIs (serial audio interface)
  - SPDIFRX interface
  - SWPMI single-wire protocol master I/F
  - MDIO Slave interface
  - 2× SD/SDIO/MMC interfaces (up to 125 MHz)
  - 2× CAN controllers: 2 with CAN FD, 1 with time-triggered CAN (TT-CAN)
  - 2× USB OTG interfaces (1FS, 1HS/FS) crystal-less solution with LPM and BCD
  - Ethernet MAC interface with DMA controller
  - HDMI-CEC
  - 8- to 14-bit camera interface (up to 80 MHz)
- 11 analog peripherals
  - 3× ADCs with 16-bit max. resolution (up to 36 channels, up to 3.6 MSPS)
  - 1× temperature sensor
  - 2× 12-bit D/A converters (1 MHz)
  - 2× ultra-low-power comparators
  - 2× operational amplifiers (7.3 MHz bandwidth)
  - 1× digital filters for sigma delta modulator (DFSDM) with 8 channels/4 filters
- Graphics
  - LCD-TFT controller up to XGA resolution
  - Chrom-ART graphical hardware Accelerator™ (DMA2D) to reduce CPU load
  - Hardware JPEG Codec
- Up to 22 timers and watchdogs
  - 1× high-resolution timer (2.1 ns max resolution)
  - 2× 32-bit timers with up to 4 IC/OC/PWM or pulse counter and quadrature (incremental) encoder input (up to 240 MHz)
  - 2× 16-bit advanced motor control timers (up to 240 MHz)
  - 10× 16-bit general-purpose timers (up to 240 MHz)
  - 5× 16-bit low-power timers (up to 240 MHz)
  - 2× watchdogs (independent and window)
  - 1× SysTick timer
  - RTC with sub-second accuracy and hardware calendar
- Debug mode
  - SWD & JTAG interfaces
  - 4-Kbyte Embedded Trace Buffer
- True random number generators (3 oscillators each)
- 96-bit unique ID



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32H743ZI ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32h743zi.html#documentation) |          STM32H743ZI datasheet and other resources           |



## Maintained By

[tyustli](https://github.com/tyustli)



## Translated By

Meco Man @ RT-Thread Community

> jiantingman@foxmail.com 
>
> https://github.com/mysterywolf