# QEMU RISC-V virt BSP

[English](README.md) | 中文

本 BSP 在 QEMU RISC-V `virt` 机器的 S-Mode 下运行 RT-Thread。目录名为兼容
现有工程继续保留，Kconfig 内部同时支持 RV32 和 RV64，默认选择 RV64。目前
RT-Thread Smart 仍只支持 RV64；RV32 运行标准版 RT-Thread。

## 编译

安装 SCons、QEMU RISC-V system emulator 和 RISC-V GCC 工具链。编译 RV32
时，工具链必须包含所选 RV32 ABI 的 multilib。

```sh
export RTT_EXEC_PATH=/path/to/toolchain/bin
export RTT_CC_PREFIX=riscv64-unknown-elf-

scons --menuconfig
scons -j$(nproc)
```

位宽在 `RISC-V XLEN` 中选择。重新生成配置后会更新 `rtconfig.h`，编译产物为
`rtthread.elf` 和 `rtthread.bin`。BSP 把 `ARCH_RAM_OFFSET` 设为 `0x80000000`，
RV32 使用 4 MiB image offset，RV64 使用 2 MiB image offset，与 QEMU/OpenSBI
的默认装载地址保持一致，不需要 BSP 本地链接脚本。

## 运行

```sh
./qemu.py
```

RV32 和 RV64 都默认启用 QEMU user 网络和一个 virtio block 磁盘。RV64
另外默认启用 AIA（APLIC/IMSIC）、NVMe、virtio-console 和 PCI serial。
RV32 默认使用 PLIC/ACLINT 和 legacy virtio-mmio，不默认挂载 NVMe 和两个
附加控制台。缺失的 qcow2 镜像会自动创建，存储设备只保留 virtio block
与 NVMe 两类。

在 QEMU 10.1 与 OpenSBI 1.5.1 组合下，RV32 S-mode AIA 能进入 IMSIC 初始化，
但访问 `siselect/sireg` 时会触发非法指令。`-aia` 参数仍可用于测试新版
模拟器和固件组合，但不作为 RV32 默认值。

常用参数：

```sh
./qemu.py -no-aia
./qemu.py -no-net -no-nvme
./qemu.py -nvme -virtio-console -pci-serial
./qemu.py -pci
./qemu.py -graphic
./qemu.py -dumpdtb qemu-virt.dtb
./qemu.py -dry-run
```

QEMU 核数必须与内核配置中的 `RT_CPUS_NR` 一致。调整 `-smp` 前应先修改
`RT_CPUS_NR` 并重新编译；当前内核没有独立的 online CPU mask，因此脚本会拒绝
核数不匹配的启动方式。

启用 `ARCH_RISCV_VECTOR` 后，脚本会从 `rtconfig.h` 读取 VLEN 并同步配置
QEMU。内核未启用 Vector 时，也可以用 `-v` 强制 QEMU 使用默认的 128-bit
Vector 配置。

## 调试

让 QEMU 暂停等待 GDB：

```sh
./qemu.py -debug
riscv64-linux-gnu-gdb rtthread.elf -ex "target remote :1234"
```

RV32 构建应使用与对应位宽和工具链匹配的 GDB。
