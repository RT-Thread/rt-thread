# HPMicro 板级支持包 (BSP) 介绍

[English](README.md) |

## 简介

本文档提供了 RT-Thread 仓库中可用的 HPMicro BSP（板级支持包）的概述。每个 BSP 都针对特定的 HPMicro 开发板进行了定制，提供必要的驱动程序和配置，以便在基于 RISC-V 的 HPMicro 微控制器上无缝运行 RT-Thread。

本文档包含以下部分：

- HPMicro BSP 概述
- 可用的 BSP
- 快速开始指南
- 通用开发环境设置
- 参考资料

通过阅读快速开始指南部分，开发者可以快速上手任何 HPMicro BSP 并在开发板上运行 RT-Thread。每个单独的 BSP 都包含特定开发板功能和高级用法的详细文档。

## 可用的 BSP

以下是当前支持的 HPMicro BSP 的完整列表：

| BSP 名称 | 支持的开发板 | MCU | 描述 |
|----------|-------------|-----|------|
| hpm5300evk | HPM5300EVK | HPM5361 | HPM5300 系列开发板 |
| hpm5301evklite | HPM5301EVKLITE | HPM5301 | HPM5301精简版开发板 |
| hpm5e00evk | HPM5E00EVK | HPM5E31 | HPM5E00 系列开发板 |
| hpm6200evk | HPM6200EVK | HPM6200 | HPM6200 系列开发板 |
| hpm6300evk | HPM6300EVK | HPM6360 | HPM6300 系列开发板，支持以太网 |
| hpm6750evk | HPM6750EVK | HPM6750 | HPM6750 系列开发板，双核 RISC-V |
| hpm6750evk2 | HPM6750EVK2 | HPM6750 | HPM6750 系列第二代开发板 |
| hpm6750evkmini | HPM6750EVKMINI | HPM6750 | HPM6750 系列迷你开发板 |
| hpm6800evk | HPM6800EVK | HPM6800 | HPM6800 系列开发板 |
| hpm6e00evk | HPM6E00EVK | HPM6E00 | HPM6E00 系列开发板 |
| hpm6p00evk | HPM6P00EVK | HPM6P00 | HPM6P00 系列开发板 |

## 快速开始指南

### 前提条件

在开始使用任何 HPMicro BSP 之前，您需要准备以下开发环境：

#### 1. RT-Thread ENV
- 下载并安装 [RT-Thread ENV](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)

