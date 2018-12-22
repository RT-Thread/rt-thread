/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_config.h"
#if APP_SDCARD_ENABLED

#include "app_sdcard.h"
#include "nrf_gpio.h"
#include "nrf_drv_spi.h"
#include "app_error.h"
#include "nrf_assert.h"

#include "nrf_pt.h"

#define CMD_MASK  0x40
#define ACMD_MASK 0x80
#define CMD0    (CMD_MASK | 0)                  /**< SDC/MMC command 0:  GO_IDLE_STATE. */
#define CMD1    (CMD_MASK | 1)                  /**< SDC/MMC command 1:  SEND_OP_COND (MMC). */
#define CMD8    (CMD_MASK | 8)                  /**< SDC/MMC command 8:  SEND_IF_COND. */
#define CMD9    (CMD_MASK | 9)                  /**< SDC/MMC command 9:  SEND_CSD. */
#define CMD10   (CMD_MASK | 10)                 /**< SDC/MMC command 10: SEND_CID. */
#define CMD12   (CMD_MASK | 12)                 /**< SDC/MMC command 12: STOP_TRANSMISSION. */
#define CMD16   (CMD_MASK | 16)                 /**< SDC/MMC command 16: SET_BLOCKLEN. */
#define CMD17   (CMD_MASK | 17)                 /**< SDC/MMC command 17: READ_SINGLE_BLOCK. */
#define CMD18   (CMD_MASK | 18)                 /**< SDC/MMC command 18: READ_MULTIPLE_BLOCK. */
#define CMD23   (CMD_MASK | 23)                 /**< SDC/MMC command 23: SET_BLOCK_COUNT (MMC). */
#define CMD24   (CMD_MASK | 24)                 /**< SDC/MMC command 24: WRITE_BLOCK. */
#define CMD25   (CMD_MASK | 25)                 /**< SDC/MMC command 25: WRITE_MULTIPLE_BLOCK. */
#define CMD32   (CMD_MASK | 32)                 /**< SDC/MMC command 32: ERASE_ER_BLK_START. */
#define CMD33   (CMD_MASK | 33)                 /**< SDC/MMC command 33: ERASE_ER_BLK_END. */
#define CMD38   (CMD_MASK | 38)                 /**< SDC/MMC command 38: ERASE. */
#define CMD55   (CMD_MASK | 55)                 /**< SDC/MMC command 55: APP_CMD. */
#define CMD58   (CMD_MASK | 58)                 /**< SDC/MMC command 58: READ_OCR. */
#define ACMD13  (ACMD_MASK | CMD_MASK | 13)     /**< SDC application command 13: SD_STATUS. */
#define ACMD23  (ACMD_MASK | CMD_MASK | 23)     /**< SDC application command 23: SET_WR_BLK_ERASE_COUNT. */
#define ACMD41  (ACMD_MASK | CMD_MASK | 41)     /**< SDC application command 41: SEND_OP_COND. */

#define IS_ACMD(CMD) ((CMD) & ACMD_MASK)        /**< Check if command is an application command (ACMD). */

#define SDC_COMMAND_LEN      6      /**< Length of a command structure sent to the card. */
#define SDC_COMMAND_POS      0      /**< Position of a command field inside the command structure. */
#define SDC_COMMAND_MASK     0x7F   /**< Bit mask of a command field. */
#define SDC_COMMAND_ARG_POS  1      /**< Position of a 32-bit argument inside the command structure. */
#define SDC_COMMAND_CRC_POS  5      /**< Position of a CRC field inside the command structure. */

#define SDC_MAX_NCR          8      /**< Maximum number of "busy" bytes sent before command response. */
#define SDC_R1_LEN           1      /**< Length of R1 format response. */
#define SDC_R3_LEN           5      /**< Length of R3 format response. */
#define SDC_R7_LEN           5      /**< Length of R7 format response. */
#define SDC_R_MAX_LEN        5      /**< Maximum length of command response. */

#define SDC_FLAG_IN_IDLE_STATE          0x01    /**< R1 response flag bit mask: idle state. */
#define SDC_FLAG_ERASE_RESET            0x02    /**< R1 response flag bit mask: erase reset. */
#define SDC_FLAG_ILLEGAL_COMMAND        0x04    /**< R1 response flag bit mask: illegal command. */
#define SDC_FLAG_COM_CRC_ERROR          0x08    /**< R1 response flag bit mask: CRC error. */
#define SDC_FLAG_ERASE_SEQUENCE_ERROR   0x10    /**< R1 response flag bit mask: erase sequence error. */
#define SDC_FLAG_ADDRESS_ERROR          0x20    /**< R1 response flag bit mask: address error. */
#define SDC_FLAG_PARAMETER_ERROR        0x40    /**< R1 response flag bit mask: parameter error. */

#define SDC_HCS_FLAG_MASK               (1uL << 30) /**< High capacity support bit mask. */

#define SDC_EMPTY_BYTE                  0xFF    /**< Idle state token. */
#define SDC_BUSY_BYTE                   0x00    /**< Busy byte token. */
#define SDC_TOKEN_START_BLOCK           0xFE    /**< Data block start token. */
#define SDC_TOKEN_START_BLOCK_MULT      0xFC    /**< Data block start token for multiple write operation. */
#define SDC_TOKEN_DATA_RESP_MASK        0x1F    /**< Data response token mask. */
#define SDC_TOKEN_DATA_RESP_ACCEPTED    0x05    /**< Data response message: accepted. */
#define SDC_TOKEN_DATA_RESP_CRC_ERR     0x0B    /**< Data response message: CRC error. */
#define SDC_TOKEN_DATA_RESP_DATA_ERR    0x0D    /**< Data response message: data error. */
#define SDC_TOKEN_STOP_TRAN             0xFD    /**< Stop transmission token. */

