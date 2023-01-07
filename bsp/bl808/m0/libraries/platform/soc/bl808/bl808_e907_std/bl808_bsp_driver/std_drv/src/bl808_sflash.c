/**
  ******************************************************************************
  * @file    bl808_sflash.c
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

#include "string.h"
#include "bl808_sflash.h"
#include "bl808_sf_ctrl.h"
#include "bl808_l1c.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLASH
 *  @{
 */

/** @defgroup  SFLASH_Private_Macros
 *  @{
 */

/*@} end of group SFLASH_Private_Macros */

/** @defgroup  SFLASH_Private_Types
 *  @{
 */

/*@} end of group SFLASH_Private_Types */

/** @defgroup  SFLASH_Private_Variables
 *  @{
 */
#define SFCTRL_BUSY_STATE_TIMEOUT (5 * 320 * 1000)

/*@} end of group SFLASH_Private_Variables */

/** @defgroup  SFLASH_Global_Variables
 *  @{
 */

/*@} end of group SFLASH_Global_Variables */

/** @defgroup  SFLASH_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SFLASH_Private_Fun_Declaration */

/** @defgroup  SFLASH_Private_Functions
 *  @{
 */

/*@} end of group SFLASH_Private_Functions */

/** @defgroup  SFLASH_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Init serial flash control interface
 *
 * @param  pSfCtrlCfg: Serial flash controller configuration pointer
 * @param  pBank2Cfg: Serial flash2 controller configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_Init(const SF_Ctrl_Cfg_Type *pSfCtrlCfg, const SF_Ctrl_Bank2_Cfg *pBank2Cfg)
{
    uint8_t clkDelay = 0;
    uint8_t rxClkInvert = 0;

    if (pBank2Cfg != NULL) {
        if (pBank2Cfg->sbus2Select) {
            if (pBank2Cfg->bank2DelaySrc) {
                clkDelay = pBank2Cfg->bank2ClkDelay;
            } else {
                if (pSfCtrlCfg != NULL) {
                    clkDelay = pSfCtrlCfg->clkDelay;
                } else {
                    clkDelay = 1;
                }
            }

            if (pBank2Cfg->bank2RxClkInvertSrc) {
                rxClkInvert = pBank2Cfg->bank2RxClkInvertSel;
            } else {
                if (pSfCtrlCfg != NULL) {
                    rxClkInvert = pSfCtrlCfg->rxClkInvert;
                } else {
                    rxClkInvert = 0;
                }
            }

            SF_Ctrl_Sbus2_Set_Delay(clkDelay, rxClkInvert);
        } else {
            SF_Ctrl_Sbus2_Revoke_replace();
        }

        SF_Ctrl_Bank2_Enable(pBank2Cfg);
    } else {
        SF_Ctrl_Sbus2_Revoke_replace();
    }

    if (pSfCtrlCfg != NULL) {
        SF_Ctrl_Enable(pSfCtrlCfg);
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Set serial flash control interface SPI or QPI mode
 *
 * @param  mode: Serial flash interface mode
 *
 * @return BFLB_RET:SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_SetSPIMode(SF_Ctrl_Mode_Type mode)
{
    BL_Err_Type stat = SUCCESS;

    /* Check the parameters */
    CHECK_PARAM(IS_SF_CTRL_MODE_TYPE(mode));

    return stat;
}
#endif

