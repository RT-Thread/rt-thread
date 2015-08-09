/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//! @addtogroup diag_audio
//! @{

/*!
 * @file imx-ssi.h
 * @brief SSI header file.
 */

#ifndef __SSI_H__
#define __SSI_H__


//! @brief Settings supported by getting routine 
typedef enum {
    SSI_SETTING_TX_FIFO1_DATAS_CNT,
    SSI_SETTING_TX_FIFO2_DATAS_CNT,
    SSI_SETTING_RX_FIFO1_DATAS_CNT,
    SSI_SETTING_RX_FIFO2_DATAS_CNT,
    SSI_SETTING_TX_WATERMARK,
    SSI_SETTING_RX_WATERMARK,
    SSI_SETTING_TX_WORD_LEN,
    SSI_SETTING_RX_WORD_LEN,
    SSI_SETTING_TX_BIT_CLOCK,
    SSI_SETTING_RX_BIT_CLOCK,
    SSI_SETTING_TX_FRAME_LENGTH,
    SSI_SETTING_RX_FRAME_LENGTH,
    SSI_SETTING_CLK_FS_DIR,
} ssi_setting_type_e;

//! @brief Frame sync  clock directions
typedef enum {
    SSI_CLK_FS_DIR_OUTPUT,
    SSI_CLK_FS_DIR_INPUT,
} ssi_clk_fs_dir_e;

//! @brief Settings supported by enable routine 
typedef enum {
    SSI_HW_ENABLE_SSI,
    SSI_HW_ENABLE_TX,
    SSI_HW_ENABLE_RX,
    SSI_HW_ENABLE_TXFIFO1,
    SSI_HW_ENABLE_TXFIFO2,
    SSI_HW_ENABLE_RXFIFO1,
    SSI_HW_ENABLE_RXFIFO2,
} ssi_hw_enable_type_e;

//! @brief I2S work modes
typedef enum{
    I2S_MODE_NORMAL = 0,
    I2S_MODE_MASTER = 1,
    I2S_MODE_SLAVE = 2,
} i2s_mode_e;

////////////////////////////////////////////////////////////////////////////////
// APIs
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Initialize the ssi module and set the ssi to default status. 
 *
 * @param       priv    a pointer passed by audio card driver, SSI driver should change it 
 *			to a audio_ctrl_p pointer which presents the SSI controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t ssi_init(void *priv);

/*!
 * @brief Configure the SSI module according the parameters which was passed by audio_card driver.
 *
 * @param       priv    a pointer passed by audio card driver, SSI driver should change it
 *                      to a audio_ctrl_p pointer which presents the SSI controller.
 * @param       para	a pointer passed by audio card driver, consists of configuration parameters
 *                      for SSI controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t ssi_config(void *priv, audio_dev_para_p para);

/*!
 * @brief Write datas to the ssi fifo in polling mode.
 * @param       priv    a pointer passed by audio card driver, SSI driver should change it
 *                      to a audio_ctrl_p pointer which presents the SSI controller.
 * @param       buf	points to the buffer which hold the data to be written to the SSI tx fifo
 * @param       size    the size of the buffer pointed by buf.
 * @param       bytes_written	bytes be written to the SSI tx fifo
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t ssi_write_fifo(void *priv, uint8_t * buf, uint32_t size, uint32_t * bytes_written);

/*!
 * @brief Read datas from the ssi fifo in polling mode.
 * @param       priv    a pointer passed by audio card driver, SSI driver should change it
 *                      to a audio_ctrl_p pointer which presents the SSI controller.
 * @param       buf	points to the buffer which hold the data to be written to the SSI tx fifo
 * @param       byte2read    bytes to read.
 * @param       bytesread    bytes be read.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t ssi_read_fifo(void *priv, uint8_t *buf, uint32_t byte2read, uint32_t * byteread);

/*!
 * @brief Close the SSI module
 * @param       priv    a pointer passed by audio card driver, SSI driver should change it
 *                      to a audio_ctrl_p pointer which presents the SSI controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t ssi_deinit(void *priv);
#endif
