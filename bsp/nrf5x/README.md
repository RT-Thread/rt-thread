# nRF5x BSP 框架

## 1. 目录结构

```
nrf5x
├───docs 
│   └───figures                     // 文档使用图片
│   └───nRF5x系列BSP制作教程.md
├───libraries                       
│   └───drivers                     // nRF5x 系列设备通用驱动文件 
│   └───templates                   // 通用设备 BSP 工程模板
│   │   └───nrf51x                  // nrf51x 系列 BSP 工程模板
│   │   │   nrf52x                  // nrf52x 系列 BSP 工程模板
│   │   └───nrf5x_board_kconfig     // 通用 BSP 工程配置文件
├───nrf52832                        // nrf52832 BSP 工程
│   └───application                 // 应用代码
│   │   board                       // 链接脚本文件，开发板硬件初始化和配置文件
│   │   package                     // 软件包目录
│   │   └───nRF5_SDK                // nordic 官方 nRF5x SDK
│   │   kconfig                     // 工程配置文件
│   └───rtconfig.h
├───nrf52840                        // nrf52840 BSP 工程
└───README.md                       
```