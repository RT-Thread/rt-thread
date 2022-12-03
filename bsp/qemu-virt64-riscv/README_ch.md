# RT-Smart QEMU SYSTEM RISC-V RV64 BSP

中文 | [English](./README.md)

## 1. 简介

本工程是在QEMU System RISC-V 64 模拟器运行，针对 virt 机器的BSP

## 2. 构建

1. 获取 [rt-smart SDK](http://117.143.63.254:9012/www/rt-smart/) risc-v 64版本.
1. 设置 `RTT_EXEC_PATH` 工具链的 bin 文件夹路径, 如 `/home/user/xxx/yyy/bin`
1. 设置 `RTT_CC_PREFIX` 为工具链前缀, 如 `riscv64-unknown-linux-musl-`
1. 设置 `RTT_CC` 为工具链名称, 如 `gcc`
1. 通过指令 `riscv64-unknown-linux-musl-gcc -v` 查看工具链的 -march 与 -mabi
1. 根据相关信息调整本目录下的 `rtconfig.py:40` 如 `DEVICE  = ' -mcmodel=medany -march=rv64imac -mabi=lp64 '`
1. `scons --menuconfig`
    * 如果 `-march` 包含 `v`, 选择 `Using RISC-V Vector Extension`, 反之关闭
    * 如果 `-march` 包含 `f/d`, 选择 `Enable FPU`, 反之关闭
1. `scons`

## 3. 运行

推荐拉取最新的 qemu 发行版在本地构建。使用指令确保qemu可用  `qemu-system-riscv64 --version`。

使用 `qemu-nographic.sh`/`qemu-nographic.bat` 启动虚拟机。

> if your -march contains characters v, using qemu-v-nographic.*
