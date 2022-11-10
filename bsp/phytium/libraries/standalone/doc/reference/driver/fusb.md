
# FUSB 驱动程序

## 1. 概述

USB是通用串行总线（Universal Serial Bus）的缩写, USB是一种简易、双向、快速、同步、即插即用（Plug and Play，PnP）且支持热插拔功能的串行接口。USB设备现在已经非常普及，如U盘、鼠标、键盘等。USB协议曾经出现过多种版本，如USB1.0、USB1.1、USB2.0、USB3.0等

USB总线体系中, USB主机（Host）是系统的主人, 负责USB通信过程中数据的控制和处理, USB设备（Device）是系统的从机，用于实现特定的功能，如常用的U盘、移动硬盘、鼠标、键盘、游戏手柄等，在USB传输过程中，USB主机处于主导地位，由USB主机发起数据和命令的传输，USB设备被动响应USB主机发来的请求命令，USB总线中的主要角色包括USB主机、根Hub、USB Hub和USB设备等

USB主机和USB设备间的通信是通过管道（Pipe）进行的，管道是指在USB主机端的一组缓冲区，用于管道中数据的收发；在USB设备端，有一个特定端点（Endpoint，ENDP）与管道对接

USB可靠传输（具有反馈机制）的最小单位是事务，事务就是利用令牌包、数据包和握手包实现一个带有错误反馈机制的通信，使USB传输更加安全可靠，按照令牌包的类型可以分为，Setup事务、IN事务、OUT事务等。基于事务，USB协议定义了传输（Transfer）用于完成一组具有特定目的的事务，包括控制传输、中断传输、批量传输和同步传输

## 2. 功能

- 驱动相关的源文件如下，
- drivers/usb
```
.
├── Kconfig
├── fusb.c
├── fusb.h
├── fusb_debug.c
├── fusb_def.h
├── fusb_dev.c
├── fusb_g.c
├── fusb_generic_hub.c
├── fusb_generic_hub.h
├── fusb_hid.c
├── fusb_hid.h
├── fusb_hub.c
├── fusb_hub.h
├── fusb_msc.c
├── fusb_msc.h
├── fusb_private.h
├── fusb_sinit.c
```

- 关于 [XHCI](./fxhci.md)

## 3. 配置方法

参考以下步骤完成 FUSB 硬件配置，

- 1. FUSB驱动支持 E2000，在 E2000 上完成测试

参考以下步骤完成 FUSB 软件配置，

- 1. 选择USB控制器类型为 XHCI
- 2. 配置 FUSB 的内存池空间，推荐在1Mb以上
- 3. 注册USB设备驱动
- 4. 调用USB控制器驱动接口启动FUSB实例
- 5. 调用USB控制器驱动接口轮询FUSB，更新USB设备状态
- 6. 调用USB设备驱动操作USB设备

## 4 应用示例

- USB主机操作和USB设备发现
### [fxhci_host](../../../baremetal/example/peripheral/usb/fxhci_host)

- USB大容量存储器读写
### [fusb_fatfs](../../../baremetal/example/storage/fusb_fatfs)

## 5. API参考

### 5.1. 用户数据结构

#### 5.1.1 USB端点

```c
typedef struct 
{
	FUsbDev *dev; /* device instance of this endpoint */
	int endpoint; /* endpoint address ep0 = 0, epn = n */
	FUsbDirection direction; /* type or direction of ep */
	int toggle; /* ep state for some device to toggle */
	int maxpacketsize; /* max packet size for ep transfer */
	FUsbEpType type; /* transfer type of ep, control, bulk or so on */
	int interval; /* expressed as binary logarithm of the number
			 		of microframes (i.e. t = 125us * 2^interval) */
} FUsbEndpoint; /* encapsulates a single endpoint of an USB device */
```

#### 5.1.2 USB设备

