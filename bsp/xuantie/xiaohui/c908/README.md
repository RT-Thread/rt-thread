# XuanTie - C908  Series

## 一 简介

### 1. 内核

C908MP 是基于RISC-V 指令架构的64 位高性能多核心处理器，主要面向IoT 市场日益增强的图像、视觉
处理领域，例如智慧视觉、车载视觉、行车记录仪、智能交互等。其他应用领域还包括扫地机器人、无人
机、自动化驾驶、增强现实、医疗图像、机器人工业视觉、移动互联网等产品。
C908MP 采用同构多核架构，支持多cluster，每个cluster 支持1~4 个核心。每个C908 核心采用自主设
计的微体系结构，并重点针对性能进行优化，采用按序双发射、多模式分支预测和多通道数据预取等高性
能技术。此外，C908 核心支持实时检测并关断内部空闲功能模块，降低处理器动态功耗。

### 2.特点
#### 2.1. C908MP 处理器体系结构的主要特点
• 同构多核架构，支持多cluster，每个cluster 支持1~4 个C908 核心；

• 支持1 个AXI4.0 或ACE Master 接口，128 比特的总线宽度；

• 支持1 个可配置的AXI4.0 低延时外设Master 接口（Low Latency Port, LLP），128 比特的总线宽度；

• 支持1 个可配的AXI4.0 设备一致性接口(Device Coherence Port, DCP)，128 比特的总线宽度；

• 一级指令/数据缓存分别支持16KB/32KB/64KB，缓存行SIZE 为64B；可配置ECC/奇偶校验机制；

• 二级高缓128KB/256KB/512KB/1MB/1.5MB/2MB/3MB/4MB，缓存行SIZE 为64B；可配置ECC 校验机制；

• 一级缓存支持MESI 一致性协议，二级缓存支持MOESI 一致性协议；

• 支持私有中断控制器CLINT 和公有中断控制器PLIC；支持多cluster 中断分发；

• 支持RISC-V 性能计数器和计时器；

• 支持Sv39 和Sv48 内存管理，支持SVNAPOT 和SVPBMT 标准扩展；

• 支持8/16/32/64 表项PMP，支持ePMP；

• 支持XuanTie TEE 扩展；

• 支持各个核心独立下电以及cluster 下电；

• 支持RISC-V 调试框架，支持多核多cluster 调试；

#### 2.2. C908 核心的主要特点
• RISC-V 64GCB[V] 指令架构；

• User Mode 支持RV64 和RV32 指令集；

• 支持小端模式；

• 9 级流水架构；

• 按序双发射，按序取指、发射、执行和退休；

• 两级TLB 内存管理单元，实现虚实地址转换与内存管理；

• 指令高缓和数据高缓大小可配置，支持16KB/32KB/64KB，缓存行为64B；

• 指令高缓可配置奇偶校验，数据高缓可配置ECC 或奇偶校验；

• 指令预取功能，硬件自动检测并动态启动；

• 指令高缓路预测的低功耗访问技术；

• 支持2KB/4KB/8KB 的多算法分支预测器；

• 支持256 表项的分支目标缓存器（BTB）；

• 支持8 层的硬件返回地址堆栈；

• 支持256 表项的间接跳转分支预测器；

• 支持循环终止预测；

• 支持指令融合技术；

• 双发射按序执行Load、Store 指令；

• 读、写内存分别支持8 路、12 路并发的总线访问；

• 支持写合并；

• 支持8 通道数据预取，支持固定stride 和规律性不定stride 数据预取；

#### 2.3. 矢量计算单元的主要特点
• 遵循RISC-V V 矢量扩展；

• 在4 核、2GHz 最大配置下，算力可达512 Gops (@int8)/ 256 GFlops (@FP16)；

• 矢量执行单元支持FP16/BFP16/FP32 浮点和INT8/INT16/INT32/INT64 整型的矢量运算；

• 支持128/256 可配置的矢量寄存器位宽VLEN；

• 支持矢量执行单元运算和数据存储流水线数量（1 或2）可配；

• 支持128 位或256 位矢量数据存储访问位宽；

• 支持segment load、store 指令；

• 性能优化的非对齐内存访问；

### 3.BSP支持情况

- 当前BSP支持下述内核：

  ```asciiarmor
  c908i c908 c908v
  ```

- 当前BSP默认设置的内核是c908v，该架构支持[F] [D] [V]扩展，可以通过menuconfig工具使能[F]扩展或者[F] [D] [V] 扩展。

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

<img src="figures/2.scons.png" alt="env" style="zoom: 95%;" />

生成可执行文件，可以直接在命令行启动qemu或者配置vscode脚本借助vscode强大的插件进行图形化调试，qemu的相关命令可以查看玄铁qemu的[用户手册](https://www.xrvm.cn/community/download?id=4397435198627713024)，下述是启动qemu的命令，在powershell或命令行可直接执行下述命令，注意qemu需要导出至环境变量或者使用绝对路径。

```shell
qemu-system-riscv64 -machine xiaohui -nographic -kernel rtthread.elf -cpu c908v
```

下述是使用vscode调试的展示。

<img src="figures/3.vscode.png" alt="env" style="zoom: 63%;" />

一起为RISC-V加油！