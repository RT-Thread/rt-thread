## Introduction

[中文页](README_ZH.md) | English Page

The **sdk-bsp-stm32h7r-realthread-artpi2** is a support package developed by the RT-Thread team for the ART-Pi development board. It also serves as a software SDK for users to develop their applications more easily and conveniently.

The **ART-Pi2** is an open-source hardware platform designed by the RT-Thread team specifically for embedded software engineers and open-source makers, offering extensive expandability for DIY projects.

<img src="figures/board_large.png" alt="image-20201009181905422" style="zoom:50%;" />

## Directory Structure

```
$ sdk-bsp-stm32h7r-realthread-artpi2
├── README.md
├── RealThread_STM32H7R-ART-Pi2.yaml
├── debug
├── documents
│ ├── coding_style_cn.md
│ ├── RT-Thread Programming Guide.pdf
│ ├── board
│ └── figures
├── libraries
│ ├── STM32H7RSxx_HAL_Driver
│ ├── drivers
│ └── touchgfx_lib
├── projects
│ ├── art_pi_blink_led
│ ├── art_pi_bootloader
│ ├── art_pi2_lvgl_demo
│ ├── art_pi2_touchgfx
│ ├── art_pi2_sdcard
│ └── art_pi_wifi
├── rt-thread
└── tools
```

- **RealThread_STMH7R-ART-Pi.yaml**: Describes the hardware information of ART-Pi.
- **documents**: Contains schematics, documents, images, and datasheets.
- **libraries**: Includes STM32H7 firmware libraries, general peripheral drivers, and TouchGFX libraries.
- **projects**: Example project folders, including factory programs, gateway programs, etc.
- **rt-thread**: RT-Thread source code.
- **tools**: Contains Wi-Fi firmware, MDK download algorithms, etc.

## Usage Instructions

sdk-bsp-stm32h7r-realthread-artpi supports MDK development and RT-Thread Studio development.

### STM32CubeProg Software

Download the latest version of the software: [STM32CubeProg - STMicroelectronics](https://www.st.com.cn/zh/development-tools/stm32cubeprog.html#get-software).

### RT-Thread Studio Development

1. Download Studio version v2.2.9: [Download Link](https://download-redirect.rt-thread.org/download/studio/RT-Thread_Studio_2.2.9-setup-x86_64_202412161335.exe).
2. Copy the [org.rt-thread.studio.common.core_1.0.128.jar](tools/studio/) file and replace the file with the same name in the `plugins` folder of the installed Studio directory.
    (This step will be fixed in the next Studio version.)
3. Open the RT-Thread Studio package manager and install the ART-Pi2 SDK resource package.
    <img src="figures/sdk_manager.png" alt="sdk_manager" style="zoom: 67%;" />
4. After installation, select `File → New → RT-Thread Project → Based on Development Board` and choose the ART-Pi2 development board.
    <img src="figures/create_proj.png" alt="sdk_manager" style="zoom: 67%;" />

### MDK Development

1. Install the latest version of MDK: [MDK-ARM Version 5.41 Product Update](https://www.keil.com/update/sw/mdk/5.41).
2. Install the STM32H7R-MDK chip pack: [Keil.STM32H7RSxx_DFP.1.0.0.pack](./tools/mdk_pack/Keil.STM32H7RSxx_DFP.1.0.0.pack).
3. Copy the `tools\download_algorithm\flm\ART-Pi2_winbond_64MB.FLM` download algorithm to the `MDK Installation Directory\Core\ARM\Flash` folder.

To avoid the SDK becoming bloated due to continuous updates, where each `projects` folder creates a copy of the `rt-thread` and `libraries` folders, these common folders have been extracted separately. This may cause compilation errors in MDK projects due to missing files from these folders. There are two methods to resolve this issue:

**Method 1:**

1. Double-click the `mklinks.bat` file in the `project` directory, such as the one in `sdk-bsp-stm32h7r-realthread-artpi2\projects\art_pi2_blink_led`.
2. Check if the `rt-thread` and `libraries` folder icons appear in the `sdk-bsp-stm32h7r-realthread-artpi2\projects\art_pi2_blink_led` directory.
3. Use the [ENV-2.0](https://club.rt-thread.org/ask/article/af8952fcf0ca464b.html) tool to execute `scons --target=mdk5` to update the MDK5 project files.

**Method 2:**

1. Download the SDK from the [ART-Pi SDK Repository](https://github.com/RT-Thread-Studio/sdk-bsp-stm32h7r-realthread-artpi2).
2. Navigate to the project directory, e.g., `sdk-bsp-stm32h7r-realthread-artpi2\projects\art_pi2_blink_led`.
3. Use the [ENV-2.0](https://club.rt-thread.org/ask/article/af8952fcf0ca464b.html) tool to execute the `mklink` command to create symbolic links for the `rt-thread` and `libraries` folders.

```shell
E:\project\sdk-bsp-stm32h7r-realthread-artpi2\projects\art_pi2_blink_led>mklink /D rt-thread ....\rt-thread
symbolic link created for rt-thread <<===>> ....\rt-thread

E:\project\sdk-bsp-stm32h7r-realthread-artpi2\projects>mklink /D libraries ....\libraries
symbolic link created for libraries <<===>> ....\libraries

E:\project\sdk-bsp-stm32h7r-realthread-artpi2\projects>
```

Use the [ENV-2.0](https://club.rt-thread.org/ask/article/af8952fcf0ca464b.html) tool to execute `scons --target=mdk5` to update the MDK5 project files.

## ART-Pi Communication Platform

ART-Pi is an open-source creative hardware platform. We look forward to more enthusiasts discovering its potential. If you have any ideas or suggestions during use, please contact us through the following channels:

- RT-Thread [Community Forum](https://club.rt-thread.org).
- ART-Pi Official QQ Group (1016035998).

![qq_group](figures/qq_group.png)

## Contributing Code

If you are interested in ART-Pi and have some fun projects you'd like to share with everyone, we welcome your code contributions. You can refer to the [ART-Pi Code Contribution Guide](https://github.com/RT-Thread-Studio/sdk-bsp-stm32h7r-realthread-artpi/blob/master/documents/UM5004-RT-Thread%20ART-Pi%20%E4%BB%A3%E7%A0%81%E8%B4%A1%E7%8C%AE%E6%89%8B%E5%86%8C.md).

## Participating in Projects

Here are some ways you can participate:

- Maintain existing SDK repository code.
- Submit project code that can be merged into the SDK repository.
- Submit showcase projects whose code cannot be merged into the SDK repository but are open-sourced elsewhere.
- Submit expansion boards.
- Write column articles.