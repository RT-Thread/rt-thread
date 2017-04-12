/*
 * File      : nftl.h
 * COPYRIGHT (C) 2012-2014, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-03-01     Bernard      the first version
 * 2012-11-01     Bernard      Add page mapping
 * 2012-12-28     Bernard      Use log trace for NFTL log.
 * 2013-01-06     Bernard      Fix oob issue when do a software page copy.
 * 2013-02-15     Bernard      Reduce memory usage
 * 2013-06-10     Bernard      Enable backup mapping block
 * 2013-09-18     Bernard      Fix the quick search issue in mapping table initialization.
 * 2013-11-11     RealThread   1.0.13 version which supports none-os environment.
 * 2013-12-25     RealThread   1.0.14 version which optimizes for memory/stack usage.
 * 2014-01-20     RealThread   1.0.15 version which optimizes for the scan speed in boot.
 * 2015-01-05     RealThread   1.0.16 version which addes NFTL manargement block protect with MPU.
 * 2015-02-12     RealThread   1.0.17 version which fix the mapping block wear_leveling issue.
 */

#ifndef __NAND_FTL_H__
#define __NAND_FTL_H__

#include <rtthread.h>
#include <rtdevice.h>

/* NFTL version information */
#define NFTL_VERSION                    1L              /* major version number */
#define NFTL_SUBVERSION                 0L              /* minor version number */
#define NFTL_REVISION                   17L             /* revise version number */

/* NFTL options */
#define NFTL_BLOCKS_MAX                 512             /* only 512 block for evaluation */
#define NFTL_PAGE_MAX                   2048
#define NFTL_OOB_MAX                    64
#define NFTL_PAGE_IN_BLOCK_MAX          64
#define NFTL_ERASE_BLANCE               10
#define NFTL_PLANE_MAX					4
#define NFTL_PM_CACHE_MAX				4
#define NFTL_BLOCKS_RECENT_MAX			32
#define NFTL_BACKUP_MAPPING_BLOCKS		4

/* using backup register to save the block number of mapping table. */
// #define NFTL_USING_BACKUP_MAPPING_BLOCK

// #define NFTL_USING_COMPATIBLE

/* using static memory for NFTl layer */
// #define NFTL_USING_STATIC

/* whether using MPU to protect NFTL core data */
// #define NFTL_USING_MPU

#define NFTL_MALLOC(sz)					RT_KERNEL_MALLOC(sz)
#define NFTL_FREE(ptr)					RT_KERNEL_FREE(ptr)

/* NFTL API for RT-Thread */
rt_err_t nftl_attach(const char* mtd_device);

/* NFTL API for diskio */
rt_err_t nftl_read_page(struct rt_mtd_nand_device *device,
                        rt_uint16_t                block_offset,
                        rt_uint16_t                page_offset,
                        rt_uint8_t                *buffer);
rt_err_t nftl_write_page(struct rt_mtd_nand_device *device,
                         rt_uint16_t                block_offset,
                         rt_uint16_t                page_offset,
                         const rt_uint8_t          *buffer);

rt_err_t nftl_read_multi_page(struct rt_mtd_nand_device *device,
                              rt_uint16_t                block_offset,
                              rt_uint16_t                page_offset,
                              rt_uint8_t                *buffer,
                              rt_size_t                  count);
rt_err_t nftl_write_multi_page(struct rt_mtd_nand_device *device,
                               rt_uint16_t                block_offset,
                               rt_uint16_t                page_offset,
                               const rt_uint8_t          *buffer,
                               rt_size_t                  count);

rt_err_t nftl_erase_pages(struct rt_mtd_nand_device* device, rt_uint32_t page_begin, rt_uint32_t page_end);

rt_err_t nftl_mapping_flush(struct rt_mtd_nand_device* device, rt_bool_t protect);

rt_err_t nftl_layer_init(struct rt_mtd_nand_device* device);

/* NFTL API for None-OS */
rt_err_t nftl_layer_attach_nand(struct rt_mtd_nand_device* device);

/* software ECC API */
int nftl_ecc_verify256(rt_uint8_t *data, rt_uint32_t size, const rt_uint8_t *code);
void nftl_ecc_compute256(const rt_uint8_t *data, rt_uint32_t size, rt_uint8_t *code);

#endif

