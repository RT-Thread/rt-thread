<!--
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * FilePath: fnand.md
 * Date: 2022-06-07 19:57:17
 * LastEditTime: 2022-06-07 19:57:18
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
-->

# 驱动概述
- NAND 作为廉价的存储介质，在大文件的存储场景中占有重要的地位，由此在嵌入式方案中，如何将此驱动做稳定做易用，尤为重要。NAND 控制器驱动具有以下特性:

1. 支持模式 Toggle 介质模式
2. 支持模式时序配置 ，同步模式，异步模式
3. 支持请求之间时间间隔
4. 采用dma 数据方式进行传输
5. 支持时序模式下的高频时钟采样相位调节
6. 支持硬件ECC纠错
当前NAND 驱动控制器主要为用户提供了以下功能接口:
1. NAND 控制器状态初始化函数
2. NAND 介质扫描接口
3. NAND 介质page读/写接口，块擦除接口，spare space 读写接口
4. 中断相关接口
5. 坏块管理接口

##  驱动功能

驱动组成由以下所示 :

.
├── fnand_bbm.c
├── fnand_bbm.h
├── fnand.c
├── fnand_dma.c
├── fnand_dma.h
├── fnand_ecc.c
├── fnand_ecc.h
├── fnand_g.c
├── fnand.h
├── fnand_hw.c
├── fnand_hw.h
├── fnand_intr.c
├── fnand_option.c
├── fnand_sinit.c
├── fnand_timing.c
├── fnand_timing.h
├── fnand_toggle.c
└── fnand_toggle.h

其中fnand.h 为用户开发者主要使用接口，提供了以下功能:
1. Nand 控制器初始化接口
2. 根据Nand 介质id 初始化介质页/块的大小
3. Nand 控制器相关状态位的回调函数注册
4. Nand 控制器中断处理函数
5. Nand 坏块管理函数


## 数据结构
```c
    typedef struct _FNand
    {
        u32 is_ready; /* Device is ininitialized and ready*/
        FNandConfig config;
        u32 work_mode;              /* NAND controler work mode */

        /* nand flash info */
        FNandInterMode inter_mode[FNAND_CONNECT_MAX_NUM]; /* NAND controler timing work mode */
        FNandTimingMode timing_mode[FNAND_CONNECT_MAX_NUM];
        u32 nand_flash_interface[FNAND_CONNECT_MAX_NUM] ; /* Nand Flash Interface , followed by FNAND_ONFI_MODE \ FNAND_TOGGLE_MODE*/

        struct FNandDmaBuffer dma_data_buffer;          /* DMA data buffer */
        struct FNandDmaBuffer descriptor_buffer;        /* DMA descriptor */
        struct FNandDmaDescriptor descriptor[2];        /* DMA descriptor */
        struct FNandSdrTimings sdr_timing;              /* SDR NAND chip timings */

        /* bbm */
        FNandBadBlockManager bbt_manager[FNAND_CONNECT_MAX_NUM];    /* bad block manager handler */
        /* nand detect */
        FNandNandGeometry nand_geometry[FNAND_CONNECT_MAX_NUM];     /* nand flash infomation */
        /* dma 页操作 */
        FnandIrqEventHandler irq_event_fun_p;                       /* Interrupt event response function */
        void *irq_args;

        FNandOperationWaitIrqCallback wait_irq_fun_p;               /* The NAND controller operates the wait function */
        void *wait_args;        

        /* operations */
        FNandTransferP write_p ;                                    /* Write page function */
        FNandTransferP read_p ;                                     /* Read page function */
        FNandTransferP write_oob_p ;                                /* Write page spare space function */
        FNandTransferP read_oob_p ;                                 /* Read page spare space function */
        FNandTransferP write_hw_ecc_p ;                             /* Write page with hardware function */
        FNandTransferP read_hw_ecc_p ;                              /* Read page with hardware function */
        FNandEraseP erase_p;                                        /* Erase block  function */
    } FNand;
```

