# ESP32-C3 BSP Introduction

[中文](README_ZH.md) | English

This document records the execution instruction of the BSP (board support package) for the [ESP32-C3](http://luatos.com/t/esp32c3) development board.

The document is covered in two parts:

- Board Resources Introduction
- Quickly Get Started

## Resources Introduction

We tested 2 development boards, it all works, but due to the different LED pins of the two development boards, so we'll need to select the corresponding development board in the menuconfig. 

- [LUATOS_ESP32C3](https://wiki.luatos.com/chips/esp32c3/board.html)

![LUATOS_ESP32C3](images/luatos_esp32c3.png)

- [HX-DK-商](https://docs.wireless-tech.cn/doc/7/)

![hongxu](images/hx_shang.png)

The mainly-used resources of LUATOS_ESP32C3 are shown as follows:

- MCU: [esp32-c3](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)，Main Frequency 160MHz, 407.22 CoreMark; 2.55 CoreMark/MHz
- Built-in Chip: 384KB ROM, 400KB SRAM
- Peripherals
  - Red LED: 2, LED: D4 (IO12), D5（IO13）
  - Button: 2, K1（BOOT） K2(RST)
  - SPI FLASH: 4M
- Common-used interfaces: USB, UART, etc.

### For more details about this board, please refer to [Here](https://wiki.luatos.com/chips/esp32c3/board.html).

## **Peripheral Condition**

Each peripheral supporting condition for this BSP is as follows:

| **On-board Peripherals** | ****Support**** | ****Remark****                                               |
| ------------------------ | --------------- | ------------------------------------------------------------ |
| GPIO                     | Support         |                                                              |
| UART                     | Support         | Using LUATOS_ESP32C3 development board requires connecting serial port to USB chip UART0_TX and UART0_RX (such as CP2102) |
| JTAG debug               | Support         | ESP32C3 usb-linked development boards can be debugged        |

## Environment construction and compilation

1. Download the RISC-V toolchain:

     ```sh
     wget https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz
     tar xf riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz
     ```

2. Configure the path of the toolchain:

     Add the local path of the `RISC-V` toolchain to the `EXEC_PATH` variable in the `rtconfig.py` file, or specify the path by setting the `RTT_EXEC_PATH` environment variable, for example:

     ```sh
     export RTT_EXEC_PATH=/opt/riscv32-esp-elf/bin
     ```

3. Compile

     Install esptool to convert ELF files to binary flash files:

     ```sh
     pip install esptool
     ```

     Execute the following command on the Linux platform to configure:

     ```
     scons --menuconfig
     ```

     It will automatically download env-related scripts to the `~/.env` directory, and then execute:

     ```sh
     source ~/.env/env.sh

     cd bsp/ESP32_C3/
     pkgs --update
     ```

     It will automatically download `RT-Thread-packages/esp-idf` and `RT-Thread-packages/FreeRTOS-Wrapper`, after updating the software packages, execute `scons` to compile the board support package.

     If the compilation is successful, `rtthread.elf`, `rtthread.bin` files will be generated.

## Download and program

1. Programming tool download

     The current bsp test uses the `flash_download_tool_3.9.4` tool to program without errors.

     Programming tool download address: [https://www.espressif.com.cn/sites/default/files/tools/flash_download_tool_3.9.4_0.zip](https://www.espressif.com.cn/sites/default/files/tools/flash_download_tool_3.9.4_0.zip)

2. Programming tool configuration

     Chip model selection `ESP32-C3`

     Configure the binary file and offset address as follows:

     | binary file | offset address |
     | ------------------- | -------- |
     | bootloader.bin | 0x0 |
     | partition-table.bin | 0x8000 |
     | rtthread.bin | 0x10000 |

     Among them, `bootloader.bin` and `partition-table.bin` can be found in the `bsp/ESP32_C3/builtin_imgs` folder. After the configuration is completed, the screenshot is as follows, and then click `START` to download.

     ![flash_download_tools](images/flash_download_tools.png)

## Notes

- The basic functions are now supported, but it needs more, welcome any contributions and feedback. 


Maintainer: 

- [supperthomas](https://github.com/supperthomas) email address: [78900636@qq.com](mailto:78900636@qq.com)
-  [tangzz98](https://github.com/tangzz98) email address: [tangz98@outlook.com](tangz98@outlook.com)

Special thanks to [chenyingchun0312](https://github.com/chenyingchun0312) for providing support on the RISC-V part working.

