# QEMU RISC-V AIA EOI 重触发观测与验证记录

记录日期：2026-11-06。

本文整理观测点添加、观测代码说明、virtio 中断处理流程，以及实际验证结果。
背景问题与兼容修复见
[QEMU RISC-V 启用 AIA 后延时打印停止的现象记录](riscv-qemu-aia-delay-issue.md)。

验证目标：

1. 设备中断输入仍有效时，修改后的 EOI 能重新触发中断，使请求继续处理。
2. 设备已经撤销中断输入时，EOI 不产生多余重触发。
3. 设备静默后，中断计数稳定，CPU0 tick 和应用延时继续正常运行。

本记录中的实际结果来自本次会话已完成的测试。文档整理时未重新运行测试。

## 1. 环境与验证边界

| 项目 | 本次配置 |
| --- | --- |
| BSP | `bsp/qemu-virt64-riscv` |
| 内核 | RT-Thread 5.4.0，RV64，SMP，4 核 |
| QEMU | 8.2.2 |
| OpenSBI | v1.3 |
| 中断控制器 | AIA，APLIC/IMSIC，MSI 模式 |
| 系统 tick | `RT_TICK_PER_SECOND=100` |
| 观测设备 | virtio-mmio 块设备 |
| 设备连接 | 使用 virtio-mmio，不添加 `-pci` |
| 磁盘 | 以原磁盘为后备文件的独立临时 qcow2 覆盖层 |
| 附加设备 | 关闭网络、NVMe、virtio-console 和 PCI serial |
| 工具 | `scons`、RISC-V GCC、`qemu-img`、`gdb-multiarch` |

本次运行中选中的逻辑 IRQ 为 `333`，APLIC hwirq 为 `8`。
编号必须在每次运行时读取，不应写死。

验证覆盖当前模拟环境中的受控电平中断路径，尚未覆盖高并发竞态、
低电平外设和真实 APLIC 硬件，不能据此保证所有场景下绝不丢中断。

## 2. 为什么需要同时观测设备 ISR 和 EOI

设备 ISR 和 APLIC EOI 的职责不同：设备 ISR 确认并处理设备事件；
APLIC EOI 检查中断输入是否仍有效，决定是否请求重新送达。

```text
设备产生事件并置中断有效
  → virtio_mmio_isr() 读取设备状态
  → 写设备 ACK，确认通知
  → 处理配置变化或 virtqueue 事件
  → 返回上层中断处理框架
  → aplic_msi_irq_eoi() 读取有效输入
  → 仍有效：写 setipnum_le，请求重新触发
  → 已无效：跳过重触发写入
```

仅看到应用能打印到 `9`，不能证明“仍有效时能够重触发”。
仅看到 `setipnum_le` 写入次数增加，也不能证明中断已经再次送达。
需要同时观察设备 ISR、EOI 分支及请求完成结果。

## 3. 第一步：添加的观测点及其作用

观测代码添加在两个文件中，均增加 `#include <rtatomic.h>`：

- [APLIC 驱动](../../libcpu/risc-v/common/pic/pic-riscv-aplic.c)：
  `aplic_msi_irq_eoi()`。
- [virtio-mmio 驱动](../../components/drivers/virtio/virtio_mmio.c)：
  `virtio_mmio_isr()`。

这次添加共 79 行，用于临时调试。原有设备 ACK、队列处理和 EOI 判断逻辑保留。
代码不在 ISR 内打印；通过 GDB 读取计数，减少打印对时序的影响。
计数操作本身仍会增加少量执行时间。

### 3.1 APLIC EOI 观测结构体

```c
static volatile struct
{
    int irq;
    int hwirq;
    rt_uint32_t mode;
    rt_uint32_t last_input;
    rt_atomic_t eoi_count;
    rt_atomic_t active_count;
    rt_atomic_t inactive_count;
    rt_atomic_t retrigger_count;
} aplic_eoi_debug = { .irq = -1 };
```

