# RT-Thread 源码结构与 RISC-V 维护学习笔记

本文面向希望阅读 RT-Thread 源码，并逐步参与 RISC-V 支持维护的开发者。具体编译配置、功能和实现以所选 BSP 及其 `.config` 为准。

第 1～9 章介绍工程目录和学习路线；第 10～16 章补充开发工具、QEMU RISC-V BSP、配置与构建脚本、模拟运行、测试及日志分析。文中的本机验证记录来自 2026 年 10 月 27～28 日，后续修改源码或配置后应重新验证。

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

## 10. RISC-V 开发工具、安装与编译环境

### 常用工具及其分工

| 工具 | 作用 |
| --- | --- |
| RISC-V GCC 工具链 | 编译、汇编、链接 RISC-V 固件，并提供目标架构所需的库 |
| Binutils | `objdump` 看反汇编，`readelf` 看 ELF 信息，`objcopy` 转换固件格式 |
| SCons | 根据 `SConstruct`、`SConscript` 组织构建，调用编译器 |
| Kconfig 配置工具 | 通过 `scons --menuconfig` 等命令选择功能、生成配置 |
| QEMU | 在主机上模拟 RISC-V CPU、内存和外设 |
| GDB / `gdb-multiarch` | 设置断点、查看调用栈和寄存器，定位运行故障 |
| OpenOCD | 配合受支持的调试探针连接真实硬件，提供调试服务 |
| `dtc`、`fdtget` | 转换或查看设备树，辅助分析硬件描述 |
| Minicom 等串口工具 | 查看实体开发板串口输出并与系统交互 |

OpenSBI 是向 S-mode 软件提供 SBI 服务的固件，作用不同于编译器。QEMU virt 的启动环境会使用相应的 SBI 固件；具体版本会影响运行环境。

### 查看本机工具

```sh
command -v gcc
gcc --version
gcc -dumpmachine

command -v riscv64-unknown-elf-gcc
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-gcc -dumpmachine
riscv64-unknown-elf-gcc --print-multi-lib

command -v qemu-system-riscv64
qemu-system-riscv64 --version
scons --version
```

`command -v` 检查当前 `PATH` 中的命令位置，查不到不等于整个磁盘都未安装该软件；也可能只是工具链的 `bin` 目录没有加入搜索路径。主机的 `gcc` 若以 `x86_64-linux-gnu` 为目标，则用于生成 x86 程序；构建此 BSP 要选择适用的 RISC-V 交叉编译器。`riscv64-unknown-elf-` 前缀的工具链是否能编译 RV32，要结合其 multilib、指令集和 ABI 支持判断。

在本次 Ubuntu 24.04 环境中，安装系统工具使用了以下命令：

```sh
sudo apt update && sudo apt install -y gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf qemu-system-misc qemu-utils gdb-multiarch openocd device-tree-compiler minicom scons python3-kconfiglib
```

该命令安装的交叉编译器不一定带有 BSP 所需的全部目标端头文件和运行库。本次实际编译遇到 `sys/types.h` 缺失，且编译器找不到 `libsupc++.a`。前者属于目标端 C 库头文件，后者属于目标端 C++ 运行库，适合通过完整工具链统一提供；不能使用主机架构的库来替代。

### 安装并验证完整工具链

