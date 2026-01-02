# NVMEM 框架

## 1. 概述

### 1.1 什么是 NVMEM？

NVMEM（Non-Volatile Memory）是一个用于访问非易失性存储器的框架，提供了统一的接口来读写各种类型的非易失性存储设备，如：
- EEPROM（I2C、SPI）
- OTP（One-Time Programmable）存储器
- eFuse
- NVRAM
- 电池支持的 SRAM
- Flash 存储器的特定区域

### 1.2 RT-Thread 中的实现

RT-Thread 的 NVMEM 框架基于 Linux 内核的 NVMEM 子系统设计，提供：
- **基于 Cell 的组织**：将存储器划分为命名的单元（cells）
- **设备树集成**：通过设备树描述存储器布局
- **消费者/提供者模型**：驱动程序可以是 NVMEM 的消费者或提供者
- **类型化访问**：支持 u8/u16/u32/u64 的直接读取
- **位级访问**：支持比特级的精确访问
- **写保护支持**：GPIO 控制的写保护

## 2. Kconfig 配置

### 2.1 启用 NVMEM 支持

```
Device Drivers  --->
    [*] Using NVMEM (Non-Volatile Memory) device drivers
```

**配置选项**：
- `RT_USING_NVMEM`：启用 NVMEM 框架支持

### 2.2 在 menuconfig 中的位置

```
RT-Thread Configuration
    → Device Drivers
        → Using NVMEM (Non-Volatile Memory) device drivers
```

## 3. 设备树绑定

### 3.1 NVMEM 提供者

定义一个 NVMEM 设备（如 EEPROM）：

```dts
eeprom@50 {
    compatible = "atmel,24c256";
    reg = <0x50>;
    #address-cells = <1>;
    #size-cells = <1>;
    
    /* 定义 NVMEM cells */
    mac_address: mac-addr@0 {
        reg = <0x0 0x6>;  /* 偏移 0x0，长度 6 字节 */
    };
    
    board_id: board-id@6 {
        reg = <0x6 0x2>;  /* 偏移 0x6，长度 2 字节 */
    };
    
    serial_number: serial@8 {
        reg = <0x8 0x10>;  /* 偏移 0x8，长度 16 字节 */
    };
    
    calibration: calib@20 {
        reg = <0x20 0x10>;  /* 偏移 0x20，长度 16 字节 */
        bits = <0 32>;      /* 位偏移 0，位长度 32 */
    };
};
```

### 3.2 NVMEM 消费者

引用 NVMEM cells：

```dts
ethernet@40028000 {
    compatible = "vendor,eth";
    reg = <0x40028000 0x1000>;
    
    /* 引用 MAC 地址 cell */
    nvmem-cells = <&mac_address>;
    nvmem-cell-names = "mac-address";
};

adc@40012000 {
    compatible = "vendor,adc";
    reg = <0x40012000 0x400>;
    
    /* 引用校准数据 */
    nvmem-cells = <&calibration>;
    nvmem-cell-names = "calibration";
};
```

### 3.3 写保护 GPIO

带写保护引脚的 EEPROM：

```dts
eeprom@50 {
    compatible = "atmel,24c256";
    reg = <0x50>;
    
    /* 写保护 GPIO */
    wp-gpios = <&gpio1 10 GPIO_ACTIVE_HIGH>;
    
    mac_address: mac-addr@0 {
        reg = <0x0 0x6>;
    };
};
```

## 4. 应用层 API

### 4.1 Cell 获取操作

#### 4.1.1 rt_nvmem_get_cell_by_name

通过名称获取 NVMEM cell。

```c
struct rt_nvmem_cell *rt_nvmem_get_cell_by_name(struct rt_device *dev, 
                                                 const char *name);
```

**参数**：
- `dev`：设备指针
- `name`：cell 名称（设备树中的 nvmem-cell-names）

**返回值**：
- 成功：cell 指针
- 失败：RT_NULL

**示例**：
```c
struct rt_nvmem_cell *cell;

cell = rt_nvmem_get_cell_by_name(dev, "mac-address");
if (!cell) {
    rt_kprintf("Failed to get NVMEM cell\n");
    return -RT_ERROR;
}
```

