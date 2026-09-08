# FRDM-MCXC162 BSP 说明

## 简介

本 BSP 面向量产版 FRDM-MCXC162，固定使用 `MCXC162VFT` Cortex-M23，内核运行
在 72 MHz FRO；不启用 FPU、TrustZone 和 MPU。

链接器只使用 `0x00000000` 起始的 64 KiB Program Flash，以及
`0x20000000` 起始的 12 KiB SRAM。位于 `0x0001C000` 的非连续 Data Flash 不会
拼入程序区。

## 支持接口

| RT-Thread 设备 | 芯片外设 | 板级引脚 | 默认状态 |
| --- | --- | --- | --- |
| `pin` | GPIO0-GPIO3 | `GET_PINS(port, pin)` | 开启 |
| `uart0` | LPUART0 | P0_2 RX、P0_3 TX | 开启，作为控制台 |
| `uart1` | LPUART1 | P2_12 RX、P2_13 TX | 关闭 |
| `uart2` | LPUART2 | P3_13 RX、P3_12 TX | 关闭 |
| `i2c0` | LPI2C0 | P3_27 SCL、P3_28 SDA | 关闭 |
| `spi0` | LPSPI0 | P3_10 SCK、P3_8 SDO、P3_9 SDI、P3_11 软件 CS | 关闭 |
| `rtc` | RTC0 | 内部 | 关闭 |
| `wdt` | WWDT0 | 内部 | 关闭 |
| `timer0`、`timer1` | CTIMER0、CTIMER1 | 内部 | 关闭 |
| `pwm0` 通道 0/1 | FLEXPWM0 SM0 A/B | P3_0、P3_1 | 关闭 |

PWM 两个通道共用周期。另一通道已经启用时，如果提交不同周期，驱动返回
`-RT_EINVAL`。

本版不支持 UART3、LPADC0、DMA、Data Flash、TRDC、低功耗和 tickless。

## 编译

先安装或更新 NXP MCX CMSIS 与 series package：

```console
pkgs --update
```

将 `RTT_EXEC_PATH` 指向编译器的可执行文件目录后编译：

```console
set RTT_CC=gcc
set RTT_EXEC_PATH=C:\path\to\arm-none-eabi\bin
scons -j8
```

主 GCC 基线为 MCUXpresso IDE 25.06 内置 Arm GNU Toolchain 14.2；另用 GCC
10.3.1 做兼容回归。SDK 26.06 的参考版本是 Keil MDK 5.43a（配合
`MCXC162_DFP 26.06.00`）和 IAR EWARM 9.70.4。工程可重新生成：

最终生成工程已使用 Keil MDK 5.42 + Arm Compiler 6.23 和 IAR EWARM
9.60.3.422 完成验证。本地未重复 SDK 参考版本 Keil 5.43a 与 IAR 9.70.4 的验证。

```console
set RTT_CC=keil
scons --target=mdk5
set RTT_CC=iar
scons --target=iar
```

Keil 应构建生成的 `project.uvprojx`，IAR 应构建生成的 `project.ewp`；
`template.*` 仅是工程生成器输入，不是构建目标。

```console
uVision.com -b project.uvprojx -j0
IarBuild.exe project.ewp -build Debug
```

## 默认运行现象

默认配置提供 1 kHz 系统 tick、115200-8-N-1 的 `uart0` 控制台和 MSH。低有效
红灯 P2_3 每 500 ms 翻转一次，应用不输出周期日志。

执行 `button_irq_test`，并在 10 秒窗口内分别按下 SW2 和 SW3；命令必须报告两键
都有非零下降沿中断计数。该等待窗口也可直观检查 RT-Thread 的 1 kHz tick。
执行 `reboot` 后，banner 和 MSH 提示符必须在软件复位后重新出现；硬复位则使用
板载 RESET 键做同样检查。

以下验收命令只在对应的可选 BSP 驱动开启后参与编译；默认 PIN + UART0 固件
不会带入额外测试代码。

两组 CI 验收配置可按下列命令构建：

```console
scons --attach=peripheral.communication
scons -j8
scons --attach=default
scons --attach=peripheral.timing_control
scons -j8
scons --attach=default
```

## 外设验收命令

测试其他 UART 时，继续用 `uart0` 作为 MSH 控制台。

