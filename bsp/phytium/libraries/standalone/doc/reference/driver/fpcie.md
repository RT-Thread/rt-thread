# FPCIE 驱动程序

## 1. 概述


- PCIe总线使用端到端的连接方式，在一条PCIe链路的两端只能各连接一个设备，这两个设备互为是数据发送端和数据接收端。PCIe总线除了总线链路外，还具有多个层次，发送端发送数据时将通过这些层次，而接收端接收数据时也使用这些层次。似

- FPCIE 模块内置两个 PCIE 单元（PCI-E Unit，PEU），分别为 PEU0 和 PEU1。每个 PEU 包含 3 个控制器：C0、C1 和 C2。当 PEU 拆分模式为 X16 时，C1 不可见。

- 本模块特点如下

1. 支持 Root Complex 和 End Point 两种模式；
2. 共 34 lane，两路 X16（可拆分为 2 个 X8）和两路 X1；
3. 内部集成 DMA 引擎，一读一写两个通道。

## 2. 功能


- 驱动相关的源文件如下，
- drivers/pcie/fpcie

```
.
├── fpcie.c
├── fpcie.h
├── fpcie.md
├── fpcie_common.h
├── fpcie_config.c
├── fpcie_dma.c
├── fpcie_dma.h
├── fpcie_ep.c
├── fpcie_g.c
├── fpcie_hw.c
├── fpcie_hw.h
├── fpcie_misc.c
├── fpcie_sinit.c
├── fpcir_intx.c
└── fspim.md
```

## 3. 配置方法

以下部分将指导您完成 PCIE 驱动的软件配置:

- 初始化PCIE控制器
- 通过API 获取特定设备的 bar 空间地址
- 使用INTX 中断响应设备中断响应函数
- 使用DMA模式完成数据通信

## 4. 应用示例

"/baremetal/example/peripheral/fpcie_probe "

## 5. API参考

### 5.1 用户数据结构



- 中断注册回调函数

```c 
   typedef struct
    {
        void (*IntxCallBack)(void *args) ;
        void *args ;
        s32 bdf ;
    } FPcieIntxFun;
```

- 初始化配置空间地址

```c
    struct FPcieRegion {
        FPcieAddr bus_start;	        /* Start on the bus */
        FPciePhysAddr phys_start;	/* Start in physical address space */
        FPcieSize size;	            /* Size */
        unsigned long flags;	    /* Resource flags */
        FPcieAddr bus_lower;
        u32 exist_flg;              /* exist flg */
    };
```

- 驱动配置数据

```c
    typedef struct
    {
        u32 instance_id; /* Id of device */
        u32 irq_num;     /* Irq number */ 
        uintptr_t ecam;  /* The Memory way */
        uintptr_t peu0_config_address;
        uintptr_t peu1_config_address;
        
        uintptr_t control_c0_address;
        uintptr_t control_c1_address;
        uintptr_t control_c2_address;
        uintptr_t control_c3_address;
        uintptr_t control_c4_address;
        uintptr_t control_c5_address;
        
        u32 io_base_addr;
        u32 io_size ;
        u32 npmem_base_addr;
        u32 npmem_size;
        u64 pmem_base_addr; /* Prefetchable memory */
        u64 pmem_size;

        u8 inta_irq_num ;
        u8 intb_irq_num ;
        u8 intc_irq_num ;
        u8 intd_irq_num ;
        u8 need_skip    ;

    } FPcieConfig;
```

- 驱动控制数据

