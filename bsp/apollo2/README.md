Apollo2 MCU是基于Ambiq Micro的Apollo MCU产品系列的第二代控制器。

Ambiq使用专利亚阈值功率优化技术（Subthreshold Power Optimized Technology， SPOT）平台来实现惊人的功耗降低，其功耗通常比性能相近的其它MCU产品降低5至10倍。

Apollo2 MCU采用32位ARM Cortex-M4F微控制器，集成了高达1 MB的闪存和256 KB的RAM，以适应无线电和传感器开销，同时仍留有足够的应用代码空间。该微控制器还包括串行主机和UART端口，用于与无线电和传感器通信，包括加速度计，陀螺仪和磁力计。

```
Features
Ultra-low supply current
    10 μA/MHz executing from flash at 3.3 V
    10 μA/MHz executing from RAM at 3.3 V

High-performance ARM Cortex-M4 Processor
    Up to 48 MHz clock frequency
    Floating point unit
    Memory protection unit
    Wake-up interrupt controller with 32 interrupts
    
Ultra-low power memory:
    Up to 1 MB of flash memory for code/data
    Up to 256 KB of low leakage RAM for code/data
    16kB 1 or 2-way Associative Cache

Ultra-low power interface for off-chip sensors:
    14 bit, 15-channel, up to 1.2 MS/s ADC
    Voltage Comparator
    Temperature sensor with +/-2C accuracy

Flexible serial peripherals:
    6x I2C/SPI master for communication with sensors,?radios, and other peripherals
    1x I2C/SPI slave for host communications
    2x UART for communication with peripherals and?legacy devices
    PDM for mono and stereo audio microphone

Rich set of clock sources:
    32.768 kHz XTAL oscillator
    Low frequency RC oscillator – 1.024 kHz
    High frequency RC oscillator – 48 MHz
    RTC based on Ambiq’s AM08X5/18X5 families

Wide operating range: 1.8-3.6 V, –40 to 85°C

Compact package options:
    2.5 x 2.5 mm 49-pin CSP with 34 GPIO
    4.5 x 4.5 mm 64-pin BGA with 50 GPIO

Board info
    Apollo2 Evaluation Board（http://ambiqmicro.com/apollo-ultra-low-power-mcu/apollo2-mcu-20170703/）
```
