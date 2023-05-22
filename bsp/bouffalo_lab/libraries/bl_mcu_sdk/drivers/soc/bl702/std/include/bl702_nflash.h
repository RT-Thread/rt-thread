/**
  ******************************************************************************
  * @file    bl702_nflah.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL702_NFLAH_H__
#define __BL702_NFLAH_H__

#include "bl702_common.h"
#include "bl702_sf_ctrl.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLAH
 *  @{
 */

/** @defgroup  SFLAH_Public_Types
 *  @{
 */

/**
 *  @brief Serial flash configuration structure type definition
 */
/*@} end of group SFLAH_Public_Types */

/** @defgroup  SFLAH_Public_Constants
 *  @{
 */

/*@} end of group SFLAH_Public_Constants */

/** @defgroup  SFLAH_Public_Macros
 *  @{
 */
#define BFLB_NAND_FLASH_BLK_DATA_SIZE   (128 * 1024)
#define BFLB_NAND_FLASH_BLK_TOTAL_SIZE  ((128 + 4) * 1024)
#define BFLB_NAND_FLASH_PAGE_SIZE       (2048)
#define BFLB_NAND_FLASH_PAGE_TOTAL_SIZE (2048 + 64)
#define BFLB_NAND_FLASH_PAGES_PER_BLOCK (64)
#define BFLB_NAND_FLASH_CMD_INVALID     (0xff)
#define DISK_SECTOR_SIZE                (512)
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef BYTE DSTATUS;
typedef enum {
    RES_OK = 0, /* 0: Successful */
    RES_ERROR,  /* 1: R/W Error */
    RES_WRPRT,  /* 2: Write Protected */
    RES_NOTRDY, /* 3: Not Ready */
    RES_PARERR  /* 4: Invalid Parameter */
} DRESULT;

typedef enum {
    READ_DATA_FROM_CACHE = 0,       //date:2048 bytes in each page
    READ_SPARE_DATA_FROM_CACHE = 1, //spare date:64 bytes in each page
} BL_Nand_Flash_READ_DATE_TYPE;

typedef struct
{
    uint8_t ioMode;               /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap */
    uint8_t cReadSupport;         /*!< Support continuous read mode,bit0:continuous read mode support,bit1:read mode cfg */
    uint8_t clkDelay;             /*!< SPI clock delay,bit0-3:delay,bit4-6:pad delay */
    uint8_t clkInvert;            /*!< SPI clock phase invert,bit0:clck invert,bit1:rx invert,bit2-4:pad delay,bit5-7:pad delay */
    uint8_t resetEnCmd;           /*!< Flash enable reset command */
    uint8_t resetCmd;             /*!< Flash reset command */
    uint8_t resetCreadCmd;        /*!< Flash reset continuous read command */
    uint8_t resetCreadCmdSize;    /*!< Flash reset continuous read command size */
    uint8_t jedecIdCmd;           /*!< JEDEC ID command */
    uint8_t jedecIdCmdDmyClk;     /*!< JEDEC ID command dummy clock */
    uint8_t qpiJedecIdCmd;        /*!< QPI JEDEC ID comamnd */
    uint8_t qpiJedecIdCmdDmyClk;  /*!< QPI JEDEC ID command dummy clock */
    uint8_t sectorSize;           /*!< *1024bytes */
    uint8_t mid;                  /*!< Manufacturer ID */
    uint16_t pageSize;            /*!< Page size */
    uint8_t chipEraseCmd;         /*!< Chip erase cmd */
    uint8_t sectorEraseCmd;       /*!< Sector erase command */
    uint8_t blk128EraseCmd;       /*!< Block 128K erase command */
    uint8_t writeEnableCmd;       /*!< Need before every erase or program */
    uint8_t programLoadCmd;       /*!< Program Load cmd */
    uint8_t qprogramLoadCmd;      /*!< Program Load cmd x4*/
    uint8_t pageProgramCmd;       /*!< Page program cmd */
    uint8_t qpageProgramCmd;      /*!< QIO page program cmd */
    uint8_t qppAddrMode;          /*!< QIO page program address mode */
    uint8_t pageReadToCacheCmd;   /*!< Page read comamnd */
    uint8_t getFeaturesCmd;       /*!< GET FEATURES command to read the status */
    uint8_t setFeaturesCmd;       /*!< SET FEATURES command to read the status */
    uint8_t readFromCacheCmd;     /*!< Read from cache command */
    uint8_t fastReadCmd;          /*!< Fast read command */
    uint8_t frDmyClk;             /*!< Fast read command dummy clock */
    uint8_t qpiFastReadCmd;       /*!< QPI fast read command */
    uint8_t qpiFrDmyClk;          /*!< QPI fast read command dummy clock */
    uint8_t fastReadDoCmd;        /*!< Fast read dual output command */
    uint8_t frDoDmyClk;           /*!< Fast read dual output command dummy clock */
    uint8_t fastReadDioCmd;       /*!< Fast read dual io comamnd */
    uint8_t frDioDmyClk;          /*!< Fast read dual io command dummy clock */
    uint8_t fastReadQoCmd;        /*!< Fast read quad output comamnd */
    uint8_t frQoDmyClk;           /*!< Fast read quad output comamnd dummy clock */
    uint8_t fastReadQioCmd;       /*!< Fast read quad io comamnd */
    uint8_t frQioDmyClk;          /*!< Fast read quad io comamnd dummy clock */
    uint8_t qpiFastReadQioCmd;    /*!< QPI fast read quad io comamnd */
    uint8_t qpiFrQioDmyClk;       /*!< QPI fast read QIO dummy clock */
    uint8_t qpiPageProgramCmd;    /*!< QPI program command */
    uint8_t writeVregEnableCmd;   /*!< Enable write reg */
    uint8_t wrEnableIndex;        /*!< Write enable register index */
    uint8_t qeIndex;              /*!< Quad mode enable register index */
    uint8_t busyIndex;            /*!< Busy status register index */
    uint8_t wrEnableBit;          /*!< Write enable bit pos */
    uint8_t qeBit;                /*!< Quad enable bit pos */
    uint8_t busyBit;              /*!< Busy status bit pos */
    uint8_t wrEnableWriteRegLen;  /*!< Register length of write enable */
    uint8_t wrEnableReadRegLen;   /*!< Register length of write enable status */
    uint8_t qeWriteRegLen;        /*!< Register length of contain quad enable */
    uint8_t qeReadRegLen;         /*!< Register length of contain quad enable status */
    uint8_t releasePowerDown;     /*!< Release power down command */
    uint8_t busyReadRegLen;       /*!< Register length of contain busy status */
    uint8_t readRegCmd[4];        /*!< Read register command buffer */
    uint8_t writeRegCmd[4];       /*!< Write register command buffer */
    uint8_t enterQpi;             /*!< Enter qpi command */
    uint8_t exitQpi;              /*!< Exit qpi command */
    uint8_t cReadMode;            /*!< Config data for continuous read mode */
    uint8_t cRExit;               /*!< Config data for exit continuous read mode */
    uint8_t burstWrapCmd;         /*!< Enable burst wrap command */
    uint8_t burstWrapCmdDmyClk;   /*!< Enable burst wrap command dummy clock */
    uint8_t burstWrapDataMode;    /*!< Data and address mode for this command */
    uint8_t burstWrapData;        /*!< Data to enable burst wrap */
    uint8_t deBurstWrapCmd;       /*!< Disable burst wrap command */
    uint8_t deBurstWrapCmdDmyClk; /*!< Disable burst wrap command dummy clock */
    uint8_t deBurstWrapDataMode;  /*!< Data and address mode for this command */
    uint8_t deBurstWrapData;      /*!< Data to disable burst wrap */
    uint16_t timeEsector;         /*!< 4K erase time */
    uint16_t timeE132k;           /*!< 132K erase time */
    uint16_t timePagePgm;         /*!< Page program time */
    uint16_t timeCe;              /*!< Chip erase time in ms */
    uint8_t pdDelay;              /*!< Release power down command delay time for wake up */
    uint8_t qeData;               /*!< QE set data */
} __attribute__((packed)) Nand_Flash_Cfg_Type;

