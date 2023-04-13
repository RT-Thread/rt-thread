/**
  ******************************************************************************
  * @file    bflb_sflash.c
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
#include "bflb_sf_ctrl.h"
#include "bflb_sflash.h"
//#include "bl628_l1c.h"

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SFLASH
 *  @{
 */

/** @defgroup  SFLASH_Private_Macros
 *  @{
 */

#if defined(BL602) || defined(BL702)
#define BFLB_SF_CTRL_BUF_BASE    ((uint32_t)0x4000B700)
#elif defined(BL702L)
#define BFLB_SF_CTRL_BUF_BASE    ((uint32_t)0x4000B600)
#elif defined(BL606P) || defined(BL808) || defined(BL616)
#define BFLB_SF_CTRL_BUF_BASE    ((uint32_t)0x2000b600)
#elif defined(BL628)
#define BFLB_SF_CTRL_BUF_BASE    ((uint32_t)0x20082600)
#endif

/*@} end of group SFLASH_Private_Macros */

/** @defgroup  SFLASH_Private_Types
 *  @{
 */

/*@} end of group SFLASH_Private_Types */

/** @defgroup  SFLASH_Private_Variables
 *  @{
 */

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
 * @param  p_sf_ctrl_cfg: Serial flash controller configuration pointer
 * @param  p_bank2_cfg: Serial flash2 controller configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
void ATTR_TCM_SECTION bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg,
                                       const struct sf_ctrl_bank2_cfg *p_bank2_cfg)
{
    uint8_t clk_delay = 0;
    uint8_t rx_clk_invert = 0;

    if (p_bank2_cfg != NULL) {
        if (p_bank2_cfg->sbus2_select) {
            if (p_bank2_cfg->bank2_delay_src) {
                clk_delay = p_bank2_cfg->bank2_clk_delay;
            } else {
                if (p_sf_ctrl_cfg != NULL) {
                    clk_delay = p_sf_ctrl_cfg->clk_delay;
                } else {
                    clk_delay = 1;
                }
            }

            if (p_bank2_cfg->bank2_rx_clk_invert_src) {
                rx_clk_invert = p_bank2_cfg->bank2_rx_clk_invert_sel;
            } else {
                if (p_sf_ctrl_cfg != NULL) {
                    rx_clk_invert = p_sf_ctrl_cfg->rx_clk_invert;
                } else {
                    rx_clk_invert = 0;
                }
            }

            bflb_sf_ctrl_sbus2_set_delay(clk_delay, rx_clk_invert);
        } else {
            bflb_sf_ctrl_sbus2_revoke_replace();
        }

        bflb_sf_ctrl_bank2_enable(p_bank2_cfg);
    } else {
        bflb_sf_ctrl_sbus2_revoke_replace();
    }
#else
void ATTR_TCM_SECTION bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg)
{
#endif

    if (p_sf_ctrl_cfg != NULL) {
        bflb_sf_ctrl_enable(p_sf_ctrl_cfg);
    }
}

/****************************************************************************/ /**
 * @brief  Set serial flash control interface SPI or QPI mode
 *
 * @param  mode: Serial flash interface mode
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_set_spi_mode(uint8_t mode)
{
    int stat = 0;

    return stat;
}

/****************************************************************************/ /**
 * @brief  Read flash register
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  reg_index: register index
 * @param  reg_value: register value pointer to store data
 * @param  reg_len: register value length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_read_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index,
                                              uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t cnt = 0;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.cmd_buf[0] = (flash_cfg->read_reg_cmd[reg_index]) << 24;
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sf_ctrl_get_busy_state()) {
        arch_delay_us(1);
        cnt++;

        if (cnt > 1000) {
            return -1;
        }
    }

    arch_memcpy(reg_value, flash_ctrl_buf, reg_len);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Write flash register
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  reg_index: register index
 * @param  reg_value: register value pointer storing data
 * @param  reg_len: register value length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_write_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index,
                                               uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t cnt = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    arch_memcpy(flash_ctrl_buf, reg_value, reg_len);

    flash_cmd.cmd_buf[0] = (flash_cfg->write_reg_cmd[reg_index]) << 24;
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    /* take 40ms for tw(write status register) as default */
    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 400) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Read flash register with read command
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  read_reg_cmd: read command
 * @param  reg_value: register value pointer to store data
 * @param  reg_len: register value length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg,
                           uint8_t read_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t cnt = 0;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.cmd_buf[0] = read_reg_cmd << 24;
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sf_ctrl_get_busy_state()) {
        arch_delay_us(1);
        cnt++;

        if (cnt > 1000) {
            return -1;
        }
    }

    arch_memcpy(reg_value, flash_ctrl_buf, reg_len);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Write flash register with write command
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  write_reg_cmd: write command
 * @param  reg_value: register value pointer storing data
 * @param  reg_len: register value length
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg,
                           uint8_t write_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t cnt = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    arch_memcpy(flash_ctrl_buf, reg_value, reg_len);

    flash_cmd.cmd_buf[0] = write_reg_cmd << 24;
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.nb_data = reg_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    /* take 40ms for tw(write status register) as default */
    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 400) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Check flash busy status
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return 1 means busy or 0 means not busy
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_busy(spi_flash_cfg_type *flash_cfg)
{
    uint32_t stat = 0;
    bflb_sflash_read_reg(flash_cfg, flash_cfg->busy_index, (uint8_t *)&stat, flash_cfg->busy_read_reg_len);

    if ((stat & (1 << flash_cfg->busy_bit)) == 0) {
        return 0;
    }

    return 1;
}

