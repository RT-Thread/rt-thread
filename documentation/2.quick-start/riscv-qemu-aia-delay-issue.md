# QEMU RISC-V 启用 AIA 后延时打印停止的现象记录

记录日期：2026-10-31。状态：已定位到旧版 QEMU 的 APLIC 电平中断重触发问题，
已在 RT-Thread APLIC 驱动加入兼容处理，并在当前环境验证通过。

下文的现象及初始对照结果描述修复前的行为；修复和验证结果见文末。

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

## 初始判断与证据边界（修复前）

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

## 临时使用方式（修复前）

学习和验证基础线程功能时，可以使用已验证正常的启动参数：

```sh
./qemu.py -no-aia -no-net -no-nvme -no-virtio-console -no-pci-serial
```

这是临时绕过方式，不是对 AIA 问题的修复。不需要为此修改延时循环或
手工编辑 `rtconfig.h`。

## 初始排查方向

1. 在相同镜像和外设配置下重复开关 AIA，确认复现稳定性，并记录 boot hart。
2. 通过 GDB 检查延时调用之后线程停在哪里、各 CPU 正在执行什么代码。
3. 检查系统 tick 是否推进，以及定时器到期后线程是否转为就绪状态。
4. 检查 AIA 下的中断处理、IPI 和 SMP 调度，排查中断循环或锁等待。
5. 分别验证单核与多核配置，再按需比较不同 QEMU/OpenSBI 版本。

更改核数应通过配置工具生成 `rtconfig.h` 并重新编译，保持 QEMU 核数与
`RT_CPUS_NR` 一致。后续修复需要同时验证 AIA 和 PLIC/CLINT 两条路径。

## 定位结果

通过 QEMU 的 GDB 调试接口，在仅打印 `0` 后暂停并查看各 CPU 状态：

- 逻辑 CPU0 的 tick 停在 `70`，中断嵌套计数为 `2`。
- 其他逻辑 CPU 的 tick 已超过 `1200`，仍在计时。
- 调用栈经过 `riscv_intc_aia_handler_raw()`、`imsic_handler()`、
  `rt_pic_handle_isr()` 和 `virtio_mmio_isr()`；再次暂停时位于
  `aplic_msi_irq_eoi()`。

当前 SMP 实现仅由逻辑 CPU0 调用 `rt_timer_check()`。该 CPU 持续处理外部
中断，无法正常推进其时钟和定时器处理，因此应用延时后没有继续打印。

APLIC 在 MSI 模式下处理电平中断时，设备驱动先确认设备中断；APLIC 驱动
随后写 `setipnum_le`，使仍然有效的电平中断能够再次送达。按照 AIA 规范，
设备已经撤销中断时，这次写入不应设置新的 pending 中断。

旧版 QEMU 的相关模拟行为不符合这一条件，导致设备中断已撤销时，EOI 中的
写入仍产生新的 MSI，形成反复进入处理函数的中断循环。
QEMU 上游提交 `bf31cf06eb5e709a1a7b082dc7956baadc4b70fa`
修正了同类 `setipnum_le` 模拟问题。

## 兼容处理

修改文件：`libcpu/risc-v/common/pic/pic-riscv-aplic.c`，
函数：`aplic_msi_irq_eoi()`。

对高、低电平中断，先读取 `in_clrip` 寄存器中的 rectified input
（考虑极性后的有效输入），仅在该中断仍被设备置为有效时写 `setipnum_le`。
输入已经无效时不重新触发，从而避免旧版模拟器产生无休止的虚假 MSI。

这项处理保留 AIA、APLIC/IMSIC 和电平中断重触发能力，不改变应用延时逻辑、
系统 tick 频率或多核数量。它是 RT-Thread 侧的兼容处理，没有修改 QEMU。

## 修复后的验证

编译命令：在 BSP 目录执行 `scons -j8`，编译和链接通过。

| 运行配置 | 结果 |
| --- | --- |
| AIA，4 核，关闭网络、NVMe 和附加串口 | 完整输出 `0` 到 `9` |
| PLIC/CLINT，4 核，关闭上述设备 | 完整输出 `0` 到 `9` |
| AIA，4 核，开启全部默认设备 | 完整输出 `0` 到 `9` |

全部默认设备测试保留 virtio 网络、NVMe、virtio-console 和 PCI serial。
由于宿主机默认串口端口 `4321` 已被其他进程占用，测试使用独立临时磁盘，
并将宿主机监听端口改为自动分配；虚拟机中的设备组合和 AIA 配置保持开启。
这不是直接使用所有默认宿主机端口的运行测试。

修复后的镜像可通过 `./qemu.py` 启动，不再需要 `-no-aia`。
若提示端口或磁盘占用，应先退出使用相同资源的旧 QEMU 实例。

验证范围为当前 QEMU 8.2.2、OpenSBI v1.3、RV64 SMP 配置；尚未覆盖真实
APLIC 硬件、低电平外设和所有模拟器版本。

## 参考资料

- [RISC-V AIA 规范](https://docs.riscv.org/reference/aia/_attachments/riscv-interrupts.pdf)：
  4.5.7 节说明读取 `in_clrip` 得到 rectified input，4.7 节说明电平中断
  在 MSI 模式下的 pending 更新条件。
- [QEMU 上游修复提交](https://github.com/qemu/qemu/commit/bf31cf06eb5e709a1a7b082dc7956baadc4b70fa)：
  `hw/intc/riscv_aplic: Fix setipnum_le write emulation for APLIC MSI-mode`。