/****************************************************************************/ /**
 * @brief  Read flash register
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  regIndex: register index
 * @param  regValue: register value pointer to store data
 * @param  regLen: register value length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Read_Reg(SPI_Flash_Cfg_Type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t cnt = 0;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.cmdBuf[0] = (flashCfg->readRegCmd[regIndex]) << 24;
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.nbData = regLen;

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SF_Ctrl_GetBusyState()) {
        arch_delay_us(1);
        cnt++;

        if (cnt > 1000) {
            return ERROR;
        }
    }

    ARCH_MemCpy(regValue, flashCtrlBuf, regLen);
    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Write flash register
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  regIndex: register index
 * @param  regValue: register value pointer storing data
 * @param  regLen: register value length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Write_Reg(SPI_Flash_Cfg_Type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t cnt = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    ARCH_MemCpy(flashCtrlBuf, regValue, regLen);

    flashCmd.cmdBuf[0] = (flashCfg->writeRegCmd[regIndex]) << 24;
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.nbData = regLen;

    SF_Ctrl_SendCmd(&flashCmd);

    /* take 40ms for tw(write status register) as default */
    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 400) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Read flash register with read command
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  readRegCmd: read command
 * @param  regValue: register value pointer to store data
 * @param  regLen: register value length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Read_Reg_With_Cmd(SPI_Flash_Cfg_Type *flashCfg, uint8_t readRegCmd, uint8_t *regValue, uint8_t regLen)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t cnt = 0;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.cmdBuf[0] = readRegCmd << 24;
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.nbData = regLen;

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SF_Ctrl_GetBusyState()) {
        arch_delay_us(1);
        cnt++;

        if (cnt > 1000) {
            return ERROR;
        }
    }

    ARCH_MemCpy(regValue, flashCtrlBuf, regLen);
    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Write flash register with write command
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  writeRegCmd: write command
 * @param  regValue: register value pointer storing data
 * @param  regLen: register value length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Write_Reg_With_Cmd(SPI_Flash_Cfg_Type *flashCfg, uint8_t writeRegCmd, uint8_t *regValue, uint8_t regLen)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t cnt = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    ARCH_MemCpy(flashCtrlBuf, regValue, regLen);

    flashCmd.cmdBuf[0] = writeRegCmd << 24;
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.nbData = regLen;

    SF_Ctrl_SendCmd(&flashCmd);

    /* take 40ms for tw(write status register) as default */
    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 400) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Check flash busy status
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SET for busy or RESET for not busy
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Sts_Type ATTR_TCM_SECTION SFlash_Busy(SPI_Flash_Cfg_Type *flashCfg)
{
    uint32_t stat = 0;
    SFlash_Read_Reg(flashCfg, flashCfg->busyIndex, (uint8_t *)&stat, flashCfg->busyReadRegLen);

    if ((stat & (1 << flashCfg->busyBit)) == 0) {
        return RESET;
    }

    return SET;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable flash write function
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Write_Enable(SPI_Flash_Cfg_Type *flashCfg)
{
    uint32_t stat = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Write enable*/
    flashCmd.cmdBuf[0] = (flashCfg->writeEnableCmd) << 24;
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    SF_Ctrl_SendCmd(&flashCmd);

    SFlash_Read_Reg(flashCfg, flashCfg->wrEnableIndex, (uint8_t *)&stat, flashCfg->wrEnableReadRegLen);

    if ((stat & (1 << flashCfg->wrEnableBit)) != 0) {
        return SUCCESS;
    }

    return ERROR;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable flash flash controller QSPI interface
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Qspi_Enable(SPI_Flash_Cfg_Type *flashCfg)
{
    uint32_t stat = 0, ret;

    if (flashCfg->qeReadRegLen == 0) {
        ret = SFlash_Write_Enable(flashCfg);

        if (SUCCESS != ret) {
            return ERROR;
        }

        SFlash_Write_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeWriteRegLen);
        return SUCCESS;
    }

    SFlash_Read_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeReadRegLen);

    if (flashCfg->qeData == 0) {
        if ((stat & (1 << flashCfg->qeBit)) != 0) {
            return SUCCESS;
        }
    } else {
        if (((stat >> (flashCfg->qeBit & 0x08)) & 0xff) == flashCfg->qeData) {
            return SUCCESS;
        }
    }

    if (flashCfg->qeWriteRegLen != 1) {
        /* This is  read r0,read r1 write r0,r1 case*/
        SFlash_Read_Reg(flashCfg, 0, (uint8_t *)&stat, 1);
        SFlash_Read_Reg(flashCfg, 1, ((uint8_t *)&stat) + 1, 1);

        if (flashCfg->qeData == 0) {
            stat |= (1 << (flashCfg->qeBit + 8 * flashCfg->qeIndex));
        } else {
            stat = stat & (~(0xff << (8 * flashCfg->qeIndex)));
            stat |= (flashCfg->qeData << (8 * flashCfg->qeIndex));
        }
    } else {
        if (flashCfg->qeData == 0) {
            stat |= (1 << (flashCfg->qeBit % 8));
        } else {
            stat = flashCfg->qeData;
        }
    }

    ret = SFlash_Write_Enable(flashCfg);

    if (SUCCESS != ret) {
        return ERROR;
    }

    SFlash_Write_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeWriteRegLen);
    SFlash_Read_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeReadRegLen);

    if (flashCfg->qeData == 0) {
        if ((stat & (1 << flashCfg->qeBit)) != 0) {
            return SUCCESS;
        }
    } else {
        if (((stat >> (flashCfg->qeBit & 0x08)) & 0xff) == flashCfg->qeData) {
            return SUCCESS;
        }
    }

    return ERROR;
}
#endif

/****************************************************************************/ /**
 * @brief  Disable flash flash controller QSPI interface
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Qspi_Disable(SPI_Flash_Cfg_Type *flashCfg)
{
    uint32_t stat = 0, ret;

    if (flashCfg->qeReadRegLen == 0) {
        ret = SFlash_Write_Enable(flashCfg);

        if (SUCCESS != ret) {
            return ERROR;
        }

        SFlash_Write_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeWriteRegLen);
        return SUCCESS;
    }

    SFlash_Read_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeReadRegLen);

    if ((stat & (1 << flashCfg->qeBit)) == 0) {
        return SUCCESS;
    }

    if (flashCfg->qeWriteRegLen != 1) {
        /* This is  read r0,read r1 write r0,r1 case*/
        SFlash_Read_Reg(flashCfg, 0, (uint8_t *)&stat, 1);
        SFlash_Read_Reg(flashCfg, 1, ((uint8_t *)&stat) + 1, 1);
        stat &= (~(1 << (flashCfg->qeBit + 8 * flashCfg->qeIndex)));
    } else {
        stat &= (~(1 << (flashCfg->qeBit % 8)));
    }

    ret = SFlash_Write_Enable(flashCfg);

    if (SUCCESS != ret) {
        return ERROR;
    }

    SFlash_Write_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeWriteRegLen);
    SFlash_Read_Reg(flashCfg, flashCfg->qeIndex, (uint8_t *)&stat, flashCfg->qeReadRegLen);

    if ((stat & (1 << flashCfg->qeBit)) == 0) {
        return SUCCESS;
    }

    return ERROR;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable flash volatile register write enable
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_Volatile_Reg_Write_Enable(SPI_Flash_Cfg_Type *flashCfg)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.cmdBuf[0] = (flashCfg->writeVregEnableCmd) << 24;
    flashCmd.rwFlag = SF_CTRL_WRITE;

    SF_Ctrl_SendCmd(&flashCmd);
}
#endif

