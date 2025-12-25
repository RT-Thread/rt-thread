# RT-Thread VirtIO 驱动

[English](README.md) | 中文

## 概述

VirtIO 驱动为 RT-Thread 提供虚拟 I/O 设备支持，主要用于 QEMU 等虚拟化环境。

## 支持的版本

驱动现已支持传统版和现代版 VirtIO 规范：

- **传统版 VirtIO (v0.95)**：版本字段为 0x1，兼容较旧的 QEMU 版本
- **现代版 VirtIO (v1.0+)**：版本字段为 0x2，支持 VirtIO 1.0、1.1 和 1.2 规范

## 支持的设备

- **VirtIO 块设备 (virtio-blk)**：虚拟块设备
- **VirtIO 网络设备 (virtio-net)**：虚拟网络接口
- **VirtIO 控制台 (virtio-console)**：虚拟串口控制台
- **VirtIO GPU (virtio-gpu)**：虚拟图形设备
- **VirtIO 输入设备 (virtio-input)**：虚拟输入设备（键盘、鼠标、触摸板）

## 配置

使用 `menuconfig` 配置 VirtIO 支持：

```
RT-Thread Components → Device Drivers → Using VirtIO device drivers
```

### 版本选择

在传统版和现代版 VirtIO 之间选择：

```
RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
```

选项：
- **VirtIO Legacy (v0.95)**：与较旧的 QEMU 版本兼容（默认）
- **VirtIO Modern (v1.0+)**：用于较新的 QEMU 版本（2.4+），具有增强功能

### 设备选择

启用各个 VirtIO 设备：

- `RT_USING_VIRTIO_BLK`：VirtIO 块设备支持
- `RT_USING_VIRTIO_NET`：VirtIO 网络设备支持
- `RT_USING_VIRTIO_CONSOLE`：VirtIO 控制台支持
- `RT_USING_VIRTIO_GPU`：VirtIO GPU 支持
- `RT_USING_VIRTIO_INPUT`：VirtIO 输入设备支持

## 主要区别

### 传统版 VirtIO (v0.95)
- 32 位特性协商
- 单一队列描述符区域
- 简单状态标志
- 客户机页面大小配置

### 现代版 VirtIO (v1.0+)
- 64 位特性协商（支持更多特性）
- 独立的描述符/驱动/设备队列区域
- 增强的状态流程，带 FEATURES_OK 检查
- 更好的内存对齐和原子性保证

## 迁移指南

### 从传统版迁移到现代版

1. 更新 QEMU 命令行以使用现代版 VirtIO 设备（最新的 QEMU 版本默认使用现代版）
2. 在 menuconfig 中更改 VirtIO 版本：
   ```
   RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
   → 选择 "VirtIO Modern (v1.0+)"
   ```
3. 重新构建应用程序
4. 驱动将自动与设备协商 VERSION_1 特性

### 向后兼容性

驱动从 MMIO 配置中自动检测设备版本，并相应调整其行为。传统版（版本 0x1）和现代版（版本 0x2）设备在同一构建中都受支持。

## BSP 支持

以下 BSP 已更新以支持传统版和现代版 VirtIO：

- `qemu-virt64-riscv`：QEMU RISC-V 64 位
- `qemu-virt64-aarch64`：QEMU ARM64 (AArch64)

## 规范参考

- [VirtIO 规范 v1.2](https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.html)（最新，2022）
- [VirtIO 规范 v1.1](https://docs.oasis-open.org/virtio/virtio/v1.1/virtio-v1.1.html)（2019）
- [VirtIO 规范 v1.0](https://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.html)（2016）
- [OASIS VirtIO 技术委员会](https://www.oasis-open.org/committees/virtio/)

## 许可证

Apache-2.0