#define SDC_MAX_RETRY_COUNT_INIT        2000    /**< Maximum number of retries while card is busy (identification stage). */
#define SDC_MAX_RETRY_COUNT             20000   /**< Maximum number of retries while card is busy. */
#define SDC_SPI_MTU                     240     /**< Maximum number of bytes in one SPI transaction. */
#define SDC_CRC_CMD0                    0x95    /**< Fixed CRC for reset command. */
#define SDC_CRC_CMD8                    0x87    /**< Fixed CRC for CMD8. */
#define SDC_CRC_DUMMY                   0xFF    /**< Dummy CRC value. */

#define SDC_CMD_BUF_LEN         16      /**< Size of a buffer for storing SDC commands. */
#define SDC_WORK_BUF_LEN        16      /**< Size of a working buffer. */
#define SDC_DATA_WAIT_TX_SIZE   16      /**< Number of bytes sent during data / busy wait. */

#define SDC_CS_ASSERT()   do { nrf_gpio_pin_clear(m_cb.cs_pin); } while (0) /**< Set CS pin to active state. */
#define SDC_CS_DEASSERT() do { nrf_gpio_pin_set(m_cb.cs_pin);   } while (0) /**< Set CS pin to inactive state. */

#define SDC_PT     &m_cb.state.pt       /**< Macro for getting SDC task structure pointer (Protothread). */
#define SDC_PT_SUB &m_cb.state.pt_sub   /**< Macro for getting SDC sub-task structure pointer (Protothread). */

/** Break current task (Protothread). */
#define SDC_BREAK(PT, EXIT_CODE) do {                            \
                                     *p_exit_code = (EXIT_CODE); \
                                     PT_EXIT(PT);                \
                                 } while(0)

/**< Check the value of R1 response and break current task on error. */
#define SDC_RESP_CHECK(PT, R1) do {                                                             \
                                   if ((R1) & ~(SDC_FLAG_IN_IDLE_STATE | SDC_FLAG_ERASE_RESET)) \
                                   {                                                            \
                                       SDC_BREAK((PT), SDC_ERROR_COMMUNICATION);                \
                                   }                                                            \
                               } while(0)

/**< Check the result of an SDC operation and break on failure. */
#define SDC_RESULT_CHECK(PT, RESULT) do {                             \
                                         if ((RESULT) != SDC_SUCCESS) \
                                         {                            \
                                             SDC_BREAK((PT), RESULT); \
                                         }                            \
                                     } while(0);


static const nrf_drv_spi_t m_spi = NRF_DRV_SPI_INSTANCE(APP_SDCARD_SPI_INSTANCE);  /**< SPI instance. */

/**
 * @brief SDC response type.
 */
typedef enum {
    SDC_RNONE = 0,
    SDC_R1,
    SDC_R3,
    SDC_R7
} sdc_response_t;

/**
 * @brief SDC operation state.
 */
typedef enum {
    SDC_UNINITIALIZED     = 0,  ///< Card not initialized.
    SDC_OP_RESET          = 1,  ///< Reset state.
    SDC_OP_IDENTIFICATION = 2,  ///< Identification procedure.
    SDC_OP_IDLE           = 3,  ///< Idle state.
    SDC_OP_READ           = 4,  ///< Data read procedure.
    SDC_OP_WRITE          = 5   ///< Data write procedure.
} sdc_op_t;

/**
 * @brief SDC data bus state.
 */
typedef enum {
    SDC_BUS_IDLE = 0,       ///< Idle state, no active transfer.
    SDC_BUS_CMD  = 1,       ///< Command is being transfered.
    SDC_BUS_ACMD = 2,       ///< Application command header transfer.
    SDC_BUS_DATA_WAIT = 3,  ///< Data wait state.
    SDC_BUS_DATA = 4        ///< Data block transfer in progress.
} sdc_bus_state_t;

/**
 * @brief Current read/write operation state structure.
 */
typedef struct {
    uint8_t * buffer;           ///< Local data buffer.
    uint32_t  address;          ///< Data block address.
    uint16_t  block_count;      ///< Total number of blocks in read/write operation.
    uint16_t  blocks_left;      ///< Blocks left in current read/write operation.
    uint16_t  position;         ///< Number of blocks left to read/write.
} sdc_rw_op_t;

/**
 * @brief SDC state structure.
 */
typedef struct {
    sdc_rw_op_t       rw_op;        ///< Read/write operation state.
    pt_t              pt;           ///< Current task (Protothread) state.
    pt_t              pt_sub;       ///< Current sub-task (Protothread) state.
    uint16_t          retry_count;  ///< Number of retries left.
    volatile sdc_op_t op;           ///< Current operation.
    sdc_bus_state_t   bus_state;    ///< Current data bud state.
    uint8_t           rsp_len;      ///< Expected response length.
} sdc_state_t;

/**
 * @beirf SDC control block.
 */
typedef struct {
    sdc_event_handler_t handler;                    ///< Event handler.
    app_sdc_info_t      info;                       ///< Card information structure.
    sdc_state_t         state;                      ///< Card state structure
    uint8_t             cmd_buf[SDC_CMD_BUF_LEN];   ///< Command buffer.
    uint8_t             rsp_buf[SDC_CMD_BUF_LEN];   ///< Card response buffer.
    uint8_t             work_buf[SDC_WORK_BUF_LEN]; ///< Working buffer
    uint8_t             cs_pin;                     ///< Chip select pin number.
} sdc_cb_t;

static sdc_cb_t m_cb;   ///< SDC control block.


