# QEMU/AArch64 VIRT 板级支持包说明

中文页 | [English](README.md)

## 1. 简介

AArch64 是 ARMv8 架构下执行 A64 指令的 64 位执行状态。本 BSP 将 RT-Thread 移植到 QEMU `virt`  AArch64 机器上，基于设备模型（DM）、Open Firmware（OFW/FDT）与 PCI 总线框架，可作为 VirtIO、PCI 及各类平台驱动的开发与验证平台。

当前默认配置要点：

| 项目 | 说明 |
| ---- | ---- |
| RT-Thread 版本 | 5.3 |
| 架构 | ARMv8 AArch64，MMU |
| SMP | 4 核（`RT_CPUS_NR=4`） |
| 中断控制器 | GICv2 / GICv3（含 ITS、MSI） |
| 控制台 | UART0（PL011，`ttyAMA0`） |
| 根文件系统 | VirtIO Block `vda0`，FatFs（elm-chan） |
| 内存 | 默认 128 MB（可通过 `qemu.py -mem` 调整） |

## 2. 编译说明

建议使用 ARM Developer GNU 交叉编译工具链，支持 Linux / Windows 平台：

```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```

下载 x86_64 Hosted 平台对应的 `xxx-aarch64-none-elf` 二进制包，解压后将 `RTT_EXEC_PATH` 环境变量指向该编译器的 `bin` 目录。

进入 `rt-thread/bsp/qemu-virt64-aarch64` 目录执行：

```
scons
```

正常生成 `rtthread.elf` 与 `rtthread.bin` 文件。

也可通过 `scons --exec-path="GCC工具链路径"` 在指定工具链的同时直接编译。

配置修改可使用 `scons --menuconfig`，保存后重新 `scons` 编译。

## 3. 运行

本 BSP 使用 `qemu-system-aarch64` 模拟器，通过 `qemu.py` 启动。

### 3.1 安装 QEMU

Windows 平台：

```
https://www.qemu.org/download/
```

Linux 平台（以 Ubuntu、Deepin 为例）：

```
sudo apt update
sudo apt install qemu-system-arm
```

部分可选功能对 QEMU 版本有要求：

| 功能 | 最低 QEMU 版本 |
| ---- | -------------- |
| UFS 存储 | 8.2.0 |
| VirtIO Sound（`-sound virtio`） | 8.2.0 |

### 3.2 环境变量

| 变量 | 说明 |
| ---- | ---- |
| `RTT_QEMU_ROOT` | QEMU 可执行文件所在目录前缀（脚本会在其后拼接 `qemu-system-aarch64`） |
| `RTT_ROOT` | RT-Thread 源码根目录，默认自动取 BSP 上两级目录 |

### 3.3 基本启动

在 BSP 目录下执行：

```
python qemu.py
```

或：

```
./qemu.py
```

首次运行会自动创建各存储设备对应的 64 MB `qcow2` 镜像。默认以 `-nographic` 模式启动，串口输出到当前终端。

典型启动日志：

```
heap: [0x40042aa0 - 0x40142aa0]

 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build ...
 2006 - 2026 Copyright by rt-thread team
hello rt-thread
msh />
```

### 3.4 `qemu.py` 命令行参数

