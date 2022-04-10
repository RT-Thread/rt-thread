# SAME70Q21B BSP 介绍

[English](README.md) 
- MCU: ATSAME70Q21B @300MHz, 2MB FLASH, 384KB RAM
- V71: 汽车级产品 AEC-Q100 Cortex-M7内核 + 100M以太网 + 2路CAN-FD + 丰富外设
- E70: 工业级产品 -40~105C Cortex-M7内核 + 100M以太网 + 2路CAN-FD + 丰富外设
- S70: 工业级产品 -40~105C Cortex-M7内核 + 丰富外设
- 管脚: J系列-64 pins, N系列-100 pins, Q系列-144 pins
- Flash: 尾缀19=512KB, 20=1024KB, 21=2048KB (flash容量=2^n)
- 手册: <https://www.microchip.com/en-us/product/ATSAME70Q21>

#### 关键特性

#### 内核
  - 32-bit Arm® Cortex®-M7 core + 双精度FPU + L1 cache: 16 Kbytes 数据DCache and 16 Kbytes 指令 Icache; 主频高达300 MHz, MPU, 2.14 DMIPS/MHz (Dhrystone 2.1), 支持 DSP指令集

#### 内存
  - 最大提供2MB 内嵌Flash，芯片内嵌独一无二的UID信息
  - 最大提供384KB 内嵌多端口SRAM, 可以将其配置为ITCM, DTCM.
  - 内部集成16 Kbytes ROM，用于板载Bootloader(UART0, USB)和IAP应用.
  
####  外设
  - 16-bit Static Memory Controller (SMC) with support for SRAM, PSRAM, LCD module, NOR and NAND Flash with on-the-fly scrambling
  - 16-bit SDRAM Controller (SDRAMC) interfacing up to 128 MB and with on-the-fly scrambling
  - One Ethernet MAC (GMAC) 10/100 Mbps in MII mode and RMII with dedicated DMA. IEEE® 1588 PTP frames and 802.3az Energy-efficiency support.
  - USB 2.0 Device/Mini Host High-speed (USBHS) at 480 Mbps, 4-Kbyte FIFO, up to 10 bidirectional endpoints, dedicated DMA
  - 12-bit ITU-R BT. 601/656 Image Sensor Interface (ISI)
  - Two master Controller Area Networks (MCAN) with Flexible Data Rate (CAN-FD) with SRAM-based mailboxes, time-triggered and event-triggered transmission
  - MediaLB® device with 3-wire mode, up to 1024 x Fs speed, supporting MOST25 and MOST50 networks
  - Three USARTs, USART0, USART1, USART2, support LIN mode, ISO7816, IrDA®, RS-485, SPI, Manchester and Modem modes; USART1 supports LON mode.
  - Five 2-wire UARTs with SleepWalking™ support
  - Three Two-Wire Interfaces (TWIHS) (I2C-compatible) with SleepWalking support
  - Quad I/O Serial Peripheral Interface (QSPI) interfacing up to 256 MB Flash and with eXecute-In-Place and onthe-fly scrambling
  - Two Serial Peripheral Interfaces (SPI)
  - One Serial Synchronous Controller (SSC) with I2S and TDM support
  - Two Inter-IC Sound Controllers (I2SC)
  - One High-speed Multimedia Card Interface (HSMCI) (SDIO/SD Card/e.MMC)
  - Four Three-Channel 16-bit Timer/Counters (TC) with Capture, Waveform, Compare and PWM modes, constant on time. Quadrature decoder logic and 2-bit Gray Up/Down Counter for stepper motor
  - Two 4-channel 16-bit PWMs with complementary outputs, Dead Time Generator and eight fault inputs per PWM for motor control, two external triggers to manage power factor correction (PFC), DC-DC and lighting control
  - Two Analog Front-End Controllers (AFEC), each supporting up to 12 channels with differential input mode and programmable gain stage, allowing dual sample-and-hold (S&H) at up to 1.7 Msps. Offset and gain error correction feature.
  - One 2-channel, 12-bit, 1 Msps-per-channel Digital-to-Analog Controller (DAC) with Differential and Over Sampling modes
  - One Analog Comparator Controller (ACC) with flexible input selection, selectable input hysteresis

#### 加密模块
  - True Random Number Generator (TRNG)
  - AES: 256-bit, 192-bit, 128-bit Key Algorithm, Compliant with FIPS PUB-197 Specifications
  - Integrity Check Monitor (ICM). Supports Secure Hash Algorithm SHA1, SHA224 and SHA256.

#### I/O接口
  - Up to 114 I/O lines with external interrupt capability (edge- or level-sensitivity), debouncing, glitch filtering and On-die Series Resistor Termination
  - Five Parallel Input/Output Controllers (PIO)

#### 工作电压
  - Single supply voltage from 3.0V to 3.6V for Qualification AEC - Q100 Grade 2 Devices
  - Single Supply voltage from 1.7V to 3.6V for Industrial Temperature Devices

#### 封装
  - LQFP144, 144-lead LQFP, 20x20 mm, pitch 0.5 mm
  - LFBGA144, 144-ball LFBGA, 10x10 mm, pitch 0.8 mm
  - TFBGA144, 144-ball TFBGA, 10x10 mm, pitch 0.8 mm
  - UFBGA144, 144-ball UFBGA, 6x6 mm, pitch 0.4 mm
  - LQFP100, 100-lead LQFP, 14x14 mm, pitch 0.5 mm
  - TFBGA100, 100-ball TFBGA, 9x9 mm, pitch 0.8 mm
  - VFBGA100, 100-ball VFBGA, 7x7 mm, pitch 0.65 mm
  - LQFP64, 64-lead LQFP, 10x10 mm, pitch 0.5 mm
  - QFN64, 64-pad QFN 9x9 mm, pitch 0.5 mm with wettable flanks

#### 官方开发板信息
- [SAM E70 XPLAINED](https://www.microchip.com/en-us/development-tool/ATSAME70-XPLD)
