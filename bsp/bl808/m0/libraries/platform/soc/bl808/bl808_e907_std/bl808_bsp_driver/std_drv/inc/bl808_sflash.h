/**
  ******************************************************************************
  * @file    bl808_sflah.h
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
#ifndef __BL808_SFLAH_H__
#define __BL808_SFLAH_H__

#include "bl808_common.h"
#include "bl808_sf_ctrl.h"

/** @addtogroup  BL808_Peripheral_Driver
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
typedef struct
{
    uint8_t ioMode;               /*!< Serail flash interface mode,bit0-3:IF mode,bit4:unwrap,bit5:32-bits addr mode support */
    uint8_t cReadSupport;         /*!< Support continuous read mode,bit0:continuous read mode support,bit1:read mode cfg */
    uint8_t clkDelay;             /*!< SPI clock delay,bit0-3:delay,bit4-6:pad delay */
    uint8_t clkInvert;            /*!< SPI clock phase invert,bit0:clck invert,bit1:rx invert,bit2-4:pad delay,bit5-7:pad delay */
    uint8_t resetEnCmd;           /*!< Flash enable reset command */
    uint8_t resetCmd;             /*!< Flash reset command */
    uint8_t resetCreadCmd;        /*!< Flash reset continuous read command */
    uint8_t resetCreadCmdSize;    /*!< Flash reset continuous read command size */
    uint8_t jedecIdCmd;           /*!< JEDEC ID command */
    uint8_t jedecIdCmdDmyClk;     /*!< JEDEC ID command dummy clock */
    uint8_t enter32BitsAddrCmd;   /*!< Enter 32-bits addr command */
    uint8_t exit32BitsAddrCmd;    /*!< Exit 32-bits addr command */
    uint8_t sectorSize;           /*!< *1024bytes */
    uint8_t mid;                  /*!< Manufacturer ID */
    uint16_t pageSize;            /*!< Page size */
    uint8_t chipEraseCmd;         /*!< Chip erase cmd */
    uint8_t sectorEraseCmd;       /*!< Sector erase command */
    uint8_t blk32EraseCmd;        /*!< Block 32K erase command,some Micron not support */
    uint8_t blk64EraseCmd;        /*!< Block 64K erase command */
    uint8_t writeEnableCmd;       /*!< Need before every erase or program */
    uint8_t pageProgramCmd;       /*!< Page program cmd */
    uint8_t qpageProgramCmd;      /*!< QIO page program cmd */
    uint8_t qppAddrMode;          /*!< QIO page program address mode */
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
    uint16_t timeE32k;            /*!< 32K erase time */
    uint16_t timeE64k;            /*!< 64K erase time */
    uint16_t timePagePgm;         /*!< Page program time */
    uint16_t timeCe;              /*!< Chip erase time in ms */
    uint8_t pdDelay;              /*!< Release power down command delay time for wake up */
    uint8_t qeData;               /*!< QE set data */
} __attribute__((packed)) SPI_Flash_Cfg_Type;

/**
 *  @brief Serial flash security register configuration
 */
typedef struct
{
    uint8_t eraseCmd;       /*!< Erase security register command */
    uint8_t programCmd;     /*!< Program security register command */
    uint8_t readCmd;        /*!< Read security register command */
    uint8_t enterSecOptCmd; /*!< Enter security register option mode command */
    uint8_t exitSecOptCmd;  /*!< Exit security register option mode command */
    uint8_t blockNum;       /*!< Security register block number */
    uint8_t *data;          /*!< Data pointer to be program/read */
    uint32_t addr;          /*!< Start address to be program/read */
    uint32_t len;           /*!< Data length to be program/read */
} SFlash_Sec_Reg_Cfg;
/*@} end of group SFLAH_Public_Types */

/** @defgroup  SFLAH_Public_Constants
 *  @{
 */

/*@} end of group SFLAH_Public_Constants */

/** @defgroup  SFLAH_Public_Macros
 *  @{
 */