#### 4.1.2 rt_nvmem_get_cell_by_index

通过索引获取 NVMEM cell。

```c
struct rt_nvmem_cell *rt_nvmem_get_cell_by_index(struct rt_device *dev, 
                                                  rt_uint32_t index);
```

**参数**：
- `dev`：设备指针
- `index`：cell 索引（从 0 开始）

**返回值**：
- 成功：cell 指针
- 失败：RT_NULL

#### 4.1.3 rt_nvmem_put_cell

释放 NVMEM cell 引用。

```c
void rt_nvmem_put_cell(struct rt_nvmem_cell *cell);
```

**参数**：
- `cell`：要释放的 cell 指针

### 4.2 数据访问操作

#### 4.2.1 rt_nvmem_cell_read

从 cell 读取数据。

```c
rt_ssize_t rt_nvmem_cell_read(struct rt_nvmem_cell *cell, 
                               rt_off_t *offset,
                               void *buf, 
                               rt_size_t size);
```

**参数**：
- `cell`：cell 指针
- `offset`：读取偏移（可为 RT_NULL，使用 cell 的偏移）
- `buf`：数据缓冲区
- `size`：要读取的字节数

**返回值**：
- 成功：实际读取的字节数
- 失败：负错误码

**示例**：
```c
rt_uint8_t mac[6];
rt_ssize_t ret;

ret = rt_nvmem_cell_read(cell, RT_NULL, mac, sizeof(mac));
if (ret != sizeof(mac)) {
    rt_kprintf("Failed to read MAC address\n");
    return -RT_ERROR;
}
```

#### 4.2.2 rt_nvmem_cell_write

向 cell 写入数据。

```c
rt_ssize_t rt_nvmem_cell_write(struct rt_nvmem_cell *cell,
                                rt_off_t *offset,
                                const void *buf,
                                rt_size_t size);
```

**参数**：
- `cell`：cell 指针
- `offset`：写入偏移（可为 RT_NULL）
- `buf`：要写入的数据
- `size`：要写入的字节数

**返回值**：
- 成功：实际写入的字节数
- 失败：负错误码

**注意**：
- 写操作可能受写保护 GPIO 限制
- 某些 NVMEM 设备可能是只读的

### 4.3 类型化读取操作

#### 4.3.1 rt_nvmem_cell_read_u8

读取 8 位无符号整数。

```c
rt_err_t rt_nvmem_cell_read_u8(struct rt_nvmem_cell *cell,
                                rt_off_t *offset,
                                rt_uint8_t *val);
```

#### 4.3.2 rt_nvmem_cell_read_u16

读取 16 位无符号整数。

```c
rt_err_t rt_nvmem_cell_read_u16(struct rt_nvmem_cell *cell,
                                 rt_off_t *offset,
                                 rt_uint16_t *val);
```

#### 4.3.3 rt_nvmem_cell_read_u32

读取 32 位无符号整数。

```c
rt_err_t rt_nvmem_cell_read_u32(struct rt_nvmem_cell *cell,
                                 rt_off_t *offset,
                                 rt_uint32_t *val);
```

#### 4.3.4 rt_nvmem_cell_read_u64

读取 64 位无符号整数。

```c
rt_err_t rt_nvmem_cell_read_u64(struct rt_nvmem_cell *cell,
                                 rt_off_t *offset,
                                 rt_uint64_t *val);
```

**参数**：
- `cell`：cell 指针
- `offset`：读取偏移（可为 RT_NULL）
- `val`：存储读取值的指针

**返回值**：
- `RT_EOK`：成功
- 负错误码：失败

**示例**：
```c
rt_uint32_t board_id;

if (rt_nvmem_cell_read_u32(cell, RT_NULL, &board_id) == RT_EOK) {
    rt_kprintf("Board ID: 0x%08x\n", board_id);
}
```

## 5. 应用层使用示例

### 5.1 以太网驱动：从 EEPROM 读取 MAC 地址

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/ofw.h>
#include <drivers/nvmem.h>

struct eth_device {
    struct rt_device parent;
    struct rt_device_phy phy;
    rt_uint8_t mac_addr[6];
    /* 其他字段... */
};

