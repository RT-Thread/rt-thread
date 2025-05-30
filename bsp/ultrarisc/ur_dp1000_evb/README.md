UR-DP1000 Evb Board Support Package 使用说明

# 1. 概述

UR-DP1000是超睿科技研发的高性能多核RISC-V Soc，拥有8个高性能自研RISC-V处理器核UR-CP100，同时集成了24路PCIe 4.0、双路DDR 4以及一系列丰富的低速接口。

本 BSP 支持 UR-DP1000 EVB开发板。采用本BSP编译生成的RT-Thread标准版本以及Smart版本可以运行在 UR-DP1000 EVB开发板上。板卡集成16GB DDR4内存。

# 2. 芯片规格说明

| 硬件 | 描述 |
| -- | -- |
|芯片型号| UR-DP1000 |
|CPU| 8核UR-CP100，64位乱序发射超标量微架构，支持rv64imafdchx指令集，支持虚拟化扩展 |
|主频| 2.0-2.3GHz |
|cache| 核内集成64KB L1I和64KB L1D Cache以及512KB L2 Cache |
| 外设 | 支持两路DDR4，支持ECC，最大支持内存容量128GB |
|  | 支持24路PCIe 4.0接口 |
| | SPI、UART、QSPI、UART、GMAC、I2C、PWM、GPIO等 |

# 3. BSP外设支持

| 设备名称 | 支持情况 | 说明                                                       |
| -------- | -------- | ---------------------------------------------------------- |
| PLIC     | 支持     | 中断控制器                                                 |
| CLINT    | 支持     | RISC-V core local 中断控制器，系统时钟及核间中断依赖该设备 |
| MMU      | 支持     | 支持SV39，支持ASID                                         |
| UART     | 支持     | 调试串口                                                   |
| SPI      | 支持     | Designware apb ssi ,支持TF卡驱动                           |

# 4. 编译

RT-Thread编译只支持Linux，推荐Ubuntu 22.04。

## 4.1. toolchain下载

toolchain下载地址：<https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2>

将下载的toolchain解压到指定路径中，例如：/opt/riscv64gc-linux-musleabi_for_x86_64-pc-linux-gnu

## 4.2. BSP编译

### 4.2.1. 设置编译环境变量

```shell
export RTT_EXEC_PATH=/opt/riscv64gc-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
```

### 4.2.2. 安装编译依赖

```shell
sudo apt install scons  python3-pip
pip install kconfiglib
```
### 4.2.3. 编译

```shell
git clone https://github.com/RT-Thread/rt-thread.git
cd bsp/ultrarisc/ur_dp1000_evb
#默认为RT-Thread标准版
scons
```

编译完成后，可以在bsp目录下生成rt-thread.elf及rtthread.bin文件。

如果要编译RT-Thread Smart版本，需要通过scons --menuconfig使能：RT-Thread Kernel->Enable RT-Thread Smart (microkernel on kernel/userland);

同时使能SPI MMC驱动：Ultrarisc DP1000 Soc Drivers Configuration->Using MMC。

# 5. 运行

编译完成后，在UR-DP1000 EVB板卡上可以通过jtag加载镜像运行：

在RT-Thread调试阶段，为了能够快速的下载RT-Thread镜像，方便功能调试，可以通过jtag下载及调试：

- 板卡上电后，首先运行固化在flash里的固件，opensbi启动；

- 将jtag调试器与板卡jtag口连接，同时启动openocd;

- 如果是标准版本，可以直接通过gdb加载rt-thread.elf，然后continue运行；如果是RT-Thread Smart版本，需要通过gdb加载rtthread.bin，然后修改pc值为0x80200000,continue运行。

  ```shell
  #gdb
  restore rtthread.bin binary 0x80200000
  set $pc=0x80200000
  continue
  ```

  成功运行时，串口端的输出如下：
  ```shell
  OpenSBI v1.6-66-gbeb27559acd
     ____                    _____ ____ _____
    / __ \                  / ____|  _ \_   _|
   | |  | |_ __   ___ _ __ | (___ | |_) || |
   | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
   | |__| | |_) |  __/ | | |____) | |_) || |_
    \____/| .__/ \___|_| |_|_____/|____/_____|
          | |
          |_|
  
  Platform Name               : ultrarisc,dp1000
  Platform Features           : medeleg
  Platform HART Count         : 8
  Platform IPI Device         : aclint-mswi
  Platform Timer Device       : aclint-mtimer @ 10000000Hz
  Platform Console Device     : uart8250
  Platform HSM Device         : ---
  Platform PMU Device         : ---
  Platform Reboot Device      : ---
  Platform Shutdown Device    : ---
  Platform Suspend Device     : ---
  Platform CPPC Device        : ---
  Firmware Base               : 0x80000000
  Firmware Size               : 403 KB
  Firmware RW Offset          : 0x40000
  Firmware RW Size            : 147 KB
  Firmware Heap Offset        : 0x54000
  Firmware Heap Size          : 67 KB (total), 4 KB (reserved), 11 KB (used), 51 KB (free)
  Firmware Scratch Size       : 4096 B (total), 400 B (used), 3696 B (free)
  Runtime SBI Version         : 2.0
  Standard SBI Extensions     : time,rfnc,ipi,base,hsm,pmu,dbcn,legacy
  Experimental SBI Extensions : fwft,sse
  
  Domain0 Name                : root
  Domain0 Boot HART           : 0
  Domain0 HARTs               : 0*,1*,2*,3*,16*,17*,18*,19*
  Domain0 Region00            : 0x0000000020310000-0x0000000020310fff M: (I,R,W) S/U: (R,W)
  Domain0 Region01            : 0x0000000080000000-0x000000008003ffff M: (R,X) S/U: ()
  Domain0 Region02            : 0x0000000080040000-0x000000008007ffff M: (R,W) S/U: ()
  Domain0 Region03            : 0x0000000008000000-0x00000000080fffff M: (I,R,W) S/U: ()
  Domain0 Region04            : 0x0000000000000000-0xffffffffffffffff M: () S/U: (R,W,X)
  Domain0 Next Address        : 0x0000000080200000
  Domain0 Next Arg1           : 0x0000000082200000
  Domain0 Next Mode           : S-mode
  Domain0 SysReset            : yes
  Domain0 SysSuspend          : yes
  
  Boot HART ID                : 0
  Boot HART Domain            : root
  Boot HART Priv Version      : v1.12
  Boot HART Base ISA          : rv64imafdchx
  Boot HART ISA Extensions    : zicntr,zihpm
  Boot HART PMP Count         : 4
  Boot HART PMP Granularity   : 2 bits
  Boot HART PMP Address Bits  : 42
  Boot HART MHPM Info         : 6 (0x000001f8)
  Boot HART Debug Triggers    : 0 triggers
  Boot HART MIDELEG           : 0x0000000000000666
  Boot HART MEDELEG           : 0x0000000000f0b509
  
  Test payload running
  ssi_version_id=4.03*
  fifo length is 64
  heap: [0x002acb28 - 0x042acb28]
  
   \ | /
  - RT -     Thread Smart Operating System
   / | \     5.2.1 build May 28 2025 08:24:41
   2006 - 2024 Copyright by RT-Thread team
  [I/drivers.serial] Using /dev/ttyS0 as default console
  Mount "/dev/sd0p1" on "/"
  Hello RT-Thread
  msh />
  / # 
  ```
  # 6. 联系人信息
  zhangjing@ultrarisc.com