/**
 * @brief Function for requesting the SPI transaction.
 *
 * The SPI bus must be initialized prior to use of this function.
 *
 * @param[in] p_txb     Pointer to the TX buffer.
 * @param[in] tx_len    TX buffer length.
 * @param[out] p_rxb    Pointer to the RX buffer.
 * @param[in] tx_len    RX buffer length.
 */
__STATIC_INLINE void sdc_spi_transfer(uint8_t const * const p_txb,
                                      uint8_t tx_len,
                                      uint8_t * const p_rxb,
                                      uint8_t rx_len)
{
    SDC_CS_ASSERT();
    ret_code_t err_code = nrf_drv_spi_transfer(&m_spi, p_txb, tx_len, p_rxb, rx_len);
    APP_ERROR_CHECK(err_code);
}


/**
 * @brief Function for switching the SPI clock to high speed mode.
 */
__STATIC_INLINE void sdc_spi_hispeed(void)
{
    nrf_spi_frequency_set((NRF_SPI_Type *)m_spi.p_registers,
                          (nrf_spi_frequency_t) APP_SDCARD_FREQ_DATA);
}


/**
 * @brief Function for extracting the number of data block from the CSD structure.
 *
 * @param[in] p_csd     Pointer to the card CSD structure.
 *
 * @return   Number of data blocks or 0 if unsupported / invalid structure was provided.
 */
static uint32_t sdc_calculate_size(uint8_t const * const p_csd)
{
    // Values are calculated as stated in SD Specifications, chapter 5.3.
    uint8_t csd_version = p_csd[0] >> 6;

    switch(csd_version)
    {
        case 0:
        case 2:
        {
            // SD Standard Capacity or MMC.
            uint32_t c_size = ((uint32_t) p_csd[8] >> 6) + (((uint32_t) p_csd[7]) << 2)
                              + ((uint32_t)(p_csd[6] & 0x03) << 10);
            uint32_t read_bl_len = p_csd[5] & 0x0F;
            uint32_t c_size_mult = ((p_csd[10] & 0x80) >> 7) + ((p_csd[9] & 0x03) << 1);

            // Block size in this implementation is set to 512, so the resulting number of bytes
            // is divided by 512 (2^9)
            return (c_size + 1) << (read_bl_len + c_size_mult + 2 - 9);
        }
        case 1:
        {
            // SD High Capacity.
            uint32_t c_size = (uint32_t) p_csd[9] + ((uint32_t) p_csd[8] << 8)
                              + (((uint32_t) p_csd[7] & 0x3F) << 16);

            // According to SD 2.0 Specifications, capacity = (C_SIZE + 1) * 512KByte.
            // Block size is equal to 512, so the result is divided by 512.
            return (c_size + 1) * 1024uL;
        }
        default:
            break;
    }
    return 0;
}


/**
 * @brief Non-blocking function for sending a command to the card.
 *
 * @param[in] cmd       SDC command ID.
 * @param[in] arg       32-bit command argument.
 * @param[in] rsp_type  Expected command response format.
 *
 * @retval NRF_SUCCESS             If command transmission was started successfully.
 * @retval NRF_ERROR_BUSY          If the card is not in idle state.
 */
static ret_code_t sdc_cmd(uint8_t cmd, uint32_t arg, sdc_response_t rsp_type)
{
    if (m_cb.state.bus_state != SDC_BUS_IDLE)
    {
        return NRF_ERROR_BUSY;
    }

    uint8_t offset = 0;

    m_cb.state.bus_state = SDC_BUS_CMD;
    if (IS_ACMD(cmd))
    {
        // ACMD is a combination of CMD55 and the requested command,
        // which will be placed next in the command buffer.
        offset = SDC_COMMAND_LEN;
        m_cb.state.bus_state = SDC_BUS_ACMD;
        m_cb.cmd_buf[SDC_COMMAND_POS] = CMD55;
        m_cb.cmd_buf[SDC_COMMAND_ARG_POS]     = 0;
        m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 1] = 0;
        m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 2] = 0;
        m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 3] = 0;
        m_cb.cmd_buf[SDC_COMMAND_CRC_POS] = SDC_CRC_DUMMY;
    }

    m_cb.cmd_buf[SDC_COMMAND_POS + offset] = cmd & SDC_COMMAND_MASK;
    m_cb.cmd_buf[SDC_COMMAND_ARG_POS + offset]     = (uint8_t)(arg >> 24);
    m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 1 + offset] = (uint8_t)(arg >> 16);
    m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 2 + offset] = (uint8_t)(arg >> 8);
    m_cb.cmd_buf[SDC_COMMAND_ARG_POS + 3 + offset] = (uint8_t)(arg);

    // Use predefined CRC values and omit the crc calculation if not required.
    uint8_t crc;
    switch (cmd)
    {
        case CMD0:
            crc = SDC_CRC_CMD0;
            break;
        case CMD8:
            crc = SDC_CRC_CMD8;
            break;
        default:
            crc = SDC_CRC_DUMMY;
            break;
    }
    m_cb.cmd_buf[SDC_COMMAND_CRC_POS + offset] = crc;

    switch (rsp_type)
    {
        case SDC_R3:
            m_cb.state.rsp_len = SDC_R3_LEN;
            break;
        case SDC_R7:
            m_cb.state.rsp_len = SDC_R7_LEN;
            break;
        default:
            m_cb.state.rsp_len = SDC_R1_LEN;
            break;
    }

    uint8_t response_len = (IS_ACMD(cmd)) ? SDC_R1_LEN : m_cb.state.rsp_len;
    sdc_spi_transfer(m_cb.cmd_buf,
                     SDC_COMMAND_LEN,
                     m_cb.rsp_buf,
                     SDC_COMMAND_LEN + SDC_MAX_NCR + response_len);

    return NRF_SUCCESS;
}


