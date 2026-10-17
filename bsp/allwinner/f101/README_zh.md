# YuzukiNeko（Allwinner F101S3）

[English](README.md)

本 BSP 面向 YuzukiNeko 开发板。这是一块树莓派 Pico 尺寸的单板计算机，使用
Allwinner F101S3（Sun252i F101）SoC；C907 内核为 RV32IMAFDC。SoC 内置的
16 MiB LPSRAM 位于 `0x40000000`，RT-Thread 镜像链接并加载到 `0x40010000`。

驱动均基于 RT-Thread Device Model（DM）和
`bsp/allwinner/dm/dts` 中的内嵌设备树实现，不依赖 `libraries/sunxi-hal`。

## 板卡介绍

| 项目 | YuzukiNeko 硬件信息 |
| --- | --- |
| SoC | Allwinner F101S3，单核 T-Head C907 RISC-V，最高 1 GHz |
| 内存 | 16 MiB 内置 LPSRAM |
| 启动存储 | 16 MiB SPI NOR Flash（PY25Q128HA） |
| 可移动存储 | microSD 卡槽，SDC0 |
| USB 与供电 | USB Type-C，提供 5 V 供电、USB 2.0 device 与 FEL 访问 |
| 扩展 | 两组 20-pin 排针，提供 GPIO、ADC、5 V、3.3 V 和 GND |
| 音频 | HPOUT 模拟音频焊盘 |
| 按键与指示 | FEL 烧录按键和电源指示灯；没有复位按键 |
| 尺寸 | 约 51 x 21 mm |

UART1 位于 H2-11（PB0/TX）和 H2-10（PB1/RX），115200 8N1。这两根信号线与
Type-C 的 SBU 路由共用，连接 USB 数据线时可能干扰外接串口适配器。

## 工具链

需要具备 RV32 `imafdc` 和 `ilp32d` multilib 的裸机 GNU 工具链。下面下载的是
RT-Thread CI 使用的 `riscv64-unknown-elf` 工具链。虽然前缀为 `riscv64`，其
内容包含本 BSP 所需的 RV32 multilib。

```sh
toolchain_url=https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz
mkdir -p "$HOME/opt/riscv64-unknown-elf"
curl -L "$toolchain_url" | tar -xz -C "$HOME/opt/riscv64-unknown-elf" --strip-components=1
export RTT_EXEC_PATH="$HOME/opt/riscv64-unknown-elf/bin"
export RTT_CC_PREFIX=riscv64-unknown-elf-
riscv64-unknown-elf-gcc -v
```

其它兼容的 GNU 工具链同样只需设置这两个环境变量。SCons 可由 RT-Thread ENV
安装，也可以使用 `python -m pip install scons` 安装。

## 构建

```sh
scons --menuconfig
scons
```

`YuzukiNeko boot privilege mode` 默认选择直接 M-mode 启动。只有已安装的 boot firmware 能通过 SBI 进入 RT-Thread，且传入标准 RISC-V 启动参数时，才应选择 S-mode。

构建产物如下：

- `rtthread.elf`：用于调试和符号解析；
- `rtthread.bin`：加载地址为 `0x40010000` 的裸镜像。

### 显示屏选择与验证

`YuzukiNeko display` 一次只能选择一种板级显示配置。默认的
`ST77916 360x360 QSPI LCD` 对应现有的 QSPI 屏；选择
`CO6300 262x928 one-lane MIPI-DSI AMOLED` 后，BSP 会启用 OSPTEK
AM319M262928ZS 的 DE0、TCON0 与单 lane RGB888 MIPI-DSI 输出。显示模组的
VCI 供电应由转接板预先保持为使能状态。DSI 使用 PD12 至 PD21，因此不能和
ST77916 的 SPI1 屏配置同时使用。