| 字段 | 含义 |
| --- | --- |
| `irq` | 选定的 RT-Thread 逻辑 IRQ；`-1` 表示关闭统计 |
| `hwirq` | 最近一次被观测中断的 APLIC 硬件中断号 |
| `mode` | 最近一次被观测中断的触发模式 |
| `last_input` | 最近一次采样时，该中断输入是否有效；值为 0 或 1 |
| `eoi_count` | 选定 IRQ 进入 EOI 函数的次数 |
| `active_count` | 电平中断输入有效、进入重触发分支的次数 |
| `inactive_count` | 电平中断输入无效、跳过重触发的次数 |
| `retrigger_count` | 执行 `setipnum_le` 写入后的计数 |

逻辑 IRQ 是 RT-Thread 管理中断描述符的编号，hwirq 是 APLIC 的中断源编号。
GDB 选择器使用逻辑 IRQ，寄存器位定位及重触发写入使用 hwirq。

函数开始时计算：

```c
rt_bool_t observe = (pirq->irq == aplic_eoi_debug.irq);
```

只有编号匹配时，才记录 hwirq、模式并增加 `eoi_count`。
此时函数尚未完成重触发判断，因此应等本次 EOI 执行结束后再比较各计数。

对于高、低电平中断，原修复代码读取 `in_clrip`。
每个寄存器包含 32 个中断源的状态，`hwirq / 32` 选择寄存器，
`hwirq % 32` 选择其中的位。

新增代码保存目标位：

```c
aplic_eoi_debug.last_input =
        !!(input & RT_BIT(pirq->hwirq % APLIC_IRQBITS_PER_REG));
```

`!!` 将结果转为 0 或 1。这里表示考虑极性后的有效输入状态：
低电平模式下，物理低电平有效也对应 `last_input=1`。
它是本次采样值，不代表之后设备状态不会改变。

输入有效分支的顺序为：

```text
active_count 加一
  → 写 setipnum_le
  → retrigger_count 加一
```

输入无效时，仅增加 `inactive_count`，不执行重触发写入。
`retrigger_count` 证明代码执行了寄存器写入；还需再次进入 ISR，
才能支持“重触发已送达”的判断。

对已执行完成的电平中断 EOI，在未清零且计数未溢出时应满足：

```text
eoi_count = active_count + inactive_count
active_count = retrigger_count
```

其他触发模式也可能增加 `eoi_count`，但不进入这两个电平分支，
因此第一条关系不适用于其他触发模式。

### 3.2 virtio-mmio ISR 观测结构体

```c
static volatile struct
{
    int irq;
    rt_uint32_t last_status;
    rt_atomic_t isr_count;
    rt_atomic_t status_nonzero_count;
    rt_atomic_t status_zero_count;
    rt_atomic_t ack_count;
    rt_atomic_t handled_count;
} virtio_mmio_irq_debug = { .irq = -1 };
```

| 字段 | 含义 |
| --- | --- |
| `irq` | 选定的逻辑 IRQ；`-1` 关闭统计 |
| `last_status` | 最近一次 ISR 在 ACK 前读取到的设备中断状态 |
| `isr_count` | ISR 读取设备状态后执行观测代码的次数 |
| `status_nonzero_count` | 读取的设备状态非零的次数 |
| `status_zero_count` | 读取的设备状态为零的次数 |
| `ack_count` | 执行设备 ACK 寄存器写入后的计数 |
| `handled_count` | ISR 执行到末尾的次数 |

设备状态非零，表示读取时有待确认的中断状态；状态为零，表示已经进入 ISR，
但读取时没有待确认状态。持续增长的零状态 ISR 可以作为虚假中断线索，
但偶发一次不能直接归因于 EOI，还需考虑在途中断和并发事件。

`last_status` 是 ACK 前保存的历史值。ACK 后即使设备状态已清零，
它仍可能保持为 `1`，不能把它当成当前设备寄存器值。

`ack_count` 只统计 ACK 写入。原代码在 `status=0` 时也会写 ACK，
因此它不等于确认的真实事件数。

`handled_count` 只表示 ISR 正常走到末尾，不能当成磁盘请求完成数：
一次 ISR 可以处理多个队列事件，零状态 ISR 也可能走到末尾。

### 3.3 原子计数、默认关闭与读取规则

`static` 让变量保留在当前 C 文件内部，并在整个运行期间存在；
带调试符号编译后，GDB 可以访问它。

