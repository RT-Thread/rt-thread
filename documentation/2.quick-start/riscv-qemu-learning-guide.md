# RISC-V RT-Thread：从 QEMU 运行到理解与维护

按“先在电脑上运行起来，再理解代码，最后尝试维护”的顺序学习。第一步是在电脑上运行 RISC-V 版 RT-Thread，第二步是理解它怎么运行，第三步才是修复问题和维护支持。暂时不需要买开发板。

本文命令按仓库路径 `/home/tengzijun/rt-thread` 编写。如果仓库位置变化，请替换相应路径。

此前环境检查记录：

- SCons：用来编译 RT-Thread。
- RISC-V GCC 13.2：把 C 和汇编代码编译成 RISC-V 程序。
- QEMU 8.2.2：在电脑上模拟 RISC-V 开发板。

以上是此前检查时的环境信息；本文整理时未实际编译、运行或修改配置。环境与配置可能随后续操作变化。

## 一、先理解几个名称

| 名称 | 可以这样理解 |
|---|---|
| RISC-V | CPU 使用的一套指令规则 |
| RV32 / RV64 | 32 位和 64 位 RISC-V |
| RT-Thread | 运行在 CPU 上的操作系统 |
| BSP | 让操作系统适配某块开发板所需的代码 |
| QEMU | 用软件模拟开发板，因此暂时不需要真实硬件 |
| 架构移植层 | 把线程切换、中断等操作转换成 RISC-V CPU 能执行的代码 |

你现在要搭建的运行关系是：

```text
你的电脑
  └─ QEMU 模拟的 RISC-V 开发板
       └─ RT-Thread
            └─ 测试程序
```

## 二、第一次编译：先保持现有配置

打开终端，进入仓库：

```bash
cd /home/tengzijun/rt-thread
git status --short
```

没有输出，表示 Git 没有检测到修改。如果有输出，先保留这些改动，不要执行清理或还原命令。

进入 QEMU 的 RISC-V BSP：

```bash
cd /home/tengzijun/rt-thread/bsp/qemu-virt64-riscv
```

这个目录就是你的第一个实验工程。

设置工具链：

```bash
export RTT_EXEC_PATH=/usr/bin
export RTT_CC_PREFIX=riscv64-unknown-elf-
```

这两行告诉编译系统：“去 `/usr/bin` 找以 `riscv64-unknown-elf-` 开头的编译工具”。它们只对当前终端及其启动的程序生效。

根据已有 `.config` 生成配置头文件：

```bash
scons --pyconfig-silent
```

这里两个文件的关系是：

```text
.config：保存配置选项
    ↓ 配置工具生成
rtconfig.h：供 C 和汇编代码使用
```

不要手工修改 `rtconfig.h`。

然后编译：

```bash
scons -j$(nproc)
```

`-j$(nproc)` 表示使用多个 CPU 核并行编译。

成功后应该得到：

```text
rtthread.elf
rtthread.bin
```

- `rtthread.elf` 带有调试所需的信息。
- `rtthread.bin` 是启动脚本使用的内核镜像。

如果编译失败，先停在这里处理。可以重新执行：

```bash
scons -j1
```

单任务编译更容易看清错误。记录第一处错误以及前后约 20 行输出，最后一句“编译失败”通常不能说明原因。

## 三、第一次启动：看到 RT-Thread 命令行

在同一个 BSP 目录执行：

```bash
python3 qemu.py -no-aia -no-net -no-nvme -no-virtio-console -no-pci-serial
```

这组参数使用 PLIC/CLINT 中断路径，并关闭几个暂时用不到的设备，减少第一次运行时需要排查的因素。脚本仍可能创建虚拟磁盘文件，这是本地运行产物。

此前检查的 `.config` 使用 RV64、4 核、标准版 RT-Thread。第一次先保持现有配置，启动脚本会读取配置中的核数。

启动后，预期能看到 RT-Thread 启动信息、类似：

```text
Hello RISC-V
```

以及命令提示符：

```text
msh />
```

看到提示符后输入：

```text
help
```

这里输入的是 RT-Thread 命令，不是 Linux 命令。可以先通过 `help` 查看有哪些可用命令，再尝试其中的线程、内存查看命令。

退出 QEMU 的常用按键是：先按 `Ctrl+A`，松开，再按 `X`。

这一阶段的完成标准：能启动，能输入命令，系统持续运行。

## 四、做一个能亲眼看到效果的小实验

先打开 [applications/main.c](../../bsp/qemu-virt64-riscv/applications/main.c)。原示例主要就是打印：

```c
rt_kprintf("Hello RISC-V\n");
```

可以把 `main()` 临时改成：

