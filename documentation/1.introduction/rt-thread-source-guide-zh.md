# RT-Thread 源码结构与 RISC-V 维护学习笔记

本文面向希望阅读 RT-Thread 源码，并逐步参与 RISC-V 支持维护的开发者。具体编译配置、功能和实现以所选 BSP 及其 `.config` 为准。

## 1. 从整体看工程

RT-Thread 由实时内核、CPU 移植层、板级支持包和可选组件组成。它们的关系可以概括为：

```text
应用程序
    ↓
components/  设备框架、命令行、文件系统、网络等可选功能
    ↓
src/         线程、调度、定时器、线程间通信、内存管理等内核实现
    ↓
libcpu/      CPU 架构相关的启动、异常和上下文切换等实现
    ↓
bsp/         具体板卡的内存布局、硬件初始化和外设驱动
```

| 目录 | 主要内容 | 阅读入口 |
| --- | --- | --- |
| `include/` | 内核接口声明、类型、宏和数据结构 | `include/rtthread.h`、`include/rtdef.h` |
| `src/` | 内核主体 | `src/components.c`、`src/thread.c`、`src/scheduler_up.c`、`src/ipc.c` |
| `libcpu/` | ARM、RISC-V 等 CPU 架构的移植代码 | `libcpu/risc-v/` |
| `bsp/` | 开发板及模拟器的板级支持包 | `bsp/qemu-virt64-riscv/` |
| `components/` | 可按需选择的系统组件 | `components/drivers/`、`components/finsh/`、`components/dfs/` |
| `examples/` | 示例程序 | 按所学功能选择 |
| `tools/` | 构建辅助脚本 | `tools/building.py` |
| `documentation/` | 入门、内核和组件文档 | `documentation/3.kernel/` |

目录中存在某个功能，并不意味着每个 BSP 都把它编入固件。应结合配置文件和构建脚本判断实际使用的代码。

## 2. `include/` 是给谁用的？

内核、BSP、组件和应用程序都可能包含 `include/` 中的头文件。头文件主要提供声明；对应实现通常在 `src/`、`libcpu/` 或 `components/` 中。`include/` 并非全是面向应用的稳定接口。

| 文件 | 作用及常见使用者 |
| --- | --- |
| `rtthread.h` | 应用最常用的内核接口入口，也供内核及组件使用；声明线程、定时器、信号量等 API |
| `rtdef.h` | 基本类型、内核对象、线程结构和宏；通常由 `rtthread.h` 间接包含 |
| `rthw.h` | 中断、上下文切换、缓存等硬件相关接口；主要供移植层和驱动使用 |
| `rtsched.h` | 调度器相关结构与接口，其中包含不应由普通应用直接操作的成员 |
| `rtdbg.h` | 调试日志接口 |

普通应用一般从 `#include <rtthread.h>` 和文档化的 `rt_thread_*`、`rt_sem_*` 等 API 开始。维护 RISC-V 移植时，再重点研究 `rthw.h`、`rtsched.h` 与 `libcpu/risc-v/` 的实现关系。能够包含某个头文件，不代表应该直接修改线程结构中的调度器状态。

## 3. `libcpu/` 中的“CPU 架构相关代码”

内核可以用通用逻辑决定“切换到哪个线程”，但保存寄存器、切换栈、进入异常处理程序和从异常返回都依赖 CPU 的指令集与寄存器约定。这些差异由 `libcpu/` 承担。

以 `libcpu/risc-v/common/` 为例：

| 文件 | 主要职责 |
| --- | --- |
| `startup_gcc.S`、`startup.c` | 启动入口及早期初始化 |
| `context_gcc.S`、`stack.c` | 线程上下文切换和初始线程栈 |
| `vector_gcc.S`、`trap.c` | 异常与中断入口、处理 |
| `riscv_timer.c` | RISC-V 平台的时钟节拍相关实现 |
| `sbi.c`、`mmu.c` | 按配置提供 SBI 和内存管理单元支持 |

`libcpu/` 解决架构层共性；`bsp/` 解决具体板卡差异，例如内存地址、设备树、时钟和外设。两者有接口配合，定位问题时应先确定它属于哪一层。

## 4. `components/` 给工程带来什么？

组件在内核基本能力之上提供可复用的系统功能，应用无需自行实现整套设备、文件或网络框架。

