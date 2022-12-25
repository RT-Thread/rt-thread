/**
  ******************************************************************************
  * @file    bl808_sf_cfg.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_sf_cfg.h"
#include "softcrc.h"
#include "bl808_xip_sflash.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CFG
 *  @{
 */

/** @defgroup  SF_CFG_Private_Macros
 *  @{
 */
#define BFLB_FLASH_CFG_MAGIC "FCFG"

/*@} end of group SF_CFG_Private_Macros */

/** @defgroup  SF_CFG_Private_Types
 *  @{
 */
#ifndef BFLB_USE_ROM_DRIVER
typedef struct
{
    uint32_t jedecID;
    char *name;
    const SPI_Flash_Cfg_Type *cfg;
} Flash_Info_t;
#endif

/*@} end of group SF_CFG_Private_Types */

/** @defgroup  SF_CFG_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_ROM_DRIVER
static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_80DV = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 0,
    .cReadMode = 0xFF,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3d,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 300,
    .timeE32k = 1200,
    .timeE64k = 1200,
    .timePagePgm = 5,
    .timeCe = 20 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_16JV = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0x20,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_64JW = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 0,
    .cReadMode = 0xf0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Winb_256FV = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xef,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0x20,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = 0x24,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1600,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 3,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Gd_Q80E_Q16E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 500,
    .timeE32k = 2000,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Gd_WQ80E_WQ16E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 32 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 8 / 8,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 300,
    .timeE32k = 1200,
    .timeE64k = 1200,
    .timePagePgm = 5,
    .timeCe = 20 * 1000,
    .pdDelay = 20,
    .qeData = 0x12,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Gd_Q32E_Q128E = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc8,

    .deBurstWrapCmd = 0x77,
    .deBurstWrapCmdDmyClk = 0x3,
    .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .deBurstWrapData = 0xF0,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 1,
    .qeBit = 0x01,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x31,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xa0,

    .burstWrapCmd = 0x77,
    .burstWrapCmdDmyClk = 0x3,
    .burstWrapDataMode = SF_CTRL_DATA_4_LINES,
    .burstWrapData = 0x40,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x32,
    .qppAddrMode = SF_CTRL_ADDR_1_LINE,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 300,
    .timeE32k = 1200,
    .timeE64k = 1200,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Mxic_128 = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xC2,

    .deBurstWrapCmd = 0xC0,
    .deBurstWrapCmdDmyClk = 0x00,
    .deBurstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .deBurstWrapData = 0x10,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 0,
    .qeBit = 0x06,
    .qeWriteRegLen = 0x01,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x35,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xA5,

    .burstWrapCmd = 0xC0,
    .burstWrapCmdDmyClk = 0x00,
    .burstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .burstWrapData = 0x02,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x38,
    .qppAddrMode = SF_CTRL_ADDR_4_LINES,

    .ioMode = SF_CTRL_QIO_MODE,
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 300,
    .timeE32k = 1200,
    .timeE64k = 1200,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 45,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION SPI_Flash_Cfg_Type flashCfg_Mxic_25L256 = {
    .resetCreadCmd = 0xff,
    .resetCreadCmdSize = 3,
    .mid = 0xc2,

    .deBurstWrapCmd = 0xC0,
    .deBurstWrapCmdDmyClk = 0x00,
    .deBurstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .deBurstWrapData = 0x10,

    /*reg*/
    .writeEnableCmd = 0x06,
    .wrEnableIndex = 0x00,
    .wrEnableBit = 0x01,
    .wrEnableReadRegLen = 0x01,

    .qeIndex = 0,
    .qeBit = 0x06,
    .qeWriteRegLen = 0x02,
    .qeReadRegLen = 0x1,

    .busyIndex = 0,
    .busyBit = 0x00,
    .busyReadRegLen = 0x1,
    .releasePowerDown = 0xab,

    .readRegCmd[0] = 0x05,
    .readRegCmd[1] = 0x15,
    .writeRegCmd[0] = 0x01,
    .writeRegCmd[1] = 0x01,

    .fastReadQioCmd = 0xeb,
    .frQioDmyClk = 16 / 8,
    .cReadSupport = 1,
    .cReadMode = 0xA5,

    .burstWrapCmd = 0xC0,
    .burstWrapCmdDmyClk = 0x00,
    .burstWrapDataMode = SF_CTRL_DATA_1_LINE,
    .burstWrapData = 0x02,
    /*erase*/
    .chipEraseCmd = 0xc7,
    .sectorEraseCmd = 0x20,
    .blk32EraseCmd = 0x52,
    .blk64EraseCmd = 0xd8,
    /*write*/
    .pageProgramCmd = 0x02,
    .qpageProgramCmd = 0x38,
    .qppAddrMode = SF_CTRL_ADDR_4_LINES,

    .ioMode = (SF_CTRL_QIO_MODE | 0x20),
    .clkDelay = 1,
    .clkInvert = 0x3f,

    .resetEnCmd = 0x66,
    .resetCmd = 0x99,
    .cRExit = 0xff,
    .wrEnableWriteRegLen = 0x00,

    /*id*/
    .jedecIdCmd = 0x9f,
    .jedecIdCmdDmyClk = 0,
    .enter32BitsAddrCmd = 0xb7,
    .exit32BitsAddrCmd = 0xe9,
    .sectorSize = 4,
    .pageSize = 256,

    /*read*/
    .fastReadCmd = 0x0b,
    .frDmyClk = 8 / 8,
    .qpiFastReadCmd = 0x0b,
    .qpiFrDmyClk = 8 / 8,
    .fastReadDoCmd = 0x3b,
    .frDoDmyClk = 8 / 8,
    .fastReadDioCmd = 0xbb,
    .frDioDmyClk = 0,
    .fastReadQoCmd = 0x6b,
    .frQoDmyClk = 8 / 8,

    .qpiFastReadQioCmd = 0xeb,
    .qpiFrQioDmyClk = 16 / 8,
    .qpiPageProgramCmd = 0x02,
    .writeVregEnableCmd = 0x50,

    /* qpi mode */
    .enterQpi = 0x38,
    .exitQpi = 0xff,

    /*AC*/
    .timeEsector = 400,
    .timeE32k = 1000,
    .timeE64k = 2000,
    .timePagePgm = 5,
    .timeCe = 33 * 1000,
    .pdDelay = 20,
    .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION Flash_Info_t flashInfos[] = {
    {
        .jedecID = 0x1440ef,
        //.name="Winb_80DV_08_33",
        .cfg = &flashCfg_Winb_80DV,
    },
    {
        .jedecID = 0x1540ef,
        //.name="Winb_16JV_16_33",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1640ef,
        //.name="Winb_32FV_32_33",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1840ef,
        //.name="Winb_128JV_128_33",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID = 0x1940ef,
        //.name="Winb_256FV_128_33",
        .cfg = &flashCfg_Winb_256FV,
    },
    {
        .jedecID = 0x1460ef,
        //.name="Winb_80EW_08_18",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1560ef,
        //.name="Winb_16FW_16_18",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1660ef,
        //.name="Winb_32FW_32_18",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1760ef,
        //.name="WB_64JW_64_18",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID = 0x1860ef,
        //.name="Winb_128JW_128_18",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID = 0x1570ef,
        //.name="Winb_16JV_16_33",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1870ef,
        //.name="Winb_128JV_128_33",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID = 0x1680ef,
        //.name="Winb_32JW_32_18",
        .cfg = &flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x1880ef,
        //.name="Winb_128JW_128_18",
        .cfg = &flashCfg_Winb_64JW,
    },
    {
        .jedecID = 0x1440C8,
        //.name="GD_Q08E_08_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1540C8,
        //.name="GD_Q16E_16_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1640C8,
        //.name="GD_Q32C_32_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x1740C8,
        //.name="GD_Q64E_64_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x1840C8,
        //.name="GD_Q128E_128_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x1460C8,
        //.name="GD_LQ08C_08_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1560C8,
        //.name="GD_LE16C_16_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1660C8,
        //.name="GD_LQ32D_32_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1760c8,
        //.name="GD_LQ64E_64_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1860c8,
        //.name="GD_LQ128E_64_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x1465C8,
        //.name="GD_WQ80E_80_33",
        .cfg = &flashCfg_Gd_WQ80E_WQ16E,
    },
    {
        .jedecID = 0x1565C8,
        //.name="GD_WQ16E_16_33",
        .cfg = &flashCfg_Gd_WQ80E_WQ16E,
    },
    {
        .jedecID = 0x1665C8,
        //.name="GD_WQ32E_32_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x15345e,
        //.name="ZB_WQ16A_16_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x15405e,
        //.name="ZB_Q16B_16_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x16405e,
        //.name="ZB_Q32B_32_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x17405e,
        //.name="ZB_Q64B_64_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x14605E,
        //.name="ZB_VQ80",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x15605E,
        //.name="ZB_VQ16",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x1820C2,
        //.name="MX_25L128_128_33",
        .cfg = &flashCfg_Mxic_128,
    },
    {
        .jedecID = 0x1920C2,
        //.name="MX_25L256_256_33",
        .cfg = &flashCfg_Mxic_25L256,
    },
    {
        .jedecID = 0x3925C2,
        //.name="MX_25U256_256_33",
        .cfg = &flashCfg_Mxic_25L256,
    },
    {
        .jedecID=0x144020,
        //.name="XM_25QH80_80_33",
        .cfg=&flashCfg_Winb_16JV,
    },
    {
        .jedecID=0x154020,
        //.name="XM_25QH16_16_33",
        .cfg=&flashCfg_Winb_16JV,
    },
    {
        .jedecID=0x164020,
        //.name="XM_25QH32_32_33",
        .cfg=&flashCfg_Winb_16JV,
    },
    {
        .jedecID=0x174020,
        //.name="XM_25QH64_64_33",
        .cfg=&flashCfg_Winb_16JV,
    },
    {
        .jedecID = 0x15400B,
        //.name="XT_25F16B_16_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x16400B,
        //.name="XT_25F32B_32_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x17400B,
        //.name="XT_25F64B_32_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x18400B,
        //.name="XT_25F128B_128_33",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x14600B,
        //.name="XT_25Q80B_08_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x16600B,
        //.name="XT_25Q32B_32_18",
        .cfg = &flashCfg_Gd_Q80E_Q16E,
    },
    {
        .jedecID = 0x144068,
        //.name="Boya_Q08B_08_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x154068,
        //.name="Boya_Q16B_16_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x164068,
        //.name="Boya_Q32B_32_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x174068,
        //.name="Boya_Q64A_64_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    },
    {
        .jedecID = 0x184068,
        //.name="Boya_Q128A_128_33",
        .cfg = &flashCfg_Gd_Q32E_Q128E,
    }
};
#endif

/*@} end of group SF_CFG_Private_Variables */

/** @defgroup  SF_CFG_Global_Variables
 *  @{
 */

/*@} end of group SF_CFG_Global_Variables */

/** @defgroup  SF_CFG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SF_CFG_Private_Fun_Declaration */

/** @defgroup  SF_CFG_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Init external flash GPIO according to flash GPIO config
 *
 * @param  extFlashPin: Flash GPIO config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Init_Ext_Flash_Gpio(uint8_t extFlashPin)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[6];
    uint8_t i = 0;

    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 2;
    cfg.smtCtrl = 1;
    cfg.gpioFun = GPIO_FUN_FLASH;

    if (extFlashPin == 0) {
        gpiopins[0] = BFLB_EXTFLASH_CLK0_GPIO;
        gpiopins[1] = BFLB_EXTFLASH_CS0_GPIO;
        gpiopins[2] = BFLB_EXTFLASH_DATA00_GPIO;
        gpiopins[3] = BFLB_EXTFLASH_DATA10_GPIO;
        gpiopins[4] = BFLB_EXTFLASH_DATA20_GPIO;
        gpiopins[5] = BFLB_EXTFLASH_DATA30_GPIO;
    } else {
        return ERROR;
    }

    for (i = 0; i < sizeof(gpiopins); i++) {
        cfg.gpioPin = gpiopins[i];

        if (i == 0 || i == 1) {
            /* flash clk and cs is output */
            cfg.gpioMode = GPIO_MODE_OUTPUT;
        } else {
            /* data are bidir */
            cfg.gpioMode = GPIO_MODE_AF;
        }

        GLB_GPIO_Init(&cfg);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Deinit external flash GPIO according to flash GPIO config
 *
 * @param  extFlashPin: Flash GPIO config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Deinit_Ext_Flash_Gpio(uint8_t extFlashPin)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[6];
    uint8_t i = 0;

    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 1;
    cfg.smtCtrl = 1;
    cfg.gpioFun = GPIO_FUN_GPIO;

    if (extFlashPin == 0) {
        gpiopins[0] = BFLB_EXTFLASH_CLK0_GPIO;
        gpiopins[1] = BFLB_EXTFLASH_CS0_GPIO;
        gpiopins[2] = BFLB_EXTFLASH_DATA00_GPIO;
        gpiopins[3] = BFLB_EXTFLASH_DATA10_GPIO;
        gpiopins[4] = BFLB_EXTFLASH_DATA20_GPIO;
        gpiopins[5] = BFLB_EXTFLASH_DATA30_GPIO;
    } else {
        return ERROR;
    }

    for (i = 0; i < sizeof(gpiopins); i++) {
        cfg.gpioPin = gpiopins[i];
        GLB_GPIO_Init(&cfg);
    }

    return SUCCESS;
}
#endif