static rt_err_t eth_load_mac_address(struct eth_device *eth, 
                                      struct rt_device *dev)
{
    struct rt_nvmem_cell *cell;
    rt_ssize_t ret;
    
    /* 通过名称获取 MAC 地址 cell */
    cell = rt_nvmem_get_cell_by_name(dev, "mac-address");
    if (!cell) {
        rt_kprintf("No MAC address in NVMEM\n");
        return -RT_ERROR;
    }
    
    /* 读取 MAC 地址 */
    ret = rt_nvmem_cell_read(cell, RT_NULL, eth->mac_addr, 6);
    if (ret != 6) {
        rt_kprintf("Failed to read MAC address: %d\n", ret);
        rt_nvmem_put_cell(cell);
        return -RT_ERROR;
    }
    
    /* 释放 cell */
    rt_nvmem_put_cell(cell);
    
    /* 验证 MAC 地址 */
    if (eth->mac_addr[0] == 0x00 && eth->mac_addr[1] == 0x00 &&
        eth->mac_addr[2] == 0x00 && eth->mac_addr[3] == 0x00 &&
        eth->mac_addr[4] == 0x00 && eth->mac_addr[5] == 0x00) {
        rt_kprintf("Invalid MAC address (all zeros)\n");
        return -RT_ERROR;
    }
    
    rt_kprintf("MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
               eth->mac_addr[0], eth->mac_addr[1], eth->mac_addr[2],
               eth->mac_addr[3], eth->mac_addr[4], eth->mac_addr[5]);
    
    return RT_EOK;
}

static rt_err_t eth_probe(struct rt_platform_device *pdev)
{
    struct eth_device *eth;
    rt_err_t ret;
    
    eth = rt_calloc(1, sizeof(*eth));
    if (!eth) {
        return -RT_ENOMEM;
    }
    
    /* 从 NVMEM 加载 MAC 地址 */
    ret = eth_load_mac_address(eth, &pdev->parent);
    if (ret != RT_EOK) {
        /* 使用默认或随机 MAC 地址 */
        rt_kprintf("Using default MAC address\n");
        eth->mac_addr[0] = 0x00;
        eth->mac_addr[1] = 0x11;
        eth->mac_addr[2] = 0x22;
        eth->mac_addr[3] = 0x33;
        eth->mac_addr[4] = 0x44;
        eth->mac_addr[5] = 0x55;
    }
    
    /* 将 MAC 地址写入硬件寄存器 */
    /* ... */
    
    rt_platform_device_set_data(pdev, eth);
    
    return RT_EOK;
}

static struct rt_platform_driver eth_driver = {
    .name = "eth-driver",
    .ids = (struct rt_ofw_node_id[]) {
        { .compatible = "vendor,ethernet" },
        { /* sentinel */ }
    },
    .probe = eth_probe,
};
```

### 5.2 读取板卡 ID 和序列号

```c
static rt_err_t board_read_info(struct rt_device *dev)
{
    struct rt_nvmem_cell *board_id_cell, *serial_cell;
    rt_uint16_t board_id;
    char serial[17] = {0};  /* 16 字节 + null */
    rt_err_t ret;
    
    /* 读取板卡 ID */
    board_id_cell = rt_nvmem_get_cell_by_name(dev, "board-id");
    if (board_id_cell) {
        ret = rt_nvmem_cell_read_u16(board_id_cell, RT_NULL, &board_id);
        if (ret == RT_EOK) {
            rt_kprintf("Board ID: %u\n", board_id);
        }
        rt_nvmem_put_cell(board_id_cell);
    }
    
    /* 读取序列号 */
    serial_cell = rt_nvmem_get_cell_by_name(dev, "serial-number");
    if (serial_cell) {
        ret = rt_nvmem_cell_read(serial_cell, RT_NULL, serial, 16);
        if (ret > 0) {
            rt_kprintf("Serial Number: %s\n", serial);
        }
        rt_nvmem_put_cell(serial_cell);
    }
    
    return RT_EOK;
}
```

## 6. 驱动实现接口

### 6.1 NVMEM 设备注册

#### 6.1.1 rt_nvmem_device_register

注册 NVMEM 设备。

```c
rt_err_t rt_nvmem_device_register(struct rt_nvmem_device *nvmem);
```

**参数**：
- `nvmem`：NVMEM 设备结构体

**返回值**：
- `RT_EOK`：成功
- 负错误码：失败

#### 6.1.2 rt_nvmem_device_unregister

注销 NVMEM 设备。

```c
rt_err_t rt_nvmem_device_unregister(struct rt_nvmem_device *nvmem);
```

#### 6.1.3 rt_nvmem_device_append_cell

向 NVMEM 设备添加 cell。

```c
rt_err_t rt_nvmem_device_append_cell(struct rt_nvmem_device *nvmem,
                                      struct rt_nvmem_cell_info *info);