/**
 * @brief Data block read subroutine.
 *
 * @param[in] p_rx_data     Pointer to the data received in last transation.
 * @param[in] rx_length     Received data length.
 * @param[in] block_len     Size of a data block to read.
 * @param[out] p_exit_code  Pointer to the subroutine exit code variable. Valid only if the thread has exited.
 *
 * @return    Protothread exit code. Zero if protothread is running and non-zero if exited.
 */
static PT_THREAD(sdc_pt_sub_data_read(uint8_t * p_rx_data,
                                      uint8_t rx_length,
                                      uint16_t block_len,
                                      sdc_result_t * p_exit_code))
{
    PT_BEGIN(SDC_PT_SUB);
    while (1)
    {
        ASSERT(block_len);
        ASSERT(m_cb.state.rw_op.block_count);

        m_cb.state.rw_op.blocks_left = m_cb.state.rw_op.block_count;

        while (m_cb.state.rw_op.blocks_left)
        {
            m_cb.state.retry_count = 0;
            m_cb.cmd_buf[0] = 0xFF;
            m_cb.state.rw_op.position = 0;
            m_cb.state.bus_state = SDC_BUS_DATA_WAIT;

            while (m_cb.state.bus_state == SDC_BUS_DATA_WAIT)
            {
                ++m_cb.state.retry_count;
                if (m_cb.state.retry_count > SDC_MAX_RETRY_COUNT)
                {
                    SDC_BREAK(SDC_PT_SUB, SDC_ERROR_TIMEOUT);
                }

                // Search for the first token.
                while(rx_length && p_rx_data[0] ==  SDC_EMPTY_BYTE)
                {
                    ++p_rx_data;
                    --rx_length;
                }

                if (rx_length)
                {
                    // A token has been found.
                    if (p_rx_data[0] == SDC_TOKEN_START_BLOCK)
                    {
                        // Expected data start token found.
                        // Copy the data bytes left in rx buffer into user buffer.
                        ++p_rx_data;
                        --rx_length;
                        m_cb.state.bus_state = SDC_BUS_DATA;
                        uint16_t copy_len = (rx_length > block_len) ? block_len : rx_length;
                        for (uint32_t i = 0; i < copy_len; ++i)
                        {
                            m_cb.state.rw_op.buffer[i] = p_rx_data[i];
                        }
                        m_cb.state.rw_op.position = copy_len;
                        m_cb.state.rw_op.buffer += copy_len;
                    }
                    else
                    {
                        // Data error.
                        SDC_BREAK(SDC_PT_SUB, SDC_ERROR_DATA);
                    }
                }
                else
                {
                    // Continue transfer until token is received.
                    sdc_spi_transfer(m_cb.cmd_buf, 1, m_cb.rsp_buf, SDC_DATA_WAIT_TX_SIZE);
                    PT_YIELD(SDC_PT_SUB);
                }
            }

            while (m_cb.state.rw_op.position < block_len)
            {
                {
                    uint16_t chunk_size = block_len - m_cb.state.rw_op.position;
                    if (chunk_size > SDC_SPI_MTU)
                    {
                        chunk_size = SDC_SPI_MTU;
                    }

                    sdc_spi_transfer(m_cb.cmd_buf, 1,
                                     m_cb.state.rw_op.buffer, chunk_size);
                    m_cb.state.rw_op.buffer   += chunk_size;
                    m_cb.state.rw_op.position += chunk_size;
                }
                PT_YIELD(SDC_PT_SUB);
            }

            // Get the CRC.
            --m_cb.state.rw_op.blocks_left;
            sdc_spi_transfer(m_cb.cmd_buf, 1,
                 m_cb.rsp_buf, 2);
            PT_YIELD(SDC_PT_SUB);



            // Set rx length to 0 to force "busy check" transmission before next data block.
            rx_length = 0;
        }

        // Send padding bytes.
        m_cb.cmd_buf[0] = SDC_EMPTY_BYTE;
        sdc_spi_transfer(m_cb.cmd_buf, 1,
                         m_cb.rsp_buf, 2);
        PT_YIELD(SDC_PT_SUB);

        m_cb.state.bus_state = SDC_BUS_IDLE;
        SDC_BREAK(SDC_PT_SUB, SDC_SUCCESS);
    }
    PT_END(SDC_PT_SUB)
}


/**
 * @brief Card identification co-routine.
 *
 * @param[in] p_rx_data     Pointer to the data received in last transation.
 * @param[in] rx_length     Received data length.
 * @param[out] p_exit_code  Pointer to the routine exit code variable. Valid only if the thread has exited.
 *
 * @return    Protothread exit code. Zero if protothread is running and non-zero if exited.
 */