/*@} end of group SF_CFG_Private_Functions */

/** @defgroup  SF_CFG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Get flash config according to flash ID
 *
 * @param  flashID: Flash ID
 * @param  pFlashCfg: Flash config pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Get_Flash_Cfg_Need_Lock(uint32_t flashID, SPI_Flash_Cfg_Type *pFlashCfg,
                                                            uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint32_t i;
    uint8_t buf[sizeof(SPI_Flash_Cfg_Type) + 8];
    uint32_t crc, *pCrc;
    uint32_t xipOffset;

    if (flashID == 0) {
        xipOffset = SF_Ctrl_Get_Flash_Image_Offset(group, bank);
        SF_Ctrl_Set_Flash_Image_Offset(0, group, bank);
        XIP_SFlash_Read_Via_Cache_Need_Lock(8 + BL808_FLASH_XIP_BASE, buf, sizeof(SPI_Flash_Cfg_Type) + 8, group, bank);
        SF_Ctrl_Set_Flash_Image_Offset(xipOffset, group, bank);

        if (ARCH_MemCmp(buf, BFLB_FLASH_CFG_MAGIC, 4) == 0) {
            crc = BFLB_Soft_CRC32((uint8_t *)buf + 4, sizeof(SPI_Flash_Cfg_Type));
            pCrc = (uint32_t *)(buf + 4 + sizeof(SPI_Flash_Cfg_Type));

            if (*pCrc == crc) {
                ARCH_MemCpy_Fast(pFlashCfg, (uint8_t *)buf + 4, sizeof(SPI_Flash_Cfg_Type));
                return SUCCESS;
            }
        }
    } else {
        for (i = 0; i < sizeof(flashInfos) / sizeof(flashInfos[0]); i++) {
            if (flashInfos[i].jedecID == flashID) {
                ARCH_MemCpy_Fast(pFlashCfg, flashInfos[i].cfg, sizeof(SPI_Flash_Cfg_Type));
                return SUCCESS;
            }
        }
    }

    return ERROR;
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash config according to flash ID patch
 *
 * @param  flashID: Flash ID
 * @param  pFlashCfg: Flash config pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Get_Flash_Cfg_Need_Lock_Ext(uint32_t flashID, SPI_Flash_Cfg_Type *pFlashCfg,
                                                                uint8_t group, SF_Ctrl_Bank_Select bank)
{
    return SF_Cfg_Get_Flash_Cfg_Need_Lock(flashID, pFlashCfg, group, bank);
}
#endif

/****************************************************************************/ /**
 * @brief  Init flash GPIO according to flash Pin config
 *
 * @param  flashPinCfg: Specify flash Pin config
 * @param  restoreDefault: Wether to restore default setting
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Init_Flash_Gpio(SF_Ctrl_Pin_Select flashPinCfg, uint8_t restoreDefault)
{
    uint8_t selEmbedded = 0;
    uint8_t swap = 0;

    if ((flashPinCfg&(1<<3)) > 0) {
        return ERROR;
    }

    if (restoreDefault) {
        /* Set Default first */
        GLB_Set_Flash_IO_PARM(1, 1);
        SF_Ctrl_Select_Pad(SF_IO_EMB_SWAP_IO0_IO3);

        /* Default is set, so return */
        if (flashPinCfg == SF_IO_EMB_SWAP_IO0_IO3) {
            return SUCCESS;
        }
    }

    if (flashPinCfg & (1 << 2)) {
        /* Init sf2 gpio */
        SF_Cfg_Init_Ext_Flash_Gpio(0);
        selEmbedded = 0;
    } else {
        selEmbedded = 1;
    }
    /* if pin select dual flash, embedded is default */
    if ((flashPinCfg & (1 << 4))) {
        selEmbedded = 1;
    }

    swap = ((flashPinCfg >> 1) & 1);
    swap = (!swap);
    GLB_Set_Flash_IO_PARM(selEmbedded, swap);
    SF_Ctrl_Select_Pad(flashPinCfg);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Identify one flash
 *
 * @param  callFromFlash: code run at flash or ram
 * @param  flashPinCfg: Bit 7: autoscan, Bit6-0: flash GPIO config
 * @param  restoreDefault: Wether restore default flash GPIO config
 * @param  pFlashCfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint32_t ATTR_TCM_SECTION SF_Cfg_Flash_Identify(uint8_t callFromFlash, uint8_t flashPinCfg,
                                                uint8_t restoreDefault, SPI_Flash_Cfg_Type *pFlashCfg, uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint8_t autoScan = 0;
    uint8_t flashPin = 0;
    uint32_t jdecId = 0;
    uint32_t i = 0;
    uint32_t offset;
    BL_Err_Type stat;

    autoScan = ((flashPinCfg >> 7) & 1);
    flashPin = (flashPinCfg & 0x7F);

    ARCH_MemCpy_Fast(pFlashCfg, &flashCfg_Winb_16JV, sizeof(SPI_Flash_Cfg_Type));

    if (callFromFlash == 1) {
        stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

        if (stat != SUCCESS) {
            SF_Ctrl_Set_Owner(SF_CTRL_OWNER_IAHB);
            return 0;
        }
    }

    if (autoScan) {
        flashPin = 0;

        do {
            if (flashPin > SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
                jdecId = 0;
                break;
            }

            if (!IS_SF_CTRL_PIN_SELECT(flashPin) || (flashPin&(1<<3)) > 0) {
                flashPin++;
                continue;
            }

            SF_Cfg_Init_Flash_Gpio(flashPin, restoreDefault);
            SFlash_Release_Powerdown(pFlashCfg);
            SFlash_Reset_Continue_Read(pFlashCfg);
            SFlash_DisableBurstWrap(pFlashCfg);
            jdecId = 0;
            SFlash_GetJedecId(pFlashCfg, (uint8_t *)&jdecId);
            SFlash_DisableBurstWrap(pFlashCfg);
            jdecId = jdecId & 0xffffff;
            flashPin++;
        } while ((jdecId & 0x00ffff) == 0 || (jdecId & 0xffff00) == 0 || (jdecId & 0x00ffff) == 0xffff || (jdecId & 0xffff00) == 0xffff00);
    } else {
        /* select media gpio */
        SF_Cfg_Init_Flash_Gpio(flashPin, restoreDefault);
        SFlash_Release_Powerdown(pFlashCfg);
        SFlash_Reset_Continue_Read(pFlashCfg);
        SFlash_DisableBurstWrap(pFlashCfg);
        SFlash_GetJedecId(pFlashCfg, (uint8_t *)&jdecId);
        SFlash_DisableBurstWrap(pFlashCfg);
        jdecId = jdecId & 0xffffff;
    }

    for (i = 0; i < sizeof(flashInfos) / sizeof(flashInfos[0]); i++) {
        if (flashInfos[i].jedecID == jdecId) {
            ARCH_MemCpy_Fast(pFlashCfg, flashInfos[i].cfg, sizeof(SPI_Flash_Cfg_Type));
            break;
        }
    }

    if (i == sizeof(flashInfos) / sizeof(flashInfos[0])) {
        if (callFromFlash == 1) {
            XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
        }

        return jdecId;
    } else {
        if (callFromFlash == 1) {
            XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
        }

        return (jdecId | BFLB_FLASH_ID_VALID_FLAG);
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Identify one flash patch
 *
 * @param  callFromFlash: code run at flash or ram
 * @param  flashPinCfg: Bit 7: autoscan, Bit6-0: flash GPIO config
 * @param  restoreDefault: Wether restore default flash GPIO config
 * @param  pFlashCfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
uint32_t ATTR_TCM_SECTION SF_Cfg_Flash_Identify_Ext(uint8_t callFromFlash, uint8_t flashPinCfg,
    uint8_t restoreDefault, SPI_Flash_Cfg_Type *pFlashCfg, uint8_t group, SF_Ctrl_Bank_Select bank)
{
    return SF_Cfg_Flash_Identify(callFromFlash, flashPinCfg, restoreDefault, pFlashCfg, group, bank);
}
#endif

/****************************************************************************/ /**
 * @brief  SF Cfg flash init
 *
 * @param  sel: SF pin select
 * @param  pSfCtrlCfg: Serial flash controller configuration pointer
 * @param  pBank2Cfg: Serial flash2 controller configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Flash_Init(SF_Ctrl_Pin_Select sel, const SF_Ctrl_Cfg_Type *pSfCtrlCfg, const SF_Ctrl_Bank2_Cfg *pBank2Cfg)
{
    uint8_t selEmbedded = 0;
    uint8_t swap = 0;

    if ((sel&(1<<3)) > 0) {
        return ERROR;
    }

    if (sel & (1 << 2)) {
        SF_Cfg_Init_Ext_Flash_Gpio(0);
        selEmbedded = 0;
    } else {
        selEmbedded = 1;
    }
    /* If pin select dual flash, embedded is default */
    if ((sel & (1 << 4))) {
        selEmbedded = 1;
    }

    swap = ((sel >> 1) & 1);
    swap = (!swap);
    GLB_Set_Flash_IO_PARM(selEmbedded, swap);
    SF_Ctrl_Select_Pad(sel);

    if (sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0) {
        /* Embedded pad1 io delay set */
        SF_Ctrl_Set_IO_Delay(SF_CTRL_PAD1, pSfCtrlCfg->doDelay, pSfCtrlCfg->diDelay, pSfCtrlCfg->oeDelay);
    } else if (sel <= SF_IO_EXT_SF2) {
        /* Pad2 or pad3 io delay set */
        SF_Ctrl_Set_IO_Delay((sel >> 2), pSfCtrlCfg->doDelay, pSfCtrlCfg->diDelay, pSfCtrlCfg->oeDelay);
    } else if (sel >= SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 && sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
        /* Dual flash mode, embedded pad1 and pad2 io delay set */
        SF_Ctrl_Set_IO_Delay(SF_CTRL_PAD1, pSfCtrlCfg->doDelay, pSfCtrlCfg->diDelay, pSfCtrlCfg->oeDelay);
        SF_Ctrl_Set_IO_Delay(SF_CTRL_PAD2, pBank2Cfg->doDelay, pBank2Cfg->diDelay, pBank2Cfg->oeDelay);
    }

    if (pBank2Cfg != NULL) {
        if (pBank2Cfg->sbus2Select) {
            if (sel >= SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 && sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
                /* Default sbus2 replace opt flash2 */
                SF_Ctrl_Sbus2_Replace(SF_CTRL_PAD2);
            }
        }
    }

    SFlash_Init(pSfCtrlCfg, pBank2Cfg);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  SF Cfg system bus 2 flash init
 *
 * @param  sel: SF pin select
 * @param  pBank2Cfg: Serial flash2 controller configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SF_Cfg_Sbus2_Flash_Init(SF_Ctrl_Pin_Select sel, const SF_Ctrl_Bank2_Cfg *pBank2Cfg)
{
    if (sel < SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 || sel > SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
        return ERROR;
    }

    /* Init flash2 gpio */
    if (sel & (1 << 2)) {
        SF_Cfg_Init_Ext_Flash_Gpio(0);
    }

    /* Set remap for flash2 xip mode */
    SF_Ctrl_Remap_Set(pBank2Cfg->remap, pBank2Cfg->remapLock);

    /* Dual flash mode, pad2 io delay set */
    SF_Ctrl_Set_IO_Delay(SF_CTRL_PAD2, pBank2Cfg->doDelay, pBank2Cfg->diDelay, pBank2Cfg->oeDelay);

    if (pBank2Cfg->sbus2Select) {
        /* Default sbus2 replace opt flash2 */
        SF_Ctrl_Sbus2_Replace(SF_CTRL_PAD2);
    }

    SFlash_Init(NULL, pBank2Cfg);

    return SUCCESS;
}
#endif

/*@} end of group SF_CFG_Public_Functions */

/*@} end of group SF_CFG */

/*@} end of group BL808_Peripheral_Driver */
