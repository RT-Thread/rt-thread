
# Memory pool

## 1. 概述

内存池 (Memory Pool)是一种内存分配方式，是为了减少频繁使用 malloc/free new/delete 等系统调用而造成的性能损耗而设计的，具有效率高、内存碎片少和防止内存泄漏等特性。内存池根据实际需要，在初始状态获取一大块内存（堆区或者静态内存），然后划分成若干内存页，进行管理，将内存页中的块传递给申请者使用。SDK中采用TLSF内存分配器管理，专门设计用于满足实时要求。

TLSF (Two-Level Segregated Fit memory allocator), 是一款通用的动态内存分配器，具有以下特点，

- malloc，free，realloc，memalign的算法复杂度变为O(1)
- 每次分配的开销极低（4字节）
- 低碎片化
- 支持动态添加和删除内存池区域

TLSF主要采用两级位图(Two-Level Bitmap)与分级空闲块链表(Segregated Free List)的数据结构管理动态内存池(memory pool)以及其中的空闲块(free blocks)，用Good-Fit的策略进行分配。

TLSF算法分配速度不一定快，只是说能保证分配的时间是个常数（malloc不能保证）。

TLSF也叫多内存堆管理算法，支持动态增加或者删除多块不连续的内存，将它们作为一个内存堆使用。

## 2. 功能

FMemory Pool主要完成内存池的初始化，为用户提供多种内存申请方法，支持内存池的使用情况监测，
- 初始化内存池
- 删除内存池
- 申请一段空间（不要求对齐）
- 按指定字节数申请一段对齐的内存
- 申请一段数组，返回被清零的空间
- 回收原来申请的空间并重新分配
- 跟踪当前内存池的使用情况

相关源文件为：
```
fmempory_pool
    ├── fmempory_pool.c
    └── fmempory_pool.h
```

```
tlsf
    ├── tlsf.c
    └── tlsf.h
```

## 3. 配置方法

以下部分将指导您完成 FMemory Pool 的软件配置:
- 使能TLSF组件

## 4. 应用示例

### [memory pool](../../../baremetal/example/system/memory_pool_test)

## 5. API参考

### 5.1. 用户数据结构

- common/fmempory_pool.h

```c
typedef struct
{
    pool_t     pool_addr;
    FSListNode list;
} FMempPoolList; /* 内存池控制数据 */

typedef struct
{
    FMempPoolList *pools_list;   /* 内存池链表 */
    tlsf_t         tlsf_ptr;     /* tlsf内存池 */
    u32            is_ready;     /* 内存池初始化完成标志 */
} FMemp; /* 内存池控制数据 */
```

### 5.2  错误码定义

- 模块错误码编号 `0x0010000`

- [0x0] FMEMP_SUCCESS : success

- [0x0010000] FMEMP_ERR_INVALID_BUF : 输入的内存池缓存区不合法

- [0x0010001] FMEMP_ERR_INIT_TLFS : 初始化TLFS内存池失败

- [0x0010002] FMEMP_ERR_BAD_MALLOC : 从TLFS内存池分配空间失败

### 5.3. 用户API接口

#### FMempInit
- 初始化内存池, 分配内存池的内存空间

```c
FError FMempInit(FMemp *memp, void *begin_addr, void *end_addr);
```

Note:

- begin_addr end_addr 指向为内存池指定的缓冲区的起止地址

Input:

- {FMemp} *memp, 内存池的控制数据
- {void} *begin_addr, 分配给内存池的空间起始地址
- {void} *end_addr, 分配给内存池的空间结束地址

Return:

- {FError} FMEMP_SUCCESS表示初始化成功，返回其它值表示初始化失败

#### FMempRemove

- 释放所有分配的内存，删除内存池

```c
void FMempRemove(FMemp *memp);
```

Note:

- 需要初始化后才能调用，调用此函数后，内存池分配的空间不再能使用

Input:

- {FMemp} *memp 内存池控制数据   

Return:

- 无

#### FMempMalloc

- 从内存池申请一段空间

```c
void *FMempMalloc(FMemp *memp, fsize_t nbytes);
```

Note:

- 需要初始化后才能调用，申请的空间再不再使用后需要调用FMempFree释放

Input:

- {FMemp} *memp 内存池控制数据
- {fsize_t} nbytes 申请的字节数

Return:

- {void *} 申请到的空间，如果申请失败，返回NULL

#### FMempCalloc

- 从内存池申请一段数组空间并清零

```c
void *FMempCalloc(FMemp *memp, fsize_t count, fsize_t size)
```

Note:

- 需要初始化后才能调用，申请的空间再不再使用后需要调用FMempFree释放

Input:

- {FMemp} *memp 内存池控制数据
- {fsize_t} count 数据成员格式
- {fsize_t} size 单个数据成员的字节数

Return:

- {void *} 申请到的空间，如果申请失败，返回NULL

#### FMempMallocAlign

- 按指定对齐方式申请一段空间

```c
void *FMempMallocAlign(FMemp *memp, fsize_t size, fsize_t align);
```

Note:

- 需要初始化后才能调用，申请的空间再不再使用后需要调用FMempFree释放

Input:

- {FMemp} *memp 内存池控制数据
- {fsize_t} size 申请的字节数
- {fsize_t} align 对齐字节数

Return:

- {void *} 申请到的空间，如果申请失败，返回NULL

#### FMempRealloc

- 回收原来申请的空间并重新分配

```c
void *FMempRealloc(FMemp *memp, void *ptr, fsize_t nbytes);
```

Note:

- 需要初始化后才能调用，申请的空间再不再使用后需要调用FMempFree释放，调用函数后，原来的空间不再能使用，原空间的数据被移动到返回指针指向的空间

Input:

- {FMemp} *memp 内存池控制数据
- {void} *ptr 原来的空间
- {fsize_t} nbytes 新申请的字节数

Return:

- {void *} 替换后空间，如果替换失败，返回NULL

#### FMempFree

- 释放一段从内存池申请的空间

```c
void FMempFree(FMemp *memp, void *ptr);
```

Note:

- 需要初始化后才能调用，传入的指针需要是FMempMalloc/FMempCalloc/FMempMallocAlign/FMempRealloc返回的

Input:

- {FMemp} *memp 内存池控制数据
- {void} *ptr 待释放的空间地址

Return:

- 无

#### FMemProbe

- 跟踪当前内存池的使用情况

```c
void FMemProbe(FMemp *memp, u32 *total, u32 *used, u32 *max_used);
```

Note:

- 需要初始化后才能调用

Input:

- {FMemp} *memp 内存池控制数据
- {u32} *total 总可用字节数
- {u32} *used 已使用字节数
- {u32} *max_used 已使用字节数的峰值

Return:

- 无

#### FMemListAll

- 打印当前分配的内存块信息

```c
void FMemListAll(FMemp *memp);
```

Note:

- 需要初始化后才能调用

Input:

- {FMemp} *memp 内存池控制数据

Return:

- 无