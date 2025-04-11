# Flash 设备及分区移植示例

本示例主要演示 Flash 设备及分区相关的移植。

## 1、Flash 设备

在定义 Flash 设备表前，需要先定义 Flash 设备，参考 [`fal_flash_sfud_port.c`](fal_flash_sfud_port.c) （基于 [SFUD](https://github.com/armink/SFUD) 万能 SPI Flash 驱动的 Flash 设备）与 [`fal_flash_stm32f2_port.c`](fal_flash_stm32f2_port.c) （STM32F2 片内 Flash）这两个文件。这里简介下 `fal_flash_stm32f2_port.c` 里的代码实现。

### 1.1 定义 Flash 设备

针对 Flash 的不同操作，这里定义了如下几个操作函数：

- `static int init(void)`：**可选** 的初始化操作

- `static int read(long offset, rt_uint8_t *buf, rt_size_t size)`：读取操作

|参数                                    |描述|
|:-----                                  |:----|
|offset                                  |读取数据的 Flash 偏移地址|
|buf                                     |存放待读取数据的缓冲区|
|size                                    |待读取数据的大小|
|return                                  |返回实际读取的数据大小|

- `static int write(long offset, const rt_uint8_t *buf, rt_size_t size)` ：写入操作

| 参数   | 描述                      |
| :----- | :------------------------ |
| offset | 写入数据的 Flash 偏移地址 |
| buf    | 存放待写入数据的缓冲区    |
| size   | 待写入数据的大小          |
| return | 返回实际写入的数据大小    |

- `static int erase(long offset, rt_size_t size)` ：擦除操作

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
## 3、如何实现读写擦除等操作
我们以fal_norflash_port.c为例，简单介绍一下。
首先 介绍一下这两个宏定义
```C
#define FAL_ALIGN_UP( size, align ) \
    ( ( ( size ) + ( align ) - 1 ) - ( ( ( size ) + ( align ) - 1 ) % ( align ) ) )
#define FAL_ALIGN_DOWN( size, align ) ( ( ( size ) / ( align ) ) * ( align ) )
```
ALIGN_UP(16,4)=16 ALIGN_UP(15,4)=16 ALIGN_UP(17,4)=20 
ALIGN_DOWN(16,4)=16 ALIGN_DOWN(15,4)=12 ALIGN_DOWN(17,4)=16
不难看出 ALIGN_UP是一个size向上取整到align的倍数，ALIGN_DOWN则是向下取整到align的倍数。
然后 介绍FLASH的特性 
    FLASH都是按块擦除 norflash的块大小一般为4K 单片机内部FLASH的块大小为1K,2K,16K不等 
    同时有最少写入数据的限制 
norflash中 是按页写入 一次最少写256个字节数据 超过则覆盖起始数据 如第257个数据会覆盖第1个数据的位置 
单片机内部flash中 一次最少写2个字节数据(STM32F105RC) 且只能将地址2字节对齐写入 只写一个字节时 给后面的字节补成FF 
实现擦除
```C
static int32_t get_sector( uint32_t address );//获取当前属于第一个扇区
extern void norflash_erase_sector( uint32_t saddr );//负责擦除单个扇区的全部数据
//FLASH都是按块擦除 我们假定在调用擦除函数时 用户知道自己将会擦除扇区内的全部数据 
static int erase( long offset, size_t size )
{
    int32_t  cur_erase_sector;
    uint32_t addr      = FLASH_START_ADDR + offset;
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_SECTOR_SIZE );

    uint32_t addr_end    = addr + size;
    uint32_t addr_end_up = FAL_ALIGN_UP( addr_end, FLASH_SECTOR_SIZE );
    uint32_t cur_addr    = addr_down;

    while ( cur_addr < addr_end_up ) {
        cur_erase_sector = get_sector( cur_addr );
        if ( cur_erase_sector == -1 ) {//获取第几个扇区失败 说明地址超出范围
            return cur_addr - addr;
        }
        norflash_erase_sector( cur_erase_sector );
        cur_addr += FLASH_SECTOR_SIZE;//这里如果每个扇区的大小不同 需要实现从当前地址获取扇区实际大小的函数
    }
    return size;
}
```
实现读取
```c
//这个比较简单 直接调用norflash_read即可
static int read( long offset, uint8_t* buf, size_t size )
{
    norflash_read( buf, offset + FLASH_START_ADDR, size );
    return size;
}
```
最后 也是最关键的一步 实现写入
```c
/* 写入任意长数据到NOR Flash函数 */
static int write( long offset, const uint8_t* buf, size_t size )
{
    // 计算实际物理地址（相对于Flash起始地址的偏移）
    uint32_t addr      = FLASH_START_ADDR + offset;
    // 计算起始地址的扇区向上对齐地址（例如0x1007 -> 0x2000 当扇区大小4K）
    uint32_t addr_up   = FAL_ALIGN_UP( addr, FLASH_SECTOR_SIZE );
    // 计算起始地址的扇区向下对齐地址（例如0x1007 -> 0x1000）
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_SECTOR_SIZE );

    // 计算写入结束地址
    uint32_t addr_end      = addr + size;
    // 结束地址的扇区向上对齐地址
    uint32_t addr_end_up   = FAL_ALIGN_UP( addr_end, FLASH_SECTOR_SIZE );
    // 结束地址的扇区向下对齐地址
    uint32_t addr_end_down = FAL_ALIGN_DOWN( addr_end, FLASH_SECTOR_SIZE );
    uint32_t cur_addr      = addr_down; // 当前处理的扇区起始地址

    uint32_t max_write_len = 0; // 单次最大可写入长度
    uint32_t write_len     = 0; // 实际写入长度

    // 地址有效性检查：结束地址超过Flash范围 或 起始地址在Flash区域外
    if ( addr_end_up > FLASH_END_ADDR || ( int )addr_end_down < FLASH_START_ADDR ) return -1;
    
    // 分配扇区大小的缓冲区（用于处理部分写入时需要保存原始数据的情况）
    uint8_t* read_sector_buf = FAL_MALLOC( FLASH_SECTOR_SIZE );
    if ( read_sector_buf == RT_NULL ) {
        return -2; // 内存分配失败
    }

    // 按扇区逐个处理（从起始扇区到结束扇区）
    while ( cur_addr < addr_end_up ) {
        /* 情况1：处理起始地址不在扇区边界的情况（首扇区部分写入） */
        if ( cur_addr < addr ) {
            // 读取整个扇区原始数据到缓冲区
            read( cur_addr - FLASH_START_ADDR, read_sector_buf, FLASH_SECTOR_SIZE );
            
            // 计算首扇区可写入的最大长度（从起始地址到扇区末尾）
            max_write_len = ( addr_up - addr );
            // 确定实际写入长度（不超过剩余数据大小）
            write_len     = size >= max_write_len ? max_write_len : size;

            // 判断是否需要擦除（检查目标区域是否包含需要从0->1的位）
            if ( judge_whether_erase( read_sector_buf + addr - cur_addr, write_len ) ){
                // 需要擦除时：执行擦除->修改缓冲区->写入整个扇区
                norflash_erase_sector( get_sector( cur_addr ) );
                // 将新数据合并到缓冲区对应位置
                FAL_MEMCPY( read_sector_buf + ( addr - cur_addr ), buf, write_len );
                // 写入整个扇区
                write_sector( cur_addr, read_sector_buf, FLASH_SECTOR_SIZE );
            }
            else {
                // 无需擦除时直接写入数据（NOR Flash允许直接写入0位）
                write_sector( addr, buf, write_len );
            }
            buf += write_len; // 移动数据指针
        }
        /* 情况2：处理结束地址不在扇区边界的情况（末扇区部分写入） */
        else if ( cur_addr == addr_end_down ) {
            // 读取整个扇区原始数据
            read( cur_addr - FLASH_START_ADDR, read_sector_buf, FLASH_SECTOR_SIZE );
            
            // 计算最大可写入长度（整个扇区）
            max_write_len = FLASH_SECTOR_SIZE;
            // 计算实际需要写入的长度（从扇区起始到结束地址）
            write_len     = addr_end - cur_addr;
            write_len     = write_len >= max_write_len ? max_write_len : write_len;

            // 判断是否需要擦除
            if ( judge_whether_erase( read_sector_buf,  write_len ) ) {
                // 需要擦除时：合并数据->擦除->写入整个扇区
                FAL_MEMCPY( read_sector_buf, buf, write_len );
                norflash_erase_sector( get_sector( cur_addr ) );
                write_sector( cur_addr, read_sector_buf, FLASH_SECTOR_SIZE );
            }
            else {
                // 直接写入数据
                write_sector( cur_addr, buf, write_len );
            }
        }
        /* 情况3：完整扇区写入（中间扇区） */
        else {
            // 直接擦除整个扇区（完整覆盖不需要保留数据）
            norflash_erase_sector( get_sector( cur_addr ) );
            // 写入整个扇区数据
            write_sector( cur_addr, buf, FLASH_SECTOR_SIZE );
            buf += FLASH_SECTOR_SIZE; // 移动数据指针
        }
        cur_addr += FLASH_SECTOR_SIZE; // 移动到下一个扇区
    }
    FAL_FREE( read_sector_buf ); // 释放缓冲区内存
    return size; // 返回成功写入的字节数
}
```
关键逻辑说明：
地址对齐处理：通过向上/向下对齐计算确定实际需要操作的扇区范围
三种写入场景：
    首扇区部分写入：需要读取原始数据，合并新数据后判断擦除必要性
    中间完整扇区：直接擦除后全量写入，提高效率
    末扇区部分写入：处理方式类似首扇区，但数据位置不同
擦除判断：通过judge_whether_erase函数检测是否需要执行擦除操作（基于NOR Flash的特性，只有需要将0变为1时才必须擦除）
数据合并：使用临时缓冲区保存原始数据，仅修改需要写入的部分，最大限度减少擦除操作
内存管理：动态分配扇区大小的缓冲区，处理完成后立即释放
到这里 工作似乎做完了 但是 我们没有写入扇区的函数 只有页写入函数 norflash_write_page
扇区写入逻辑和任意写入逻辑基本相同
下面实现扇区写入函数
```c
/* 扇区写入函数：处理按页对齐的NOR Flash写入操作 */
static int write_sector( long offset, const uint8_t* buf, size_t size )
{
    // 计算实际物理地址（FLASH起始地址 + 偏移量）
    uint32_t addr      = FLASH_START_ADDR + offset;
    
    // 计算地址的页对齐上边界和下边界（按FLASH_PAGE_SIZE对齐）
    uint32_t addr_up   = FAL_ALIGN_UP( addr, FLASH_PAGE_SIZE );
    uint32_t addr_down = FAL_ALIGN_DOWN( addr, FLASH_PAGE_SIZE );

    // 计算写入结束地址及其页对齐边界
    uint32_t addr_end      = addr + size;
    uint32_t addr_end_up   = FAL_ALIGN_UP( addr_end, FLASH_PAGE_SIZE );
    uint32_t addr_end_down = FAL_ALIGN_DOWN( addr_end, FLASH_PAGE_SIZE );

    // 初始化当前处理地址和长度变量
    uint32_t cur_addr      = addr_down;    // 从页对齐起始地址开始处理
    uint32_t max_write_len = 0;            // 单次最大可写入长度
    uint32_t write_len     = 0;            // 实际写入长度
    
    // 循环处理所有需要写入的页
    while ( cur_addr < addr_end_up ) {
        // 处理起始未对齐部分（跨页起始边界）
        if ( cur_addr < addr ) {
            // 计算当前页剩余可写空间（页结束地址 - 实际起始地址）
            max_write_len = ( addr_up - addr );
            // 取实际剩余长度和总长度的最小值
            write_len     = size >= max_write_len ? max_write_len : size;
            
            // 执行页写入：参数依次是数据指针、物理地址、写入长度
            norflash_write_page( buf, addr, write_len );
            buf += write_len;  // 移动数据指针
        }
        // 处理结束未对齐部分（跨页结束边界）
        else if ( cur_addr == addr_end_down ) {
            // 单页最大写入长度
            max_write_len = FLASH_PAGE_SIZE;
            // 计算实际需要写入的长度（结束地址 - 当前页起始地址）
            write_len     = addr_end - cur_addr;
            // 确保不超过页最大长度
            write_len     = write_len >= max_write_len ? max_write_len : write_len;
            
            // 执行页写入
            norflash_write_page( buf, cur_addr, write_len );
        }
        // 处理完整页写入
        else {
            // 整页写入（FLASH_PAGE_SIZE长度）
            norflash_write_page( buf, cur_addr, FLASH_PAGE_SIZE );
            buf += FLASH_PAGE_SIZE;  // 移动数据指针整页长度
        }

        // 移动到下一页起始地址
        cur_addr += FLASH_PAGE_SIZE;
    }
    return size;  // 返回成功写入的总字节数
}
```
至此 我们就完成了Flash驱动的移植 实现了读写擦除等操作 上面的思路对于大部分flash驱动来说是通用的