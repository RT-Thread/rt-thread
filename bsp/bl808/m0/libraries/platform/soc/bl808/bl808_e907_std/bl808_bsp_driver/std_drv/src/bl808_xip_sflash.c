/**
  ******************************************************************************
  * @file    bl808_xip_sflash.c
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
#include "bl808_xip_sflash.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  XIP_SFLASH
 *  @{
 */

/** @defgroup  XIP_SFLASH_Private_Macros
 *  @{
 */

/*@} end of group XIP_SFLASH_Private_Macros */

/** @defgroup  XIP_SFLASH_Private_Types
 *  @{
 */

/*@} end of group XIP_SFLASH_Private_Types */

/** @defgroup  XIP_SFLASH_Private_Variables
 *  @{
 */

/*@} end of group XIP_SFLASH_Private_Variables */

/** @defgroup  XIP_SFLASH_Global_Variables
 *  @{
 */

/*@} end of group XIP_SFLASH_Global_Variables */

/** @defgroup  XIP_SFLASH_Private_Fun_Declaration
 *  @{
 */

/*@} end of group XIP_SFLASH_Private_Fun_Declaration */

/** @defgroup  XIP_SFLASH_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Save flash controller state
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  offset: CPU XIP flash offset pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_State_Save(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t *offset,
                                                   uint8_t group, SF_Ctrl_Bank_Select bank)
{
    /* XIP_SFlash_Delay */
    volatile uint32_t i = 32 * 2;

    while (i--)
        ;

    if (bank == SF_CTRL_FLASH_BANK1) {
        SF_Ctrl_Sbus2_Replace(SF_CTRL_PAD2);
    }
    SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
    /* Exit form continous read for accepting command */
    SFlash_Reset_Continue_Read(pFlashCfg);
    /* For disable command that is setting register instaed of send command, we need write enable */
    SFlash_DisableBurstWrap(pFlashCfg);
    /* Enable 32Bits addr mode again in case reset command make it reset */
    SFlash_Set32BitsAddrMode(pFlashCfg, ENABLE);
    if ((pFlashCfg->ioMode & 0x0f) == SF_CTRL_QO_MODE || (pFlashCfg->ioMode & 0x0f) == SF_CTRL_QIO_MODE) {
        /* Enable QE again in case reset command make it reset */
        SFlash_Qspi_Enable(pFlashCfg);
    }
    /* Deburst again to make sure */
    SFlash_DisableBurstWrap(pFlashCfg);

    /* Clear offset setting*/
    *offset = SF_Ctrl_Get_Flash_Image_Offset(group, bank);
    SF_Ctrl_Set_Flash_Image_Offset(0, group, bank);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Restore flash controller state
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  offset: CPU XIP flash offset
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_State_Restore(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t offset,
                                                      uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint32_t tmp[1];
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    SF_Ctrl_Set_Flash_Image_Offset(offset, group, bank);

    if(((pFlashCfg->ioMode>>4)&0x01) == 0) {
        if((pFlashCfg->ioMode&0x0f)==SF_CTRL_QO_MODE || (pFlashCfg->ioMode&0x0f)==SF_CTRL_QIO_MODE) {
            SFlash_SetBurstWrap(pFlashCfg);
        }
    }
    SFlash_Set32BitsAddrMode(pFlashCfg, ENABLE);
    SFlash_Read(pFlashCfg, ioMode, 1, 0x0, (uint8_t *)tmp, sizeof(tmp));
    SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    if (bank == SF_CTRL_FLASH_BANK1) {
        SF_Ctrl_Sbus2_Revoke_replace();
    }

    return SUCCESS;
}
#endif

/*@} end of group XIP_SFLASH_Private_Functions */