```

### 6.2 NVMEM 设备结构

```c
struct rt_nvmem_device {
    struct rt_device parent;
    const struct rt_nvmem_ops *ops;
    rt_size_t size;          /* 总大小 */
    rt_size_t word_size;     /* 字大小 */
    rt_size_t stride;        /* 访问步长 */
    rt_bool_t read_only;     /* 只读标志 */
    struct rt_ofw_node *np;  /* 设备树节点 */
    void *priv;              /* 私有数据 */
};
```

### 6.3 NVMEM 操作接口

```c
struct rt_nvmem_ops {
    rt_ssize_t (*read)(struct rt_nvmem_device *nvmem, rt_off_t offset,
                       void *buf, rt_size_t size);
    rt_ssize_t (*write)(struct rt_nvmem_device *nvmem, rt_off_t offset,
                        const void *buf, rt_size_t size);
};
```

### 6.4 I2C EEPROM 驱动示例

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/ofw.h>
#include <drivers/nvmem.h>
#include <drivers/i2c.h>

struct eeprom_priv {
    struct rt_i2c_client *client;
    struct rt_nvmem_device nvmem;
    struct rt_gpio_pin *wp_gpio;  /* 写保护 GPIO */
};

static rt_ssize_t eeprom_read(struct rt_nvmem_device *nvmem, 
                              rt_off_t offset,
                              void *buf, 
                              rt_size_t size)
{
    struct eeprom_priv *priv = nvmem->priv;
    struct rt_i2c_msg msgs[2];
    rt_uint8_t addr_buf[2];
    rt_ssize_t ret;
    
    /* 设置地址（大端序） */
    addr_buf[0] = (offset >> 8) & 0xFF;
    addr_buf[1] = offset & 0xFF;
    
    /* 写地址 */
    msgs[0].addr = priv->client->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = addr_buf;
    msgs[0].len = 2;
    
    /* 读数据 */
    msgs[1].addr = priv->client->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = buf;
    msgs[1].len = size;
    
    ret = rt_i2c_transfer(priv->client->bus, msgs, 2);
    if (ret != 2) {
        return -RT_ERROR;
    }
    
    return size;
}

static rt_ssize_t eeprom_write(struct rt_nvmem_device *nvmem,
                               rt_off_t offset,
                               const void *buf,
                               rt_size_t size)
{
    struct eeprom_priv *priv = nvmem->priv;
    struct rt_i2c_msg msg;
    rt_uint8_t *write_buf;
    rt_ssize_t ret;
    rt_size_t written = 0;
    rt_size_t page_size = 64;  /* EEPROM 页大小 */
    
    /* 禁用写保护 */
    if (priv->wp_gpio) {
        rt_pin_write(priv->wp_gpio->pin, PIN_LOW);
        rt_thread_mdelay(1);
    }
    
    write_buf = rt_malloc(page_size + 2);
    if (!write_buf) {
        ret = -RT_ENOMEM;
        goto out;
    }
    
    /* 逐页写入 */
    while (size > 0) {
        rt_size_t chunk = RT_MIN(size, page_size);
        rt_size_t page_offset = offset % page_size;
        
        /* 如果不是页对齐，调整写入大小 */
        if (page_offset + chunk > page_size) {
            chunk = page_size - page_offset;
        }
        
        /* 准备写缓冲区：地址 + 数据 */
        write_buf[0] = (offset >> 8) & 0xFF;
        write_buf[1] = offset & 0xFF;
        rt_memcpy(&write_buf[2], buf + written, chunk);
        
        /* 写入 */
        msg.addr = priv->client->client_addr;
        msg.flags = RT_I2C_WR;
        msg.buf = write_buf;
        msg.len = chunk + 2;
        
        ret = rt_i2c_transfer(priv->client->bus, &msg, 1);
        if (ret != 1) {
            rt_kprintf("EEPROM write failed at offset %d\n", offset);
            ret = -RT_ERROR;
            goto cleanup;
        }
        
        /* 等待写周期完成（~5ms） */
        rt_thread_mdelay(5);
        
        offset += chunk;
        written += chunk;
        size -= chunk;
    }
    
    ret = written;
    
cleanup:
    rt_free(write_buf);
    
out:
    /* 重新启用写保护 */
    if (priv->wp_gpio) {
        rt_pin_write(priv->wp_gpio->pin, PIN_HIGH);
    }
    
    return ret;
}

static const struct rt_nvmem_ops eeprom_ops = {
    .read = eeprom_read,
    .write = eeprom_write,
};

static rt_err_t eeprom_probe(struct rt_platform_device *pdev)
{
    struct eeprom_priv *priv;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    rt_uint32_t size;
    rt_err_t ret;
    
    priv = rt_calloc(1, sizeof(*priv));
    if (!priv) {
        return -RT_ENOMEM;
    }
    
    /* 获取 I2C 客户端 */
    priv->client = (struct rt_i2c_client *)pdev->parent.parent;
    
    /* 获取 EEPROM 大小 */
    if (rt_ofw_prop_read_u32(np, "size", &size)) {
        size = 32768;  /* 默认 32KB */
    }
    
    /* 获取写保护 GPIO */
    priv->wp_gpio = rt_ofw_get_named_pin(np, "wp-gpios", 0, NULL, NULL);
    if (priv->wp_gpio) {
        rt_pin_mode(priv->wp_gpio->pin, PIN_MODE_OUTPUT);
        rt_pin_write(priv->wp_gpio->pin, PIN_HIGH);  /* 初始启用写保护 */
    }
    
    /* 初始化 NVMEM 设备 */
    priv->nvmem.parent = pdev->parent;
    priv->nvmem.ops = &eeprom_ops;
    priv->nvmem.size = size;
    priv->nvmem.word_size = 1;
    priv->nvmem.stride = 1;
    priv->nvmem.read_only = RT_FALSE;
    priv->nvmem.np = np;
    priv->nvmem.priv = priv;
    
    /* 注册 NVMEM 设备 */
    ret = rt_nvmem_device_register(&priv->nvmem);
    if (ret != RT_EOK) {
        rt_kprintf("Failed to register NVMEM device\n");
        rt_free(priv);
        return ret;
    }
    
    rt_platform_device_set_data(pdev, priv);
    
    rt_kprintf("EEPROM registered: %u bytes\n", size);
    
    return RT_EOK;
}

static struct rt_platform_driver eeprom_driver = {
    .name = "i2c-eeprom",
    .ids = (struct rt_ofw_node_id[]) {
        { .compatible = "atmel,24c256" },
        { .compatible = "microchip,24lc256" },
        { /* sentinel */ }
    },
    .probe = eeprom_probe,
};
```

