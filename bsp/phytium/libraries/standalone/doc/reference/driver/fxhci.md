# FXHCI 驱动程序

## 1. 概述

XHCI，即可扩展的主机控制器接口，是英特尔公司开发的一个USB主机控制器接口，它主要是面向USB 3.0的，同时它也支持USB 2.0及以下的设备，包括所有种类速度的USB设备(USB 3.0 SuperSpeed, USB 2.0 Low-, Full-, and High-speed, USB 1.1 Low- and Full-speed)，是UHCI/OHCI/EHCI等接口标准的升级版本

XHCI接口架构主要包括三大部分,

1. 主机配置空间(Host Configuration Space)

- 每个xHC实现都应包括一种通过系统软件识别和枚举主机控制器的方法。本规范提供了一个主机配置空间的PCI示例，它被称为PCI配置空间。PCI配置空间定义提供了一个关于系统xHC枚举和资源（中断、电源、虚拟化等）的配置空间使用的工作示例

2. 寄存器空间(MMIO Space)

- 寄存器空间表示xHC向驻留在内存地址空间中的系统软件提供的硬件寄存器。寄存器空间提供了在xHCI正常和扩展功能寄存器中定义的实现特定参数、操作和运行时控制和状态寄存器，以及用于标记对单个USB设备的访问的门钟阵列。该空间，通常被称为I/O空间，被实现为内存映射的I/O(MMIO)空间

3. 主机空间(Host Memory)

- 主机空间由控制数据结构（设备上下文基地址阵列、设备上下文、传输环等）定义。以及由xHC驱动程序分配和管理的数据缓冲区，以启用单个设备的端点流量。此空间将在内存地址空间的内核和用户区域中分配

## 2. 功能

- 驱动相关的源文件如下，

```
drivers/usb/fxhci
├── fxhci.c
├── fxhci.h
├── fxhci_cmd.c
├── fxhci_debug.c
├── fxhci_dev.c
├── fxhci_evt.c
├── fxhci_hw.c
├── fxhci_hw.h
├── fxhci_private.h
└── fxhci_roothub.c
```

## 3. 配置方法

- 1. 通过 PCIe 总线连接或者板载外设, 连接 XHCI 控制器
- 2. 如果使用 PCIe 总线连接的 XHCI 控制器，先调用 FPCIE 驱动完成设备枚举和 PCIe 配置
- 3. 初始化 FUSB 驱动，通过 FUSB 驱动框架，初始化 FXHCI 控制器驱动
- 4. 通过 FUSB 驱动完成控制器和设备初始化
- 5. 调用 FUSB 轮询接口更新设备状态  

## 4 应用示例

- USB主机操作和USB设备发现
### [fxhci_host_pcie](../../../baremetal/example/peripheral/usb/fxhci_host_pcie)

- USB大容量存储器读写
### [fusb_fatfs](../../../baremetal/example/storage/fusb_fatfs)

## 5. API参考

### 5.1. 用户数据结构

无

### 5.2  错误码定义

- [1] FXHCI_CC_SUCCESS : success
- [-65] FXHCI_CC_TIMEOUT : wait transfer timeout
- [-66] FXHCI_CC_CONTROLLER_ERROR : usb controller in wrong state
- [-67] FXHCI_CC_COMMUNICATION_ERROR : communication error
- [-68] FXHCI_CC_OUT_OF_MEMORY : memory used up
- [-69] FXHCI_CC_DRIVER_ERROR : driver in wrong state
- [-1] FXHCI_CC_GENERAL_ERROR : general error
- [0] FXHCI_CC_ZERO_BYTES : failed, transfer zero bytes

>下列错误码来自XHCI标准
- [5] FXHCI_CC_TRB_ERROR : TRB error (XHCI spec.)
- [6] FXHCI_CC_STALL_ERROR : stall error (XHCI spec.)
- [7] FXHCI_CC_RESOURCE_ERROR : resource error (XHCI spec.)
- [8] FXHCI_CC_BANDWIDTH_ERROR : bandwidth error (XHCI spec.)
- [9] FXHCI_CC_NO_SLOTS_AVAILABLE : No available slot error (XHCI spec.)
- [13] FXHCI_CC_SHORT_PACKET : short packet error (XHCI spec.)
- [21] FXHCI_CC_EVENT_RING_FULL_ERROR : event ring full error (XHCI spec.)
- [24] FXHCI_CC_COMMAND_RING_STOPPED : command ring stopped error (XHCI spec.)
- [25] FXHCI_CC_STOPPED : command abort error (XHCI spec.)
- [26] FXHCI_CC_TRB_ERROR : stopped error (XHCI spec.)
- [27] FXHCI_CC_STOPPED_LENGTH_INVALID : stopped invalid length error (XHCI spec.)

### 5.3. 用户API接口

#### FXhciHcInit

```c
FUsbHc *FXhciHcInit (FUsb *instance, uintptr base_addr)
```

Note:

- 创建XHCI USB 控制器实例，完成初始化

Input:

- {FUsb} *instance, USB实例
- {uintptr} base_addr, XHCI控制器基地址

Return:

- {FUsbHc *} 类型为XHCI的USB控制器实例
