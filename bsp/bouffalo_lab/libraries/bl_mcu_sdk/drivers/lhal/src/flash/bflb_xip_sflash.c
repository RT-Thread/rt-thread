/**
  ******************************************************************************
  * @file    bflb_xip_sflash.c
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

#include "bflb_common.h"
#include "bflb_xip_sflash.h"

/** @addtogroup  BL628_Peripheral_Driver
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
 * @param  p_flash_cfg: Flash config pointer
 * @param  offset: CPU XIP flash offset pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_state_save(spi_flash_cfg_type *p_flash_cfg, uint32_t *offset,
                                                    uint8_t group, uint8_t bank)
{
    /* XIP_SFlash_Delay */
    volatile uint32_t i = 32 * 2;

    while (i--)
        ;

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (bank == SF_CTRL_FLASH_BANK1) {
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
    }
#endif
    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
    /* Exit form continous read for accepting command */
    bflb_sflash_reset_continue_read(p_flash_cfg);
    /* For disable command that is setting register instaed of send command, we need write enable */
    bflb_sflash_disable_burst_wrap(p_flash_cfg);
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
    /* Enable 32Bits addr mode again in case reset command make it reset */
    bflb_sflash_set_32bits_addr_mode(p_flash_cfg, 1);
#endif
    if ((p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QIO_MODE) {
        /* Enable QE again in case reset command make it reset */
        bflb_sflash_qspi_enable(p_flash_cfg);
    }
    /* Deburst again to make sure */
    bflb_sflash_disable_burst_wrap(p_flash_cfg);

    /* Clear offset setting*/
    *offset = bflb_sf_ctrl_get_flash_image_offset(group, bank);
    bflb_sf_ctrl_set_flash_image_offset(0, group, bank);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Restore flash controller state
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  offset: CPU XIP flash offset
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_state_restore(spi_flash_cfg_type *p_flash_cfg, uint32_t offset,
                                                       uint8_t group, uint8_t bank)
{
    uint32_t tmp[1];
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_sf_ctrl_set_flash_image_offset(offset, group, bank);

    if(((p_flash_cfg->io_mode>>4)&0x01) == 0) {
        if((p_flash_cfg->io_mode&0x0f)==SF_CTRL_QO_MODE || (p_flash_cfg->io_mode&0x0f)==SF_CTRL_QIO_MODE) {
            bflb_sflash_set_burst_wrap(p_flash_cfg);
        }
    }
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
    bflb_sflash_set_32bits_addr_mode(p_flash_cfg, 1);
#endif
    bflb_sflash_read(p_flash_cfg, io_mode, 1, 0x0, (uint8_t *)tmp, sizeof(tmp));
    bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (bank == SF_CTRL_FLASH_BANK1) {
        bflb_sf_ctrl_sbus2_revoke_replace();
    }
#endif

    return 0;
}

/*@} end of group XIP_SFLASH_Private_Functions */

/** @defgroup  XIP_SFLASH_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  start_addr: start address to erase
 * @param  len: data length to erase
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_erase_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t start_addr,
                                                         int len, uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = bflb_sflash_erase(p_flash_cfg, start_addr, start_addr + len - 1);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Program flash one region
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: start address to be programed
 * @param  data: data pointer to be programed
 * @param  len: data length to be programed
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_write_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data,
                                                         uint32_t len, uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = bflb_sflash_program(p_flash_cfg, io_mode, addr, data, len);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Read data from flash
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_read_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data,
                                                        uint32_t len, uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = bflb_sflash_read(p_flash_cfg, io_mode, 0, addr, data, len);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Get Flash Jedec ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Jedec ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_get_jedecid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                               uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_jedecid(p_flash_cfg, data);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Get Flash Device ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  is_32bits_addr: Is flash addr mode in 32-bits
 * @param  data: data pointer to store Device ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_get_deviceid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t is_32bits_addr,
                                                                uint8_t *data, uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_deviceid(data, is_32bits_addr);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Get Flash Unique ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Device ID Read from flash
 * @param  id_len: Unique id len
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_get_uniqueid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                                uint8_t id_len, uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_uniqueid(data, id_len);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return 0;
}

/****************************************************************************//**
 * @brief  Clear flash status register need lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_clear_status_register_need_lock(spi_flash_cfg_type *p_flash_cfg,
                                                                     uint8_t group, uint8_t bank)
{
    int stat = 0;
    uint32_t offset = 0;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = bflb_sflash_clear_status_register(p_flash_cfg);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    bflb_xip_sflash_opt_exit(aes_enable);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Read data from flash via XIP
 *
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_read_via_cache_need_lock(uint32_t addr, uint8_t *data, uint32_t len,
                                                                  uint8_t group, uint8_t bank)
{
    uint32_t offset = 0;

    addr = addr & (BFLB_FLASH_XIP_END-BFLB_FLASH_XIP_BASE-1);
    addr |= BFLB_FLASH_XIP_BASE;

    offset = bflb_sf_ctrl_get_flash_image_offset(group, bank);
    bflb_sf_ctrl_set_flash_image_offset(0, group, bank);
    /* Flash read */
    arch_memcpy_fast(data, (void *)(uintptr_t)(addr - bflb_sf_ctrl_get_flash_image_offset(group, bank)), len);
    bflb_sf_ctrl_set_flash_image_offset(offset, group, bank);

    return 0;
}

/****************************************************************************/ /**
 * @brief  XIP SFlash option save
 *
 * @param  aes_enable: AES enable status pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_xip_sflash_opt_enter(uint8_t *aes_enable)
{
    *aes_enable = bflb_sf_ctrl_is_aes_enable();

    if (*aes_enable) {
        bflb_sf_ctrl_aes_disable();
    }
}

/****************************************************************************/ /**
 * @brief  XIP SFlash option restore
 *
 * @param  aes_enable: AES enable status
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_xip_sflash_opt_exit(uint8_t aes_enable)
{
    if (aes_enable) {
        bflb_sf_ctrl_aes_enable();
    }
}

/*@} end of group XIP_SFLASH_Public_Functions */

/*@} end of group XIP_SFLASH */

/*@} end of group BL628_Peripheral_Driver */
