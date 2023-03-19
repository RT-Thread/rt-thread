/**
  ******************************************************************************
  * @file    bl602_xip_sflash_ext.c
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
#include "bflb_sf_cfg.h"
#include "bl602_sf_cfg_ext.h"
#include "bflb_xip_sflash.h"
#include "bl602_xip_sflash_ext.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  XIP_SFLASH_EXT
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

static spi_flash_cfg_type flash_cfg;
static uint8_t aes_enable;

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

/*@} end of group XIP_SFLASH_EXT_Private_Functions */

/** @defgroup  XIP_SFLASH_EXT_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Save flash controller state
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  offset: CPU XIP flash offset pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_state_save_ext(spi_flash_cfg_type *p_flash_cfg,uint32_t *offset,
                                                                         uint8_t group, uint8_t bank)
{
    /* XIP_SFlash_Delay */
    volatile uint32_t i=32*2;
    while(i--);
    
    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
    /* Exit form continous read for accepting command */
    bflb_sflash_reset_continue_read(p_flash_cfg);
    /* Send software reset command(80bv has no this command)to deburst wrap for ISSI like */
    bflb_sflash_software_reset(p_flash_cfg);
    /* For disable command that is setting register instaed of send command, we need write enable */
    bflb_sflash_disable_burst_wrap(p_flash_cfg);
    if ((p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QIO_MODE) {
        /* Enable QE again in case reset command make it reset */
        bflb_sflash_qspi_enable(p_flash_cfg);
    }
    /* Deburst again to make sure */
    bflb_sflash_disable_burst_wrap(p_flash_cfg);

    /* Clear offset setting*/
    *offset=bflb_sf_ctrl_get_flash_image_offset(group, bank);
    bflb_sf_ctrl_set_flash_image_offset(0, group, bank);

    return 0;
}

/****************************************************************************//**
 * @brief  Restore flash controller state
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  offset: CPU XIP flash offset
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_state_restore_ext(spi_flash_cfg_type *p_flash_cfg, uint32_t offset,
                                                                            uint8_t group, uint8_t bank)
{
    uint32_t tmp[1];
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    bflb_sf_ctrl_set_flash_image_offset(offset, group, bank);

    if (((p_flash_cfg->io_mode >> 4) & 0x01) == 0) {
        if ((p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QIO_MODE) {
            bflb_sflash_set_burst_wrap(p_flash_cfg);
        }
    }
    bflb_sflash_read(p_flash_cfg, io_mode, 1, 0x0, (uint8_t *)tmp, sizeof(tmp));
    bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);

    return 0;
}

/*@} end of group XIP_SFLASH_EXT_Public_Functions */

