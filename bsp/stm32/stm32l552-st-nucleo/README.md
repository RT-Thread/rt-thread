# NUCLEO-STM32L552ZE-Q- BSP Introduction

[中文](README_zh.md)

## MCU: STM32L552ZE @110MHz, 256 KB FLASH,  156KB RAM

The STM32L552xx devices are an ultra-low-power microcontrollers family (STM32L5 Series) based on the high-performance Arm® Cortex®-M33 32-bit RISC core. They operate at a frequency of up to 110 MHz. The Cortex-M33 core features a single-precision floating-point unit (FPU), which supports all the Arm® single-precision data-processing instructions and all the data types. The Cortex-M33 core also implements a full set of DSP (digital signal processing) instructions, TrustZone aware support and a memory protection unit (MPU) which enhances the applications security. These devices embed high-speed memories (512 Kbytes of Flash memory and 256 Kbytes of SRAM), a flexible external memory controller (FSMC) for static memories (for devices with packages of 100 pins and more), an OctoSPI Flash memories interface (available on all packages) and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB buses and a 32-bit multi-AHB bus matrix.

The STM32L552xx devices embed several protection mechanisms for embedded Flash memory and SRAM: readout protection, write protection, secure and hide protection areas. These devices offer two fast 12-bit ADC (5 Msps), two comparators, two operational amplifiers, two DAC channels, an internal voltage reference buffer, a low-power RTC, two general-purpose 32-bit timer, two 16-bit PWM timers dedicated to motor control, seven general-purpose 16-bit timers, and two 16-bit low-power timers. The devices support four digital filters for external sigma delta modulators (DFSDM). In addition, up to 22 capacitive sensing channels are available.

#### KEY FEATURES

- Core
  - Ultra-low-power with FPU Arm Cortex-M33 with Trust Zone
- Memories
  - Up to 512 Kbytes Flash, two banks read-while-write
  - 256 Kbytes of SRAM including 64 Kbytes with hardware parity check
  - External memory interface supporting SRAM, PSRAM, NOR, NAND and FRAM memories
  - OCTOSPI memory interface
- Security
  - Arm TrustZone with the ARMv8-M mainline security extension
  - Up to 8 configurable SAU regions
  - RDP, active tamper, secure firmware upgrade support, secure hide protection
  - TrustZone aware and securable peripherals
- General-purpose input/outputs
  - Up to 114 fast I/Os with interrupt capability most 5 V-tolerant and up to 14 I/Os with independent supply down to 1.08 V
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
| [STM32L552ZE ST Official Website]([STM32L552ZE - Ultra-low-power with FPU Arm Cortex-M33 with Trust Zone, MCU 110 MHz with 512 kbytes of Flash memory - STMicroelectronics](https://www.st.com/en/microcontrollers-microprocessors/stm32l552ze.html)) |           STM32L552ZEdatasheet and other resources

## Maintained By

[liukang](https://github.com/liukangcc)
