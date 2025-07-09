/*****************************************************************************
* File Name      : fal_cfg.c
* Author         : Inhand Embedded Team
* Description    :
* Copyright      : InHand Networks Co., Ltd.
* Website        : https://www.inhand.com.cn
******************************************************************************
* modification history :
* liliang created on 2019-11-06 14:49:04
* weiyf   modify  on 2020-03-18 修改SPI FLASH 大小
* weiyf   modify  on 2020-05-08 重分SPI Flash分区
* weiyf   modify  on 2020-07-01 FAL重分区
******************************************************************************/
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_
/******************************************************************************/
#include <rtconfig.h>
#include <fal_def.h>
#include <board.h>
/******************************************************************************/
//#if defined(PKG_USING_FAL) && defined(FAL_PART_HAS_TABLE_CFG)
/************************************************************************************
 *                  SPI Flash Partition  8MB (0x00000000 ~ 0x00800000)
 * -----------------------------------------------------------------------------------
 *      Use                     |   Address Space                  |     Size
 * -----------------------------------------------------------------------------------
 *    Vendor                    |  0x00000000 ~ 0x00010000         |    64KB 
 * -----------------------------------------------------------------------------------
 *    Easyflash                 |  0x00010000 ~ 0x00110000         |    1024KB 
 * -----------------------------------------------------------------------------------
 *    App Backup                |  0x00110000 ~ 0x00310000         |    2048KB
 * -----------------------------------------------------------------------------------
 *    Littlefs                  |  0x00310000 ~ 0x00710000         |    4096KB
 * -----------------------------------------------------------------------------------
 *    Resv                      |  0x00710000 ~ 0x00800000         |    960KB
 * -----------------------------------------------------------------------------------
 * **********************************************************************************/
//#if defined(BSP_USING_SPI_FLASH) && defined(RT_USING_SFUD)
extern struct fal_flash_dev nor_flash0;
#define SPI_FLASH_SIZE                                      (16 * 1024 * 1024)
#define SPI_FLASH_DEV_NAME                                  "W25Q128JVSSIQ"
/* Vendor */
#define SPI_FLASH_AREA_NAME1                                "Vendor"
#define SPI_FLASH_AREA_OFFSET1                              (0)
#define SPI_FLASH_AREA_SIZE1                                (64 * 1024)


/* FATFS */
#define SPI_FLASH_AREA_NAME2                                "Littlefs"
#define SPI_FLASH_AREA_OFFSET2                              (SPI_FLASH_AREA_OFFSET1 + SPI_FLASH_AREA_SIZE1)
#define SPI_FLASH_AREA_SIZE2                                (16320 * 1024)


#define FAL_FLASH_DEV_TABLE     \
{                               \
    &nor_flash0                  \
}
/* Partition Table */
#define FAL_PART_TABLE          \
{                               \
    {FAL_PART_MAGIC_WORD, SPI_FLASH_AREA_NAME1, SPI_FLASH_DEV_NAME, SPI_FLASH_AREA_OFFSET1, SPI_FLASH_AREA_SIZE1, 0},     \
    {FAL_PART_MAGIC_WORD, SPI_FLASH_AREA_NAME2, SPI_FLASH_DEV_NAME, SPI_FLASH_AREA_OFFSET2, SPI_FLASH_AREA_SIZE2, 0},     \
}
#endif /* BSP_USING_SPI_FLASH && RT_USING_SFUD */

//#endif /* defined(PKG_USING_FAL) && defined(FAL_PART_HAS_TABLE_CFG) */

//#endif /* _FAL_CFG_H_ */
