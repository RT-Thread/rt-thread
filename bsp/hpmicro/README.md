# HPMicro Board Support Package (BSP) Introduction

[中文页](README_zh.md) |

## Introduction

This document provides an overview of the HPMicro BSPs (Board Support Package) available in the RT-Thread repository. Each BSP is tailored for specific HPMicro development boards, offering necessary drivers and configurations to run RT-Thread seamlessly on RISC-V based HPMicro microcontrollers.

The document consists of the following parts:

- HPMicro BSP Overview
- Available BSPs
- Quick Start Guide
- Common Development Environment Setup
- References

By reading the Quick Start Guide section, developers can quickly get their hands on any HPMicro BSP and run RT-Thread on the board. Each individual BSP contains detailed documentation for specific board features and advanced usage.

## Available BSPs

Below is a comprehensive list of HPMicro BSPs currently supported:

| BSP Name | Supported Board | MCU | Description |
|----------|-----------------|-----|-------------|
| hpm5300evk | HPM5300EVK | HPM5361 | Development board for HPM5300 series |
| hpm5301evklite | HPM5301EVKLITE | HPM5301 | Lite version development board for HPM5301 |
| hpm5e00evk | HPM5E00EVK | HPM5E31 | Development board for HPM5E00 series |
| hpm6200evk | HPM6200EVK | HPM6200 | Development board for HPM6200 series |
| hpm6300evk | HPM6300EVK | HPM6360 | Development board for HPM6300 series with Ethernet support |
| hpm6750evk | HPM6750EVK | HPM6750 | Development board for HPM6750 series with dual-core RISC-V |
| hpm6750evk2 | HPM6750EVK2 | HPM6750 | Second generation development board for HPM6750 series |
| hpm6750evkmini | HPM6750EVKMINI | HPM6750 | Mini development board for HPM6750 series |
| hpm6800evk | HPM6800EVK | HPM6800 | Development board for HPM6800 series |
| hpm6e00evk | HPM6E00EVK | HPM6E00 | Development board for HPM6E00 series |
| hpm6p00evk | HPM6P00EVK | HPM6P00 | Development board for HPM6P00 series |

## Quick Start Guide

### Prerequisites

Before getting started with any HPMicro BSP, you need to prepare the following development environment:

#### 1. RT-Thread ENV
- Download and install [RT-Thread ENV](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)

