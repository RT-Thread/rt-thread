# 全志 D1s 运行 RT-Smart

* [基于柿饼M7运行 RT-Smart](./README-M7.md)
* [基于麻雀MQ运行 RT-Smart](./README-MQ.md)
* [在 QEMU 中运行（Run on QEMU）](#在-qemu-中运行run-on-qemu)

## 在 QEMU 中运行（Run on QEMU）

没有板子时，可以用 [d1s-qemu](https://github.com/cms19859230182-lang/d1s-qemu)
提供的 QEMU `d1s` 机型启动本 BSP 编出的 `rtthread.bin`：

```sh
# 1. 编译 d1s-qemu（见该仓库 README）
git clone https://github.com/cms19859230182-lang/d1s-qemu
cd d1s-qemu && scripts/fetch-qemu.sh && scripts/apply-patches.sh && scripts/build.sh

# 2. 在本目录编译 RT-Thread（工具链见 README-M7.md；也可用环境变量指定，例如
#    RTT_EXEC_PATH=/path/to/toolchain/bin RTT_CC_PREFIX=riscv64-linux-musleabi-）
scons

# 3. 启动（UART0 接到终端）
D1S_QEMU_DIR=/path/to/d1s-qemu ./qemu-d1s.sh
```

当前状态：默认配置下能打印 RT-Thread Smart 启动信息，完成 SD/MMC（SMHC0/SMHC1，
`run.sh` 自动挂空白镜像）初始化并进入 `msh />`；空白镜像没有文件系统，根文件系统挂载失败属正常现象。

Without a board, `rtthread.bin` from this BSP can be started on the `d1s`
machine of d1s-qemu with `D1S_QEMU_DIR=/path/to/d1s-qemu ./qemu-d1s.sh`.
The RT-Thread Smart banner is printed, SD/MMC (SMHC0/SMHC1, blank images
attached by run.sh) is probed and the boot reaches `msh />`. Mounting the root
file system fails on the blank images, which is expected.