| 参数 | 默认值 | 说明 |
| ---- | ------ | ---- |
| `-gic` | `2` | GIC 版本（`2` 或 `3`）；`-smp` 大于 8 时自动切换为 GICv3；`-el 2` 且 GICv3 时内部使用 `gic-version=max`（不可通过 `-gic max` 手动指定） |
| `-smp` | `RT_CPUS_NR`（4） | CPU 核心数；`-dtbo` 检测到 `amp_soc` 时自动加 1 |
| `-mem` | `128` | 内存大小（MB） |
| `-el` | `1` | 异常级别：`1` 默认；`2` 开启虚拟化；`3` 开启 secure |
| `-bootargs` | 见下文 | 内核启动参数 |
| `-initrd` | — | 指定 initrd 镜像路径 |
| `-graphic` | — | 图形模式（ramfb + `virtio-gpu-device` + VirtIO 键盘/平板），替代 `-nographic` |
| `-gl` | — | 图形模式下挂载 `virtio-gpu-gl-pci` 并开启 QEMU 显示端 OpenGL（如 `-gl gtk`）；需 QEMU 带 `--enable-opengl`、`--enable-virglrenderer`，且须与 `-graphic` 合用 |
| `-debug` | — | 启用 GDB 调试（`-S -s`） |
| `-dumpdtb` | — | 导出运行时 DTB 并转为 DTS |
| `-dtb` | — | 使用自定义 DTB 文件 |
| `-virtio-block` | `virtio` | VirtIO Block 磁盘镜像名前缀（生成 `virtio.qcow2`，挂载为 `vda`） |
| `-scsi` | `scsi` | VirtIO SCSI 磁盘镜像名前缀 |
| `-flash` | `flash` | pflash 磁盘镜像名前缀（pflash1，CFI NOR） |
| `-emmc` | `emmc` | SDHCI eMMC 磁盘镜像名前缀 |
| `-nvme` | `nvme` | NVMe 磁盘镜像名前缀 |
| `-ahci` | `ahci` | AHCI SATA 磁盘镜像名前缀 |
| `-ufs` | `ufs` | UFS 磁盘镜像名前缀（QEMU ≥ 8.2.0） |
| `-cdrom` | — | SCSI CD-ROM 镜像路径（如 ISO 文件） |
| `-sound` | `hda` | 音频设备：`hda`（Intel HDA）或 `virtio`（VirtIO Sound PCI） |
| `-tap` | — | 使用 TAP 网卡（替代 user 模式） |
| `-ssh` | `12055` | user 模式下 SSH 端口转发（`hostfwd=tcp::PORT-:22`） |
| `-9p` | — | VirtIO 9P 共享目录路径（需在 menuconfig 中启用 VirtIO 9P） |
| `-camera` | — | 宿主机 V4L2 设备路径（如 `/dev/video0`）；仅 Linux；需对设备有读权限（通常加入 `video` 组）；后台编译运行 `qemu-device-camera.c` 并通过 vfio-user 挂载 PCI 摄像头（需安装 **libvfio-user**） |
| `-dtbo` | — | AMP 模式：指定 DTBO overlay 文件（如 `amp.dtsi`）；自动将 `-smp` 加 1；**须 Smart 版本内核**且配置足够 `-mem`（见下文） |

默认 `-bootargs`：

```
console=ttyAMA0 earlycon cma=8M coherent_pool=2M root=vda0 rootfstype=elm rootwait rw
```

### 3.5 常用启动示例

图形界面（VirtIO GPU + 键鼠）：

```
./qemu.py -graphic
```

QEMU OpenGL 显示（`-gl`）：

```
./qemu.py -graphic -gl gtk
```

> **说明**：`-gl` 仅在 QEMU / 宿主机显示链路侧启用 OpenGL（`virtio-gpu-gl-pci` + VirGL）。本 BSP 默认仅包含 VirtIO GPU 2D 帧缓冲驱动，**没有 OpenGL / VirGL 用户态与内核侧实现**，因此 `-gl` 不会带来 RT-Thread 内的 OpenGL 加速；图形演示请使用 `-graphic`（`virtio-gpu-device`）配合 framebuffer 栈。

GDB 调试：

```
./qemu.py -debug
```

更大内存与 GICv3：

```
./qemu.py -mem 256 -gic 3
```

挂载 CD-ROM：

```
./qemu.py -cdrom /path/to/image.iso
```

VirtIO Sound 音频：

```
./qemu.py -sound virtio
```

9P 目录共享（需先启用 `RT_VIRTIO_9P`）：

```
./qemu.py -9p /path/to/share
```

AMP 异构多核（RPMSG 从核，**须 Smart 版本**）：

```
./qemu.py -dtbo amp.dtsi -mem 258
```

> **说明**：AMP 示例要求启用 **Smart 版本**（`RT_USING_SMART`），且必须使用 **`-mem 258`**（`amp.dtsi` 内存布局约需 258 MB，默认 128 MB 不足）。`qemu.py` 检测到 `amp_soc` 时会将 `-smp` 自动加 1（例如 `RT_CPUS_NR=4` 时实际以 `-smp 5` 启动）。QEMU `loader` 会预先将 `amp.dtb` 与 `rtthread.bin` 加载到 `amp.dtsi` 指定的固定物理地址（如 `kernel-entry = 0x48480000`），主核再通过 PSCI 拉起从核。标准版内核要求在虚拟地址与物理地址相等的区域运行，无法用于从核地址空间。请在 menuconfig 中开启 Smart 后重新编译。

摄像头演示（`camera.c` 叠加画面到 framebuffer，需配合 `-graphic`）：

```
./qemu.py -graphic -camera /dev/video0
```