`volatile` 要求编译器保留对调试字段的访问，但本身不保证并发安全。
计数器使用 `rt_atomic_t` 和 `rt_atomic_add()`，避免多 CPU 同时递增时丢失计数。

两处选择器默认均为 `-1`，其他字段初始化为零。启用时必须选择同一个逻辑 IRQ：

```gdb
set var aplic_eoi_debug.irq = $irq
set var virtio_mmio_irq_debug.irq = $irq
```

所有选择器修改、计数读取和清零，都应在 GDB 默认 all-stop 模式下暂停全部 CPU 后执行。
多个字段整体并非原子快照；尽量在本次 ISR/EOI 完成后读取，以免看到中间状态。
不要启用 GDB non-stop 模式执行本文操作。

将选择器设回 `-1` 只停止后续统计，不清零；再次选择 IRQ 会继续累加。
重新启动虚拟机可以恢复初始状态，也是两组独立测试推荐的清零方式。

## 4. virtio 配置变化与队列处理代码说明

设备 ACK 后，原 ISR 根据先前保存的 `status` 执行：

```c
if (status & VIRTIO_MMIO_INT_CONFIG)
{
    rt_virtio_device_config_changed(&vio->parent);
}

if (status & VIRTIO_MMIO_INT_VIRTQ)
{
    struct rt_virtqueue *vq;
    rt_ubase_t level = rt_spin_lock_irqsave(&vio->spinlock);

    rt_list_for_each_entry(vq, &vio->parent.vq_node, list)
    {
        rt_virtqueue_isr(irqno, vq);
    }

    rt_spin_unlock_irqrestore(&vio->spinlock, level);
}
```

`VIRTIO_MMIO_INT_CONFIG` 表示设备配置变化通知。
`rt_virtio_device_config_changed()` 将通知交给对应设备驱动，
与通过 GDB 修改调试选择器无关。

`VIRTIO_MMIO_INT_VIRTQ` 表示设备至少在一个 virtqueue 中放入了已使用的缓冲区。
以磁盘读请求为例：驱动提交请求，QEMU 处理并更新 used ring，随后产生中断，
驱动通过队列处理逻辑检查完成情况。

该状态位不直接标识具体队列，因此 ISR 遍历设备的全部 virtqueue，
调用 `rt_virtqueue_isr()`，交由对应队列回调处理。
块设备可通知等待请求完成的线程，网络设备可处理收包或发送完成通知。

`rt_spin_lock_irqsave()` 保存并关闭本地中断，同时获取自旋锁，
协调其他使用同一把锁的 CPU；处理结束后释放锁并恢复之前的本地中断状态。
两个条件使用独立的 `if`，同一次中断可以同时处理配置变化和队列事件。

ACK 是确认设备通知，上述代码负责处理通知对应的工作。
因此后面的提前返回测试会同时跳过 ACK 和实际队列处理，
由重触发后的下一次 ISR 正常完成这些工作。

## 5. 编译与调试环境准备

### 5.1 终端 A：编译并启动 QEMU

退出使用相同调试端口的旧 QEMU 实例，再执行：

```sh
cd /home/tengzijun/rt-thread/bsp/qemu-virt64-riscv
scons -j8

testdir=$(mktemp -d /tmp/rtt-eoi-test.XXXXXX)
qemu-img create -f qcow2 -F qcow2 \
    -b "$PWD/virtio.qcow2" "$testdir/disk.qcow2"

python3 qemu.py -debug \
    -no-net -no-nvme -no-virtio-console -no-pci-serial \
    -block "$testdir/disk.qcow2"
```

本环境默认工具链可直接执行 `scons -j8`。
若需要明确指定工具链，使用原问题记录中的 `RTT_EXEC_PATH`、`RTT_CC_PREFIX` 设置。
编译后的 `rtthread.bin` 与 GDB 使用的 `rtthread.elf` 必须来自同一次构建。

覆盖层将测试写入放在临时文件中，后备磁盘应保持不变；不要在测试期间让其他实例
修改同一个后备磁盘。临时磁盘、日志和编译产物不提交到仓库。

