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

[中文](README_zh.md)

# HPM SDK Overview
The HPM SDK Project is a software development kit based on HPMicro's MCUs, which supports a wide range of MCUs, based on the BSD license, including drivers, middleware and RTOS, such as littlevgl/ lwIP/ TinyUSB/ FreeRTOS, etc. It supports a large number of Boards.

## SDK Directory Structure

| Name | Description |
|--------|--------|
| <HPM_SDK_BASE>/arch | cpu architecture |
| <HPM_SDK_BASE>/boards | board support files |
| <HPM_SDK_BASE>/cmake | cmake extensions |
| <HPM_SDK_BASE>/components | software components |
| <HPM_SDK_BASE>/docs | documentation |
| <HPM_SDK_BASE>/drivers | low level driver files |
| <HPM_SDK_BASE>/middleware | middleware files |
| <HPM_SDK_BASE>/samples | sample source for drivers, middleware, components |
| <HPM_SDK_BASE>/scripts | util scripts |
| <HPM_SDK_BASE>/soc | SoC specific source |
| <HPM_SDK_BASE>/utils | util source |

## SDK Documentation
- Local:
  SDK documentation can be built locally, once it's done, it can be accessed with the following entries:
  - <HPM_SDK_BASE>>/docs/index.html
  - <HPM_SDK_BASE>>/docs/index_zh.html
  > Please refer to for [hpm_sdk Getting Started](docs/en/get_started.md) more details about documentation building.
- Online:
  - http://hpm-sdk.readthedocs.io/
  - http://hpm-sdk-zh.readthedocs.io/

## Repositories
- hpm_sdk: https://github.com/hpmicro/hpm_sdk
- sdk_env: https://github.com/hpmicro/sdk_env
- sdk extra demo: https://github.com/hpmicro/hpm_sdk_extra
- openocd (hpmicro patched): https://github.com/hpmicro/riscv-openocd
- gnu gcc toolchain: https://github.com/hpmicro/riscv-gnu-toolchain

> Note: repositories are mirrored on gitee.
