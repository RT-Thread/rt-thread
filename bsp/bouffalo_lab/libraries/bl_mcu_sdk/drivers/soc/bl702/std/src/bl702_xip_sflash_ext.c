/**
  ******************************************************************************
  * @file    bl702_xip_sflash_ext.c
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

#include "bl702_xip_sflash_ext.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  XIP_SFLASH
 *  @{
 */

/** @defgroup  XIP_SFLASH_EXT_Private_Macros
 *  @{
 */

/*@} end of group XIP_SFLASH_EXT_Private_Macros */

/** @defgroup  XIP_SFLASH_EXT_Private_Types
 *  @{
 */

/*@} end of group XIP_SFLASH_EXT_Private_Types */

/** @defgroup  XIP_SFLASH_EXT_Private_Variables
 *  @{
 */

/*@} end of group XIP_SFLASH_EXT_Private_Variables */

/** @defgroup  XIP_SFLASH_EXT_Global_Variables
 *  @{
 */

/*@} end of group XIP_SFLASH_EXT_Global_Variables */

/** @defgroup  XIP_SFLASH_EXT_Private_Fun_Declaration
 *  @{
 */

/*@} end of group XIP_SFLASH_EXT_Private_Fun_Declaration */

/** @defgroup  XIP_SFLASH_EXT_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  XIP SFlash option save
 *
 * @param  aes_enable: AES enable status pointer
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION bflb_xip_sflash_opt_enter(uint8_t *aes_enable)
{
    *aes_enable = bflb_sf_ctrl_is_aes_enable();

    if (*aes_enable) {
        bflb_sf_ctrl_aes_disable();
    }
}

/****************************************************************************//**
 * @brief  XIP SFlash option restore
 *
 * @param  aes_enable: AES enable status
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION bflb_xip_sflash_opt_exit(uint8_t aes_enable)
{
    if (aes_enable) {
        bflb_sf_ctrl_aes_enable();
    }
}

/****************************************************************************//**
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
int ATTR_TCM_SECTION bflb_xip_sflash_read_via_cache_need_lock(uint32_t addr,uint8_t *data, uint32_t len,
                                                              uint8_t group, uint8_t bank)
{
    uint32_t offset;

    if(addr>=BL702_FLASH_XIP_BASE && addr<BL702_FLASH_XIP_END){
        offset=bflb_sf_ctrl_get_flash_image_offset(group, bank);
        bflb_sf_ctrl_set_flash_image_offset(0, group, bank);
        /* Flash read */
        BL702_MemCpy_Fast(data,(void *)(addr-bflb_sf_ctrl_get_flash_image_offset(group, bank)),len);
        bflb_sf_ctrl_set_flash_image_offset(offset, group, bank);
    }

    return 0;
}


/****************************************************************************//**
 * @brief  XIP KH25V40 flash write protect set
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  protect: protect area
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_xip_sflash_kh25v40_write_protect_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t protect)
{
    int stat = -1;
    uint32_t offset;

    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, 0, 0);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, 1, 0, 32, 0, 0);
    } else {
        stat = bflb_sflash_kh25v40_write_protect(p_flash_cfg, protect);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, 0, 0);
    }

    return stat;
}

/****************************************************************************//**
 * @brief  Clear flash status register need lock
 *
 * @param  p_flash_cfg: Flash config pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_xip_sflash_clear_status_register_need_lock(spi_flash_cfg_type *p_flash_cfg,
                                                                     uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;

    stat=bflb_xip_sflash_state_save(p_flash_cfg, &offset, 0, 0);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, 1, 0, 32, 0, 0);
    } else {
        stat=bflb_sflash_clear_status_register(p_flash_cfg);
        bflb_xip_sflash_state_restore(p_flash_cfg, offset, 0, 0);
    }

    return stat;
}

/*@} end of group XIP_SFLASH_EXT_Public_Functions */

/*@} end of group XIP_SFLASH_EXT */

/*@} end of group BL702_Peripheral_Driver */
