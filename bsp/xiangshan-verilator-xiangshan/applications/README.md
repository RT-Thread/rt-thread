# XiangShan Verilator Simulation on RT-Thread

## 目标

在 RT-Thread qemu-virt64-riscv BSP 中运行 XiangShan 的 Verilator 仿真，guest 负载为 `XiangShan/ready-to-run/hello.bin`。

## 构建前提

- XiangShan 产物已通过 `make emu NO_DIFF=1 ...` 生成（`build/verilator-compile/`、`build/generated-src/` 等）。
- `NOOP_HOME` 环境变量指向 XiangShan 根目录（或设置 `RTT_XIANGSHAN_ROOT`）。

## 构建命令

```sh
export NOOP_HOME=~/rt-thread-for-corvus/XiangShan
scons --exec-path=$HOME/riscv-baremetal/bin --cc-prefix=riscv64-unknown-elf- -j64
```

## 运行命令

```sh
timeout 720 ~/qemu/build/qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin
```

## 验收标准

QEMU 日志中出现 guest UART 输出 `Hello, world!`，宿主不崩溃。

## 运行入口

`applications/xiangshan_rtthread_main.cpp`：RT-Thread 专用 XiangShan 仿真入口，使用固定 `CommonArgs` 配置，不依赖命令行参数。
