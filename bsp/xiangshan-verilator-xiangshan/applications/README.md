# Verilated DUT on RT-Thread (qemu-virt64-riscv)

## 目标

在 RT-Thread qemu-virt64-riscv BSP 中运行 Verilator 生成的 `dut_150` 仿真程序，使用 C++ 测试逻辑（`applications/main.cpp`）。

## 关键裁剪点

- **单线程运行**：若运行环境缺少 pthread，需强制 `threads(1)`；本目录已将线程池改为 RT-Thread API，可按需开启多线程。
- **禁用计时/波形**：去除 coroutine/timing/trace 相关源码与生成选项：`--no-timing --no-trace`。
- **RT-Thread 适配宏**：使用 `-DVL_RT_THREAD -DVL_MT_DISABLED` 避免调用缺失的 libc/线程特性，使用自带的字符串/数学函数。
- **运行库精简**：通过 `verilator --getenv VERILATOR_ROOT` 获取 Verilator 安装目录，只从其 `include/` 中编译 `verilated.cpp`、`verilated_random.cpp`、`verilated_threads.cpp` 这 3 个运行时源文件。
- **运行库来源**：BSP 不再依赖 `applications/verilator_runtime` 这份本地拷贝参与构建，而是直接使用当前系统 Verilator 安装中的 runtime。

## 生成模型

路径：`bsp/xiangshan-verilator/verilator-case/Makefile`

- 默认调用：`verilator -Wall --cc dut_150.v --exe tb_150.cpp -Mdir ../applications/verilated_dut_150 --no-timing --no-trace --threads 1 --CFLAGS "-DVL_RT_THREAD -DVL_MT_DISABLED"`
- 输出：`applications/verilated_dut_150/` 下的 `Vdut_150.*`。

## 应用构建集成

文件：`applications/SConscript`

- 编译源：`*.c`/`*.cpp` + `verilated_dut_150/*.cpp` + 运行库最小集。
- `CPPPATH`：应用目录、`verilated_dut_150`、`verilator --getenv VERILATOR_ROOT` 返回目录下的 `include/`。
- `CPPDEFINES`：包含 `VL_RT_THREAD`。

## 运行入口

文件：`applications/main.cpp`

- 创建上下文后可按需设置线程数，默认跟随 Verilator 生成的 `threads()`。
- 重置与驱动 DUT 的测试序列，带有 `rt_kprintf`/`std::cout` 日志方便调试。
- 为避免退出流程触发异常，结尾保持循环休眠（`rt_thread_mdelay`)。

## 构建与运行

- 构建：`scons --exec-path=$HOME/riscv-baremetal/bin --cc-prefix=riscv64-unknown-elf-`（在 `bsp/xiangshan-verilator`）。
- 运行：`timeout 1 ~/qemu/build/qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin`。

## 已知行为

- 文件系统未挂载会提示 `DFS.fs mount / failed ...`，但不影响仿真测试逻辑。
- 运行日志会打印 `[TB] ...`，确认 DUT 已构造并执行测试用例。
