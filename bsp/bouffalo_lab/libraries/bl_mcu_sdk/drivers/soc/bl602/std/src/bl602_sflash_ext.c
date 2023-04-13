/**
  ******************************************************************************
  * @file    bl602_sflash_ext.c
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

#include "bl602_l1c.h"
#include "bl602_sflash_ext.h"
#include "bflb_sf_ctrl.h"
#include "l1c_reg.h"

/** @addtogroup  BL602_Peripheral_Driver
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
#define SFCTRL_BUSY_STATE_TIMEOUT (5 * 160 * 1000)

#define SFLASH_L1C_BASE_ADDR      (0x40009000)
#define SFLASH_L1C_CONFIG_OFFSET  (0x0)
#define SFLASH_L1C_CACHEABLE      (1<<0U)
#define SFLASH_L1C_CNT_EN         (1<<1U)
#define SFLASH_L1C_INVALID_EN     (1<<2U)
#define SFLASH_L1C_INVALID_DONE   (1<<3U)
#define SFLASH_L1C_WAY_DIS_SHIFT  (8U)
#define SFLASH_L1C_WAY_DIS_MASK   (0xf<<SFLASH_L1C_WAY_DIS_SHIFT)
#define SFLASH_L1C_BYPASS         (1<<14U)
#define SFLASH_L1C_EARLY_RESP_DIS (1<<25U)
#define SFLASH_L1C_WRAP_DIS       (1<<26U)

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
 * @brief  Sflash restore from power down
 *
 * @param  p_flash_cfg: Flash configuration pointer
 * @param  flash_cont_read: Whether enable continuous read
 *
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *p_flash_cfg,
                                                  uint8_t flash_cont_read, uint8_t bank)
{
    int stat = -1;
    uint32_t jedec_id = 0;
    uint8_t tmp[8];
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    /* Wake flash up from power down */
    bflb_sflash_release_powerdown(p_flash_cfg);
    BL602_Delay_US(120);

    bflb_sflash_get_jedecid(p_flash_cfg, (uint8_t *)&jedec_id);

    if (SF_CTRL_QO_MODE == io_mode || SF_CTRL_QIO_MODE == io_mode) {
        bflb_sflash_qspi_enable(p_flash_cfg);
    }

    if (((p_flash_cfg->io_mode >> 4) & 0x01) == 1) {
        /* unwrap */
        L1C_Set_Wrap(DISABLE);
    } else {
        /* burst wrap */
        L1C_Set_Wrap(ENABLE);
        /* For command that is setting register instead of send command, we need write enable */
        bflb_sflash_write_enable(p_flash_cfg);
        bflb_sflash_set_burst_wrap(p_flash_cfg);
    }

    if (flash_cont_read) {
        stat = bflb_sflash_read(p_flash_cfg, io_mode, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));
        stat = bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, 0);
    } else {
        stat = bflb_sflash_set_xip_cfg(p_flash_cfg, io_mode, 0, 0, 32, 0);
    }

    return stat;
}