/****************************************************************************/ /**
 * @brief  Enable flash write function
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_write_enable(spi_flash_cfg_type *flash_cfg)
{
    uint32_t stat = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Write enable*/
    flash_cmd.cmd_buf[0] = (flash_cfg->write_enable_cmd) << 24;
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    bflb_sf_ctrl_sendcmd(&flash_cmd);

    bflb_sflash_read_reg(flash_cfg, flash_cfg->wr_enable_index, (uint8_t *)&stat, flash_cfg->wr_enable_read_reg_len);

    if ((stat & (1 << flash_cfg->wr_enable_bit)) != 0) {
        return 0;
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Enable flash flash controller QSPI interface
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_qspi_enable(spi_flash_cfg_type *flash_cfg)
{
    uint32_t stat = 0, ret = 0;

    if (flash_cfg->qe_read_reg_len == 0) {
        ret = bflb_sflash_write_enable(flash_cfg);

        if (0 != ret) {
            return -1;
        }

        bflb_sflash_write_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_write_reg_len);
        return 0;
    }

    bflb_sflash_read_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_read_reg_len);

    if (flash_cfg->qe_data == 0) {
        if ((stat & (1 << flash_cfg->qe_bit)) != 0) {
            return 0;
        }
    } else {
        if (((stat >> (flash_cfg->qe_bit & 0x08)) & 0xff) == flash_cfg->qe_data) {
            return 0;
        }
    }

    if (flash_cfg->qe_write_reg_len != 1) {
        /* This is  read r0,read r1 write r0,r1 case*/
        bflb_sflash_read_reg(flash_cfg, 0, (uint8_t *)&stat, 1);
        bflb_sflash_read_reg(flash_cfg, 1, ((uint8_t *)&stat) + 1, 1);

        if (flash_cfg->qe_data == 0) {
            stat |= (1 << (flash_cfg->qe_bit + 8 * flash_cfg->qe_index));
        } else {
            stat = stat & (~(0xff << (8 * flash_cfg->qe_index)));
            stat |= (flash_cfg->qe_data << (8 * flash_cfg->qe_index));
        }
    } else {
        if (flash_cfg->qe_data == 0) {
            stat |= (1 << (flash_cfg->qe_bit % 8));
        } else {
            stat = flash_cfg->qe_data;
        }
    }

    ret = bflb_sflash_write_enable(flash_cfg);

    if (0 != ret) {
        return -1;
    }

    bflb_sflash_write_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_write_reg_len);
    bflb_sflash_read_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_read_reg_len);

    if (flash_cfg->qe_data == 0) {
        if ((stat & (1 << flash_cfg->qe_bit)) != 0) {
            return 0;
        }
    } else {
        if (((stat >> (flash_cfg->qe_bit & 0x08)) & 0xff) == flash_cfg->qe_data) {
            return 0;
        }
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Disable flash flash controller QSPI interface
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_qspi_disable(spi_flash_cfg_type *flash_cfg)
{
    uint32_t stat = 0, ret = 0;

    if (flash_cfg->qe_read_reg_len == 0) {
        ret = bflb_sflash_write_enable(flash_cfg);

        if (0 != ret) {
            return -1;
        }

        bflb_sflash_write_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_write_reg_len);
        return 0;
    }

    bflb_sflash_read_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_read_reg_len);

    if ((stat & (1 << flash_cfg->qe_bit)) == 0) {
        return 0;
    }

    if (flash_cfg->qe_write_reg_len != 1) {
        /* This is  read r0,read r1 write r0,r1 case*/
        bflb_sflash_read_reg(flash_cfg, 0, (uint8_t *)&stat, 1);
        bflb_sflash_read_reg(flash_cfg, 1, ((uint8_t *)&stat) + 1, 1);
        stat &= (~(1 << (flash_cfg->qe_bit + 8 * flash_cfg->qe_index)));
    } else {
        stat &= (~(1 << (flash_cfg->qe_bit % 8)));
    }

    ret = bflb_sflash_write_enable(flash_cfg);

    if (0 != ret) {
        return -1;
    }

    bflb_sflash_write_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_write_reg_len);
    bflb_sflash_read_reg(flash_cfg, flash_cfg->qe_index, (uint8_t *)&stat, flash_cfg->qe_read_reg_len);

    if ((stat & (1 << flash_cfg->qe_bit)) == 0) {
        return 0;
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Enable flash volatile register write enable
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_volatile_reg_write_enable(spi_flash_cfg_type *flash_cfg)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.cmd_buf[0] = (flash_cfg->write_vreg_enable_cmd) << 24;
    flash_cmd.rw_flag = SF_CTRL_WRITE;

    bflb_sf_ctrl_sendcmd(&flash_cmd);
}

