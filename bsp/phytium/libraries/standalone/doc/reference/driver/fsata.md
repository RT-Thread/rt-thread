# FSATA 驱动程序

## 1. 概述

串口硬盘SATA(Serial ATA)与以往的并口硬盘PATA(Parallel ATA)相比，数据传输速度更加快捷，并支持热插拔；
SATA总线使用嵌入式时钟信号，具备了更强的纠错能力，能对传输指令进行检查，如果发现错误会自动矫正，提高了数据传输的可靠性；

## 2. 功能

AHCI控制器驱动提供了SATA的控制访问方法，
- 初始化AHCI控制器
- 以PIO方式发送/接收数据和命令
- 以DMA方式发送/接收数据和命令
- 设置AHCI控制器的中断工作模式和中断响应函数

驱动相关的源文件包括，
```
fsata

    ├── fsata_g.c
    ├── fsata_hw.c
    ├── fsata_hw.h
    ├── fsata_intr.c
    ├── fsata_sinit.c
    ├── fsata.c
    └── fsata.h
```

## 3. 配置方法

以下部分将指导您完成 fsata 驱动的软件配置:

- 初始化ahci控制器
- 通过协议命令读写sata数据

## 4 应用示例

### [读写sata二进制数据](../../../baremetal/example/peripheral/sata)

### [通过文件系统使用sata](../../../baremetal/example/storage/sata_fatfs)

## 5. API参考

### 5.1. 用户数据结构

- fsata控制数据

```c
typedef struct
{
	FSataConfig config; 	/* sata配置 */
	u32 is_ready;		/* sata初始化完成标志 */
	u32 private_data;
	FSataAhciIoPorts port[FSATA_AHCI_MAX_PORTS];
	u16 *ataid[FSATA_AHCI_MAX_PORTS];
	u32	n_ports;
	u32	cap;	/* cache of HOST_CAP register */
	u32	port_map; /* cache of HOST_PORTS_IMPL reg */
	u32	link_port_map; /*linkup port map*/
	
	FSataIrqCallBack fsata_dhrs_cb; /* device-to-host register fis interrupt */
    void *dhrs_args;
	FSataIrqCallBack fsata_pss_cb; /* pio setup fis interrupt */
    void *pss_args;
	FSataIrqCallBack fsata_dss_cb; /* dma setup fis interrupt */
    void *dss_args;
	FSataIrqCallBack fsata_sdbs_cb; /* set device bits interrupt */
    void *sdbs_args;
	FSataIrqCallBack fsata_pcs_cb; /* port connect change status interrupt */
    void *pcs_args;
} FSataCtrl;
```

- fsata配置数据

```c
typedef struct
{
	uintptr base_addr; /* sata控制寄存器基地址 */
	const char *instance_name; /* instance name */
	u32 irq_num;     /* Irq number */
} FSataConfig; /* sata配置 */
```

- fsata port memmory
```c
typedef struct
{
	uintptr	port_mmio;
	FSataAhciCommandList *cmd_list; /*  Command List structure, will include cmd_tbl's address */
	uintptr cmd_tbl_base_addr; /* command table addr, also the command table's first part */
	FSataAhciCommandTablePrdt *cmd_tbl_prdt;	/* command table's second part , cmd_tbl + cmd_tbl_prdt = command table*/
	FSataAhciRecvFis *rx_fis;	/* Received FIS Structure */
	uintptr mem;
	FSataInfo dev_info;
} FSataAhciIoPorts;
```

- fsata属性
```c
typedef struct
{
	unsigned char if_type;		/* type of the interface */
	unsigned char part_type;	/* partition type */
	unsigned char type;		/* device type */
	unsigned char removable;	/* removable device */
	char vendor[BLK_VEN_SIZE + 1]; /* device vendor string */
	char product[BLK_PRD_SIZE + 1]; /* device product number */
	char revision[BLK_REV_SIZE + 1]; /* firmware revision */
	unsigned long lba;		/* number of blocks */
	unsigned long blksz;		/* block size */

}FSataInfo;
```