```c
    typedef struct
    {
        u32 is_ready; /* Device is ininitialized and ready*/
        FPcieConfig config;

        struct FPcieRegion mem;
        struct FPcieRegion mem_prefetch;
        struct FPcieRegion mem_io;

        s32  bus_max; /* 当前最大bus num */

        FPcieIrqCallBack fpcie_dma_rx_cb;
        void *dma_rx_args;

        FPcieIrqCallBack fpcie_dma_tx_cb;
        void *dma_tx_args;

        FPcieIrqCallBack fpcie_dma_rx_error_cb;
        void *dma_rx_error_args;

        FPcieIrqCallBack fpcie_dma_tx_error_cb;
        void *dma_tx_error_args;

        FPcieIntxFun inta_fun;

        FPcieIntxFun intb_fun;

        FPcieIntxFun intc_fun;

        FPcieIntxFun intd_fun;

    } FPcie;
```


- 配置空间标记参数

```
#define FPCIE_REGION_MEM		0x00000000	/* PCI memory space */
#define FPCIE_REGION_IO		    0x00000001	/* PCI IO space */
#define PCI_REGION_PREFETCH	    0x00000008	/* prefetchable PCI memory */
```


- 配置空间中对应的bar 标号

```
#define FPCIE_BAR_0 0
#define FPCIE_BAR_1 1
#define FPCIE_BAR_2 2
#define FPCIE_BAR_3 3
#define FPCIE_BAR_4 4
#define FPCIE_BAR_5 5
```


### 5.2 错误码定义

- 模块错误码编号：0x1090000
- [0x0] FT_SUCCESS
- [0x1090001] FPCIE_ERR_INVALID_PARAM 
- [0x1090002] FPCIE_ERR_OUTOF_BUS 
- [0x1090003] FPCIE_ERR_CONFIG_WRITE 
- [0x1090004] FPCIE_ERR_TYPE0 
- [0x1090005] FPCIE_ERR_TIMEOUT 
- [0x1090006] FPCIE_NEED_SKIP 
- [0x1090007] FPCIE_NOT_FOUND 


### 5.3 用户API接口


#### FPcieLookupConfig

- 获取FPCIE驱动的默认配置参数

```c
const FPcieConfig *FPcieLookupConfig(u32 instance_id)
```

Note:

- 用户可以通过此接口获取驱动默认配置的副本，进行修改后，作为`FPcieCfgInitialize`函数的入参使用

Input:

- u32 instance_id, 选择的FPcie控制器实例号

Return:

- const FPcieConfig *, 返回的默认驱动配置，返回NULL表示失败



#### FPcieCfgInitialize

- 初始化配置空间和FPCIE 实例

```c
FError FPcieCfgInitialize(FPcie *instance_p, FPcieConfig *config_p)
```

Note:

- 用户可以使用'FPcieLookupConfig'所产生的配置参数进行初始化，也可以自己组织配置参数进行初始化

Input:

- FPcie *instance_p 指向FPcie实例的指针。

- FPcieConfig *config_p 指向FPcieConfig的指针。

Return :

- 成功返回 FT_SUCCESS


#### FPcieDmaDescSet

- PCIE DMA描述符分组包

```c
FError FPcieDmaDescSet(uintptr axi_addr,
                       uintptr bar_addr,
                       u32 length,
                       struct FPcieDmaDescriptor *desc,
                       struct FPcieDmaDescriptor *next_desc)
```

Note:

- 用户使用dma 方式进行PCIE 数据传输时，用此函数将源地址与目标地址进行组合打包


Input:

- uintptr axi_addr 内存地址，可以为接收地址也可为发送地址

- uintptr bar_addr 需要通信function中对应的bar寄存器中分配的地址空间，可以为接收地址也可为发送地址

- u32 length       需要传输的字节长度

- struct FPcieDmaDescriptor *next_desc 是下一个需要发送的描述符  

Output:

- struct FPcieDmaDescriptor *desc 需要要配置的描述符



#### FPcieDmaRead

Note:

- 通过dma的方式读取Pcie function

```c
void FPcieDmaRead(uintptr bar_address, struct FPcieDmaDescriptor *desc)
```

Input:

- uintptr bar_address 基地地址寄存器的值

- struct FPcieDmaDescriptor *desc  接收描述符的起始地址

#### FPcieDmaWrite