/****************************************************************************/ /**
 * @brief  Sflash enable RCV mode to recovery for erase while power drop
 *
 * @param  p_flash_cfg: Flash configuration pointer
 * @param  r_cmd: Read RCV register cmd
 * @param  w_cmd: Write RCV register cmd
 * @param  bit_pos: RCV register bit pos
 *
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_rcv_enable(spi_flash_cfg_type *p_flash_cfg, uint8_t r_cmd, uint8_t w_cmd, uint8_t bit_pos)
{
    int stat = -1;
    uint32_t cnt = 0;
    uint32_t regval = 0;

    while (SET == bflb_sflash_busy(p_flash_cfg)) {
        BL602_Delay_US(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return -1;
        }
    }

    stat = bflb_sflash_read_reg_with_cmd(p_flash_cfg, r_cmd, (uint8_t *)&regval, 1);

    if (0 != stat) {
        stat = -1;
    }

    if (((regval >> bit_pos) & 0x01) > 0) {
        return 0;
    }

    regval |= (uint32_t)(1 << bit_pos);
    stat = bflb_sflash_write_enable(p_flash_cfg);

    if (0 != stat) {
        stat = -1;
    }

    stat = bflb_sflash_write_reg_with_cmd(p_flash_cfg, w_cmd, (uint8_t *)&regval, 1);

    if (0 != stat) {
        return stat;
    }

    while (SET == bflb_sflash_busy(p_flash_cfg)) {
        BL602_Delay_US(500);
        cnt++;

        if (cnt > 20000 * 3) {
            return -1;
        }
    }

    stat = bflb_sflash_read_reg_with_cmd(p_flash_cfg, r_cmd, (uint8_t *)&regval, 1);

    if (0 != stat) {
        stat = -1;
    }

    if (((regval >> bit_pos) & 0x01) <= 0) {
        return -1;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash security register one block
 *
 * @param  p_flash_cfg: Flash configuration pointer
 * @param  p_sec_reg_cfg: Security register configuration pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_erase_security_register(spi_flash_cfg_type *p_flash_cfg, struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    uint32_t cnt = 0;
    uint8_t cmd = 0;
    uint8_t sec_opt_mode = 0;
    uint32_t time_out = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
        }
    }

    int stat = bflb_sflash_write_enable(p_flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uint32_t)&flash_cmd) % 4 == 0) {
        BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
    }

    cmd = p_sec_reg_cfg->erase_cmd;
    flash_cmd.cmd_buf[0] = (cmd << 24) | (p_sec_reg_cfg->block_num << 12);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    bflb_sf_ctrl_sendcmd(&flash_cmd);

    while (SET == bflb_sflash_busy(p_flash_cfg)) {
        BL602_Delay_US(500);
        cnt++;

        if (cnt > p_flash_cfg->time_e_sector * 3) {
            return -1;
        }
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Program flash security register one block
 *
 * @param  p_flash_cfg: Flash configuration pointer
 * @param  p_sec_reg_cfg: Security register configuration pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_program_security_register(spi_flash_cfg_type *p_flash_cfg,
                                                  struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t i = 0, cur_len = 0;
    uint32_t cnt = 0;
    int stat = -1;
    uint8_t cmd;
    uint8_t sec_opt_mode = 0;
    uint8_t *data = p_sec_reg_cfg->data;
    uint32_t addr = p_sec_reg_cfg->addr;
    uint32_t len = p_sec_reg_cfg->len;
    uint32_t current_addr = 0;
    uint32_t time_out = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
        }
    }

    if (((uint32_t)&flash_cmd) % 4 == 0) {
        BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
    }

    /* Prepare command */
    flash_cmd.rw_flag = SF_CTRL_WRITE;
    flash_cmd.addr_size = 3;
    cmd = p_sec_reg_cfg->program_cmd;

    for (i = 0; i < len;) {
        /* Write enable is needed for every program */
        stat = bflb_sflash_write_enable(p_flash_cfg);

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
        BL602_MemCpy_Fast(flash_ctrl_buf, data, cur_len);
        flash_cmd.cmd_buf[0] = (cmd << 24) | (current_addr);
        flash_cmd.nb_data = cur_len;

        bflb_sf_ctrl_sendcmd(&flash_cmd);

        /* Adjust address and programmed length */
        addr += cur_len;
        i += cur_len;
        data += cur_len;

        /* Wait for write done */
        cnt = 0;

        while (SET == bflb_sflash_busy(p_flash_cfg)) {
            BL602_Delay_US(100);
            cnt++;

            if (cnt > p_flash_cfg->time_page_pgm * 20) {
                return -1;
            }
        }
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
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
 * @return 0 or -1
 *
*******************************************************************************/
int ATTR_TCM_SECTION bflb_sflash_read_security_register(struct sflash_sec_reg_cfg *p_sec_reg_cfg)
{
    uint8_t *const flash_ctrl_buf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t cur_len, i;
    uint8_t cmd;
    uint8_t sec_opt_mode = 0;
    uint8_t *data = p_sec_reg_cfg->data;
    uint32_t addr = p_sec_reg_cfg->addr;
    uint32_t len = p_sec_reg_cfg->len;
    uint32_t current_addr = 0;
    uint32_t time_out = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;

    if (p_sec_reg_cfg->enter_sec_opt_cmd != 0x00) {
        sec_opt_mode = 1;

        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->enter_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
        }
    }

    if (((uint32_t)&flash_cmd) % 4 == 0) {
        BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
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

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
        }

        BL602_MemCpy_Fast(data, flash_ctrl_buf, cur_len);

        addr += cur_len;
        i += cur_len;
        data += cur_len;
    }

    if (sec_opt_mode > 0) {
        if (((uint32_t)&flash_cmd) % 4 == 0) {
            BL602_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
        } else {
            BL602_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
        }

        flash_cmd.cmd_buf[0] = (p_sec_reg_cfg->exit_sec_opt_cmd << 24);
        flash_cmd.rw_flag = SF_CTRL_WRITE;
        bflb_sf_ctrl_sendcmd(&flash_cmd);

        time_out = SFCTRL_BUSY_STATE_TIMEOUT;

        while (SET == bflb_sf_ctrl_get_busy_state()) {
            time_out--;

            if (time_out == 0) {
                return -2;
            }
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
    uint8_t read_reg_value0 = 0;
    uint8_t read_reg_value1 = 0;

    if((p_flash_cfg->io_mode&0xf)==SF_CTRL_QO_MODE || (p_flash_cfg->io_mode&0xf)==SF_CTRL_QIO_MODE){
        qe_value = 1;
    }

    bflb_sflash_read_reg(p_flash_cfg, 0, (uint8_t *)&read_reg_value0, 1);
    bflb_sflash_read_reg(p_flash_cfg, 1, (uint8_t *)&read_reg_value1, 1);
    read_value = (read_reg_value0|(read_reg_value1<<8));
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

/****************************************************************************/ /**
 * @brief  Enable cache
 *
 * @param  way_disable: cache way disable config
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_cache_enable_set(uint8_t way_disable)
{
    uint32_t regval = 0;

    uint32_t cnt = 0;

    /* Set cacheable to 0 */
    regval = getreg32(SFLASH_L1C_BASE_ADDR + SFLASH_L1C_CONFIG_OFFSET);
    regval &= ~SFLASH_L1C_CACHEABLE;
    regval |= SFLASH_L1C_BYPASS;
    regval &= ~SFLASH_L1C_WAY_DIS_MASK;
    regval &= ~SFLASH_L1C_CNT_EN;
    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);

    regval = getreg32(SFLASH_L1C_BASE_ADDR + SFLASH_L1C_CONFIG_OFFSET);
    /*Set Tag RAM to zero */
    regval &= ~SFLASH_L1C_INVALID_EN;
    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    regval|= SFLASH_L1C_INVALID_EN;
    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    /* Polling for invalid done */
    do {
        BL602_Delay_US(1);
        cnt++;
        regval = getreg32(SFLASH_L1C_BASE_ADDR + SFLASH_L1C_CONFIG_OFFSET);
    } while (!((regval&SFLASH_L1C_INVALID_DONE) > 0 ? 1:0) && cnt < 100);

    regval |= SFLASH_L1C_BYPASS;
    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);

    regval &= ~SFLASH_L1C_BYPASS;
    regval &= ~SFLASH_L1C_WAY_DIS_MASK;
    regval |= SFLASH_L1C_CNT_EN;
    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);

    regval &= ~SFLASH_L1C_WAY_DIS_MASK;
    regval |= (way_disable << SFLASH_L1C_WAY_DIS_SHIFT);

    /* If way disable is 0x0f, cacheable can't be set */
    if (way_disable != 0x0f) {
        regval |= SFLASH_L1C_CACHEABLE;
    } else {
        regval &= ~SFLASH_L1C_CACHEABLE;
    }

    putreg32(regval, SFLASH_L1C_BASE_ADDR+SFLASH_L1C_CONFIG_OFFSET);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Flush cache
 *
 * @param  None
 *
 * @return 0 or -1
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_sflash_cache_flush(void)
{
    uint32_t regval = 0;
    uint32_t way_disable = 0;

    /* Disable early respone */
    regval = getreg32(SFLASH_L1C_BASE_ADDR + SFLASH_L1C_CONFIG_OFFSET);
    way_disable = (regval&SFLASH_L1C_WAY_DIS_MASK) >> SFLASH_L1C_WAY_DIS_SHIFT;
    bflb_sflash_cache_enable_set(way_disable & 0xf);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    return 0;
}

/*@} end of group SFLASH_EXT_Public_Functions */

/*@} end of group SFLASH_EXT */

/*@} end of group BL602_Peripheral_Driver */