/****************************************************************************/ /**
 * @brief  Erase flash whole chip
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Chip_Erase(SPI_Flash_Cfg_Type *flashCfg)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t cnt = 0;
    uint32_t timeout = 0;
    BL_Err_Type stat = SFlash_Write_Enable(flashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.cmdBuf[0] = (flashCfg->chipEraseCmd) << 24;
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;

    SF_Ctrl_SendCmd(&flashCmd);

    timeout = flashCfg->timeCe;

    if ((timeout >> 15) > 0) {
        timeout = (timeout & 0x7FFF) * 1000;
    }

    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > timeout * 3) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Erase flash one sector
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  secNum: flash sector number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Sector_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t secNum)
{
    uint32_t cnt = 0;
    uint8_t is32BitsAddr = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    BL_Err_Type stat = SFlash_Write_Enable(flashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
        flashCmd.cmdBuf[0] = (flashCfg->sectorEraseCmd << 24) | ((flashCfg->sectorSize * 1024 * secNum) >> 8);
        flashCmd.cmdBuf[1] = ((flashCfg->sectorSize * 1024 * secNum) << 24);
    } else {
        flashCmd.cmdBuf[0] = (flashCfg->sectorEraseCmd << 24) | (flashCfg->sectorSize * 1024 * secNum);
    }

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flashCfg->timeEsector * 3) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Erase flash one 32K block
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  blkNum: flash 32K block number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Blk32_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t blkNum)
{
    uint32_t cnt = 0;
    uint8_t is32BitsAddr = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    BL_Err_Type stat = SFlash_Write_Enable(flashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
        flashCmd.cmdBuf[0] = (flashCfg->blk32EraseCmd << 24) | ((BFLB_SPIFLASH_BLK32K_SIZE * blkNum) >> 8);
        flashCmd.cmdBuf[1] = ((BFLB_SPIFLASH_BLK32K_SIZE * blkNum) << 24);
    } else {
        flashCmd.cmdBuf[0] = (flashCfg->blk32EraseCmd << 24) | (BFLB_SPIFLASH_BLK32K_SIZE * blkNum);
    }

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flashCfg->timeE32k * 3) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Erase flash one 64K block
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  blkNum: flash 64K block number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Blk64_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t blkNum)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t cnt = 0;
    uint8_t is32BitsAddr = 0;
    BL_Err_Type stat = SFlash_Write_Enable(flashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
        flashCmd.cmdBuf[0] = (flashCfg->blk64EraseCmd << 24) | ((BFLB_SPIFLASH_BLK64K_SIZE * blkNum) >> 8);
        flashCmd.cmdBuf[1] = ((BFLB_SPIFLASH_BLK64K_SIZE * blkNum) << 24);
    } else {
        flashCmd.cmdBuf[0] = (flashCfg->blk64EraseCmd << 24) | (BFLB_SPIFLASH_BLK64K_SIZE * blkNum);
    }

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flashCfg->timeE64k * 3) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  startaddr: start address to erase
 * @param  endaddr: end address(include this address) to erase
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Erase(SPI_Flash_Cfg_Type *flashCfg, uint32_t startaddr, uint32_t endaddr)
{
    uint32_t len = 0;
    uint32_t eraseLen = 0;
    BL_Err_Type ret = SUCCESS;

    if (startaddr > endaddr) {
        return ERROR;
    }

    while (startaddr <= endaddr) {
        len = endaddr - startaddr + 1;

        if (flashCfg->blk64EraseCmd != BFLB_SPIFLASH_CMD_INVALID &&
            (startaddr & (BFLB_SPIFLASH_BLK64K_SIZE - 1)) == 0 &&
            len > (BFLB_SPIFLASH_BLK64K_SIZE - flashCfg->sectorSize * 1024)) {
            /* 64K margin address,and length > 64K-sector size, erase one first */
            ret = SFlash_Blk64_Erase(flashCfg, startaddr / BFLB_SPIFLASH_BLK64K_SIZE);
            eraseLen = BFLB_SPIFLASH_BLK64K_SIZE;
        } else if (flashCfg->blk32EraseCmd != BFLB_SPIFLASH_CMD_INVALID &&
                   (startaddr & (BFLB_SPIFLASH_BLK32K_SIZE - 1)) == 0 &&
                   len > (BFLB_SPIFLASH_BLK32K_SIZE - flashCfg->sectorSize * 1024)) {
            /* 32K margin address,and length > 32K-sector size, erase one first */
            ret = SFlash_Blk32_Erase(flashCfg, startaddr / BFLB_SPIFLASH_BLK32K_SIZE);
            eraseLen = BFLB_SPIFLASH_BLK32K_SIZE;
        } else {
            /* Sector erase */
            startaddr = ((startaddr) & (~(flashCfg->sectorSize * 1024 - 1)));
            ret = SFlash_Sector_Erase(flashCfg, startaddr / flashCfg->sectorSize / 1024);
            eraseLen = flashCfg->sectorSize * 1024;
        }

        startaddr += eraseLen;

        if (ret != SUCCESS) {
            return ERROR;
        }
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash unique ID
 *
 * @param  data: data pointer to store read data
 * @param  idLen: unique ID len
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_GetUniqueId(uint8_t *data, uint8_t idLen)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd, dummyClks;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    dummyClks = 4;
    cmd = 0x4B;
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = idLen;

    SF_Ctrl_SendCmd(&flashCmd);

    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

    while (SET == SF_Ctrl_GetBusyState()) {
        timeOut--;

        if (timeOut == 0) {
            return;
        }
    }

    ARCH_MemCpy(data, flashCtrlBuf, idLen);
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash jedec ID
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  data: data pointer to store read data
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_GetJedecId(SPI_Flash_Cfg_Type *flashCfg, uint8_t *data)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd, dummyClks;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    dummyClks = flashCfg->jedecIdCmdDmyClk;
    cmd = flashCfg->jedecIdCmd;
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = 3;

    SF_Ctrl_SendCmd(&flashCmd);

    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

    while (SET == SF_Ctrl_GetBusyState()) {
        timeOut--;

        if (timeOut == 0) {
            return;
        }
    }

    ARCH_MemCpy(data, flashCtrlBuf, 3);
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash device ID
 *
 * @param  data: data pointer to store read data
 * @param  is32BitsAddr: Is flash addr mode in 32-bits
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_GetDeviceId(uint8_t *data, BL_Fun_Type is32BitsAddr)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd, dummyClks;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t addr = 0x00000001;
    uint8_t readMode = 0xFF;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.addrMode = SF_CTRL_ADDR_4_LINES;
    flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
    dummyClks = 2;
    cmd = 0x94;
    flashCmd.addrSize = 4;

    if (is32BitsAddr) {
        flashCmd.cmdBuf[0] = (cmd << 24) | (addr >> 8);
        flashCmd.cmdBuf[1] = (addr << 24) | (readMode << 16);
        flashCmd.addrSize++;
    } else {
        flashCmd.cmdBuf[0] = (cmd << 24) | (addr);
        flashCmd.cmdBuf[1] = (readMode << 24);
    }

    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = 2;

    SF_Ctrl_SendCmd(&flashCmd);

    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

    while (SET == SF_Ctrl_GetBusyState()) {
        timeOut--;

        if (timeOut == 0) {
            return;
        }
    }

    ARCH_MemCpy(data, flashCtrlBuf, 2);
}
#endif

