MIPSSIM 板级支持包


---

## 1. 简介

本BSP用于在MIPSSIM或QEMU的MIPSSIM Machine模拟器中运行RT-Thread。
使用mips-sde-elf工具链编译。
在QEMU中使用如下命令运行：
```
qemu-system-mipsel -M mipssim -cpu P5600 -nographic -kernel ./rtthread.elf
```

MIPSSIM拥有一个8250串口和一个MIPSNET网卡外设，本BSP目前仅实现了串口。