static PT_THREAD(sdc_pt_identification(uint8_t * p_rx_data,
                                       uint8_t rx_length,
                                       sdc_result_t * p_exit_code))
{
    uint8_t r1   = p_rx_data[0];
    uint32_t rsp = ((uint32_t)p_rx_data[1] << 24)
                   | ((uint32_t)p_rx_data[2] << 16)
                   | ((uint32_t)p_rx_data[3] << 8)
                   | ((uint32_t)p_rx_data[4]);
    uint32_t arg;
    ret_code_t err_code;
    sdc_result_t sub_exit_code;

    PT_BEGIN(SDC_PT);
    while (1)
    {
        err_code = sdc_cmd(CMD0, 0, SDC_R1);
        APP_ERROR_CHECK(err_code);
        PT_YIELD(SDC_PT);
        err_code = sdc_cmd(CMD0, 0, SDC_R1);
        APP_ERROR_CHECK(err_code);
        PT_YIELD(SDC_PT);

        SDC_RESP_CHECK(SDC_PT, r1);
        // Send CMD8 with fixed argument - 0x01AA.
        err_code = sdc_cmd(CMD8, 0x1AA, SDC_R7);
        APP_ERROR_CHECK(err_code);
        PT_YIELD(SDC_PT);

        if (!(r1 & SDC_FLAG_ILLEGAL_COMMAND))
        {
            // CMD8 was accepted - SD v2 card.
            m_cb.info.type.version = SDC_TYPE_SDV2;
            SDC_RESP_CHECK(SDC_PT, r1);
        }

        m_cb.state.retry_count = 0;
        arg = (m_cb.info.type.version == SDC_TYPE_SDV2) ? SDC_HCS_FLAG_MASK : 0;
        err_code = sdc_cmd(ACMD41, arg, SDC_R3);
        APP_ERROR_CHECK(err_code);
        PT_YIELD(SDC_PT);

        if (r1 & SDC_FLAG_ILLEGAL_COMMAND)
        {
            // ACMD41 was rejected - MMC card.
            m_cb.info.type.version = SDC_TYPE_MMCV3;
            r1 &= ~SDC_FLAG_ILLEGAL_COMMAND;

            do
            {
                ++m_cb.state.retry_count;
                if (m_cb.state.retry_count > SDC_MAX_RETRY_COUNT_INIT)
                {
                    SDC_BREAK(SDC_PT, SDC_ERROR_TIMEOUT);
                }

                err_code = sdc_cmd(CMD1, 0, SDC_R3);
                APP_ERROR_CHECK(err_code);
                PT_YIELD(SDC_PT);
                SDC_RESP_CHECK(SDC_PT, r1);
            }
            while (r1 & SDC_FLAG_IN_IDLE_STATE);
        }
        else
        {
            // SDv1 or SDv2 card. Send CMD58 or retry ACMD41 if not ready.
            SDC_RESP_CHECK(SDC_PT, r1);

            while (r1 & SDC_FLAG_IN_IDLE_STATE)
            {
                ++m_cb.state.retry_count;
                if (m_cb.state.retry_count > SDC_MAX_RETRY_COUNT_INIT)
                {
                    SDC_BREAK(SDC_PT, SDC_ERROR_TIMEOUT);
                }

                arg = (m_cb.info.type.version == SDC_TYPE_SDV2) ? SDC_HCS_FLAG_MASK : 0;
                err_code = sdc_cmd(ACMD41, arg, SDC_R3);
                APP_ERROR_CHECK(err_code);
                PT_YIELD(SDC_PT);
                SDC_RESP_CHECK(SDC_PT, r1);
            }

            err_code = sdc_cmd(CMD58, 0, SDC_R3);
            APP_ERROR_CHECK(err_code);
            PT_YIELD(SDC_PT);
            SDC_RESP_CHECK(SDC_PT, r1);

            if (rsp & SDC_HCS_FLAG_MASK)
            {
                m_cb.info.type.sdhc = 1;
            }
        }

        if (m_cb.info.type.version != SDC_TYPE_SDV2)
        {
            // Set block length to 512 (SDv1 and MMC cards only.)
            err_code = sdc_cmd(CMD16, SDC_SECTOR_SIZE, SDC_R1);
            APP_ERROR_CHECK(err_code);
            PT_YIELD(SDC_PT);
            SDC_RESP_CHECK(SDC_PT, r1);
        }

        // Setup the read operation and get the contents of 128-bit CSD register.
        m_cb.state.rw_op.buffer = m_cb.work_buf;
        m_cb.state.rw_op.block_count = 1;

        err_code = sdc_cmd(CMD9, 0, SDC_R1);
        APP_ERROR_CHECK(err_code);
        PT_YIELD(SDC_PT);
        SDC_RESP_CHECK(SDC_PT, r1);

        p_rx_data += SDC_R1_LEN;
        rx_length -= SDC_R1_LEN;
        PT_SPAWN(SDC_PT, SDC_PT_SUB, sdc_pt_sub_data_read(p_rx_data, rx_length, \
                                                          16, &sub_exit_code));
        SDC_RESULT_CHECK(SDC_PT, sub_exit_code);

        m_cb.info.num_blocks = sdc_calculate_size(m_cb.work_buf);
        m_cb.info.block_len  = SDC_SECTOR_SIZE;

        SDC_BREAK(SDC_PT, SDC_SUCCESS);
    }
    PT_END(SDC_PT)
}


/**
 * @brief Data read co-routine.
 *
 * @param[in] p_rx_data     Pointer to the data received in last transaction.
 * @param[in] rx_length     Received data length.
 * @param[out] p_exit_code  Pointer to the routine exit code variable. Valid only if the thread has exited.
 *
 * @return    Protothread exit code. Zero if protothread is running and non-zero if exited.
 */
static PT_THREAD(sdc_pt_read(uint8_t * p_rx_data,
                             uint8_t rx_length,
                             sdc_result_t * p_exit_code))
{
    uint8_t r1;
    ret_code_t err_code;
    sdc_result_t sub_exit_code;

    PT_BEGIN(SDC_PT);
    while (1)
    {
        r1 = p_rx_data[0];
        SDC_RESP_CHECK(SDC_PT, r1);

        p_rx_data += SDC_R1_LEN;
        rx_length -= SDC_R1_LEN;

        // Run the block read subroutine.
        PT_SPAWN(SDC_PT, SDC_PT_SUB, sdc_pt_sub_data_read(p_rx_data, rx_length,
                                                          SDC_SECTOR_SIZE,
                                                          &sub_exit_code));
        SDC_RESULT_CHECK(SDC_PT, sub_exit_code);

        if (m_cb.state.rw_op.block_count > 1)
        {
            // Send the STOP_TRANSMISSION command in multiple block read mode.
            err_code = sdc_cmd(CMD12, 0, SDC_R1);
            APP_ERROR_CHECK(err_code);
            PT_YIELD(SDC_PT);
        }

        SDC_BREAK(SDC_PT, SDC_SUCCESS);
    }
    PT_END(SDC_PT)
}