RV64 下脚本默认保留 AIA，不应添加 `-no-aia` 或 `-no-msi`。
不添加 `-pci`，以便经过本次观测的 virtio-mmio 路径。
`-debug` 暂停启动并开放 GDB 端口 `1234`，等待调试器连接。

首次调试时，受限执行环境曾报 `Failed to create a socket: Operation not permitted`
及 GDB `could not connect: Operation not permitted`。
当时经授权在允许创建、连接本机调试套接字的环境中完成测试，未修改驱动绕过限制。

### 5.2 终端 B：连接 GDB，选择块设备

```sh
cd /home/tengzijun/rt-thread/bsp/qemu-virt64-riscv
gdb-multiarch -q rtthread.elf
```

以下命令均在 GDB 中执行：

```gdb
set pagination off
set confirm off
target remote :1234

break virtio_mmio_isr if *(unsigned int *)(((struct virtio_mmio *)param)->base + 8) == 2
continue
```

条件读取 virtio-mmio 基址偏移 `0x008` 的设备 ID，值 `2` 选择块设备。
启动过程中的磁盘访问即可触发，无需额外提交请求。

本文假设使用全新 GDB 会话且没有其他用户断点：上述断点编号为 `1`。
如果编号不同，先执行 `info breakpoints`，后文的 `disable`、`enable` 编号相应替换。

在函数入口停住后，尚未执行 `observe` 的初始化，此时设置选择器：

```gdb
set $irq = irqno
set var aplic_eoi_debug.irq = $irq
set var virtio_mmio_irq_debug.irq = $irq

p $irq
p _pirq_hash[$irq].hwirq
p _pirq_hash[$irq].mode
```

`$irq` 是 GDB 方便变量，保存本次逻辑 IRQ。`_pirq_hash` 是当前实现的中断描述表，
这里只读取，不修改。实际测试读到逻辑 IRQ `333`、hwirq `8`。

不要等 `observe` 已计算完成后才启用计数，否则当前 ISR 可能不被统计。

### 5.3 停在设备 ACK 之前

```gdb
disable 1
tbreak components/drivers/virtio/virtio_mmio.c:157 if ((struct virtio_mmio *)param)->irq == $irq
continue

p status
p virtio_mmio_irq_debug
```

`disable 1` 暂时关闭入口断点。`tbreak` 是命中一次后自动删除的临时断点，
在全新会话中编号为 `2`。

记录时的第 `157` 行为：

```c
virtio_mmio_write32(vio, VIRTIO_MMIO_INTERRUPT_ACK, status);
```

断点停在执行这行之前，此时已读取并统计设备状态，但尚未写 ACK，也未获取队列锁。
若源码行号变化，必须先找到这条语句，替换断点行号。

条件通过 `param` 读取设备 IRQ，是因为实际调试中在该位置直接使用 `irqno`
曾出现 `value has been optimized out`；函数入口处读取 `irqno` 则可用。

首次受控请求预期：

```text
status 非零（本次观察为 1）
isr_count = 1
status_nonzero_count = 1
status_zero_count = 0
ack_count = 0
handled_count = 0
```

若状态为零，不应将该次用于“保留真实设备中断”的测试，应重新捕获真实事件。

## 6. 第二步：验证输入仍有效时 EOI 能重触发

### 6.1 仅让第一次 ISR 提前返回

在上述 ACK 前断点处执行：

```gdb
return

break aplic_msi_irq_eoi if pirq->irq == $irq
continue
```

GDB 的 `return` 强制当前 `virtio_mmio_isr()` 返回到调用者，
不执行 ACK、配置变化处理、队列处理和末尾计数。
此时尚未进入队列锁区，不能在已经持锁的位置照搬该操作。

因为设备通知未被确认，中断输入应保持有效。
这是一项单次调试注入，不修改源码中的 ISR 行为。
`set confirm off` 已关闭确认提示，`return` 会直接执行。

新建的 EOI 断点在本文会话中编号为 `3`。命中后：

```gdb
finish
p aplic_eoi_debug
```

`finish` 运行到当前函数返回，确保本次 EOI 分支和计数均已执行完成。
预期：

