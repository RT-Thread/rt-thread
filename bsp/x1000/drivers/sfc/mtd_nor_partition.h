/**
  ******************************************************************************
  * @file    spi_flash_mtd_partition.h
  * @author  Urey
  * @version V1.0.0
  * @date    2017Äê2ÔÂ11ÈÕ
  * @brief   TODO
  ******************************************************************************         
**/ 


#ifndef _SPI_FLASH_MTD_PARTITION_H_
#define _SPI_FLASH_MTD_PARTITION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <drivers/mtd_nor.h>

#define PART_FLAG_RDONLY    0x0001
#define PART_FLAG_WRONLY    0x0002
#define PART_FLAG_RDWR      0x0003

#define PART_TYPE_BLK       0x0010
#define PART_TYPE_MTD       0x0020

struct rt_mtd_nor_partition
{
    union
    {
        struct rt_mtd_nor_device    mtd;
        struct rt_device            blk;
    };

    const char *name;
    rt_uint32_t offset;             /* offset within the master MTD space */
    rt_uint32_t size;               /* partition size */
    rt_uint32_t mask_flags;         /* master MTD flags to mask out for this partition */
    void*       user_data;          /* hold parent device */
};

/*
 * functions
 */
extern rt_err_t mtd_nor_init_partition(const char *mtd_name,struct rt_mtd_nor_partition *parts);


#ifdef __cplusplus
}
#endif

#endif /* _SPI_FLASH_MTD_PARTITION_H_ */
