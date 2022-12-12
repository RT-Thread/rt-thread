# README

- FT2004 rtos 驱动介绍

## 1. 当前版本

- V0.4.2

## 2. 关于此文档

- 本文档提供此项目框架性和基本功能介绍

- 详细的硬件 bsp 介绍请阅读 doc 文件中模块子文档。

## 3. 编译器版本

- gcc-arm-none-eabi-10-2020-q4-major

## 4. 文件结构介绍

| 目录名    | 内容                                     |
| --------- | ---------------------------------------- |
| bsp       | 存放芯片上的外设，例如网卡，i2c 和串口等 |
| component | 板载外设驱动 ,rtc、eeprom、sdmmc 等      |
| cpu       | cpu 架构方面指令                         |
| doc       | 具体外设文档                             |
| drivers   | 与不同 rtos 进行耦合的驱动               |
| gcc       | gcc 编译环境下的启动、链接文件           |
| include   | 平台相关的包含                           |

## 5. 支持外设

| 外设名   | 备注                   |
| -------- | ---------------------- |
| ft_gicv3 | gicv3 中断控制器       |
| ft_gmac  | ft gmac 千兆网卡控制器 |
| ft_i2c   | FT I2C                 |
| ft_qspi  | FT qspi 控制器         |
| ft_sd    | FT mmcsd 控制器        |
| ft_uart  | PrimeCell PL011        |
| ft_spi   | FT spi 控制器          |
| ft_gpio  | FT gpio 控制器         |
| ft_can   | FT can 控制器          |

## 6. 使用实例

[freertos](https://gitee.com/phytium_embedded/ft2004-freertos)

## 7. 参考资源

armv8 Architecture Reference Manual

FT-2000／4 软件编程手册-V1.4

FT-2000／4 硬件设计指导手册

FT-2000 四核处理器数据手册 V1.6

## 8. 贡献方法

请联系飞腾嵌入式软件部

huanghe@phytium.com.cn

zhugengyu@phytium.com.cn

## 9. 许可协议

Apache License.