| 组件 | 提供的能力 |
| --- | --- |
| `components/drivers/` | 统一设备接口及通用驱动框架，例如 `rt_device_*` |
| `components/finsh/` | 交互式命令行，便于观察状态和执行调试命令 |
| `components/dfs/` | 文件系统及文件、目录操作接口 |
| `components/net/` | 网络相关功能 |
| `components/utilities/ulog/` | 日志记录功能 |
| `components/libc/`、`components/lwp/` | 按配置提供 C 库兼容层、轻量级进程等能力 |

组件通常由 Kconfig 选项控制，并由相应的 `SConscript` 加入构建。查看具体 BSP 的 `.config`，才能确定当前固件启用了什么。

### `components/` 和 `bsp/` 有什么区别？

`components/` 面向多个板卡都能使用的能力；`bsp/` 面向某块具体开发板或模拟器的硬件条件。两者通常配合使用：

| 场景 | `components/` 提供 | `bsp/` 提供 |
| --- | --- | --- |
| 使用串口 | 通用串口设备框架和统一的设备访问接口 | 该板的串口寄存器地址、中断号、时钟以及硬件操作 |
| 使用文件系统 | DFS 的文件和目录接口 | 存储设备及其板级连接、初始化与驱动适配 |
| 使用命令行 | FinSH 的命令解析和交互能力 | 可用于输入输出的控制台设备及其硬件驱动 |

判断代码归属时，可以问“换一块板子后，这段代码是否仍能复用”。通用机制通常放在组件或通用驱动层；写明特定寄存器地址、引脚或中断连接的代码通常放在 BSP。具体工程还需以现有目录和构建关系为准。

### 单片机为什么可能需要这些组件？

RT-Thread 既可裁剪用于资源受限的 MCU，也可用于存储和外设更丰富的设备。组件解决的是应用需求，并不是每个单片机工程的必需品。

| 功能 | 嵌入式设备中的用途 | 可以不启用的情况 |
| --- | --- | --- |
| FinSH 命令行 | 通过串口执行调试命令、查看线程与设备状态 | 功能简单，且无交互或现场调试需求 |
| DFS 文件系统 | 在 SD 卡、Flash 等存储设备上组织配置、日志或采集数据 | 只保存少量固定数据，直接读写存储区域已足够 |
| 设备框架 | 通过相对统一的接口访问串口、SPI、I²C 等设备，便于驱动和应用配合 | 极小工程只使用少量外设，并采用直接的板级驱动接口 |

例如，一个定时读取传感器并控制 LED 的小 MCU 工程，可能只需要内核和少量驱动；一个带 SD 卡、网络和多个传感器的设备，则可能用到文件系统、网络和命令行。FinSH 是嵌入式系统中的可选交互工具，不要求设备具备桌面操作系统那样的终端环境。最终固件包含哪些功能，仍由 BSP 配置和构建脚本决定。

## 5. `examples/` 是给谁看的？

`examples/` 主要面向使用 RT-Thread 开发应用的人，包括单片机开发者。它展示如何调用已有的内核或组件接口，例如 `examples/network/` 中的网络通信示例、`examples/file/` 中的文件操作示例，以及 `examples/ulog/` 中的日志示例。`examples/test/` 还包含功能测试和性能测试代码，维护人员也可以参考。

示例的侧重点是**如何使用功能及观察运行结果**，不是解释实现原理。例如，两个线程的示例能帮助观察调度结果；要理解线程状态与调度算法，应继续阅读 `src/thread.c` 和 `src/scheduler_up.c`。文件操作示例展示文件 API；要理解其实现，应阅读 `components/dfs/`。

| 学习目标 | 优先阅读位置 |
| --- | --- |
| 线程、设备、文件或网络 API 如何使用 | `examples/` |
| 内核如何调度和管理线程 | `src/` 中的线程与调度代码 |
| 组件如何实现设备、文件或网络接口 | `components/` 中相应组件的源码 |
| RISC-V 如何保存寄存器、处理异常和切换线程 | `libcpu/risc-v/`，并结合目标 BSP |

示例不一定自动编入当前 BSP，也不一定能在每块板子上运行。运行前应确认其依赖的组件、配置和硬件条件。维护 RISC-V 时，可以把示例作为复现问题的运行场景，再沿“示例 API → 内核或组件 → `libcpu/` 与 BSP”的路径定位原因。