/**
 * @brief Data write co-routine.
 *
 * @param[in] p_rx_data     Pointer to the data received in last transation.
 * @param[in] rx_length     Received data length.
 * @param[out] p_exit_code  Pointer to the routine exit code variable. Valid only if the thread has exited.
 *
 * @return    Protothread exit code. Zero if protothread is running and non-zero if exited.
 */
static PT_THREAD(sdc_pt_write(uint8_t * rx_data,
                              uint8_t rx_length,
                              sdc_result_t * p_exit_code))
{
    ret_code_t err_code;
    PT_BEGIN(SDC_PT);
    while (1)
    {
        uint8_t r1;
        r1 = rx_data[0];
        SDC_RESP_CHECK(SDC_PT, r1);
        if (m_cb.info.type.version != SDC_TYPE_MMCV3 && m_cb.state.rw_op.block_count > 1)
        {
            err_code = sdc_cmd(CMD25, m_cb.state.rw_op.address, SDC_R1);
            APP_ERROR_CHECK(err_code);
            PT_YIELD(SDC_PT);
            r1 = rx_data[0];
            SDC_RESP_CHECK(SDC_PT, r1);
        }

        m_cb.state.rw_op.blocks_left = m_cb.state.rw_op.block_count;
        while (m_cb.state.rw_op.blocks_left)
        {
            m_cb.state.rw_op.position = 0;
            m_cb.state.bus_state = SDC_BUS_DATA;

            // Send block start token.
            m_cb.cmd_buf[0] = SDC_EMPTY_BYTE;
            m_cb.cmd_buf[1] = (m_cb.state.rw_op.block_count > 1) ? SDC_TOKEN_START_BLOCK_MULT
                                                           : SDC_TOKEN_START_BLOCK;
            sdc_spi_transfer(m_cb.cmd_buf, 2, m_cb.rsp_buf, 2);
            PT_YIELD(SDC_PT);

            // Send the data block.
            while (m_cb.state.rw_op.position < SDC_SECTOR_SIZE)
            {
                {
                    uint16_t chunk_size = SDC_SECTOR_SIZE - m_cb.state.rw_op.position;
                    if (chunk_size > SDC_SPI_MTU)
                    {
                        chunk_size = SDC_SPI_MTU;
                    }
                    sdc_spi_transfer(&m_cb.state.rw_op.buffer[m_cb.state.rw_op.position],
                                     chunk_size,
                                     m_cb.rsp_buf,
                                     1);
                    m_cb.state.rw_op.position += chunk_size;
                }
                PT_YIELD(SDC_PT);
            }
            m_cb.state.rw_op.buffer += SDC_SECTOR_SIZE;

            // Send the dummy CRC (2 bytes) and receive data response token (1 byte).
            m_cb.state.bus_state = SDC_BUS_DATA_WAIT;
            sdc_spi_transfer(m_cb.cmd_buf, 1,
                             m_cb.rsp_buf, 3);
            PT_YIELD(SDC_PT);

            {
                uint8_t token = m_cb.rsp_buf[2] & SDC_TOKEN_DATA_RESP_MASK;
                if (token != SDC_TOKEN_DATA_RESP_ACCEPTED)
                {
                    if (token == SDC_TOKEN_DATA_RESP_CRC_ERR
                        || token == SDC_TOKEN_DATA_RESP_DATA_ERR)
                    {
                        SDC_BREAK(SDC_PT, SDC_ERROR_DATA);
                    }
                    else
                    {
                        SDC_BREAK(SDC_PT, SDC_ERROR_COMMUNICATION);
                    }
                }
            }

            // Wait for the card to complete the write process.
            m_cb.state.retry_count = 0;
            while (m_cb.state.bus_state == SDC_BUS_DATA_WAIT)
            {
                ++m_cb.state.retry_count;
                if (m_cb.state.retry_count > SDC_MAX_RETRY_COUNT)
                {
                    SDC_BREAK(SDC_PT, SDC_ERROR_TIMEOUT);
                }

                sdc_spi_transfer(m_cb.cmd_buf, 1,
                                 m_cb.rsp_buf, SDC_DATA_WAIT_TX_SIZE);
                PT_YIELD(SDC_PT);

                for (uint32_t i = 0; i < rx_length; ++i)
                {
                    if (rx_data[i] != 0x00)
                    {
                        m_cb.state.bus_state = SDC_BUS_IDLE;
                        break;
                    }
                }
            }

            --m_cb.state.rw_op.blocks_left;
        }

        if (m_cb.state.rw_op.block_count > 1)
        {
            // Send STOP_TRAN token + padding byte when writing multiple blocks.
            m_cb.cmd_buf[0] = SDC_EMPTY_BYTE;
            m_cb.cmd_buf[1] = SDC_TOKEN_STOP_TRAN;
            sdc_spi_transfer(m_cb.cmd_buf, 2,
                             m_cb.rsp_buf, 3);
            PT_YIELD(SDC_PT);

            m_cb.state.retry_count = 0;
            m_cb.state.bus_state = SDC_BUS_DATA_WAIT;

            // Wait for the card to complete the write process.
            while (m_cb.state.bus_state == SDC_BUS_DATA_WAIT)
            {
                ++m_cb.state.retry_count;
                if (m_cb.state.retry_count > SDC_MAX_RETRY_COUNT)
                {
                    SDC_BREAK(SDC_PT, SDC_ERROR_TIMEOUT);
                }

                sdc_spi_transfer(m_cb.cmd_buf, 1,
                                 m_cb.rsp_buf, SDC_DATA_WAIT_TX_SIZE);
                PT_YIELD(SDC_PT);

                for (uint32_t i = 0; i < rx_length; ++i)
                {
                    if (rx_data[i] != 0x00)
                    {
                        m_cb.state.bus_state = SDC_BUS_IDLE;
                        break;
                    }
                }
            }
        }

        SDC_BREAK(SDC_PT, SDC_SUCCESS);
    }
    PT_END(SDC_PT)
}