```text
eoi_count       = 1
last_input      = 1
active_count    = 1
inactive_count  = 0
retrigger_count = 1
```

这些值说明：EOI 采样到输入有效，并执行了一次重触发写入。
还不能只凭这一步认定中断已送达。

### 6.2 捕获重触发后的第二次 ISR

```gdb
enable 1
continue
```

预期再次停在同一个块设备的 `virtio_mmio_isr()` 入口，逻辑 IRQ 与 `$irq` 一致。
第一次 ISR 没有处理队列，也没有完成对应请求，此处再次进入 ISR 是重触发送达的关键证据。
测试期间不主动提交其他请求，以减少新事件对判断的干扰。

这次不再执行 `return`，让设备正常 ACK 并处理队列：

```gdb
disable 1
continue
```

随后应命中同一 IRQ 的 EOI 断点 `3`。执行：

```gdb
finish
p aplic_eoi_debug
p virtio_mmio_irq_debug
```

预期计数：

| 结构体 | 字段 | 预期值 |
| --- | --- | ---: |
| `aplic_eoi_debug` | `eoi_count` | 2 |
| `aplic_eoi_debug` | `active_count` | 1 |
| `aplic_eoi_debug` | `inactive_count` | 1 |
| `aplic_eoi_debug` | `retrigger_count` | 1 |
| `aplic_eoi_debug` | `last_input` | 0 |
| `virtio_mmio_irq_debug` | `isr_count` | 2 |
| `virtio_mmio_irq_debug` | `status_nonzero_count` | 2 |
| `virtio_mmio_irq_debug` | `status_zero_count` | 0 |
| `virtio_mmio_irq_debug` | `ack_count` | 1 |
| `virtio_mmio_irq_debug` | `handled_count` | 1 |

EOI 总数为 2，只有第一次执行重触发；设备 ACK 后，第二次 EOI 的输入为 0，
重触发总数保持为 1。这组结果在首次手工验证中实际观察到。

### 6.3 让系统继续运行，检查静默状态

```gdb
disable 3
continue
```

等待系统启动结束、应用打印到 `9`，在 GDB 终端按 Ctrl+C 暂停，再执行：

```gdb
p aplic_eoi_debug
p virtio_mmio_irq_debug
p _cpus[0].tick
continue
```

继续运行约 10 秒，再按 Ctrl+C，重复读取。判断标准：

- 没有新的设备事件时，目标中断的计数保持稳定。
- `retrigger_count` 没有无故增长。
- 没有持续增长的 `status_zero_count`。
- CPU0 tick 继续推进，应用延时和打印正常。

启动期间还可能发生其他磁盘访问，最终总数不必停在 2。
不要要求每个请求严格对应一次中断：设备可合并通知，也可能存在在途通知。

## 7. 第三步：独立验证正常 ACK 后不产生多余重触发

退出上一组测试，重新启动 QEMU 和全新 GDB，会话及计数从零开始。
重复第 5 节操作，直到停在 ACK 前的临时断点。

**本组不执行 `return`。** 直接设置 EOI 断点并继续：

```gdb
break aplic_msi_irq_eoi if pirq->irq == $irq
continue
finish

p aplic_eoi_debug
p virtio_mmio_irq_debug
```

设备 ISR 将正常 ACK 并处理队列。对于没有并发新事件的本次受控处理，预期：

```text
EOI：
  eoi_count       = 1
  active_count    = 0
  inactive_count  = 1
  retrigger_count = 0
  last_input      = 0

设备 ISR：
  isr_count       = 1
  ack_count       = 1
  handled_count   = 1
  status_zero_count = 0
```

随后执行：

```gdb
disable 3
continue
```

应用打印到 `9` 后，按第 6.3 节方法做两次静默采样。
通过标准是计数稳定、无持续虚假 ISR，CPU0 tick 继续推进。
如果 EOI 期间设备确有新事件，输入有效并产生必要重触发不应被误判为失败。

测试结束，在 GDB 中执行 `detach`、`quit`；在 QEMU 终端依次按 Ctrl+A、X 退出。

## 8. 首次手工验证记录