/****************************************************************************/ /**
 * @brief  Erase flash whole chip
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_chip_erase(spi_flash_cfg_type *flash_cfg)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t cnt = 0;
    uint32_t timeout = 0;
    int stat = bflb_sflash_write_enable(flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.cmd_buf[0] = (flash_cfg->chip_erase_cmd) << 24;
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = flash_cfg->time_ce;

    if ((timeout >> 15) > 0) {
        timeout = (timeout & 0x7FFF) * 1000;
    }

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > timeout * 3) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one sector
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  sector_num: flash sector number
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_sector_erase(spi_flash_cfg_type *flash_cfg, uint32_t sector_num)
{
    uint32_t cnt = 0;
    uint8_t is_32bits_addr = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    int stat = bflb_sflash_write_enable(flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
        flash_cmd.cmd_buf[0] = (flash_cfg->sector_erase_cmd << 24) | ((flash_cfg->sector_size * 1024 * sector_num) >> 8);
        flash_cmd.cmd_buf[1] = ((flash_cfg->sector_size * 1024 * sector_num) << 24);
    } else {
        flash_cmd.cmd_buf[0] = (flash_cfg->sector_erase_cmd << 24) | (flash_cfg->sector_size * 1024 * sector_num);
    }

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flash_cfg->time_e_sector * 3) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one 32K block
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  blk_num: flash 32K block number
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_blk32_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num)
{
    uint32_t cnt = 0;
    uint8_t is_32bits_addr = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    int stat = bflb_sflash_write_enable(flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
        flash_cmd.cmd_buf[0] = (flash_cfg->blk32_erase_cmd << 24) | ((BFLB_SPIFLASH_BLK32K_SIZE * blk_num) >> 8);
        flash_cmd.cmd_buf[1] = ((BFLB_SPIFLASH_BLK32K_SIZE * blk_num) << 24);
    } else {
        flash_cmd.cmd_buf[0] = (flash_cfg->blk32_erase_cmd << 24) | (BFLB_SPIFLASH_BLK32K_SIZE * blk_num);
    }

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flash_cfg->time_e_32k * 3) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one 64K block
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  blk_num: flash 64K block number
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_blk64_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t cnt = 0;
    uint8_t is_32bits_addr = 0;
    int stat = bflb_sflash_write_enable(flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
        flash_cmd.cmd_buf[0] = (flash_cfg->blk64_erase_cmd << 24) | ((BFLB_SPIFLASH_BLK64K_SIZE * blk_num) >> 8);
        flash_cmd.cmd_buf[1] = ((BFLB_SPIFLASH_BLK64K_SIZE * blk_num) << 24);
    } else {
        flash_cmd.cmd_buf[0] = (flash_cfg->blk64_erase_cmd << 24) | (BFLB_SPIFLASH_BLK64K_SIZE * blk_num);
    }

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flash_cfg->time_e_64k * 3) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  start_addr: start address to erase
 * @param  end_addr: end address(include this address) to erase
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_erase(spi_flash_cfg_type *flash_cfg, uint32_t start_addr, uint32_t end_addr)
{
    uint32_t len = 0;
    uint32_t erase_len = 0;
    uint8_t ret = 0;

    if (start_addr > end_addr) {
        return -1;
    }

    while (start_addr <= end_addr) {
        len = end_addr - start_addr + 1;

        if (flash_cfg->blk64_erase_cmd != BFLB_SPIFLASH_CMD_INVALID &&
            (start_addr & (BFLB_SPIFLASH_BLK64K_SIZE - 1)) == 0 &&
            len > (BFLB_SPIFLASH_BLK64K_SIZE - flash_cfg->sector_size * 1024)) {
            /* 64K margin address,and length > 64K-sector size, erase one first */
            ret = bflb_sflash_blk64_erase(flash_cfg, start_addr / BFLB_SPIFLASH_BLK64K_SIZE);
            erase_len = BFLB_SPIFLASH_BLK64K_SIZE;
        } else if (flash_cfg->blk32_erase_cmd != BFLB_SPIFLASH_CMD_INVALID &&
                   (start_addr & (BFLB_SPIFLASH_BLK32K_SIZE - 1)) == 0 &&
                   len > (BFLB_SPIFLASH_BLK32K_SIZE - flash_cfg->sector_size * 1024)) {
            /* 32K margin address,and length > 32K-sector size, erase one first */
            ret = bflb_sflash_blk32_erase(flash_cfg, start_addr / BFLB_SPIFLASH_BLK32K_SIZE);
            erase_len = BFLB_SPIFLASH_BLK32K_SIZE;
        } else {
            /* Sector erase */
            start_addr = ((start_addr) & (~(flash_cfg->sector_size * 1024 - 1)));
            ret = bflb_sflash_sector_erase(flash_cfg, start_addr / flash_cfg->sector_size / 1024);
            erase_len = flash_cfg->sector_size * 1024;
        }

        start_addr += erase_len;

        if (ret != 0) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Get flash unique ID
 *
 * @param  data: data pointer to store read data
 * @param  id_len: unique ID len
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_get_uniqueid(uint8_t *data, uint8_t id_len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    dummy_clks = 4;
    cmd = 0x4B;
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = id_len;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }

    arch_memcpy(data, flash_ctrl_buf, id_len);
}