/****************************************************************************/ /**
 * @brief  Set flash power down
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_Powerdown(void)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t cmd = 0;
    uint32_t timeOut = 0;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    cmd = 0xB9;
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_WRITE;

    SF_Ctrl_SendCmd(&flashCmd);

    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

    while (SET == SF_Ctrl_GetBusyState()) {
        timeOut--;

        if (timeOut == 0) {
            return;
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Release flash power down for wake up
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_Release_Powerdown(SPI_Flash_Cfg_Type *flashCfg)
{
    uint8_t cmd;
    uint32_t timeOut = 0;

    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    cmd = flashCfg->releasePowerDown;
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_WRITE;

    SF_Ctrl_SendCmd(&flashCmd);

    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

    while (SET == SF_Ctrl_GetBusyState()) {
        timeOut--;

        if (timeOut == 0) {
            return;
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Sflash restore from power down
 *
 * @param  pFlashCfg: Flash configuration pointer
 * @param  flashContRead: Whether enable continuous read
 * @param  bank: bank select type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Restore_From_Powerdown(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t flashContRead,
                                                           SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t jdecId = 0;
    uint8_t tmp[8];
    uint8_t ioMode = pFlashCfg->ioMode & 0xf;

    /* Wake flash up from power down */
    SFlash_Release_Powerdown(pFlashCfg);
    arch_delay_us(120);

    SFlash_GetJedecId(pFlashCfg, (uint8_t *)&jdecId);

    if (SF_CTRL_QO_MODE == ioMode || SF_CTRL_QIO_MODE == ioMode) {
        SFlash_Qspi_Enable(pFlashCfg);
    }

    if (((pFlashCfg->ioMode >> 4) & 0x01) == 1) {
        /* unwrap */
        L1C_Set_Wrap(DISABLE);
    } else {
        /* burst wrap */
        L1C_Set_Wrap(ENABLE);
        /* For command that is setting register instead of send command, we need write enable */
        SFlash_Write_Enable(pFlashCfg);
        SFlash_SetBurstWrap(pFlashCfg);
    }

    if (flashContRead) {
        stat = SFlash_Read(pFlashCfg, ioMode, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));
        stat = SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        stat = SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 0, 0, 32, bank);
    }

    return stat;
}
#endif

/****************************************************************************/ /**
 * @brief  Set flash burst wrap config
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_SetBurstWrap(SPI_Flash_Cfg_Type *flashCfg)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd, dummyClks;
    uint32_t wrapData;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((flashCfg->ioMode >> 4) & 0x01) == 1) {
        /* Disable burst wrap ,just return */
        return;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.addrMode = (SF_Ctrl_Addr_Mode_Type)flashCfg->burstWrapDataMode;
    flashCmd.dataMode = (SF_Ctrl_Data_Mode_Type)flashCfg->burstWrapDataMode;
    dummyClks = flashCfg->burstWrapCmdDmyClk;
    cmd = flashCfg->burstWrapCmd;
    wrapData = flashCfg->burstWrapData;
    ARCH_MemCpy4((uint32_t *)flashCtrlBuf, &wrapData, 4);
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = 1;

    SF_Ctrl_SendCmd(&flashCmd);
}
#endif

