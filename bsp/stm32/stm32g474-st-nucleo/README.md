# STM32G431-Nucleo BSP Introduction

**English** | [中文](README_zh.md) 

## MCU: STM32G474RB @170MHz, 512KB FLASH,  128KB RAM

The STM32G474xB/xC/xE devices are based on the high-performance Arm® Cortex®-M4 32-bit RISC core. They operate at a frequency of up to 170 MHz. The Cortex-M4 core features a single-precision floating-point unit (FPU), which supports all the Arm single-precision data-processing instructions and all the data types. It also implements a full set of DSP (digital signal processing) instructions and a memory protection unit (MPU) which enhances the application’s security.
These devices embed high-speed memories (up to 512 Kbytes of Flash memory, and 128 Kbytes of SRAM), a flexible external memory controller (FSMC) for static memories (for devices with packages of 100 pins and more), a Quad-SPI Flash memory interface, and an extensive range of enhanced I/Os and peripherals connected to two APB buses, two AHB buses and a 32-bit multi-AHB bus matrix.
The devices also embed several protection mechanisms for embedded Flash memory and SRAM: readout protection, write protection, securable memory area and proprietary code readout protection.
The devices embed peripherals allowing mathematical/arithmetic function acceleration (CORDIC for trigonometric functions and FMAC unit for filter functions).
They offer five fast 12-bit ADCs (4 Msps), seven comparators, six operational amplifiers, seven DAC channels (3 external and 4 internal), an internal voltage reference buffer, a low-power RTC, two general-purpose 32-bit timers, three 16-bit PWM timers dedicated to motor control, seven general-purpose 16-bit timers, and one 16-bit low-power timer, and high resolution timer with 184 ps resolution.
They also feature standard and advanced communication interfaces such as:
\- Four I2Cs
\- Four SPIs multiplexed with two half duplex I2Ss
\- Three USARTs, two UARTs and one low-power UART.
\- Three FDCANs
\- One SAI
\- USB device
\- UCPD
The devices operate in the -40 to +85 °C (+105 °C junction) and -40 to +125 °C (+130 °C junction) temperature ranges from a 1.71 to 3.6 V power supply. A comprehensive set of power-saving modes allows the design of low-power applications.
Some independent power supplies are supported including an analog independent supply input for ADC, DAC, OPAMPs and comparators. A VBAT input allows backup of the RTC and the registers.
The STM32G474xB/xC/xE family offers 9 packages from 48-pin to 128-pin.

#### KEY FEATURES

- Core: Arm® 32-bit Cortex®-M4 CPU with FPU, Adaptive real-time accelerator (ART Accelerator) allowing 0-wait-state execution from Flash memory, frequency up to 170 MHz with 213 DMIPS, MPU, DSP instructions
- Operating conditions:
  - VDD, VDDA voltage range: 1.71 V to 3.6 V
- Mathematical hardware accelerators
  - CORDIC for trigonometric functions acceleration
  - FMAC: filter mathematical accelerator
- Memories
  - 512 Kbytes of Flash memory with ECC support, two banks read-while-write, proprietary code readout protection (PCROP), securable memory area, 1 Kbyte OTP
  - 96 Kbytes of SRAM, with hardware parity check implemented on the first 32 Kbytes
  - Routine booster: 32 Kbytes of SRAM on instruction and data bus, with hardware parity check (CCM SRAM)
  - External memory interface for static memories FSMC supporting SRAM, PSRAM, NOR and NAND memories
  - Quad-SPI memory interface
- Reset and supply management
  - Power-on/power-down reset (POR/PDR/BOR)
  - Programmable voltage detector (PVD)
  - Low-power modes: sleep, stop, standby and shutdown
  - VBAT supply for RTC and backup registers
- Clock management
  - 4 to 48 MHz crystal oscillator
  - 32 kHz oscillator with calibration
  - Internal 16 MHz RC with PLL option (± 1%)
  - Internal 32 kHz RC oscillator (± 5%)
- Up to 107 fast I/Os
  - All mappable on external interrupt vectors
  - Several I/Os with 5 V tolerant capability
- Interconnect matrix
- 16-channel DMA controller
- 5 x 12-bit ADCs 0.25 µs, up to 42 channels. Resolution up to 16-bit with hardware oversampling, 0 to 3.6 V conversion range
- 7 x 12-bit DAC channels
  - 3 x buffered external channels 1 MSPS
  - 4 x unbuffered internal channels 15 MSPS
- 7 x ultra-fast rail-to-rail analog comparators
- 6 x operational amplifiers that can be used in PGA mode, all terminals accessible
- Internal voltage reference buffer (VREFBUF) supporting three output voltages (2.048 V, 2.5 V, 2.9 V)
- 17 timers:
  - HRTIM (Hi-Resolution and complex waveform builder): 6 x16-bit counters, 184 ps resolution, 12 PWM
  - 2 x 32-bit timer and 2 x 16-bit timers with up to four IC/OC/PWM or pulse counter and quadrature (incremental) encoder input
  - 3 x 16-bit 8-channel advanced motor control timers, with up to 8 x PWM channels, dead time generation and emergency stop
  - 1 x 16-bit timer with 2 x IC/OCs, one OCN/PWM, dead time generation and emergency stop
  - 2 x 16-bit timers with IC/OC/OCN/PWM, dead time generation and emergency stop
  - 2 x watchdog timers (independent, window)
  - 1 x SysTick timer: 24-bit downcounter
  - 2 x 16-bit basic timers
  - 1 x low-power timer
- Calendar RTC with alarm, periodic wakeup from stop/standby
- Communication interfaces
  - 3 x FDCAN controller supporting flexible data rate
  - 4 x I2C Fast mode plus (1 Mbit/s) with 20 mA current sink, SMBus/PMBus, wakeup from stop
  - 5 x USART/UARTs (ISO 7816 interface, LIN, IrDA, modem control)
  - 1 x LPUART
  - 4 x SPIs, 4 to 16 programmable bit frames, 2 x with multiplexed half duplex I2S interface
  - 1 x SAI (serial audio interface)
  - USB 2.0 full-speed interface with LPM and BCD support
  - IRTIM (infrared interface)
  - USB Type-C™ /USB power delivery controller (UCPD)
- True random number generator (RNG)
- CRC calculation unit, 96-bit unique ID
- Development support: serial wire debug (SWD), JTAG, Embedded Trace Macrocell™



## Read more

|                          Documents                           |                         Description                          |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [STM32_Nucleo-64_BSP_Introduction](../docs/STM32_Nucleo-64_BSP_Introduction.md) | How to run RT-Thread on STM32 Nucleo-64 boards (**Must-Read**) |
| [STM32G474RE ST Official Website](https://www.st.com/en/microcontrollers-microprocessors/stm32g474re.html#documentation) |          STM32G474RB datasheet and other resources           |



## Maintained By

[mazhiyuan](https://github.com/cndabai), <mazhiyuan@rt-thread.com>