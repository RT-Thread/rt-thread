/*********************************************************************************************************
**
**                                苏州诺金智通信息科技有限公司
**
**                               Copyright All Rights Reserved
**
**--------------文件信息--------------------------------------------------------------------------------
**
** 文 件 名: cfs-coffee_arch.h
**
** 创 建 人: Urey(风飘柳絮)
**
** 创建日期: 2015年11月11日
**
** 描    述: TODO
*********************************************************************************************************/


#ifndef _CFS_COFFEE_ARCH_H_
#define _CFS_COFFEE_ARCH_H_

#include <rtdef.h>

extern struct rt_device_blk_geometry   xmem_geometry;
//extern rt_device_t xmem_device;


/* Coffee configuration parameters. */
#define COFFEE_SECTOR_SIZE      (xmem_geometry.block_size)
#define COFFEE_PAGE_SIZE        256UL
#define COFFEE_START            COFFEE_SECTOR_SIZE
#define COFFEE_SIZE             ((xmem_geometry.sector_count * xmem_geometry.bytes_per_sector) - COFFEE_START)

#define COFFEE_NAME_LENGTH      16
#define COFFEE_MAX_OPEN_FILES   6
#define COFFEE_FD_SET_SIZE      8
#define COFFEE_LOG_TABLE_LIMIT  256
#define COFFEE_DYN_SIZE         4*1024
#define COFFEE_LOG_SIZE         1024


#define COFFEE_MICRO_LOGS       1

#define XMEM_ERASE_UNIT_SIZE    (COFFEE_SECTOR_SIZE)


/* Flash operations. */
#define COFFEE_WRITE(buf, size, offset)             \
        xmem_pwrite((char *)(buf), (size), COFFEE_START + (offset))

#define COFFEE_READ(buf, size, offset)              \
        xmem_pread((char *)(buf), (size), COFFEE_START + (offset))

#define COFFEE_ERASE(sector)                        \
        xmem_erase(COFFEE_SECTOR_SIZE, COFFEE_START + (sector) * COFFEE_SECTOR_SIZE)

/* Coffee types. */
typedef int16_t coffee_page_t;

/*********************************************************************************************************
**   函数申明
*********************************************************************************************************/
int xmem_init   (rt_device_t device);
int xmem_erase  (long size, unsigned long addr);
int xmem_pwrite (const void *_buf, int size, unsigned long addr);
int xmem_pread  (void *_p, int size, unsigned long offset);

#endif /* _CFS_COFFEE_ARCH_H_ */
