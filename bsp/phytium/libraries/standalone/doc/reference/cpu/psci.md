# fpsci

## 1概述

PSCI 规范关注的是安全世界和正常世界之间进行电源管理的接口。
PSCI具有以下预期用途：

- 提供一个通用接口，监管软件可以使用该接口在以下情况下管理电源：
  - 核心空闲管理。（core idle management）
  - 动态添加和移除系统中的核心，通常称为热插拔。 （hotplug）
  - 辅助核心引导。（Secibdary core boot）
  - 在不同核心之间移动可信操作系统上下文。 (trusted)
  - 系统关机和重启。(system shutdown and reset)
- 提供一个接口，监管软件可以与固件表（FDT和ACPI）描述一起使用，以支持电源管理代码的通用化。

## 2驱动功能

组成由以下所示
.
├── fpsci.c
└── fpsci.h

本驱动为开发者提供了特性：

1. PSCI接口初始化以及function id 检查
2. 查看PSCI 版本信息功能
3. CPU_SUSPEND接口支持
4. CPU hotplug 接口支持
5. CPU Affinity power state 查看接口支持
6. 冷启动接口支持

## 3数据结构

## 4错误码定义

```c
#define FPSCI_SUCCESS			0
#define FPSCI_NOT_SUPPORTED			-1
#define FPSCI_INVALID_PARAMS			-2
#define FPSCI_DENIED				-3
#define FPSCI_ALREADY_ON			-4
#define FPSCI_ON_PENDING			-5
#define FPSCI_INTERNAL_FAILURE		-6
#define FPSCI_NOT_PRESENT			-7
#define FPSCI_DISABLED			-8
#define FPSCI_INVALID_ADDRESS		-9
```

## 5应用示例

/example/arch/armv8/fpsci --- 展示接口特性以及cpu hotplug 特性

## 6API使用步骤

1. 初始化PSCI模块，并且确定当前soc下支持哪些psci的functions

   ```c
    FPsciInit() ;
   ```
2. 初始化之后以下接口可以被正常使用：

   ```c
   FPsciVersion
   FPsciCpuSuspend
   FPsciCpuOn
   FPsciAffinityInfo
   FPsciSystemReset
   FPsciFeatureCheck
   FPsciCpuOff
   ```
3. hotplug 功能示例

   ```c
   /* 需要power down 的核心,假设次核心ID为1，主动调用以下接口实现CPU_OFF */
   FPsciCpuOff() ;
   /* Never get here */
   ```

   ```c
   /* 准备唤醒核心ID为1的CPU */
   unsigned long cpu_affinity ;
   GetCpuAffinity(1,&cpu_affinity) ;
   /* 其中0x80100000为核心1需要执行的地址 */
   FPsciCpuOn(cpu_affinity,0x80100000,0) ;
   ```

## 7API介绍

### 1. FPsciInit

```c
int FPsciInit(void)
```

#### 介绍

初始化 PSCI 驱动的接口函数。

#### 参数

无

#### 返回

- int: 返回值表示初始化结果，0 表示初始化成功，其他值表示初始化失败。

#### 功能描述

- 调用 FSmccInit 函数对 SMCC 接口进行初始化。
- 调用 FPsciVersion 函数获取 PSCI 的版本信息，并打印主版本号和次版本号。
- 调用 FPsciCheckFeatures 函数检查 PSCI 支持的接口是否可用。

### 2. FPsciSystemReset

```c
void FPsciSystemReset(u32 reset_type)
```

#### 介绍

重置系统的接口函数。

#### 参数

- u32 reset_type: 系统重置的类型（冷启动/热启动）。使用FPSCI_SYSTEM_RESET_TYPE_COLD 、FPSCI_SYSTEM_RESET_TYPE_WARM

#### 返回

无

#### 功能描述

- 该函数用于重置系统。通过 reset_type 参数指定重置的类型。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 使用 FASSERT 宏来检查相关条件是否满足，例如检查 fpsci_ringt_bit_flg 和 f_psci_invoke 是否已经初始化。

注意：

- 调用该函数将会重置整个系统，请谨慎使用。该接口是否有效也与固件有关

### 3. FPsciVersion

```c
int FPsciVersion(void)
```

#### 介绍

获取 PSCI 实现的版本信息的接口函数。

#### 返回

- int: PSCI 实现的版本信息。配合FPSCI_MAJOR_VERSION与 FPSCI_MINOR_VERSION 可以解析出版本号

#### 功能描述

- 该函数用于获取 PSCI 实现的版本信息，该信息从 PSCI VERSION 接口中获取。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 使用 FASSERT 宏来检查相关条件是否满足，例如检查 f_psci_invoke 是否已经初始化。
- 函数返回 PSCI 实现的版本信息，该信息存储在 f_psci_invoke 的返回值 res.a0 中。

### 4. FPsciCpuSuspend

```c
int FPsciCpuSuspend(u32 power_state, unsigned long entry_point_address, unsigned long context_id)
```

#### 介绍

暂停特定 CPU 的执行的接口函数。

#### 参数

- u32 power_state: 要进入的电源状态。
- unsigned long entry_point_address: 在唤醒时要执行的地址。
- unsigned long context_id: 上下文特定的标识符。

#### 返回

- int: 操作的状态代码，根据 PSCI 规范定义。

#### 功能描述