/****************************************************************************/ /**
 * @brief  Get flash jedec ID
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  data: data pointer to store read data
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_get_jedecid(spi_flash_cfg_type *flash_cfg, uint8_t *data)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    dummy_clks = flash_cfg->jedec_id_cmd_dmy_clk;
    cmd = flash_cfg->jedec_id_cmd;
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = 3;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }

    arch_memcpy(data, flash_ctrl_buf, 3);
}

/****************************************************************************/ /**
 * @brief  Get flash device ID
 *
 * @param  data: data pointer to store read data
 * @param  is_32bits_addr: Is flash addr mode in 32-bits
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_get_deviceid(uint8_t *data, uint8_t is_32bits_addr)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint32_t addr = 0x00000001;
    uint8_t read_mode = 0xFF;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
    flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
    dummy_clks = 2;
    cmd = 0x94;
    flash_cmd.addr_size = 4;

    if (is_32bits_addr) {
        flash_cmd.cmd_buf[0] = (cmd << 24) | (addr >> 8);
        flash_cmd.cmd_buf[1] = (addr << 24) | (read_mode << 16);
        flash_cmd.addr_size++;
    } else {
        flash_cmd.cmd_buf[0] = (cmd << 24) | (addr);
        flash_cmd.cmd_buf[1] = (read_mode << 24);
    }

    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = 2;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }

    arch_memcpy(data, flash_ctrl_buf, 2);
}

/****************************************************************************/ /**
 * @brief  Set flash power down
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_powerdown(void)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint8_t cmd = 0;
    uint32_t timeout = 0;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    cmd = 0xB9;
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_WRITE;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Release flash power down for wake up
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_release_powerdown(spi_flash_cfg_type *flash_cfg)
{
    uint8_t cmd = 0;
    uint32_t timeout = 0;

    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    cmd = flash_cfg->release_powerdown;
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_WRITE;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Sflash restore from power down
 *
 * @param  flash_cfg: Flash configuration pointer
 * @param  flash_cont_read: Whether enable continuous read
 * @param  bank: bank select type
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *flash_cfg,
                                                    uint8_t flash_cont_read, uint8_t bank)
{
    int stat = 0;
    uint32_t jedecid = 0;
    uint8_t tmp[8];
    uint8_t io_mode = flash_cfg->io_mode & 0xf;

    /* Wake flash up from power down */
    bflb_sflash_release_powerdown(flash_cfg);
    arch_delay_us(120);

    bflb_sflash_get_jedecid(flash_cfg, (uint8_t *)&jedecid);

    if (SF_CTRL_QO_MODE == io_mode || SF_CTRL_QIO_MODE == io_mode) {
        bflb_sflash_qspi_enable(flash_cfg);
    }

    if (((flash_cfg->io_mode >> 4) & 0x01) == 1) {
        /* unwrap */
        //L1C_Set_Wrap(0);
    } else {
        /* burst wrap */
        //L1C_Set_Wrap(1);
        /* For command that is setting register instead of send command, we need write enable */
        bflb_sflash_write_enable(flash_cfg);
        bflb_sflash_set_burst_wrap(flash_cfg);
    }

    if (flash_cont_read) {
        stat = bflb_sflash_read(flash_cfg, io_mode, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));
        stat = bflb_sflash_set_xip_cfg(flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = bflb_sflash_set_xip_cfg(flash_cfg, io_mode, 0, 0, 32, bank);
    }

    return stat;
}

/****************************************************************************/ /**
 * @brief  Set flash burst wrap config
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_set_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t wrap_data = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((flash_cfg->io_mode >> 4) & 0x01) == 1) {
        /* Disable burst wrap ,just return */
        return;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.addr_mode = flash_cfg->burst_wrap_data_mode;
    flash_cmd.data_mode = flash_cfg->burst_wrap_data_mode;
    dummy_clks = flash_cfg->burst_wrap_cmd_dmy_clk;
    cmd = flash_cfg->burst_wrap_cmd;
    wrap_data = flash_cfg->burst_wrap_data;
    arch_memcpy4((uint32_t *)flash_ctrl_buf, &wrap_data, 4);
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = 1;

    bflb_sf_ctrl_sendcmd(&flash_cmd);
}

