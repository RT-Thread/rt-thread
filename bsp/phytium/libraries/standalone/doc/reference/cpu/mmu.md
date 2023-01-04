<!--
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: mmu.md
 * Date: 2022-02-22 16:26:16
 * LastEditTime: 2022-02-22 16:26:16
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
-->

# MMU 

## 1. 概述

- 虚拟内存系统（VMSA）提供了一套内存管理单元（MMU）， 它控制着地址转换、访问权限和内存属性的确定和检查。

- 地址转换过程将CPU使用的虚拟地址(VAs)映射到物理内存系统的物理地址(PAs)上。

- 在本SDK中 aarch32 state 采用 section 格式的转换表
- 在本SDK中 aarch64 state 采用 4KB 粒度 格式的转换表

## 2. 功能

- MMU功能支持用户根据需要修改MMU表的默认内存属性。

## 3. 配置方法

## 4. 应用示例

"baremetal/example/system/amp/libmetal_test"
"baremetal/example/system/amp/openamp"

## 5. API参考


### 5.1 用户定义


/* 访问权限 */
```
#define MT_P_NA_U_NA  /* higher Exception level access=NA, user=NA */
#define MT_P_RW_U_NA  /* higher Exception level access=RW, user=NA */
#define MT_P_RW_U_RO  /* higher Exception level access=RW, user=RO */
#define MT_P_RW_U_RW  /* higher Exception level access=RW, user=RW */
#define MT_P_RO_U_NA  /* higher Exception level access=RO, user=NA */
#define MT_P_RO_U_RO  /* higher Exception level access=RO, user=RO */
```

/* 内存属性参数 */
```
#define MT_DEVICE_NGNRNE       /* Device-nGnRnE , Outer Shareable */
#define MT_DEVICE_NGNRE        /* Device-nGnRE , Outer Shareable */

#define MT_NORMAL_WT           /* Outer and Inner Write-Through, Read-Allocate No Write-Allocate , Outer Shareable  */

#define MT_NORMAL_WB_WCN       /* Outer and Inner Write-Back, Read-Allocate No Write-Allocate , Outer Shareable  */

#define MT_NORMAL_NC          /* Outer and Inner Non-cacheable , Outer Shareable , Outer Shareable */
#define MT_NORMAL             /* Outer and Inner Write-Back, Read-Allocate Write-Allocate , Outer Shareable , Outer Shareable  */

```

### 5.2 用户API接口

- 此函数用于配置转换表中地址对应条目的内存属性与访问权限

```c
void FSetTlbAttributes(uintptr addr, fsize_t size, u32 attrib);
```

    Note:
        aarch32 state 采用 section 页表，由此addr 建议采用1MB 地址对齐，size 建议为MB的整数倍。
        aarch64 state 采用 4KB 粒度 页表，由此addr 建议采用4KB 地址对齐，size 建议为4KB的整数倍。

    Input:

    - addr ， 需要为内存区域设置属性与权限的起始地址

    - size ， 内存区域的范围

    - attrib，指定内存区域的属性 ,内存属性的取值由 访问权限 与 内存属性参数 组成，具体类型参考 ### 5.1 用户定义

    Return:

    - void
