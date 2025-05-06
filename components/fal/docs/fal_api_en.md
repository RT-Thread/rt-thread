# FAL API

## Find Flash device

```C
const struct fal_flash_dev *fal_flash_device_find(const char *name)
```

| Parameters | Description |
| :----- | :----------------------- |
| name | Flash device name |
| return | If the search is successful, the Flash device object will be returned, and if the search fails, it will return NULL |

## Find Flash Partition

```C
const struct fal_partition *fal_partition_find(const char *name)
```

| Parameters | Description |
| :----- | :----------------------- |
| name | Flash partition name |
| return | If the search is successful, the Flash partition object will be returned, and if the search fails, it will return NULL |

## Get the partition table

```C
const struct fal_partition *fal_get_partition_table(rt_size_t *len)
```

| Parameters | Description |
| :----- | :----------------------- |
| len | The length of the partition table |
| return | Partition table |

## Temporarily set the partition table

The default partition table will be automatically loaded when FAL is initialized. Using this setting will temporarily modify the partition table and will **lost** this setting after restarting

```C
void fal_set_partition_table_temp(struct fal_partition *table, rt_size_t len)
```

| Parameters | Description |
| :----- | :----------------------- |
| table | Partition table |
| len | Length of the partition table |

## Read data from partition

```C
int fal_partition_read(const struct fal_partition *part, rt_uint32_t addr, rt_uint8_t *buf, rt_size_t size)
```

| Parameters | Description |
| :----- | :----------------------- |
| part | Partition object |
| addr | Relative partition offset address |
| buf | Buffer to store the data to be read |
| size | The size of the data to be read |
| return | Return the actual read data size |

## Write data to partition

```C
int fal_partition_write(const struct fal_partition *part, rt_uint32_t addr, const rt_uint8_t *buf, rt_size_t size)
```

| Parameters | Description |
| :----- | :----------------------- |
| part | Partition object |
| addr | Relative partition offset address |
| buf | Buffer to store data to be written |
| size | The size of the data to be written |
| return | Return the actual written data size |

## Erase partition data

```C
int fal_partition_erase(const struct fal_partition *part, rt_uint32_t addr, rt_size_t size)
```

| Parameters | Description |
| :----- | :----------------------- |
| part | Partition object |
| addr | Relative partition offset address |
| size | The size of the erased area |
| return | Return the actual erased area size |

## Erase the entire partition data

```C
int fal_partition_erase_all(const struct fal_partition *part)
```

| Parameters | Description |
| :----- | :----------------------- |
| part | Partition object |
| return | Return the actual erased area size |

## Print partition table

```c
void fal_show_part_table(void)
```

## Create block device

This function can create the corresponding block device according to the specified partition name, so as to mount the file system on the specified partition

```C
struct rt_device *fal_blk_device_create(const char *parition_name)
```

| Parameters | Description |
| :----- | :----------------------- |
| parition_name | partition name |
| return | If the creation is successful, the corresponding block device will be returned, and if it fails, empty |

## Create MTD Nor Flash device

This function can create the corresponding MTD Nor Flash device according to the specified partition name, so as to mount the file system on the specified partition

```C
struct rt_device *fal_mtd_nor_device_create(const char *parition_name)
```

| Parameters | Description |
| :------------ | :---------------------------------- ------------------ |
| parition_name | Partition name |
| return | If the creation is successful, the corresponding MTD Nor Flash device will be returned, otherwise empty |

## Create a character device

This function can create the corresponding character device according to the specified partition name to facilitate the operation of the partition through the deivice interface or the devfs interface. After POSIX is turned on, the partition can also be operated through the open/read/write function.

```C
struct rt_device *fal_char_device_create(const char *parition_name)
```

| Parameters | Description |
| :------------ | :---------------------------------- ------- |
| parition_name | partition name |
| return | If the creation is successful, the corresponding character device will be returned, otherwise empty |