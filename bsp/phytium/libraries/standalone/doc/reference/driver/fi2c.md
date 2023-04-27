# I2C 驱动程序

## 1. 概述


- I2C 是一种串行同步半双工通信协议，总线上可以同时挂载多个主机和从机。I2C 总线由串行数据线 (SDA) 和串行时钟线 (SCL) 线构成。这些线都需要上拉电阻。

- I2C 具有简单且制造成本低廉等优点，主要用于低速外围设备的短距离通信（一英尺以内）。

- I2C 驱动支持的平台包括 FT2000/4、D2000、E2000。


## 2. 驱动功能

I2C 驱动程序管理在 I2C 总线上设备的通信，该驱动程序具备以下功能：

- 在主机模式下读写字节
- 支持从机模式

## 3. 使用方法

以下部分将指导您完成 I2C 驱动的硬件配置：

- 1. I2C驱动支持 FT2000/4, D2000和E2000，在FT2000/4上完成测试
- 2. FT2000/4, D2000上，使用I2C驱动需要打开IO复用，I2C0的引脚默认设置为给I2C使用，I2C1/I2C2/I2C3需要先设置IO复用才能使用
- 3. E2000上，使用MIO的的IIC驱动需要打开MIO配置功能寄存器，设置IIC模式，引脚复用设置为MIO功能，才能使用
- 4. FT2000/4, D2000上，I2C的参考时钟为48MHz,在E2000上，I2C的参考时钟为50MHz 不支持修改设置

以下部分将指导您完成 I2C 驱动的软件配置：

- 1. 配置驱动程序，新建应用工程，使能I2C驱动模块
- 2. 设置配置参数，选择为 I2C 主机还是从机，调整默认的 I2C 通信参数（如时序、位序等）
- 3. 配置中断服务
- 4. 处理错误码
- 5. 去使能驱动程序

## 4. 应用示例

### [fi2c_eeprom](../../../baremetal/example/peripheral/i2c/fi2c_eeprom/README.md)

### [fi2c_slave](../../../baremetal/example/peripheral/i2c/fi2c_master_slave/README.md)


## 5. API参考


### 5.1. 用户数据结构

- drivers/i2c/fi2c/fi2c.h

```c

typedef struct
{
    u32         instance_id; /* Device instance id */
    uintptr     base_addr;   /* Device base address */
    u32         irq_num;     /* Device intrrupt id */
    u32         irq_prority;  /* Device intrrupt priority */
    u32         ref_clk_hz;   /* Input reference clock frequency in Hz */
    u32         work_mode;   /* Device work mode Slave or Master */
    u32         slave_addr;      /* Slave Address writing/reading to/from */
    boolean     use_7bit_addr;  /* Slave in-chip address offset in 7bit or 10bit */
    u32         speed_rate;  /* I2C speed rate */
} FI2cConfig; /* Device configure setting */
```

- I2C驱动实例配置

```c

typedef struct
{
    FI2cConfig  config;             /* Current active configs */
    u32         is_ready;           /* Device is initialized and ready */
    volatile u32    status;
    FI2cFrameTX     txframe;
    FI2cFrameRX     rxframe;
    /** only apply to master device **/
    /* Master intrrupt handler */
    FI2cEvtHandler master_evt_handlers[FI2C_MASTER_INTR_EVT_NUM];  

    /** only apply to slave device **/
    /* Slave intrrupt handler */
    FI2cEvtHandler slave_evt_handlers[FI2C_SLAVE_INTR_EVT_NUM];

} FI2c; /* Device instance */
```

- I2C驱动实例

### 5.2  错误码定义

- 模块错误码编号 `0x10b0000`

- [0x0] FI2C_SUCCESS : fi2c success

- [0x10b0001] FI2C_ERR_INVAL_PARM : fi2c invalid input parameters

- [0x10b0002] FI2C_ERR_NOT_READY : fi2c driver not ready

- [0x10b0001] FI2C_ERR_INVAL_PARM : fi2c invalid input parameters

- [0x10b0003] FI2C_ERR_TIMEOUT : fi2c wait timeout

- [0x10b0004] FI2C_ERR_NOT_SUPPORT : fi2c non support operation

- [0x10b0005] FI2C_ERR_INVAL_STATE : fi2c invalid state

### 5.3 用户API接口


```c
const FI2cConfig *FI2cLookupConfig(u32 instance_id);
```
- 获取I2C驱动的默认配置参数

Note:
    
    - 用户需要修改配置参数时，可以通过修改返回的FI2cConfig副本，作为FI2cCfgInitialize函数的入参，

Input:

    - u32 instance_id, 当前控制的I2C控制器实例号    