## 7. 最佳实践

### 7.1 消费者最佳实践

1. **总是检查返回值**：
```c
cell = rt_nvmem_get_cell_by_name(dev, "mac-address");
if (!cell) {
    /* 处理错误 */
}
```

2. **及时释放 cells**：
```c
rt_nvmem_put_cell(cell);
```

3. **验证数据有效性**：
```c
if (rt_nvmem_cell_read(cell, RT_NULL, data, size) == size) {
    /* 检查数据是否有效 */
    if (is_data_valid(data)) {
        use_data(data);
    }
}
```

4. **提供默认值**：
```c
if (rt_nvmem_cell_read_u32(cell, RT_NULL, &value) != RT_EOK) {
    value = DEFAULT_VALUE;
}
```

### 7.2 提供者最佳实践

1. **实现错误处理**：
```c
static rt_ssize_t nvmem_read(struct rt_nvmem_device *nvmem, 
                             rt_off_t offset, void *buf, rt_size_t size)
{
    /* 检查参数 */
    if (offset + size > nvmem->size) {
        return -RT_EINVAL;
    }
    
    /* 执行读取 */
    /* ... */
}
```

2. **处理写保护**：
```c
static rt_ssize_t nvmem_write(struct rt_nvmem_device *nvmem,
                              rt_off_t offset, const void *buf, rt_size_t size)
{
    struct priv *priv = nvmem->priv;
    
    /* 禁用写保护 */
    if (priv->wp_gpio) {
        rt_pin_write(priv->wp_gpio->pin, PIN_LOW);
    }
    
    /* 执行写入 */
    /* ... */
    
    /* 重新启用写保护 */
    if (priv->wp_gpio) {
        rt_pin_write(priv->wp_gpio->pin, PIN_HIGH);
    }
    
    return size;
}
```