| 项目 | 接线 | 命令 | 通过判据 |
| --- | --- | --- | --- |
| UART1 | Arduino D1/P2_13 TX 短接 D0/P2_12 RX | `uart_loop uart1` | 115200-8-N-1 回环 8 字节并输出 `PASS` |
| UART2 | mikroBUS TX/P3_12 短接 RX/P3_13 | `uart_loop uart2` | 115200-8-N-1 回环 8 字节并输出 `PASS` |
| P3T1755 | 无需接线；板载器件已连接 P3_27 SCL、P3_28 SDA | `p3t1755` | `0x48` 应答并打印一次温度 |
| SPI0 | Arduino D11/P3_8 SDO 短接 D12/P3_9 SDI；在 D13/P3_10 SCK、D10/P3_11 CS 测量 | `spi_loop` | 输出 `PASS`，且波形为 mode 0、1 MHz SCK、低有效 CS |
| CTIMER0 | 无需接线 | `ctimer0_test` | RT-Thread clock-time 后端完成一次 100 ms 单次定时 |
| CTIMER1 | 无需接线 | `ctimer_test timer1 oneshot`，再运行 `ctimer_test timer1 periodic` | 单次模式 1 次中断；周期模式 550 ms 内 4-6 次中断 |

`timer0` 由 RT-Thread clock-time 子系统独占打开，不能作为普通定时器设备再次
打开或控制。直接验证单次/周期设备接口时使用 `timer1`。

P3_11 由 RT-Thread 软件控制片选；LPSPI 内部改用未路由的 PCS，因此复合 SPI
消息之间 P3_11 会保持有效。本 BSP 只支持低有效软件片选。

`p3t1755` 把温度寄存器指针写入和两字节读取放在同一个双消息事务中，线上会
产生 repeated START，满足 ERR053261 的要求。

v1 I2C 适配要求每次 `rt_i2c_transfer()` 以 START 开始、以 STOP 结束；若首条
消息设置 `RT_I2C_NO_START`，或末条消息设置 `RT_I2C_NO_STOP`，请求会被拒绝。
仅发往同一地址的连续写消息允许使用 `RT_I2C_NO_START` 拼接。

WWDT 两种测试应分别在复位后执行。`wwdt refresh` 启动 3 秒看门狗并每秒喂狗，
期间没有周期输出；至少稳定运行 10 秒后按 RESET 结束。`wwdt timeout` 不喂狗，
MCU 应在约 3 秒后复位，下一次启动应打印
`last reset was caused by WWDT0`。

RTC set/get 和 PWM 控制直接复用 RT-Thread 标准 MSH 命令：

```console
date 2026 9 3 12 0 0
date
rtc_alarm_test

pwm probe pwm0
pwm set 0 1000000 250000
pwm enable 0
pwm set 1 1000000 500000
pwm enable 1
pwm get 0
pwm get 1
pwm disable 0
pwm disable 1
```

`rtc_alarm_test` 还需开启 `RT_USING_ALARM`，约 3 秒后应输出 `PASS`。PWM 测量点
为 Arduino D5/P3_0（通道 0）和 D6/P3_1（通道 1），相对 GND 应分别得到 1 kHz、
25% 和 50% 占空比。通道 0 已启用时执行
`pwm set 1 2000000 1000000`，必须返回 `-RT_EINVAL`，共享的 1 ms 周期不得改变。

## 实板验收

以下验证已在量产版 FRDM-MCXC162 Rev 1 实板上完成：

- banner、MSH、红灯、SW2 P3_14/SW3 P3_29 中断、软硬复位、1 kHz tick 和
  10 分钟稳定运行；
- UART1/UART2 跳线回环；
- `i2c0` 上板载 P3T1755 地址 `0x48` 应答及温度读取；
- SPI0 SDO→SDI 回环，并检查 SCK/CS；
- RTC 走时/alarm、WWDT refresh/故意超时复位、CTIMER 单次/周期模式，以及
  PWM 频率、占空比、启停和共享周期拒绝；
- Keil 与 IAR 分别完成下载、启动、tick、console 和 GPIO 验证。

针对 MCXC162 勘误 ERR053261，连续 LPI2C 读命令之间必须插入 STOP/START 或
repeated START。

实板烧写及 MCUXpresso IDE 下载配置由板卡使用者完成。

## 参考资料

- [FRDM-MCXC162 官方页](https://www.nxp.com/design/design-center/development-boards-and-designs/FRDM-MCXC162)
- [MCXC162 数据手册](https://www.nxp.com/docs/en/data-sheet/MCXCP048M072F20.pdf)
- [MCXC162 芯片勘误](https://www.nxp.com/docs/en/errata/MCXC162VFT_0P18R.pdf)
- [NXP MCXC162 device 文件](https://github.com/nxp-mcuxpresso/mcux-devices-mcx/tree/main/MCXC/MCXC162)
- [MCUX SDK 26.06 release notes](https://docs.mcuxpresso.nxp.com/mcuxsdk/26.06.00/html/boards/MCX/frdmmcxc162/releaseNotes/rnindex.html)
