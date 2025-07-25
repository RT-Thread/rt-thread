# FAL API

## 查找 Flash 设备 

```C
const struct fal_flash_dev *fal_flash_device_find(const char *name)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| name   | Flash 设备名称 |
| return | 如果查找成功，将返回 Flash 设备对象，查找失败返回 NULL    |

## 查找 Flash 分区

```C
const struct fal_partition *fal_partition_find(const char *name)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| name   | Flash 分区名称 |
| return | 如果查找成功，将返回 Flash 分区对象，查找失败返回 NULL    |

## 获取分区表

```C
const struct fal_partition *fal_get_partition_table(rt_size_t *len)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| len    | 分区表的长度 |
| return | 分区表   |

## 临时设置分区表

FAL 初始化时会自动装载默认分区表。使用该设置将临时修改分区表，重启后会 **丢失** 该设置

```C
void fal_set_partition_table_temp(struct fal_partition *table, rt_size_t len)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| table  | 分区表 |
| len    | 分区表的长度 |

## 从分区读取数据

```C
int fal_partition_read(const struct fal_partition *part, rt_uint32_t addr, rt_uint8_t *buf, rt_size_t size)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| part   | 分区对象 |
| addr   | 相对分区的偏移地址 |
| buf    | 存放待读取数据的缓冲区 |
| size   | 待读取数据的大小 |
| return | 返回实际读取的数据大小   |

## 往分区写入数据

```C
int fal_partition_write(const struct fal_partition *part, rt_uint32_t addr, const rt_uint8_t *buf, rt_size_t size)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| part   | 分区对象 |
| addr   | 相对分区的偏移地址 |
| buf    | 存放待写入数据的缓冲区 |
| size   | 待写入数据的大小 |
| return | 返回实际写入的数据大小   |

## 擦除分区数据

```C
int fal_partition_erase(const struct fal_partition *part, rt_uint32_t addr, rt_size_t size)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| part   | 分区对象 |
| addr   | 相对分区的偏移地址 |
| size   | 擦除区域的大小 |
| return | 返回实际擦除的区域大小   |

##  擦除整个分区数据

```C
int fal_partition_erase_all(const struct fal_partition *part)
```

| 参数    | 描述                      |
| :----- | :----------------------- |
| part   | 分区对象 |
| return | 返回实际擦除的区域大小   |

## 打印分区表

```c
void fal_show_part_table(void)
```

## 创建块设备

该函数可以根据指定的分区名称，创建对应的块设备，以便于在指定的分区上挂载文件系统

```C
struct rt_device *fal_blk_device_create(const char *parition_name)
```

| 参数           | 描述                      |
| :-----        | :-----------------------  |
| parition_name | 分区名称 |
| return        | 创建成功，则返回对应的块设备，失败返回空   |

## 创建 MTD Nor Flash 设备

该函数可以根据指定的分区名称，创建对应的 MTD Nor Flash 设备，以便于在指定的分区上挂载文件系统

```C
struct rt_device *fal_mtd_nor_device_create(const char *parition_name)
```

| 参数          | 描述                                                  |
| :------------ | :---------------------------------------------------- |
| parition_name | 分区名称                                              |
| return        | 创建成功，则返回对应的 MTD Nor Flash 设备，失败返回空 |

## 创建字符设备

该函数可以根据指定的分区名称，创建对应的字符设备，以便于通过 deivice 接口或 devfs 接口操作分区，开启了 POSIX 后，还可以通过 open/read/write 函数操作分区。

```C
struct rt_device *fal_char_device_create(const char *parition_name)
```

| 参数          | 描述                                       |
| :------------ | :----------------------------------------- |
| parition_name | 分区名称                                   |
| return        | 创建成功，则返回对应的字符设备，失败返回空 |

