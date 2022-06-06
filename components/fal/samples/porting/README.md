# Flash 设备及分区移植示例

本示例主要演示 Flash 设备及分区相关的移植。

## 1、Flash 设备

在定义 Flash 设备表前，需要先定义 Flash 设备，参考 [`fal_flash_sfud_port.c`](fal_flash_sfud_port.c) （基于 [SFUD](https://github.com/armink/SFUD) 万能 SPI Flash 驱动的 Flash 设备）与 [`fal_flash_stm32f2_port.c`](fal_flash_stm32f2_port.c) （STM32F2 片内 Flash）这两个文件。这里简介下 `fal_flash_stm32f2_port.c` 里的代码实现。

### 1.1 定义 Flash 设备

针对 Flash 的不同操作，这里定义了如下几个操作函数：

- `static int init(void)`：**可选** 的初始化操作

- `static int read(long offset, uint8_t *buf, size_t size)`：读取操作

|参数                                    |描述|
|:-----                                  |:----|
|offset                                  |读取数据的 Flash 偏移地址|
|buf                                     |存放待读取数据的缓冲区|
|size                                    |待读取数据的大小|
|return                                  |返回实际读取的数据大小|

- `static int write(long offset, const uint8_t *buf, size_t size)` ：写入操作

| 参数   | 描述                      |
| :----- | :------------------------ |
| offset | 写入数据的 Flash 偏移地址 |
| buf    | 存放待写入数据的缓冲区    |
| size   | 待写入数据的大小          |
| return | 返回实际写入的数据大小    |

- `static int erase(long offset, size_t size)` ：擦除操作

| 参数   | 描述                      |
| :----- | :------------------------ |
| offset | 擦除区域的 Flash 偏移地址 |
| size   | 擦除区域的大小            |
| return | 返回实际擦除的区域大小    |

用户需要根据自己的 Flash 情况分别实现这些操作函数。在文件最底部定义了具体的 Flash 设备对象(stm32f2_onchip_flash)：

`const struct fal_flash_dev stm32f2_onchip_flash = { "stm32_onchip", 0x08000000, 1024*1024, 128*1024, {init, read, write, erase} };`

- `"stm32_onchip"` : Flash 设备的名字
- 0x08000000: 对 Flash 操作的起始地址
- 1024*1024：Flash 的总大小（1MB）
- 128*1024：Flash 块/扇区大小（因为 STM32F2 各块大小不均匀，所以擦除粒度为最大块的大小：128K）
- {init, read, write, erase} }：Flash 的操作函数。 如果没有 init 初始化过程，第一个操作函数位置可以置空。

### 1.2 定义 Flash 设备表

Flash 设备表定义在 `fal_cfg.h` 头文件中，定义分区表前需 **新建 `fal_cfg.h` 文件** 。

参考 [示例文件 samples/porting/fal_cfg.h](samples/porting/fal_cfg.h) 或如下代码：

```c
/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32f2_onchip_flash;
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32f2_onchip_flash,                                           \
    &nor_flash0,                                                     \
}
```

Flash 设备表中，有两个 Flash 对象，一个为 STM32F2 的片内 Flash ，一个为片外的 Nor Flash。

## 2、Flash 分区

Flash 分区基于 Flash 设备，每个 Flash 设备又可以有 N 个分区，这些分区的集合就是分区表。在配置分区表前，务必保证已定义好 Flash 设备及设备表。

分区表也定义在 `fal_cfg.h` 头文件中。参考 [示例文件 samples/porting/fal_cfg.h](samples/porting/fal_cfg.h) 或如下代码：

```C
#define NOR_FLASH_DEV_NAME             "norflash0"
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD,        "bl",     "stm32_onchip",         0,   64*1024, 0}, \
    {FAL_PART_MAGIC_WORD,       "app",     "stm32_onchip",   64*1024,  704*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "easyflash", NOR_FLASH_DEV_NAME,         0, 1024*1024, 0}, \
    {FAL_PART_MAGIC_WORD,  "download", NOR_FLASH_DEV_NAME, 1024*1024, 1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */
```

上面这个分区表详细描述信息如下：

| 分区名      | Flash 设备名   | 偏移地址  | 大小  | 说明               |
| :---------- | :------------- | :-------- | :---- | :----------------- |
| "bl"        | "stm32_onchip" | 0         | 64KB  | 引导程序           |
| "app"       | "stm32_onchip" | 64*1024   | 704KB | 应用程序           |
| "easyflash" | "norflash0"    | 0         | 1MB   | EasyFlash 参数存储 |
| "download"  | "norflash0"    | 1024*1024 | 1MB   | OTA 下载区         |

用户需要修改的分区参数包括：分区名称、关联的 Flash 设备名、偏移地址（相对 Flash 设备内部）、大小，需要注意以下几点：

- 分区名保证 **不能重复**
- 关联的 Flash 设备 **务必已经在 Flash 设备表中定义好** ，并且 **名称一致** ，否则会出现无法找到 Flash 设备的错误
- 分区的起始地址和大小 **不能超过 Flash 设备的地址范围** ，否则会导致包初始化错误

> 注意：每个分区定义时，除了填写上面介绍的参数属性外，需在前面增加 `FAL_PART_MAGIC_WORD` 属性，末尾增加 `0` （目前用于保留功能）