```c
typedef struct _FUsbDev
{
	FUsbHc *controller; /* Hc instance where device attached */
	FUsbEndpoint endpoints[FUSB_MAX_EP_NUM]; /* all Ep instance of device */
	int num_endp; /* num of Ep in use */
	FUsbDevAddr address; /* USB address */
	FUsbDevClass class;	/* USB device class, e.g hid */
	int hub; /* hub where device is attached to */
	int port; /* port where device is attached */
	FUsbSpeed speed; /* speed type of device */
	void *data; /* private data for specific type of device */
	FUsbDeviceDescriptor *descriptor; /* device descriptor ever get from device hw */
	FUsbConfigurationDescriptor *configuration; /* configure descriptor followed with interface descriptor ever get from device hw */
	FUsbConfigParser  config_parser; /* parser for configure descriptor */
	FUsbStringParser  string_parser; /* parser for string descriptor */
	void (*init)(FUsbDev *dev); /* device init function of specific device type for register */
	void (*destroy) (FUsbDev *dev); /* device deinit function of specific device type for register */
	void (*poll) (FUsbDev *dev); /* device poll function of specific device type for register */
} FUsbDev; /* encapsulates a single USB device */
```

#### 5.1.3 USB主机

```c
typedef struct _FUsbHc
{
	FUsbHc *next; /* next Hc instance in the list */
	uintptr reg_base; /* base address of Hc register */
	FUsb *usb; /* instance of USB system */
	FUsbHcType type; /* type of Hc, e.g XHCI */
	FUsbDev *devices[FUSB_MAX_DEV_NUM];	/* dev 0 is root hub, 127 is last addressable */

	/* start():     Resume operation. */
	void (*start) (FUsbHc *controller);
	/* stop():      Stop operation but keep controller initialized. */
	void (*stop) (FUsbHc *controller);
	/* reset():     Perform a controller reset. The controller needs to
	                be (re)initialized afterwards to work (again). */
	void (*reset) (FUsbHc *controller);
	/* init():      Initialize a (previously reset) controller
	                to a working state. */
	void (*init) (FUsbHc *controller);
	/* shutdown():  Stop operation, detach host controller and shutdown
	                this driver instance. After calling shutdown() any
					other usage of this hci_t* is invalid. */
	void (*shutdown) (FUsbHc *controller);

	FUsbTransCode (*bulk) (FUsbEndpoint *ep, int size, u8 *data, int finalize);
	FUsbTransCode (*control) (FUsbDev *dev, FUsbDirection pid, int dr_length,
							  void *devreq, int data_length, u8 *data);
	void* (*create_intr_queue) (FUsbEndpoint *ep, int reqsize, int reqcount, int reqtiming);
	void (*destroy_intr_queue) (FUsbEndpoint *ep, void *queue);
	u8* (*poll_intr_queue) (void *queue);
	void *instance; /* instance to specific Hc implementation, e.g XHCI */

	/* set_address():		Tell the USB device its address (xHCI
					controllers want to do this by
					themselves). Also, allocate the FUsbDev
					structure, initialize enpoint 0
					(including MPS) and return it. */
	FUsbDev *(*set_address) (FUsbHc *controller, FUsbSpeed speed,
				  			 int hubport, int hubaddr);
	/* finish_device_config():	Another hook for xHCI, returns 0 on success. */
	int (*finish_device_config) (FUsbDev *dev);
	/* destroy_device(): Finally, destroy all structures that
						 were allocated during set_address()
						 and finish_device_config(). */
	void (*destroy_device) (FUsbHc *controller, int devaddr);
} FUsbHc; /* encapsulates a single USB host */
```

#### 5.1.4 USB系统配置

```c
typedef struct
{
	void *(*malloc_align)(size_t size, size_t align);
	void (*free)(void *mem);
} FUsbMemAllocator; /* memory allocator used in USB system */

typedef struct
{
    u32 instance_id; /* id for this USB system */
    uintptr base_addr; /* base addr of Hc register, set as 0 for pci-usb */
	u32 irq_num;
	u32 irq_priority;
	FUsbMemAllocator allocator; /* memory allocator to support dynamic memory */
} FUsbConfig; /* configure data of the USB system */
```

#### 5.1.4 USB系统

