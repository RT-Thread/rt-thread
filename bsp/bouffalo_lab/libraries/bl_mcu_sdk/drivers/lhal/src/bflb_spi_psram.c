/**
  ******************************************************************************
  * @file    bflb_spi_psram.c
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

#include "bflb_spi_psram.h"
#include "bflb_l1c.h"

/** @addtogroup  BFLB_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM
 *  @{
 */

/** @defgroup  PSRAM_Private_Macros
 *  @{
 */

/*@} end of group PSRAM_Private_Macros */

/** @defgroup  PSRAM_Private_Types
 *  @{
 */

/*@} end of group PSRAM_Private_Types */

/** @defgroup  PSRAM_Private_Variables
 *  @{
 */

/*@} end of group PSRAM_Private_Variables */

/** @defgroup  PSRAM_Global_Variables
 *  @{
 */

/*@} end of group PSRAM_Global_Variables */

/** @defgroup  PSRAM_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PSRAM_Private_Fun_Declaration */

/** @defgroup  PSRAM_Private_Functions
 *  @{
 */

/*@} end of group PSRAM_Private_Functions */

/** @defgroup  PSRAM_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Init serial psram control interface
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  cmds_cfg: Serial Serial Flash controller configuration pointer
 * @param  sf_ctrl_psram_cfg: Serial psram controller configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_psram_init(struct spi_psram_cfg_type *psram_cfg, struct sf_ctrl_cmds_cfg *cmds_cfg,
                                 struct sf_ctrl_psram_cfg *sf_ctrl_psram_cfg)
{
    bflb_sf_ctrl_psram_init(sf_ctrl_psram_cfg);
    bflb_sf_ctrl_cmds_set(cmds_cfg, 0);

#if defined(BL702L)
    bflb_sf_ctrl_burst_toggle_set(psram_cfg->burst_toggle_en, psram_cfg->ctrl_mode);
#endif
    bflb_psram_setdrivestrength(psram_cfg);
    bflb_psram_setburstwrap(psram_cfg);
}

/****************************************************************************/ /**
 * @brief  Read psram register
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  reg_value: Register value pointer to store data
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_psram_readreg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value)
{
    uint8_t *const psram_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BASE;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type psram_cmd;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (psram_cfg->ctrl_mode == PSRAM_QPI_CTRL_MODE) {
        psram_cmd.cmd_mode = SF_CTRL_CMD_4_LINES;
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
    }

    psram_cmd.cmd_buf[0] = (psram_cfg->read_reg_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_READ;
    psram_cmd.addr_size = 3;
    psram_cmd.dummy_clks = psram_cfg->read_reg_dmy_clk;
    psram_cmd.nb_data = 1;

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }

    arch_memcpy(reg_value, psram_ctrl_buf, 1);
}

/****************************************************************************/ /**
 * @brief  Write psram register
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  reg_value: Register value pointer storing data
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_psram_writereg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value)
{
    uint8_t *const psram_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BASE;
    struct sf_ctrl_cmd_cfg_type psram_cmd;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    arch_memcpy(psram_ctrl_buf, reg_value, 1);

    if (psram_cfg->ctrl_mode == PSRAM_QPI_CTRL_MODE) {
        psram_cmd.cmd_mode = SF_CTRL_CMD_4_LINES;
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
    }

    psram_cmd.cmd_buf[0] = (psram_cfg->write_reg_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_WRITE;
    psram_cmd.addr_size = 3;
    psram_cmd.nb_data = 1;

    bflb_sf_ctrl_sendcmd(&psram_cmd);
}

/****************************************************************************/ /**
 * @brief  Set psram driver strength
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_setdrivestrength(struct spi_psram_cfg_type *psram_cfg)
{
    uint32_t stat = 0;

    bflb_psram_readreg(psram_cfg, (uint8_t *)&stat);

    if ((stat & 0x3) == psram_cfg->drive_strength) {
        return 0;
    }

    stat &= (~0x3);
    stat |= psram_cfg->drive_strength;

    bflb_psram_writereg(psram_cfg, (uint8_t *)&stat);
    /* Wait for write done */

    bflb_psram_readreg(psram_cfg, (uint8_t *)&stat);

    if ((stat & 0x3) == psram_cfg->drive_strength) {
        return 0;
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Set psram burst wrap size
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_setburstwrap(struct spi_psram_cfg_type *psram_cfg)
{
    uint32_t stat = 0;

    bflb_psram_readreg(psram_cfg, (uint8_t *)&stat);

    if (((stat >> 5) & 0x3) == psram_cfg->burst_length) {
        return 0;
    }

    stat &= (~(0x3 << 5));
    stat |= (psram_cfg->burst_length << 5);

    bflb_psram_writereg(psram_cfg, (uint8_t *)&stat);
    /* Wait for write done */

    bflb_psram_readreg(psram_cfg, (uint8_t *)&stat);

    if (((stat >> 5) & 0x3) == psram_cfg->burst_length) {
        return 0;
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Get psram ID
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  data: Data pointer to store read data
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_psram_readid(struct spi_psram_cfg_type *psram_cfg, uint8_t *data)
{
    uint8_t *const psram_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BASE;
    uint32_t timeout = 0;
    struct sf_ctrl_cmd_cfg_type psram_cmd;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    psram_cmd.cmd_buf[0] = (psram_cfg->read_id_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_READ;
    psram_cmd.addr_size = 3;
    psram_cmd.dummy_clks = psram_cfg->read_id_dmy_clk;
    psram_cmd.nb_data = 8;

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return;
        }
    }

    arch_memcpy(data, psram_ctrl_buf, 8);
}

/****************************************************************************/ /**
 * @brief  Psram enter quad mode
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_enterquadmode(struct spi_psram_cfg_type *psram_cfg)
{
    struct sf_ctrl_cmd_cfg_type psram_cmd;
    uint32_t timeout = 0;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    psram_cmd.cmd_buf[0] = (psram_cfg->enter_quad_mode_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_READ;

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return -2;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Psram exit quad mode
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_exitquadmode(struct spi_psram_cfg_type *psram_cfg)
{
    struct sf_ctrl_cmd_cfg_type psram_cmd;
    uint32_t timeout = 0;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    psram_cmd.cmd_mode = SF_CTRL_CMD_4_LINES;
    psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
    psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;

    psram_cmd.cmd_buf[0] = (psram_cfg->exit_quad_mode_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_READ;

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return -2;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Psram toggle burst length
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  ctrl_mode: Psram ctrl mode type
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_toggleburstlength(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode)
{
    struct sf_ctrl_cmd_cfg_type psram_cmd;
    uint32_t timeout = 0;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (ctrl_mode == PSRAM_QPI_CTRL_MODE) {
        psram_cmd.cmd_mode = SF_CTRL_CMD_4_LINES;
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
    }

    psram_cmd.cmd_buf[0] = (psram_cfg->burst_toggle_cmd) << 24;
    psram_cmd.rw_flag = SF_CTRL_READ;

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return -2;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Psram software reset
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  ctrl_mode: Psram ctrl mode type
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_softwarereset(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode)
{
    struct sf_ctrl_cmd_cfg_type psram_cmd;
    uint32_t timeout = 0;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (ctrl_mode == PSRAM_QPI_CTRL_MODE) {
        psram_cmd.cmd_mode = SF_CTRL_CMD_4_LINES;
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
    }

    /* Reset enable */
    psram_cmd.cmd_buf[0] = (psram_cfg->reset_enable_cmd) << 24;
    /* rw_flag don't care */
    psram_cmd.rw_flag = SF_CTRL_READ;
    /* Wait for write done */

    bflb_sf_ctrl_sendcmd(&psram_cmd);

    timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return -2;
        }
    }

    /* Reset */
    psram_cmd.cmd_buf[0] = (psram_cfg->reset_cmd) << 24;
    /* rw_flag don't care */
    psram_cmd.rw_flag = SF_CTRL_READ;
    bflb_sf_ctrl_sendcmd(&psram_cmd);

    while (bflb_sf_ctrl_get_busy_state()) {
        timeout--;

        if (timeout == 0) {
            return -2;
        }
    }

    arch_delay_us(50);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Psram set IDbus config
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  io_mode: Psram ctrl mode type
 * @param  addr: Address to read/write
 * @param  len: Data length to read/write
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_set_idbus_cfg(struct spi_psram_cfg_type *psram_cfg,
                                                 uint8_t io_mode, uint32_t addr, uint32_t len)
{
    uint8_t cmd, dummy_clks;
    struct sf_ctrl_cmd_cfg_type psram_cmd;
    uint8_t cmd_valid = 1;

    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_IAHB);

    /* read mode cache set */
    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = psram_cfg->f_read_cmd;
        dummy_clks = psram_cfg->f_read_dmy_clk;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = psram_cfg->f_read_quad_cmd;
        dummy_clks = psram_cfg->f_read_quad_dmy_clk;
    } else {
        return -1;
    }

    /* prepare command */
    psram_cmd.rw_flag = SF_CTRL_READ;
    psram_cmd.addr_size = 3;
    psram_cmd.cmd_buf[0] = (cmd << 24) | addr;
    psram_cmd.dummy_clks = dummy_clks;
    psram_cmd.nb_data = len;
    bflb_sf_ctrl_psram_read_set(&psram_cmd, cmd_valid);

    /* write mode cache set */
    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = psram_cfg->write_cmd;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = psram_cfg->quad_write_cmd;
    } else {
        return -1;
    }

    dummy_clks = 0;

    /* prepare command */
    psram_cmd.rw_flag = SF_CTRL_WRITE;
    psram_cmd.addr_size = 3;
    psram_cmd.cmd_buf[0] = (cmd << 24) | addr;
    psram_cmd.dummy_clks = dummy_clks;
    psram_cmd.nb_data = len;
    bflb_sf_ctrl_psram_write_set(&psram_cmd, cmd_valid);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Set cache write to psram with cache
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  io_mode: Psram controller interface mode
 * @param  wt_en: Psram cache write through enable
 * @param  wb_en: Psram cache write back enable
 * @param  wa_en: Psram cache write allocate enable
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_cache_write_set(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode,
                                                uint8_t wt_en, uint8_t wb_en, uint8_t wa_en)
{
    int stat = -1;

    /* Cache now only support 32 bytes read */
    stat = bflb_psram_set_idbus_cfg(psram_cfg, io_mode, 0, 32);

    if (0 != stat) {
        return stat;
    }

    bflb_l1c_cache_write_set(wt_en, wb_en, wa_en);
    return 0;
}

