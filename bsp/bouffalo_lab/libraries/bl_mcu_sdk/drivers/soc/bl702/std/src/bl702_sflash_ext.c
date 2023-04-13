/**
  ******************************************************************************
  * @file    bl702_sflash_ext.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>
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

#include "bflb_sf_ctrl.h"
#include "bl702_sflash_ext.h"
#include "l1c_reg.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLASH_EXT
 *  @{
 */

/** @defgroup  SFLASH_EXT_Private_Macros
 *  @{
 */

/*@} end of group SFLASH_EXT_Private_Macros */

/** @defgroup  SFLASH_EXT_Private_Types
 *  @{
 */

/*@} end of group SFLASH_EXT_Private_Types */

/** @defgroup  SFLASH_EXT_Private_Variables
 *  @{
 */

/*@} end of group SFLASH_EXT_Private_Variables */

/** @defgroup  SFLASH_EXT_Global_Variables
 *  @{
 */

/*@} end of group SFLASH_EXT_Global_Variables */

/** @defgroup  SFLASH_EXT_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SFLASH_EXT_Private_Fun_Declaration */

/** @defgroup  SFLASH_EXT_Private_Functions
 *  @{
 */

/*@} end of group SFLASH_EXT_Private_Functions */

/** @defgroup  SFLASH_EXT_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  KH25V40 flash write protect set
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  protect: protect area
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_kh25v40_write_protect(spi_flash_cfg_type *flash_cfg, uint8_t protect)
{
    uint32_t stat = 0, ret;

    bflb_sflash_read_reg(flash_cfg, 0, (uint8_t *)&stat, 1);
    if (((stat >> 2) & 0xf) == protect) {
        return 0;
    }

    stat |= ((protect << 2) & 0xff);

    ret = bflb_sflash_write_enable(flash_cfg);
    if (0 != ret) {
        return -1;
    }

    bflb_sflash_write_reg(flash_cfg, 0, (uint8_t *)&stat, 1);
    bflb_sflash_read_reg(flash_cfg, 0, (uint8_t *)&stat, 1);
    if (((stat >> 2) & 0xf) == protect) {
        return 0;
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Read flash register with read command
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  read_reg_cmd: read command
 * @param  reg_value: register value pointer to store data
 * @param  reg_len: register value length
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)SF_CTRL_BUF_BASE;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t cnt = 0;

    if (((uint32_t)&flash_cmd) % 4 == 0) {
        BL702_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        BL702_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.cmd_buf[0] = read_reg_cmd << 24;
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (SET == bflb_sf_ctrl_get_busy_state()) {
        BL702_Delay_US(1);
        cnt++;

        if (cnt > 1000) {
            return -1;
        }
    }

    BL702_MemCpy(reg_value, flash_ctrl_buf, reg_len);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Write flash register with write command
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  read_reg_cmd: write command
 * @param  reg_value: register value pointer storing data
 * @param  reg_len: register value length
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t cnt = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uint32_t)&flash_cmd) % 4 == 0) {
        BL702_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        BL702_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
    }

    BL702_MemCpy(flash_ctrl_buf, reg_value, reg_len);

    flash_cmd.cmd_buf[0] = read_reg_cmd << 24;
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    /* take 40ms for tw(write status register) as default */
    while (SET == bflb_sflash_busy(flash_cfg)) {
        BL702_Delay_US(100);
        cnt++;

        if (cnt > 400) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************//**
 * @brief  Clear flash status register
 *
 * @param  p_flash_cfg: Flash configuration pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_clear_status_register(spi_flash_cfg_type *p_flash_cfg)
{
    uint32_t ret = 0;
    uint32_t qe_value = 0;
    uint32_t reg_value = 0;
    uint32_t read_value = 0;
    uint8_t readreg_value0 = 0;
    uint8_t readreg_value1 = 0;

    if((p_flash_cfg->io_mode&0xf)==SF_CTRL_QO_MODE || (p_flash_cfg->io_mode&0xf)==SF_CTRL_QIO_MODE){
        qe_value = 1;
    }

    bflb_sflash_read_reg(p_flash_cfg, 0, (uint8_t *)&readreg_value0, 1);
    bflb_sflash_read_reg(p_flash_cfg, 1, (uint8_t *)&readreg_value1, 1);
    read_value = (readreg_value0|(readreg_value1<<8));
    if ((read_value & (~((1<<(p_flash_cfg->qe_index*8+p_flash_cfg->qe_bit)) |
                        (1<<(p_flash_cfg->busy_index*8+p_flash_cfg->busy_bit)) |
                        (1<<(p_flash_cfg->wr_enable_index*8+p_flash_cfg->wr_enable_bit))))) == 0){
        return 0;
    }

    ret = bflb_sflash_write_enable(p_flash_cfg);
    if (0 != ret) {
        return -1;
    }
    if (p_flash_cfg->qe_write_reg_len == 2) {
        reg_value = (qe_value<<(p_flash_cfg->qe_index*8+p_flash_cfg->qe_bit));
        bflb_sflash_write_reg(p_flash_cfg, 0, (uint8_t *)&reg_value, 2);
    } else {
        if (p_flash_cfg->qe_index == 0) {
            reg_value = (qe_value<<p_flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        bflb_sflash_write_reg(p_flash_cfg, 0, (uint8_t *)&reg_value, 1);
        ret = bflb_sflash_write_enable(p_flash_cfg);
        if (0 != ret) {
            return -1;
        }
        if (p_flash_cfg->qe_index == 1) {
            reg_value = (qe_value<<p_flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        bflb_sflash_write_reg(p_flash_cfg, 1, (uint8_t *)&reg_value, 1);
    }
    return 0;
}

/*@} end of group SFLASH_EXT_Public_Functions */

/*@} end of group SFLASH_EXT */

/*@} end of group BL702_Peripheral_Driver */