/****************************************************************************/ /**
 * @brief  Disable flash burst wrap config
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_DisableBurstWrap(SPI_Flash_Cfg_Type *flashCfg)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd, dummyClks;
    uint32_t wrapData;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.addrMode = (SF_Ctrl_Addr_Mode_Type)flashCfg->deBurstWrapDataMode;
    flashCmd.dataMode = (SF_Ctrl_Data_Mode_Type)flashCfg->deBurstWrapDataMode;
    dummyClks = flashCfg->deBurstWrapCmdDmyClk;
    cmd = flashCfg->deBurstWrapCmd;
    wrapData = flashCfg->deBurstWrapData;
    ARCH_MemCpy4((uint32_t *)flashCtrlBuf, &wrapData, 4);
    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = 1;

    SF_Ctrl_SendCmd(&flashCmd);
}
#endif

/****************************************************************************/ /**
 * @brief  Set flash 24-bits or 32-bits addr mode
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  en32BitsAddr: Serial flash enable or disable 32-bits addr
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Set32BitsAddrMode(SPI_Flash_Cfg_Type *flashCfg, BL_Fun_Type en32BitsAddr)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t cmd = 0;

    if ((flashCfg->ioMode & 0x20) == 0) {
        return ERROR;
    }

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    SF_Ctrl_32bits_Addr_En(en32BitsAddr);

    if (en32BitsAddr) {
        cmd = flashCfg->enter32BitsAddrCmd;
    } else {
        cmd = flashCfg->exit32BitsAddrCmd;
    }

    flashCmd.cmdBuf[0] = (cmd << 24);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;

    SF_Ctrl_SendCmd(&flashCmd);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Software reset flash
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Software_Reset(SPI_Flash_Cfg_Type *flashCfg)
{
    uint16_t cnt = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Reset enable */
    flashCmd.cmdBuf[0] = (flashCfg->resetEnCmd) << 24;
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;

    /* Wait for write done */
    while (SET == SFlash_Busy(flashCfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 20) {
            return ERROR;
        }
    }

    SF_Ctrl_SendCmd(&flashCmd);

    /* Reset */
    flashCmd.cmdBuf[0] = (flashCfg->resetCmd) << 24;
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    SF_Ctrl_SendCmd(&flashCmd);

    arch_delay_us(50);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Reset flash continous read mode
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_Reset_Continue_Read(SPI_Flash_Cfg_Type *flashCfg)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Reset continous read */
    ARCH_MemSet(&flashCmd.cmdBuf[0], flashCfg->resetCreadCmd, 4);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = flashCfg->resetCreadCmdSize;
    SF_Ctrl_SendCmd(&flashCmd);
}
#endif