#### 2. RISC-V Toolchain
- Download the RISC-V toolchain: [riscv32-gnu-toolchain](https://github.com/helloeagleyang/riscv32-gnu-toolchain-win/archive/2022.04.12.zip)
- Extract it to a specified directory, for example: `C:\DevTools\riscv32-gnu-toolchain`
- Set environment variable `RTT_RISCV_TOOLCHAIN` to `<TOOLCHAIN_DIR>\bin`
  - For example: `C:\DevTools\riscv32-gnu-toolchain\bin`

#### 3. OpenOCD for HPMicro
- Download OpenOCD: [rtt-debugger-support-package](https://github.com/hpmicro/rtt-debugger-support-package/archive/v0.4.0.zip)
- Extract it to a specified directory, for example: `C:\DevTools\openocd-hpmicro`
- Set environment variable `OPENOCD_HPMICRO` to `<OPENOCD_HPMICRO_DIR>\bin`
  - For example: `C:\DevTools\openocd-hpmicro\bin`

### Getting Started with a Specific BSP

1. **Navigate to the desired BSP directory**:
   ```bash
   cd rt-thread/bsp/hpmicro/<bsp_name>
   ```

2. **Configure the project**:
   - Open RT-Thread ENV command-line
   - Change directory to the BSP directory
   - Run `menuconfig` to configure the project

3. **Build the project**:
   ```bash
   scons -jN  # N equals to the number of CPU cores
   ```

4. **Hardware Connection**:
   - Switch BOOT pin to 2'b00
   - Connect the `PWR_DEBUG` port to PC via TYPE-C cable

5. **Download and Debug**:
   - Use the provided OpenOCD scripts for downloading and debugging
   - Refer to individual BSP README files for specific commands

### Running Results

Once the project is successfully downloaded, the system runs automatically. The LED on the board will flash periodically.

Connect the serial port of the board to the PC, communicate with it via a serial terminal tool (115200-8-1-N). Reset the board and the startup information of RT-Thread will be observed:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.2.2 build Aug 16 2025 18:18:18
 2006 - 2025 Copyright by RT-Thread team
msh >
```

## Common Peripheral Support

Most HPMicro BSPs support the following peripherals:

| **On-board Peripherals** | **Support** | **Note** |
| ------------------------ | ----------- | -------- |
| USB                      | √           |          |
| QSPI Flash               | √           |          |
| GPIO                     | √           |          |
| SPI                      | √           |          |
| I2C                      | √           |          |
| UART                     | √           |          |
| PWM                      | √           |          |
| RTC                      | √           |          |
| On-Board Debugger        | √           | ft2232   |

Additional peripherals may be supported depending on the specific board:
- **Ethernet**: Available on 
  - HPM6300EVK
  - HPM6750EVK
  - HPM6750EVK2
  - HPM6750EVKMINI + ART-Pi Industry IO extension
  - HPM6800EVK
  - HPM6E00EVK
  - HPM6P00EVK
  - HPM5E00EVK
- **CAN**: Available on HPM6750 series Development Boards, HPM5300EVK, HPM6800EVK, HPM6E00EVK, HPM6P00EVK and HPM5E00EVK
- **SDIO**: Available on HPM6300EVK, HPM6750EVKMINI, HPM6750EVK, HPM6750EVK2 and HPM6800EVK
- **Display/Audio**: Available on HPM6750EVK, HPM6800EVK, HPM6E00EVK，HPM6P00EVK

## Development Environment Setup


### Using Command Line Tools

1. Set up the environment variables as described in the Prerequisites section
2. Use `scons` for building
3. Use OpenOCD and GDB for debugging or use the Ozone + JLink for debugging

## Individual BSP Documentation

Each BSP contains its own detailed README file with:
- Board-specific hardware information
- Peripheral configuration details
- Specific download and debug commands
- Advanced features and examples

Please refer to the individual BSP directories for detailed documentation:
- `hpm5300evk/README.md`
- `hpm5301evklite/README.md`
- `hpm5e00evk/README.md`
- `hpm6200evk/README.md`
- `hpm6300evk/README.md`
- `hpm6750evk/README.md`
- `hpm6750evk2/README.md`
- `hpm6750evkmini/README.md`
- `hpm6800evk/README.md`
- `hpm6e00evk/README.md`
- `hpm6p00evk/README.md`

## Troubleshooting

### Common Issues

1. **Toolchain not found**: Ensure `RTT_RISCV_TOOLCHAIN` environment variable is set correctly
2. **OpenOCD connection failed**: Check USB connection and driver installation
3. **Build errors**: Verify all dependencies are installed and environment variables are set
4. **Serial communication issues**: Check baud rate (115200) and COM port settings

### Getting Help

- Check the individual BSP README files for board-specific issues
- Visit [RT-Thread Community](https://club.rt-thread.org/)
- Refer to [RT-Thread Documentation](https://www.rt-thread.org/document/site/)

## References

- [RT-Thread Document Center](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/README)
- [RT-Thread ENV](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md)
- [HPMicro Official Website](https://www.hpmicro.com/)
- [HPMicro SDK Documentation](https://hpmicro.github.io/)
- [RISC-V Toolchain](https://github.com/riscv/riscv-gnu-toolchain)

## Contributing

Contributions to enhance existing BSPs or add new ones are welcome. Please follow the RT-Thread contribution guidelines and ensure that your BSP adheres to the project's standards.

For contributing to HPMicro BSPs:
1. Fork the `RT-Thread` repository
2. Create a feature branch
3. Make your changes following the existing code style
4. Test your changes thoroughly
5. Submit a pull request with a clear description

## License

This BSP is released under the [RT-Thread license](https://github.com/RT-Thread/rt-thread/blob/master/LICENSE).