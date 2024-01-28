# cvitek bsp

## 支持芯片
针对算能系列 RISC-V 芯片的 bsp，包括：

| 芯片名称 | 内存大小 |
| ------- | ------- |
| cv1800b | 64MByte |
| | |

## FAQ
1. 如遇到不能正常编译，请先使用 `scons --menuconfig` 重新生成配置。
2. 编译成功后，会在 `bsp/cvitek` 目录下自动生成 `fip.bin` 和 `boot.sd` 文件。