> **说明**：`-camera` 必须传入宿主机 V4L2 设备路径。Linux 下需先安装 [libvfio-user](https://github.com/nutanix/libvfio-user)（详见 `qemu-device-camera.c` 注释），并确保当前用户对设备节点有读权限（例如 `sudo usermod -aG video $USER` 后重新登录，或用 `ls -l /dev/video0` 确认权限）。若设备正被其他程序占用，也会打开失败。脚本会编译 `qemu-device-camera.c`、等待 `/tmp/qemu-device-camera.sock` 就绪后启动 QEMU，并在 QEMU 退出后结束辅助进程。

### 3.6 控制台与 Telnet

| 端口 | 设备 | 说明 |
| ---- | ---- | ---- |
| 当前终端 | UART0（PL011） | 默认 `-nographic` 串口 |
| `4321` | VirtIO Console | `telnet 127.0.0.1 4321`，端口名 `org.rt-thread.console` |
| `4322` | PCI 8250 串口 | `telnet 127.0.0.1 4322` |
| `4323` | AMP 从核控制台 | 仅 `-dtbo` 模式，`telnet localhost 4323` |

VirtIO Console 连接示例：

```
telnet 127.0.0.1 4321
```

### 3.7 网络

默认使用 user 模式网络（`-netdev user`），SSH 端口转发到本机 `12055`（可用 `-ssh` 修改）。

TAP 网卡模式示例（以 `tap0` 为例）：

```
./qemu.py -tap
```

Linux 下需预先配置 TAP 网桥，Windows / WSL 下 TAP 支持有限。TAP 模式下 SSH 端口转发不可用。

## 4. QEMU 默认挂载设备

`qemu.py` 默认向虚拟机挂载以下设备（与驱动默认配置对应）。UFS 仅在 QEMU ≥ 8.2.0 时挂载；带触发条件的可选设备在表中标注。

| QEMU 设备 | 镜像文件 | RT-Thread 侧 |
| --------- | -------- | ------------ |
| `virtio-blk-device` | `virtio.qcow2` | VirtIO Block，根分区 `vda0` |
| `virtio-scsi-pci` + `scsi-hd` | `scsi.qcow2` | VirtIO SCSI |
| `scsi-cd`（可选 `-cdrom`） | 用户指定 | SCSI CD-ROM |
| `pflash`（index=1） | `flash.qcow2` | MTD NOR CFI |
| `sdhci-pci` + `sd-card` | `emmc.qcow2` | SDHCI eMMC（需启用 SDIO） |
| `nvme` + `nvme-ns` | `nvme.qcow2` | NVMe |
| `ahci` + `ide-hd` | `ahci.qcow2` | AHCI SATA |
| `ufs` + `ufs-lu`（仅 QEMU ≥ 8.2.0） | `ufs.qcow2` | UFS |
| `virtio-net-device` | — | VirtIO Net（需启用网络协议栈） |
| `virtio-rng-device` | — | VirtIO RNG |
| `virtio-crypto-device` | — | VirtIO Crypto |
| `virtio-serial-device` | — | VirtIO Console / RPROC Serial |
| `pci-serial`（8250 PCI） | — | PCI 8250 串口 |
| `intel-hda` + `hda-duplex` | — | Intel HDA 音频 |
| `i6300esb` | — | I6300ESB 看门狗 |
| `edu` | — | QEMU EDU 教学设备（MFD） |
| `virtio-gpu-device`（`-graphic`） | — | VirtIO GPU 2D（默认） |
| `virtio-gpu-gl-pci`（`-graphic -gl`） | — | QEMU OpenGL 显示设备；RT-Thread 侧无对应 GL 驱动 |
| `virtio-keyboard-device` / `virtio-tablet-device` | — | VirtIO Input |
| `virtio-9p-device`（`-9p`） | — | VirtIO 9P（需启用驱动） |
| `virtio-sound-pci`（`-sound virtio`） | — | VirtIO Sound |
| vfio-user 摄像头（`-camera <路径>`） | 宿主机 V4L2 设备 | PCI 摄像头（BSP `drv_camera`） |

## 5. 驱动支持情况

### 5.1 默认已启用

| 类别 | 驱动 | 说明 |
| ---- | ---- | ---- |
| 串口 | PL011 | UART0，系统控制台 `uart0` / `ttyAMA0` |
| 串口 | 8250 PCI | PCI 串口，Telnet 端口 4322 |
| RTC | PL031 | 实时时钟 |
| GPIO | PL061 | GPIO 控制器 |
| 看门狗 | I6300ESB | PCI 看门狗 |
| 存储 | VirtIO Block | 块设备，`vda` |
| 存储 | VirtIO SCSI | SD / CD-ROM |
| 存储 | AHCI PCI | SATA 磁盘 |
| 存储 | NVMe PCI | NVMe 磁盘 |
| 存储 | UFS PCI | UFS 磁盘 |
| 存储 | MTD NOR CFI | pflash 闪存 |
| 存储 | BLK 分区 | DFS / EFI 分区表 |
| 图形 | VirtIO GPU | 2D 帧缓冲（`-graphic`）；不含 OpenGL / VirGL |
| 图形 | Framebuffer | RAMFB 800×600（`RT_GRAPHIC_ROMFB_WIDTH` / `HEIGHT`，`drv_romfb.c`） |
| 图形 | LCD | LCD 设备框架 |
| 输入 | VirtIO Input | 键盘、鼠标、平板（`-graphic`） |
| 音频 | Intel HDA | 默认 `-sound hda` |
| 音频 | VirtIO Sound | `-sound virtio` |
| 加密 | VirtIO Crypto | VirtIO 加密后端 |
| 随机数 | VirtIO RNG | 硬件随机数 |
| 通信 | VirtIO Console | Telnet 4321 |
| 通信 | RPMSG | VirtIO RPMSG 字符设备 |
| 通信 | Mailbox PIC | 邮箱中断控制器 |
| 固件 | QEMU FW_CFG | 固件配置接口 |
| 总线 | PCI | ECAM + Generic Host，MSI / MSI-X |
| 其他 | MFD EDU | 多功能设备 |

### 5.2 默认未启用但可通过 menuconfig 开启

本 BSP 已启用 PCI 总线与 VirtIO PCI 传输，QEMU 中也已挂载对应设备。下列驱动在默认 `.config` 中未勾选，开启相应 Kconfig 选项并重新编译后即可使用（无需修改 `qemu.py`）：

| 驱动 / 功能 | Kconfig 要点 | QEMU 设备 | 说明 |
| ----------- | ------------ | --------- | ---- |
| VirtIO Net | `RT_USING_SAL` + `RT_USING_LWIP` + `RT_USING_ETHERNET` | `virtio-net-device` | 网络协议栈未默认启用 |
| VirtIO 9P | `RT_VIRTIO_9P` | `virtio-9p-device` | 配合 `-9p` 共享目录 |
| SDHCI eMMC | `RT_USING_SDIO` + `RT_SDIO_SDHCI_PCI` | `sdhci-pci` | eMMC 存储 |

> **说明**：凡标注 `depends on RT_USING_PCI` 的 PCI 类驱动，均可在此 BSP 上通过 menuconfig 启用；QEMU 侧若未挂载对应设备，需自行在 `qemu.py` 中添加 `-device` 参数。

### 5.3 BSP 特有功能（驱动层）

| 功能 | 配置项 | 启动方式 |
| ---- | ------ | -------- |
| RAMFB 分辨率 | `RT_GRAPHIC_ROMFB_WIDTH` / `RT_GRAPHIC_ROMFB_HEIGHT` | `-graphic`（`drv_romfb.c` 向 RAMFB 提供尺寸） |
| 摄像头驱动 | `RT_SOC_CAMERA` | `-camera <v4l2路径>`；`camera.c` 预览需加 `-graphic` |

### 5.4 示例应用（`applications/`）

| 源文件 | 编译条件 | 说明 |
| ------ | -------- | ---- |
| `main.c` | 始终编译 | 入口 `main()`，打印 `hello rt-thread` |
| `amp.c` | `RT_RPMSG_RT_THREAD_VIRTIO` | AMP 异构多核与 RPMSG 通信示例 |
| `camera.c` | `RT_SOC_CAMERA` | 摄像头画面叠加到 framebuffer |

**`main.c`**

默认应用，系统启动后输出 `hello rt-thread`，随后进入 msh。

**`amp.c`（AMP + RPMSG）**

QEMU `loader` 预先将 `amp.dtb` 与 `rtthread.bin` 加载到 `amp.dtsi` 指定地址，主核再通过 `amp_soc` 设备树节点与 PSCI 拉起从核 CPU。主从之间通过 VirtIO RPMSG + Mailbox 通信。主核将 VirtIO Block `vdb` 的资源信息写入从核 DTB 后启动从核。`qemu.py` 会为这颗额外 CPU 将 `-smp` 加 1。

**版本要求**：须 **Smart 版本**（menuconfig 中 `RT_USING_SMART`），且须使用 **`-mem 258`**。标准版内核必须在虚拟地址与物理地址一致的映射下运行；AMP 从核加载到独立物理内存区域（见 `amp.dtsi` 中 `amp_memory`、`kernel-entry` 等），不满足该约束，因此标准版无法用于 AMP 演示。

启动方式：

```
./qemu.py -dtbo amp.dtsi -mem 258
```

从核控制台：`telnet localhost 4323`。

msh 命令：

| 命令 | 说明 |
| ---- | ---- |
| `rpmsg_write <设备> <消息>` | 向 RPMSG 字符设备写入消息 |
| `rpmsg_read <设备>` | 读取 RPMSG 字符设备全部消息 |
| `amp_startup` | 手动触发 AMP 从核启动（同时启用控制台与 msh 时导出；否则自动在应用初始化阶段执行） |

系统启动时会自动创建 RPMSG 端点（`rpmsg_char0`，端点名 `rpmsg-char`，地址 114/514）。从核侧地址互换。

**`camera.c`（摄像头预览）**

将 vfio-user PCI 摄像头画面居中叠加到 framebuffer，默认设备 `camera0` → `fb0`，约 10 秒（300 帧）。

启动方式（Linux 宿主机，已安装 libvfio-user 且存在 V4L2 摄像头）：

```
./qemu.py -graphic -camera /dev/video0
```

msh 命令：

```
camera [摄像头设备] [framebuffer设备]
```

示例：`camera camera0 fb0`

## 6. 存储与分区

- 根文件系统默认挂载在 VirtIO Block 第一个分区 `vda0`，文件系统类型 `elm`（FatFs）。
- 各存储镜像首次运行自动创建为 64 MB `qcow2` 文件，可通过 `qemu-img` 扩容或预先替换。
- pflash0 用于 BootROM（如 UEFI），本 BSP 使用 pflash1（`flash.qcow2`）作为 CFI NOR；pflash0 数据在 QEMU 退出后不保留。
- Linux 下可使用 `qemu-nbd` + `fdisk` 对 `qcow2` 镜像分区（Windows 不支持）。

## 7. QEMU Monitor 热插拔提示

在 QEMU Monitor 中可动态增删 VirtIO 串口端口：

```
(qemu) chardev-add socket,host=127.0.0.1,port=4323,server=on,wait=off,telnet=on,id=console2
(qemu) device_add virtserialport,chardev=console2,name=org.rt-thread.port,id=port2
(qemu) device_del port2
(qemu) chardev-remove console2
```

VirtIO 设备可选参数（在 `qemu.py` 中按需添加）：

- 禁用 legacy：` -global virtio-mmio.force-legacy=false`
- Virtqueue packed：` -device virtio-XXX-device,packed=on`
- PCI 模式（≥ 1.0）：` -device virtio-XXX-pci,disable-legacy=on`

## 8. 修改配置后的注意事项

- 修改 CPU 数量后，重新编译使 `RT_CPUS_NR` 与之一致（或用 `qemu.py -smp` 覆盖）。`-dtbo` 模式下 `qemu.py` 会自动将 CPU 数加 1。
- 超过 8 核时 GIC 自动切换为 v3，也可手动指定 `-gic 3`。`gic-version=max` 仅在 `-el 2` 且 GICv3 时由脚本内部设置。
- 启用 9P 目录共享需 QEMU 编译时包含 virtfs（`--enable-virtfs`）。
- 使用 `-gl` 需 QEMU 编译时包含 OpenGL / VirGL（`--enable-opengl`、`--enable-virglrenderer`）；这与 RT-Thread 是否支持 OpenGL 无关，当前软件栈默认仅 2D 图形。
- AMP（`-dtbo`）须 Smart 版本内核（`RT_USING_SMART`）、`-mem 258`，且自动增加 CPU 数；标准版要求 VA=PA 运行，无法用于从核固定物理地址加载场景。
- `-camera` 须传入宿主机 V4L2 设备路径，仅支持 Linux，且需 libvfio-user；当前用户须能访问该设备（通常加入 `video` 组）；`-graphic` 仅 `camera.c` framebuffer 预览演示需要。
- 修改根设备或启动参数时，通过 `-bootargs` 覆盖默认参数。