//BL_Nand_Flash_Program_Bit_Err_Type ATTR_TCM_SECTION NFlash_Pass(uint8_t errorCode, BL_Nand_Flash_OP_Type opType);
BL_Err_Type NFlash_GetJedecId(Nand_Flash_Cfg_Type *flashCfg, uint8_t *data);
BL_Err_Type ATTR_TCM_SECTION NFlash_Erase(Nand_Flash_Cfg_Type *flashCfg, uint32_t startAddr, uint32_t endAddr);
BL_Err_Type ATTR_TCM_SECTION NFlash_Blk128_Erase(Nand_Flash_Cfg_Type *flashCfg, uint32_t blockNum);
BL_Err_Type ATTR_TCM_SECTION NFlash_Write_Enable(Nand_Flash_Cfg_Type *flashCfg);
BL_Err_Type ATTR_TCM_SECTION NFlash_Read(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, uint8_t *data, uint32_t len);
BL_Err_Type ATTR_TCM_SECTION NFlash_Program(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, const uint8_t *data, uint32_t len);
BL_Err_Type ATTR_TCM_SECTION NFlash_Page_Read_To_Cache(Nand_Flash_Cfg_Type *flashCfg, uint32_t absolutePageNum);
BL_Err_Type ATTR_TCM_SECTION NFlash_Get_Feature(Nand_Flash_Cfg_Type *flashCfg, uint8_t *data, uint8_t cmdType);
BL_Err_Type ATTR_TCM_SECTION NFlash_Read_From_Cache(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t readType);
BL_Err_Type ATTR_TCM_SECTION NFlash_Program_Execute(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr);
BL_Err_Type ATTR_TCM_SECTION NFlash_Set_Feature(Nand_Flash_Cfg_Type *flashCfg);
BL_Err_Type ATTR_TCM_SECTION NFlash_Program_Load(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, const uint8_t *data, uint32_t len);
BL_Err_Type ATTR_TCM_SECTION NFlash_Check_Bad_Block(Nand_Flash_Cfg_Type *flashCfg, uint32_t blockNum, uint8_t *data, uint32_t len);
DRESULT ff_disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
DRESULT ff_disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
DSTATUS ff_disk_initialize(BYTE pdrv);

/*@} end of group SFLAH_Public_Functions */

/*@} end of group SFLAH */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_SFLAH_H__ */
