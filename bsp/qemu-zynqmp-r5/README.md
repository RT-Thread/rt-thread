# QEMU ZynqMP 板级支持包说明

## 简介
本文档是为 QEMU 模拟 Xilinx Zynq UltraScale+ (ZynqMP) 平台提供的说明。
> qemu-zynqmp-r5平台的支持，同时提供了两个部分。一是cortex-r5独立的libcpu，二是BSP的实现。

## 板载信息
| **核心**       | **支持情况** | **备注**               |
|:---------------|:------------:|:-----------------------|
| R5-CPU0        | 支持         | 运行系统的为R5核的CPU0 |
| **中断控制器** | **支持情况** | **备注**               |
| GICV1          | 支持         | PL390                  |
| **片上外设**   | **支持情况** | **备注**               |
| UART           | 支持         | UART0                  |
| TTC            | 支持         |                        |

## 环境搭建（非常重要）
根据 Xilinx 官方给出的方案，`qemu-system-aarch64` 自带的 `xlnx-zcu102` 并不完善，故使用 QEMU Xilinx 补丁版。
> 笔者暂无 Windows 平台，故此说明文档是以 Linux 为背景的。

### QEMU 源码下载与编译
[Building and Running QEMU from Source Code](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/822312999/Building+and+Running+QEMU+from+Source+Code)

## 编译
`scons -j12`

## 运行和退出
### 运行脚本
| 脚本文件          | 运行平台 | 备注                     |
|-------------------|----------|:------------------------:|
| qemu-nographic.sh | Linux    | 以不带界面的模式启动运行 |

### 运行
> 注意：`sh qemu-nographic.sh`后面一定要加上，上面编译的`qemu-system-aarch64`
```bash
$ sh qemu-nographic.sh qemu-system-aarch64
QEMU emulator version 7.1.0 (v2.6.0-55407-g21adc9f99e)
Copyright (c) 2003-2022 Fabrice Bellard and the QEMU Project developers

\ | /
- RT -     Thread Operating System
/ | \      5.0.1 build May 15 2023 22:41:21
 2006 - 2022 Copyright by RT-Thread team
Hello RT-Thread!
msh />
```

### 退出
`ctrl c`

## 调试
此版本QEMU的实现目前无法支持GDB调试，所以只能通过串口打印作为调试手段！

## 参考资料
- ARMv7-A and ARMv7-R Architecture Reference Manual (ARM DDI 0406C ID051414)
- Cortex-R5 and Cortex-R5F Technical Reference Manual (ARM DDI 0460C ID021511)
- Zynq UltraScale+ Device Technical Reference Manual (UG1085)

## 联系人信息

维护人：[lepustse](https://gitee.com/lepustse)