#define BFLB_SPIFLASH_BLK32K_SIZE (32 * 1024)
#define BFLB_SPIFLASH_BLK64K_SIZE (64 * 1024)
#define BFLB_SPIFLASH_CMD_INVALID 0xff

/*@} end of group SFLAH_Public_Macros */

/** @defgroup  SFLAH_Public_Functions
 *  @{
 */
void ATTR_TCM_SECTION SFlash_Init(const SF_Ctrl_Cfg_Type *pSfCtrlCfg, const SF_Ctrl_Bank2_Cfg *pBank2Cfg);
BL_Err_Type SFlash_SetSPIMode(SF_Ctrl_Mode_Type mode);
BL_Err_Type SFlash_Read_Reg(SPI_Flash_Cfg_Type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen);
BL_Err_Type SFlash_Write_Reg(SPI_Flash_Cfg_Type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen);
BL_Err_Type SFlash_Read_Reg_With_Cmd(SPI_Flash_Cfg_Type *flashCfg, uint8_t readRegCmd, uint8_t *regValue,
                                     uint8_t regLen);
BL_Err_Type SFlash_Write_Reg_With_Cmd(SPI_Flash_Cfg_Type *flashCfg, uint8_t writeRegCmd, uint8_t *regValue,
                                      uint8_t regLen);
BL_Sts_Type SFlash_Busy(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Write_Enable(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Qspi_Enable(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Qspi_Disable(SPI_Flash_Cfg_Type *flashCfg);
void SFlash_Volatile_Reg_Write_Enable(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Chip_Erase(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Sector_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t secNum);
BL_Err_Type SFlash_Blk32_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t blkNum);
BL_Err_Type SFlash_Blk64_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t blkNum);
BL_Err_Type SFlash_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t startaddr, uint32_t endaddr);
void SFlash_GetUniqueId(uint8_t *data, uint8_t idLen);
void SFlash_GetJedecId(SPI_Flash_Cfg_Type *flashCfg, uint8_t *data);
void SFlash_GetDeviceId(uint8_t *data, BL_Fun_Type is32BitsAddr);
void SFlash_Powerdown(void);
void SFlash_Release_Powerdown(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Restore_From_Powerdown(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t flashContRead,
                                          SF_Ctrl_Bank_Select bank);
void SFlash_SetBurstWrap(SPI_Flash_Cfg_Type *flashCfg);
void SFlash_DisableBurstWrap(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Set32BitsAddrMode(SPI_Flash_Cfg_Type *flashCfg, BL_Fun_Type en32BitsAddr);
BL_Err_Type SFlash_Software_Reset(SPI_Flash_Cfg_Type *flashCfg);
void SFlash_Reset_Continue_Read(SPI_Flash_Cfg_Type *flashCfg);
BL_Err_Type SFlash_Set_IDbus_Cfg(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode, uint8_t contRead, uint32_t addr,
                                 uint32_t len, SF_Ctrl_Bank_Select bank);
BL_Err_Type SFlash_IDbus_Read_Enable(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode, uint8_t contRead,
                                     SF_Ctrl_Bank_Select bank);
void SFlash_IDbus_Read_Disable(void);
BL_Err_Type SFlash_RCV_Enable(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t rCmd, uint8_t wCmd, uint8_t bitPos);
BL_Err_Type SFlash_Erase_Security_Register(SPI_Flash_Cfg_Type *pFlashCfg, SFlash_Sec_Reg_Cfg *pSecRegCfg);
BL_Err_Type SFlash_Program_Security_Register(SPI_Flash_Cfg_Type *pFlashCfg,
                                             SFlash_Sec_Reg_Cfg *pSecRegCfg);
BL_Err_Type SFlash_Read_Security_Register(SFlash_Sec_Reg_Cfg *pSecRegCfg);
BL_Err_Type SFlash_Read(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode, uint8_t contRead, uint32_t addr, uint8_t *data,
                        uint32_t len);
BL_Err_Type SFlash_Program(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode, uint32_t addr, uint8_t *data, uint32_t len);

/*@} end of group SFLAH_Public_Functions */

/*@} end of group SFLAH */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_SFLAH_H__ */