/****************************************************************************/ /**
 * @brief  Disable flash burst wrap config
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_disable_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t wrap_data = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    flash_cmd.addr_mode = flash_cfg->de_burst_wrap_data_mode;
    flash_cmd.data_mode = flash_cfg->de_burst_wrap_data_mode;
    dummy_clks = flash_cfg->de_burst_wrap_cmd_dmy_clk;
    cmd = flash_cfg->de_burst_wrap_cmd;
    wrap_data = flash_cfg->de_burst_wrap_data;
    arch_memcpy4((uint32_t *)flash_ctrl_buf, &wrap_data, 4);
    flash_cmd.cmd_buf[0] = (cmd << 24);
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = 1;

    bflb_sf_ctrl_sendcmd(&flash_cmd);
}

#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
/****************************************************************************/ /**
 * @brief  Set flash 24-bits or 32-bits addr mode
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  en_32bits_addr: Serial flash enable or disable 32-bits addr
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_set_32bits_addr_mode(spi_flash_cfg_type *flash_cfg,
                                                          uint8_t en_32bits_addr)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint8_t cmd = 0;

    if ((flash_cfg->io_mode & 0x20) == 0) {
        return -1;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    bflb_sf_ctrl_32bits_addr_en(en_32bits_addr);

    if (en_32bits_addr) {
        cmd = flash_cfg->enter_32bits_addr_cmd;
    } else {
        cmd = flash_cfg->exit_32bits_addr_cmd;
    }

    flash_cmd.cmd_buf[0] = (cmd << 24);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    return 0;
}
#endif

/****************************************************************************/ /**
 * @brief  Software reset flash
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_software_reset(spi_flash_cfg_type *flash_cfg)
{
    uint16_t cnt = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Reset enable */
    flash_cmd.cmd_buf[0] = (flash_cfg->reset_en_cmd) << 24;
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;

    /* Wait for write done */
    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(100);
        cnt++;

        if (cnt > 20) {
            return -1;
        }
    }

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    /* Reset */
    flash_cmd.cmd_buf[0] = (flash_cfg->reset_cmd) << 24;
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    bflb_sf_ctrl_sendcmd(&flash_cmd);

    arch_delay_us(50);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Reset flash continous read mode
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_reset_continue_read(spi_flash_cfg_type *flash_cfg)
{
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Reset continous read */
    arch_memset(&flash_cmd.cmd_buf[0], flash_cfg->reset_c_read_cmd, 4);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = flash_cfg->reset_c_read_cmd_size;
    bflb_sf_ctrl_sendcmd(&flash_cmd);
}

/****************************************************************************/ /**
 * @brief  Set xip read flash configuration in flash controller
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  io_mode: flash controller interface mode
 * @param  cont_read: Wether enable cont read mode
 * @param  addr: address to read/write
 * @param  len: data length to read/write
 * @param  bank: bank select type
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_set_xip_cfg(spi_flash_cfg_type *flash_cfg, uint8_t io_mode,
                                     uint8_t cont_read, uint32_t addr, uint32_t len, uint8_t bank)
{
    uint8_t cmd = 0, dummy_clks = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint8_t cmd_valid = 1;
    uint8_t no_read_mode_cfg = 0;
    uint8_t c_read_support = 0;
    uint8_t is_32bits_addr = 0;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_IAHB);

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = flash_cfg->fast_read_cmd;
        dummy_clks = flash_cfg->fr_dmy_clk;
    } else if (SF_CTRL_DO_MODE == io_mode) {
        flash_cmd.data_mode = SF_CTRL_DATA_2_LINES;
        cmd = flash_cfg->fast_read_do_cmd;
        dummy_clks = flash_cfg->fr_do_dmy_clk;
    } else if (SF_CTRL_DIO_MODE == io_mode) {
        flash_cmd.addr_mode = SF_CTRL_ADDR_2_LINES;
        flash_cmd.data_mode = SF_CTRL_DATA_2_LINES;
        cmd = flash_cfg->fast_read_dio_cmd;
        dummy_clks = flash_cfg->fr_dio_dmy_clk;
    } else if (SF_CTRL_QO_MODE == io_mode) {
        flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = flash_cfg->fast_read_qo_cmd;
        dummy_clks = flash_cfg->fr_qo_dmy_clk;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        flash_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = flash_cfg->fast_read_qio_cmd;
        dummy_clks = flash_cfg->fr_qio_dmy_clk;
    } else {
        return -1;
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /*prepare command**/
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
        flash_cmd.cmd_buf[0] = (cmd << 24) | (addr >> 8);
        flash_cmd.cmd_buf[1] = (addr << 24);
    } else {
        flash_cmd.cmd_buf[0] = (cmd << 24) | addr;
    }

    if (SF_CTRL_QIO_MODE == io_mode || SF_CTRL_DIO_MODE == io_mode) {
        no_read_mode_cfg = flash_cfg->c_read_support & 0x02;
        c_read_support = flash_cfg->c_read_support & 0x01;

        if (no_read_mode_cfg == 0) {
            /* Read mode must be set*/
            if (c_read_support == 0) {
                /* Not support cont read,but we still need set read mode(winbond 80dv)*/
                if (is_32bits_addr > 0) {
                    flash_cmd.cmd_buf[1] |= (flash_cfg->c_read_mode << 16);
                } else {
                    flash_cmd.cmd_buf[1] = (flash_cfg->c_read_mode << 24);
                }
            } else {
                /* Flash support cont read, setting depend on user parameter */
                if (cont_read) {
                    if (is_32bits_addr > 0) {
                        flash_cmd.cmd_buf[0] = addr;
                        flash_cmd.cmd_buf[1] = (flash_cfg->c_read_mode << 24);
                    } else {
                        flash_cmd.cmd_buf[0] = (addr << 8) | flash_cfg->c_read_mode;
                    }

                    cmd_valid = 0;
                } else {
                    if (is_32bits_addr > 0) {
                        flash_cmd.cmd_buf[1] |= ((!flash_cfg->c_read_mode) << 16);
                    } else {
                        flash_cmd.cmd_buf[1] = ((!flash_cfg->c_read_mode) << 24);
                    }
                }
            }

            flash_cmd.addr_size++;
        }
    }

    flash_cmd.dummy_clks = dummy_clks;
    flash_cmd.nb_data = len;
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (bank == SF_CTRL_FLASH_BANK0) {
        bflb_sf_ctrl_xip_set(&flash_cmd, cmd_valid);
    } else {
        bflb_sf_ctrl_xip2_set(&flash_cmd, cmd_valid);
    }