/****************************************************************************/ /**
 * @brief  Set I/D bus read flash configuration in flash controller
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  ioMode: flash controller interface mode
 * @param  contRead: Wether enable cont read mode
 * @param  addr: address to read/write
 * @param  len: data length to read/write
 * @param  bank: bank select type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Set_IDbus_Cfg(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode, uint8_t contRead,
                                                  uint32_t addr, uint32_t len, SF_Ctrl_Bank_Select bank)
{
    uint8_t cmd, dummyClks;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t cmdValid = 1;
    uint8_t noReadModeCfg = 0;
    uint8_t cReadSupport = 0;
    uint8_t is32BitsAddr = 0;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    SF_Ctrl_Set_Owner(SF_CTRL_OWNER_IAHB);

    if (SF_CTRL_NIO_MODE == ioMode) {
        cmd = flashCfg->fastReadCmd;
        dummyClks = flashCfg->frDmyClk;
    } else if (SF_CTRL_DO_MODE == ioMode) {
        flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
        cmd = flashCfg->fastReadDoCmd;
        dummyClks = flashCfg->frDoDmyClk;
    } else if (SF_CTRL_DIO_MODE == ioMode) {
        flashCmd.addrMode = SF_CTRL_ADDR_2_LINES;
        flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
        cmd = flashCfg->fastReadDioCmd;
        dummyClks = flashCfg->frDioDmyClk;
    } else if (SF_CTRL_QO_MODE == ioMode) {
        flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
        cmd = flashCfg->fastReadQoCmd;
        dummyClks = flashCfg->frQoDmyClk;
    } else if (SF_CTRL_QIO_MODE == ioMode) {
        flashCmd.addrMode = SF_CTRL_ADDR_4_LINES;
        flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
        cmd = flashCfg->fastReadQioCmd;
        dummyClks = flashCfg->frQioDmyClk;
    } else {
        return ERROR;
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /*prepare command**/
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
        flashCmd.cmdBuf[0] = (cmd << 24) | (addr >> 8);
        flashCmd.cmdBuf[1] = (addr << 24);
    } else {
        flashCmd.cmdBuf[0] = (cmd << 24) | addr;
    }

    if (SF_CTRL_QIO_MODE == ioMode || SF_CTRL_DIO_MODE == ioMode) {
        noReadModeCfg = flashCfg->cReadSupport & 0x02;
        cReadSupport = flashCfg->cReadSupport & 0x01;

        if (noReadModeCfg == 0) {
            /* Read mode must be set*/
            if (cReadSupport == 0) {
                /* Not support cont read,but we still need set read mode(winbond 80dv)*/
                if (is32BitsAddr > 0) {
                    flashCmd.cmdBuf[1] |= (flashCfg->cReadMode << 16);
                } else {
                    flashCmd.cmdBuf[1] = (flashCfg->cReadMode << 24);
                }
            } else {
                /* Flash support cont read, setting depend on user parameter */
                if (contRead) {
                    if (is32BitsAddr > 0) {
                        flashCmd.cmdBuf[0] = addr;
                        flashCmd.cmdBuf[1] = (flashCfg->cReadMode << 24);
                    } else {
                        flashCmd.cmdBuf[0] = (addr << 8) | flashCfg->cReadMode;
                    }

                    cmdValid = 0;
                } else {
                    if (is32BitsAddr > 0) {
                        flashCmd.cmdBuf[1] |= ((!flashCfg->cReadMode) << 16);
                    } else {
                        flashCmd.cmdBuf[1] = ((!flashCfg->cReadMode) << 24);
                    }
                }
            }

            flashCmd.addrSize++;
        }
    }

    flashCmd.dummyClks = dummyClks;
    flashCmd.nbData = len;
    if (bank == SF_CTRL_FLASH_BANK0) {
        SF_Ctrl_Flash_Read_Icache_Set(&flashCmd, cmdValid);
    } else {
        SF_Ctrl_Flash2_Read_Icache_Set(&flashCmd, cmdValid);
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable I/D bus read from flash
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  ioMode: flash controller interface mode
 * @param  contRead: Wether enable cont read mode
 * @param  bank: bank select type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_IDbus_Read_Enable(SPI_Flash_Cfg_Type *flashCfg, SF_Ctrl_IO_Type ioMode,
                                                      uint8_t contRead, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;

    stat = SFlash_Set_IDbus_Cfg(flashCfg, ioMode, contRead, 0, 32, bank);

    if (SUCCESS != stat) {
        return stat;
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Disable read from flash with IDbus
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION SFlash_IDbus_Read_Disable(void)
{
    //L1C_Cache_Read_Disable();
}
#endif

/****************************************************************************/ /**
 * @brief  Sflash enable RCV mode to recovery for erase while power drop
 *
 * @param  pFlashCfg: Flash configuration pointer
 * @param  rCmd: Read RCV register cmd
 * @param  wCmd: Write RCV register cmd
 * @param  bitPos: RCV register bit pos
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_RCV_Enable(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t rCmd, uint8_t wCmd, uint8_t bitPos)
{
    BL_Err_Type stat;
    uint32_t cnt = 0;
    uint32_t tempVal = 0;

    while (SET == SFlash_Busy(pFlashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return ERROR;
        }
    }

    stat = SFlash_Read_Reg_With_Cmd(pFlashCfg, rCmd, (uint8_t *)&tempVal, 1);

    if (SUCCESS != stat) {
        stat = ERROR;
    }

    if (((tempVal >> bitPos) & 0x01) > 0) {
        return SUCCESS;
    }

    tempVal |= (uint32_t)(1 << bitPos);
    stat = SFlash_Write_Enable(pFlashCfg);

    if (SUCCESS != stat) {
        stat = ERROR;
    }

    stat = SFlash_Write_Reg_With_Cmd(pFlashCfg, wCmd, (uint8_t *)&tempVal, 1);

    if (SUCCESS != stat) {
        return stat;
    }

    while (SET == SFlash_Busy(pFlashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return ERROR;
        }
    }

    stat = SFlash_Read_Reg_With_Cmd(pFlashCfg, rCmd, (uint8_t *)&tempVal, 1);

    if (SUCCESS != stat) {
        stat = ERROR;
    }

    if (((tempVal >> bitPos) & 0x01) <= 0) {
        return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Erase flash security register one block
 *
 * @param  pFlashCfg: Flash configuration pointer
 * @param  pSecRegCfg: Security register configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_Erase_Security_Register(SPI_Flash_Cfg_Type *pFlashCfg, SFlash_Sec_Reg_Cfg *pSecRegCfg)
{
    uint32_t cnt = 0;
    uint8_t cmd = 0;
    uint8_t secOptMode = 0;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (pSecRegCfg->enterSecOptCmd != 0x00) {
        secOptMode = 1;

        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->enterSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    BL_Err_Type stat = SFlash_Write_Enable(pFlashCfg);

    if (stat != SUCCESS) {
        return stat;
    }

    if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        arch_memset(&flashCmd, 0, sizeof(flashCmd));
    }

    cmd = pSecRegCfg->eraseCmd;
    flashCmd.cmdBuf[0] = (cmd << 24) | (pSecRegCfg->blockNum << 12);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    SF_Ctrl_SendCmd(&flashCmd);

    while (SET == SFlash_Busy(pFlashCfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > pFlashCfg->timeEsector * 3) {
            return ERROR;
        }
    }

    if (secOptMode > 0) {
        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->exitSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Program flash security register one block
 *
 * @param  pFlashCfg: Flash configuration pointer
 * @param  pSecRegCfg: Security register configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_Program_Security_Register(SPI_Flash_Cfg_Type *pFlashCfg, SFlash_Sec_Reg_Cfg *pSecRegCfg)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t i = 0, curLen = 0;
    uint32_t cnt = 0;
    BL_Err_Type stat;
    uint8_t cmd;
    uint8_t secOptMode = 0;
    uint8_t *data = pSecRegCfg->data;
    uint32_t addr = pSecRegCfg->addr;
    uint32_t len = pSecRegCfg->len;
    uint32_t currentAddr = 0;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (pSecRegCfg->enterSecOptCmd != 0x00) {
        secOptMode = 1;

        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->enterSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        arch_memset(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Prepare command */
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.addrSize = 3;
    cmd = pSecRegCfg->programCmd;

    for (i = 0; i < len;) {
        /* Write enable is needed for every program */
        stat = SFlash_Write_Enable(pFlashCfg);

        if (stat != SUCCESS) {
            return stat;
        }

        /* Get current programmed length within page size */
        curLen = 256 - addr % 256;

        if (curLen > len - i) {
            curLen = len - i;
        }

        currentAddr = (pSecRegCfg->blockNum << 12) | addr;

        /* Prepare command */
        arch_memcpy_fast(flashCtrlBuf, data, curLen);
        flashCmd.cmdBuf[0] = (cmd << 24) | (currentAddr);
        flashCmd.nbData = curLen;

        SF_Ctrl_SendCmd(&flashCmd);

        /* Adjust address and programmed length */
        addr += curLen;
        i += curLen;
        data += curLen;

        /* Wait for write done */
        cnt = 0;

        while (SET == SFlash_Busy(pFlashCfg)) {
            arch_delay_us(100);
            cnt++;

            if (cnt > pFlashCfg->timePagePgm * 20) {
                return ERROR;
            }
        }
    }

    if (secOptMode > 0) {
        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->exitSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Read data from flash security register one block
 *
 * @param  pSecRegCfg: Security register configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION SFlash_Read_Security_Register(SFlash_Sec_Reg_Cfg *pSecRegCfg)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t curLen, i;
    uint8_t cmd;
    uint8_t secOptMode = 0;
    uint8_t *data = pSecRegCfg->data;
    uint32_t addr = pSecRegCfg->addr;
    uint32_t len = pSecRegCfg->len;
    uint32_t currentAddr = 0;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (pSecRegCfg->enterSecOptCmd != 0x00) {
        secOptMode = 1;

        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->enterSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        arch_memset(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Prepare command */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;
    flashCmd.dummyClks = 1;
    cmd = pSecRegCfg->readCmd;

    /* Read data */
    for (i = 0; i < len;) {
        currentAddr = (pSecRegCfg->blockNum << 12) | addr;
        /* Prepare command */
        flashCmd.cmdBuf[0] = (cmd << 24) | (currentAddr);
        curLen = len - i;

        if (curLen >= NOR_FLASH_CTRL_BUF_SIZE) {
            curLen = NOR_FLASH_CTRL_BUF_SIZE;
            flashCmd.nbData = curLen;
        } else {
            /* Make sf_ctrl word read */
            flashCmd.nbData = ((curLen + 3) >> 2) << 2;
        }

        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }

        arch_memcpy_fast(data, flashCtrlBuf, curLen);

        addr += curLen;
        i += curLen;
        data += curLen;
    }

    if (secOptMode > 0) {
        if (((uint32_t)(uintptr_t)&flashCmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
        } else {
            arch_memset(&flashCmd, 0, sizeof(flashCmd));
        }

        flashCmd.cmdBuf[0] = (pSecRegCfg->exitSecOptCmd << 24);
        flashCmd.rwFlag = SF_CTRL_WRITE;
        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Read data from flash
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  ioMode: flash controller interface mode
 * @param  contRead: Wether enable cont read mode
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Read(SPI_Flash_Cfg_Type *flashCfg,
                                         SF_Ctrl_IO_Type ioMode, uint8_t contRead, uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t curLen, i;
    uint8_t cmd, dummyClks;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t noReadModeCfg = 0;
    uint8_t cReadSupport = 0;
    uint8_t is32BitsAddr = 0;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    if (SF_CTRL_NIO_MODE == ioMode) {
        cmd = flashCfg->fastReadCmd;
        dummyClks = flashCfg->frDmyClk;
    } else if (SF_CTRL_DO_MODE == ioMode) {
        flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
        cmd = flashCfg->fastReadDoCmd;
        dummyClks = flashCfg->frDoDmyClk;
    } else if (SF_CTRL_DIO_MODE == ioMode) {
        flashCmd.addrMode = SF_CTRL_ADDR_2_LINES;
        flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
        cmd = flashCfg->fastReadDioCmd;
        dummyClks = flashCfg->frDioDmyClk;
    } else if (SF_CTRL_QO_MODE == ioMode) {
        flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
        cmd = flashCfg->fastReadQoCmd;
        dummyClks = flashCfg->frQoDmyClk;
    } else if (SF_CTRL_QIO_MODE == ioMode) {
        flashCmd.addrMode = SF_CTRL_ADDR_4_LINES;
        flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
        cmd = flashCfg->fastReadQioCmd;
        dummyClks = flashCfg->frQioDmyClk;
    } else {
        return ERROR;
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* Prepare command */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
    }

    if (SF_CTRL_QIO_MODE == ioMode || SF_CTRL_DIO_MODE == ioMode) {
        noReadModeCfg = flashCfg->cReadSupport & 0x02;
        cReadSupport = flashCfg->cReadSupport & 0x01;

        if (noReadModeCfg == 0) {
            /* Read mode must be set*/
            if (cReadSupport == 0) {
                /* Not support cont read,but we still need set read mode(winbond 80dv)*/
                if (is32BitsAddr > 0) {
                    flashCmd.cmdBuf[1] |= (flashCfg->cReadMode << 16);
                } else {
                    flashCmd.cmdBuf[1] = (flashCfg->cReadMode << 24);
                }
            } else {
                /* Flash support cont read, setting depend on user parameter */
                if (contRead) {
                    if (is32BitsAddr > 0) {
                        flashCmd.cmdBuf[1] |= (flashCfg->cReadMode << 16);
                    } else {
                        flashCmd.cmdBuf[1] = (flashCfg->cReadMode << 24);
                    }
                } else {
                    if (is32BitsAddr > 0) {
                        flashCmd.cmdBuf[1] |= ((!flashCfg->cReadMode) << 16);
                    } else {
                        flashCmd.cmdBuf[1] = ((!flashCfg->cReadMode) << 24);
                    }
                }
            }

            flashCmd.addrSize++;
        }
    }

    flashCmd.dummyClks = dummyClks;

    /* Read data */
    for (i = 0; i < len;) {
        /* Prepare command */
        if (is32BitsAddr > 0) {
            flashCmd.cmdBuf[0] = (cmd << 24) | (addr >> 8);
            flashCmd.cmdBuf[1] |= (addr << 24);
        } else {
            flashCmd.cmdBuf[0] = (cmd << 24) | (addr);
        }

        curLen = len - i;

        if (curLen >= NOR_FLASH_CTRL_BUF_SIZE) {
            curLen = NOR_FLASH_CTRL_BUF_SIZE;
            flashCmd.nbData = curLen;
        } else {
            /* Make sf_ctrl word read */
            flashCmd.nbData = ((curLen + 3) >> 2) << 2;
        }

        SF_Ctrl_SendCmd(&flashCmd);

        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == SF_Ctrl_GetBusyState()) {
            timeOut--;

            if (timeOut == 0) {
                return TIMEOUT;
            }
        }

        ARCH_MemCpy_Fast(data, flashCtrlBuf, curLen);

        addr += curLen;
        i += curLen;
        data += curLen;
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Program flash one region
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  ioMode: progran mode:SPI mode or QPI mode
 * @param  addr: start address to be programed
 * @param  data: data pointer to be programed
 * @param  len: data length to be programed
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION SFlash_Program(SPI_Flash_Cfg_Type *flashCfg,
                                            SF_Ctrl_IO_Type ioMode, uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t i = 0, curLen = 0;
    uint32_t cnt = 0;
    uint8_t is32BitsAddr = 0;
    BL_Err_Type stat;
    uint8_t cmd;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if (((uintptr_t)&flashCmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    } else {
        ARCH_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    if (SF_CTRL_NIO_MODE == ioMode || SF_CTRL_DO_MODE == ioMode || SF_CTRL_DIO_MODE == ioMode) {
        cmd = flashCfg->pageProgramCmd;
    } else if (SF_CTRL_QIO_MODE == ioMode || SF_CTRL_QO_MODE == ioMode) {
        flashCmd.addrMode = (SF_Ctrl_Addr_Mode_Type)flashCfg->qppAddrMode;
        flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
        cmd = flashCfg->qpageProgramCmd;
    } else {
        return ERROR;
    }

    is32BitsAddr = (flashCfg->ioMode & 0x20);
    /* Prepare command */
    flashCmd.rwFlag = SF_CTRL_WRITE;
    flashCmd.addrSize = 3;

    if (is32BitsAddr > 0) {
        flashCmd.addrSize++;
    }

    for (i = 0; i < len;) {
        /* Write enable is needed for every program */
        stat = SFlash_Write_Enable(flashCfg);

        if (stat != SUCCESS) {
            return stat;
        }

        /* Get current programmed length within page size */
        curLen = flashCfg->pageSize - addr % flashCfg->pageSize;

        if (curLen > len - i) {
            curLen = len - i;
        }

        /* Prepare command */
        ARCH_MemCpy_Fast(flashCtrlBuf, data, curLen);

        if (is32BitsAddr > 0) {
            flashCmd.cmdBuf[0] = (cmd << 24) | (addr >> 8);
            flashCmd.cmdBuf[1] = (addr << 24);
        } else {
            flashCmd.cmdBuf[0] = (cmd << 24) | (addr);
        }

        flashCmd.nbData = curLen;

        SF_Ctrl_SendCmd(&flashCmd);

        /* Adjust address and programmed length */
        addr += curLen;
        i += curLen;
        data += curLen;

        /* Wait for write done */
        cnt = 0;

        while (SET == SFlash_Busy(flashCfg)) {
            arch_delay_us(100);
            cnt++;

            if (cnt > flashCfg->timePagePgm * 20) {
                return ERROR;
            }
        }
    }

    return SUCCESS;
}
#endif

/*@} end of group SFLASH_Public_Functions */

/*@} end of group SFLASH */

/*@} end of group BL808_Peripheral_Driver */
