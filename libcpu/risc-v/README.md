# RISC-V libcpu 重构说明

本目录在 BSP 逐个迁移期间同时保留旧实现和新的统一实现。架构重构不应
通过一次提交强制所有 MCU 和 MMU BSP 更换 context、trap、中断和链接 ABI。

相关讨论：

- <https://github.com/RT-Thread/rt-thread/issues/11246>
- <https://github.com/RT-Thread/rt-thread/pull/11261>

## 构建路由

`RT_USING_RISCV_NEW_COMMON` 是唯一的新旧实现路由开关。该开关由已完成迁移的 BSP
`select`，不向用户显示。

| 配置 | libcpu 路径 |
| --- | --- |
| `RT_USING_RISCV_NEW_COMMON=y` | `common/` + 可选的新 vendor 目录，例如 `t-head/` |
| 未选择 | `legacy_common/` 或原有 `common64/`，再加原有 CPU/vendor 实现 |

旧 `common/` 已原样移到 `legacy_common/`；旧 `t-head/c906` 和 `t-head/c908` 已移到
`legacy-t-head/`。`common64/`、`rv64/` 和旧 `vector/` 在迁移期继续保留。旧
`virt64/` 随 QEMU BSP 迁移一并删除，因为已无其他 BSP 使用。
未选择新 common 的 BSP 仍走重构前的源文件组合，不得混入新 context 或新
vendor override。

## 配置宏责任

- `ARCH_RISCV` 表示 RISC-V 架构家族。
- `ARCH_RISCV32` 和 `ARCH_RISCV64` 是长期保留的 RISC-V 子架构选择符，
  选择新 common 的 BSP 必须按 XLEN 选择其中之一。`ARCH_RISCV64`
  同时选择通用属性 `ARCH_CPU_64BIT`，但 RISC-V 配置不用该通用属性
  取代子架构宏。未迁移 BSP 的宏选择在 legacy 阶段保持不变。
- `__riscv_xlen` 是汇编和寄存器布局代码中的位宽判断。
- `RT_USING_RISCV_NEW_COMMON` 只负责新旧 libcpu 路由，不表示 XLEN、特权级或 MMU。
- 选择新 common 后，架构目录统一提供 `_start`；BSP 根目录存在 `link.lds` 时使用
  BSP 脚本，否则自动生成公共脚本。`setup.c` 只随 `RT_USING_DM` 编译，不使用额外的
  源文件选择宏。
- `ARCH_RISCV_M_MODE`、`ARCH_MM_MMU`、`RT_USING_DM` 分别描述特权模式、内存管理
  和设备模型，它们之间不用 CPU 名称或 `virt64` 进行隐式推导。

## 目录结构

```text
libcpu/risc-v/
├── Kconfig
├── README.md
├── SConscript
├── link.lds.S
├── common/                 # 新的 RV32/RV64 统一实现
│   ├── include/
│   ├── pic/                # INTC, PLIC, CLIC, ACLINT, APLIC, IMSIC
│   ├── hwcache/
│   ├── serial/
│   └── vector/
├── t-head/                 # 新 common 的 T-Head override
├── legacy_common/          # 重构前的 MCU common
├── legacy-t-head/          # 重构前的 c906/c908 实现
├── common64/               # 未迁移 RV64 BSP 兼容实现
├── rv64/                   # 未迁移实现
└── vector/                 # 未迁移向量上下文
```

新 vendor 目录是架构级 override，不再复制整套 CPU port。当 vendor 提供
`mmu_vendor.h` 或 `opcode_vendor.h` 时，通用页表和指令头通过编译开关接入；
`cache.c` 和 `setup.c` 则通过 weak hook 覆盖。

## Hartid 映射

本轮重构不修改内核 `src` 的 master CPU 语义。RISC-V 侧维护 physical hartid 与
logical CPU id 的转换表：

1. 最先进入 RT-Thread 的 boot hart 注册为 logical CPU0。
2. DM 平台从 FDT `/cpus` 枚举剩余 hart；非 DM 平台可覆盖
   `riscv_hartid_list_get()` 提供枚举顺序。
3. SBI HSM、spinwait、IPI 和 per-CPU 中断初始化使用
   `riscv_cpu_id_to_hartid()` 和 `riscv_hartid_to_cpu_id()` 转换。

因此 QEMU/OpenSBI 选择任意 boot hart 时，调度器仍只看到连续的 CPU0..N。

## 当前验证边界

`bsp/qemu-virt64-riscv` 是第一个选择新 common 的 BSP，同一目录可构建 RV32
和 RV64 S-mode：

- RV32 默认使用 PLIC/ACLINT 和 legacy virtio-mmio，已验证 SMP、virtio block、
  virtio-net 和 msh。
- RV64 默认使用 APLIC/IMSIC，已验证 SMP、PCI MSI、NVMe、virtio block、
  virtio-net 和 msh；`-no-aia` 可切换到 PLIC/ACLINT。
- 当前 QEMU/OpenSBI 组合下，RV32 S-mode 访问 IMSIC `siselect/sireg` 会触发
  illegal instruction，因此 RV32 不默认启用 AIA 和 NVMe。这不限制通用 AIA
  驱动的 XLEN，但不将未验证组合设为 BSP 默认值。

新 common 不保留旧 MCU context、trap 或栈帧 ABI；未迁移 BSP 由
`legacy_common/` 完整承担。本轮重构不宣称尚未选择新实现的 MCU BSP
已完成迁移。新 common 的非 DM 移植接口见
[`common/README.md`](common/README.md)。

## BSP 迁移步骤

每个 BSP 应以独立 commit 迁移：

1. 保持原配置构建通过，确认它仍使用 legacy 路径。
2. 在 BSP Kconfig 中 `select RT_USING_RISCV_NEW_COMMON`，删除本地重复的 startup、
   context、timer、PIC 或 cache 代码。依赖 flash 数据搬运或特殊 reset 流程的 BSP，
   应先把所需能力整理为边界明确的早期平台 hook，再切换到新 common。
3. DM BSP 通过标准目录变量引入架构驱动 Kconfig，按实际需要设置：

   ```text
   SOC_DM_PIC_DIR      := $(RTT_DIR)/libcpu/risc-v/common/pic
   SOC_DM_SERIAL_DIR   := $(RTT_DIR)/libcpu/risc-v/common/serial
   SOC_DM_HWCACHE_DIR  := $(RTT_DIR)/libcpu/risc-v/common/hwcache
   ```

4. 按平台选择 M/S-mode、MMU/MPU、DM/非 DM 以及 PIC，不用 CPU 目录名推导功能。
5. 验证启动、tick、中断、线程切换；SMP 平台另验证非 0 boot hart 和全部
   secondary CPU。
6. DM BSP 再验证 OFW 和 ioremap；有 MMU 的 BSP 继续验证 PCI/MSI、DMA、
   存储和网络。

只有当最后一个 BSP 完成迁移后，才删除 `legacy_common/`、`legacy-t-head/`、
`common64/`、`rv64/` 和旧 `vector/`。
