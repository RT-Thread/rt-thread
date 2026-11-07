# libcpu Kconfig 的 ARM 配置拆分说明

## 目的与范围

`libcpu/Kconfig` 原来同时包含 CPU 公共能力、跨架构内存管理、ARM 配置、其他架构配置及子配置文件入口。本次将 ARM 专属配置集中到 `libcpu/arm/Kconfig`，便于按架构维护。

本次只搬迁 ARM 配置，保留配置符号、类型、提示文字、默认值、依赖、选择关系和原有条件，不拆分其他架构，不新增菜单，不修改 BSP 配置。

## 文件职责

| 文件 | 职责 |
| --- | --- |
| `libcpu/Kconfig` | CPU 公共能力、跨架构内存管理、其他架构配置，以及子文件引用 |
| `libcpu/arm/Kconfig` | ARM 架构标识、内核型号及 ARM 专属能力 |
| `libcpu/aarch64/Kconfig` | 原有 AArch64 详细配置，本次不修改 |
| `libcpu/risc-v/Kconfig` | 原有 RISC-V 详细配置，本次不修改 |

新增文件沿用仓库已有的 `Kconfig` 大小写命名。

## 搬迁内容

- ARM 架构及内核标识：`ARCH_ARM`、所有 `ARCH_ARM_CORTEX_*`、`ARCH_ARM_ARM9`、`ARCH_ARM_ARM11` 和 `ARCH_ARMV8`。
- ARM 专属能力：`ARCH_ARM_BOOTWITH_FLUSH_CACHE`、`ARCH_ARM_MMU`、`ARCH_ARM_MPU` 和 `ARCH_ARM_SECURE_MODE`。
- Cortex-A 配套选项：`RT_SMP_AUTO_BOOT`、`RT_USING_GIC_V2`、`RT_USING_GIC_V3` 和 `RT_NO_USING_GIC`。
- 当前依赖 Cortex-A 的选项：`RT_IOREMAP_LATE` 和 `RT_BACKTRACE_FUNCTION_NAME`。

ARM 条目在新文件内保留原先的相对顺序。

## 引用与依赖处理

`libcpu/Kconfig` 在原 `ARCH_ARM_BOOTWITH_FLUSH_CACHE` 定义的位置无条件引入 ARM 子文件：

```kconfig
rsource "arm/Kconfig"
```

`rsource` 按当前 Kconfig 文件所在目录解析相对路径，且目标文件缺失时会报错。BSP 继续通过原有入口加载 `libcpu/Kconfig`，无需逐个调整引用。

引用外不增加 `if ARCH_ARM`。子文件本身定义 `ARCH_ARM`，各内核型号通过 `select` 选择该符号；额外增加条件会改变依赖关系，并可能形成循环依赖。

以下配置保留在公共文件：

- CPU 位宽、大小端、缓存、原子操作、栈方向和 FFS 等公共能力。
- `ARCH_MM_MMU`、`ARCH_MM_MPU`、`ARCH_REMAP_KERNEL`、`ARCH_USING_ASID` 等跨架构能力。
- `KERNEL_VADDR_START`：同时包含 ARM、ARMv8 和 RISC-V 的地址默认值，继续保留在 `if RT_USING_SMART` 内。

`RT_IOREMAP_LATE` 搬迁后单独保留 `if RT_USING_SMART`，并保留原有的 Cortex-A、MMU 依赖。GIC 等选项继续位于原有的 `if ARCH_ARM_CORTEX_A` 内。

`ARCH_ARMV8` 作为 ARM 架构标识一起搬迁；原有 `ARCH_ARMV8 && ARCH_CPU_64BIT` 条件下的 AArch64 子文件入口保持原样。

原文件中两处 `ARCH_ARM_CORTEX_R` 定义一起原样搬迁，不在此次合并；公共配置中重复的 `ARCH_CPU_STACK_GROWS_UPWARD` 也保持原样。

## 验证结果

使用 Kconfiglib 14.1.0，基于以下 BSP 工作区已有的 `.config`，比较搬迁前后的解析结果：

| BSP | 覆盖范围 | 比较结果 |
| --- | --- | --- |
| `bsp/frdm-k64f` | Cortex-M4 | 一致 |
| `bsp/qemu-vexpress-a9` | Cortex-A9、MMU、GIC | 一致 |
| `bsp/renesas/rzt2m_rsk` | Cortex-R52 | 一致 |
| `bsp/qemu-virt64-aarch64` | ARMv8、64 位及 AArch64 子配置 | 一致 |
| `bsp/qemu-virt64-riscv` | RISC-V 和公共配置 | 一致 |

比较覆盖全部解析符号的值、类型、可见性、可赋值范围、默认值、直接依赖、反向依赖，以及各定义节点的提示、依赖、`select` 和 `imply`。忽略文件路径及行号变化后，解析警告也与搬迁前一致，没有新增警告。

此外，在内存中为 Cortex-A9、AArch64 和 RISC-V BSP 启用 `RT_USING_SMART` 后再次比较，结果一致：

- Cortex-A9 的 `KERNEL_VADDR_START` 为 `0xc0000000`，并验证 `RT_IOREMAP_LATE` 可启用。
- AArch64 的 `KERNEL_VADDR_START` 为 `0xffff000000000000`。
- RISC-V 的 `KERNEL_VADDR_START` 为 `0xffffffc000000000`。

验证仅加载配置及在内存中调整选项，没有写入 BSP 的 `.config` 或 `rtconfig.h`，没有进行固件编译或运行验证。

## 后续验证方式

在已安装 Kconfiglib 的 Python 环境中，从待验证 BSP 的目录运行以下命令，可以检查配置解析及主要架构符号；该命令不写回配置文件：

```sh
python3 - <<'PY'
import kconfiglib

config = kconfiglib.Kconfig("Kconfig")
config.load_config(".config")
for name in ("ARCH_ARM", "ARCH_ARMV8", "ARCH_CPU_64BIT", "ARCH_RISCV"):
    print("{}={}".format(name, config.syms[name].str_value))
PY
```

需要复查等价性时，应在变更前后使用同一份 BSP 配置和同一版本的解析器，比较上述符号属性，并排除搬迁导致的诊断位置变化。上述简短命令只用于解析检查，不能替代完整的前后比较。
