# Infineon XMC7100D-F144K4160AA 说明

## 简介

本文档为 `RT-Thread` 为 ` XMC7100D-F144K4160AA`开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 `RT-Thread` 驱动更多板载资源。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注** |
| :----------: | :----------: | :------: |
|  USB 转串口  |     支持     |  UART4   |
|     GPIO     |     支持     |    —     |
|     UART     |     支持     | UART2,UART4  |
|     I2C     |     支持     | I2C1  |

## 快速上手

本 BSP 是以 `GCC` 和 `Jlink` 为开发环境（编译器：GCC），接下来介绍如何将系统运行起来。

### 使用 Vscode 开发

#### 硬件连接

将开发板的swd接口与jlink相连,注意jlink版本建议V8.18以上

#### 编译下载

1、下载软件包：在ENV环境下输入`pkgs --update`命令，将所需要的HAL库软件包下载下来，文件会存放在`Packages`目录下。

2、编译工程：在ENV环境下输入`SCons -j4`或者 `SCons -j16` 命令，j后面的数字取决于cpu线程数，然后ENV会自动编译生成可烧写elf文件

3、下载此工程：

Vscode下载拓展Cortex-Debug，然后在.vscode下新建launch.json文件,并添加以下内容

```

{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Launch XMC7100D CM7 (JLink)",
            "type": "cortex-debug",
            "request": "launch",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceRoot}/rt-thread.elf",
            "servertype": "jlink",
            "device": "XMC7100-4160_CM7_0_tm",
            "interface": "swd",
            "serialNumber": "",
            "preLaunchCommands": [
                // Program via the hex file to get complete coverage
                "exec-file rt-thread.hex"
            ],
            "overrideRestartCommands": [
                "starti"
            ],
            // svdFile is optional, it can be very large.
            "svdFile": "${workspaceRoot}/libs/cat1c4m.svd",
            "breakAfterReset": true,
            "runToEntryPoint": "main",    // Specifies application entry point name where program will halt
            "showDevDebugOutput": "none",
            "presentation": {
                "hidden": false,
                "group": "CM7"
            },
            "serverpath": "C:/Program Files/SEGGER/JLink_V820/JLinkGDBServerCL.exe"
        },
        // When using 'attach', make sure your program is running on the board and that your
        // executable matches the image in the chip exactly, or else strange things can happen
        // with breakpoints, variables, etc.
        {
            "name": "Attach XMC7100D CM7 (JLink)",
            "type": "cortex-debug",
            "request": "attach",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceRoot}/rt-thread.elf",
            "servertype": "jlink",
            "device": "XMC7100-4160_CM7_0_tm",
            "interface": "swd",
            "serialNumber": "",
            "overrideRestartCommands": [
                "starti"
            ],
            // svdFile is optional, it can be very large.
            "svdFile": "${workspaceRoot}/libs/cat1c4m.svd",
            "breakAfterReset": true,
            "runToEntryPoint": "main",    // Specifies application entry point name for restart/reset
            "showDevDebugOutput": "none",
            "presentation": {
                "hidden": false,
                "group": "CM7"
            },
            "serverpath": "C:/Program Files/SEGGER/JLink_V820/JLinkGDBServerCL.exe"
        }
    ]
}

```

随后点击运行按钮即可自动下载程序到开发板

## 运行结果

下载程序成功之后，点击全速运行。然后打开终端工具串口助手，选择波特率为 115200。复位设备后，LED 将会闪烁，而且在终端上可以看到 `RT-Thread` 的输出信息：

注：推荐使用串口调试助手如：`MobaXterm`

```c
 \ | /
- RT -     Thread Operating System
 / | \     5.2.1 build Apr 21 2025 20:49:36
 2006 - 2024 Copyright by RT-Thread team
msh >
```

## 联系人

维护人:

- [LZerro](https://github.com/LZerro)
- [Hydevcode](https://github.com/hydevcode)