```c
typedef struct _FUsb
{
    FUsbConfig config; /* configuration of USB system */
    void *pcie_instance; /* NULL if unused */
	void *pcie_info[FUSB_MAX_CTRL_NUM]; /* NULL if unused */
	FUsbHc *hc; /* first hc, there might have multiple hc in pcie-mode */
	/* hook to set init function for specific device type */
	FUsbDevInitFunc dev_init[FUSB_MAX_DEV_TYPE_NUM];
	u32 dev_init_num; /* number of init function in used */
	u32 is_ready; /* indicator of system okay */
} FUsb; /* instance of the USB system */
```

### 5.2  错误码定义


- 模块错误码编号 `0x1110000`

- [0x0] FUSB_SUCCESS : success
- [0x1110000] FUSB_ERR_WAIT_TIMEOUT : wait for status timeout
- [0x1110001] FUSB_ERR_INVALID_PARA : invalid input parameters
- [0x1110002] FUSB_ERR_NOT_SUPPORT : parameters or feature not supported
- [0x1110003] FUSB_ERR_NON_INSTANCE : cannot find instance
- [0x1110004] FUSB_ERR_INVALID_DATA : invalid input data
- [0x1110005] FUSB_ERR_DESC_PARSE_ERR : failed to parse descriptor
- [0x1110006] FUSB_ERR_ALLOCATE_FAIL : failed to allocate memory from memory pool
- [0x1110007] FUSB_ERR_TRANS_FAIL : failed to transfer data


- 传输过程完成错误码

- [0] FUSB_CC_ZERO_BYTES : failed, transfer zero bytes
- [1] FUSB_CC_SUCCESS : transfer success with bytes unkonwn

### 5.3. 用户API接口

#### FUsbLookupConfig

```c
const FUsbConfig *FUsbLookupConfig(u32 instance_id)
```

Note:

- 获取USB的默认配置

Input:

- {u32} instance_id USB实例号

Return:

- {const FUsbConfig *} USB默认配置

#### FUsbCfgInitialize

```c
FError FUsbCfgInitialize(FUsb *instance, const FUsbConfig *input_config)
```

Note:

- 初始化USB实例
- 在PCIE模式下，USB Hc实例在PCIE总线发现控制器后创建

Input:

- {FUsb} *instance, USB实例
- {const FUsbConfig} *input_config, USB输入配置

Return:

- {FError} 初始化错误码

#### FUsbDeInitialize

```c
void FUsbDeInitialize(FUsb *instance);
```

Note:

- 去初始化USB实例

Input:

- {FUsb} *instance, USB实例

Return:

- 无

#### FUsbPoll

```c
void FUsbPoll(FUsb *instance)
```

Note:

- 轮询USB控制器连接的所有设备, 更新设备拓扑

Input:

- {FUsb} *instance, USB实例

Return:

- 无

#### FUsbExit

```c
void FUsbExit(FUsb *instance)
```

Note:

- 关闭所有的USB控制器，移除所有连接的设备

Input:

- {FUsb} *instance, USB实例

Return:

- 无


#### FUsbAssignDevInitFunc

```c
FError FUsbAssignDevInitFunc(FUsb *instance, const FUsbDevIndex *index, FUsbDevInitHandler handler)
```

Note:

- 指定特定USB设备的初始化函数，供创建USB设备实例时使用

Input:

- {FUsb} *instance, USB实例
- {FUsbDevIndex} *index, 特定USB设备的索引
- {FUsbDevInitHandler} handler, 特定USB设备的初始化函数

Return:

- {FError} 处理返回错误码

#### FUsbGetAllDevEntries

```c
size_t FUsbGetAllDevEntries(FUsbHc *controller, FUsbDev *devs[], size_t max_dev_num)
```

Note:

- 获取USB控制器上连接的所有USB设备实例

Input:

- {FUsbHc} *controller, USB控制器实例
- {FUsbDev} *devs, 放置USB设备实例的缓冲区
- {size_t} max_dev_num, 最多可以获取的USB设备实例数目

Return:

