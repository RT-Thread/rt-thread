# XuanTie - E907  Series

## 一 简介

### 1. 内核

E907 是一款基于 RISC-V 指令集的高性能嵌入式微处理处理器，是玄铁 RISC-V MCU 产品线中的最高性能处理器。E907 主要面向语音、MPU、导航、WiFi 等应用领域。

### 2.特点

E907 处理器体系结构的主要特点如下：

• 32 位 RISC 处理器；

• 支持 RISC-V RV32IMA[F][D]C[P] 指令集；

• 支持 RISC-V 32/16 位混编指令集；

• 支持 RISC-V 机器模式和用户模式；

• 32 个 32 位整型通用寄存器，32 个 32 位/64 位浮点通用寄存器；

• 整型 5 级/浮点 7 级，单发射，顺序执行流水线；

• 支持 AXI4.0 主设备接口以及 AHB5.0 外设接口；

• 指令 Cache，两路组相连结构，2KB-32KB 可配置；

• 数据 Cache，两路组相连结构，2KB-32KB 可配置；

• 支持非对齐内存访问；

• 双周期硬件乘法器，基 4 硬件除法器；

• 可选配 BHT 和 BTB；

• 支持玄铁扩展增强指令集；

• 支持玄铁 MCU 特性扩展技术，包括中断处理加速技术、MCU 扩展特性；

• 兼容 RISC-V CLIC 中断标准，支持中断嵌套，外部中断源数量最高可配置 240 个；

• 兼容 RISC-V PMP 内存保护标准，0/4/8/12/16 区域可配置；

• 支持可配的性能监测单元；

• 支持 RISC-V Debug 协议标准；

• 频率 >1.0GHz@T28 HPCPlus，9T SVT(worst case)，Coremark > 3.8 coremark/MHz，Dhrystone

\> 2.0 DMIPS/MHz。

### 3.BSP支持情况

- 当前BSP支持下述内核：

  ```asciiarmor
   e907 e907f e907fd e907p e907fp e907fdp 
  ```

- 当前BSP默认设置的内核是e907fd，该架构支持[F] [D]扩展，可以通过menuconfig工具使能[F]扩展或者[F] [D] 扩展。

- 当使用其他内核架构时需要修改，rtconfig.py文件中的`MCPU`字段。

### 4.运行QEMU

- BSP根目录下存在`qemu.bat`脚本，生成可执行文件后可点击该脚本直接启动QEMU.

## 二 工具

- 编译器： https://www.xrvm.cn/community/download?id=4433353576298909696
- 模拟器： https://www.xrvm.cn/community/download?id=4397435198627713024

注：若上述链接中的编译器与模拟器不能使用，可以使用下述CDK中的编译器与模拟器

- SDK：https://www.xrvm.cn/community/download?id=4397799570420076544

## 三 调试方法

**下述调试方法以E906举例，本BSP操作方式一致**，搭建完成RT-Thread开发环境，在BSP根目录使用env工具在当前目录打开env。

![](figures/1.env.png)

使用前执行一次**menuconfig**命令，更新rtconfig.h配置，然后在当前目录执行**scons -j12**命令编译生成可可执行文件。

<img src="figures/2.scons.png" alt="env">

生成可执行文件，可以直接在命令行启动qemu或者配置vscode脚本借助vscode强大的插件进行图形化调试，qemu的相关命令可以查看玄铁qemu的[用户手册](https://www.xrvm.cn/community/download?id=4397435198627713024)，下述是启动qemu的命令，在powershell或命令行可直接执行下述命令，注意qemu需要导出至环境变量或者使用绝对路径。

```shell
qemu-system-riscv64 -machine smartl -nographic -kernel rtthread.elf -cpu e906
```

下述是使用vscode调试的展示。

<img src="figures/3.vscode.png" alt="env" />

一起为RISC-V加油！