#else
    bflb_sf_ctrl_xip_set(&flash_cmd, cmd_valid);
#endif

    return 0;
}

/****************************************************************************/ /**
 * @brief  Enable xip read from flash
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  io_mode: flash controller interface mode
 * @param  cont_read: Wether enable cont read mode
 * @param  bank: bank select type
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_xip_read_enable(spi_flash_cfg_type *flash_cfg,
                                    uint8_t io_mode, uint8_t cont_read, uint8_t bank)
{
    int stat = 0;

    stat = bflb_sflash_set_xip_cfg(flash_cfg, io_mode, cont_read, 0, 32, bank);
    if (0 != stat) {
        return stat;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Disable read from flash with xip
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sflash_xip_read_disable(void)
{

}

/****************************************************************************/ /**
 * @brief  Sflash enable RCV mode to recovery for erase while power drop
 *
 * @param  flash_cfg: Flash configuration pointer
 * @param  r_cmd: Read RCV register cmd
 * @param  w_cmd: Write RCV register cmd
 * @param  bit_pos: RCV register bit pos
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_rcv_enable(spi_flash_cfg_type *flash_cfg, uint8_t r_cmd,
                                                uint8_t w_cmd, uint8_t bit_pos)
{
    int stat = 0;
    uint32_t cnt = 0;
    uint32_t temp_val = 0;

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return -1;
        }
    }

    stat = bflb_sflash_read_reg_with_cmd(flash_cfg, r_cmd, (uint8_t *)&temp_val, 1);
    if (0 != stat) {
        stat = -1;
    }

    if (((temp_val >> bit_pos) & 0x01) > 0) {
        return 0;
    }

    temp_val |= (uint32_t)(1 << bit_pos);
    stat = bflb_sflash_write_enable(flash_cfg);
    if (0 != stat) {
        stat = -1;
    }

    stat = bflb_sflash_write_reg_with_cmd(flash_cfg, w_cmd, (uint8_t *)&temp_val, 1);
    if (0 != stat) {
        return stat;
    }

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return -1;
        }
    }

    stat = bflb_sflash_read_reg_with_cmd(flash_cfg, r_cmd, (uint8_t *)&temp_val, 1);
    if (0 != stat) {
        stat = -1;
    }

    if (((temp_val >> bit_pos) & 0x01) <= 0) {
        return -1;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash security register one block
 *
 * @param  flash_cfg: Flash configuration pointer
 * @param  p_sec_reg_cfg: Security register configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_erase_security_register(spi_flash_cfg_type *flash_cfg,
                                                  struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    int stat = 0;
    uint32_t cnt = 0;
    uint8_t cmd = 0;
    uint8_t sec_opt_mode = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    stat = bflb_sflash_write_enable(flash_cfg);
    if (stat != 0) {
        return stat;
    }

    if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    cmd = p_sec_reg_cfg->erase_cmd;
    flash_cmd.cmd_buf[0] = (cmd << 24) | (p_sec_reg_cfg->block_num << 12);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (bflb_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flash_cfg->time_e_sector * 3) {
            return -1;
        }
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Program flash security register one block
 *
 * @param  flash_cfg: Flash configuration pointer
 * @param  p_sec_reg_cfg: Security register configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_program_security_register(spi_flash_cfg_type *flash_cfg,
                                                    struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t i = 0, cur_len = 0;
    uint32_t cnt = 0;
    int stat = 0;
    uint8_t cmd = 0;
    uint8_t sec_opt_mode = 0;
    uint8_t *data = p_sec_reg_cfg->data;
    uint32_t addr = p_sec_reg_cfg->addr;
    uint32_t len = p_sec_reg_cfg->len;
    uint32_t current_addr = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Prepare command */
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.addr_size = 3;
    cmd = p_sec_reg_cfg->program_cmd;

    for (i = 0; i < len;) {
        /* Write enable is needed for every program */
        stat = bflb_sflash_write_enable(flash_cfg);

        if (stat != 0) {
            return stat;
        }

        /* Get current programmed length within page size */
        cur_len = 256 - addr % 256;

        if (cur_len > len - i) {
            cur_len = len - i;
        }

        current_addr = (p_sec_reg_cfg->block_num << 12) | addr;

        /* Prepare command */
        arch_memcpy_fast(flash_ctrl_buf, data, cur_len);
        flash_cmd.cmd_buf[0] = (cmd << 24) | (current_addr);
        flash_cmd.nb_data = cur_len;

        bflb_sf_ctrl_sendcmd(&flash_cmd);

        /* Adjust address and programmed length */
        addr += cur_len;
        i += cur_len;
        data += cur_len;

        /* Wait for write done */
        cnt = 0;

        while (bflb_sflash_busy(flash_cfg)) {
            arch_delay_us(100);
            cnt++;

            if (cnt > flash_cfg->time_page_pgm * 20) {
                return -1;
            }
        }
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Read data from flash security register one block
 *
 * @param  p_sec_reg_cfg: Security register configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_read_security_register(struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t cur_len = 0, i = 0;
    uint8_t cmd = 0;
    uint8_t sec_opt_mode = 0;
    uint8_t *data = p_sec_reg_cfg->data;
    uint32_t addr = p_sec_reg_cfg->addr;
    uint32_t len = p_sec_reg_cfg->len;
    uint32_t current_addr = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Prepare command */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;
    flash_cmd.dummy_clks = 1;
    cmd = p_sec_reg_cfg->read_cmd;

    /* Read data */
    for (i = 0; i < len;) {
        current_addr = (p_sec_reg_cfg->block_num << 12) | addr;
        /* Prepare command */
        flash_cmd.cmd_buf[0] = (cmd << 24) | (current_addr);
        cur_len = len - i;

        if (cur_len >= NOR_FLASH_CTRL_BUF_SIZE) {
            cur_len = NOR_FLASH_CTRL_BUF_SIZE;
            flash_cmd.nb_data = cur_len;
        } else {
            /* Make sf_ctrl word read */
            flash_cmd.nb_data = ((cur_len + 3) >> 2) << 2;
        }

        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }

        arch_memcpy_fast(data, flash_ctrl_buf, cur_len);

        addr += cur_len;
        i += cur_len;
        data += cur_len;
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)(uintptr_t)&flash_cmd) % 4 == 0) {
            arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }
    }

    return 0;
}