首次测试仅对一个事件故意跳过 ACK，观察到第 6 节的预期计数。
继续启动后，设备还有正常磁盘事件，最终两次静默采样均为：

```text
EOI：总数 4，有效 1，无效 3，重触发 1
ISR：总数 4，ACK 3，正常结束 3，零状态 0
```

其中唯一一次未 ACK，是人为提前返回的 ISR。应用完整打印 `0` 到 `9`。
这组结果与下面独立三轮测试的计数不同，因为注入次数不同。

## 9. 后续三轮实际验证结果

后续分别运行“保留电平”和“正常 ACK”两组独立实例，每组观察三个磁盘请求。
保留电平组对每个请求的第一次 ISR 均在 ACK 前提前返回；
第二次 ISR 正常处理。正常 ACK 组不注入提前返回。

除读取观测计数外，还通过 GDB 跟踪 `virtio_blk_request()` 的实际返回结果。
SMP 下请求线程可能迁移 CPU，最终采用函数返回指令处断点读取返回寄存器的方式，
避免只依赖绑定原执行线程的返回断点。两组请求均返回 `0`，表示成功。

| 观测项 | 保留电平组 | 正常 ACK 组 |
| --- | ---: | ---: |
| 请求开始数 | 3 | 3 |
| 请求完成数 | 3 | 3 |
| 请求返回值 | `0, 0, 0` | `0, 0, 0` |
| ISR 次数 | 6 | 3 |
| EOI 次数 | 6 | 3 |
| 输入有效次数 | 3 | 0 |
| 输入无效次数 | 3 | 3 |
| 重触发写入次数 | 3 | 0 |
| 设备 ACK 次数 | 3 | 3 |
| ISR 正常结束次数 | 3 | 3 |
| 设备状态为零的 ISR 次数 | 0 | 0 |

保留电平组每轮 EOI 累计结果：

| 观测位置 | EOI 总数 | 输入有效 | 输入无效 | 重触发 |
| --- | ---: | ---: | ---: | ---: |
| 第 1 轮不 ACK 后 | 1 | 1 | 0 | 1 |
| 第 1 轮正常 ACK 后 | 2 | 1 | 1 | 1 |
| 第 2 轮不 ACK 后 | 3 | 2 | 1 | 2 |
| 第 2 轮正常 ACK 后 | 4 | 2 | 2 | 2 |
| 第 3 轮不 ACK 后 | 5 | 3 | 2 | 3 |
| 第 3 轮正常 ACK 后 | 6 | 3 | 3 | 3 |

每次输入有效后都再次进入同一设备 ISR，每次正常 ACK 后重触发计数保持不变。
三个请求最终均完成，没有仅凭 ISR 次数推断请求成功。

静默后两次采样中，两组各自的中断计数完全相同。CPU0 tick 分别为：

- 保留电平组：`2645 → 3983`。
- 正常 ACK 组：`83 → 3477`。

两组应用均完整打印 `RISC-V test: 0` 到 `RISC-V test: 9`。
测试启动日志也报告原磁盘的根文件系统挂载失败，因此这里的成功结果只指
块设备请求完成及中断路径验证，不表示文件系统挂载或文件读写验证通过。

本次未额外修改仓库代码，结束时测试实例均已退出。

当时脚本、日志和 JSON 结果保存于 `/tmp/rtt-eoi-validation.EiRTun/`，
包括 `check.gdb`、`retrigger.json`、`normal.json` 及对应日志。
文档整理时该临时目录已不存在；上述数值依据会话中保留的执行输出记录，
不能再依赖这些临时路径下载原始附件。

## 10. 结论及尚未验证的范围

当前受控测试支持以下结论：设备输入仍有效时，兼容修改保留了 EOI 重触发能力，
后续 ISR 能正常处理并完成请求；设备正常撤销中断后，EOI 跳过重触发写入，
静默后未观察到持续虚假中断。

本次为每组三个请求的定向测试，不是高负载压力测试，也未覆盖所有时序窗口。
要进一步验证读取 `in_clrip` 前后电平恰好变化的竞态，需要 QEMU 侧可控事件注入或跟踪。
真实 APLIC、低电平外设、其他模拟器版本及长期并发负载仍需单独验证。
