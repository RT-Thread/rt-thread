# QEMU RISC-V 启用 AIA 后延时打印停止的现象记录

记录日期：2026-10-31。状态：已在当前环境复现，根因待定位，尚未修复。

## 现象

在 `bsp/qemu-virt64-riscv` 中，应用先打印计数，再调用
`rt_thread_mdelay(1000)` 延时。用户报告：直接执行 `./qemu.py` 时打印异常，
关闭部分默认设备后可以正常打印。

进一步对照测试发现：保留 AIA、关闭网络、NVMe 和附加串口时，程序仅打印
`RISC-V test: 0`，直到测试超时仍未继续输出；关闭 AIA 后可以打印到 `9`。

本记录只描述当前环境的测试结果，不代表所有 RISC-V 平台或所有 AIA 配置
都存在同样问题。

## 测试环境

- BSP：`bsp/qemu-virt64-riscv`。
- 内核：RT-Thread 5.4.0，标准版，RV64，SMP，4 核。
- 公共移植层：启用 `RT_USING_RISCV_NEW_COMMON`。
- 系统 tick：`RT_TICK_PER_SECOND=100`。
- QEMU：8.2.2。
- OpenSBI：启动日志显示 v1.3。
- 编译器：`riscv64-unknown-elf-gcc` 13.2.0。
- 测试镜像：当前工作区生成的 `rtthread.bin`，启动横幅中的编译时间为
  `Oct 31 2026 19:25:20`。

## 测试程序

文件：`bsp/qemu-virt64-riscv/applications/main.c`。

```c
#include <rtthread.h>

int main(void)
{
    int count;

    for (count = 0; count < 10; count++)
    {
        rt_kprintf("RISC-V test: %d\n", count);
        rt_thread_mdelay(1000);
    }

    return 0;
}
```

预期：第一次立即打印 `0`，随后约每秒打印一次，直到 `9`，再延时一次后
退出 `main()`。这是有限循环，打印十次后停止属于正常行为。

## 复现步骤

先退出之前运行的 QEMU，再进入 BSP 目录并编译：

```sh
cd bsp/qemu-virt64-riscv
export RTT_EXEC_PATH=/usr/bin
export RTT_CC_PREFIX=riscv64-unknown-elf-
scons -j$(nproc)
```

以上路径和工具链设置对应本次环境。修改 C 代码后需要重新编译；
`qemu.py` 只启动模拟器，不会自动编译应用。

### 对照一：关闭 AIA

```sh
python3 qemu.py -no-aia -no-net -no-nvme -no-virtio-console -no-pci-serial
```

实际结果：系统完成启动后，依次打印 `RISC-V test: 0` 到
`RISC-V test: 9`。

### 对照二：保留 AIA，关闭其他上述设备

```sh
python3 qemu.py -no-net -no-nvme -no-virtio-console -no-pci-serial
```

RV64 下脚本默认开启 AIA。实际测试观察窗口为进程启动后的 20 秒：
系统进入应用并打印 `RISC-V test: 0`，之后直到超时没有继续输出。

测试时使用了独立的临时虚拟磁盘，避免占用用户正在使用的镜像。
上面给出的复现命令使用脚本默认磁盘，因此请逐个运行，避免磁盘锁冲突。

### 其他观察

| 配置 | 结果 |
| --- | --- |
| 直接执行 `./qemu.py`，使用默认设备 | 用户报告输出异常 |
| 关闭 AIA、网络、NVMe 和附加串口 | 实测打印 `0` 到 `9` |
| 保留 AIA，关闭网络和附加串口，启用 NVMe | 实测在 22 秒观察窗口内仅打印 `0` |
| 保留 AIA，关闭网络、NVMe 和附加串口 | 实测在 20 秒观察窗口内仅打印 `0` |

## 启动参数为什么会影响结果

当前 `qemu.py` 在 RV64 下默认启用 AIA，即使用 APLIC/IMSIC 中断配置。
传入 `-no-aia` 后，脚本选择 PLIC/CLINT 路径。

此外，脚本默认是否启用 NVMe 与 AIA 选项有关：未显式指定 NVMe 参数时，
关闭 AIA 也会取消默认启用的 NVMe。因此，仅比较 `./qemu.py` 和
`./qemu.py -no-aia` 不足以隔离变量；上述对照一、二显式关闭了 NVMe
及其他附加设备。

`python3 qemu.py` 与 `./qemu.py` 都可以启动该脚本，本次已知差异是设备参数，
没有证据表明异常来自这两种调用形式。

## 当前判断与证据边界

线程的执行顺序为：

```text
打印 0 → 延时并让出 CPU → 等待到期 → 线程恢复执行 → 打印 1
```

打印出 `0` 证明应用已经开始执行；后续没有输出说明需要检查延时调用、
时钟推进、线程唤醒和调度，以及恢复执行后的输出路径。

对照测试把问题范围缩小到了当前环境的 AIA 配置相关运行路径，尚不能确定
具体责任在 QEMU、OpenSBI、RT-Thread 中断驱动还是 SMP 调度交互。
目前没有直接测量 tick、线程状态或中断计数，不能据此断言时钟中断一定停止，
也不能认定线程一定没有被唤醒。

## 临时使用方式

学习和验证基础线程功能时，可以使用已验证正常的启动参数：

```sh
./qemu.py -no-aia -no-net -no-nvme -no-virtio-console -no-pci-serial
```

这是临时绕过方式，不是对 AIA 问题的修复。不需要为此修改延时循环或
手工编辑 `rtconfig.h`。

## 后续排查方向

1. 在相同镜像和外设配置下重复开关 AIA，确认复现稳定性，并记录 boot hart。
2. 通过 GDB 检查延时调用之后线程停在哪里、各 CPU 正在执行什么代码。
3. 检查系统 tick 是否推进，以及定时器到期后线程是否转为就绪状态。
4. 检查 AIA 下的中断处理、IPI 和 SMP 调度，排查中断循环或锁等待。
5. 分别验证单核与多核配置，再按需比较不同 QEMU/OpenSBI 版本。

更改核数应通过配置工具生成 `rtconfig.h` 并重新编译，保持 QEMU 核数与
`RT_CPUS_NR` 一致。后续修复需要同时验证 AIA 和 PLIC/CLINT 两条路径。
