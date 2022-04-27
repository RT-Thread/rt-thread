# SAML10E16A BSP Introduction

[中文](README_zh.md) 
- MCU: ATSAML10E16A @32MHz, 64KB FLASH, 16KB RAM, 1.62V – 3.63V
- L10: Cortex-M23 + Hardware multiplier & divider + ultra low power(< 25 μA/MHz)
- Pin: E=32 pins, D=24pins
- Flash: 16=64KB, 15=32KB, 14=16KB(size=2^n)
- SRAM : 16KB(Flash 64KB), 8KB(Flash 32KB), 4KB(Flash 16KB)
- Datasheet: <https://www.microchip.com/en-us/product/ATSAML10E16A>

#### KEY FEATURES

#### Core
  - 32 MHz (2.64 CoreMark/MHz and up to 31 DMIPS) Arm® Cortex®-M23 with:
  - Single-cycle hardware multiplier
  - Hardware divider
  - Nested Vector Interrupt Controller (NVIC)
  - Memory Protection Unit (MPU)
  - Stack Limit Checking
  - TrustZone® for ARMv8-M (optional)

#### Memories
  - 16/32/64-KB Flash
  - 4/8/16-KB SRAM
  - 2-KB Data Flash Write-While-Read (WWR) section for non-volatile data storage
  - 256 bytes TrustRAM with physical protection features

#### System
  - Power-on Reset (POR) and programmable Brown-out Detection (BOD)
  - 8-channel Direct Memory Access Controller (DMAC)
  - 8-channel event system for Inter-peripheral Core-independent Operation
  - CRC-32 generator

#### Clock Management
  - Flexible clock distribution optimized for low power
  - 32.768 kHz crystal oscillator
  - 32.768 kHz ultra low-power internal RC oscillator
  - 0.4 to 32 MHz crystal oscillator
  - 16/12/8/4 MHz low-power internal RC oscillator
  - Ultra low-power digital Frequency-Locked Loop (DFLLULP)
  - 32-96 MHz fractional digital Phase-Locked Loop (FDPLL96M)
  - One frequency meter
  - Low-Power and Power Management
  - Active, Idle, Standby with partial or full SRAM retention and off sleep modes:
  - Active mode (< 25 μA/MHz)
  - Idle mode (< 10 μA/MHz) with 1.5 μs wake-up time
  - Standby with Full SRAM Retention (0.5 μA) with 5.3 μs wake-up time
  - Off mode (< 100 nA)
  - Static and dynamic power gating architecture
  - Sleepwalking peripherals
  - Two performance levels
  - Embedded Buck/LDO regulator with on-the-fly selection

#### Security
  - Up to four tamper pins for static and dynamic intrusion detections
  - Data Flash
  - Optimized for secure storage
  - Address and data scrambling with user-defined key (optional)
  - Rapid tamper erase on scrambling key and on one user-defined row
  - Silent access for data read noise reduction
  - TrustRAM
  - Address and data scrambling with user-defined key
  - Chip-level tamper detection on physical RAM to resist microprobing attacks
  - Rapid tamper erase on scrambling key and RAM data
  - Silent access for data read noise reduction
  - Data remanence prevention
  - Peripherals
  - One True Random Generator (TRNG)
  - AES-128, SHA-256, and GCM cryptography accelerators (optional)
  - Secure pin multiplexing to isolate on dedicated I/O pins a secured communication with external devices from the non-secure application (optional)
  - TrustZone for flexible hardware isolation of memories and peripherals (optional)
  - Up to six regions for the Flash
  - Up to two regions for the Data Flash
  - Up to two regions for the SRAM
  - Individual security attribution for each peripheral, I/O, external interrupt line, and Event System Channel
  - Secure Boot with SHA-based authentication (optional)
  - Up to three debug access levels
  - Up to three Chip Erase commands to erase part of or the entire embedded memories
  - Unique 128-bit serial number
  - SAM L11 Securely Key Provisioned (KPH) (optional)
  - Key Provisioning using Root of Trust flow
  - Security Software Framework using Kinibi-M™ Software Development Kit (SDK)

#### Advanced Analog and Touch
  - One 12-bit 1 Msps Analog-to-Digital Converter (ADC) with up to 10 channels
  - Two Analog Comparators (AC) with window compare function
  - One 10-bit 350 kSPS Digital-to-Analog Converter (DAC) with external and internal outputs
  - Three Operational Amplifiers (OPAMP)
  - One enhanced Peripheral Touch Controller (PTC):
  - Up to 20 self-capacitance channels
  - Up to 100 (10x10) mutual-capacitance channels
  - Low-power, high-sensitivity, environmentally robust capacitive touch buttons, sliders, and wheels
  - Hardware noise filtering and noise signal desynchronization for high conducted immunity
  - Driven Shield Plus for better noise immunity and moisture tolerance
  - Parallel Acquisition through Polarity control
  - Supports wake-up on touch from Standby Sleep mode

#### Communication Interfaces
  - Up to three Serial Communication Interfaces (SERCOM) that can operate as:
  - USART with full-duplex and single-wire half-duplex configuration
  - I2C up to 3.4 Mbit/s (High-Speed mode) on one instance and up to 1 Mbit/s (Fast-mode Plus) on the second instance
  - Serial Peripheral Interface (SPI)
  - ISO7816 on one instance (Available on 32-pin packages only)
  - RS-485 on one instance (Available on 32-pin packages only)
  - LIN Slave on one instance (Available on 32-pin packages only)
  - Timers/Output Compare/Input Capture
  - Three 16-bit Timers/Counters (TC), each configurable as:
  - One 16-bit TC with two compare/capture channels
  - One 8-bit TC with two compare/capture channels
  - One 32-bit TC with two compare/capture channels, by using two TCs
  - 32-bit Real-Time Counter (RTC) with clock/calendar functions
  - Watchdog Timer (WDT) with Window mode
  - Input/Output (I/O)
  - Up to 25 programmable I/O lines
  - Eight external interrupts (EIC)
  - One non-maskable interrupt (NMI)
  - One Configurable Custom Logic (CCL) that supports:
  - Combinatorial logic functions, such as AND, NAND, OR, and NOR
  - Sequential logic functions, such as Flip-Flop and Latches

#### Qualification
  - AEC-Q100 Grade 1 (-40°C to 125°C)
  - Class-B safety library, IEC 60730 (future)

#### Packages
  - 24-pin VQFN(4*4mm/17 I/O pins)
  - 32-pin VQFN(5*5mm/25 I/O pins)
  - 32-pin TQFP(7*7mm/17 I/O pins)
  - 32-pin WLCSP(2.79*2.79mm/25 I/O pins)

#### Board info
- [SAM L10 XPLAINED PRO](https://ww1.microchip.com/downloads/en/Appnotes/Getting-Started-with-SAM%20L10L11-Xplained-Pro-DS00002722A.pdf)