3. **实现页写入**：
```c
/* 对于 EEPROM，尊重页边界 */
while (size > 0) {
    rt_size_t chunk = RT_MIN(size, page_size);
    /* 写入块 */
    /* 等待写周期 */
    rt_thread_mdelay(write_cycle_time);
}
```

## 8. 故障排除

### 8.1 常见问题

**问题：获取 cell 失败**
```
错误：rt_nvmem_get_cell_by_name() 返回 RT_NULL
```
**解决方案**：
- 检查设备树中的 nvmem-cells 和 nvmem-cell-names 属性
- 验证 NVMEM 提供者已正确注册
- 确认 cell 名称拼写正确

**问题：读取操作返回错误**
```
错误：rt_nvmem_cell_read() 返回负值
```
**解决方案**：
- 检查 NVMEM 设备是否可访问
- 验证偏移和大小是否在范围内
- 检查总线通信（I2C、SPI）

**问题：写入操作失败**
```
错误：rt_nvmem_cell_write() 失败
```
**解决方案**：
- 检查设备是否为只读
- 验证写保护 GPIO 是否正确配置
- 确认写入时序（等待写周期）

### 8.2 调试技巧

1. **启用 NVMEM 调试日志**：
```c
#define NVMEM_DEBUG
```

2. **验证设备树配置**：
```bash
# 检查 NVMEM 节点
cat /proc/device-tree/eeprom@50/compatible
```

3. **测试读写操作**：
```c
/* 读取测试 */
rt_uint8_t test_data[16];
ret = rt_nvmem_cell_read(cell, RT_NULL, test_data, sizeof(test_data));
rt_kprintf("Read %d bytes\n", ret);

/* 转储数据 */
for (int i = 0; i < ret; i++) {
    rt_kprintf("%02x ", test_data[i]);
}
rt_kprintf("\n");
```

## 9. 性能考虑

### 9.1 读取优化

1. **批量读取**：
```c
/* 好：一次读取所有数据 */
rt_nvmem_cell_read(cell, RT_NULL, buffer, total_size);

/* 差：多次小读取 */
for (i = 0; i < count; i++) {
    rt_nvmem_cell_read(cell, &offset, &buffer[i], 1);
}
```

2. **缓存数据**：
```c
/* 在初始化时读取，然后缓存 */
static rt_uint8_t cached_mac[6];
static rt_bool_t mac_loaded = RT_FALSE;

if (!mac_loaded) {
    rt_nvmem_cell_read(cell, RT_NULL, cached_mac, 6);
    mac_loaded = RT_TRUE;
}
```

### 9.2 写入优化

1. **页对齐写入**：
```c
/* 对齐到页边界以获得最佳性能 */
offset = ALIGN(offset, page_size);
```

2. **最小化写周期**：
```c
/* 仅写入更改的数据 */
if (memcmp(old_data, new_data, size) != 0) {
    rt_nvmem_cell_write(cell, RT_NULL, new_data, size);
}
```

## 10. 相关模块

- **OFW**：设备树解析和 cell 查找
- **I2C/SPI**：EEPROM 设备的总线接口
- **GPIO**：写保护引脚控制
- **Platform**：NVMEM 驱动注册

## 11. 参考资料

- `components/drivers/include/drivers/nvmem.h`：NVMEM API 头文件
- `components/drivers/nvmem/`：NVMEM 核心实现
- Linux Kernel NVMEM 子系统文档
- 设备树规范 - NVMEM 绑定