/** @defgroup  XIP_SFLASH_EXT_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  startaddr: start address to erase
 * @param  endaddr: end address(include this address) to erase
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_erase_need_lock_ext(spi_flash_cfg_type *p_flash_cfg, uint32_t startaddr,
                                                               uint32_t endaddr, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode&0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat=bflb_xip_sflash_state_save(p_flash_cfg,&offset,group,bank);
    if(stat!=0){
        bflb_sflash_set_xip_cfg(p_flash_cfg,io_mode,1,0,32,bank);
    }else{
        stat=bflb_sflash_erase(p_flash_cfg,startaddr,endaddr);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg,offset,group,bank);
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
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_write_need_lock_ext(spi_flash_cfg_type *p_flash_cfg, uint32_t addr,
                                               uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode&0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat=bflb_xip_sflash_state_save(p_flash_cfg,&offset,group,bank);
    if(stat!=0){
        bflb_sflash_set_xip_cfg(p_flash_cfg,io_mode,1,0,32,bank);
    }else{
        stat= bflb_sflash_program(p_flash_cfg,io_mode,addr,data,len);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg,offset,group,bank);
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
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_read_need_lock_ext(spi_flash_cfg_type *p_flash_cfg, uint32_t addr,
                                              uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode&0xf;

    bflb_xip_sflash_opt_enter(&aes_enable);
    stat=bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if(stat!=0){
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    }else{
        stat=bflb_sflash_read(p_flash_cfg, io_mode,0, addr, data, len);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, group, bank);
    }
    bflb_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************//**
 * @brief  Clear flash status register need lock
 *
 * @param  p_flash_cfg: Flash config pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_clear_status_register_need_lock(spi_flash_cfg_type *p_flash_cfg,
                                                                         uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode&0xf;

    stat=bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat=bflb_sflash_clear_status_register(p_flash_cfg);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset,  group, bank);
    }

    return stat;
}

/****************************************************************************//**
 * @brief  Get Flash Jedec ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Jedec ID Read from flash
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_getjedecid_need_lock_ext(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                                                 uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_jedecid(p_flash_cfg, data);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, group, bank);
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Get Flash Device ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Device ID Read from flash
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_get_deviceid_need_lock_ext(spi_flash_cfg_type *p_flash_cfg,
                             uint8_t is_32bits_addr, uint8_t *data, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_deviceid(data, is_32bits_addr);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, group, bank);
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Get Flash Unique ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Device ID Read from flash
 * @param  id_len: Unique id len
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_get_uniqueid_need_lock_ext(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                                uint8_t id_len, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        bflb_sflash_get_uniqueid(data, id_len);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, group, bank);
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Sflash enable RCV mode to recovery for erase while power drop need lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  r_cmd: Read RCV register cmd
 * @param  w_cmd: Write RCV register cmd
 * @param  bit_pos: RCV register bit pos
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_rcv_enable_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t r_cmd, uint8_t w_cmd,
                                                          uint8_t bit_pos, uint8_t group, uint8_t bank)
{
    int stat = -1;
    uint32_t offset;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    stat = bflb_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);
    if (stat != 0) {
        bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32 , bank);
    } else {
        stat = bflb_sflash_rcv_enable(p_flash_cfg, r_cmd, w_cmd, bit_pos);
        bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, group, bank);
    }

    return stat;
}

/****************************************************************************//**
 * @brief  Read data from flash with lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: flash read start address
 * @param  dst: data pointer to store data read from flash
 * @param  len: data length to read
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_read_with_lock_ext(spi_flash_cfg_type *p_flash_cfg,uint32_t addr, uint8_t *dst, int len)
{
    __disable_irq();
    bflb_xip_sflash_read_need_lock_ext(p_flash_cfg, addr, dst, len, 0, 0);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Program flash one region with lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: Start address to be programed
 * @param  src: Data pointer to be programed
 * @param  len: Data length to be programed
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_ip_sflash_write_with_lock_ext(spi_flash_cfg_type *p_flash_cfg,uint32_t addr, uint8_t *src, int len)
{
    __disable_irq();
    bflb_xip_sflash_write_need_lock_ext(p_flash_cfg, addr, src, len, 0, 0);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Erase flash one region with lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: Start address to be erased
 * @param  len: Data length to be erased
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_erase_with_lock_ext(spi_flash_cfg_type *p_flash_cfg,uint32_t addr, int len)
{
    __disable_irq();
    bflb_xip_sflash_erase_need_lock_ext(p_flash_cfg, addr, addr + len - 1, 0, 0);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Clear flash status register with lock
 *
 * @param  p_flash_cfg: Flash config pointer
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_clear_status_register_with_lock(spi_flash_cfg_type *p_flash_cfg)
{
    __disable_irq();
    bflb_xip_sflash_clear_status_register_need_lock(p_flash_cfg, 0, 0);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Sflash enable RCV mode to recovery for erase while power drop with lock
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  r_cmd: Read RCV register cmd
 * @param  w_cmd: Write RCV register cmd
 * @param  bit_pos: RCV register bit pos
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_rcv_enable_with_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t r_cmd, uint8_t w_cmd, uint8_t bit_pos)
{
    __disable_irq();
    bflb_xip_sflash_rcv_enable_need_lock(p_flash_cfg, r_cmd, w_cmd, bit_pos, 0, 0);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Read data from flash with lock
 *
 * @param  p_flash_cfg:Flash config pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_init(spi_flash_cfg_type *p_flash_cfg)
{
    uint32_t ret;

    if(p_flash_cfg==NULL){
        /* Get flash config identify */
        bflb_xip_sflash_opt_enter(&aes_enable);
        ret=bflb_sf_cfg_flash_identify_ext(1, 0x80, 0, &flash_cfg, 0, 0);
        bflb_xip_sflash_opt_exit(aes_enable);
        if((ret&BFLB_FLASH_ID_VALID_FLAG)==0){
            return -1;
        }
    }else{
        memcpy(&flash_cfg,p_flash_cfg,sizeof(flash_cfg));
    }
    
    return 0;
}

/****************************************************************************//**
 * @brief  Read data from flash with lock
 *
 * @param  addr: flash read start address
 * @param  dst: data pointer to store data read from flash
 * @param  len: data length to read
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_read(uint32_t addr, uint8_t *dst, int len)
{
    __disable_irq();
    bflb_xip_sflash_opt_enter(&aes_enable);
    bflb_xip_sflash_read_need_lock_ext(&flash_cfg, addr, dst, len, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enable);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Program flash one region with lock
 *
 * @param  addr: Start address to be programed
 * @param  src: Data pointer to be programed
 * @param  len: Data length to be programed
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_write(uint32_t addr, uint8_t *src, int len)
{
    __disable_irq();
    bflb_xip_sflash_opt_enter(&aes_enable);
    bflb_xip_sflash_write_need_lock_ext(&flash_cfg, addr, src, len, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enable);
    __enable_irq();
    return 0;
}

/****************************************************************************//**
 * @brief  Erase flash one region with lock
 *
 * @param  addr: Start address to be erased
 * @param  len: Data length to be erased
 *
 * @return 0
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_xip_sflash_erase(uint32_t addr, int len)
{
    __disable_irq();
    bflb_xip_sflash_opt_enter(&aes_enable);
    bflb_xip_sflash_erase_need_lock_ext(&flash_cfg, addr, addr + len - 1, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enable);
    __enable_irq();
    return 0;
}
/*@} end of group XIP_SFLASH_EXT_Public_Functions */

/*@} end of group XIP_SFLASH_EXT */

/*@} end of group BL602_Peripheral_Driver */
