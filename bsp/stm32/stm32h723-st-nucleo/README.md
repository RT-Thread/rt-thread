# STM32H723-Nucleo BSP Introduction

[中文](README_zh.md) 

### Description

STM32H723xE/G devices are based on the high-performance Arm® Cortex®-M7 32-bit RISC core operating at up to 550 MHz. The Cortex® -M7 core features a floating-point unit (FPU) which supports Arm® double-precision (IEEE 754 compliant) and single-precision data-processing instructions and data types. The Cortex -M7 core includes 32 Kbytes of instruction cache and 32 Kbytes of data cache. STM32H723xE/G devices support a full set of DSP instructions and a memory protection unit (MPU) to enhance application security.

STM32H723xE/G devices incorporate high-speed embedded memories with up to 1 Mbyte of flash memory, up to 564 Kbytes of RAM (including 192 Kbytes that can be shared between ITCM and AXI, plus 64 Kbytes exclusively ITCM, plus 128 Kbytes exclusively AXI, 128 Kbyte DTCM, 48 Kbytes AHB and 4 Kbytes of backup RAM), as well as an extensive range of enhanced I/Os and peripherals connected to APB buses, AHB buses, 2x32-bit multi-AHB bus matrix and a multilayer AXI interconnect supporting internal and external memory access. To improve application robustness, all memories feature error code correction (one error correction, two error detections).

The devices embed peripherals allowing mathematical/arithmetic function acceleration (CORDIC coprocessor for trigonometric functions and FMAC unit for filter functions). All the devices offer three ADCs, two DACs, two operational amplifiers, two ultra-low-power comparators, a low-power RTC, four general-purpose 32-bit timers, 12 general-purpose 16-bit timers including two PWM timers for motor control, five low-power timers, a true random number generator (RNG). The devices support four digital filters for external sigma-delta modulators (DFSDM). They also feature standard and advanced communication interfaces.

### All features

- Includes ST state-of-the-art patented technology
- Core
  - 32-bit Arm® Cortex®-M7 CPU with DP-FPU, L1 cache: 32-Kbyte data cache and 32-Kbyte instruction cache allowing 0-wait state execution from embedded flash memory and external memories, frequency up to 550 MHz, MPU, 1177 DMIPS/2.14 DMIPS/MHz (Dhrystone 2.1), and DSP instructions
- Memories
  - Up to 1 Mbyte of embedded flash memory with ECC
  - SRAM: total 564 Kbytes all with ECC, including 128 Kbytes of data TCM RAM for critical real-time data + 432 Kbytes of system RAM (up to 256 Kbytes can remap on instruction TCM RAM for critical real time instructions) + 4 Kbytes of backup SRAM (available in the lowest-power modes)
  - Flexible external memory controller with up to 16-bit data bus: SRAM, PSRAM, SDRAM/LPSDR SDRAM, NOR/NAND memories
  - 2 x Octo-SPI interface with XiP
  - 2 x SD/SDIO/MMC interface
  - Bootloader
- Graphics
  - Chrom-ART Accelerator graphical hardware accelerator enabling enhanced graphical user interface to reduce CPU load
  - LCD-TFT controller supporting up to XGA resolution
- Clock, reset and supply management
  - 1.62 V to 3.6 V application supply and I/O
  - POR, PDR, PVD and BOR
  - Dedicated USB power
  - Embedded LDO regulator
  - Internal oscillators: 64 MHz HSI, 48 MHz HSI48, 4 MHz CSI, 32 kHz LSI
  - External oscillators: 4-50 MHz HSE, 32.768 kHz LSE
- Low power
  - Sleep, Stop and Standby modes
  - VBAT supply for RTC, 32×32-bit backup registers
- Analog
  - 2×16-bit ADC, up to 3.6 MSPS in 16-bit: up to 18 channels and 7.2 MSPS in double-interleaved mode
  - 1 x 12-bit ADC, up to 5 MSPS in 12-bit, up to 12 channels
  - 2 x comparators
  - 2 x operational amplifier GBW = 8 MHz
  - 2× 12-bit D/A converters
- Digital filters for sigma delta modulator (DFSDM)
  - 8 channels/4 filters
- 4 DMA controllers to offload the CPU
  - 1 × MDMA with linked list support
  - 2 × dual-port DMAs with FIFO
  - 1 × basic DMA with request router capabilities
- 24 timers
  - Seventeen 16-bit (including 5 x low power 16-bit timer available in stop mode) and four 32-bit timers, each with up to 4 IC/OC/PWM or pulse counter and quadrature (incremental) encoder input
  - 2x watchdogs, 1x SysTick timer
- Debug mode
  - SWD and JTAG interfaces
  - 2-Kbyte embedded trace buffer

- Up to 114 I/O ports with interrupt capability
- Up to 35 communication interfaces
  - Up to 5 × I2C FM+ interfaces (SMBus/PMBus™)
  - Up to 5 USARTs/5 UARTs (ISO7816 interface, LIN, IrDA, modem control) and 1 x LPUART
  - Up to 6 SPIs with 4 with muxed duplex I2S for audio class accuracy via internal audio PLL or external clock and up to 5 x SPI (from 5 x USART when configured in synchronous mode)
  - 2x SAI (serial audio interface)
  - 1× FD/TT-CAN and 2x FD-CAN
  - 8- to 14-bit camera interface
  - 16-bit parallel slave synchronous interface
  - SPDIF-IN interface
  - HDMI-CEC
  - Ethernet MAC interface with DMA controller
  - USB 2.0 high-speed/full-speed device/host/OTG controller with dedicated DMA, on-chip FS PHY and ULPI for external HS PHY
  - SWPMI single-wire protocol master I/F
  - MDIO slave interface
- Mathematical acceleration
  - CORDIC for trigonometric functions acceleration
  - FMAC: Filter mathematical accelerator
- Digital temperature sensor
- True random number generator
- CRC calculation unit
- RTC with subsecond accuracy and hardware calendar
- ROP, PC-ROP, tamper detection
- 96-bit unique ID
- All packages are ECOPACK2 compliant

## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-144_BSP_Introduction](../docs/STM32_Nucleo-144_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-144 boards (**Must-Read**) |
| [STM32H723ZG ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32h723zg.html#documentation) |          STM32H723ZG datasheet and other resources           |

## Maintained By

[hywing](https://github.com/hywing)