/****************************************************************************/ /**
 * @brief  Write psram one region
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  io_mode: Write mode: SPI mode or QPI mode
 * @param  addr: Start address to be write
 * @param  data: Data pointer to be write
 * @param  len: Data length to be write
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_write(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode,
                                      uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const psram_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BASE;
    uint32_t i = 0, cur_len = 0;
    uint32_t burst_len = 512;
    uint8_t cmd;
    struct sf_ctrl_cmd_cfg_type psram_cmd;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = psram_cfg->write_cmd;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = psram_cfg->quad_write_cmd;
    } else {
        return -1;
    }

    /* Prepare command */
    psram_cmd.rw_flag = SF_CTRL_WRITE;
    psram_cmd.addr_size = 3;

    if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_16_BYTES) {
        burst_len = 16;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_32_BYTES) {
        burst_len = 32;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_64_BYTES) {
        burst_len = 64;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_512_BYTES) {
        burst_len = 512;
    }

    for (i = 0; i < len;) {
        /* Get current programmed length within page size */
        cur_len = burst_len - addr % burst_len;

        if (cur_len > len - i) {
            cur_len = len - i;
        }

        /* Prepare command */
        arch_memcpy_fast(psram_ctrl_buf, data, cur_len);
        psram_cmd.cmd_buf[0] = (cmd << 24) | (addr);
        psram_cmd.nb_data = cur_len;

        bflb_sf_ctrl_sendcmd(&psram_cmd);

        /* Adjust address and programmed length */
        addr += cur_len;
        i += cur_len;
        data += cur_len;

        /* Wait for write done */
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Read data from psram
 *
 * @param  psram_cfg: Serial psram parameter configuration pointer
 * @param  io_mode: IoMode: psram controller interface mode
 * @param  addr: Psram read start address
 * @param  data: Data pointer to store data read from psram
 * @param  len: Data length to read
 *
 * @return BFLB_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION bflb_psram_read(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode,
                                     uint32_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *const psram_ctrl_buf = (uint8_t *)BFLB_SF_CTRL_BASE;
    uint32_t cur_len, i;
    uint32_t burst_len = 512;
    uint32_t timeout = 0;
    uint8_t cmd, dummy_clks;
    struct sf_ctrl_cmd_cfg_type psram_cmd;

    if (((uint32_t)&psram_cmd) % 4 == 0) {
        arch_memset4((uint32_t *)&psram_cmd, 0, sizeof(psram_cmd) / 4);
    } else {
        arch_memset(&psram_cmd, 0, sizeof(psram_cmd));
    }

    if (SF_CTRL_NIO_MODE == io_mode) {
        cmd = psram_cfg->f_read_cmd;
        dummy_clks = psram_cfg->f_read_dmy_clk;
    } else if (SF_CTRL_QIO_MODE == io_mode) {
        psram_cmd.addr_mode = SF_CTRL_ADDR_4_LINES;
        psram_cmd.data_mode = SF_CTRL_DATA_4_LINES;
        cmd = psram_cfg->f_read_quad_cmd;
        dummy_clks = psram_cfg->f_read_quad_dmy_clk;
    } else {
        return -1;
    }

    /* Prepare command */
    psram_cmd.rw_flag = SF_CTRL_READ;
    psram_cmd.addr_size = 3;
    psram_cmd.dummy_clks = dummy_clks;

    if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_16_BYTES) {
        burst_len = 16;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_32_BYTES) {
        burst_len = 32;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_64_BYTES) {
        burst_len = 64;
    } else if (psram_cfg->burst_length == PSRAM_BURST_LENGTH_512_BYTES) {
        burst_len = 512;
    }

    /* Read data */
    for (i = 0; i < len;) {
        /* Prepare command */
        psram_cmd.cmd_buf[0] = (cmd << 24) | (addr);
        cur_len = burst_len - addr % burst_len;

        if (cur_len > len - i) {
            cur_len = len - i;
        }

        if (cur_len >= NOR_FLASH_CTRL_BUF_SIZE) {
            cur_len = NOR_FLASH_CTRL_BUF_SIZE;
            psram_cmd.nb_data = cur_len;
        } else {
            /* Make sf_ctrl word read */
            psram_cmd.nb_data = ((cur_len + 3) >> 2) << 2;
        }

        bflb_sf_ctrl_sendcmd(&psram_cmd);

        timeout = SF_CTRL_BUSY_STATE_TIMEOUT;
        while (bflb_sf_ctrl_get_busy_state()) {
            timeout--;

            if (timeout == 0) {
                return -2;
            }
        }

        arch_memcpy_fast(data, psram_ctrl_buf, cur_len);

        addr += cur_len;
        i += cur_len;
        data += cur_len;
    }

    return 0;
}

/*@} end of group PSRAM_Public_Functions */

/*@} end of group PSRAM */

/*@} end of group BFLB_Peripheral_Driver */
