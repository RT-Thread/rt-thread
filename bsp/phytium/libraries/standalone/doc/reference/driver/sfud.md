# SFUD 驱动框架

## 1. 概述


- [SFUD Gitee](https://gitee.com/Armink/SFUD)
- SFUD 是一款开源的串行 SPI Flash 通用驱动库

## 2. 功能

- third-party/sfud-1.1.0
- 目前SFUD框架实现对接FSPIM驱动的对接，用于读写SPI Flash
```
├── Kconfig
├── inc
│   ├── sfud.h
│   ├── sfud_cfg.h
│   ├── sfud_def.h
│   └── sfud_flash_def.h
├── library.json
├── ports
│   └── f_spim
│       └── sfud_port.c
└── src
    ├── sfud.c
    └── sfud_sfdp.c
```

## 3. 配置方法

- 使能 CONFIG_USE_SFUD 配置
- 选择底层的SPI驱动，如CONFIG_USE_FSPIM
- 调用 SFUD 提供的 API 读写 SPI 从设备

## 4 应用示例

### [fspim_nor_flash](../../../baremetal/example/fspim_nor_flash/README.md)

## 4. API参考

- sfud.h 和 sfud_port.c 是主要需要对接的源文件
- 参考[SFUD API指南](https://gitee.com/Armink/SFUD/)