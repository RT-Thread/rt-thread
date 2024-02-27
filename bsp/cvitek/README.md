# cvitek bsp


## 支持芯片
针对算能系列 RISC-V 芯片的 bsp，包括：

- 大核

| 芯片名称 | 芯片架构 | 内存大小 | 默认日志串口 | 备注 |
| ------- | ------- |------- | -------- | -------- |
| cv1800b | RISC-V C906 | 64MByte | uart0 | 默认开启 MMU，运行 RT-SMART 模式 |

- 小核

| 目录 | 内存大小 | 默认日志串口 | 备注 |
| ---- | ------- | -------- | --- |
| c906-little | 与大核共享 | uart1 | 无 MMU，运行 RT-Thread 标准 |

> 注：异构芯片需单独编译每个核的 OS


## 运行

编译成功后，会在 `bsp/cvitek` 目录下自动生成 `fip.bin` 和 `boot.sd` 文件，其中大核运行文件在 `boot.sd` 中，小核的运行文件在 `fip.bin` 中。

1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。
2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制 SD 卡第一个分区中。
	- fip.bin：fsbl、 opensbi、uboot、小核运行文件打包后的 bin 文件
	- boot.sd：大核打包后的 bin 文件

## 驱动支持列表

| 驱动 | 支持情况 | 备注              |
| :--- | :------- | :---------------- |
| uart | 支持     | 默认波特率115200 |
| gpio | 支持 |  |
| i2c  | 支持 |  |
| adc | 支持 |  |

## 支持开发板
- milk-v duo: [https://milkv.io/duo](https://milkv.io/duo)

## FAQ
1. 如遇到不能正常编译，请先使用 `scons --menuconfig` 重新生成配置。

## 联系人信息

维护人：[flyingcys](https://github.com/flyingcys)