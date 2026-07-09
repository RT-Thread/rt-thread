# BSP 贡献规范

本文说明新增或调整 BSP 时应遵循的目录层级关系，避免把板级、芯片级和架构级代码混放。

## BSP 目录层级

BSP 目录根据共享代码所在层级，主要分为厂商级共享和厂商 + 系列级共享两类。无论采用哪种结构，都应遵循以下原则：

- `board/` 放置板级初始化、引脚、时钟、链接脚本等只属于当前开发板的内容。
- 上层或同级共享 `libraries/` 放置同一厂商或同一系列 BSP 共用的芯片库、HAL、CMSIS、SDK、驱动和驱动适配代码，驱动目录也应放在 `libraries/` 下。
- 同级 `tools/` 放置同一厂商或同一系列 BSP 共用的辅助脚本。

若多个 BSP 共用同一个软件包或 SDK，不应在每个 BSP 目录下重复维护，应放在共享层级或使用软件包机制，并由 BSP 通过构建脚本引用。新增 BSP 时不要随意新建额外层级，也不要把 BSP 代码放入 `components/`、`src/`、`include/` 等非 BSP 目录；抽象驱动框架属于 `components/drivers/`，芯片或 CPU 架构公共移植代码属于 `libcpu/`。

### 厂商级共享目录结构（以 STM32 为例）

STM32 BSP 通常直接位于 `bsp/stm32/<board>`，同一厂商下多个 BSP 共用的驱动适配、模板、工具和软件包选择放在 `bsp/stm32/libraries/` 与 `bsp/stm32/tools/`：

```text
bsp/stm32/
├── libraries/
│   ├── HAL_Drivers/        # STM32 BSP 共用的驱动适配
│   ├── drivers/            # 多个 STM32 BSP 共用的驱动（如有）
│   ├── templates/          # 新增 BSP 参考模板
│   └── Kconfig             # 原厂 HAL/CMSIS 软件包选择
├── tools/                  # 厂商级辅助脚本
├── stm32f407-atk-explorer/
│   ├── board/              # 当前开发板专用的初始化、引脚、时钟、链接脚本
│   ├── Kconfig
│   ├── SConscript
│   └── SConstruct
└── stm32f429-atk-apollo/
    ├── board/
    ├── Kconfig
    ├── SConscript
    └── SConstruct
```

### 厂商 + 系列级共享目录结构（以 NXP 为例）

NXP 这类 BSP 通常会先按厂商、产品线或芯片系列分层，再把当前系列共用的驱动适配、模板、工具和软件包选择放在系列目录下。例如 i.MX RT 使用 `bsp/nxp/imx/imxrt/libraries/`，LPC55S 使用 `bsp/nxp/lpc/lpc55sxx/libraries/`，MCX 按 `mcxa`、`mcxc`、`mcxe`、`mcxn` 等系列分别维护 `libraries/`。

NXP 目录下也存在一些历史 BSP，例如 `lpc176x` 这类单 BSP 目录，或少量旧目录使用 `Libraries/` 命名。新增或重构 BSP 时不应继续扩散旧结构；若驱动、SDK 或模板需要被多个 BSP 复用，应迁移或放入对应系列的 `libraries/` 与 `tools/` 层级。

```text
bsp/nxp/
├── imx/
│   └── imxrt/
│       ├── libraries/
│       │   ├── drivers/        # i.MX RT 系列共用的驱动和驱动适配
│       │   ├── templates/      # 新增 BSP 参考模板
│       │   └── Kconfig         # NXP i.MX RT SDK 软件包选择
│       ├── tools/              # 当前系列 BSP 共用的辅助脚本
│       └── imxrt1052-nxp-evk/
│           ├── board/          # 当前开发板专用的初始化、引脚、时钟、链接脚本
│           ├── Kconfig
│           ├── SConscript
│           └── SConstruct
├── lpc/
│   └── lpc55sxx/
│       ├── libraries/          # LPC55S 系列共用的驱动适配、模板和软件包选择
│       ├── tools/
│       └── lpc55s69_nxp_evk/
│           ├── board/
│           ├── Kconfig
│           ├── SConscript
│           └── SConstruct
└── mcx/
    ├── tools/                  # MCX 系列共用工具
    └── mcxn/
        ├── libraries/          # MCXN 系列共用的 CMSIS、系列驱动和软件包选择
        └── frdm-mcxn947/
            ├── board/
            ├── Kconfig
            ├── SConscript
            └── SConstruct
```

### 原厂 HAL/SDK 软件包

若原厂 HAL、CMSIS 或 SDK 已经以 RT-Thread 软件包形式提供，BSP 不应再提交或维护重复的完整源码副本。BSP 应通过 `Kconfig` 选择相应 `PKG_USING_*` 软件包，并在 `SConscript` 中按配置引用软件包内容；`pkgs --update` 负责下载软件包源码。

这种情况下，`libraries/` 主要保留驱动适配、可复用驱动、模板、工具脚本和软件包选择逻辑。不要把 `pkgs --update` 下载出的软件包目录作为 BSP 源码提交，也不要让 `scons --dist` 打包当前 BSP 没有启用的软件包或库文件。

## 提交要求

- 新增 BSP 应保持层级清晰，只提交当前开发板必需的板级文件。
- 同一厂商或同一系列 BSP 共用的库、驱动适配、可复用驱动、模板和脚本应放在共享 `libraries/` 或 `tools/` 层级，避免在多个 BSP 中重复拷贝。
- 驱动适配代码和可复用驱动应放在 `libraries/` 下，不应放在单个开发板目录中。
- 原厂 HAL、CMSIS 或 SDK 已软件包化时，应优先通过软件包机制引用，不应在 BSP 中重复提交软件包源码。
- 构建脚本应从共享层级引用公共代码，`scons --dist` 打包时不应带入当前 BSP 不需要的软件包或库文件。
