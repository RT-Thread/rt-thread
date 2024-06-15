``` mermaid
gantt
    title HPM SDK Release Plan
    dateFormat  YYYY-MM-DD
    section Mainline Release
    v1.5.0           :a1, 2024-01-01, 2024-03-31
    v1.6.0           :a2, 2024-04-01, 2024-06-30
    v1.7.0           :a3, 2024-07-01, 2024-09-30
    v1.8.0           :a4, 2024-10-01, 2024-12-31
```

[English](README.md)

# HPM SDK 概述
HPM SDK项目是基于HPMicro 公司的MCU编写的软件开发包，支持多种MCU。基于BSD许可证，包含了底层驱动，中间件和RTOS，例如littlevgl/ lwIP/ TinyUSB/ FreeRTOS等，支持大量评估板。

## HPM SDK 目录结构

| 目录名称 | 描述 |
|--------|--------|
| <HPM_SDK_BASE>/arch | cpu架构相关文件 |
| <HPM_SDK_BASE>/boards | 板级文件 |
| <HPM_SDK_BASE>/cmake | cmake扩展 |
| <HPM_SDK_BASE>/components | 软件组件 |
| <HPM_SDK_BASE>/docs | 文档 |
| <HPM_SDK_BASE>/drivers | 底层驱动文件|
| <HPM_SDK_BASE>/middleware | 中间件 |
| <HPM_SDK_BASE>/samples | 驱动、中间件以及软件组件示例代码 |
| <HPM_SDK_BASE>/scripts | 辅助脚本 |
| <HPM_SDK_BASE>/soc | SoC相关文件 |
| <HPM_SDK_BASE>/utils | 辅助文件 |

## SDK文档
- 本地文档:
  SDK文档可以进行本地编译，成功编译之后可以通过以下入口访问本地文档:
  - <HPM_SDK_BASE>>/docs/index.html
  - <HPM_SDK_BASE>>/docs/index_zh.html
  > 文档编译方式请参考[hpm_sdk Getting Started](docs/zh/get_started.md)
- 在线文档：
  - http://hpm-sdk.readthedocs.io/
  - http://hpm-sdk-zh.readthedocs.io/

## 代码仓库
- hpm_sdk github: https://github.com/hpmicro/hpm_sdk
- sdk_env github: https://github.com/hpmicro/sdk_env
- sdk extra demo: https://github.com/hpmicro/hpm_sdk_extra
- openocd (hpmicro patched): https://github.com/hpmicro/riscv-openocd
- gnu gcc toolchain: https://github.com/hpmicro/riscv-gnu-toolchain

> 仓库在gitee上有对应的镜像。