```c
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

保存后，重新编译：

```bash
scons -j$(nproc)
```

再用上面的 QEMU 命令启动。

预期结果：每隔大约一秒打印一次数字，打印十次结束。

这个实验可以初步检查：

- 你的代码确实被编译并运行了。
- 系统时钟在工作。
- 线程延时后可以再次被调度运行。

它还不能证明整个 RISC-V 移植完全正确，但能帮你建立“修改 → 编译 → 运行 → 观察”的基本流程。

## 五、学习配置工具，并切换到单核

跑通现有配置后，再做一次配置实验：

```bash
scons --menuconfig
```

常见操作是：

- 上下方向键：移动。
- `Enter`：进入菜单。
- 空格：开关选项。
- `/`：搜索配置项。
- 退出时选择保存。

搜索 `RT_USING_SMP`。它表示“是否启用多核调度”。找到对应菜单中的 `Enable SMP (Symmetric multiprocessing)`，关闭后保存退出。

重新编译：

```bash
scons -j$(nproc)
```

再使用相同的 QEMU 启动命令。脚本会根据生成后的配置决定启动核数；不要单独添加一个与内核配置不同的 `-smp` 数值。

这样，你就完成了第一个配置对比：

```text
原来的四核运行 → 修改配置 → 单核运行
```

学习阶段建议先在单核配置下理解调度和中断，再回到多核。

## 六、运行仓库已有的内核测试

你不需要一开始就自己写测试。当前仓库已经有 utest 测试框架。

再次执行：

```bash
scons --menuconfig
```

搜索 `RT_USING_UTESTCASES`，启用 RT-Thread Utestcases，然后查看其中由 [src/utest/Kconfig](../../src/utest/Kconfig) 提供的内核测试选项。

第一次只选少量基础测试，例如线程、信号量、定时器相关的项目，具体以菜单显示为准。保存后重新编译、启动。

在 RT-Thread 的 `msh />` 提示符下执行：

```text
utest_list
```

它会列出已经编译进来的测试。

查看运行方法：

```text
utest_run -help
```

先运行一个测试：

```text
utest_run 实际测试名称
```

其中“实际测试名称”要替换成 `utest_list` 列出的名字。

也可以执行：

```text
utest_run
```

运行所有已启用的测试。

如果提示没有 `utest_run` 命令，优先检查是否启用了测试配置，以及是否重新编译、重新启动了新镜像。

这一阶段的完成标准：能列出测试、执行测试、看懂成功或失败结果。

## 七、按照执行顺序阅读代码

等前面的操作熟悉后，再开始读移植代码。不要一次阅读整个 `libcpu/risc-v`。

先读 [公共移植指南](../../libcpu/risc-v/common/README.md)，然后按下面的顺序阅读：

| 顺序 | 文件 | 阅读时要回答的问题 |
|---|---|---|
| 1 | `common/startup_gcc.S`、`common/startup.c` | CPU 启动后，怎么进入 RT-Thread？ |
| 2 | [bsp/qemu-virt64-riscv/driver/board.c](../../bsp/qemu-virt64-riscv/driver/board.c) | 内存、串口、中断等如何初始化？ |
| 3 | `common/stack.c` | 一个新线程运行前，初始寄存器状态如何准备？ |
| 4 | `common/context_gcc.S` | 切换线程时，怎样保存旧线程并恢复新线程？ |
| 5 | `common/vector_gcc.S`、`common/trap.c` | CPU 遇到中断或异常后进入哪里？ |
| 6 | `common/riscv_timer.c` | 系统时钟中断如何产生？ |

表中 `common/` 都指向：

```text
/home/tengzijun/rt-thread/libcpu/risc-v/common/
```

读代码前，先理解三个概念：

- 寄存器：CPU 当前正在使用的数据和运行状态。
- 线程栈：保存函数调用信息，也用于保存线程现场。
- 上下文切换：保存线程 A 的状态，再恢复线程 B 的状态，让 B 接着执行。

对于前面的延时实验，你可以带着这个问题读代码：

> main 线程延时一秒后，CPU 去运行了什么？一秒后又是谁让它继续运行？

能沿着代码解释这个过程，就已经开始理解架构移植了。

## 八、开始做真正的维护

有了运行和测试能力后，每次维护都按同一套步骤：

1. 描述问题：哪个配置、执行什么操作、出现什么现象。
2. 复现问题：修改代码前，确认问题确实存在。
3. 定位层次：是公共架构代码、板级代码，还是配置或工具链问题。
4. 做最小修改：一个改动解决一个明确问题。
5. 重新验证：确认原问题消失，同时运行相关测试。
6. 检查差异：确认没有夹带无关修改和生成文件。

提交前查看：

```bash
git diff --check
git diff
git status --short
```

PR 描述至少写清：

```text
问题：什么情况下会出错
原因：为什么会出错
修改：修改了什么
验证：使用哪个 BSP、配置和工具链，运行了哪些测试
```

当前仓库同时保留新公共实现和旧移植路径，具体由 `RT_USING_RISCV_NEW_COMMON` 控制。修复问题前，要确认目标 BSP 实际编译的是哪条路径。

你现在先完成第二、三步就够了：编译出镜像，并进入 `msh />`。成功后再做打印实验；失败时保留第一处错误输出，按实际问题继续排查。
