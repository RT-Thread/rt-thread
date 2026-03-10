# XuanTie - E901  Series

## 一 简介

### 1. 内核

玄铁 E901+ 是基于 RISC-V 指令架构的低成本、高能效的 32 位嵌入式 CPU 处理器，用户可以以近似 8 位CPU 的成本获得 32 位嵌入式处理器的效率与性能。E901+ 处理器兼容 RV32E[M] [B]_Zc 指令架构，采用 16/32 位混合编码系统，指令系统与流水线硬件结构精简高效。同时支持配置协处理器接口，用于满足用户 DSA（Domain Specific Accelerator）需求，加速特定应用执行，并支持用户进行自定义指令扩展。

E901+ 主要针对智能卡、智能电网、低成本微控制器、无线传感网络等嵌入式应用。

### 2.特点

E902 处理器体系结构的主要特点如下：

E901+ 处理器体系结构的主要特点如下：

• 支持 RV32E [M] [B]_Zc 指令集

• 16 个 32 位通用寄存器

• 两级顺序执行流水线

• 支持 RISC-V 机器模式和用户模式

• 支持 RISC-V Debug 架构，支持标准五线 JTAG 调试接口，支持 CJTAG 两线调试接口

• 支持以下硬件乘/除法器配置：

**–** 不配置硬件乘/除法器

**–** 配置单周期快速硬件乘法器，以及多周期（1-33）慢速硬件除法器

**–** 配置多周期（3-33）慢速硬件乘法器，以及多周期（1-33）慢速硬件除法器

• 兼容 RISC-V CLIC 中断标准，支持中断优先级可配置，支持中断嵌套和中断咬尾

• 外部中断源数量最高可配置为 112 个

• 兼容 RISC-V PMP 内存保护标准，0/2/4/8/16 区域可配置

• 支持指令总线和系统总线，指令总线支持 AHB-Lite（即 AHB 3.0）协议，系统总线协议支持 AHB 2.0

和 AHB-Lite

• 支持指令高速缓存，缓存行 16 字节，容量 2KiB/4KiB/8KiB 可配

• 支持玄铁扩展编程模型

• 支持复位启动地址硬件集成时可配置

• 支持软复位操作

• 支持协处理器接口可配置

### 3.BSP支持情况

- 当前BSP支持下述内核：

  ```asciiarmor
  e901plusbm-cp
  ```

- 当前BSP默认设置的内核是e901plusbm-cp。

- 当使用其他内核架构时需要修改，rtconfig.py文件中的`MCPU`字段。

### 4.运行QEMU

- BSP根目录下存在`qemu.bat`脚本，生成可执行文件后可点击该脚本直接启动QEMU.

## 二 工具

- 编译器： https://www.xrvm.cn/community/download?id=4433353576298909696
- 模拟器： https://www.xrvm.cn/community/download?id=4397435198627713024

注：若上述链接中的编译器与模拟器不能使用，可以使用下述CDK中的编译器与模拟器

- SDK：https://www.xrvm.cn/community/download?id=4397799570420076544

## 三 调试方法

**下述调试方法以E902举例，本BSP操作方式一致**，搭建完成RT-Thread开发环境，在BSP根目录使用env工具在当前目录打开env。

![](figures/1.env.png)

使用前执行一次**menuconfig**命令，更新rtconfig.h配置，然后在当前目录执行**scons -j12**命令编译生成可可执行文件。

<img src="figures/2.scons.png" alt="env" style="zoom: 95%;" />

生成可执行文件，可以直接在命令行启动qemu或者配置vscode脚本借助vscode强大的插件进行图形化调试，qemu的相关命令可以查看玄铁qemu的[用户手册](https://www.xrvm.cn/community/download?id=4397435198627713024)，下述是启动qemu的命令，在powershell或命令行可直接执行下述命令，注意qemu需要导出至环境变量或者使用绝对路径。

```shell
qemu-system-riscv32 -machine smartl -nographic -kernel rtthread.elf -cpu e901plusbm-cp
```

下述是使用vscode调试的展示。

<img src="figures/3.vscode.png" alt="env" style="zoom: 63%;" />

一起为RISC-V加油！