## 错误码定义
```
FNAND_ERR_OPERATION					/* NAND 控制器操作NAND flash 失败 */
FNAND_ERR_INVAILD_PARAMETER			/* 当NAND 控制器配置信息不存在 */
FNAND_IS_BUSY							/* NAND 控制器操作NAND flash ,控制器正忙 */
FNAND_OP_TIMEOUT						/* NAND  控制器操作超时*/
FNAND_VALUE_ERROR						/* NAND 控制器在进行BBM 搜索过程时，获取坏块管理信息不匹配 */
FNAND_VALUE_FAILURE						/* 获取的数据与预期不相符合 */
FNAND_NOT_FET_TOGGLE_MODE			/* toggle 模式 */
FNAND_ERR_READ_ECC						/* 读取过程中，进行硬件ecc ，错误超过纠错的范围 */
FNAND_ERR_IRQ_OP_FAILED                 /* 中断进行读/写/擦操作时，回调函数反馈错误 */
FNAND_ERR_IRQ_LACK_OF_CALLBACK          /* 中断进行读/写/擦操作时，缺少回调函数 */
FNAND_ERR_IRQ_OP_FAILED                 /* 等待中断回应失败 */
FNAND_ERR_NOT_MATCH                     /* 进行flash id 检测时，检测结果与预期不符合    */
```
## 应用例程
- baremetal/example/peripheral/nand/nand_test
## API 介绍

### 1. FNandLookupConfig

```
FNandConfig *FNandLookupConfig(u32 instance_id)
```

#### 介绍
- 获取当前FNand驱动默认配置

#### 参数
- u32 instance_id :当前Nand驱动中对应的ID

#### 返回
FGicConfig * :静态默认配置


### 2. FNandCfgInitialize

```
FError FNandCfgInitialize(FNand *instance_p,FNandConfig *config_p)
```

#### 介绍
- 根据传入配置，初始化NAND驱动实例

#### 参数
- FNand *instance_p  FNand 控制器实例的指针
- FNandConfig * 需要应用于示例中的配置项

#### 返回
- FError :FT_SUCCESS 为初始成功

### 3. FNandScan

```
FError FNandScan(FNand *instance_p)
```

#### 介绍
- Nand flash 扫描，此接口调用之后会自动扫描Nand flash 介质信息

#### 参数
- FNand *instance_p  FNand 控制器实例的指针

#### 返回
- FError :FT_SUCCESS 为初始成功

### 4. FNandWritePage