该模组的触摸控制器为 CST3530，I2C 地址是 `0x58`。CO6300 板级配置默认将
它接到 I2C2（`PB2`/SDA、`PB3`/SCL），频率为 400 kHz，并以 20 ms 周期轮询，
因此只连接 I2C 两线即可使用。若额外连接了模组的中断和复位线，可在 DTS 节点
中添加 `interrupt-gpios`、`reset-gpios`，驱动会自动改用中断上报和硬件复位。

DE framebuffer 注册为 `fb0`。启动后可使用以下命令验证 DE 扫描输出和 G2D：

```text
g2d_test
g2d_anim
```

`g2d_test` 会将填充、BitBlt、缩放、旋转和 alpha 混合的结果显示到 `fb0`；
`g2d_anim` 持续执行缩放和旋转合成。两个命令都可以额外指定 `g2d` 和
framebuffer 设备名。准备兼容的 JPEG 或 MJPEG AVI 文件后，`jpegshow` 和
`mjpegplay` 还可用于验证 JPEG 解码和 framebuffer 显示路径。

## 下载与运行

本 BSP 只生成裸 `rtthread.bin`，不会替换 boot ROM、boot0、GPT 或板级启动配置。
M-mode 启动固件将 `rtos` 负载复制到 `0x40010000`，然后跳转到 `_start`。选择 S-mode
时，启动固件则必须经 SBI 进入，并传入标准 RISC-V 启动参数。

### SPI NOR 烧录

F101 的 FEL 访问使用当前版本的 [xboot/xfel](https://github.com/xboot/xfel)。在主机上
构建工具，按住板子的 FEL 按键上电；`xfel version` 应显示 `F101`。

```sh
git clone https://github.com/xboot/xfel.git
make -C xfel
XFEL=$PWD/xfel/xfel
$XFEL version
$XFEL spinor
```

不要将 `rtthread.bin` 直接写入 SPI NOR。应保留当前 TOC 中的 `melis-config` 条目，使用
板子既有的 `package_rtos.cfg` 和 Allwinner `dragonsecboot` 打包工具，将其与新的 `rtos`
条目一起封装为 `sunxi-package` 格式的 `boot_package.fex`。备份后只替换 `bootA` 包：

```sh
$XFEL spinor read 0xe0000 0x154000 f101-boota-backup.fex
$XFEL spinor write 0xe0000 boot_package.fex
$XFEL reset
```

`0xe0000` 是出厂 16 MiB SPI NOR 布局中 `bootA` 分区的起始位置。使用相同的
`spinor write` 命令写回备份即可恢复原 RTOS 包。不要覆盖 flash 偏移零或 GPT。

## 设备驱动支持

| 设备 | 状态 | 说明 |
| --- | --- | --- |
| ADC | 支持 | - |
| AUDIO | 支持 | - |
| UART | 支持 | - |
| DMA | 支持 | - |
| HWCrypto | 支持 | - |
| I2C | 支持 | - |
| SPI | 支持 | - |
| PWM | 支持 | - |
| Flash | 支持 | SPI-NOR/MTD |
| SDIO | 支持 | - |
| USB | 支持 | CDC ACM character-device |
| Watchdog | 支持 | - |
| IR-RX | 支持 | - |
| RTC | 支持 | - |
| Display | 支持 | QSPI ST77916 或 MIPI-DSI CO6300；RGB/LVDS/DSI 后端 |
| Touch | 支持 | CO6300 模组的 CST3530 |
| G2D | 支持 | - |
| Video | 支持 | - |

## 参考资料

- [YuzukiNeko 硬件工程](https://github.com/YuzukiHD/YuzukiNeko)
- [YuzukiNeko 使用文档](https://dshanpi.100ask.net/docs/F101-YuzukiNeko/)
- [OSPTEK AM319M262928ZS CO6300 屏幕参考工程](https://github.com/osptek/amoled-3.19-262x928-mipi-co6300)
- [OpenixSuit 发布页](https://github.com/YuzukiTsuru/OpenixSuit/releases)