#### 2. RISC-V 工具链
- 下载 RISC-V 工具链：[riscv32-gnu-toolchain](https://github.com/helloeagleyang/riscv32-gnu-toolchain-win/archive/2022.04.12.zip)
- 解压到指定目录，例如：`C:\DevTools\riscv32-gnu-toolchain`
- 设置环境变量 `RTT_RISCV_TOOLCHAIN` 为 `<TOOLCHAIN_DIR>\bin`
  - 例如：`C:\DevTools\riscv32-gnu-toolchain\bin`

#### 3. HPMicro 专用 OpenOCD
- 下载 OpenOCD：[rtt-debugger-support-package](https://github.com/hpmicro/rtt-debugger-support-package/archive/v0.4.0.zip)
- 解压到指定目录，例如：`C:\DevTools\openocd-hpmicro`
- 设置环境变量 `OPENOCD_HPMICRO` 为 `<OPENOCD_HPMICRO_DIR>\bin`
  - 例如：`C:\DevTools\openocd-hpmicro\bin`

### 使用特定 BSP 开始

1. **导航到所需的 BSP 目录**：
   ```bash
   cd rt-thread/bsp/hpmicro/<bsp_name>
   ```

2. **配置项目**：
   - 打开 RT-Thread ENV 命令行
   - 切换到 BSP 目录
   - 运行 `menuconfig` 来配置项目

3. **构建项目**：
   ```bash
   scons -jN  # N 等于 CPU 核心数
   ```

4. **硬件连接**：
   - 将 BOOT 引脚切换到 2'b00
   - 通过 TYPE-C 线缆将 `PWR_DEBUG` 端口连接到 PC

5. **下载和调试**：
   - 使用提供的 OpenOCD 脚本进行下载和调试
   - 参考各个 BSP 的 README 文件获取具体命令

### 运行结果

项目成功下载后，系统会自动运行。开发板上的 LED 会周期性闪烁。

将开发板的串口连接到 PC，通过串口终端工具（115200-8-1-N）与其通信。重置开发板后，将观察到 RT-Thread 的启动信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     5.2.2 build Aug 16 2025 18:18:18
 2006 - 2025 Copyright by RT-Thread team
msh >
```

## 通用外设支持

大多数 HPMicro BSP 支持以下外设：

| **板载外设** | **支持** | **备注** |
| ------------ | -------- | -------- |
| USB          | √        |          |
| QSPI Flash   | √        |          |
| GPIO         | √        |          |
| SPI          | √        |          |
| I2C          | √        |          |
| UART         | √        |          |
| PWM          | √        |          |
| RTC          | √        |          |
| 板载调试器   | √        | ft2232   |

根据特定开发板，可能支持其他外设：
- **以太网**：在如下开发板上可用
  - HPM6300EVK
  - HPM6750EVK
  - HPM6750EVK2
  - HPM6750EVKMINI + ART-Pi Industry IO 扩展板
  - HPM6800EVK
  - HPM6E00EVK
  - HPM6P00EVK
  - HPM5E00EVK
- **CAN**：HPM5300EVK、HPM6750系列开发板，HPM6300EVK，HPM6800EVK, HPM6E00EVK, HPM6P00EVK 和HPM5E00EVK
- **SDIO**：HPM6300EVK、HPM6750EVK 系列可用
- **显示/音频**：HPM6750EVK 系列可用

## 开发环境设置

### 使用命令行工具

1. 按照前提条件部分所述设置环境变量
2. 使用 `scons` 进行构建
3. 使用 OpenOCD 和 GDB 进行调试

## 各个 BSP 文档

每个 BSP 都包含自己的详细 README 文件，内容包括：
- 特定开发板的硬件信息
- 外设配置详情
- 具体的下载和调试命令
- 高级功能和示例

请参考各个 BSP 目录获取详细文档：
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

## 故障排除

### 常见问题

1. **找不到工具链**：确保 `RTT_RISCV_TOOLCHAIN` 环境变量设置正确
2. **OpenOCD 连接失败**：检查 USB 连接和驱动程序安装
3. **构建错误**：验证所有依赖项已安装且环境变量已设置
4. **串口通信问题**：检查波特率（115200）和 COM 端口设置

### 获取帮助

- 查看各个 BSP 的 README 文件了解特定开发板的问题
- 访问 [RT-Thread 社区](https://club.rt-thread.org/)
- 参考 [RT-Thread 文档](https://www.rt-thread.org/document/site/)

## 参考资料

- [RT-Thread 文档中心](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/README)
- [RT-Thread ENV](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md)
- [HPMicro 官方网站](https://www.hpmicro.com/)
- [HPMicro SDK 文档](https://hpmicro.github.io/)
- [RISC-V 工具链](https://github.com/riscv/riscv-gnu-toolchain)

## 贡献

欢迎对增强现有 BSP 或添加新 BSP 做出贡献。请遵循 RT-Thread 贡献指南，确保您的 BSP 符合项目标准。

为 HPMicro BSP 做出贡献：
1. Fork `RT-Thread` 仓库
2. 创建功能分支
3. 按照现有代码风格进行更改
4. 彻底测试您的更改
5. 提交带有清晰描述的拉取请求

## 许可证

此 BSP 在 [RT-Thread 许可证](https://github.com/RT-Thread/rt-thread/blob/master/LICENSE) 下发布。
