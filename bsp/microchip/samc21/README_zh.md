# SAMC21J18A BSP 介绍

[English](README.md) 

- MCU: ATSAMC21J18A @64MHz, 256KB FLASH, 32KB RAM, 2.7V – 5.5V
- C21: Cortex-M0+内核 + 丰富外设 + 2路CAN-FD + Delta-Sigma ADC
- 管脚: N系列-100 pins, J系列-64 pins, G系列-48 pins, E系列-32 pins
- Flash: 18=256KB, 17=128KB, 16=64KB , 15=32KB(size=2^n)
- SRAM : 32KB(Flash 256KB), 16KB(Flash 128KB), 8KB(Flash 64KB), 4KB(Flash 32KB)
## 手册: <https://www.microchip.com/en-us/product/ATSAMC21J18A>

#### KEY FEATURES

#### 内核
  - 32-bit Arm® Cortex®-M0+ 内核， 主频最高48MHz和64 MHz+单指令周期的硬件乘法器

####  内存
  - 32/64/128/256 KB in-system self-programmable Flash
  - 1/2/4/8 KB independent self-programmable Flash for EEPROM emulation
  - 4/8/16/32 KB SRAM main memory

#### 系统特性
  - Power-on Reset (POR) and Brown-out Detection (BOD)
  - Internal and external clock options with 48 MHz to 96 MHz Fractional Digital Phase Locked Loop (FDPLL96M)
  - External Interrupt Controller (EIC) (Interrupt pin debouncing is only available in SAM C20/C21 N)
  - 16 external interrupts
  - One non-maskable interrupt
  - Two-pin Serial Wire Debug (SWD) programming, test, and debugging interface

#### 高性能外设
  - Hardware Divide and Square Root Accelerator (DIVAS)
  - 12-channel Direct Memory Access Controller (DMAC)
  - 12-channel Event System
  - Up to eight 16-bit Timer/Counters (TC), configurable as either
  - Two 24-bit and one 16-bit Timer/Counter for Control (TCC), with extended functions
  - Frequency Meter (The division reference clock is only available in the SAM C21N)
  - 32-bit Real Time Counter (RTC) with clock/calendar function
  - Watchdog Timer (WDT)
  - CRC-32 generator
  - Up to two Controller Area Network (CAN) interfaces in the SAM C21
  - Up to eight Serial Communication Interfaces (SERCOM), each configurable to operate as USART/I2C/SPI
  - One Configurable Custom Logic (CCL)
  - Up to Two 12-bit, 1 Msps Analog-to-Digital Converter (ADC) with up to 12 channels each (20 unique channels)
  - One 16-bit Sigma-Delta Analog-to-Digital Converter (SDADC) with up to 3 differential channels in the SAM C21
  - 10-bit, 350 ksps Digital-to-Analog Converter (DAC) in the SAM C21
  - Up to four Analog Comparators (AC) with Window Compare function
  - Integrated Temperature Sensor in the SAM C21
  - Peripheral Touch Controller (PTC)
  - 256-Channel capacitive touch

#### I/O管脚
  - 最多提供84个用户可编程I/O管脚

#### 汽车应用
  - AEC - Q100 Grade 1 (-40°C to 125°C)

#### 工作电压
  - 2.7V – 5.5V
  - -40°C to +125°C, DC to 48 MHz
  - -40°C to +85°C, DC to 64 MHz

#### 封装
  - 100-pin TQFP
  - 64-pin TQFP, VQFN
  - 56-pin WLCSP
  - 48-pin TQFP, VQFN
  - 32-pin TQFP, VQFN

#### 官方开发板信息
- [SAM C21 XPLAINED PRO]（https://www.microchip.com/en-us/development-tool/ATSAMC21-XPRO）