# RT-Thread Bluetooth Documentation / RT-Thread 蓝牙文档

This directory contains documentation about Bluetooth implementation in RT-Thread and comparisons with other Bluetooth stacks.

本目录包含 RT-Thread 蓝牙实现的相关文档以及与其他蓝牙协议栈的对比。

## Documents / 文档

### English

- [BlueZ vs RT-Thread Bluetooth Implementation](bluez_vs_rtthread_en.md) - Explains the differences between Linux BlueZ (using D-Bus) and RT-Thread's direct Bluetooth implementation

### 中文

- [BlueZ 与 RT-Thread 蓝牙实现对比](bluez_vs_rtthread_zh.md) - 解释 Linux BlueZ（使用 D-Bus）与 RT-Thread 直接蓝牙实现的区别

## Quick Answer / 快速答案

**Q: What bus does BlueZ use in Linux?**  
**A: BlueZ uses D-Bus (Desktop Bus) as its inter-process communication (IPC) mechanism.**

**问：Linux 中 BlueZ 使用什么总线？**  
**答：BlueZ 使用 D-Bus（桌面总线）作为其进程间通信（IPC）机制。**

## Key Takeaways / 要点

- **Linux BlueZ**: Uses D-Bus for IPC, suitable for desktop/server environments with multiple processes
- **RT-Thread**: Uses direct function calls, optimized for embedded real-time systems with limited resources

- **Linux BlueZ**：使用 D-Bus 进行 IPC，适用于具有多个进程的桌面/服务器环境
- **RT-Thread**：使用直接函数调用，针对资源有限的嵌入式实时系统进行了优化