/** @defgroup  XIP_SFLASH_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  startaddr: start address to erase
 * @param  len: data length to erase
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_Erase_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t startaddr, int len,
                                                        uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        stat = SFlash_Erase(pFlashCfg, startaddr, startaddr + len - 1);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return stat;
}
#endif

/****************************************************************************/ /**
 * @brief  Program flash one region
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  addr: start address to be programed
 * @param  data: data pointer to be programed
 * @param  len: data length to be programed
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_Write_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t addr, uint8_t *data, uint32_t len,
                                                        uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        stat = SFlash_Program(pFlashCfg, ioMode, addr, data, len);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return stat;
}
#endif

/****************************************************************************/ /**
 * @brief  Read data from flash
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_Read_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint32_t addr, uint8_t *data, uint32_t len,
                                                       uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        stat = SFlash_Read(pFlashCfg, ioMode, 0, addr, data, len);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return stat;
}
#endif

/****************************************************************************/ /**
 * @brief  Get Flash Jedec ID
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  data: data pointer to store Jedec ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_GetJedecId_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t *data,
                                                             uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        SFlash_GetJedecId(pFlashCfg, data);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Get Flash Device ID
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  is32BitsAddr: Is flash addr mode in 32-bits
 * @param  data: data pointer to store Device ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_GetDeviceId_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, BL_Fun_Type is32BitsAddr, uint8_t *data,
                                                              uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        SFlash_GetDeviceId(data, is32BitsAddr);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Get Flash Unique ID
 *
 * @param  pFlashCfg: Flash config pointer
 * @param  data: data pointer to store Device ID Read from flash
 * @param  idLen: Unique id len
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_GetUniqueId_Need_Lock(SPI_Flash_Cfg_Type *pFlashCfg, uint8_t *data, uint8_t idLen,
                                                              uint8_t group, SF_Ctrl_Bank_Select bank)
{
    BL_Err_Type stat;
    uint32_t offset;
    uint8_t aesEnable = 0;
    SF_Ctrl_IO_Type ioMode = (SF_Ctrl_IO_Type)pFlashCfg->ioMode & 0xf;

    XIP_SFlash_Opt_Enter(&aesEnable);
    stat = XIP_SFlash_State_Save(pFlashCfg, &offset, group, bank);

    if (stat != SUCCESS) {
        SFlash_Set_IDbus_Cfg(pFlashCfg, ioMode, 1, 0, 32, bank);
    } else {
        SFlash_GetUniqueId(data, idLen);
        XIP_SFlash_State_Restore(pFlashCfg, offset, group, bank);
    }

    XIP_SFlash_Opt_Exit(aesEnable);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Read data from flash via XIP
 *
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION XIP_SFlash_Read_Via_Cache_Need_Lock(uint32_t addr, uint8_t *data, uint32_t len,
                                                                 uint8_t group, SF_Ctrl_Bank_Select bank)
{
    uint32_t offset;

    addr = addr & (BL808_FLASH_XIP_END-BL808_FLASH_XIP_BASE-1);
    addr |= BL808_FLASH_XIP_BASE;

    offset = SF_Ctrl_Get_Flash_Image_Offset(group, bank);
    SF_Ctrl_Set_Flash_Image_Offset(0, group, bank);
    /* Flash read */
    ARCH_MemCpy_Fast(data, (void *)(uintptr_t)(addr), len);
    SF_Ctrl_Set_Flash_Image_Offset(offset, group, bank);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  XIP SFlash option save
 *
 * @param  aesEnable: AES enable status pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION XIP_SFlash_Opt_Enter(uint8_t *aesEnable)
{
    *aesEnable = SF_Ctrl_Is_AES_Enable();

    if (*aesEnable) {
        SF_Ctrl_AES_Disable();
    }
}

/****************************************************************************/ /**
 * @brief  XIP SFlash option restore
 *
 * @param  aesEnable: AES enable status
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION XIP_SFlash_Opt_Exit(uint8_t aesEnable)
{
    if (aesEnable) {
        SF_Ctrl_AES_Enable();
    }
}

/*@} end of group XIP_SFLASH_Public_Functions */

/*@} end of group XIP_SFLASH */

/*@} end of group BL808_Peripheral_Driver */