- 通过dma的方式写入Pcie function

```c
void FPcieDmaWrite(uintptr bar_address, struct FPcieDmaDescriptor *desc)
```

Input:

- uintptr bar_address 基地地址寄存器的值

- struct FPcieDmaDescriptor *desc  发送描述符的起始地址


#### FPcieDmaPollDone

- 轮询等待DMA完成

```c
FError FPcieDmaPollDone(struct FPcieDmaDescriptor *desc, u32 wait_cnt)
```

Input:

- struct FPcieDmaDescriptor *desc  Desc是需要等待完成的dma 描述符

- u32 wait_cnt 是需要等待结束的计数  

####  FPcieFetchDeviceInBus

- 该功能用于扫描整个总线上的树形结构，并且对其中的节点进行初始化与配置空间的设置

```c
FError FPcieFetchDeviceInBus(FPcie *instance_p, u32 bus_num)
```

Input:

- FPcie *instance_p 指向FPcie实例的指针。

- u32 bus_num 扫描对应总线上已经连接的网桥/端点。  

Output:

- FError FT_SUCCESS 为成功


#### FPcieFindDeviceNum

- 根据输入的Vendor ID 与 Device ID ，获取当前PCIE 总线上一共存在多少此类设备

```c
u32  FPcieFindDeviceNum(FPcie *instance_p, u32 bus_num,u32 vendor_id,u32 device_id)
```

Input:

- FPcie *instance_p 指向FPcie实例的指针。

- u32 bus_num 需要查找的bus号

- u32 vendor_id 目标 Vendor ID

- u32 device_id 目标 Device ID

Output:

- u32 return 所需查找设备的数量



#### FPcieGetBusDeviceBarInfo

- 通过Vendor ID和device ID获取对应的function id、device id 和 bar 空间

```c
FError FPcieGetBusDeviceBarInfo(FPcie *instance_p,u32 bus,u32 vendor_id,u32 device_id,u32 bar_num ,u32 *device_p,u32 *function_p,uintptr *bar_addr_p)
```

Input:
- FPcie *instance_p 指向FPcie实例的指针。

- u32 bus 需要查找的bus号

- u32 vendor_id 目标 Vendor ID

- u32 device_id 目标 Device ID

- u32 bar_num 需要查找对应bar空间的编号

Output:

- u32 * device_p 需要获取对应设备号的指针

- u32 * function_p 需要获取对应功能号的指针

- uintptr * bar_addr_p 需要获取对应bar地址空间的指针

- FError return FT_SUCCESS 为成功


#### FPcieSearchFunByClass

- 使用 class code 获取设备的信息

```c
u32 FPcieSearchFunByClass(FPcie *instance_p,u32 class_code,FPcieSearchFunNode *node_p ,u32 node_num)
```

Input:

- FPcie *instance_p 指向FPcie实例的指针。

- u32 class_code 对应的类号

- FPcieSearchFunNode * node_p 是一个存放特定函数信息缓冲区的指针

- u32 node_num 缓冲器的数量

Output:

- u32 return 输出中的实际节点的个数



#### FPcieIntxIrqHandler

- fpcie的Intx中断服务函数

```c
void FPcieIntxIrqHandler(s32 vector, void *args)
```

Input:

- s32 vector 中断向量号

- void * args 需要传入的参数


#### FPcieIntxRegiterIrqHandler

- 使用bus id、device id 和function id在INTX上注册中断响应函数  

```c
FError FPcieIntxRegiterIrqHandler(FPcie *instance_p,
                                u32 bus,
                                u32 device,
                                u32 function,
                                FPcieIntxFun *intx_fun_p)
```

Input:

- FPcie *instance_p 指向FPcie实例的指针。

- u32 bus       需要配置的bus id

- u32 device    需要配置的device id

- u32 function  需要配置的function id

- FPcieIntxFun * intx_fun_p 是用户用来注册回调函数信息的指针