仓库的 [自动测试工作流](../../.github/workflows/utest_auto_run.yml) 使用 [RT-Thread 发布的 GCC 10.2 工具链](https://github.com/RT-Thread/toolchains-ci/releases/tag/v1.4)。本次将它安装在用户目录，不需要管理员密码。首次安装时执行：

```sh
cd /tmp
wget -c https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz
mkdir -p "$HOME/.local/opt"
tar -xzf riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz -C "$HOME/.local/opt"

export RTT_EXEC_PATH="$HOME/.local/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin"
export RTT_CC_PREFIX=riscv64-unknown-elf-
```

检查选中的编译器，而非仍在 `PATH` 中的另一套编译器：

```sh
"$RTT_EXEC_PATH/riscv64-unknown-elf-gcc" --version
printf '#include <sys/types.h>\n' | "$RTT_EXEC_PATH/riscv64-unknown-elf-gcc" -E -x c - -o /dev/null
"$RTT_EXEC_PATH/riscv64-unknown-elf-gcc" -print-file-name=libsupc++.a
```

头文件检查应成功，库查询应返回完整路径；仅返回 `libsupc++.a` 表示未找到。该工具链已在本次环境中通过这两项检查，并成功构建当前 BSP。其他 BSP 或新扩展仍需检查工具链兼容性。

### 避免每次手工执行 `export`

一种方式是把上述两条 `export` 加入个人 `~/.bashrc`，执行一次 `source ~/.bashrc`；以后新开的 Bash 终端会加载这些设置。若需要同时维护不同架构，使用独立编译脚本更便于控制影响范围。

例如，把以下内容保存为个人目录中的 `~/build-rtt-riscv.sh`。这里假定仓库位于 `~/rt-thread`，实际目录不同时应调整：

```bash
#!/usr/bin/env bash
set -e

export RTT_EXEC_PATH="$HOME/.local/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin"
export RTT_CC_PREFIX=riscv64-unknown-elf-

exec scons -C "$HOME/rt-thread/bsp/qemu-virt64-riscv" "$@"
```

使用方法：

```sh
bash ~/build-rtt-riscv.sh -j4 --strict
bash ~/build-rtt-riscv.sh --menuconfig
```

脚本内的环境变量只影响它启动的构建进程。个人工具链路径和编译脚本应保存在用户目录，避免作为本机环境文件提交到仓库。

## 11. QEMU RISC-V BSP 的工程结构

[bsp/qemu-virt64-riscv](../../bsp/qemu-virt64-riscv) 是 QEMU virt 虚拟板卡的 BSP。目录名保留 `virt64`，但其 Kconfig 同时提供 RV32 和 RV64 选择；RT-Smart 的适用范围以该 BSP 的说明为准。

```text
qemu-virt64-riscv/
├── README_cn.md                 编译、运行和调试说明
├── Kconfig                      BSP 配置规则
├── .config                      当前选项
├── rtconfig.h                   生成的配置宏
├── rtconfig.py                  工具链与编译、链接参数
├── SConstruct                   工程构建入口
├── SConscript                   子目录构建脚本的分发入口
├── applications/
│   ├── main.c                   应用入口
│   ├── SConscript
│   ├── test/test_vector/        向量功能与上下文相关测试
│   └── utest/                   向量状态恢复测试
├── driver/
│   ├── board.c                  板级初始化入口
│   ├── board.h                  板级声明
│   ├── drv_romfb.c              显示尺寸适配
│   ├── Kconfig
│   └── SConscript
├── .ci/attachconfig/            附加测试配置
├── qemu.py                      QEMU 启动脚本
└── smart-env.bat                Windows 下的 RT-Smart 辅助脚本
```

本次检查时的配置为 RV64 标准版、4 核 SMP、32 个优先级、100 Hz 系统节拍、MMU、双精度浮点和 128 位向量扩展，启用了设备模型、设备树、命令行、文件系统和网络。UTest 未启用。这是一次配置快照，之后应以自己的 `.config` 和生成的 `rtconfig.h` 为准。

### 为什么板级初始化代码很短？

[driver/board.c](../../bsp/qemu-virt64-riscv/driver/board.c) 的核心只有：

```c
void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
```

实际工作进入 [libcpu/risc-v/common/setup.c](../../libcpu/risc-v/common/setup.c)：建立内存管理环境，处理设备树，初始化 CPU 信息、中断控制器和定时器，执行板级自动初始化，并设置控制台。其他 CPU 通过公共次级 CPU 入口完成每 CPU 初始化后进入调度器。

BSP 选择了 `RT_USING_RISCV_NEW_COMMON`，因此使用公共启动汇编。若 BSP 没有提供自己的 `link.lds`，公共构建脚本还会从 `libcpu/risc-v/link.lds.S` 生成链接脚本。当前 RV64 配置的 RAM 基地址为 `0x80000000`、镜像偏移为 `0x200000`，对应镜像起始地址 `0x80200000`；启动、链接和装载地址需要配套。

### 驱动为何分布在其他目录？

QEMU 生成设备树，启动环境把它交给 RT-Thread；设备模型根据硬件描述与驱动匹配。例如，8250 串口驱动位于 `components/drivers/serial/device/8250/`，VirtIO 驱动位于 `components/drivers/virtio/`，公共 RISC-V 中断控制器代码位于 `libcpu/risc-v/common/pic/`。因此，本地 `driver/` 并不是该 BSP 使用的全部驱动。

`drv_romfb.c` 仅提供显示缓冲区宽高参数。`applications/main.c` 输出 `Hello RISC-V` 后返回；main 线程结束后，命令行、空闲线程等仍可继续运行。

向量测试也受到 `RT_USING_UTEST`、`ENABLE_VECTOR` 等条件控制。目录存在、构建脚本被遍历，均不代表用例已启用；旧向量测试还含有固定 RV64 编译参数，切换 RV32 时需要检查适用性。

## 12. `Kconfig`、`.config`、`rtconfig.h`、`rtconfig.py` 的区别

| 文件 | 内容与读取者 | 修改方式 |
| --- | --- | --- |
| `Kconfig` | 配置项、类型、默认值和约束；由配置工具读取 | 开发者维护功能规则 |
| `.config` | 已保存的配置选择，以及规则计算结果 | 通常通过配置界面保存；脚本修改后需重新处理 |
| `rtconfig.h` | 配置选择转换成的 C 宏；由预处理器、构建工具及部分脚本读取 | 自动生成，不手工编辑 |
| `rtconfig.py` | 编译器路径、编译和链接参数；由 SCons 导入 | 开发者维护构建策略，也接受环境变量 |

### Kconfig 定义规则，`.config` 保存结果

例如，内核 Kconfig 定义：

```kconfig
config RT_USING_SMP
    bool "Enable SMP (Symmetric multiprocessing)"
    default n

config RT_CPUS_NR
    int "Number of CPUs"
    default 1
    range 1 1 if !RT_USING_SMP && !RT_USING_AMP
```

`bool` 定义开关，`int` 定义整数，`default` 提供默认值，`range` 约束取值。这里在没有 SMP、AMP 时限制 CPU 数量为 1。其他常见语法包括：

| 语法 | 作用 |
| --- | --- |
| `hex`、`string` | 十六进制或字符串配置 |
| `depends on` | 限制选项可用的条件 |
| `select` | 开启关联配置项 |
| `choice` | 定义互斥选项，例如 RV32/RV64 |
| `source`、`rsource` | 引入其他 Kconfig 文件 |

一个 BSP 的配置界面由多个目录的 Kconfig 组合而来。改变 Kconfig 中的默认值，不一定覆盖 `.config` 中已有的明确选择。

当前选择可以保存为：

```text
CONFIG_RT_USING_SMP=y
CONFIG_RT_CPUS_NR=4
CONFIG_RT_TICK_PER_SECOND=100
# CONFIG_RT_USING_SMART is not set
```

### `.config` 如何转换成 C 宏？

工具会去掉配置名前的 `CONFIG_`，并转换为：

```c
#define RT_USING_SMP
#define RT_CPUS_NR 4
#define RT_TICK_PER_SECOND 100
```

未开启的布尔选项通常不生成对应的开启宏。布尔宏可能没有数值，所以一般使用 `#ifdef RT_USING_SMP`，而非直接使用 `#if RT_USING_SMP`。

`include/rtthread.h` 包含了 `rtconfig.h`。除此以外，[tools/building.py](../../tools/building.py) 也会解析它，让 `SConscript` 使用 `GetDepend()` 选择源码。例如启用 SMP 时选择 `scheduler_mp.c`，关闭时选择 `scheduler_up.c`。配置既影响文件内部的代码分支，也影响哪些文件参与编译。

只修改 `.config` 后执行普通 `scons`，不能保证头文件已经同步。通过配置工具生成之后再构建：

```sh
scons --menuconfig
# 或：从已有 .config 重新处理配置并生成 rtconfig.h
scons --pyconfig-silent
```

### `rtconfig.py` 是构建脚本，不是自动生成的配置头文件

本 BSP 的 `rtconfig.py` 读取 `RTT_EXEC_PATH`、`RTT_CC_PREFIX`，确定编译器命令；再读取 `rtconfig.h` 中的位宽、浮点等选项，选择 `-march`、`-mabi` 并探测编译器兼容性。它还设置调试、优化、链接和固件转换参数：

| 变量或参数 | 作用 |
| --- | --- |
| `CC`、`CXX`、`AS`、`LINK` | C、C++、汇编和链接命令 |
| `CFLAGS`、`CXXFLAGS`、`AFLAGS`、`LFLAGS` | 相应阶段的参数 |
| `-march` | 允许生成的 RISC-V 指令集及扩展 |
| `-mabi` | 调用约定和数据布局等 ABI 选择 |
| `BUILD` | 选择脚本中的调试或优化配置 |
| `POST_ACTION` | 链接后的二进制转换、尺寸统计 |

`rtconfig.py` 由开发者维护，并不是由 `.config` 自动转换而来。更换本机工具链路径优先使用环境变量或个人脚本；调整 BSP 的编译、链接策略再检查它。

```text
Kconfig + 已保存的 .config
    → 配置工具处理并保存 .config
    → 生成 rtconfig.h
        → C 条件编译
        → SConscript 选择源码
        → rtconfig.py 读取架构选项，结合工具链环境变量
    → SCons 调用编译器和链接器，生成固件
```

## 13. `SConstruct` 与 `SConscript` 的具体分工

两者都是由 SCons 执行的构建脚本，使用 Python 语法并调用 SCons 接口。通常运行 `scons`，而非直接用 Python 执行它们。

### `SConstruct` 是 BSP 工程入口

[SConstruct](../../bsp/qemu-virt64-riscv/SConstruct) 首先导入 `rtconfig.py`，建立包含编译器和参数的 `Environment`，再调用：

```python
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)
DoBuilding(TARGET, objs)
```

`PrepareBuilding()` 收集 BSP、内核、CPU 移植和组件代码。这里 `has_libcpu=False` 表示 BSP 没有自行包办 CPU 移植代码的加入，因此公共流程会继续加入 `libcpu/`。`DoBuilding()` 组织最终构建，当前目标是 `rtthread.elf`，后处理生成 `rtthread.bin`。

### `SConscript` 负责目录中的构建组织

BSP 根目录的 [SConscript](../../bsp/qemu-virt64-riscv/SConscript) 遍历子目录，执行其中的 `SConscript`，汇总返回结果。具体规则由子脚本维护：

| 位置 | 当前规则 |
| --- | --- |
| `applications/SConscript` | 收集本目录的 `.c`、`.cpp`，继续处理子目录脚本 |
| `driver/SConscript` | 显式加入 `board.c`；按配置加入 `drv_romfb.c` |
| `src/SConscript` | 按配置选择内核实现 |
| `libcpu/SConscript` | 引入架构移植 |
| `components/SConscript` | 收集组件，再由各组件判断依赖 |

`Return('objs')`、`SConscript(...)`、`Environment(...)` 等是 SCons 接口。往 `applications/` 添加普通 C 文件通常会由现有 `Glob('*.c')` 规则收集；往 `driver/` 添加驱动则需要检查并更新显式源码列表。

```text
scons
    → SConstruct
    → PrepareBuilding()
        ├── BSP/SConscript → applications/、driver/
        ├── src/SConscript
        ├── libcpu/SConscript
        └── components/SConscript
    → DoBuilding()
    → rtthread.elf、rtthread.bin
```

## 14. `qemu.py`、虚拟开发板与常用操作

### 执行 Python 脚本，怎样变成运行固件？

`python3 qemu.py` 让主机的 Python 执行 [qemu.py](../../bsp/qemu-virt64-riscv/qemu.py)。脚本读取内核配置、组织模拟硬件参数，然后启动 QEMU，加载已编译的 `rtthread.bin`。

```text
scons：源码 → 固件
python3 qemu.py：启动 QEMU → 加载固件 → RT-Thread 在模拟 CPU 上执行
```

QEMU virt 可以理解为一块虚拟 RISC-V 开发板，提供 CPU、内存、串口、中断控制器以及选择的其他设备。它不对应某一块特定实体开发板。线程调度、中断、内存和相应虚拟驱动可以在这里测试；真实板卡的时钟、引脚、Flash、DMA、硬件时序等仍需在目标 BSP 与实物上验证。

### 按代码执行顺序理解脚本

| 函数或代码阶段 | 具体作用 |
| --- | --- |
| `read_default_cpus()` | 从 `rtconfig.h` 读取 `RT_CPUS_NR`，读不到时默认 1 |
| `read_riscv_xlen()` | 根据配置选择 RV32/RV64 对应的模拟器 |
| `read_vector_vlen()` | 判断内核是否启用向量，并读取 VLEN |
| `using_rt_smart()` | 判断是否需要应用 RT-Smart 相关 CPU 参数 |
| `qemu_tool()` | 通过 `RTT_QEMU_ROOT` 或系统搜索路径选择 QEMU 工具 |
| `qemu_version()` | 查询 QEMU 版本，辅助检查部分功能兼容性 |
| `ensure_qcow2()` | 为磁盘名补充后缀，必要时调用 `qemu-img` 创建镜像 |
| `virtio_device()` | 根据 `-pci` 选择 VirtIO PCI 或默认设备形式 |
| `parse_args()` | 定义并读取用户输入的命令行参数 |
| `main()` | 检查参数、选择默认设备、构造命令列表并启动 QEMU |
| `dump_dtb_to_dts()` | 导出设备树后，使用 `dtc` 转换为可阅读形式 |

`main()` 先检查核数匹配、图形参数和网络参数冲突，再决定 AIA、附加控制台等默认配置。它构造包含 `-M`、`-cpu`、`-smp`、`-m`、`-kernel`、`-append` 的命令列表，按选项加入设备，最后通过 `subprocess.call(cmd)` 执行 QEMU 并返回退出码。脚本不会编译固件，也不会替内核启用对应驱动。

脚本按当前工作目录读取 `rtconfig.h` 和默认固件，因此先进入 BSP 目录：

```sh
cd "$HOME/rt-thread/bsp/qemu-virt64-riscv"
python3 qemu.py -h
python3 qemu.py -dry-run
```

`-dry-run` 打印最终 QEMU 命令，不启动虚拟机、不创建磁盘镜像；脚本仍可能查询 QEMU 版本。查看输出有助于理解主机上的 QEMU 命令如何对应虚拟硬件。

### 常用参数

| 参数 | 作用及条件 |
| --- | --- |
| 无参数 | 加载当前目录的 `rtthread.bin`；默认 CPU 为 `max`、内存 256 MB，无图形窗口 |
| `-smp 4` | 指定核数，必须与固件的 `RT_CPUS_NR` 一致 |
| `-mem 512` | 模拟 512 MB 内存 |
| `-cpu rv64` | 选择 CPU 模型，实际可用模型取决于 QEMU |
| `-kernel FILE` | 加载指定固件 |
| `-bootargs "..."` | 替换传给系统的启动参数 |
| `-debug` | 添加 QEMU 的 `-S -s`，暂停 CPU 等待 GDB 在 1234 端口连接 |
| `-dumpdtb FILE` | 导出 QEMU 设备树；安装 `dtc` 时还尝试转换为 DTS |
| `-dtb FILE` | 使用指定设备树，必须与模拟硬件匹配 |
| `-initrd FILE` | 传入初始内存盘镜像 |
| `-aia`、`-no-aia` | 选择 APLIC/IMSIC 或非 AIA 的 PLIC/ACLINT 路径 |
| `-no-msi` | 脚本中的兼容参数，效果是关闭 AIA |
| `-v` | 启用 QEMU 向量能力；不是详细日志开关，不能代替内核向量配置 |
| `-block NAME` | 指定 VirtIO 块设备镜像名，也可写 `-virtio-block NAME` |
| `-nvme [NAME]`、`-no-nvme` | 添加或关闭 NVMe 磁盘 |
| `-net`、`-no-net` | 开启或关闭默认用户网络 |
| `-ssh 12056` | 将主机端口转发到虚拟机 TCP 22；不会自动启动 SSH 服务 |
| `-tap` | 使用已有的 `tap0` 网络接口，与 `-no-net` 冲突 |
| `-pci` | 让相应 VirtIO 设备通过 PCI 接入 |
| `-virtio-console`、`-no-virtio-console` | 控制映射到主机 4321 端口的附加控制台 |
| `-pci-serial`、`-no-pci-serial` | 控制映射到主机 4322 端口的 PCI 串口 |
| `-graphic` | 添加图形显示、键盘等设备 |
| `-gl BACKEND` | 使用相应图形后端，要求同时启用 `-graphic` |
| `-sound none/hda/virtio` | 选择声音设备，仍需主机和固件支持；脚本检查 VirtIO 声音的版本要求 |
| `-9p PATH` | 提供主机目录的 9P 共享；虚拟机还需对应驱动与挂载支持 |
| `-watchdog`、`-edu` | 添加相应看门狗或 PCI 测试设备；有对应关闭参数 |
| `-rv64ilp32` | 使用特殊的 `qemu-system-rv64ilp32`，需另行具备相应模拟器和固件 |

RV64 默认启用 AIA 和附加控制台；没有被显式覆盖时，默认 NVMe 选择还受 AIA、`-no-msi` 影响。当前脚本始终添加 VirtIO 块设备、随机数设备和加密设备等基础设备，因此关闭几个可选项并不等于移除了所有外设。磁盘镜像不存在时创建为 64 MB qcow2 文件，但这不会在盘内建立 FAT 文件系统。

### 启动、调试和查看设备树

基础启动可使用下面的命令，减少可选设备并避免默认根文件系统参数的影响：

```sh
python3 qemu.py -no-aia -no-net -no-nvme \
  -no-virtio-console -no-pci-serial \
  -bootargs "console=ttyS0 earlycon=sbi"
```

正常退出终端模式的 QEMU：先按 `Ctrl+A`，松开后按 `X`。

调试时第一个终端执行：

```sh
python3 qemu.py -no-aia -debug
```

第二个终端进入同一个 BSP 目录执行：

```sh
gdb-multiarch rtthread.elf
```

进入 GDB 后：

```gdb
target remote :1234
break main
continue
bt
info registers
```

`-debug` 下暂停等待连接属于预期行为。GDB 的 `bt` 查看调用栈，`info registers` 查看寄存器，还可使用 `step`、`next`、`continue`。定位运行故障时应使用与固件对应的 ELF 调试信息。

导出或指定设备树：

```sh
python3 qemu.py -dumpdtb qemu-virt.dtb
python3 qemu.py -dtb myboard.dtb
```

## 15. 自己编译、测试与判断 BSP 是否正常

### 从编译到基础运行

进入 BSP 目录，使用本次已验证的完整工具链编译。下面的环境变量只作用于该条命令，无需先单独执行 `export`：

```sh
cd "$HOME/rt-thread/bsp/qemu-virt64-riscv"

RTT_EXEC_PATH="$HOME/.local/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin" \
RTT_CC_PREFIX=riscv64-unknown-elf- \
scons -j4 --strict
```

看到 `scons: done building targets.` 并生成固件，说明该配置可构建。随后使用第 14 章的基础启动命令，检查 `Hello RISC-V`、`msh` 提示符，以及多核启动输出。在 RT-Thread 命令行中执行：

```text
ps
free
list device
mount
```

这些命令分别查看线程、堆内存、设备和挂载状态。命令应能持续响应。等待事件的线程处于 `suspend` 很常见，`ps` 错误列中的单个 `EINTRPT` 也不能单独作为故障证据。内存使用量应结合相同操作前后变化判断，持续增长且不回落时需检查泄漏；栈接近耗尽或触发溢出检查时需排查。

### 用 UTest 验证内核功能

通过 `scons --menuconfig` 进入 `RT-Thread Utestcases`，启用测试集合，再在 `Kernel Core` 选择线程、调度器、定时器、中断、原子操作等测试，随后按需加入信号量和互斥量。保存、重新编译、重启 QEMU 后执行：

```text
utest_list
utest_run
```

`utest_list` 应列出有效用例。确认测试完整结束，并检查 `FAILED`、断言、异常和超时；仅启用框架而没有选择用例，不能形成有效验证。若命令不存在，先检查配置与重新编译是否完成。

### 分层验证与故障定位

| 阶段或现象 | 优先检查 |
| --- | --- |
| 缺头文件、缺运行库 | 交叉工具链及其目标端库 |
| 找不到 `rtthread.bin` | 编译是否完成、工作目录或 `-kernel` 是否正确 |
| QEMU 报未知设备或属性 | QEMU 版本和启动参数 |
| 主机端口被占用 | 附加控制台或网络转发参数 |
| 输出停在启动阶段 | 启动代码、链接和装载地址、等待设备或 GDB 的条件 |
| 正常启动出现断言、非法指令、页故障或异常回溯 | 根据异常信息定位内核、驱动与架构实现；也要确认测试是否有意触发异常 |
| 单个外设失败 | 设备是否被模拟、描述是否正确、驱动是否编入及其初始化结果 |
| 多核卡死或同步失败 | CPU 配置、每 CPU 初始化、IPI、调度及同步实现 |

基础检查通过后，再分别比较单核/SMP、RV32/RV64、AIA/非 AIA、浮点与向量配置；涉及用户态和系统调用时加入 RT-Smart 对应测试。修改核数需要重新配置并编译，不能只改 QEMU `-smp`。涉及真实硬件时，在目标板对应 BSP 上重复验证并补充外设、DMA、时序等测试。

每次保留提交号、`.config`、工具链和 QEMU 版本、完整命令、串口输出及失败用例名。每次尽量只改变一个条件，再比较结果。

### 本次已验证的范围

2026 年 10 月 27～28 日，使用完整 GCC 10.2 工具链构建了该 BSP。随后在 QEMU 8.2.2、OpenSBI 1.3 环境下，以 RV64、4 核和非 AIA 的简化启动配置完成了基础检查：出现 `Hello RISC-V` 和 `msh`，其他三个 CPU 打印启动成功，`ps`、`free` 正常响应。日志仍有 ISA 识别及相关中断控制器信息。

这些结果只证明所测配置可构建、可启动和交互。本次没有启用 UTest，也没有据此验证所有外设或全部 RISC-V 配置。后续默认配置的日志还需结合下一章分析。

## 16. 对本次默认启动日志的分析

用户执行 `python qemu.py` 后提供的日志包含完整启动输出、命令行和 `Hello RISC-V`，同时出现 ISA、PCI 中断和文件系统错误。Ubuntu 环境中可明确使用 `python3 qemu.py`。

### 哪些输出表示启动已推进？

| 日志 | 可以确认的事项 |
| --- | --- |
| `OpenSBI v1.3`、`Next Mode: S-mode` | 启动固件准备进入 S-mode 运行目标镜像 |
| `Platform HART Count : 4` | 模拟平台包含 4 个 hart |
| 内存、保留区域与页管理输出 | 已执行相应内存初始化 |
| `Call cpu 1/2/3 on success` | 其他逻辑 CPU 已进入对应启动流程，仍需负载和同步测试 |
| `lwIP-2.0.3 initialized` | 协议栈初始化，尚不能证明网络收发正常 |
| `msh />`、`Hello RISC-V` | 命令行和应用入口已执行 |

`Boot HART ID : 2` 本身不表示错误，启动 hart 不必为 0，硬件 hart ID 与内核逻辑 CPU ID 也需区分。`184 MB memory installed to system page` 不表示其余内存丢失，前面已经列出了固件、内核、64 MB 堆、设备树、DMA 等保留区域。

### `Unknow ISA`：识别表缺项与前缀解析缺陷

这些日志来自 [setup.c](../../libcpu/risc-v/common/setup.c) 对设备树 ISA 名称的解析。部分扩展没有列入当前表，属于未识别名称，不等于 CPU 执行了非法指令。

其中 `Unknow ISA in` 已确认涉及一个解析缺陷。本机 QEMU 设备树含有 `zfhmin`，表中 `zfh` 又位于 `zfhmin` 之前；当前前缀匹配先接受 `zfh`，剩下的 `min` 随后被错误跳过一个字符，最终打印 `in`。应按完整扩展名边界处理，不能只接受较短前缀。此次只分析并验证了该现象，没有修改解析代码。

### PCI `irq parse failed with err = ENOENT`

日志中两个 PCI 设备的错误来自 [components/drivers/pci/ofw.c](../../components/drivers/pci/ofw.c) 的 INTx 中断映射解析。这里的 `ENOENT` 与设备树中断路由有关，并非表示主机磁盘镜像文件不存在。

后续 `NVM Express v1.0 ...` 说明驱动至少已识别、处理 NVMe 控制器，但不能证明其读写及中断全部正常。[NVMe PCI 驱动](../../components/drivers/nvme/nvme-pci.c) 还会尝试 MSI-X，因此 INTx 解析失败也不能直接推导为 NVMe 完全不可用。需确认具体 PCI 设备、映射和实际中断使用路径，再做 I/O 验证。

### qcow2 创建与根文件系统挂载失败

```text
Formatting 'nvme.qcow2' ... fmt=qcow2 ...
[W/DFS.fs] mount / failed with file system type: elm
[W/rtdm.mnt] Mount root on /dev/vda0 type=elm fail
```

第一行只是 `qemu-img` 创建虚拟磁盘容器，不是在盘内建立 FAT 文件系统。默认启动参数要求把 VirtIO 块设备 `vda0` 以 `elm`（FatFs）挂载到 `/`，与开头新建的 NVMe 镜像需要区分。

挂载失败的常见原因是 VirtIO 磁盘尚未建立预期文件系统，或分区和设备布局不符，也需排除设备读写问题。先通过 `list device` 和 `mount` 检查，不应未经确认格式化已有数据盘。若仅测试内核启动，可使用第 14 章仅保留控制台参数的启动命令。

后续的 `File system initialization done` 来自 [mnt.c](../../components/drivers/core/mnt.c) 中另一个初始化函数，并不能证明前面的根目录挂载成功。

### `QEMU: Terminated` 是否代表崩溃？

若按 `Ctrl+A`、`X` 主动退出，这是预期的进程结束。若没有主动退出，还需检查 QEMU 进程的退出原因。单独这一行不能证明 RT-Thread 内核崩溃；本次所贴日志已经到达应用入口，未显示内核断言或异常回溯，但所列功能问题仍需分别验证。