/**
 * @brief SPI event handler.
 *
 * @param[in] p_event       Pointer to the SPI event structure.
 */
static void spi_handler(nrf_drv_spi_evt_t const * p_event,
                        void *                    p_context)
{
    uint8_t * rx_data = p_event->data.done.p_rx_buffer;
    uint8_t rx_length = p_event->data.done.rx_length;

    if (!m_cb.state.rw_op.blocks_left)
    {
        // Deassert CS pin if not in active data transfer.
        SDC_CS_DEASSERT();
    }

    if (m_cb.state.bus_state == SDC_BUS_ACMD || m_cb.state.bus_state == SDC_BUS_CMD)
    {
        // Find the beginning of a response.
        ASSERT(rx_length > SDC_COMMAND_LEN);
        rx_length -= SDC_COMMAND_LEN;
        rx_data   += SDC_COMMAND_LEN;

        if (p_event->data.done.p_tx_buffer[0] == CMD12)
        {
            // Ignore the first byte if CMD12 was sent.
            if (rx_length)
            {
                --rx_length;
                ++rx_data;
            }
        }

        while (rx_length && rx_data[0] == SDC_EMPTY_BYTE)
        {
            --rx_length;
            ++rx_data;
        }
        if (rx_length == 0)
        {
            if (p_event->data.done.p_tx_buffer[0] == CMD12)
            {
                // Ignore invalid reply on CMD12.
                ++rx_length;
                --rx_data;
            }
            else
            {
                rx_data = NULL;
            }
        }

        if (!rx_data && m_cb.state.op != SDC_OP_RESET)
        {
            // Command response missing.
            sdc_evt_t evt;
            evt.result = SDC_ERROR_NOT_RESPONDING;
            switch(m_cb.state.op)
            {
                case SDC_OP_RESET:
                case SDC_OP_IDENTIFICATION:
                    evt.type      = SDC_EVT_INIT;
                    m_cb.state.op = SDC_OP_IDLE;
                    APP_ERROR_CHECK(app_sdc_uninit());
                    break;
                case SDC_OP_READ:
                    evt.type      = SDC_EVT_READ;
                    break;
                case SDC_OP_WRITE:
                    evt.type      = SDC_EVT_WRITE;
                    break;
                default:
                    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
                    break;
            }

            SDC_CS_DEASSERT();
            m_cb.state.op = SDC_OP_IDLE;
            m_cb.handler(&evt);
            return;
        }

        if (m_cb.state.bus_state == SDC_BUS_ACMD)
        {
            // Check the status of CMD55 and send the scheduled command if no errors has been reported.
            m_cb.state.bus_state = SDC_BUS_CMD;
            uint8_t r1 = rx_data[0];
            if (!(r1 & (~SDC_FLAG_IN_IDLE_STATE)))
            {
                sdc_spi_transfer(m_cb.cmd_buf + SDC_COMMAND_LEN, SDC_COMMAND_LEN,
                                 m_cb.rsp_buf, SDC_COMMAND_LEN + SDC_MAX_NCR + m_cb.state.rsp_len);
                return;
            }
        }
        m_cb.state.bus_state = SDC_BUS_IDLE;
    }

    sdc_result_t exit_code = SDC_ERROR_INTERNAL;
    sdc_evt_t evt;
    switch(m_cb.state.op)
    {
        case SDC_OP_RESET:
            m_cb.state.op = SDC_OP_IDENTIFICATION;
            PT_INIT(SDC_PT);
            //lint -e{616}
        case SDC_OP_IDENTIFICATION:
            if (!PT_SCHEDULE(sdc_pt_identification(rx_data, rx_length, &exit_code)))
            {
                evt.type      = SDC_EVT_INIT;
                evt.result    = exit_code;
                m_cb.state.op = SDC_OP_IDLE;
                SDC_CS_DEASSERT();
                if (exit_code != SDC_SUCCESS)
                {
                    // Initialization process failed. Roll back to uninitialized state.
                    APP_ERROR_CHECK(app_sdc_uninit());
                }
                sdc_spi_hispeed();
                m_cb.handler(&evt);
            }
            break;
        case SDC_OP_READ:
            if (!PT_SCHEDULE(sdc_pt_read(rx_data, rx_length, &exit_code)))
            {
                evt.type      = SDC_EVT_READ;
                evt.result    = exit_code;
                m_cb.state.op = SDC_OP_IDLE;
                m_cb.state.rw_op.block_count = 0;
                m_cb.state.rw_op.blocks_left = 0;
                m_cb.state.bus_state = SDC_BUS_IDLE;
                SDC_CS_DEASSERT();
                m_cb.handler(&evt);
            }
            break;
        case SDC_OP_WRITE:
            if (!PT_SCHEDULE(sdc_pt_write(rx_data, rx_length, &exit_code)))
            {
                evt.type      = SDC_EVT_WRITE;
                evt.result    = exit_code;
                m_cb.state.op = SDC_OP_IDLE;
                m_cb.state.bus_state = SDC_BUS_IDLE;
                m_cb.state.rw_op.block_count = 0;
                m_cb.state.rw_op.blocks_left = 0;
                SDC_CS_DEASSERT();
                m_cb.handler(&evt);
            }
            break;
        default:
            APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
            break;
    }

    return;
}