```
FError FNandWritePage(FNand *instance_p,u32 page_addr,u8 *buffer,u32 page_copy_offset ,u32 length,u8 *oob_buffer,u32 oob_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 每次写一个页面的操作，包括写页面数据和空闲数据 ，默认会进行硬件ecc 编码写入

#### 参数
- FNand *instance_p  FNand 控制器实例的指针
- u32 page_addr     页操作地址，单位为页
- u8 *buffer	      指向写入内容缓冲区的指针
- u32 page_copy_offset 写入某一页中的具体位置，当此参数非0 时，写入的地址为 ，在page_addr 对应的页面下，0 + page_copy_offset 开始的地址，未覆盖的地方默认填入0xff
- u32 length 		  数据写入页面下的长度
- u8 *oob_buffer	  指向写入spare space内容 缓冲区的指针
- u32 oob_copy_offset 写入某一页中spare space 的具体位置，当此参数非0 时，在page_addr 对应的页面下，写入的地址为 页长度 + page_copy_offset 开始的地址，未覆盖的地方默认填入0xff
- u32 oob_length      spare space数据写入页面下的长度
- u32 chip_addr		   芯片地址

#### 返回
- FError :FT_SUCCESS 为写入成功

### 5. FNandWritePageRaw

```
FError FNandWritePageRaw(FNand *instance_p,u32 page_addr,u8 *buffer,u32 page_copy_offset ,u32 length,u8 *oob_buffer,u32 oob_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 每次写一个页面的操作，包括写页面数据和空闲数据 ，默认不会进行硬件ecc 编码写入

#### 参数
- FNand *instance_p  FNand 控制器实例的指针
- u32 page_addr     页操作地址，单位为页
- u8 *buffer	      指向写入内容缓冲区的指针
- u32 page_copy_offset 写入某一页中的具体位置，当此参数非0 时，写入的地址为 ，在page_addr 对应的页面下，0 + page_copy_offset 开始的地址，未覆盖的地方默认填入0xff
- u32 length 		  数据写入页面下的长度
- u8 *oob_buffer	  指向写入spare space内容 缓冲区的指针
- u32 oob_copy_offset 写入某一页中spare space 的具体位置，当此参数非0 时，在page_addr 对应的页面下，写入的地址为 页长度 + page_copy_offset 开始的地址，未覆盖的地方默认填入0xff
- u32 oob_length      spare space数据写入页面下的长度
- u32 chip_addr		   芯片地址

#### 返回
- FError :FT_SUCCESS 为写入成功


### 6. FNandReadPage

```
FError FNandReadPage(FNand *instance_p,u32 page_addr,u8 *buffer,u32 page_copy_offset,u32 length,u8 *oob_buffer,u32 oob_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 每次读出一个页面的操作，包括读页面数据和空闲数据 ，默认会进行ecc 纠错

#### 参数
```
FNand *instance_p  FNand 控制器实例的指针
u32 page_addr     页操作地址，单位为页
u8 *buffer	      指向读出内容缓冲区的指针
u32 page_copy_offset 读出某一页中的具体位置，当此参数非0 时，读出的地址为 ，在page_addr 对应的页面下 0 + page_copy_offset 开始的地址
u32 length 		  数据读出页面下的长度
u8 *oob_buffer	  指向读出spare space内容 缓冲区的指针
u32 oob_copy_offset 读出某一页中spare space 的具体位置，当此参数非0 时，在page_addr 对应的页面下，读出的地址为 页长度 + page_copy_offset 开始的地址
u32 oob_length      spare space数据读出的长度
u32 chip_addr		   芯片地址
```


#### 返回
- FError :FT_SUCCESS 为读出成功

### 7. FNandReadPageRaw

```
FError FNandReadPageRaw(FNand *instance_p,u32 page_addr,u8 *buffer,u32 page_copy_offset,u32 length,u8 *oob_buffer,u32 oob_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 每次读出一个页面的操作，包括读页面数据和空闲数据 ，不会进行ecc 纠错

#### 参数
```
FNand *instance_p  FNand 控制器实例的指针
u32 page_addr     页操作地址，单位为页
u8 *buffer	      指向读出内容缓冲区的指针
u32 page_copy_offset 读出某一页中的具体位置，当此参数非0 时，读出的地址为 ，在page_addr 对应的页面下 0 + page_copy_offset 开始的地址
u32 length 		  数据读出页面下的长度
u8 *oob_buffer	  指向读出spare space内容 缓冲区的指针
u32 oob_copy_offset 读出某一页中spare space 的具体位置，当此参数非0 时，在page_addr 对应的页面下，读出的地址为 页长度 + page_copy_offset 开始的地址
u32 oob_length      spare space数据读出的长度
u32 chip_addr		   芯片地址
```


#### 返回
- FError :FT_SUCCESS 为读出成功

### 8. FNandEraseBlock

```
FError FNandEraseBlock(FNand *instance_p, u32 block, u32 chip_addr)
```

#### 介绍
- 擦除块数据

#### 参数
FNand *instance_p  FNand 控制器实例的指针
u32 block 		  块的位置号
u32 chip_addr		  芯片地址

#### 返回
- FError :FT_SUCCESS 为写入成功



### 9. FNandReadPageOOb

```
FError FNandReadPageOOb(FNand *instance_p,u32 page_addr,u8 *oob_buffer,u32 oob_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 读取每一页中的 spare space 内容

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- u32 page_addr	  需要读取空闲空间的Row Address 
- u8 * oob_buffer	  指向读取数据的缓冲区
- u32 oob_copy_offset 读出某一页中spare space 中位置的偏移，当此参数非0 时，读出的地址为 ，在page_addr 对应的页面下 page length +  oob_copy_offset 开始的地址
- u32 	oob_length 	   需要读取是页面中spare space 中的长度
- u32 chip_addr		  芯片地址

#### 返回
- FError :FT_SUCCESS 为写入成功

### 10. FNandWritePageOOb


```
FError FNandWritePageOOb(FNand *instance_p,u32 page_addr,u8 *oob_buffer,u32 page_copy_offset,u32 oob_length,u32 chip_addr)
```

#### 介绍
- 读取每一页中的 spare space 内容

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- u32 page_addr	  需要写入空闲空间的Row Address 
- u8 * oob_buffer	  指向写入数据的缓冲区
- u32 oob_copy_offset 写入某一页中spare space 中位置的偏移，当此参数非0时，写入的地址为 ，在page_addr 对应的页面下 page length +  oob_copy_offset 开始的地址
- u32 oob_length 	   需要写入是页面中spare space 中的长度
- u32 chip_addr		  芯片地址

#### 返回
- FError :FT_SUCCESS 为写入成功


### 11. FNandSetIsrHandler

```
void FNandSetIsrHandler(FNand *instance_p, FnandIrqEventHandler event_p, void *irq_args)
```

#### 介绍
- 初始化中断事件回调函数

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- FnandIrqEventHandler event_p 中断事件回调函数
- void *irq_args 	       回调函数传入参数

#### 返回
无

### 12. FNandIrqHandler

```
void FNandIrqHandler(s32 vector, void *param)
```

#### 介绍
- Nand 控制器中断响应函数

#### 参数
- s32 vector  中断ID
- void * param 中断传入参数 

#### 返回
- 无

### 13. FNandInitBbtDesc

```
void FNandInitBbtDesc(FNand *instance_p)
```

#### 介绍
- 坏块表初始化

#### 参数
- FNand *instance_p   FNand 控制器实例的指针

#### 返回
- 无


### 10. FNandScanBbt

```
FError FNandScanBbt(FNand *instance_p, u32 target_addr)
```

#### 介绍
- 在Nand flash中扫描具体目标地址的坏块表

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- u32 chip_addr		  芯片地址

#### 返回
- FError :FT_SUCCESS 为扫描成功

### 11. FNandIsBlockBad

```
FError FNandIsBlockBad(FNand *instance_p, u32 block, u32 target_addr)
```
#### 介绍
- 检查当前块是否为坏块

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- u32 block			   需要检查的块ID号
- u32 chip_addr		  芯片地址

#### 返回
- FError :FT_SUCCESS 为当前块为坏块

### 12. FNandOperationWaitIrqRegister 

```
void FNandOperationWaitIrqRegister(FNand *instance_p,FNandOperationWaitIrqCallback wait_irq_fun_p ,void *wait_args)
```

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- FNandOperationWaitIrqCallback 用户使用读/写/擦接口过程中，等待中断完成的回调函数接口 ，用户的回调函数，驱动以FT_SUCCESS 作为成功判断，否则为失败
- void *wait_args     用户需要传入至回调函数中的参数

### 返回

无


### 13. FNandSetOption

- 依据options 选项参数，配置对应参数

```c
FError FNandSetOption(FNand *instance_p,u32 options,u32 value)
```

#### 参数
- FNand *instance_p   FNand 控制器实例的指针
- u32 option 具体配置项
- u32 value  配置项中对应的参数