### 例子：`examples/libc/file.c` 调用了哪些接口？

这个例程直接调用的 RT-Thread 内核 API 只有 `rt_thread_delay()`。文件中的 `sleep(int tick)` 是它自己定义的包装函数，后面的 `sleep(1)` 表示延时一个系统 tick，不是 POSIX `sleep()` 所表示的一秒。

| 调用 | 所属层次 | 用途 |
| --- | --- | --- |
| `rt_thread_delay()` | RT-Thread 内核 API | 让当前线程延时 |
| `open()`、`write()`、`lseek()`、`fstat()`、`close()`、`unlink()` | POSIX 风格文件接口 | 创建、写入、定位、查询与删除文件 |
| `fopen()`、`fdopen()`、`fread()`、`fwrite()`、`fseek()`、`fseeko()`、`fclose()` 等 | C 库文件流接口 | 测试带缓冲的文件读写与定位 |
| `getenv()`、`mkstemp()`、`asprintf()`、`printf()` 等 | C 库及扩展接口 | 生成临时文件名、输出结果及辅助操作 |
| `FINSH_FUNCTION_EXPORT(...)` | FinSH 组件的注册宏 | 将测试函数注册为可调用的命令 |

`libc_fstat()` 的主要调用顺序是 `open → write → lseek → fstat → close`；`libc_fseek()` 则集中测试文件流的读写、定位和文件状态。文件操作在相应配置下可通过 C 库适配层进入 DFS，例如 `components/dfs/dfs_v2/src/dfs_posix.c` 中实现了部分 POSIX 风格接口；实际路径取决于所选 C 库和 DFS 配置。`examples/libc/SConscript` 要求启用 `RT_USING_NEWLIBC` 和 `RT_USING_PTHREADS` 才会将该目录的例程纳入对应构建。

## 6. 沿启动流程阅读内核

以启用 `RT_USING_USER_MAIN` 的工程为例，`src/components.c` 中的主要流程是：

```text
CPU / BSP 启动入口
    → rtthread_startup()
    → rt_hw_board_init()              板级初始化，如堆、中断、控制台
    → 初始化定时器与调度器
    → rt_application_init()           创建 main 线程
    → 创建定时器线程、空闲线程等
    → rt_system_scheduler_start()
    → main 线程执行组件初始化和应用 main()
```

因此，应用 `main()` 通常已经运行在线程中。`INIT_BOARD_EXPORT` 注册的函数在板级初始化阶段执行；设备、组件、环境、应用等初始化函数则按级别在后续阶段执行。宏定义见 `include/rtdef.h`，执行逻辑见 `src/components.c`。

读内核可以按下列调用链推进：

1. **对象与线程：**`src/object.c`、`src/thread.c`。追踪创建、启动、延时、挂起和唤醒。
2. **调度与时钟：**单核看 `src/scheduler_up.c`，多核看 `src/scheduler_mp.c`；时钟节拍看 `src/clock.c`，硬件上下文切换看对应 `libcpu/` 代码。
3. **定时器与通信：**`src/timer.c`、`src/ipc.c`。比较信号量、互斥量、事件、邮箱和消息队列传递的内容与等待行为。
4. **内存：**`src/mem.c`、`src/mempool.c`、`src/memheap.c` 等。具体编入的实现取决于配置。

## 7. 配置和构建如何决定固件内容

RT-Thread 通常从某个 BSP 目录构建。以 `bsp/qemu-virt64-riscv/` 为例：

```text
Kconfig → .config → rtconfig.h → SConstruct / SConscript → 编译链接
```

`Kconfig` 定义可选项，`.config` 保存选择，`rtconfig.h` 向 C 代码提供配置宏，`SConstruct` 和 `SConscript` 决定编译哪些源码。配置应通过 `scons --menuconfig` 或 `scons --pyconfig-silent` 从 `.config` 生成；不要手工修改 BSP 的 `rtconfig.h`。

具体安装、构建与运行命令以 `bsp/qemu-virt64-riscv/README_cn.md` 为准。该 BSP 可选择 RV32 或 RV64，运行脚本是 `./qemu.py`；脚本可能创建磁盘镜像，编译会生成固件文件。这些生成物不应提交到仓库。