Return:

    - const FI2cConfig *, 返回驱动默认参数， NULL表示失败


```c
FError FI2cCfgInitialize(FI2c *instance_p, const FI2cConfig *cofig_p);
```
- 完成I2C驱动实例的初始化，使之可以使用

Note:

    - 此函数会将驱动实例中的所有数据全部重置，同时会进行I2C控制器的重置，请不要在I2C数据传输过程中调用此函数

Input:

    - FI2c *instance_p, I2C驱动实例数据 
    
    - const FI2cConfig *cofig_p， I2C驱动配置数据 

Return:

    FError，参考6.2章错误码定义

```c
void FI2cDeInitialize(FI2c *instance_p);
```

- 完成I2C驱动实例去使能，清零实例数据

Note:

    - 此函数会将驱动实例中的所有数据全部重置，

Input:

    - FI2c *instance_p, I2C驱动实例数据 

Return:

    无

```c
const char *FI2cErrorToMessage(FError error);
```

- 获取I2C模块错误码对应的错误信息

Note:

    - 请输入属于FI2C模块的错误码，否则返回的错误信息为空

Input:

    - {FError} error, I2C输入错误码

Return:

    - {const char *}, 错误码信息，NULL表示失败

```c
FError FI2cMasterReadPoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len);
```
- I2C主机读，阻塞直到完成读操作或失败

Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Master工作模式下调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据 
    - @param {u32} inchip_addr 从机的内部偏移地址
    - @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
    - @param {u8} *buf_p 读目的缓冲区
    - @param {int} buf_len 读目的缓冲区长度

Return:
    - @return {FError *} 返回错误码

```c
FError FI2cMasterReadIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len);
```
- I2C主机读，接收中断读操作或者失败

Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Master工作模式下调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据 
    - @param {u32} inchip_addr 从机的内部偏移地址
    - @param {u8} *buf_p 读目的缓冲区
    - @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
    - @param {int} buf_len 读目的缓冲区长度

Return:
    - @return {FError *} 返回错误码

```c
FError FI2cMasterWriteIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len);
```
- I2C主机读，中断发送直到完成写操作或失败
Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Master工作模式下调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据 
    - @param {u32} inchip_addr 从机的内部偏移地址
    - @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
    - @param {u8} *buf_p 写源缓冲区
    - @param {size_t} buf_len 写源缓冲区长度

Return:
    - @return {FError *} 返回错误码

```c
FError FError FI2cMasterWritePoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len);
```
- I2C主机写，阻塞直到完成写操作或失败

Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Master工作模式下调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据 
    - @param {u32} inchip_addr 从机的内部偏移地址
    - @param {u8} mem_byte_len, Size of internal memory address 1->8bit ~ 4->32bit
    - @param {u8} *buf_p 写源缓冲区
    - @param {size_t} buf_len 写源缓冲区长度

Return:
    - @return {FError *} 返回错误码

```c
u32 FI2cGetIntr(FI2c *instance_p);
```
- 获取I2C instance_p的中断值

Note:
    - 请先初始化I2C驱动再调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据 

Return:
    - @return {u32} 中断状态寄存器的值

```c
FError FI2cMasterSetupIntr(FI2c *instance_p,u32 mask);
```
- 设置I2C主机的中断

Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Master工作模式下调用此函数

Input:
    - {FI2c} *instance_p I2C驱动实例数据
    - {u32} mask 需要操作的中断寄存器位
Return:
    - {FError *} 返回错误码

```c
void FI2cMasterRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler);
```
- 注册I2C主机中断事件函数

Note:
    无

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据
    - @param {u32} evt 中断事件，参考 FI2C_MASTER_INTR_EVT_NUM
    - @param {FI2cEvtHandler} handler 中断事件回调函数

Return:

    无

```c
FError FI2cSlaveSetupIntr(FI2c *instance_p);
```

- 设置I2C从机的中断

Note:
    - 请先初始化I2C驱动再调用此函数
    - 请在Slave工作模式下调用此函数

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据
    - @param {u32} evt 中断事件，参考 FI2C_MASTER_INTR_EVT_NUM
    - @param {FI2cEvtHandler} handler 中断事件回调函数

Return:
    - {FError *} 返回错误码

```c
void FI2cSlaveRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler);
```

- 注册I2C从机中断事件函数

Note:
    无

Input:
    - @param {FI2c} *instance_p I2C驱动实例数据
    - @param {u32} evt 中断事件，参考 FI2C_SLAVE_INTR_EVT_NUM
    - @param {FI2cEvtHandler} handler 中断事件回调函数

Return:

    无
