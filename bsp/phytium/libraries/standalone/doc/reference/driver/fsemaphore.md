# FSemaphore 驱动程序

## 1. 概述

硬件信号量（Semaphore）是E2000提供的一个二值信号量模块，支持 32 个硬件信号量。每个信号量包括 UNLOCK 和 LOCKED 两个状态

## 2. 功能

FSemaphore 驱动程序主要完成 Semaphore 模块的初始化，锁的分配、获取与释放，
相关源文件为：
```
fsemaphore
    .
    ├── fsemaphore.c
    ├── fsemaphore.h
    ├── fsemaphore_g.c
    ├── fsemaphore_hw.h
    └── fsemaphore_sinit.c
```

## 3. 配置方法

以下部分将指导您完成 FSemaphore 驱动的软件配置:

- 初始化 Semaphore 控制器
- 获取 Semaphore 锁
- 加锁/解锁操作

## 4. 应用示例

### [Semaphore加锁解锁测试](../../../baremetal/example/peripheral/ipc/fsemaphore_test)

## 5. API参考


### 5.1. 用户数据结构

#### FSemaConfig

- Semaphore控制器配置

```c
typedef struct 
{
    u32 id;             /* Semaphore控制器id */
    uintptr base_addr;  /* Semaphore控制器基地址 */
} FSemaConfig; /* Semaphore控制器配置 */
```

#### FSemaLocker

- Semaphore锁实例

```c
typedef struct
{
    u32 index;                              /* Semaphore锁id */
#define FSEMA_LOCKER_NAME_LEN       32U
    char name[FSEMA_LOCKER_NAME_LEN];       /* Semaphore锁的名字 */
    u32 owner;                              /* Semaphore锁的拥有者 */
    FSema *sema;                            /* Semaphore控制器实例 */
} FSemaLocker; /* Semaphore锁实例 */
```

#### FSema

- Semaphore控制器实例

```c
typedef struct _FSema
{
    FSemaConfig config;                       /* Semaphore控制器配置 */
    u32 is_ready;                             /* Semaphore控制器初始化是否完成 */
    FSemaLocker *locker[FSEMA_NUM_OF_LOCKER]; /* Semaphore锁实例，locker[i] == NULL 表示锁尚未分配 */
} FSema; /* Semaphore控制器实例 */
```
### 5.2  错误码定义

FSEMA_SUCCESS                   ：成功 
FSEMA_ERR_NOT_INIT              ：控制器未初始化
FSEMA_ERR_NO_AVAILABLE_LOCKER   ：没有空闲的锁可以分配
FSEMA_ERR_LOCK_TIMEOUT          ：锁被占用，获取锁失败
FSEMA_ERR_NO_PERMISSION         ：当前角色没有权限操作

### 5.3. 用户API接口

#### FSemaLoopkupConfig

```c
const FSemaConfig *FSemaLoopkupConfig(u32 instance_id)
```

Note:

- 获取Semaphore的默认配置

Input:

- {u32} instance_id, Semaphore的实例id

Return:

- {const FSemaConfig *} Semaphore的默认配置

#### FSemaCfgInitialize

```c
FError FSemaCfgInitialize(FSema *const instance, const FSemaConfig *input_config)
```

Note:

- 初始化Semaphore控制器

Input:

- {FSema} *instance, Semaphore控制器实例
- {FSemaConfig} *input_config, Semaphore控制器配置

Return:

- {FError} FSEMA_SUCCESS 表示初始化成功

#### FSemaDeInitialize

```c
void FSemaDeInitialize(FSema *const instance)
```

Note:

- 去初始化Semaphore控制器

Input:

- {FSema} *instance, Semaphore控制器实例

Return:

- 无

#### FSemaCreateLocker

```c
FError FSemaCreateLocker(FSema *const instance, FSemaLocker *const locker)
```

Note:

- 分配和创建Semaphore锁

Input:

- {FSema} *instance, Semaphore控制器实例
- {FSemaLocker} *locker, Semaphore锁的实例

Return:

- {FError} FSEMA_SUCCESS 表示分配成功

#### FSemaDeleteLocker

```c
FError FSemaDeleteLocker(FSemaLocker *const locker)
```

Note:

- 强制解除Semaphore锁并删除锁实例

Input:

- {FSemaLocker} *locker, Semaphore锁实例

Return:

- {FError} FSEMA_SUCCESS 表示删除锁成功

#### FSemaTryLock

```c
FError FSemaTryLock(FSemaLocker *const locker, u32 owner, u32 try_times, FSemaRelaxHandler relax_handler)
```

Note:

- 尝试获取Semaphore锁

Input:

- {FSemaLocker} *locker, Semaphore锁的实例
- {u32} owner, 当前尝试获取锁的是谁
- {u32} try_times, 尝试获取的次数
- {FSemaRelaxHandler} relax_handler, 每次尝试获取锁失败后的relax函数

Return:

- {FError} FSEMA_SUCCESS 表示成功获取锁，FSEMA_ERR_LOCK_TIMEOUT 表示锁已经被占用

#### FSemaUnlock

```c
FError FSemaUnlock(FSemaLocker *const locker, u32 owner)
```

Note:

- 尝试释放Semaphore锁

Input:

- {FSemaLocker} *locker, Semaphore锁实例
- {u32} owner, 当前尝试释放锁的身份

Return:

- {FError} FSEMA_SUCCESS释放锁成功

#### FSemaUnlockAll

```c
FError FSemaUnlockAll(FSema *const instance)
```

Note:

- 强制解除所有Semaphore锁

Input:

- {FSema} *instance, Semaphore控制器实例

Return:

- {FError} FSEMA_SUCCESS表示强制解锁成功

#### FSemaIsLocked

```c
boolean FSemaIsLocked(FSemaLocker *locker)
```

Note:

- 检查指定Semaphore锁是否处于锁定状态

Input:

- {FSemaLocker} *locker, Semaphore锁实例

Return:

- {boolean} TRUE: 处于锁定状态