- fsata中断类型和中断事件
```c
#define	FSATA_PORT_IRQ_COLD_PRES	BIT(31) /* cold presence detect */
#define	FSATA_PORT_IRQ_TF_ERR		BIT(30) /* task file error */
#define	FSATA_PORT_IRQ_HBUS_ERR	    BIT(29) /* host bus fatal error */
#define	FSATA_PORT_IRQ_HBUS_DATA_ERR	BIT(28) /* host bus data error */
#define	FSATA_PORT_IRQ_IF_ERR		BIT(27) /* interface fatal error */
#define	FSATA_PORT_IRQ_IF_NONFATAL	BIT(26) /* interface non-fatal error */
#define	FSATA_PORT_IRQ_OVERFLOW	    BIT(24) /* xfer exhausted available S/G */
#define	FSATA_PORT_IRQ_BAD_PMP	    BIT(23) /* incorrect port multiplier */

#define	FSATA_PORT_IRQ_PHYRDY		BIT(22) /* PhyRdy changed */
#define	FSATA_PORT_IRQ_DEV_ILCK	    BIT(7) /* device interlock */
#define	FSATA_PORT_IRQ_CONNECT	    BIT(6) /* port connect change status */
#define	FSATA_PORT_IRQ_SG_DONE	    BIT(5) /* descriptor processed */
#define	FSATA_PORT_IRQ_UNK_FIS	    BIT(4) /* unknown FIS rx'd */
#define	FSATA_PORT_IRQ_SDB_FIS	    BIT(3) /* Set Device Bits FIS rx'd */
#define	FSATA_PORT_IRQ_DMAS_FIS	    BIT(2) /* DMA Setup FIS rx'd */
#define	FSATA_PORT_IRQ_PIOS_FIS	    BIT(1) /* PIO Setup FIS rx'd */
#define	FSATA_PORT_IRQ_D2H_REG_FIS	BIT(0) /* D2H Register FIS rx'd */
```

### 5.2  错误码定义

- FSATA_SUCCESS : success
- FSATA_ERR_INVAILD_PARAMETER : 参数无效
- FSATA_ERR_TIMEOUT : 数据或者命令传输等待超时
- FSATA_ERR_OPERATION : 错误操作
- FSATA_UNKNOWN_DEVICE : 未知设备

### 5.3. 用户API接口

#### FSataLookupConfig

- 获取Fata控制器默认配置

```c
const FSataConfig *FSataLookupConfig(void);
```

Note:

- 获取默认配置参数，包括中断号，instance_name等

Input:

- {void} 

Return:

- {const FSataConfig *}  fsata默认配置，返回NULL如果找不到默认配置

#### FSataCfgInitialize

- 初始化fsata控制器, 使之可以使用

```c
FError FSataCfgInitialize(FSataCtrl *instance_p, const FSataConfig *input_config_p);
```

Note:

- 输入配置通过FSataLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据
- {FSataConfig} *input_config_p fsata用户输入配置

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FSataAhciInit

- 初始化ahci, 使之可以使用

```c
FError FSataAhciInit(FSataCtrl *instance_p);
```

Note:

- 包含ahci初始化和port memory的内存分配输入，用户需保证mem的大小足够

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败


#### FSataAhciReadInfo

- 读取sata信息，包括型号、容量等，通过串口输出

```c
FError FSataAhciReadInfo(FSataCtrl *instance_p, u8 port);
```

Note:

- 输入配置通过FSataLookupConfig获取，用户按照需要修改后传入此函数

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据
- {u8} port fsata的port端口号

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FSataReadWrite

- pio方式读写sata数据

```c
FError FSataReadWrite(FSataCtrl *instance_p, u8 port, u32 start,
					  u16 blk_cnt, u8 *buffer, u8 is_write);
```

Note:

- 以pio方式读写sata数据，需注意传入的buffer是否完整

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据
- {u8} port fsata的port端口号
- {u32} start 读写的起始block
- {u16} blk_cnt 读写的block个数
- {u8} *buffer 读写数据的缓存地址
- {u8} is_write 读/写的标志位

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败

#### FSataFPDmaReadWrite

- dma方式读写sata数据

```c
FError FSataFPDmaReadWrite(FSataCtrl *instance_p, u8 port, u32 start,
					  u16 blk_cnt, u8 *buffer, u8 is_write);
```

Note:

- 以dma方式读写sata数据，需注意传入的buffer是否完整

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据
- {u8} port fsata的port端口号
- {u32} start 读写的起始block
- {u16} blk_cnt 读写的block个数
- {u8} *buffer 读写数据的缓存地址
- {u8} is_write 读/写的标志位

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败

/* set specific sata irq function entry */
FError FSataSetHandler(FSataCtrl *instance_p, u32 handler_type,
					   void *func_pointer, void *call_back_ref);


#### FSataSetHandler

- 设置各中断的处理函数

```c
FError FSataSetHandler(FSataCtrl *instance_p, u32 handler_type,
					   void *func_pointer, void *call_back_ref);
```

Note:

- 根据中断类型，设置对应的回调函数和参数传入

Input:

- {FSataCtrl} *instance_p fsata驱动控制数据
- {u32} handler_type 中断类型
- {void} *func_pointer 回调函数入口
- {void} *call_back_ref 回调函数参数

Return:

- {FError} 驱动初始化的错误码信息，FSATA_SUCCESS 表示初始化成功，其它返回值表示初始化失败