ret_code_t app_sdc_block_read(uint8_t * p_buf, uint32_t block_address, uint16_t block_count)
{
    ASSERT(p_buf);

    if (m_cb.state.op == SDC_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (m_cb.state.op != SDC_OP_IDLE)
    {
        return NRF_ERROR_BUSY;
    }
    if (block_count == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_cb.state.op = SDC_OP_READ;

    if (!m_cb.info.type.sdhc)
    {
        m_cb.state.rw_op.address = block_address * SDC_SECTOR_SIZE;
    }
    else
    {
        m_cb.state.rw_op.address = block_address;
    }
    m_cb.state.rw_op.buffer = p_buf;
    m_cb.state.rw_op.block_count = block_count;
    m_cb.state.rw_op.blocks_left = block_count;

    PT_INIT(&m_cb.state.pt);
    uint8_t command = (block_count > 1) ? CMD18 : CMD17;
    ret_code_t err_code = sdc_cmd(command, m_cb.state.rw_op.address, SDC_R1);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}


ret_code_t app_sdc_block_write(uint8_t const * p_buf, uint32_t block_address, uint16_t block_count)
{
    ASSERT(p_buf);

    if (m_cb.state.op == SDC_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (m_cb.state.op != SDC_OP_IDLE)
    {
        return NRF_ERROR_BUSY;
    }
    if (block_count == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    m_cb.state.op = SDC_OP_WRITE;

    if (!m_cb.info.type.sdhc)
    {
        m_cb.state.rw_op.address = block_address * 512uL;
    }
    else
    {
        m_cb.state.rw_op.address = block_address;
    }
    m_cb.state.rw_op.buffer = (uint8_t *) p_buf;
    m_cb.state.rw_op.block_count = block_count;
    m_cb.state.rw_op.blocks_left = block_count;

    PT_INIT(&m_cb.state.pt);

    ret_code_t err_code;
    if (block_count == 1)
    {
        err_code = sdc_cmd(CMD24, m_cb.state.rw_op.address, SDC_R1);

        APP_ERROR_CHECK(err_code);
        return NRF_SUCCESS;
    }

    if (m_cb.info.type.version == SDC_TYPE_MMCV3)
    {
        // Start multiple block write.
        err_code = sdc_cmd(CMD25, m_cb.state.rw_op.address, SDC_R1);
    }
    else
    {
        // Set pre-erase for SD cards before sending CMD25.
        err_code = sdc_cmd(ACMD23, block_count, SDC_R1);
    }

    APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}


ret_code_t app_sdc_init(app_sdc_config_t const * const p_config, sdc_event_handler_t event_handler)
{
    if (m_cb.state.op != SDC_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if ((!event_handler)
        || (p_config->cs_pin == NRF_DRV_SPI_PIN_NOT_USED)
        || (p_config->miso_pin == NRF_DRV_SPI_PIN_NOT_USED)
        || (p_config->mosi_pin == NRF_DRV_SPI_PIN_NOT_USED)
        || (p_config->sck_pin == NRF_DRV_SPI_PIN_NOT_USED))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    ret_code_t err_code;
    ASSERT(p_config->cs_pin && p_config->miso_pin
           && p_config->mosi_pin && p_config->sck_pin);

    // Configure chip select pin.
    m_cb.cs_pin = p_config->cs_pin;
    nrf_gpio_cfg_output(m_cb.cs_pin);
    SDC_CS_DEASSERT();

    const nrf_drv_spi_config_t spi_cfg = {
                            .sck_pin      = p_config->sck_pin,
                            .mosi_pin     = p_config->mosi_pin,
                            .miso_pin     = p_config->miso_pin,
                            .ss_pin       = NRF_DRV_SPI_PIN_NOT_USED,
                            .irq_priority = SPI_DEFAULT_CONFIG_IRQ_PRIORITY,
                            .orc          = 0xFF,
                            .frequency    = (nrf_drv_spi_frequency_t) APP_SDCARD_FREQ_INIT,
                            .mode         = NRF_DRV_SPI_MODE_0,
                            .bit_order    = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST,
                        };
    err_code = nrf_drv_spi_init(&m_spi, &spi_cfg, spi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    m_cb.handler            = event_handler;
    m_cb.state.op           = SDC_OP_RESET;
    m_cb.info.type.version  = SDC_TYPE_UNKNOWN;
    m_cb.info.type.sdhc     = 0;
    m_cb.state.bus_state    = SDC_BUS_IDLE;

    // Send 80 clocks with CS inactive to switch into SPI mode.
    m_cb.cmd_buf[0] = 0xFF;
    err_code = nrf_drv_spi_transfer(&m_spi, m_cb.cmd_buf, 1,
                                            m_cb.rsp_buf, 10);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}


ret_code_t app_sdc_uninit(void)
{
    if (m_cb.state.op == SDC_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (m_cb.state.op != SDC_OP_IDLE)
    {
        return NRF_ERROR_BUSY;
    }

    nrf_drv_spi_uninit(&m_spi);
    nrf_gpio_cfg_input(m_cb.cs_pin, NRF_GPIO_PIN_NOPULL);

    m_cb.state.bus_state = SDC_BUS_IDLE;
    m_cb.state.op = SDC_UNINITIALIZED;

    return NRF_SUCCESS;
}


bool app_sdc_busy_check(void)
{
    return ((m_cb.state.op != SDC_OP_IDLE) && (m_cb.state.op != SDC_UNINITIALIZED));
}


app_sdc_info_t const * app_sdc_info_get(void)
{
    if (m_cb.state.op >= SDC_OP_IDLE)
    {
        return &m_cb.info;
    }
    return NULL;
}

#endif //APP_SDCARD_ENABLED