- {size_t} 实际获取的USB设备实例数目

#### FUsbSetFeature

```c
FUsbTransCode FUsbSetFeature(FUsbDev *dev, int endp, int feature, int rtype)
```

Note:

- 标准USB主机请求，使能设备/接口/端点的某个特性

Input:

- {FUsbDev} *dev, USB设备实例
- {int} endp, 设备号(0x00)/接口号/端点号
- {int} feature, 待使能的特性
- {int} rtype, 请求类型，由FUsbGenerateReqType生成

Return:

- {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbGetStatus

```c
FUsbTransCode FUsbGetStatus(FUsbDev *dev, int intf, int rtype, int len, void *data)
```

Note:

- 标准USB主机请求，获取设备/接口/端点的状态

Input:

- {FUsbDev} *dev, USB设备实例
- {int} intf，设备号(0x00)/接口号/端点号
- {int} rtype, 请求类型，由FUsbGenerateReqType生成
- {int} len, Data Stage的数据长度
- {void} *data, Data Stage的数据缓冲区

Return:

- {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbGetDescriptor

```c
FUsbTransCode FUsbGetDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType desc_type, int desc_idx, void *data, size_t len)
```

Note:

- 标准USB主机请求，获取指定描述符

Input:

- {FUsbDev} *dev, USB设备实例
- {int} rtype, 请求类型，由FUsbGenerateReqType生成
- {FUsbDescriptorType} desc_type, 描述符类型
- {int} desc_idx, 描述符索引
- {void} *data, Data Stage的数据缓冲区
- {size_t} len, Data Stage的数据长度

Return:

- {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbGetStringDescriptor

```c
FUsbTransCode FUsbGetStringDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType desc_type, int desc_idx, int lang_id, void *data, size_t len)
```

Note:

- USB主机请求，获取字符串描述符

Input:

- {FUsbDev} *dev, USB设备实例
- {int} rtype, 请求类型，由FUsbGenerateReqType生成
- {int} desc_type, 描述符类型
- {int} desc_idx, 描述符索引
- {int} lang_id, 语言类型
- {void} *data, Data Stage的数据缓冲区
- {size_t} len, Data Stage的数据长度

Return:

- {int} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbSetConfiguration

```c
FUsbTransCode FUsbSetConfiguration(FUsbDev *dev)
```

Note:

- 标准USB主机请求，设置配置值

Input:

- {FUsbDev} *dev, USB设备实例

Return:

- {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbClearFeature

```c
FUsbTransCode FUsbClearFeature(FUsbDev *dev, int endp, int feature, int rtype)
```

Note:

- 标准USB主机请求，去使能设备/接口/端点的某个特性

Input:

- {FUsbDev} *dev, USB设备实例
- {int} endp, 设备号(0x00)/接口号/端点号
- {int} feature，待去除的特性
- {int} rtype, 请求类型，由FUsbGenerateReqType生成

Return:

- {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目

#### FUsbDumpAllDescriptors

```c
void FUsbDumpAllDescriptors(FUsbDev *dev)
```

Note:

- 打印USB设备的描述符信息（设备描述符，配置描述符和接口描述符）

Input:

- {FUsbDev} *dev, USB设备实例，已完成初始化

Return:

- 无

#### FUsbDetachDev

```c
void FUsbDetachDev(FUsbHc *controller, int devno)
```

Note:

- 从USB主机移除指定USB设备(USB设备驱动使用)

Input:

- {FUsbHc} *controller, USB控制器实例
- {int} devno, USB设备地址

Return:

- 无


#### FUsbAttachDev

```c
FUsbDevAddr FUsbAttachDev(FUsbHc *controller, int hubaddress, int port, FUsbSpeed speed)
```

Note:

- 向USB主机添加USB设备(USB设备驱动使用)

Input:

- {FUsbHc} *controller, USB控制器实例
- {int} hubaddress, Hub地址
- {int} port, 连接的Port
- {FUsbSpeed} speed, USB设备的设置速度类型

Return:

- {FUsbDevAddr} 分配的USB设备地址