## 8. 维护 RISC-V 支持的切入点

`libcpu/risc-v/SConscript` 中并存两条移植路径：选择 `RT_USING_RISCV_NEW_COMMON` 的 BSP 使用 `libcpu/risc-v/common/`；其他 BSP 可能仍使用 `common64/` 或 `legacy_common/`。QEMU virt BSP 选择了新公共实现。维护前先确认目标 BSP 实际编入哪条路径。

| 问题 | 优先检查 |
| --- | --- |
| 多个 RISC-V BSP 共同出现的启动、异常或切换问题 | `libcpu/risc-v/common/`，或目标使用的旧移植路径 |
| 厂商特殊指令、缓存或 MMU 行为 | 对应的 `libcpu/risc-v/` 厂商目录 |
| 某块板子特有的内存布局、外设、中断接线 | 对应的 `bsp/` |
| 某配置未编入正确文件或编译选项错误 | BSP 与 `libcpu/risc-v/` 的 `Kconfig`、`SConscript`、`rtconfig.py` |

### 维护一块具体的 RISC-V 开发板，从哪里开始？

首先在 `bsp/` 中找到该芯片或开发板的目录，阅读其 `README`、`Kconfig`、`.config`、`SConstruct`、`SConscript`、`rtconfig.py` 和板级驱动代码。没有确定具体板卡时，可用 `bsp/qemu-virt64-riscv/` 了解一个可运行的 BSP 结构。

接着确认该 BSP 实际使用的新公共移植还是旧移植路径：检查 `.config` 中的 `RT_USING_RISCV_NEW_COMMON`，再对照 `libcpu/risc-v/SConscript`。若只有这块板的串口、时钟或外设中断异常，先检查其 BSP；若多个 RISC-V BSP 都在异常处理或上下文切换时出错，再检查它们共用的 `libcpu/risc-v/` 实现。通用设备接口本身出错时，进一步检查 `components/drivers/`。

开始修改前应记录目标板卡型号、RV32/RV64、运行模式、是否使用 MMU 与 SMP，以及可复现的编译或运行故障。这些信息决定应从板级代码、CPU 移植层还是组件层定位。配置更改应从 `.config` 通过配置工具生成 `rtconfig.h`，不要手工编辑它。可结合 [内核移植说明](../3.kernel/kernel-porting/kernel-porting.md) 学习接口要求。

建议先用 QEMU virt BSP 建立可重复的基线，记录提交号、`.config`、工具链版本、QEMU 版本、复现命令和运行结果。随后按问题涉及范围验证：

1. 编译目标 BSP；公共汇编、类型或栈帧修改应考虑 RV32 与 RV64。
2. 验证启动、时钟节拍、线程切换、延时、同步与中断。
3. 涉及 SMP、浮点、向量、MMU 或用户态时，运行相应配置的测试。
4. 参考 `.github/workflows/utest_auto_run.yml` 中现有的 RISC-V 标准内核、RT-Smart 和 SMP 测试，以及 BSP 的 `.ci/attachconfig/ci.attachconfig.yml`。

新公共移植的更具体约定见 [RISC-V 公共移植指南](../../libcpu/risc-v/common/README.md)。修改异常、CSR、页表或 SBI 行为时，还应对照 RISC-V 特权架构和 SBI 规范，确认预期行为。

## 9. 推荐的学习顺序

1. 读 [仓库介绍](../../README_zh.md)、[内核基础](../3.kernel/basic/basic.md)，建立目录与启动流程全图。
2. 根据 [QEMU RISC-V BSP 说明](../../bsp/qemu-virt64-riscv/README_cn.md) 跑通构建和启动，观察 `main()` 与命令行。
3. 对照 [线程管理](../3.kernel/thread/thread.md)，追踪线程创建、就绪、调度、延时和唤醒。
4. 用两个线程做优先级与信号量实验，再读 `src/scheduler_up.c`、`src/thread.c` 和 `src/ipc.c`。
5. 阅读定时器、线程同步、线程通信与内存管理文档。
6. 追踪一次 RISC-V 时钟中断和一次上下文切换，最后深入目标板卡或组件。

每次带着一个具体问题追调用链，例如“`rt_thread_delay()` 如何让其他线程运行”，通常比逐文件通读更容易建立整体理解。