/****************************************************************************//**
 * @brief  Clear flash status register
 *
 * @param  flash_cfg: Flash configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_clear_status_register(spi_flash_cfg_type *flash_cfg)
{
    uint32_t ret = 0;
    uint32_t qe_value = 0;
    uint32_t reg_value = 0;
    uint32_t read_value = 0;
    uint8_t read_reg_value0 = 0;
    uint8_t read_reg_value1 = 0;

    if ((flash_cfg->io_mode&0xf)==SF_CTRL_QO_MODE || (flash_cfg->io_mode&0xf)==SF_CTRL_QIO_MODE) {
        qe_value = 1;
    }

    bflb_sflash_read_reg(flash_cfg, 0, (uint8_t *)&read_reg_value0, 1);
    bflb_sflash_read_reg(flash_cfg, 1, (uint8_t *)&read_reg_value1, 1);
    read_value = (read_reg_value0|(read_reg_value1<<8));
    if ((read_value & (~((1<<(flash_cfg->qe_index*8+flash_cfg->qe_bit)) |
                         (1<<(flash_cfg->busy_index*8+flash_cfg->busy_bit)) |
                         (1<<(flash_cfg->wr_enable_index*8+flash_cfg->wr_enable_bit))))) == 0) {
        return 0;
    }

    ret = bflb_sflash_write_enable(flash_cfg);
    if (0 != ret) {
        return ret;
    }
    if (flash_cfg->qe_write_reg_len == 2) {
        reg_value = (qe_value<<(flash_cfg->qe_index*8+flash_cfg->qe_bit));
        bflb_sflash_write_reg(flash_cfg, 0, (uint8_t *)&reg_value, 2);
    } else {
        if (flash_cfg->qe_index == 0) {
            reg_value = (qe_value<<flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        bflb_sflash_write_reg(flash_cfg, 0, (uint8_t *)&reg_value, 1);
        ret = bflb_sflash_write_enable(flash_cfg);
        if (0 != ret) {
            return ret;
        }
        if (flash_cfg->qe_index == 1) {
            reg_value = (qe_value<<flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        bflb_sflash_write_reg(flash_cfg, 1, (uint8_t *)&reg_value, 1);
    }
    return 0;
}

/****************************************************************************/ /**
 * @brief  Read data from flash
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  io_mode: flash controller interface mode
 * @param  cont_read: Wether enable cont read mode
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_read(spi_flash_cfg_type *flash_cfg, uint8_t io_mode,
                           uint8_t cont_read, uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t cur_len = 0, i = 0;
    uint8_t cmd = 0, dummy_clks = 0;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    uint8_t no_read_mode_cfg = 0;
    uint8_t c_read_support = 0;
    uint8_t is_32bits_addr = 0;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = flash_cfg->fast_read_cmd;
        dummy_clks = flash_cfg->fr_dmy_clk;
    } else if (SF_CTRL_DO_MODE == io_mode) {
        flash_cmd.data_mode = SF_CTRL_DATA_2_LINES;
        cmd = flash_cfg->fast_read_do_cmd;
        dummy_clks = flash_cfg->fr_do_dmy_clk;
    } else if (SF_CTRL_DIO_MODE == io_mode) {
        flash_cmd.addr_mode = SF_CTRL_ADDR_2_LINES;
        flash_cmd.data_mode = SF_CTRL_DATA_2_LINES;
        cmd = flash_cfg->fast_read_dio_cmd;
        dummy_clks = flash_cfg->fr_dio_dmy_clk;
    } else if (SF_CTRL_QO_MODE == io_mode) {
        flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = flash_cfg->fast_read_qo_cmd;
        dummy_clks = flash_cfg->fr_qo_dmy_clk;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        flash_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = flash_cfg->fast_read_qio_cmd;
        dummy_clks = flash_cfg->fr_qio_dmy_clk;
    } else {
        return -1;
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* Prepare command */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
    }

    if (SF_CTRL_QIO_MODE == io_mode || SF_CTRL_DIO_MODE == io_mode) {
        no_read_mode_cfg = flash_cfg->c_read_support & 0x02;
        c_read_support = flash_cfg->c_read_support & 0x01;

        if (no_read_mode_cfg == 0) {
            /* Read mode must be set*/
            if (c_read_support == 0) {
                /* Not support cont read,but we still need set read mode(winbond 80dv)*/
                if (is_32bits_addr > 0) {
                    flash_cmd.cmd_buf[1] |= (flash_cfg->c_read_mode << 16);
                } else {
                    flash_cmd.cmd_buf[1] = (flash_cfg->c_read_mode << 24);
                }
            } else {
                /* Flash support cont read, setting depend on user parameter */
                if (cont_read) {
                    if (is_32bits_addr > 0) {
                        flash_cmd.cmd_buf[1] |= (flash_cfg->c_read_mode << 16);
                    } else {
                        flash_cmd.cmd_buf[1] = (flash_cfg->c_read_mode << 24);
                    }
                } else {
                    if (is_32bits_addr > 0) {
                        flash_cmd.cmd_buf[1] |= ((!flash_cfg->c_read_mode) << 16);
                    } else {
                        flash_cmd.cmd_buf[1] = ((!flash_cfg->c_read_mode) << 24);
                    }
                }
            }

            flash_cmd.addr_size++;
        }
    }

    flash_cmd.dummy_clks = dummy_clks;

    /* Read data */
    for (i = 0; i < len;) {
        /* Prepare command */
        if (is_32bits_addr > 0) {
            flash_cmd.cmd_buf[0] = (cmd << 24) | (addr >> 8);
            flash_cmd.cmd_buf[1] |= (addr << 24);
        } else {
            flash_cmd.cmd_buf[0] = (cmd << 24) | (addr);
        }

        cur_len = len - i;

        if (cur_len >= NOR_FLASH_CTRL_BUF_SIZE) {
            cur_len = NOR_FLASH_CTRL_BUF_SIZE;
            flash_cmd.nb_data = cur_len;
        } else {
            /* Make sf_ctrl word read */
            flash_cmd.nb_data = ((cur_len + 3) >> 2) << 2;
        }

        bflb_sf_ctrl_sendcmd(&flash_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;

        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }

        arch_memcpy_fast(data, flash_ctrl_buf, cur_len);

        addr += cur_len;
        i += cur_len;
        data += cur_len;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Program flash one region
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  io_mode: progran mode:SPI mode or QPI mode
 * @param  addr: start address to be programed
 * @param  data: data pointer to be programed
 * @param  len: data length to be programed
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_program(spi_flash_cfg_type *flash_cfg, uint8_t io_mode,
                                                 uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BUF_BASE;
    uint32_t i = 0, cur_len = 0;
    uint32_t cnt = 0;
    int stat = 0;
    uint8_t is_32bits_addr = 0;
    uint8_t cmd = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        arch_memset(&flash_cmd, 0, sizeof(flash_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode || SF_CTRL_DO_MODE == io_mode || SF_CTRL_DIO_MODE == io_mode) {
        cmd = flash_cfg->page_program_cmd;
    } else if (SF_CTRL_QIO_MODE == io_mode || SF_CTRL_QO_MODE == io_mode) {
        flash_cmd.addr_mode = flash_cfg->qpp_addr_mode;
        flash_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = flash_cfg->qpage_program_cmd;
    } else {
        return -1;
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* Prepare command */
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
    }

    for (i = 0; i < len;) {
        /* Write enable is needed for every program */
        stat = bflb_sflash_write_enable(flash_cfg);

        if (stat != 0) {
            return stat;
        }

        /* Get current programmed length within page size */
        cur_len = flash_cfg->page_size - addr % flash_cfg->page_size;

        if (cur_len > len - i) {
            cur_len = len - i;
        }

        /* Prepare command */
        arch_memcpy_fast(flash_ctrl_buf, data, cur_len);

        if (is_32bits_addr > 0) {
            flash_cmd.cmd_buf[0] = (cmd << 24) | (addr >> 8);
            flash_cmd.cmd_buf[1] = (addr << 24);
        } else {
            flash_cmd.cmd_buf[0] = (cmd << 24) | (addr);
        }

        flash_cmd.nb_data = cur_len;

        bflb_sf_ctrl_sendcmd(&flash_cmd);

        /* Adjust address and programmed length */
        addr += cur_len;
        i += cur_len;
        data += cur_len;

        /* Wait for write done */
        cnt = 0;

        while (bflb_sflash_busy(flash_cfg)) {
            arch_delay_us(100);
            cnt++;

            if (cnt > flash_cfg->time_page_pgm * 20) {
                return -1;
            }
        }
    }

    return 0;
}

/*@} end of group SFLASH_Public_Functions */

/*@} end of group SFLASH */

/*@} end of group BL628_Peripheral_Driver */