- 该函数用于暂停特定 CPU 的执行，并返回指示操作是否成功的状态代码。
- 函数参数 power_state 指定要进入的电源状态，entry_point_address 指定唤醒时要执行的地址，context_id 为上下文特定的标识符。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 使用 FASSERT 宏来检查相关条件是否满足，例如检查 f_psci_invoke 是否已经初始化。
- 函数返回操作的状态代码，该代码存储在 f_psci_invoke 的返回值 res.a0 中，状态代码的含义由 PSCI 规范定义。

### 5. FPsciCpuOn

```c
int FPsciCpuOn(unsigned long target_cpu, unsigned long entry_point_address, unsigned long context_id)
```

#### 介绍

启动特定 CPU 的接口函数。

#### 参数

- unsigned long target_cpu: 要启动的目标 CPU。
- unsigned long entry_point_address: 在唤醒时要执行的地址。
- unsigned long context_id: 上下文特定的标识符。

#### 返回

- int: 操作的状态代码，根据 PSCI 规范定义。

#### 功能描述

- 该函数用于启动特定 CPU，并返回指示操作是否成功的状态代码。
- 函数参数 target_cpu 指定要启动的目标 CPU，entry_point_address 指定唤醒时要执行的地址，context_id 为上下文特定的标识符。
- 根据目标 CPU 的位宽，选择相应的 PSCI_CPU_ON 接口 ID。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 使用 FASSERT 宏来检查相关条件是否满足，例如检查 f_psci_invoke 是否已经初始化。
- 函数返回操作的状态代码，该代码存储在 f_psci_invoke 的返回值 res.a0 中，状态代码的含义由 PSCI 规范定义。

### 6. FPsciAffinityInfo

```c
int FPsciAffinityInfo(unsigned long target_affinity, u32 lowest_affinity_level)
```

#### 介绍

获取特定关联级别的电源状态的接口函数。

#### 参数

- unsigned long target_affinity: 目标关联级别。
- u32 lowest_affinity_level: 最低关联级别。

#### 返回

- int: 指定关联级别的电源状态，根据 PSCI 规范定义。

#### 功能描述

- 该函数用于获取特定关联级别的电源状态，并返回该电源状态的代码。
- 函数参数 target_affinity 指定要获取电源状态的关联级别，lowest_affinity_level 指定最低关联级别。
- 根据目标关联级别的位宽，选择相应的 PSCI_AFFINITY_INFO 接口 ID。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 使用 FASSERT 宏来检查相关条件是否满足，例如检查 f_psci_invoke 是否已经初始化。
- 函数返回指定关联级别的电源状态代码，该代码存储在 f_psci_invoke 的返回值 res.a0 中，电源状态的含义由 PSCI 规范定义。

### 7. FPsciFeatures

```c
int FPsciFeatures(u32 psci_fid)
```

#### 介绍

检查是否支持某个 PSCI 功能的接口函数。

#### 参数

- u32 psci_fid: 要检查的 PSCI 功能的功能 ID。

#### 返回

- int: 如果支持该功能，则返回1；否则返回0。

#### 功能描述

- 该函数用于检查是否支持指定的 PSCI 功能。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 使用 FASSERT 宏来检查 f_psci_invoke 是否已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 函数返回值为1表示支持指定的 PSCI 功能，返回值为0表示不支持。

### 8. FPsciCpuOff

```c
int FPsciCpuOff(void)
```

#### 介绍

这是 PSCI CPU_Off 接口的包装函数，用于关闭当前 CPU。

#### 返回

- int: 返回 'FSmcccRes' 结构体的 'a0' 字段，表示调用的结果。返回值为 0 (PSCI_SUCCESS) 表示成功，其他任何值表示发生了错误。

#### 功能描述

- 该函数用于关闭当前 CPU，即将当前 CPU 关机。
- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 使用 FASSERT 宏来检查 f_psci_invoke 是否已经初始化。
- 函数内部通过调用 f_psci_invoke 函数实现 PSCI 接口的调用，并传递相应的参数。
- 函数返回值为 'a0' 字段，表示 PSCI 调用的结果。返回值为 0 表示成功，其他任何值表示发生了错误。

注意事项：

- 被 CPU_OFF 关闭的核心只能通过 CPU_ON 命令重新启动。


### 10. FPsciCpuMaskOn

```c
int FPsciCpuMaskOn(s32 cpu_id_mask, uintptr bootaddr)
```

#### 介绍

此函数用于根据 CPU ID 掩码将指定的 CPU 打开并进入指定的入口地址。

#### 参数

- s32 cpu_id_mask: CPU ID 掩码，用于指定要打开的 CPU。
- uintptr bootaddr: 要执行的入口地址。

#### 返回

- int: 函数执行的结果代码。返回值为 FPSCI_SUCCESS 表示成功，其他值表示错误。

#### 功能描述

- 通过调用 `GetCpuAffinityByMask` 函数获取与 CPU ID 掩码对应的 CPU 所属的集群。
- 如果获取集群失败，则返回 `FPSCI_INVALID_PARAMS` 错误。
- 否则，调用 `FPsciCpuOn` 函数将指定的集群打开，并进入指定的入口地址。
- 函数返回 `FPsciCpuOn` 函数的执行结果。

注意事项：

- 在调用此函数之前，请确保 PSCI 驱动已经初始化。
- 请确保 `GetCpuAffinityByMask` 函数已经正确实现，并能根据 CPU ID 掩码获取正确的 CPU 所属的集群信息。
